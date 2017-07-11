/*
 * LaputaComm.h
 *
 *  Created on: 2015年3月17日
 *      Author: ZhangYu
 *      Need SoftwareSerial.h
 *      D2---->Rx
 *      D3---->Tx
 */

#ifndef LAPUTACOMMSW_H_
#define LAPUTACOMMSW_H_

#define SW_SERIAL

#include "Arduino.h"
//#include "EEPROM.h"
//#include <avr/wdt.h>
#include"SoftwareSerial.h"

//#define DEBUG

extern SoftwareSerial mySerial;
//extern HardwareSerial Serial;

typedef unsigned char 		Uint8;
typedef char 				Int8;
typedef unsigned int 		Uint16;
typedef int 				Int16;
typedef unsigned long		Uint32;
typedef long 				Int32;
typedef unsigned long long 	Uint64;
typedef long long 			Int64;
typedef void (*_Pfn)(void);
#define BUFFER_SIZE			(32)
//typedef enum
//{
//	STATE_IDLE,				//设备空闲
//	STATE_OP_WITHOUT_CMD,	//设备正在被操作，无需与其他设备联动
//	STATE_OP_WITH_CMD,		//设备正在被操作，需要与其他设备联动
//	STATE_DONE,				//玩家操作成功，需激活下一个设备
//	STATE_LATCH,			//玩家操作失误，设备锁定，需其他触发条件解锁
//};
typedef enum
{
	STATUS_OK,
	STATUS_WRONG_CHKSUM,
	STATUS_UNSUPPORT_CMD,
	STATUS_WRONG_DATA_LEN,
}ACK_STATUS;
// supported CMD
typedef enum
{
	/*0x00*/
	COMMON_CMD_READ_STATE,		//读取从机当前状态
	COMMON_CMD_READ_STATE_SUB_1,
	COMMON_CMD_READ_STATE_SUB_2,
	/*0xF0*/
	COMMON_CMD_GOTO_BOOTLOADER=0xF0,//jump to boot loader
	/*0xF1*/
	COMMON_CMD_INIT_ME,		//Back to initial state
	/*0xF2*/
	COMMON_CMD_RESET_ME,//call a watch dog reset, a really reset.
	/*0xF3*/
	COMMON_CMD_CHANGE_ADDR,	//更改地址，包括主机均有效
}_CMD_LIST;

//typedef union
//{
//	Uint8 all;
//	struct
//	{
//		unsigned char isReceiving :1;
//		unsigned char isNeedProcess :1;
//		unsigned char isWaitingForACK :1;
//		unsigned char isStopAutoReporting :1;
//		unsigned char chksumWrong :1;
//		unsigned char getMassData :1;
//		unsigned char withoutChksum :1;
//		unsigned char rsvd7 :1;
//	} bit;
//} FLAG_COMM;
typedef enum
{
	Frame_Header1,
	Frame_Header2,
	Frame_Address,
	Frame_CMD,
	Frame_Length,
	Frame_data0,
	Frame_data1,
}FRAME_STRUCT;
typedef union
{
	Uint8 bytes[BUFFER_SIZE];
	struct
	{
		Uint8 header1;
		Uint8 header2;
		Uint8 address;
		Uint8 err_status;
		Uint8 length;
		Uint8 content[BUFFER_SIZE-5];
	}bit;
}STRUCT_TX;
typedef union
{
	Uint8 bytes[BUFFER_SIZE];
	struct
	{
		Uint8 header1;
		Uint8 header2;
		Uint8 address;
		Uint8 cmd;
		Uint8 length;
		Uint8 content[BUFFER_SIZE-5];
	}bit;
}STRUCT_RX;
class LaputaComm
{
public:
	Uint8 address;
	Uint8 state;
	Uint8 state_sub_1;
	Uint8 state_sub_2;
	Uint8 rx_ptr;
	LaputaComm(Uint8 addr);
	Uint8 begin(Uint8 room_addr,Int32 BDR,Uint8 setPin=4);
	Uint8 begin(Int32 BDR);
	Uint8 rxBuffer[BUFFER_SIZE];
	STRUCT_TX txBuffer;
	//发送相关的命令
	void sendCMD();
	//接收相关的命令
	bool receiveCMD();	//当串口缓冲区有未处理的数据时，调用此函数
	void cmd_ACK(Uint8 status);
//	bool isNeedProcessing(void);	//是否有待处理的命令？
	virtual ~LaputaComm();

private:
	Uint8 calc_chksum(Uint8 *ptr,Uint8 length);
	void read_handle(Uint8 data);
	Uint8 setPin;
	bool try_BDR(Int32 BDR,Int32 BDR_des, Uint8 ch);
//	bool cmdHandler();	//返回1时，说明需要操作
//	unsigned long receiveMoment;	//记录接收时刻
//	FLAG_COMM flag;
};
void resetMyself();

#endif /* LAPUTACOMM_H_ */
