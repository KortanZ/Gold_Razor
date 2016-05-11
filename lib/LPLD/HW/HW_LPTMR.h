/**
 * @file HW_LPTMR.h
 * @version 3.0[By LPLD]
 * @date 2013-06-18
 * @brief LPTMR�ײ�ģ����غ���
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
#ifndef __HW_LPTMR_H__
#define __HW_LPTMR_H__
/********************************************************************/

//����LPTMR��ʱ��ģʽ
#define LPTMR_MODE_TIMER    0
#define LPTMR_MODE_PLACC    1

//����LPTMR�����ۼ�ͨ��
#define CMP0_OUTPUT         0
#define LPTMR_ALT1          1
#define LPTMR_ALT2          2

//LPTMRģ���жϻص���������
typedef void (*LPTMR_ISR_CALLBACK)(void);

typedef struct 
{
  /*
    ������
      ѡ��LPTMRģʽ
    ȡֵ��
      LPTMR_MODE_TIMER--�͹��Ķ�ʱ��ģʽ
      LPTMR_MODE_PLACC--�����ۼ�ģʽ
    ��ʼ����
      �����ʼ�� 
  */
  uint8  LPTMR_Mode;
  
  /*
    ������
      �趨��ʱ���Ķ�ʱֵ ��λms
    ȡֵ��
      1~65535--1ms<= ��ʱ����  <=65535ms
    ��ʼ����
      ���ѡ��LPTMR_MODE_PLACC�����ۼ�ģʽ�����س�ʼ�� 
      ���ѡ��LPTMR_MODE_TIMER�͹��Ķ�ʱ��ģʽ����Ҫ���ö�ʱ������
  */
  uint16 LPTMR_PeriodMs;
  
  /*
    ������
      ѡ��LPTMR�����ۼ�ģʽ�µ�����IO
    ȡֵ��
      CMP0_OUTPUT-CMP0ģ�����
      LPTMR_ALT1-PTA19���� 
      LPTMR_ALT2-PTC5����
    ��ʼ����
      �������ʼ����Ĭ��CMP0_OUTPUT
  */
  uint8  LPTMR_PluseAccInput;
    
  /*
    ������
      ʹ��LPTMR�ж�
    ȡֵ��
      TRUE-ʹ��
      FALSE-����
    ��ʼ����
      �������ʼ����Ĭ��ֵFALSE
  */
  boolean LPTMR_IntEnable;
  
  /*
    ������
      LPTMR�жϻص�����
    ȡֵ��
      ��������Ϊ�޷���ֵ,�޲���(eg. void isr(void);)
    ��ʼ����
      �������ʼ������δ��ʼ���򲻻ᴥ���ж�
  */
  LPTMR_ISR_CALLBACK LPTMR_Isr;

}LPTMR_InitTypeDef;

//��ʼ��LPTMR����ģʽ����������ͨ��
uint8 LPLD_LPTMR_Init(LPTMR_InitTypeDef);
//LPTMR����ʼ������
uint8 LPLD_LPTMR_Deinit(void);
//LPTMR��λCounter
void LPLD_LPTMR_ResetCounter(void);
//LPTMR�ж�ʹ�ܺ���
uint8 LPLD_LPTMR_EnableIrq(void);
//LPTMR��ֹʹ�ܺ���
uint8 LPLD_LPTMR_DisableIrq(void);
//LPTMR��ò���ֵ����
uint16 LPLD_LPTMR_GetPulseAcc(void);
//LPTMR ms��ʱ����
void LPLD_LPTMR_DelayMs(uint16);

#endif /* __HW_LPTMR_H__ */
