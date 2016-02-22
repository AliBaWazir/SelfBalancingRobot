#include "application_main.h"
#include "tm_stm32_usart.h"
#define ANGLE_CURRENT		temps[1]	/* ANGLE we actually have */
#define ANGLE_WANT			temps[0]	/* ANGLE we want to have */


#define PID_PARAM_KP		10.0     	/* Proportional */
#define PID_PARAM_KI		0.05		/* Integral */
#define PID_PARAM_KD		0.9			/* Derivative */
#define MINANGLE 200
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
    initSteppers();
    
    TM_USART_Init(USART2, TM_USART_PinsPack_2, 115200);
	
	/* Put test string */
	TM_USART_Puts(USART2, "Hello world\n");
    
    setStepperAccel(1);
    ANGLE_WANT = 0;
    output = 0;
    
    //PID.Kp = PID_PARAM_KP;		/* Proporcional */
	//PID.Ki = PID_PARAM_KI;		/* Integral */
	//PID.Kd = PID_PARAM_KD;		/* Derivative */
    controllerPositionP = 0.05;
    controllerPositionI = 0;
    controllerPositionD = 0;//.05;
    
    controllerAngleP = 60;
    controllerAngleI = 50;//0.2;
    controllerAngleD = 70;//.5;
    
    
    
    
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
    
    
    angle+= 40;
    int aInt = angle;
    char str[5];
    sprintf(str, "%d", aInt);
    TM_USART_Puts(USART2, str);
    TM_USART_Puts(USART2,"\n");
    counter++;
    //if(1){return;};
    //angle6 = angle5;
    //angle5 = angle4;
    //angle4 = angle3;
    angle3 = angle2;
    angle2 = angle1;
    angle1 = angle;
    angle = ((angle2*0.3)+(angle3*0.2)+(angle1*0.5));
    if(HAL_GetTick()<5000)
    {
        
        dWrite(PORTD+12, HIGH);
        
        
        return;
    }
    
    if(abs(angle) > MINANGLE){
        angle = 0;
        discrete_PID_terminate(); //kill PID since robot is lying down
        setStepperCurrentPosition(0);
        
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
    
    //ac4 = ac3;
    ac3 = ac2;
    ac2 = ac1;
    ac1 = output;
    
    acceleration = output;//(+ac3+ac2+ac1)/3.0;
    
    if(output >0)stepperMove(-2000);
    if(output <0)stepperMove(2000);
    setStepperAccel(abs(output)*350);
    
    
    
    
    
    
    
    
    //newSpeed = acceleration/0.1;
    
    //setStepperSpeed(-newSpeed);
    //oldSpeed = newSpeed;
    //if(newSpeed > MAXSPEED&& newSpeed > 0)newSpeed = MAXSPEED;
    //if(newSpeed > -MAXSPEED&& newSpeed < 0)newSpeed = -MAXSPEED;
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

