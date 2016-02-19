#include "line_following_mode.h"
#include <PID_v1.h>


/****************************************************************************************
 * STATIC VARIABLES
 ***************************************************************************************/
static bool                 initial_frame_decoded            = false;         // this boolean is set to true after the initial frame is decoded
static black_lines_info_t   initial_frame_black_lines_info;

/****************************************************************************************
 * STATIC FUNCTIONS
 ***************************************************************************************/
static void direct_robot_given_black_lines_info(black_lines_info_t *black_lines_info){
    if (black_lines_info->black_lines_count <= 0){
        return;
    }

    
    if (initial_frame_decoded && initial_frame_black_lines_info.black_lines_count ==1){
        // follow one line and keep the black line at the center
        Serial.print("INFO>> direct_robot_given_black_lines_info: will follow ONE line and will center the robot at index ");
        Serial.println(black_lines_info->black_lines_positions[0]);
      
    }else if (initial_frame_decoded && initial_frame_black_lines_info.black_lines_count ==2){
        // follow two lines and keep the white space at the center
        Serial.print("INFO>> direct_robot_given_black_lines_info: will follow TWO lines");

    } else if (initial_frame_decoded && initial_frame_black_lines_info.black_lines_count ==3){
        // follow one line and keep the black line at the center
        Serial.print("INFO>> direct_robot_given_black_lines_info: will follow THREE lines");
      
    }
  
}


/****************************************************************************************
 * GLOBAL FUNCTIONS
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
            direct_robot_given_black_lines_info(&current_black_lines_info);
        }

    }

    return err_follow_line;
}



