/*********************************************************************
This is an example for our Monochrome OLEDs based on SSD1306 drivers

  Pick one up today in the adafruit shop!
  ------> http://www.adafruit.com/category/63_98

This example is for a 128x64 size display using I2C to communicate
3 pins are required to interface (2 I2C and one reset)

Adafruit invests time and resources providing this open source code, 
please support Adafruit and open-source hardware by purchasing 
products from Adafruit!

Written by Limor Fried/Ladyada  for Adafruit Industries.  
BSD license, check license.txt for more information
All text above, and the splash screen must be included in any redistribution
*********************************************************************/

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

#define NUMFLAKES 10
#define XPOS 0
#define YPOS 1
#define DELTAY 2


#define LOGO16_GLCD_HEIGHT 16 
#define LOGO16_GLCD_WIDTH  16 
//static const unsigned char PROGMEM logo16_glcd_bmp[] =

static const unsigned char PROGMEM Bowser_1[] = {
0x01, 0x00, 0x98, 0x00, 0x00, 0x02, 0x81, 0x54, 0x00, 0x00, 0x02, 0x8B, 0x73, 0x20, 0x00, 0x04,
0x94, 0x12, 0xD0, 0x00, 0x04, 0xE0, 0x11, 0x38, 0x00, 0x04, 0xE3, 0xE3, 0x74, 0x00, 0x04, 0xFF,
0xE3, 0x08, 0x00, 0x0F, 0xFF, 0xF6, 0x10, 0x00, 0x13, 0xFC, 0x7E, 0x14, 0x00, 0x23, 0xF8, 0x1F,
0x0A, 0x00, 0x49, 0xF7, 0xBF, 0x04, 0x00, 0x3C, 0xC9, 0xFF, 0x84, 0x00, 0x1A, 0xC8, 0xCF, 0xC4,
0x00, 0x18, 0xF1, 0x87, 0x83, 0x00, 0x1F, 0xCF, 0x03, 0xE3, 0xC0, 0x30, 0xEE, 0x23, 0x91, 0xD0,
0x60, 0x3C, 0xF3, 0x0D, 0xF8, 0x40, 0x01, 0xB3, 0x0F, 0x38, 0xD8, 0xC3, 0xF7, 0x03, 0xFC, 0x88,
0x83, 0xF7, 0x80, 0xFE, 0x80, 0x0E, 0xF7, 0xFC, 0x7F, 0x80, 0x1F, 0xEF, 0xFE, 0x3F, 0xC7, 0x39,
0x8F, 0xFF, 0x1F, 0x7F, 0xF1, 0x9F, 0xFF, 0x9F, 0x49, 0xF1, 0x1F, 0xFF, 0xCF, 0x29, 0xF9, 0x1F,
0xFF, 0xCF, 0x1A, 0xFA, 0x3F, 0xFF, 0xE7, 0x03, 0x18, 0x3F, 0xFF, 0xE7, 0x02, 0x00, 0x7F, 0xFF,
0xE7, 0x03, 0x01, 0xFF, 0xFF, 0xE7, 0x05, 0xFF, 0xFE, 0xD7, 0xE7, 0x07, 0xFF, 0xFF, 0xFF, 0xE7,
0x07, 0xFF, 0xFF, 0xFE, 0x00, 0x07, 0xFE, 0x07, 0xFE, 0x00, 0x04, 0x92, 0x04, 0x92, 0x00, 0x02,
0xDA, 0x02, 0xD4, 0x00, 0x01, 0xB6, 0x01, 0xA8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
};

