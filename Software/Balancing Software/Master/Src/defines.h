/**
 *  Defines for your entire project at one place
 * 
 *	@author 	Tilen Majerle
 *	@email		tilen@majerle.eu
 *	@website	http://stm32f4-discovery.com
 *	@version 	v1.0
 *	@ide		Keil uVision 5
 *	@license	GNU GPL v3
 *	
 * |----------------------------------------------------------------------
 * | Copyright (C) Tilen Majerle, 2014
 * | 
 * | This program is free software: you can redistribute it and/or modify
 * | it under the terms of the GNU General Public License as published by
 * | the Free Software Foundation, either version 3 of the License, or
 * | any later version.
 * |  
 * | This program is distributed in the hope that it will be useful,
 * | but WITHOUT ANY WARRANTY; without even the implied warranty of
 * | MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * | GNU General Public License for more details.
 * | 
 * | You should have received a copy of the GNU General Public License
 * | along with this program.  If not, see <http://www.gnu.org/licenses/>.
 * |----------------------------------------------------------------------
 */
#ifndef TM_DEFINES_H
#define TM_DEFINES_H



#define PCBVERSION
#define STM32F4xx


/* Put your global defines for all libraries here used in your project */

#define HIGH 0x1
#define LOW  0x0

#define INPUT 0x0
#define OUTPUT 0x1
//#define USB_VCP

#define PORTPINS 16


#define PORTA PORTPINS*0
#define PORTB PORTPINS*1
#define PORTC PORTPINS*2
#define PORTD PORTPINS*3
#define PORTE PORTPINS*4
#define PORTF PORTPINS*5
#define PORTG PORTPINS*6
#define PORTH PORTPINS*7

#ifdef PCBVERSION


//right = stepper 1
//left = stepper 2
#define STEPPER_RIGHT_STEP_PIN PORTA+4
#define STEPPER_RIGHT_DIR_PIN PORTA+5

#define STEPPER_RIGHT_M0_PIN PORTA+1
#define STEPPER_RIGHT_M1_PIN PORTA+2

#define STEPPER_RIGHT_EN PORTA
#define STEPPER_RIGHT_SLP PORTA+3


#define STEPPER_LEFT_STEP_PIN PORTC+4
#define STEPPER_LEFT_DIR_PIN PORTC+5

#define STEPPER_LEFT_M0_PIN PORTC+1
#define STEPPER_LEFT_M1_PIN PORTC+2

#define STEPPER_LEFT_EN PORTC
#define STEPPER_LEFT_SLP PORTC+3

#define LED1 GPIO_PIN_12
#define LED2 GPIO_PIN_13
#define LED3 GPIO_PIN_14
#define LED4 GPIO_PIN_15
#define LEDALL LED1 | LED2 | LED3 | LED4
#define LEDPORT GPIOC


#endif


#ifdef DISCOVERSION
#define STM32F4_DISCOVERY
#define DISCO_USE_FUNCTIONS




#define STEPPER_RIGHT_STEP_PIN PORTA+2
#define STEPPER_RIGHT_DIR_PIN PORTA+5

#define STEPPER_LEFT_STEP_PIN PORTC+3
#define STEPPER_LEFT_DIR_PIN PORTC+4

#define STEPPER_RIGHT_M0_PIN PORTC+7
#define STEPPER_RIGHT_M1_PIN PORTC+6

#define STEPPER_LEFT_M0_PIN PORTD+10
#define STEPPER_LEFT_M1_PIN PORTD+9

#endif

//#define DEBUGFIFO

#define MICROSTEPS_1    (0x01)
#define MICROSTEPS_2    (0x02)
#define MICROSTEPS_4    (0x04)
#define MICROSTEPS_8    (0x08)
#define MICROSTEPS_16   (0x10)
#define MICROSTEPS_32   (0x20)

#define MAXSPEED        (float)(5000)
#define MAXACCEL        (float)(15000)

#define PRINT_ACCEL     (0x01)
#define PRINT_GYRO      (0x02)
#define PRINT_QUAT      (0x04)
#define PRINT_COMPASS   (0x08)
#define PRINT_EULER     (0x10)
#define PRINT_ROT_MAT   (0x20)
#define PRINT_HEADING   (0x40)
#define PRINT_PEDO      (0x80)
#define PRINT_LINEAR_ACCEL (0x100)


#define ACCEL_ON        (0x01)
#define GYRO_ON         (0x02)
#define COMPASS_ON      (0x04)

#define MOTION          (0)
#define NO_MOTION       (1)

#define DEFAULT_MPU_HZ  (200)

#define FLASH_SIZE      (512)
#define FLASH_MEM_START ((void*)0x1800)

#define PEDO_READ_MS    (1000)
#define TEMP_READ_MS    (500)
#define DATA_TX_MS      (20)//was 20
#define COMPASS_READ_MS (5)

#endif
