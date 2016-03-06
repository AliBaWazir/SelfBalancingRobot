#ifndef LINE_FOLLOWING_MODE_h
#define LINE_FOLLOWING_MODE_h

#include "linear_sensor_array_driver.h"


/****************************************************************************************
 * DEFINES AND TYPE DEFINITIONS
 ****************************************************************************************/
#define DEFAULT_CENTRE_LINE 64;

typedef enum{
  LINE_FOLLOWING_OK,
  LINE_FOLLOWING_ERROR_OBSTACLE,
  LINE_FOLLOWING_ERROR_LINE_DECTETION
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


