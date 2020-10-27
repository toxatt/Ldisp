/**
  ******************************************************************************
  * @file    main.c
  * @author  Ac6
  * @version V1.0
  * @date    01-December-2013
  * @brief   Default main function.
  ******************************************************************************
*/

#include "stm32f10x.h"
#include "Sysinit.h"
#include "main.h"
#include "FreeRTOS.h"
#include "task.h"
#include "can.h"
#include "string.h"
#include "stdio.h"
#include "time.h"
#include "queue.h"
#include "semphr.h"
#include "hardware.h"
#include "cmd.h"


#ifdef USE_DISPLAY_GR
#include "KS0108.h"
#include "graphic.h"
#endif

T_settings settings;
T_display Disp;

struct tm * ptm;
time_t rawtime;

RTC_DateTimeTypeDef date;

T_data data;
T_data_IN IN;

xQueueHandle CNT_disp_queue = NULL;
xQueueHandle Data_IN_queue = NULL;
xQueueHandle Data_out_cnt = NULL;		//Counter on display to CAN
xQueueHandle Data_out_G_cnt = NULL;		//Global counter to CAN
xQueueHandle Data_out_display = NULL;	//Display to CAN
xSemaphoreHandle S_Save = NULL;			//Save settings

void Read_settings(void);
void Write_settings(void);
void vDefaultTask(void * pvParameters);
//void xCANTask(void * pvParameters);
void vCanTask(void *args);
void vDisplayTask(void * pvParameters);
void vLogicTask(void * pvParametrs);
void RTC_GetDateTime(uint32_t RTC_Counter, RTC_DateTimeTypeDef* RTC_DateTimeStruct);
void Pr_start(void);
void Pr_stop(void);

uint32_t CRC_Calc(uint32_t * ptr, uint32_t BufferLength);
uint8_t Settings_read (T_settings * s,uint32_t  Addr);
uint8_t Settings_write (T_settings * s,uint32_t  Addr);
uint8_t Settings_check (T_settings * s);
void Settings_default (T_settings * s);
void Disp_Global(uint32_t ex_g);
uint32_t Get_Global(uint32_t ex_g);

#ifdef USE_DISPLAY_GR
void GDisp_imp2litr (uint32_t cnt, char * ptr);

#endif

int main(void)
{
    Init_sys();

    Read_settings();

    xTaskCreate(vDefaultTask,"SYS_Task",configMINIMAL_STACK_SIZE,NULL,tskIDLE_PRIORITY,NULL);
    xTaskCreate(vDisplayTask,"Display_Task",512,NULL,tskIDLE_PRIORITY+1,NULL);
    xTaskCreate(vCanTask,"CAN_Task",1024,NULL,tskIDLE_PRIORITY+3,NULL);
    xTaskCreate(vLogicTask,"Logic_Task",512,NULL,tskIDLE_PRIORITY+2,NULL);

    CNT_disp_queue =  xQueueCreate(4,sizeof(T_display_queue));
    Data_IN_queue = xQueueCreate(2,sizeof(T_data_IN));
    Data_out_cnt = xQueueCreate(2,sizeof(uint64_t));
    Data_out_G_cnt = xQueueCreate(2,sizeof(uint64_t));
    Data_out_display = xQueueCreate(1,sizeof(Disp.d));

    S_Save = xSemaphoreCreateBinary();



    if (CNT_disp_queue== NULL
    		|| Data_IN_queue == NULL
			|| Data_out_cnt == NULL
			|| Data_out_G_cnt == NULL
			|| Data_out_display == NULL)
    {
    	__NOP();
    	__NOP();
    	__NOP();
    	//Error
    }

    vTaskStartScheduler();

    for(;;)
	{
	};
}

/*
 Get State of valve
 */
