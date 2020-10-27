
#include "stm32f10x.h"

#define CONNECT_VER		"0002"

#define MODE_MASTER 0
#define MODE_SLAVE 	1

//#define GMT 3600 * 3	//Correcting time zone

#define LED_Port		GPIOC
#define LED_Pin			GPIO_Pin_13
#define Disp_RCK_Port	GPIOA
#define Disp_RCK_Pin	GPIO_Pin_6

#define LED1_Port		GPIOB
#define LED2_Port		GPIOB
#ifdef USE_DISPLAY_GR
#define LED1_Pin		GPIO_Pin_13
#define LED2_Pin		GPIO_Pin_13

#else
#define LED1_Pin		GPIO_Pin_0
#define LED2_Pin		GPIO_Pin_1
#endif

#define UNIT_ADDR	40	//My CAN ID


#define  ADDR_EX		0x03
#define  CAN_NUMBER_TX_MSG 2


#define CNT_PGN			0x18F743
#define CNT_Start 		0
#define CNT_Bit			32
#define CNT_timeout		5

#define VLV_PGN			0x18F710
#define VLV_Start		48
#define VLV_Bit			1
#define VLV_timeout		5

#define AIN_PGN			0x18F720
#define AIN_Start		0
#define AIN_Bit			16
#define AIN_timeout		5

#define Time_ADDR		0x01
#define Time_PGN		0x18F7F3
#define Time_Start		32
#define Time_Bit		32
#define Time_timeout	5


#define ADDR_CARD		6
#define CARD_PGN		0X18F703
#define CARD_Start		16
#define CARD_Bit		40
#define CARD_timeout	5

#define TPASS_DEFAULT	11111

typedef enum
{
    Display_Idle =0,
    Display_time,
    Display_start_refueling,
    Display_refueling,
    Display_end_refueling,
    Display_show_error,
	Display_slave_mode
}T_Dislpay_states;

typedef enum

{
	SysState_Idle =0,
	SysState_normal,
	SysState_refueling,
	SysState_emergency_refueling,
	SysState_stop,
	SysState_slave_mode
}T_system_states;


typedef struct
{
    uint8_t addr;
    uint32_t pgn;
    uint8_t start;
    uint8_t bit;
    uint16_t timeout;
}T_CAN_sensor;

typedef struct
{
	uint32_t PGN;
	u16 timeout;
	u8 enable;
	u8 dummy;
} T_CAN_static_TX_MSG;


typedef struct
__attribute__((packed))
{
	uint8_t 		MY_ADDR;
	uint16_t 		key;
    T_CAN_sensor 	CNT;
    T_CAN_sensor 	valve;
    T_CAN_sensor 	Ain;
    T_CAN_sensor 	Time;
    T_CAN_sensor 	CADR;
    T_CAN_sensor 	MASTER_Dispay;
    T_CAN_static_TX_MSG TX_MSG[CAN_NUMBER_TX_MSG];
    double			cnt_ratio;
    double 			cnt_pulses_per_litre;
    uint32_t 		cnt_EX_trim;	//start of pulses
    uint32_t 		cnt_start;	//start counter
    uint8_t 		mode;		//Master/Slave display mode
    uint8_t 		timezone;
    uint8_t			dummy[3];		//for aligning
    uint32_t 		TPASS;
    uint32_t 		crc;
} T_settings;

extern T_settings settings;



typedef struct
{
    uint8_t d[8];
    uint8_t txt[16];
    uint8_t index;
    uint8_t dot;
    uint8_t backlight;
    T_Dislpay_states State;
}T_display;

extern T_display Disp;


// (UnixTime = 00:00:00 01.01.1970 = JD0 = 2440588)
#define JULIAN_DATE_BASE    2440588


typedef struct
{
    uint8_t RTC_Hours;
    uint8_t RTC_Minutes;
    uint8_t RTC_Seconds;
    uint8_t RTC_Date;
    uint8_t RTC_Wday;
    uint8_t RTC_Month;
    uint16_t RTC_Year;
} RTC_DateTimeTypeDef;

extern u32 cnt;

typedef enum
{
	state_unknown =0,
	state_off,
	state_on
} T_Valve_state;

typedef struct
{
	uint32_t	G_CNT_EX;
	uint32_t	G_CNT_EX_start;
	uint32_t	G_CNT_EX_stop;

	uint32_t	Ain1,Ain2,Ain3;
	uint32_t	cnt_disp;
	uint8_t		CARD[5],display_d[8];

	T_Valve_state	valve_state,pump_state;
	uint32_t	time_TR;
	T_system_states state;
} T_data;

extern T_data data;

typedef struct
{
	uint32_t G_CNT_EX;
	uint32_t Ain1, Ain2, Ain3;
	uint8_t CARD[5],master_d[8];
	uint32_t time_TR;
	unsigned  valid_CNT :1, valid_AIN :1, valid_valve :1, valid_timer :1,valid_card:1, valid_master_disp:1;
	T_Valve_state valve_state,pump_state;
} T_data_IN;

typedef struct

{
	uint32_t pulses;
	T_Dislpay_states new_state;
}T_display_queue;





