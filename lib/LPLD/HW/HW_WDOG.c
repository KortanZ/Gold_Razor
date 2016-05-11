/**
 * @file HW_WDOG.c
 * @version 3.0[By LPLD]
 * @date 2013-06-18
 * @brief WDOG�ײ�ģ����غ���
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
#include "common.h"
#include "HW_WDOG.h"

static void LPLD_WDOG_Unlock(void);

/*
 * LPLD_WDOG_Init
 * ���Ź���ʼ��
 * 
 * ����:
 *    period_ms--���Ź���λ����
 *      |__��λΪ����
 *
 * ���:
 *    0--���ô���
 *    1--���óɹ�
 */
uint8 LPLD_WDOG_Init(uint32 period_ms)
{
  uint8 presc = 3;
  uint32 bus_khz = g_bus_clock / 1000;
  uint32 value;
  
  if(period_ms==0)
  {
    return 0;
  }
    
  value=(period_ms*bus_khz)/(presc+1);
    
  //�Ƚ����Ĵ���
  LPLD_WDOG_Unlock();
  //���÷�Ƶ
  WDOG->PRESC = WDOG_PRESC_PRESCVAL(presc);
  //���ü�ʱ���ֵ
  WDOG->TOVALH = (value&0xFFFF0000)>>16;
  WDOG->TOVALL = (value&0x0000FFFF)>>0;  
  //ʹ��WDOG
  WDOG->STCTRLH |= WDOG_STCTRLH_WDOGEN_MASK;
  
  return 1;
}

/*
 * LPLD_WDOG_Enable
 * ���Ź�ʹ��
 * 
 * ����:
 *    ��
 *
 * ���:
 *    ��
 */
void LPLD_WDOG_Enable(void)
{
  //�Ƚ����Ĵ���
  LPLD_WDOG_Unlock();
  //ʹ��WDOG
  WDOG->STCTRLH |= WDOG_STCTRLH_WDOGEN_MASK;
}

/*
 * LPLD_WDOG_Disable
 * ���Ź�����
 * 
 * ����:
 *    ��
 *
 * ���:
 *    ��
 */
void LPLD_WDOG_Disable(void)
{
  //�Ƚ����Ĵ���
  LPLD_WDOG_Unlock();
  //����WDOG
  WDOG->STCTRLH &= ~(WDOG_STCTRLH_WDOGEN_MASK);
}

/*
 * LPLD_WDOG_Feed
 * ι��
 * 
 * ����:
 *    ��
 *
 * ���:
 *    ��
 */
void LPLD_WDOG_Feed(void)
{
  WDOG->REFRESH = 0xA602;
  WDOG->REFRESH = 0xB480;
}

/*
 * LPLD_WDOG_Unlock
 * WDOG�����������ڲ�����
 * 
 * ����:
 *    ��
 *
 * ���:
 *    ��
 */
static void LPLD_WDOG_Unlock(void)
{
  //���´��������20��ʱ����������ɣ�����Ḵλ
  DisableInterrupts;
  
  //д0xC520�������Ĵ���
  WDOG->UNLOCK = 0xC520;
  
  //������д0xD928��ɽ���
  WDOG->UNLOCK = 0xD928;
  	
  EnableInterrupts;
}