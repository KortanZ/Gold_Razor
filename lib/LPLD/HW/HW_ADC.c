/**
 * @file HW_ADC.c
 * @version 3.0[By LPLD]
 * @date 2013-06-18
 * @brief ADC�ײ�ģ����غ���
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
#include "HW_ADC.h"

//�û��Զ����жϷ���������
#if defined(CPU_MK60DZ10) || defined(CPU_MK60D10) 
ADC_ISR_CALLBACK ADC_ISR[2];
#elif defined(CPU_MK60F12) || defined(CPU_MK60F15)
ADC_ISR_CALLBACK ADC_ISR[4];
#endif
static uint8 LPLD_ADC_Cal(ADC_Type *);

/*
 * LPLD_ADC_Init
 * ADCͨ�ó�ʼ��������ѡ��ADCx���ɼ�ģʽ�����ȵȲ���
 * 
 * ����:
 *    adc_init_structure--ADC��ʼ���ṹ�壬
 *                        ���嶨���ADC_InitTypeDef
 *
 * ���:
 *    0--���ô���
 *    1--���óɹ�
 */
uint8 LPLD_ADC_Init(ADC_InitTypeDef adc_init_structure)
{
  uint8 i;
  ADC_Type *adcx = adc_init_structure.ADC_Adcx;
  uint8 diff = adc_init_structure.ADC_DiffMode;
  uint8 mode = adc_init_structure.ADC_BitMode;
  uint8 time = adc_init_structure.ADC_SampleTimeCfg;
  uint8 ltime = adc_init_structure.ADC_LongSampleTimeSel;
  uint8 avg = adc_init_structure.ADC_HwAvgSel;
  uint8 muxab = adc_init_structure.ADC_MuxSel;
  uint8 pga = adc_init_structure.ADC_PgaGain;
  uint8 hwtrg = adc_init_structure.ADC_HwTrgCfg;
  ADC_ISR_CALLBACK isr_func = adc_init_structure.ADC_Isr;
  
  //�������
  ASSERT( (diff==ADC_SE)||(diff==ADC_DIFF) );  //�ж�ģʽѡ��
  ASSERT( mode<=SE_16BIT );       //�жϾ���ѡ��
  ASSERT( (time==SAMTIME_SHORT)||(time==SAMTIME_LONG) );  //�жϲ���ʱ��ѡ��
  ASSERT( ltime<=LSAMTIME_2EX );  //�жϳ�����ʱ��
  ASSERT( (avg&0x3)<=(HW_32AVG&0x3) );  //�ж�Ӳ��ƽ��
  ASSERT( (muxab==MUX_ADXXA)||(muxab==MUX_ADXXB) );  //�ж�ADC����ABѡ��
  ASSERT( (pga&0x7)<=(LSAMTIME_2EX&0x7));  //�ж�PGA
  
  //����ADCʱ��
  if(adcx == ADC0)
  {
    i=0;
    SIM->SCGC6 |= SIM_SCGC6_ADC0_MASK;   // ����ADC0ʱ��
  }
  else if(adcx == ADC1)
  {
    i=1;
    SIM->SCGC3 |= SIM_SCGC3_ADC1_MASK;   // ����ADC1ʱ��
  }
#if defined(CPU_MK60F12) || defined(CPU_MK60F15)
  else if(adcx == ADC2)
  {
    i=2;
    SIM->SCGC6 |= SIM_SCGC6_ADC2_MASK;   // ����ADC1ʱ��
  }
  else if(adcx == ADC3)
  {
    i=3;
    SIM->SCGC3 |= SIM_SCGC3_ADC3_MASK;   // ����ADC1ʱ��
  }
#endif
  else 
  {
    return 0;
  }

  if(adc_init_structure.ADC_CalEnable == TRUE)
    LPLD_ADC_Cal(adcx);  //����ADCУ׼
  
  //����ADCCFG1�Ĵ���
  adcx->CFG1  =  0& (~ADC_CFG1_ADLPC_MASK)         // ����Ϊ����ʹ�ý�������
                  | ADC_CFG1_ADIV(ADIV_1)          // ADC����ʱ�ӷ�ƵΪ 1
                  | time                           // ���ó���ʱ�����ģʽ
                  | ADC_CFG1_ADICLK(ADICLK_BUS_2)  // ADC����ʱ��ԴΪ BusClk
                  | ADC_CFG1_MODE(mode);           //����ADCת������

  //����ADCCFG2�Ĵ���
  adcx->CFG2 = 0 & (~ADC_CFG2_ADACKEN_MASK)   //�����첽ʱ�����
                 | muxab        // ADC����ѡ��
                 | ADC_CFG2_ADHSC_MASK        // ����ת��
                 | ADC_CFG2_ADLSTS(ltime);    // ������ʱ��ʱ������ѡ��
                                              // �ܲ������ڼ�K60�����ĵ� page:840
  //�����趨��ֵ
  adcx->CV1  = 0x1234u ; 
  adcx->CV2  = 0x5678u ;
  
  adcx->SC2  = 0 | (hwtrg & ADC_SC2_ADTRG_MASK) //���ô�����ʽ
                 & (~ADC_SC2_ACFE_MASK)         //�رձȽϹ���
                 & (~ADC_SC2_DMAEN_MASK)        //�ر�DMA
                 |  ADC_SC2_ACREN_MASK          //ʹ�ܷ�Χ�Ƚ�
                 |  ADC_SC2_ACFGT_MASK          //ʹ�ܴ��ڱȽϹ���
                 |  ADC_SC2_REFSEL(REFSEL_EXT); //ѡ���ⲿ�ο�ԴVREFH��VREFL
  
  if(adc_init_structure.ADC_DmaEnable == TRUE) 
    adcx->SC2  |= ADC_SC2_DMAEN_MASK;   //ʹ��DMA

  adcx->SC3  = 0 & (~ADC_SC3_CAL_MASK)          //�ر�У׼
                 & (~ADC_SC3_ADCO_MASK)         //ѡ��һ��ת��
                 |  avg;        //Ӳ��ƽ��
  
  adcx->PGA  = pga<<ADC_PGA_PGAG_SHIFT; 
  
  //У׼��Ϻ������³�ʼ��ADC�Ĵ���
  //adcx->SC1[0] = ADC_SC1_ADCH(AD31);    //��λSC1
  adcx->SC1[hwtrg & 0x01] = diff;         //���õ��ˡ��������
  
  if(isr_func!= NULL)
  {
    ADC_ISR[i] = isr_func;
  }
  
  return 1;
}

