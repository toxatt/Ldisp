/**
  ******************************************************************************
  * @file    stm32f1xx_it.c
  * @brief   Interrupt Service Routines.
  ******************************************************************************
  *
  * COPYRIGHT(c) 2017 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/

/* USER CODE BEGIN 0 */
#include "main.h"
#include "string.h"
#include "stm32f10x.h"
#include "strings.h"
#include "hardware.h"
#include "Sysinit.h"



extern const uint8_t LCD_DIGIT[];
extern const uint8_t SevenSegmentASCII[];
extern const uint8_t LCD_ASCII[];

/* USER CODE END 0 */

/* External variables --------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M3 Processor Interruption and Exception Handlers         */ 
/******************************************************************************/

/**
* @brief This function handles Non maskable interrupt.
*/
void NMI_Handler(void)
{
  /* USER CODE BEGIN NonMaskableInt_IRQn 0 */

  /* USER CODE END NonMaskableInt_IRQn 0 */
  /* USER CODE BEGIN NonMaskableInt_IRQn 1 */

  /* USER CODE END NonMaskableInt_IRQn 1 */
}

/**
* @brief This function handles Hard fault interrupt.
*/
void HardFault_Handler(void)
{
  /* USER CODE BEGIN HardFault_IRQn 0 */

  /* USER CODE END HardFault_IRQn 0 */

  while (1)
  {

  }
  /* USER CODE BEGIN HardFault_IRQn 1 */

  /* USER CODE END HardFault_IRQn 1 */
}

/**
* @brief This function handles Memory management fault.
*/
void MemManage_Handler(void)
{
  /* USER CODE BEGIN MemoryManagement_IRQn 0 */

  /* USER CODE END MemoryManagement_IRQn 0 */
  while (1)
  {
  }
  /* USER CODE BEGIN MemoryManagement_IRQn 1 */

  /* USER CODE END MemoryManagement_IRQn 1 */
}

/**
* @brief This function handles Prefetch fault, memory access fault.
*/
void BusFault_Handler(void)
{
  /* USER CODE BEGIN BusFault_IRQn 0 */

  /* USER CODE END BusFault_IRQn 0 */
  while (1)
  {
  }
  /* USER CODE BEGIN BusFault_IRQn 1 */

  /* USER CODE END BusFault_IRQn 1 */
}

/**
* @brief This function handles Undefined instruction or illegal state.
*/
void UsageFault_Handler(void)
{
  /* USER CODE BEGIN UsageFault_IRQn 0 */

  /* USER CODE END UsageFault_IRQn 0 */
  while (1)
  {
  }
  /* USER CODE BEGIN UsageFault_IRQn 1 */

  /* USER CODE END UsageFault_IRQn 1 */
}

/**
* @brief This function handles System service call via SWI instruction.
*/
//void SVC_Handler(void)
//{
//  /* USER CODE BEGIN SVCall_IRQn 0 */
//
//  /* USER CODE END SVCall_IRQn 0 */
//  /* USER CODE BEGIN SVCall_IRQn 1 */
//
//  /* USER CODE END SVCall_IRQn 1 */
//}

/**
* @brief This function handles Debug monitor.
*/
void DebugMon_Handler(void)
{
  /* USER CODE BEGIN DebugMonitor_IRQn 0 */

  /* USER CODE END DebugMonitor_IRQn 0 */
  /* USER CODE BEGIN DebugMonitor_IRQn 1 */

  /* USER CODE END DebugMonitor_IRQn 1 */
}

/**
* @brief This function handles Pendable request for system service.
*/
//void PendSV_Handler(void)
//{
//  /* USER CODE BEGIN PendSV_IRQn 0 */
//
//  /* USER CODE END PendSV_IRQn 0 */
//  /* USER CODE BEGIN PendSV_IRQn 1 */
//
//  /* USER CODE END PendSV_IRQn 1 */
//}

/**
* @brief This function handles System tick timer.
*/
//void SysTick_Handler(void)
//{
//  /* USER CODE BEGIN SysTick_IRQn 0 */
//
//  /* USER CODE END SysTick_IRQn 0 */
// // HAL_IncTick();
// // HAL_SYSTICK_IRQHandler();
//  /* USER CODE BEGIN SysTick_IRQn 1 */
//
//  /* USER CODE END SysTick_IRQn 1 */
//}

