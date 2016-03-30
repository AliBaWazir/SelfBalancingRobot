
#include "bluetooth_driver.h"

/****************************************************************************************
 * HARDWARE PORTS ASSIGNMENTS
 ****************************************************************************************/



/****************************************************************************************
 * GLOBAL VARIABLES
 ***************************************************************************************/

 
/****************************************************************************************
 * STATIC VARIABLES
 ****************************************************************************************/
static bool bluetooth_driver_initialized             = false;
static bool driver_in_testing_mode                   = true;



/****************************************************************************************
 * STATIC FUNCTION PROTOTYPES
 ***************************************************************************************/




 
/****************************************************************************************
 * STATIC FUNCTIONS
 ***************************************************************************************/



/****************************************************************************************
 * PUBLIC FUNCTIONS
 ***************************************************************************************/
bool bluetooth_driver_init(){
    bool ret = true;

    if(!bluetooth_driver_initialized){
        //initialize serial port for bluetooth module
        Serial3.begin(9600);
        
        bluetooth_driver_initialized = true;
    }

    return ret;
}

bluetooth_module_data_e bluetooth_driver_get_data(bluetooth_driver_data_type_e data_type){
    bluetooth_module_data_e ret_code = BLUETOOTH_MODULE_DATA_ERROR;
    char inByte ='\0';
    
    //get command from bluetooth module via serial1 port
    if (Serial3.available()) {
        inByte = Serial3.read();
  
    } else{
            Serial.println("ERROR>> bluetooth_driver_get_data: serial1 is not available. Will put the robot in line following mode");
            if (driver_in_testing_mode){
                ret_code= BLUETOOTH_MODULE_DATA_MODE_LINE_FOLLOWING;
            } else{
                return ret_code;
            }
    }
    
    switch(data_type){
        if(data_type==BLUETOOTH_DRIVER_DATA_TYPE_MODE){
            switch(inByte){
                case 'M': //manual mode
                    ret_code= BLUETOOTH_MODULE_DATA_MODE_MANUAL;
                break;

                case 'A': // auto mode (i.e. line following mode)
                    ret_code= BLUETOOTH_MODULE_DATA_MODE_LINE_FOLLOWING;
                break;

                default:
                    Serial.print("ERROR>> bluetooth_driver_get_data: received UNKNOWN MODE type from serial port");
                break;
            }
          
        } else if(data_type==BLUETOOTH_DRIVER_DATA_TYPE_DIRECTION){
          
            switch(inByte){
                case 'F':
                    Serial.println("INFO>> bluetooth_driver_get_data: command= FORWARD");
                    ret_code= BLUETOOTH_MODULE_DATA_DIRECTION_FORWARD;
                break;
    
                case 'R':
                    Serial.println("INFO>> bluetooth_driver_get_data: command= RIGHT");
                    ret_code= BLUETOOTH_MODULE_DATA_DIRECTION_RIGHT;
                break;

                case 'B':
                    Serial.println("INFO>> bluetooth_driver_get_data: command= BACKWARD");
                    ret_code= BLUETOOTH_MODULE_DATA_DIRECTION_BACKWARD;
                break;
                
                case 'L':
                    Serial.println("INFO>> bluetooth_driver_get_data: command= LEFT");
                    ret_code= BLUETOOTH_MODULE_DATA_DIRECTION_LEFT;
                break;
    
                default:
                    Serial.println("ERROR>> bluetooth_driver_get_data: received UNKNOWN COMMAND type from serial port");
                break;        
            }
            
        }else{
            Serial.print("ERROR>> bluetooth_driver_get_data: data_type is UNKNOWN");
        }

    }
    return ret_code;
}
