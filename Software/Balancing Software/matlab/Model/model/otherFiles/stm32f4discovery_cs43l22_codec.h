/* Copyright 2013 The MathWorks, Inc. */
#ifndef _STM32F4DISCOVERY_CS43L22_CODEC_H_
#define _STM32F4DISCOVERY_CS43L22_CODEC_H_

#define I2C_SPEED                        100000
#define CODEC_ADDRESS                    0x94

#define DMA_SPI3_TX_STREAM              DMA1_Stream7
#define DMA_SPI3_TX_STREAM_IRQn         DMA1_Stream7_IRQn
#define DMA_SPI3_TX_STREAM_IRQHandler   DMA1_Stream7_IRQHandler
#define DMA_TX_COMPLETE_IT_FLAG         DMA_IT_TCIF7

#define waitForI2SDataSend() {while(RESET == (SPI3->SR & SPI_I2S_FLAG_TXE));}

#define stm32_SPI_I2S_SendData(Data)  {waitForI2SDataSend();SPI3->DR = (Data); \
									   waitForI2SDataSend();SPI3->DR = (Data);}

void stm32f4_audio_i2s_init(uint32_t audio_sample_freq);
void cs43l22_codec_write_register(uint8_t reg_addr, uint8_t reg_value);
uint32_t cs43l22_codec_read_register(uint8_t reg_addr);
void stm32f4_audio_codec_init(uint32_t audio_sample_freq);
void cs43l22_codec_init(void);
void stm32f4_audio_ctrl_i2c_init(void);
void cs43l22_codec_reset(void);
void cs43l22_codec_gpio_config(void);
void stm32f4_audio_output(void * auido_input_ptr, uint16_t frame_length);

#endif /* _STM32F4DISCOVERY_CS43L22_CODEC_H_ */
