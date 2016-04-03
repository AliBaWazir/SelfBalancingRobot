#include "buttons.h"
TM_BUTTON_t* leftButton;
TM_BUTTON_t* rightButton;
uint8_t leftButtonState = 0;
uint8_t rightButtonState = 0;

uint8_t state = 0;
static void leftButton_Callback(TM_BUTTON_t* ButtonPtr, TM_BUTTON_PressType_t PressType);
static void rightButton_Callback(TM_BUTTON_t* ButtonPtr, TM_BUTTON_PressType_t PressType);

void setupButtons(void){
    leftButton = TM_BUTTON_Init(GPIOB, 
                              BUTTONLEFTPIN, 
                              leftButtonState,
                              leftButton_Callback);
    rightButton = TM_BUTTON_Init(GPIOB, 
                              BUTTONRIGHTPIN, 
                              rightButtonState,
                              rightButton_Callback);
}

void updateButtons(void){
    
     TM_BUTTON_Update();
}

static void leftButton_Callback(TM_BUTTON_t* ButtonPtr, TM_BUTTON_PressType_t PressType) {
    /* Normal press detected */
    if (PressType == TM_BUTTON_PressType_Normal) {
        /* Set LEDS ON */
        TM_GPIO_SetPinHigh(LEDPORT, LEDALL);
        state = 0;
    } else if (PressType == TM_BUTTON_PressType_Long) {
        /* Set LEDS OFF */

    }
}
static void rightButton_Callback(TM_BUTTON_t* ButtonPtr, TM_BUTTON_PressType_t PressType) {
    /* Normal press detected */
    if (PressType == TM_BUTTON_PressType_Normal) {
        /* Set LEDS ON */
        TM_GPIO_SetPinLow(LEDPORT, LED1);
        state = 1;
        
    } else if (PressType == TM_BUTTON_PressType_Long) {
        /* Set LEDS OFF */

    }
    
    
}
