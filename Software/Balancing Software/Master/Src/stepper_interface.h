// stepper_interface.h
// Jonathan Lukas Goldnau-Vogt
// Used to run Arduino libraries on STM32F4xx

#include <stdbool.h>
#include <stdint.h>
#include <algorithm>
#include <math.h>
//#include "tm_stm32f4_delay.h"
//#include "tm_stm32f4_gpio.h"
extern "C"{
void stepperProgram();
void initSteppers();
}
