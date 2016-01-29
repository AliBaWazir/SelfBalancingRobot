/* GNU GCC startup file for STM32F4xx*/

/* Copyright 2013-2014 The MathWorks, Inc. */
#include "startup_stm32f4xx.h"

#ifdef USE_RTX
	#define __STACK_SIZE       512U      /*!< Stack size (in Words)           */
#else
	#define __STACK_SIZE       2048U      /*!< Stack size (in Words)           */
#endif
/* Define stack: 8Kb base + extra */
__attribute__ ((section(".co_stack")))
unsigned long pulStack[__STACK_SIZE + (((STACK_SIZE>>2) + 7) & ~7)];

void _start(void);
static void Default_Handler(void);

/* ISR vector table */
__attribute__ ((section(".vectors")))
void (* const g_pfnVectors[])(void) =
{
  (void (*)(void))((unsigned long)pulStack + sizeof(pulStack)),
  Reset_Handler,
  NMI_Handler,
  HardFault_Handler,
  MemManage_Handler,
  BusFault_Handler,
  UsageFault_Handler,
  0,  /* Reserved */
  0,
  0,
  0,                   
  SVC_Handler,               
  DebugMon_Handler,          
  0, /* Reserved */                       
  PendSV_Handler,
  SysTick_Handler,
  
  /* Peripheral exceptions */
  WWDG_IRQHandler,           
  PVD_IRQHandler,            
  TAMP_STAMP_IRQHandler,     
  RTC_WKUP_IRQHandler,       
  FLASH_IRQHandler,          
  RCC_IRQHandler  ,          
  EXTI0_IRQHandler,          
  EXTI1_IRQHandler,          
  EXTI2_IRQHandler,          
  EXTI3_IRQHandler,          
  EXTI4_IRQHandler,          
  DMA1_Stream0_IRQHandler,   
  DMA1_Stream1_IRQHandler,   
  DMA1_Stream2_IRQHandler,   
  DMA1_Stream3_IRQHandler,   
  DMA1_Stream4_IRQHandler,   
  DMA1_Stream5_IRQHandler,   
  DMA1_Stream6_IRQHandler,   
  ADC_IRQHandler,            
  CAN1_TX_IRQHandler,        
  CAN1_RX0_IRQHandler,       
  CAN1_RX1_IRQHandler,       
  CAN1_SCE_IRQHandler,       
  EXTI9_5_IRQHandler,        
  TIM1_BRK_TIM9_IRQHandler,  
  TIM1_UP_TIM10_IRQHandler,  
  TIM1_TRG_COM_TIM11_IRQHandler,
  TIM1_CC_IRQHandler,        
  TIM2_IRQHandler,           
  TIM3_IRQHandler,           
  TIM4_IRQHandler,           
  I2C1_EV_IRQHandler,        
  I2C1_ER_IRQHandler,        
  I2C2_EV_IRQHandler,        
  I2C2_ER_IRQHandler,        
  SPI1_IRQHandler,           
  SPI2_IRQHandler,           
  USART1_IRQHandler,         
  USART2_IRQHandler,         
  USART3_IRQHandler,         
  EXTI15_10_IRQHandler,      
  RTC_Alarm_IRQHandler,      
  OTG_FS_WKUP_IRQHandler,    
  TIM8_BRK_TIM12_IRQHandler, 
  TIM8_UP_TIM13_IRQHandler,  
  TIM8_TRG_COM_TIM14_IRQHandler,
  TIM8_CC_IRQHandler,        
  DMA1_Stream7_IRQHandler,   
  FSMC_IRQHandler,           
  SDIO_IRQHandler,           
  TIM5_IRQHandler,           
  SPI3_IRQHandler,           
  UART4_IRQHandler,          
  UART5_IRQHandler,          
  TIM6_DAC_IRQHandler,       
  TIM7_IRQHandler,           
  DMA2_Stream0_IRQHandler,   
  DMA2_Stream1_IRQHandler,   
  DMA2_Stream2_IRQHandler,   
  DMA2_Stream3_IRQHandler,   
  DMA2_Stream4_IRQHandler,   
  ETH_IRQHandler,            
  ETH_WKUP_IRQHandler,       
  CAN2_TX_IRQHandler,        
  CAN2_RX0_IRQHandler,       
  CAN2_RX1_IRQHandler,       
  CAN2_SCE_IRQHandler,       
  OTG_FS_IRQHandler,         
  DMA2_Stream5_IRQHandler,   
  DMA2_Stream6_IRQHandler,   
  DMA2_Stream7_IRQHandler,   
  USART6_IRQHandler,         
  I2C3_EV_IRQHandler,        
  I2C3_ER_IRQHandler,        
  OTG_HS_EP1_OUT_IRQHandler, 
  OTG_HS_EP1_IN_IRQHandler,  
  OTG_HS_WKUP_IRQHandler,    
  OTG_HS_IRQHandler,         
  DCMI_IRQHandler,           
  CRYP_IRQHandler,           
  HASH_RNG_IRQHandler,       
  FPU_IRQHandler 
};


/* Startup routine */
void Default_ResetHandler(void)
{
  /* Initialize data and bss */
  unsigned long *pulSrc, *pulDest;

  /* Copy the data segment initializers from flash to SRAM */
  pulSrc = &_sidata;

  for(pulDest = &_sdata; pulDest < &_edata; ) {
      *(pulDest++) = *(pulSrc++);
  }
  
  /* Clear .bss */
  __asm("  ldr     r0, =_sbss\n"
        "  ldr     r1, =_ebss\n"
        "  mov     r2, #0\n"
        "  .thumb_func\n"
        "zero_loop:\n"
        "    cmp     r0, r1\n"
        "    it      lt\n"
        "    strlt   r2, [r0], #4\n"
        "    blt     zero_loop");

#ifndef __NO_SYSTEM_INIT
  /* Call CMSIS system initialization code */
  SystemInit();
#endif
  
  /* Branch to main */
#ifndef __START
#define __START main
#endif

  __START();
}

/* Default interrupt handler */
static void Default_Handler(void)
{
	/* Go into an infinite loop. */
	while (1)
	{
	}
}

/* EOF */
