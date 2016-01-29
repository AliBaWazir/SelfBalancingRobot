/* Copyright 2013 The MathWorks, Inc. */
#ifndef _STM32F4DISCOVERY_MP45DT02_MEMS_MIC_H_
#define _STM32F4DISCOVERY_MP45DT02_MEMS_MIC_H_

#include <string.h>

#define DMA_SPI2_RX_STREAM              DMA1_Stream3
#define DMA_SPI2_RX_STREAM_IRQn         DMA1_Stream3_IRQn
#define DMA_SPI2_RX_STREAM_IRQHandler   DMA1_Stream3_IRQHandler
#define DMA_RX_COMPLETE_IT_FLAG         DMA_IT_TCIF3

extern uint16_t MW_MIC_Data0[];
extern uint16_t MW_MIC_Data1[];

void mems_mic_gpio_init(void);
void stm32f4_mic_i2s_init(uint32_t sample_freq);
void stm32f4_mic_i2s_interrupt_config(uint8_t priority);
void stm32f4_pdm_filter_init(uint32_t sample_freq,
                             uint32_t low_pass_cutoff_freq,
                             uint32_t high_pass_cutoff_freq,
                             uint8_t input_mic_chls,
                             uint8_t output_mic_chls);

void stm32f4_mems_mic_init(uint32_t sample_freq,
                           uint32_t low_pass_cutoff_freq,
                           uint32_t high_pass_cutoff_freq,
                           uint8_t interrupt_priority,
                           void * mic_output);

#endif /* _STM32F4DISCOVERY_MP45DT02_MEMS_MIC_H_ */