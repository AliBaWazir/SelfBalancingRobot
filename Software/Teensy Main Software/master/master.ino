/*
 * This is the master main of the teensy based code. 
 */
#include "line_following_mode.h"


/****************************************************************************************
 * TYPE DEFINITIONS
 ****************************************************************************************/
 typedef enum {
    startup_mode = 0,
    manual_mode,
    manual_with_obstacle_avoidance,
    line_following_mode,
    debug_mode
 }state_e;


/****************************************************************************************
 * SATIC VARIABLES
 ****************************************************************************************/
static state_e robot_state;
static bool linear_sensor_array_driver_initialized = false;



/****************************************************************************************
 * GLOBAL VARIABLES
 ****************************************************************************************/
void setup() {

  // initialize serial communications at 9600 bps
  Serial.begin(9600);

  // initialize all drivers
  if (linear_sensor_array_driver_init()){
    linear_sensor_array_driver_initialized = true;
  }
  // PLEASE INITIALIZE ALL OTHER DRIVERS HERE:

  
  // set the robot mode
  robot_state= line_following_mode;

  Serial.println("INFO>> master: Setup is complete!");
}

void loop() {
  //Serial.println("master: loop is called!");

  switch (robot_state){
      case startup_mode:
      ;
      break;
      
      case manual_mode:
      ;
      break;

      case manual_with_obstacle_avoidance:
      ;
      break;

      case line_following_mode:
      if (linear_sensor_array_driver_initialized){
          if (follow_line()== BLACK_LINES_DETECTION_FAILURE){
              Serial.println("ERROR>> master: no black lines were detected successfully. Please reposition the roboot and start over");
              //TODO: add a quit handler function
          }
      } else{
          Serial.println("ERROR>> master: linear_sensor_array_driver is not initialized");
      }
      break;


      case debug_mode:
      ;
      break;

      default:
      robot_state = startup_mode;
      break;
    }
}
