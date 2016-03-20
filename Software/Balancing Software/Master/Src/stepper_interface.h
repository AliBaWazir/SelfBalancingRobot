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
EXTERNC void setStepperMaxSpeed(float);
EXTERNC void setStepperAccel(float);
EXTERNC void setStepperSpeed(float);
EXTERNC void runSpeed(void);
EXTERNC void dWrite(uint8_t, uint8_t);
EXTERNC void stepperMoveTo(int32_t);
EXTERNC void stepperRun(void);
EXTERNC int32_t stepperCurrentPosition(void);
EXTERNC void stepperMove(int32_t);
EXTERNC void setStepperCurrentPosition(int32_t);
EXTERNC void stepperDisable(void);
EXTERNC void stepperEnable(void);
