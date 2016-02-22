#include "linear_sensor_array_driver.h"

/****************************************************************************************
 * DEFINES AND TYPE DEFINITIONS
 ****************************************************************************************/
#define DEFAULT_CENTRE_LINE 64;

typedef enum{
  BLACK_LINES_DETECTION_OK,
  BLACK_LINES_DETECTION_FAILURE
}err_follow_line_e;

typedef enum{
  MOVE_TO_RIGHT,
  MOVE_TO_LEFT
}movement_direction_e;

typedef void (*direct_robot_callback_f)(movement_direction_e movement_direction, int movement_magnitude);

/****************************************************************************************
 * PUBLIC FUNCTIONS PROTOTYPES
 ****************************************************************************************/
err_follow_line_e follow_line(void);




