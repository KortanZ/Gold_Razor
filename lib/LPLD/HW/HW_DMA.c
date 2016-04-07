/**
 * @file HW_DMA.c
 * @version 3.0[By LPLD]
 * @date 2013-06-18
 * @brief DMA�ײ�ģ����غ���
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
#include "HW_DMA.h"

#if defined(CPU_MK60DZ10) || defined(CPU_MK60D10) 
//�û��Զ����жϷ���������
DMA_ISR_CALLBACK DMA_ISR[16];
#elif defined(CPU_MK60F12) || defined(CPU_MK60F15)
DMA_ISR_CALLBACK DMA_ISR[32];
#endif
/*
 * LPLD_DMA_Init
 * ��ʼ��eDMAģ��
 * 
 * ����:
 *    dma_init_struct--eDMA��ʼ���ṹ�壬
 *                        ���嶨���DMA_InitTypeDef
 *
 * ���:
 *    0--���ô���
 *    1--���óɹ�
 */
uint8 LPLD_DMA_Init(DMA_InitTypeDef dma_init_struct)
{
  uint8 chx = dma_init_struct.DMA_CHx;
  uint8 req = dma_init_struct.DMA_Req;
  boolean periodic_trigg = dma_init_struct.DMA_PeriodicTriggerEnable;
  uint16 major_cnt = dma_init_struct.DMA_MajorLoopCnt;
  uint32 minor_cnt = dma_init_struct.DMA_MinorByteCnt;
  uint32 src_addr = dma_init_struct.DMA_SourceAddr;
  uint8 src_dsize = dma_init_struct.DMA_SourceDataSize;
  int16 src_addroffset = dma_init_struct.DMA_SourceAddrOffset;
  int32 src_lastadj = dma_init_struct.DMA_LastSourceAddrAdj;
  uint32 dst_addr = dma_init_struct.DMA_DestAddr;
  uint8 dst_dsize = dma_init_struct.DMA_DestDataSize;
  int16 dst_addroffset = dma_init_struct.DMA_DestAddrOffset;
  int32 dst_lastadj = dma_init_struct.DMA_LastDestAddrAdj;
  boolean auto_disable = dma_init_struct.DMA_AutoDisableReq;
  
  //�������
#if defined(CPU_MK60DZ10) || defined(CPU_MK60D10) 
  ASSERT( chx <= DMA_CH15 );       //eDMAͨ��ѡ��
#elif defined(CPU_MK60F12) || defined(CPU_MK60F15)
  ASSERT( chx <= DMA_CH31 );       //eDMAͨ��ѡ��
#endif
  ASSERT( req <= DMA_MUX_63 );     //����Դѡ��
  ASSERT( major_cnt <= 0x7FFF );   //�������ж�
  ASSERT( src_addr != NULL );      //Դ��ַ�ж�
  ASSERT( (src_dsize <= DMA_SRC_32BIT)||(src_dsize == DMA_SRC_16BYTE) );     //Դ���ݴ����С�ж�
  ASSERT( dst_addr != NULL );      //Ŀ�ĵ�ַ�ж�
  ASSERT( (dst_dsize <= DMA_DST_32BIT)||(dst_dsize == DMA_DST_16BYTE) );     //Ŀ�����ݴ����С�ж�
 
#if defined(CPU_MK60DZ10) || defined(CPU_MK60D10)   
  SIM->SCGC6 |= SIM_SCGC6_DMAMUX_MASK;  //��DMAͨ����·������ʱ�� 
#elif defined(CPU_MK60F12) || defined(CPU_MK60F15)
  SIM->SCGC6 |= SIM_SCGC6_DMAMUX0_MASK;  //��DMAͨ����·������ʱ�� 
  SIM->SCGC6 |= SIM_SCGC6_DMAMUX1_MASK;  //��DMAͨ����·������ʱ�� 
#endif  
  SIM->SCGC7 |= SIM_SCGC7_DMA_MASK;     //��DMAģ��ʱ��
  
  //�ر�ͨ��xӲ��DMA���� 
  DMA0->ERQ &= ~(1<<chx);
  
  //ѡ�� ͨ��x ���������DMAԴ������
#if defined(CPU_MK60DZ10) || defined(CPU_MK60D10) 
  DMAMUX->CHCFG[chx] = DMAMUX_CHCFG_SOURCE(req);
  //�Ƿ�ʹ�����ڴ�������
  if(periodic_trigg == TRUE)
  {
    DMAMUX->CHCFG[chx] |= DMAMUX_CHCFG_TRIG_MASK;
  }
  else
  {
    DMAMUX->CHCFG[chx] &= ~(DMAMUX_CHCFG_TRIG_MASK);
  }
#elif defined(CPU_MK60F12) || defined(CPU_MK60F15)
  if(chx < 16)
  {
    DMAMUX0->CHCFG[chx] = DMAMUX_CHCFG_SOURCE(req);
    //�Ƿ�ʹ�����ڴ�������
    if(periodic_trigg == TRUE)
    {
      DMAMUX0->CHCFG[chx] |= DMAMUX_CHCFG_TRIG_MASK;
    }
    else
    {
      DMAMUX0->CHCFG[chx] &= ~(DMAMUX_CHCFG_TRIG_MASK);
    }
  }
  else // ch > 16
  {
    DMAMUX1->CHCFG[chx - 16] = DMAMUX_CHCFG_SOURCE(req);
    //�Ƿ�ʹ�����ڴ�������
    if(periodic_trigg == TRUE)
    {
      DMAMUX1->CHCFG[chx - 16] |= DMAMUX_CHCFG_TRIG_MASK;
    }
    else
    {
      DMAMUX1->CHCFG[chx - 16] &= ~(DMAMUX_CHCFG_TRIG_MASK);
    }
  }
#endif   

  
  
  //����Դ��ַ   
  DMA0->TCD[chx].SADDR = DMA_SADDR_SADDR(src_addr);
  //��ִ�������Դ��ַ�Ĳ���֮����Դ��ַ�Ļ���������/����ƫ�Ƶ�ַ
  DMA0->TCD[chx].SOFF = DMA_SOFF_SOFF(src_addroffset);
  //����Դ��ַ�Ĵ����С
  DMA0->TCD[chx].ATTR = 0 | DMA_ATTR_SSIZE(src_dsize);
  //���ļ���������major iteration count���ﵽ�����µ���Դ��ַ
  DMA0->TCD[chx].SLAST = DMA_SLAST_SLAST(src_lastadj);
  
  //����Ŀ�ĵ�ַ 
  DMA0->TCD[chx].DADDR = DMA_DADDR_DADDR(dst_addr);
  //��ִ�������Ŀ�ĵ�ַ�Ĳ���֮����Ŀ�ĵ�ַ�Ļ���������/����ƫ�Ƶ�ַ
  DMA0->TCD[chx].DOFF = DMA_DOFF_DOFF(dst_addroffset);
  //����Ŀ�ĵ�ַ�Ĵ�����
  DMA0->TCD[chx].ATTR |= DMA_ATTR_DSIZE(dst_dsize);
  //���ļ���������major iteration count���ﵽ�����µ���Ŀ�ĵ�ַ
  DMA0->TCD[chx].DLAST_SGA = DMA_DLAST_SGA_DLASTSGA(dst_lastadj);
  
  //Ĭ��Ϊ����ͨ�����ӹ��ܣ�����������Ӵ˹���
  if( 1 == 1)
  {
    //===============���������������ȣ�ѭ������====================================
    //������ѭ�������� current major loop count
    DMA0->TCD[chx].CITER_ELINKNO = DMA_CITER_ELINKNO_CITER(major_cnt);
    //��ʼѭ��������������ѭ��������Ϊ���ʱ�򣬽�װ����ʼѭ����������ֵ
    DMA0->TCD[chx].BITER_ELINKNO = DMA_CITER_ELINKNO_CITER(major_cnt);
  }
  
  //Ĭ��Ϊ���ô�ѭ����ַƫ�ƹ��ܣ�����������Ӵ˹���
  if( 1 == 1)
  {
    //��ѭ��һ�δ����ֽڵĸ���
    DMA0->TCD[chx].NBYTES_MLNO = DMA_NBYTES_MLNO_NBYTES(minor_cnt);
  }
  
  //���TCD���ƼĴ���     
  DMA0->TCD[chx].CSR = 0;
  
  //����eDMA�ж�
  if((dma_init_struct.DMA_Isr != NULL) && 
     (dma_init_struct.DMA_MajorCompleteIntEnable == TRUE))
  {

       DMA0->TCD[chx].CSR |= DMA_CSR_INTMAJOR_MASK; //ʹ��DMA ��ѭ�������������� �ж�
       DMA_ISR[chx] = dma_init_struct.DMA_Isr;
  }
  if((dma_init_struct.DMA_Isr != NULL) && 
     (dma_init_struct.DMA_MajorHalfCompleteIntEnable == TRUE))
  {

       DMA0->TCD[chx].CSR |= DMA_CSR_INTHALF_MASK; //ʹ��DMA ��ѭ������������һ�� �ж�
       DMA_ISR[chx] = dma_init_struct.DMA_Isr;
  }
    
  if(auto_disable == TRUE)
  {
     DMA0->TCD[chx].CSR |= DMA_CSR_DREQ_MASK; //��ѭ����������������Զ��ر�DMA 
  }
  else
  {
     DMA0->TCD[chx].CSR &= ~(DMA_CSR_DREQ_MASK); //��ѭ��������������󣬲��ر�DMA
  } 
 
  //DMAͨ��ʹ��
#if defined(CPU_MK60DZ10) || defined(CPU_MK60D10)   
  DMAMUX->CHCFG[chx] |= DMAMUX_CHCFG_ENBL_MASK;
#elif defined(CPU_MK60F12) || defined(CPU_MK60F15)
  if(chx < 16)
  {
    DMAMUX0->CHCFG[chx] |= DMAMUX_CHCFG_ENBL_MASK;
  }
  else
  {
    DMAMUX1->CHCFG[chx - 16] |= DMAMUX_CHCFG_ENBL_MASK;
  }
#endif
  return 1;
}

