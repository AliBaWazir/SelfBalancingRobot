#ifndef DISPLAY_DRIVER_h
#define DISPLAY_DRIVER_h


#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_SSD1306T.h>


#if (SSD1306_LCDHEIGHT != 64)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif


/****************************************************************************************
 * DEFINES AND TYPE DEFINITIONS
 ****************************************************************************************/
 typedef enum{
    DISPLAY_IDENTIFIER_RIGHT,
    DISPLAY_IDENTIFIER_LEFT,
    DISPLAY_IDENTIFIER_BOTH
 }display_identifier_e;

 typedef enum{
    //animation has negative value
    WOMAN_EYES_ANIMATION= -10,
    MAN_EYES_ANIMATION,

    //still bitmaps has positive values
    X_SIGN= 1,
    LINEAR_SENSOR_ARRAY_FRAME
 }display_driver_object_identifier_e;
 

/****************************************************************************************
 * PUBLIC FUNCTIONS PROTOTYPES
 ****************************************************************************************/
bool display_driver_init();
bool display_driver_display_object(display_identifier_e display_identifier, display_driver_object_identifier_e object_identifier);
bool display_driver_construct_bitmap_from_frame_and_display(display_identifier_e display_identifier, const int* frame_data);


#endif


