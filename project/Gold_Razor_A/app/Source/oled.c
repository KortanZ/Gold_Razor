//////////////////////////////////////////////////////////////////////////////////
//������ֻ��ѧϰʹ�ã�δ���������ɣ��������������κ���;
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
//******************************************************************************/��
#include "oled.h"
//#include "stdlib.h"
#include "oledfont.h"
//#include "delay.h"
//OLED���Դ�
//��Ÿ�ʽ����.
//[0]0 1 2 3 ... 127
//[1]0 1 2 3 ... 127
//[2]0 1 2 3 ... 127
//[3]0 1 2 3 ... 127
//[4]0 1 2 3 ... 127
//[5]0 1 2 3 ... 127
//[6]0 1 2 3 ... 127
//[7]0 1 2 3 ... 127
void delay_ms(unsigned int ms)
{
	unsigned int a;
	while (ms)
	{
		a = 1800;
		while (a--);
		ms--;
	}
	return;
}
#if OLED_MODE==1
//��SSD1106д��һ���ֽڡ�
//dat:Ҫд�������/����
//cmd:����/�����־ 0,��ʾ����;1,��ʾ����;
void OLED_WR_Byte(u8 dat, u8 cmd)
{
	DATAOUT(dat);
	if (cmd)
		OLED_DC_Set();
	else
		OLED_DC_Clr();
	OLED_CS_Clr();
	OLED_WR_Clr();
	OLED_WR_Set();
	OLED_CS_Set();
	OLED_DC_Set();
}
#else
//��SSD1306д��һ���ֽڡ�
//dat:Ҫд�������/����
//cmd:����/�����־ 0,��ʾ����;1,��ʾ����;
void OLED_WR_Byte(u8 dat, u8 cmd)
{
	u8 i;
	if (cmd)
		OLED_DC_Set();
	else
		OLED_DC_Clr();
	OLED_CS_Clr();
	for (i = 0; i<8; i++)
	{
		OLED_SCLK_Clr();
		if (dat & 0x80)
			OLED_SDIN_Set();
		else
			OLED_SDIN_Clr();
		OLED_SCLK_Set();
		dat <<= 1;
	}

	OLED_SCLK_Clr();
	OLED_CS_Set();
	OLED_DC_Set();
}

#endif
void OLED_Set_Pos(unsigned char x, unsigned char y)
{
	OLED_WR_Byte(0xb0 + y, OLED_CMD);
	OLED_WR_Byte(((x & 0xf0) >> 4) | 0x10, OLED_CMD);
	OLED_WR_Byte((x & 0x0f), OLED_CMD);
}
//����OLED��ʾ
void OLED_Display_On(void)
{
	OLED_WR_Byte(0X8D, OLED_CMD);  //SET DCDC����
	OLED_WR_Byte(0X14, OLED_CMD);  //DCDC ON
	OLED_WR_Byte(0XAF, OLED_CMD);  //DISPLAY ON
}
//�ر�OLED��ʾ
void OLED_Display_Off(void)
{
	OLED_WR_Byte(0X8D, OLED_CMD);  //SET DCDC����
	OLED_WR_Byte(0X10, OLED_CMD);  //DCDC OFF
	OLED_WR_Byte(0XAE, OLED_CMD);  //DISPLAY OFF
}
//��������,������,������Ļ�Ǻ�ɫ��!��û����һ��!!!
void OLED_Clear(void)
{
	u8 i, n;
	for (i = 0; i<8; i++)
	{
		OLED_WR_Byte(0xb0 + i, OLED_CMD);    //����ҳ��ַ��0~7��
		OLED_WR_Byte(0x00, OLED_CMD);      //������ʾλ�á��е͵�ַ
		OLED_WR_Byte(0x10, OLED_CMD);      //������ʾλ�á��иߵ�ַ
		for (n = 0; n<128; n++)OLED_WR_Byte(0, OLED_DATA);
	} //������ʾ
}

