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


//////////////////////// audio file names ////////////////////////////////
static char * DRAMA_cstr         = "DRAMA.WAV";
static char * CELLPHONE_cstr     = "CELLPHONE.WAV";
static char * APPL1_cstr         = "APPL1.WAV";
static char * DROID4_cstr        = "DROID4.WAV";
static char * DROID3_cstr        = "DROID3.WAV";
static char * DROID2_cstr        = "DROID2.WAV";
static char * DROID1_cstr        = "DROID1.WAV";
static char * LAUGH1_cstr        = "LAUGH1.WAV";
static char * LAUGH2_cstr        = "LAUGH2.WAV";
static char * CHICKEN_cstr       = "CHICKEN.WAV";
static char * CHIRP_cstr         = "CHIRP.WAV";
static char * LION_cstr          = "LION.WAV";
static char * AM_cstr            = "AM.WAV";
static char * FM_cstr            = "FM.WAV";
static char * DOG_cstr           = "DOG.WAV";
static char * HORN_cstr          = "HORN.WAV";
static char * RICKROLL_cstr      = "RICKROLL.WAV";

/****************************************************************************************
 * STATIC FUNCTION PROTOTYPES
 ***************************************************************************************/




 
/****************************************************************************************
 * STATIC FUNCTIONS
 ***************************************************************************************/
static char* speaker_driver_map_audio_identifier(speaker_driver_audio_identifier_e audio_identifier){
    char* retcode = NULL;
    
    if(audio_identifier == AUDIO_IDENTIFIER_OBSTACLE){
        retcode = HORN_cstr;
    }

    return retcode;
  
}


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


bool speaker_driver_play_file(speaker_driver_audio_identifier_e audio_identifier){
    bool ret = true;
    char* audio_to_play = NULL;

    audio_to_play= speaker_driver_map_audio_identifier(audio_identifier);
    if(audio_to_play == NULL){
        Serial.println("ERROR>> speaker_driver_play_file: speaker_driver_map_audio_identifier returned NULL");
        return false;
    } else{
        playWav1.play(audio_to_play);
    }
    
    return ret;
}

bool speaker_driver_test(){
    bool ret = true;

    playWav1.play(RICKROLL_cstr);
    
    return ret;
}

