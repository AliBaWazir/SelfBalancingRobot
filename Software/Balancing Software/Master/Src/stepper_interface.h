// stepper_interface.h
// Jonathan Lukas Goldnau-Vogt
// Used to run Arduino libraries on STM32F4xx

#ifdef __cplusplus
#define EXTERNC extern "C"
#else
#define EXTERNC
#endif

//#include "tm_stm32f4_delay.h"
//#include "tm_stm32f4_gpio.h"

EXTERNC void stepperProgram();
EXTERNC void initSteppers();

