
#include "led_driver.h"

/****************************************************************************************
 * HARDWARE PORTS ASSIGNMENTS
 ****************************************************************************************/
//Pins for the mouth
const int LED0_pin                = 9;
const int LED1_pin                = 26; //pin high but not the LED
const int LED2_pin                = 25; //pin high but not the LED
const int LED3_pin                = A11; //pin LOW==> not proberly soldered!
const int LED4_pin                = 31;
const int LED5_pin                = A12;//pin LOW==> not proberly soldered!
const int LED6_pin                = A13;
const int LED7_pin                = A10;
const int LED8_pin                = 17;

//Pins for other LEDs
const int LED_up_pin                = 3;
const int LED_right_pin             = 6;
const int LED_down_pin              = 5;
const int LED_left_pin              = 4;
/****************************************************************************************
 * GLOBAL VARIABLES
 ***************************************************************************************/

 
/****************************************************************************************
 * STATIC VARIABLES
 ****************************************************************************************/
static bool led_driver_initialized                   = false;
static bool driver_in_testing_mode                   = false;

static int led_lighting_array [LED_FRAME_COUNT][9]= {{1, 1, 1, 1, 1, 1, 1, 1, 1},
                                                     {0, 0, 0, 0, 1, 0, 0, 0, 0},
                                                     {0, 0, 0, 1, 1, 1, 0, 0, 0},
                                                     {0, 0, 1, 1, 1, 1, 1, 0, 0},
                                                     {0, 1, 1, 1, 1, 1, 1, 1, 0},
                                                     {0, 1, 1, 1, 1, 1, 1, 1, 0},
                                                     {0, 1, 1, 1, 1, 1, 1, 1, 0},
                                                     {1, 1, 1, 1, 1, 1, 1, 1, 1},
                                                     {0, 1, 1, 1, 1, 1, 1, 1, 0},
                                                     {0, 0, 1, 1, 1, 1, 1, 0, 0},
                                                     {0, 0, 0, 1, 1, 1, 0, 0, 0},
                                                     {0, 0, 0, 1, 1, 1, 0, 0, 0},
                                                     {0, 0, 0, 0, 1, 0, 0, 0, 0}};

static uint32_t discarded_led_update_count      = 5; //this varible will allow the LEDs to update their state in specific frequency
static uint8_t  current_led_frame               = 1;

                                      

/****************************************************************************************
 * STATIC FUNCTION PROTOTYPES
 ***************************************************************************************/




 
/****************************************************************************************
 * STATIC FUNCTIONS
 ***************************************************************************************/



/****************************************************************************************
 * PUBLIC FUNCTIONS
 ***************************************************************************************/
bool led_driver_init(){
    bool ret = true;

    if(!led_driver_initialized){
        //set pins mode
        pinMode(LED0_pin, OUTPUT);
        pinMode(LED1_pin, OUTPUT);
        pinMode(LED2_pin, OUTPUT);
        pinMode(LED3_pin, OUTPUT);
        pinMode(LED4_pin, OUTPUT);
        pinMode(LED5_pin, OUTPUT);
        pinMode(LED6_pin, OUTPUT);
        pinMode(LED7_pin, OUTPUT);
        pinMode(LED8_pin, OUTPUT);
        
        if (driver_in_testing_mode){
            digitalWrite(LED0_pin, HIGH);
            digitalWrite(LED1_pin, HIGH);
            digitalWrite(LED2_pin, HIGH);
            digitalWrite(LED3_pin, HIGH);
            digitalWrite(LED4_pin, HIGH);
            digitalWrite(LED5_pin, HIGH);
            digitalWrite(LED6_pin, HIGH);
            digitalWrite(LED7_pin, HIGH);
            digitalWrite(LED8_pin, HIGH);
        }
        
        
        led_driver_initialized = true;
    }

    return ret;
}

