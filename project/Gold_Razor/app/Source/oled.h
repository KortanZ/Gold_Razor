//////////////////////////////////////////////////////////////////////////////////
//±¾³ÌÐòÖ»¹©Ñ§Ï°Ê¹ÓÃ£¬Î´¾­×÷ÕßÐí¿É£¬²»µÃÓÃÓÚÆäËüÈÎºÎÓÃÍ¾
//ÖÐ¾°Ô°µç×Ó
//µêÆÌµØÖ·£ºhttp://shop73023976.taobao.com/?spm=2013.1.0.0.M4PqC2
//
//  ÎÄ ¼þ Ãû   : main.c
//  °æ ±¾ ºÅ   : v2.0
//  ×÷    Õß   : HuangKai
//  Éú³ÉÈÕÆÚ   : 2014-0101
//  ×î½üÐÞ¸Ä   :
//  ¹¦ÄÜÃèÊö   : OLED 4½Ó¿ÚÑÝÊ¾Àý³Ì(51ÏµÁÐ)
//              ËµÃ÷:
//              ----------------------------------------------------------------
//              GND    µçÔ´µØ
//              VCC  ½Ó5V»ò3.3vµçÔ´
//              D0   P1^0£¨SCL£©
//              D1   P1^1£¨SDA£©
//              RES  ½ÓP12
//              DC   ½ÓP13
//              CS   ½ÓP14
//              ----------------------------------------------------------------
// ÐÞ¸ÄÀúÊ·   :
// ÈÕ    ÆÚ   :
// ×÷    Õß   : HuangKai
// ÐÞ¸ÄÄÚÈÝ   : ´´½¨ÎÄ¼þ
//°æÈ¨ËùÓÐ£¬µÁ°æ±Ø¾¿¡£
//Copyright(C) ÖÐ¾°Ô°µç×Ó2014/3/16
//All rights reserved
//******************************************************************************/

#ifndef __OLED_H
#define __OLED_H

#include "common.h"
#define  u8 unsigned char
#define  u32 unsigned int
#define OLED_CMD  0	//Ð´ÃüÁî
#define OLED_DATA 1	//Ð´Êý¾Ý
#define OLED_MODE 0

#define OLED_CS PTD,8   //Æ¬Ñ¡
#define OLED_RST PTB,22 //¸´Î»
#define OLED_DC PTD,9   //Êý¾Ý/ÃüÁî¿ØÖÆ
#define OLED_SCLK PTB,21 //Ê±ÖÓ D0£¨SCLK)
#define OLED_SDIN PTB,20//D1£¨MOSI£© Êý¾Ý


#define OLED_CS_Clr()  LPLD_GPIO_Output_b(OLED_CS,0)
#define OLED_CS_Set()  LPLD_GPIO_Output_b(OLED_CS,1)

#define OLED_RST_Clr() LPLD_GPIO_Output_b(OLED_RST,0)
#define OLED_RST_Set() LPLD_GPIO_Output_b(OLED_RST,1)

#define OLED_DC_Clr() LPLD_GPIO_Output_b(OLED_DC,0)
#define OLED_DC_Set() LPLD_GPIO_Output_b(OLED_DC,1)

#define OLED_SCLK_Clr() LPLD_GPIO_Output_b(OLED_SCLK,0)
#define OLED_SCLK_Set() LPLD_GPIO_Output_b(OLED_SCLK,1)

#define OLED_SDIN_Clr() LPLD_GPIO_Output_b(OLED_SDIN,0)
#define OLED_SDIN_Set() LPLD_GPIO_Output_b(OLED_SDIN,1)





//OLEDÄ£Ê½ÉèÖÃ
//0:4Ïß´®ÐÐÄ£Ê½
//1:²¢ÐÐ8080Ä£Ê½

#define SIZE 8
#define Num_Size 12
#define Num_Len 5
#define XLevelL		0x02
#define XLevelH		0x10
#define Max_Column	128
#define Max_Row		64
#define	Brightness	0xFF
#define X_WIDTH 	128
#define Y_WIDTH 	64
//-----------------OLED¶Ë¿Ú¶¨Òå----------------

void delay_ms(unsigned int ms);




//OLED¿ØÖÆÓÃº¯Êý
void OLED_WR_Byte(u8 dat,u8 cmd);
void OLED_Display_On(void);
void OLED_Display_Off(void);
void OLED_Init(void);
void OLED_Clear(void);
void OLED_DrawPoint(u8 x,u8 y, u8 cmd);
void OLED_ShowChar(u8 x,u8 y,u8 chr);
void OLED_ShowNum(u8 x,u8 y,u32 num,u8 len);
void OLED_NumClear(u8 x,u8 y,u8 len);
void OLED_ShowString(u8 x,u8 y, u8 *p);
void OLED_Set_Pos(unsigned char x, unsigned char y);
void OLED_ShowCHinese(u8 x,u8 y,u8 no);
void OLED_DrawBMP(unsigned char x0, unsigned char y0,unsigned char x1, unsigned char y1,const unsigned char BMP[]);

#endif




