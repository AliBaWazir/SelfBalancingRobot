/* Copyright 2014 The MathWorks, Inc. */
#ifndef __MW_SEMAPHORE__H__
#define __MW_SEMAPHORE__H__

typedef struct _mw_semaphore_t {
	uint32_t semaphoreInternalData[2];
	osSemaphoreId semaphoreId;
	osSemaphoreDef_t semaphoreDef;
} mw_semaphore_t;

/* Create and Initialize a Semaphore object used for managing resources. */
int32_t  mw_osSemaphoreCreate 	(mw_semaphore_t * semaphore_def, int32_t count);
/* Wait until a Semaphore token becomes available. */
int32_t  mw_osSemaphoreWait 	(mw_semaphore_t * semaphore_def, uint32_t millisec);
/* Wait until a Semaphore token becomes available. */
int32_t  mw_osSemaphoreWaitEver	(mw_semaphore_t * semaphore_def);
/* Release a Semaphore token. */
osStatus mw_osSemaphoreRelease  (mw_semaphore_t * semaphore_def);
/* Delete a Semaphore that was created by osSemaphoreCreate. */
osStatus mw_osSemaphoreDelete 	(mw_semaphore_t * semaphore_def);

#endif /* __MW_SEMAPHORE__H__ */