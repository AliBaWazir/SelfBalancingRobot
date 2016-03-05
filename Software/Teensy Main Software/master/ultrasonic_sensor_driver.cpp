
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
int maximumRange  = 200; // Maximum range needed
int minimumRange  = 0; // Minimum range needed
long duration, distance; // Duration used to calculate distance

/****************************************************************************************
 * STATIC FUNCTION PROTOTYPES
 ***************************************************************************************/






 /****************************************************************************************
 * STATIC DEBUG AND TEST FUNCTIONS
 ****************************************************************************************/


 
/****************************************************************************************
 * STATIC FUNCTIONS
 ***************************************************************************************/



/****************************************************************************************
 * PUBLIC FUNCTIONS
 ***************************************************************************************/
bool ultrasonic_sensor_driver_init(){
    bool ret = true;
    
    pinMode(trigPin_front_sensor, OUTPUT);
    pinMode(echoPin_front_sensor, INPUT);
    pinMode(trigPin_back_sensor, OUTPUT);
    pinMode(echoPin_back_sensor, INPUT);
    pinMode(LEDPin, OUTPUT); // Use LED indicator (if required)
    //pinMode(BrakeA, OUTPUT);
    //pinMode(DIRA, OUTPUT);
  
    //pinMode(BrakeB, OUTPUT);
    //pinMode (DIRB, OUTPUT);

    return ret;
}

bool ultrasonic_sensor_get_data(){
    bool ret = true;

    /* The following trigPin/echoPin cycle is used to determine the
    distance of the nearest object by bouncing soundwaves off of it. */ 
    digitalWrite(trigPin_front_sensor, LOW); 
    delayMicroseconds(2); 
    digitalWrite(trigPin_front_sensor, HIGH);
    delayMicroseconds(10); 
 
    digitalWrite(trigPin_front_sensor, LOW);
    duration = pulseIn(echoPin_front_sensor, HIGH);
 
    //Calculate the distance (in cm) based on the speed of sound.
    distance = duration/58.2;
    Serial.print("distance for front sensor = ");
    Serial.println(distance);
 
    if (distance >= maximumRange || distance <= minimumRange){
        /* Send a negative number to computer and Turn LED ON 
        to indicate "out of range" */
        Serial.println("-1");
        digitalWrite(LEDPin, HIGH); 
         //Backword();   
   } else {
        /* Send the distance to the computer using Serial protocol, and
        turn LED OFF to indicate successful reading. */
        //Serial.println(distance);
        digitalWrite(LEDPin, LOW); 
        //Farward();  
   }
    /* The following trigPin/echoPin cycle is used to determine the
    distance of the nearest object by bouncing soundwaves off of it. */ 
    digitalWrite(trigPin_back_sensor, LOW); 
    delayMicroseconds(2); 
    digitalWrite(trigPin_back_sensor, HIGH);
    delayMicroseconds(10); 
 
    digitalWrite(trigPin_back_sensor, LOW);
    duration = pulseIn(echoPin_back_sensor, HIGH);
    //Serial.println(duration);
    
    //Calculate the distance (in cm) based on the speed of sound.
    distance = duration/58.2;
    Serial.print("distance for back sensor = ");
    Serial.println(distance);
 
    if (distance >= maximumRange || distance <= minimumRange){
        /* Send a negative number to computer and Turn LED ON 
        to indicate "out of range" */
        Serial.println("-1");
        digitalWrite(LEDPin, HIGH); 
        //Farward();   
   } else {
        /* Send the distance to the computer using Serial protocol, and
        turn LED OFF to indicate successful reading. */
        //Serial.println(distance);
        digitalWrite(LEDPin, LOW); 
        //Backword();
    }         //Delay 50ms before next reading.
     delay(50);

    return ret;
}



