/*
 * This is the master main of the teensy based code. 
 */
#include "line_following_mode.h"
#include "manual_mode.h"
#include "bluetooth_driver.h"



/****************************************************************************************
 * TYPE DEFINITIONS
 ****************************************************************************************/
typedef enum {
    STARTUP_MODE = 0,
    MANUAL_MODE,
    LINE_FOLLOWING_MODE,
    DEBUG_MODE
}robot_mode_e;


/****************************************************************************************
 * SATIC VARIABLES
 ****************************************************************************************/
static robot_mode_e current_robot_mode;
 
static bool line_following_mode_drivers_initialized  = false;
static bool manual_mode_drivers_initialized          = false;
static bool bluetooth_driver_initialized             = false;




/****************************************************************************************
 * STATIC FUNCTIONS
 ****************************************************************************************/
static bool get_current_robot_mode(){
    bool ret = true;
    bluetooth_module_data_e bluetooth_module_data= bluetooth_driver_get_data(BLUETOOTH_DRIVER_DATA_TYPE_MODE);

    if(bluetooth_module_data==BLUETOOTH_MODULE_DATA_ERROR){
        Serial.println("ERROR>> get_current_robot_mode: could not get the current robot mode from bluetooth module");
        ret = false;
    } else if(bluetooth_module_data==BLUETOOTH_MODULE_DATA_MODE_MANUAL){
        current_robot_mode= MANUAL_MODE;
    } else if(bluetooth_module_data==BLUETOOTH_MODULE_DATA_MODE_LINE_FOLLOWING){
        current_robot_mode= LINE_FOLLOWING_MODE;
    }

    return ret;
}
 

/****************************************************************************************
 * MAIN FUNCTIONS
 ****************************************************************************************/
void setup() {

  // initialize serial communications at 9600 bps
  Serial.begin(9600);

  // initialize all drivers
  if (line_following_mode_drivers_init()){
      line_following_mode_drivers_initialized= true;
  } else{
      Serial.println("ERROR>> setup: line_following_mode_drivers_init failed");
  }

  if (manual_mode_drivers_init()){
      manual_mode_drivers_initialized= true;
  } else{
      Serial.println("ERROR>> setup: manual_mode_drivers_init failed");
  }

  if (bluetooth_driver_init()){
      bluetooth_driver_initialized= true;
  } else{
      Serial.println("ERROR>> setup: bluetooth_driver_init failed");
  }

  Serial.println("INFO>> master: Setup is complete!");
}

void loop() {
  //Serial.println("INFO>> master: loop is called!");

  //check the current robot mode
  if(!get_current_robot_mode()){
      Serial.println("ERROR>> loop: failed to get the current robot mode");
  }
  
  switch (current_robot_mode){
      case STARTUP_MODE:
          ;
      break;
      
      case MANUAL_MODE:
          if(bluetooth_driver_initialized && manual_mode_drivers_initialized){
              manual_mode_error_e manual_mode_error = MANUAL_MODE_OK;
              
              //get the direction command from bluetooth module
              bluetooth_module_data_e direction_command = bluetooth_driver_get_data(BLUETOOTH_DRIVER_DATA_TYPE_DIRECTION);
              if (direction_command != BLUETOOTH_MODULE_DATA_ERROR){
                  manual_command_e tmp_command;
                  
                  switch (direction_command){
                      case BLUETOOTH_MODULE_DATA_DIRECTION_FORWARD:
                          tmp_command= MANUAL_FORWARD;
                      break;

                      case BLUETOOTH_MODULE_DATA_DIRECTION_RIGHT:
                          tmp_command= MANUAL_RIGHT;
                      break;

                      case BLUETOOTH_MODULE_DATA_DIRECTION_BACKWARD:
                          tmp_command= MANUAL_BACKWARD;
                      break;

                      case BLUETOOTH_MODULE_DATA_DIRECTION_LEFT:
                          tmp_command= MANUAL_LEFT;
                      break;
                  }
                  
                  manual_mode_error = manual_mode_run(tmp_command);
              }

              if (manual_mode_error!= MANUAL_MODE_OK){
    
                  if (manual_mode_error==MANUAL_MODE_ERROR_COMMAND_UNKNOWN){
                      Serial.println("ERROR>> loop: manual mode command is not recognized");
                      //TODO: play audio track once you get this error
                  } else if(manual_mode_error==MANUAL_MODE_ERROR_OBSTACLE){
                      Serial.println("ERROR>> loop: an obstacle is detected in front or back of robot");
                      //TODO: play audio track once you get this error
                  } else if(manual_mode_error==MANUAL_MODE_ERROR_MOTOR_FAILED){
                      Serial.println("ERROR>> loop: manual mode motor failure");
                      //TODO: play audio track once you get this error
                  }
                  
              }
              
          } else{
              Serial.println("ERROR>> loop: one of manual mode drivers is not initialized");
          }
      
      break;

      case LINE_FOLLOWING_MODE:
          if (line_following_mode_drivers_initialized){
              line_following_error_e line_following_error = LINE_FOLLOWING_OK;
    
              line_following_error = line_following_mode_run();
              if (line_following_error!= LINE_FOLLOWING_OK){
    
                  if(line_following_error==LINE_FOLLOWING_ERROR_OBSTACLE){
                      Serial.println("ERROR>> loop: an obstacle is detected in front of robot");
                      //TODO: play audio track once you get this error
                  } else if(line_following_error==LINE_FOLLOWING_ERROR_LINE_DECTETION){
                      Serial.println("ERROR>> loop: black line detection failure");
                      //TODO: play audio track once you get this error
                  }
                  
              }
          } else{
              Serial.println("ERROR>> master: one required driver for line following mode is not initialized yet");
          }
      break;

      case DEBUG_MODE:
          ;
      break;

      default:
          //current_robot_mode= startup_mode;
          current_robot_mode= MANUAL_MODE;
      break;
    }
}
