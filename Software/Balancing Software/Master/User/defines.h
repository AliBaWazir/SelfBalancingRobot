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

/* Put your global defines for all libraries here used in your project */
#define PORTPINS 16

#define PORTA PORTPINS*0
#define PORTB PORTPINS*1
#define PORTC PORTPINS*2
#define PORTD PORTPINS*3
#define PORTE PORTPINS*4
#define PORTF PORTPINS*5
#define PORTG PORTPINS*6
#define PORTH PORTPINS*7

#define STEPPER_RIGHT_STEP_PIN PORTA+2
#define STEPPER_RIGHT_DIR_PIN PORTA+5

#define STEPPER_LEFT_STEP_PIN PORTC+3
#define STEPPER_LEFT_DIR_PIN PORTC+4

#define STEPPER_RIGHT_M0_PIN PORTC+7
#define STEPPER_RIGHT_M1_PIN PORTC+6

#define STEPPER_LEFT_M0_PIN PORTD+14
#define STEPPER_LEFT_M1_PIN PORTD+15


#endif
