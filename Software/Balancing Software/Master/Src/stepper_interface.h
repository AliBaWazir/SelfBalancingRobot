// stepper_interface.h
// Jonathan Lukas Goldnau-Vogt
// Used to run Arduino libraries on STM32F4xx
#include "stdint.h"
#ifdef __cplusplus
#define EXTERNC extern "C"
#else
#define EXTERNC
#endif

//#include "tm_stm32f4_delay.h"
//#include "tm_stm32f4_gpio.h"

EXTERNC void stepperProgram(void);
EXTERNC void initSteppers(void);
EXTERNC void setSteppingMode(uint8_t);
EXTERNC void setStepperMaxSpeed(uint16_t maxSpeed);
EXTERNC void setStepperAccel(uint16_t accel);
EXTERNC void setStepperSpeed(uint16_t speed);
EXTERNC void runSpeed(void);

