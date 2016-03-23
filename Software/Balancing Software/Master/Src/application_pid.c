#include "application_pid.h"
#include "tm_stm32_usart.h"
#include "arm_math.h"




#define PID_PARAM_KP		2.5  	/* Proportional */
#define PID_PARAM_KI		1.2		/* Integral */
#define PID_PARAM_KD		.8		/* Derivative */


#define PID_PARAM_KP2		0.5  	/* Proportional */
#define PID_PARAM_KI2		0.0		/* Integral */
#define PID_PARAM_KD2		0.2	/* Derivative */

#define MINANGLE 10000
float pid_error2;
float pid_error;
double setpoints = 0;
int32_t force, force1, force2;
arm_pid_instance_f32 PID;
arm_pid_instance_f32 PID2;

float pid_error;

int32_t angleAdjust;
arm_pid_instance_f32 PID2;

real_T angle1, angle2, angle3, angle4, angle5, angle6;

void application_pid(int32_t angle){
    //angle = angle;
    //angle = angle;
    //angle3 = angle2;
    angle2 = angle1;
    angle1 = angle;
    angle = (angle1+angle2)/2;
    
    pid_error = angle + setpoints;
    
    pid_error2 = stepperCurrentPosition();
    
    
    force = arm_pid_f32(&PID, pid_error);
    setpoints = arm_pid_f32(&PID2, pid_error2);
    if(setpoints>150)arm_pid_reset_f32(&PID2);
    if(setpoints<-150)arm_pid_reset_f32(&PID2);
    if(force > 10000||force <-10000)arm_pid_reset_f32(&PID);
    
    //if(force >0)stepperMove(-500);
    //if(force <0)stepperMove(500);
    //setStepperAccel((float)abs(force));
    force2=force1;
    force1=force;
    force = (force2+force1)/2;
    setStepperSpeed((float)force);
    TM_USART_Puts(USART3,"^");
    char str2[5];
    sprintf(str2, "%d", (int)setpoints);
    
    //setStepperCurrentPosition(0);
    
    TM_USART_Puts(USART3, str2);
    
    TM_USART_Puts(USART3,"\n");
    
}


void init_pid(void){
    PID.Kp = PID_PARAM_KP;        /* Proporcional */
    PID.Ki = PID_PARAM_KI;        /* Integral */
    PID.Kd = PID_PARAM_KD;        /* Derivative */
    arm_pid_init_f32(&PID, 1);
    
    
    //pid2
    PID2.Kp = PID_PARAM_KP2;        /* Proporcional */
    PID2.Ki = PID_PARAM_KI2;        /* Integral */
    PID2.Kd = PID_PARAM_KD2;        /* Derivative */
    arm_pid_init_f32(&PID2, 1);
    
}