/*
 * LPLD_ADC_Deinit
 * ADC����ʼ������������ADCģ��
 * 
 * ����:
 *    adc_init_structure--ADC��ʼ���ṹ�壬
 *                        ���嶨���ADC_InitTypeDef
 *
 * ���:
 *    0--���ô���
 *    1--���óɹ�
 */
uint8 LPLD_ADC_Deinit(ADC_InitTypeDef adc_init_structure)
{
  ADC_Type *adcx = adc_init_structure.ADC_Adcx;
  uint8 hwtrg = adc_init_structure.ADC_HwTrgCfg;
  
  adcx->SC1[hwtrg & 0x01] = ADC_SC1_ADCH(AD31);    //��λSC1
  
  //����ADCʱ��
  if(adcx == ADC0)
  {
    SIM->SCGC6 &= ~(SIM_SCGC6_ADC0_MASK);   // �ر�ADC0ʱ��
  }
  else if(adcx == ADC1)
  {
    SIM->SCGC3 &= ~(SIM_SCGC3_ADC1_MASK);   // �ر�ADC1ʱ��
  }
#if defined(CPU_MK60F12) || defined(CPU_MK60F15)
  else if(adcx == ADC2)
  {
    SIM->SCGC3 &= ~(SIM_SCGC6_ADC2_MASK);   // ����ADC1ʱ��
  }
  else if(adcx == ADC3)
  {
    SIM->SCGC3 &= ~(SIM_SCGC3_ADC3_MASK);   // ����ADC1ʱ��
  }
#endif
  else 
  {
    return 0;
  }
  
  return 1;
}

