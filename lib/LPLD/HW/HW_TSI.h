/**
 * @file HW_TSI.h
 * @version 3.0[By LPLD]
 * @date 2013-06-18
 * @brief TSI�ײ�ģ����غ���
 *
 * ���Ľ���:�������޸Ĵ��룬��ע�Ϳ������޸Ĳ���ֵ
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
#ifndef __HW_TSI_H__
#define __HW_TSI_H__

/********�û����޸�ֵ ��ʼ***********/
//TSI�缫��ֵ����ֵ
//��ֵ���ݾ���ֵ�趨���û����������޸�
#define TSI_OVERRUN_VAL (0x30000)

//TSI�缫��������ֵ
//��ֵ���ݾ���ֵ�趨���û����������޸�
#define TSI_TOUCH_VAL   (0x800)

//TSI�缫δ��������ֵ
//��ֵ���ݾ���ֵ�趨�����������ʼ���Լ��������ֵ
#define TSI_BASE_VAL    (0x800)
/********�û����޸�ֵ ����***********/

//TSIģ���жϻص���������
typedef void (*TSI_ISR_CALLBACK)(void);

//TSIͨ�����붨��
typedef enum TsiChxEnum
{
  TSI_Ch0  = 0x0001,    //PTB0
  TSI_Ch1  = 0x0002,    //PTA0
  TSI_Ch2  = 0x0004,    //PTA1
  TSI_Ch3  = 0x0008,    //PTA2
  TSI_Ch4  = 0x0010,    //PTA3
  TSI_Ch5  = 0x0020,    //PTA4
  TSI_Ch6  = 0x0040,    //PTB1
  TSI_Ch7  = 0x0080,    //PTB2
  TSI_Ch8  = 0x0100,    //PTB3
  TSI_Ch9  = 0x0200,    //PTB16
  TSI_Ch10 = 0x0400,    //PTB17
  TSI_Ch11 = 0x0800,    //PTB18
  TSI_Ch12 = 0x1000,    //PTB19
  TSI_Ch13 = 0x2000,    //PTC0
  TSI_Ch14 = 0x4000,    //PTC1
  TSI_Ch15 = 0x8000     //PTC2
}TsiChxEnum_Type;

//TSI_InitTypeDef�ṹ��TSI_ScanTriggerModeȡֵ
#define TSI_SCAN_SOFT   0       //�������ɨ��
#define TSI_SCAN_PERIOD 1       //���ڴ���ɨ��
//TSI_InitTypeDef�ṹ��TSI_EndScanOrOutRangeȡֵ
#define TSI_OUTOFRANGE_INT 0    //��Χ����ж�
#define TSI_ENDOFDCAN_INT  1    //ɨ������ж�

typedef struct 
{
  /*
    ������
      ѡ��Ҫ��ʼ����ͨ��
    ȡֵ��
      TSI_Ch0~TSI_Ch15-��Ӧ�����ż�TsiChxEnum_Typeö��ע��
    ��ʼ����
      �����ʼ��
  */
  uint16 TSI_Chs;
  
  /*
    ������
      ѡ�񴥷�ɨ���ģʽ
    ȡֵ��
      TSI_SCAN_SOFT-�������ɨ��
      TSI_SCAN_PERIOD-���ڴ���ɨ��
    ��ʼ����
      �������ʼ����Ĭ��TSI_SCAN_SOFT
  */
  uint8 TSI_ScanTriggerMode;
  
  /*
    ������
      ѡ��ɨ����������жϻ��Ƿ�Χ��������ж�
    ȡֵ��
      TSI_OUTOFRANGE_INT-��Χ����ж�
      TSI_ENDOFDCAN_INT-ɨ������ж�
    ��ʼ����
      �������ʼ����Ĭ��TSI_OUTOFRANGE_INT
  */ 
  uint8 TSI_EndScanOrOutRangeInt;
  
  /*
    ������
      ʹ�ܴ����ж�
    ȡֵ��
      TRUE-ʹ��
      FALSE-����
    ��ʼ����
      �������ʼ����Ĭ��FALSE
  */ 
  boolean TIS_ErrIntEnable;

  /*
    ������
      ɨ������жϻص�����
    ȡֵ��
      ��������Ϊ�޷���ֵ,�޲���(eg. void isr(void);)
    ��ʼ����
      �������ʼ������δ��ʼ���򲻻ᴥ���ж�
  */
  TSI_ISR_CALLBACK TSI_EndScanIsr;

  /*
    ������
      ��Χ����жϻص�����
    ȡֵ��
      ��������Ϊ�޷���ֵ,�޲���(eg. void isr(void);)
    ��ʼ����
      �������ʼ������δ��ʼ���򲻻ᴥ���ж�
  */
  TSI_ISR_CALLBACK TSI_OutRangeIsr;

  /*
    ������
      �����жϻص�����
    ȡֵ��
      ��������Ϊ�޷���ֵ,�޲���(eg. void isr(void);)
    ��ʼ����
      �������ʼ������δ��ʼ���򲻻ᴥ���ж�
  */
  TSI_ISR_CALLBACK TSI_ErrIsr;
  
  /*
    ������
      �Ƿ�ʹ�ܳ�ʼ���Ե�׼
    ȡֵ��
      TRUE-ʹ��
      FALSE-����
    ��ʼ����
      �������ʼ����Ĭ��FALSE
  */ 
  boolean TSI_IsInitSelfCal;
  
}TSI_InitTypeDef;

//���ɨ�������־
#define LPLD_TSI_ClearEndScanFlag()   (TSI0->GENCS|=TSI_GENCS_EOSF_MASK)
//�����Χ�����־
#define LPLD_TSI_ClearOutRangeFlag()  (TSI0->GENCS|=TSI_GENCS_OUTRGF_MASK)
//���ͨ��CHX��ɨ��Ӵ���־��CHXȡֵTSI_Ch0~TSI_Ch15
#define LPLD_TSI_ClearEndScanFlagChx(CHX)   (TSI0->STATUS|=CHX)
//���ͨ��CHX�Ĵ����־��CHXȡֵTSI_Ch0~TSI_Ch15
#define LPLD_TIS_ClrarErrorFlagChx(CHX)     (TSI0->STATUS|=(CHX<<16))
//ͨ��CHX�Ƿ�Χ�����CHXȡֵTSI_Ch0~TSI_Ch15
#define LPLD_TSI_IsChxOutRange(CHX)   (TSI0->STATUS&CHX)
//ͨ��CHX�Ƿ����CHXȡֵTSI_Ch0~TSI_Ch15
#define LPLD_TSI_IsChxError(CHX)      (TSI0->STATUS&(CHX<<16))
//ʹ��TSI�ж�
#define LPLD_TSI_EnableIrq()     enable_irq(TSI0_IRQn)
//����TSI�ж�
#define LPLD_TSI_DisableIrq()    disable_irq(TSI0_IRQn)

//TSIͨ�ó�ʼ������
uint8 LPLD_TSI_Init(TSI_InitTypeDef);
//TSI����ʼ������
void LPLD_TSI_Deinit(void);
//���Ϊch_num��ͨ���Ƿ��д�������
boolean LPLD_TSI_IsChxTouched(uint8);

#endif /* __HW_TSI_H__ */