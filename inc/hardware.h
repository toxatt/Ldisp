//*** <<< Use Configuration Wizard in Context Menu >>> ***
#ifndef __HARDWARE_H__
#define __HARDWARE_H__

#include "stm32f10x.h"
#include "Sysinit.h"


#define USE_DISPLAY_SERIAL 1
#define HW_VEHICLE 1

//#define HW_STATION 1
//#define USE_DISPLAY_PARALLEL 1
//#define USE_DISPLAY_GR	1

//#define USE_DISPLAY_LCD_6	1

#ifdef USE_DISPLAY_LCD_6
//#define DISPLAY_DIGIT	6
#else
//#error "SELECT number of digit"
#endif

#define Display_port 		GPIOA
#define Display_port_digit 	GPIOB
#define Display_digit_msk	0xFC00
#define Display_digit_0		0x0400


#if		defined( STM32F2XX )	|| \
		defined( STM32F4XX )

	#define PinMode_AIn			(PinMode_Type)(GPIO_Mode_AIN)
	#define PinMode_In			(PinMode_Type)(GPIO_Mode_IN  | (GPIO_PuPd_NOPULL << 2))
	#define PinMode_In_PD		(PinMode_Type)(GPIO_Mode_IN  | (GPIO_PuPd_DOWN   << 2))
	#define PinMode_In_PU		(PinMode_Type)(GPIO_Mode_IN  | (GPIO_PuPd_UP     << 2))
	#define PinMode_Out_OD		(PinMode_Type)(GPIO_Mode_OUT | (GPIO_OType_OD << 6) | (GPIO_Speed_50MHz << 4))
	#define PinMode_Out_OD_2	(PinMode_Type)(GPIO_Mode_OUT | (GPIO_OType_OD << 6) | (GPIO_Speed_2MHz  << 4))
	#define PinMode_Out_PP		(PinMode_Type)(GPIO_Mode_OUT | (GPIO_OType_PP << 6) | (GPIO_Speed_50MHz << 4))
	#define PinMode_Out_PP_2	(PinMode_Type)(GPIO_Mode_OUT | (GPIO_OType_PP << 6) | (GPIO_Speed_2MHz  << 4))
	#define PinMode_AF_OD		(PinMode_Type)(GPIO_Mode_AF  | (GPIO_OType_OD << 6) | (GPIO_Speed_50MHz << 4))
	#define PinMode_AF_PP		(PinMode_Type)(GPIO_Mode_AF  | (GPIO_OType_PP << 6) | (GPIO_Speed_50MHz << 4))
	#define PinMode_AF_PP_100	(PinMode_Type)(GPIO_Mode_AF  | (GPIO_OType_PP << 6) | (GPIO_Speed_100MHz << 4))
	#define PinMode_AF_PP_PU	(PinMode_Type)(GPIO_Mode_AF  | (GPIO_OType_PP << 6) | (GPIO_PuPd_UP << 2) | (GPIO_Speed_50MHz  << 4))

#elif	defined( STM32F10X_HD )	|| \
		defined( STM32F10X_MD )	|| \
		defined( STM32F10X_MD_VL )

	#define PinMode_AIn			(PinMode_Type)(GPIO_Mode_AIN)
	#define PinMode_In			(PinMode_Type)(GPIO_Mode_IN_FLOATING)
	#define PinMode_In_PD		(PinMode_Type)(GPIO_Mode_IPD)
	#define PinMode_In_PU		(PinMode_Type)(GPIO_Mode_IPU)

	#define PinMode_Out_OD		(PinMode_Type)(GPIO_Mode_Out_OD | GPIO_Speed_50MHz)
	#define PinMode_Out_OD_2	(PinMode_Type)(GPIO_Mode_Out_OD | GPIO_Speed_2MHz)
	#define PinMode_Out_OD_10	(PinMode_Type)(GPIO_Mode_Out_OD | GPIO_Speed_10MHz)
	#define PinMode_Out_OD_50	(PinMode_Type)(GPIO_Mode_Out_OD | GPIO_Speed_50MHz)

	#define PinMode_Out_PP		(PinMode_Type)(GPIO_Mode_Out_PP | GPIO_Speed_50MHz)
	#define PinMode_Out_PP_2	(PinMode_Type)(GPIO_Mode_Out_PP | GPIO_Speed_2MHz)
	#define PinMode_Out_PP_10	(PinMode_Type)(GPIO_Mode_Out_PP | GPIO_Speed_10MHz)
	#define PinMode_Out_PP_50	(PinMode_Type)(GPIO_Mode_Out_PP | GPIO_Speed_50MHz)

	#define PinMode_AF_OD		(PinMode_Type)(GPIO_Mode_AF_OD  | GPIO_Speed_50MHz)
	#define PinMode_AF_PP		(PinMode_Type)(GPIO_Mode_AF_PP  | GPIO_Speed_50MHz)

