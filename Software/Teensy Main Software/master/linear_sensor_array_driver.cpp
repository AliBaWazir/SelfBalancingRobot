#include "linear_sensor_array_driver.h"

/****************************************************************************************
 * HARDWARE PORTS ASSIGNMENTS
 ****************************************************************************************/
const int clkPin          = 14;  // digial sampling pin of the clock
const int exposurePin     = 15;  // digial sampling pin for the sampling
const int analogInputPin  = A2;  // Analog input pin for sensor's AOUT signal

const int togglePin       = 20;  // digial sampling pin for the toggling used to generate pulses when edge points detected


/****************************************************************************************
 * STATIC FUNCTION PROTOTYPES
 ***************************************************************************************/
static void debug_print_array (int *input_array, int length, int margin_offset);
static void debug_print_decoded_frame_buffer_full_data (pixel_data_t* full_decoded_frame_buffer, uint8_t frame_length);
static void debug_print_decoded_frame_buffer_edge_pixel_indexes (pixel_data_t* full_decoded_frame_buffer, uint8_t frame_length);
static void debug_print_balck_lines_info();
static void create_test_frame(int *dest_frame);
static void locate_black_line_positions(pixel_data_t* full_decoded_frame_buffer, uint8_t frame_length, black_lines_info_t* extracted_info);
static void decode_frame_buffer (int *frame_buffer, int frame_length);

/****************************************************************************************
 * GLOBAL VARIABLES
 ***************************************************************************************/


/****************************************************************************************
 * STATIC VARIABLES
 ***************************************************************************************/
static int                  sensor_value;                                      // value read from the analogInputPin
static int                  frame_buffer[128];                                // data of a single frame as received from the sensor
static int                  black_lines_count= 0;       // the count of the black lines is determined by the initial frame only
static pixel_data_t         decoded_frame_buffer[FRAME_BUFFER_LENGTH];
static black_lines_info_t   current_black_lines_info;

static bool                 linear_sensor_array_driver_initialized = false;
static bool                 driver_in_testing_mode                 = false;          // this variable should be set to true only in the testing process to enable creating an internal frame



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
    Serial.print("INFO>> debug_print_array: frame data from Linear Array Sensor: ");
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
    Serial.print("INFO>> debug_print_decoded_frame_buffer_edge_pixel_indexes: edge pixel indices: ");
    for (int i=0; i< frame_length; i++){
      if (full_decoded_frame_buffer[i].edge_pixel){
        Serial.print(i);
        if (full_decoded_frame_buffer[i].edge_pixel_pair==EDGE_PIXEL_FIRST_PAIR){
          Serial.print("(first pair)");
        } else if(full_decoded_frame_buffer[i].edge_pixel_pair==EDGE_PIXEL_SECOND_PAIR){
          Serial.print("(second pair)");
        } else{
          Serial.print(":? pair");
        }
        Serial.print(", ");
      }
    }
    Serial.println("");
}

static void debug_print_balck_lines_info(){
    if (current_black_lines_info.black_lines_count>0){
    Serial.print("INFO>> debug_print_balck_lines_info: black lines count: ");
    Serial.println(current_black_lines_info.black_lines_count);
    Serial.print("INFO>> debug_print_balck_lines_info: black lines indices: ");
    for (int i=0; i< current_black_lines_info.black_lines_count; i++){
      Serial.print(current_black_lines_info.black_lines_positions[i]);
      Serial.print(", ");
    }
    Serial.println("");
  }
}


