#include "application_pid.h"
#include "tm_stm32_usart.h"
#include "arm_math.h"




#define PID_PARAM_KP		10;//10//2.5/2  	/* Proportional */
#define PID_PARAM_KI		0;//1.2/2		/* Integral */
#define PID_PARAM_KD		0;.4		/* Derivative */


#define PID_PARAM_KP2		0.5  	/* Proportional */
#define PID_PARAM_KI2		0		/* Integral */
#define PID_PARAM_KD2		0
	/* Derivative */

#define MINANGLE 10000
float pid_error2;
float pid_error;
double setpoints = 0;
int32_t force, force1, force2;
arm_pid_instance_f32 anglePID;
arm_pid_instance_f32 positionPID;
double scaleFactor = 1;
float pid_error;
uint16_t positionCounter = 0;
int32_t angleAdjust;
double angle1, angle2, angle3, angle4, angle5, angle6;
void application_pid(int32_t angle){
    
    

    angle = angle+100;
    angle2 = angle1;
    angle1 = angle;
    angle = (angle1+angle2)/2;
    
    
     if((force>0 && stepperCurrentPosition() <0)||(force<0 && stepperCurrentPosition() >0)){
               pid_error = angle + (setpoints*scaleFactor);
              TM_USART_Puts(UARTTEENSY,"YES");
            } 
            else{
              pid_error = angle+ setpoints;
              TM_USART_Puts(UARTTEENSY,"NO");
            }
    
     
  
   
    
    

   
    
    TM_USART_Puts(UARTTEENSY,"^");
    char str2[5];
    sprintf(str2, "%d", (int)pid_error);
    
    TM_USART_Puts(UARTTEENSY, str2);
    
    TM_USART_Puts(UARTTEENSY,"\n");
            
            
    pid_error2 = stepperCurrentPosition();
    
    
    force = arm_pid_f32(&anglePID, pid_error);
    if(positionCounter >= 5){
        setpoints = arm_pid_f32(&positionPID, pid_error2);
        positionCounter=0;
    }
    positionCounter++;
    
    if(setpoints>600 || setpoints<-600){
        
        arm_pid_reset_f32(&positionPID);
        setpoints = 0;
        setStepperCurrentPosition(0);
    }

    if(force > 10000||force <-10000)arm_pid_reset_f32(&anglePID);

    force2=force1;
    force1=force;
    force = (force2+force1)/2;
    
    
    scaleFactor = 1;//((1000-abs(force))/1000.0);
    
    //motor output
    setStepperSpeed((float)force);
    
    
    writeLog("Angle:", angle)
    writeLog("Setpoints",setpoints);
    writeLog("Force", force);

    
}

void resetPID(void){
    
    
}


void init_pid(void){
    anglePID.Kp = PID_PARAM_KP;        /* Proporcional */
    anglePID.Ki = PID_PARAM_KI;        /* Integral */
    anglePID.Kd = PID_PARAM_KD;        /* Derivative */
    arm_pid_init_f32(&anglePID, 1);
    
    
    //pid2
    positionPID.Kp = PID_PARAM_KP2;        /* Proporcional */
    positionPID.Ki = PID_PARAM_KI2;        /* Integral */
    positionPID.Kd = PID_PARAM_KD2;        /* Derivative */
    arm_pid_init_f32(&positionPID, 1);
    
}
