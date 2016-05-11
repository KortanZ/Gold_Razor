/**
 * @file HW_DAC.c
 * @version 3.0[By LPLD]
 * @date 2013-06-18
 * @brief DAC�ײ�ģ����غ���
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
#include "HW_DAC.h"

//�û��Զ����жϷ���������
DAC_ISR_CALLBACK DAC_RDPTBOT_ISR[2];
DAC_ISR_CALLBACK DAC_RDPTTOP_ISR[2];
DAC_ISR_CALLBACK DAC_WATERMK_ISR[2];


/*
 * LPLD_DAC_Init
 * DAC��ʼ��������ʹ��DAC�����
 * 
 * ����:
 *    dac_init_struct--DAC��ʼ���ṹ�壬
 *                        ���嶨���DAC_InitTypeDef
 *
 * ���:
 *    0--���ô���
 *    1--���óɹ�
 */
uint8 LPLD_DAC_Init(DAC_InitTypeDef dac_init_struct)
{
  uint8 x;
  DAC_Type *dacx = dac_init_struct.DAC_Dacx;
  uint8 work_mode = dac_init_struct.DAC_BufferWorkMode;
  uint8 watermark = dac_init_struct.DAC_BufferWatermarkSel;
  uint8 upper = dac_init_struct.DAC_BufferUpperLimit;
  DAC_ISR_CALLBACK rdptbot_isr = dac_init_struct.DAC_ReadPointerBottomIsr;
  DAC_ISR_CALLBACK rdpttop_isr = dac_init_struct.DAC_ReadPointerTopIsr;
  DAC_ISR_CALLBACK watermk_isr = dac_init_struct.DAC_BufferWatermarkIsr;
  
  upper = (upper==NULL?1:upper);
    
  //�������
  ASSERT( work_mode <= BUFFER_MODE_ONETIMESCAN );  //�ж�ģʽѡ��
  ASSERT( watermark <= WATERMARK_4WORDS );      //�жϻ�����ˮӡѡ��
  ASSERT( upper <= 16);         //�жϻ�����������ֵ
    
  //����DACʱ��
  if(dacx == DAC0)
  {
    x = 0;
    SIM->SCGC2 |= SIM_SCGC2_DAC0_MASK;   //����DAC0ʱ��
  }
  else if(dacx == DAC1)
  {
    x = 1;
    SIM->SCGC2 |= SIM_SCGC2_DAC1_MASK;   //����DAC1ʱ��
  }
  else 
  {
    return 0;
  }
  
  //����C2�Ĵ���
  dacx->C2 = DAC_C2_DACBFUP(upper - 1);     //���û�����������ֵ
  
  //����C1�Ĵ���
  dacx->C1 = 0;
  if(dac_init_struct.DAC_BufferEnable == TRUE)
  {
    dacx->C1 |= DAC_C1_DACBFEN_MASK;    //ʹ�ܻ����� 
  }
  dacx->C1 |= DAC_C1_DACBFMD(work_mode);        //����������ģʽ����
  dacx->C1 |= DAC_C1_DACBFWM(watermark);        //������ˮӡѡ������
  if(dac_init_struct.DAC_DmaEnable == TRUE)
  {
    dacx->C1 |= DAC_C1_DMAEN_MASK;      //ʹ��DMA
  }
  
  //����C0�Ĵ���
  dacx->C0 = 0;
  if(dac_init_struct.DAC_ReadPointerBottomIntEnable == TRUE && rdptbot_isr != NULL)
  {
    dacx->C0 |= DAC_C0_DACBBIEN_MASK;   //ʹ�ܻ������ײ��ж�
    DAC_RDPTBOT_ISR[x] = rdptbot_isr;
  }
  if(dac_init_struct.DAC_ReadPointerTopIntEnable == TRUE && rdpttop_isr != NULL)
  {
    dacx->C0 |= DAC_C0_DACBTIEN_MASK;   //ʹ�ܻ����������ж�
    DAC_RDPTTOP_ISR[x] = rdpttop_isr;
  }
  if(dac_init_struct.DAC_BufferWatermarkIntEnable == TRUE && watermk_isr != NULL)
  {
    dacx->C0 |= DAC_C0_DACBWIEN_MASK;   //ʹ�ܻ�����ˮӡ�ж�
    DAC_WATERMK_ISR[x] = watermk_isr;
  }
  if(dac_init_struct.DAC_SoftTrgEnable == TRUE)
  {
    dacx->C0 |= DAC_C0_DACTRGSEL_MASK;  //ʹ���������������
  }
  dacx->C0 |= DAC_C0_DACRFS_MASK;       //ʹ��DACREF_2(VDDA)Ϊ�ο���ѹ
  
  //ʹ��DACģ�飬�ɱ�̲ο���������ʼ����
  dacx->C0 |= DAC_C0_DACEN_MASK;
  
  return 1;
}