void OLED_ClearLine(u8 y)
{
	unsigned char i = 0;
	if (SIZE == 16)
	{
		OLED_Set_Pos(0, y);
		for (i = 0; i<128; i++)
			OLED_WR_Byte(0x00, OLED_DATA);
		OLED_Set_Pos(0, y + 1);
		for (i = 0; i<128; i++)
			OLED_WR_Byte(0x00, OLED_DATA);
	}
	else {
		OLED_Set_Pos(0, y + 1);
		for (i = 0; i<128; i++)
			OLED_WR_Byte(0x00, OLED_DATA);

	}
}

void OLED_DrawPoint(u8 x, u8 y, u8 cmd)
{
	static uint8 imgMap[8][128] = { 0 };
	uint8 i, j;
	if (cmd)
	{

		imgMap[y / 8][x] = imgMap[y / 8][x] | (0x01 << (y % 8));
		OLED_Set_Pos(x, y / 8);
		OLED_WR_Byte(imgMap[y / 8][x], OLED_DATA);
	}
	else
	{

		for (i = 0; i < 8; i++)
		for (j = 0; j < 128; j++)
		{
			imgMap[i][j] = 0x00;
			OLED_Set_Pos(j, i);
			OLED_WR_Byte(imgMap[i][j], OLED_DATA);
		}
	}

}


//��ָ��λ����ʾһ���ַ�,���������ַ�
//x:0~127
//y:0~63
//mode:0,������ʾ;1,������ʾ
//size:ѡ������ 16/12
void OLED_ShowChar(u8 x, u8 y, u8 chr)
{
	unsigned char c = 0, i = 0;
	c = chr - ' ';//�õ�ƫ�ƺ��ֵ
	if (x>Max_Column - 1){ x = 0; y = y + 2; }
	if (SIZE == 16)
	{
		OLED_Set_Pos(x, y);
		for (i = 0; i<8; i++)
			OLED_WR_Byte(F8X16[c * 16 + i], OLED_DATA);
		OLED_Set_Pos(x, y + 1);
		for (i = 0; i<8; i++)
			OLED_WR_Byte(F8X16[c * 16 + i + 8], OLED_DATA);
	}
	else {
		OLED_Set_Pos(x, y + 1);
		for (i = 0; i<6; i++)
			OLED_WR_Byte(F6x8[c][i], OLED_DATA);

	}
}


//m^n����
u32 oled_pow(u8 m, u8 n)
{
	u32 result = 1;
	while (n--)result *= m;
	return result;
}
//��ʾ2������
//x,y :�������
//len :���ֵ�λ��
//size:�����С
//mode:ģʽ	0,���ģʽ;1,����ģʽ
//num:��ֵ(0~4294967295);
void OLED_ShowNum(u8 x, u8 y, int32 num, u8 len)
{
	u8 t, temp;
	u8 enshow = 0;

	for (t = 0; t<len; t++)
	{
		temp = ((num >= 0 ? num : -num) / oled_pow(10, len - t - 1)) % 10;
		if (enshow == 0 && t<(len - 1))
		{
			if (temp == 0)
			{
				OLED_ShowChar(x + (Num_Size / 2)*t, y, ' ');
				continue;
			}
			else
			{
				if(num < 0)
					OLED_ShowChar(x + (Num_Size / 2)*(t - 1), y, '-');
				enshow = 1;
			}

		}
		OLED_ShowChar(x + (Num_Size / 2)*t, y, temp + '0');
	}

}
void OLED_NumClear(u8 x, u8 y, u8 len)
{
	u8 t;
	for (t = 0; t<len; t++)
	{
		OLED_ShowChar(x + (Num_Size / 2)*t, y, ' ');
	}

}

//��ʾһ���ַ��Ŵ�
void OLED_ShowString(u8 x, u8 y, u8 *chr)
{
	unsigned char j = 0;
	while (chr[j] != '\0')
	{
		OLED_ShowChar(x, y, chr[j]);
		x += 8;
		if (x>120){ x = 0; y += 2; }
		j++;
	}
}

