/*
 * File: rtwdemo_roll.h
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

#ifndef RTW_HEADER_rtwdemo_roll_h_
#define RTW_HEADER_rtwdemo_roll_h_
#include <math.h>
#ifndef rtwdemo_roll_COMMON_INCLUDES_
# define rtwdemo_roll_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                                 /* rtwdemo_roll_COMMON_INCLUDES_ */

#include "rtwdemo_roll_types.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
# define rtmGetErrorStatus(rtm)        ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
# define rtmSetErrorStatus(rtm, val)   ((rtm)->errorStatus = (val))
#endif

/* Block states (auto storage) for system '<Root>' */
typedef struct {
  real32_T FixPtUnitDelay1_DSTATE;     /* '<S7>/FixPt Unit Delay1' */
  real32_T Integrator_DSTATE;          /* '<S1>/Integrator' */
  int8_T Integrator_PrevResetState;    /* '<S1>/Integrator' */
} DW_rtwdemo_roll_T;

/* External inputs (root inport signals with auto storage) */
typedef struct {
  real32_T Phi;                        /* '<Root>/Phi' */
  real32_T Psi;                        /* '<Root>/Psi' */
  real32_T P;                          /* '<Root>/P' */
  real32_T TAS;                        /* '<Root>/TAS' */
  boolean_T AP_Eng;                    /* '<Root>/AP_Eng' */
  boolean_T HDG_Mode;                  /* '<Root>/HDG_Mode' */
  real32_T HDG_Ref;                    /* '<Root>/HDG_Ref' */
  real32_T Turn_Knob;                  /* '<Root>/Turn_Knob' */
} ExtU_rtwdemo_roll_T;

/* External outputs (root outports fed by signals with auto storage) */
typedef struct {
  real32_T Ail_Cmd;                    /* '<Root>/Ail_Cmd' */
} ExtY_rtwdemo_roll_T;

/* Real-time Model Data Structure */
struct tag_RTM_rtwdemo_roll_T {
  const char_T * volatile errorStatus;
};

/* Block states (auto storage) */
extern DW_rtwdemo_roll_T rtwdemo_roll_DW;

/* External inputs (root inport signals with auto storage) */
extern ExtU_rtwdemo_roll_T rtwdemo_roll_U;

/* External outputs (root outports fed by signals with auto storage) */
extern ExtY_rtwdemo_roll_T rtwdemo_roll_Y;

/* Model entry point functions */
extern void rtwdemo_roll_initialize(void);
extern void rtwdemo_roll_step(void);
extern void rtwdemo_roll_terminate(void);

/* Real-time Model object */
extern RT_MODEL_rtwdemo_roll_T *const rtwdemo_roll_M;

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<S7>/FixPt Data Type Duplicate1' : Unused code path elimination
 */

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
 * '<Root>' : 'rtwdemo_roll'
 * '<S1>'   : 'rtwdemo_roll/BasicRollMode'
 * '<S2>'   : 'rtwdemo_roll/HeadingMode'
 * '<S3>'   : 'rtwdemo_roll/RollAngleReference'
 * '<S4>'   : 'rtwdemo_roll/System I//O Specification'
 * '<S5>'   : 'rtwdemo_roll/BasicRollMode/System I//O Specification'
 * '<S6>'   : 'rtwdemo_roll/HeadingMode/System I//O Specification'
 * '<S7>'   : 'rtwdemo_roll/RollAngleReference/LatchPhi'
 * '<S8>'   : 'rtwdemo_roll/RollAngleReference/System I//O Specification'
 */

/*-
 * Requirements for '<Root>': rtwdemo_roll
 */
#endif                                 /* RTW_HEADER_rtwdemo_roll_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