/*
 * LPLD_DMA_EnableIrq
 * ʹ��eDMA�ж�
 * 
 * ����:
 *    dma_init_struct--eDMA��ʼ���ṹ�壬
 *                        ���嶨���DMA_InitTypeDef
 *
 * ���:
 *    0--ʧ��
 *    1--�ɹ�
 */
uint8 LPLD_DMA_EnableIrq(DMA_InitTypeDef dma_init_struct)
{
#if defined(CPU_MK60DZ10) || defined(CPU_MK60D10) 
  enable_irq((IRQn_Type)(dma_init_struct.DMA_CHx + DMA0_IRQn)); 
#elif defined(CPU_MK60F12) || defined(CPU_MK60F15)
  if(dma_init_struct.DMA_CHx < 16)
  {
    enable_irq((IRQn_Type)(dma_init_struct.DMA_CHx + DMA0_DMA16_IRQn));
  }
  else // ch > 16
  {
    enable_irq((IRQn_Type)(dma_init_struct.DMA_CHx - 16 + DMA0_DMA16_IRQn));
  }
#endif 
  return 1;
}

/*
 * LPLD_DMA_DisableIrq
 * ����eDMA�ж�
 * 
 * ����:
 *    dma_init_struct--eDMA��ʼ���ṹ�壬
 *                        ���嶨���DMA_InitTypeDef
 *
 * ���:
 *    0--ʧ��
 *    1--�ɹ�
 */
