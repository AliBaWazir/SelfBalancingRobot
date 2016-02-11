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


/****************************************************************************************
 * GLOBAL VARIABLES
 ****************************************************************************************/
void setup() {
  robot_state= manual_with_obstacle_avoidance;

}

void loop() {
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
      follow_line();
      break;


      case debug_mode:
      ;
      break;

      default:
      robot_state = startup_mode;
      break;
    }
}
