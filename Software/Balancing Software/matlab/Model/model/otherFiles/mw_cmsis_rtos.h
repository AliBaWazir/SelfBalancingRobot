/* Copyright 2014 The MathWorks, Inc. */
#ifndef __CMSIS_RTOS_INIT_H__
#define __CMSIS_RTOS_INIT_H__

#include <stdio.h>
#include "cmsis_os.h"

#include "mw_thread.h"
#include "mw_semaphore.h"
#include "mw_timer.h"

#include "MW_target_hardware_resources.h"

#ifndef USER_CHECK_STATUS
	#define CHECK_STATUS(status, expStatus, fcn)  		// if (status != expStatus) {printf("Call to %s returned error status (%d).\n", fcn, status); osError(7);}
	#define CHECK_STATUS_NOT(status, errStatus, fcn)	// if (status == errStatus) {printf("Call to %s returned error status (%d).\n", fcn, status); osError(7);}
#else
	void CHECK_STATUS(int32_t status, int32_t expStatus, char_t * str);
	void CHECK_STATUS_NOT(int32_t status, int32_t expStatus, char_t * str);
#endif

void mw_WaitForThisEvent(int sigNo);
void mw_AddBlockForThisEvent(int sigNo);
void mw_AddHandlerForThisEvent(int sigNo, int sigToBlock[], int numSigToBlock, void *sigHandler);
void mw_RestoreDefaultHandlerForThisEvent(int sigNo);

extern void mw_RTOSInit(float baseRatePeriod, int numSubrates);

#endif //__CMSIS_RTOS_INIT_H__