/***********������������ʾ��ʾBMPͼƬ128��64��ʼ������(x,y),x�ķ�Χ0��127��yΪҳ�ķ�Χ0��7*****************/
void OLED_DrawBMP(unsigned char x0, unsigned char y0, unsigned char x1, unsigned char y1, const unsigned char BMP[])
{
	unsigned int j = 0;
	unsigned char x, y;
	for (y = y0; y<y1; y++)
	{
		OLED_Set_Pos(x0, y);
		for (x = x0; x<x1; x++)
		{
			OLED_WR_Byte(BMP[j++], OLED_DATA);
		}
	}
}
void OLED_PinInit(void)
{

	GPIO_InitTypeDef gpio_init_struct;
	gpio_init_struct.GPIO_PTx = PTB;
	gpio_init_struct.GPIO_Pins = GPIO_Pin20 | GPIO_Pin21 | GPIO_Pin22;
	gpio_init_struct.GPIO_Dir = DIR_OUTPUT;
	gpio_init_struct.GPIO_Output = OUTPUT_H;
	gpio_init_struct.GPIO_PinControl = IRQC_DIS;
	LPLD_GPIO_Init(gpio_init_struct);

	gpio_init_struct.GPIO_PTx = PTD;
	gpio_init_struct.GPIO_Pins = GPIO_Pin8 | GPIO_Pin9;
	gpio_init_struct.GPIO_Dir = DIR_OUTPUT;
	gpio_init_struct.GPIO_Output = OUTPUT_H;
	gpio_init_struct.GPIO_PinControl = IRQC_DIS;
	LPLD_GPIO_Init(gpio_init_struct);
}


