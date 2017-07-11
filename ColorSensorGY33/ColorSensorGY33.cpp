/*
 * ColorSensorGY33.cpp
 *
 *  Created on: 2016Äê8ÔÂ20ÈÕ
 *      Author: admin
 */

#include "ColorSensorGY33.h"

ColorSensorGY33::ColorSensorGY33()
{
	// TODO Auto-generated constructor stub
	this->CT=0;
	this->lux=0;
	this->color=0;
	this->RGB.Blue=0;
	this->RGB.Green=0;
	this->RGB.Red=0;
	this->rawRGB.Blue=0;
	this->rawRGB.Clear=0;
	this->rawRGB.Green=0;
	this->rawRGB.Red=0;

}
void ColorSensorGY33::init()
{
	Wire.begin();
}
void ColorSensorGY33::getColor()
{
	Wire.beginTransmission(ADDR);
	Wire.write(reg_Color);
	Wire.endTransmission(false);
	Wire.requestFrom(ADDR,1);
	while(!Wire.available());
	this->color=Wire.read();
}
void ColorSensorGY33::getRGB()
{
	Wire.beginTransmission(ADDR);
	Wire.write(reg_R);
	Wire.endTransmission(false);
	Wire.requestFrom(ADDR,1);
	while(!Wire.available());
	this->RGB.Red=Wire.read();

	Wire.beginTransmission(ADDR);
	Wire.write(reg_G);
	Wire.endTransmission(false);
	Wire.requestFrom(ADDR,1);
	while(!Wire.available());
	this->RGB.Green=Wire.read();

	Wire.beginTransmission(ADDR);
	Wire.write(reg_B);
	Wire.endTransmission(false);
	Wire.requestFrom(ADDR,1);
	while(!Wire.available());
	this->RGB.Blue=Wire.read();
}
void ColorSensorGY33::getRawRGB()
{

}
void ColorSensorGY33::getLux()
{

}
void ColorSensorGY33::getCT()
{

}
void ColorSensorGY33::calibration()
{
	Wire.beginTransmission(ADDR);
	Wire.write(reg_Config);
	Wire.write((3<<4)+1);
	Wire.endTransmission(false);
}
ColorSensorGY33::~ColorSensorGY33()
{
	// TODO Auto-generated destructor stub
}

