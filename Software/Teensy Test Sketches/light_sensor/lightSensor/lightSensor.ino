/*
  Linear Array Sensor

 Operates the Linear Array sensor by performing some clocking and get the output analog signal as 128 bit array. 
 The 128 bit array is then processed to define the relative location of a black line. A certain threshold value is defined for the black line. 
 This value can be chaneged based by calibrating the sensor given any condition.

 The circuit:
   * clk pin connected to digital pin 14.
   * SI pin connected to digital pin 15.
   * AOUT pin connected to analog pin A2.

 created 20 Jan. 2016
 by Ali Ba Wazir

 This example code is in the public domain.

 */

/****************************************************************************************
 * PORTS ASSIGNMENTS
 ****************************************************************************************/
const int clkPin          = 14;  // digial sampling pin of the clock
const int exposurePin     = 15;  // digial sampling pin for the sampling
const int togglePin       = 20;  // digial sampling pin for the toggling
const int analogInputPin  = A2;  // Analog input pin for sensor's AOUT signal



/****************************************************************************************
 * DEFINES AND TYPE DEFINITIONS
 ****************************************************************************************/
#define BLACK_POINT_THRESHOLD 300
#define WHITE_POINT_THRESHOLD 1000
#define FRAME_BUFFER_LENGTH 128
#define FRAME_BUFFER_MARGIN_LENGHT 10
#define MAX_CONTRAST_LENGTH 8

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
  uint8_t black_lines_positions[3];       // 3 is maximum black lines decoded
}black_lines_info_t;






/****************************************************************************************
 * GLOBAL VARIABLES
 ***************************************************************************************/
int sensorValue;        // value read from the analogInputPin
int frame_buffer[128];  // data of a single frame as received from the sensor
bool init_frame_decoded= false;  // this boolean is set to true after the initial frame is decoded
int black_lines_count= 0; // the count of the black lines is determined by the initial frame only
pixel_data_t decoded_frame_buffer[FRAME_BUFFER_LENGTH];
black_lines_info_t black_lines_info;


/****************************************************************************************
 * ARDUINO MAIN FUNCTIONS
 ***************************************************************************************/
void setup() {
  // initialize serial communications at 9600 bps:
  Serial.begin(9600);

  // set the input pins:
  pinMode(analogInputPin, INPUT);
  
  // set the output pins:
  pinMode(exposurePin, OUTPUT);
  pinMode(clkPin, OUTPUT);
  pinMode(togglePin,OUTPUT); 
}

void loop() {
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
  
  //decode the frame buffer
  decode_frame_buffer(frame_buffer, FRAME_BUFFER_LENGTH);

  //delay 10 m seconds
  delay(10);
}


/****************************************************************************************
 * DEBUG FUNCTIONS
 ***************************************************************************************/

/*
 * prints the values of an array given its length and an offset of values that need to be ignored
 * 
 * @param input_array    the array to be printed
 * @param length         the length of array to be printed
 * @param margin_offset  an offset to from the start and end of the array where entries should be ignored. 
 *                       This value should be 0 if all entries of the array are to be displayed
 */
void debug_print_array (int *input_array, int length, int margin_offset){
    Serial.print("sensor = ");
    for (int i=(margin_offset-1); i<(length-margin_offset); i++){
       Serial.print(input_array[i]);
       Serial.print(",");
    }
    Serial.println("");
}


void debug_print_decoded_frame_buffer_full_data (pixel_data_t* full_decoded_frame_buffer, uint8_t frame_length){
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

void debug_print_decoded_frame_buffer_edge_pixel_indexes (pixel_data_t* full_decoded_frame_buffer, uint8_t frame_length){
    Serial.print("Edge pixels are: ");
    for (int i=0; i< frame_length; i++){
      if (full_decoded_frame_buffer[i].edge_pixel){
        Serial.print(i);
        Serial.print(", ");
      }
    }
    Serial.println("");
}

void debug_print_balck_lines_info(){
    if (black_lines_info.black_lines_count>0){
    Serial.print("Number of black lines = ");
    Serial.println(black_lines_info.black_lines_count);
    Serial.print("Black lines positions = ");
    for (int i=0; i< black_lines_info.black_lines_count; i++){
      Serial.print(black_lines_info.black_lines_positions[i]);
      Serial.print(", ");
    }
    Serial.println("");
  }
}



/****************************************************************************************
 * STATIC FUNCTIONS
 ***************************************************************************************/

/*
 * decodes an a frame buffer and decides on which proportion of the vector the black line is
 * 
 * @param input_array    the array to be printed
 * @param length         the length of array to be printed
 * @param margin_offset  an offset to from the start and end of the array where entries should be ignored. 
 *                       This value should be 0 if all entries of the array are to be displayed
 */
void decode_frame_buffer (int *frame_buffer, int frame_length){
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
    if (decoded_frame_buffer[i-1].pixel_color == PIXEL_BLACK && decoded_frame_buffer[i].pixel_color == PIXEL_BLACK){
          // set the right most pixel as edge pixel if it is black and there are already white pixel encountered at the middle (i.e contrast)
          if ((i==FRAME_BUFFER_LENGTH-FRAME_BUFFER_MARGIN_LENGHT-1) && (most_left_black_edge_detected) && (!most_right_black_edge_detected)){
            decoded_frame_buffer[i].edge_pixel= true;
            most_right_black_edge_detected = true;
          }
    }
    else if (decoded_frame_buffer[i-1].pixel_color == PIXEL_BLACK && decoded_frame_buffer[i].pixel_color != PIXEL_BLACK){
        //check if the following white pixel is within the next few pixels
        for (int j = i; j<i+MAX_CONTRAST_LENGTH && j<FRAME_BUFFER_LENGTH-FRAME_BUFFER_MARGIN_LENGHT; j++){
          if (decoded_frame_buffer[j].pixel_color == PIXEL_WHITE){
            //set the black pixel as edge pixel
            decoded_frame_buffer[i].edge_pixel= true;
            
            // go back and set the left most black pixel as edge pixel if the it is not set yet
            for (int x= i-2; (!most_left_black_edge_detected) && (x>FRAME_BUFFER_MARGIN_LENGHT); x--){
              if (decoded_frame_buffer[x].pixel_color == PIXEL_BLACK && decoded_frame_buffer[x--].pixel_color != PIXEL_BLACK){
                decoded_frame_buffer[x].edge_pixel= true;
                most_left_black_edge_detected= true;
              } else if (x== FRAME_BUFFER_MARGIN_LENGHT+1){
                // if we reached the beggining of the frame, set the first pixel as edge pixel
                decoded_frame_buffer[x].edge_pixel= true;
                //Serial.println(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> left most edge is detected");
                break;
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
  locate_black_line_positions(decoded_frame_buffer, FRAME_BUFFER_LENGTH, &black_lines_info);

  //print the black lines info
  debug_print_balck_lines_info();

  
}


void locate_black_line_positions(pixel_data_t* full_decoded_frame_buffer, uint8_t frame_length, black_lines_info_t* extracted_info){
  //memset the existing black lines info
  memset (extracted_info, 0, sizeof(black_lines_info_t));
  
  for (int i= 0; i<frame_length; i++){
    if (full_decoded_frame_buffer[i].edge_pixel){
      //find the next edge pixel
      for (int j= i+1; j<frame_length; j++){
        if (full_decoded_frame_buffer[j].edge_pixel){
          extracted_info->black_lines_positions[black_lines_info.black_lines_count]= (i + j)/2;
          extracted_info->black_lines_count++;

          //jump forward
          i=j;
          break;
        }
        
      }
      
    }
    
  }

}

