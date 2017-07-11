/*
 * LaputaLEDController.h
 *
 *  Created on: 2017Äê4ÔÂ3ÈÕ
 *      Author: zhangyu
 */

#ifndef LAPUTALEDCONTROLLER_H_
#define LAPUTALEDCONTROLLER_H_

#include"Arduino.h"
#include"Adafruit_NeoPixel.h"

typedef enum
{
	Strip_color_off,
	Strip_color_red,
	Strip_color_green,
	Strip_color_blue,
	Strip_color_total,
}COLOR_TYPE;
const uint32_t color[]={0x00,0xff0000,0xff00,0xff};

#define SEG_NUM (5)

class LaputaLEDController
{
public:
	LaputaLEDController(uint16_t n,uint16_t p=10, neoPixelType t= NEO_GRB + NEO_KHZ800 );
	void begin();
	void show_pure_color(uint8_t c);
	void set_single_pixel_color(uint8_t n,uint8_t c);
	void set_segment_color(uint8_t seg,uint8_t c);
	void show();
	virtual ~LaputaLEDController();
private:
	uint16_t num;
	uint16_t dataPin;
	neoPixelType type;
};
extern Adafruit_NeoPixel strip;
#endif /* LAPUTALEDCONTROLLER_H_ */
