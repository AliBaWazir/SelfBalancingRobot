/*
 * File: inverted_pendulum.c
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

#include "inverted_pendulum.h"

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

/* Block parameters (auto storage) */
P_inverted_pendulum_T inverted_pendulum_P = {
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
B_inverted_pendulum_T inverted_pendulum_B;

/* Continuous states */
X_inverted_pendulum_T inverted_pendulum_X;

/* External outputs (root outports fed by signals with auto storage) */
ExtY_inverted_pendulum_T inverted_pendulum_Y;

/* Real-time model */
RT_MODEL_inverted_pendulum_T inverted_pendulum_M_;
RT_MODEL_inverted_pendulum_T *const inverted_pendulum_M = &inverted_pendulum_M_;

/* private model entry point functions */
extern void inverted_pendulum_derivatives(void);
static void rate_monotonic_scheduler(void);

/*
 * Set which subrates need to run this base step (base rate always runs).
 * This function must be called prior to calling the model step function
 * in order to "remember" which rates need to run this base step.  The
 * buffering of events allows for overlapping preemption.
 */
void inverted_pendulum_SetEventsForThisBaseStep(boolean_T *eventFlags)
{
  /* Task runs when its counter is zero, computed via rtmStepTask macro */
  eventFlags[2] = ((boolean_T)rtmStepTask(inverted_pendulum_M, 2));
}

/*
 *   This function updates active task flag for each subrate
 * and rate transition flags for tasks that exchange data.
 * The function assumes rate-monotonic multitasking scheduler.
 * The function must be called at model base rate so that
 * the generated code self-manages all its subrates and rate
 * transition flags.
 */
static void rate_monotonic_scheduler(void)
{
  /* To ensure a deterministic data transfer between two rates,
   * data is transferred at the priority of a fast task and the frequency
   * of the slow task.  The following flags indicate when the data transfer
   * happens.  That is, a rate interaction flag is set true when both rates
   * will run, and false otherwise.
   */

  /* tid 0 shares data with slower tid rate: 2 */
  inverted_pendulum_M->Timing.RateInteraction.TID0_2 =
    (inverted_pendulum_M->Timing.TaskCounters.TID[2] == 0);

  /* Compute which subrates run during the next base time step.  Subrates
   * are an integer multiple of the base rate counter.  Therefore, the subtask
   * counter is reset when it reaches its limit (zero means run).
   */
  (inverted_pendulum_M->Timing.TaskCounters.TID[2])++;
  if ((inverted_pendulum_M->Timing.TaskCounters.TID[2]) > 9) {/* Sample time: [1.0s, 0.0s] */
    inverted_pendulum_M->Timing.TaskCounters.TID[2] = 0;
  }
}

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
  inverted_pendulum_derivatives();

  /* f(:,2) = feval(odefile, t + hA(1), y + f*hB(:,1), args(:)(*)); */
  hB[0] = h * rt_ODE3_B[0][0];
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0]);
  }

  rtsiSetT(si, t + h*rt_ODE3_A[0]);
  rtsiSetdX(si, f1);
  inverted_pendulum_step0();
  inverted_pendulum_derivatives();

  /* f(:,3) = feval(odefile, t + hA(2), y + f*hB(:,2), args(:)(*)); */
  for (i = 0; i <= 1; i++) {
    hB[i] = h * rt_ODE3_B[1][i];
  }

  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0] + f1[i]*hB[1]);
  }

  rtsiSetT(si, t + h*rt_ODE3_A[1]);
  rtsiSetdX(si, f2);
  inverted_pendulum_step0();
  inverted_pendulum_derivatives();

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

/* Model step function for TID0 */
void inverted_pendulum_step0(void)     /* Sample time: [0.0s, 0.0s] */
{
  if (rtmIsMajorTimeStep(inverted_pendulum_M)) {
    /* set solver stop time */
    rtsiSetSolverStopTime(&inverted_pendulum_M->solverInfo,
                          ((inverted_pendulum_M->Timing.clockTick0+1)*
      inverted_pendulum_M->Timing.stepSize0));

    {                                  /* Sample time: [0.0s, 0.0s] */
      rate_monotonic_scheduler();
    }
  }                                    /* end MajorTimeStep */

  /* Update absolute time of base rate at minor time step */
  if (rtmIsMinorTimeStep(inverted_pendulum_M)) {
    inverted_pendulum_M->Timing.t[0] = rtsiGetT(&inverted_pendulum_M->solverInfo);
  }

  /* StateSpace: '<Root>/Angle Controller' incorporates:
   *  Inport: '<Root>/angle'
   */
  F = 0.0;
  F += inverted_pendulum_P.AngleController_C[0] *
    inverted_pendulum_X.AngleController_CSTATE[0];
  F += inverted_pendulum_P.AngleController_C[1] *
    inverted_pendulum_X.AngleController_CSTATE[1];
  F += inverted_pendulum_P.AngleController_D * Theta;

  /* ZeroOrderHold: '<Root>/Zero-Order Hold' */
  if (rtmIsMajorTimeStep(inverted_pendulum_M) &&
      inverted_pendulum_M->Timing.RateInteraction.TID0_2) {
    inverted_pendulum_B.ZeroOrderHold = F;
  }

  /* End of ZeroOrderHold: '<Root>/Zero-Order Hold' */
  if (rtmIsMajorTimeStep(inverted_pendulum_M)) {
    rt_ertODEUpdateContinuousStates(&inverted_pendulum_M->solverInfo);

    /* Update absolute time */
    /* The "clockTick0" counts the number of times the code of this task has
     * been executed. The absolute time is the multiplication of "clockTick0"
     * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
     * overflow during the application lifespan selected.
     */
    ++inverted_pendulum_M->Timing.clockTick0;
    inverted_pendulum_M->Timing.t[0] = rtsiGetSolverStopTime
      (&inverted_pendulum_M->solverInfo);

    /* Update absolute time */
    /* The "clockTick1" counts the number of times the code of this task has
     * been executed. The resolution of this integer timer is 0.1, which is the step size
     * of the task. Size of "clockTick1" ensures timer will not overflow during the
     * application lifespan selected.
     */
    inverted_pendulum_M->Timing.clockTick1++;
  }                                    /* end MajorTimeStep */
}

