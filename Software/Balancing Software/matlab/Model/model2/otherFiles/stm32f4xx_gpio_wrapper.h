/* Wrapper header for STM32F4-Discovery 
 * 
 * Copyright 2013 The MathWorks, Inc.
 */
#ifndef _STM32F4XX_GPIO_WRAPPER_H_
#define _STM32F4XX_GPIO_WRAPPER_H_

#define MW_BitEnableClockToPeripheral(pos, offset) ((uint32_t)(1U << ((pos)+(offset))))

/*
 *******************************************
 * GPIO Wrapper functions
 *******************************************
 */
#define MW_GetGpioPinPosition(GPIO_Pin) ((uint16_t)(1 << (GPIO_Pin)))

extern uint32_t GpioClockEnableBit(uint8_t GPIOx_selected);
extern void MW_GpioInit(uint8_t GPIOx_selected, 
                        uint32_t GPIO_Pin, 
                        GPIOMode_TypeDef GPIO_Mode, 
                        GPIOSpeed_TypeDef GPIO_Speed, 
                        GPIOOType_TypeDef GPIO_OType, 
                        GPIOPuPd_TypeDef GPIO_PuPd);

extern void MW_RCC_AHB1PeriphClockCmd(uint8_t GPIOx_selection, uint8_t enable_or_disable);

extern uint8_t MW_GPIO_ReadInputDataBit(uint8_t GPIOx_selected, uint8_t GPIO_Pin);

extern void MW_GPIO_WriteBit(uint8_t GPIOx_selected, uint16_t GPIO_Pin, uint8_t BitVal);

extern void MW_GPIO_ToggleBits(uint8_t GPIOx_selected, uint16_t GPIO_Pin, uint8_t BitVal);

#endif // _STM32F4XX_GPIO_WRAPPER_H_
