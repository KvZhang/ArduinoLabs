/*
 * ColorSensorGY33.h
 *
 *  Created on: 2016Äê8ÔÂ20ÈÕ
 *      Author: admin
 */

#ifndef COLORSENSORGY33_H_
#define COLORSENSORGY33_H_

#include <Wire.h>
#include "Arduino.h"

#define ADDR 				(0x5A)
typedef enum
{
	reg_RAW_RED_H,
	reg_RAW_RED_L,
	reg_RAW_GREEN_H,
	reg_RAW_GREEN_L,
	reg_RAW_BLUE_H,
	reg_RAW_BLUE_L,
	reg_RAW_CLEAR_H,
	reg_RAW_CLEAR_L,
	reg_Lux_H,
	reg_Lux_L,
	reg_CT_H,
	reg_CT_L,
	reg_R,
	reg_G,
	reg_B,
	reg_Color,
	reg_Config,
}_REGESTER_FOR_GY33;
#define SENSED_COLOR_RED	(1<<0)
#define SENSED_COLOR_YELLOW	(1<<1)
#define SENSED_COLOR_PINK	(1<<2)
#define SENSED_COLOR_WHITE	(1<<3)
#define SENSED_COLOR_BLACK	(1<<4)
#define SENSED_COLOR_GREEN	(1<<5)
#define SENSED_COLOR_INDIGO	(1<<6)
#define SENSED_COLOR_BLUE	(1<<7)

typedef struct
{
    uint16_t Red;
    uint16_t Green;
    uint16_t Blue;
    uint16_t Clear;
} _RAW_RGB;
typedef struct
{
    uint8_t Red;
    uint8_t Green;
    uint8_t Blue;
} _CALC_RGB;

class ColorSensorGY33
{
public:
	ColorSensorGY33();
	_RAW_RGB rawRGB;
	_CALC_RGB RGB;
	uint16_t lux;
	uint16_t CT;
	uint8_t color;
	void init();
	void getColor();
	void getRGB();
	void getRawRGB();
	void getLux();
	void getCT();
	void calibration();
	virtual ~ColorSensorGY33();
};

#endif /* COLORSENSORGY33_H_ */