/******************************************************************************/
/* STM32F1xx Peripheral Interrupt Handlers                                    */
/* Add here the Interrupt Handlers for the used peripherals.                  */
/* For the available peripheral interrupt handler names,                      */
/* please refer to the startup file (startup_stm32f1xx.s).                    */
/******************************************************************************/

/**
* @brief This function handles USB low priority or CAN RX0 interrupts.
*/
//void USB_LP_CAN1_RX0_IRQHandler(void)
//{
  /* USER CODE BEGIN USB_LP_CAN1_RX0_IRQn 0 */

  /* USER CODE END USB_LP_CAN1_RX0_IRQn 0 */
 // HAL_CAN_IRQHandler(&hcan);
 // HAL_PCD_IRQHandler(&hpcd_USB_FS);
  /* USER CODE BEGIN USB_LP_CAN1_RX0_IRQn 1 */

  /* USER CODE END USB_LP_CAN1_RX0_IRQn 1 */
//}

/**
* @brief This function handles USART1 global interrupt.
*/
void USART1_IRQHandler(void)
{
  /* USER CODE BEGIN USART1_IRQn 0 */
//     if ((USART1->SR & USART_SR_RXNE) == USART_SR_RXNE)
//  {
//
//    if (RX1_index > 2 && stat.RX_timeout ==0) RX1_index =0;
//
//    RX1_buf[RX1_index++] = USART1->DR ;
//    USART1->SR &= ~(USART_SR_RXNE);
//
//    if (((RX1_index > 0) && (RX1_buf[0]!='$')) || ((RX1_index > 1) && (RX1_buf[1]!='G') ))  //start preambule
//      {
//
//          RX1_index =0;
//					memset(RX1_buf,0,10);
//      } else
//			if (RX1_buf[(RX1_index-1)]=='\n') //end
//			{
//
//				if (memcmp(RX1_buf,"$GPGGA",6)==0)
//				{
//					NMEA.got_gga++;
//					if (NMEA.got_gga >1)
//					{
//						memset(TX1_buf,0,200);
//
//						NMEA.next = sprintf ((char*)&TX1_buf,"%s",NMEA.GPGGA);;
//						NMEA.got_gga =0;
//						HAL_GPIO_TogglePin(GPIOC,GPIO_PIN_13);
//					};
//					 strcpy((char*)&NMEA.GPGGA,(char*)&RX1_buf);
//				} else
//					if (memcmp(RX1_buf,"$GPGSA",6)==0)
//					{
//						strcpy((char*)&NMEA.GPGSA,(char*)&RX1_buf);
//					} else
//				if (memcmp(RX1_buf,"$GPZDA",6)==0)
//				{
//					strcpy((char*)&NMEA.GPZDA,(char*)&RX1_buf);
//				}
//					else
//					if (memcmp(RX1_buf,"$GPVTG",6)==0)
//				{
//					strcpy((char*)&NMEA.GPVTG,(char*)&RX1_buf);
//				};
//				memset (RX1_buf,0,200);
//				RX1_index=0;
//
//			};
//      stat.RX_timeout = 100;
//
//      if (TR_stat.config ==0 &&  RX_index >= PACKET_LENGTH)
//      {
//        TR_stat.RX_ok = 1;
//        RX_index = 0;
//        USART1->CR1 &= ~(USART_CR1_RXNEIE);
//      };
//		}
  /* USER CODE END USART1_IRQn 0 */
 // HAL_UART_IRQHandler(&huart1);
  /* USER CODE BEGIN USART1_IRQn 1 */

  /* USER CODE END USART1_IRQn 1 */
}

/* USER CODE BEGIN 1 */


//void USART1_IRQHandler(void)
//{
//  /* USER CODE BEGIN USART1_IRQn 0 */
//      if ((USART1->SR & USART_SR_RXNE) == USART_SR_RXNE)
//  {

//    if (RX1_index > 2 && stat.RX_timeout ==0) RX1_index =0;

//    RX1_buf[RX1_index++] = USART1->DR ;
//    USART1->SR &= ~(USART_SR_RXNE);

