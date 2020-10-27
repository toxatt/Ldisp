#include "hardware.h"
#include "FreeRTOS.h"
#include "queue.h"
#include "semphr.h"
#include "task.h"
#include "can.h"
#include "debug.h"
#include "main.h"
#include "string.h"
#include "timers.h"
#include  "stddef.h"
#include "stdio.h"
#include "stdlib.h"
#include "cmd.h"

#if (USE_CAN_SUPPORT)

//#define  CAN_RX1_IRQHandler


#define CAN_RX_QUEUE_SIZE		8
#define CAN_TX_QUEUE_SIZE		4
//
//#define CAN_MODE_ENGINE_COOLANT	0
//#define CAN_MODE_ENGINE_RPM		1
//#define CAN_MODE_VEHICLE_SPEED	2
//#define CAN_MODE_MAF_SENSOR		3
//#define CAN_MODE_THROTTLE		4
//#define CAN_MODE_O2_VOLTAGE		5
//#define CAN_MODE_VIN_COUNT		6
//#define CAN_MODE_VIN_DATA		7
//#define CAN_MODE_FUELLEVEL		8
//#define CAN_MODE_DTC			9
//#define CAN_MODE_LAST			10

//-------------------------------------------------
#define CAN_SENSORS				6

#define CAN_SENSOR_CNT 			1
#define CAN_SENSOR_valve		2
#define CAN_SENSOR_Ain			3
#define CAN_SENSOR_Time			4
#define CAN_SENSOR_CARD			5
#define CAN_SENSOR_Master		6
//------------------------------------------------

//-------------------------------------------- Output messages  ------------------------


//
//#define CAN_MSG_COUNTER_ON_Display	0
//#define CAN_MSG_STATISTIC				1
//#define CAN_MSG_HW					2
//#define CAN_MSG_TIMEUP				3
//#define CAN_MSG_DEVID					4
//#define CAN_MSG_Global_CNT			5
//#define CAN_MSG_Data_on_display		6

const CAN_MSG_t CAN_msg_map[]=
{
	//  #	  message PGN	timeout *100ms
		{1,	CAN_MSG_COUNTER_ON_Display,		0x18F743,	10},
		{1, CAN_MSG_STATISTIC,				0x18F740,	10},
		{1, CAN_MSG_HW,						0x18F713,	50},	//
		{1, CAN_MSG_TIMEUP,					0x18F712,	50},
		{1, CAN_MSG_DEVID,					0x18F711,	50},
		{1, CAN_MSG_Global_CNT,				0x18F744,	10},
		{1, CAN_MSG_Data_on_display,		0x18F745,	5}
};



//volatile uint8_t canMode;
xQueueHandle CanRxQueue;
xQueueHandle CanTxQueue;
xTimerHandle CanTxTimer;

CanTxMsg TxMessage;
CanRxMsg RxMessage;

#define CAN_SET_BUF_SIZE	600

u8 CAN_set_RX_buffer[CAN_SET_BUF_SIZE];
u8 CAN_set_TX_buffer[CAN_SET_BUF_SIZE];

T_CAN_TX CAN_TX;

T_CAN_SET_MSG CAN_set_msg, CAN_set_answer;

extern xQueueHandle Data_out_cnt;
extern xQueueHandle Data_out_G_cnt;
extern xQueueHandle Data_out_display;


typedef struct
{
	uint32_t ExtId;
	uint32_t timeout;
	uint64_t data;
	uint64_t previous_data;
	uint8_t valid;
} SensData_t;

typedef struct CanData_s
{
	SensData_t CAN[CAN_SENSORS];	//data
}CanData_t;

CanData_t CanData;

uint32_t CAN_SENS_RX_Timeout [CAN_SENSORS+1];


void CAN_send_Timer(xTimerHandle xTimer);
void CAN_set_Deinit(T_CAN_SET_MSG * x);
void CAN_set_RX_Init(T_CAN_SET_MSG * x);
void CAN_set_answer_Init(T_CAN_SET_MSG * v,T_CAN_SET_MSG * x ,u8 * buf);


