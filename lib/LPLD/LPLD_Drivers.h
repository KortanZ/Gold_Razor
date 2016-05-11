/**
 * @file LPLD_Drivers.h
 * @version 3.1[By LPLD]
 * @date 2015-01-11
 * @brief LPLD Kinetis������ͨ�ö�������
 *
 * ���Ľ���:�������޸�
 *
 * �ô��������������K60�̼��������ͷ�ļ���
 * ��������PORT�����ţ���ö��ֵ
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
#ifndef __LPLD_DRIVERS_H__
#define __LPLD_DRIVERS_H__

//�ײ��汾����
#define OSKinetis_Version     "3.1 b1"

//�˿�����ö�ٶ���
typedef enum PortPinsEnum
{
  //PortA
  PTA0=0,    PTA1=1,    PTA2=2,    PTA3=3,
  PTA4=4,    PTA5=5,    PTA6=6,    PTA7=7,
  PTA8=8,    PTA9=9,    PTA10=10,  PTA11=11,
  PTA12=12,  PTA13=13,  PTA14=14,  PTA15=15,
  PTA16=16,  PTA17=17,  PTA18=18,  PTA19=19,
  /********* MK60DZ10��PTA20~23 ************/
  PTA24=24,  PTA25=25,  PTA26=26,  PTA27=27,
  PTA28=28,  PTA29=29,
  /********* MK60DZ10��PTA30~31 ************/

  //PortB
  PTB0=32,   PTB1=33,   PTB2=34,   PTB3=35,
  PTB4=36,   PTB5=37,   PTB6=38,   PTB7=39,
  PTB8=40,   PTB9=41,   PTB10=42,  PTB11=43,
  /********* MK60DZ10��PTB12~15 ************/
  PTB16=48,  PTB17=49,  PTB18=50,  PTB19=51,
  PTB20=52,  PTB21=53,  PTB22=54,  PTB23=55,
  /********* MK60DZ10��PTB24~27 ************/
  /********* MK60DZ10��PTB28~31 ************/

  //PortC
  PTC0=60,   PTC1=61,   PTC2=62,   PTC3=63,
  PTC4=64,   PTC5=65,   PTC6=66,   PTC7=67,
  PTC8=68,   PTC9=69,   PTC10=70,  PTC11=71,
  PTC12=72,  PTC13=73,  PTC14=74,  PTC15=75,
  PTC16=76,  PTC17=77,  PTC18=78,  PTC19=79,
  /********* MK60DZ10��PTC20~23 ************/
  /********* MK60DZ10��PTC24~27 ************/
  /********* MK60DZ10��PTC28~31 ************/

  //PortD
  PTD0=92,   PTD1=93,   PTD2=94,   PTD3=95,
  PTD4=96,   PTD5=97,   PTD6=98,   PTD7=99,
  PTD8=100,  PTD9=101,  PTD10=102, PTD11=103,
  PTD12=104, PTD13=105, PTD14=106, PTD15=107,
  /********* MK60DZ10��PTD16~19 ************/
  /********* MK60DZ10��PTD20~23 ************/
  /********* MK60DZ10��PTD24~27 ************/
  /********* MK60DZ10��PTD28~31 ************/

  //PortE
  PTE0=124,  PTE1=125,  PTE2=126,  PTE3=127,
  PTE4=128,  PTE5=129,  PTE6=130,  PTE7=131,
  PTE8=132,  PTE9=133,  PTE10=134, PTE11=135,
#if defined(CPU_MK60F12) || defined(CPU_MK60F15)
  PTE12=136,
#endif
  /********* MK60DZ10��PTE12~15 ************/
  /********* MK60DZ10��PTE16~19 ************/
  /********* MK60DZ10��PTE20~23 ************/
  PTE24=148, PTE25=149, PTE26=150, PTE27=151,
  PTE28=152
  /********* MK60DZ10��PTE29~31 ************/
} PortPinsEnum_Type;

#include "DEV_SCCB.h"

#include "HW_MCG.h"
#include "HW_WDOG.h"
#include "HW_UART.h"
#include "HW_GPIO.h"
#include "HW_PIT.h"
#include "HW_FTM.h"
#include "HW_ADC.h"
#include "HW_DAC.h"
#include "HW_PDB.h"
#include "HW_LPTMR.h"
#include "HW_FLASH.h"
#include "HW_I2C.h"
#include "HW_CAN.h"
#include "HW_SDHC.h"
#include "HW_DMA.h"
#include "HW_RTC.h"
#include "HW_FLEXBUS.h"
#include "HW_TSI.h"
#include "HW_ENET.h"
#include "HW_SPI.h"
#include "HW_USB.h"
#include "HW_SYSTICK.h"
#include "HW_NVIC.h"


#endif /* __LPLD_DRIVERS_H__ */