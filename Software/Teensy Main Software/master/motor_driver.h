#include "arduino.h"


/****************************************************************************************
 * DEFINES AND TYPE DEFINITIONS
 ****************************************************************************************/
typedef enum{
    SELECTED_MOTOR_BOTH  = 0,
    SELECTED_MOTOR_RIGHT = 1,
    SELECTED_MOTOR_LEFT  = 2
}motor_driver_selected_motor_e;

/****************************************************************************************
 * GLOBAL VARIABLES
 ****************************************************************************************/


/****************************************************************************************
 * PUBLIC FUNCTIONS PROTOTYPES
 ****************************************************************************************/
bool motor_driver_move_stepper(motor_driver_selected_motor_e selected_motor, int steps_count, int speed);