uint8 LPLD_DMA_DisableIrq(DMA_InitTypeDef dma_init_struct)
{
#if defined(CPU_MK60DZ10) || defined(CPU_MK60D10) 
  disable_irq((IRQn_Type)(dma_init_struct.DMA_CHx + DMA0_IRQn)); 
#elif defined(CPU_MK60F12) || defined(CPU_MK60F15)
  if(dma_init_struct.DMA_CHx < 16)
  {
    disable_irq((IRQn_Type)(dma_init_struct.DMA_CHx + DMA0_DMA16_IRQn));
  }
  else // ch > 16
  {
    disable_irq((IRQn_Type)(dma_init_struct.DMA_CHx - 16 + DMA0_DMA16_IRQn));
  }
#endif 
  return 1;
}

/*
 * LPLD_DMA_SoftwareStartService
 * DMA�������������ʼ
 * 
 * ����:
 *    dma_init_struct--eDMA��ʼ���ṹ�壬
 *                        ���嶨���DMA_InitTypeDef
 *
 * ���:
 *    ��
 */
__INLINE void LPLD_DMA_SoftwareStartService(DMA_InitTypeDef dma_init_struct)
{
  DMA0->TCD[dma_init_struct.DMA_CHx].CSR |= DMA_CSR_START_MASK; 
}

/*
 * eDMA�жϴ�����
 * �������ļ�startup_K60.s�е��ж����������
 * �û������޸ģ������Զ������Ӧͨ���жϺ���
 */
#if defined(CPU_MK60DZ10) || defined(CPU_MK60D10) 
void DMA0_IRQHandler(void)
{
#if (UCOS_II > 0u)
  OS_CPU_SR  cpu_sr = 0u;
  OS_ENTER_CRITICAL(); //��֪ϵͳ��ʱ�Ѿ��������жϷ����Ӻ���
  OSIntEnter();
  OS_EXIT_CRITICAL();
#endif  
  
  //�����û��Զ����жϷ���
  DMA_ISR[0]();
  //����жϱ�־λ
  DMA0->INT |= 0x1u<<0;
  
#if (UCOS_II > 0u)
  OSIntExit();          //��֪ϵͳ��ʱ�����뿪�жϷ����Ӻ���
#endif
}

void DMA1_IRQHandler(void)
{
#if (UCOS_II > 0u)
  OS_CPU_SR  cpu_sr = 0u;
  OS_ENTER_CRITICAL(); //��֪ϵͳ��ʱ�Ѿ��������жϷ����Ӻ���
  OSIntEnter();
  OS_EXIT_CRITICAL();
#endif  
  
  //�����û��Զ����жϷ���
  DMA_ISR[1]();
  //����жϱ�־λ
  DMA0->INT |= 0x1u<<1;
  
#if (UCOS_II > 0u)
  OSIntExit();          //��֪ϵͳ��ʱ�����뿪�жϷ����Ӻ���
#endif
}

void DMA2_IRQHandler(void)
{
#if (UCOS_II > 0u)
  OS_CPU_SR  cpu_sr = 0u;
  OS_ENTER_CRITICAL(); //��֪ϵͳ��ʱ�Ѿ��������жϷ����Ӻ���
  OSIntEnter();
  OS_EXIT_CRITICAL();
#endif  
  
  //�����û��Զ����жϷ���
  DMA_ISR[2]();
  //����жϱ�־λ
  DMA0->INT |= 0x1u<<2;
  
#if (UCOS_II > 0u)
  OSIntExit();          //��֪ϵͳ��ʱ�����뿪�жϷ����Ӻ���
#endif
}