static const unsigned char PROGMEM Bowser_2[] = {
0x01, 0x00, 0x98, 0x00, 0x00, 0x02, 0x81, 0x54, 0x00, 0x00, 0x02, 0x8B, 0x73, 0x20, 0x00, 0x04,
0x94, 0x12, 0xD0, 0x00, 0x04, 0xE0, 0x11, 0x28, 0x00, 0x04, 0xE3, 0xE3, 0x74, 0x00, 0x04, 0xFF,
0xE3, 0x08, 0x00, 0x0F, 0xFF, 0xF6, 0x10, 0x00, 0x17, 0xFE, 0x7E, 0x14, 0x00, 0x23, 0xFC, 0x1F,
0x0A, 0x00, 0x4B, 0xF8, 0x3F, 0x04, 0x00, 0x39, 0xF9, 0xFF, 0x84, 0x00, 0x1D, 0xEE, 0xCF, 0xC4,
0x00, 0x1A, 0xC9, 0x87, 0x83, 0x00, 0x1F, 0xF7, 0x03, 0xE3, 0xC0, 0x30, 0xE6, 0x23, 0x91, 0xD0,
0x60, 0x3C, 0xF3, 0x0D, 0xF8, 0x40, 0x01, 0xB3, 0x0F, 0x38, 0xD8, 0xC3, 0xF7, 0x03, 0xFC, 0x88,
0x83, 0xF7, 0x80, 0xFE, 0x80, 0x0E, 0xF7, 0xFC, 0x7F, 0x80, 0x1F, 0xEF, 0xFE, 0x3F, 0xC7, 0x39,
0x8F, 0xFF, 0x1F, 0x7F, 0xF1, 0x9F, 0xFF, 0x9F, 0x49, 0xF1, 0x1F, 0xFF, 0xCF, 0x29, 0xF9, 0x1F,
0xFF, 0xCF, 0x1A, 0xFA, 0x3F, 0xFF, 0xE7, 0x03, 0x18, 0x3F, 0xFF, 0xE7, 0x02, 0x00, 0x7F, 0xFF,
0xE7, 0x03, 0x01, 0xFF, 0xFF, 0xE7, 0x05, 0xFF, 0xFE, 0xD7, 0xE7, 0x07, 0xFF, 0xFF, 0xFF, 0xE7,
0x07, 0xFF, 0x07, 0xFE, 0x00, 0x07, 0xFE, 0x07, 0xFE, 0x00, 0x04, 0x92, 0x04, 0x92, 0x00, 0x02,
0xDA, 0x02, 0xD4, 0x00, 0x01, 0xB6, 0x01, 0xA8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
};

static const unsigned char PROGMEM Bowser_3[] = {
0x01, 0x00, 0x98, 0x00, 0x00, 0x02, 0x81, 0x54, 0x00, 0x00, 0x02, 0x8B, 0x73, 0x20, 0x00, 0x04,
0x94, 0x12, 0xD0, 0x00, 0x04, 0xE0, 0x11, 0x28, 0x00, 0x04, 0xE3, 0xE3, 0x74, 0x00, 0x04, 0xFF,
0xE3, 0x08, 0x00, 0x0F, 0xFF, 0xF6, 0x10, 0x00, 0x17, 0xFE, 0x7E, 0x14, 0x00, 0x23, 0xFC, 0x1F,
0x0A, 0x00, 0x4B, 0xF8, 0x3F, 0x04, 0x00, 0x39, 0xF9, 0xCF, 0x84, 0x00, 0x1D, 0xEE, 0x87, 0xC4,
0x00, 0x1A, 0xCF, 0x07, 0x83, 0x00, 0x1F, 0xF4, 0x23, 0xE3, 0xC0, 0x30, 0xE8, 0x73, 0x91, 0xD0,
0x60, 0x31, 0xE3, 0x0D, 0xF8, 0x58, 0xC3, 0x83, 0x0F, 0x38, 0xC8, 0x86, 0x17, 0x03, 0xFC, 0x80,
0x0E, 0x17, 0x80, 0xFE, 0x80, 0x1E, 0x1F, 0xFC, 0x7F, 0xC0, 0x78, 0x1F, 0xFE, 0x3F, 0xFF, 0xF0,
0x3F, 0xFF, 0x1F, 0x4F, 0xF0, 0x7F, 0xFF, 0x9F, 0x49, 0xE0, 0xFF, 0xFF, 0xCF, 0x28, 0x01, 0xFF,
0xFF, 0xCF, 0x1F, 0x0F, 0xFF, 0xFF, 0xE7, 0x03, 0xFF, 0xFF, 0xFF, 0xE7, 0x01, 0xFF, 0xFF, 0xFF,
0xE7, 0x03, 0xFF, 0xFF, 0xFF, 0xE7, 0x05, 0xB7, 0xFE, 0xD7, 0xE7, 0x07, 0xFF, 0xFF, 0xFF, 0xE7,
0x07, 0xFF, 0xFF, 0xFE, 0x00, 0x07, 0xFE, 0x07, 0xFE, 0x00, 0x04, 0x92, 0x04, 0x92, 0x00, 0x02,
0xDA, 0x02, 0xD4, 0x00, 0x01, 0xB6, 0x01, 0xA8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
};

