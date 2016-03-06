#include "arduino.h"

/****************************************************************************************
 * DEFINES AND TYPE DEFINITIONS
 ****************************************************************************************/
typedef enum{
    ULTRASONIC_SENSOR_ACTIVE_FRONT,
    ULTRASONIC_SENSOR_ACTIVE_BACK
}ultrasonic_sensor_active_direction_e;

/****************************************************************************************
 * GLOBAL VARIABLES
 ****************************************************************************************/

/****************************************************************************************
 * PUBLIC FUNCTIONS PROTOTYPES
 ****************************************************************************************/
bool ultrasonic_sensor_driver_init();
bool ultrasonic_sensor_check_clear_path(ultrasonic_sensor_active_direction_e active_direction);

