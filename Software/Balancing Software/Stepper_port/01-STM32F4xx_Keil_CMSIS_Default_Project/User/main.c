/**
 * Keil project template
 *
 * Before you start, select your target, on the right of the "Load" button
 *
 * @author    Tilen Majerle
 * @email     tilen@majerle.eu
 * @website   http://stm32f4-discovery.com
 * @ide       Keil uVision 5
 * @conf      PLL parameters are set in "Options for Target" -> "C/C++" -> "Defines"
 * @packs     STM32F4xx Keil packs version 2.4.0 or greater required
 * @stdperiph STM32F4xx Standard peripheral drivers version 1.5.0 or greater required
 */
/* Include core modules */
#include "stm32f4xx.h"
/* Include my libraries here */
#include "arduino32.h"
#include "defines.h"
#include "tm_stm32f4_delay.h"
#include "tm_stm32f4_disco.h"
#define OUTPUTPIN  4*16+3
int main(void) {
	

	SystemInit();
	

	TM_DELAY_Init();
	

	TM_DISCO_LedInit();
	

	TM_DISCO_LedOn(LED_ALL);
	

	Delayms(2000);
	
	while (1) {

		TM_DISCO_LedToggle(LED_ALL);
		

		Delayms(500);
	}
	
/*
	SystemInit();
	

	TM_DELAY_Init();
	

	pinMode(OUTPUTPIN, OUTPUT);
	
	


	
	while (1) {
		
		//Delayms(5);
		digitalWrite(OUTPUTPIN, LOW);

		//Delayms(5);
		digitalWrite(OUTPUTPIN, HIGH);
	}
	
	*/
}