static const unsigned char PROGMEM Bowser_4[] = {
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x20, 0x13, 0x00, 0x00, 0x00, 0x50, 0x2A, 0x80, 0x00, 0x00, 0x51, 0x6E,
0x64, 0x00, 0x00, 0x92, 0x82, 0x5A, 0x00, 0x00, 0x9C, 0x02, 0x25, 0x00, 0x00, 0x9C, 0x7C, 0x6E,
0x80, 0x00, 0x9F, 0xFC, 0x61, 0x00, 0x01, 0xFF, 0xFE, 0xC2, 0x00, 0x02, 0xFF, 0xCF, 0xC2, 0x80,
0x04, 0x7F, 0x83, 0xE1, 0x40, 0x09, 0x7F, 0x07, 0xE0, 0x80, 0x07, 0x3F, 0x39, 0xF0, 0x80, 0x03,
0xBD, 0xD0, 0xF8, 0x80, 0x03, 0x59, 0xE0, 0xF0, 0x60, 0x03, 0xFE, 0x84, 0x7C, 0x78, 0x06, 0x1D,
0x0E, 0x72, 0x3A, 0x0C, 0x06, 0x3C, 0x61, 0xBF, 0x0B, 0x18, 0x70, 0x61, 0xE7, 0x19, 0x10, 0xC2,
0xE0, 0x7F, 0x10, 0x01, 0xC2, 0xF0, 0x1F, 0x10, 0x03, 0xC3, 0xFF, 0x8F, 0x18, 0x0F, 0x03, 0xFF,
0xC7, 0x1F, 0xFE, 0x07, 0xFF, 0xE3, 0x09, 0xFE, 0x0F, 0xFF, 0xF3, 0xFF, 0xFF, 0xFF, 0xC0, 0x00,
0xFF, 0xC0, 0xFF, 0xC0, 0x00, 0x92, 0x40, 0x92, 0x40, 0x00, 0x5B, 0x40, 0x5A, 0x80, 0x00, 0x36,
0xC0, 0x35, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
};

static const unsigned char PROGMEM Bowser_5[] = {
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x20, 0x13, 0x00, 0x00, 0x00, 0x50, 0x2A, 0x80, 0x00, 0x00, 0x51, 0x6E, 0x64, 0x00, 0x00,
0x92, 0x82, 0x5A, 0x00, 0x00, 0x9C, 0x02, 0x25, 0x00, 0x00, 0x9C, 0x7C, 0x6E, 0x80, 0x00, 0x9F,
0xFC, 0x61, 0x00, 0x01, 0xFF, 0xFE, 0xC2, 0x00, 0x02, 0xFF, 0xCF, 0xC2, 0x80, 0x04, 0x7F, 0x83,
0xE1, 0x40, 0x09, 0x7F, 0x07, 0xE0, 0x80, 0x07, 0x3F, 0x39, 0xF0, 0x80, 0x03, 0xBD, 0xD0, 0xF8,
0x80, 0x03, 0x59, 0xE0, 0xF0, 0x60, 0x03, 0xFE, 0x84, 0x7C, 0x78, 0x06, 0x1D, 0x0E, 0x72, 0x3A,
0xFF, 0xFF, 0xFF, 0xC0, 0x00, 0xFF, 0xC0, 0xFF, 0xC0, 0x00, 0x92, 0x40, 0x92, 0x40, 0x00, 0x5B,
0x40, 0x5A, 0x80, 0x00, 0x36, 0xC0, 0x35, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
};

