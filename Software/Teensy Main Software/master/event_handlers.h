#ifndef EVENT_HANDLERS_h
#define EVENT_HANDLERS_h

#include "arduino.h"
#include "display_driver.h"
#include "speaker_driver.h"


/****************************************************************************************
 * DEFINES AND TYPE DEFINITIONS
 ****************************************************************************************/
 typedef enum{
    EVENT_OBSTACLE_DETECTED,
    EVENT_INITIAL_BLACK_LINES_DETECTION_PROCESSING,
    EVENT_INITIAL_BLACK_LINES_DETECTION_FAILURE,
    EVENT_INITIAL_BLACK_LINES_DETECTION_SUCCESS,
    EVENT_TURNING_RIGHT,
    EVENT_TURNING_LEFT,
    EVENT_MOVING_FORWARD,
    EVENT_MOVING_BACKWARD,

    //manual mode event
    EVENT_MANUAL_MODE_RUN
 }event_e;
 
 

/****************************************************************************************
 * PUBLIC FUNCTIONS PROTOTYPES
 ****************************************************************************************/
bool fire_event(event_e event);



#endif