T_Valve_state get_valve_state (void)
{
	//static uint32_t valve_close_tick=0;

#ifdef HW_VEHICLE

	if (IN.valid_valve ==1)
	{
	//if ((data.Ain1 > 10000) )
	//{
		if (IN.valve_state == state_on && IN.pump_state == state_on)  return (state_on); else
			if (IN.valve_state == state_off)return (state_off);
		return (state_unknown);
//	}
	} else
	{
		return (data.valve_state);	//return last valid state
	}

#endif


#ifdef HW_STATION
	if (IN.valid_valve ==1)
		{

			if (IN.valve_state == state_on)  return (state_on); else
				if (IN.valve_state == state_off)return (state_off);
			return (state_unknown);

		} else
		{
			return (data.valve_state);	//return last valid state
		}

#endif

	return (state_unknown);
}

uint8_t is_CARD (void)
{

	if (IN.CARD[0] > 1 || IN.CARD[1]!=0 || IN.CARD[2]!=0 || IN.CARD[3] != 0 || IN.CARD[4]!=0)
	return 1;
	return 0;
}

void Disp_time_to_display(void)
{
	rawtime = RTC_GetCounter();
#ifdef USE_DISPLAY_GR
	uint8_t xx[16];
#endif
	if (data.time_TR > 1565702549
			&& (data.time_TR > (rawtime + 60) || data.time_TR < (rawtime - 60)))
	{
		PWR_BackupAccessCmd(ENABLE);
		RTC_SetCounter(data.time_TR);
	};
	RTC_GetDateTime(rawtime + (3600 * settings.timezone), &date);
#ifdef USE_DISPLAY_GR
	if ((rawtime & 0x01) !=0)
		sprintf((char*) &xx[0], "   %02u:%02u ", date.RTC_Hours,date.RTC_Minutes);
	else
		sprintf((char*) &xx[0], "   %02u %02u ", date.RTC_Hours,date.RTC_Minutes);
	GLCD_GoTo(72,7);
	GLCD_WriteString((char*)&xx[0]);
#else

	if ((rawtime & 0x01) !=0)
		Disp.dot = 0x10;
	else
		Disp.dot = 0;
	sprintf((char*) &Disp.d[0], "   %02u%02u ", date.RTC_Hours,
			date.RTC_Minutes);
#endif
}

void Disp_imp2litr(uint32_t cnt)
{
	static uint32_t c, litr = 0;
	double l;

	if (cnt != c)
	{
		c = cnt;
		l = c / settings.cnt_pulses_per_litre;
		l *= 10;
		litr = (uint32_t) l;
	};

	if (litr < 10)
		sprintf((char*) &Disp.d[0], "      0%1u", (unsigned int) litr);
	else
		sprintf((char*) &Disp.d[0], "%8u", (unsigned int) litr);
	Disp.dot = 0x40;
	xQueueSend(Data_out_cnt,&litr,0);
}

void GDisp_imp2litr (uint32_t cnt, char * ptr)
 {
	static uint32_t c, litr, i;
	double l = 0;
	char x;

	if (cnt != c) {
		c = cnt;
		l = c * settings.cnt_ratio;
		l *= 10;
		litr = (uint32_t) l;

	};

	i = sprintf(ptr, "%010u.", (unsigned int) litr);
	if (i > 3) {
		i--;
		x = ptr[i];
		ptr[i] = ptr[i - 1];
		ptr[i - 1] = x;
	}
}

#ifdef USE_DISPLAY_GR

void GDisp_imp2litr_BIG(uint32_t cnt, char * ptr) {
	static uint32_t c, litr;
	double l = 0;
	char x;

	if (cnt != c) {
		c = cnt;
		l = c * settings.cnt_ratio;
		l *= 10;
		litr = (uint32_t) l;

	};
	if (litr < 10)
		sprintf(ptr, "    0%1u", (unsigned int) litr);
	else
		sprintf(ptr, "%6u", (unsigned int) litr);

}

#endif


/*****************************************************************************************
 *  Function Name	:	Get_Global
 * Description		:	calculate global counter from pulses in EX
 *
 *****************************************************************************************/