#endif

typedef unsigned char PinMode_Type;
void	pinMode		(uint8_t pin, PinMode_Type mode);
void	pinLow		(uint8_t pin);
void	pinHigh		(uint8_t pin);
void	pinToggle	(uint8_t pin);
void	pinRemap	(uint8_t pin, uint8_t GPIO_AF);

void Led1_On(void);
void Led2_On(void);
void Leds_Off(void);



//#define ERROR_CAN_TRANSMITE			0x31
//#define ERROR_CAN_TASK_FAIL			0x32
//
//#define ERROR_UNKNOWN_EXCEPTION		0x51
//#define ERROR_UNKNOWN_INTERRUPT		0x52
//#define ERROR_NO_TASK_MEMORY		0x53
//#define ERROR_TASK_FAILED			0x54
//#define ERROR_FLASH_ERASE			0x55
//#define ERROR_MCU_HARD				0x56
//#define ERROR_STACK_LOW				0x57

#define USE_CAN_SUPPORT		1


#define PA			0x00
#define PB			0x10
#define PC			0x20
#define PD			0x30
#define PE			0x40
#define PF			0x50
#define PG			0x60
#define PH			0x70

#define GPIO_PIN(p,n)	(p | n)
#define GPIO_MASK(pin)	(1 << (pin & 0xF))
#define GPIO_PORT(pin)	((GPIO_TypeDef *)(GPIOA_BASE + ((pin & 0xF0) << 6)))
#define GPIO_READ(pin)	(GPIO_PORT(pin)->IDR & GPIO_MASK(pin))

#define PA0			GPIO_PIN(PA, 0)
#define PA1			GPIO_PIN(PA, 1)
#define PA2			GPIO_PIN(PA, 2)
#define PA3			GPIO_PIN(PA, 3)
#define PA4			GPIO_PIN(PA, 4)
#define PA5			GPIO_PIN(PA, 5)
#define PA6			GPIO_PIN(PA, 6)
#define PA7			GPIO_PIN(PA, 7)
#define PA8			GPIO_PIN(PA, 8)
#define PA9			GPIO_PIN(PA, 9)
#define PA10		GPIO_PIN(PA,10)
#define PA11		GPIO_PIN(PA,11)
#define PA12		GPIO_PIN(PA,12)
#define PA13		GPIO_PIN(PA,13)
#define PA14		GPIO_PIN(PA,14)
#define PA15		GPIO_PIN(PA,15)

#define PB0			GPIO_PIN(PB, 0)
#define PB1			GPIO_PIN(PB, 1)
#define PB2			GPIO_PIN(PB, 2)
#define PB3			GPIO_PIN(PB, 3)
#define PB4			GPIO_PIN(PB, 4)
#define PB5			GPIO_PIN(PB, 5)
#define PB6			GPIO_PIN(PB, 6)
#define PB7			GPIO_PIN(PB, 7)
#define PB8			GPIO_PIN(PB, 8)
#define PB9			GPIO_PIN(PB, 9)
#define PB10		GPIO_PIN(PB,10)
#define PB11		GPIO_PIN(PB,11)
#define PB12		GPIO_PIN(PB,12)
#define PB13		GPIO_PIN(PB,13)
#define PB14		GPIO_PIN(PB,14)
#define PB15		GPIO_PIN(PB,15)

