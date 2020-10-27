
#include "Sysinit.h"
#include "stm32f10x.h"
#include "hardware.h"

#ifndef USE_DISPLAY_LCD_6
const uint8_t SevenSegmentASCII[128] = {
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0b00000000, /* (space) */
	0b10000110, /* ! */
	0b00100010, /* " */
	0b01111110, /* # */
	0b01101101, /* $ */
	0b11010010, /* % */
	0b01000110, /* & */
	0b00100000, /* ' */
	0b00101001, /* ( */
	0b00001011, /* ) */
	0b00100001, /* * */
	0b01110000, /* + */
	0b00010000, /* , */
	0b01000000, /* - */
	0b10000000, /* . */
	0b01010010, /* / */
	0b00111111, /* 0 */
	0b00000110, /* 1 */
	0b01011011, /* 2 */
	0b01001111, /* 3 */
	0b01100110, /* 4 */
	0b01101101, /* 5 */
	0b01111101, /* 6 */
	0b00000111, /* 7 */
	0b01111111, /* 8 */
	0b01101111, /* 9 */
	0b00001001, /* : */
	0b00001101, /* ; */
	0b01100001, /* < */
	0b01001000, /* = */
	0b01000011, /* > */
	0b11010011, /* ? */
	0b01011111, /* @ */
	0b01110111, /* A */
	0b01111100, /* B */
	0b00111001, /* C */
	0b01011110, /* D */
	0b01111001, /* E */
	0b01110001, /* F */
	0b00111101, /* G */
	0b01110110, /* H */
	0b00110000, /* I */
	0b00011110, /* J */
	0b01110101, /* K */
	0b00111000, /* L */
	0b00010101, /* M */
	0b00110111, /* N */
	0b00111111, /* O */
	0b01110011, /* P */
	0b01101011, /* Q */
	0b00110011, /* R */
	0b01101101, /* S */
	0b01111000, /* T */
	0b00111110, /* U */
	0b00111110, /* V */
	0b00101010, /* W */
	0b01110110, /* X */
	0b01101110, /* Y */
	0b01011011, /* Z */
	0b00111001, /* [ */
	0b01100100, /* \ */
	0b00001111, /* ] */
	0b00100011, /* ^ */
	0b00001000, /* _ */
	0b00000010, /* ` */
	0b01011111, /* a */
	0b01111100, /* b */
	0b01011000, /* c */
	0b01011110, /* d */
	0b01111011, /* e */
	0b01110001, /* f */
	0b01101111, /* g */
	0b01110100, /* h */
	0b00010000, /* i */
	0b00001100, /* j */
	0b01110101, /* k */
	0b00110000, /* l */
	0b00010100, /* m */
	0b01010100, /* n */
	0b01011100, /* o */
	0b01110011, /* p */
	0b01100111, /* q */
	0b01010000, /* r */
	0b01101101, /* s */
	0b01111000, /* t */
	0b00011100, /* u */
	0b00011100, /* v */
	0b00010100, /* w */
	0b01110110, /* x */
	0b01101110, /* y */
	0b01011011, /* z */
	0b01000110, /* { */
	0b00110000, /* | */
	0b01110000, /* } */
	0b00000001, /* ~ */
	0b00000000, /* (del) */
};

#else

const uint8_t LCD_DIGIT[8] = /*{5,6,7,2,3,4,0,0}; */{4,3,2,7,6,5,0,0};