uint32_t Get_Global(uint32_t ex_g)
{
	uint32_t out;
	double x;
	//out = (ex - ex_start) / ppl

	x = (ex_g - settings.cnt_EX_trim);
	x = x / settings.cnt_pulses_per_litre;
	x += settings.cnt_start;

	out = x;
	if (out >=100000000 )
		out -=100000000;
	if (out >=100000000 )
			out -=100000000;
	if (out >=100000000 )
			out -=100000000;
	if (out >=100000000 )
			out -=100000000;
	return (uint32_t)(out);

};


/*****************************************************************************************
 *  Function Name	:	Disp_Global
 * Description		:	Convert global liters to string end send to display out
 *
 *****************************************************************************************/
void Disp_Global(uint32_t ex_g)
{
	uint32_t x;
	x = Get_Global(ex_g);
	sprintf((char*) &Disp.d[0], "%8u", (unsigned int) x);

	Disp.dot = 0x00;
	xQueueSend(Data_out_cnt,&x,0);
};

void vDisplayTask(void * pvParameters)
{
	T_display_queue data_for_display={0,0};
	uint8_t d_out[8];
	__IO uint32_t i, j, tick_start;
	static T_Dislpay_states previous_state;
	static char xx[32];
#ifdef USE_DISPLAY_GR
	GLCD_Initalize();
	GLCD_ClearScreen();
	GLCD_GoTo(0,0);
	GLCD_WriteString("+-------------------+");
	GLCD_GoTo(0,1);
	GLCD_WriteString("|    TOXASYSTEMS    |");
	GLCD_GoTo(0,2);
	GLCD_WriteString("|                   |");
	GLCD_GoTo(0,3);
	GLCD_WriteString("|    Gas station    |");
	GLCD_GoTo(0,4);
	GLCD_WriteString("|      Display      |");
	GLCD_GoTo(0,5);
	GLCD_WriteString("|                   |");
	GLCD_GoTo(0,6);
	GLCD_WriteString("| 2019              |");
	GLCD_GoTo(0,7);
	GLCD_WriteString("+-------------------+");
#else

	Disp.backlight = 1;
	LED1_Port->BSRR = LED1_Pin;
	sprintf((char*) &Disp.d[0], "  HELLO ");
#endif
	vTaskDelay(1500);
	LED1_Port->BRR = LED1_Pin;
	LED2_Port->BSRR = LED2_Pin;

	sprintf((char*) &Disp.d[0], "        ");
	vTaskDelay(1000);
	LED2_Port->BRR = LED2_Pin;
	i = 0;
	j = 0;


#ifdef USE_DISPLAY_GR
	vTaskDelay(2000);
	GLCD_ClearScreen();

#endif

	while (1)
	{
		xQueueReceive(CNT_disp_queue, &data_for_display, 0);

#ifndef USE_DISPLAY_GR
		switch (Disp.State)
		{
//--------------------------------------------------------------------------------
		case Display_Idle:
			Disp.State = Display_time;
			break;

//--------------------------------------------------------------------------------
		case Display_time:
			//Update time
			//read_rtc
			switch (i)
			{
			case 0:
				i++;
				tick_start = xTaskGetTickCount();
				break;
			case 1:
				//Disp_imp2litr(IN.G_CNT_EX);
				Disp_Global(IN.G_CNT_EX);
				if (xTaskGetTickCount() > (tick_start + 5000))
					i++;
				break;
			case 2:
				Disp_time_to_display();
				if (xTaskGetTickCount() > (tick_start + 12000))
					i++;
				break;
			case 3:
				i = 0;
			default:
				i = 0;
				break;
			}
		//	Disp_time_to_display();
			vTaskDelay(10);
			LED2_Port->BRR = LED2_Pin;
			break;
//----------------------------------------------------------------------------------
		case Display_start_refueling:

			sprintf((char*) &Disp.d[0], "  START ");
			Disp.dot = 0;
			LED1_Port->BSRR = LED1_Pin;
			LED2_Port->BRR = LED2_Pin;
			vTaskDelay(800);
			Disp.State = Display_refueling;
			data_for_display.new_state = Disp.State;

			break;
//----------------------------------------------------------------------------------
		case Display_refueling:
			if (get_valve_state() == state_on)
				LED1_Port->BSRR = LED1_Pin;
			Disp_imp2litr(data_for_display.pulses);
			i = 0;
			j = 0;
			break;
//-----------------------------------------------------------------------------------
		case Display_end_refueling:
			LED1_Port->BRR = LED1_Pin;
			LED2_Port->BSRR = LED2_Pin;
			switch (i)
			{
			case 0:
				i++;
				sprintf((char*) &Disp.d[0], "  STOP ");
				Disp.dot = 0;
				vTaskDelay(1500);
				break;
			case 1:
				i++;
				tick_start = xTaskGetTickCount();
				break;

			case 2:
				Disp_imp2litr(data_for_display.pulses);
				if (xTaskGetTickCount() > tick_start + 2000)
					i++;
				break;
			case 3:
				//Disp_imp2litr(IN.G_CNT_EX);
				Disp_Global(IN.G_CNT_EX);
				if (xTaskGetTickCount() > tick_start + 10000)
					i++;
				break;
			case 4:
				Disp_time_to_display();
				if (xTaskGetTickCount() > tick_start + 12000)
					i++;
				break;
			case 5:
				if (xTaskGetTickCount() > tick_start + 14000)
					i++;
			case 6:
				i = 1;
				if (j++ > 25)
					Disp.State = Display_time;
			default:
				i = 1;
				break;
			}
			break;
//-------------------------------------------------------------------------------
		case Display_show_error:
			break;
		case Display_slave_mode:
			memcpy(Disp.d, data.display_d,8);
			Disp.dot = data.display_d[0];
			break;
		default:
			break;
		};
#else

		//Update time
		//read_rtc
		Disp_time_to_display();

		//Display current liters
		GLCD_GoTo(0,0);
		GDisp_imp2litr_BIG(data_for_display.pulses,xx);
		GLCD_WriteString_BIG(xx);
		GLCD_GoTo(97,3);
		GLCD_WriteString("*");

		GLCD_GoTo(0,5);
		GDisp_imp2litr(IN.G_CNT_EX,xx);
		GLCD_WriteString(xx);

		switch (Disp.State)
		{
//--------------------------------------------------------------------------------
		case Display_Idle:
			Disp.State = Display_time;
			break;

//--------------------------------------------------------------------------------
		case Display_time:
			//Disp_imp2litr(IN.G_CNT_EX);
			vTaskDelay(10);
			break;
//----------------------------------------------------------------------------------
		case Display_start_refueling:
			GLCD_GoTo(0,7);
			GLCD_WriteString("  START     ");
		//	vTaskDelay(400);
			Disp.State = Display_refueling;
			data_for_display.new_state = Disp.State;
			break;
//----------------------------------------------------------------------------------
		case Display_refueling:
			Disp_imp2litr(data_for_display.pulses);
			break;
//-----------------------------------------------------------------------------------
		case Display_end_refueling:
			GLCD_GoTo(0,7);
			GLCD_WriteString("  STOP      ");
				Disp_imp2litr(data_for_display.pulses);
				Disp_imp2litr(IN.G_CNT_EX);
			break;
//-------------------------------------------------------------------------------
		case Display_show_error:
			break;

		default:
			break;
		};
#endif

		memcpy(d_out,Disp.d,8);
		d_out[0] = Disp.dot;
		xQueueSendToBack(Data_out_display,&d_out[0],0);
		vTaskDelay(10);
		if ((data_for_display.new_state != 0)
				&& (data_for_display.new_state != previous_state))
		{
			Disp.State = data_for_display.new_state;
			previous_state = data_for_display.new_state;
		};

	};

}
;


