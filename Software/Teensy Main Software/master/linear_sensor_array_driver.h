
#include "arduino.h"


/****************************************************************************************
 * DEFINES AND TYPE DEFINITIONS
 ****************************************************************************************/
#define BLACK_POINT_THRESHOLD 500
#define WHITE_POINT_THRESHOLD 1000
#define FRAME_BUFFER_LENGTH 128
#define FRAME_BUFFER_MARGIN_LENGHT 10
#define MAX_CONTRAST_LENGTH 8
#define MAX_BLACK_LINES_PER_FRAME 3


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
  uint8_t black_lines_positions[MAX_BLACK_LINES_PER_FRAME];       // 3 is maximum black lines decoded
}black_lines_info_t;

/****************************************************************************************
 * GLOBAL VARIABLES
 ****************************************************************************************/


/****************************************************************************************
 * PUBLIC FUNCTIONS PROTOTYPES
 ****************************************************************************************/
bool linear_sensor_array_driver_init();
black_lines_info_t* linear_sensor_array_driver_get_data();
int* linear_sensor_array_driver_get_current_frame();


