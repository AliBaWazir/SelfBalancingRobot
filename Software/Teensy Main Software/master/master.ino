/*
 * This is the master main of the teensy based code. 
 */
#include "line_following_mode.h"
#include "manual_mode.h"


/****************************************************************************************
 * TYPE DEFINITIONS
 ****************************************************************************************/
 typedef enum {
    startup_mode = 0,
    manual_mode,
    line_following_mode,
    debug_mode
 }mode_e;


/****************************************************************************************
 * SATIC VARIABLES
 ****************************************************************************************/
static mode_e robot_mode;
static bool line_following_mode_drivers_initialized  = false;
static bool manual_mode_drivers_initialized          = false;



/****************************************************************************************
 * STATIC FUNCTIONS
 ****************************************************************************************/
static bool get_current_robot_mode(){
    bool ret = true;

    


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
      line_following_mode_drivers_initialized = true;
  } else{
      Serial.println("ERROR>> setup: line_following_mode_drivers_init failed");
  }

  if (manual_mode_drivers_init()){
      manual_mode_drivers_initialized = true;
  } else{
      Serial.println("ERROR>> setup: manual_mode_drivers_init failed");
  }


  Serial.println("INFO>> master: Setup is complete!");
}

void loop() {
  //Serial.println("INFO>> master: loop is called!");

  //check the current robot mode
  
  // set the robot mode
  robot_mode= manual_mode;
  
  switch (robot_mode){
      case startup_mode:
      ;
      break;
      
      case manual_mode:
      if (manual_mode_drivers_initialized){
          manual_mode_error_e manual_mode_error = MANUAL_MODE_OK;

          manual_mode_error = manual_mode_run();
          if (manual_mode_error!= MANUAL_MODE_OK){

              if (manual_mode_error==MANUAL_MODE_ERROR_COMMAND_UNKNOWN){
                  Serial.println("ERROR>> loop: manual mode command from app is not recognized");
                  //TODO: play audio track once you get this error
              }
              else if(manual_mode_error==MANUAL_MODE_ERROR_OBSTACLE){
                  Serial.println("ERROR>> loop: an obstacle is detected in front or back of robot");
                  //TODO: play audio track once you get this error
              } else if(manual_mode_error==MANUAL_MODE_ERROR_MOTOR_FAILED){
                  Serial.println("ERROR>> loop: manual mode motor failure");
                  //TODO: play audio track once you get this error
              }
              
          }
      } else{
          Serial.println("ERROR>> master: one required driver for line manual mode is not initialized yet");

      }
      
      break;

      case line_following_mode:
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


      case debug_mode:
      
      break;

      default:
      robot_mode = startup_mode;
      break;
    }
}
