#include "line_following_mode.h"
//#include <PID_v1.h>


/****************************************************************************************
 * STATIC VARIABLES
 ***************************************************************************************/
static bool                 initial_frame_decoded            = false;         // this boolean is set to true after the initial frame is decoded
static black_lines_info_t   initial_frame_black_lines_info;
static bool                 busy_processing_moving_command   = false;         // this boolean is set to true while the robot is moving to the right or left
static bool                 robot_is_centred                 = false;         // this boolean is set to true once the robot is centred at the default centre

/****************************************************************************************
 * STATIC FUNCTIONS
 ***************************************************************************************/
static void direct_robot_given_black_lines_info(black_lines_info_t *black_lines_info, direct_robot_callback_f callback){
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
            callback(MOVE_TO_RIGHT, abs(centre_line_offset));
        } else if (centre_line_offset < 0){
            robot_is_centred = false;
            // black line is in the left side of the default centre ==> move robot to the left
            callback(MOVE_TO_LEFT, abs(centre_line_offset));
        } else{
            Serial.print("ERROR>> direct_robot_given_black_lines_info: centre_line_offset is invaild ");
        }
        
      
    }else if (initial_frame_decoded && initial_frame_black_lines_info.black_lines_count ==2){
        // follow two lines and keep the white space at the center
        Serial.print("INFO>> direct_robot_given_black_lines_info: will follow TWO lines");

    } else if (initial_frame_decoded && initial_frame_black_lines_info.black_lines_count ==3){
        // follow one line and keep the black line at the center
        Serial.print("INFO>> direct_robot_given_black_lines_info: will follow THREE lines");
      
    }
  
}

void process_direct_robot_command(movement_direction_e movement_direction, int movement_magnitude){

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

  switch (movement_direction){
      case MOVE_TO_RIGHT:
          //motor_step(left_motor, movement_magnitude*constant);
          Serial.println("INFO>> process_direct_robot_command: truring the motor to the right");
      break;

      case MOVE_TO_LEFT:
          //motor_step(right_motor, movement_magnitude*constant);
          Serial.println("INFO>> process_direct_robot_command: truring the motor to the left");
          
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
err_follow_line_e follow_line(void){
    err_follow_line_e err_follow_line = BLACK_LINES_DETECTION_OK;
    
    if (linear_sensor_array_driver_get_data()){
        // check if the initial frame has black lines detected successfully
        if (!initial_frame_decoded){
            if (current_black_lines_info.black_lines_count <= 0){
                Serial.println("ERROR>> line_following_mode: no black lines are detected in the initial frame");
                err_follow_line = BLACK_LINES_DETECTION_FAILURE;
            } else if (current_black_lines_info.black_lines_count > 0 && current_black_lines_info.black_lines_count < MAX_BLACK_LINES_PER_FRAME){
                
                // clone the values of the current frame to the initial frame
                initial_frame_black_lines_info.black_lines_count = current_black_lines_info.black_lines_count;
                for (int i=0; i< MAX_BLACK_LINES_PER_FRAME; i++){
                    initial_frame_black_lines_info.black_lines_positions[i]= current_black_lines_info.black_lines_positions[i];
                }
                
                initial_frame_decoded = true;
                
            } else{
                Serial.println("ERROR>> line_following_mode: number of black lines detected exceeds the limit");
                err_follow_line = BLACK_LINES_DETECTION_FAILURE;
            }
        }

        if (err_follow_line == BLACK_LINES_DETECTION_OK){
            // direct the robot based on the last decoded data found in the global variable current_black_lines_info
            direct_robot_given_black_lines_info(&current_black_lines_info, process_direct_robot_command);
        }

    }

    return err_follow_line;
}



