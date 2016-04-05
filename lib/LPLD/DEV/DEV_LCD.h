/**
 * @file DEV_LCD.h
 * @version 0.1[By LPLD]
 * @date 2013-09-24
 * @brief LCD�豸��������
 *
 * ���Ľ���:�ɸ���ʵ��Ӳ���޸�
 *
 * ��Ȩ����:�����������µ��Ӽ������޹�˾
 * http://www.lpld.cn
 * mail:support@lpld.cn
 *
 * @par
 * ����������������[LPLD]������ά������������ʹ���߿���Դ���롣
 * �����߿���������ʹ�û��Դ���롣�����μ�����ע��Ӧ���Ա�����
 * ���ø��Ļ�ɾ��ԭ��Ȩ���������������ο����߿��Լ�ע���ΰ�Ȩ�����ߡ�
 * ��Ӧ�����ش�Э��Ļ����ϣ�����Դ���롢���ó��۴��뱾��
 * �������²���������ʹ�ñ��������������κ��¹ʡ��������λ���ز���Ӱ�졣
 * ����������������͡�˵��������ľ���ԭ�����ܡ�ʵ�ַ�����
 * ������������[LPLD]��Ȩ�������߲��ý�������������ҵ��Ʒ��
 */
#ifndef __DEV_LCD_H__
#define __DEV_LCD_H__

#include "common.h"

/********�û����޸�ֵ ��ʼ***********/
//LCD������ʾ����1Ϊ����0Ϊ����
#define HORIZONTAL  1    
//LCDָ�����߻���ַ
#define LCD_CMD_ADDRESS   (0x60000000)
//LCD�������߻���ַ
#define LCD_DATA_ADDRESS  (0x60010000)
//LCD��λ����
#define LCD_SET_RST       PTC19_O=1
#define LCD_CLR_RST       PTC19_O=0
//д�Ĵ��������ʱ
#define LCD_DELAY_TIME    2
/********�û����޸�ֵ ����***********/
#if  ( HORIZONTAL == 1 )
#define  MAX_X  320
#define  MAX_Y  240   
#else
#define  MAX_X  240
#define  MAX_Y  320   
#endif

/* LCD color */
#define COLOR_White          0xFFFF
#define COLOR_Black          0x0000
#define COLOR_Gray           0xF7DE
#define COLOR_Blue           0x001F
#define COLOR_Blue2          0x051F
#define COLOR_Red            0xF800
#define COLOR_Magenta        0xF81F
#define COLOR_Green          0x07E0
#define COLOR_Cyan           0x7FFF
#define COLOR_Yellow         0xFFE0

//R��G��Bת16λRGB
#define RGB565CONVERT(red, green, blue)\
(uint16)( (( red   >> 3 ) << 11 ) | \
(( green >> 2 ) << 5  ) | \
( blue  >> 3 ))

//LCD�豸��Ϣ�ṹ��
typedef struct 
{
  uint16 Lcd_Id;    //LCD�豸ID
  uint16 Write_GRAM;  //дGRAM��ַ
  uint16 X_GRAM;  //GRAM ˮƽ��ַ
  uint16 Y_GRAM;  //GRAM ��ֱ��ַ
      
}LPLD_LCD_Info_t;

extern uint16 *LCD_GRAM;

//LCD��ʼ��
uint16 LPLD_LCD_Init(void);
//���LCD����ɫ
void LPLD_LCD_FillBackground(uint16);
//���LCD����ɫ��LCD_GRAM
void LPLD_LCD_FillBackgroundGRAM(uint16 *);

//ȡ��LCDĳ���16λRGBֵ
uint16 LPLD_LCD_GetPoint(uint16, uint16);
//����LCDĳ���16λRGBֵ
void LPLD_LCD_SetPoint(uint16, uint16, uint16);

//��ָ��������ʾ�ַ�
void LPLD_LCD_ShowChar(uint16, uint16, uint8, uint16, uint16);
//��ָ��������ʾ����
void LPLD_LCD_ShowNum(uint16, uint16, uint16, uint8, uint16, uint16);
//��ָ��������ʾ�ַ���
void LPLD_LCD_ShowString(uint16, uint16, uint8 *,uint16, uint16);
//����һ����ʾ�ַ���
void LPLD_LCD_PrintStringLine(uint8 *, uint16, uint16);
//���ŵ�ǰ����ʾ�ַ���
void LPLD_LCD_PrintString(uint8 *,uint16, uint16);
//����һ����ʾ����
void LPLD_LCD_PrintNumLine(uint16, uint8, uint16, uint16);
//���ŵ�ǰ����ʾ����
void LPLD_LCD_PrintNum(uint16, uint8, uint16, uint16);

//��ָ��������ʾֱ��
void LPLD_LCD_DrawLine(uint16, uint16, uint16, uint16 , uint16);
//��ָ��������ʾ������
void LPLD_LCD_DrawSquare(uint16, uint16, uint16, uint16, uint16);
//��ָ��������ʾ����
void LPLD_LCD_DrawRectangle(uint16, uint16, uint16, uint16, uint16, uint16);
//��ʾһ��ָ����С��U8�Ҷ�ͼ��
void LPLD_LCD_DrawU8Gray(uint8 *, uint16, uint16);

//���ָ����ɫ�ľ��ε�LCD_GRAM
void LPLD_LCD_GRAMFillRec(uint16, uint16, uint16, uint16, uint16);
//���ָ����ɫ�ĺ��ߵ�LCD_GRAM
void LPLD_LCD_GRAMDrawHLine(uint16, uint16, uint16, uint16);

//BGR��ɫתRGB��ɫ
uint16 LPLD_LCD_BGR2RGB(uint16);
//U8�Ҷ���ɫתΪRGB��ɫ
uint16 LPLD_LCD_U8GRAY2RGB(uint8);

//��ָ��������ʾ����
#define LPLD_LCD_DrawHLine(x0,y0,len,color) LPLD_LCD_DrawLine(x0,y0,x0+len-1,y0,color)
//��ָ��������ʾ����
#define LPLD_LCD_DrawVLine(x0,y0,len,color) LPLD_LCD_DrawLine(x0,y0,x0,y0+len-1,color)
//����LCD_GRAMĳ���16λRGBֵ
#define LPLD_LCD_SetPointGRAM(Xpos,Ypos,color) LCD_GRAM[MAX_X*MAX_Y-(Ypos-1)*MAX_Y-(Xpos)]=color

#endif 








