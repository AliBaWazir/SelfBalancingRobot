#include <Audio.h>
#include <Wire.h>
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

 
/****************************************************************************************
 * STATIC VARIABLES
 ****************************************************************************************/
static bool speaker_driver_initialized             = false;
static bool driver_in_testing_mode                 = true;

AudioPlaySdWav           playWav1;

AudioOutputAnalog        audioOutput;
AudioConnection          patchCord1(playWav1, 0, audioOutput, 0);
AudioConnection          patchCord2(playWav1, 1, audioOutput, 1);

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
        
        SPI.setMOSI(SDCARD_MOSI_PIN);
        SPI.setSCK(SDCARD_SCK_PIN);
        if (!(SD.begin(SDCARD_CS_PIN))) {
            Serial.println("ERROR>> speaker_driver_init: unable to access the SD card");
            ret= false;
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

