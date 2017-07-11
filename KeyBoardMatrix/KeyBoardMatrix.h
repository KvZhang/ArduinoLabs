/*
 * KeyBoardMatrix.h
 *
 *  Created on: 2017Äê4ÔÂ15ÈÕ
 *      Author: zhangyu
 */

#ifndef KEYBOARDMATRIX_H_
#define KEYBOARDMATRIX_H_

#include "Arduino.h"
#define MATRIX_SIZE (5)//Max 5*5 key matrix


/***************
 *
 * test 5*5 handle will takes within 120us
 */
//#define DEBUG_KEYBOARD

class KeyBoardMatrix
{
public:
	KeyBoardMatrix(const uint8_t* linePtr,const uint8_t* columnPtr,uint8_t lineNum,uint8_t columnNum);
	bool keyHandler();//no key be pushed, return 0, need about 80 us
	uint8_t getKey();//will return 0, until all key released
	virtual ~KeyBoardMatrix();
private:
	uint8_t lineNumber;
	uint8_t columnNumber;
	uint8_t linePin[MATRIX_SIZE];
	uint8_t columnPin[MATRIX_SIZE];
	uint8_t lastKey;
	uint8_t keyPushed;
	uint8_t readLineInput();
	uint8_t readColumnInput();
	uint32_t releaseMoment;


};

#endif /* KEYBOARDMATRIX_H_ */
