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
void application_pid(int32_t);
extern void writeLog(char* name,double num);
extern void logNewLine(void);
void resetPID(void);
extern int32_t getZeroAngle(void);
extern void setState(uint8_t);
