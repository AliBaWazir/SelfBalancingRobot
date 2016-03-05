/*
 * This is the master main of the teensy based code. 
 */
#include "line_following_mode.h"


/****************************************************************************************
 * TYPE DEFINITIONS
 ****************************************************************************************/
 typedef enum {
    startup_mode = 0,
    manual_mode,
    line_following_mode,
    debug_mode
 }state_e;


/****************************************************************************************
 * SATIC VARIABLES
 ****************************************************************************************/
static state_e robot_state;
static bool linear_sensor_array_driver_initialized = false;
static bool ultrasonic_sensor_driver_initialized   = false;
static bool lcd_display_driver_initialized         = false;




/****************************************************************************************
 * GLOBAL VARIABLES
 ****************************************************************************************/
void setup() {

  // initialize serial communications at 9600 bps
  Serial.begin(9600);

  // initialize all drivers
  if (linear_sensor_array_driver_init()){
    linear_sensor_array_driver_initialized = true;
  }
  if (ultrasonic_sensor_driver_init()){
    ultrasonic_sensor_driver_initialized = true;
  }
  if (lcd_display_driver_init()){
    lcd_display_driver_initialized = true;
  }  
  //PLEASE INITIALIZE ALL OTHER DRIVERS HERE:

  
  // set the robot mode
  robot_state= debug_mode;

  Serial.println("INFO>> master: Setup is complete!");
}

void loop() {
  //Serial.println("master: loop is called!");

  switch (robot_state){
      case startup_mode:
      ;
      break;
      
      case manual_mode:
      ;
      break;

      case line_following_mode:
      if (linear_sensor_array_driver_initialized && ultrasonic_sensor_driver_initialized){
          if (follow_line()== BLACK_LINES_DETECTION_FAILURE){
              Serial.println("ERROR>> master: no black lines were detected successfully. Please reposition the roboot and start over");
              //TODO: add a quit handler function
          }
      } else{
          Serial.println("ERROR>> master: one of the required drivers is not initialized yet");
      }
      break;


      case debug_mode:
          lcd_display_driver_display_bitmap(NULL);
          delay(5000);
      break;

      default:
      robot_state = startup_mode;
      break;
    }
}
