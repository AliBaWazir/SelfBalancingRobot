#include "motor_driver.h"
#include "led_driver.h"

/****************************************************************************************
 * HARDWARE PORTS ASSIGNMENTS
 ****************************************************************************************/



/****************************************************************************************
 * DEFINES
 ***************************************************************************************/
#define MAX_SIGNED_BYTE_VALUE 127
#define MIN_SIGNED_BYTE_VALUE -127

#define PACKET_ID_FIRST_BYTE 0xEF
#define PACKET_ID_SECOND_BYTE 0xFE


 
/****************************************************************************************
 * STATIC VARIABLES
 ****************************************************************************************/
 static bool motor_driver_initialized                = false;
 static bool driver_in_testing_mode                  = false;


/****************************************************************************************
 * STATIC FUNCTION PROTOTYPES
 ***************************************************************************************/




 
/****************************************************************************************
 * STATIC FUNCTIONS
 ***************************************************************************************/
static void debug_print_control_backet_data(motor_driver_control_packet_t *control_packet){

  if(control_packet==NULL){
      return;
  }

  Serial.println("INFO>> ----------------------------- PACKET DATA --------------------------------");
  Serial.print("                         ID= ");
  Serial.print(control_packet->packet_id_first_byte, HEX);
  Serial.print(control_packet->packet_id_second_byte, HEX);
  Serial.print(" | LMS=");
  Serial.print(control_packet->left_motor_steps);
  Serial.print(" | RMS=");
  Serial.println(control_packet->right_motor_steps);

  Serial.println("INFO>> --------------------------------------------------------------------------");
  
}

/****************************************************************************************
 * PUBLIC FUNCTIONS
 ****************************************************************************************/
bool motor_driver_init(){
    bool ret = true;

    if(!motor_driver_initialized){
        //initialize serial port for bluetooth module
        Serial1.begin(115200);
        
        motor_driver_initialized = true;
    }

    return ret;
}

bool motor_driver_move_stepper(motor_driver_selected_motor_e selected_motor, int steps_count, int stepper_speed){
    bool                                 ret = true;
    motor_driver_control_packet_t        control_packet;
    uint8_t                              LED_index;

    Serial.println("INFO>> motor_driver_move_stepper: is called");
    memset(&control_packet, 0, sizeof(motor_driver_control_packet_t));
    
    //construct the control packet
    control_packet.packet_id_first_byte= PACKET_ID_FIRST_BYTE;
    control_packet.packet_id_second_byte= PACKET_ID_SECOND_BYTE;
    
    if(selected_motor==SELECTED_MOTOR_BOTH){
      
        if(steps_count<MIN_SIGNED_BYTE_VALUE){
            control_packet.left_motor_steps= MIN_SIGNED_BYTE_VALUE;
            control_packet.right_motor_steps= MIN_SIGNED_BYTE_VALUE;
        } else if (steps_count > MAX_SIGNED_BYTE_VALUE){
            control_packet.left_motor_steps= MAX_SIGNED_BYTE_VALUE;
            control_packet.right_motor_steps=MAX_SIGNED_BYTE_VALUE;
        } else{
            control_packet.left_motor_steps= steps_count;
            control_packet.right_motor_steps= steps_count;
        }
        
        if(steps_count==0){
            LED_index= 100; //no LED has this value==> trun them all off
        } else{
            LED_index= 4;
        }
        
    } else if (selected_motor==SELECTED_MOTOR_RIGHT){

        if(steps_count<MIN_SIGNED_BYTE_VALUE){
            control_packet.left_motor_steps= -MIN_SIGNED_BYTE_VALUE;
            control_packet.right_motor_steps= MIN_SIGNED_BYTE_VALUE;
        } else if (steps_count > MAX_SIGNED_BYTE_VALUE){
            control_packet.left_motor_steps= -MAX_SIGNED_BYTE_VALUE;
            control_packet.right_motor_steps= MAX_SIGNED_BYTE_VALUE;
        } else{
            control_packet.left_motor_steps= -steps_count;
            control_packet.right_motor_steps= steps_count;
        }

        //control_packet.left_motor_steps= -(steps_count);
        //control_packet.right_motor_steps= steps_count;
        LED_index= 8;
        
    } else if(selected_motor==SELECTED_MOTOR_LEFT){
      
        if(steps_count<MIN_SIGNED_BYTE_VALUE){
            control_packet.left_motor_steps= MIN_SIGNED_BYTE_VALUE;
            control_packet.right_motor_steps= -MIN_SIGNED_BYTE_VALUE;
        } else if (steps_count > MAX_SIGNED_BYTE_VALUE){
            control_packet.left_motor_steps= MAX_SIGNED_BYTE_VALUE;
            control_packet.right_motor_steps= -MAX_SIGNED_BYTE_VALUE;
        } else{
            control_packet.left_motor_steps= steps_count;
            control_packet.right_motor_steps= -steps_count;
        }
        //control_packet.left_motor_steps= steps_count;
        //control_packet.right_motor_steps= -(steps_count);
        LED_index= 0;
        
    } else{
        Serial.println("ERROR>> motor_driver_move_stepper: selected_motor is UNKNOWN");
        ret=false;
    }

    if (ret){

        //turn the corresponding LED on to indicate turning, the middle LED to indicate straight movement, or none to indicate stopping
        if (driver_in_testing_mode){
            ret= led_driver_turn_led_on_others_off(LED_index);
        } else{

            //test
            //Serial1.write(0xAA);
            //Serial.println("INFO>> motor_driver_move_stepper: >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> sent 0xAA>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>");
            //Serial1.write(0xEF);
            //Serial1.write(0xFE);
            //Serial1.write(0xFF);
            //Serial1.write(0xFF);
            //Serial1.write(0xFF);
            //Serial1.write(0xC3);
            //Serial1.write(0x4C);
            //end of test
            
       
            //send the control packet
            if (Serial1.write((uint8_t*)(&control_packet), sizeof(motor_driver_control_packet_t))!= sizeof(int32_t)){           
                Serial.println("ERROR>> motor_driver_move_stepper: failed to write control_packet to the serial port");
                if (!driver_in_testing_mode){
                    ret=false;
               }
            }
          
        }
        
        debug_print_control_backet_data(&control_packet);
    }
    

    return ret;
}

