#include "motor_driver.h"
#include "led_driver.h"

/****************************************************************************************
 * HARDWARE PORTS ASSIGNMENTS
 ****************************************************************************************/



/****************************************************************************************
 * GLOBAL VARIABLES
 ***************************************************************************************/

 
/****************************************************************************************
 * STATIC VARIABLES
 ****************************************************************************************/
 static bool motor_driver_initialized                = false;
 static bool driver_in_testing_mode                  = true;


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
  Serial.print(control_packet->packet_id);
  Serial.print(" | LMS=");
  Serial.print(control_packet->left_motor_steps);
  Serial.print(" | RMS=");
  Serial.print(control_packet->right_motor_steps);
  Serial.print(" | UD=");
  Serial.println(control_packet->user_data);

  Serial.println("INFO>> --------------------------------------------------------------------------");
  
}


/****************************************************************************************
 * PUBLIC FUNCTIONS
 ****************************************************************************************/
bool motor_driver_init(){
    bool ret = true;

    if(!motor_driver_initialized){
        //initialize serial port for bluetooth module
        Serial1.begin(9600);
        
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

    //check if the serial port is available before constructing the packet
    if ((!Serial1.available()) && (!driver_in_testing_mode)) {
        Serial.println("ERROR>> motor_driver_move_stepper: serial1 is not available.");
        return false;
  
    }

    //construct the control packet
    control_packet.packet_id= 0xFF;
    if(selected_motor==SELECTED_MOTOR_BOTH){
      
        control_packet.left_motor_steps= steps_count;
        control_packet.right_motor_steps= steps_count;
        if(steps_count==0){
            LED_index= 100; //no LED has this value==> trun them all off
        } else{
            LED_index= 4;
        }
        
    } else if (selected_motor==SELECTED_MOTOR_RIGHT){
        
        control_packet.left_motor_steps= -(steps_count);
        control_packet.right_motor_steps= steps_count;
        LED_index= 8;
        
    } else if(selected_motor==SELECTED_MOTOR_LEFT){
      
        control_packet.left_motor_steps= steps_count;
        control_packet.right_motor_steps= -(steps_count);
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
            
            //send the control packet
            if (Serial1.write((uint8_t*)(&control_packet), sizeof(motor_driver_control_packet_t))!= sizeof(motor_driver_control_packet_t)){           
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

