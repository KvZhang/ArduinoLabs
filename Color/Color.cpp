/*
 * Color.cpp
 *
 *  Created on: 2017Äê7ÔÂ16ÈÕ
 *      Author: zhangyu
 */

#include "Color.h"
#include "Wire.h"

Color::Color()
{
	// TODO Auto-generated constructor stub
	this->color_result.all=0;
	this->flag_end=0;
}
void Color::begin()
{
	Wire.begin();
}
uint32_t Color::read(uint8_t addr)
{

	Wire.beginTransmission(addr);
	Wire.write(Read_RGC_Real);
	Wire.endTransmission(false);
	Wire.requestFrom((unsigned char)addr,(unsigned char)3);
	while(!Wire.available());
	this->color_result.RGB.R=Wire.read();
	this->color_result.RGB.G=Wire.read();
	this->color_result.RGB.B=Wire.read();
	return this->color_result.all;
}
bool Color::is_desired_color(uint32_t desired_color)
{
	COLOR_STRUCT color;
	color.all=desired_color;
	return (abs(color.RGB.R-this->color_result.RGB.R)<=5 && abs(color.RGB.G-this->color_result.RGB.G)<=5
			&& abs(color.RGB.B-this->color_result.RGB.B)<=5);
}
Color::~Color()
{
	// TODO Auto-generated destructor stub
}

