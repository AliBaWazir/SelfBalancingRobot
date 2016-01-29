/*
 * File: inverted_pendulum_private.h
 *
 * Code generated for Simulink model 'inverted_pendulum'.
 *
 * Model version                  : 1.48
 * Simulink Coder version         : 8.8 (R2015a) 09-Feb-2015
 * C/C++ source code generated on : Thu Jan 28 20:19:09 2016
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef RTW_HEADER_inverted_pendulum_private_h_
#define RTW_HEADER_inverted_pendulum_private_h_
#include "rtwtypes.h"

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

/* Imported (extern) block signals */
extern real_T F;                       /* '<Root>/Angle Controller' */
extern real_T Theta;                   /* '<Root>/angle' */

/* private model entry point functions */
extern void inverted_pendulum_derivatives(void);

#endif                                 /* RTW_HEADER_inverted_pendulum_private_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