void DMA3_IRQHandler(void)
{
#if (UCOS_II > 0u)
  OS_CPU_SR  cpu_sr = 0u;
  OS_ENTER_CRITICAL(); //��֪ϵͳ��ʱ�Ѿ��������жϷ����Ӻ���
  OSIntEnter();
  OS_EXIT_CRITICAL();
#endif  
  
  //�����û��Զ����жϷ���
  DMA_ISR[3]();
  //����жϱ�־λ
  DMA0->INT |= 0x1u<<3;
  
#if (UCOS_II > 0u)
  OSIntExit();          //��֪ϵͳ��ʱ�����뿪�жϷ����Ӻ���
#endif
}

void DMA4_IRQHandler(void)
{
#if (UCOS_II > 0u)
  OS_CPU_SR  cpu_sr = 0u;
  OS_ENTER_CRITICAL(); //��֪ϵͳ��ʱ�Ѿ��������жϷ����Ӻ���
  OSIntEnter();
  OS_EXIT_CRITICAL();
#endif  
  
  //�����û��Զ����жϷ���
  DMA_ISR[4]();
  //����жϱ�־λ
  DMA0->INT |= 0x1u<<4;
  
#if (UCOS_II > 0u)
  OSIntExit();          //��֪ϵͳ��ʱ�����뿪�жϷ����Ӻ���
#endif
}

void DMA5_IRQHandler(void)
{
#if (UCOS_II > 0u)
  OS_CPU_SR  cpu_sr = 0u;
  OS_ENTER_CRITICAL(); //��֪ϵͳ��ʱ�Ѿ��������жϷ����Ӻ���
  OSIntEnter();
  OS_EXIT_CRITICAL();
#endif  
  
  //�����û��Զ����жϷ���
  DMA_ISR[5]();
  //����жϱ�־λ
  DMA0->INT |= 0x1u<<5;
  
#if (UCOS_II > 0u)
  OSIntExit();          //��֪ϵͳ��ʱ�����뿪�жϷ����Ӻ���
#endif
}

void DMA6_IRQHandler(void)
{
#if (UCOS_II > 0u)
  OS_CPU_SR  cpu_sr = 0u;
  OS_ENTER_CRITICAL(); //��֪ϵͳ��ʱ�Ѿ��������жϷ����Ӻ���
  OSIntEnter();
  OS_EXIT_CRITICAL();
#endif  
  
  //�����û��Զ����жϷ���
  DMA_ISR[6]();
  //����жϱ�־λ
  DMA0->INT |= 0x1u<<6;
  
#if (UCOS_II > 0u)
  OSIntExit();          //��֪ϵͳ��ʱ�����뿪�жϷ����Ӻ���
#endif
}

void DMA7_IRQHandler(void)
{
#if (UCOS_II > 0u)
  OS_CPU_SR  cpu_sr = 0u;
  OS_ENTER_CRITICAL(); //��֪ϵͳ��ʱ�Ѿ��������жϷ����Ӻ���
  OSIntEnter();
  OS_EXIT_CRITICAL();
#endif  
  
  //�����û��Զ����жϷ���
  DMA_ISR[7]();
  //����жϱ�־λ
  DMA0->INT |= 0x1u<<7;
  
#if (UCOS_II > 0u)
  OSIntExit();          //��֪ϵͳ��ʱ�����뿪�жϷ����Ӻ���
#endif
}

void DMA8_IRQHandler(void)
{
#if (UCOS_II > 0u)
  OS_CPU_SR  cpu_sr = 0u;
  OS_ENTER_CRITICAL(); //��֪ϵͳ��ʱ�Ѿ��������жϷ����Ӻ���
  OSIntEnter();
  OS_EXIT_CRITICAL();
#endif  
  
  //�����û��Զ����жϷ���
  DMA_ISR[8]();
  //����жϱ�־λ
  DMA0->INT |= 0x1u<<8;
  
#if (UCOS_II > 0u)
  OSIntExit();          //��֪ϵͳ��ʱ�����뿪�жϷ����Ӻ���
#endif
}

void DMA9_IRQHandler(void)
{
#if (UCOS_II > 0u)
  OS_CPU_SR  cpu_sr = 0u;
  OS_ENTER_CRITICAL(); //��֪ϵͳ��ʱ�Ѿ��������жϷ����Ӻ���
  OSIntEnter();
  OS_EXIT_CRITICAL();
#endif  
  
  //�����û��Զ����жϷ���
  DMA_ISR[9]();
  //����жϱ�־λ
  DMA0->INT |= 0x1u<<9;
  
#if (UCOS_II > 0u)
  OSIntExit();          //��֪ϵͳ��ʱ�����뿪�жϷ����Ӻ���
#endif
}

