/**
 * @file HW_PDB.h
 * @version 3.0[By LPLD]
 * @date 2013-06-18
 * @brief PDB�ײ�ģ����غ���
 *
 * ���Ľ���:�������޸�
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
#ifndef __HW_PDB_H__
#define __HW_PDB_H__
#include "common.h"

//PDBģ���жϻص���������
typedef void (*PDB_ISR_CALLBACK)(void);

//PDB_InitTypeDef->PDB_TriggerInputSourceSel����ȡֵ���壺����ģʽ
#define TRIGGER_EXTERNAL        0
#define TRIGGER_CMP0            1
#define TRIGGER_CMP1            2
#define TRIGGER_CMP2            3
#define TRIGGER_PIT0            4
#define TRIGGER_PIT1            5
#define TRIGGER_PIT2            6
#define TRIGGER_PIT3            7
#define TRIGGER_FTM0            8
#define TRIGGER_FTM1            9
#define TRIGGER_FTM2            10
#define TRIGGER_RESERVED        11
#define TRIGGER_RTCALARM        12
#define TRIGGER_RTCSECONDS      13
#define TRIGGER_LPTMR           14
#define TRIGGER_SOFTWARE        15

//PDB_InitTypeDef->PDB_LoadModeSel����ȡֵ���壺LDMOD����ģʽ
#define LOADMODE_0       0
#define LOADMODE_1       1
#define LOADMODE_2       2
#define LOADMODE_3       3

//LPLD_PDB_AdcTriggerCfg����cfg�β�ȡֵ���壺ʹ��ADCxͨ��CHn���Ƿ���ʱ������Ƿ�BBģʽ
#define PRETRIG_EN_A            PDB_C1_EN(0x01)
#define PRETRIG_EN_B            PDB_C1_EN(0x02)
#define PRETRIG_DLY_A           PDB_C1_TOS(0x01)
#define PRETRIG_DLY_B           PDB_C1_TOS(0x02)
#define PRETRIG_BB_A            PDB_C1_BB(0x01)
#define PRETRIG_BB_B            PDB_C1_BB(0x02)

//LPLD_PDB_DacTriggerCfg����cfg�β�ȡֵ���壺ʹ��DACx����������Ƿ��ⲿ����
#define EXT_TRIG_EN             (PDB_INTC_EXT_MASK<<PDB_INTC_EXT_SHIFT)
#define INT_TRIG_EN             (PDB_INTC_TOE_MASK<<PDB_INTC_TOE_SHIFT)


//PDBģ���ʼ���ṹ�壬��������PDB�������
typedef struct
{  
  /*
    ������
      ����PDBx������������ڣ���λus
    ȡֵ��
      1~0xFFFFFFFF
    ��ʼ����
      �������ʼ����PDB_CounterPeriodUs��PDB_CounterPeriodMs��PDB_CounterPeriodS����һ����ʼ��
  */
  uint32 PDB_CounterPeriodUs;
  
  /*
    ������
      ����PDBx������������ڣ���λms
    ȡֵ��
      1~0xFFFFFFFF
    ��ʼ����
      �������ʼ����PDB_CounterPeriodUs��PDB_CounterPeriodMs��PDB_CounterPeriodS����һ����ʼ��
  */
  uint32 PDB_CounterPeriodMs;
  
  /*
    ������
      ����PDBx������������ڣ���λs
    ȡֵ��
      1~0xFFFFFFFF
    ��ʼ����
      �������ʼ����PDB_CounterPeriodUs��PDB_CounterPeriodMs��PDB_CounterPeriodS����һ����ʼ��
  */
  uint32 PDB_CounterPeriodS;
  
  /*
    ������
      ѡ��PDBxģ��MOD��IDLY��CHnDLYm��INTx��POyDLY�Ĵ����ļ���ģʽѡ��
    ȡֵ��
      LOADMODE_0-ģʽ0����LDOKд1������������ֵ�������Ĵ�����
      LOADMODE_1-ģʽ1����LDOKд1����PDBx������ֵ����MOD�Ĵ���ֵʱ������ֵ�������Ĵ�����
      LOADMODE_2-ģʽ2����LDOKд1����һ�����봥���¼�����⵽ʱ������ֵ�������Ĵ�����
      LOADMODE_3-ģʽ3����LDOKд1����(PDBx������ֵ����MOD�Ĵ���ֵ �� һ�����봥���¼�����⵽)ʱ������ֵ�������Ĵ�����
    ��ʼ����
      �������ʼ����Ĭ��LOADMODE_0
  */
  uint8 PDB_LoadModeSel;
  
  /*
    ������
      ����PDBx��������ʼ���������봥��Դ
    ȡֵ��
      TRIGGER_EXTERNAL        -�ⲿ����
      TRIGGER_CMP0            -CMP0ģ�鴥��
      TRIGGER_CMP1            -CMP1ģ�鴥��
      TRIGGER_CMP2            -CMP2ģ�鴥��
      TRIGGER_PIT0            -PIT0ģ�鴥��
      TRIGGER_PIT1            -PIT1ģ�鴥��
      TRIGGER_PIT2            -PIT2ģ�鴥��
      TRIGGER_PIT3            -PIT3ģ�鴥��
      TRIGGER_FTM0            -FTM0ģ�鴥��
      TRIGGER_FTM1            -FTM1ģ�鴥��
      TRIGGER_FTM2            -FTM2ģ�鴥��
      TRIGGER_RESERVED        -����
      TRIGGER_RTCALARM        -RTC Alarm����
      TRIGGER_RTCSECONDS      -RTC Seconds����
      TRIGGER_LPTMR           -LPTMRģ�鴥��
      TRIGGER_SOFTWARE        -�������
    ��ʼ����
      �������ʼ����Ĭ��TRIGGER_EXTERNAL
  */
  uint8 PDB_TriggerInputSourceSel;
  
  /*
    ������
      ʹ��PDBx��������ģʽ��ʹ�ܺ�PDBx���ڵ�һ�δ�������������
    ȡֵ��
      TRUE-ʹ������
      FALSE-��������
    ��ʼ����
      �������ʼ����Ĭ��FALSE
  */
  boolean PDB_ContinuousModeEnable;
  
  /*
    ������
      ʹ��PDBxģ��DMA����
    ȡֵ��
      TRUE-ʹ��
      FALSE-����
    ��ʼ����
      �������ʼ����Ĭ��FALSE
  */
  boolean PDB_DmaEnable;
  
  /*
    ������
      ʹ��PDBxģ���жϣ�ʱ�ܺ�PDBx����������ʱ�����PDB_Delay�󴥷��ж�
    ȡֵ��
      TRUE-ʹ��
      FALSE-����
    ��ʼ����
      �������ʼ����Ĭ��FALSE
  */
  boolean PDB_IntEnable;
    
  /*
    ������
      ʹ��PDBxģ�����д����ж�
    ȡֵ��
      TRUE-ʹ��
      FALSE-����
    ��ʼ����
      �������ʼ����Ĭ��FALSE
  */  
  boolean PDB_SeqErrIntEnable;
  
  /*
    ������
      ����PDBx��ʱ�Ĵ������ʱ�䣬��λus
    ȡֵ��
      1~0xFFFFFFFF
    ��ʼ����
      �������ʼ��
  */
  uint32 PDB_DelayUs;
  
  /*
    ������
      ����PDBx��ʱ�Ĵ������ʱ�䣬��λms
    ȡֵ��
      1~0xFFFFFFFF
    ��ʼ����
      �������ʼ��
  */
  uint32 PDB_DelayMs;
  
  /*
    ������
      ����PDBx��ʱ�Ĵ������ʱ�䣬��λs
    ȡֵ��
      1~0xFFFFFFFF
    ��ʼ����
      �������ʼ��
  */
  uint32 PDB_DelayS;

  /*
    ������
      PDBx�жϻص�����
    ȡֵ��
      ��������Ϊ�޷���ֵ,�޲���(eg. void isr(void);)
    ��ʼ����
      �������ʼ������δ��ʼ���򲻻ᴥ���ж�
  */
  PDB_ISR_CALLBACK PDB_Isr; 

  /*
    ������
      PDBx���д����жϻص�����
    ȡֵ��
      ��������Ϊ�޷���ֵ,�޲���(eg. void isr(void);)
    ��ʼ����
      �������ʼ������δ��ʼ���򲻻ᴥ���ж�
  */
  PDB_ISR_CALLBACK PDB_SeqErrIsr; 
  
} PDB_InitTypeDef;

//ʹ��PDBx�ж�
#define LPLD_PDB_EnableIrq()    enable_irq(PDB0_IRQn)
//����PDBx�ж�
#define LPLD_PDB_DisableIrq()   disable_irq(PDB0_IRQn)
//�������PDBx��������ʼ����
#define LPLD_PDB_SoftwareTrigger()      (PDB0->SC|=PDB_SC_SWTRIG_MASK)

//PDBxģ��ͨ�ó�ʼ����������ʼ��PDBx���������ڡ�����ģʽ������Դ���жϵ�����
uint8 LPLD_PDB_Init(PDB_InitTypeDef);
//PDBxģ�鷴��ʼ������������PDBx���й���
void LPLD_PDB_Deinit(void);
//PDBx����ADCxģ�����ú���
uint8 LPLD_PDB_AdcTriggerCfg(ADC_Type *, uint32, uint16);
//PDBx����DACxģ�����ú���
uint8 LPLD_PDB_DacTriggerCfg(DAC_Type *, uint32, uint16);

#endif /* __HW_PDB_H__ */