void vDefaultTask(void * pvParameters)
{


    while(1)
	{
	    LED_Port->BSRR = LED_Pin;
//	    vTaskDelay(500);
//	    LED_Port->BRR = LED_Pin;
	    if (xSemaphoreTake(S_Save,0) == pdTRUE)
	    	Write_settings();
	    vTaskDelay(10);

	   // LED1_Port->BSRR = LED1_Pin;
	   // LED2_Port->BSRR = LED2_Pin;
	    IWDG_ReloadCounter();
	};
};


void vLogicTask(void * pvParametrs)
{

	static T_display_queue to_display;


	__IO uint8_t couner_stable;	//increasing when counter not change
	__IO uint8_t counter_inreased;
	__IO uint32_t previous_cnt=0;

	uint32_t	G_cnt;

	to_display.new_state = 0;
	to_display.pulses = 0;
	for (;;)
	{
		if (pdPASS == xQueueReceive(Data_IN_queue, &IN, 2500))
		{

			if (IN.valid_CNT == 1)
			{
				if (IN.G_CNT_EX != data.G_CNT_EX)
				{
					data.G_CNT_EX = IN.G_CNT_EX; //Update global counter
					if (data.G_CNT_EX > (previous_cnt+2)) //the counter has increased by more than 2 pulses
					{
						previous_cnt = data.G_CNT_EX;
						counter_inreased = 1;
					};
					couner_stable = 0;
				}
				else
					couner_stable++; //counter was  not change


				G_cnt = Get_Global(data.G_CNT_EX);
				xQueueSend(Data_out_G_cnt,&G_cnt,0);

			}

			if (IN.valid_timer == 1)
				data.time_TR = IN.time_TR;

			if (IN.valid_AIN == 1)
			{
				data.Ain1 = IN.Ain1;
				data.Ain2 = IN.Ain2;
				data.Ain3 = IN.Ain3;
			};

			if (IN.valid_card == 1)
			{
				memcpy(data.CARD, IN.CARD, 5);
			}
			if (IN.valid_master_disp ==1)
			{
				memcpy(data.display_d ,IN.master_d,8);
			}



		}else
		{

			//CAN no data long time
			vTaskDelay(100);
			//	NVIC_SystemReset();
		};

		switch (data.state)
		{
		case SysState_Idle:
			//All initialization
			//vTaskDelay(10);
			if (IN.valid_CNT == 1) //wait valid counter data
			{
				if ((IN.G_CNT_EX != 0) && (data.G_CNT_EX_stop == 0))
				{
					data.G_CNT_EX_stop = IN.G_CNT_EX;//after power on, save counter as last stop counter
				};
				data.state = SysState_normal;	//change system status
				counter_inreased = 0;
			};
			if (settings.mode == 1) data.state = SysState_slave_mode;
			break;
//-------------------------------------------------------------------------------------------------------
		case SysState_normal:  //Normal state, waiting for refueling

			if (get_valve_state() == state_on
					//|| counter_inreased == 1
				)
			{//Start refueling
				data.valve_state = state_on;
				to_display.new_state = Display_start_refueling;
				Pr_start();
			}
//			if (data.valve_state == state_on
//					&& get_valve_state() == state_off)
//			{
//				data.state = SysState_stop;
//			}
//			else if (IN.G_CNT_EX != data.G_CNT_EX_stop)
//				data.G_CNT_EX_stop = IN.G_CNT_EX;

			break;
//-------------------------------------------------------------------------------------------------------
		case SysState_refueling:
			//
			//vTaskDelay(5);
			data.cnt_disp = data.G_CNT_EX - data.G_CNT_EX_stop;
			if (get_valve_state() == state_off
					//data.valve_state == state_on

					&& couner_stable > 5) //Stop refueling
			{
				data.valve_state = state_off;	//change status
				to_display.new_state = Display_end_refueling;
				Pr_stop();
			};

			to_display.new_state = Display_refueling;

			break;
//-------------------------------------------------------------------------------------------------------
		case SysState_emergency_refueling:
			//This state is activating when filling without card
			break;
//-------------------------------------------------------------------------------------------------------
		case SysState_stop: //Stopping refueling, save data

			data.state = SysState_normal;
			data.G_CNT_EX_stop = data.G_CNT_EX;
			to_display.new_state = Display_end_refueling;
			break;
		case SysState_slave_mode:
			to_display.new_state = Display_slave_mode;
			break;
		default:
			break;
		}
		to_display.pulses = data.cnt_disp;
		xQueueSend(CNT_disp_queue, &to_display,10);
		vTaskDelay(10);


	}
}