/*
 * LPLD_ADC_Get
 * �������ģʽ��ȡADת�����
 * 
 * ����:
 *    adcx--ADCxģ���
 *      |__ADC0          --ADC0
 *      |__ADC1          --ADC1
 *      <ע:ֻ��MK60Fϵ�к���ADC2,ADC3>
 *      |__ADC2          --ADC2
 *      |__ADC3          --ADC3
 *    chn--ADC�ɼ�����ͨ��,��������ֲ�K60P144M100SF2RM��118ҳ
 *      ADC0
 *      |__DAD0          --���(ADC0_DP0��ADC0_DM0)/����(ADC0_DP0)
 *      |__DAD1          --���(ADC0_DP1��ADC0_DM1)/����(ADC0_DP1)
 *      |__DAD2          --���(PGA0_DP��PGA0_DM)/����(PGA0_DP)
 *      |__DAD3          --���(ADC0_DP3��ADC0_DM3)/����(ADC0_DP3)
 *      |__AD4           --����A(����)/����B(ADC0_SE4b--PTC2)
 *      |__AD5           --����A(����)/����B(ADC0_SE5b--PTD1)
 *      |__AD6           --����A(����)/����B(ADC0_SE6b--PTD5)
 *      |__AD7           --����A(����)/����B(ADC0_SE7b--PTD6)
 *      |__AD8           --����(ADC0_SE8--PTB0)
 *      |__AD9           --����(ADC0_SE9--PTB1)
 *      |__AD10          --����(ADC0_SE10--PTA7)
 *      |__AD11          --����(ADC0_SE11--PTA8)
 *      |__AD12          --����(ADC0_SE12--PTB2)
 *      |__AD13          --����(ADC0_SE13--PTB3)
 *      |__AD14          --����(ADC0_SE14--PTC0)
 *      |__AD15          --����(ADC0_SE15--PTC1)
 *      |__AD16          --����(ADC0_SE16)
 *      |__AD17          --����(ADC0_SE17-PTE24)
 *      |__AD18          --����(ADC0_SE18--PTE25)
 *      |__AD19          --����(ADC0_DM0)
 *      |__AD20          --����(ADC0_DM1)
 *      |__AD23          --����(DAC0)
 *      |__AD26          --�¶ȴ�����
 *      |__AD27          --Bandgap
 *      |__AD29          --���(-VREFH)/����(VREFH)
 *      |__AD30          --����(VREFL)
 *      ADC1
 *      |__DAD0          --���(ADC1_DP0��ADC1_DM0)/����(ADC1_DP0)
 *      |__DAD1          --���(ADC1_DP1��ADC1_DM1)/����(ADC1_DP1)
 *      |__DAD2          --���(PGA1_DP��PGA1_DM)/����(PGA1_DP)
 *      |__DAD3          --���(ADC1_DP3��ADC1_DM3)/����(ADC1_DP3)
 *      |__AD4           --����A(ADC1_SE4a--PTE0)/����B(ADC1_SE4b--PTC8)
 *      |__AD5           --����A(ADC1_SE5a--PTE1)/����B(ADC1_SE5b--PTC9)
 *      |__AD6           --����A(ADC1_SE6a--PTE2)/����B(ADC1_SE6b--PTC10)
 *      |__AD7           --����A(ADC1_SE7a--PTE3)/����B(ADC1_SE7b--PTC11)
 *      |__AD8           --����(ADC1_SE8--PTB0)
 *      |__AD9           --����(ADC1_SE9--PTB1)
 *      |__AD10          --����(ADC1_SE10--PTB4)
 *      |__AD11          --����(ADC1_SE11--PTB5)
 *      |__AD12          --����(ADC1_SE12--PTB6)
 *      |__AD13          --����(ADC1_SE13--PTB7)
 *      |__AD14          --����(ADC1_SE14--PTB10)
 *      |__AD15          --����(ADC1_SE15--PTB11)
 *      |__AD16          --����(ADC1_SE16)
 *      |__AD17          --����(ADC1_SE17--PTA17)
 *      |__AD18          --����(VREF)
 *      |__AD19          --����(ADC1_DM0)
 *      |__AD20          --����(ADC1_DM1)
 *      |__AD23          --����(DAC1)
 *      |__AD26          --�¶ȴ�����
 *      |__AD27          --Bandgap
 *      |__AD29          --���(-VREFH)/����(VREFH)
 *      |__AD30          --����(VREFL)
 *      <ע:ֻ��MK60Fϵ�к���ADC2,ADC3>
 *          ��������ֲ�K60P144M120SF2RM��131ҳ
 *      ADC2      
 *      |__DAD0          --���(ADC2_DP0��ADC2_DM0)/����(ADC2_DP0)
 *      |__DAD1          --���(ADC2_DP1��ADC2_DM1)/����(ADC2_DP1)
 *      |__DAD2          --���(PGA2_DP��PGA2_DM)/����(PGA2_DP)
 *      |__DAD3          --���(ADC2_DP3��ADC2_DM3)/����(ADC2_DP3)
 *      |__AD4           --����A(ADC2_SE4a--PTB20)/����B(����)
 *      |__AD5           --����A(ADC2_SE5a--PTB21)/����B(����)
 *      |__AD6           --����A(����)/����B(����)
 *      |__AD7           --����A(����)/����B(����)
 *      |__AD8           --����(ADC2_SE8--PTB0)
 *      |__AD9           --����(ADC2_SE9--PTB1)
 *      |__AD10          --����(ADC2_SE10)
 *      |__AD11          --����(ADC2_SE11)
 *      |__AD12          --����(ADC2_SE12--PTA29)
 *      |__AD13          --����(ADC2_SE13--PTA28)
 *      |__AD14          --����(ADC2_SE14--PTA27)
 *      |__AD15          --����(ADC2_SE15--PTA26)
 *      |__AD16          --����(ADC2_SE16--PTE8)
 *      |__AD17          --����(ADC2_SE17--PTE9)
 *      |__AD18          --����(ADC2_SE18)
 *      |__AD19          --����(ADC2_DM0)
 *      |__AD20          --����(ADC2_DM1)
 *      |__AD23          --����(DAC2)
 *      |__AD26          --�¶ȴ�����
 *      |__AD27          --Bandgap
 *      |__AD29          --���(-VREFH)/����(VREFH)
 *      |__AD30          --����(VREFL)
 *      ADC3
 *      |__DAD0          --���(ADC3_DP0��ADC3_DM0)/����(ADC3_DP0)
 *      |__DAD1          --���(ADC3_DP1��ADC3_DM1)/����(ADC3_DP1)
 *      |__DAD2          --���(PGA3_DP��PGA3_DM)/����(PGA3_DP)
 *      |__DAD3          --���(ADC3_DP3��ADC3_DM3)/����(ADC3_DP3)
 *      |__AD4           --����A(ADC3_SE4a--PTA10)/����B(ADC3_SE4b--PTE27)
 *      |__AD5           --����A(ADC3_SE5a--PTA9)/����B(ADC3_SE5b--PTE26)
 *      |__AD6           --����A(ADC3_SE6a--PTA6)/����B(����)
 *      |__AD7           --����A(ADC3_SE7a--PTE28)/����B(����)
 *      |__AD8           --����(ADC3_SE8--PTB0)
 *      |__AD9           --����(ADC3_SE9--PTB1)
 *      |__AD10          --����(ADC3_SE10)
 *      |__AD11          --����(ADC3_SE11)
 *      |__AD12          --����(ADC3_SE12)
 *      |__AD13          --����(ADC3_SE13)
 *      |__AD14          --����(ADC3_SE14)
 *      |__AD15          --����(ADC3_SE15--PTA11)
 *      |__AD16          --����(ADC3_SE16--PTE11)
 *      |__AD17          --����(ADC3_SE17--PTE12)
 *      |__AD18          --����(VREF)
 *      |__AD19          --����(ADC3_DM0)
 *      |__AD20          --����(ADC3_DM1)
 *      |__AD23          --����(DAC3)
 *      |__AD26          --�¶ȴ�����
 *      |__AD27          --Bandgap
 *      |__AD29          --���(-VREFH)/����(VREFH)
 *      |__AD30          --����(VREFL)
 * ���:
 *    ADͨ��ת��ֵ(�Ҷ���)����Ϊ���ת���������Ϊ�����Ʋ����ʽ(��ǿ��ת��Ϊint16)
 *
 */
uint16 LPLD_ADC_Get(ADC_Type *adcx, AdcChnEnum_Type chn)
{
  adcx->SC1[0] &= ~(ADC_SC1_AIEN_MASK);
  adcx->SC1[0] &= ~(ADC_SC1_ADCH_MASK);
  adcx->SC1[0] |= ADC_SC1_ADCH(chn);
  while((adcx->SC1[0]&ADC_SC1_COCO_MASK) == 0); //�ȴ�ת�����  
  return adcx->R[0];
}

/*
 * LPLD_ADC_EnableConversion
 * ʹ��ADCxת��ͨ������������жϡ�Ӳ��������ģʽ
 * 
 * ����:
 *    adcx--ADCxģ���
 *      |__ADC0          --ADC0
 *      |__ADC1          --ADC1
 *      <ע:ֻ��MK60Fϵ�к���ADC2,ADC3>
 *      |__ADC2          --ADC2
 *      |__ADC3          --ADC3
 *    chn--ADC�ɼ�����ͨ��,��������ֲ�K60P144M100SF2RM��118ҳ
 *      ȡֵͬLPLD_ADC_Get�β�chn
 *      <ע:ֻ��MK60Fϵ�к���ADC2,ADC3>
 *          MK60F��������ֲ�K60P144M120SF2RM��131ҳ
 *    ab--SC1�Ĵ���A��Bͨ��ѡ��
 *      |__0          --Aת��ͨ��
 *      |__1          --Bת��ͨ��
 *    irq--�Ƿ�ʹ��ת������ж�
 *      |__TRUE       --ʹ��ת������ж�
 *      |__FALSE      --����ת������ж�
 *
 * ���:
 *    ��
 *
 */
