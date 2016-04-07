/**
 * @file HW_PDB.c
 * @version 3.0[By LPLD]
 * @date 2013-06-18
 * @brief PDB�ײ�ģ����غ���
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
#include "HW_PDB.h"

//�û��Զ����жϷ���������
PDB_ISR_CALLBACK PDB_ISR[1];
PDB_ISR_CALLBACK PDB_SE_ISR[1];

//PDBʱ��Ԥ��Ƶϵ������
const uint8 pdb_sc_mults[4] = {1, 10, 20, 40};


/*
 * LPLD_PDB_Init
 * PDBxģ��ͨ�ó�ʼ����������ʼ��PDBx���������ڡ�����ģʽ������Դ���жϵ�����
 * 
 * ����:
 *    pdb_init_struct--PDBx��ʼ���ṹ�壬
 *                        ���嶨���PDB_InitTypeDef
 *
 * ���:
 *    0--���ô���
 *    1--���óɹ�
 */
uint8 LPLD_PDB_Init(PDB_InitTypeDef pdb_init_struct)
{
  uint32 us = pdb_init_struct.PDB_CounterPeriodUs
            + pdb_init_struct.PDB_CounterPeriodMs*1000
            + pdb_init_struct.PDB_CounterPeriodS*1000000;
  uint32 delayus = pdb_init_struct.PDB_DelayUs
            + pdb_init_struct.PDB_DelayMs*1000
            + pdb_init_struct.PDB_DelayS*1000000;
  uint8 loadmode = pdb_init_struct.PDB_LoadModeSel;
  uint8 trriger = pdb_init_struct.PDB_TriggerInputSourceSel;
  uint32 bus_clk = g_bus_clock/1000000;
  uint8 prescaler, mult;
  uint32 mod;
  float32 temp;
  
  //�������
  ASSERT( loadmode <= LOADMODE_3 );       //����ģʽѡ��
  ASSERT( trriger <= TRIGGER_SOFTWARE );  //��������Դѡ��
  
/*
 *************************************************
  ��LPLDע�⡿PDB�ؼ�ϵ��
  prescaler(����ʱ��Ԥ��Ƶϵ��): 2^n(n:0~7)
  mult(prescaler�ı���): 1��10��20��40
  mod(������ģ����Ӱ�����������): 0~0xFFFF
  ���������� = (prescaler*mult*mod)/bus_clk
 *************************************************
 */
  
  //���������ļ����������Զ��趨prescaler��mult��mod��ֵ
  for(uint8 i=0; i<4; i++)
  {
    mult = i;
    for(uint8 j=0; j<8; j++)
    {
      prescaler = j;
      mod = (bus_clk*us)/((1<<j)*pdb_sc_mults[i]);
      if(mod <= 0xFFFFu)
        break;
    }
    if(mod <= 0xFFFFu)
      break;
    else if(i == 3)
      return 0;         //PDB�����������õĹ�С���������
  }
  
  //ʹ��PDBʱ��
  SIM->SCGC6 |= SIM_SCGC6_PDB_MASK;
  
  //��ʼ��SC�Ĵ���
  PDB0->SC = 0x00;
  //ʹ��PDB
  PDB0->SC |= PDB_SC_PDBEN_MASK;
  PDB0->SC |= PDB_SC_MULT(mult);
  PDB0->SC |= PDB_SC_PRESCALER(prescaler);
  //����MOD��IDLY��CHnDLYm��INTx��POyDLY�Ĵ����ļ���ģʽ
  PDB0->SC |= PDB_SC_LDMOD(loadmode); 
  //���ô�������Դ
  PDB0->SC |= PDB_SC_TRGSEL(trriger);
  
  //�Ƿ�ʹ������ģʽ
  if(pdb_init_struct.PDB_ContinuousModeEnable == TRUE)
    PDB0->SC |= PDB_SC_CONT_MASK;
  else
    PDB0->SC &= ~(PDB_SC_CONT_MASK);
  
  //�Ƿ�ʹ��DMA
  if(pdb_init_struct.PDB_DmaEnable == TRUE)
    PDB0->SC |= PDB_SC_DMAEN_MASK;
  else
    PDB0->SC &= ~(PDB_SC_DMAEN_MASK);
  
  if(pdb_init_struct.PDB_Isr != NULL)
  {
    PDB_ISR[0] = pdb_init_struct.PDB_Isr;
    //�Ƿ�ʹ��PDB�ж�
    if(pdb_init_struct.PDB_IntEnable == TRUE)
      PDB0->SC |= PDB_SC_PDBIE_MASK;
    else
      PDB0->SC &= ~(PDB_SC_PDBIE_MASK);
  }
  
  if(pdb_init_struct.PDB_SeqErrIsr != NULL)
  {
    PDB_SE_ISR[0] = pdb_init_struct.PDB_SeqErrIsr;
    //�Ƿ�ʹ��PDB���д����ж�
    if(pdb_init_struct.PDB_SeqErrIntEnable == TRUE)
      PDB0->SC |= PDB_SC_PDBEIE_MASK;
    else
      PDB0->SC &= ~(PDB_SC_PDBEIE_MASK);
  }
  
  //����PDB�ж���ʱʱ��
  if( delayus <= us )
  {
    temp = (float32)mod/(float32)us;
    PDB0->IDLY = (uint32)(delayus*temp);
  }
  
  //����ֵ
  PDB0->SC |= PDB_SC_LDOK_MASK;
  
  return 1;
}