static const unsigned char PROGMEM Bowser_6[] = {
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x13, 0x00, 0x00, 0x00, 0x50, 0x2A,
0x80, 0x00, 0x00, 0x51, 0x6E, 0x64, 0x00, 0x00, 0x92, 0x82, 0x5A, 0x00, 0x00, 0x9C, 0x02, 0x27,
0x00, 0x00, 0x9C, 0x7C, 0x6E, 0x80, 0x00, 0x9F, 0xFC, 0x61, 0x00, 0x01, 0xFF, 0xFE, 0xC2, 0x00,
0xFF, 0xFF, 0xFF, 0xC0, 0x00, 0xFF, 0xC0, 0xFF, 0xC0, 0x00, 0x92, 0x40, 0x92, 0x40, 0x00, 0x5B,
0x40, 0x5A, 0x80, 0x00, 0x36, 0xC0, 0x35, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
};

const unsigned char PROGMEM CAT[] = {
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x22, 0x00, 0x00, 0x00, 0x00, 0x04, 0x80, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x88, 0x02, 0x00, 0x00, 0x00, 0x02, 0x91, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x90, 0x40, 0x00, 0x11, 0x40, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x10, 0x92, 0x12, 0x04, 0x00, 0x00, 0x05, 0x12, 0x44,
0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x08, 0x00, 0x51, 0x00, 0x00, 0x02, 0xC0, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x02, 0x20, 0x01, 0x04, 0x4A, 0x00, 0x29, 0x24, 0x00,
0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x08, 0x10, 0xA1, 0x00, 0x00, 0x02, 0x81, 0x20,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x09, 0x50, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0xA0, 0x00, 0xA0, 0x52, 0x20, 0x12, 0x84, 0x80,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x09, 0x08, 0x00, 0x09, 0x50, 0x00,
0x00, 0x00, 0x00, 0x20, 0x00, 0x04, 0x20, 0x00, 0x80, 0x02, 0x00, 0x40, 0x02, 0x54, 0xC2, 0x20,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x40, 0x00, 0x29, 0x09, 0x40, 0x0A, 0xA0, 0x80,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x80, 0x40, 0x14, 0xA9, 0x48, 0x04,
0x00, 0x00, 0x88, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x02, 0x24, 0x00, 0x15, 0x42, 0x40,
0x00, 0x0A, 0x50, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x91, 0x01, 0x55, 0x50, 0x00,
0x00, 0x20, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x08, 0x40, 0x20, 0x5A, 0xA5, 0x20,
0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0xA1, 0x25, 0x14, 0x2A, 0xA0, 0x00,
0x00, 0x02, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0xAA, 0x91, 0x20,
0x00, 0x05, 0x45, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x2A, 0x54, 0x05, 0x2D, 0x44, 0x00,
0x00, 0x05, 0x20, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x25, 0x40, 0x80, 0x11, 0x56, 0xA0, 0x88,
0x00, 0x05, 0x40, 0xB0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x81, 0x38, 0x24, 0x04, 0xAB, 0x44, 0x20,
0x00, 0x06, 0xA1, 0x54, 0x00, 0x00, 0x00, 0x00, 0x02, 0x03, 0xB8, 0x01, 0x52, 0xD5, 0x01, 0x00,
0x00, 0x05, 0x41, 0x50, 0x00, 0x00, 0x00, 0x00, 0x08, 0xAD, 0x54, 0x00, 0x05, 0x6A, 0xA4, 0x40,
0x00, 0x87, 0x61, 0x68, 0x00, 0x00, 0x00, 0x00, 0x02, 0x8D, 0xB8, 0x08, 0x00, 0x2E, 0x01, 0x00,
0x00, 0x02, 0xA5, 0xA8, 0x10, 0x00, 0x00, 0x00, 0x2A, 0xC1, 0xEC, 0x20, 0x0A, 0xAA, 0x88, 0x20,
0x02, 0x40, 0xF6, 0xD0, 0x02, 0x00, 0x00, 0x00, 0x0B, 0x42, 0xB6, 0x14, 0x40, 0x55, 0x22, 0x80,
0x00, 0x01, 0x7B, 0x60, 0x00, 0x00, 0x00, 0x00, 0x4D, 0xA3, 0xF8, 0x20, 0x15, 0x2A, 0x00, 0x00,
0x00, 0x10, 0x6E, 0xC0, 0x04, 0x00, 0x00, 0x02, 0x06, 0xC2, 0xA8, 0x29, 0x00, 0x96, 0x84, 0x80,
0x00, 0x00, 0x1B, 0x00, 0x00, 0x80, 0x40, 0x10, 0x87, 0xA7, 0xF0, 0x84, 0x10, 0xAA, 0x10, 0x00,
0x00, 0x44, 0x00, 0x00, 0x02, 0x20, 0x00, 0x8A, 0x06, 0xFA, 0xE0, 0x50, 0x0A, 0x2D, 0x02, 0x40,
0x00, 0x12, 0x00, 0x00, 0x00, 0x00, 0x10, 0x40, 0x83, 0xDF, 0xA0, 0x00, 0x08, 0xAA, 0x40, 0x00,
0x00, 0x01, 0x48, 0x00, 0x05, 0x48, 0x04, 0x12, 0x01, 0xF7, 0x81, 0x50, 0x02, 0x54, 0x09, 0x00,
0x00, 0x00, 0x20, 0x00, 0x00, 0x84, 0x10, 0x00, 0x00, 0x7A, 0x00, 0x40, 0x29, 0x2A, 0x20, 0x00,
0x00, 0x01, 0x0A, 0xA0, 0x02, 0x20, 0x05, 0x0A, 0x00, 0x00, 0x05, 0x10, 0x84, 0xA8, 0x84, 0x80,
0x00, 0x00, 0x40, 0x14, 0x00, 0x92, 0x10, 0x80, 0x00, 0x04, 0x11, 0x40, 0x09, 0x54, 0x00, 0x00,
0x00, 0x00, 0x0A, 0x40, 0x00, 0x08, 0x84, 0x40, 0x24, 0x00, 0x48, 0x00, 0x12, 0x51, 0x02, 0x00,
0x00, 0x00, 0x00, 0x90, 0x02, 0x41, 0x12, 0xA8, 0x0A, 0xAA, 0x92, 0x10, 0x04, 0xA8, 0x10, 0x40,
0x00, 0x00, 0x04, 0x04, 0x00, 0x04, 0x49, 0x00, 0x04, 0x14, 0x48, 0x80, 0x22, 0x52, 0x01, 0x00,
0x00, 0x00, 0x21, 0x40, 0x00, 0x00, 0x24, 0xA0, 0x45, 0x42, 0x80, 0x08, 0x95, 0x68, 0x48, 0x00,
0x00, 0x00, 0x84, 0x10, 0x20, 0x05, 0x5A, 0x00, 0x00, 0x28, 0x00, 0x02, 0x00, 0xA1, 0x01, 0x00,
0x00, 0x04, 0x00, 0x40, 0x82, 0x00, 0xAD, 0x48, 0x2A, 0x92, 0x50, 0x00, 0xAA, 0x50, 0x00, 0x00,
0x00, 0x00, 0x11, 0x02, 0x01, 0x2A, 0xAD, 0x01, 0x00, 0x01, 0x01, 0x22, 0x11, 0x44, 0x08, 0x00,
0x00, 0x10, 0x80, 0x20, 0x00, 0x81, 0x57, 0x80, 0x4A, 0x94, 0x04, 0x08, 0xA5, 0x20, 0x21, 0x00,
0x00, 0x00, 0x02, 0x00, 0x42, 0x2A, 0xAE, 0xA1, 0x00, 0x80, 0x10, 0x01, 0x08, 0xA4, 0x00, 0x00,
0x00, 0x00, 0x00, 0x84, 0x00, 0x09, 0x5B, 0x40, 0x22, 0x48, 0x41, 0x04, 0x45, 0x00, 0x84, 0x00,
0x00, 0x00, 0x10, 0x00, 0x01, 0x4A, 0xD5, 0x82, 0x90, 0x02, 0x00, 0x21, 0x02, 0xA2, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x7E, 0xA0, 0x00, 0x20, 0x10, 0x0A, 0x29, 0x00, 0x11, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x21, 0x55, 0x80, 0xA8, 0x88, 0x82, 0x80, 0x01, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x48, 0x40, 0x11, 0xAA, 0xC0, 0x82, 0x00, 0x20, 0x2A, 0x0A, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x0A, 0xAB, 0x62, 0x40, 0x20, 0x04, 0x00, 0x21, 0x20, 0x84, 0x00,
0x00, 0x00, 0x00, 0x02, 0x40, 0xA5, 0x15, 0x41, 0x24, 0x04, 0x81, 0x28, 0x0A, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x20, 0x01, 0x10, 0x02, 0xE0, 0x91, 0x02, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x01, 0x20, 0xA9, 0x09, 0x51, 0x48, 0x40, 0x91, 0x20, 0x50, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0xA0, 0x54, 0xA5, 0x00, 0x40, 0x80, 0x08, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x22, 0x00, 0x00, 0x00, 0x00, 0xA2, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x20, 0x54, 0xA0, 0x09, 0x00, 0x08, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x40, 0x02, 0xA0, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x2A, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x10, 0x00, 0x00, 0x10, 0x02, 0x80, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x09, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x40, 0x04, 0x80, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x08, 0x40, 0x10, 0x00, 0x00, 0x00, 0x00
};



