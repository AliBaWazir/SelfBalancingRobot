#include "linear_sensor_array_driver.h"

/****************************************************************************************
 * HARDWARE PORTS ASSIGNMENTS
 ****************************************************************************************/
const int clkPin          = 14;  // digial sampling pin of the clock
const int exposurePin     = 15;  // digial sampling pin for the sampling
const int togglePin       = 20;  // digial sampling pin for the toggling
const int analogInputPin  = A2;  // Analog input pin for sensor's AOUT signal

/****************************************************************************************
 * STATIC FUNCTION PROTOTYPES
 ***************************************************************************************/
static void debug_print_array (int *input_array, int length, int margin_offset);
static void debug_print_decoded_frame_buffer_full_data (pixel_data_t* full_decoded_frame_buffer, uint8_t frame_length);
static void debug_print_decoded_frame_buffer_edge_pixel_indexes (pixel_data_t* full_decoded_frame_buffer, uint8_t frame_length);
static void debug_print_balck_lines_info();
static void create_test_frame();
static void locate_black_line_positions(pixel_data_t* full_decoded_frame_buffer, uint8_t frame_length, black_lines_info_t* extracted_info);
static void decode_frame_buffer (int *frame_buffer, int frame_length);


/****************************************************************************************
 * GLOBAL VARIABLES
 ***************************************************************************************/
 black_lines_info_t current_black_lines_info;

/****************************************************************************************
 * STATIC VARIABLES
 ***************************************************************************************/
static int                  sensorValue;                                      // value read from the analogInputPin
static int                  frame_buffer[128];                                // data of a single frame as received from the sensor
static int                  black_lines_count= 0;       // the count of the black lines is determined by the initial frame only
static pixel_data_t         decoded_frame_buffer[FRAME_BUFFER_LENGTH];
static double               Setpoint, Input, Output;
static bool                 driver_in_testing_mode           = false;          // this variable should be set to true only in the testing process to enable creating an internal frame



/****************************************************************************************
 * STATIC DEBUG AND TEST FUNCTIONS
 ***************************************************************************************/

/*
 * prints the values of an array given its length and an offset of values that need to be ignored
 * 
 * @param input_array    the array to be printed
 * @param length         the length of array to be printed
 * @param margin_offset  an offset to from the start and end of the array where entries should be ignored. 
 *                       This value should be 0 if all entries of the array are to be displayed
 */
static void debug_print_array (int *input_array, int length, int margin_offset){
    Serial.print("read frame from sensor = ");
    for (int i=(margin_offset); i<(length-margin_offset); i++){
       Serial.print(input_array[i]);
       Serial.print(",");
    }
    Serial.println("");
}


static void debug_print_decoded_frame_buffer_full_data (pixel_data_t* full_decoded_frame_buffer, uint8_t frame_length){
    Serial.println("");
    for (int i=0; i< frame_length; i++){
      Serial.print("[");
      Serial.print(i);
      Serial.print("]");
      Serial.print(", black pixel = ");
      Serial.print(full_decoded_frame_buffer[i].pixel_color);
      Serial.print(", edge pixel = ");
      Serial.print(full_decoded_frame_buffer[i].edge_pixel);
      
    }
}

static void debug_print_decoded_frame_buffer_edge_pixel_indexes (pixel_data_t* full_decoded_frame_buffer, uint8_t frame_length){
    Serial.print("Edge pixels are: ");
    for (int i=0; i< frame_length; i++){
      if (full_decoded_frame_buffer[i].edge_pixel){
        Serial.print(i);
        Serial.print(", ");
      }
    }
    Serial.println("");
}

static void debug_print_balck_lines_info(){
    if (current_black_lines_info.black_lines_count>0){
    Serial.print("Number of black lines = ");
    Serial.println(current_black_lines_info.black_lines_count);
    Serial.print("Black lines positions = ");
    for (int i=0; i< current_black_lines_info.black_lines_count; i++){
      Serial.print(current_black_lines_info.black_lines_positions[i]);
      Serial.print(", ");
    }
    Serial.println("");
  }
}


