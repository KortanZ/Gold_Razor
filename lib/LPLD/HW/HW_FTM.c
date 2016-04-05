/**
 * @file HW_FTM.c
 * @version 3.0[By LPLD]
 * @date 2013-06-18
 * @brief FTM�ײ�ģ����غ���
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
#include "HW_FTM.h"

//�û��Զ����жϷ���������
#if defined(CPU_MK60DZ10) || defined(CPU_MK60D10) 
FTM_ISR_CALLBACK FTM_ISR[3];
#elif defined(CPU_MK60F12) || defined(CPU_MK60F15)
FTM_ISR_CALLBACK FTM_ISR[4];
#endif

static uint8 LPLD_FTM_PWM_Init(FTM_InitTypeDef);
static uint8 LPLD_FTM_IC_Init(FTM_InitTypeDef);
static uint8 LPLD_FTM_QD_Init(FTM_InitTypeDef);
static uint8 LPLD_FTM_DEC_Init(FTM_InitTypeDef);
static uint8 LPLD_FTM_PinInit(FTM_Type *, FtmChnEnum_Type, PortPinsEnum_Type);
static uint8 LPLD_FTM_PinDeinit(FTM_Type *, FtmChnEnum_Type);


/*
 * LPLD_FTM_Init
 * FTMģ��ͨ�ó�ʼ�����ɳ�ʼ��ΪPWM�����벶���������롢˫�߲���ģʽ
 *
 * ����:
 *    ftm_init_structure--FTM��ʼ���ṹ�壬
 *                        ���嶨���FTM_InitTypeDef
 *
 * ���:
 *    0--���ô���
 *    1--���óɹ�
 */
uint8 LPLD_FTM_Init(FTM_InitTypeDef ftm_init_structure)
{
  uint8 result, i;
  //�������
  ASSERT( ftm_init_structure.FTM_Mode & 
         (FTM_MODE_PWM|FTM_MODE_IC|FTM_MODE_QD|FTM_MODE_DEC));  //�ж�ģʽѡ��
  
  // ʹ��FTMʱ��ģ��
  if(ftm_init_structure.FTM_Ftmx == FTM0)
  {
    i=0; 
    SIM->SCGC6 |= SIM_SCGC6_FTM0_MASK;
  }
  else if(ftm_init_structure.FTM_Ftmx == FTM1)
  {
    i=1;
    SIM->SCGC6 |= SIM_SCGC6_FTM1_MASK;
  }
  else if(ftm_init_structure.FTM_Ftmx == FTM2)
  {
    i=2;
    SIM->SCGC3 |= SIM_SCGC3_FTM2_MASK;
  }
#if defined(CPU_MK60F12) || defined(CPU_MK60F15)
  else if(ftm_init_structure.FTM_Ftmx == FTM3)
  {
    i=3;
    SIM->SCGC3 |= SIM_SCGC3_FTM3_MASK;
  }
#endif
  else
  {
    return 0;
  }
  
  if(ftm_init_structure.FTM_Mode & FTM_MODE_PWM)
  {
    result = LPLD_FTM_PWM_Init(ftm_init_structure);
  }
  else if(ftm_init_structure.FTM_Mode & FTM_MODE_IC)
  {
    result = LPLD_FTM_IC_Init(ftm_init_structure);
  }
  else if(ftm_init_structure.FTM_Mode & FTM_MODE_QD)
  {
    result = LPLD_FTM_QD_Init(ftm_init_structure);
  }
  else if(ftm_init_structure.FTM_Mode & FTM_MODE_DEC)
  {
    result = LPLD_FTM_DEC_Init(ftm_init_structure);
  }
  
  if(result == 1)
  {    
    //�ж��Ƿ�������ж�
    if(ftm_init_structure.FTM_Isr!=NULL)
    {      
      FTM_ISR[i] = ftm_init_structure.FTM_Isr;
      if(ftm_init_structure.FTM_ToiEnable == TRUE)
      {
        ftm_init_structure.FTM_Ftmx->SC |= FTM_SC_TOIE_MASK;
      }
    }
  }
  
  return result;
}

/*
 * LPLD_FTM_Deinit
 * FTMģ��ͨ�÷���ʼ��
 *
 * ����:
 *    ftm_init_structure--FTM��ʼ���ṹ�壬
 *                        ���嶨���FTM_InitTypeDef
 *
 * ���:
 *    0--���ô���
 *    1--���óɹ�
 */
uint8 LPLD_FTM_Deinit(FTM_InitTypeDef ftm_init_structure)
{
  if(ftm_init_structure.FTM_Ftmx == FTM0)
  {
    SIM->SCGC6 &= ~SIM_SCGC6_FTM0_MASK;
  }
  else if(ftm_init_structure.FTM_Ftmx == FTM1)
  {
    SIM->SCGC6 &= ~SIM_SCGC6_FTM1_MASK;
  }
  else if(ftm_init_structure.FTM_Ftmx == FTM2)
  {
    SIM->SCGC3 &= ~SIM_SCGC3_FTM2_MASK;
  }
#if defined(CPU_MK60F12) || defined(CPU_MK60F15)
  else if(ftm_init_structure.FTM_Ftmx == FTM3)
  {
    SIM->SCGC3 &= ~SIM_SCGC3_FTM3_MASK;
  }
#endif
  else
  {
    return 0;
  }
  
  return LPLD_FTM_DisableIrq(ftm_init_structure);
}

/*
 * LPLD_FTM_PWM_Enable
 * FTMģ��PWMģʽ���ʹ�ܣ��������ͨ����ռ�ձȡ�ָ����Ӧ�����š����뷽ʽ
 * 
 * ����:
 *    ftmx--FTMxģ���
 *      |__FTM0          --FTM0
 *      |__FTM1          --FTM1
 *      |__FTM2          --FTM2
 *      <ע:ֻ��MK60Fϵ�к���FTM3>
 *      |__FTM3          --FTM3
 *    chn--PWM���ͨ��
 *      <ע:ֻ��MK60Fϵ�к���FTM3>
 *      |__FTM_Ch0          --FTMxͨ��0(FTM0\FTM1\FTM2\FTM3)
 *      |__FTM_Ch1          --FTMxͨ��1(FTM0\FTM1\FTM2\FTM3)
 *      |__FTM_Ch2          --FTMxͨ��2(FTM0\FTM3)
 *      |__FTM_Ch3          --FTMxͨ��3(FTM0\FTM3)
 *      |__FTM_Ch4          --FTMxͨ��4(FTM0\FTM3)
 *      |__FTM_Ch5          --FTMxͨ��5(FTM0\FTM3)
 *      |__FTM_Ch6          --FTMxͨ��6(FTM0\FTM3)
 *      |__FTM_Ch7          --FTMxͨ��7(FTM0\FTM3)
 *    duty--PWM���ռ�ձ�
 *      |__0~10000--ռ�ձ�0.00%~100.00%
 *    pin--FTMxͨ����Ӧ������
 *      FTM0
 *       FTM_Ch0-PTA3\PTC1
 *       FTM_Ch1-PTA4\PTC2
 *       FTM_Ch2-PTA5\PTC3
 *       FTM_Ch3-PTA6\PTC4
 *       FTM_Ch4-PTA7\PTD4
 *       FTM_Ch5-PTA0\PTD5
 *       FTM_Ch6-PTA1\PTD6
 *       FTM_Ch7-PTA2\PTD7
 *      FTM1
 *       FTM_Ch0-PTA8\PTA12\PTB0
 *       FTM_Ch1-PTA9\PTA13\PTB1
 *      FTM2
 *       FTM_Ch0-PTA10\PTB18
 *       FTM_Ch1-PTA11\PTB19
 *      <ע:ֻ��MK60Fϵ�к���FTM3>
 *      FTM3
 *       FTM_Ch0-PTE5\PTD0
 *       FTM_Ch1-PTE6\PTD1
 *       FTM_Ch2-PTE7\PTD2
 *       FTM_Ch3-PTE8\PTD3
 *       FTM_Ch4-PTE9\PTC8
 *       FTM_Ch5-PTE10\PTC9
 *       FTM_Ch6-PTE11\PTC10
 *       FTM_Ch7-PTE12\PTC11
 *    align--������뷽ʽ
 *      |__ALIGN_LEFT    --�����
 *      |__ALIGN_RIGHT   --�Ҷ���
 *
 * ���:
 *    0--���ô���
 *    1--���óɹ�
 */
