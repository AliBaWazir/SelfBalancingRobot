/*
 $License:
    Copyright (C) 2010 InvenSense Corporation, All Rights Reserved.
 $
 */
/*******************************************************************************
 * $Id: $
 *******************************************************************************/

/**
 *  @defgroup MSP430_System_Layer MSP430 System Layer
 *  @brief  MSP430 System Layer APIs.
 *          To interface with any platform, eMPL needs access to various
 *          system layer functions.
 *
 *  @{
 *      @file   log_msp430.c
 *      @brief  Logging facility for the TI MSP430.
 */

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <math.h>

#include "main.h"
#include "packet.h"
#include "log.h"
#include "stm32f4xx_hal.h"



#include "usb_device.h"
#include "usbd_cdc.h"

#define BUF_SIZE        (256)
#define PACKET_LENGTH   (23)

#define PACKET_DEBUG    (1)
#define PACKET_QUAT     (2)
#define PACKET_DATA     (3)

#define ONE         0
#define TWO         1
#define THREE       2
#define FOUR        3

/**
 *  @brief      Prints a variable argument log message.
 *  USB output will be formatted as follows:\n
 *  packet[0]       = $\n
 *  packet[1]       = packet type (1: debug, 2: quat, 3: data)\n
 *  packet[2]       = \n for debug packets: log priority\n
 *                    for quaternion packets: unused\n
 *                    for data packets: packet content (accel, gyro, etc)\n
 *  packet[3-20]    = data\n
 *  packet[21]      = \\r\n
 *  packet[22]      = \\n
 *  @param[in]  priority    Log priority (based on Android).
 *  @param[in]  tag         File specific string.
 *  @param[in]  fmt         String of text with optional format tags.
 *
 *  @return     0 if successful.
 */
int _MLPrintLog (int priority, const char* tag, const char* fmt, ...)
{
	va_list args;
	int length, ii;
	char buf[BUF_SIZE], out[PACKET_LENGTH], this_length;

	/* This can be modified to exit for unsupported priorities. */
	switch (priority)
	{
	case MPL_LOG_UNKNOWN:
	case MPL_LOG_DEFAULT:
	case MPL_LOG_VERBOSE:
	case MPL_LOG_DEBUG:
	case MPL_LOG_INFO:
	case MPL_LOG_WARN:
	case MPL_LOG_ERROR:
	case MPL_LOG_SILENT:
		break;
	default:
		return 0;
	}

	va_start(args, fmt);

	length = vsprintf(buf, fmt, args);
	if (length <= 0)
	{
		va_end(args);
		return length;
	}

	memset(out, 0, PACKET_LENGTH);
	out[0] = '$';
	out[1] = PACKET_DEBUG;
	out[2] = priority;
	out[21] = '\r';
	out[22] = '\n';
	for (ii = 0; ii < length; ii += (PACKET_LENGTH-5))
	{
#define min(a,b) ((a < b) ? a : b)
		this_length = min(length-ii, PACKET_LENGTH-5);
		memset(out+3, 0, 18);
		memcpy(out+3, buf+ii, this_length);
		
		USBD_CDC_SetTxBuffer (&hUsbDeviceFS, (uint8_t *)buf, PACKET_LENGTH);
		USBD_CDC_TransmitPacket (&hUsbDeviceFS);
	}
					
	va_end(args);

	return 0;
}

