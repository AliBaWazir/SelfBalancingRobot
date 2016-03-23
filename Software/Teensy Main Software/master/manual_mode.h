#ifndef MANUAL_MODE_h
#define MANUAL_MODE_h


/****************************************************************************************
 * DEFINES AND TYPE DEFINITIONS
 ****************************************************************************************/
 
typedef enum{
  MANUAL_MODE_OK,
  MANUAL_MODE_ERROR_COMMAND_UNKNOWN,
  MANUAL_MODE_ERROR_OBSTACLE,
  MANUAL_MODE_ERROR_MOTOR_FAILED
}manual_mode_error_e;

typedef enum{
  MANUAL_FORWARD,
  MANUAL_RIGHT,
  MANUAL_BACKWARD,
  MANUAL_LEFT
}manual_command_e;

/****************************************************************************************
 * PUBLIC FUNCTIONS PROTOTYPES
 ****************************************************************************************/
bool manual_mode_drivers_init();
manual_mode_error_e manual_mode_run();




#endif


