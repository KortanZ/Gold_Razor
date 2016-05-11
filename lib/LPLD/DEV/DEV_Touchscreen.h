/**
 * @file DEV_Touchscreen.h
 * @version 1.0[By LPLD]
 * @date 2013-09-24
 * @brief Touchscreen�豸��������
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

#ifndef __DEV_TOUCHSCREEN_H__
#define __DEV_TOUCHSCREEN_H__

#include "common.h"
#include "HW_SPI.h"

/********�û����޸�ֵ ��ʼ**********/
//ѡ��TOUCHSCREENʹ�õ�SPIģ��
#define TOUCHSCREEN_SPIX    (SPI2)

//ѡ��TOUCHSCREEN MOSI����Ӧ��IO
#define TOUCHSCREEN_MOSI  (PTD13)

//ѡ��TOUCHSCREEN MISO����Ӧ��IO
#define TOUCHSCREEN_MISO  (PTD14)

//ѡ��TOUCHSCREEN SCK����Ӧ��IO
#define TOUCHSCREEN_SCK  (PTD12)

//ѡ��TOUCHSCREEN PCS0����Ӧ��IO
#define TOUCHSCREEN_PCS0  (PTD11)

//==========����ADS7843���Ϳ���ָ��===================
//ADS7843���Ϳ��������ʽ��
//bit7 bit6  bit5 bit4 bit3    bit2 bit1 bit0
//   S   A2    A1   A0 MODE SER/DFR  PD1  PD0

/*A2  A1  A0 SER/ DFR  AnalogInput  X Sw  Y Sw  +REF   �CREF
* 0   0   1   1        X+           OFF   ON    VREF   GND  
* 0   1   0   1        IN3          OFF   OFF   VREF   GND  
* 1   0   1   1        Y+           ON    OFF   VREF   GND  
* 1   1   0   1        IN4          OFF   OFF   VREF   GND  
* 0   0   1   0        X+           OFF   ON    Y+     Y?  
* 1   0   1   0        Y+           ON    OFF   X+     X? 
* 1   1   0   0        Outputs Identity Code, 1000 0000 0000*/   

#define CHIP_ID      (0x0800)
//���忪ʼ��־
#define INIT_START   (0x80)
//����X��Y ����
#define Y_SWITCH_ON  (0x10)
#define X_SWITCH_ON  (0x50)
#define ID_CODE      (0x60)
//����ת��ģʽ
#define MODE_8BITS   (0x08)
#define MODE_12BITS  (0x00)
//���嵥��/���ģʽ
#define SINGLEEND    (0x04)
#define DIFFERENTIAL (0x00)
//���幦��ģʽ��PENIRQ�Ƿ�����
#define POWERDOWN_ENABLE_PENIRQ   (0x00)//��ת�����оƬPOWERDOWN PENIRQʹ��
#define POWERDOWN_DISABLED_PENIRQ (0x01)//��ת�����оƬPOWERDOWN PENIRQ��ֹ
#define POWERUP_ENABLE_PENIRQ     (0x02)//��ת�����оƬ����POWERUP PENIRQʹ��
#define POWERUP_DISABLED_PENIRQ   (0x03)//��ת�����оƬ����POWERUP PENIRQ��ֹ

//���ó�X��ɼ���12λ���ȡ����ˡ�����POWERUPģʽ��PENIRQ��ֹ
#define LPLD_SER_SAMPLE_X   (INIT_START|X_SWITCH_ON|MODE_12BITS|SINGLEEND|POWERDOWN_ENABLE_PENIRQ)//11010111B
//���ó�Y��ɼ���12λ���ȡ����ˡ�����POWERUPģʽ��PENIRQ��ֹ  
#define LPLD_SER_SAMPLE_Y   (INIT_START|Y_SWITCH_ON|MODE_12BITS|SINGLEEND|POWERDOWN_ENABLE_PENIRQ)//10010111B 
//��ȡID
#define LPLD_GET_CHIPID (INIT_START|ID_CODE|MODE_12BITS|DIFFERENTIAL|POWERUP_DISABLED_PENIRQ)
//
#define LPLD_CMD_DUMMY       0x00

/********�û����޸�ֵ ����**********/

//Touchscreen��ʼ������
void LPLD_Touchscreen_Init (void);
//Touchscreen���X��Y��λ��ADת���������
uint16 LPLD_Touchscreen_GetResult(uint8);
//Touchscreen���������
void LPLD_Touchscreen_SendCmd(uint8,uint8);
//Touchscreen���ת���������
uint8 LPLD_Touchscreen_GetCovValue(uint8,uint8);

#endif