//-------------------------------------------------------------------------------------------------
// Universal KS0108 driver library
// (c) Rados�aw Kwiecie�, radek@dxp.pl
//-------------------------------------------------------------------------------------------------
#include "KS0108.h"
#include "font5x8.h"
#include "font20x32.h"
#include "stm32f10x.h"

//-------------------------------------------------------------------------------------------------
extern void GLCD_InitalizePorts(void);
//-------------------------------------------------------------------------------------------------
unsigned char screen_x = 0, screen_y = 0, char_index=0;
//-------------------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------------------
void GLCD_Initalize(void)
{
unsigned char i;
//GLCD_InitalizePorts();
for(i = 0; i < 3; i++)
  GLCD_WriteCommand((DISPLAY_ON_CMD | ON), i);
}
//-------------------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------------------
void GLCD_GoTo(unsigned char x, unsigned char y)
{
unsigned char i;
screen_x = x;
screen_y = y;

for(i = 0; i < KS0108_SCREEN_WIDTH/64; i++)
  {
  GLCD_WriteCommand(DISPLAY_SET_Y | 0,i);
  GLCD_WriteCommand(DISPLAY_SET_X | y,i);
  GLCD_WriteCommand(DISPLAY_START_LINE | 0,i);
  }
GLCD_WriteCommand(DISPLAY_SET_Y | (x % 64), (x / 64));
GLCD_WriteCommand(DISPLAY_SET_X | y, (x / 64));
}
//-------------------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------------------
void GLCD_ClearScreen(void)
{
unsigned char i, j;
for(j = 0; j < KS0108_SCREEN_HEIGHT/8; j++)
  {
  GLCD_GoTo(0,j);
  for(i = 0; i < KS0108_SCREEN_WIDTH; i++)
    GLCD_WriteData(0x00);
  }
}
//-------------------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------------------
void GLCD_WriteChar(char charToWrite)
{
int i;
charToWrite -= 32; 
for(i = 0; i < 5; i++)
  GLCD_WriteData(GLCD_ReadByteFromROMMemory((char *)((int)font5x8 + (5 * charToWrite) + i)));
GLCD_WriteData(0x00);
}

//-------------------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------------------
void GLCD_WriteChar_BIG(char charToWrite)
{
int i,j=0;
unsigned int xx,yy;

yy = screen_y;
xx = screen_x;
charToWrite -= 32;
for(i = 1; i < 80; i++)
{
  GLCD_WriteData(GLCD_ReadByteFromROMMemory((char *)((uint32_t)Ubuntu20x32 + (81 * charToWrite) + i)));
//GLCD_WriteData(0xFF);
  if (i % 20==0 && i>1)
	  {
	  GLCD_GoTo(xx,screen_y+1);
	//  if (j++>2)
	 // {
	//	  GLCD_GoTo(xx=screen_x+5,yy);
//		  j=0;
	//  }

	  }
}
GLCD_WriteData(0x00);
GLCD_GoTo(xx+20,yy);
}
//-------------------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------------------
void GLCD_WriteString(char * stringToWrite)
{
while(*stringToWrite)
  GLCD_WriteChar(*stringToWrite++);
}

//-------------------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------------------
void GLCD_WriteString_BIG(char * stringToWrite)
{
	char_index =0;
while(*stringToWrite)
{
  GLCD_WriteChar_BIG(*stringToWrite++);
  char_index++;
};
}
//-------------------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------------------
void GLCD_SetPixel(unsigned char x, unsigned char y, unsigned char color)
{
unsigned char tmp;
GLCD_GoTo(x, (y / 8));
tmp = GLCD_ReadData();
GLCD_GoTo(x, (y / 8));
tmp = GLCD_ReadData();
GLCD_GoTo(x, (y / 8));
tmp |= (1 << (y % 8));
GLCD_WriteData(tmp);
}
//-------------------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------------------
void GLCD_Bitmap(char * bmp, unsigned char x, unsigned char y, unsigned char dx, unsigned char dy)
{
unsigned char i, j;
for(j = 0; j < dy / 8; j++)
  {
  GLCD_GoTo(x,y + j);
  for(i = 0; i < dx; i++) 
    GLCD_WriteData(GLCD_ReadByteFromROMMemory(bmp++));
  }
}
//-------------------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------------------





