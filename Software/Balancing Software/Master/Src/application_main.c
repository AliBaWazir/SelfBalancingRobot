#include "application_main.h"

#define ANGLE_CURRENT		temps[1]	/* ANGLE we actually have */
#define ANGLE_WANT			temps[0]	/* ANGLE we want to have */


#define PID_PARAM_KP		10.0     	/* Proportional */
#define PID_PARAM_KI		0.05		/* Integral */
#define PID_PARAM_KD		0.9			/* Derivative */
float temps[2];
float pid_error;
float output;
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
// This is where it happens
void setup(){
    TM_RCC_InitSystem();
    TM_DELAY_Init();
    initSteppers();
    
    setStepperAccel(1);
    ANGLE_WANT = 0;
    output = 0;
    
    //PID.Kp = PID_PARAM_KP;		/* Proporcional */
	//PID.Ki = PID_PARAM_KI;		/* Integral */
	//PID.Kd = PID_PARAM_KD;		/* Derivative */
    controllerPositionP = 0.01;
    controllerPositionI = 0;
    controllerPositionD = 0.01;
    
    controllerAngleP = 10;
    controllerAngleI = 6;
    controllerAngleD = 0.2;
    
    
    
    
    /* Initialize PID system, float32_t format */
	//arm_pid_init_f32(&PID, 1);
    discrete_PID_initialize();
}
//This function gets called by the MPU with angle Data



void application_main(int16_t angle){
    angle6 = angle5;
    angle5 = angle4;
    angle4 = angle3;
    angle3 = angle2;
    angle2 = angle1;
    angle1 = angle;
    angle = (angle6+angle5+angle4+angle2+angle3+angle1)/6;
    if(HAL_GetTick()<5000)
    {
        
        dWrite(PORTD+12, HIGH);
        return;
    }
	controllerInputAngle = -angle;
    controllerInputPosition = 0 + (real_T)stepperCurrentPosition();
	__disable_irq();
	rt_OneStep();
	__enable_irq();
    
    output = controllerOutput;
    
    acceleration = output;
    
    newSpeed = acceleration/10;
    
    setStepperSpeed(-newSpeed);
    //oldSpeed = newSpeed;
    if(newSpeed> MAXSPEED&& newSpeed >0)newSpeed = MAXSPEED;
    if(newSpeed> -MAXSPEED&& newSpeed <0)newSpeed = -MAXSPEED;
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
   runSpeed(); 
}

