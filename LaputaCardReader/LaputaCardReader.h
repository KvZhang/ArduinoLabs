/*
 * LaputaCardReader.h
 *
 *  Created on: 2017年3月11日
 *      Author: zhangyu
 */

#ifndef LAPUTACARDREADER_H_
#define LAPUTACARDREADER_H_

#include"MFRC522.h"

typedef enum{
	READ_BLOCK=5,
	WRITE_BLOCK=6,
} _RC522_BLOCK;
//RC522 read buffer
typedef union{
	struct{
		unsigned char cardNumber;
		unsigned char cardType;
		unsigned char cardColour;
		unsigned char cardCmd;
		unsigned char totleLifes;//本卡可刷卡次数
		unsigned char activeTimes;//激活时长等级
		unsigned char rsv[14];
	}fields;
	unsigned char BYTES[20];
}_RC522_READ_BUFFER;
//RC522 write buffer
typedef union{
	struct{
		unsigned char remainLifes;
		unsigned int  gameStartMoment;
		unsigned char rsv[17];
	}fields;
	unsigned char BYTES[20];
}_RC522_WRITE_BUFFER;
//Card type
typedef enum{
	CARD_TYPE_PRIMARY_PLAYER,
	CARD_TYPE_NORMAL_PLAYER,
	CARD_TYPE_SENIOR_PLAYER,
	CARD_TYPE_SUPER_PLAYER,
	CARD_TYPE_GAME_MASTER,
	CARD_TYPE_ADMIN,
	CARD_TYPE_ROOM_1,
	CARD_TYPE_ROOM_2,
	CARD_TYPE_ROOM_3,
	CARD_TYPE_ROOM_4,
	CARD_TYPE_ROOM_5,
	CARD_TYPE_ROOM_6,
	CARD_TYPE_ROOM_7,
	CARD_TYPE_ROOM_8,
	CARD_TYPE_TOOLS,
}_CARD_TYPE;
//Card color
typedef enum{
	CARD_COLOR_RED,
	CARD_COLOR_YELLOW,
	CARD_COLOR_BLUE,
	CARD_COLOR_GREEN,
	CARD_COLOR_WHITE,
	CARD_COLOR_BLACK,
}_CARD_COLOUR;
//Card command
typedef enum{
	CARD_CMD_RESET_ME,
	CARD_CMD_RESET_ALL,
	CARD_CMD_OPEN_DOOR,
}_CARD_CMD;
typedef union
{
	unsigned char all;
	struct
	{
		unsigned char is_new_card_found:1;
		unsigned char card_not_removed:1;
		unsigned char cmd_found:1;
		unsigned char rsv:5;
	}bit;
}RC522_FLAG;
class LaputaCardReader {
public:
	MFRC522::Uid last_uid;
	unsigned long last_occurred_moment;
	uint8_t repeat_times;
	LaputaCardReader();
	MFRC522::MIFARE_Key key;
	MFRC522 *reader;
	_RC522_READ_BUFFER content;
	RC522_FLAG flag;
	unsigned char readCard();
	bool check_uid();
	virtual ~LaputaCardReader();
};
#endif /* LAPUTACARDREADER_H_ */