const uint8_t LCD_ASCII[128] = {
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0b00000000, /* (space) */
	0b10000110, /* ! */
	0b00100010, /* " */
	0b01111110, /* # */
	0b01101101, /* $ */
	0b11010010, /* % */
	0b01000110, /* & */
	0b00100000, /* ' */
	0b00101001, /* ( */
	0b00001011, /* ) */
	0b00100001, /* * */
	0b01110000, /* + */
	0b00010000, /* , */
	0b01000000, /* - */
	0b10000000, /* . */
	0b01010010, /* / */
	0b01111101, /* 0 */
	0b00000101, /* 1 */
	0b01101110, /* 2 */
	0b01001111, /* 3 */
	0b00010111, /* 4 */
	0b01011011, /* 5 */
	0b01111011, /* 6 */
	0b00001101, /* 7 */
	0b01111111, /* 8 */
	0b01011111, /* 9 */
	0b00001001, /* : */
	0b00001101, /* ; */
	0b01100001, /* < */
	0b01001000, /* = */
	0b01000011, /* > */
	0b11010011, /* ? */
	0b01011111, /* @ */
	0b01110111, /* A */
	0b01111100, /* B */
	0b00111001, /* C */
	0b01011110, /* D */
	0b01111010, /* E */	//+
	0b01110001, /* F */
	0b00111101, /* G */
	0b00110111, /* H */ //+
	0b00110000, /* I */
	0b00011110, /* J */
	0b01110101, /* K */
	0b01110000, /* L */ //+
	0b00010101, /* M */
	0b00110111, /* N */
	0b01111101, /* O */	//+
	0b00111110, /* P */ //+
	0b01101011, /* Q */
	0b00100010, /* R */ //+
	0b01011011, /* S */ //+
	0b01110010, /* T */	//+
	0b01110101, /* U */	//+
	0b00111110, /* V */
	0b00101010, /* W */
	0b01110110, /* X */
	0b01101110, /* Y */
	0b01011011, /* Z */
	0b00111001, /* [ */
	0b01100100, /* \ */
	0b00001111, /* ] */
	0b00100011, /* ^ */
	0b00001000, /* _ */
	0b00000010, /* ` */
	0b01011111, /* a */
	0b01111100, /* b */
	0b01011000, /* c */
	0b01011110, /* d */
	0b01111011, /* e */
	0b01110001, /* f */
	0b01101111, /* g */
	0b01110100, /* h */
	0b00010000, /* i */
	0b00001100, /* j */
	0b01110101, /* k */
	0b00110000, /* l */
	0b00010100, /* m */
	0b01010100, /* n */
	0b01011100, /* o */
	0b01110011, /* p */
	0b01100111, /* q */
	0b01010000, /* r */
	0b01101101, /* s */
	0b01111000, /* t */
	0b00011100, /* u */
	0b00011100, /* v */
	0b00010100, /* w */
	0b01110110, /* x */
	0b01101110, /* y */
	0b01011011, /* z */
	0b01000110, /* { */
	0b00110000, /* | */
	0b01110000, /* } */
	0b00000001, /* ~ */
	0b00000000 /* (del) */

};


