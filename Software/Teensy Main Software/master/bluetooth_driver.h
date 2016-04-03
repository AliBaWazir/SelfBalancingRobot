#include "arduino.h"

/****************************************************************************************
 * DEFINES AND TYPE DEFINITIONS
 ****************************************************************************************/
typedef enum{
    BLUETOOTH_DRIVER_DATA_TYPE_MODE,
    BLUETOOTH_DRIVER_DATA_TYPE_DIRECTION
}bluetooth_driver_data_type_e;


typedef enum {
    BLUETOOTH_MODULE_DATA_ERROR= -1,
    
    BLUETOOTH_MODULE_DATA_MODE_MANUAL=0,
    BLUETOOTH_MODULE_DATA_MODE_LINE_FOLLOWING,

    BLUETOOTH_MODULE_DATA_DIRECTION_FORWARD=10,
    BLUETOOTH_MODULE_DATA_DIRECTION_RIGHT,
    BLUETOOTH_MODULE_DATA_DIRECTION_BACKWARD,
    BLUETOOTH_MODULE_DATA_DIRECTION_LEFT,
    BLUETOOTH_MODULE_DATA_DIRECTION_UNKNOWN
    
} bluetooth_module_data_e;

/****************************************************************************************
 * GLOBAL VARIABLES
 ****************************************************************************************/

/****************************************************************************************
 * PUBLIC FUNCTIONS PROTOTYPES
 ****************************************************************************************/
bool bluetooth_driver_init();
bluetooth_module_data_e bluetooth_driver_get_data(bluetooth_driver_data_type_e data_type);