#define PC0			GPIO_PIN(PC, 0)
#define PC1			GPIO_PIN(PC, 1)
#define PC2			GPIO_PIN(PC, 2)
#define PC3			GPIO_PIN(PC, 3)
#define PC4			GPIO_PIN(PC, 4)
#define PC5			GPIO_PIN(PC, 5)
#define PC6			GPIO_PIN(PC, 6)
#define PC7			GPIO_PIN(PC, 7)
#define PC8			GPIO_PIN(PC, 8)
#define PC9			GPIO_PIN(PC, 9)
#define PC10		GPIO_PIN(PC,10)
#define PC11		GPIO_PIN(PC,11)
#define PC12		GPIO_PIN(PC,12)
#define PC13		GPIO_PIN(PC,13)
#define PC14		GPIO_PIN(PC,14)
#define PC15		GPIO_PIN(PC,15)

#define PD0			GPIO_PIN(PD, 0)
#define PD1			GPIO_PIN(PD, 1)
#define PD2			GPIO_PIN(PD, 2)



enum {
	E_OK				= 0,
	E_ERROR				= 1,
	E_TIMEOUT			= 2,
	E_SEND_ERROR		= 3,
	E_BAD_RESPONSE		= 9,
	E_GSM_NOT_READY		= 10,
	E_SIM_NOT_READY		= 11,
	E_NO_SIM			= 12,
	E_REG_DENIED		= 13,
	E_NOT_REGISTER		= 14,
	E_GSM_TCP_DISABLE	= 15,
	E_GSM_TCP_NOT_OPEN	= 16,
	E_BAD_COMMAND		= 17,
	E_NO_RESPONSE		= 18,
	E_FW_ERROR			= 20,

	E_TASK_DONE			= 252,
	E_TASK_ERROR		= 253,
	E_TASK_QUEUED		= 254,
	E_TASK_SENDED	 	= 255
};

enum {
	E_CMD_END		= 0x00,	// End of list
	E_CMD_SMS		= 0x01,	// Only from SMS
	E_CMD_HOST		= 0x02,	// Only from host
	E_CMD_BOTH		= 0x03,	// From SMS and host
	E_CMD_SINGLE	= 0x80	// Save last
};


#if ( USE_SERIAL_DEBUG )

	#define DEBUG_USART			USART2
	#define DEBUG_TX_AF			GPIO_AF_USART2
	#define DEBUG_RX_AF			GPIO_AF_USART2
	#define DEBUG_USART_CLK(m)	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, m)

	#define DEBUG_TX_PIN		PA2
	#define DEBUG_RX_PIN		PA3

	#define DEBUG_USART_IRQn		USART2_IRQn
	#define DEBUG_USART_IRQHandler	USART2_IRQHandler

	#if defined( STM32F2XX ) || defined( STM32F4XX )
		#define DEBUG_PIN_INIT()	\
			do {					\
				pinMode(DEBUG_TX_PIN, PinMode_AF_PP_PU);	\
				pinMode(DEBUG_RX_PIN, PinMode_AF_PP_PU);	\
				pinRemap(DEBUG_TX_PIN, DEBUG_TX_AF);		\
				pinRemap(DEBUG_RX_PIN, DEBUG_RX_AF);		\
				DEBUG_USART_CLK(ENABLE);					\
			} while(0)

	#elif	defined( STM32F10X_HD )	|| \
			defined( STM32F10X_MD )	|| \
			defined( STM32F10X_MD_VL )

		#define DEBUG_PIN_INIT()						\
			do {										\
				pinMode(DEBUG_TX_PIN, PinMode_AF_PP);	\
				pinMode(DEBUG_RX_PIN, PinMode_In_PU);	\
				DEBUG_USART_CLK(ENABLE);				\
			} while(0)

	#else
		#error "CPU type not define"
	#endif
#endif

extern const char VERSION[];
			