static void create_test_frame(int *dest_frame){
    //int   testing_frame [128] = {1021,1021,1021,1020,1021,1021,1022,1019,1021,10,20,10,30,1020,1021,1022,1021,1021,1021,1021,1021,1021,1022,1021,700,600,500,400,20,150,100,100,100,100,20,100,100,100,50,70,200,300,400,500,600,700,1021,1021,1021,1021,1021,1021,1020,1021,1021,1019,1021,1021,1021,1021,1021,1021,1021,1021,1021,1022,1021,1022,1021,1020,1020,1021,1021,1021,1021,1021,1019,1021,1021,1021,1021,1021,1021,1021,1021,1021,1021,1021,1021,1021,1021,1021,1021,1021,1021,1022,1021,1021,1021,1021,1020,1019,1021,1021,1020,1021,1021,1019,1021,1021,1021,1021,1020,1021,1021,1022,1019,1021};
    //peak in 63-64
    //int   testing_frame [128] = {10,20,10,30,10,20,10,30,10,20,10,30,10,20,10,30,10,20,10,30,10,20,10,30,10,20,10,30,10,20,10,30,10,20,10,30,10,20,10,30,40,20,10,30,10,20,10,30,10,20,10,51,52,53,10,30,10,20,10,30,10,20,10,1010,1020,65,10,30,10,20,10,30,10,20,10,30,10,20,10,30,10,20,10,30,10,20,10,30,10,20,10,30,10,20,10,30,10,20,10,30,10,20,10,30,10,20,10,30,10,20,10,30,10,20,10,30,10};
    //peak in 50-54
    int   testing_frame [128] = {10,20,10,30,10,20,10,30,10,20,10,30,10,20,10,30,10,20,10,30,10,20,10,30,10,20,10,30,10,20,10,30,10,20,10,30,10,20,10,30,40,20,10,30,10,20,10,30,10,20,1020,1020,1020,1020,1020,30,10,20,10,30,10,20,10,40,30,65,10,30,10,20,10,30,10,20,10,30,10,20,10,30,10,20,10,30,10,20,10,30,10,20,10,30,10,20,10,30,10,20,10,30,10,20,10,30,10,20,10,30,10,20,10,30,10,20,10,30,10};
    //valley in 10-15 
    //int   testing_frame [128] = {1021,1021,1021,1020,1021,1021,1022,1019,1021,1021,10,11,12,13,14,15,1022,1021,1021,1021,1021,1021,1021,1022,1021,1021,1021,1021,1021,1021,1021,1022,1021,1021,1021,1021,1021,1021,1022,1021,1021,1021,1021,1021,1021,1020,1021,1021,1019,1021,1021,1021,1021,1021,1021,1021,1021,1021,1022,1021,1022,1021,1020,1020,1021,1021,1021,1021,1021,1019,1021,1021,1021,1021,1021,1021,1021,1021,1021,1021,1021,1021,1021,1021,1021,1021,1021,1021,1022,1021,1021,1021,1021,1020,1019,1021,1021,1020,1021,1021,1019,1021,1021,1021,1021,1020,1021,1021,1022,1019,1021};
    //vally in 1-5 int   testing_frame [128] = {10,11,12,13,14,15,1022,1021,1021,1021,1021,1021,1021,1022,1021,1021,1021,1021,1021,1021,1021,1022,1021,1021,1021,1021,1021,1021,1022,1021,1021,1021,1021,1021,1021,1020,1021,1021,1019,1021,1021,1021,1021,1021,1021,1021,1021,1021,1022,1021,1022,1021,1020,1020,1021,1021,1021,1021,1021,1019,1021,1021,1021,1021,1021,1021,1021,1021,1021,1021,1021,1021,1021,1021,1021,1021,1021,1021,1022,1021,1021,1021,1021,1020,1019,1021,1021,1020,1021,1021,1019,1021,1021,1021,1021,1020,1021,1021,1022,1019,1021,1021,1021,1021,1021,1020,1021,1021,1022,1019,1021,1021,1021,1021,1021,1020,1021,1021,1019,1020,1021,1022,1023,1024,1025,1026,1027, 1028};
    //vally in 122-127 
    //int   testing_frame [128] = {1022,1021,1021,1021,1021,1021,1021,1022,1021,1021,1021,1021,1021,1021,1021,1022,1021,1021,1021,1021,1021,1021,1022,1021,1021,1021,1021,1021,1021,1020,1021,1021,1019,1021,1021,1021,1021,1021,1021,1021,1021,1021,1022,1021,1022,1021,1020,1020,1021,1021,1021,1021,1021,1019,1021,1021,1021,1021,1021,1021,1021,1021,1021,1021,1021,1021,1021,1021,1021,1021,1021,1021,1022,1021,1021,1021,1021,1020,1019,1021,1021,1020,1021,1021,1019,1021,1021,1021,1021,1020,1021,1021,1022,1019,1021,1021,1021,1021,1021,1020,1021,1021,1022,1019,1021,1021,1021,1021,1021,1020,1021,1021,1019,1020,1021,1022,1023,1024,1025,1026,1027,1028,22,23,24,25,26,27};

    for (int i= 0; i<128; i++){
        dest_frame[i] = testing_frame[i];
    }
}


/****************************************************************************************
 * STATIC FUNCTIONS
 ***************************************************************************************/