void LPLD_ADC_EnableConversion(ADC_Type *adcx, AdcChnEnum_Type chn, uint8 ab, boolean irq)
{
  //�������
  ASSERT( ab<=1 );  //�ж�AB���ƼĴ���
  ASSERT( irq<=1 );  //�ж��Ƿ�ʹ���ж�
  if(irq == TRUE)
  {
    adcx->SC1[ab] |= (ADC_SC1_AIEN_MASK);
  }
  adcx->SC1[ab] &= ~(ADC_SC1_ADCH_MASK);
  adcx->SC1[ab] |= ADC_SC1_ADCH(chn);
}

/*
 * LPLD_ADC_GetResult
 * ��ȡADת�����
 * 
 * ����:
 *    adcx--ADCxģ���
 *      |__ADC0          --ADC0
 *      |__ADC1          --ADC1
 *      <ע:ֻ��MK60Fϵ�к���ADC2,ADC3>
 *      |__ADC2          --ADC2
 *      |__ADC3          --ADC3
 *    ab--SC1�Ĵ���A��Bͨ��ѡ��
 *      |__0          --Aת��ͨ��
 *      |__1          --Bת��ͨ��
 *
 * ���:
 *    ADͨ��ת��ֵ(�Ҷ���)����Ϊ���ת���������Ϊ�����Ʋ����ʽ(��ǿ��ת��Ϊint16)
 *
 */
uint16 LPLD_ADC_GetResult(ADC_Type *adcx, uint8 ab)
{
  //�������
  ASSERT( ab<=1 );  //�ж�AB���ƼĴ���
  return adcx->R[ab];
}

/*
 * LPLD_ADC_GetSC1nCOCO
 * ��ȡSC1�Ĵ�����COCOλ��1�ı��
 * 
 * ����:
 *    adcx--ADCxģ���
 *      |__ADC0          --ADC0
 *      |__ADC1          --ADC1
 *      <ע:ֻ��MK60Fϵ�к���ADC2,ADC3>
 *      |__ADC2          --ADC2
 *      |__ADC3          --ADC3
 *
 * ���:
*    0--SC1A�Ĵ���COCOλ��1
*    1--SC1B�Ĵ���COCOλ��1
 *
 */
uint8 LPLD_ADC_GetSC1nCOCO(ADC_Type *adcx)
{
  if(adcx->SC1[0] & ADC_SC1_COCO_MASK)
    return 0;
  if(adcx->SC1[1] & ADC_SC1_COCO_MASK)
    return 1;
  return -1;
}

/*
 * LPLD_ADC_EnableIrq
 * ʹ��ADCx�ж�
 * 
 * ����:
 *    adc_init_structure--PIT��ʼ���ṹ�壬
 *                        ���嶨���ADC_InitTypeDef
 *
 * ���:
 *    0--���ô���
 *    1--���óɹ�
 *
 */
uint8 LPLD_ADC_EnableIrq(ADC_InitTypeDef adc_init_structure)
{
  uint8 i;
  ADC_Type *adcx = adc_init_structure.ADC_Adcx;
  
  if(adcx == ADC0)
    i=0;
  else if(adcx == ADC1)
    i=1;
#if defined(CPU_MK60F12) || defined(CPU_MK60F15)
  else if(adcx == ADC2)
    i=2;
  else if(adcx == ADC3)
    i=3;
#endif
  else
    return 0;

  enable_irq((IRQn_Type)(ADC0_IRQn + i));
  
  return 1;
}

/*
 * LPLD_ADC_DisableIrq
 * ����ADCx�ж�
 * 
 * ����:
 *    adc_init_structure--PIT��ʼ���ṹ�壬
 *                        ���嶨���ADC_InitTypeDef
 *
 * ���:
 *    0--���ô���
 *    1--���óɹ�
 *
 */
uint8 LPLD_ADC_DisableIrq(ADC_InitTypeDef adc_init_structure)
{
  uint8 i;
  ADC_Type *adcx = adc_init_structure.ADC_Adcx;
  
  if(adcx == ADC0)
    i=0;
  else if(adcx == ADC1)
    i=1;
#if defined(CPU_MK60F12) || defined(CPU_MK60F15)
  else if(adcx == ADC2)
    i=2;
  else if(adcx == ADC3)
    i=3;
#endif
  else
    return 0;

  disable_irq((IRQn_Type)(ADC0_IRQn + i));
  
  return 1;
}

