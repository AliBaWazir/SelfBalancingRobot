#include <Audio.h>
#include <i2c_t3.h>
#include <SPI.h>
#include <SD.h>

#include "speaker_driver.h"

/****************************************************************************************
 * HARDWARE PORTS ASSIGNMENTS
 ****************************************************************************************/
// Use these with the audio adaptor board
#define SDCARD_CS_PIN    10
#define SDCARD_MOSI_PIN  11
#define SDCARD_SCK_PIN   13


/****************************************************************************************
 * GLOBAL VARIABLES
 ***************************************************************************************/
 char* OBSTACLE_STOP_cstr    = "OBSTACLE_STOP";
 char* DETECTING_WAIT_cstr   = "DETECTING_WAIT";
 char* FAILURE_SOUND_cstr    = "FAILURE_SOUND";
 char* GLITTER_cstr          = "GLITTER.WAV";
 char* MINION_cstr           = "MINION1.WAV";
/*
STABLE.WAV    2016-04-02 19:12:18 715558
BEEP1.WAV     2016-04-02 19:09:38 0
ROBO1.WAV     2016-04-02 19:13:56 0
MINION1.WAV   2016-04-02 19:28:24 64643500
1.WAV         2016-01-14 23:57:12 5440798
2.WAV         2016-01-14 23:59:56 3431650
REWARD.WAV    2016-01-15 00:16:10 202318
GLITTER.WAV   2016-01-15 13:03:54 11907264
*/


/****************************************************************************************
 * STATIC VARIABLES
 ****************************************************************************************/
static bool speaker_driver_initialized             = false;
static bool driver_in_testing_mode                 = false;

AudioPlaySdWav           playWav1;

AudioOutputAnalog        audioOutput;
AudioConnection          patchCord1(playWav1, 0, audioOutput, 0);
AudioConnection          patchCord2(playWav1, 1, audioOutput, 1);

AudioControlSGTL5000     sgtl5000_1;


/****************************************************************************************
 * STATIC FUNCTION PROTOTYPES
 ***************************************************************************************/




 
/****************************************************************************************
 * STATIC FUNCTIONS
 ***************************************************************************************/



/****************************************************************************************
 * PUBLIC FUNCTIONS
 ***************************************************************************************/
bool speaker_driver_init(){
    bool ret = true;

    if(!speaker_driver_initialized){

        // Audio connections require memory to work.  For more
        // detailed information, see the MemoryAndCpuUsage example
        AudioMemory(8);
        
        SPI.setMOSI(SDCARD_MOSI_PIN);
        SPI.setSCK(SDCARD_SCK_PIN);
        if (!(SD.begin(SDCARD_CS_PIN))) {
            Serial.println("ERROR>> speaker_driver_init: unable to access the SD card");
            if(!driver_in_testing_mode){
                ret= false;
            } 
        }
        
        speaker_driver_initialized = true;
    }

    return ret;
}


bool speaker_driver_play_file(char* file_name){
    bool ret = true;

    playWav1.play(file_name);
    
    return ret;
}

bool speaker_driver_test(){
    bool ret = true;

    playWav1.play(GLITTER_cstr);
    
    return ret;
}

