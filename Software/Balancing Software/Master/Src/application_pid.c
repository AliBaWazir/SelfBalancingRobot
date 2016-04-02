#include "application_pid.h"
#include "tm_stm32_usart.h"
#include "arm_math.h"




#define PID_PARAM_KP		10//2.5/2  	/* Proportional */
#define PID_PARAM_KI		0;//1.2/2		/* Integral */
#define PID_PARAM_KD		.8/2		/* Derivative */


#define PID_PARAM_KP2		0.5  	/* Proportional */
#define PID_PARAM_KI2		0		/* Integral */
#define PID_PARAM_KD2		0.00
	/* Derivative */

#define MINANGLE 10000
float pid_error2;
float pid_error;
double setpoints = 0;
int32_t force, force1, force2;
arm_pid_instance_f32 PID;
arm_pid_instance_f32 PID2;
double scaleFactor = 1;
float pid_error;
uint16_t positionCounter = 0;

int32_t angleAdjust;
arm_pid_instance_f32 PID2;

real_T angle1, angle2, angle3, angle4, angle5, angle6;

struct teensyData{
    int16_t packetId;
    int16_t leftMotorSteps;
    int16_t rightMotorSteps;
    int16_t userData;
    
};

void application_pid(int32_t angle){
    
    
    uint8_t data = TM_USART_Getc(UARTTEENSY);
    if(data){
      TM_USART_Putc(UARTFTDI,data); 
    }
    
    //angle = angle;
    //angle = angle;
    //angle3 = angle2;
    angle = angle+100;
    angle2 = angle1;
    angle1 = angle;
    angle = (angle1+angle2)/2;
    
    
     if((force>0 && stepperCurrentPosition() <0)||(force<0 && stepperCurrentPosition() >0)){
               pid_error = angle + (setpoints*scaleFactor);
              TM_USART_Puts(USART3,"YES");
            } 
            else{
              pid_error = angle+ setpoints;
              TM_USART_Puts(USART3,"NO");
            }
    
     
            
            
    TM_USART_Puts(USART3,"^");
    char str3[5];
    sprintf(str3, "%d", (int)setpoints);
    
    TM_USART_Puts(USART3, str3);
    
    //TM_USART_Puts(USART3,"\n");
   
    
    TM_USART_Puts(USART3,"^");
    char str2[5];
    sprintf(str2, "%d", (int)pid_error);
    
    TM_USART_Puts(USART3, str2);
    
    TM_USART_Puts(USART3,"\n");
            
            
    pid_error2 = stepperCurrentPosition();
    
    
    force = arm_pid_f32(&PID, pid_error);
    if(positionCounter >= 5){
        setpoints = arm_pid_f32(&PID2, pid_error2);
        positionCounter=0;
    }
    positionCounter++;
    if(setpoints>600 || setpoints<-600){
        
        arm_pid_reset_f32(&PID2);
        setpoints = 0;
        setStepperCurrentPosition(0);
    }

    if(force > 10000||force <-10000)arm_pid_reset_f32(&PID);
    
    //if(force >0)stepperMove(-500);
    //if(force <0)stepperMove(500);
    //setStepperAccel((float)abs(force));
    force2=force1;
    force1=force;
    force = (force2+force1)/2;
    
    
    scaleFactor = 1;//((1000-abs(force))/1000.0);
    
   
    setStepperSpeed((float)force);
    
    
    
    
    

    
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
