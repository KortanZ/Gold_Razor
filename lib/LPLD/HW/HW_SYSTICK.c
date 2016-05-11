/**
 * @file HW_SYSTICK.c
 * @version 3.02[By LPLD]
 * @date 2013-11-29
 * @brief SYSTICK�ײ�ģ����غ���
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
#include "HW_SYSTICK.h"

/*
*   SyStick��һ��Cotex-M4�ں˵Ķ�ʱ��
*   SyStick���ü������ķ�ʽ����������㣬������COUNTFLAG��־λ�����ʹ���жϣ�������ж�
*   Ȼ���������RVR�е�ֵ������������
*   �������òο�Cortex-M4 Reference Manual
*/
SYSTICK_ISR_CALLBACK SYSTICK_ISR;
/*
* LPLD_SYSTICK_Init
* SYSTICK��ʼ������������SYStick��ʱ��������ʱ��ԴΪ�ں�ʱ��
* >����ڽṹ���ʼ����ʱ����ص���������LPLD_SYSTICK_Init�п����жϹ���
* >���û���õ��жϣ�����ͨ��ѭ���ж�LPLD_SYSTICK_ISDONE�ķ�ʽ���SYSTICK�Ƿ�������
* 
* ����:
*    systick_init_structure--SYSTICK��ʼ���ṹ�壬
*                        ���嶨���SYSTICK_InitType
*
* �����
*   ��
*/
void LPLD_SYSTICK_Init(SYSTICK_InitType systick_init_structure)  
{      
  //����ں�ʱ����100Mhz�����ʱ167ms
  uint32 ldval = systick_init_structure.SYSTICK_PeriodUs * SYSTICK_UINT_US(g_core_clock)
             + systick_init_structure.SYSTICK_PeriodMs * SYSTICK_UINT_MS(g_core_clock);
  //�����Ĵ�����ֵ���ܳ���0xFFFFFF           
  if( ldval > SYSTICK_COUNTER_MAX)
  {
    return;
  }
  
  SYSTICK->CSR = 0 & (~SYSTICK_CSR_ENABLE_MASK)      //��ֹSYSTICK
                    | SYSTICK_CSR_CLKSOURCE_MASK     //ѡ���ں�ʱ����Ϊʱ��Դ
                    | SYSTICK_CSR_COUNTFLAG_MASK;    //�����־λ
  if(systick_init_structure.SYSTICK_Isr != NULL)
  {
    SYSTICK->CSR |= SYSTICK_CSR_TICKINT_MASK;  //ʹ��systick�ж�
    SYSTICK_ISR = systick_init_structure.SYSTICK_Isr;
    NVIC_SetPriority (SysTick_IRQn, (1<<__NVIC_PRIO_BITS) - 1);
    enable_irq(SysTick_IRQn);                 //ʹ��SYSTICK�ж�
  }
  SYSTICK->RVR = ldval - 1;  
  SYSTICK->CVR = 0x00;  
  SYSTICK->CSR |= SYSTICK_CSR_ENABLE_MASK;  //ʹ��SYSTICK
}

/*
* LPLD_SYSTICK_Init
* SYSTICK����ʼ���������ر�SYStick��ʱ��
* �ر��жϣ���ռ�����
* 
* ����:
*   ��
*
* �����
*   ��
*/
void LPLD_SYSTICK_DeInit(void)
{
  SYSTICK->CSR = 0 & (~SYSTICK_CSR_ENABLE_MASK)   //��ֹSYSTICK
                   & (~SYSTICK_CSR_TICKINT_MASK)  //��ֹ�����ں�SYSTICK�쳣
                   & (~SYSTICK_CSR_CLKSOURCE_MASK)//ѡ���ں�ʱ����Ϊʱ��Դ
                   | SYSTICK_CSR_COUNTFLAG_MASK;  //�����־λ                     
  disable_irq(SysTick_IRQn);         //��ֹSYSTICK�ж�       
  SYSTICK->CVR = 0x00;  
}