void DMA10_IRQHandler(void)
{
#if (UCOS_II > 0u)
  OS_CPU_SR  cpu_sr = 0u;
  OS_ENTER_CRITICAL(); //��֪ϵͳ��ʱ�Ѿ��������жϷ����Ӻ���
  OSIntEnter();
  OS_EXIT_CRITICAL();
#endif  
  
  //�����û��Զ����жϷ���
  DMA_ISR[10]();
  //����жϱ�־λ
  DMA0->INT |= 0x1u<10;
  
#if (UCOS_II > 0u)
  OSIntExit();          //��֪ϵͳ��ʱ�����뿪�жϷ����Ӻ���
#endif
}

void DMA11_IRQHandler(void)
{
#if (UCOS_II > 0u)
  OS_CPU_SR  cpu_sr = 0u;
  OS_ENTER_CRITICAL(); //��֪ϵͳ��ʱ�Ѿ��������жϷ����Ӻ���
  OSIntEnter();
  OS_EXIT_CRITICAL();
#endif  
  
  //�����û��Զ����жϷ���
  DMA_ISR[11]();
  //����жϱ�־λ
  DMA0->INT |= 0x1u<<11;
  
#if (UCOS_II > 0u)
  OSIntExit();          //��֪ϵͳ��ʱ�����뿪�жϷ����Ӻ���
#endif
}

void DMA12_IRQHandler(void)
{
#if (UCOS_II > 0u)
  OS_CPU_SR  cpu_sr = 0u;
  OS_ENTER_CRITICAL(); //��֪ϵͳ��ʱ�Ѿ��������жϷ����Ӻ���
  OSIntEnter();
  OS_EXIT_CRITICAL();
#endif  
  
  //�����û��Զ����жϷ���
  DMA_ISR[12]();
  //����жϱ�־λ
  DMA0->INT |= 0x1u<<12;
  
#if (UCOS_II > 0u)
  OSIntExit();          //��֪ϵͳ��ʱ�����뿪�жϷ����Ӻ���
#endif
}

void DMA13_IRQHandler(void)
{
#if (UCOS_II > 0u)
  OS_CPU_SR  cpu_sr = 0u;
  OS_ENTER_CRITICAL(); //��֪ϵͳ��ʱ�Ѿ��������жϷ����Ӻ���
  OSIntEnter();
  OS_EXIT_CRITICAL();
#endif  
  
  //�����û��Զ����жϷ���
  DMA_ISR[13]();
  //����жϱ�־λ
  DMA0->INT |= 0x1u<<13;
  
#if (UCOS_II > 0u)
  OSIntExit();          //��֪ϵͳ��ʱ�����뿪�жϷ����Ӻ���
#endif
}

void DMA14_IRQHandler(void)
{
#if (UCOS_II > 0u)
  OS_CPU_SR  cpu_sr = 0u;
  OS_ENTER_CRITICAL(); //��֪ϵͳ��ʱ�Ѿ��������жϷ����Ӻ���
  OSIntEnter();
  OS_EXIT_CRITICAL();
#endif  
  
  //�����û��Զ����жϷ���
  DMA_ISR[14]();
  //����жϱ�־λ
  DMA0->INT |= 0x1u<<14;
  
#if (UCOS_II > 0u)
  OSIntExit();          //��֪ϵͳ��ʱ�����뿪�жϷ����Ӻ���
#endif
}

