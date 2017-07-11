/*
 * LaputaLEDController.cpp
 *
 *  Created on: 2017Äê4ÔÂ3ÈÕ
 *      Author: zhangyu
 */

#include "LaputaLEDController.h"
Adafruit_NeoPixel strip(5,10);
LaputaLEDController::LaputaLEDController(uint16_t n,uint16_t p, neoPixelType t)
{
	// TODO Auto-generated constructor stub
	this->dataPin=p;
	this->num=n;
	this->type=t;

}
void LaputaLEDController::begin()
{
	strip.updateType(this->type);
	strip.updateLength(this->num);
	strip.setPin(this->dataPin);
	strip.begin();
	strip.show();
}
void LaputaLEDController::show_pure_color(uint8_t c)
{
	if(c>=Strip_color_total)
	{
		return;
	}
	for(uint16_t i=0; i<strip.numPixels(); i++)
	{
		strip.setPixelColor(i, color[c]);
	}
	strip.show();
}
void LaputaLEDController::set_single_pixel_color(uint8_t n,uint8_t c)
{
	strip.setPixelColor(n, color[c]);
}
void LaputaLEDController::set_segment_color(uint8_t seg,uint8_t c)
{
	//segment from 1 to n
	for(uint8_t i=0;i<SEG_NUM;i++)
	{
		strip.setPixelColor((seg-1)*SEG_NUM+i, color[c]);
	}
}
void LaputaLEDController::show()
{
	strip.show();
}
LaputaLEDController::~LaputaLEDController()
{
	// TODO Auto-generated destructor stub
}

