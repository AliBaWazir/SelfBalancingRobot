#include "application_main.h"
#include "tm_stm32_usart.h"
#include "buttons.h"
#include "arm_math.h"




#define MINANGLE 10000
float temps[2];


int32_t zeroAngle = 72;
uint8_t calibrateFlag = 0;
uint8_t state = 3;
uint32_t calibrateCounter = 200;
double acceleration = 0;
double newSpeed = 0;
double oldSpeed = -0.1;
double angleSetpoint = 0;
double ac1, ac2, ac3, ac4;
uint32_t counter = 0;

uint8_t ledCounter = 0;



void setup(){
    initLED();
    setupButtons();
    TM_DELAY_Init();
    initSteppers();
    initTimerInterrupt();
    setupLog();
    stepperEnable();
    init_pid();
}


void userLoop(){
    if(runFlag >= 1){
        runFlag = 0;
        //runSpeed(); 
        
    }
}

void noMatlab(int32_t angle){
    application_pid(angle);
}

void application_main(int32_t angle){
    updateButtons();    
    switch (state){
        case 0:
            stepperDisable();
            TM_GPIO_SetPinLow(LEDPORT, LEDALL);
        break;
        case 1:
            stepperEnable();
            switch(ledCounter){
                case 0:
                    TM_GPIO_TogglePinValue(LEDPORT, LED1);
                break;
                case 32:
                    TM_GPIO_TogglePinValue(LEDPORT, LED2);
                break;
                case 64:
                    TM_GPIO_TogglePinValue(LEDPORT, LED3);
                break;
                case 96:
                    TM_GPIO_TogglePinValue(LEDPORT, LED4);
                break;
                default:
                break;         
            }
            ledCounter +=16;
            parseCommands();
            noMatlab(angle);
            logNewLine();
        break;
        case 2:
            stepperDisable();
            calibrateZero(angle);
        break;
        case 3:
            if(HAL_GetTick()<10000)TM_GPIO_TogglePinValue(LEDPORT, LED3);
        break;
        default:
        break;                
    }
}
void setCalibrateFlag(uint8_t flag){
    calibrateFlag = flag;
}

TIM_HandleTypeDef TIM_Handle;
void initTimerInterrupt(void)
{
    __TIM4_CLK_ENABLE();
    TIM_Handle.Init.Prescaler = 0;
    TIM_Handle.Init.CounterMode = TIM_COUNTERMODE_UP;
    TIM_Handle.Init.Period = 8399; //50us//13439;
    TIM_Handle.Instance = TIM4;   //Same timer whose clocks we enabled
    HAL_TIM_Base_Init(&TIM_Handle);     // Init timer
    HAL_TIM_Base_Start_IT(&TIM_Handle); // start timer interrupts
    HAL_NVIC_SetPriority(TIM4_IRQn, 5, 15);
    HAL_NVIC_EnableIRQ(TIM4_IRQn);

}

void calibrateZero(int32_t angle){
    
    
    if(!calibrateCounter){
        calibrateCounter = 200;
        zeroAngle = angle;
        TM_GPIO_SetPinLow(LEDPORT, LED2);
        setState(1);
    }
    else{
        calibrateCounter--;
        TM_GPIO_TogglePinValue(LEDPORT, LED2);
    }
  
}
void setState(uint8_t newState){
    state = newState;
}
int32_t getZeroAngle(void){
    return zeroAngle;
}
void TIM4_IRQHandler(void)
{
    if (__HAL_TIM_GET_FLAG(&TIM_Handle, TIM_FLAG_UPDATE) != RESET)      //In case other interrupts are also running
    {
        if (__HAL_TIM_GET_ITSTATUS(&TIM_Handle, TIM_IT_UPDATE) != RESET)
        {
            __HAL_TIM_CLEAR_FLAG(&TIM_Handle, TIM_FLAG_UPDATE);
            /*put your code here */
            
            stepperRun();
            
            
        }
    }
}