/*******************************************************************
 * 		Prepare to starting refueling
 *******************************************************************/
void Pr_start(void)
{
	if (data.G_CNT_EX_stop == 0 && data.G_CNT_EX_start == 0)
	{
		data.cnt_disp = 0;//reset counter
	};

	data.state = SysState_refueling;
}

/******************************************************************
 * 		Prepare to stopping refueling
 ******************************************************************/
void Pr_stop (void)
{
	data.state = SysState_stop;
}


/*TODO
 * Time indication +
 * Main logic refueling +
 * counter transmit into CAN +
 * Read/Write settings +
 * Configuration from CAN +
 * Change ratio of counter without offset global counter
 * Slave mode
 *
 *
 */

// Get current date
void RTC_GetDateTime(uint32_t RTC_Counter,
		RTC_DateTimeTypeDef* RTC_DateTimeStruct)
{
	unsigned long time;
	unsigned long t1, a, b, c, d, e, m;
	int year = 0;
	int mon = 0;
	int wday = 0;
	int mday = 0;
	int hour = 0;
	int min = 0;
	int sec = 0;
	uint64_t jd = 0;

	uint64_t jdn = 0;

	jd = ((RTC_Counter + 43200) / (86400 >> 1)) + (2440587 << 1) + 1;
	jdn = jd >> 1;

	time = RTC_Counter;
	t1 = time / 60;
	sec = time - t1 * 60;

	time = t1;
	t1 = time / 60;
	min = time - t1 * 60;

	time = t1;
	t1 = time / 24;
	hour = time - t1 * 24;

	wday = jdn % 7;

	a = jdn + 32044;
	b = (4 * a + 3) / 146097;
	c = a - (146097 * b) / 4;
	d = (4 * c + 3) / 1461;
	e = c - (1461 * d) / 4;
	m = (5 * e + 2) / 153;
	mday = e - (153 * m + 2) / 5 + 1;
	mon = m + 3 - 12 * (m / 10);
	year = 100 * b + d - 4800 + (m / 10);

	RTC_DateTimeStruct->RTC_Year = year;
	RTC_DateTimeStruct->RTC_Month = mon;
	RTC_DateTimeStruct->RTC_Date = mday;
	RTC_DateTimeStruct->RTC_Hours = hour;
	RTC_DateTimeStruct->RTC_Minutes = min;
	RTC_DateTimeStruct->RTC_Seconds = sec;
	RTC_DateTimeStruct->RTC_Wday = wday;
}

