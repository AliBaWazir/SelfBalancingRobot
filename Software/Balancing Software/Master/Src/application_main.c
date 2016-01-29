#include "application_main.h"

// This is where it happens
void setup(){
    TM_RCC_InitSystem();
    TM_DELAY_Init();
    initSteppers();
    setStepperSpeed((int16_t)500000);
    
}
//This function gets called by the MPU with angle Data
void application_main(int16_t angle){
    //if(angle >0){
        
        
    //}
    //else{
    //    setStepperSpeed(-5000);
    //}

    
    /*
    while(1){
               
        TM_RCC_InitSystem();
       
        HAL_Init();
        TM_DELAY_Init();
        
        TM_GPIO_Init(GPIOD, 0x1000U, TM_GPIO_Mode_OUT, TM_GPIO_OType_PP, TM_GPIO_PuPd_NOPULL, TM_GPIO_Speed_High);
        
        //
        initSteppers();
        
        while (1) {
                HAL_Delay(100);
                TM_GPIO_SetPinHigh(GPIOD, (uint16_t)(0x1000U));
                HAL_Delay(100);
                TM_GPIO_SetPinLow(GPIOD, (uint16_t)(0x1000U));
                Theta = 5;
                main_pend();
                stepperProgram();
        }
        
    }
    */
    
}

void TM_DELAY_1msHandler(){
   runSpeed();
   
    
}

