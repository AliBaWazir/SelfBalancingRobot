/*
 * File: rtwdemo_roll.c
 *
 * Code generated for Simulink model 'rtwdemo_roll'.
 *
 * Model version                  : 1.134
 * Simulink Coder version         : 8.8 (R2015a) 09-Feb-2015
 * C/C++ source code generated on : Thu Jan 28 20:09:43 2016
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Generic->32-bit Embedded Processor
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. Traceability
 *    3. Safety precaution
 *    4. RAM efficiency
 * Validation result: Not run
 */

#include "rtwdemo_roll.h"
#include "rtwdemo_roll_private.h"

/* Block states (auto storage) */
DW_rtwdemo_roll_T rtwdemo_roll_DW;

/* External inputs (root inport signals with auto storage) */
ExtU_rtwdemo_roll_T rtwdemo_roll_U;

/* External outputs (root outports fed by signals with auto storage) */
ExtY_rtwdemo_roll_T rtwdemo_roll_Y;

/* Real-time model */
RT_MODEL_rtwdemo_roll_T rtwdemo_roll_M_;
RT_MODEL_rtwdemo_roll_T *const rtwdemo_roll_M = &rtwdemo_roll_M_;

/* Model step function */
void rtwdemo_roll_step(void)
{
  boolean_T rtb_NotEngaged_f;
  real32_T rtb_FixPtUnitDelay1;

  /* Outputs for Atomic SubSystem: '<Root>/RollAngleReference' */
  /* UnitDelay: '<S7>/FixPt Unit Delay1' */
  rtb_FixPtUnitDelay1 = rtwdemo_roll_DW.FixPtUnitDelay1_DSTATE;

  /* Switch: '<S7>/Enable' incorporates:
   *  Inport: '<Root>/AP_Eng'
   *  Logic: '<S3>/NotEngaged'
   */
  if (!rtwdemo_roll_U.AP_Eng) {
    /* Switch: '<S3>/RefSwitch' incorporates:
     *  Constant: '<S3>/LoThr'
     *  Constant: '<S3>/UpThr'
     *  Constant: '<S3>/Zero'
     *  Inport: '<Root>/Phi'
     *  Logic: '<S3>/Or'
     *  RelationalOperator: '<S3>/RefThreshold1'
     *  RelationalOperator: '<S3>/RefThreshold2'
     */
    if ((rtwdemo_roll_U.Phi >= 6.0F) || (rtwdemo_roll_U.Phi <= -6.0F)) {
      rtwdemo_roll_DW.FixPtUnitDelay1_DSTATE = rtwdemo_roll_U.Phi;
    } else {
      rtwdemo_roll_DW.FixPtUnitDelay1_DSTATE = 0.0F;
    }

    /* End of Switch: '<S3>/RefSwitch' */
  }

  /* End of Switch: '<S7>/Enable' */
  /* End of Outputs for SubSystem: '<Root>/RollAngleReference' */

  /* Switch: '<Root>/ModeSwitch' incorporates:
   *  Abs: '<S3>/Abs'
   *  Constant: '<S3>/Three'
   *  Gain: '<S2>/DispGain'
   *  Inport: '<Root>/HDG_Mode'
   *  Inport: '<Root>/HDG_Ref'
   *  Inport: '<Root>/Psi'
   *  Inport: '<Root>/TAS'
   *  Inport: '<Root>/Turn_Knob'
   *  Product: '<S2>/Product'
   *  RelationalOperator: '<S3>/TKThreshold'
   *  Sum: '<S2>/Sum'
   *  Switch: '<S3>/TKSwitch'
   */
  if (rtwdemo_roll_U.HDG_Mode) {
    /* Outputs for Atomic SubSystem: '<Root>/HeadingMode' */
    rtb_FixPtUnitDelay1 = (rtwdemo_roll_U.HDG_Ref - rtwdemo_roll_U.Psi) * 0.015F
      * rtwdemo_roll_U.TAS;

    /* End of Outputs for SubSystem: '<Root>/HeadingMode' */
  } else {
    /* Outputs for Atomic SubSystem: '<Root>/RollAngleReference' */
    if (!((real32_T)fabs(rtwdemo_roll_U.Turn_Knob) < 3.0F)) {
      rtb_FixPtUnitDelay1 = rtwdemo_roll_U.Turn_Knob;
    }

    /* End of Outputs for SubSystem: '<Root>/RollAngleReference' */
  }

  /* End of Switch: '<Root>/ModeSwitch' */

  /* Outputs for Atomic SubSystem: '<Root>/BasicRollMode' */
  /* Logic: '<S1>/NotEngaged' incorporates:
   *  Inport: '<Root>/AP_Eng'
   */
  rtb_NotEngaged_f = !rtwdemo_roll_U.AP_Eng;

  /* DiscreteIntegrator: '<S1>/Integrator' */
  if (rtb_NotEngaged_f || (rtwdemo_roll_DW.Integrator_PrevResetState != 0)) {
    rtwdemo_roll_DW.Integrator_DSTATE = 0.0F;
  }

  if (rtwdemo_roll_DW.Integrator_DSTATE >= 5.0F) {
    rtwdemo_roll_DW.Integrator_DSTATE = 5.0F;
  } else {
    if (rtwdemo_roll_DW.Integrator_DSTATE <= -5.0F) {
      rtwdemo_roll_DW.Integrator_DSTATE = -5.0F;
    }
  }

  /* Saturate: '<S1>/DispLimit' */
  if (rtb_FixPtUnitDelay1 > 30.0F) {
    rtb_FixPtUnitDelay1 = 30.0F;
  } else {
    if (rtb_FixPtUnitDelay1 < -30.0F) {
      rtb_FixPtUnitDelay1 = -30.0F;
    }
  }

  /* Gain: '<S1>/DispGain' incorporates:
   *  Inport: '<Root>/Phi'
   *  Saturate: '<S1>/DispLimit'
   *  Sum: '<S1>/Sum'
   */
  rtb_FixPtUnitDelay1 = (rtb_FixPtUnitDelay1 - rtwdemo_roll_U.Phi) * 0.75F;

  /* Saturate: '<S1>/RateLimit' */
  if (rtb_FixPtUnitDelay1 > 6.0F) {
    rtb_FixPtUnitDelay1 = 6.0F;
  } else {
    if (rtb_FixPtUnitDelay1 < -6.0F) {
      rtb_FixPtUnitDelay1 = -6.0F;
    }
  }

  /* Sum: '<S1>/Sum1' incorporates:
   *  Inport: '<Root>/P'
   *  Saturate: '<S1>/RateLimit'
   */
  rtb_FixPtUnitDelay1 -= rtwdemo_roll_U.P;

  /* Sum: '<S1>/Sum2' incorporates:
   *  DiscreteIntegrator: '<S1>/Integrator'
   *  Gain: '<S1>/RateGain'
   */
  rtwdemo_roll_Y.Ail_Cmd = 2.0F * rtb_FixPtUnitDelay1 +
    rtwdemo_roll_DW.Integrator_DSTATE;

  /* Update for DiscreteIntegrator: '<S1>/Integrator' incorporates:
   *  Gain: '<S1>/IntGain'
   */
  rtwdemo_roll_DW.Integrator_DSTATE += 0.5F * rtb_FixPtUnitDelay1 * 0.025F;
  if (rtwdemo_roll_DW.Integrator_DSTATE >= 5.0F) {
    rtwdemo_roll_DW.Integrator_DSTATE = 5.0F;
  } else {
    if (rtwdemo_roll_DW.Integrator_DSTATE <= -5.0F) {
      rtwdemo_roll_DW.Integrator_DSTATE = -5.0F;
    }
  }

  rtwdemo_roll_DW.Integrator_PrevResetState = (int8_T)rtb_NotEngaged_f;

  /* End of Update for DiscreteIntegrator: '<S1>/Integrator' */
  /* End of Outputs for SubSystem: '<Root>/BasicRollMode' */

  /* Switch: '<Root>/EngSwitch' incorporates:
   *  Inport: '<Root>/AP_Eng'
   */
  if (rtwdemo_roll_U.AP_Eng) {
    /* Outputs for Atomic SubSystem: '<Root>/BasicRollMode' */
    /* Saturate: '<S1>/CmdLimit' */
    if (rtwdemo_roll_Y.Ail_Cmd > 15.0F) {
      /* Sum: '<S1>/Sum2' incorporates:
       *  Outport: '<Root>/Ail_Cmd'
       */
      rtwdemo_roll_Y.Ail_Cmd = 15.0F;
    } else {
      if (rtwdemo_roll_Y.Ail_Cmd < -15.0F) {
        /* Sum: '<S1>/Sum2' incorporates:
         *  Outport: '<Root>/Ail_Cmd'
         */
        rtwdemo_roll_Y.Ail_Cmd = -15.0F;
      }
    }

    /* End of Saturate: '<S1>/CmdLimit' */
    /* End of Outputs for SubSystem: '<Root>/BasicRollMode' */
  } else {
    /* Sum: '<S1>/Sum2' incorporates:
     *  Constant: '<Root>/Zero'
     *  Outport: '<Root>/Ail_Cmd'
     */
    rtwdemo_roll_Y.Ail_Cmd = 0.0F;
  }

  /* End of Switch: '<Root>/EngSwitch' */
}

/* Model initialize function */
void rtwdemo_roll_initialize(void)
{
  /* (no initialization code required) */
}

/* Model terminate function */
void rtwdemo_roll_terminate(void)
{
  /* (no terminate code required) */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