#endif
void Init_sys(void)
{

    //ON Clocking
	RCC->AHBENR  |= RCC_AHBENR_CRCEN;
    RCC->APB2ENR |= RCC_APB2ENR_SPI1EN | RCC_APB2ENR_AFIOEN;
    RCC->APB1ENR |= RCC_APB1ENR_PWREN | RCC_APB1ENR_BKPEN | RCC_APB1ENR_CAN1EN | RCC_APB1ENR_WWDGEN | RCC_APB1ENR_TIM3EN | RCC_APB1ENR_TIM4EN;


//    RCC->CR |= ((uint32_t)RCC_CR_HSEON); 												// Enable HSE
//    while (!(RCC->CR & RCC_CR_HSERDY));													// Ready start HSE
//
//    FLASH->ACR = FLASH_ACR_PRFTBE | FLASH_ACR_LATENCY;					// Cloclk Flash memory
//
//    RCC->CFGR |= RCC_CFGR_HPRE_DIV1;														// AHB = SYSCLK/1
//    RCC->CFGR |= RCC_CFGR_PPRE1_DIV1;														// APB1 = HCLK/1
//    RCC->CFGR |= RCC_CFGR_PPRE2_DIV1;														// APB2 = HCLK/1
//
//    RCC->CFGR &= ~RCC_CFGR_PLLMULL;             // clear PLLMULL bits
//    RCC->CFGR &= ~RCC_CFGR_PLLSRC;															// clearn PLLSRC bits
//    RCC->CFGR &= ~RCC_CFGR_PLLXTPRE;														// clearn PLLXTPRE bits
//
//    //RCC->CFGR |= RCC_CFGR_PLLSRC_PREDIV1; 		// source HSE
//   // RCC->CFGR |= RCC_CFGR_PLLXTPRE_PREDIV1_Div2; 	// source HSE/2 = 4 MHz
//    RCC->CFGR |= RCC_CFGR_PPRE1_DIV1;
//    RCC->CFGR |= RCC_CFGR_PLLXTPRE_PREDIV1_Div2;
//
//    RCC->CFGR |= RCC_CFGR_PLLMULL6; 														// PLL x6: clock = 4 MHz * 6 = 24 MHz
//
//    RCC->CR |= RCC_CR_PLLON;                      							// enable PLL
//    while((RCC->CR & RCC_CR_PLLRDY) == 0) {}      							// wait till PLL is ready
//
//    RCC->CFGR &= ~RCC_CFGR_SW;                   							 	// clear SW bits
//    RCC->CFGR |= RCC_CFGR_SW_PLL;                 							// select source SYSCLK = PLL
//    while((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_1) {} 			// wait till PLL is used
    PWR->CR |= PWR_CR_DBP;
    RCC->BDCR |= RCC_BDCR_LSEON | RCC_BDCR_RTCEN;
    RCC->BDCR |= RCC_BDCR_RTCSEL_0;
    PWR->CR &= ~(PWR_CR_DBP);
    SystemInit();

    InitGPIO();
#if defined (USE_DISPLAY_SERIAL) || defined (USE_DISPLAY_LCD_6)
    InitSPI();
#endif
    RTC->CRL |= RTC_CRL_CNF;	//Configuration mode
    RTC->PRLL = 0x7FFF;

    RTC->CRL &= ~(RTC_CRL_CNF);
#ifdef USE_DISPLAY_LCD_6
    TIM3->ARR = 1500;
#else
    TIM3->ARR = 700;
#endif
    TIM3->PSC = 71;
    TIM3->DIER |= TIM_DIER_UIE;
    TIM3->CR1 |= TIM_CR1_ARPE;
    TIM3->CR1 |= TIM_CR1_CEN;

  //  NVIC_
    NVIC_SetPriority(TIM3_IRQn,250);
    NVIC_EnableIRQ(TIM3_IRQn);

//	TIM4->ARR = 1000;
//	TIM4->PSC = 7100;
//	TIM4->DIER |= TIM_DIER_UIE;
//	TIM4->CR1 |= TIM_CR1_ARPE;
//	TIM4->CR1 |= TIM_CR1_CEN;
//
//    NVIC_SetPriority(TIM4_IRQn,255);	//100ms
//    NVIC_EnableIRQ(TIM4_IRQn);

   // IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);
   // IWDG_SetPrescaler(IWDG_Prescaler_16);
  //  IWDG_SetReload(0x0FFF);
   // IWDG_Enable();

};

