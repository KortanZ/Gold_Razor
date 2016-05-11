/**
 * @file HW_PIT.c
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
#include "common.h"
#include "HW_PIT.h"

//�û��Զ����жϷ���������
PIT_ISR_CALLBACK PIT_ISR[4];

/*
 * LPLD_PIT_Init
 * PITͨ�ó�ʼ��������ѡ��PITx�������ж����ڡ��жϺ���
 * 
 * ����:
 *    pit_init_structure--PIT��ʼ���ṹ�壬
 *                        ���嶨���PIT_InitTypeDef
 *
 * ���:
 *    0--���ô���
 *    1--���óɹ�
 */
uint8 LPLD_PIT_Init(PIT_InitTypeDef pit_init_structure)
{ 
  //���㶨ʱ����ֵ
  uint32 ldval = pit_init_structure.PIT_PeriodUs*(g_bus_clock/1000000)
               + pit_init_structure.PIT_PeriodMs*1000*(g_bus_clock/1000000)
               + pit_init_structure.PIT_PeriodS*1000000*(g_bus_clock/1000000);
  PITx pitx = pit_init_structure.PIT_Pitx;
  PIT_ISR_CALLBACK isr_func = pit_init_structure.PIT_Isr;
  
  //�������
  ASSERT( pitx <= PIT3);        //�ж�ģ���
  ASSERT( ldval > 0);           //�ж�ʱ����ֵ                
  
  //������ʱģ��ʱ��
  SIM->SCGC6 |= SIM_SCGC6_PIT_MASK;
  
  // ���� PIT
  PIT->MCR = 0x00;
 
  if(isr_func != NULL){
    PIT_ISR[pitx] = isr_func;
    //ʹ���ж�
    PIT->CHANNEL[pitx].TCTRL = PIT_TCTRL_TIE_MASK;
    //��NVIC��ʹ��PIT�ж�
    //enable_irq((IRQn_Type)(PIT0_IRQn + (IRQn_Type)pitx)); 
  }
  
  //period = (period_ns/bus_period_ns)-1
  PIT->CHANNEL[pitx].LDVAL = ldval-1;
  //ʹ���ж�
  //PIT->CHANNEL[pitx].TCTRL = PIT_TCTRL_TIE_MASK;
  //��ʼ��ʱ
  PIT->CHANNEL[pitx].TCTRL |= PIT_TCTRL_TEN_MASK;
  
  return 1;
}

/*
 * LPLD_PIT_Deinit
 * PIT����ʼ���������ر�ѡ���PITx
 * 
 * ����:
 *    pit_init_structure--PIT��ʼ���ṹ�壬
 *                        ���嶨���PIT_InitTypeDef
 *
 * ���:
 *    ��
 */
void LPLD_PIT_Deinit(PIT_InitTypeDef pit_init_structure)
{ 
  PITx pitx = pit_init_structure.PIT_Pitx;
  
  //�������
  ASSERT( pitx <= PIT3);        //�ж�ģ���              

  disable_irq((IRQn_Type)(PIT0_IRQn + (IRQn_Type)pitx)); 

  //�����ж�\ֹͣ��ʱ
  PIT->CHANNEL[pitx].TCTRL = 0;
}

/*
 * LPLD_PIT_EnableIrq
 * ʹ��PITx�ж�
 * 
 * ����:
 *    pit_init_structure--PIT��ʼ���ṹ�壬
 *                        ���嶨���PIT_InitTypeDef
 *
 * ���:
 *    ��
 *
 */
void LPLD_PIT_EnableIrq(PIT_InitTypeDef pit_init_structure)
{
  PITx pitx = pit_init_structure.PIT_Pitx;
  
  //�������
  ASSERT( pitx <= PIT3);                //�ж�PITx

  enable_irq((IRQn_Type)(PIT0_IRQn + (IRQn_Type)pitx)); 
}

/*
 * LPLD_PIT_DisableIrq
 * ����PITx�ж�
 * 
 * ����:
 *    pit_init_structure--PIT��ʼ���ṹ�壬
 *                        ���嶨���PIT_InitTypeDef
 *
 * ���:
 *    ��
 *
 */
void LPLD_PIT_DisableIrq(PIT_InitTypeDef pit_init_structure)
{
  PITx pitx = pit_init_structure.PIT_Pitx;
  
  //�������
  ASSERT( pitx <= PIT3);                //�ж�PITx
  
  disable_irq((IRQn_Type)(PIT0_IRQn + (IRQn_Type)pitx));
}


/*
 * PIT0--PIT3�жϴ�����
 * �������ļ�startup_K60.s�е��ж����������
 * �û������޸ģ������Զ������Ӧͨ���жϺ���
 */

void PIT0_IRQHandler(void)
{
#if (UCOS_II > 0u)
  OS_CPU_SR  cpu_sr = 0u;
  OS_ENTER_CRITICAL(); //��֪ϵͳ��ʱ�Ѿ��������жϷ����Ӻ���
  OSIntEnter();
  OS_EXIT_CRITICAL();
#endif
  
  //�����û��Զ����жϷ���
  PIT_ISR[0]();  
  //����жϱ�־λ
  PIT->CHANNEL[0].TFLG |= PIT_TFLG_TIF_MASK;
  
#if (UCOS_II > 0u)
  OSIntExit();          //��֪ϵͳ��ʱ�����뿪�жϷ����Ӻ���
#endif
}
void PIT1_IRQHandler(void)
{
#if (UCOS_II > 0u)
  OS_CPU_SR  cpu_sr = 0u;
  OS_ENTER_CRITICAL(); //��֪ϵͳ��ʱ�Ѿ��������жϷ����Ӻ���
  OSIntEnter();
  OS_EXIT_CRITICAL();
#endif
  
  //�����û��Զ����жϷ���
  PIT_ISR[1]();  
  //����жϱ�־λ
  PIT->CHANNEL[1].TFLG |= PIT_TFLG_TIF_MASK;
  
#if (UCOS_II > 0u)
  OSIntExit();          //��֪ϵͳ��ʱ�����뿪�жϷ����Ӻ���
#endif
}
void PIT2_IRQHandler(void)
{
#if (UCOS_II > 0u)
  OS_CPU_SR  cpu_sr = 0u;
  OS_ENTER_CRITICAL(); //��֪ϵͳ��ʱ�Ѿ��������жϷ����Ӻ���
  OSIntEnter();
  OS_EXIT_CRITICAL();
#endif
  
  //�����û��Զ����жϷ���
  PIT_ISR[2]();  
  //����жϱ�־λ
  PIT->CHANNEL[2].TFLG |= PIT_TFLG_TIF_MASK;
  
#if (UCOS_II > 0u)
  OSIntExit();          //��֪ϵͳ��ʱ�����뿪�жϷ����Ӻ���
#endif
}
void PIT3_IRQHandler(void)
{
#if (UCOS_II > 0u)
  OS_CPU_SR  cpu_sr = 0u;
  OS_ENTER_CRITICAL(); //��֪ϵͳ��ʱ�Ѿ��������жϷ����Ӻ���
  OSIntEnter();
  OS_EXIT_CRITICAL();
#endif
  
  //�����û��Զ����жϷ���
  PIT_ISR[3]();  
  //����жϱ�־λ
  PIT->CHANNEL[3].TFLG |= PIT_TFLG_TIF_MASK;
  
#if (UCOS_II > 0u)
  OSIntExit();          //��֪ϵͳ��ʱ�����뿪�жϷ����Ӻ���
#endif
}