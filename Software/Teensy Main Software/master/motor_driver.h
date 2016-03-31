#include "arduino.h"


/****************************************************************************************
 * DEFINES AND TYPE DEFINITIONS
 ****************************************************************************************/
#define STEPPER_CONSTANT          10           //this constant is determined from the testing results
#define DEFAULT_STEPPER_VELOCITY  10
#define DEFAULT_STEPPER_DISTANCE  100

typedef enum{
    SELECTED_MOTOR_BOTH  = 0,
    SELECTED_MOTOR_RIGHT = 1,
    SELECTED_MOTOR_LEFT  = 2
}motor_driver_selected_motor_e;

typedef struct{
    int16_t packet_id;
    int16_t left_motor_steps;
    int16_t right_motor_steps;
    int16_t user_data;
} motor_driver_control_packet_t;

/****************************************************************************************
 * GLOBAL VARIABLES
 ****************************************************************************************/


/****************************************************************************************
 * PUBLIC FUNCTIONS PROTOTYPES
 ****************************************************************************************/
 bool motor_driver_init();
 bool motor_driver_move_stepper(motor_driver_selected_motor_e selected_motor, int steps_count, int stepper_speed);