//��ʼ��SSD1306
void OLED_Init(void)
{


	OLED_PinInit();
	OLED_RST_Set();
	delay_ms(100);
	OLED_RST_Clr();
	delay_ms(100);
	OLED_RST_Set();
	/*
	OLED_WR_Byte(0xAE,OLED_CMD);//--turn off oled panel
	OLED_WR_Byte(0x00,OLED_CMD);//---set low column address
	OLED_WR_Byte(0x10,OLED_CMD);//---set high column address
	OLED_WR_Byte(0x40,OLED_CMD);//--set start line address  Set Mapping RAM Display Start Line (0x00~0x3F)
	OLED_WR_Byte(0x81,OLED_CMD);//--set contrast control register
	OLED_WR_Byte(0xCF,OLED_CMD); // Set SEG Output Current Brightness
	OLED_WR_Byte(0xA1,OLED_CMD);//--Set SEG/Column Mapping     0xa0���ҷ��� 0xa1����
	OLED_WR_Byte(0xC8,OLED_CMD);//Set COM/Row Scan Direction   0xc0���·��� 0xc8����
	OLED_WR_Byte(0xA6,OLED_CMD);//--set normal display
	OLED_WR_Byte(0xA8,OLED_CMD);//--set multiplex ratio(1 to 64)
	OLED_WR_Byte(0x3f,OLED_CMD);//--1/64 duty
	OLED_WR_Byte(0xD3,OLED_CMD);//-set display offset	Shift Mapping RAM Counter (0x00~0x3F)
	OLED_WR_Byte(0x00,OLED_CMD);//-not offset
	OLED_WR_Byte(0xd5,OLED_CMD);//--set display clock divide ratio/oscillator frequency
	OLED_WR_Byte(0x80,OLED_CMD);//--set divide ratio, Set Clock as 100 Frames/Sec
	OLED_WR_Byte(0xD9,OLED_CMD);//--set pre-charge period
	OLED_WR_Byte(0xF1,OLED_CMD);//Set Pre-Charge as 15 Clocks & Discharge as 1 Clock
	OLED_WR_Byte(0xDA,OLED_CMD);//--set com pins hardware configuration
	OLED_WR_Byte(0x12,OLED_CMD);
	OLED_WR_Byte(0xDB,OLED_CMD);//--set vcomh
	OLED_WR_Byte(0x40,OLED_CMD);//Set VCOM Deselect Level
	OLED_WR_Byte(0x20,OLED_CMD);//-Set Page Addressing Mode (0x00/0x01/0x02)
	OLED_WR_Byte(0x02,OLED_CMD);//
	OLED_WR_Byte(0x8D,OLED_CMD);//--set Charge Pump enable/disable
	OLED_WR_Byte(0x14,OLED_CMD);//--set(0x10) disable
	OLED_WR_Byte(0xA4,OLED_CMD);// Disable Entire Display On (0xa4/0xa5)
	OLED_WR_Byte(0xA6,OLED_CMD);// Disable Inverse Display On (0xa6/a7)
	OLED_WR_Byte(0xAF,OLED_CMD);//--turn on oled panel
	*/

	OLED_WR_Byte(0xAE, OLED_CMD);//--turn off oled panel
	OLED_WR_Byte(0x00, OLED_CMD);//---set low column address
	OLED_WR_Byte(0x10, OLED_CMD);//---set high column address
	OLED_WR_Byte(0x40, OLED_CMD);//--set start line address  Set Mapping RAM Display Start Line (0x00~0x3F)
	OLED_WR_Byte(0x81, OLED_CMD);//--set contrast control register
	OLED_WR_Byte(0xCF, OLED_CMD); // Set SEG Output Current Brightness
	OLED_WR_Byte(0xA1, OLED_CMD);//--Set SEG/Column Mapping     0xa0���ҷ��� 0xa1����
	OLED_WR_Byte(0xC8, OLED_CMD);//Set COM/Row Scan Direction   0xc0���·��� 0xc8����
	OLED_WR_Byte(0xA6, OLED_CMD);//--set normal display
	OLED_WR_Byte(0xA8, OLED_CMD);//--set multiplex ratio(1 to 64)
	OLED_WR_Byte(0x3f, OLED_CMD);//--1/64 duty
	OLED_WR_Byte(0xD3, OLED_CMD);//-set display offset	Shift Mapping RAM Counter (0x00~0x3F)
	OLED_WR_Byte(0x00, OLED_CMD);//-not offset
	OLED_WR_Byte(0xd5, OLED_CMD);//--set display clock divide ratio/oscillator frequency
	OLED_WR_Byte(0x80, OLED_CMD);//--set divide ratio, Set Clock as 100 Frames/Sec
	OLED_WR_Byte(0xD9, OLED_CMD);//--set pre-charge period
	OLED_WR_Byte(0xF1, OLED_CMD);//Set Pre-Charge as 15 Clocks & Discharge as 1 Clock
	OLED_WR_Byte(0xDA, OLED_CMD);//--set com pins hardware configuration
	OLED_WR_Byte(0x12, OLED_CMD);
	OLED_WR_Byte(0xDB, OLED_CMD);//--set vcomh
	OLED_WR_Byte(0x40, OLED_CMD);//Set VCOM Deselect Level
	OLED_WR_Byte(0x01, OLED_CMD);//-Set Page Addressing Mode (0x00/0x01/0x02)
	OLED_WR_Byte(0x02, OLED_CMD);//
	OLED_WR_Byte(0x8D, OLED_CMD);//--set Charge Pump enable/disable
	OLED_WR_Byte(0x14, OLED_CMD);//--set(0x10) disable
	OLED_WR_Byte(0xA4, OLED_CMD);// Disable Entire Display On (0xa4/0xa5)
	OLED_WR_Byte(0xA6, OLED_CMD);// Disable Inverse Display On (0xa6/a7)
	OLED_WR_Byte(0xAF, OLED_CMD);//--turn on oled panel

	OLED_WR_Byte(0xAF, OLED_CMD); /*display ON*/
}