#if (SSD1306_LCDHEIGHT != 64)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif
#define BOWSERH  37
#define BOWSERW  40
#define DELAYBOWSER 100
void setup()   { 
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  digitalWrite(4, HIGH);
  digitalWrite(5, LOW);  
  Serial.begin(9600);

  // by default, we'll generate the high voltage from the 3.3v line internally! (neat!)
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3D (for the 128x64)
  // init done
  
  // Show image buffer on the display hardware.
  // Since the buffer is intialized with an Adafruit splashscreen
  // internally, this will display the splashscreen.
  display.display();
  delay(2000);
}

   
  

  
void loop() {
  
  display.clearDisplay();
  
  display.drawBitmap(0, 0, CAT,  128,  64, WHITE);
  
  display.display();

  delay(5000);
  
  
  display.clearDisplay();
  
  display.drawBitmap(0, 0, Bowser_1,  BOWSERW,  BOWSERH, WHITE);
  
  display.display();

  delay(1000);
  

  //
  
  display.clearDisplay();
  
  display.drawBitmap(0, 0, Bowser_2,  BOWSERW,  BOWSERH, WHITE);
  
  display.display();
  delay(DELAYBOWSER);

   //
  
  display.clearDisplay();
  
  display.drawBitmap(0, 0, Bowser_3,  BOWSERW,  BOWSERH, WHITE);
  
  display.display();
  delay(DELAYBOWSER);
  
   //
  
  display.clearDisplay();
  
  display.drawBitmap(0, 0, Bowser_4,  BOWSERW,  BOWSERH, WHITE);
  
  display.display();
  delay(DELAYBOWSER);

   //
  
  display.clearDisplay();
  
  display.drawBitmap(0, 0, Bowser_5,  BOWSERW,  BOWSERH, WHITE);
  
  display.display();
  delay(DELAYBOWSER);

   //
  
  display.clearDisplay();
  
  display.drawBitmap(0, 0, Bowser_6,  BOWSERW,  BOWSERH, WHITE);
  
  display.display();
  delay(DELAYBOWSER);
    
  // draw a bitmap icon and 'animate' movement
}