/*
 * LPLD_DAC_Deinit
 * DAC����ʼ������������DACģ��
 * 
 * ����:
 *    dac_init_struct--DAC��ʼ���ṹ�壬
 *                        ���嶨���DAC_InitTypeDef
 *
 * ���:
 *    0--���ô���
 *    1--���óɹ�
 */
uint8 LPLD_DAC_Deinit(DAC_InitTypeDef dac_init_struct)
{
  uint8 x;
  DAC_Type *dacx = dac_init_struct.DAC_Dacx;

  //�ر�DACģ��
  dacx->C0 &= ~(DAC_C0_DACEN_MASK);
  
  //�ر�DACʱ��
  if(dacx == DAC0)
  {
    x = 0;
    SIM->SCGC2 &= ~(SIM_SCGC2_DAC0_MASK);   
  }
  else if(dacx == DAC1)
  {
    x = 1;
    SIM->SCGC2 &= ~(SIM_SCGC2_DAC1_MASK);   
  }
  else 
  {
    return 0;
  }

  disable_irq((IRQn_Type)(DAC0_IRQn + x));
  
  return 1;
}

/*
 * LPLD_DAC_EnableIrq
 * ʹ��DACx�ж�
 * 
 * ����:
 *    dac_init_struct--DAC��ʼ���ṹ�壬
 *                        ���嶨���DAC_InitTypeDef
 *
 * ���:
 *    0--���ô���
 *    1--���óɹ�
 */
uint8 LPLD_DAC_EnableIrq(DAC_InitTypeDef dac_init_struct)
{
  uint8 x;
  DAC_Type *dacx = dac_init_struct.DAC_Dacx;
  
  if(dacx == DAC0)
    x = 0;
  else if(dacx == DAC1)
    x = 1;
  else
    return 0;

  enable_irq((IRQn_Type)(DAC0_IRQn + x));
  
  return 1;
}

/*
 * LPLD_DAC_DisableIrq
 * ����DACx�ж�
 * 
 * ����:
 *    dac_init_struct--DAC��ʼ���ṹ�壬
 *                        ���嶨���DAC_InitTypeDef
 *
 * ���:
 *    0--���ô���
 *    1--���óɹ�
 */
uint8 LPLD_DAC_DisableIrq(DAC_InitTypeDef dac_init_struct)
{
  uint8 x;
  DAC_Type *dacx = dac_init_struct.DAC_Dacx;
  
  if(dacx == DAC0)
    x = 0;
  else if(dacx == DAC1)
    x = 1;
  else
    return 0;

  disable_irq((IRQn_Type)(DAC0_IRQn + x));
  
  return 1;
}

/*
 * LPLD_DAC_SetBufferDataN
 * ����DAC��������������n
 * 
 * ����:
 *    dacx--DACxģ���
 *      |__DAC0          --DAC0
 *      |__DAC1          --DAC1
 *    data--�������������
 *      |__0~4095        --12λ����
 *    num--ָ��������λ��
 *      |__1~16          --��������1��16����
 *
 * ���:
 *    ��
 */
void LPLD_DAC_SetBufferDataN(DAC_Type *dacx, uint16 data, uint8 num)
{
  //�������
  ASSERT( (num <= 16)&&(num > 0) );  //�ж��������

  dacx->DAT[num-1].DATL = data & 0x0FF;
  dacx->DAT[num-1].DATH = (data & 0xF00)>>8;
}

/*
 * LPLD_DAC_SetBufferData
 * ����DAC��������������
 * 
 * ����:
 *    dacx--DACxģ���
 *      |__DAC0          --DAC0
 *      |__DAC1          --DAC1
 *    *data--�����������������ָ��
 *      |__*0~4095       --12λ��������
 *    len--�������鳤��
 *      |__1~16          --����Ϊ1~16
 *
 * ���:
 *    ��
 */
