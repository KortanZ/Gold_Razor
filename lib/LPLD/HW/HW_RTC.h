/**
 * @file HW_RTC.h
 * @version 3.01[By LPLD]
 * @date 2013-10-4
 * @brief RTC�ײ�ģ����غ���
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
#ifndef __HW_RTC_H__
#define __HW_RTC_H__

//RTCģ���жϻص���������
typedef void (*RTC_ISR_CALLBACK)(void);

//����RTC�жϷ�ʽ
#define RTC_INT_DIS           (0)
#define RTC_INT_INVALID       (1)
#define RTC_INT_OVERFLOW      (2)
#define RTC_INT_ALARM         (4)

typedef struct 
{
  /*
    ������
      ����RTC���������ʼֵ
    ȡֵ��
      �������������Ϊ0���ڲ���λ������¿ɼ���2��32�η��룬Լ136��
    ��ʼ����
      �����ʼ��
  */
  uint32 RTC_Seconds; 
  
  /*
    ������
      ���ñ���ֵ
    ȡֵ��
      ������ֵ����RTC_TSR������TAF��־λ���ɴ����ж�
    ��ʼ����
      �����Ҫ�������ܣ������ʼ��
  */
  uint32 RTC_AlarmTime; 
  
  /*
    ������
      ����RTC ��Ч�����ж�
    ȡֵ��
      TRUE - ����RTC��Ч�����ж�
      FALSE - �ر�RTC��Ч�����ж�
    ��ʼ����
      �������ʼ����Ĭ��ֵFLASE
  */
  boolean  RTC_InvalidIntEnable; 
  
  /*
    ������
      ����RTC ����������ж�
    ȡֵ��
      TRUE - ����RTC����������ж�
      FALSE - �ر�RTC����������ж�
    ��ʼ����
      �������ʼ����Ĭ��ֵFLASE
  */
  boolean  RTC_OverflowIntEnable;
  
  /*
    ������
      ����RTC �����ж�
    ȡֵ��
      TRUE - ����RTC����������ж�
      FALSE - �ر�RTC����������ж�
    ��ʼ����
      �������ʼ����Ĭ��ֵRTC_INT_DIS �ر�RTC�ж�
  */
  boolean  RTC_AlarmIntEnable; 
  
  /*
    ������
      ��Ч�����жϻص�����
    ȡֵ��
      ��������Ϊ�޷���ֵ,�޲���(eg. void isr(void);)
    ��ʼ����
      �������ʼ������δ��ʼ���򲻻ᴥ���ж�
  */
  RTC_ISR_CALLBACK RTC_InvalidIsr;
  
  /*
    ������
      ��������жϻص�����
    ȡֵ��
      ��������Ϊ�޷���ֵ,�޲���(eg. void isr(void);)
    ��ʼ����
      �������ʼ������δ��ʼ���򲻻ᴥ���ж�
  */
  RTC_ISR_CALLBACK RTC_OverflowIsr;
  
  /*
    ������
      �����жϻص�����
    ȡֵ��
      ��������Ϊ�޷���ֵ,�޲���(eg. void isr(void);)
    ��ʼ����
      �������ʼ������δ��ʼ���򲻻ᴥ���ж�
  */
  RTC_ISR_CALLBACK RTC_AlarmIsr;

}RTC_InitTypeDef;

//RTCʹ��ģ���ж�
#define LPLD_RTC_EnableIrq()    enable_irq(RTC_IRQn)
//RTC��ֹģ���ж�
#define LPLD_RTC_DisableIrq()   disable_irq(RTC_IRQn)
//RTC���ʵʱ���������
#define LPLD_RTC_GetRealTime()  (RTC->TSR)
//RTC�������������������
#define LPLD_RTC_SetRealTime(TIME)     (RTC->TSR=TIME)
//RTC�������ñ����Ĵ�������
#define LPLD_RTC_SetAlarmTime(TIME)    (RTC->TAR=TIME)
//RTC�رպ���
#define LPLD_RTC_Stop()         (RTC->SR&=(~RTC_SR_TCE_MASK))


//RTC��ʼ������
uint8 LPLD_RTC_Init(RTC_InitTypeDef );
//RTC����ʼ���������ر�ѡ���RTCx
void LPLD_RTC_Deinit(void );
//�ж�RTC�Ƿ����к���
uint8 LPLD_RTC_IsRunning(void);     
#endif /* __HW_RTC_H__ */