uint32_t CRC_Calc(uint32_t * ptr, uint32_t BufferLength)
{
  uint32_t index = 0;

  CRC_ResetDR();
  for(index = 0; index < BufferLength; index+=4)
  {
    CRC->DR = *ptr++;
  }
  return (uint32_t)(CRC->DR);
}

void Read_settings(void)
{
	uint8_t res=0;
	//uint8_t * st_src;
	T_settings tmp;

	res = Settings_read(&tmp, SETTINGS_START);
	if (Settings_check(&tmp) != E_OK)
	{
		res = Settings_read(&tmp, SETTINGS_START_COPY);
		if (Settings_check(&tmp) != E_OK)
		{
			Settings_default(&settings);
			Settings_write(&settings, SETTINGS_START);
		}
	}
	else
	{
		memcpy(&settings,&tmp,sizeof(T_settings));
	//	memcpy(&set_new,&settings,sizeof(T_settings));
	}

}

void Write_settings(void)
{
	uint8_t res=0;
	//uint8_t * st_src;
	T_settings tmp;

	res = Settings_write(&settings, SETTINGS_START);
	res = Settings_read(&tmp, SETTINGS_START);
	if (Settings_check(&tmp) == E_OK)
	{
		Settings_write(&settings, SETTINGS_START_COPY);
		Settings_read(&tmp, SETTINGS_START_COPY);
		if (Settings_check(&tmp) != E_OK)
		{
		//	Settings_default(&settings);
		//	Settings_write(&settings, SETTINGS_START);
		}
	}

}


