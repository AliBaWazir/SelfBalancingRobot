
#include "buttons_driver.h"

/****************************************************************************************
 * HARDWARE PORTS ASSIGNMENTS
 ****************************************************************************************/
const int button_right =28;
const int button_left  =27;


/****************************************************************************************
 * GLOBAL VARIABLES
 ***************************************************************************************/

 
/****************************************************************************************
 * STATIC VARIABLES
 ****************************************************************************************/
static bool buttons_driver_initialized               = false;
static bool driver_in_testing_mode                   = false;
static bool button_right_ON                          = false;
static bool button_left_ON                           = false;




/****************************************************************************************
 * STATIC FUNCTION PROTOTYPES
 ***************************************************************************************/

static void button_right_up(){
    button_right_ON= true;
    button_left_ON= false;
}

static void button_left_up(){
    button_left_ON= true;
    button_right_ON= false;
}


 
/****************************************************************************************
 * STATIC FUNCTIONS
 ***************************************************************************************/



/****************************************************************************************
 * PUBLIC FUNCTIONS
 ***************************************************************************************/
bool buttons_driver_init(){
    bool ret = true;

    if(!buttons_driver_initialized){
        //initialize the buttons' PINs
        pinMode(button_right, INPUT);
        pinMode(button_left, INPUT);

        //attach inturrupts
        attachInterrupt (button_right, button_right_up, RISING);  // attach button_right interrupt handler 
        attachInterrupt (button_left, button_left_up, RISING);  // attach button_left interrupt handler
        
        buttons_driver_initialized = true;
    }

    return ret;
}

//will return which button is ON and will return
button_on_en get_button_on(){
    button_on_en  retcode= BUTTON_ON_NONE;
    
    if (button_right_ON){
        retcode= BUTTON_ON_RIGHT;
    } else if (button_left_ON){
        retcode= BUTTON_ON_LEFT;
    }

    return retcode;
}

