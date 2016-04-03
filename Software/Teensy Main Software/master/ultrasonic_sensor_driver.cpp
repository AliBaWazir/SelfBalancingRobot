
#include "ultrasonic_sensor_driver.h"

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
const int echoPin_back_sensor   = 22; //  Echo Pin for the back sensor
const int echoPin_front_sensor  = 20; // Echo Pin for the front sensor
const int trigPin_back_sensor   = 23; // Trigger Pin for the back sensor 
const int trigPin_front_sensor  = 21; // Trigger Pin for the front sensor 
const int LEDPin                = 13; // Onboard LED


/****************************************************************************************
 * GLOBAL VARIABLES
 ***************************************************************************************/

 
/****************************************************************************************
 * STATIC VARIABLES
 ****************************************************************************************/
static int maximumRange  = 30; // Maximum range needed
static int minimumRange  = 0; // Minimum range needed
static long duration, distance; // Duration used to calculate distance

static bool ultrasonic_sensor_driver_initialized   = false;
static bool driver_in_testing_mode                 = false;


/****************************************************************************************
 * STATIC FUNCTION PROTOTYPES
 ***************************************************************************************/




 
/****************************************************************************************
 * STATIC FUNCTIONS
 ***************************************************************************************/



/****************************************************************************************
 * PUBLIC FUNCTIONS
 ***************************************************************************************/
bool ultrasonic_sensor_driver_init(){
    bool ret = true;

    if(!ultrasonic_sensor_driver_initialized){
        pinMode(trigPin_front_sensor, OUTPUT);
        pinMode(echoPin_front_sensor, INPUT);
        pinMode(trigPin_back_sensor, OUTPUT);
        pinMode(echoPin_back_sensor, INPUT);
        pinMode(LEDPin, OUTPUT); // Use LED indicator (if required)
        //pinMode(BrakeA, OUTPUT);
        //pinMode(DIRA, OUTPUT);
  
        //pinMode(BrakeB, OUTPUT);
        //pinMode (DIRB, OUTPUT);

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