static void create_test_frame(){
    int frame [128] = {1021,1021,1021,1020,1021,1021,1022,1019,1021,1021,1021,1021,1021,1020,1021,1022,1021,1021,1021,1021,1021,1021,1022,1021,700,600,500,400,20,150,100,100,100,100,20,100,100,100,50,70,200,300,400,500,600,700,1021,1021,1021,1021,1021,1021,1020,1021,1021,1019,1021,1021,1021,1021,1021,1021,1021,1021,1021,1022,1021,1022,1021,1020,1020,1021,1021,1021,1021,1021,1019,1021,1021,1021,1021,1021,1021,1021,1021,1021,1021,1021,1021,1021,1021,1021,1021,1021,1021,1022,1021,1021,1021,1021,1020,1019,1021,1021,1020,1021,1021,1019,1021,1021,1021,1021,1020,1021,1021,1022,1019,1021};

    debug_print_array(frame, 128, 0);
    decode_frame_buffer (frame, 128);

    //delay 10 m seconds
    delay(10);
}


/****************************************************************************************
 * STATIC FUNCTIONS
 ***************************************************************************************/

static void locate_black_line_positions(pixel_data_t* full_decoded_frame_buffer, uint8_t frame_length, black_lines_info_t* extracted_black_lines_info){
  //memset the existing black lines info
  memset (extracted_black_lines_info, 0, sizeof(black_lines_info_t));
  
  for (int i= 0; i<frame_length; i++){
    if (full_decoded_frame_buffer[i].edge_pixel){
      //find the next edge pixel
      for (int j= i+1; j<frame_length; j++){
        if (full_decoded_frame_buffer[j].edge_pixel){
          extracted_black_lines_info->black_lines_positions[extracted_black_lines_info->black_lines_count]= (i + j)/2;
          extracted_black_lines_info->black_lines_count++;

          //jump forward
          i=j;
          break;
        }
        
      }
      
    }
    
  }

}

/*
 * decodes an a frame buffer and decides on which proportion of the vector the black line is
 * 
 * @param input_array    the array to be printed
 * @param length         the length of array to be printed
 * @param margin_offset  an offset to from the start and end of the array where entries should be ignored. 
 *                       This value should be 0 if all entries of the array are to be displayed
 */
static void decode_frame_buffer (int *frame_buffer, int frame_length){
  bool most_right_black_edge_detected= false;
  bool most_left_black_edge_detected= false;
  memset (&decoded_frame_buffer, 0, sizeof(pixel_data_t)*FRAME_BUFFER_LENGTH);
  
  for (int i= 0; i<FRAME_BUFFER_LENGTH; i++){
    if (frame_buffer[i]<BLACK_POINT_THRESHOLD){
      decoded_frame_buffer[i].pixel_color= PIXEL_BLACK;
    } else if (frame_buffer[i]>WHITE_POINT_THRESHOLD){
      decoded_frame_buffer[i].pixel_color= PIXEL_WHITE;
    } else{
      decoded_frame_buffer[i].pixel_color= PIXEL_UNKNOWN;
    }

    //set all pixels as no edge points by default
    decoded_frame_buffer[i].edge_pixel= false;
  }
  
  // loop through the decoded frame of pixels and set the other edge pixels
  for (int i= FRAME_BUFFER_MARGIN_LENGHT+1; i<FRAME_BUFFER_LENGTH-FRAME_BUFFER_MARGIN_LENGHT; i++){
    // The following if block is intended to set the right most edge point if the line ends with black point 
    if (decoded_frame_buffer[i-1].pixel_color == PIXEL_BLACK && decoded_frame_buffer[i].pixel_color == PIXEL_BLACK){
          // set the right most pixel as edge pixel if it is black and there are already white pixel encountered at the middle (i.e contrast)
          if ((i==FRAME_BUFFER_LENGTH-FRAME_BUFFER_MARGIN_LENGHT-1) && (most_left_black_edge_detected) && (!most_right_black_edge_detected)){
            decoded_frame_buffer[i].edge_pixel= true;
            most_right_black_edge_detected = true;
          }
    }

    // The following if block is intended to set any black point that is followed with a white point within a margin to be edge point
    else if (decoded_frame_buffer[i-1].pixel_color == PIXEL_BLACK && decoded_frame_buffer[i].pixel_color != PIXEL_BLACK){
        //check if the following white pixel is within the next few pixels
        for (int j = i; j<i+MAX_CONTRAST_LENGTH && j<FRAME_BUFFER_LENGTH-FRAME_BUFFER_MARGIN_LENGHT; j++){
          if (decoded_frame_buffer[j].pixel_color == PIXEL_WHITE){
            //set the black pixel as edge pixel
            decoded_frame_buffer[i].edge_pixel= true;
            
            // go back and set the left most black pixel as edge pixel if it is not set yet
            for (int x= i-2; (!most_left_black_edge_detected) && (x>=FRAME_BUFFER_MARGIN_LENGHT); x--){
              if (decoded_frame_buffer[x].pixel_color == PIXEL_BLACK && decoded_frame_buffer[x--].pixel_color != PIXEL_BLACK){
                decoded_frame_buffer[x].edge_pixel= true;
                most_left_black_edge_detected= true;
              } else if (x== FRAME_BUFFER_MARGIN_LENGHT+1){
                // if we reached the beggining of the frame, set the first pixel as edge pixel only if its black
                if (decoded_frame_buffer[x].pixel_color == PIXEL_BLACK){
                  decoded_frame_buffer[x].edge_pixel= true;
                  break;
                }

              }
            }
            
            //jump forward to the edge point 
            i=j;
            break;
          }    
        }
    }

    else if(decoded_frame_buffer[i-1].pixel_color == PIXEL_WHITE && decoded_frame_buffer[i].pixel_color == PIXEL_WHITE){
      continue;
    }

    else if (decoded_frame_buffer[i-1].pixel_color == PIXEL_WHITE && decoded_frame_buffer[i].pixel_color != PIXEL_WHITE){
        //check if the following black pixel is within the next few pixels
        for (int j = i; j<i+MAX_CONTRAST_LENGTH && j<frame_length-FRAME_BUFFER_MARGIN_LENGHT; j++){
          if (decoded_frame_buffer[j].pixel_color == PIXEL_BLACK){
            //set the black pixel as edge pixel
            decoded_frame_buffer[j].edge_pixel= true;
            //jump forward to the edge point 
            i=j;
            break;
        }    
      }
    }
  }

  //print the edge values of the decoded data
  debug_print_decoded_frame_buffer_edge_pixel_indexes(decoded_frame_buffer, FRAME_BUFFER_LENGTH);
  
  //locate the black line position
  locate_black_line_positions(decoded_frame_buffer, FRAME_BUFFER_LENGTH, &current_black_lines_info);

  //print the black lines info
  debug_print_balck_lines_info();

  
}


