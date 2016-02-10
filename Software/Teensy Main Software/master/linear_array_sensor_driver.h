
#include <PID_v1.h>
#include "arduino.h"
/****************************************************************************************
 * PORTS ASSIGNMENTS
 ****************************************************************************************/
const int clkPin          = 14;  // digial sampling pin of the clock
const int exposurePin     = 15;  // digial sampling pin for the sampling
const int togglePin       = 20;  // digial sampling pin for the toggling
const int analogInputPin  = A2;  // Analog input pin for sensor's AOUT signal



/****************************************************************************************
 * DEFINES AND TYPE DEFINITIONS
 ****************************************************************************************/
#define BLACK_POINT_THRESHOLD 300
#define WHITE_POINT_THRESHOLD 1000
#define FRAME_BUFFER_LENGTH 128
#define FRAME_BUFFER_MARGIN_LENGHT 10
#define MAX_CONTRAST_LENGTH 8

typedef enum {
  PIXEL_WHITE,
  PIXEL_BLACK,
  PIXEL_UNKNOWN
}pixel_color_e;

typedef struct {
  int pixel_index;
  pixel_color_e pixel_color; 
  bool edge_pixel;
}pixel_data_t;

typedef struct {
  uint8_t black_lines_count;
  uint8_t black_lines_positions[3];       // 3 is maximum black lines decoded
}black_lines_info_t;


/****************************************************************************************
 * PUBLIC FUNCTIONS PROTOTYPES
 ****************************************************************************************/
bool linear_array_sensor_init();
void linear_array_sensor_get_data();


