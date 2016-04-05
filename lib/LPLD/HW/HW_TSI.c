/**
 * @file HW_TSI.c
 * @version 3.0[By LPLD]
 * @date 2013-06-18
 * @brief TSI�ײ�ģ����غ���
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
#include "HW_TSI.h"


//�û��Զ����жϷ���������
TSI_ISR_CALLBACK TSI_ISR[2];

//ͨ����׼ֵ
uint16 TSI_ChxBaseVal[16];

const uint16* TSI_CNTR[16]={(uint16*)&TSI0->CNTR1, (uint16*)(&TSI0->CNTR1)+1,
                            (uint16*)&TSI0->CNTR3, (uint16*)(&TSI0->CNTR3)+1,
                            (uint16*)&TSI0->CNTR5, (uint16*)(&TSI0->CNTR5)+1,
                            (uint16*)&TSI0->CNTR7, (uint16*)(&TSI0->CNTR7)+1,
                            (uint16*)&TSI0->CNTR9, (uint16*)(&TSI0->CNTR9)+1,
                            (uint16*)&TSI0->CNTR11, (uint16*)(&TSI0->CNTR11)+1,
                            (uint16*)&TSI0->CNTR13, (uint16*)(&TSI0->CNTR13)+1,
                            (uint16*)&TSI0->CNTR15, (uint16*)(&TSI0->CNTR15)+1}; 
 
const uint32* TSI_PORT[32]={(uint32*)&PORTB->PCR[0], (uint32*)&PORTA->PCR[0], (uint32*)&PORTA->PCR[1], (uint32*)&PORTA->PCR[2],
                            (uint32*)&PORTA->PCR[3], (uint32*)&PORTA->PCR[4], (uint32*)&PORTB->PCR[1], (uint32*)&PORTB->PCR[2], 
                            (uint32*)&PORTB->PCR[3], (uint32*)&PORTB->PCR[16], (uint32*)&PORTB->PCR[17], (uint32*)&PORTB->PCR[18], 
                            (uint32*)&PORTB->PCR[19], (uint32*)&PORTC->PCR[0], (uint32*)&PORTC->PCR[1], (uint32*)&PORTC->PCR[2]};

/*
 * LPLD_TSI_Init
 * TSIͨ�ó�ʼ������
 * 
 * ����:
 *    tsi_init_struct--TSI��ʼ���ṹ�壬
 *                        ���嶨���TSI_InitTypeDef
 *
 * ���:
 *    0--���ô���
 *    1--���óɹ�
 */
uint8 LPLD_TSI_Init(TSI_InitTypeDef tsi_init_struct)
{
  uint16 chs = tsi_init_struct.TSI_Chs;
  uint8 mode = tsi_init_struct.TSI_ScanTriggerMode;
  uint8 esor = tsi_init_struct.TSI_EndScanOrOutRangeInt;
  boolean err = tsi_init_struct.TIS_ErrIntEnable;
   
  //�������
  ASSERT( chs != 0);                  //�ж�ͨ��
  ASSERT( mode <= TSI_SCAN_PERIOD);   //�ж��ж�ģʽ
  ASSERT( esor <= TSI_ENDOFDCAN_INT);//�ж��ж�ģʽ
  
  //����TSIģ��ʱ��
  SIM->SCGC5 |= (SIM_SCGC5_TSI_MASK); 
  
  //����ʹ�����ͨ�������Ÿ��ù���
  for(uint8 i=0; i<16; i++)
  {
    if((chs>>i)&0x1L)
    {
      *((uint32 *)TSI_PORT) = PORT_PCR_MUX(0); 
    }
  }
  
  //����ͨ�ÿ��ƼĴ���
  TSI0->GENCS = ((TSI_GENCS_NSCN(10))  //ÿ���缫ÿ��ɨ��(10)�Ρ�
                  |(TSI_GENCS_PS(3)));  //�缫����(2^3)��Ƶ
  //����ɨ��Ĵ���
  TSI0->SCANC = ((TSI_SCANC_EXTCHRG(3))        //0.8pF�ڲ��ο�����
                  |(TSI_SCANC_REFCHRG(31))      //32uA������
#if defined(CPU_MK60DZ10)
                  |(TSI_SCANC_DELVOL(7))        //600mV�����ѹ
#endif
                  |(TSI_SCANC_SMOD(0))          //ɨ������mod
                  |(TSI_SCANC_AMPSC(0)));       //����ʱ��(2^0)��Ƶ
  //ʹ��ͨ��
  TSI0->PEN = chs;
  
  //ʹ������ж�
  //TSI_ENDOFDCAN_INT��TSI_OUTOFRANGE_INTֻ��ѡ����һ
  if(tsi_init_struct.TSI_EndScanIsr!=NULL && esor==TSI_ENDOFDCAN_INT)
  {
    TSI0->GENCS |= TSI_GENCS_ESOR_MASK;
    TSI_ISR[0] = tsi_init_struct.TSI_EndScanIsr;
    TSI0->GENCS |= TSI_GENCS_TSIIE_MASK;   
  }
  else if(tsi_init_struct.TSI_OutRangeIsr!=NULL && esor==TSI_OUTOFRANGE_INT)
  {
    TSI0->GENCS &= ~(TSI_GENCS_ESOR_MASK);
    TSI_ISR[0] = tsi_init_struct.TSI_OutRangeIsr;
    TSI0->GENCS |= TSI_GENCS_TSIIE_MASK;  
  }
  if(tsi_init_struct.TSI_ErrIsr!=NULL && err==TRUE)
  {
    TSI0->GENCS |= TSI_GENCS_ERIE_MASK;
    TSI_ISR[1] = tsi_init_struct.TSI_EndScanIsr;
    TSI0->GENCS |= TSI_GENCS_TSIIE_MASK;  
  }
    
  //ʹ��TSIģ��  
  TSI0->GENCS |= (TSI_GENCS_TSIEN_MASK); 
 
  //�Ƿ���л�׼ֵУ��
  if(tsi_init_struct.TSI_IsInitSelfCal == TRUE)
  {
    //ʹ���������
    TSI0->GENCS |= TSI_GENCS_SWTS_MASK;
    //�ȴ�ɨ�����
    while(!(TSI0->GENCS&TSI_GENCS_EOSF_MASK)){};
    for(uint16 i=0; i<5000; i++)
    {
      for(uint8 j=0; j<200; j++)
      {
        asm("NOP");
      }
    }
    //����׼ֵ���顢��ֵ�Ĵ���
    for(uint8 i=0; i<16; i++)
    {
      if((chs>>i)&0x1L)
      {
        TSI_ChxBaseVal[i] = *((uint16 *)TSI_CNTR[i]);
#if defined(CPU_MK60DZ10)
        TSI0->THRESHLD[i] = TSI_ChxBaseVal[i] + TSI_OVERRUN_VAL;
#elif defined(CPU_MK60F12) || defined(CPU_MK60F15)
        TSI0->THRESHOLD = TSI_ChxBaseVal[i] + TSI_OVERRUN_VAL;
#endif
      }
    }  
  }
  else
  {
    for(uint8 i=0; i<16; i++)
    {
      TSI_ChxBaseVal[i] = TSI_BASE_VAL;
    }
  }
  
  //����ɨ��ģʽor�������ģʽ
  if(mode == TSI_SCAN_PERIOD)
  {
    TSI0->GENCS |= TSI_GENCS_STM_MASK;
  }
  else
  {
    TSI0->GENCS &= ~(TSI_GENCS_STM_MASK);
  }
  
  return 1;
}

