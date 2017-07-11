/*
 * LaputaTelephone.h
 *
 *  Created on: 2017Äê4ÔÂ23ÈÕ
 *      Author: zhangyu
 */

#ifndef LAPUTATELEPHONE_H_
#define LAPUTATELEPHONE_H_

#include"Arduino.h"
#include"LaputaMp3.h"

#define MAX_NUM_LENGTH (10)
#define MAX_RIGHT_ANSWER_COUNT (5)

extern LaputaMp3 myMp3;

typedef union{
	unsigned char all;
	struct{
		unsigned char answer_right:1;
		unsigned char time_out:1;
		unsigned char bit2:1;
		unsigned char bit3:1;
		unsigned char bit4:1;
		unsigned char bit5:1;
		unsigned char bit6:1;
		unsigned char bit7:1;
	}bit;
}TELE_FLAG;

typedef enum
{
	Phone_picked_up,
	Phone_hang_out,
};

typedef enum
{
	song_idle=1,
	song_buzy,
	song_wrong_number,
	song_dialing,
	song_ringing,
	song_voice_0,
	song_voice_right,
	song_voice_1=8,
	song_voice_2,
	song_voice_3,
	song_voice_4,
};

typedef enum
{
	Status_phone_idle,
	Status_phone_pick_up,
	Status_phone_dialing,
	Status_phone_dialed,
	Status_phone_wait_for_end
}PHONE_STATUS;

typedef struct
{
	uint8_t* ptr;
	uint8_t len;
}STRUCT_PHONE_NUM;

class LaputaTelephone
{
public:
	LaputaTelephone(uint8_t hold_pin,uint8_t dial_pin,uint8_t num_pin,uint8_t speaker_pin);
	uint8_t read_status(void);
	uint8_t get_length();
	void set_right_num(uint8_t *ptr,uint8_t len, uint8_t n);
	void handler();
	uint8_t num[MAX_NUM_LENGTH];
	uint8_t check_answer();
	void force_to_ring(bool flag);
	virtual ~LaputaTelephone();
	TELE_FLAG flag;
private:
	uint8_t ptr;
	void status_idle();
	void status_pick_up();
	void status_dialing();
	void status_dialed();
	void status_wait_for_end();
	uint8_t force_ring;
	uint8_t hold_pin;
	uint8_t dial_pin;
	uint8_t num_pin;
	uint8_t speaker_pin;
	uint8_t status;
	uint32_t counter;

	STRUCT_PHONE_NUM right_num[MAX_RIGHT_ANSWER_COUNT];
};

#endif /* LAPUTATELEPHONE_H_ */
