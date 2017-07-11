/*
 * LaputaComm.cpp
 *
 *  Created on: 2015Äê3ÔÂ17ÈÕ
 *      Author: ZhangYu
 */
#define SERIAL_MAIN (1)
#include "LaputaCommSWV2.h"

SoftwareSerial mySerial(2,3);

LaputaComm::LaputaComm(unsigned char addr)
{
	// TODO Auto-generated constructor stub
	this->address=addr;
	this->state=0;
	this->state_sub_1=0;
	this->state_sub_2=0;
	memset(this->rxBuffer,0,sizeof(this->rxBuffer));
	memset((Uint8 *)&this->txBuffer,0,sizeof(this->txBuffer));
	this->txBuffer.bit.header1=0xab;
	this->txBuffer.bit.header2=0xcd;
	this->txBuffer.bit.address=addr;
	this->rx_ptr=0;
	this->setPin=4;
}
Uint8 LaputaComm::calc_chksum(Uint8 *ptr,Uint8 length)
{
	Uint8 checksum=0;
	for(unsigned i=0;i<length;i++)
	{
		checksum+=*(ptr+i);
	}
	return checksum;
}
bool LaputaComm::try_BDR(Int32 BDR,Int32 BDR_des, Uint8 ch)
{
	mySerial.begin(BDR);
	mySerial.println("AT+FU3");
	delay(100);
	if(mySerial.available())
	{
		if(mySerial.read()=='O' && mySerial.read()=='K')
		{
			mySerial.print("AT+C");
			if(ch<=9)
			{
				mySerial.print("00");
			}
			else
			{
				mySerial.print("0");
			}
			mySerial.println(ch);
			delay(100);
			mySerial.print("AT+B");
			mySerial.println(BDR_des);
			delay(100);
			mySerial.begin(BDR_des);
			return 0;
		}
		else
		{
			return 1;
		}
	}
	return 1;
}
Uint8 LaputaComm::begin(Uint8 room_addr,Int32 BDR,Uint8 setPin)
{
	pinMode(setPin,OUTPUT);
	digitalWrite(setPin,LOW);
	delay(100);
	mySerial.begin(BDR);
	mySerial.println("AT+FU3");
	delay(100);
	if(mySerial.available())
	{
		if(mySerial.read()=='O' && mySerial.read()=='K')
		{
			mySerial.print("AT+C");
			if(room_addr<=9)
			{
				mySerial.print("00");
			}
			else
			{
				mySerial.print("0");
			}
			mySerial.println(room_addr);
			delay(100);
			pinMode(setPin,INPUT_PULLUP);
			return 0;
		}
		else
		{
			return 1;
		}
	}

	if(this->try_BDR(9600, BDR, room_addr))
	{
		if(this->try_BDR(19200, BDR, room_addr))
		{
			if(this->try_BDR(38400, BDR, room_addr))
			{
				if(this->try_BDR(57600, BDR, room_addr))
				{
					if(this->try_BDR(115200, BDR, room_addr))
					{
						pinMode(setPin,INPUT_PULLUP);
						return 2;
					}
					else
					{
						goto normal_return;
					}
				}
				else
				{
					goto normal_return;
				}
			}
			else
			{
				goto normal_return;
			}
		}
		else
		{
			goto normal_return;
		}
	}
	else
	{

		goto normal_return;
	}
	pinMode(setPin,INPUT_PULLUP);
	return 3;
normal_return:
	mySerial.flush();
	pinMode(setPin,INPUT_PULLUP);
	return 0;
}
Uint8 LaputaComm::begin(Int32 BDR)
{
	mySerial.begin(BDR);
	return 0;
}
void LaputaComm::sendCMD()
{
	this->txBuffer.bit.address=this->address;
	if(this->txBuffer.bit.length<=BUFFER_SIZE-6)
	{
		this->txBuffer.bit.content[this->txBuffer.bit.length]=this->calc_chksum((Uint8 *)&this->txBuffer.bit.address, this->txBuffer.bit.length+3);
		mySerial.write((const char*)&this->txBuffer, this->txBuffer.bit.length+6);
	}
	delay(10);
}
bool LaputaComm::receiveCMD()
{
	Uint8 checksum = 0;

	//if there is sth, delay 10ms for receive all bytes
	if (mySerial.available() > 0)
	{
#ifdef DEBUG
		Serial.println("status 1");
#endif
		delay(10);
	}
	else
		return 0;
	//check the start byte 0xAA
	do
	{
		this->rxBuffer[0]=mySerial.read();
#ifdef DEBUG
		Serial.println(this->rxBuffer[0]);
#endif
		if(mySerial.available()==0)
		{
			return 0;
#ifdef DEBUG
		Serial.println("status 4");
#endif
		}
	}
	while(this->rxBuffer[0]!=0xAB);
#ifdef DEBUG
		Serial.println("status 2");
#endif
	//OK, we get a 0xAB, if the next byte count less than 3, must be an error info, flush it
	this->rxBuffer[1]=mySerial.read();
	if(mySerial.available()<3 || this->rxBuffer[1]!=0xCD)
	{
		mySerial.flush();
		return 0;
	}
#ifdef DEBUG
		Serial.println("status 3");
#endif
	//long than 3, save them
	this->rx_ptr=Frame_Address;
	while(mySerial.available() > 0)
	{
		this->rxBuffer[this->rx_ptr]=mySerial.read();
		this->rx_ptr++;
		if(rx_ptr>=BUFFER_SIZE)
		{
			mySerial.flush();
			break;
		}
	}
	//check the address
	if(this->rxBuffer[Frame_Address]!=this->address)
	{
		this->rx_ptr=0;
		return 0;
	}
	//more than 4 bytes, must a write CMD, need to check if we  have already finished the receiving
	if(this->rx_ptr>5)
	{
		//long than 16 bytes, an error length
		if(this->rxBuffer[Frame_Length]>0x10)
		{
			this->rx_ptr=0;
			this->cmd_ACK(STATUS_WRONG_DATA_LEN);
			return 0;
		}
		// we did not receive all the bytes, need another 10 ms
		else if(this->rxBuffer[Frame_Length]>this->rx_ptr-6)
		{
			delay(10);
			while(mySerial.available() > 0)
			{
				this->rxBuffer[this->rx_ptr]=mySerial.read();
				this->rx_ptr++;
			}
			//still not receive all
			if(this->rxBuffer[Frame_Length]>this->rx_ptr-6)
			{
				this->rx_ptr=0;
				this->cmd_ACK(STATUS_WRONG_DATA_LEN);
				return 0;
			}
		}
	}
	//check the checksum
	checksum=this->calc_chksum(&rxBuffer[Frame_Address], this->rx_ptr-3);
	if(checksum!=rxBuffer[this->rx_ptr-1])
	{
		this->rx_ptr=0;
		this->cmd_ACK(STATUS_WRONG_CHKSUM);
		return 0;
	}
	switch(this->rxBuffer[Frame_CMD])
	{
//	case COMMON_CMD_READ_STATE:
//		this->read_handle(this->state);
//		return 0;
//	case COMMON_CMD_READ_STATE_SUB_1:
//		this->read_handle(this->state_sub_1);
//		return 0;
//	case COMMON_CMD_READ_STATE_SUB_2:
//		this->read_handle(this->state_sub_2);
//		return 0;
	case COMMON_CMD_GOTO_BOOTLOADER:
		this->cmd_ACK(STATUS_OK);
		delay(10);
		asm("JMP 15872 ");
		return 0;
	case COMMON_CMD_INIT_ME:
		this->cmd_ACK(STATUS_OK);
		delay(10);
		resetMyself();
		return 0;
	case COMMON_CMD_CHANGE_ADDR:
	case COMMON_CMD_RESET_ME:
		this->cmd_ACK(STATUS_UNSUPPORT_CMD);
		return 0;
	default:
		this->txBuffer.bit.err_status=STATUS_OK;
		return 1;
	}
	this->txBuffer.bit.err_status=STATUS_OK;
	return 1;
}

void LaputaComm::read_handle(Uint8 data)
{
	this->txBuffer.bit.err_status=STATUS_OK;
	this->txBuffer.bit.length=1;
	this->txBuffer.bit.content[0]=data;
	this->sendCMD();
}

void LaputaComm::cmd_ACK(Uint8 status)
{
	this->txBuffer.bit.err_status=status;
	this->txBuffer.bit.length=0;
	this->sendCMD();
}

LaputaComm::~LaputaComm()
{
// TODO Auto-generated destructor stub
}

