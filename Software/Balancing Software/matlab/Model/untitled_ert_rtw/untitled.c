/*
 * File: untitled.c
 *
 * Code generated for Simulink model 'untitled'.
 *
 * Model version                  : 1.0
 * Simulink Coder version         : 8.8 (R2015a) 09-Feb-2015
 * C/C++ source code generated on : Thu Jan 28 20:46:09 2016
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "untitled.h"
#include "untitled_private.h"

/* Block states (auto storage) */
DW_untitled_T untitled_DW;

/* External inputs (root inport signals with auto storage) */
ExtU_untitled_T untitled_U;

/* External outputs (root outports fed by signals with auto storage) */
ExtY_untitled_T untitled_Y;

/* Real-time model */
RT_MODEL_untitled_T untitled_M_;
RT_MODEL_untitled_T *const untitled_M = &untitled_M_;

/* Model step function */
void untitled_step(void)
{
  real_T rtb_Sum;

  /* Sum: '<Root>/Sum' incorporates:
   *  Gain: '<Root>/Gain'
   *  Gain: '<Root>/Gain1'
   *  Inport: '<Root>/u'
   *  UnitDelay: '<Root>/Unit Delay'
   */
  rtb_Sum = untitled_P.Gain_Gain * untitled_U.u + untitled_P.Gain1_Gain *
    untitled_DW.UnitDelay_DSTATE;

  /* Outport: '<Root>/y' */
  untitled_Y.y = rtb_Sum;

  /* Update for UnitDelay: '<Root>/Unit Delay' */
  untitled_DW.UnitDelay_DSTATE = rtb_Sum;
}

/* Model initialize function */
void untitled_initialize(void)
{
  /* Registration code */

  /* initialize error status */
  rtmSetErrorStatus(untitled_M, (NULL));

  /* states (dwork) */
  (void) memset((void *)&untitled_DW, 0,
                sizeof(DW_untitled_T));

  /* external inputs */
  untitled_U.u = 0.0;

  /* external outputs */
  untitled_Y.y = 0.0;

  /* InitializeConditions for UnitDelay: '<Root>/Unit Delay' */
  untitled_DW.UnitDelay_DSTATE = untitled_P.UnitDelay_InitialCondition;
}

/* Model terminate function */
void untitled_terminate(void)
{
  /* (no terminate code required) */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
