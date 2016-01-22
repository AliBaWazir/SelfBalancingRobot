/**
 * Keil project template
 *
 * Before you start, select your target, on the right of the "Load" button
 *
 * @author    Tilen Majerle
 * @email     tilen@majerle.eu
 * @website   http://stm32f4-discovery.com
 * @ide       Keil uVision 5
 * @conf      PLL parameters are set in "Options for Target" -> "C/C++" -> "Defines"
 * @packs     STM32F4xx Keil packs version 2.4.0 or greater required
 * @stdperiph STM32F4xx Standard peripheral drivers version 1.5.0 or greater required
 */
/* Include core modules */
#include "stm32f4xx.h"
/* Include my libraries here */
#include "arduino32.h"
#include "defines.h"
#include "tm_stm32f4_delay.h"
#include "tm_stm32f4_disco.h"
#include "AccelStepper.h"
#define OUTPUTPIN  4*16+3

#define PORTPINS 16

#define PORTA PORTPINS*0
#define PORTB PORTPINS*1
#define PORTC PORTPINS*2
#define PORTD PORTPINS*3
#define PORTE PORTPINS*4
#define PORTF PORTPINS*5
#define PORTG PORTPINS*6
#define PORTH PORTPINS*7

#define STEPPER_RIGHT_STEP_PIN PORTA+2
#define STEPPER_RIGHT_DIR_PIN PORTA+5



#define STEPPER_LEFT_STEP_PIN PORTC+3
#define STEPPER_LEFT_DIR_PIN PORTC+4


#define STEPPER_RIGHT_M0_PIN PORTC+7
#define STEPPER_RIGHT_M1_PIN PORTC+6

#define STEPPER_LEFT_M0_PIN PORTD+14
#define STEPPER_LEFT_M1_PIN PORTD+15


void TM_DELAY_1msHandler()
{
	//digitalWrite(OUTPUTPIN, HIGH);
	//Delay(5);
	//digitalWrite(OUTPUTPIN, LOW);
	
}
AccelStepper stepperR(AccelStepper::DRIVER, STEPPER_RIGHT_STEP_PIN, STEPPER_RIGHT_DIR_PIN);
AccelStepper stepperL(AccelStepper::DRIVER, STEPPER_LEFT_STEP_PIN, STEPPER_LEFT_DIR_PIN);
int main(void) {
	

	

	SystemInit();
	

	TM_DELAY_Init();
	pinMode(PORTD+11, OUTPUT);
    digitalWrite(PORTD+11, HIGH);
    
    pinMode(STEPPER_RIGHT_M0_PIN, INPUT);
    pinMode(STEPPER_RIGHT_M1_PIN, OUTPUT);
    pinMode(STEPPER_LEFT_M0_PIN, INPUT);
    pinMode(STEPPER_LEFT_M1_PIN, OUTPUT);
    
    /*   M0    M1
    FULL LOW   LOW
    HALF HIGH  LOW
    1/4  FLOAT LOW
    */
    
    
    //digitalWrite(STEPPER_RIGHT_M0_PIN, HIGH);
    digitalWrite(STEPPER_RIGHT_M1_PIN, LOW);
    
    //digitalWrite(STEPPER_LEFT_M0_PIN, HIGH);
    digitalWrite(STEPPER_LEFT_M1_PIN, HIGH);
    
    
    pinMode(STEPPER_RIGHT_DIR_PIN, OUTPUT);
    pinMode(STEPPER_RIGHT_STEP_PIN, OUTPUT);
    pinMode(STEPPER_LEFT_DIR_PIN, OUTPUT);
    pinMode(STEPPER_LEFT_STEP_PIN, OUTPUT);

	stepperR.setMaxSpeed(10000.0);
    stepperR.setAcceleration(2000.0);
    
    stepperL.setMaxSpeed(10000000.0);
    stepperL.setAcceleration(2000.0);
	stepperR.setSpeed(600);
    stepperL.setSpeed(600);


	
	while (1) {
        
        //stepperR.runToNewPosition(0);
        //stepperR.runToNewPosition(2000);
        //stepperL.runToNewPosition(0);
        //stepperL.runToNewPosition(2000);
        
        
        //for(uint32_t i = 1000000; i>0;i--){
            //Delay(1);
            stepperR.runSpeed();
            stepperL.runSpeed();
            
        //}
        //digitalWrite(OUTPUTPIN, HIGH);
        //Delay(10);
        //digitalWrite(OUTPUTPIN, LOW);
        //Delay(10);
		//Delay(1);

//stepper.runSpeed();
	}
	
	
}
