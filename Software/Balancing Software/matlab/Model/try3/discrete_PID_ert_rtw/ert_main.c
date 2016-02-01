/*
 * File: ert_main.c
 *
 * Code generated for Simulink model 'discrete_PID'.
 *
 * Model version                  : 1.8
 * Simulink Coder version         : 8.8 (R2015a) 09-Feb-2015
 * C/C++ source code generated on : Mon Feb 01 06:07:24 2016
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "discrete_PID.h"
#include "rtwtypes.h"

volatile int IsrOverrun = 0;
static boolean_T OverrunFlag = 0;
void rt_OneStep(void)
{
  /* Check for overrun. Protect OverrunFlag against preemption */
  if (OverrunFlag++) {
    IsrOverrun = 1;
    OverrunFlag--;
    return;
  }

  __enable_irq();
  discrete_PID_step();

  /* Get model outputs here */
  __disable_irq();
  OverrunFlag--;
}

//int main(void)
//{
//  volatile boolean_T runModel = 1;
//  float modelBaseRate = 0.01;
//  float systemClock = 168;

//#ifndef USE_RTX

//  __disable_irq();

//#endif

//  ;
//  stm32f4xx_init_board();
//  SystemCoreClockUpdate();
//  rtmSetErrorStatus(discrete_PID_M, 0);
//  discrete_PID_initialize();
//  ARMCM_SysTick_Config(modelBaseRate);
//  runModel =
//    rtmGetErrorStatus(discrete_PID_M) == (NULL);
//  __enable_irq();
//  __enable_irq();
//  while (runModel) {
//    runModel =
//      rtmGetErrorStatus(discrete_PID_M) == (NULL);
//  }

//  /* Disable rt_OneStep() here */

//  /* Terminate model */
//  discrete_PID_terminate();
//  __disable_irq();
//  return 0;
//}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