void eMPL_send_quat(long *quat)
{
    int32_t angle;
    double quat1 = 0;
    double quat2 = 0;
    double quat3 = 0;
    double quat4 = 0;
	char out[18];
	
	if (!quat)
		return;
	
	memset(out, 0, 18);
	//out[0] = '$';
	//out[1] = '$';
    /*
	out[2] = (char)(quat[ONE] >> 24);
	out[3] = (char)(quat[ONE] >> 16);
	out[4] = (char)(quat[ONE] >> 8);
	out[5] = (char)quat[ONE];
	out[6] = (char)(quat[TWO] >> 24);
	out[7] = (char)(quat[TWO] >> 16);
	out[8] = (char)(quat[TWO] >> 8);
	out[9] = (char)quat[TWO];
	out[10] = (char)(quat[THREE] >> 24);
	out[11] = (char)(quat[THREE] >> 16);
	out[12] = (char)(quat[THREE] >> 8);
	out[13] = (char)quat[THREE];
	out[14] = (char)(quat[FOUR] >> 24);
	out[15] = (char)(quat[FOUR] >> 16);
	out[16] = (char)(quat[FOUR] >> 8);
	out[17] = (char)quat[FOUR];
    */
    quat1 = (double)quat[ONE]/0xEFFFFFFF;
    quat2 = (double)quat[TWO]/0xEFFFFFFF;
    quat3 = (double)quat[THREE]/0xEFFFFFFF;
    quat4 = (double)quat[FOUR]/0xEFFFFFFF;
    
    angle =  4.0*4096.0*asin(-2.0*((double)quat2*(double)quat4 - (double)quat1*(double)quat3));
    out[0] = angle>>24;
    out[1] = angle>>16;
    out[2] = angle>>8;
    out[3] = angle;
	
	USBD_CDC_SetTxBuffer (&hUsbDeviceFS, (uint8_t *)out, 18);
	USBD_CDC_TransmitPacket (&hUsbDeviceFS);
    application_main(angle);
        
    
}

void eMPL_send_data(unsigned char type, long *data)
{
	char out[PACKET_LENGTH];
	
	if (!data)
		return;
	 
	memset(out, 0, PACKET_LENGTH);
	out[0] = '$';
	out[1] = PACKET_DATA;
	out[2] = type;
	//out[21] = '\r';
	//out[22] = '\n';
	switch (type) {
	/* Two bytes per-element. */
	case PACKET_DATA_ROT:
		out[3] = (char)(data[0] >> 24);
		//out[4] = (char)(data[0] >> 16);
		out[5] = (char)(data[1] >> 24);
		//out[6] = (char)(data[1] >> 16);
		out[7] = (char)(data[2] >> 24);
		//out[8] = (char)(data[2] >> 16);
		out[9] = (char)(data[3] >> 24);
		//out[10] = (char)(data[3] >> 16);
		out[11] = (char)(data[4] >> 24);
		//out[12] = (char)(data[4] >> 16);
		out[13] = (char)(data[5] >> 24);
		//out[14] = (char)(data[5] >> 16);
		out[15] = (char)(data[6] >> 24);
		//out[16] = (char)(data[6] >> 16);
		out[17] = (char)(data[7] >> 24);
		//out[18] = (char)(data[7] >> 16);
		out[19] = (char)(data[8] >> 24);
		//out[20] = (char)(data[8] >> 16);
		break;
	/* Four bytes per-element. */
	/* Four elements. */
	case PACKET_DATA_QUAT:
		out[15] = (char)(data[3] >> 24);
		out[16] = (char)(data[3] >> 16);
		out[17] = (char)(data[3] >> 8);
		out[18] = (char)data[3];
    
        
	/* Three elements. */
	case PACKET_DATA_ACCEL:
	case PACKET_DATA_GYRO:
	case PACKET_DATA_COMPASS:
	case PACKET_DATA_EULER:
        
        //out[3] = (char)(data[0] >> 24);
		//out[4] = (char)(data[1] >> 24)-'0';
        //out[5] = (char)(data[2] >> 24)-'0';
        /*
		out[3] = (char)(data[0] >> 24);
		out[4] = (char)(data[0] >> 16);
		out[5] = (char)(data[0] >> 8);
		out[6] = (char)data[0];
		out[7] = (char)(data[1] >> 24);
		out[8] = (char)(data[1] >> 16);
		out[9] = (char)(data[1] >> 8);
		out[10] = (char)data[1];
		out[11] = (char)(data[2] >> 24);
		out[12] = (char)(data[2] >> 16);
		out[13] = (char)(data[2] >> 8);
		out[14] = (char)data[2];
        */
		break;
	case PACKET_DATA_HEADING:
		out[3] = (char)(data[0] >> 24);
		out[4] = (char)(data[0] >> 16);
		out[5] = (char)(data[0] >> 8);
		out[6] = (char)data[0];
		break;
	default:
		return;
	}
	
	USBD_CDC_SetTxBuffer (&hUsbDeviceFS, (uint8_t *)out, PACKET_LENGTH);
	USBD_CDC_TransmitPacket (&hUsbDeviceFS);
}

/**
 * @}
**/