/*
 * LPLD_ADC_Chn_Enable
 * ʹ��ADCx��Ӧת��ͨ����AD�ɼ�����
 * 
 * ����:
 *    adcx--ADCxģ���
 *      |__ADC0          --ADC0
 *      |__ADC1          --ADC1
 *      <ע:ֻ��MK60Fϵ�к���ADC2,ADC3>
 *      |__ADC2          --ADC2
 *      |__ADC3          --ADC3
 *    chn--ADC�ɼ�����ͨ��,��������ֲ�K60P144M100SF2RM��118ҳ
 *      ADC0
 *      |__DAD0          --���(ADC0_DP0��ADC0_DM0)/����(ADC0_DP0)
 *      |__DAD1          --���(ADC0_DP1��ADC0_DM1)/����(ADC0_DP1)
 *      |__DAD2          --���(PGA0_DP��PGA0_DM)/����(PGA0_DP)
 *      |__DAD3          --���(ADC0_DP3��ADC0_DM3)/����(ADC0_DP3)
 *      |__AD4           --����A(����)/����B(ADC0_SE4b--PTC2)
 *      |__AD5           --����A(����)/����B(ADC0_SE5b--PTD1)
 *      |__AD6           --����A(����)/����B(ADC0_SE6b--PTD5)
 *      |__AD7           --����A(����)/����B(ADC0_SE7b--PTD6)
 *      |__AD8           --����(ADC0_SE8--PTB0)
 *      |__AD9           --����(ADC0_SE9--PTB1)
 *      |__AD10          --����(ADC0_SE10--PTA7)
 *      |__AD11          --����(ADC0_SE11--PTA8)
 *      |__AD12          --����(ADC0_SE12--PTB2)
 *      |__AD13          --����(ADC0_SE13--PTB3)
 *      |__AD14          --����(ADC0_SE14--PTC0)
 *      |__AD15          --����(ADC0_SE15--PTC1)
 *      |__AD16          --����(ADC0_SE16)
 *      |__AD17          --����(ADC0_SE17-PTE24)
 *      |__AD18          --����(ADC0_SE18--PTE25)
 *      |__AD19          --����(ADC0_DM0)
 *      |__AD20          --����(ADC0_DM1)
 *      |__AD23          --����(DAC0)
 *      |__AD26          --�¶ȴ�����
 *      |__AD27          --Bandgap
 *      |__AD29          --���(-VREFH)/����(VREFH)
 *      |__AD30          --����(VREFL)
 *      ADC1
 *      |__DAD0          --���(ADC1_DP0��ADC1_DM0)/����(ADC1_DP0)
 *      |__DAD1          --���(ADC1_DP1��ADC1_DM1)/����(ADC1_DP1)
 *      |__DAD2          --���(PGA1_DP��PGA1_DM)/����(PGA1_DP)
 *      |__DAD3          --���(ADC1_DP3��ADC1_DM3)/����(ADC1_DP3)
 *      |__AD4           --����A(ADC1_SE4a--PTE0)/����B(ADC1_SE4b--PTC8)
 *      |__AD5           --����A(ADC1_SE5a--PTE1)/����B(ADC1_SE5b--PTC9)
 *      |__AD6           --����A(ADC1_SE6a--PTE2)/����B(ADC1_SE6b--PTC10)
 *      |__AD7           --����A(ADC1_SE7a--PTE3)/����B(ADC1_SE7b--PTC11)
 *      |__AD8           --����(ADC1_SE8--PTB0)
 *      |__AD9           --����(ADC1_SE9--PTB1)
 *      |__AD10          --����(ADC1_SE10--PTB4)
 *      |__AD11          --����(ADC1_SE11--PTB5)
 *      |__AD12          --����(ADC1_SE12--PTB6)
 *      |__AD13          --����(ADC1_SE13--PTB7)
 *      |__AD14          --����(ADC1_SE14--PTB10)
 *      |__AD15          --����(ADC1_SE15--PTB11)
 *      |__AD16          --����(ADC1_SE16)
 *      |__AD17          --����(ADC1_SE17--PTA17)
 *      |__AD18          --����(VREF)
 *      |__AD19          --����(ADC1_DM0)
 *      |__AD20          --����(ADC1_DM1)
 *      |__AD23          --����(DAC1)
 *      |__AD26          --�¶ȴ�����
 *      |__AD27          --Bandgap
 *      |__AD29          --���(-VREFH)/����(VREFH)
 *      |__AD30          --����(VREFL)
 *      <ע:ֻ��MK60Fϵ�к���ADC2,ADC3>
 *          ��������ֲ�K60P144M120SF2RM��131ҳ
 *      ADC2      
 *      |__DAD0          --���(ADC2_DP0��ADC2_DM0)/����(ADC2_DP0)
 *      |__DAD1          --���(ADC2_DP1��ADC2_DM1)/����(ADC2_DP1)
 *      |__DAD2          --���(PGA2_DP��PGA2_DM)/����(PGA2_DP)
 *      |__DAD3          --���(ADC2_DP3��ADC2_DM3)/����(ADC2_DP3)
 *      |__AD4           --����A(ADC2_SE4a--PTB20)/����B(����)
 *      |__AD5           --����A(ADC2_SE5a--PTB21)/����B(����)
 *      |__AD6           --����A(����)/����B(����)
 *      |__AD7           --����A(����)/����B(����)
 *      |__AD8           --����(ADC2_SE8--PTB0)
 *      |__AD9           --����(ADC2_SE9--PTB1)
 *      |__AD10          --����(ADC2_SE10)
 *      |__AD11          --����(ADC2_SE11)
 *      |__AD12          --����(ADC2_SE12--PTA29)
 *      |__AD13          --����(ADC2_SE13--PTA28)
 *      |__AD14          --����(ADC2_SE14--PTA27)
 *      |__AD15          --����(ADC2_SE15--PTA26)
 *      |__AD16          --����(ADC2_SE16--PTE8)
 *      |__AD17          --����(ADC2_SE17--PTE9)
 *      |__AD18          --����(ADC2_SE18)
 *      |__AD19          --����(ADC2_DM0)
 *      |__AD20          --����(ADC2_DM1)
 *      |__AD23          --����(DAC2)
 *      |__AD26          --�¶ȴ�����
 *      |__AD27          --Bandgap
 *      |__AD29          --���(-VREFH)/����(VREFH)
 *      |__AD30          --����(VREFL)
 *      ADC3
 *      |__DAD0          --���(ADC3_DP0��ADC3_DM0)/����(ADC3_DP0)
 *      |__DAD1          --���(ADC3_DP1��ADC3_DM1)/����(ADC3_DP1)
 *      |__DAD2          --���(PGA3_DP��PGA3_DM)/����(PGA3_DP)
 *      |__DAD3          --���(ADC3_DP3��ADC3_DM3)/����(ADC3_DP3)
 *      |__AD4           --����A(ADC3_SE4a--PTA10)/����B(ADC3_SE4b--PTE27)
 *      |__AD5           --����A(ADC3_SE5a--PTA9)/����B(ADC3_SE5b--PTE26)
 *      |__AD6           --����A(ADC3_SE6a--PTA6)/����B(����)
 *      |__AD7           --����A(ADC3_SE7a--PTE28)/����B(����)
 *      |__AD8           --����(ADC3_SE8--PTB0)
 *      |__AD9           --����(ADC3_SE9--PTB1)
 *      |__AD10          --����(ADC3_SE10)
 *      |__AD11          --����(ADC3_SE11)
 *      |__AD12          --����(ADC3_SE12)
 *      |__AD13          --����(ADC3_SE13)
 *      |__AD14          --����(ADC3_SE14)
 *      |__AD15          --����(ADC3_SE15--PTA11)
 *      |__AD16          --����(ADC3_SE16--PTE11)
 *      |__AD17          --����(ADC3_SE17--PTE12)
 *      |__AD18          --����(VREF)
 *      |__AD19          --����(ADC3_DM0)
 *      |__AD20          --����(ADC3_DM1)
 *      |__AD23          --����(DAC3)
 *      |__AD26          --�¶ȴ�����
 *      |__AD27          --Bandgap
 *      |__AD29          --���(-VREFH)/����(VREFH)
 *      |__AD30          --����(VREFL)
 * ���:
 *    0--���ô���
 *    1--���óɹ�
 *
 */