//    if (((RX1_index > 0) && (RX1_buf[0]!='$')) || ((RX1_index > 1) && (RX1_buf[1]!='G') ))  //start preambule
//      {
//       
//          RX1_index =0;
//					memset(RX1_buf,0,10);
//      } else
//			if (RX1_buf[(RX1_index-1)]=='\n') //end 
//			{	
//				if (memcmp(RX1_buf,"$GPGGA",6)==0)
//				{
//					NMEA.got_gga++;
//					if (NMEA.got_gga >1)
//					{
//						memset(TX1_buf,0,1024);
//						memcpy(TX1_buf,NMEA.GPGGA,strlen((char*)&NMEA.GPGGA));
//						NMEA.next =1;
//						NMEA.got_gga =0;
//						HAL_GPIO_TogglePin(GPIOC,GPIO_PIN_13);
//					};
//					memcpy(NMEA.GPGGA,RX1_buf,RX1_index);
//				} else
//					if (memcmp(RX1_buf,"$GPGSA",6)==0) 
//					{
//						memcpy(NMEA.GPGSA,RX1_buf,RX1_index);
//					} else
//				if (memcmp(RX1_buf,"$GPZDA",6)==0) 
//				{
//					memcpy(NMEA.GPZDA,RX1_buf,RX1_index);
//				}
//					else
//					if (memcmp(RX1_buf,"$GPVTG",6)==0) 
//				{
//					memcpy(NMEA.GPVTG,RX1_buf,RX1_index);
//				};
//				
//			};
//      stat.RX_timeout = 50;
//			
////      if (TR_stat.config ==0 &&  RX_index >= PACKET_LENGTH)
////      {
////        TR_stat.RX_ok = 1;
////        RX_index = 0;
////        USART1->CR1 &= ~(USART_CR1_RXNEIE);
////      };

//  }
//};

void SPI1_IRQHandler(void)

{


};

void TIM3_IRQHandler(void) {
	__IO uint32_t temp = 0;
#ifdef USE_DISPLAY_LCD_6
	static uint8_t inv = 0;
#endif
	static uint8_t xx = 0;
#ifdef USE_DISPLAY_SERIAL
	Disp_RCK_Port->BSRR = Disp_RCK_Pin;
	__NOP();
	Disp_RCK_Port->BRR = Disp_RCK_Pin;
	temp = ((0x100<<Disp.index)|( 0xFF & ~SevenSegmentASCII[Disp.d[Disp.index]]));
	if ((Disp.dot>>Disp.index & 0x01 )!=0) temp &= ~(0x80);
	if ((SPI1->SR & SPI_SR_TXE) !=0) SPI1->DR = temp;
	Disp.index++;
	Disp.index &=0x07;

#elif USE_DISPLAY_LCD_6
	if ((SPI1->SR & SPI_SR_TXE) != 0) {

		if (Disp.index++ > 4) {
			// Storage data into storage register
			Disp_RCK_Port->BSRR = Disp_RCK_Pin;
			__NOP();
			Disp_RCK_Port->BRR = Disp_RCK_Pin;
			Disp.index = 0;
			if (inv != 0)
				inv = 0;
			else
				inv = 1;
		}
		temp = LCD_ASCII[0x7F & Disp.d[LCD_DIGIT[Disp.index]]];
		temp <<= 1;

		//digit
		if ((Disp.dot >> LCD_DIGIT[Disp.index] & 0x01) != 0)
			temp |= 0x01; //dot place here
		if (inv != 0) {
			temp = ~temp;
			temp &= 0xFF;
			if (Disp.index == 3)
				temp |= 1;
		}
		if (Disp.index == 2) {
			if (Disp.backlight == 1)
				temp |= 1;
			else
				temp &= 0xFE;
		}
		if (Disp.index < 3) { //reverse bit order
			temp <<= 24;
			temp = __RBIT(temp);
		}

		SPI1->DR = temp & 0xFF;

	}

#elif USE_DISPLAY_PARALLEL
	//6 Digits 7-segment display
	//PA0-PA7 segments
	//PB10-PB15 digits
	if (xx==0)
	{
	xx++;
	Display_port_digit->BRR = Display_digit_msk;
	Display_port->BRR = 0xFF;
	temp  = SevenSegmentASCII[Disp.d[Disp.index+2]];
	if ((Disp.dot>>(Disp.index+2) & 0x01 )!=0) temp |= 0x80;
	Display_port->BSRR = temp;
	Display_port_digit->BSRR = (Display_digit_0 << Disp.index);//	temp |= 0x80;
	if (Disp.index++ > 5) Disp.index = 0;
	} else
		{
		Display_port_digit->BRR = Display_digit_msk;
		Display_port->BRR = 0xFF;

		if (xx++> 1)xx=0;
		}
#elif USE_DISPLAY_GR


#endif

	TIM3->SR = 0;
}


//void TIM4_IRQHandler (void)
//{
//	u8 i;
//
//	TIM4->SR =0;
//
//}


/* USER CODE END 1 */
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