uint8 LPLD_FTM_PWM_Enable(FTM_Type *ftmx, FtmChnEnum_Type chn, uint32 duty, PortPinsEnum_Type pin, uint8 align)
{
  uint32 cv;
  vuint32 mod;
  
  //�������
  ASSERT( duty <= 10000 );                  //�ж�ռ�ձ�
  
  if(!LPLD_FTM_PinInit(ftmx, chn, pin))
    return 0;
  
  //������Ҷ��룬100%-ռ�ձ�
  if(align == ALIGN_RIGHT)
  {
    duty = 10000 - duty;
  }
  
  //ռ�ձ� = (CnV-CNTIN)/(MOD-CNTIN+1)
  mod = ftmx->MOD;
  cv = (duty*(mod-0+1)+0)/10000;
  
  // ����FTMͨ�����ƼĴ��� 
  // ͨ��ģʽ MSB:MSA-1X, ͨ����Եѡ�� ����� ELSB:ELSA-10
  // ͨ��ģʽ MSB:MSA-1X, ͨ����Եѡ�� �Ҷ��� ELSB:ELSA-X1
  ftmx->CONTROLS[chn].CnSC = align;
  // ����FTMͨ��ֵ
  ftmx->CONTROLS[chn].CnV  = cv;
  
  return 1;
}

/*
 * LPLD_FTM_PWM_ChangeDuty
 * ���FTMģ��PWMģʽָ��ͨ�������ռ�ձ�
 *
 * ����:
 *    ftmx--FTMxģ���
 *      |__FTM0          --FTM0
 *      |__FTM1          --FTM1
 *      |__FTM2          --FTM2
 *      <ע:ֻ��MK60Fϵ�к���FTM3>
 *      |__FTM3          --FTM3
 *    chn--PWM���ͨ��
 *      <ע:ֻ��MK60Fϵ�к���FTM3>
 *      |__FTM_Ch0          --FTMxͨ��0(FTM0\FTM1\FTM2\FTM3)
 *      |__FTM_Ch1          --FTMxͨ��1(FTM0\FTM1\FTM2\FTM3)
 *      |__FTM_Ch2          --FTMxͨ��2(FTM0\FTM3)
 *      |__FTM_Ch3          --FTMxͨ��3(FTM0\FTM3)
 *      |__FTM_Ch4          --FTMxͨ��4(FTM0\FTM3)
 *      |__FTM_Ch5          --FTMxͨ��5(FTM0\FTM3)
 *      |__FTM_Ch6          --FTMxͨ��6(FTM0\FTM3)
 *      |__FTM_Ch7          --FTMxͨ��7(FTM0\FTM3)
 *    duty--PWM���ռ�ձ�
 *      |__0~10000--ռ�ձ�0.00%~100.00%
 *
 * ���:
 *    0--���ô���
 *    1--���óɹ�
 */
uint8 LPLD_FTM_PWM_ChangeDuty(FTM_Type *ftmx, FtmChnEnum_Type chn, uint32 duty)
{
  uint32 cv;
  vuint32 mod;
  
  //�������
  ASSERT( duty <= 10000 );                  //�ж�ռ�ձ�
    
  //������Ҷ��룬100%-ռ�ձ�
  if(ftmx->CONTROLS[chn].CnSC & FTM_CnSC_ELSA_MASK)
  {
    duty = 10000 - duty;
  }
  
  //ռ�ձ� = (CnV-CNTIN)/(MOD-CNTIN+1)
  mod = ftmx->MOD;
  cv = (duty*(mod-0+1)+0)/10000;
 
  // ����FTMͨ��ֵ
  ftmx->CONTROLS[chn].CnV = cv;
  
  return 1;
}

/*
 * LPLD_FTM_DisableChn
 * ����FTMģ��ָ��ͨ�������������
 *
 * ����:
 *    ftmx--FTMxģ���
 *      |__FTM0          --FTM0
 *      |__FTM1          --FTM1
 *      |__FTM2          --FTM2
 *      <ע:ֻ��MK60Fϵ�к���FTM3>
 *      |__FTM3          --FTM3
 *    chn--PWM���ͨ��
 *      <ע:ֻ��MK60Fϵ�к���FTM3>
 *      |__FTM_Ch0          --FTMxͨ��0(FTM0\FTM1\FTM2\FTM3)
 *      |__FTM_Ch1          --FTMxͨ��1(FTM0\FTM1\FTM2\FTM3)
 *      |__FTM_Ch2          --FTMxͨ��2(FTM0\FTM3)
 *      |__FTM_Ch3          --FTMxͨ��3(FTM0\FTM3)
 *      |__FTM_Ch4          --FTMxͨ��4(FTM0\FTM3)
 *      |__FTM_Ch5          --FTMxͨ��5(FTM0\FTM3)
 *      |__FTM_Ch6          --FTMxͨ��6(FTM0\FTM3)
 *      |__FTM_Ch7          --FTMxͨ��7(FTM0\FTM3)
 *
 * ���:
 *    0--���ô���
 *    1--���óɹ�
 */
uint8 LPLD_FTM_DisableChn(FTM_Type *ftmx, FtmChnEnum_Type chn)
{
  LPLD_FTM_PinDeinit(ftmx, chn);
  ftmx->CONTROLS[chn].CnSC = 0;
  ftmx->CONTROLS[chn].CnV  = 0;
  
  return 1;
}



/*
 * LPLD_FTM_IC_Enable
 * FTMģ�����벶��ģʽ���ʹ�ܣ���������ͨ����ָ����Ӧ�����š������Ե
 *
 * ����:
 *    ftmx--FTMxģ���
 *      |__FTM0          --FTM0
 *      |__FTM1          --FTM1
 *      |__FTM2          --FTM2
 *      <ע:ֻ��MK60Fϵ�к���FTM3>
 *      |__FTM3          --FTM3
 *    chn--PWM���ͨ��
 *      <ע:ֻ��MK60Fϵ�к���FTM3>
 *      |__FTM_Ch0          --FTMxͨ��0(FTM0\FTM1\FTM2\FTM3)
 *      |__FTM_Ch1          --FTMxͨ��1(FTM0\FTM1\FTM2\FTM3)
 *      |__FTM_Ch2          --FTMxͨ��2(FTM0\FTM3)
 *      |__FTM_Ch3          --FTMxͨ��3(FTM0\FTM3)
 *      |__FTM_Ch4          --FTMxͨ��4(FTM0\FTM3)
 *      |__FTM_Ch5          --FTMxͨ��5(FTM0\FTM3)
 *      |__FTM_Ch6          --FTMxͨ��6(FTM0\FTM3)
 *      |__FTM_Ch7          --FTMxͨ��7(FTM0\FTM3)
 *    duty--PWM���ռ�ձ�
 *      |__0~10000--ռ�ձ�0.00%~100.00%
 *    pin--FTMxͨ����Ӧ������
 *      FTM0
 *       FTM_Ch0-PTA3\PTC1
 *       FTM_Ch1-PTA4\PTC2
 *       FTM_Ch2-PTA5\PTC3
 *       FTM_Ch3-PTA6\PTC4
 *       FTM_Ch4-PTA7\PTD4
 *       FTM_Ch5-PTA0\PTD5
 *       FTM_Ch6-PTA1\PTD6
 *       FTM_Ch7-PTA2\PTD7
 *      FTM1
 *       FTM_Ch0-PTA8\PTA12\PTB0
 *       FTM_Ch1-PTA9\PTA13\PTB1
 *      FTM2
 *       FTM_Ch0-PTA10\PTB18
 *       FTM_Ch1-PTA11\PTB19
 *      <ע:ֻ��MK60Fϵ�к���FTM3>
 *      FTM3
 *       FTM_Ch0-PTE5\PTD0
 *       FTM_Ch1-PTE6\PTD1
 *       FTM_Ch2-PTE7\PTD2
 *       FTM_Ch3-PTE8\PTD3
 *       FTM_Ch4-PTE9\PTC8
 *       FTM_Ch5-PTE10\PTC9
 *       FTM_Ch6-PTE11\PTC10
 *       FTM_Ch7-PTE12\PTC11
 *    capture_edge--�����Ե����
 *      |__CAPTURE_RI    --�����ز���
 *      |__CAPTURE_FA    --�½��ز���
 *      |__CAPTURE_RIFA  --�����½��ز���
 *
 * ���:
 *    0--���ô���
 *    1--���óɹ�
 */
