/* Copyright 2014 The MathWorks, Inc. */
#ifndef __MW_THREAD__H__
#define __MW_THREAD__H__

typedef struct _mw_thread_t {
	osThreadId threadId;
	osThreadDef_t threadDef;
} mw_thread_t;

/* Create a thread and add it to Active Threads and set it to state READY. */
int32_t mw_osThreadCreate(mw_thread_t * thread_def, void (*pthread)(void *), int32_t priority, int32_t stacksize, void *argument);
/* Return the thread ID of the current running thread.  */
osThreadId mw_osThreadGetId 		(void);
/* Terminate execution of a thread and remove it from Active Threads. */
osStatus   mw_osThreadTerminate 	(mw_thread_t * thread_def);
/* Change priority of an active thread. */
osStatus   mw_osThreadSetPriority 	(mw_thread_t * thread_def, osPriority priority);
/* Get current priority of an active thread. */
osPriority mw_osThreadGetPriority 	(mw_thread_t * thread_def);
/* Pass control to next thread that is in state READY. */
osStatus   mw_osThreadYield 		(void);
/* RK Posix compatibility to be discussed: Exit from thread */
void   mw_osThreadExit 	(void * value_ptr);
/* RK Posix compatibility to be discussed: Join */
int32_t   mw_osThreadJoin 	(mw_thread_t thread_def, void ** value_ptr);

#endif /* __MW_THREAD__H__ */