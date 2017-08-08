
#include "arduino.h"


/****************************************************************************************
 * DEFINES AND TYPE DEFINITIONS
 ****************************************************************************************/
#define BLACK_POINT_THRESHOLD 400 //300
#define WHITE_POINT_THRESHOLD 1000
#define FRAME_BUFFER_MARGIN_LENGHT 10
#define CONTRAST_MARGIN 7

#define MAX_BLACK_LINES_PER_FRAME 3
#define FRAME_BUFFER_LENGTH 128


typedef enum {
  PIXEL_UNKNOWN,
  PIXEL_WHITE,
  PIXEL_BLACK
}pixel_color_e;

typedef enum{
  EDGE_PIXEL_UNDEFINED_PAIR,
  EDGE_PIXEL_FIRST_PAIR=1,
  EDGE_PIXEL_SECOND_PAIR
}edge_pixel_pair_e;

typedef struct {
  int pixel_index;
  pixel_color_e pixel_color; 
  bool edge_pixel;
  edge_pixel_pair_e edge_pixel_pair;
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


