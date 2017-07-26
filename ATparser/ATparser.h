/*
 * ATparser.h
 *
 *  Created on: 2017.7.1
 *      Author: zhangyu
 */

#ifndef ATPARSER_H_
#define ATPARSER_H_
#include "Arduino.h"
/**************************************
 * "AT", return "OK"
 * "AT+Cxx", return "OK+Cxx", xx is number 0~16
 * "AT+Nxxx", return "OK+Nxxx" ,xxx is number 0~255
 * "AT+Rx",  return "OK+Cxx,Nxxx"
 *
 */
#define MAX_PARSE_BUFFER_LEN (20)
	enum PARSE_RESULT
	{
		PARSE_OK,
		PARSE_ERROR,
		PARSE_SET_CH,
		PARSE_SET_NUM,
		PARSE_READ_PARA,
	};
class AT_parser
{
public:

	char string_buffer[MAX_PARSE_BUFFER_LEN];
	uint8_t length;
	uint8_t parsed_para;
	AT_parser();
	uint8_t parse();
	virtual ~AT_parser();
private:
	uint8_t convert_to_num();

};

#endif /* ATPARSER_H_ */
