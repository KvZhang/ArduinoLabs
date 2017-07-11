/*
 * LaputaCardReader.cpp
 *
 *  Created on: 2017Äê3ÔÂ11ÈÕ
 *      Author: zhangyu
 */

#include "LaputaCardReader.h"

LaputaCardReader::LaputaCardReader() {
	// TODO Auto-generated constructor stub
	reader=NULL;
	memset(&this->last_uid,0,sizeof(this->last_uid));
	memset(&this->content,0xff,sizeof(this->content));
	this->flag.all=0;
	memset(&this->key,0xff,sizeof(this->key));
	this->last_occurred_moment=0;
	this->repeat_times=0;
}

bool LaputaCardReader::check_uid()
{
	if(this->reader->uid.size>10)
	{
		return 0;
	}
	for(unsigned char i=0;i<this->reader->uid.size;i++)
	{
		if(this->last_uid.uidByte[i]!=this->reader->uid.uidByte[i])
		{
			return 0;
		}
	}
	return 1;
}
unsigned char LaputaCardReader::readCard()
{
	byte status=0;
	uint8_t address = sizeof(this->content);
	if(this->reader==NULL)
	{
		status = 1;
		goto the_end;
	}

	if (!this->reader->PICC_IsNewCardPresent())
	{
		if(this->last_occurred_moment&&(millis()-this->last_occurred_moment>1000))
		{
			this->flag.all=0;
			this->last_occurred_moment=0;
			this->repeat_times=0;
			memset(&this->last_uid,0,sizeof(this->last_uid));
		}
		status = 2;
		goto the_end;
	}

	if (!this->reader->PICC_ReadCardSerial ())
	{
		status = 3;
		goto the_end;
	}
	else
	{
		if(this->check_uid())// same UID could return, and didn't process the cmd
		{
			this->flag.bit.card_not_removed=1;
			this->repeat_times++;
			this->flag.bit.is_new_card_found=0;
			status = 6;
		}
		else
		{
			this->repeat_times=0;
			this->flag.bit.is_new_card_found=1;
			this->last_occurred_moment=millis();
			memcpy(&this->last_uid,&this->reader->uid,sizeof(this->last_uid));
		}
	}

	if (this->reader->PCD_Authenticate (MFRC522::PICC_CMD_MF_AUTH_KEY_A,
            READ_BLOCK, &this->key, &(this->reader->uid)) != MFRC522::STATUS_OK)
	{
		status = 4;
		goto next;
	}

	if(status==6)
	{
		goto next;
	}

	if (this->reader->MIFARE_Read (READ_BLOCK, (unsigned char *)&this->content,
            &address) != MFRC522::STATUS_OK)
	{
		status = 5;
		goto next;
	}
	else
	{
		this->flag.bit.cmd_found=1;
	}

next:
	this->reader->PCD_StopCrypto1 ();  // Stop encryption on PCD
	this->reader->PICC_HaltA (); // Halt PICC
the_end:
	return status;
}

LaputaCardReader::~LaputaCardReader() {
	// TODO Auto-generated destructor stub
}

