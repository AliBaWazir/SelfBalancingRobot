#include "line_following_mode.h"
#include "ultrasonic_sensor_driver.h"
#include "display_driver.h"
#include "motor_driver.h"

//#include <PID_v1.h>

/****************************************************************************************
 * DEFINES AND TYPE DEFINITIONS
 ****************************************************************************************/
#define DEFAULT_CENTRE_LINE  64;
#define STEPPER_CONSTANT     10;            //this constant is determined from the testing results

/****************************************************************************************
 * STATIC FUNCTION PROTOTYPES
 ***************************************************************************************/
static void direct_robot_given_black_lines_info(black_lines_info_t *black_lines_info);
static void process_direct_robot_command(turning_direction_e turning_direction, int movement_magnitude);

/****************************************************************************************
 * STATIC VARIABLES
 ***************************************************************************************/
static bool                 initial_frame_decoded            = false;         // this boolean is set to true after the initial frame is decoded
static black_lines_info_t   initial_frame_black_lines_info;
static bool                 busy_processing_moving_command   = false;         // this boolean is set to true while the robot is moving to the right or left
static bool                 robot_is_centred                 = false;         // this boolean is set to true once the robot is centred at the default centre
static int                  initial_frame_discarded_count    =0;              // this boolean determines the count of discarded initial frames

/****************************************************************************************
 * STATIC FUNCTIONS
 ***************************************************************************************/
static void direct_robot_given_black_lines_info(black_lines_info_t *black_lines_info){
    int centre_line_offset = 0;
    int centre_line_position = 0;
    
    if (black_lines_info->black_lines_count <= 0){
        return;
    }

    if (initial_frame_decoded && initial_frame_black_lines_info.black_lines_count ==1){
        // follow one line and keep the black line at the center
        centre_line_position = black_lines_info->black_lines_positions[0];

        // calculate the differrence from the black line posistion to the center 64
        centre_line_offset = centre_line_position - DEFAULT_CENTRE_LINE;  // if offset is positive ==> line to the right ==> move robot to the right
        if (centre_line_offset == 0){
            // black line is centered
            robot_is_centred = true;
            // robot is not processing any command
            busy_processing_moving_command = false;
            //TODO: pass a stop command to the ARM processor to stop turning the motor
            
            return;
        } else if (centre_line_offset > 0){
            robot_is_centred = false;
            // black line is in the right side of the default centre ==> move robot to the right
            Serial.print("INFO>> direct_robot_given_black_lines_info: will follow ONE line and will center the robot at index ");
            Serial.println(centre_line_position);
            process_direct_robot_command(TURN_RIGHT, abs(centre_line_offset));
        } else if (centre_line_offset < 0){
            robot_is_centred = false;
            // black line is in the left side of the default centre ==> move robot to the left
            process_direct_robot_command(TURN_LEFT, abs(centre_line_offset));
        } else{
            Serial.print("ERROR>> direct_robot_given_black_lines_info: centre_line_offset is invaild ");
        }
        
      
    }else if (initial_frame_decoded && initial_frame_black_lines_info.black_lines_count ==2){
        // follow two lines and keep the white space at the center
        Serial.println("INFO>> direct_robot_given_black_lines_info: will follow TWO lines");

    } else if (initial_frame_decoded && initial_frame_black_lines_info.black_lines_count ==3){
        // follow one line and keep the black line at the center
        Serial.println("INFO>> direct_robot_given_black_lines_info: will follow THREE lines");
      
    }
  
}

static void process_direct_robot_command(turning_direction_e turning_direction, int movement_magnitude){

  //Serial.println("INFO>> process_direct_robot_command: called!!");

  if (movement_magnitude <= 0){
      Serial.println("ERROR>> process_direct_robot_command: invalid parameter movement_magnitude");
      return;
  }

  if (busy_processing_moving_command){
      // the robot is still processing previous movement command ==> bale;
      Serial.println("INFO>> process_direct_robot_command: previous command is still prcessing");
      return;
  }

  // set the busy_processing_moving_command to true
  busy_processing_moving_command = true;

  switch (turning_direction){
      case TURN_RIGHT:
          Serial.println("INFO>> process_direct_robot_command: truring the motor to the right");
          ///if (!motor_driver_move_stepper(SELECTED_MOTOR_LEFT, STEPPER_CONSTANT*movement_magnitude, 10)){
              //Serial.println("ERROR>> process_direct_robot_command: failed to call motor_driver_move_stepper");
          ///}
      break;

      case TURN_LEFT:
          Serial.println("INFO>> process_direct_robot_command: truring the motor to the left");
          ///if (!motor_driver_move_stepper(SELECTED_MOTOR_RIGHT, movement_magnitude*STEPPER_CONSTANT, 10)){
             /// Serial.println("ERROR>> process_direct_robot_command: failed to call motor_driver_move_stepper");
         /// }
          
      break;

      default:
          Serial.println("ERROR>> process_direct_robot_command: invalid parameter movement_direction");
          return;
      break;
    
  }

}


