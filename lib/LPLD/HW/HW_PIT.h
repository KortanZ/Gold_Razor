/**
 * @file HW_PIT.h
 * @version 3.0[By LPLD]
 * @date 2013-06-18
 * @brief PIT�ײ�ģ����غ���
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
#ifndef __HW_PIT_H__
#define __HW_PIT_H__
/********************************************************************/

//PITģ���жϻص���������
typedef void (*PIT_ISR_CALLBACK)(void);

//PITģ��Ŷ���
typedef enum PITx
{
  PIT0=0,
  PIT1=1,
  PIT2=2,
  PIT3=3
}PITx;

//PITģ���ʼ���ṹ�壬��������PIT�������
typedef struct
{  
  /*
    ������
      ѡ��PITx
    ȡֵ��
      PIT0��PIT1��PIT2��PIT3
    ��ʼ����
      �����ʼ��
  */
  PITx PIT_Pitx;
  
  /*
    ������
      PITxģ������ڣ���λus
    ȡֵ��
      1~0xFFFFFFFF
    ��ʼ����
      �������ʼ����PIT_PeriodUs��PIT_PeriodMs��PIT_PeriodS����һ����ʼ��
  */
  uint32 PIT_PeriodUs;
  
  /*
    ������
      PITxģ������ڣ���λms
    ȡֵ��
      1~0xFFFFFFFF
    ��ʼ����
      �������ʼ����PIT_PeriodUs��PIT_PeriodMs��PIT_PeriodS����һ����ʼ��
  */
  uint32 PIT_PeriodMs;
  
  /*
    ������
      PITxģ������ڣ���λs
    ȡֵ��
      1~0xFFFFFFFF
    ��ʼ����
      �������ʼ����PIT_PeriodUs��PIT_PeriodMs��PIT_PeriodS����һ����ʼ��
  */
  uint32 PIT_PeriodS;

  /*
    ������
      PITx�жϻص�����
    ȡֵ��
      ��������Ϊ�޷���ֵ,�޲���(eg. void isr(void);)
    ��ʼ����
      �������ʼ������δ��ʼ���򲻻ᴥ���ж�
  */
  PIT_ISR_CALLBACK PIT_Isr; 
} PIT_InitTypeDef;

//PITͨ�ó�ʼ��������ѡ��PITx�������ж����ڡ��жϺ���
uint8 LPLD_PIT_Init(PIT_InitTypeDef);
//PIT����ʼ���������ر�ѡ���PITx
void LPLD_PIT_Deinit(PIT_InitTypeDef);
//ʹ��PITx�ж�
void LPLD_PIT_EnableIrq(PIT_InitTypeDef);
//����PITx�ж�
void LPLD_PIT_DisableIrq(PIT_InitTypeDef);

#endif /* __HW_PIT_H__ */