/*******************************************************************************
* Function Name	:	CanSum...
* Description	:
*******************************************************************************/
//uint8_t CanEnable;
//uint8_t CanDisabled;
//
//void CanSumInit(void)
//{
//	int i;
//	for(i = 0; i < CAN_VALUES_SIZE; i++)
//	{
//		CanValues[i].count = 0;
//		CanValues[i].sum = 0;
//	}
//}
//
//void CanSumAdd(int index, double value)
//{
//	CanValues[index].count++;
//	CanValues[index].sum += value;
//}
//
//double CanSumGet(int index)
//{
//	double value = 0;
//	if (CanValues[index].count > 0)
//		value = CanValues[index].sum / CanValues[index].count;
//	return value;
//}

/*******************************************************************************
* Function Name	:	CanInit
* Description	:	Initialize CAN interface
*******************************************************************************/
void CanInit(u8 CANSpeed)
{
	CAN_InitTypeDef			can_init;
	CAN_FilterInitTypeDef	can_filter_init;

	CAN_ITConfig(CAN_CAN, CAN_IT_FMP0, DISABLE);
	CAN_DeInit(CAN_CAN);

	CAN_StructInit(&can_init);


	can_init.CAN_NART = ENABLE;
	can_init.CAN_ABOM = DISABLE;
	can_init.CAN_RFLM = DISABLE;
	can_init.CAN_Mode = CAN_Mode_Normal;
#if   defined( STM32F10X_HD )	// 72 MHz	(CAN 36MHz)
	can_init.CAN_SJW = CAN_SJW_3tq;
	can_init.CAN_BS1 = CAN_BS1_12tq;
	can_init.CAN_BS2 = CAN_BS2_5tq;
#elif defined ( STM32F2XX )		// 120 MHz	(CAN 30MHz)
	can_init.CAN_SJW = CAN_SJW_1tq;
	can_init.CAN_BS1 = CAN_BS1_6tq;
	can_init.CAN_BS2 = CAN_BS2_8tq;
#elif defined ( STM32F10X_MD )		// 72 MHz	(CAN 36MHz)
	can_init.CAN_SJW = CAN_SJW_1tq;
	can_init.CAN_BS1 = CAN_BS1_13tq;//CAN_BS1_6tq;
	can_init.CAN_BS2 = CAN_BS2_2tq;//CAN_BS2_8tq;
#else
	#error "CPU not define"
#endif

//	if (CANSpeed == CAN_SPEED_1000)
//		can_init.CAN_Prescaler = 2;
//	else if (CANSpeed == CAN_SPEED_500)
//		can_init.CAN_Prescaler = 4;
//	else if (CANSpeed == CAN_SPEED_250)
//		can_init.CAN_Prescaler = 8;
//	else if (CANSpeed == CAN_SPEED_125)
//		can_init.CAN_Prescaler = 16;
//	else	// if (CANSpeed == CAN_SPEED_100)
//		can_init.CAN_Prescaler = 22;
	can_init.CAN_Prescaler = 9;
	CAN_Init(CAN_CAN, &can_init);

	can_filter_init.CAN_FilterNumber			= 0;
	can_filter_init.CAN_FilterMode				= CAN_FilterMode_IdMask;
	can_filter_init.CAN_FilterScale				= CAN_FilterScale_32bit;
	can_filter_init.CAN_FilterIdHigh			= 0;//(((u32)PID_REPLY << 21) & 0xFFFF0000) >> 16;
	can_filter_init.CAN_FilterIdLow				= 0;//(((u32)PID_REPLY << 21) | CAN_ID_STD | CAN_RTR_DATA) & 0xFFFF;
	can_filter_init.CAN_FilterMaskIdHigh		= 0;//0xFFFF;
	can_filter_init.CAN_FilterMaskIdLow			= 0;//0xFFFF;
	can_filter_init.CAN_FilterFIFOAssignment		= 0;
	can_filter_init.CAN_FilterActivation			= ENABLE;

	CAN_FilterInit(&can_filter_init);
	CAN_ITConfig(CAN_CAN, CAN_IT_FMP0, ENABLE);
	NVIC_SetPriority(USB_LP_CAN1_RX0_IRQn ,15);	//what priority we need? who know...
	NVIC_EnableIRQ(USB_LP_CAN1_RX0_IRQn);
	//NVIC_SetPriority (CAN_RX0_IRQn, 1);

}