/*
 * LPLD_PDB_Deinit
 * PDBxģ�鷴��ʼ������������PDBx���й���
 * 
 * ����:
 *    ��
 *
 * ���:
 *    ��
 */
void LPLD_PDB_Deinit(void)
{
 
  PDB0->CH[0].C1 = 0;
  PDB0->CH[1].C1 = 0;
  
  PDB0->DAC[0].INTC = 0;
  PDB0->DAC[1].INTC = 0;
  
  PDB0->SC = 0;
  
  //����PDBʱ��
  SIM->SCGC6 &= ~(SIM_SCGC6_PDB_MASK);
  
  disable_irq(PDB0_IRQn);
}


/*
 * LPLD_PDB_AdcTriggerCfg
 * PDBx����ADCxģ�����ú���
 * 
 * ����:
 *    adcx--ADCxģ���
 *      |__ADC0          --ADC0
 *      |__ADC1          --ADC1
 *    cfg--ADCxԤ�����������ã��ɶ��ֵ�ϲ�����(eg. cfg=PRETRIG_EN_A|PRETRIG_DLY_A;)
 *      ADCx A������
 *      |__PRETRIG_EN_A  --ʹ��ADCx��A��Ԥ��������
 *      |__PRETRIG_DLY_A --ʹ��ADCx��A����ʱ���Ԥ��������
 *      |__PRETRIG_BB_A  --ʹ��ADCx��A�顰Back to Back��ģʽ
 *      ADCx B������
 *      |__PRETRIG_EN_B  --ʹ��ADCx��B��Ԥ��������
 *      |__PRETRIG_DLY_B --ʹ��ADCx��B����ʱ���Ԥ��������
 *      |__PRETRIG_BB_B  --ʹ��ADCx��B�顰Back to Back��ģʽ
 *    delay--ADCx A��B�����ʱ���Ԥ����ʱ�䣬��λus
 *      |__0~0xFFFF      --0~4095us
 *
 * ���:
 *    0--���ô���
 *    1--���óɹ�
 */
uint8 LPLD_PDB_AdcTriggerCfg(ADC_Type *adcx, uint32 cfg, uint16 delay)
{
  uint8 n,m;
  uint8 prescaler, mult;
  uint32 bus_clk = g_bus_clock/1000000;

  if(adcx == ADC0)
    n = 0;
  else if(adcx == ADC1)
    n = 1;
#if defined(CPU_MK60F12) || defined(CPU_MK60F15)
  else if(adcx == ADC2)
    n = 2;
  else if(adcx == ADC3)
    n = 3;  
#endif 
  else
    return 0;
    
  if(cfg & 0x01)
    m = 0;
  else if(cfg & 0x02)
    m = 1;
  else
    return 0;
  
  prescaler = 1<<((PDB0->SC & PDB_SC_PRESCALER_MASK) >> PDB_SC_PRESCALER_SHIFT);
  mult = pdb_sc_mults[(PDB0->SC & PDB_SC_MULT_MASK) >> PDB_SC_MULT_SHIFT];
  
  PDB0->CH[n].C1 |= cfg;        //���ݲ�������BBģʽ��ѡ��Ԥ���������ʹ��Ԥ����
  PDB0->CH[n].DLY[m] = (bus_clk * delay)/(prescaler * mult);    //����ADCn��m��Ԥ������ʱֵ
  
  PDB0->SC |= PDB_SC_LDOK_MASK; //����ֵ
  
  return 1;
}

