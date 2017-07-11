/*
 * KeyBoardMatrix.cpp
 *
 *  Created on: 2017Äê4ÔÂ15ÈÕ
 *      Author: zhangyu
 */

#include "KeyBoardMatrix.h"

KeyBoardMatrix::KeyBoardMatrix(const uint8_t* linePtr,const uint8_t* columnPtr,uint8_t lineNum,uint8_t columnNum)
{
	// TODO Auto-generated constructor stub
	this->columnNumber=columnNum;
	this->lineNumber=lineNum;
	for(uint8_t i=0;i<lineNum;i++)
	{
		this->linePin[i]=*(linePtr+i);
		pinMode(this->linePin[i],OUTPUT);
		digitalWrite(this->linePin[i],LOW);
	}
	for(uint8_t i=0;i<columnNum;i++)
	{
		this->columnPin[i]=*(columnPtr+i);
		pinMode(this->columnPin[i],INPUT_PULLUP);
	}
	this->keyPushed=0;
	this->lastKey=0;
	releaseMoment=0;
}
bool KeyBoardMatrix::keyHandler()
{
	uint8_t temp=0xff;
	uint8_t lineIndex=0xff;
	uint8_t columnIndex=0xff;

	temp=readColumnInput();

	if(temp==0xff)//no key be pushed
	{

		keyPushed=0;
		return 0;
	}
	else
	{
		keyPushed=1;
		releaseMoment=millis();
		for(uint8_t i=0;i<this->columnNumber;i++)
		{
			if((temp^(1<<i))==0xff)
			{
				columnIndex=i;

				break;
			}
		}
		if(columnIndex==0xff)//more than two column pushed, ignore
		{

		}
		else// lets get the line index
		{
			temp=readLineInput();
			for(uint8_t i=0;i<this->lineNumber;i++)
			{
				if((temp^(1<<i))==0xff)
				{
					lineIndex=i;

					break;
				}
			}
			if(lineIndex!=0xff)
			{
				this->lastKey=(lineIndex)*columnNumber+columnIndex+1;

			}
		}
	}

	return 1;
}
uint8_t KeyBoardMatrix::readLineInput()
{
	uint8_t temp=0xff;
	for(uint8_t i=0;i<this->lineNumber;i++)
	{
		pinMode(linePin[i],INPUT_PULLUP);
		if(this->lineNumber==this->columnNumber)
		{
			pinMode(columnPin[i],OUTPUT);
			digitalWrite(columnPin[i],LOW);
		}
	}
	if(this->lineNumber!=this->columnNumber)
	{
		for(uint8_t i=0;i<this->columnNumber;i++)
		{
			pinMode(columnPin[i],OUTPUT);
			digitalWrite(columnPin[i],LOW);
		}
	}
	for(uint8_t i=0;i<this->lineNumber;i++)
	{
		if(digitalRead(this->linePin[i])==0)
		{
			temp&=~(1<<i);
		}
	}
	return temp;
}
uint8_t KeyBoardMatrix::readColumnInput()
{
	uint8_t temp=0xff;
	for(uint8_t i=0;i<columnNumber;i++)
	{
		pinMode(columnPin[i],INPUT_PULLUP);
		if(lineNumber==columnNumber)
		{
			pinMode(linePin[i],OUTPUT);
			digitalWrite(linePin[i],LOW);
		}
	}
	if(lineNumber!=columnNumber)
	{
		for(uint8_t i=0;i<lineNumber;i++)
		{
			pinMode(linePin[i],OUTPUT);
			digitalWrite(linePin[i],LOW);
		}
	}
	for(uint8_t i=0;i<this->columnNumber;i++)
	{
		if(digitalRead(this->columnPin[i])==0)
		{
			temp&=~(1<<i);
		}
	}
	return temp;
}
uint8_t KeyBoardMatrix::getKey()
{
#ifdef DEBUG_KEYBOARD
				Serial.println(this->keyPushed);
#endif
	if(lastKey && keyPushed==0 &&(millis()-releaseMoment>100))//100ms debounce
	{
		uint8_t temp=lastKey;
		lastKey=0;
		return temp;
	}
	else
	{
		return 0;
	}
}
KeyBoardMatrix::~KeyBoardMatrix()
{
	// TODO Auto-generated destructor stub
}

