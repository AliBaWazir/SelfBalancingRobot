/*
 * File: ert_main.c
 *
 * Code generated for Simulink model 'rct_pendulum'.
 *
 * Model version                  : 1.55
 * Simulink Coder version         : 8.8 (R2015a) 09-Feb-2015
 * C/C++ source code generated on : Tue Jan 19 21:12:32 2016
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex
 * Code generation objective: Execution efficiency
 * Validation result: Not run
 */

#include "rct_pendulum.h"
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
  rct_pendulum_step();

  /* Get model outputs here */
  __disable_irq();
  OverrunFlag--;
}

int main(void)
{
  volatile boolean_T runModel = 1;
  float modelBaseRate = 0.01;
  float systemClock = 168;

#ifndef USE_RTX

  __disable_irq();

#endif

  ;
  stm32f4xx_init_board();
  SystemCoreClockUpdate();
  rtmSetErrorStatus(rct_pendulum_M, 0);
  rct_pendulum_initialize();
  ARMCM_SysTick_Config(modelBaseRate);
  runModel =
    (rtmGetErrorStatus(rct_pendulum_M) == (NULL)) && !rtmGetStopRequested
    (rct_pendulum_M);
  __enable_irq();
  __enable_irq();
  while (runModel) {
    runModel =
      (rtmGetErrorStatus(rct_pendulum_M) == (NULL)) && !rtmGetStopRequested
      (rct_pendulum_M);
  }

  /* Disable rt_OneStep() here */

  /* Terminate model */
  rct_pendulum_terminate();
  __disable_irq();
  return 0;
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