void testdrawchar(void) {
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);

  for (uint8_t i=0; i < 168; i++) {
    if (i == '\n') continue;
    display.write(i);
    if ((i > 0) && (i % 21 == 0))
      display.println();
  }    
  display.display();
}

void testdrawcircle(void) {
  for (int16_t i=0; i<display.height(); i+=2) {
    display.drawCircle(display.width()/2, display.height()/2, i, WHITE);
    display.display();
  }
}

void testfillrect(void) {
  uint8_t color = 1;
  for (int16_t i=0; i<display.height()/2; i+=3) {
    // alternate colors
    display.fillRect(i, i, display.width()-i*2, display.height()-i*2, color%2);
    display.display();
    color++;
  }
}

void testdrawtriangle(void) {
  for (int16_t i=0; i<min(display.width(),display.height())/2; i+=5) {
    display.drawTriangle(display.width()/2, display.height()/2-i,
                     display.width()/2-i, display.height()/2+i,
                     display.width()/2+i, display.height()/2+i, WHITE);
    display.display();
  }
}

void testfilltriangle(void) {
  uint8_t color = WHITE;
  for (int16_t i=min(display.width(),display.height())/2; i>0; i-=5) {
    display.fillTriangle(display.width()/2, display.height()/2-i,
                     display.width()/2-i, display.height()/2+i,
                     display.width()/2+i, display.height()/2+i, WHITE);
    if (color == WHITE) color = BLACK;
    else color = WHITE;
    display.display();
  }
}

