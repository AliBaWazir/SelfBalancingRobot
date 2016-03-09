#include "arduino.h"


/****************************************************************************************
 * DEFINES AND TYPE DEFINITIONS
 ****************************************************************************************/
#define STEPPER_CONSTANT          10           //this constant is determined from the testing results
#define DEFAULT_STEPPER_VELOCITY  10

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
bool motor_driver_move_stepper(motor_driver_selected_motor_e selected_motor, int steps_count, int stepper_speed);


