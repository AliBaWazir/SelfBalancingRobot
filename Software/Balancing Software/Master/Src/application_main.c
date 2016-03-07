#include "application_main.h"
#include "tm_stm32_usart.h"

#define ANGLE_CURRENT		temps[1]	/* ANGLE we actually have */
#define ANGLE_WANT			temps[0]	/* ANGLE we want to have */


#define PID_PARAM_KP		10.0     	/* Proportional */
#define PID_PARAM_KI		0.05		/* Integral */
#define PID_PARAM_KD		0.9			/* Derivative */
#define MINANGLE 10000
float temps[2];
float pid_error;
double output;
int32_t force;
arm_pid_instance_f32 PID;
real_T  controllerAngleP, 
        controllerAngleI, 
        controllerAngleD, 
        controllerInputAngle, 
        controllerOutput,
        controllerPositionI,
        controllerPositionP,
        controllerPositionD,
        controllerInputPosition;
double acceleration = 0;
double newSpeed = 0;
double oldSpeed = -0.1;
real_T angleSetpoint = 0;
real_T angle1, angle2, angle3, angle4, angle5, angle6;
real_T ac1, ac2, ac3, ac4;
uint32_t counter = 0;
// This is where it happens
void setup(){
    //TM_RCC_InitSystem();
    TM_DELAY_Init();
    //initSteppers();
    initTimerInterrupt();
    TM_USART_Init(USART3, TM_USART_PinsPack_2, 115200);
	
	/* Put test string */
	TM_USART_Puts(USART3, "Hello world\n");
    
    setStepperAccel(1);
    ANGLE_WANT = 0;
    output = 0;
    
    //PID.Kp = PID_PARAM_KP;		/* Proporcional */
	//PID.Ki = PID_PARAM_KI;		/* Integral */
	//PID.Kd = PID_PARAM_KD;		/* Derivative */
    controllerPositionP = 0;//;500;//.05;
    controllerPositionI = 0;
    controllerPositionD = 0;//1;//.05;
    double scaleFactor = 0.1;
    controllerAngleP = 1.2*scaleFactor;
    controllerAngleI = 0;//0.01;//.1*scaleFactor;//0.2;
    controllerAngleD = 0;//0.15;//.5*scaleFactor;//.5;
    
    
    
    
    /* Initialize PID system, float32_t format */
	//arm_pid_init_f32(&PID, 1);
    discrete_PID_initialize();
}
//This function gets called by the MPU with angle Data

void userLoop(){
    if(runFlag >= 1){
        runFlag = 0;
        //runSpeed(); 
        
    }
}

void application_main(int32_t angle){
    
    
    angle+= 10;
    //angle = angle*abs(angle)/100;
    
    
    counter++;
    //if(1){return;};
    /*
    angle6 = angle5;
    angle5 = angle4;
    angle4 = angle3;
    angle3 = angle2;
    angle2 = angle1;
    angle1 = angle;
    angle = ((angle1*0.3)+(angle2*0.2)+(angle3*0.2)+(angle4*0.2)+(angle5*0.1)+(angle6*0.1));
    */
    /*
    int aInt = angle;
    char str[5];
    
    sprintf(str, "%d", aInt);
    //TM_USART_Puts(USART3, "Angle: ");
    TM_USART_Puts(USART3, str);
    */
    if(HAL_GetTick()<1000)
    {
        
        dWrite(PORTD+12, HIGH);
        TM_USART_Puts(USART3,"\n");
        
        return;
    }
    
    if(abs(angle) > MINANGLE){
        angle = 0;
        discrete_PID_terminate(); //kill PID since robot is lying down
        setStepperCurrentPosition(0);

        TM_USART_Puts(USART3,"^F!\n");
  
        return;
    }
    if(rtmGetErrorStatus(discrete_PID_M) != (NULL)){
        discrete_PID_initialize();
    }
	controllerInputAngle = -angle;
    controllerInputPosition = (real_T)stepperCurrentPosition();
	__disable_irq();
	rt_OneStep();
	__enable_irq();
    
    output = controllerOutput;
    /*
    ac4 = ac3;
    ac3 = ac2;
    ac2 = ac1;
    ac1 = output;
    
    acceleration = (+ac3+ac2+ac1)/3.0;//output;//(+ac3+ac2+ac1)/3.0;
   */
    acceleration = output;
    
    /*
    TM_USART_Puts(USART3,"^");
    char str2[5];
    sprintf(str2, "%d", (int)acceleration);
    
    
    
    TM_USART_Puts(USART3, str2);
    
    TM_USART_Puts(USART3,"\n");
    
    */
    
   
    if(output >0)stepperMove(-20000);
    if(output <0)stepperMove(20000);
    setStepperAccel(abs(output)*300);
    
    
    
    
    
    
    
    
    
	/*
    ANGLE_CURRENT = angle/10;
    if(abs(ANGLE_CURRENT) > 7){
        stepperMoveTo(stepperCurrentPosition());
    return;
    }
    
    pid_error = ANGLE_CURRENT - ANGLE_WANT;
    
    
    output = arm_pid_f32(&PID, pid_error)/10;
    if (output> 5) {
				output = 5;
			} else if (output < -5) {
				output = -5;
			}
    
    
    stepperMoveTo(stepperCurrentPosition()+output);
    //Delay(1);
   
    
   */
    
}
void TM_DELAY_1msHandler(){
   //runSpeed(); 
}

TIM_HandleTypeDef TIM_Handle;
void initTimerInterrupt(void)
{
    __TIM4_CLK_ENABLE();
    TIM_Handle.Init.Prescaler = 0;
    TIM_Handle.Init.CounterMode = TIM_COUNTERMODE_UP;
    TIM_Handle.Init.Period = 13439;
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
            
            runSpeed();
            
            
        }
    }
}


