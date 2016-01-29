/* Wrapper header for STM32F4-Discovery 
 * 
 * Copyright 2013 The MathWorks, Inc.
 */
#include "stm32f4discovery_wrapper.h"

void stm32f4xx_init_board(void)
{
	/* Enable double word stack alignment */
	SCB->CCR |= SCB_CCR_STKALIGN_Msk;

	#if MW_MULTI_TASKING_MODE == 1
    /* Set the interrupt priority at highest */
    NVIC_SetPriority(SVCall_IRQn, 0x0);
    #endif
  
    #if defined(MW_ENABLE_CLOCK_TO_I2S) && (MW_ENABLE_CLOCK_TO_I2S == 1)
    MW_I2S_Clock_config((uint32_t)MW_I2S_CLOCK_PLLN, (uint32_t)MW_I2S_CLOCK_PLLR);
    #endif
}
