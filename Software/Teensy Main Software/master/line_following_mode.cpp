#include "line_following_mode.h"
#include "linear_array_sensor_driver.h"


static bool linear_array_sensor_driver_initialized = false;

void follow_line(void){
  if (linear_array_sensor_init()){
    linear_array_sensor_driver_initialized = true;
  }

  while (linear_array_sensor_driver_initialized){
    linear_array_sensor_get_data();
  }
}

