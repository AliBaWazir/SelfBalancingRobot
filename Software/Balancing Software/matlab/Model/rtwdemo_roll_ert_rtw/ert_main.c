/*
 * File: ert_main.c
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

#include <stddef.h>
#include <stdio.h>                     /* This ert_main.c example uses printf/fflush */
#include "rtwdemo_roll.h"              /* Model's header file */
#include "rtwtypes.h"

/*
 * Associating rt_OneStep with a real-time clock or interrupt service routine
 * is what makes the generated code "real-time".  The function rt_OneStep is
 * always associated with the base rate of the model.  Subrates are managed
 * by the base rate from inside the generated code.  Enabling/disabling
 * interrupts and floating point context switches are target specific.  This
 * example code indicates where these should take place relative to executing
 * the generated code step function.  Overrun behavior should be tailored to
 * your application needs.  This example simply sets an error status in the
 * real-time model and returns from rt_OneStep.
 */
void rt_OneStep(void);
void rt_OneStep(void)
{
  static boolean_T OverrunFlag = false;

  /* Disable interrupts here */

  /* Check for overrun */
  if (OverrunFlag) {
    rtmSetErrorStatus(rtwdemo_roll_M, "Overrun");
    return;
  }

  OverrunFlag = true;

  /* Save FPU context here (if necessary) */
  /* Re-enable timer or interrupt here */
  /* Set model inputs here */

  /* Step the model */
  rtwdemo_roll_step();

  /* Get model outputs here */

  /* Indicate task complete */
  OverrunFlag = false;

  /* Disable interrupts here */
  /* Restore FPU context here (if necessary) */
  /* Enable interrupts here */
}

/*
 * The example "main" function illustrates what is required by your
 * application code to initialize, execute, and terminate the generated code.
 * Attaching rt_OneStep to a real-time clock is target specific.  This example
 * illustates how you do this relative to initializing the model.
 */
int_T main(int_T argc, const char *argv[])
{
  /* Unused arguments */
  (void)(argc);
  (void)(argv);

  /* Initialize model */
  rtwdemo_roll_initialize();

  /* Attach rt_OneStep to a timer or interrupt service routine with
   * period 0.025 seconds (the model's base sample time) here.  The
   * call syntax for rt_OneStep is
   *
   *  rt_OneStep();
   */
  printf("Warning: The simulation will run forever. "
         "Generated ERT main won't simulate model step behavior. "
         "To change this behavior select the 'MAT-file logging' option.\n");
  fflush((NULL));
  while (rtmGetErrorStatus(rtwdemo_roll_M) == (NULL)) {
    /*  Perform other application tasks here */
  }

  /* Disable rt_OneStep() here */

  /* Terminate model */
  rtwdemo_roll_terminate();
  return 0;
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