#if	defined( UTRACKER_4 )

	#if defined( STM32F100CB )
		#define VERSION_INFO_MAJOR		"C01"
		#if ( USE_AVERAGE == 1)
			#if ( USE_KALMAN == 1)
				#define VERSION_INFO	VERSION_INFO_MAJOR"AK"
			#else
				#define VERSION_INFO	VERSION_INFO_MAJOR"A"
			#endif
		#else
			#if ( USE_KALMAN == 1)
				#define VERSION_INFO	VERSION_INFO_MAJOR"K"
			#else
				#define VERSION_INFO	VERSION_INFO_MAJOR
			#endif
		#endif
	#elif defined( STM32F101RC )
		#define VERSION_INFO_MAJOR		"R01"
		#if ( USE_AVERAGE == 1)
			#if ( USE_KALMAN == 1)
				#define VERSION_INFO	VERSION_INFO_MAJOR"AK"
			#else
				#define VERSION_INFO	VERSION_INFO_MAJOR"A"
			#endif
		#else
			#if ( USE_KALMAN == 1)
				#define VERSION_INFO	VERSION_INFO_MAJOR"K"
			#else
				#define VERSION_INFO	VERSION_INFO_MAJOR
			#endif
		#endif
	#elif defined( STM32F205RE )
		#define VERSION_INFO_MAJOR		"R02"
		#if ( USE_AVERAGE == 1)
			#if ( USE_KALMAN == 1)
				#define VERSION_INFO	VERSION_INFO_MAJOR"AK"
			#else
				#define VERSION_INFO	VERSION_INFO_MAJOR"A"
			#endif
		#else
			#if ( USE_KALMAN == 1)
				#define VERSION_INFO	VERSION_INFO_MAJOR"K"
			#else
				#define VERSION_INFO	VERSION_INFO_MAJOR
			#endif
		#endif
	#elif defined( STM32F405RE )
		#define VERSION_INFO_MAJOR		"R03"
		#if ( USE_AVERAGE == 1)
			#if ( USE_KALMAN == 1)
				#define VERSION_INFO	VERSION_INFO_MAJOR"AK"
			#else
				#define VERSION_INFO	VERSION_INFO_MAJOR"A"
			#endif
		#else
			#if ( USE_KALMAN == 1)
				#define VERSION_INFO	VERSION_INFO_MAJOR"K"
			#else
				#define VERSION_INFO	VERSION_INFO_MAJOR
			#endif
		#endif
	#else
		#error "CPU not define"
	#endif

	#define USB_DISC_INIT()
	#define USB_P_INIT()
	#define SD_INIT()

	#define LED1_PIN			PB3
	#define LED2_PIN			PB4

	#define LED1_ON()			Led1_On()
	#define LED1_OFF()			Leds_Off()
	#define LED2_ON()			Led2_On()
	#define LED2_OFF()			Leds_Off()

	#define LED_ON()			LED1_ON()
	#define LED_OFF()			LED1_OFF()

	#define LED_INIT()			\
		do	{					\
			pinLow(LED1_PIN);					\
			pinLow(LED2_PIN);					\
			pinMode(LED1_PIN, PinMode_Out_PP);	\
			pinMode(LED2_PIN, PinMode_Out_PP);	\
		} while(0)

	#define ACC_INT1_PIN		PB5
	#define ACC_SCL_PIN			PB6
	#define ACC_SDA_PIN			PB7

	#define ACC_INIT()			\
		do {										\
			pinHigh(ACC_SDA_PIN);					\
			pinHigh(ACC_SCL_PIN);					\
			pinMode(ACC_SCL_PIN, PinMode_Out_OD);	\
			pinMode(ACC_SDA_PIN, PinMode_Out_OD);	\
			pinMode(ACC_INT1_PIN, PinMode_In_PU);	\
		} while (0)

	#define SENS_D1_PIN			PA0
	#define SENS_D1_INIT()		pinMode(SENS_D1_PIN, PinMode_In)
	#define SENS_D1_READ()		(GPIO_READ(SENS_D1_PIN) != 0)

	#define SENS_A1_PIN			PA1
	#define SENS_A1_INIT()		pinMode(SENS_A1_PIN, PinMode_AIn)
	#define SENS_A1_CHANNEL		ADC_Channel_12

	#define RELAY_PIN			PB0
	#define RELAY_ON()			pinHigh(RELAY_PIN)
	#define RELAY_OFF()			pinLow(RELAY_PIN)
	#define RELAY_INIT()		RELAY_OFF(); pinMode(RELAY_PIN, PinMode_Out_PP)

