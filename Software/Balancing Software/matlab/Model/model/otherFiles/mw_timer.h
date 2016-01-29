/* Copyright 2014 The MathWorks, Inc. */
#ifndef __MW_TIMER__H__
#define __MW_TIMER__H__

typedef struct _mw_timer_t {
	osTimerId timerId;
	osTimerDef_t timerDef;
	uint32_t timerInternalData[5];
} mw_timer_t;

/* Create timer */
int32_t mw_osTimerCreate (mw_timer_t * timer_def, os_timer_type type, void (*func_ptr)(void *), void *argument);
/* Start timer */
osStatus mw_osTimerStart (mw_timer_t * timer_def, uint32_t millisec);
/* Stop timer */
osStatus mw_osTimerStop (mw_timer_t * timer_def);
/* Delete timer */
osStatus mw_osTimerDelete (mw_timer_t * timer_def);

#endif /* __MW_TIMER__H__ */