static void locate_black_line_positions(pixel_data_t* full_decoded_frame_buffer, uint8_t frame_length, black_lines_info_t* extracted_black_lines_info){
  if(full_decoded_frame_buffer==NULL || extracted_black_lines_info==NULL){
      Serial.println("ERROR>> locate_black_line_positions: NULL argument pointer");
      return;
  }
  
  //memset the existing black lines info
  memset (extracted_black_lines_info, 0, sizeof(black_lines_info_t));
  
  for (int i= 0; i<frame_length; i++){
    if ((full_decoded_frame_buffer[i].edge_pixel) && (full_decoded_frame_buffer[i].edge_pixel_pair==EDGE_PIXEL_FIRST_PAIR)){
      //find the second edge pixel
      for (int j= i+1; j<frame_length; j++){
        if ((full_decoded_frame_buffer[j].edge_pixel) &&(full_decoded_frame_buffer[j].edge_pixel_pair==EDGE_PIXEL_SECOND_PAIR)){
          extracted_black_lines_info->black_lines_positions[extracted_black_lines_info->black_lines_count]= (i + j)/2;
          if (extracted_black_lines_info->black_lines_count == 0){
            extracted_black_lines_info->black_lines_count= 1;
          } else{
            extracted_black_lines_info->black_lines_count++;
          }
          

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
 */
static void decode_frame_buffer (int *frame_buffer, int frame_length){
  bool rightmost_black_edge_detected= false;
  bool leftmost_black_edge_detected= false;
  
  memset (&decoded_frame_buffer, 0, sizeof(pixel_data_t)*FRAME_BUFFER_LENGTH);
  
  for (int i= 0; i<FRAME_BUFFER_LENGTH; i++){
    //set pixel index
    decoded_frame_buffer[i].pixel_index= i;
    
    if (frame_buffer[i]<BLACK_POINT_THRESHOLD){
      decoded_frame_buffer[i].pixel_color= PIXEL_BLACK;
    } else if (frame_buffer[i]>WHITE_POINT_THRESHOLD){
      decoded_frame_buffer[i].pixel_color= PIXEL_WHITE;
    } else{
      decoded_frame_buffer[i].pixel_color= PIXEL_UNKNOWN;
    }

    //set all pixels as no edge points by default
    decoded_frame_buffer[i].edge_pixel= false;

    //set all pixels as undefined edge pixel pairs
    decoded_frame_buffer[i].edge_pixel_pair=EDGE_PIXEL_UNDEFINED_PAIR;
  }
  
  // loop through the decoded frame of pixels and set the other edge pixels
  for (int i= FRAME_BUFFER_MARGIN_LENGHT+1; i<FRAME_BUFFER_LENGTH-FRAME_BUFFER_MARGIN_LENGHT; i++){
    
    // The following block is intended to set the right most edge point if the line ends with black point 
    if (decoded_frame_buffer[i-1].pixel_color == PIXEL_BLACK && decoded_frame_buffer[i].pixel_color == PIXEL_BLACK){  
        // set the right most pixel as edge pixel if it is black and there are already white pixel encountered at the middle (i.e contrast)
        if ((i==FRAME_BUFFER_LENGTH-FRAME_BUFFER_MARGIN_LENGHT-1) && (leftmost_black_edge_detected) && (!rightmost_black_edge_detected)){
            decoded_frame_buffer[i].edge_pixel= true;
            decoded_frame_buffer[i].edge_pixel_pair= EDGE_PIXEL_SECOND_PAIR;
            rightmost_black_edge_detected = true;
        }
    }

    // The following block is intended to set any black point that is followed by a white point within the margin to be edge point
    else if (decoded_frame_buffer[i-1].pixel_color == PIXEL_BLACK && decoded_frame_buffer[i].pixel_color != PIXEL_BLACK){
        //check if the following white pixel is within the next few pixels
        for (int j = i; j<i+CONTRAST_MARGIN && j<FRAME_BUFFER_LENGTH-FRAME_BUFFER_MARGIN_LENGHT; j++){
          if (decoded_frame_buffer[j].pixel_color == PIXEL_WHITE){
            //set the black pixel as edge pixel
            decoded_frame_buffer[i-1].edge_pixel= true;
            
            //set the black pixel as a second edge pixel pair and look for the first pair before it
            decoded_frame_buffer[i-1].edge_pixel_pair=EDGE_PIXEL_SECOND_PAIR;
            
            // go back and set the left most black pixel as edge pixel if it is not set yet
            for (int x= i-2; (!leftmost_black_edge_detected) && (x>FRAME_BUFFER_MARGIN_LENGHT); x--){

              if (decoded_frame_buffer[x].pixel_color == PIXEL_BLACK && decoded_frame_buffer[x--].pixel_color != PIXEL_BLACK){
                decoded_frame_buffer[x].edge_pixel= true;
                //set the black pixel as a first edge pixel pair
                decoded_frame_buffer[x].edge_pixel_pair=EDGE_PIXEL_FIRST_PAIR;
                leftmost_black_edge_detected= true;
              } else if (x<= FRAME_BUFFER_MARGIN_LENGHT+1){
                // if we reached the beggining of the frame, set the first pixel as edge pixel only if its black
                if (decoded_frame_buffer[x].pixel_color == PIXEL_BLACK){
                  decoded_frame_buffer[x].edge_pixel= true;
                  //set the black pixel as a first edge pixel pair
                  decoded_frame_buffer[x].edge_pixel_pair=EDGE_PIXEL_FIRST_PAIR;
                  leftmost_black_edge_detected= true;
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
        for (int j = i; j<i+CONTRAST_MARGIN && j<frame_length-FRAME_BUFFER_MARGIN_LENGHT; j++){
          if (decoded_frame_buffer[j].pixel_color == PIXEL_BLACK){
            //set the black pixel as the leftmost edge pixel
            decoded_frame_buffer[j].edge_pixel= true;
            leftmost_black_edge_detected= true;
            //set the black pixel as a first edge pixel pair
            decoded_frame_buffer[j].edge_pixel_pair=EDGE_PIXEL_FIRST_PAIR;
            
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
  
  if(!linear_sensor_array_driver_initialized){
      // set the input pins:
      pinMode(analogInputPin, INPUT);
  
      // set the output pins:
      pinMode(exposurePin, OUTPUT);
      pinMode(clkPin, OUTPUT);
      pinMode(togglePin,OUTPUT);

      //set flag to true to avoid multiple initializations
      linear_sensor_array_driver_initialized = true;
  }
  
  return true;
}


//This function is commented out as it is replaced by the new one
/*
black_lines_info_t* linear_sensor_array_driver_get_data() {
  
  //Serial.print("INFO>> linear_sensor_array_driver_get_data: called");
  if (driver_in_testing_mode){
    create_test_frame(frame_buffer);
        
  } else{
      memset(frame_buffer, 0, 128);
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
        sensor_value = analogRead(analogInputPin);
        if (decoded_frame_buffer[i].edge_pixel){
            digitalWrite(togglePin,HIGH); 
        }

        // sotore the analogInputPin value into the array:
        frame_buffer[i]= sensor_value;

        // set the clk LOW
        digitalWrite(clkPin, LOW);
        delayMicroseconds(50);
      }

  }

  // print the frame_buffer to the serial monitor:
  debug_print_array(frame_buffer, FRAME_BUFFER_LENGTH, FRAME_BUFFER_MARGIN_LENGHT);
  
  // decode the frame buffer. Results will be stored in the global variable current_black_lines_info
  decode_frame_buffer(frame_buffer, FRAME_BUFFER_LENGTH);

  //delay 10 m seconds
  delay(10);
  

  return  &current_black_lines_info;
}

*/

int* linear_sensor_array_driver_get_current_frame(){
    return frame_buffer;
}


black_lines_info_t* linear_sensor_array_driver_get_data() {
  
  //Serial.print("INFO>> linear_sensor_array_driver_get_data: called");
  if (driver_in_testing_mode){
    create_test_frame(frame_buffer);
        
  } else{
      memset(frame_buffer, 0, 128);
  
      // set the clk LOW
      digitalWrite(clkPin, LOW);
      delayMicroseconds(50);

      // set the exposurePin HIGH
      digitalWrite(exposurePin, HIGH);
      
      // set the clk HIGH
      digitalWrite(clkPin, HIGH);
      delayMicroseconds(50);
      
      // set the exposurePin LOW
      digitalWrite(exposurePin, LOW);

      digitalWrite(clkPin, LOW);
      delayMicroseconds(50);

      // do the cloking 128times to sample the values of the 128 array of pixels
      for (int i=0; i<128; i++){
        // set the clk HIGH with a half period of 50 micro seconds
        digitalWrite(clkPin, HIGH);
        delayMicroseconds(50);
    
        // read the analogInputPin value:
        sensor_value = analogRead(analogInputPin);

        // sotore the analogInputPin value into the array:
        frame_buffer[i]= sensor_value;

        // set the clk LOW
        digitalWrite(clkPin, LOW);
        delayMicroseconds(50);
      }

  }

  // print the frame_buffer to the serial monitor:
  debug_print_array(frame_buffer, FRAME_BUFFER_LENGTH, FRAME_BUFFER_MARGIN_LENGHT);
  
  // decode the frame buffer. Results will be stored in the global variable current_black_lines_info
  decode_frame_buffer(frame_buffer, FRAME_BUFFER_LENGTH);

  //delay 10 m seconds
  delay(10);
  

  return  &current_black_lines_info;
}


