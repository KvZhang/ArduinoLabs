/*
 * ATparser.cpp
 *
 *  Created on: 2017Äê7ÔÂ1ÈÕ
 *      Author: zhangyu
 */

#include "ATparser.h"
#include "LaputaConfig.h"
AT_parser::AT_parser()
{
	// TODO Auto-generated constructor stub
	memset(&this->string_buffer[0],0,MAX_PARSE_BUFFER_LEN);
	this->length=0;
	this->parsed_para=0;
}

uint8_t AT_parser::parse()
{
	if(this->length>=3)// a AT CMD with parameters
	{
		if(this->string_buffer[0]=='\r')
		{
			return PARSE_OK;
		}
		else if(this->string_buffer[0]=='+')
		{
			switch(this->string_buffer[1])
			{
			case 'C':
			case 'c':
				this->parsed_para=convert_to_num();
				return PARSE_SET_CH;
			case 'N':
			case 'n':
				this->parsed_para=convert_to_num();
				return PARSE_SET_NUM;
			case 'R':
			case 'r':
				return PARSE_READ_PARA;
			case 'X':
				if(convert_to_num()==100)
				{
					extern LaputaConfig myConfig;
					myConfig.context.count=0;
					myConfig.save_config();
				}
				return PARSE_ERROR;
			default:
				return PARSE_ERROR;
			}
		}
		else
		{
			return PARSE_ERROR;
		}
	}
	else if(this->length)//1 or 2 byte, seems like a error CMD
	{
		return PARSE_ERROR;
	}
	else
	{
		return PARSE_OK;
	}

}

uint8_t AT_parser::convert_to_num()
{
	uint16_t temp=0;
	for(uint8_t i=2;i<this->length;i++)
	{
		if(this->string_buffer[i]>'9'||this->string_buffer[i]<'0')
		{
			break;
		}
		else
		{
			temp=temp*10+string_buffer[i]-'0';
		}
	}
	if(temp>255) return 255;
	return temp;
}
AT_parser::~AT_parser()
{
	// TODO Auto-generated destructor stub
}

