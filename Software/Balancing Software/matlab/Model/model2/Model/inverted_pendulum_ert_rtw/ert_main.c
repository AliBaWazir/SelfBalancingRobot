/*
 * File: ert_main.c
 *
 * Code generated for Simulink model 'inverted_pendulum'.
 *
 * Model version                  : 1.48
 * Simulink Coder version         : 8.8 (R2015a) 09-Feb-2015
 * C/C++ source code generated on : Thu Jan 28 21:02:07 2016
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */
#include "ert_main.h"




volatile int IsrOverrun = 0;
boolean_T isRateRunning[3] = { 0, 0, 0 };

boolean_T need2runFlags[3] = { 0, 0, 0 };

real_T F;                       /* '<Root>/Angle Controller' */
real_T Theta; 

void rt_OneStep(void)
{
  boolean_T eventFlags[3];

  /* Check base rate for overrun */
  if (isRateRunning[0]++) {
    IsrOverrun = 1;
    isRateRunning[0]--;                /* allow future iterations to succeed*/
    return;
  }

  /*
   * For a bare-board target (i.e., no operating system), the rates
   * that execute this base step are buffered locally to allow for
   * overlapping preemption.  The generated code includes function
   * writeCodeInfoFcn() which sets the rates
   * that need to run this time step.  The return values are 1 and 0
   * for true and false, respectively.
   */
  inverted_pendulum_SetEventsForThisBaseStep(eventFlags);
  __enable_irq();
  inverted_pendulum_step0();

  /* Get model outputs here */
  __disable_irq();
  isRateRunning[0]--;
  if (eventFlags[2]) {
    if (need2runFlags[2]++) {
      IsrOverrun = 1;
      need2runFlags[2]--;              /* allow future iterations to succeed*/
      return;
    }
  }

  if (need2runFlags[2]) {
    if (isRateRunning[1]) {
      /* Yield to higher priority*/
      return;
    }

    isRateRunning[2]++;
    __enable_irq();

    /* Step the model for subrate "2" */
    switch (2)
    {
     case 2 :
      inverted_pendulum_step2();

      /* Get model outputs here */
      break;

     default :
      break;
    }

    __disable_irq();
    need2runFlags[2]--;
    isRateRunning[2]--;
  }
}

void main_pend(void)
{
  volatile boolean_T runModel = 1;
  //float modelBaseRate = 0.1;
  //float systemClock = 168;

#ifndef USE_RTX

  __disable_irq();

#endif

  ;
  //stm32f4xx_init_board();
  //SystemCoreClockUpdate();
  rtmSetErrorStatus(inverted_pendulum_M, 0);
  inverted_pendulum_initialize();
  //ARMCM_SysTick_Config(modelBaseRate);
  runModel =
    (rtmGetErrorStatus(inverted_pendulum_M) == (NULL)) && !rtmGetStopRequested
    (inverted_pendulum_M);
  __enable_irq();
  __enable_irq();
  while (runModel) {
    runModel =
      (rtmGetErrorStatus(inverted_pendulum_M) == (NULL)) && !rtmGetStopRequested
      (inverted_pendulum_M);
  }

  /* Disable rt_OneStep() here */

  /* Terminate model */
  inverted_pendulum_terminate();
  __disable_irq();

}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
