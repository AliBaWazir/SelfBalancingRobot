/*
 * File: rct_pendulum.h
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

#ifndef RTW_HEADER_rct_pendulum_h_
#define RTW_HEADER_rct_pendulum_h_
#include "rtwtypes.h"
#include <string.h>
#include <stddef.h>
#ifndef rct_pendulum_COMMON_INCLUDES_
# define rct_pendulum_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"
#endif                                 /* rct_pendulum_COMMON_INCLUDES_ */

#include "MW_target_hardware_resources.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
# define rtmGetErrorStatus(rtm)        ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
# define rtmSetErrorStatus(rtm, val)   ((rtm)->errorStatus = (val))
#endif

#ifndef rtmGetStopRequested
# define rtmGetStopRequested(rtm)      ((rtm)->Timing.stopRequestedFlag)
#endif

#ifndef rtmSetStopRequested
# define rtmSetStopRequested(rtm, val) ((rtm)->Timing.stopRequestedFlag = (val))
#endif

#ifndef rtmGetStopRequestedPtr
# define rtmGetStopRequestedPtr(rtm)   (&((rtm)->Timing.stopRequestedFlag))
#endif

#ifndef rtmGetT
# define rtmGetT(rtm)                  (rtmGetTPtr((rtm))[0])
#endif

/* Forward declaration for rtModel */
typedef struct tag_RTM_rct_pendulum_T RT_MODEL_rct_pendulum_T;

/* Block signals (auto storage) */
typedef struct {
  real_T AngleController;              /* '<Root>/Angle Controller' */
} B_rct_pendulum_T;

/* Continuous states (auto storage) */
typedef struct {
  real_T AngleController_CSTATE[2];    /* '<Root>/Angle Controller' */
} X_rct_pendulum_T;

/* State derivatives (auto storage) */
typedef struct {
  real_T AngleController_CSTATE[2];    /* '<Root>/Angle Controller' */
} XDot_rct_pendulum_T;

/* State disabled  */
typedef struct {
  boolean_T AngleController_CSTATE[2]; /* '<Root>/Angle Controller' */
} XDis_rct_pendulum_T;

#ifndef ODE3_INTG
#define ODE3_INTG

/* ODE3 Integration Data */
typedef struct {
  real_T *y;                           /* output */
  real_T *f[3];                        /* derivatives */
} ODE3_IntgData;

#endif

/* External outputs (root outports fed by signals with auto storage) */
typedef struct {
  real_T accel;                        /* '<Root>/accel' */
} ExtY_rct_pendulum_T;

/* Parameters (auto storage) */
struct P_rct_pendulum_T_ {
  real_T AngleController_A[4];         /* Computed Parameter: AngleController_A
                                        * Referenced by: '<Root>/Angle Controller'
                                        */
  real_T AngleController_B[2];         /* Computed Parameter: AngleController_B
                                        * Referenced by: '<Root>/Angle Controller'
                                        */
  real_T AngleController_C[2];         /* Computed Parameter: AngleController_C
                                        * Referenced by: '<Root>/Angle Controller'
                                        */
  real_T AngleController_D;            /* Computed Parameter: AngleController_D
                                        * Referenced by: '<Root>/Angle Controller'
                                        */
  real_T AngleController_X0;           /* Expression: 0
                                        * Referenced by: '<Root>/Angle Controller'
                                        */
};

/* Parameters (auto storage) */
typedef struct P_rct_pendulum_T_ P_rct_pendulum_T;

/* Real-time Model Data Structure */
struct tag_RTM_rct_pendulum_T {
  const char_T *errorStatus;
  RTWSolverInfo solverInfo;

  /*
   * ModelData:
   * The following substructure contains information regarding
   * the data used in the model.
   */
  struct {
    X_rct_pendulum_T *contStates;
    int_T *periodicContStateIndices;
    real_T *periodicContStateRanges;
    real_T *derivs;
    boolean_T *contStateDisabled;
    boolean_T zCCacheNeedsReset;
    boolean_T derivCacheNeedsReset;
    boolean_T blkStateChange;
    real_T odeY[2];
    real_T odeF[3][2];
    ODE3_IntgData intgData;
  } ModelData;

  /*
   * Sizes:
   * The following substructure contains sizes information
   * for many of the model attributes such as inputs, outputs,
   * dwork, sample times, etc.
   */
  struct {
    int_T numContStates;
    int_T numPeriodicContStates;
    int_T numSampTimes;
  } Sizes;

  /*
   * Timing:
   * The following substructure contains information regarding
   * the timing information for the model.
   */
  struct {
    uint32_T clockTick0;
    time_T stepSize0;
    uint32_T clockTick1;
    SimTimeStep simTimeStep;
    boolean_T stopRequestedFlag;
    time_T *t;
    time_T tArray[2];
  } Timing;
};

/* Imported (extern) block signals */
extern real_T Theta;                   /* '<Root>/angle' */
extern real_T x;                       /* '<Root>/x' */

/* Block parameters (auto storage) */
extern P_rct_pendulum_T rct_pendulum_P;

/* Block signals (auto storage) */
extern B_rct_pendulum_T rct_pendulum_B;

/* Continuous states (auto storage) */
extern X_rct_pendulum_T rct_pendulum_X;

/* External outputs (root outports fed by signals with auto storage) */
extern ExtY_rct_pendulum_T rct_pendulum_Y;

/*
 * Exported Global Signals
 *
 * Note: Exported global signals are block signals with an exported global
 * storage class designation.  Code generation will declare the memory for
 * these signals and export their symbols.
 *
 */
extern real_T F;                       /* '<Root>/Sum1' */

/* Model entry point functions */
extern void rct_pendulum_initialize(void);
extern void rct_pendulum_step(void);
extern void rct_pendulum_terminate(void);

/* Real-time Model object */
extern RT_MODEL_rct_pendulum_T *const rct_pendulum_M;

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Use the MATLAB hilite_system command to trace the generated code back
 * to the model.  For example,
 *
 * hilite_system('<S3>')    - opens system 3
 * hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'rct_pendulum'
 * '<S1>'   : 'rct_pendulum/Disturbance'
 * '<S2>'   : 'rct_pendulum/Plant'
 * '<S3>'   : 'rct_pendulum/Position Controller'
 * '<S4>'   : 'rct_pendulum/Plant/PS-Simulink Converter'
 * '<S5>'   : 'rct_pendulum/Plant/PS-Simulink Converter1'
 * '<S6>'   : 'rct_pendulum/Plant/Simulink-PS Converter'
 * '<S7>'   : 'rct_pendulum/Plant/Simulink-PS Converter1'
 * '<S8>'   : 'rct_pendulum/Plant/Solver Configuration'
 * '<S9>'   : 'rct_pendulum/Plant/PS-Simulink Converter/EVAL_KEY'
 * '<S10>'  : 'rct_pendulum/Plant/PS-Simulink Converter1/EVAL_KEY'
 * '<S11>'  : 'rct_pendulum/Plant/Simulink-PS Converter/EVAL_KEY'
 * '<S12>'  : 'rct_pendulum/Plant/Simulink-PS Converter1/EVAL_KEY'
 * '<S13>'  : 'rct_pendulum/Plant/Solver Configuration/EVAL_KEY'
 */
#endif                                 /* RTW_HEADER_rct_pendulum_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
