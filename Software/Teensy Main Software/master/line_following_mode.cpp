#include "line_following_mode.h"
#include "ultrasonic_sensor_driver.h"
#include "linear_sensor_array_driver.h"
#include "event_handlers.h"
#include "motor_driver.h"
#include "led_driver.h"

//#include <PID_v1.h>

/****************************************************************************************
 * STATIC DEFINES AND TYPE DEFINITIONS
 ****************************************************************************************/
#define DEFAULT_CENTRE_LINE  64
#define MOVING_FORWARD_DEFAULT_STEPS 10

/****************************************************************************************
 * STATIC FUNCTION PROTOTYPES
 ***************************************************************************************/
static bool continue_moving_forward();
static bool direct_robot_given_black_lines_info(black_lines_info_t *black_lines_info);
static bool process_direct_robot_command(turning_direction_e turning_direction, int movement_magnitude);

/****************************************************************************************
 * STATIC VARIABLES
 ***************************************************************************************/
static volatile bool        initial_frame_decoded            = false;         // this boolean is set to true after the initial frame is decoded
static black_lines_info_t   initial_frame_black_lines_info;
static bool                 busy_processing_moving_command   = false;         // this boolean is set to true while the robot is moving to the right or left
static bool                 robot_is_centred                 = false;         // this boolean is set to true once the robot is centred at the default centre
static int                  initial_frame_discarded_count    = 1;             // this boolean determines the count of discarded initial frames



/****************************************************************************************
 * STATIC FUNCTIONS
 ***************************************************************************************/