void InitGPIO(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;              // enable clock for port A
    RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;              // enable clock for port B
    RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;              // enable clock for port C


    GPIOC->CRH &= ~GPIO_CRH_CNF8;
    GPIOC->CRH |= GPIO_CRH_MODE8_0;

    GPIOC->CRH &= ~GPIO_CRH_CNF9;
    GPIOC->CRH |= GPIO_CRH_MODE9_0;

    GPIOC->CRL &= ~GPIO_CRL_CNF0;
    GPIOC->CRL &= ~GPIO_CRL_MODE0;

    GPIOC->CRH &= ~GPIO_CRH_CNF13;	//LED on board
    GPIOC->CRH |= GPIO_CRH_MODE13;

    GPIOB->CRL &= ~(GPIO_CRL_CNF0 | GPIO_CRL_CNF1);
    GPIOB->CRL |= GPIO_CRL_MODE0 | GPIO_CRL_MODE1;

#ifdef USE_DISPLAY_PARALLEL

    //6 Digits 7-segment display
    //PA0-PA7 segments
    //PB10-PB15 digits
    Display_port->CRL &= ~(GPIO_CRL_CNF);	//Reset all
    Display_port->CRL |= (GPIO_CRL_MODE);	//Set all

    GPIOB->CRH &= ~(GPIO_CRH_CNF10 | GPIO_CRH_CNF11 | GPIO_CRH_CNF12 | GPIO_CRH_CNF13 | GPIO_CRH_CNF14 | GPIO_CRH_CNF15 );
    GPIOB->CRH |= (GPIO_CRH_MODE10 | GPIO_CRH_MODE11 | GPIO_CRH_MODE12 | GPIO_CRH_MODE13 | GPIO_CRH_MODE14 | GPIO_CRH_MODE15);
#endif

#if defined  (USE_DISPLAY_SERIAL) || defined (USE_DISPLAY_LCD_6)

    GPIOA->CRL &= ~GPIO_CRL_CNF6;	//Disp_RCK
    GPIOA->CRL |= GPIO_CRL_MODE6; 	//OUT

    GPIOA->CRL	&= ~(GPIO_CRL_CNF7 | GPIO_CRL_CNF5);
    GPIOA->CRL	|= GPIO_CRL_CNF7_1 | GPIO_CRL_MODE7 | GPIO_CRL_CNF5_1 | GPIO_CRL_MODE5;	//SPI1_MOSI
#endif

#ifdef USE_DISPLAY_GR

    //PA0-PA7 D0-D7
    //PB0 - CS1
    //PB1 - CS2
    //PB10 - D/I
    //PB11 - R/!W
    //PB12 - E

    GPIOA->CRL &= ~(GPIO_CRL_CNF);	//Reset all
    GPIOA->CRL |= (GPIO_CRL_MODE);	//Set all

    GPIOB->CRH &= ~(GPIO_CRH_CNF10 | GPIO_CRH_CNF11 | GPIO_CRH_CNF12);	//PB10-PB12
    GPIOB->CRH |= (GPIO_CRH_MODE10 | GPIO_CRH_MODE11 | GPIO_CRH_MODE12); //PB10-PB12

    GPIOB->CRL &= ~(GPIO_CRL_CNF0 | GPIO_CRL_CNF1);
    GPIOB->CRL |= (GPIO_CRL_MODE0 | GPIO_CRL_MODE1);

#endif

    GPIOB->CRH &= ~(GPIO_CRH_CNF8 | GPIO_CRH_MODE8);
    GPIOB->CRH |= GPIO_CRH_CNF8_1 ;
    GPIOB->ODR |= GPIO_ODR_ODR8;
    //GPIOB->CRH |= GPIO_CRH_MODE8_0;
    GPIOB->CRH &= ~GPIO_CRH_CNF9;
    GPIOB->CRH |= GPIO_CRH_MODE9 | GPIO_CRH_CNF9_1;


    AFIO->MAPR |= AFIO_MAPR_CAN_REMAP_REMAP2; /*!< CANRX mapped to PB8, CANTX mapped to PB9 */

    GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_8;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IPU;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

};

void InitSPI(void)

{

#ifdef USE_DISPLAY_LCD_6
	SPI1->CR1 |= (SPI_CR1_BIDIOE  | SPI_CR1_BR_2 | SPI_CR1_MSTR | SPI_CR1_SSI | SPI_CR1_SSM | SPI_CR1_BIDIMODE );
#else
    SPI1->CR1 |= (SPI_CR1_BIDIOE | SPI_CR1_DFF | SPI_CR1_BR_2 | SPI_CR1_MSTR | SPI_CR1_SSI | SPI_CR1_SSM | SPI_CR1_BIDIMODE);
#endif
    SPI1->CR1 |= SPI_CR1_SPE;

};

void InitCAN (void)
    {


    };