uint8 LPLD_FTM_IC_Enable(FTM_Type *ftmx, FtmChnEnum_Type chn, PortPinsEnum_Type pin, uint8 capture_edge)
{
  if(!LPLD_FTM_PinInit(ftmx, chn, pin))
    return 0;
  
  ftmx->CONTROLS[chn].CnSC = 0x00;
  
  ftmx->CONTROLS[chn].CnSC |= capture_edge;        
  
  ftmx->CONTROLS[chn].CnSC &= (~FTM_CnSC_CHF_MASK);
  ftmx->CONTROLS[chn].CnSC |= FTM_CnSC_CHIE_MASK;         //ʹ��ͨ�����������ж�
  
  ftmx->CONTROLS[chn].CnSC &= (~FTM_CnSC_MSB_MASK);
  ftmx->CONTROLS[chn].CnSC &= (~FTM_CnSC_MSA_MASK);       //���ó�Input captureģʽ
  
  ftmx->CONTROLS[chn].CnSC &= (~FTM_CnSC_DMA_MASK);       //�ر�DMA
  
  return 1;
}

/*
 * LPLD_FTM_IsTOF
 * �ж�FTMx�Ƿ������������жϱ�־
 * 
 * ����:
 *    ftmx--FTMxģ���
 *      |__FTM0          --FTM0
 *      |__FTM1          --FTM1
 *      |__FTM2          --FTM2
 *      <ע:ֻ��MK60Fϵ�к���FTM3>
 *      |__FTM3          --FTM3
 *
 * ���:
 *    TRUE��FALSE
 *
 */
__INLINE boolean LPLD_FTM_IsTOF(FTM_Type *ftmx)
{
  return (boolean)((ftmx->SC & FTM_SC_TOF_MASK)>>FTM_SC_TOF_SHIFT);
}

/*
 * LPLD_FTM_ClearTOF
 * ���FTMx����������жϱ�־
 * 
 * ����:
 *    ftmx--FTMxģ���
 *      |__FTM0          --FTM0
 *      |__FTM1          --FTM1
 *      |__FTM2          --FTM2
 *      <ע:ֻ��MK60Fϵ�к���FTM3>
 *      |__FTM3          --FTM3
 *
 * ���:
 *    ��
 *
 */
__INLINE void LPLD_FTM_ClearTOF(FTM_Type *ftmx)
{
  ftmx->SC = ftmx->SC & ~FTM_SC_TOF_MASK;
}

/*
 * LPLD_FTM_IsCHnF
 * �ж�ͨ��n�Ƿ�����жϱ�־
 * 
 * ����:
 *    ftmx--FTMxģ���
 *      |__FTM0          --FTM0
 *      |__FTM1          --FTM1
 *      |__FTM2          --FTM2
 *      <ע:ֻ��MK60Fϵ�к���FTM3>
 *      |__FTM3          --FTM3
 *    chn--PWM���ͨ��
 *      <ע:ֻ��MK60Fϵ�к���FTM3>
 *      |__FTM_Ch0          --FTMxͨ��0(FTM0\FTM1\FTM2\FTM3)
 *      |__FTM_Ch1          --FTMxͨ��1(FTM0\FTM1\FTM2\FTM3)
 *      |__FTM_Ch2          --FTMxͨ��2(FTM0\FTM3)
 *      |__FTM_Ch3          --FTMxͨ��3(FTM0\FTM3)
 *      |__FTM_Ch4          --FTMxͨ��4(FTM0\FTM3)
 *      |__FTM_Ch5          --FTMxͨ��5(FTM0\FTM3)
 *      |__FTM_Ch6          --FTMxͨ��6(FTM0\FTM3)
 *      |__FTM_Ch7          --FTMxͨ��7(FTM0\FTM3)
 *
 * ���:
 *    TRUE��FALSE
 *
 */
__INLINE boolean LPLD_FTM_IsCHnF(FTM_Type *ftmx, FtmChnEnum_Type chn)
{
  return (boolean)((ftmx->CONTROLS[chn].CnSC & FTM_CnSC_CHF_MASK)>>FTM_CnSC_CHF_SHIFT);
}

/*
 * LPLD_FTM_ClearCHnF
 * ���ͨ��n�жϱ�־
 * 
 * ����:
 *    ftmx--FTMxģ���
 *      |__FTM0          --FTM0
 *      |__FTM1          --FTM1
 *      |__FTM2          --FTM2
 *      <ע:ֻ��MK60Fϵ�к���FTM3>
 *      |__FTM3          --FTM3
 *    chn--PWM���ͨ��
 *      <ע:ֻ��MK60Fϵ�к���FTM3>
 *      |__FTM_Ch0          --FTMxͨ��0(FTM0\FTM1\FTM2\FTM3)
 *      |__FTM_Ch1          --FTMxͨ��1(FTM0\FTM1\FTM2\FTM3)
 *      |__FTM_Ch2          --FTMxͨ��2(FTM0\FTM3)
 *      |__FTM_Ch3          --FTMxͨ��3(FTM0\FTM3)
 *      |__FTM_Ch4          --FTMxͨ��4(FTM0\FTM3)
 *      |__FTM_Ch5          --FTMxͨ��5(FTM0\FTM3)
 *      |__FTM_Ch6          --FTMxͨ��6(FTM0\FTM3)
 *      |__FTM_Ch7          --FTMxͨ��7(FTM0\FTM3)
 *
 * ���:
 *    ��
 *
 */
__INLINE void LPLD_FTM_ClearCHnF(FTM_Type *ftmx, FtmChnEnum_Type chn)
{
  ftmx->CONTROLS[chn].CnSC = ftmx->CONTROLS[chn].CnSC & ~FTM_CnSC_CHF_MASK;
}