/****************************************************************************************
 * GLOBAL FUNCTIONS
 ***************************************************************************************/
bool linear_sensor_array_driver_init() {

  // set the input pins:
  pinMode(analogInputPin, INPUT);
  
  // set the output pins:
  pinMode(exposurePin, OUTPUT);
  pinMode(clkPin, OUTPUT);
  pinMode(togglePin,OUTPUT);
  
  return true;
}

bool linear_sensor_array_driver_get_data() {
  //Serial.print("INFO>> linear_sensor_array_driver_get_data: called");
  if (driver_in_testing_mode){
    create_test_frame();
    return true;
  }
  
  digitalWrite(togglePin,LOW); 
  
  // set the clk LOW
  digitalWrite(clkPin, LOW);
  delayMicroseconds(50);
  
  // set the exposurePin HIGH
  digitalWrite(exposurePin, HIGH);
  delayMicroseconds(50);

  // set the clkPin HIGH
  digitalWrite(clkPin, HIGH);
  delayMicroseconds(1);
  
  // set the exposurePin HIGH to start magnetizing the pixels in the sensor.
  // the expusure should last ~1 micro seconds
  digitalWrite(exposurePin, HIGH);
  delayMicroseconds(1);

  // set the exposurePin LOW
  digitalWrite(exposurePin, LOW);

  // do the cloking 128times to sample the values of the 128 array of pixels
  for (int i=0; i<128; i++){
    // set the clk HIGH with a half period of 50 micro seconds
    digitalWrite(clkPin, HIGH);
    delayMicroseconds(50);
    
    // read the analogInputPin value:
    sensorValue = analogRead(analogInputPin);
    if (decoded_frame_buffer[i].edge_pixel){
      digitalWrite(togglePin,HIGH); 
    }

    // sotore the analogInputPin value into the array:
    frame_buffer[i]= sensorValue;

    // set the clk LOW
    digitalWrite(clkPin, LOW);
    delayMicroseconds(50);
  }

  // print the frame_buffer to the serial monitor:
  debug_print_array(frame_buffer, FRAME_BUFFER_LENGTH, FRAME_BUFFER_MARGIN_LENGHT); //will ignore the first 16 bits
  
  // decode the frame buffer. Results will be stored in the global variable current_black_lines_info
  decode_frame_buffer(frame_buffer, FRAME_BUFFER_LENGTH);

  //delay 10 m seconds
  delay(10);

  return true;
}