/*******************************************************************************
* Function Name		:	OBDMessage
* Description		:	Prepare OBD message
* Return			:	pointer to message
*******************************************************************************/
CanTxMsg* PrepareMessage(CanTxMsg* msg, u8 mode, u8 pid_code)
{
	//msg->StdId		= PID_REQUEST;
	msg->ExtId		= 0;
	msg->RTR		= CAN_RTR_DATA;
	msg->IDE		= CAN_ID_STD;
	msg->DLC		= 8;
	msg->Data[0]	= 0x02;
	msg->Data[1]	= mode;
	msg->Data[2]	= pid_code;
	msg->Data[3]	= 0;
	msg->Data[4]	= 0;
	msg->Data[5]	= 0;
	msg->Data[6]	= 0;
	return msg;
}


/*******************************************************************************
* Function Name		:	S6BUSMessgae
* Description		:	Prepare S6bus message
* Return			:	pointer to message
*******************************************************************************/
CanTxMsg* PrepareMessage_S6(CanTxMsg* msg, u32 PGN, u8 ID, u8 * data)
{

	msg->ExtId		= (PGN<<8 | ID);
	msg->RTR		= CAN_RTR_DATA;
	msg->IDE		= CAN_ID_EXT;
	msg->DLC		= 8;
	memcpy(msg->Data,data,8);

	return msg;
}




u8 IsCanRxAvailable(void)
{
	if (uxQueueMessagesWaiting(CanRxQueue) != 0)
		return 1;
	return 0;
}

#if ( USE_DEBUG )
void PrintCanMsg(CanTxMsg *msg)
{
	printf("StdId: %4X\n", msg->StdId);
	printf("ExtId: %4X\n", msg->ExtId);
	printf("  IDE: %4X\n", msg->IDE);
	printf("  RTR: %4X\n", msg->RTR);
	printf("  DLC: %d\n", msg->DLC);
	printf(" Data: %2X %2X %2X %2X %2X %2X %2X %2X\n",
		msg->Data[0],
		msg->Data[1],
		msg->Data[2],
		msg->Data[3],
		msg->Data[4],
		msg->Data[5],
		msg->Data[6],
		msg->Data[7]
		);
}

void PrintCanMsgTx(CanTxMsg *msg)
{
	DebugPutLineln("---------------");
	DebugPutLineln("TX Message:");
	PrintCanMsg((CanTxMsg *)msg);
}

void PrintCanMsgRx(CanRxMsg *msg)
{
	DebugPutLineln("---------------");
	DebugPutLineln("RX Message:");
	PrintCanMsg((CanTxMsg *)msg);
	// printf("  FMI: %X\n", msg->FMI);
}
#else
	#define PrintCanMsg(x)
	#define PrintCanMsgTx(x)
	#define PrintCanMsgRx(x)
#endif

/*******************************************************************************
* Function Name	:	ObdSend
* Description		:	Initialize hardware
* Return			:	mailbox number or CAN_NO_MB if no free mailbox
*******************************************************************************/
u8 SendRequest(u8 mode, u8 pid_code)
{
	PrepareMessage(&TxMessage, mode, pid_code);	// Build package
	PrintCanMsgTx(&TxMessage);
	return CAN_Transmit(CAN_CAN, &TxMessage);
}

/*******************************************************************************
* Function Name		:	Send Data to CAN BUS
* Description		:	Initialize hardware
* Return			:	mailbox number or CAN_NO_MB if no free mailbox
*******************************************************************************/
u8 Send_S6(u32 PGN, u8 * data)
{
	PrepareMessage_S6(&TxMessage, PGN,settings.MY_ADDR, data);	// Build package
	PrintCanMsgTx(&TxMessage);
	return CAN_Transmit(CAN_CAN, &TxMessage);
}



double Get_D(uint32_t * x)
{
	return *((double *) x);
}