/*
 *	GPS
 */
	#define GPS_PWR_PIN				PA12
	#define GPS_PWR_ON()			pinHigh(GPS_PWR_PIN)
	#define GPS_PWR_OFF()			pinLow(GPS_PWR_PIN)
	#define GPS_PWR_INIT()			\
		do {										\
			GPS_PWR_OFF();							\
			pinMode(GPS_PWR_PIN, PinMode_Out_PP);	\
		} while(0)

	#define GPS_USART				USART3
	#define GPS_USART_IRQn			USART3_IRQn
	#define GPS_USART_CLK(m)		RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, m)
	#define GPS_USART_IRQHandler	USART3_IRQHandler

	#define GPS_TX_PIN				PB10
	#define GPS_RX_PIN				PB11
	#define GPS_TX_HIGH()			pinHigh(GPS_TX_PIN)
	#define GPS_RX_HIGH()			pinHigh(GPS_RX_PIN)
	#define GPS_RX_PREPARE()		pinMode(GPS_RX_PIN, PinMode_In_PU)
	#define GPS_REMAP()

/*
 *	GSM
 */
	#define GSM_PWR_PIN				PA11
	#define GSM_PWR_ON()			pinHigh(GSM_PWR_PIN)
	#define GSM_PWR_OFF()			pinLow(GSM_PWR_PIN)
	#define GSM_PWR_INIT()			GSM_PWR_OFF();	pinMode(GSM_PWR_PIN, PinMode_Out_PP)

	#define GSM_REMAP()

	#define GSM_USART				USART1
	#define GSM_USART_IRQn			USART1_IRQn
	#define GSM_USART_IRQHandler	USART1_IRQHandler
	#define GSM_USART_CLK(m)		RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, m)

	#define GSM_TX_PIN				PA9
	#define GSM_RX_PIN				PA10

	#define GSM_READY_PIN			GSM_RX_PIN
	#define GSM_READY_INIT()
	#define GSM_READY_PREPARE()		pinMode(GSM_RX_PIN, PinMode_In_PD)
	#define GSM_READY()				(GPIO_READ(GSM_READY_PIN) != 0)
	
	#define GSM_ON_INIT()
	#define GSM_DTR_INIT()
	#define GSM_DTR_DEINIT()
	#define GSM_DTR_LOW()
	#define GSM_RTS_INIT()
	#define GSM_RTS_DEINIT()
	#define GSM_RTS_LOW()
	#define GSM_CTS_INIT()
	#define GSM_CTS_DEINIT()
	
	#define CPU_PWR_INIT()
	#define VDC_INIT()
	#define VBAT_SENS_INIT()
	#define KEY_INIT()

	#define CUSTOM_INIT()			\
		do {								\
			pinMode(PA4, PinMode_In_PU);	\
			pinMode(PA5, PinMode_In_PU);	\
			pinMode(PA6, PinMode_In_PU);	\
			pinMode(PA7, PinMode_In_PU);	\
		} while(0)

	#define CAN_RX_PIN				PB8
	#define CAN_TX_PIN				PB9

	#define CAN_TX_DEINIT()			pinMode(CAN_TX_PIN, PinMode_In_PD)
	#define CAN_RX_DEINIT()			pinMode(CAN_RX_PIN, PinMode_In_PD)

	#define CAN_EN_PIN				PA15
	#define CAN_EN_LOW()			pinLow(CAN_EN_PIN)
	#define CAN_EN_HIGH()			pinHigh(CAN_EN_PIN)
	#define CAN_EN_INIT()			pinMode(CAN_EN_PIN, PinMode_In_PD)