/*
 * LPLD_TSI_Deinit
 * TSI����ʼ������
 * 
 * ����:
 *    ��
 *
 * ���:
 *    ��
 */
void LPLD_TSI_Deinit(void)
{
  LPLD_TSI_DisableIrq();
#if defined(CPU_MK60DZ10)
  TSI0->STATUS = 0xFFFFFFFF;
#endif
  TSI0->PEN = 0;
  TSI0->SCANC = 0;
  TSI0->GENCS = 0;
  //�ر�TSIģ��ʱ��
  SIM->SCGC5 &= ~(SIM_SCGC5_TSI_MASK); 
}

/*
 * LPLD_TSI_IsChxTouched
 * ͨ��x�ĵ缫�Ƿ񱻴���
 * 
 * ����:
 *    ch_num--ͨ��x������
 *      |_0~15
 *
 * ���:
 *    TRUE-�д���
 *    FALSE-δ����
 */
boolean LPLD_TSI_IsChxTouched(uint8 ch_num)
{ 
  if(TSI_ChxBaseVal[ch_num]<*((uint16 *)TSI_CNTR[ch_num]))
    return TRUE;
  return FALSE;
}

/*
 * TSI�жϴ�����
 * �������ļ�startup_K60.s�е��ж����������
 * �û������޸ģ������Զ������Ӧͨ���жϺ���
 */
void TSI_IRQHandler(void)
{
#if (UCOS_II > 0u)
  OS_CPU_SR  cpu_sr = 0u;
  OS_ENTER_CRITICAL(); //��֪ϵͳ��ʱ�Ѿ��������жϷ����Ӻ���
  OSIntEnter();
  OS_EXIT_CRITICAL();
#endif
  
  if(TSI0->GENCS&(TSI_GENCS_ESOR_MASK|TSI_GENCS_EOSF_MASK) &&
     TSI_ISR[0] != NULL)
  {
    TSI_ISR[0]();
    TSI0->GENCS |= TSI_GENCS_OUTRGF_MASK;
    TSI0->GENCS |= TSI_GENCS_EOSF_MASK;
#if defined(CPU_MK60DZ10)
    TSI0->STATUS = 0x0000FFFF;
#endif
  }
#if defined(CPU_MK60DZ10)
  else if(TSI0->STATUS != 0 && TSI_ISR[1] != NULL)
  {
    TSI_ISR[1]();
    TSI0->STATUS = 0xFFFF0000;
  }
#endif   
#if (UCOS_II > 0u)
  OSIntExit();          //��֪ϵͳ��ʱ�����뿪�жϷ����Ӻ���
#endif
}