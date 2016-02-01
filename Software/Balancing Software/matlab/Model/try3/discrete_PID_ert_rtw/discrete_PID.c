/*
 * File: discrete_PID.c
 *
 * Code generated for Simulink model 'discrete_PID'.
 *
 * Model version                  : 1.2
 * Simulink Coder version         : 8.8 (R2015a) 09-Feb-2015
 * C/C++ source code generated on : Mon Feb 01 03:38:39 2016
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "discrete_PID.h"

/* Block parameters (auto storage) */
P_discrete_PID_T discrete_PID_P = {
  0.01,                                /* Computed Parameter: Integrator_gainval
                                        * Referenced by: '<S1>/Integrator'
                                        */
  0.0,                                 /* Expression: InitialConditionForIntegrator
                                        * Referenced by: '<S1>/Integrator'
                                        */
  0.01,                                /* Computed Parameter: Filter_gainval
                                        * Referenced by: '<S1>/Filter'
                                        */
  0.0,                                 /* Expression: InitialConditionForFilter
                                        * Referenced by: '<S1>/Filter'
                                        */
  0.01,                                /* Computed Parameter: Integrator_gainval_c
                                        * Referenced by: '<S2>/Integrator'
                                        */
  0.0,                                 /* Expression: InitialConditionForIntegrator
                                        * Referenced by: '<S2>/Integrator'
                                        */
  0.01,                                /* Computed Parameter: Filter_gainval_h
                                        * Referenced by: '<S2>/Filter'
                                        */
  0.0                                  /* Expression: InitialConditionForFilter
                                        * Referenced by: '<S2>/Filter'
                                        */
};

/* Block states (auto storage) */
DW_discrete_PID_T discrete_PID_DW;

/* Real-time model */
RT_MODEL_discrete_PID_T discrete_PID_M_;
RT_MODEL_discrete_PID_T *const discrete_PID_M = &discrete_PID_M_;

/* Model step function */
void discrete_PID_step(void)
{
  real_T rtb_NOut;
  real_T rtb_NOut_j;

  /* Product: '<S1>/NOut' incorporates:
   *  DiscreteIntegrator: '<S1>/Filter'
   *  Inport: '<Root>/In1'
   *  Inport: '<Root>/In4'
   *  Product: '<S1>/DOut'
   *  Sum: '<S1>/SumD'
   */
  rtb_NOut = (controllerInputAngle * controllerAngleD -
              discrete_PID_DW.Filter_DSTATE) * 0.0;

  /* Product: '<S2>/NOut' incorporates:
   *  DiscreteIntegrator: '<S2>/Filter'
   *  Inport: '<Root>/In5'
   *  Inport: '<Root>/In8'
   *  Product: '<S2>/DOut'
   *  Sum: '<S2>/SumD'
   */
  rtb_NOut_j = (controllerInputPosition * controllerPositionD -
                discrete_PID_DW.Filter_DSTATE_l) * 0.0;

  /* Sum: '<Root>/Sum' incorporates:
   *  DiscreteIntegrator: '<S1>/Integrator'
   *  DiscreteIntegrator: '<S2>/Integrator'
   *  Inport: '<Root>/In1'
   *  Inport: '<Root>/In2'
   *  Inport: '<Root>/In5'
   *  Inport: '<Root>/In6'
   *  Product: '<S1>/POut'
   *  Product: '<S2>/POut'
   *  Sum: '<S1>/Sum'
   *  Sum: '<S2>/Sum'
   */
  controllerOutput = ((controllerInputAngle * controllerAngleP +
                       discrete_PID_DW.Integrator_DSTATE) + rtb_NOut) +
    ((controllerInputPosition * controllerPositionP +
      discrete_PID_DW.Integrator_DSTATE_h) + rtb_NOut_j);

  /* Update for DiscreteIntegrator: '<S1>/Integrator' incorporates:
   *  Inport: '<Root>/In1'
   *  Inport: '<Root>/In3'
   *  Product: '<S1>/IOut'
   */
  discrete_PID_DW.Integrator_DSTATE += controllerInputAngle * controllerAngleI *
    discrete_PID_P.Integrator_gainval;

  /* Update for DiscreteIntegrator: '<S1>/Filter' */
  discrete_PID_DW.Filter_DSTATE += discrete_PID_P.Filter_gainval * rtb_NOut;

  /* Update for DiscreteIntegrator: '<S2>/Integrator' incorporates:
   *  Inport: '<Root>/In5'
   *  Inport: '<Root>/In7'
   *  Product: '<S2>/IOut'
   */
  discrete_PID_DW.Integrator_DSTATE_h += controllerInputPosition *
    controllerPositionI * discrete_PID_P.Integrator_gainval_c;

  /* Update for DiscreteIntegrator: '<S2>/Filter' */
  discrete_PID_DW.Filter_DSTATE_l += discrete_PID_P.Filter_gainval_h *
    rtb_NOut_j;
}

/* Model initialize function */
void discrete_PID_initialize(void)
{
  /* Registration code */

  /* initialize error status */
  rtmSetErrorStatus(discrete_PID_M, (NULL));

  /* states (dwork) */
  (void) memset((void *)&discrete_PID_DW, 0,
                sizeof(DW_discrete_PID_T));

  /* InitializeConditions for DiscreteIntegrator: '<S1>/Integrator' */
  discrete_PID_DW.Integrator_DSTATE = discrete_PID_P.Integrator_IC;

  /* InitializeConditions for DiscreteIntegrator: '<S1>/Filter' */
  discrete_PID_DW.Filter_DSTATE = discrete_PID_P.Filter_IC;

  /* InitializeConditions for DiscreteIntegrator: '<S2>/Integrator' */
  discrete_PID_DW.Integrator_DSTATE_h = discrete_PID_P.Integrator_IC_b;

  /* InitializeConditions for DiscreteIntegrator: '<S2>/Filter' */
  discrete_PID_DW.Filter_DSTATE_l = discrete_PID_P.Filter_IC_b;
}

/* Model terminate function */
void discrete_PID_terminate(void)
{
  /* (no terminate code required) */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