#else
#if defined( Ldisp )

	#define VERSION_INFO_MAJOR		"LDisp 01"
	#define VERSION_INFO	VERSION_INFO_MAJOR" VER 02"

	#define CAN_RX_PIN				PB8
	#define CAN_TX_PIN				PB9

	#define CAN_TX_DEINIT()			pinMode(CAN_TX_PIN, PinMode_In_PD)
	#define CAN_RX_DEINIT()			pinMode(CAN_RX_PIN, PinMode_In_PD)

	#define CAN_EN_PIN			PA15
	#define CAN_EN_LOW()			pinLow(CAN_EN_PIN)
	#define CAN_EN_HIGH()			pinHigh(CAN_EN_PIN)
	#define CAN_EN_INIT()			pinMode(CAN_EN_PIN, PinMode_In_PD)
	#define CAN_CAN 			CAN1

	#define LED1_PIN			PB3
	#define LED2_PIN			PB4

	#define LED1_ON()			Led1_On()
	#define LED1_OFF()			Leds_Off()
	#define LED2_ON()			Led2_On()
	#define LED2_OFF()			Leds_Off()

	#define LED_ON()			LED1_ON()
	#define LED_OFF()			LED1_OFF()

	#define LED_INIT()			\
		do	{					\
			pinLow(LED1_PIN);					\
			pinLow(LED2_PIN);					\
			pinMode(LED1_PIN, PinMode_Out_PP);	\
			pinMode(LED2_PIN, PinMode_Out_PP);	\
		} while(0)


#else

	#error "Board not define"

#endif
#endif

#define CAN_PIN_DEINIT()		\
	do {						\
		CAN_EN_INIT();			\
		CAN_TX_DEINIT();		\
		CAN_RX_DEINIT();		\
	} while(0);

#define GPS_TX_DEINIT()						\
	do {									\
		pinMode(GPS_TX_PIN, PinMode_AIn);	\
	} while(0)

#define GPS_RX_DEINIT()						\
	do {									\
		pinMode(GPS_RX_PIN, PinMode_AIn);	\
	} while(0)

#if		defined( STM32F2XX )	|| \
		defined( STM32F4XX )

	#define GPS_TX_INIT()							\
		do {										\
			pinMode(GPS_TX_PIN, PinMode_AF_PP_PU);	\
			pinRemap(GPS_TX_PIN, GPS_TX_RX_AF);		\
		} while(0)

	#define GPS_RX_INIT()							\
		do {										\
			pinMode(GPS_RX_PIN, PinMode_AF_PP);		\
			pinRemap(GPS_RX_PIN, GPS_TX_RX_AF);		\
		} while(0)

#elif	defined( STM32F10X_HD )	|| \
		defined( STM32F10X_MD )	|| \
		defined( STM32F10X_MD_VL )

	#define GPS_TX_INIT()	pinMode(GPS_TX_PIN, PinMode_AF_PP)
	#define GPS_RX_INIT()	pinMode(GPS_RX_PIN, PinMode_In)

#else
	#error "CPU not define"
#endif

#if defined( STM32F2XX ) || defined( STM32F4XX )

	#define GSM_TX_INIT()							\
		do {										\
			pinMode(GSM_TX_PIN, PinMode_AF_PP_PU);	\
			pinRemap(GSM_TX_PIN, GSM_TX_RX_AF);		\
		} while(0)
	#define GSM_RX_INIT()							\
		do {										\
			pinMode(GSM_RX_PIN, PinMode_AF_PP);	 	\
			pinRemap(GSM_RX_PIN, GSM_TX_RX_AF);		\
		} while(0)

#elif	defined( STM32F10X_HD )	|| \
		defined( STM32F10X_MD )	|| \
		defined( STM32F10X_MD_VL )

	#define GSM_TX_INIT()			pinMode(GSM_TX_PIN, PinMode_AF_PP)
	#define GSM_RX_INIT()			pinMode(GSM_RX_PIN, PinMode_In)

#else
	#error "CPU not define"
#endif

