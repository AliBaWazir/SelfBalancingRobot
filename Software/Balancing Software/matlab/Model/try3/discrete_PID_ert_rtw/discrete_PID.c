/*
 * File: discrete_PID.c
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

/* Block parameters (auto storage) */
P_discrete_PID_T discrete_PID_P = {
  -100.0,                              /* Mask Parameter: Position_LowerSaturationLimit
                                        * Referenced by: '<S2>/Saturate'
                                        */
  -100.0,                              /* Mask Parameter: Angle_LowerSaturationLimit
                                        * Referenced by: '<S1>/Saturate'
                                        */
  100.0,                               /* Mask Parameter: Position_UpperSaturationLimit
                                        * Referenced by: '<S2>/Saturate'
                                        */
  100.0,                               /* Mask Parameter: Angle_UpperSaturationLimit
                                        * Referenced by: '<S1>/Saturate'
                                        */
  0.01,                                /* Computed Parameter: Filter_gainval
                                        * Referenced by: '<S2>/Filter'
                                        */
  0.0,                                 /* Expression: InitialConditionForFilter
                                        * Referenced by: '<S2>/Filter'
                                        */
  0.01,                                /* Computed Parameter: Integrator_gainval
                                        * Referenced by: '<S2>/Integrator'
                                        */
  0.0,                                 /* Expression: InitialConditionForIntegrator
                                        * Referenced by: '<S2>/Integrator'
                                        */
  0.01,                                /* Computed Parameter: Integrator_gainval_n
                                        * Referenced by: '<S1>/Integrator'
                                        */
  0.0,                                 /* Expression: InitialConditionForIntegrator
                                        * Referenced by: '<S1>/Integrator'
                                        */
  0.01,                                /* Computed Parameter: Filter_gainval_h
                                        * Referenced by: '<S1>/Filter'
                                        */
  0.0                                  /* Expression: InitialConditionForFilter
                                        * Referenced by: '<S1>/Filter'
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
  real_T rtb_Sum1;
  real_T rtb_NOut;
  real_T rtb_NOut_b;
  real_T u0;

  /* Product: '<S2>/NOut' incorporates:
   *  DiscreteIntegrator: '<S2>/Filter'
   *  Inport: '<Root>/In5'
   *  Inport: '<Root>/In8'
   *  Product: '<S2>/DOut'
   *  Sum: '<S2>/SumD'
   */
  rtb_NOut = (controllerInputPosition * controllerPositionD -
              discrete_PID_DW.Filter_DSTATE) * 0.0;

  /* Sum: '<S2>/Sum' incorporates:
   *  DiscreteIntegrator: '<S2>/Integrator'
   *  Inport: '<Root>/In5'
   *  Inport: '<Root>/In6'
   *  Product: '<S2>/POut'
   */
  u0 = (controllerInputPosition * controllerPositionP +
        discrete_PID_DW.Integrator_DSTATE) + rtb_NOut;

  /* Saturate: '<S2>/Saturate' */
  if (u0 > discrete_PID_P.Position_UpperSaturationLimit) {
    u0 = discrete_PID_P.Position_UpperSaturationLimit;
  } else {
    if (u0 < discrete_PID_P.Position_LowerSaturationLimit) {
      u0 = discrete_PID_P.Position_LowerSaturationLimit;
    }
  }

  /* Sum: '<Root>/Sum1' incorporates:
   *  Inport: '<Root>/In1'
   *  Inport: '<Root>/In9'
   *  Saturate: '<S2>/Saturate'
   */
  rtb_Sum1 = (controllerInputAngle - angleSetpoint) - u0;

  /* Product: '<S1>/NOut' incorporates:
   *  DiscreteIntegrator: '<S1>/Filter'
   *  Inport: '<Root>/In4'
   *  Product: '<S1>/DOut'
   *  Sum: '<S1>/SumD'
   */
  rtb_NOut_b = (rtb_Sum1 * controllerAngleD - discrete_PID_DW.Filter_DSTATE_f) *
    0.0;

  /* Sum: '<S1>/Sum' incorporates:
   *  DiscreteIntegrator: '<S1>/Integrator'
   *  Inport: '<Root>/In2'
   *  Product: '<S1>/POut'
   */
  u0 = (rtb_Sum1 * controllerAngleP + discrete_PID_DW.Integrator_DSTATE_l) +
    rtb_NOut_b;

  /* Saturate: '<S1>/Saturate' */
  if (u0 > discrete_PID_P.Angle_UpperSaturationLimit) {
    controllerOutput = discrete_PID_P.Angle_UpperSaturationLimit;
  } else if (u0 < discrete_PID_P.Angle_LowerSaturationLimit) {
    controllerOutput = discrete_PID_P.Angle_LowerSaturationLimit;
  } else {
    controllerOutput = u0;
  }

  /* End of Saturate: '<S1>/Saturate' */

  /* Update for DiscreteIntegrator: '<S2>/Filter' */
  discrete_PID_DW.Filter_DSTATE += discrete_PID_P.Filter_gainval * rtb_NOut;

  /* Update for DiscreteIntegrator: '<S2>/Integrator' incorporates:
   *  Inport: '<Root>/In5'
   *  Inport: '<Root>/In7'
   *  Product: '<S2>/IOut'
   */
  discrete_PID_DW.Integrator_DSTATE += controllerInputPosition *
    controllerPositionI * discrete_PID_P.Integrator_gainval;

  /* Update for DiscreteIntegrator: '<S1>/Integrator' incorporates:
   *  Inport: '<Root>/In3'
   *  Product: '<S1>/IOut'
   */
  discrete_PID_DW.Integrator_DSTATE_l += rtb_Sum1 * controllerAngleI *
    discrete_PID_P.Integrator_gainval_n;

  /* Update for DiscreteIntegrator: '<S1>/Filter' */
  discrete_PID_DW.Filter_DSTATE_f += discrete_PID_P.Filter_gainval_h *
    rtb_NOut_b;
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

  /* InitializeConditions for DiscreteIntegrator: '<S2>/Filter' */
  discrete_PID_DW.Filter_DSTATE = discrete_PID_P.Filter_IC;

  /* InitializeConditions for DiscreteIntegrator: '<S2>/Integrator' */
  discrete_PID_DW.Integrator_DSTATE = discrete_PID_P.Integrator_IC;

  /* InitializeConditions for DiscreteIntegrator: '<S1>/Integrator' */
  discrete_PID_DW.Integrator_DSTATE_l = discrete_PID_P.Integrator_IC_f;

  /* InitializeConditions for DiscreteIntegrator: '<S1>/Filter' */
  discrete_PID_DW.Filter_DSTATE_f = discrete_PID_P.Filter_IC_a;
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