uint8 LPLD_ADC_Chn_Enable(ADC_Type *adcx, AdcChnEnum_Type chn)
{
  //�жϸ���������a��b
  uint8 mux = (adcx->CFG2 & ADC_CFG2_MUXSEL_MASK)>>ADC_CFG2_MUXSEL_SHIFT;
    
  if(chn > AD30)
    return 0;
  
  //��ͬ��ͨ����Ӧ��ͬ�����ţ������Ҫ�жϲ�����
  if(adcx == ADC0)
  {
    switch(chn)
    {
      case DAD0:   //ADC0_DP0 -- PGA0_DP
      case DAD1:   //ADC0_DP1 -- PGA2_DP
      case DAD2:   //PGA0_DP
      case DAD3:   //ADC0_DP3 -- PGA1_DP
        break;
      case AD4:   //ADC0_SE4b -- PTC2     
        if(mux == 1)    //b
          PORTC->PCR[2] =  PORT_PCR_MUX(0);
        break;
      case AD5:   //ADC0_SE5b -- PTD1     
        if(mux == 1)    //b
          PORTD->PCR[1] =  PORT_PCR_MUX(0);
        break;
      case AD6:   //ADC0_SE6b -- PTD5
      case AD7:   //ADC0_SE7b -- PTD6     
        if(mux == 1)    //b
          PORTD->PCR[chn-1] =  PORT_PCR_MUX(0);
        break;
      case AD8:  //ADC0_SE8 -- PTB0
      case AD9:  //ADC0_SE9 -- PTB1
        PORTB->PCR[chn-8] =  PORT_PCR_MUX(0);
        break;
      case AD10:  //ADC0_SE10 -- PTA7
      case AD11:  //ADC0_SE11 -- PTA8
        PORTA->PCR[chn-3] =  PORT_PCR_MUX(0);
        break;
      case AD12:  //ADC0_SE12 -- PTB2
      case AD13:  //ADC0_SE13 -- PTB3
        PORTB->PCR[chn-10] =  PORT_PCR_MUX(0);
        break;
      case AD14:  //ADC0_SE14 -- PTC0
      case AD15:  //ADC0_SE15 -- PTC1
        PORTC->PCR[chn-14] =  PORT_PCR_MUX(0);
        break;
      case AD16:   //ADC0_SE16
        break;
      case AD17:   //ADC0_SE17 -- PTE24
      case AD18:   //ADC0_SE18 -- PTE25
        PORTE->PCR[chn+7] =  PORT_PCR_MUX(0);
        break;
      case AD19:   //ADC0_DM0 -- PGA0_DM
      case AD20:   //ADC0_DM1 -- PGA2_DM
      case AD23:   //ADC0_SE23 -- DAC0_OUT
      case AD26:   //Temperature Sensor (S.E)
      case AD27:   //Bandgap (S.E)
      case AD29:   //VREFH (S.E)
      case AD30:   //VREFL
        break;
      default:
        return 0;  
    }
  }
  else if(adcx == ADC1)
  {
    switch(chn)
    {
      case DAD0:   //ADC1_DP0 -- PGA1_DP
      case DAD1:   //ADC1_DP1 -- PGA3_DP
      case DAD2:   //PGA1_DP 
      case DAD3:   //ADC1_DP3 -- PGA0_DP
        break;
      case AD4:   //ADC1_SE4a -- PTE0     //ADC1_SE4b -- PTC8
      case AD5:   //ADC1_SE5a -- PTE1     //ADC1_SE5b -- PTC9
      case AD6:   //ADC1_SE6a -- PTE2     //ADC1_SE6b -- PTC10
      case AD7:   //ADC1_SE7a -- PTE3     //ADC1_SE7b -- PTC11
        if(mux == 0)    //a
          PORTE->PCR[chn-4] =  PORT_PCR_MUX(0);
        else            //b
          PORTC->PCR[chn+4] =  PORT_PCR_MUX(0);
        break;
      case AD8:  //ADC1_SE8 -- PTB0
      case AD9:  //ADC1_SE9 -- PTB1
        PORTB->PCR[chn-8] =  PORT_PCR_MUX(0);
        break;
      case AD10:  //ADC1_SE10 -- PTB4
      case AD11:  //ADC1_SE11 -- PTB5
      case AD12:  //ADC1_SE12 -- PTB6
      case AD13:  //ADC1_SE13 -- PTB7
        PORTB->PCR[chn-6] =  PORT_PCR_MUX(0);
        break;
      case AD14:  //ADC1_SE14 -- PTB10
      case AD15:  //ADC1_SE15 -- PTB11
        PORTB->PCR[chn-4] =  PORT_PCR_MUX(0);
        break;
      case AD16:   //ADC1_SE16
        break;
      case AD17:  //ADC1_SE17 -- PTA17
        PORTA->PCR[chn] =  PORT_PCR_MUX(0);
        break;
      case AD18:   //VREF Output
      case AD19:   //ADC1_DM0 -- PGA1_DM
      case AD20:   //ADC1_DM1 -- PGA3_DM
      case AD23:   //DAC1_OUT 
      case AD26:   //Temperature Sensor (S.E)
      case AD27:   //Bandgap (S.E)
      case AD29:   //VREFH (S.E)
      case AD30:   //VREFL
        break;
      default:
        return 0;  
    }
  }
#if defined(CPU_MK60F12) || defined(CPU_MK60F15)
  else if(adcx == ADC2)
  {
    switch(chn)
    {
      case DAD0:   //ADC2_DP0 -- PGA1_DP
      case DAD1:   //ADC2_DP1 -- PGA3_DP
      case DAD2:   //PGA2_DP 
      case DAD3:   //ADC2_DP3 -- PGA0_DP
        break;
      case AD4:   //ADC2_SE4a -- PTB20     
      case AD5:   //ADC2_SE5a -- PTB21
        if(mux == 0)    //a
          PORTB->PCR[chn+16] =  PORT_PCR_MUX(0);
        //else            //b
          //PORTC->PCR[chn+4] =  PORT_PCR_MUX(0);
        break;
      case AD6:  //ADC1_SE6      
      case AD7:  //ADC1_SE7
        break;        
      case AD8:  //ADC2_SE8 -- PTB0
      case AD9:  //ADC2_SE9 -- PTB1
        PORTB->PCR[chn-8] =  PORT_PCR_MUX(0);
        break;
      case AD10:  //ADC1_SE10
      case AD11:  //ADC1_SE11
        break;
      case AD12:  //ADC2_SE12 -- PTA29
      case AD13:  //ADC2_SE13 -- PTA28
      case AD14:  //ADC2_SE14 -- PTA27
      case AD15:  //ADC2_SE15 -- PTA26
        PORTA->PCR[41-chn] =  PORT_PCR_MUX(0);
        break;
      case AD16:   //ADC2_SE16 -- PTE8
      case AD17:   //ADC2_SE17 -- PTE9
        PORTE->PCR[chn-8] =  PORT_PCR_MUX(0);
        break;
      case AD18:   //VREF Output
      case AD19:   //ADC1_DM0 -- PGA1_DM
      case AD20:   //ADC1_DM1 -- PGA3_DM
      case AD23:   //DAC1_OUT 
      case AD26:   //Temperature Sensor (S.E)
      case AD27:   //Bandgap (S.E)
      case AD29:   //VREFH (S.E)
      case AD30:   //VREFL
        break;
      default:
        return 0;  
    }
  }
  else if(adcx == ADC3)
  {
    switch(chn)
    {
      case DAD0:   //ADC3_DP0 -- PGA1_DP
      case DAD1:   //ADC3_DP1 -- PGA3_DP
      case DAD2:   //PGA3_DP 
      case DAD3:   //ADC3_DP3 -- PGA0_DP
        break;
      case AD4:   //ADC3_SE4a -- PTA10  //ADC3_SE4b -- PTE27   
      case AD5:   //ADC3_SE5a -- PTA9   //ADC3_SE5b -- PTE26
        if(mux == 0)    //a
          PORTA->PCR[14 - chn] =  PORT_PCR_MUX(0);
        else            //b
          PORTE->PCR[31 - chn] =  PORT_PCR_MUX(0);
        break;
      case AD6:   //ADC3_SE6a--PTA6
        PORTA->PCR[6] =  PORT_PCR_MUX(0);
        break;     
      case AD7:   //ADC3_SE7a--PTE28
        PORTE->PCR[28] =  PORT_PCR_MUX(0);
        break;       
      case AD8:  //ADC3_SE8 -- PTB0
      case AD9:  //ADC3_SE9 -- PTB1
        PORTB->PCR[chn-8] =  PORT_PCR_MUX(0);
        break;
      case AD10:  //ADC3_SE10
      case AD11:  //ADC3_SE11
      case AD12:  //ADC3_SE12 
      case AD13:  //ADC3_SE13 
      case AD14:  //ADC3_SE14 
        break;
      case AD15:  //ADC3_SE15 -- PTA11
        PORTA->PCR[11] =  PORT_PCR_MUX(0);
        break;
      case AD16:   //ADC3_SE16 -- PTE11
      case AD17:   //ADC3_SE17 -- PTE12
        PORTE->PCR[chn-5] =  PORT_PCR_MUX(0);
        break;
      case AD18:   //VREF Output
      case AD19:   //ADC1_DM0 -- PGA1_DM
      case AD20:   //ADC1_DM1 -- PGA3_DM
      case AD23:   //DAC1_OUT 
      case AD26:   //Temperature Sensor (S.E)
      case AD27:   //Bandgap (S.E)
      case AD29:   //VREFH (S.E)
      case AD30:   //VREFL
        break;
      default:
        return 0;  
    }
  }
#endif
  else
  {
    return 0;
  }
  
  return 1;
}

