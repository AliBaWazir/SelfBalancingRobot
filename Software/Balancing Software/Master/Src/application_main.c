#include "application_main.h"
#include "tm_stm32_usart.h"
#include "buttons.h"
#include "arm_math.h"




#define MINANGLE 10000
float temps[2];

double output;


double acceleration = 0;
double newSpeed = 0;
double oldSpeed = -0.1;
double angleSetpoint = 0;
double ac1, ac2, ac3, ac4;
uint32_t counter = 0;





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
    int aInt = angle;
    char str[5];
    sprintf(str, "%d", aInt);
    TM_USART_Puts(UARTTEENSY, str);
    
    if(HAL_GetTick()<10000 )
    {
        TM_GPIO_TogglePinValue(LEDPORT, LED3);
        dWrite(PORTD+12, HIGH);
        TM_USART_Puts(UARTTEENSY,"\n");
        return;
    }
    TM_GPIO_TogglePinValue(LEDPORT, LED4);
    parseCommands();
    noMatlab(angle);
    
    logNewLine();
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