/****************************************************************************************
 * PUBLIC FUNCTIONS
 ***************************************************************************************/
bool line_following_mode_drivers_init(){

  if (!linear_sensor_array_driver_init()){
      Serial.println("ERROR>> line_following_mode_drivers_init: linear_sensor_array_driver_init failed");
      return false;
  }
  if (!ultrasonic_sensor_driver_init()){
      Serial.println("ERROR>> line_following_mode_drivers_init: ultrasonic_sensor_driver_init failed");
      return false;
  }
  if (!display_driver_init()){
      Serial.println("ERROR>> line_following_mode_drivers_init: display_driver_init failed");
      return false;
  }  
  //PLEASE INITIALIZE ALL OTHER DRIVERS HERE:

  return true;
}


line_following_error_e line_following_mode_run(){
  
    line_following_error_e    line_following_error       = LINE_FOLLOWING_OK;
    black_lines_info_t       *current_black_lines_info   = NULL;
    const int                *current_frame              = NULL;

    //check for any obstcales in front ultrasonic sensor
    if(!ultrasonic_sensor_check_clear_path(ULTRASONIC_SENSOR_ACTIVE_FRONT)){
        //stop both stepper motors
        if (!motor_driver_move_stepper(SELECTED_MOTOR_BOTH, 0, 0)){
            Serial.println("ERROR>> process_direct_robot_command: failed to call motor_driver_move_stepper");
        }
        line_following_error = LINE_FOLLOWING_ERROR_OBSTACLE;
    }
    
    current_black_lines_info = linear_sensor_array_driver_get_data();
    if (current_black_lines_info != NULL){
        
        // display the current frame data in the LCD diplays
        current_frame = linear_sensor_array_driver_get_current_frame();
        if(current_frame != NULL){
            display_driver_display_frame(current_frame);
        }
        
        // check if the initial THIRD frame has black lines detected successfully. (i.e. ignore the first and second frames as they are not properly read)
        if (!initial_frame_decoded){

            //discard the initial two frames
            if(initial_frame_discarded_count <2){
                initial_frame_discarded_count++;
                return LINE_FOLLOWING_PROCESSING;
            }

            if (current_black_lines_info->black_lines_count <= 0){
                Serial.println("ERROR>> line_following_mode_run: no black lines are detected in the initial frame");
                line_following_error = LINE_FOLLOWING_ERROR_LINE_DECTETION;
            } else if (current_black_lines_info->black_lines_count > 0 && current_black_lines_info->black_lines_count < MAX_BLACK_LINES_PER_FRAME){
                
                // clone the values of the current frame to the initial frame
                initial_frame_black_lines_info.black_lines_count = current_black_lines_info->black_lines_count;
                for (int i=0; i< MAX_BLACK_LINES_PER_FRAME; i++){
                    initial_frame_black_lines_info.black_lines_positions[i]= current_black_lines_info->black_lines_positions[i];
                }
                
                initial_frame_decoded = true;
                
            } else{
                Serial.println("ERROR>> line_following_mode_run: number of black lines detected exceeds the limit");
                line_following_error = LINE_FOLLOWING_ERROR_LINE_DECTETION;
            }
        }

        if (line_following_error == LINE_FOLLOWING_OK){
            // direct the robot based on the last decoded data found in the global variable current_black_lines_info
            direct_robot_given_black_lines_info(current_black_lines_info);
        }

    } else{
          Serial.println("ERROR>> line_following_mode_run: current_black_lines_info is NULL");
          line_following_error = LINE_FOLLOWING_ERROR_LINE_DECTETION;
    }

    return line_following_error;
}



