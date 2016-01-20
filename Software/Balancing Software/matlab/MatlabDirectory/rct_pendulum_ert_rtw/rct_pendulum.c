/*
 * File: rct_pendulum.c
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

/* Private macros used by the generated code to access rtModel */
#ifndef rtmIsMajorTimeStep
# define rtmIsMajorTimeStep(rtm)       (((rtm)->Timing.simTimeStep) == MAJOR_TIME_STEP)
#endif

#ifndef rtmIsMinorTimeStep
# define rtmIsMinorTimeStep(rtm)       (((rtm)->Timing.simTimeStep) == MINOR_TIME_STEP)
#endif

#ifndef rtmGetTPtr
# define rtmGetTPtr(rtm)               ((rtm)->Timing.t)
#endif

#ifndef rtmSetTPtr
# define rtmSetTPtr(rtm, val)          ((rtm)->Timing.t = (val))
#endif

/* Exported block signals */
real_T F;                              /* '<Root>/Sum1' */

/* Block parameters (auto storage) */
P_rct_pendulum_T rct_pendulum_P = {
  /*  Computed Parameter: AngleController_A
   * Referenced by: '<Root>/Angle Controller'
   */
  { 15.4898634340509, 26.4858841705556, -3.0704117154182, -136.900629246653 },

  /*  Computed Parameter: AngleController_B
   * Referenced by: '<Root>/Angle Controller'
   */
  { 124.240427443766, -262.107188254329 },

  /*  Computed Parameter: AngleController_C
   * Referenced by: '<Root>/Angle Controller'
   */
  { -88.8990856237622, -699.794525555653 },
  -1656.81755505379,                   /* Computed Parameter: AngleController_D
                                        * Referenced by: '<Root>/Angle Controller'
                                        */
  0.0                                  /* Expression: 0
                                        * Referenced by: '<Root>/Angle Controller'
                                        */
};

/* Block signals (auto storage) */
B_rct_pendulum_T rct_pendulum_B;

/* Continuous states */
X_rct_pendulum_T rct_pendulum_X;

/* External outputs (root outports fed by signals with auto storage) */
ExtY_rct_pendulum_T rct_pendulum_Y;

/* Real-time model */
RT_MODEL_rct_pendulum_T rct_pendulum_M_;
RT_MODEL_rct_pendulum_T *const rct_pendulum_M = &rct_pendulum_M_;

/* private model entry point functions */
extern void rct_pendulum_derivatives(void);

/*
 * This function updates continuous states using the ODE3 fixed-step
 * solver algorithm
 */
static void rt_ertODEUpdateContinuousStates(RTWSolverInfo *si )
{
  /* Solver Matrices */
  static const real_T rt_ODE3_A[3] = {
    1.0/2.0, 3.0/4.0, 1.0
  };

  static const real_T rt_ODE3_B[3][3] = {
    { 1.0/2.0, 0.0, 0.0 },

    { 0.0, 3.0/4.0, 0.0 },

    { 2.0/9.0, 1.0/3.0, 4.0/9.0 }
  };

  time_T t = rtsiGetT(si);
  time_T tnew = rtsiGetSolverStopTime(si);
  time_T h = rtsiGetStepSize(si);
  real_T *x = rtsiGetContStates(si);
  ODE3_IntgData *id = (ODE3_IntgData *)rtsiGetSolverData(si);
  real_T *y = id->y;
  real_T *f0 = id->f[0];
  real_T *f1 = id->f[1];
  real_T *f2 = id->f[2];
  real_T hB[3];
  int_T i;
  int_T nXc = 2;
  rtsiSetSimTimeStep(si,MINOR_TIME_STEP);

  /* Save the state values at time t in y, we'll use x as ynew. */
  (void) memcpy(y, x,
                (uint_T)nXc*sizeof(real_T));

  /* Assumes that rtsiSetT and ModelOutputs are up-to-date */
  /* f0 = f(t,y) */
  rtsiSetdX(si, f0);
  rct_pendulum_derivatives();

  /* f(:,2) = feval(odefile, t + hA(1), y + f*hB(:,1), args(:)(*)); */
  hB[0] = h * rt_ODE3_B[0][0];
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0]);
  }

  rtsiSetT(si, t + h*rt_ODE3_A[0]);
  rtsiSetdX(si, f1);
  rct_pendulum_step();
  rct_pendulum_derivatives();

  /* f(:,3) = feval(odefile, t + hA(2), y + f*hB(:,2), args(:)(*)); */
  for (i = 0; i <= 1; i++) {
    hB[i] = h * rt_ODE3_B[1][i];
  }

  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0] + f1[i]*hB[1]);
  }

  rtsiSetT(si, t + h*rt_ODE3_A[1]);
  rtsiSetdX(si, f2);
  rct_pendulum_step();
  rct_pendulum_derivatives();

  /* tnew = t + hA(3);
     ynew = y + f*hB(:,3); */
  for (i = 0; i <= 2; i++) {
    hB[i] = h * rt_ODE3_B[2][i];
  }

  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0] + f1[i]*hB[1] + f2[i]*hB[2]);
  }

  rtsiSetT(si, tnew);
  rtsiSetSimTimeStep(si,MAJOR_TIME_STEP);
}