bool led_driver_continue_talking(){
    bool ret = true;

    Serial.println("INFO>> led_driver_continue_talking: is called ");
    discarded_led_update_count++;
    //Serial.println(discarded_led_update_count);
    
    if ((discarded_led_update_count>=MAX_DISCARDED_LED_UPDATES) && (current_led_frame<LED_FRAME_COUNT)){
        Serial.println("INFO>> led_driver_continue_talking:  discarded_led_update_count>=MAX_DISCARDED_LED_UPDATES");

        
        
        //TODO: toggle the pin
        //update LED state
        if (led_lighting_array[current_led_frame][0]==1){
            //turn on the corresponding LED
            digitalWrite(LED0_pin, HIGH);
        } else{
            digitalWrite(LED0_pin, LOW);
        }

        if (led_lighting_array[current_led_frame][1]==1){
            //digitalWrite(LED1_pin, HIGH);
        } else{
            //digitalWrite(LED1_pin, LOW);
        }
        
        if (led_lighting_array[current_led_frame][2]==1){
            //digitalWrite(LED2_pin, HIGH);
        } else{
            //digitalWrite(LED2_pin, LOW);
        }
        
        if (led_lighting_array[current_led_frame][3]==1){
            //digitalWrite(LED3_pin, HIGH);
        } else {
            //digitalWrite(LED3_pin, LOW);

        } 
        
        if (led_lighting_array[current_led_frame][4]==1){
            digitalWrite(LED4_pin, HIGH);
        } else {
            digitalWrite(LED4_pin, LOW);
        } 
        
        if (led_lighting_array[current_led_frame][5]==1){
            //digitalWrite(LED5_pin, HIGH);
        } else {
            //digitalWrite(LED5_pin, LOW);
          
        } 
        
        if (led_lighting_array[current_led_frame][6]==1){
            digitalWrite(LED6_pin, HIGH);
        } else {
            digitalWrite(LED6_pin, LOW);
        } 
        
        if (led_lighting_array[current_led_frame][7]==1){
            digitalWrite(LED7_pin, HIGH);
        } else {
            digitalWrite(LED7_pin, LOW);
        } 
        
        if (led_lighting_array[current_led_frame][8]==1){
            digitalWrite(LED8_pin, HIGH);
        } else{
            digitalWrite(LED8_pin, LOW);
        }

        //move the the next frame
        current_led_frame++;
        if(current_led_frame>=LED_FRAME_COUNT){
            current_led_frame=0;
        }

        discarded_led_update_count=0;
      
    }

    return ret;
}


bool led_driver_turn_led_on_others_off(int8_t LED){

    bool ret = true;

    Serial.println("INFO>> led_driver_turn_led_on_others_off: called");
    
    if (LED == 0){
        digitalWrite(LED0_pin, HIGH);
    } else{
        digitalWrite(LED0_pin, LOW);
    }

    if (LED == 1){
        digitalWrite(LED1_pin, HIGH);
    } else{
        digitalWrite(LED1_pin, LOW);
    }

    if (LED == 2){
        digitalWrite(LED2_pin, HIGH);
    } else{
        digitalWrite(LED2_pin, LOW);
    }
    
    if (LED == 3){
        digitalWrite(LED3_pin, HIGH);
    } else{
        digitalWrite(LED3_pin, LOW);
    }

    if (LED == 4){
        digitalWrite(LED4_pin, HIGH);
    } else{
        digitalWrite(LED4_pin, LOW);
    }

    if (LED == 5){
        digitalWrite(LED5_pin, HIGH);
    } else{
        digitalWrite(LED5_pin, LOW);
    }

    if (LED == 6){
        digitalWrite(LED6_pin, HIGH);
    } else{
        digitalWrite(LED6_pin, LOW);
    }

    if (LED == 7){
        digitalWrite(LED7_pin, HIGH);
    } else{
        digitalWrite(LED7_pin, LOW);
    }

    if (LED == 8){
        digitalWrite(LED8_pin, HIGH);
    } else{
        digitalWrite(LED8_pin, LOW);
    }

    return ret;
      
}