void LPLD_DAC_SetBufferData(DAC_Type *dacx, uint16 *data, uint8 len)
{
  //�������
  ASSERT( (len <= 16)&&(len > 0) );  //�ж����ݳ���
  
  for(uint8 i=0; i < len; i++)
  {
    dacx->DAT[i].DATL = data[i] & 0x0FF;
    dacx->DAT[i].DATH = (data[i] & 0xF00)>>8;
  }
}

/*
 * LPLD_DAC_SoftwareTrigger
 * �������DAC����������
 * 
 * ����:
 *    dacx--DACxģ���
 *      |__DAC0          --DAC0
 *      |__DAC1          --DAC1
 *
 * ���:
 *    ��
 */
void LPLD_DAC_SoftwareTrigger(DAC_Type *dacx)
{
  dacx->C0 |= DAC_C0_DACSWTRG_MASK;
}

/*
 * DAC0--DAC1�жϴ�����
 * �������ļ�startup_K60.s�е��ж����������
 * �û������޸ģ������Զ������Ӧͨ���жϺ���
 */

void DAC0_IRQHandler(void)
{
#if (UCOS_II > 0u)
  OS_CPU_SR  cpu_sr = 0u;
  OS_ENTER_CRITICAL(); //��֪ϵͳ��ʱ�Ѿ��������жϷ����Ӻ���
  OSIntEnter();
  OS_EXIT_CRITICAL();
#endif
  
  //�Ƿ�Ϊָ��ײ��ж�
  if((DAC0->SR & DAC_SR_DACBFRPBF_MASK) && (DAC0->C0 & DAC_C0_DACBBIEN_MASK))
  {
    //�����û��Զ����жϷ���
    DAC_RDPTBOT_ISR[0]();  
    DAC0->SR &= ~(DAC_SR_DACBFRPBF_MASK);
  }
  //�Ƿ�Ϊָ�붥���ж�
  if((DAC0->SR & DAC_SR_DACBFRPTF_MASK) && (DAC0->C0 & DAC_C0_DACBTIEN_MASK))
  {
    //�����û��Զ����жϷ���
    DAC_RDPTTOP_ISR[0]();  
    DAC0->SR &= ~(DAC_SR_DACBFRPTF_MASK);
  }
  //�Ƿ�Ϊˮӡ�ж�
  if((DAC0->SR & DAC_SR_DACBFWMF_MASK) && (DAC0->C0 & DAC_C0_DACBWIEN_MASK))
  {
    //�����û��Զ����жϷ���
    DAC_WATERMK_ISR[0]();  
    DAC0->SR &= ~(DAC_SR_DACBFWMF_MASK);
  }
  
#if (UCOS_II > 0u)
  OSIntExit();          //��֪ϵͳ��ʱ�����뿪�жϷ����Ӻ���
#endif
}

void DAC1_IRQHandler(void)
{
#if (UCOS_II > 0u)
  OS_CPU_SR  cpu_sr = 0u;
  OS_ENTER_CRITICAL(); //��֪ϵͳ��ʱ�Ѿ��������жϷ����Ӻ���
  OSIntEnter();
  OS_EXIT_CRITICAL();
#endif
  
  //�Ƿ�Ϊָ��ײ��ж�
  if((DAC1->SR & DAC_SR_DACBFRPBF_MASK) && (DAC1->C0 & DAC_C0_DACBBIEN_MASK))
  {
    //�����û��Զ����жϷ���
    DAC_RDPTBOT_ISR[1]();  
    DAC1->SR &= ~(DAC_SR_DACBFRPBF_MASK);
  }
  //�Ƿ�Ϊָ�붥���ж�
  if((DAC1->SR & DAC_SR_DACBFRPTF_MASK) && (DAC1->C0 & DAC_C0_DACBTIEN_MASK))
  {
    //�����û��Զ����жϷ���
    DAC_RDPTTOP_ISR[1]();  
    DAC1->SR &= ~(DAC_SR_DACBFRPTF_MASK);
  }
  //�Ƿ�Ϊˮӡ�ж�
  if((DAC1->SR & DAC_SR_DACBFWMF_MASK) && (DAC1->C0 & DAC_C0_DACBWIEN_MASK))
  {
    //�����û��Զ����жϷ���
    DAC_WATERMK_ISR[1]();  
    DAC1->SR &= ~(DAC_SR_DACBFWMF_MASK);
  }
  
#if (UCOS_II > 0u)
  OSIntExit();          //��֪ϵͳ��ʱ�����뿪�жϷ����Ӻ���
#endif
}