/* Model step function */
void rct_pendulum_step(void)
{
  if (rtmIsMajorTimeStep(rct_pendulum_M)) {
    /* set solver stop time */
    rtsiSetSolverStopTime(&rct_pendulum_M->solverInfo,
                          ((rct_pendulum_M->Timing.clockTick0+1)*
      rct_pendulum_M->Timing.stepSize0));
  }                                    /* end MajorTimeStep */

  /* Update absolute time of base rate at minor time step */
  if (rtmIsMinorTimeStep(rct_pendulum_M)) {
    rct_pendulum_M->Timing.t[0] = rtsiGetT(&rct_pendulum_M->solverInfo);
  }

  /* StateSpace: '<Root>/Angle Controller' incorporates:
   *  Inport: '<Root>/angle'
   */
  rct_pendulum_B.AngleController = 0.0;
  rct_pendulum_B.AngleController += rct_pendulum_P.AngleController_C[0] *
    rct_pendulum_X.AngleController_CSTATE[0];
  rct_pendulum_B.AngleController += rct_pendulum_P.AngleController_C[1] *
    rct_pendulum_X.AngleController_CSTATE[1];
  rct_pendulum_B.AngleController += rct_pendulum_P.AngleController_D * Theta;

  /* Sum: '<Root>/Sum1' */
  F = rct_pendulum_B.AngleController;

  /* Outport: '<Root>/accel' */
  rct_pendulum_Y.accel = F;
  if (rtmIsMajorTimeStep(rct_pendulum_M)) {
    rt_ertODEUpdateContinuousStates(&rct_pendulum_M->solverInfo);

    /* Update absolute time for base rate */
    /* The "clockTick0" counts the number of times the code of this task has
     * been executed. The absolute time is the multiplication of "clockTick0"
     * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
     * overflow during the application lifespan selected.
     */
    ++rct_pendulum_M->Timing.clockTick0;
    rct_pendulum_M->Timing.t[0] = rtsiGetSolverStopTime
      (&rct_pendulum_M->solverInfo);

    {
      /* Update absolute timer for sample time: [0.01s, 0.0s] */
      /* The "clockTick1" counts the number of times the code of this task has
       * been executed. The resolution of this integer timer is 0.01, which is the step size
       * of the task. Size of "clockTick1" ensures timer will not overflow during the
       * application lifespan selected.
       */
      rct_pendulum_M->Timing.clockTick1++;
    }
  }                                    /* end MajorTimeStep */
}

