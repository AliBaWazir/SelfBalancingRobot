#include "stm32f4xx_hal.h"
#include "stepper_interface.h"
#include "arm_math.h"

#include "tm_stm32_delay.h"
#include "stm32fxxx_hal.h"
#ifndef PCBVERSION
#include "tm_stm32_disco.h"
#endif
#include "inv_mpu.h"
#include "inv_mpu_dmp_motion_driver.h"
#include "invensense.h"
#include "invensense_adv.h"
#include "eMPL_outputs.h"
#include "mltypes.h"
#include "mpu.h"
#include "log.h"
#include "packet.h"
#include "defines.h"

void setup(void);
void application_main(int32_t);
extern void discrete_PID_initialize(void);
extern void rt_OneStep(void);
void userLoop(void);
void initTimerInterrupt(void);
void initLED(void);
extern void init_pid(void);
extern void application_pid(int32_t);
extern void setupLog(void);
extern void parseCommands(void);
extern void logNewLine(void);
void calibrateZero(int32_t);
void setCalibrateFlag(uint8_t);
int32_t getZeroAngle(void);
void setState(uint8_t);