/*******************************************************************************
* Function Name	:	vCanTask
* Description	:	CAN Task
*******************************************************************************/
void vCanTask(void *args)
{
	//__IO u32 canModeSave;
	__IO u8 can_rx_addr=0;
	__IO u32 can_rx_PGN;
	__IO u32 Err_CAN_count = 0;
	__IO u32 tick;
	__IO u32 i;

	T_data_IN IN_CAN;


	/* Here the queue handle is extern. */
	extern xQueueHandle Data_IN_queue;

	DebugWaitConnect();
	DebugPutLine("CAN Initialize ... ");

	CanRxQueue = xQueueCreate(CAN_RX_QUEUE_SIZE, sizeof(CanRxMsg));

	if (CanRxQueue == NULL)
	{
		DebugPutLineln("Error");
		//ShowError(ERROR_CAN_TASK_FAIL);
		return;
	}
	CanTxQueue = xQueueCreate(CAN_TX_QUEUE_SIZE, sizeof(CanTxMsg));

	if (CanTxQueue == NULL)
	{
		DebugPutLineln("Error");
		//ShowError(ERROR_CAN_TASK_FAIL);
		return;
	}
	CanTxTimer = xTimerCreate("CAN TX",10,pdTRUE,0,CAN_send_Timer);
	xTimerReset(CanTxTimer,0);

	//DebugPutLineln("OK");
	
CAN_restart:
	Err_CAN_count = 0;
	CAN_set_Deinit(&CAN_set_msg);
	CAN_set_RX_Init(&CAN_set_msg);
	memset(&IN_CAN,0,sizeof(IN_CAN));

//	CanSumInit();

	for(;;)
	{

		CanInit(CAN_SPEED_250);

		vTaskDelay(50);
//		if ((can_last_mb = SendRequest(pid_mode, pid_request)) == CAN_NO_MB)
//		{	// Send package error (no mailbox)
//			//DebugPutLineln("No Tx Mailboxes");
//		//	ShowError(ERROR_CAN_TRANSMITE);
//			vTaskDelay(1000);
//			continue;
//		}

		//canModeSave = canMode;
		xTimerStart(CanTxTimer,5);
		while (1)//(canMode == canModeSave)
		{	// Repeat untill mode change or receive timeout
			if (xQueueReceive(CanRxQueue, &RxMessage, 10000) == pdPASS)
			{
				//	CAN message recieved, check it
				can_rx_addr = (RxMessage.ExtId & 0xFF);
				can_rx_PGN = RxMessage.ExtId >> 8;
				Err_CAN_count =0 ;
				if (can_rx_addr == settings.Ain.addr
						|| can_rx_addr == settings.CNT.addr
						|| can_rx_addr == settings.Time.addr
						|| can_rx_addr == settings.valve.addr
						|| can_rx_addr == settings.CADR.addr
						|| can_rx_addr == settings.MASTER_Dispay.addr)
				{
					//PrintCanMsgRx(&RxMessage);
					LED_Port->BRR = LED_Pin;
					tick = xTaskGetTickCount();
					tick /=100;
					CAN_SENS_RX_Timeout[0] = tick; //Current tick to index 0
					if (can_rx_PGN == settings.Ain.pgn && can_rx_addr == settings.Ain.addr)
					{
						//Analog parsing
						IN_CAN.Ain1 = ((RxMessage.Data[1]<<8) | RxMessage.Data[0]);
						IN_CAN.Ain2 = ((RxMessage.Data[3]<<8) | RxMessage.Data[2]);
						IN_CAN.Ain3 = ((RxMessage.Data[5]<<8) | RxMessage.Data[4]);
						CAN_SENS_RX_Timeout[CAN_SENSOR_Ain] = tick;
						IN_CAN.valid_AIN  = 1;

					};
						//-----------   Counter    --------------------------------------
					if (can_rx_PGN == settings.CNT.pgn && can_rx_addr == settings.CNT.addr)
					{
						IN_CAN.G_CNT_EX = RxMessage.Data[3]<<24 |  RxMessage.Data[2]<<16 |  RxMessage.Data[1]<<8 | RxMessage.Data[0];
						CAN_SENS_RX_Timeout[CAN_SENSOR_CNT] = tick;
						IN_CAN.valid_CNT = 1;
					};
						//---------------  Time  --------------------------------
						if (can_rx_PGN == settings.Time.pgn && can_rx_addr == settings.Time.addr)
					{
						IN_CAN.time_TR = RxMessage.Data[4] | RxMessage.Data[5]<<8 | RxMessage.Data[6] <<16 | RxMessage.Data[7]<<24;
						CAN_SENS_RX_Timeout[CAN_SENSOR_Time] = tick;
						IN_CAN.valid_timer = 1;
					};
						//------------------  Valve -----------------------------------
					if (can_rx_PGN == settings.valve.pgn && can_rx_addr == settings.valve.addr)
					{
						if((RxMessage.Data[1] ) !=0	)IN_CAN.pump_state = state_on; else IN_CAN.pump_state =state_off;
						if ((RxMessage.Data[6]) ==0	)IN_CAN.valve_state = state_on; else IN_CAN.valve_state = state_off;
						CAN_SENS_RX_Timeout[CAN_SENSOR_valve] = tick;
						IN_CAN.valid_valve = 1;
					}
					if (can_rx_PGN == settings.CADR.pgn && can_rx_addr == settings.CADR.addr)
					{
						//IN.CARD[0] = RxMessage.Data[2];
						memcpy(IN_CAN.CARD,&RxMessage.Data[2],5);
						IN_CAN.valid_card = 1;
						CAN_SENS_RX_Timeout[CAN_SENSOR_CARD] = tick;
					}

					if (can_rx_PGN == settings.MASTER_Dispay.pgn && can_rx_addr == settings.MASTER_Dispay.addr)
					{
						memcpy(IN_CAN.master_d,&RxMessage.Data[0],8);
						IN_CAN.valid_master_disp = 1;
						CAN_SENS_RX_Timeout[CAN_SENSOR_Master] = tick;
					}
				//	tick = xTaskGetTickCount();

					for (i=0;i<(CAN_SENSORS);i++)
						if ((CAN_SENS_RX_Timeout[0] > (CAN_SENS_RX_Timeout[i+1]) + 1000))
						{
							switch (i+1) {
								case CAN_SENSOR_Ain:
									IN_CAN.valid_AIN =0;
									break;
								case CAN_SENSOR_CARD:
									IN_CAN.valid_card =0;
									break;
								case CAN_SENSOR_CNT:
									IN_CAN.valid_CNT =0;
									break;
								case CAN_SENSOR_Time:
									IN_CAN.valid_timer =0;
									break;
								case CAN_SENSOR_valve:
									IN_CAN.valid_valve =0;
									break;
								case CAN_SENSOR_Master:
									IN_CAN.valid_master_disp =0;
									break;
								default:
									break;
							}
						};
					xQueueSend(Data_IN_queue,&IN_CAN,0);//Send data to main logic task
				}

				if (can_rx_PGN == CAN_SET_HEDLINE_PGN)
				{
					//new text message start
					if (CAN_set_msg.status ==0)	//idle state?
					{

						if (RxMessage.Data[0]==0x20
								&& RxMessage.Data[5]== settings.MY_ADDR
								&& RxMessage.Data[7] == 0xA8
								)
						{
							//start receive
							CAN_set_msg.status = 1;
							CAN_set_msg.ID = can_rx_addr;
							CAN_set_msg.char_len = RxMessage.Data[1] | (RxMessage.Data[2]<<8);
							CAN_set_msg.msg_len = RxMessage.Data[3]; //
							CAN_set_msg.startTick = xTaskGetTickCount();
						}
					}
				} else
					if (can_rx_PGN == CAN_SET_PGN)
					{
						//receive next line
						if (can_rx_addr == CAN_set_msg.ID)
						{
							if (RxMessage.Data[0]== 1+CAN_set_msg.msg_index++)
							{
								for (i=1;i<8;i++) if (RxMessage.Data[i] >= 0x02 && RxMessage.Data[i] <= 0x7F)
								{
									//add to buffer
									if (CAN_set_msg.char_index < CAN_SET_BUF_SIZE)
									*(CAN_set_msg.ptr+CAN_set_msg.char_index) = RxMessage.Data[i];
									CAN_set_msg.char_index++;
								};
								if (CAN_set_msg.status != 2
										&& CAN_set_msg.char_len <= CAN_set_msg.char_index)
								{
									//all receive
									CAN_set_msg.status = 2;
									*CAN_set_TX_buffer =0;
									CMD_Parsing(CAN_set_msg.ptr,CAN_set_TX_buffer,CAN_set_msg.ID);
									CAN_set_answer_Init(&CAN_set_msg,&CAN_set_answer,(u8*)CAN_set_TX_buffer);
									CAN_set_RX_Init(&CAN_set_msg);
									break;
								}
							} else
							{
								CAN_set_RX_Init(&CAN_set_msg);
								break;
							}
						}

					}
				if (CAN_set_msg.status == 1 && xTaskGetTickCount() > CAN_set_msg.startTick + CAN_SET_TIMEOUT) CAN_set_RX_Init(&CAN_set_msg);
			}
			else
			{
				if (Err_CAN_count++ > 20) goto CAN_restart;
				//No RX message in the queue
				//Maybe need to restart CAN
				//CAN_CancelTransmit(CAN_CAN, can_last_mb);

			}
		}
	}
}

