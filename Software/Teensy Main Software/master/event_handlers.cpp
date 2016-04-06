/*********************************************************************
This is the code that will handle the any event occuring during the operation of the system.

Written by Ali Ba Wazir  for ELEC3907 W2016 "Self Balancing Robot".  
*********************************************************************/
#include "event_handlers.h"

 /****************************************************************************************
 * HARDWARE PORTS ASSIGNMENTS
 ****************************************************************************************/



/****************************************************************************************
 * GLOBAL VARIABLES
 ***************************************************************************************/


/****************************************************************************************
 * DEFINITIONS
 ****************************************************************************************/


/****************************************************************************************
 * STATIC VARIABLES
 ****************************************************************************************/

/****************************************************************************************
 * STATIC FUNCTION PROTOTYPES
 ***************************************************************************************/






 /****************************************************************************************
 * STATIC DEBUG AND TEST FUNCTIONS
 ****************************************************************************************/

 
/****************************************************************************************
 * STATIC FUNCTIONS
 ***************************************************************************************/
static bool obstacle_detected_event_handler(){
    bool ret = true;
    
    //display X sign to indicate obstacle
    if(!display_driver_display_object(DISPLAY_IDENTIFIER_BOTH, X_SIGN)){
        Serial.println("ERROR>> obstacle_detected_event_handler: failed to call display_driver_display_object");
        ret= false;
    }
    
    //play sound saying I am stopping!
    if(ret&&!speaker_driver_play_file(" ")){
        Serial.println("ERROR>> obstacle_detected_event_handler: failed to call speaker_driver_play_file");
        ret= false;
    }

    return ret;
}

static bool initial_black_lines_detection_processing_event_handler(){
    bool ret = true;

    //play sound saying I am detecting lines!
    if((ret)&&(!speaker_driver_play_file(MINION_cstr))){
        Serial.println("ERROR>> initial_black_lines_detection_processing_event_handler: failed to call speaker_driver_play_file");
        ret= false;
    }
    
    //display quotation mark to indicate processing
    //if((ret)&& (!display_driver_display_object(DISPLAY_IDENTIFIER_BOTH, PROSESSING))){
        //Serial.println("ERROR>> initial_black_lines_detection_processing_event_handler: failed to call display_driver_display_object");
        //ret= false;
    //}
    



    return ret;
}
static bool initial_black_lines_detection_failure_event_handler(){
    bool ret = true;
    
    //display sad faces to indicate failure
    //if(!display_driver_display_object(DISPLAY_IDENTIFIER_BOTH, FAILURE_DISPLAY)){
        //Serial.println("ERROR>> initial_black_lines_detection_failure_event_handler: failed to call display_driver_display_object");
        //ret= false;
    //}
    
    //play sound saying I am stopping!
    if((ret)&&(!speaker_driver_play_file(" "))){
        Serial.println("ERROR>> initial_black_lines_detection_failure_event_handler: failed to call speaker_driver_play_file");
        ret= false;
    }
    return ret;
}

static bool initial_black_lines_detection_success_event_handler(){
    bool ret = true;

    return ret;
}


static bool turning_right_event_handler(){
    bool ret = true;

    return ret;  
}
static bool turning_left_event_handler(){
    bool ret = true;

    return ret;  
}
static bool moving_forward_event_handler(){
    bool ret = true;

    return ret;  
}

static bool moving_backward_event_handler(){
    bool ret = true;

    return ret;  
}


static bool manual_mode_run_event_handler(){
    bool ret = true;

    //display animating eyes in both displays
    if(!display_driver_display_object(DISPLAY_IDENTIFIER_BOTH, WOMAN_EYES_ANIMATION)){
        Serial.println("ERROR>> initial_black_lines_detection_failure_event_handler: failed to call display_driver_display_object");
        ret= false;
    }
    

    return ret;  
}



 /****************************************************************************************
 * PUBLIC FUNCTIONS
 ***************************************************************************************/
bool fire_event(event_e event){
    bool    ret = true;
    //test
    //speaker_driver_test();
    //end of test

    switch (event){

        case EVENT_OBSTACLE_DETECTED:
            ret= obstacle_detected_event_handler();
        break;

        case EVENT_INITIAL_BLACK_LINES_DETECTION_PROCESSING:
            ret= initial_black_lines_detection_processing_event_handler();
        break;
        
        case EVENT_INITIAL_BLACK_LINES_DETECTION_FAILURE:
            ret= initial_black_lines_detection_failure_event_handler();
        break;

        case EVENT_INITIAL_BLACK_LINES_DETECTION_SUCCESS:
            ret= initial_black_lines_detection_success_event_handler();
        break;
        
        case EVENT_TURNING_RIGHT:
            ret= turning_right_event_handler();
        break;

        case EVENT_TURNING_LEFT:
            ret= turning_left_event_handler();
        break;

        case EVENT_MOVING_FORWARD:
            ret= moving_forward_event_handler();
        break;

        case EVENT_MOVING_BACKWARD:
            ret= moving_backward_event_handler();
        break;

        case EVENT_MANUAL_MODE_RUN:
            ret= manual_mode_run_event_handler();
        break;
        
        default:
            Serial.println("ERROR>> fire_event: event has UNKOWN value");
            ret= false;
        break;


    }


    return ret;
}