/*
 * LPLD_FTM_GetChVal
 * ��ȡFTMxͨ��n�����FTMx����ֵ
 * 
 * ����:
 *    ftmx--FTMxģ���
 *      |__FTM0          --FTM0
 *      |__FTM1          --FTM1
 *      |__FTM2          --FTM2
 *      <ע:ֻ��MK60Fϵ�к���FTM3>
 *      |__FTM3          --FTM3
 *    chn--PWM���ͨ��
 *      <ע:ֻ��MK60Fϵ�к���FTM3>
 *      |__FTM_Ch0          --FTMxͨ��0(FTM0\FTM1\FTM2\FTM3)
 *      |__FTM_Ch1          --FTMxͨ��1(FTM0\FTM1\FTM2\FTM3)
 *      |__FTM_Ch2          --FTMxͨ��2(FTM0\FTM3)
 *      |__FTM_Ch3          --FTMxͨ��3(FTM0\FTM3)
 *      |__FTM_Ch4          --FTMxͨ��4(FTM0\FTM3)
 *      |__FTM_Ch5          --FTMxͨ��5(FTM0\FTM3)
 *      |__FTM_Ch6          --FTMxͨ��6(FTM0\FTM3)
 *      |__FTM_Ch7          --FTMxͨ��7(FTM0\FTM3)
 *
 * ���:
 *    0x1~0xFFFF
 *
 */
__INLINE uint16 LPLD_FTM_GetChVal(FTM_Type *ftmx, FtmChnEnum_Type chn)
{
  return ftmx->CONTROLS[chn].CnV;    //��ȡ��Ӧͨ�����񵽵�FTM������ֵ
}

/*
 * LPLD_FTM_GetClkDiv
 * ��ȡFTMxʱ�ӷ�Ƶϵ��
 * 
 * ����:
 *    ftmx--FTMxģ���
 *      |__FTM0          --FTM0
 *      |__FTM1          --FTM1
 *      |__FTM2          --FTM2
 *      <ע:ֻ��MK60Fϵ�к���FTM3>
 *      |__FTM3          --FTM3
 *
 * ���:
 *    1��2��4��8��16��32��64��128
 *
 */
__INLINE uint8 LPLD_FTM_GetClkDiv(FTM_Type *ftmx)
{
  return 1u<<((ftmx->SC & FTM_SC_PS_MASK)>>FTM_SC_PS_SHIFT);    //���ʱ�ӷ�Ƶϵ��
}

/*
 * LPLD_FTM_GetCounter
 * ��ȡFTMx������ֵ
 * 
 * ����:
 *    ftmx--FTMxģ���
 *      |__FTM0          --FTM0
 *      |__FTM1          --FTM1
 *      |__FTM2          --FTM2
 *      <ע:ֻ��MK60Fϵ�к���FTM3>
 *      |__FTM3          --FTM3
 *
 * ���:
 *    ��
 *
 */
__INLINE uint16 LPLD_FTM_GetCounter(FTM_Type *ftmx)
{
  return ftmx->CNT;        //��ȡFTMx������ֵ
}

/*
 * LPLD_FTM_ClearCounter
 * ���FTMx������
 * 
 * ����:
 *    ftmx--FTMxģ���
 *      |__FTM0          --FTM0
 *      |__FTM1          --FTM1
 *      |__FTM2          --FTM2
 *      <ע:ֻ��MK60Fϵ�к���FTM3>
 *      |__FTM3          --FTM3
 *
 * ���:
 *    ��
 *
 */
__INLINE void LPLD_FTM_ClearCounter(FTM_Type *ftmx)
{
  ftmx->CNT = 0;        //���FTMx������ֵ
}

/*
 * LPLD_FTM_EnableIrq
 * ʹ��FTMx�ж�
 * 
 * ����:
 *    ftm_init_structure--FTM��ʼ���ṹ�壬
 *                        ���嶨���FTM_InitTypeDef
 *
 * ���:
 *    0--���ô���
 *    1--���óɹ�
 *
 */
uint8 LPLD_FTM_EnableIrq(FTM_InitTypeDef ftm_init_structure)
{
  uint8 i;
  FTM_Type *ftmx = ftm_init_structure.FTM_Ftmx;
  
  if(ftmx == FTM0)
    i=0;
  else if(ftmx == FTM1)
    i=1;
  else if(ftmx == FTM2)
    i=2;
#if defined(CPU_MK60F12) || defined(CPU_MK60F15)
  else if(ftmx == FTM3)
    i=3;
#endif
  else
    return 0;

  enable_irq((IRQn_Type)(FTM0_IRQn + i));
  
  return 1;
}

/*
 * LPLD_FTM_DisableIrq
 * ����FTMx�ж�
 * 
 * ����:
 *    ftm_init_structure--FTM��ʼ���ṹ�壬
 *                        ���嶨���FTM_InitTypeDef
 *
 * ���:
 *    0--���ô���
 *    1--���óɹ�
 *
 */
uint8 LPLD_FTM_DisableIrq(FTM_InitTypeDef ftm_init_structure)
{
  uint8 i;
  FTM_Type *ftmx = ftm_init_structure.FTM_Ftmx;
  
  if(ftmx == FTM0)
    i=0;
  else if(ftmx == FTM1)
    i=1;
  else if(ftmx == FTM2)
    i=2;
#if defined(CPU_MK60F12) || defined(CPU_MK60F15)
  else if(ftmx == FTM3)
    i=3;
#endif
  else
    return 0;

  disable_irq((IRQn_Type)(FTM0_IRQn + i));
  
  return 1;
}

/*
 * LPLD_FTM_QD_Enable
 * FTMģ����������ģʽ����ʹ�ܣ���������ͨ��PHA��PHB
 *
 * ����:
 *    ftmx--FTMxģ���
 *      |__FTM1          --FTM1
 *      |__FTM2          --FTM2
 *    pha--PHA����ͨ������
 *      FTM1
 *        PTA8\PTA12\PTB0
 *      FTM2
 *        PTA10\PTB18
 *    phb--PHB����ͨ������
 *      FTM1
 *        PTA9\PTA13\PTB1
 *      FTM2
 *        PTA11\PTB19
 *
 * ���:
 *    0--���ô���
 *    1--���óɹ�
 */
uint8 LPLD_FTM_QD_Enable(FTM_Type *ftmx, PortPinsEnum_Type pha, PortPinsEnum_Type phb)
{
  if(!LPLD_FTM_PinInit(ftmx, FTM_PhA, pha))
    return 0;
  if(!LPLD_FTM_PinInit(ftmx, FTM_PhB, phb))
    return 0;
  
  return 1;
}

/*
 * LPLD_FTM_QD_Disable
 * FTMģ����������ģʽ�������
 *
 * ����:
 *    ftmx--FTMxģ���
 *      |__FTM1          --FTM1
 *      |__FTM2          --FTM2
 *
 * ���:
 *    0--���ô���
 *    1--���óɹ�
 */
uint8 LPLD_FTM_QD_Disable(FTM_Type *ftmx)
{
  if(!LPLD_FTM_PinDeinit(ftmx, FTM_PhA))
    return 0;
  if(!LPLD_FTM_PinDeinit(ftmx, FTM_PhB))
    return 0;
  
  return 1;
}

/*
 * LPLD_FTM_PWM_Init
 * FTMģ��PWMģʽ��ʼ�����ڲ�����
 */
