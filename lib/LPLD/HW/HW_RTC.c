/**
 * @file HW_RTC.c
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
#include "common.h"
#include "HW_RTC.h"

//�û��Զ����жϷ�����
RTC_ISR_CALLBACK RTC_ISR[3];

/*
 * LPLD_RTC_Init
 * RTCͨ�ó�ʼ������,�ڸú�����Ҫ����RTC��������������Ҫ��������
 * ��Ҫʹ�ܱ����жϣ������ñ����Ĵ���
 * 
 * ����:
 *    rtc_init_structure--RTC��ʼ���ṹ�壬
 *                        ���嶨���RTC_InitTypeDef
 *
 * ���:
 *    0--���ô���
 *    1--���óɹ�
 */
uint8 LPLD_RTC_Init(RTC_InitTypeDef rtc_init_structure)
{
  int delay;
  uint32 seconds = rtc_init_structure.RTC_Seconds;
  uint32 alarm_time = rtc_init_structure.RTC_AlarmTime;
  RTC_ISR_CALLBACK invalid_isr_func = rtc_init_structure.RTC_InvalidIsr;
  RTC_ISR_CALLBACK overflow_isr_func = rtc_init_structure.RTC_OverflowIsr;
  RTC_ISR_CALLBACK alarm_isr_func = rtc_init_structure.RTC_AlarmIsr;

  SIM->SCGC6 |= SIM_SCGC6_RTC_MASK;
  //��λ����RTC�Ĵ��� ����SWRλ RTC_WAR��RTC_RAR�Ĵ���
  //��VBAT POR����֮��,��������SWR
  //��λRTC�Ĵ���
  RTC->CR  = RTC_CR_SWR_MASK; 
  //���RTC��λ��־  
  RTC->CR  &= ~RTC_CR_SWR_MASK;  
  //ʹ��RTC 32.768 kHzRTCʱ��Դ
  //ʹ��֮��Ҫ��ʱһ��ʱ��ȴ�
  //�ȴ�ʱ���ȶ���������RTCʱ�Ӽ�����
  RTC->CR |= RTC_CR_OSCE_MASK;
  
  //�ȴ�32.768ʱ������
  for(delay = 0;delay < 0x600000 ;delay++);
  
  if(rtc_init_structure.RTC_InvalidIntEnable == TRUE)
  { 
    RTC->IER |= (RTC_INT_INVALID & 0x07);//����RTC��Ч�����ж�
    RTC_ISR[0] = invalid_isr_func;
  }
  else
  {
    RTC->IER &= ~RTC_INT_INVALID;
  }

  if(rtc_init_structure.RTC_OverflowIntEnable == TRUE)
  { 
    RTC->IER |= (RTC_INT_OVERFLOW & 0x07);//����RTC����������ж�
    RTC_ISR[1] = overflow_isr_func;
  }
  else
  {
    RTC->IER &= ~RTC_INT_OVERFLOW;
  }

  if(rtc_init_structure.RTC_AlarmIntEnable == TRUE)
  {   
    RTC->IER |= (RTC_INT_ALARM & 0x07);//����RTC�����ж�
    RTC_ISR[2] = alarm_isr_func;
  }
  else
  {
    RTC->IER &= ~RTC_INT_ALARM;
  }

  //����ʱ�Ӳ����Ĵ���
  RTC->TCR = RTC_TCR_CIR(0) | RTC_TCR_TCR(0);
  
  //�����������
  RTC->TSR = seconds;
    
  //���ñ����Ĵ���
  RTC->TAR = alarm_time;
  
  //ʹ���������
  RTC->SR |= RTC_SR_TCE_MASK;
  
  return 1;
}

/*
 * LPLD_RTC_Deinit
 * RTC����ʼ���������ر�RTCx����ֹRTC�ж�
 * 
 * ����:
 *    ��
 *
 * ���:
 *    ��
 */
void LPLD_RTC_Deinit(void)
{
  //��ֹRTCģ���ж�
  disable_irq(RTC_IRQn);
  //�ر�RTC
  RTC->SR &= (~RTC_SR_TCE_MASK);
  //�ر�RTC����ʱ��
  SIM->SCGC6 |= SIM_SCGC6_RTC_MASK;  
}

/*
 * LPLD_RTC_IsRunning
 * �ж�RTC�Ƿ����к���
 * 
 * ����:
 *    ��
 *
 * ���:
 *    1��RTC��������������
 *    0��RTC�������Ը�λ
 */
uint8 LPLD_RTC_IsRunning(void)
{
  uint8 request;
  SIM->SCGC6 |= SIM_SCGC6_RTC_MASK;
  
  if(RTC->SR & RTC_SR_TIF_MASK)
  {
    request = 0;
  }
  else
  {
    request = 1;
  }
  return request;
}

/*
 * RTC�жϴ�����
 * �������ļ�startup_K60.s�е��ж����������
 * �û������޸ģ������Զ������Ӧͨ���жϺ���
 */
void RTC_IRQHandler(void)
{
#if (UCOS_II > 0u)
  OS_CPU_SR  cpu_sr = 0u;
  OS_ENTER_CRITICAL(); //��֪ϵͳ��ʱ�Ѿ��������жϷ����Ӻ���
  OSIntEnter();
  OS_EXIT_CRITICAL();
#endif
  
  if((RTC->SR & RTC_SR_TIF_MASK)== 0x01)
  {
    //�����û��Զ����жϷ���
    RTC_ISR[0](); 
    //����жϱ�־λ
    RTC->SR |= RTC_SR_TIF_MASK;
    
  }	
  else if((RTC->SR & RTC_SR_TOF_MASK) == 0x02)
  {
    //�����û��Զ����жϷ���
    RTC_ISR[1]();  
    //����жϱ�־λ
    RTC->SR |= RTC_SR_TOF_MASK;
  }	 	
  else if((RTC->SR & RTC_SR_TAF_MASK) == 0x04)
  {
    //�����û��Զ����жϷ���
    RTC_ISR[2]();  
    //����жϱ�־λ
    RTC->SR |= RTC_SR_TAF_MASK;
  }	
  
#if (UCOS_II > 0u)
  OSIntExit();          //��֪ϵͳ��ʱ�����뿪�жϷ����Ӻ���
#endif
}
