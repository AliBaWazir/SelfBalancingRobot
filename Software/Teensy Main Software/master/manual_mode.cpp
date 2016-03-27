#include "manual_mode.h"
#include "ultrasonic_sensor_driver.h"
#include "display_driver.h"
#include "motor_driver.h"


/****************************************************************************************
 * DEFINES AND TYPE DEFINITIONS
 ****************************************************************************************/

/****************************************************************************************
 * STATIC FUNCTION PROTOTYPES
 ***************************************************************************************/
static manual_mode_error_e direct_robot_given_manual_command(manual_command_e command_type);

/****************************************************************************************
 * STATIC VARIABLES
 ***************************************************************************************/


/****************************************************************************************
 * STATIC FUNCTIONS
 ***************************************************************************************/
static manual_mode_error_e direct_robot_given_manual_command(manual_command_e command_type){

    manual_mode_error_e retcode = MANUAL_MODE_OK;
    
    switch (command_type){
        case MANUAL_FORWARD:
            //check for any obtsacale in the front
            if (!ultrasonic_sensor_check_clear_path(ULTRASONIC_SENSOR_ACTIVE_FRONT)){
                //an obstacle is detected in the front
                retcode = MANUAL_MODE_ERROR_OBSTACLE;
            } else{
                if (!motor_driver_move_stepper(SELECTED_MOTOR_BOTH, DEFAULT_STEPPER_DISTANCE, DEFAULT_STEPPER_VELOCITY)){
                    retcode = MANUAL_MODE_ERROR_MOTOR_FAILED;
                }
            }
        break;

        case MANUAL_RIGHT:
            if (!motor_driver_move_stepper(SELECTED_MOTOR_LEFT, DEFAULT_STEPPER_DISTANCE, DEFAULT_STEPPER_VELOCITY)){
                retcode = MANUAL_MODE_ERROR_MOTOR_FAILED;
            }
        break;
        
        case MANUAL_BACKWARD:
            //check for any obtsacale in the back
            if (!ultrasonic_sensor_check_clear_path(ULTRASONIC_SENSOR_ACTIVE_BACK)){
                //an obstacle is detected in the front
                retcode = MANUAL_MODE_ERROR_OBSTACLE;
            } else{
                if (!motor_driver_move_stepper(SELECTED_MOTOR_BOTH, -DEFAULT_STEPPER_DISTANCE, DEFAULT_STEPPER_VELOCITY)){
                    retcode = MANUAL_MODE_ERROR_MOTOR_FAILED;
                }
            }
        break;

        case MANUAL_LEFT:
            if (!motor_driver_move_stepper(SELECTED_MOTOR_RIGHT, DEFAULT_STEPPER_DISTANCE, DEFAULT_STEPPER_VELOCITY)){
                retcode = MANUAL_MODE_ERROR_MOTOR_FAILED;
            }
        break;

        default:
            Serial.print("ERROR>> direct_robot_given_manual_command: command is unknown");
            retcode = MANUAL_MODE_ERROR_COMMAND_UNKNOWN;
        break;
        
            
            
    }

    return retcode;
}

/****************************************************************************************
 * PUBLIC FUNCTIONS
 ***************************************************************************************/
bool manual_mode_drivers_init(){

  if (!ultrasonic_sensor_driver_init()){
      Serial.println("ERROR>> manual_mode_drivers_init: ultrasonic_sensor_driver_init failed");
      return false;
  }
  if (!display_driver_init()){
      Serial.println("ERROR>> manual_mode_drivers_init: display_driver_init failed");
      return false;
  }  
  //PLEASE INITIALIZE ALL OTHER DRIVERS HERE:


  return true;
}


manual_mode_error_e manual_mode_run(manual_command_e control_command){
    manual_mode_error_e manual_mode_error = MANUAL_MODE_OK;
    
    Serial.println("INFO>> manual_mode_run: called");

    manual_mode_error = direct_robot_given_manual_command(control_command);
    
    return manual_mode_error;
}



