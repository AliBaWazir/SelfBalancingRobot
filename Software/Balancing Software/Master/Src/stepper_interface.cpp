#include "stepper_interface.h"
#include "AccelStepper.h"
#include "defines.h"

AccelStepper stepperR(AccelStepper::DRIVER, STEPPER_RIGHT_STEP_PIN, STEPPER_RIGHT_DIR_PIN);
AccelStepper stepperL(AccelStepper::DRIVER, STEPPER_LEFT_STEP_PIN, STEPPER_LEFT_DIR_PIN);
void initSteppers(void){
    
    
    //enable steppers
    pinMode(PORTD+11, OUTPUT);
    digitalWrite(PORTD+11, HIGH);
    
    setSteppingMode(MICROSTEPS_8);

    pinMode(STEPPER_RIGHT_DIR_PIN, OUTPUT);
    pinMode(STEPPER_RIGHT_STEP_PIN, OUTPUT);
    pinMode(STEPPER_LEFT_DIR_PIN, OUTPUT);
    pinMode(STEPPER_LEFT_STEP_PIN, OUTPUT);
    
    



    
}
void setStepperMaxSpeed(uint16_t maxSpeed){
    stepperR.setMaxSpeed(maxSpeed);
    stepperL.setMaxSpeed(maxSpeed);
}
void setStepperAccel(uint16_t accel){
    stepperR.setAcceleration(MAXACCEL);
    stepperL.setAcceleration(MAXACCEL);
}
void setStepperSpeed(uint16_t speed){
    stepperR.setSpeed(speed);
    stepperL.setSpeed(speed);
}

void runSpeed(){
    stepperR.runSpeed();
    stepperL.runSpeed();
}

void setSteppingMode(uint8_t mode){
    
    pinMode(STEPPER_RIGHT_M0_PIN, OUTPUT);
    pinMode(STEPPER_RIGHT_M1_PIN, OUTPUT);
    pinMode(STEPPER_LEFT_M0_PIN, OUTPUT);
    pinMode(STEPPER_LEFT_M1_PIN, OUTPUT);
    
    
    digitalWrite(STEPPER_RIGHT_M0_PIN, LOW);
    digitalWrite(STEPPER_RIGHT_M1_PIN, LOW);
    digitalWrite(STEPPER_LEFT_M0_PIN, LOW);
    digitalWrite(STEPPER_LEFT_M1_PIN, LOW);
    
    switch(mode)
        {
        case MICROSTEPS_1: 
            digitalWrite(STEPPER_RIGHT_M0_PIN, LOW);
            digitalWrite(STEPPER_RIGHT_M1_PIN, LOW);
            digitalWrite(STEPPER_LEFT_M0_PIN, LOW);
            digitalWrite(STEPPER_LEFT_M1_PIN, LOW);
        break;
        case MICROSTEPS_2: 
            digitalWrite(STEPPER_RIGHT_M0_PIN, HIGH);
            digitalWrite(STEPPER_RIGHT_M1_PIN, LOW);
            digitalWrite(STEPPER_LEFT_M0_PIN, HIGH);
            digitalWrite(STEPPER_LEFT_M1_PIN, LOW);
        break;
        case MICROSTEPS_4:
            pinMode(STEPPER_RIGHT_M0_PIN, INPUT);
            digitalWrite(STEPPER_RIGHT_M1_PIN, LOW);
            pinMode(STEPPER_LEFT_M0_PIN, INPUT);
            digitalWrite(STEPPER_LEFT_M1_PIN, LOW);
        break;
        case MICROSTEPS_8: 
            digitalWrite(STEPPER_RIGHT_M0_PIN, LOW);
            digitalWrite(STEPPER_RIGHT_M1_PIN, HIGH);
            digitalWrite(STEPPER_LEFT_M0_PIN, LOW);
            digitalWrite(STEPPER_LEFT_M1_PIN, HIGH);
        break;
        case MICROSTEPS_16: 
            digitalWrite(STEPPER_RIGHT_M0_PIN, HIGH);
            digitalWrite(STEPPER_RIGHT_M1_PIN, HIGH);
            digitalWrite(STEPPER_LEFT_M0_PIN, HIGH);
            digitalWrite(STEPPER_LEFT_M1_PIN, HIGH);
        break;
        case MICROSTEPS_32:
            pinMode(STEPPER_RIGHT_M0_PIN, INPUT);
            digitalWrite(STEPPER_RIGHT_M1_PIN, HIGH);
            pinMode(STEPPER_LEFT_M0_PIN, INPUT);
            digitalWrite(STEPPER_LEFT_M1_PIN, HIGH);
        break;
    
    }
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

