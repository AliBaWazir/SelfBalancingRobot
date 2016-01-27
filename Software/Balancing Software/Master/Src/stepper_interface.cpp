#include "stepper_interface.h"
#include "AccelStepper.h"
#include "defines.h"

AccelStepper stepperR(AccelStepper::DRIVER, STEPPER_RIGHT_STEP_PIN, STEPPER_RIGHT_DIR_PIN);
AccelStepper stepperL(AccelStepper::DRIVER, STEPPER_LEFT_STEP_PIN, STEPPER_LEFT_DIR_PIN);
void initSteppers(void){
    
    
    
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
    
    
    digitalWrite(STEPPER_RIGHT_M0_PIN, HIGH);
    digitalWrite(STEPPER_RIGHT_M1_PIN, LOW);
    
    digitalWrite(STEPPER_LEFT_M0_PIN, HIGH);
    digitalWrite(STEPPER_LEFT_M1_PIN, HIGH);
    
    
    pinMode(STEPPER_RIGHT_DIR_PIN, OUTPUT);
    pinMode(STEPPER_RIGHT_STEP_PIN, OUTPUT);
    pinMode(STEPPER_LEFT_DIR_PIN, OUTPUT);
    pinMode(STEPPER_LEFT_STEP_PIN, OUTPUT);

		stepperR.setMaxSpeed(8000.0);
    stepperR.setAcceleration(2000.0);
    
    stepperL.setMaxSpeed(100.0);
    stepperL.setAcceleration(10000.0);
		stepperR.setSpeed(6000);
    stepperL.setSpeed(6000);
    //while(1){
    //    stepperR.runSpeed();
    //    stepperL.runSpeed();
   // }
    
}

void stepperProgram(void){
    
    	
	while (1) {
        
        stepperR.runToNewPosition(0);
        stepperR.runToNewPosition(5000);
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

