#ifndef DISPLAY_DRIVER_h
#define DISPLAY_DRIVER_h

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
//#include <Adafruit_SSD1306T.h>


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

 #define CLOSE_EYE "CLOSE_EYE"

/****************************************************************************************
 * PUBLIC FUNCTIONS PROTOTYPES
 ****************************************************************************************/
bool display_driver_init();
bool display_driver_display_bitmap(uint8_t *bitmap);
void display_driver_display_frame(const int* frame_data);
bool display_driver_display_object(display_identifier_e display_identifier, char* bitmap_identifier);


#endif