/*
 * ADC_Cal
 * ADCģ��У׼�������ڲ�����
 * 
 * ����:
 *    adcx--ADCģ���
 *      |__ADC0         -ADC0ģ��
 *      |__ADC1         -ADC1ģ��
 *      <ע:ֻ��MK60Fϵ�к���ADC2,ADC3>
 *      |__ADC2         -ADC0ģ��
 *      |__ADC3         -ADC1ģ��
 * ���:
 *    0--���ô���
 *    1--���óɹ�
 */
static uint8 LPLD_ADC_Cal(ADC_Type *adcx)
{
  uint16 cal_var;
    
  //Ϊ�Զ�У׼���ò���
  //Ϊ���У׼���ȣ�������Ϊ��
  //32��Ӳ��ƽ����ADCK������4MHz
  //�ο���=Vdda����������ģʽ
  //�ɺ��Ե����ã�
  //����ͨ����ת��ģʽ�������ܡ��ȽϹ��ܡ����ȡ���ֵ���
  //����ADCCFG1�Ĵ���
  adcx->CFG1  = 0 &(~ADC_CFG1_ADLPC_MASK)          // ������������
                  | ADC_CFG1_ADIV(ADIV_8)          // ADC����ʱ�ӷ�ƵΪ8
                  | ADC_CFG1_ADLSMP_MASK           // ���ó�ʱ�����ģʽ
                  | ADC_CFG1_ADICLK(ADICLK_BUS_2); // ADC����ʱ��ԴΪ BusClk/2

  //����ADCCFG2�Ĵ���
  adcx->CFG2 = 0 & (~ADC_CFG2_ADACKEN_MASK)
                 | ADC_CFG2_ADHSC_MASK         // ����ת��
                 | ADC_CFG2_ADLSTS(LSAMTIME_20EX); // ������ʱ��ʱ������ѡ�� ����20��ʱ�����ڣ���24��ADCK����
                                               // �ܲ������ڼ�K60�����ĵ� page:840
  //�����趨��ֵ
  adcx->CV1  = 0x1234u ; 
  adcx->CV2  = 0x5678u ;
  
  adcx->SC2 = 0 & (~ADC_SC2_ADTRG_MASK)        //ʹ�����������ΪУ׼
                | ADC_SC2_REFSEL(REFSEL_EXT);  //ѡ���ⲿ�ο�ԴVREFH��VREFL
    
  adcx->SC3 &= ( ~ADC_SC3_ADCO_MASK & ~ADC_SC3_AVGS_MASK );  //���õ���ת�������ƽ����־
  adcx->SC3 |= ( ADC_SC3_AVGE_MASK | ADC_SC3_AVGS(HW_32AVG) );//��ƽ����־�����õ�������ƽ׼
  
  adcx->SC3 |= ADC_SC3_CAL_MASK ;                            //��ʼУ׼
  
  while((adcx->SC1[0] & ADC_SC1_COCO_MASK)== 0x00 );         //�ȴ�У׼���
  	
  if ((adcx->SC3& ADC_SC3_CALF_MASK) == ADC_SC3_CALF_MASK )
  {  
   return 0;    //��鵽У׼���󣬷��ش���
  }
  // Calculate plus-side calibration
  cal_var  = 0x00;
  cal_var  = adcx->CLP0;       
  cal_var += adcx->CLP1;      
  cal_var += adcx->CLP2;      
  cal_var += adcx->CLP3;      
  cal_var += adcx->CLP4;      
  cal_var += adcx->CLPS;      
  cal_var  = cal_var/2;
  cal_var |= 0x8000; // Set MSB
  
  adcx->PG = ADC_PG_PG(cal_var);

  // Calculate minus-side calibration
  cal_var = 0x00;
  cal_var =  adcx->CLM0; 
  cal_var += adcx->CLM1;
  cal_var += adcx->CLM2;
  cal_var += adcx->CLM3;
  cal_var += adcx->CLM4;
  cal_var += adcx->CLMS;
  cal_var = cal_var/2;
  cal_var |= 0x8000; // Set MSB

  adcx->MG   = ADC_MG_MG(cal_var); 
  adcx->SC3 &= ~ADC_SC3_CAL_MASK ; //���У���־
  
  return 1;
}

