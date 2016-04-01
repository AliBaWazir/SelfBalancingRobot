#include "motor_driver.h"

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

    memset(&control_packet, 0, sizeof(motor_driver_control_packet_t));

    //check if the serial port is available before constructing the packet
    if (!(Serial1.available())) {
        Serial.println("ERROR>> motor_driver_move_stepper: serial1 is not available.");
        return false;
  
    }

    //construct the control packet
    control_packet.packet_id= 0xFF;
    if(selected_motor==SELECTED_MOTOR_BOTH){
      
        control_packet.left_motor_steps= steps_count;
        control_packet.right_motor_steps= steps_count;
        
    } else if (selected_motor==SELECTED_MOTOR_RIGHT){
        
        control_packet.left_motor_steps= -(steps_count);
        control_packet.right_motor_steps= steps_count;
        
    } else if(selected_motor==SELECTED_MOTOR_LEFT){
        control_packet.left_motor_steps= steps_count;
        control_packet.right_motor_steps= -(steps_count);
    } else{
        Serial.println("ERROR>> motor_driver_move_stepper: selected_motor is UNKNOWN");
        ret=false;
    }

    if (ret){
        //send the control packet
        if (Serial1.write((uint8_t*)(&control_packet), sizeof(motor_driver_control_packet_t))!= sizeof(motor_driver_control_packet_t)){
            
            Serial.println("ERROR>> motor_driver_move_stepper: failed to write control_packet to the serial port");
            if (!driver_in_testing_mode){
                ret=false;
            }
            
        }
    }
    

    return ret;
}