static uint8 LPLD_FTM_PWM_Init(FTM_InitTypeDef ftm_init_structure)
{
  uint32 bus_clk_hz;
  uint32 mod, mod2;
  uint8 ps;
  uint32 freq = ftm_init_structure.FTM_PwmFreq;
  uint32 dt_en = ftm_init_structure.FTM_PwmDeadtimeCfg;
  uint8 dt_div = ftm_init_structure.FTM_PwmDeadtimeDiv;
  uint8 dt_val = ftm_init_structure.FTM_PwmDeadtimeVal;
  FTM_Type *ftmx = ftm_init_structure.FTM_Ftmx;
  
  //�������
  ASSERT( freq );                  //�ж�Ƶ��
  ASSERT( dt_val<=63 );            //�ж���������ֵ
  
  bus_clk_hz = g_bus_clock;
  
  if(freq>bus_clk_hz) return 0;
  
  if((mod=bus_clk_hz/(freq*128)) < 0xFFFFu)
  {
    ps = 7;
    mod2=mod;
    if((mod=bus_clk_hz/(freq*64)) < 0xFFFFu)
    {
      ps = 6;  
      mod2=mod;  
      if((mod=bus_clk_hz/(freq*32)) < 0xFFFFu)
      {
        ps = 5;  
        mod2=mod;
        if((mod=bus_clk_hz/(freq*16)) < 0xFFFFu)
        {
          ps = 4;  
          mod2=mod;   
          if((mod=bus_clk_hz/(freq*8)) < 0xFFFFu)
          {
            ps = 3;
            mod2=mod;
            if((mod=bus_clk_hz/(freq*4)) < 0xFFFFu)
            {
              ps = 2;
              mod2=mod;
              if((mod=bus_clk_hz/(freq*2)) < 0xFFFFu)
              {
                ps = 1;
                mod2=mod;
                if((mod=bus_clk_hz/(freq*1)) < 0xFFFFu)
                {
                  ps = 0;
                  mod2=mod;
                }
              }
            }
          }
        }  
      }
    }
  }
  else
  {
    return 0;
  }
  
  ftmx->SC = 0;
  
  // ����PWM���ڼ�ռ�ձ�
  //    PWM���� = (MOD-CNTIN+1)*FTMʱ������ :
  // ����FTM������ʼֵ
  ftmx->CNT = 0;
  ftmx->CNTIN = 0;
  // ����FTM����MODֵ
  ftmx->MOD = mod2;
  
  ftmx->DEADTIME = FTM_DEADTIME_DTPS(dt_div) | FTM_DEADTIME_DTVAL(dt_val);
  ftmx->COMBINE = dt_en;        //ʹ������
  
  // ����FTM���ƼĴ���
  // �����ж�, �Ӽ���ģʽ, ʱ��Դ:System clock��Bus Clk��, ��Ƶϵ��:8
  // ����SysClk = 50MHz, SC_PS=3, FTM Clk = 50MHz/2^3 = 6.25MHz
  ftmx->SC = FTM_SC_CLKS(1)|FTM_SC_PS(ps);
  
  return 1;
}

/*
 * LPLD_FTM_IC_Init
 * FTMģ�����벶��ģʽ��ʼ�����ڲ�����
 */
static uint8 LPLD_FTM_IC_Init(FTM_InitTypeDef ftm_init_structure)
{
  uint8 i;
  uint8 ps = ftm_init_structure.FTM_ClkDiv;
  FTM_ISR_CALLBACK isr_func = ftm_init_structure.FTM_Isr;
  FTM_Type *ftmx = ftm_init_structure.FTM_Ftmx;
  
  //�������
  ASSERT( ps <= 7);             //ʱ�ӷ�Ƶϵ��
  
  ftmx->CONF=FTM_CONF_BDMMODE(0x3);
  
  ftmx->SC = 0;
  
  ftmx->CNT = 0;
  ftmx->CNTIN = 0;
  ftmx->MOD = 0;                           
  ftmx->QDCTRL = (~FTM_QDCTRL_QUADEN_MASK); //�ر���������
  ftmx->FILTER = 0x00;                      //�ع�����
  
  // ����FTM���ƼĴ���
  // ��FTM Counter���ó�Free Counter
  // �����ж�, �Ӽ���ģʽ, ʱ��Դ:System clock��Bus Clk��, ��Ƶϵ��:PS
  // ����SysClk = 50MHz, SC_PS=3, FTM Clk = 50MHz/2^3 = 6.25MHz
  ftmx->SC |= FTM_SC_CLKS(1)|FTM_SC_PS(ps);
  //ftmx->SC |= FTM_SC_TOIE_MASK;             //ʹ�ܼ�������ж�
  ftmx->SC &= (~FTM_SC_CPWMS_MASK);         //FTM�Ӽ���

  //�����жϺ�����ڵ�ַ�������ж�
  if(isr_func!=NULL)
  {
    if(ftmx == FTM0)
      i=0;
    else if(ftmx == FTM1)
      i=1;
    else if(ftmx == FTM2)
      i=2;
#if defined(CPU_MK60F12) || defined(CPU_MK60F15)
    else if(ftmx == FTM3)
      i=3;
#endif   
    else
      return 0;
    FTM_ISR[i] = isr_func;
  }

  return 1;
}

/*
 * LPLD_FTM_PinInit
 * ��ʼ��ͨ��nָ�����ŵ�FTM���ù��ܣ��ڲ�����
 */
