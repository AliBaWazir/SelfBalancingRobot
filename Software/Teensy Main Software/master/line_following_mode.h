#ifndef LINE_FOLLOWING_MODE_h
#define LINE_FOLLOWING_MODE_h

/****************************************************************************************
 * DEFINES AND TYPE DEFINITIONS
 ****************************************************************************************/
 
typedef enum{
  LINE_FOLLOWING_OK = 1,
  LINE_FOLLOWING_PROCESSING = -20,
  LINE_FOLLOWING_ERROR_OBSTACLE =-19,
  LINE_FOLLOWING_ERROR_LINE_DECTETION =-18,
  LINE_FOLLOWING_ERROR_MOTOR_CONTROL=-17,
  LINE_FOLLOWING_ERROR_INVALID_ARGUMENT=-16
  
}line_following_error_e;

typedef enum{
  TURN_RIGHT,
  TURN_LEFT
}turning_direction_e;

/****************************************************************************************
 * PUBLIC FUNCTIONS PROTOTYPES
 ****************************************************************************************/
bool line_following_mode_drivers_init();
line_following_error_e line_following_mode_run();




#endif