/* Derivatives for root system: '<Root>' */
void inverted_pendulum_derivatives(void)
{
  XDot_inverted_pendulum_T *_rtXdot;
  _rtXdot = ((XDot_inverted_pendulum_T *) inverted_pendulum_M->ModelData.derivs);

  /* Derivatives for StateSpace: '<Root>/Angle Controller' incorporates:
   *  Derivatives for Inport: '<Root>/angle'
   */
  _rtXdot->AngleController_CSTATE[0] = 0.0;
  _rtXdot->AngleController_CSTATE[1] = 0.0;
  _rtXdot->AngleController_CSTATE[0] += inverted_pendulum_P.AngleController_A[0]
    * inverted_pendulum_X.AngleController_CSTATE[0];
  _rtXdot->AngleController_CSTATE[0] += inverted_pendulum_P.AngleController_A[1]
    * inverted_pendulum_X.AngleController_CSTATE[1];
  _rtXdot->AngleController_CSTATE[1] += inverted_pendulum_P.AngleController_A[2]
    * inverted_pendulum_X.AngleController_CSTATE[0];
  _rtXdot->AngleController_CSTATE[1] += inverted_pendulum_P.AngleController_A[3]
    * inverted_pendulum_X.AngleController_CSTATE[1];
  _rtXdot->AngleController_CSTATE[0] += inverted_pendulum_P.AngleController_B[0]
    * Theta;
  _rtXdot->AngleController_CSTATE[1] += inverted_pendulum_P.AngleController_B[1]
    * Theta;
}

/* Model step function for TID2 */
void inverted_pendulum_step2(void)     /* Sample time: [1.0s, 0.0s] */
{
  /* Outport: '<Root>/accel' */
  inverted_pendulum_Y.accel = inverted_pendulum_B.ZeroOrderHold;
}

/* Model initialize function */
void inverted_pendulum_initialize(void)
{
  /* Registration code */

  /* initialize real-time model */
  (void) memset((void *)inverted_pendulum_M, 0,
                sizeof(RT_MODEL_inverted_pendulum_T));

  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&inverted_pendulum_M->solverInfo,
                          &inverted_pendulum_M->Timing.simTimeStep);
    rtsiSetTPtr(&inverted_pendulum_M->solverInfo, &rtmGetTPtr
                (inverted_pendulum_M));
    rtsiSetStepSizePtr(&inverted_pendulum_M->solverInfo,
                       &inverted_pendulum_M->Timing.stepSize0);
    rtsiSetdXPtr(&inverted_pendulum_M->solverInfo,
                 &inverted_pendulum_M->ModelData.derivs);
    rtsiSetContStatesPtr(&inverted_pendulum_M->solverInfo, (real_T **)
                         &inverted_pendulum_M->ModelData.contStates);
    rtsiSetNumContStatesPtr(&inverted_pendulum_M->solverInfo,
      &inverted_pendulum_M->Sizes.numContStates);
    rtsiSetErrorStatusPtr(&inverted_pendulum_M->solverInfo, (&rtmGetErrorStatus
      (inverted_pendulum_M)));
    rtsiSetRTModelPtr(&inverted_pendulum_M->solverInfo, inverted_pendulum_M);
  }

  rtsiSetSimTimeStep(&inverted_pendulum_M->solverInfo, MAJOR_TIME_STEP);
  inverted_pendulum_M->ModelData.intgData.y =
    inverted_pendulum_M->ModelData.odeY;
  inverted_pendulum_M->ModelData.intgData.f[0] =
    inverted_pendulum_M->ModelData.odeF[0];
  inverted_pendulum_M->ModelData.intgData.f[1] =
    inverted_pendulum_M->ModelData.odeF[1];
  inverted_pendulum_M->ModelData.intgData.f[2] =
    inverted_pendulum_M->ModelData.odeF[2];
  inverted_pendulum_M->ModelData.contStates = ((X_inverted_pendulum_T *)
    &inverted_pendulum_X);
  rtsiSetSolverData(&inverted_pendulum_M->solverInfo, (void *)
                    &inverted_pendulum_M->ModelData.intgData);
  rtsiSetSolverName(&inverted_pendulum_M->solverInfo,"ode3");
  rtmSetTPtr(inverted_pendulum_M, &inverted_pendulum_M->Timing.tArray[0]);
  inverted_pendulum_M->Timing.stepSize0 = 0.1;

  /* block I/O */
  (void) memset(((void *) &inverted_pendulum_B), 0,
                sizeof(B_inverted_pendulum_T));

  /* states (continuous) */
  {
    (void) memset((void *)&inverted_pendulum_X, 0,
                  sizeof(X_inverted_pendulum_T));
  }

  /* external outputs */
  inverted_pendulum_Y.accel = 0.0;

  /* InitializeConditions for StateSpace: '<Root>/Angle Controller' */
  inverted_pendulum_X.AngleController_CSTATE[0] =
    inverted_pendulum_P.AngleController_X0;
  inverted_pendulum_X.AngleController_CSTATE[1] =
    inverted_pendulum_P.AngleController_X0;
}

/* Model terminate function */
void inverted_pendulum_terminate(void)
{
  /* (no terminate code required) */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
