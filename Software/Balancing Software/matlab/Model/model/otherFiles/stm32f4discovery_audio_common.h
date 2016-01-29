#ifndef _STM32F4DISCOVERY_AUDIO_COMMON_H_
#define _STM32F4DISCOVERY_AUDIO_COMMON_H_

#define MW_I2SCFGR_CLEAR_MASK        ((uint16_t)0xF040)

void MW_I2S_Clock_config(uint32_t plln, uint32_t pllr);
void MW_I2S_GetPrescaler(uint32_t audio_sample_freqHz, 
                         uint8_t num_chls, 
                         uint8_t nb_bits_per_sample, 
                         uint8_t enable_master_clk, 
                         uint8_t * i2sdiv, 
                         uint8_t * i2sodd);
void MW_I2S_SetPrescaler(SPI_TypeDef* SPIx, uint8_t i2sdiv, uint8_t i2sodd, I2S_InitTypeDef* I2S_InitStruct);
void MW_I2S_Init(SPI_TypeDef* SPIx, I2S_InitTypeDef* I2S_InitStruct);

#endif