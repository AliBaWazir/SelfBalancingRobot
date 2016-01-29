/* Wrapper header for STM32F4-Discovery 
 * 
 * Copyright 2013 The MathWorks, Inc.
 */
#ifndef _STM32F4XX_ADC_WRAPPER_H_
#define _STM32F4XX_ADC_WRAPPER_H_

#define MW_ADC_AVAILABLE		3
#define MW_SINGLE_MODE			0
#define MW_DUAL_MODE			1
#define MW_TRIPLE_MODE			2
#define MW_REGULAR_SMLT_AND_INJECTED_SMLT_MODE		0
#define MW_REGULAR_SMLT_AND_ALTERNATE_TRIGGER_MODE	1
#define MW_INJECTED_SMLT_MODE						2
#define MW_REGULAR_SMLT_MODE						3
#define MW_INTERLEAVED_MODE							4
#define MW_ALTERNATE_TRIGGER_MODE					5

/*
 *******************************************
 * ADC Wrapper functions
 *******************************************
 */
typedef enum _adc_grp_t {REGULAR_GRP = 0, INJECTED_GRP} adc_grp_t;

extern ADC_TypeDef * ADC_base_array[MW_ADC_AVAILABLE];

#define MW_ADC_GetConversionValue(ADCx_selected) 	 (uint16_t)(ADC_base_array[(ADCx_selected)]->DR)
#define MW_ADC_WaitForEOCFlag(ADCx_selected)   		 {while (RESET == ((ADC_base_array[(ADCx_selected)]->SR) & ADC_FLAG_EOC)) {};}
#define MW_ADC_WaitForEOCInjectedFlag(ADCx_selected) {while (RESET == ((ADC_base_array[(ADCx_selected)]->SR) & ADC_FLAG_JEOC)) {};}

extern void MW_ADC_SetScanConvModeAndResolution(uint8_t ADCx_selected, uint8_t ScanConvMode, uint8_t Resolution);

extern void MW_ADC_Init(uint8_t ADCx_selected,
						uint8_t group_selected,
						uint8_t Resolution,
						uint8_t ScanConvMode,
						uint8_t ContinuousConvMode,
						uint8_t ExternalTrigConvEdge,
						uint8_t ExternalTrigConv,
						uint8_t DataAlign,
						uint8_t NbrOfConversion);

extern void MW_ADC_Init_Injected(uint8_t ADCx_selected,
								 uint8_t group_selected,
								 uint8_t Resolution,
								 uint8_t ScanConvMode,
								 uint8_t AutoInjectionConvMode,
								 uint8_t ExternalTrigConvEdge,
								 uint8_t ExternalTrigConv,
								 uint8_t DataAlign,
								 uint8_t NbrOfConversion);

extern void MW_ADC_InjectedChannelConfig(uint8_t ADCx_selected, uint8_t ADC_Channel, uint8_t Rank, uint8_t ADC_SampleTime);
extern void MW_ADC_RegularChannelConfig(uint8_t ADCx_selected, uint8_t ADC_Channel, uint8_t Rank, uint8_t ADC_SampleTime);
extern void MW_ADC_Cmd(uint8_t ADCx_selected, uint8_t NewState);
extern void MW_ADC_EOCOnEachRegularChannelCmd(uint8_t ADCx_selected, uint8_t NewState);
extern void MW_ADC_WriteOverrunInterrupt(uint8_t ADCx_selected, uint8_t interrupt_state);
extern void MW_ADC_WriteWatchdogInterrupt(uint8_t ADCx_selected, uint8_t interrupt_state);
extern void MW_ADC_WriteEOCInterrupt(uint8_t ADCx_selected, uint8_t interrupt_state);
extern void MW_ADC_WriteEOCInjectedInterrupt(uint8_t ADCx_selected, uint8_t interrupt_state);
extern void MW_ADC_SoftwareStartConv(uint8_t ADCx_selected, uint8_t socCond);
extern void MW_ADC_SoftwareStartInjectedConv(uint8_t ADCx_selected, uint8_t socCond);
extern uint16_t MW_ADC_GetInjectedConversionValue(uint8_t ADCx_selected, uint8_t ADC_InjectedChannel);
extern uint8_t MW_ADC_GetFlagStatus(uint8_t ADCx_selected, uint8_t ADC_FLAG);
extern void MW_ADC_ClearFlag(uint8_t ADCx_selected, uint8_t ADC_FLAG);
extern void MW_ADC_AnalogWatchdogCmd(uint8_t ADCx_selected, uint8_t enable_on_reg_grp, uint8_t enable_on_inj_grp, uint8_t enable_single_chl);
extern void MW_ADC_AnalogWatchdogThresholdsConfig(uint8_t ADCx_selected, uint16_t HighThreshold,uint16_t LowThreshold);
extern void MW_ADC_AnalogWatchdogSingleChannelConfig(uint8_t ADCx_selected, uint8_t ADC_Channel);
extern void MW_ADC_CommonInit(uint8_t ADC_MultMode,
							  uint8_t ADC_MultiModeOperation,
							  uint8_t ADC_Prescaler,
							  uint8_t ADC_DMAAccessMode,
							  uint8_t ADC_TwoSamplingDelay,
							  uint8_t dma_disable_selection);

#endif // _STM32F4XX_ADC_WRAPPER_H_
