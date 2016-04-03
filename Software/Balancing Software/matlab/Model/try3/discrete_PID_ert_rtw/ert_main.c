/*
 * File: ert_main.c
 *
 * Code generated for Simulink model 'discrete_PID'.
 *
 * Model version                  : 1.8
 * Simulink Coder version         : 8.8 (R2015a) 09-Feb-2015
 * C/C++ source code generated on : Wed Mar 09 05:37:09 2016
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */


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


/*
 * File trailer for generated code.
 *
 * [EOF]
 */