uint8_t Settings_read (T_settings * s,uint32_t  Addr)
{
	//st_src = (uint8_t *)SETTINGS_START;
	memcpy(s,(__IO uint32_t*)Addr,sizeof(T_settings));
	return E_OK;
}

uint8_t Settings_check (T_settings * s)
{
	uint32_t crc;

	crc = CRC_Calc((void *)s,sizeof (T_settings) - 4);
	if (crc == s->crc && crc!=0) return E_OK;
	return E_ERROR;
}

uint8_t Settings_write(T_settings * s, uint32_t Addr) {
	uint32_t size;
	FLASH_Unlock();
	FLASH_ErasePage(Addr);
	uint32_t *source_addr = (void *) s;
	uint32_t *dest_addr = (uint32_t *) Addr;
	size = sizeof(T_settings) / 2;
	s->crc = CRC_Calc(source_addr, sizeof(T_settings)-4);
	for (uint16_t i = 0; i < size; i++) {
		FLASH_ProgramWord((uint32_t) dest_addr, *source_addr);
		source_addr++;
		dest_addr++;
	}
	return E_OK;
}



void Settings_default (T_settings * s)
{

			//set default
		   s->CNT.addr = ADDR_EX;
		   s->CNT.pgn = CNT_PGN;
		   s->CNT.start = CNT_Start;
		   s->CNT.bit = CNT_Bit;
		   s->CNT.timeout = CNT_timeout;

		   s->valve.addr = ADDR_EX;
		   s->valve.pgn = VLV_PGN;
		   s->valve.start = VLV_Start;
		   s->valve.bit  =VLV_Bit;
		   s->valve.timeout = VLV_timeout;

		   s->Ain.addr = ADDR_EX;
		   s->Ain.pgn = AIN_PGN;
		   s->Ain.start = AIN_Start;
		   s->Ain.bit = AIN_Bit;
		   s->Ain.timeout = AIN_timeout;

		   s->Time.addr = Time_ADDR;
		   s->Time.pgn = Time_PGN;
		   s->Time.start = Time_Start;
		   s->Time.bit = Time_Bit;
		   s->Time.timeout = Time_timeout;

		   s->MY_ADDR = UNIT_ADDR;

		   s->CADR.addr  = ADDR_CARD;
		   s->CADR.pgn = CARD_PGN;
		   s->CADR.bit = CARD_Bit;
		   s->CADR.start = CARD_Start;
		   s->CADR.timeout = CARD_timeout;

//		   s->TX_MSG[0].PGN = MSG1_PGN;
//		   s->TX_MSG[0].timeout = MSG1_TIMEOUT;
//
//		   s->TX_MSG[1].PGN = MSG2_PGN;
//		   s->TX_MSG[1].timeout = MSG2_TIMEOUT;

		   s->TX_MSG[0].enable =1;
		   s->TX_MSG[1].enable =1;

		   s->TPASS = TPASS_DEFAULT;
		   //settings.cnt_ratio = 0.0479;
		  // s->cnt_ratio = 0.023809524;//rassvet2
		   //settings.cnt_ratio = 0.022893773;//rassvet
		   settings.cnt_pulses_per_litre = 20.855;//old - 20.87682672;
		   //settings.cnt_pulses_per_litre = 43.68;//rassvet
		  //s->cnt_pulses_per_litre = 42;//rassvet2


//		//set default

//	   //settings.cnt_ratio = 0.0479;
//	   settings.cnt_ratio = 0.023809524;//rassvet2
//	   //settings.cnt_ratio = 0.022893773;//rassvet
//	   //settings.cnt_pulses_per_litre = 20.855;//old - 20.87682672;
//	   //settings.cnt_pulses_per_litre = 43.68;//rassvet
//	  settings.cnt_pulses_per_litre = 42;//rassvet2

}