void CAN_set_Deinit(T_CAN_SET_MSG * x)
{
	x->ID =0;
	x->char_index = 0;
	x->msg_index =0;
	x->char_len = 0;
	x->msg_len =0;
	x->startTick =0;
	x->ptr = NULL;
	x->status =0;
};

void CAN_set_RX_Init(T_CAN_SET_MSG * x )
{
	x->ID =0;
	x->char_index = 0;
	x->msg_index =0;
	x->char_len = 0;
	x->msg_len =0;
	x->startTick =0;
	x->ptr = & CAN_set_RX_buffer[0];
	x->status =0;
	memset(CAN_set_RX_buffer,0,CAN_SET_BUF_SIZE);
}

void CAN_set_answer_Init(T_CAN_SET_MSG * v, T_CAN_SET_MSG * x, u8 * buf) {
	u32 i, o = 0;

	x->char_index = 0;
	x->msg_index = 0;
	x->msg_len = 1;
	x->startTick = 0;
	x->ptr = &CAN_set_TX_buffer[0];
	x->char_len = strlen((char*) buf);
	if (x->char_len) {
		//memcpy((u8*)x->ptr,(u8*)buf,x->char_len);
		x->ID = v->ID;
		for (i = 0; i < x->char_len; i++) {
			*(x->ptr + i) = *(buf + i);
			if (++o > 6) {
				x->msg_len++;
				o = 0;
			}
		}
		x->status = 1;
	}

}




