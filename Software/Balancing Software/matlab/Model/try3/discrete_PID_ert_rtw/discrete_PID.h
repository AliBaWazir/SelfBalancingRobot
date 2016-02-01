/*
 * File: discrete_PID.h
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

#ifndef RTW_HEADER_discrete_PID_h_
#define RTW_HEADER_discrete_PID_h_
#include "rtwtypes.h"
#include <stddef.h>
#include <string.h>
#ifndef discrete_PID_COMMON_INCLUDES_
# define discrete_PID_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"
#endif                                 /* discrete_PID_COMMON_INCLUDES_ */

#include "MW_target_hardware_resources.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
# define rtmGetErrorStatus(rtm)        ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
# define rtmSetErrorStatus(rtm, val)   ((rtm)->errorStatus = (val))
#endif

/* Forward declaration for rtModel */
typedef struct tag_RTM_discrete_PID_T RT_MODEL_discrete_PID_T;

/* Block states (auto storage) for system '<Root>' */
typedef struct {
  real_T Integrator_DSTATE;            /* '<S1>/Integrator' */
  real_T Filter_DSTATE;                /* '<S1>/Filter' */
  real_T Integrator_DSTATE_h;          /* '<S2>/Integrator' */
  real_T Filter_DSTATE_l;              /* '<S2>/Filter' */
} DW_discrete_PID_T;

/* Parameters (auto storage) */
struct P_discrete_PID_T_ {
  real_T Integrator_gainval;           /* Computed Parameter: Integrator_gainval
                                        * Referenced by: '<S1>/Integrator'
                                        */
  real_T Integrator_IC;                /* Expression: InitialConditionForIntegrator
                                        * Referenced by: '<S1>/Integrator'
                                        */
  real_T Filter_gainval;               /* Computed Parameter: Filter_gainval
                                        * Referenced by: '<S1>/Filter'
                                        */
  real_T Filter_IC;                    /* Expression: InitialConditionForFilter
                                        * Referenced by: '<S1>/Filter'
                                        */
  real_T Integrator_gainval_c;         /* Computed Parameter: Integrator_gainval_c
                                        * Referenced by: '<S2>/Integrator'
                                        */
  real_T Integrator_IC_b;              /* Expression: InitialConditionForIntegrator
                                        * Referenced by: '<S2>/Integrator'
                                        */
  real_T Filter_gainval_h;             /* Computed Parameter: Filter_gainval_h
                                        * Referenced by: '<S2>/Filter'
                                        */
  real_T Filter_IC_b;                  /* Expression: InitialConditionForFilter
                                        * Referenced by: '<S2>/Filter'
                                        */
};

/* Parameters (auto storage) */
typedef struct P_discrete_PID_T_ P_discrete_PID_T;

/* Real-time Model Data Structure */
struct tag_RTM_discrete_PID_T {
  const char_T * volatile errorStatus;
};

/* Imported (extern) block signals */
extern real_T controllerOutput;        /* '<Root>/Sum' */
extern real_T controllerInputAngle;    /* '<Root>/In1' */
extern real_T controllerAngleP;        /* '<Root>/In2' */
extern real_T controllerAngleI;        /* '<Root>/In3' */
extern real_T controllerAngleD;        /* '<Root>/In4' */
extern real_T controllerInputPosition; /* '<Root>/In5' */
extern real_T controllerPositionP;     /* '<Root>/In6' */
extern real_T controllerPositionI;     /* '<Root>/In7' */
extern real_T controllerPositionD;     /* '<Root>/In8' */

/* Block parameters (auto storage) */
extern P_discrete_PID_T discrete_PID_P;

/* Block states (auto storage) */
extern DW_discrete_PID_T discrete_PID_DW;

/* Model entry point functions */
extern void discrete_PID_initialize(void);
extern void discrete_PID_step(void);
extern void discrete_PID_terminate(void);

/* Real-time Model object */
extern RT_MODEL_discrete_PID_T *const discrete_PID_M;

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
 * '<Root>' : 'discrete_PID'
 * '<S1>'   : 'discrete_PID/Angle'
 * '<S2>'   : 'discrete_PID/Position'
 */
#endif                                 /* RTW_HEADER_discrete_PID_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
