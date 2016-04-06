
#include "ultrasonic_sensor_driver.h"
#include <NewPing.h>
//#include <NewPingT.h>

/****************************************************************************************
 * HARDWARE PORTS ASSIGNMENTS
 ****************************************************************************************/
/*
 HC-SR04 Ping distance sensor:
 VCC to arduino 5v 
 GND to arduino GND
 Echo to Arduino pin 20 
 trigPin_front_sensor to Arduino pin 21
 trigPin_back_sensor to Arduino pin 23
 */
const int trigPin_back_sensor   = 21;//23; // Trigger Pin for the back sensor 
const int echoPin_back_sensor   = 20;//22; //  Echo Pin for the back sensor

const int trigPin_front_sensor  =23; //21; // Trigger Pin for the front sensor 
const int echoPin_front_sensor  =22; //20; // Echo Pin for the front sensor 

const int LEDPin                = 13; // Onboard LED


/****************************************************************************************
 * GLOBAL VARIABLES
 ***************************************************************************************/

#define MAX_DISTANCE 200
NewPing sonar_front(trigPin_front_sensor, echoPin_front_sensor, MAX_DISTANCE);
NewPing sonar_back(trigPin_back_sensor, echoPin_back_sensor, MAX_DISTANCE);
/****************************************************************************************
 * STATIC VARIABLES
 ****************************************************************************************/
static int maximumRange  = 30; // Maximum range needed
static int minimumRange  = 0; // Minimum range needed
//static long duration, distance; // Duration used to calculate distance

static bool ultrasonic_sensor_driver_initialized   = false;
static bool driver_in_testing_mode                 = false;


/****************************************************************************************
 * STATIC FUNCTION PROTOTYPES
 ***************************************************************************************/




 
/****************************************************************************************
 * STATIC FUNCTIONS
 ***************************************************************************************/
////////////////////////////////////////////////////////new code ///////////////////////////////////

 

volatile int pingVal_front = 0;
volatile int pingVal_back = 0;

volatile boolean front_sensor_changed = true;
volatile boolean back_sensor_changed = true;


// Echo pin falling edge interrupt
void sonarEchoISR_front()
{
    pingVal_front = sonar_front.ping_2();
    front_sensor_changed = true;
}

void sonarEchoISR_back()
{
    pingVal_back = sonar_back.ping_2();
    back_sensor_changed = true;
}



bool ultrasonic_sensor_check_clear_path(ultrasonic_sensor_active_direction_e active_direction){
  int uS        = 0;
  int distance  = 0;
  
  Serial.println(active_direction);
  switch (active_direction){
    case ULTRASONIC_SENSOR_ACTIVE_FRONT:
        
        if (front_sensor_changed){
            uS = pingVal_front;
            sonar_front.ping_trigger_2();
            front_sensor_changed = false;
        }
    break;
  
    case ULTRASONIC_SENSOR_ACTIVE_BACK:
         if (back_sensor_changed){
            uS = pingVal_back;
            sonar_back.ping_trigger_2();
            back_sensor_changed = false;
        }
    break;
  }

  distance= uS / US_ROUNDTRIP_CM;
  Serial.print(distance);
  Serial.println("cm");
  if (distance < maximumRange && distance > minimumRange){
      return false;
  }
  
  return true;
  
}
  

void ultrasonic_sensor_send_ping()
{
  sonar_front.ping_trigger_2();
  sonar_back.ping_trigger_2();
}


/****************************************************************************************
 * PUBLIC FUNCTIONS
 ***************************************************************************************/
bool ultrasonic_sensor_driver_init(){
    bool ret = true;

    if(!ultrasonic_sensor_driver_initialized){
        pinMode(LEDPin, OUTPUT); // Use LED indicator (if required)
        attachInterrupt(echoPin_front_sensor, sonarEchoISR_front, FALLING); 
        attachInterrupt(echoPin_back_sensor, sonarEchoISR_back, FALLING); 
        //sonar_front.ping_trigger_2();
        //sonar_back.ping_trigger_2();
        ultrasonic_sensor_send_ping();

        ultrasonic_sensor_driver_initialized = true;
    }

    return ret;
}