uint8_t PrepareData(uint8_t num,uint8_t * dt)
{
	uint32_t xx;
	uint8_t *ptr;
	switch (num)
	{
	case CAN_MSG_COUNTER_ON_Display:	//message 1
		if (settings.mode ==0)
		{
		if (pdPASS == xQueueReceive(Data_out_cnt,&xx,0))
		{
			ptr = (uint8_t*)&xx;
			memcpy(dt,ptr,4);
		}
		else
		dt[0] = 1;

		return 0;
		}
		else return 1;
		break;
	case CAN_MSG_STATISTIC:
		if (settings.mode ==0 )
			{
				dt[0] = data.state;
				return 0;
			}
		return 1;
		break;

	case CAN_MSG_HW:
		memcpy(dt,"LD01"CONNECT_VER,8);
		return 0;
		break;

	case CAN_MSG_TIMEUP:
		xx = xTaskGetTickCount()/1000;
		ptr = (uint8_t*)&xx;
		memcpy(dt,ptr,4);
		return 0;
		break;
	case CAN_MSG_Global_CNT:
		if (pdPASS == xQueueReceive(Data_out_G_cnt,&xx,0)
				&& settings.mode == 0)
		{
			ptr = (uint8_t*)&xx;
			memcpy(dt,ptr,4);
			return 0;
		}
		return 1;
		break;
	case CAN_MSG_Data_on_display:
			if (pdPASS == xQueueReceive(Data_out_display,&xx,0)
					&& settings.mode ==0)
			{
				ptr = (uint8_t*)&xx;
				memcpy(dt,ptr,8);
				return 0;
			}
			return 1;
			break;
	default:
		return 1;
		break;
	}
	return 1;
}
/**
 *
 */


u8 CAN_send_msg(u8 num)
{
	uint8_t data[8];
	uint8_t result;
	memset(&data,0,sizeof(data));
	result = PrepareData(num,(uint8_t*)&data);
	if (result == 0) Send_S6(CAN_msg_map[num].PGN,(u8*) &data);

	return 0;
}

/***********************************************************
 * 	RTOS program timer called once in 10ms
 ************************************************************/
