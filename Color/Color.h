/*
 * Color.h
 *
 *  Created on: 2017Äê7ÔÂ16ÈÕ
 *      Author: zhangyu
 */

#ifndef COLOR_H_
#define COLOR_H_
#include "Arduino.h"

typedef enum
{
	Read_RGBC_AD,//read back 8 bytes,L->H: R_H,R_L,G_H,G_L,B_H,B_L,C_H,C_L
	Read_Lux=0x08,//read back 4 bytes
	Read_RGC_Real=0x0C,//read RGB 3 bytes
}COLOR_REG;

typedef union
{
	uint32_t all;
	struct
	{
		uint8_t R;
		uint8_t G;
		uint8_t B;
		uint8_t rsv;
	}RGB;
}COLOR_STRUCT;

class Color
{
public:
	void begin();
	uint32_t read(uint8_t addr=0x5A);
	bool is_convert_finished();
	bool is_desired_color(uint32_t desired_color=0x00);
	Color();
	virtual ~Color();
private:
	COLOR_STRUCT color_result;
	uint8_t flag_end;
};

#endif /* COLOR_H_ */