#define GSM_TX_DEINIT()		pinMode(GSM_TX_PIN, PinMode_AIn)
#define GSM_RX_DEINIT()		pinMode(GSM_RX_PIN, PinMode_AIn)

#define GSM_PIN_DEINIT()	\
	do {					\
		GSM_TX_DEINIT();	\
		GSM_RX_DEINIT();	\
		GSM_DTR_DEINIT();	\
		GSM_RTS_DEINIT();	\
		GSM_CTS_DEINIT();	\
	} while(0)

#define GSM_PIN_INIT()		\
	do {					\
		GSM_TX_INIT();		\
		GSM_RX_INIT();		\
		GSM_DTR_INIT();		\
		GSM_RTS_INIT();		\
		GSM_CTS_INIT();		\
	} while(0)

#define GPS_DEINIT()		\
	do {					\
		USART_ITConfig(GPS_USART, USART_IT_RXNE, DISABLE);	\
		USART_ITConfig(GPS_USART, USART_IT_TXE, DISABLE);	\
		USART_Cmd(GPS_USART, DISABLE);						\
		GPS_USART_CLK(DISABLE);								\
		GPS_TX_DEINIT();									\
		GPS_RX_DEINIT();									\
		GPS_PWR_OFF();										\
	} while(0)
	
#define GSM_DEINIT()		\
	do {					\
		USART_ITConfig(GSM_USART, USART_IT_RXNE, DISABLE);	\
		USART_ITConfig(GSM_USART, USART_IT_TXE, DISABLE);	\
		USART_Cmd(GSM_USART, DISABLE);						\
		GPS_USART_CLK(DISABLE);								\
		GSM_PIN_DEINIT();									\
	} while(0)

#if 	defined( STM32F10X_MD )		||	\
		defined( STM32F10X_MD_VL )

		#define FLASH_PAGE_SIZE		0x0400

#elif 	defined( STM32F10X_HD )

		#define FLASH_PAGE_SIZE		0x0800
#else
		#error "CPU type not define"
#endif


#if 	defined( STM32F405RE )	|| \
		defined( STM32F205RE )	|| \
		defined( STM32F103RE )

	#define FLASH_SIZE_KB		512ul

#elif 	defined( STM32F405RG )

	#define FLASH_SIZE_KB		1024ul

#elif 	defined( STM32F103RD )

	#define FLASH_SIZE_KB		384ul

#elif	defined( STM32F103RC )	|| \
		defined( STM32F101RC )

	#define FLASH_SIZE_KB		256ul

#elif 	defined( STM32F100CB )

	#define FLASH_SIZE_KB		128ul


#elif 	defined( STM32F103C8 )

	#define FLASH_SIZE_KB		64ul

#else
	#error "CPU model not define"
#endif

//Memory

#define FLASH_APP_START		((uint32_t)0x1000)

#define FLASH_BLOCK_MASK	~(uint32_t)(FLASH_PAGE_SIZE - 1)
#define FLASH_SIZE			(FLASH_SIZE_KB * 1024UL)
#define FLASH_TOP_RESERVED	(uint32_t)(0 * FLASH_PAGE_SIZE)
#define FLASH_TOP			(uint32_t)(FLASH_BASE + FLASH_SIZE - FLASH_TOP_RESERVED)

#define BL_WORK_START		(FLASH_BASE + 0)
#define FW_WORK_START		(FLASH_BASE + FLASH_APP_START)
#define MAX_FW_SIZE			(uint32_t)(FLASH_TOP - FW_WORK_START) / 2
#define FW_COPY_START		((uint32_t)(FW_WORK_START + MAX_FW_SIZE))


#define FLASH_SIZE_EX_KB		128ul
#define FLASH_SIZE_EX			(FLASH_SIZE_EX_KB * 1024UL)
#define FLASH_TOP_SET_RESERV	(uint32_t)(2 * FLASH_PAGE_SIZE)

#define SETTINGS_START			(uint32_t)(FLASH_BASE + FLASH_SIZE_EX - 2048UL)
#define SETTINGS_START_COPY		(uint32_t)(FLASH_BASE + FLASH_SIZE_EX - 1024UL)

#endif