void testdrawroundrect(void) {
  for (int16_t i=0; i<display.height()/2-2; i+=2) {
    display.drawRoundRect(i, i, display.width()-2*i, display.height()-2*i, display.height()/4, WHITE);
    display.display();
  }
}

void testfillroundrect(void) {
  uint8_t color = WHITE;
  for (int16_t i=0; i<display.height()/2-2; i+=2) {
    display.fillRoundRect(i, i, display.width()-2*i, display.height()-2*i, display.height()/4, color);
    if (color == WHITE) color = BLACK;
    else color = WHITE;
    display.display();
  }
}
   
void testdrawrect(void) {
  for (int16_t i=0; i<display.height()/2; i+=2) {
    display.drawRect(i, i, display.width()-2*i, display.height()-2*i, WHITE);
    display.display();
  }
}

void testdrawline() {  
  for (int16_t i=0; i<display.width(); i+=4) {
    display.drawLine(0, 0, i, display.height()-1, WHITE);
    display.display();
  }
  for (int16_t i=0; i<display.height(); i+=4) {
    display.drawLine(0, 0, display.width()-1, i, WHITE);
    display.display();
  }
  delay(250);
  
  display.clearDisplay();
  for (int16_t i=0; i<display.width(); i+=4) {
    display.drawLine(0, display.height()-1, i, 0, WHITE);
    display.display();
  }
  for (int16_t i=display.height()-1; i>=0; i-=4) {
    display.drawLine(0, display.height()-1, display.width()-1, i, WHITE);
    display.display();
  }
  delay(250);
  
  display.clearDisplay();
  for (int16_t i=display.width()-1; i>=0; i-=4) {
    display.drawLine(display.width()-1, display.height()-1, i, 0, WHITE);
    display.display();
  }
  for (int16_t i=display.height()-1; i>=0; i-=4) {
    display.drawLine(display.width()-1, display.height()-1, 0, i, WHITE);
    display.display();
  }
  delay(250);

  display.clearDisplay();
  for (int16_t i=0; i<display.height(); i+=4) {
    display.drawLine(display.width()-1, 0, 0, i, WHITE);
    display.display();
  }
  for (int16_t i=0; i<display.width(); i+=4) {
    display.drawLine(display.width()-1, 0, i, display.height()-1, WHITE); 
    display.display();
  }
  delay(250);
}

void testscrolltext(void) {
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(10,0);
  display.clearDisplay();
  display.println("scroll");
  display.display();
 
  display.startscrollright(0x00, 0x0F);
  delay(2000);
  display.stopscroll();
  delay(1000);
  display.startscrollleft(0x00, 0x0F);
  delay(2000);
  display.stopscroll();
  delay(1000);    
  display.startscrolldiagright(0x00, 0x07);
  delay(2000);
  display.startscrolldiagleft(0x00, 0x07);
  delay(2000);
  display.stopscroll();
}