/*
* LPLD_SYSTICK_DelayUs
*
* ����SYSTICK����Us��ʱ,���ں����ڲ���ʼ����ֱ�ӵ��øú����ȿ��Բ�����ʱ
* ����SYStick��ʱ�������ö�ʱ���ļ������Ϊ1/g_core_clock us
* ���ü��ؼĴ��������ؼĴ�����ֵΪ1/g_core_clock us ��period_us������
*
* ����:
*    period_us--��ʱ��΢��ֵ
*
* ���:
*   ��
*/
void LPLD_SYSTICK_DelayUs(uint32 period_us)
{  
  uint32 i;
  
  SYSTICK->CSR = 0 & (~SYSTICK_CSR_ENABLE_MASK)      //��ֹSYSTICK
                 & (~SYSTICK_CSR_TICKINT_MASK)       //��ֹ�����ں�SYSTICK�쳣
                 | SYSTICK_CSR_CLKSOURCE_MASK        //ѡ���ں�ʱ����Ϊʱ��Դ
                 | SYSTICK_CSR_COUNTFLAG_MASK;       //�����־λ
                  
  i = period_us * SYSTICK_UINT_US(g_core_clock) - 1; 
  //�����Ĵ�����ֵ���ܳ���0xFFFFFF
  if( i > SYSTICK_COUNTER_MAX)
  {
    return;
  }
  SYSTICK->RVR = i;  
  SYSTICK->CVR = 0x00;  
  SYSTICK->CSR |= SYSTICK_CSR_ENABLE_MASK;  
  do  
  {  
    i = SYSTICK->CSR;  
  }  
  while(i & SYSTICK_CSR_ENABLE_MASK \
        && !(i & SYSTICK_CSR_COUNTFLAG_MASK)); 
   
  SYSTICK->CSR = 0 & (~SYSTICK_CSR_ENABLE_MASK)     //��ֹSYSTICK
                 & (~SYSTICK_CSR_TICKINT_MASK)      //��ֹ�����ں�SYSTICK�쳣
                 | SYSTICK_CSR_CLKSOURCE_MASK       //ѡ���ں�ʱ����Ϊʱ��Դ
                 | SYSTICK_CSR_COUNTFLAG_MASK;      //�����־λ  
                 
  SYSTICK->CVR = 0x00;  
}  

/*
* LPLD_SYSTICK_DelayMs
*
* ����SYSTICK����Ms��ʱ,���ں����ڲ���ʼ����ֱ�ӵ��øú����ȿ��Բ�����ʱ
* ����SYStick��ʱ�������ö�ʱ���ļ������Ϊ1/g_core_clock ms
* ���ü��ؼĴ��������ؼĴ�����ֵΪ1/g_core_clock ms ��period_ms������
*
* ����:
*    period_ms--��ʱ�ĺ���ֵ
*
* ���:
*   ��
*/
void LPLD_SYSTICK_DelayMs(uint32 period_ms)
{  
  uint32 i;
  
  SYSTICK->CSR = 0 & (~SYSTICK_CSR_ENABLE_MASK)    //��ֹSYSTICK
               & (~SYSTICK_CSR_TICKINT_MASK)       //��ֹ�����ں�SYSTICK�쳣
               | SYSTICK_CSR_CLKSOURCE_MASK        //ѡ���ں�ʱ����Ϊʱ��Դ
               | SYSTICK_CSR_COUNTFLAG_MASK;       //�����־λ
               
  i = period_ms * SYSTICK_UINT_MS(g_core_clock) - 1;
  //�����Ĵ�����ֵ���ܳ���0xFFFFFF
  if( i > SYSTICK_COUNTER_MAX)
  {
    return;
  }
  SYSTICK->RVR = i;  
  SYSTICK->CVR = 0x00;  
  SYSTICK->CSR |= SYSTICK_CSR_ENABLE_MASK;  
  do  
  {  
    i = SYSTICK->CSR;  
  }  
  while(i & SYSTICK_CSR_ENABLE_MASK \
        && !(i & SYSTICK_CSR_COUNTFLAG_MASK)); 
   
  SYSTICK->CSR = 0 & (~SYSTICK_CSR_ENABLE_MASK)    //��ֹSYSTICK
                 & (~SYSTICK_CSR_TICKINT_MASK)     //��ֹ�����ں�SYSTICK�쳣
                 | SYSTICK_CSR_CLKSOURCE_MASK      //ѡ���ں�ʱ����Ϊʱ��Դ
                 | SYSTICK_CSR_COUNTFLAG_MASK;     //�����־λ  
                 
  SYSTICK->CVR = 0x00;  
} 

#if (UCOS_II == 0u)
void OS_CPU_SysTickHandler(void)
{
  SYSTICK_ISR();
}
#endif
