#ifndef SPEAKER_DRIVER_h
#define SPEAKER_DRIVER_h

#include "arduino.h"

/****************************************************************************************
 * DEFINES AND TYPE DEFINITIONS
 ****************************************************************************************/
typedef enum{
    AUDIO_IDENTIFIER_OBSTACLE,
    AUDIO_IDENTIFIER_FOLLOWING_LINE
  
}speaker_driver_audio_identifier_e;


/****************************************************************************************
 * GLOBAL VARIABLES
 ****************************************************************************************/
 

/****************************************************************************************
 * PUBLIC FUNCTIONS PROTOTYPES
 ****************************************************************************************/
bool speaker_driver_init();
bool speaker_driver_play_file(speaker_driver_audio_identifier_e audio_identifier);
bool speaker_driver_test();


#endif