/* Derivatives for root system: '<Root>' */
void rct_pendulum_derivatives(void)
{
  XDot_rct_pendulum_T *_rtXdot;
  _rtXdot = ((XDot_rct_pendulum_T *) rct_pendulum_M->ModelData.derivs);

  /* Derivatives for StateSpace: '<Root>/Angle Controller' incorporates:
   *  Derivatives for Inport: '<Root>/angle'
   */
  _rtXdot->AngleController_CSTATE[0] = 0.0;
  _rtXdot->AngleController_CSTATE[1] = 0.0;
  _rtXdot->AngleController_CSTATE[0] += rct_pendulum_P.AngleController_A[0] *
    rct_pendulum_X.AngleController_CSTATE[0];
  _rtXdot->AngleController_CSTATE[0] += rct_pendulum_P.AngleController_A[1] *
    rct_pendulum_X.AngleController_CSTATE[1];
  _rtXdot->AngleController_CSTATE[1] += rct_pendulum_P.AngleController_A[2] *
    rct_pendulum_X.AngleController_CSTATE[0];
  _rtXdot->AngleController_CSTATE[1] += rct_pendulum_P.AngleController_A[3] *
    rct_pendulum_X.AngleController_CSTATE[1];
  _rtXdot->AngleController_CSTATE[0] += rct_pendulum_P.AngleController_B[0] *
    Theta;
  _rtXdot->AngleController_CSTATE[1] += rct_pendulum_P.AngleController_B[1] *
    Theta;
}

/* Model initialize function */
void rct_pendulum_initialize(void)
{
  /* Registration code */

  /* initialize real-time model */
  (void) memset((void *)rct_pendulum_M, 0,
                sizeof(RT_MODEL_rct_pendulum_T));

  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&rct_pendulum_M->solverInfo,
                          &rct_pendulum_M->Timing.simTimeStep);
    rtsiSetTPtr(&rct_pendulum_M->solverInfo, &rtmGetTPtr(rct_pendulum_M));
    rtsiSetStepSizePtr(&rct_pendulum_M->solverInfo,
                       &rct_pendulum_M->Timing.stepSize0);
    rtsiSetdXPtr(&rct_pendulum_M->solverInfo, &rct_pendulum_M->ModelData.derivs);
    rtsiSetContStatesPtr(&rct_pendulum_M->solverInfo, (real_T **)
                         &rct_pendulum_M->ModelData.contStates);
    rtsiSetNumContStatesPtr(&rct_pendulum_M->solverInfo,
      &rct_pendulum_M->Sizes.numContStates);
    rtsiSetErrorStatusPtr(&rct_pendulum_M->solverInfo, (&rtmGetErrorStatus
      (rct_pendulum_M)));
    rtsiSetRTModelPtr(&rct_pendulum_M->solverInfo, rct_pendulum_M);
  }

  rtsiSetSimTimeStep(&rct_pendulum_M->solverInfo, MAJOR_TIME_STEP);
  rct_pendulum_M->ModelData.intgData.y = rct_pendulum_M->ModelData.odeY;
  rct_pendulum_M->ModelData.intgData.f[0] = rct_pendulum_M->ModelData.odeF[0];
  rct_pendulum_M->ModelData.intgData.f[1] = rct_pendulum_M->ModelData.odeF[1];
  rct_pendulum_M->ModelData.intgData.f[2] = rct_pendulum_M->ModelData.odeF[2];
  rct_pendulum_M->ModelData.contStates = ((X_rct_pendulum_T *) &rct_pendulum_X);
  rtsiSetSolverData(&rct_pendulum_M->solverInfo, (void *)
                    &rct_pendulum_M->ModelData.intgData);
  rtsiSetSolverName(&rct_pendulum_M->solverInfo,"ode3");
  rtmSetTPtr(rct_pendulum_M, &rct_pendulum_M->Timing.tArray[0]);
  rct_pendulum_M->Timing.stepSize0 = 0.01;

  /* block I/O */
  (void) memset(((void *) &rct_pendulum_B), 0,
                sizeof(B_rct_pendulum_T));

  /* exported global signals */
  F = 0.0;

  /* states (continuous) */
  {
    (void) memset((void *)&rct_pendulum_X, 0,
                  sizeof(X_rct_pendulum_T));
  }

  /* external outputs */
  rct_pendulum_Y.accel = 0.0;

  /* InitializeConditions for StateSpace: '<Root>/Angle Controller' */
  rct_pendulum_X.AngleController_CSTATE[0] = rct_pendulum_P.AngleController_X0;
  rct_pendulum_X.AngleController_CSTATE[1] = rct_pendulum_P.AngleController_X0;
}

/* Model terminate function */
void rct_pendulum_terminate(void)
{
  /* (no terminate code required) */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