void DMA15_IRQHandler(void)
{
#if (UCOS_II > 0u)
  OS_CPU_SR  cpu_sr = 0u;
  OS_ENTER_CRITICAL(); //��֪ϵͳ��ʱ�Ѿ��������жϷ����Ӻ���
  OSIntEnter();
  OS_EXIT_CRITICAL();
#endif  
  
  //�����û��Զ����жϷ���
  DMA_ISR[15]();
  //����жϱ�־λ
  DMA0->INT |= 0x1u<<15;
  
#if (UCOS_II > 0u)
  OSIntExit();          //��֪ϵͳ��ʱ�����뿪�жϷ����Ӻ���
#endif
}
#elif defined(CPU_MK60F12) || defined(CPU_MK60F15)
//DMA0 DMA16���ô�Handler
void DMA0_IRQHandler(void)
{
#if (UCOS_II > 0u)
  OS_CPU_SR  cpu_sr = 0u;
  OS_ENTER_CRITICAL(); //��֪ϵͳ��ʱ�Ѿ��������жϷ����Ӻ���
  OSIntEnter();
  OS_EXIT_CRITICAL();
#endif  
  
  if( DMA0->INT & 0x1u<<0)
  {
    //�����û��Զ����жϷ���
    DMA_ISR[0]();
    //����жϱ�־λ
    DMA0->INT |= 0x1u<<0;
  }
  else if(DMA0->INT & 0x1u<<16)
  {
    //�����û��Զ����жϷ���
    DMA_ISR[16]();
    //����жϱ�־λ
    DMA0->INT |= 0x1u<<16;
  }
  else
  {}
  
#if (UCOS_II > 0u)
  OSIntExit();          //��֪ϵͳ��ʱ�����뿪�жϷ����Ӻ���
#endif
}
//DMA1 DMA17���ô�Handler
void DMA1_IRQHandler(void)
{
#if (UCOS_II > 0u)
  OS_CPU_SR  cpu_sr = 0u;
  OS_ENTER_CRITICAL(); //��֪ϵͳ��ʱ�Ѿ��������жϷ����Ӻ���
  OSIntEnter();
  OS_EXIT_CRITICAL();
#endif  
  
  if( DMA0->INT & 0x1u<<1)
  {
    //�����û��Զ����жϷ���
    DMA_ISR[1]();
    //����жϱ�־λ
    DMA0->INT |= 0x1u<<1;
  }
  else if(DMA0->INT & 0x1u<<17)
  {
    //�����û��Զ����жϷ���
    DMA_ISR[17]();
    //����жϱ�־λ
    DMA0->INT |= 0x1u<<17;
  }
  else
  {}
  
#if (UCOS_II > 0u)
  OSIntExit();          //��֪ϵͳ��ʱ�����뿪�жϷ����Ӻ���
#endif
}
//DMA2 DMA18���ô�Handler
void DMA2_IRQHandler(void)
{
#if (UCOS_II > 0u)
  OS_CPU_SR  cpu_sr = 0u;
  OS_ENTER_CRITICAL(); //��֪ϵͳ��ʱ�Ѿ��������жϷ����Ӻ���
  OSIntEnter();
  OS_EXIT_CRITICAL();
#endif  
  
  if( DMA0->INT & 0x1u<<2)
  {
    //�����û��Զ����жϷ���
    DMA_ISR[2]();
    //����жϱ�־λ
    DMA0->INT |= 0x1u<<2;
  }
  else if(DMA0->INT & 0x1u<<18)
  {
    //�����û��Զ����жϷ���
    DMA_ISR[18]();
    //����жϱ�־λ
    DMA0->INT |= 0x1u<<18;
  }
  else
  {}
  
#if (UCOS_II > 0u)
  OSIntExit();          //��֪ϵͳ��ʱ�����뿪�жϷ����Ӻ���
#endif
}
//DMA3 DMA19���ô�Handler
void DMA3_IRQHandler(void)
{
#if (UCOS_II > 0u)
  OS_CPU_SR  cpu_sr = 0u;
  OS_ENTER_CRITICAL(); //��֪ϵͳ��ʱ�Ѿ��������жϷ����Ӻ���
  OSIntEnter();
  OS_EXIT_CRITICAL();
#endif  
  
  if( DMA0->INT & 0x1u<<3)
  {
    //�����û��Զ����жϷ���
    DMA_ISR[3]();
    //����жϱ�־λ
    DMA0->INT |= 0x1u<<3;
  }
  else if(DMA0->INT & 0x1u<<19)
  {
    //�����û��Զ����жϷ���
    DMA_ISR[19]();
    //����жϱ�־λ
    DMA0->INT |= 0x1u<<19;
  }
  else
  {}
  
#if (UCOS_II > 0u)
  OSIntExit();          //��֪ϵͳ��ʱ�����뿪�жϷ����Ӻ���
#endif
}
//DMA4 DMA20���ô�Handler
void DMA4_IRQHandler(void)
{
#if (UCOS_II > 0u)
  OS_CPU_SR  cpu_sr = 0u;
  OS_ENTER_CRITICAL(); //��֪ϵͳ��ʱ�Ѿ��������жϷ����Ӻ���
  OSIntEnter();
  OS_EXIT_CRITICAL();
#endif  
  
  if( DMA0->INT & 0x1u<<4)
  {
    //�����û��Զ����жϷ���
    DMA_ISR[4]();
    //����жϱ�־λ
    DMA0->INT |= 0x1u<<4;
  }
  else if(DMA0->INT & 0x1u<<20)
  {
    //�����û��Զ����жϷ���
    DMA_ISR[20]();
    //����жϱ�־λ
    DMA0->INT |= 0x1u<<20;
  }
  else
  {}
  
#if (UCOS_II > 0u)
  OSIntExit();          //��֪ϵͳ��ʱ�����뿪�жϷ����Ӻ���
#endif
}
//DMA5 DMA21���ô�Handler
void DMA5_IRQHandler(void)
{
#if (UCOS_II > 0u)
  OS_CPU_SR  cpu_sr = 0u;
  OS_ENTER_CRITICAL(); //��֪ϵͳ��ʱ�Ѿ��������жϷ����Ӻ���
  OSIntEnter();
  OS_EXIT_CRITICAL();
#endif  
  
  if( DMA0->INT & 0x1u<<5)
  {
    //�����û��Զ����жϷ���
    DMA_ISR[5]();
    //����жϱ�־λ
    DMA0->INT |= 0x1u<<5;
  }
  else if(DMA0->INT & 0x1u<<21)
  {
    //�����û��Զ����жϷ���
    DMA_ISR[21]();
    //����жϱ�־λ
    DMA0->INT |= 0x1u<<21;
  }
  else
  {}
  
#if (UCOS_II > 0u)
  OSIntExit();          //��֪ϵͳ��ʱ�����뿪�жϷ����Ӻ���
#endif
}
//DMA6 DMA22���ô�Handler
void DMA6_IRQHandler(void)
{
#if (UCOS_II > 0u)
  OS_CPU_SR  cpu_sr = 0u;
  OS_ENTER_CRITICAL(); //��֪ϵͳ��ʱ�Ѿ��������жϷ����Ӻ���
  OSIntEnter();
  OS_EXIT_CRITICAL();
#endif  
  
  if( DMA0->INT & 0x1u<<6)
  {
    //�����û��Զ����жϷ���
    DMA_ISR[6]();
    //����жϱ�־λ
    DMA0->INT |= 0x1u<<6;
  }
  else if(DMA0->INT & 0x1u<<22)
  {
    //�����û��Զ����жϷ���
    DMA_ISR[22]();
    //����жϱ�־λ
    DMA0->INT |= 0x1u<<22;
  }
  else
  {}
  
#if (UCOS_II > 0u)
  OSIntExit();          //��֪ϵͳ��ʱ�����뿪�жϷ����Ӻ���
#endif
}
//DMA7 DMA23���ô�Handler
void DMA7_IRQHandler(void)
{
#if (UCOS_II > 0u)
  OS_CPU_SR  cpu_sr = 0u;
  OS_ENTER_CRITICAL(); //��֪ϵͳ��ʱ�Ѿ��������жϷ����Ӻ���
  OSIntEnter();
  OS_EXIT_CRITICAL();
#endif  
  
  if( DMA0->INT & 0x1u<<7 )
  {
    //�����û��Զ����жϷ���
    DMA_ISR[7]();
    //����жϱ�־λ
    DMA0->INT |= 0x1u<<7;
  }
  else if( DMA0->INT & 0x1u<<23 )
  {
    //�����û��Զ����жϷ���
    DMA_ISR[23]();
    //����жϱ�־λ
    DMA0->INT |= 0x1u<<23;
  }
  else
  {}
  
#if (UCOS_II > 0u)
  OSIntExit();          //��֪ϵͳ��ʱ�����뿪�жϷ����Ӻ���
#endif
}
//DMA8 DMA24���ô�Handler
void DMA8_IRQHandler(void)
{
#if (UCOS_II > 0u)
  OS_CPU_SR  cpu_sr = 0u;
  OS_ENTER_CRITICAL(); //��֪ϵͳ��ʱ�Ѿ��������жϷ����Ӻ���
  OSIntEnter();
  OS_EXIT_CRITICAL();
#endif  
  
  if( DMA0->INT & 0x1u<<8 )
  {
    //�����û��Զ����жϷ���
    DMA_ISR[8]();
    //����жϱ�־λ
    DMA0->INT |= 0x1u<<8;
  }
  else if( DMA0->INT & 0x1u<<24 )
  {
    //�����û��Զ����жϷ���
    DMA_ISR[24]();
    //����жϱ�־λ
    DMA0->INT |= 0x1u<<24;
  }
  else
  {}
  
#if (UCOS_II > 0u)
  OSIntExit();          //��֪ϵͳ��ʱ�����뿪�жϷ����Ӻ���
#endif
}
//DMA9 DMA25���ô�Handler
void DMA9_IRQHandler(void)
{
#if (UCOS_II > 0u)
  OS_CPU_SR  cpu_sr = 0u;
  OS_ENTER_CRITICAL(); //��֪ϵͳ��ʱ�Ѿ��������жϷ����Ӻ���
  OSIntEnter();
  OS_EXIT_CRITICAL();
#endif  
  
  if( DMA0->INT & 0x1u<<9 )
  {
    //�����û��Զ����жϷ���
    DMA_ISR[9]();
    //����жϱ�־λ
    DMA0->INT |= 0x1u<<9;
  }
  else if( DMA0->INT & 0x1u<<25 )
  {
    //�����û��Զ����жϷ���
    DMA_ISR[25]();
    //����жϱ�־λ
    DMA0->INT |= 0x1u<<25;
  }
  else
  {}
  
#if (UCOS_II > 0u)
  OSIntExit();          //��֪ϵͳ��ʱ�����뿪�жϷ����Ӻ���
#endif
}
//DMA10 DMA26���ô�Handler
void DMA10_IRQHandler(void)
{
#if (UCOS_II > 0u)
  OS_CPU_SR  cpu_sr = 0u;
  OS_ENTER_CRITICAL(); //��֪ϵͳ��ʱ�Ѿ��������жϷ����Ӻ���
  OSIntEnter();
  OS_EXIT_CRITICAL();
#endif  
  
  if( DMA0->INT & 0x1u<<10 )
  {
    //�����û��Զ����жϷ���
    DMA_ISR[10]();
    //����жϱ�־λ
    DMA0->INT |= 0x1u<<10;
  }
  else if( DMA0->INT & 0x1u<<26 )
  {
    //�����û��Զ����жϷ���
    DMA_ISR[26]();
    //����жϱ�־λ
    DMA0->INT |= 0x1u<<26;
  }
  else
  {}
  
#if (UCOS_II > 0u)
  OSIntExit();          //��֪ϵͳ��ʱ�����뿪�жϷ����Ӻ���
#endif
}
//DMA11 DMA27���ô�Handler
void DMA11_IRQHandler(void)
{
#if (UCOS_II > 0u)
  OS_CPU_SR  cpu_sr = 0u;
  OS_ENTER_CRITICAL(); //��֪ϵͳ��ʱ�Ѿ��������жϷ����Ӻ���
  OSIntEnter();
  OS_EXIT_CRITICAL();
#endif  
  
  if( DMA0->INT & 0x1u<<11 )
  {
    //�����û��Զ����жϷ���
    DMA_ISR[11]();
    //����жϱ�־λ
    DMA0->INT |= 0x1u<<11;
  }
  else if( DMA0->INT & 0x1u<<27 )
  {
    //�����û��Զ����жϷ���
    DMA_ISR[27]();
    //����жϱ�־λ
    DMA0->INT |= 0x1u<<27;
  }
  else
  {}  
#if (UCOS_II > 0u)
  OSIntExit();          //��֪ϵͳ��ʱ�����뿪�жϷ����Ӻ���
#endif
}
//DMA12 DMA28���ô�Handler
void DMA12_IRQHandler(void)
{
#if (UCOS_II > 0u)
  OS_CPU_SR  cpu_sr = 0u;
  OS_ENTER_CRITICAL(); //��֪ϵͳ��ʱ�Ѿ��������жϷ����Ӻ���
  OSIntEnter();
  OS_EXIT_CRITICAL();
#endif  
  
  if( DMA0->INT & 0x1u<<12 )
  {
    //�����û��Զ����жϷ���
    DMA_ISR[12]();
    //����жϱ�־λ
    DMA0->INT |= 0x1u<<12;
  }
  else if( DMA0->INT & 0x1u<<28 )
  {
    //�����û��Զ����жϷ���
    DMA_ISR[28]();
    //����жϱ�־λ
    DMA0->INT |= 0x1u<<28;
  }
  else
  {}  
  
#if (UCOS_II > 0u)
  OSIntExit();          //��֪ϵͳ��ʱ�����뿪�жϷ����Ӻ���
#endif
}
//DMA13 DMA29���ô�Handler
void DMA13_IRQHandler(void)
{
#if (UCOS_II > 0u)
  OS_CPU_SR  cpu_sr = 0u;
  OS_ENTER_CRITICAL(); //��֪ϵͳ��ʱ�Ѿ��������жϷ����Ӻ���
  OSIntEnter();
  OS_EXIT_CRITICAL();
#endif  
  
  if( DMA0->INT & 0x1u<<13 )
  {
    //�����û��Զ����жϷ���
    DMA_ISR[13]();
    //����жϱ�־λ
    DMA0->INT |= 0x1u<<13;
  }
  else if( DMA0->INT & 0x1u<<29 )
  {
    //�����û��Զ����жϷ���
    DMA_ISR[29]();
    //����жϱ�־λ
    DMA0->INT |= 0x1u<<29;
  }
  else
  {}   
  
#if (UCOS_II > 0u)
  OSIntExit();          //��֪ϵͳ��ʱ�����뿪�жϷ����Ӻ���
#endif
}
//DMA14 DMA30���ô�Handler
void DMA14_IRQHandler(void)
{
#if (UCOS_II > 0u)
  OS_CPU_SR  cpu_sr = 0u;
  OS_ENTER_CRITICAL(); //��֪ϵͳ��ʱ�Ѿ��������жϷ����Ӻ���
  OSIntEnter();
  OS_EXIT_CRITICAL();
#endif  
  
  if( DMA0->INT & 0x1u<<14 )
  {
    //�����û��Զ����жϷ���
    DMA_ISR[14]();
    //����жϱ�־λ
    DMA0->INT |= 0x1u<<14;
  }
  else if( DMA0->INT & 0x1u<<30 )
  {
    //�����û��Զ����жϷ���
    DMA_ISR[30]();
    //����жϱ�־λ
    DMA0->INT |= 0x1u<<30;
  }
  else
  {}   
  
#if (UCOS_II > 0u)
  OSIntExit();          //��֪ϵͳ��ʱ�����뿪�жϷ����Ӻ���
#endif
}

//DMA15 DMA31���ô�Handler
void DMA15_IRQHandler(void)
{
#if (UCOS_II > 0u)
  OS_CPU_SR  cpu_sr = 0u;
  OS_ENTER_CRITICAL(); //��֪ϵͳ��ʱ�Ѿ��������жϷ����Ӻ���
  OSIntEnter();
  OS_EXIT_CRITICAL();
#endif  
  
  if( DMA0->INT & 0x1u<<15 )
  {
    //�����û��Զ����жϷ���
    DMA_ISR[15]();
    //����жϱ�־λ
    DMA0->INT |= 0x1u<<15;
  }
  else if( DMA0->INT & 0x1u<<31 )
  {
    //�����û��Զ����жϷ���
    DMA_ISR[31]();
    //����жϱ�־λ
    DMA0->INT |= 0x1u<<31;
  }
  else
  {}
  
#if (UCOS_II > 0u)
  OSIntExit();          //��֪ϵͳ��ʱ�����뿪�жϷ����Ӻ���
#endif
}
#endif