/*
 * ADC0--ADC1�жϴ�����
 * �������ļ�startup_K60.s�е��ж����������
 * �û������޸ģ������Զ������Ӧͨ���жϺ���
 */

void ADC0_IRQHandler(void)
{
#if (UCOS_II > 0u)
  OS_CPU_SR  cpu_sr = 0u;
  OS_ENTER_CRITICAL(); //��֪ϵͳ��ʱ�Ѿ��������жϷ����Ӻ���
  OSIntEnter();
  OS_EXIT_CRITICAL();
#endif
  
  //�����û��Զ����жϷ���
  ADC_ISR[0]();  
  
#if (UCOS_II > 0u)
  OSIntExit();          //��֪ϵͳ��ʱ�����뿪�жϷ����Ӻ���
#endif
}

void ADC1_IRQHandler(void)
{
#if (UCOS_II > 0u)
  OS_CPU_SR  cpu_sr = 0u;
  OS_ENTER_CRITICAL(); //��֪ϵͳ��ʱ�Ѿ��������жϷ����Ӻ���
  OSIntEnter();
  OS_EXIT_CRITICAL();
#endif
  
  //�����û��Զ����жϷ���
  ADC_ISR[1]();  
  
#if (UCOS_II > 0u)
  OSIntExit();          //��֪ϵͳ��ʱ�����뿪�жϷ����Ӻ���
#endif
}

#if defined(CPU_MK60F12) || defined(CPU_MK60F15)
void ADC2_IRQHandler(void)
{
#if (UCOS_II > 0u)
  OS_CPU_SR  cpu_sr = 0u;
  OS_ENTER_CRITICAL(); //��֪ϵͳ��ʱ�Ѿ��������жϷ����Ӻ���
  OSIntEnter();
  OS_EXIT_CRITICAL();
#endif
  
  //�����û��Զ����жϷ���
  ADC_ISR[2]();  
  
#if (UCOS_II > 0u)
  OSIntExit();          //��֪ϵͳ��ʱ�����뿪�жϷ����Ӻ���
#endif
}

void ADC3_IRQHandler(void)
{
#if (UCOS_II > 0u)
  OS_CPU_SR  cpu_sr = 0u;
  OS_ENTER_CRITICAL(); //��֪ϵͳ��ʱ�Ѿ��������жϷ����Ӻ���
  OSIntEnter();
  OS_EXIT_CRITICAL();
#endif
  
  //�����û��Զ����жϷ���
  ADC_ISR[2]();  
  
#if (UCOS_II > 0u)
  OSIntExit();          //��֪ϵͳ��ʱ�����뿪�жϷ����Ӻ���
#endif
}
#endif