void CAN_send_Timer(xTimerHandle xTimer) {
	u8 i, buf[8];
	static uint8_t dec;
//
//	for (i = 0; i < CAN_NUMBER_TX_MSG; i++)
//		if (settings.TX_MSG[i].enable != 0) {
//			if (CAN_TX.CAN[i].timeout > 0)
//				CAN_TX.CAN[i].timeout--;
//			else {
//				//TX
//				if (CAN_TX.CAN[i].timeout == 0) {
//					if (CAN_send_msg(i) == 0)	//send message to CAN bus
//							{
//						if (settings.TX_MSG[i].timeout < 2)
//							CAN_TX.CAN[i].timeout = 10;
//						else
//							CAN_TX.CAN[i].timeout = settings.TX_MSG[i].timeout;	// Update timeout variable if TX is OK
//					}
//				}
//			};
//		}


	if (dec++>=10)
	{
		dec =0;

	for (i = 0; i < CAN_MSG_NUMBER; i++)

		if (CAN_TX.CAN[i].timeout > 0)
			CAN_TX.CAN[i].timeout--;
		else {
			//TX
			if (CAN_msg_map[i].enable ==1 && CAN_TX.CAN[i].timeout == 0) {
				if ( CAN_send_msg(i) == 0)	//send message to CAN bus
						{
					if (CAN_msg_map[i].timeout < 2)
						CAN_TX.CAN[i].timeout = 10;
					else
						CAN_TX.CAN[i].timeout = CAN_msg_map[i].timeout;	// Update timeout variable if TX is OK
				}
			}
		}

	}

	//Transmit set message data to CAN

	if (CAN_set_answer.status == 1) {
		//send headline message
		CAN_set_answer.char_index =0;
		CAN_set_answer.msg_index =1;
		CAN_set_answer.status = 2;	//send packet

		buf[0] = 0x20;
		buf[1] = CAN_set_answer.char_len & 0xFF;
		buf[2] = ((CAN_set_answer.char_len>>8 )& 0xFF);
		buf[3] = CAN_set_answer.msg_len;
		buf[4] = 0xFF;
		buf[5] = CAN_set_answer.ID;
		buf[6] = 0x00;
		buf[7] = 0xA8;
		Send_S6(CAN_SET_HEDLINE_PGN,&buf[0]);

	} else if (CAN_set_answer.status == 2) {
		if (CAN_set_answer.msg_index <= CAN_set_answer.msg_len) {
			//send next
			buf[0] = CAN_set_answer.msg_index++;
		for (i=1;i<8;i++)
		{

			if (*(CAN_set_answer.ptr + CAN_set_answer.char_index) >= 0x0A
					&& *(CAN_set_answer.ptr + CAN_set_answer.char_index) < 0x7F
					&& CAN_set_answer.char_index <= CAN_set_answer.char_len)
			{
				buf[i] = *(CAN_set_answer.ptr + CAN_set_answer.char_index++);
			} else
				{
					buf[i] = 0xFF;
					CAN_set_answer.char_index++;
				}

		}
		Send_S6(CAN_SET_PGN,&buf[0]);
	} else {
		//all data are send
		CAN_set_answer.status = 3;
	}
}
}

CanRxMsg RxMessageISR;
//CanTxMsg TxMessageISR;

#ifdef CAN_RX0_IRQHandler
void CAN_RX0_IRQHandler(void)
{
	portBASE_TYPE canTaskSwitchNeed;
	CAN_Receive(CAN_CAN, CAN_FIFO0, &RxMessageISR);

	canTaskSwitchNeed = pdFALSE;
	xQueueSendFromISR(CanRxQueue, &RxMessageISR, &canTaskSwitchNeed);
	portEND_SWITCHING_ISR( canTaskSwitchNeed );
}
#endif

#ifdef CAN_RX1_IRQHandler
void CAN1_RX1_IRQHandler(void)
{
	portBASE_TYPE canTaskSwitchNeed;
	CAN_Receive(CAN_CAN, CAN_FIFO1, &RxMessageISR);

	portBASE_TYPE canRxTaskSwitchNeed = pdFALSE;
	xQueueSendFromISR(CanRxQueue, &RxMessageISR, &canTaskSwitchNeed);
	portEND_SWITCHING_ISR( canTaskSwitchNeed );
}
#endif

void USB_LP_CAN1_RX0_IRQHandler(void)
{
	portBASE_TYPE canTaskSwitchNeed;
	CAN_Receive(CAN_CAN, CAN_FIFO0, &RxMessageISR);
	CAN_ClearITPendingBit(CAN_CAN,CAN_IT_FMP0);
	portBASE_TYPE canRxTaskSwitchNeed = pdFALSE;
	xQueueSendFromISR(CanRxQueue, &RxMessageISR, &canTaskSwitchNeed);
	portEND_SWITCHING_ISR( canTaskSwitchNeed );
}

#ifdef CAN_TX_IRQHandler
void CAN_TX_IRQHandler(void)
{

}
#endif

#ifdef CAN_SCE_IRQHandler
void CAN1_SCE_IRQHandler(void)
{

}
#endif
#endif
