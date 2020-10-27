#ifndef __CAN_H__
#define __CAN_H__

#include <stdint.h>

#if (USE_CAN_SUPPORT)

#define CAN_VALUES_SIZE		4


#define CAN_MSG_NUMBER	7	//Number of out message

enum CAN_SPEED {
	CAN_SPEED_100,
	CAN_SPEED_125,
	CAN_SPEED_250,
	CAN_SPEED_500,
	CAN_SPEED_1000
};


typedef struct
{
	u8 status;
	u8 msg_index;
	u8 msg_len;
	u8 char_len;
	u8 ID;
	u16 char_index;
	u8 * ptr;
	u32 startTick;
} T_CAN_SET_MSG;

extern T_CAN_SET_MSG CAN_set_msg;

typedef enum
{
 CAN_MSG_COUNTER_ON_Display = 0,
 CAN_MSG_STATISTIC,
 CAN_MSG_HW,
 CAN_MSG_TIMEUP,
 CAN_MSG_DEVID,
 CAN_MSG_Global_CNT,
 CAN_MSG_Data_on_display
} CAN_MSG_e;


struct CAN_MSG_s {
	u8	enable;
	CAN_MSG_e n;
	u32 PGN;
	u16	timeout;
};

typedef struct CAN_MSG_s CAN_MSG_t;

typedef struct
{
	uint32_t timeout;
	uint8_t error;
}T_CAN_TX_MSG;


typedef struct
{
	T_CAN_TX_MSG CAN[CAN_MSG_NUMBER];
}T_CAN_TX;


#define CAN_SET_HEDLINE_PGN		0x18EC00
#define CAN_SET_PGN				0x18EB00
#define CAN_SET_TIMEOUT			5000

//----------------------------------------------------------------------------------------------------

u8 CAN_send_msg (u8 num);
void vCanTask(void *pvArg);
extern void vCanTask(void *pvArg);
//double CanSumGet(int index);
//void  CanSumInit(void);
//extern uint8_t CanEnable;
//extern uint8_t CanDisabled;


#endif
#endif