static bool direct_robot_given_black_lines_info(black_lines_info_t *black_lines_info){
    int centre_line_offset = 0;
    int centre_line_position = 0;
    bool ret= true;

    Serial.println("INFO>> direct_robot_given_black_lines_info: called ");
    
    if ((black_lines_info->black_lines_count) <= 0){
        Serial.print("ERROR>> direct_robot_given_black_lines_info: no black line is to be followed. black_lines_info->black_lines_count= ");
        Serial.println(black_lines_info->black_lines_count);
        //TODO: send command to ARM to rotate the robot 360 degrees looking for a black line
        return true;
    }

    //The robot has to detect the correct number of lines in the begging and the number of lines has to remain the same
    //if (initial_frame_decoded && initial_frame_black_lines_info.black_lines_count ==1 && black_lines_info->black_lines_count==1){
    if (initial_frame_decoded && black_lines_info->black_lines_count==1){
        Serial.println("INFO>> direct_robot_given_black_lines_info: robot is following one black line >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>");
        // follow one line and keep the black line at the center
        centre_line_position = black_lines_info->black_lines_positions[0];
        // calculate the differrence from the black line posistion to the center 64
        centre_line_offset = centre_line_position - DEFAULT_CENTRE_LINE;  // if offset is positive ==> line to the right ==> move robot to the right
        if (abs(centre_line_offset) == 0 || abs(centre_line_offset)<=2){ //allow 2 point to componsate for rounding off
            //TODO: change the follwoing into event based functions
            // black line is centered
            robot_is_centred = true;
            // robot is not processing any command
            busy_processing_moving_command = false;
            //TODO: pass a stop command to the ARM processor to stop turning the motor
            
            //continue moving forward in constant speed
            if(!continue_moving_forward()){
                Serial.print("INFO>> direct_robot_given_black_lines_info: continue_moving_forward failed ");
                ret= false;
            }
            
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
        
      
    //}else if (initial_frame_decoded && initial_frame_black_lines_info.black_lines_count ==2 && black_lines_info->black_lines_count==2){
    }else if (initial_frame_decoded && black_lines_info->black_lines_count==2){
        // follow two lines and keep the white space at the center
        Serial.println("INFO>> direct_robot_given_black_lines_info: will follow TWO lines");
        
        // follow two lines and keep the both black lines at the center
        centre_line_position = (black_lines_info->black_lines_positions[0]+black_lines_info->black_lines_positions[1])/2;

        // calculate the differrence from the mid point between the two black lines and the center (i.e. pixel 64)
        centre_line_offset = centre_line_position - DEFAULT_CENTRE_LINE;  // if offset is positive ==> line to the right ==> move robot to the right

        if ((centre_line_offset == 0) || (abs(centre_line_offset)<=2)){
            // mid point between the two black lines is centered
            robot_is_centred = true;
            // robot is not processing any command
            busy_processing_moving_command = false;
            //TODO: pass a stop command to the ARM processor to stop turning the motor

            //continue moving forward in constant speed
            if(!continue_moving_forward()){
                Serial.print("INFO>> direct_robot_given_black_lines_info: continue_moving_forward failed ");
                ret= false;
            } else{
                // fire moving forward event
                ret= fire_event(EVENT_MOVING_FORWARD);
                if (!ret){
                    Serial.print("ERROR>> direct_robot_given_black_lines_info: failed to fire event EVENT_MOVING_FORWARD");
                }
            }
            
        } else if (centre_line_offset > 0){
            robot_is_centred = false;
            // mid point between the two black lines is in the right side of the default centre ==> move robot to the right
            Serial.print("INFO>> direct_robot_given_black_lines_info: will follow TWO lines and will center the robot at index ");
            Serial.println(centre_line_position);
            process_direct_robot_command(TURN_RIGHT, abs(centre_line_offset));
        } else if (centre_line_offset < 0){
            robot_is_centred = false;
            // mid point between the two black lines is in the left side of the default centre ==> move robot to the left
            process_direct_robot_command(TURN_LEFT, abs(centre_line_offset));
        } else{
            Serial.print("ERROR>> direct_robot_given_black_lines_info: centre_line_offset is invaild ");
        }
        

    } else if (initial_frame_decoded && black_lines_info->black_lines_count==3){
        // follow one line and keep the black line at the center
        Serial.println("INFO>> direct_robot_given_black_lines_info: will follow THREE lines");
        //TOD: develop this case
      
    } else {
        //uint8_t tmp =0;
        Serial.print("ERROR>> direct_robot_given_black_lines_info: Current black line count is above 3");
        //tmp= initial_frame_black_lines_info.black_lines_count;
        //Serial.print(tmp);
        Serial.print(" Current= ");
        Serial.println(black_lines_info->black_lines_count);
    }

    return ret;
  
}

static bool continue_moving_forward(){
    bool ret                  = true;
    int movement_distance     = 0;
    int movement_velocity     = 0;

    Serial.println("INFO>> continue_moving_forward: called");
    
    movement_distance = MOVING_FORWARD_DEFAULT_STEPS;
    movement_velocity = DEFAULT_STEPPER_VELOCITY;
    
    if (!motor_driver_move_stepper(SELECTED_MOTOR_BOTH, movement_distance, movement_velocity)){
        Serial.println("ERROR>> continue_moving_forward: failed to call motor_driver_move_stepper");
        ret=false;
    }
    
    return ret;
}


static bool process_direct_robot_command(turning_direction_e turning_direction, int movement_magnitude){

  bool ret               = true;
  int movement_distance  = 0;
  int movement_velocity  = 0;
  
  //Serial.println("INFO>> process_direct_robot_command: called!!");

  if (movement_magnitude <= 0){
      Serial.println("ERROR>> process_direct_robot_command: invalid parameter movement_magnitude");
      return false;
  }

  if (busy_processing_moving_command){
      // the robot is still processing previous movement command ==> bale;
      Serial.println("INFO>> process_direct_robot_command: previous command is still prcessing");
      //return true;
  }

  
  //determine the desired movement distance and velocity
  movement_distance = movement_magnitude*STEPPER_CONSTANT;
  movement_velocity = DEFAULT_STEPPER_VELOCITY;
  

  switch (turning_direction){
      case TURN_RIGHT:
          Serial.println("INFO>> process_direct_robot_command: truring the motor to the right");
          if (!motor_driver_move_stepper(SELECTED_MOTOR_LEFT, movement_distance, movement_velocity)){
              Serial.println("ERROR>> process_direct_robot_command: failed to call motor_driver_move_stepper");
              ret = false;
          }
      break;

      case TURN_LEFT:
          Serial.println("INFO>> process_direct_robot_command: truring the motor to the left");
          if (!motor_driver_move_stepper(SELECTED_MOTOR_RIGHT, movement_distance, movement_velocity)){
              Serial.println("ERROR>> process_direct_robot_command: failed to call motor_driver_move_stepper");
              ret= false;
          }
          
      break;

      default:
          Serial.println("ERROR>> process_direct_robot_command: invalid parameter movement_direction");
          return false;
      break;
    
  }

  return ret;

}


/****************************************************************************************
 * PUBLIC FUNCTIONS
 ***************************************************************************************/
bool line_following_mode_drivers_init(){

  memset(&initial_frame_black_lines_info, 0, sizeof(black_lines_info_t));

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
  if (!speaker_driver_init()){
      Serial.println("ERROR>> line_following_mode_drivers_init: speaker_driver_init failed");
      return false;
  }
  if (!motor_driver_init()){
      Serial.println("ERROR>> line_following_mode_drivers_init: motor_driver_init failed");
      return false; 
  }

    if (!led_driver_init()){
      Serial.println("ERROR>> line_following_mode_drivers_init: led_driver_init failed");
      return false; 
  }
  //PLEASE INITIALIZE ALL OTHER DRIVERS HERE:

  return true;
}


line_following_error_e line_following_mode_run(){
  
    line_following_error_e    line_following_error       = LINE_FOLLOWING_OK;
    black_lines_info_t       *current_black_lines_info   = NULL;
    const int                *current_frame              = NULL;
    
    //TODO: call this function only when there is sound playing==> move this call to speaker driver
    //led_driver_continue_talking();

    //TODO: put this on back
    //if (!fire_event(EVENT_LINE_FOLLWOING_MODE_RUN)){
        //Serial.println("ERROR>> line_following_mode_run: failed to call fire_event EVENT_LINE_FOLLWOING_MODE_RUN");
    //}
    
    //check for any obstcales in front ultrasonic sensor
    if(!ultrasonic_sensor_check_clear_path(ULTRASONIC_SENSOR_ACTIVE_FRONT)){
    //if(!ultrasonic_sensor_check_clear_path(ULTRASONIC_SENSOR_ACTIVE_BACK)){
        
        // fire event
        if (!fire_event(EVENT_OBSTACLE_DETECTED)){
            Serial.println("ERROR>> line_following_mode_run: failed to call fire_event EVENT_OBSTACLE_DETECTED");
        }
        
        //stop both stepper motors
        if (!motor_driver_move_stepper(SELECTED_MOTOR_BOTH, 0, 0)){
            Serial.println("ERROR>> line_following_mode_run: failed to call motor_driver_move_stepper");
        }
        line_following_error = LINE_FOLLOWING_ERROR_OBSTACLE;
        
    }
    
    current_black_lines_info = linear_sensor_array_driver_get_data();
    if (current_black_lines_info != NULL){
        
        // display the current frame data in the LCD diplays
        current_frame = linear_sensor_array_driver_get_current_frame();
        if(current_frame != NULL){
            display_driver_construct_bitmap_from_frame_and_display(DISPLAY_IDENTIFIER_RIGHT, current_frame);
        }
        
        // check if the initial THIRD frame has black lines detected successfully. (i.e. ignore the first and second frames as they are not properly read)
        if (!initial_frame_decoded){

            //discard the initial 5 frames
            if(initial_frame_discarded_count <=5){
                
                initial_frame_discarded_count++;
                
                // fire event at the beggninning of detection
                //if (initial_frame_discarded_count==1 && !fire_event(EVENT_INITIAL_BLACK_LINES_DETECTION_PROCESSING)){
                    //Serial.println("ERROR>> line_following_mode_run: failed to call fire_event EVENT_PROCESSING_BLACK_LINES_DETECTION");
                //}
                return LINE_FOLLOWING_PROCESSING;
                
            }

            if (current_black_lines_info->black_lines_count <= 0){
                Serial.println("ERROR>> line_following_mode_run: no black lines are detected in the initial frame");
                // fire event
                //if (!fire_event(EVENT_INITIAL_BLACK_LINES_DETECTION_FAILURE)){
                    //Serial.println("ERROR>> line_following_mode_run: failed to call fire_event EVENT_INITIAL_BLACK_LINES_DETECTION_FAILURE");
                //}
                line_following_error = LINE_FOLLOWING_ERROR_LINE_DECTETION;
            } else if (current_black_lines_info->black_lines_count > 0){
                
                // clone the values of the current frame to the initial frame. Up to three black lines will be considered
                initial_frame_black_lines_info.black_lines_count = current_black_lines_info->black_lines_count;
                Serial.print("INFO>> line_following_mode_run: initial_frame_black_lines_info.black_lines_count= ");
                int tmp= initial_frame_black_lines_info.black_lines_count;
                Serial.println(tmp);

                for (int i=0; i< MAX_BLACK_LINES_PER_FRAME; i++){
                    initial_frame_black_lines_info.black_lines_positions[i]= current_black_lines_info->black_lines_positions[i];
                }
                
                initial_frame_decoded = true;

                // fire event
                //if (!fire_event(EVENT_INITIAL_BLACK_LINES_DETECTION_SUCCESS)){
                    //Serial.println("ERROR>> line_following_mode_run: failed to call fire_event EVENT_INITIAL_BLACK_LINES_DETECTION_SUCCESS");
                //}
                
            }
        }

        if (line_following_error == LINE_FOLLOWING_OK){
            // direct the robot based on the last decoded data found in the global variable current_black_lines_info
            if(!direct_robot_given_black_lines_info(current_black_lines_info)){
                  Serial.println("ERROR>> line_following_mode_run: direct_robot_given_black_lines_info failed");
                  line_following_error= LINE_FOLLOWING_ERROR_MOTOR_CONTROL;
            }
        }

    } else{
          Serial.println("ERROR>> line_following_mode_run: current_black_lines_info is NULL");
          line_following_error = LINE_FOLLOWING_ERROR_INVALID_ARGUMENT;
    }

    return line_following_error;
}