static uint8 LPLD_FTM_PinInit(FTM_Type *ftmx, FtmChnEnum_Type chn, PortPinsEnum_Type pin)
{ 
  //����ftmxʹ����Ӧpin��ftm����
  if(ftmx == FTM0)
  {
    switch(chn)
    {
    case FTM_Ch0:
      if(pin == PTA3)
        PORTA->PCR[3] = PORTA->PCR[3] & ~PORT_PCR_MUX_MASK | PORT_PCR_MUX(3); 
      else if(pin == PTC1)
        PORTC->PCR[1] = PORTC->PCR[1] & ~PORT_PCR_MUX_MASK | PORT_PCR_MUX(4);
      else
        return 0;
      break;
    case FTM_Ch1:
      if(pin == PTA4)
        PORTA->PCR[4] = PORTA->PCR[4] & ~PORT_PCR_MUX_MASK | PORT_PCR_MUX(3); 
      else if(pin == PTC2)
        PORTC->PCR[2] = PORTC->PCR[2] & ~PORT_PCR_MUX_MASK | PORT_PCR_MUX(4);
      else
        return 0;
      break;
    case FTM_Ch2:
      if(pin == PTA5)
        PORTA->PCR[5] = PORTA->PCR[5] & ~PORT_PCR_MUX_MASK | PORT_PCR_MUX(3); 
      else if(pin == PTC3)
        PORTC->PCR[3] = PORTC->PCR[3] & ~PORT_PCR_MUX_MASK | PORT_PCR_MUX(4);
      else
        return 0;
      break;
    case FTM_Ch3:
      if(pin == PTA6)
        PORTA->PCR[6] = PORTA->PCR[6] & ~PORT_PCR_MUX_MASK | PORT_PCR_MUX(3); 
      else if(pin == PTC4)
        PORTC->PCR[4] = PORTC->PCR[4] & ~PORT_PCR_MUX_MASK | PORT_PCR_MUX(4);
      else
        return 0;
      break;
    case FTM_Ch4:
      if(pin == PTA7)
        PORTA->PCR[7] = PORTA->PCR[7] & ~PORT_PCR_MUX_MASK | PORT_PCR_MUX(3); 
      else if(pin == PTD4)
        PORTD->PCR[4] = PORTD->PCR[4] & ~PORT_PCR_MUX_MASK | PORT_PCR_MUX(4);
      else
        return 0;
      break;
    case FTM_Ch5:
      if(pin == PTA0)
        PORTA->PCR[0] = PORTA->PCR[0] & ~PORT_PCR_MUX_MASK | PORT_PCR_MUX(3); 
      else if(pin == PTD5)
        PORTD->PCR[5] = PORTD->PCR[5] & ~PORT_PCR_MUX_MASK | PORT_PCR_MUX(4);
      else
        return 0;
      break;
    case FTM_Ch6:
      if(pin == PTA1)
        PORTA->PCR[1] = PORTA->PCR[1] & ~PORT_PCR_MUX_MASK | PORT_PCR_MUX(3); 
      else if(pin == PTD6)
        PORTD->PCR[6] = PORTD->PCR[6] & ~PORT_PCR_MUX_MASK | PORT_PCR_MUX(4);
      else
        return 0;
      break;
    case FTM_Ch7:
      if(pin == PTA2)
        PORTA->PCR[2] = PORTA->PCR[2] & ~PORT_PCR_MUX_MASK | PORT_PCR_MUX(3); 
      else if(pin == PTD7)
        PORTD->PCR[7] = PORTD->PCR[7] & ~PORT_PCR_MUX_MASK | PORT_PCR_MUX(4);
      else
        return 0;
      break;
    default:
      return 0;     
    }
  }
  else if(ftmx == FTM1)
  {
    switch(chn)
    {
    case FTM_Ch0:
      if(pin == PTA8)
        PORTA->PCR[8] = PORTA->PCR[8] & ~PORT_PCR_MUX_MASK | PORT_PCR_MUX(3); 
      else if(pin == PTA12)
        PORTA->PCR[12] = PORTA->PCR[12] & ~PORT_PCR_MUX_MASK | PORT_PCR_MUX(3);
      else if(pin == PTB0)
        PORTB->PCR[0] = PORTB->PCR[0] & ~PORT_PCR_MUX_MASK | PORT_PCR_MUX(3);
      else
        return 0;
      break;
    case FTM_Ch1:
      if(pin == PTA9)
        PORTA->PCR[9] = PORTA->PCR[9] & ~PORT_PCR_MUX_MASK | PORT_PCR_MUX(3); 
      else if(pin == PTA13)
        PORTA->PCR[13] = PORTA->PCR[13] & ~PORT_PCR_MUX_MASK | PORT_PCR_MUX(3);
      else if(pin == PTB1)
        PORTB->PCR[1] = PORTB->PCR[1] & ~PORT_PCR_MUX_MASK | PORT_PCR_MUX(3);
      else
        return 0;
      break;
    case FTM_PhA:
      if(pin == PTA8)
        PORTA->PCR[8] = PORTA->PCR[8] & ~PORT_PCR_MUX_MASK | PORT_PCR_MUX(6); 
      else if(pin == PTA12)
        PORTA->PCR[12] = PORTA->PCR[12] & ~PORT_PCR_MUX_MASK | PORT_PCR_MUX(7);
      else if(pin == PTB0)
        PORTB->PCR[0] = PORTB->PCR[0] & ~PORT_PCR_MUX_MASK | PORT_PCR_MUX(6);
      else
        return 0;
      break;
    case FTM_PhB:
      if(pin == PTA9)
        PORTA->PCR[9] = PORTA->PCR[9] & ~PORT_PCR_MUX_MASK | PORT_PCR_MUX(6); 
      else if(pin == PTA13)
        PORTA->PCR[13] = PORTA->PCR[13] & ~PORT_PCR_MUX_MASK | PORT_PCR_MUX(7);
      else if(pin == PTB1)
        PORTB->PCR[1] = PORTB->PCR[1] & ~PORT_PCR_MUX_MASK | PORT_PCR_MUX(6);
      else
        return 0;
    default:
      return 0;   
    }
  }
  else if(ftmx == FTM2)
  {
    switch(chn)
    {
    case FTM_Ch0:
      if(pin == PTA10)
        PORTA->PCR[10] = PORTA->PCR[10] & ~PORT_PCR_MUX_MASK | PORT_PCR_MUX(3); 
      else if(pin == PTB18)
        PORTB->PCR[18] = PORTB->PCR[18] & ~PORT_PCR_MUX_MASK | PORT_PCR_MUX(3);
      else
        return 0;
      break;
    case FTM_Ch1:
      if(pin == PTA11)
        PORTA->PCR[11] = PORTA->PCR[11] & ~PORT_PCR_MUX_MASK | PORT_PCR_MUX(3); 
      else if(pin == PTB19)
        PORTB->PCR[19] = PORTB->PCR[19] & ~PORT_PCR_MUX_MASK | PORT_PCR_MUX(3);
      else
        return 0;
      break;
    case FTM_PhA:
      if(pin == PTA10)
        PORTA->PCR[10] = PORTA->PCR[10] & ~PORT_PCR_MUX_MASK | PORT_PCR_MUX(6); 
      else if(pin == PTB18)
        PORTB->PCR[18] = PORTB->PCR[18] & ~PORT_PCR_MUX_MASK | PORT_PCR_MUX(6);
      else
        return 0;
      break;
    case FTM_PhB:
      if(pin == PTA11)
        PORTA->PCR[11] = PORTA->PCR[11] & ~PORT_PCR_MUX_MASK | PORT_PCR_MUX(6); 
      else if(pin == PTB19)
        PORTB->PCR[19] = PORTB->PCR[19] & ~PORT_PCR_MUX_MASK | PORT_PCR_MUX(6);
      else
        return 0;
      break;
    default:
      return 0;   
    }
  }
  
#if defined(CPU_MK60F12) || defined(CPU_MK60F15)
  else if(ftmx == FTM3)
  {
    switch(chn)
    {
    case FTM_Ch0:
      if(pin == PTE5)
        PORTE->PCR[5] = PORTE->PCR[5] & ~PORT_PCR_MUX_MASK | PORT_PCR_MUX(6); 
      else if(pin == PTD0)
        PORTD->PCR[0] = PORTD->PCR[0] & ~PORT_PCR_MUX_MASK | PORT_PCR_MUX(4);
      else
        return 0;
      break;
    case FTM_Ch1:
      if(pin == PTE6)
        PORTE->PCR[6] = PORTE->PCR[6] & ~PORT_PCR_MUX_MASK | PORT_PCR_MUX(6); 
      else if(pin == PTD0)
        PORTD->PCR[1] = PORTD->PCR[1] & ~PORT_PCR_MUX_MASK | PORT_PCR_MUX(4);
      else
        return 0;
      break;
    case FTM_Ch2:
      if(pin == PTE7)
        PORTE->PCR[7] = PORTE->PCR[7] & ~PORT_PCR_MUX_MASK | PORT_PCR_MUX(6); 
      else if(pin == PTD0)
        PORTD->PCR[2] = PORTD->PCR[2] & ~PORT_PCR_MUX_MASK | PORT_PCR_MUX(4);
      else
        return 0;
      break;
    case FTM_Ch3:
      if(pin == PTE8)
        PORTE->PCR[8] = PORTE->PCR[8] & ~PORT_PCR_MUX_MASK | PORT_PCR_MUX(6); 
      else if(pin == PTD0)
        PORTD->PCR[3] = PORTD->PCR[3] & ~PORT_PCR_MUX_MASK | PORT_PCR_MUX(4);
      else
        return 0;
      break;
    case FTM_Ch4:
      if(pin == PTE9)
        PORTE->PCR[9] = PORTE->PCR[9] & ~PORT_PCR_MUX_MASK | PORT_PCR_MUX(6); 
      else if(pin == PTC8)
        PORTC->PCR[8] = PORTC->PCR[8] & ~PORT_PCR_MUX_MASK | PORT_PCR_MUX(3);
      else
        return 0;
      break;
    case FTM_Ch5:
      if(pin == PTE10)
        PORTE->PCR[10] = PORTE->PCR[10] & ~PORT_PCR_MUX_MASK | PORT_PCR_MUX(6); 
      else if(pin == PTC9)
        PORTC->PCR[9] = PORTC->PCR[9] & ~PORT_PCR_MUX_MASK | PORT_PCR_MUX(3);
      else
        return 0;
      break;
    case FTM_Ch6:
      if(pin == PTE11)
        PORTE->PCR[11] = PORTE->PCR[11] & ~PORT_PCR_MUX_MASK | PORT_PCR_MUX(6); 
      else if(pin == PTC10)
        PORTC->PCR[10] = PORTC->PCR[10] & ~PORT_PCR_MUX_MASK | PORT_PCR_MUX(3);
      else
        return 0;
      break;
    case FTM_Ch7:
      if(pin == PTE12)
        PORTE->PCR[12] = PORTE->PCR[12] & ~PORT_PCR_MUX_MASK | PORT_PCR_MUX(6); 
      else if(pin == PTC11)
        PORTC->PCR[11] = PORTC->PCR[11] & ~PORT_PCR_MUX_MASK | PORT_PCR_MUX(3);
      else
        return 0;
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
 * LPLD_FTM_PinInit
 * ����ʼ��ͨ��nָ�����ŵ�FTM���ù��ܣ��ڲ�����
 */
static uint8 LPLD_FTM_PinDeinit(FTM_Type *ftmx, FtmChnEnum_Type chn)
{
  //����ftmx������Ӧpin��ftm���ܣ��ظ���Ĭ�Ϲ���
  if(ftmx == FTM0)
  {
    switch(chn)
    {
    case FTM_Ch0:
      if((PORTA->PCR[3]& PORT_PCR_MUX_MASK) == PORT_PCR_MUX(3))
        PORTA->PCR[3] = PORT_PCR_MUX(0); 
      if((PORTC->PCR[1]& PORT_PCR_MUX_MASK) == PORT_PCR_MUX(4))
        PORTC->PCR[1] = PORT_PCR_MUX(0);
      break;
    case FTM_Ch1:
      if((PORTA->PCR[4]& PORT_PCR_MUX_MASK) == PORT_PCR_MUX(3))
        PORTA->PCR[4] = PORT_PCR_MUX(0); 
      if((PORTC->PCR[2]& PORT_PCR_MUX_MASK) == PORT_PCR_MUX(4))
        PORTC->PCR[2] = PORT_PCR_MUX(0);
      break;
    case FTM_Ch2:
      if((PORTA->PCR[5]& PORT_PCR_MUX_MASK) == PORT_PCR_MUX(3))
        PORTA->PCR[5] = PORT_PCR_MUX(0); 
      if((PORTC->PCR[3]& PORT_PCR_MUX_MASK) == PORT_PCR_MUX(4))
        PORTC->PCR[3] = PORT_PCR_MUX(0);
      break;
    case FTM_Ch3:
      if((PORTA->PCR[6]& PORT_PCR_MUX_MASK) == PORT_PCR_MUX(3))
        PORTA->PCR[6] = PORT_PCR_MUX(0); 
      if((PORTC->PCR[4]& PORT_PCR_MUX_MASK) == PORT_PCR_MUX(4))
        PORTC->PCR[4] = PORT_PCR_MUX(0);
      break;
    case FTM_Ch4:
      if((PORTA->PCR[7]& PORT_PCR_MUX_MASK) == PORT_PCR_MUX(3))
        PORTA->PCR[7] = PORT_PCR_MUX(0); 
      if((PORTD->PCR[4]& PORT_PCR_MUX_MASK) == PORT_PCR_MUX(4))
        PORTD->PCR[4] = PORT_PCR_MUX(0);
      break;
    case FTM_Ch5:
      if((PORTA->PCR[0]& PORT_PCR_MUX_MASK) == PORT_PCR_MUX(3))
        PORTA->PCR[0] = PORT_PCR_MUX(0); 
      if((PORTD->PCR[5]& PORT_PCR_MUX_MASK) == PORT_PCR_MUX(4))
        PORTD->PCR[5] = PORT_PCR_MUX(0);
      break;
    case FTM_Ch6:
      if((PORTA->PCR[1]& PORT_PCR_MUX_MASK) == PORT_PCR_MUX(3))
        PORTA->PCR[1] = PORT_PCR_MUX(0); 
      if((PORTD->PCR[6]& PORT_PCR_MUX_MASK) == PORT_PCR_MUX(4))
        PORTD->PCR[6] = PORT_PCR_MUX(0);
      break;
    case FTM_Ch7:
      if((PORTA->PCR[2]& PORT_PCR_MUX_MASK) == PORT_PCR_MUX(3))
        PORTA->PCR[2] = PORT_PCR_MUX(0); 
      if((PORTD->PCR[7]& PORT_PCR_MUX_MASK) == PORT_PCR_MUX(4))
        PORTD->PCR[7] = PORT_PCR_MUX(0);      
      break;
    default:
      return 0;     
    }
  }
  else if(ftmx == FTM1)
  {
    switch(chn)
    {
    case FTM_Ch0:
      if((PORTA->PCR[8]& PORT_PCR_MUX_MASK) == PORT_PCR_MUX(3))
        PORTA->PCR[8] = PORT_PCR_MUX(0); 
      if((PORTA->PCR[12]& PORT_PCR_MUX_MASK) == PORT_PCR_MUX(3))
        PORTA->PCR[12] = PORT_PCR_MUX(0);
      if((PORTB->PCR[0]& PORT_PCR_MUX_MASK) == PORT_PCR_MUX(3))
        PORTB->PCR[0] = PORT_PCR_MUX(0);
      break;
    case FTM_Ch1:
      if((PORTA->PCR[9]& PORT_PCR_MUX_MASK) == PORT_PCR_MUX(3))
        PORTA->PCR[9] = PORT_PCR_MUX(0); 
      if((PORTA->PCR[13]& PORT_PCR_MUX_MASK) == PORT_PCR_MUX(3))
        PORTA->PCR[13] = PORT_PCR_MUX(0);
      if((PORTB->PCR[1]& PORT_PCR_MUX_MASK) == PORT_PCR_MUX(3))
        PORTB->PCR[1] = PORT_PCR_MUX(0);
      break;
    case FTM_PhA:
      if((PORTA->PCR[8]& PORT_PCR_MUX_MASK) == PORT_PCR_MUX(6))
        PORTA->PCR[8] = PORT_PCR_MUX(0); 
      if((PORTA->PCR[12]& PORT_PCR_MUX_MASK) == PORT_PCR_MUX(7))
        PORTA->PCR[12] = PORT_PCR_MUX(0);
      if((PORTB->PCR[0]& PORT_PCR_MUX_MASK) == PORT_PCR_MUX(6))
        PORTB->PCR[0] = PORT_PCR_MUX(0);
      break;
    case FTM_PhB:
      if((PORTA->PCR[9]& PORT_PCR_MUX_MASK) == PORT_PCR_MUX(6))
        PORTA->PCR[9] = PORT_PCR_MUX(0); 
      if((PORTA->PCR[13]& PORT_PCR_MUX_MASK) == PORT_PCR_MUX(7))
        PORTA->PCR[13] = PORT_PCR_MUX(0);
      if((PORTB->PCR[1]& PORT_PCR_MUX_MASK) == PORT_PCR_MUX(6))
        PORTB->PCR[1] = PORT_PCR_MUX(0);
      break;
    default:
      return 0;   
    }
  }
  else if(ftmx == FTM2)
  {
    switch(chn)
    {
    case FTM_Ch0:
      if((PORTA->PCR[10]& PORT_PCR_MUX_MASK) == PORT_PCR_MUX(3))
        PORTA->PCR[10] = PORT_PCR_MUX(0); 
      if((PORTB->PCR[18]& PORT_PCR_MUX_MASK) == PORT_PCR_MUX(3))
        PORTB->PCR[18] = PORT_PCR_MUX(0);
      break;
    case FTM_Ch1:
      if((PORTA->PCR[11]& PORT_PCR_MUX_MASK) == PORT_PCR_MUX(3))
        PORTA->PCR[11] = PORT_PCR_MUX(0); 
      if((PORTB->PCR[19]& PORT_PCR_MUX_MASK) == PORT_PCR_MUX(3))
        PORTB->PCR[19] = PORT_PCR_MUX(0);
      break;
    case FTM_PhA:
      if((PORTA->PCR[10]& PORT_PCR_MUX_MASK) == PORT_PCR_MUX(6))
        PORTA->PCR[10] = PORT_PCR_MUX(0); 
      if((PORTB->PCR[18]& PORT_PCR_MUX_MASK) == PORT_PCR_MUX(6))
        PORTB->PCR[18] = PORT_PCR_MUX(0);
      break;
    case FTM_PhB:
      if((PORTA->PCR[11]& PORT_PCR_MUX_MASK) == PORT_PCR_MUX(6))
        PORTA->PCR[11] = PORT_PCR_MUX(0); 
      if((PORTB->PCR[19]& PORT_PCR_MUX_MASK) == PORT_PCR_MUX(6))
        PORTB->PCR[19] = PORT_PCR_MUX(0);
      break;
    default:
      return 0;   
    }
  }
#if defined(CPU_MK60F12) || defined(CPU_MK60F15)
  else if(ftmx == FTM3)
  {
    switch(chn)
    {
    case FTM_Ch0:
      if((PORTE->PCR[5]& PORT_PCR_MUX_MASK) == PORT_PCR_MUX(6))
        PORTE->PCR[5] = PORT_PCR_MUX(0); 
      if((PORTD->PCR[0]& PORT_PCR_MUX_MASK) == PORT_PCR_MUX(4))
        PORTD->PCR[0] = PORT_PCR_MUX(0);
      break;
    case FTM_Ch1:
      if((PORTE->PCR[6]& PORT_PCR_MUX_MASK) == PORT_PCR_MUX(6))
        PORTE->PCR[6] = PORT_PCR_MUX(0); 
      if((PORTD->PCR[1]& PORT_PCR_MUX_MASK) == PORT_PCR_MUX(4))
        PORTD->PCR[1] = PORT_PCR_MUX(0);
      break;
    case FTM_Ch2:
      if((PORTE->PCR[7]& PORT_PCR_MUX_MASK) == PORT_PCR_MUX(6))
        PORTE->PCR[7] = PORT_PCR_MUX(0); 
      if((PORTD->PCR[2]& PORT_PCR_MUX_MASK) == PORT_PCR_MUX(4))
        PORTD->PCR[2] = PORT_PCR_MUX(0);
      break;
    case FTM_Ch3:
      if((PORTE->PCR[8]& PORT_PCR_MUX_MASK) == PORT_PCR_MUX(6))
        PORTE->PCR[8] = PORT_PCR_MUX(0); 
      if((PORTD->PCR[3]& PORT_PCR_MUX_MASK) == PORT_PCR_MUX(4))
        PORTD->PCR[3] = PORT_PCR_MUX(0);
      break;
    case FTM_Ch4:
      if((PORTE->PCR[9]& PORT_PCR_MUX_MASK) == PORT_PCR_MUX(6))
        PORTE->PCR[9] = PORT_PCR_MUX(0); 
      if((PORTC->PCR[8]& PORT_PCR_MUX_MASK) == PORT_PCR_MUX(3))
        PORTC->PCR[8] = PORT_PCR_MUX(0);
      break;
    case FTM_Ch5:
      if((PORTE->PCR[10]& PORT_PCR_MUX_MASK) == PORT_PCR_MUX(6))
        PORTE->PCR[10] = PORT_PCR_MUX(0); 
      if((PORTC->PCR[9]& PORT_PCR_MUX_MASK) == PORT_PCR_MUX(3))
        PORTC->PCR[9] = PORT_PCR_MUX(0);
      break;
    case FTM_Ch6:
      if((PORTE->PCR[11]& PORT_PCR_MUX_MASK) == PORT_PCR_MUX(6))
        PORTE->PCR[11] = PORT_PCR_MUX(0); 
      if((PORTC->PCR[10]& PORT_PCR_MUX_MASK) == PORT_PCR_MUX(3))
        PORTC->PCR[10] = PORT_PCR_MUX(0);
      break;
    case FTM_Ch7:
      if((PORTE->PCR[12]& PORT_PCR_MUX_MASK) == PORT_PCR_MUX(6))
        PORTE->PCR[12] = PORT_PCR_MUX(0); 
      if((PORTC->PCR[11]& PORT_PCR_MUX_MASK) == PORT_PCR_MUX(3))
        PORTC->PCR[11] = PORT_PCR_MUX(0);
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
 * LPLD_FTM_QD_Init
 * FTMģ����������ģʽ��ʼ�����ڲ�����
 */
static uint8 LPLD_FTM_QD_Init(FTM_InitTypeDef ftm_init_structure)
{
  uint8 mode = ftm_init_structure.FTM_QdMode;
  FTM_Type *ftmx = ftm_init_structure.FTM_Ftmx;
 
  ftmx->MODE |= FTM_MODE_FTMEN_MASK;    //FTM2EN=1   
  
  ftmx->CNTIN = 0;//FTM0��������ʼֵΪ0  
  ftmx->CNT=0;  
  ftmx->MOD = 0xFFFF;//����ֵ  
  
  ftmx->QDCTRL |= mode;     //����ģʽѡ��
  ftmx->QDCTRL |= FTM_QDCTRL_QUADEN_MASK;       //ʹ����������ģʽ 

  return 1;
}

static uint8 LPLD_FTM_DEC_Init(FTM_InitTypeDef ftm_init_structure)
{
  
  return 0;
}

/*
 * FTM0--FTM1�жϴ�����
 * �������ļ�startup_K60.s�е��ж����������
 * �û������޸ģ������Զ������Ӧͨ���жϺ���
 */
void FTM0_IRQHandler(void)
{
#if (UCOS_II > 0u)
  OS_CPU_SR  cpu_sr = 0u;
  OS_ENTER_CRITICAL(); //��֪ϵͳ��ʱ�Ѿ��������жϷ����Ӻ���
  OSIntEnter();
  OS_EXIT_CRITICAL();
#endif
  
  FTM_ISR[0]();
  
#if (UCOS_II > 0u)
  OSIntExit();          //��֪ϵͳ��ʱ�����뿪�жϷ����Ӻ���
#endif
}

void FTM1_IRQHandler(void)
{
#if (UCOS_II > 0u)
  OS_CPU_SR  cpu_sr = 0u;
  OS_ENTER_CRITICAL(); //��֪ϵͳ��ʱ�Ѿ��������жϷ����Ӻ���
  OSIntEnter();
  OS_EXIT_CRITICAL();
#endif
  
  FTM_ISR[1]();
  
#if (UCOS_II > 0u)
  OSIntExit();          //��֪ϵͳ��ʱ�����뿪�жϷ����Ӻ���
#endif
}

void FTM2_IRQHandler(void)
{
#if (UCOS_II > 0u)
  OS_CPU_SR  cpu_sr = 0u;
  OS_ENTER_CRITICAL(); //��֪ϵͳ��ʱ�Ѿ��������жϷ����Ӻ���
  OSIntEnter();
  OS_EXIT_CRITICAL();
#endif
  
  FTM_ISR[2]();
  
#if (UCOS_II > 0u)
  OSIntExit();          //��֪ϵͳ��ʱ�����뿪�жϷ����Ӻ���
#endif
}

#if defined(CPU_MK60F12) || defined(CPU_MK60F15)
void FTM3_IRQHandler(void)
{
#if (UCOS_II > 0u)
  OS_CPU_SR  cpu_sr = 0u;
  OS_ENTER_CRITICAL(); //��֪ϵͳ��ʱ�Ѿ��������жϷ����Ӻ���
  OSIntEnter();
  OS_EXIT_CRITICAL();
#endif
  
  FTM_ISR[3]();
  
#if (UCOS_II > 0u)
  OSIntExit();          //��֪ϵͳ��ʱ�����뿪�жϷ����Ӻ���
#endif
}
#endif