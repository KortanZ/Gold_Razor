//////////////////////////////////////////////////////////////////////////////////
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//�о�԰����
//���̵�ַ��http://shop73023976.taobao.com/?spm=2013.1.0.0.M4PqC2
//
//  �� �� ��   : main.c
//  �� �� ��   : v2.0
//  ��    ��   : HuangKai
//  ��������   : 2014-0101
//  ����޸�   :
//  ��������   : OLED 4�ӿ���ʾ����(51ϵ��)
//              ˵��:
//              ----------------------------------------------------------------
//              GND    ��Դ��
//              VCC  ��5V��3.3v��Դ
//              D0   P1^0��SCL��
//              D1   P1^1��SDA��
//              RES  ��P12
//              DC   ��P13
//              CS   ��P14
//              ----------------------------------------------------------------
// �޸���ʷ   :
// ��    ��   :
// ��    ��   : HuangKai
// �޸�����   : �����ļ�
//��Ȩ���У�����ؾ���
//Copyright(C) �о�԰����2014/3/16
//All rights reserved
//******************************************************************************/

#ifndef __OLED_H
#define __OLED_H

#include "common.h"
#define  u8 unsigned char
#define  u32 unsigned int
#define OLED_CMD  0	//д����
#define OLED_DATA 1	//д����
#define OLED_MODE 0

#define OLED_CS PTD,8   //Ƭѡ
#define OLED_RST PTB,22 //��λ
#define OLED_DC PTD,9   //����/�������
#define OLED_SCLK PTB,21 //ʱ�� D0��SCLK)
#define OLED_SDIN PTB,20//D1��MOSI�� ����


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





//OLEDģʽ����
//0:4�ߴ���ģʽ
//1:����8080ģʽ

#define SIZE 8
#define Num_Size 12
#define Num_Len 4
#define XLevelL		0x02
#define XLevelH		0x10
#define Max_Column	128
#define Max_Row		64
#define	Brightness	0xFF
#define X_WIDTH 	128
#define Y_WIDTH 	64
//-----------------OLED�˿ڶ���----------------

void delay_ms(unsigned int ms);




//OLED�����ú���
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