/*
//This function returns false if an obstacle is detected by the ultrasonic sensor in the requested direction
bool ultrasonic_sensor_check_clear_path(ultrasonic_sensor_active_direction_e active_direction){
    bool ret = true;

    if(driver_in_testing_mode){
        return true;
    }
    
    if (active_direction == ULTRASONIC_SENSOR_ACTIVE_FRONT){
         //The following trigPin/echoPin cycle is used to determine the distance of the nearest object by bouncing soundwaves off of it. 
        digitalWrite(trigPin_front_sensor, LOW); 
        delayMicroseconds(2); 
        digitalWrite(trigPin_front_sensor, HIGH);
        delayMicroseconds(10); 
 
        digitalWrite(trigPin_front_sensor, LOW);
        duration = pulseIn(echoPin_front_sensor, HIGH);
        Serial.print("duration = ");
        Serial.println(duration);

        //Calculate the distance (in cm) based on the speed of sound.
        
        distance = duration/58.2;
        Serial.print("distance for front sensor = ");
        Serial.println(distance);
 
        if (distance >= maximumRange || distance <= minimumRange){
            //Send a negative number to computer and Turn LED ON to indicate "out of range" 
            Serial.println("-1");
            digitalWrite(LEDPin, HIGH); 
            //Backword();
            
        } else {
            // Send the distance to the computer using Serial protocol, andturn LED OFF to indicate successful reading. 
            Serial.println(distance);
            digitalWrite(LEDPin, LOW); 
            //Farward(); 
            ret= false;   
        }
    } else if(active_direction == ULTRASONIC_SENSOR_ACTIVE_BACK){
        //The following trigPin/echoPin cycle is used to determine the distance of the nearest object by bouncing soundwaves off of it. 
        digitalWrite(trigPin_back_sensor, LOW); 
        delayMicroseconds(2); 
        digitalWrite(trigPin_back_sensor, HIGH);
        delayMicroseconds(10); 
 
        digitalWrite(trigPin_back_sensor, LOW);
        duration = pulseIn(echoPin_back_sensor, HIGH);
        Serial.println(duration);
    
        //Calculate the distance (in cm) based on the speed of sound.
        distance = duration/58.2;
        Serial.print("distance for back sensor = ");
        Serial.println(distance);
 
        if (distance >= maximumRange || distance <= minimumRange){
            //Send a negative number to computer and Turn LED ON to indicate "out of range" 
            Serial.println("-1");
            digitalWrite(LEDPin, HIGH); 
            //Farward();
        } else {
            // Send the distance to the computer using Serial protocol, and turn LED OFF to indicate successful reading. 
            //Serial.println(distance);
            digitalWrite(LEDPin, LOW); 
            //Backword();
            ret= false;
        }
    } else{
        Serial.println("ERROR>> ultrasonic_sensor_check_clear_path: active_direction has undefined value");           
    }
    
    //Delay 50ms before next reading.
     //delay(50);

    return ret;
}

*/

/*
//recently added by Ali

bool ultrasonic_sensor_check_clear_path(ultrasonic_sensor_active_direction_e active_direction){
    bool ret = true;
    unsigned long echo;
    unsigned long distance;

    Serial.println("INFO>> ultrasonic_sensor_check_clear_path: is called");
    if(driver_in_testing_mode){
        return true;
    }
    
    if (active_direction == ULTRASONIC_SENSOR_ACTIVE_FRONT){
        digitalWrite(trigPin_front_sensor, LOW); 
        delayMicroseconds(2); 
        digitalWrite(trigPin_front_sensor, HIGH);
        delayMicroseconds(5); 
        digitalWrite(trigPin_front_sensor, LOW);

        pinMode(echoPin_front_sensor, INPUT);        
        //digitalWrite(echoPin_front_sensor, HIGH); //turn on pull-up resistor
        
        echo = pulseIn(echoPin_front_sensor, HIGH, 10); //listen to echo which has a pulse of 10us
        Serial.print("echo = ");
        Serial.println(echo);

        //Calculate the distance (in cm) based on the speed of echo.
        
        distance = echo/58.138;
        Serial.print("distance for front sensor = ");
        Serial.println(distance);
 
        if (distance >= maximumRange || distance <= minimumRange){
            // Send a negative number to computer to indicate "out of range"
            digitalWrite(LEDPin, HIGH);            
        } else {
            // turn LED OFF to indicate successful reading. 
            digitalWrite(LEDPin, LOW); 
            ret= false;   
        } 
    }else if (active_direction == ULTRASONIC_SENSOR_ACTIVE_BACK){
        digitalWrite(trigPin_back_sensor, LOW); 
        delayMicroseconds(2); 
        digitalWrite(trigPin_back_sensor, HIGH);
        delayMicroseconds(5); 
        digitalWrite(trigPin_back_sensor, LOW);

        pinMode(echoPin_back_sensor, INPUT);        
        digitalWrite(echoPin_back_sensor, HIGH); //turn on pull-up resistor
        
        echo = pulseIn(echoPin_back_sensor, HIGH); //listen to echo which has a pulse of 10us
        Serial.print("echo = ");
        Serial.println(echo);

        //Calculate the distance (in cm) based on the speed of echo.
        
        distance = echo/58.138;
        Serial.print("distance for back sensor = ");
        Serial.println(distance);
 
        if (distance >= maximumRange || distance <= minimumRange){
            // Send a negative number to computer to indicate "out of range"
            digitalWrite(LEDPin, HIGH);            
        } else {
            //turn LED OFF to indicate successful reading. 
            digitalWrite(LEDPin, LOW); 
            ret= false;   
        }
    }

    return ret;
}

*/