/*
 * LPLD_PDB_DacTriggerCfg
 * PDBx����DACxģ�����ú���
 * 
 * ����:
 *    dacx--DACxģ���
 *      |__DAC0          --DAC0
 *      |__DAC1          --DAC1
 *    cfg--DACx������������
 *      |__EXT_TRIG_EN   --ʹ���ⲿ����
 *      |__EINT_TRIG_EN  --ʹ���ڲ��������
 *    int_delay--DACx�������ʱ�䣬��λus
 *      |__0~0xFFFF      --0~4095us
 *
 * ���:
 *    0--���ô���
 *    1--���óɹ�
 */
uint8 LPLD_PDB_DacTriggerCfg(DAC_Type *dacx, uint32 cfg, uint16 int_delay)
{
  uint8 n;
  uint8 prescaler, mult;
  uint32 bus_clk = g_bus_clock/1000000;
  
  if(dacx == DAC0)
    n = 0;
  else if(dacx == DAC1)
    n = 1;
  else
    return 0;
  
  prescaler = 1<<((PDB0->SC & PDB_SC_PRESCALER_MASK) >> PDB_SC_PRESCALER_SHIFT);
  mult = pdb_sc_mults[(PDB0->SC & PDB_SC_MULT_MASK) >> PDB_SC_MULT_SHIFT];
  
  PDB0->DAC[n].INTC |= cfg;     //����ʹ���ⲿ���������ڲ��������
  PDB0->DAC[n].INT = (bus_clk * int_delay)/(prescaler * mult);    //����DACn�ļ������ʱ��
  
  PDB0->SC |= PDB_SC_LDOK_MASK; //����ֵ
  
  return 1;
}

/*
 * PDB�жϴ�����
 * �������ļ�startup_K60.s�е��ж����������
 * �û������޸ģ������Զ������Ӧͨ���жϺ���
 */
void PDB_IRQHandler(void)
{
#if (UCOS_II > 0u)
  OS_CPU_SR  cpu_sr = 0u;
  OS_ENTER_CRITICAL(); //��֪ϵͳ��ʱ�Ѿ��������жϷ����Ӻ���
  OSIntEnter();
  OS_EXIT_CRITICAL();
#endif
  
  //�Ƿ�ΪPDB�ж�
  if((PDB0->SC & PDB_SC_PDBIF_MASK) && (PDB0->SC & PDB_SC_PDBIE_MASK))
  {
    //�����û��Զ����жϷ���
    PDB_ISR[0]();  
    //����жϱ�־λ  
    PDB0->SC &= ~PDB_SC_PDBIF_MASK;
  }
  
  //�Ƿ�ΪPDB���д����ж� CH0
  if((PDB0->CH[0].S & PDB_S_ERR(1)) && (PDB0->SC & PDB_SC_PDBEIE_MASK))
  {
    //�����û��Զ����жϷ���
    PDB_SE_ISR[0]();  
    PDB0->CH[0].S |= PDB_S_ERR(1);
  }
  
  //�Ƿ�ΪPDB���д����ж� CH1
  if((PDB0->CH[1].S & PDB_S_ERR(2)) && (PDB0->SC & PDB_SC_PDBEIE_MASK))
  {
    //�����û��Զ����жϷ���
    PDB_SE_ISR[0]();  
    PDB0->CH[1].S |= PDB_S_ERR(2);
  }
  
#if (UCOS_II > 0u)
  OSIntExit();          //��֪ϵͳ��ʱ�����뿪�жϷ����Ӻ���
#endif
}