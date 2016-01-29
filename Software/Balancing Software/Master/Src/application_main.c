#include "application_main.h"

#define ANGLE_CURRENT		temps[1]	/* ANGLE we actually have */
#define ANGLE_WANT			temps[0]	/* ANGLE we want to have */


#define PID_PARAM_KP		10.0     	/* Proportional */
#define PID_PARAM_KI		0.05		/* Integral */
#define PID_PARAM_KD		0.9			/* Derivative */
float temps[2];
float pid_error;
float output;

arm_pid_instance_f32 PID;


// This is where it happens
void setup(){
    TM_RCC_InitSystem();
    TM_DELAY_Init();
    initSteppers();
    
    setStepperAccel(1);
    ANGLE_WANT = -0.02;
    output = 0;
    
    PID.Kp = PID_PARAM_KP;		/* Proporcional */
	PID.Ki = PID_PARAM_KI;		/* Integral */
	PID.Kd = PID_PARAM_KD;		/* Derivative */

    
    /* Initialize PID system, float32_t format */
	arm_pid_init_f32(&PID, 1);
    
}
//This function gets called by the MPU with angle Data
void application_main(int16_t angle){
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
   
    
   
    
}
void TM_DELAY_1msHandler(){
   runSpeed();
   
   
    
}

