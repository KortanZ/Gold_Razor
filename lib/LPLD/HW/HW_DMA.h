/**
* @file HW_DMA.h
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
#ifndef __HW_DMA_H__
#define __HW_DMA_H__

//����eDMA�жϻص�����
typedef void (*DMA_ISR_CALLBACK)(void);

#if defined(CPU_MK60DZ10) || defined(CPU_MK60D10) 
//=====================================
//  DMA request sources Number--MUX0
//      �����DMA�����
//=====================================
#define UART0_REV_DMAREQ  2
#define UART0_TRAN_DMAREQ 3
#define UART1_REV_DMAREQ  4
#define UART1_TRAN_DMAREQ 5
#define UART2_REV_DMAREQ  6
#define UART2_TRAN_DMAREQ 7
#define UART3_REV_DMAREQ  8
#define UART3_TRAN_DMAREQ 9
#define UART4_REV_DMAREQ  10
#define UART4_TRAN_DMAREQ 11
#define UART5_REV_DMAREQ  12
#define UART5_TRAN_DMAREQ 13
#define I2S0_REV_DMAREQ   14
#define I2S0_TRAN_DMAREQ  15
#define SPI0_REV_DMAREQ   16
#define SPI0_TRAN_DMAREQ  17
#define SPI1_REV_DMAREQ   18
#define SPI1_TRAN_DMAREQ  19
#define I2C0_DMAREQ       22
#define I2C1_DMAREQ       23
#define FTM0_CH0_DMAREQ   24
#define FTM0_CH1_DMAREQ   25
#define FTM0_CH2_DMAREQ   26
#define FTM0_CH3_DMAREQ   27
#define FTM0_CH4_DMAREQ   28
#define FTM0_CH5_DMAREQ   29
#define FTM0_CH6_DMAREQ   30
#define FTM0_CH7_DMAREQ   31
#define FTM1_CH0_DMAREQ   32
#define FTM1_CH1_DMAREQ   33
#define FTM2_CH0_DMAREQ   34
#define FTM2_CH1_DMAREQ   35
#define FTM3_CH0_DMAREQ   36
#define FTM3_CH1_DMAREQ   37
#define FTM3_CH2_DMAREQ   38
#define FTM1_CH3_DMAREQ   39  
#define ADC0_DMAREQ       40
#define ADC1_DMAREQ       41
#define CMP0_DMAREQ       42
#define CMP1_DMAREQ       43
#define CMP2_DMAREQ       44
#define DAC0_DMAREQ       45
#define DAC1_DMAREQ       46
#define CMT_DMAREQ        47
#define PDB_DMAREQ        48
#define PORTA_DMAREQ      49
#define PORTB_DMAREQ      50
#define PORTC_DMAREQ      51
#define PORTD_DMAREQ      52
#define PORTE_DMAREQ      53
#define FTM3_CH4_DMAREQ   54
#define FTM3_CH5_DMAREQ   55
#define FTM3_CH6_DMAREQ   56
#define FTM3_CH7_DMAREQ   57
#define DMA_MUX_58        58
#define DMA_MUX_59        59
#define DMA_MUX_60        60
#define DMA_MUX_61        61
#define DMA_MUX_62        62
#define DMA_MUX_63        63

#elif defined(CPU_MK60F12) || defined(CPU_MK60F15)
//==========================================================
//  DMA request sources Number--MUX0 channel00 -- channel15
//      �����DMA�����
//===========================================================
#define UART0_REV_DMAREQ  2
#define UART0_TRAN_DMAREQ 3
#define UART1_REV_DMAREQ  4
#define UART1_TRAN_DMAREQ 5
#define UART2_REV_DMAREQ  6
#define UART2_TRAN_DMAREQ 7
#define UART3_REV_DMAREQ  8
#define UART3_TRAN_DMAREQ 9
#define UART4_REV_DMAREQ  10
#define UART4_TRAN_DMAREQ 11
#define UART5_REV_DMAREQ  12
#define UART5_TRAN_DMAREQ 13
#define I2S0_REV_DMAREQ   14
#define I2S0_TRAN_DMAREQ  15
#define SPI0_REV_DMAREQ   16
#define SPI0_TRAN_DMAREQ  17
#define SPI1_REV_DMAREQ   18
#define SPI1_TRAN_DMAREQ  19
#define SPI2_REV_DMAREQ   20
#define SPI2_TRAN_DMAREQ  21
#define I2C0_DMAREQ       22
#define I2C1_I2C2_DMAREQ  23
#define FTM0_CH0_DMAREQ   24
#define FTM0_CH1_DMAREQ   25
#define FTM0_CH2_DMAREQ   26
#define FTM0_CH3_DMAREQ   27
#define FTM0_CH4_DMAREQ   28
#define FTM0_CH5_DMAREQ   29
#define FTM0_CH6_DMAREQ   30
#define FTM0_CH7_DMAREQ   31
#define FTM1_CH0_DMAREQ   32
#define FTM1_CH1_DMAREQ   33
#define FTM2_CH0_DMAREQ   34
#define FTM2_CH1_DMAREQ   35
#define IEEE_1588_Timers0 36
#define IEEE_1588_Timers1 37
#define IEEE_1588_Timers2 38
#define IEEE_1588_Timers3 39
#define ADC0_DMAREQ       40
#define ADC1_DMAREQ       41
#define CMP0_DMAREQ       42
#define CMP1_DMAREQ       43
#define CMP2_DMAREQ       44
#define DAC0_DMAREQ       45
#define DAC1_DMAREQ       46
#define CMT_DMAREQ        47
#define PDB_DMAREQ        48
#define PORTA_DMAREQ      49
#define PORTB_DMAREQ      50
#define PORTC_DMAREQ      51
#define PORTD_DMAREQ      52
#define PORTE_DMAREQ      53
#define DMA_MUX_54        54
#define DMA_MUX_55        55
#define DMA_MUX_56        56
#define DMA_MUX_57        57
#define DMA_MUX_58        58
#define DMA_MUX_59        59
#define DMA_MUX_60        60
#define DMA_MUX_61        61
#define DMA_MUX_62        62
#define DMA_MUX_63        63
//==========================================================
//  DMA request sources Number--MUX1 channel16 -- channel31
//      �����DMA�����
//==========================================================
#define UART0_REV_DMAREQ  2
#define UART0_TRAN_DMAREQ 3
#define UART1_REV_DMAREQ  4
#define UART1_TRAN_DMAREQ 5
#define UART2_REV_DMAREQ  6
#define UART2_TRAN_DMAREQ 7
#define UART3_REV_DMAREQ  8
#define UART3_TRAN_DMAREQ 9
#define UART4_REV_DMAREQ  10
#define UART4_TRAN_DMAREQ 11
#define UART5_REV_DMAREQ  12
#define UART5_TRAN_DMAREQ 13
#define I2S0_REV_DMAREQ   14
#define I2S0_TRAN_DMAREQ  15
#define SPI0_REV_DMAREQ   16
#define SPI0_TRAN_DMAREQ  17
#define SPI1_REV_DMAREQ   18
#define SPI1_TRAN_DMAREQ  19
#define SPI2_REV_DMAREQ   20
#define SPI2_TRAN_DMAREQ  21
#define FTM3_CH0_DMAREQ   24
#define FTM3_CH1_DMAREQ   25
#define FTM3_CH2_DMAREQ   26
#define FTM3_CH3_DMAREQ   27
#define FTM3_CH4_DMAREQ   28
#define FTM3_CH5_DMAREQ   29
#define FTM3_CH6_DMAREQ   30
#define FTM3_CH7_DMAREQ   31
#define IEEE_1588_Timers0 36
#define IEEE_1588_Timers1 37
#define IEEE_1588_Timers2 38
#define IEEE_1588_Timers3 39
#define ADC0_DMAREQ       40
#define ADC1_DMAREQ       41
#define ADC2_DMAREQ       42
#define ADC3_DMAREQ       43
#define DAC0_DMAREQ       45
#define DAC1_DMAREQ       46
#define CMP0_REQ          47
#define CMP1_REQ          48
#define CMP2_REQ          49
#define CMP3_REQ          50
#define PORTF_DMAREQ      53
#define DMA_MUX_54        54
#define DMA_MUX_55        55
#define DMA_MUX_56        56
#define DMA_MUX_57        57
#define DMA_MUX_58        58
#define DMA_MUX_59        59
#define DMA_MUX_60        60
#define DMA_MUX_61        61
#define DMA_MUX_62        62
#define DMA_MUX_63        63
#endif

//==========================================
//      ����DMAͨ����
//==========================================
#define  DMA_CH0 0
#define  DMA_CH1 1
#define  DMA_CH2 2
#define  DMA_CH3 3
#define  DMA_CH4 4
#define  DMA_CH5 5
#define  DMA_CH6 6
#define  DMA_CH7 7
#define  DMA_CH8 8
#define  DMA_CH9 9
#define  DMA_CH10 10
#define  DMA_CH11 11
#define  DMA_CH12 12
#define  DMA_CH13 13
#define  DMA_CH14 14
#define  DMA_CH15 15
#if defined(CPU_MK60F12) || defined(CPU_MK60F15)
#define  DMA_CH16 16
#define  DMA_CH17 17
#define  DMA_CH18 18
#define  DMA_CH19 19
#define  DMA_CH20 20
#define  DMA_CH21 21
#define  DMA_CH22 22
#define  DMA_CH23 23
#define  DMA_CH24 24
#define  DMA_CH25 25
#define  DMA_CH26 26
#define  DMA_CH27 27
#define  DMA_CH28 28
#define  DMA_CH29 29
#define  DMA_CH30 30
#define  DMA_CH31 31
#endif
//===========================================
//      DMA ��������ݳ���
//      Դ��ַ���ݳ��ȷ�Ϊ��  8bit��16bit��32bit
//      Ŀ�ĵ�ַ���ݳ��ȷ�Ϊ��8bit��16bit��32bit
//===========================================
#define DMA_SRC_8BIT    0
#define DMA_SRC_16BIT   1
#define DMA_SRC_32BIT   2
#define DMA_SRC_16BYTE  4

#define DMA_DST_8BIT    0
#define DMA_DST_16BIT   1
#define DMA_DST_32BIT   2
#define DMA_DST_16BYTE  4


typedef struct 
{
  /*
    ������
      ѡ��DMAͨ��
    ȡֵ��
      DMA_CH0~DMA_CH15
    <ע:ֻ��MK60Fϵ�к���DMA_CH16~DMA_CH31>
    ��ʼ����
      �����ʼ��
  */
  uint8  DMA_CHx;  
  
  /*
    ������
      ѡ��DMAͨ����Ӧ������Դ
    ȡֵ��
      ����ҳ"DMA request sources Number"�궨��
    ��ʼ����
      �����ʼ��
  */
  uint8  DMA_Req; 
  
  /*
    ������
      �Ƿ�ʹ��DMA�����ڴ�������
    ȡֵ��
      TRUE-ʹ�����ڴ���
      FALSE-�������ڴ���
    ��ʼ����
      �������ʼ����Ĭ��FALSE
  */
  boolean DMA_PeriodicTriggerEnable;
  
  /*
    ������
      ������ѭ������
    ȡֵ��
      15λ�޷������ͣ�0~0x7FFF��
    ��ʼ����
      �����ʼ��
  */
  uint16 DMA_MajorLoopCnt;
  
  /*
    ������
      ���ô�ѭ�������ֽ���
    ȡֵ��
      0~0xFFFFFFFF-32λ�޷�������
    ��ʼ����
      �����ʼ��
  */
  uint32 DMA_MinorByteCnt;   
    
  /*
    ������
      ����Դ���ݵ�ַ
    ȡֵ��
      32λ��ַ��0~0xFFFFFFFF��
    ��ʼ����
      �����ʼ��
  */  
  uint32 DMA_SourceAddr;
    
  /*
    ������
      ����Դ���ݴ�С
    ȡֵ��
      DMA_SRC_8BIT-8λ����
      DMA_SRC_16BIT-16λ����
      DMA_SRC_32BIT-32λ����
      DMA_SRC_16BYTE-16�ֽ�����
    ��ʼ����
      �������ʼ����Ĭ��DMA_SRC_8BIT
  */
  uint8 DMA_SourceDataSize;
  
  /*
    ������
      ����Դ���ݵ�ַƫ�ƣ������ϴζ�ȡ��Դ��ַ��ƫ����
    ȡֵ��
      16λ�з������ͣ�-32768~32767��
    ��ʼ����
      �������ʼ����Ĭ��0
  */ 
  int16 DMA_SourceAddrOffset;
  
  /*
    ������
      ����Դ���ݵ�ַ����ѭ����ɺ�ĵ�����
    ȡֵ��
      32λ�з�������
    ��ʼ����
      �������ʼ����Ĭ��0
  */ 
  int32 DMA_LastSourceAddrAdj;  
    
  /*
    ������
      ����Ŀ�����ݵ�ַ
    ȡֵ��
      32λ��ַ��0~0xFFFFFFFF��
    ��ʼ����
      �����ʼ��
  */  
  uint32 DMA_DestAddr;
    
  /*
    ������
      ����Ŀ�����ݴ�С
    ȡֵ��
      DMA_DST_8BIT-8λ����
      DMA_DST_16BIT-16λ����
      DMA_DST_32BIT-32λ����
      DMA_DST_16BYTE-16�ֽ�����
    ��ʼ����
      �������ʼ����Ĭ��DMA_DST_8BIT
  */
  uint8 DMA_DestDataSize;
  
  /*
    ������
      ����Ŀ�����ݵ�ַƫ�ƣ������ϴ�д���Ŀ�ĵ�ַ��ƫ����
    ȡֵ��
      16λ�з������ͣ�-32768~32767��
    ��ʼ����
      �������ʼ����Ĭ��0
  */ 
  int16 DMA_DestAddrOffset;
  
  /*
    ������
      ����Ŀ�����ݵ�ַ����ѭ����ɺ�ĵ�����
    ȡֵ��
      32λ�з�������
    ��ʼ����
      �������ʼ����Ĭ��0
  */ 
  int32 DMA_LastDestAddrAdj;
  
  /*
    ������
      ʹ���Զ���������ʹ�ܺ�ͨ����������ѭ�����������
    ȡֵ��
      TRUE-ʹ���Զ���������
      FALSE-�����Զ���������
    ��ʼ����
      �������ʼ����Ĭ��FALSE
  */
  boolean DMA_AutoDisableReq;
  
  /*
    ������
      ʹ��DMA��ѭ������ж�
    ȡֵ��
      TRUE-ʹ��
      FALSE-����
    ��ʼ����
      �������ʼ����Ĭ��FALSE
  */
  boolean DMA_MajorCompleteIntEnable;
  
  /*
    ������
      ʹ��DMA��ѭ����ɵ�һ���ж�
    ȡֵ��
      TRUE-ʹ��
      FALSE-����
    ��ʼ����
      �������ʼ����Ĭ��FALSE
  */
  boolean DMA_MajorHalfCompleteIntEnable;
    
  /*
    ������
      DMA�жϻص�����
    ȡֵ��
      ��������Ϊ�޷���ֵ,�޲���(eg. void isr(void);)
    ��ʼ����
      �������ʼ������δ��ʼ���򲻻ᴥ���ж�
  */
  DMA_ISR_CALLBACK DMA_Isr; 
   
}DMA_InitTypeDef;

//ʹ��ͨ��x��DMA����
#define LPLD_DMA_EnableReq(CHX)  (DMA0->ERQ|=(1<<CHX))
//����ͨ��x��DMA����
#define LPLD_DMA_DisableReq(CHX) (DMA0->ERQ&=~(1<<CHX))
//����Դ��ַ
#define LPLD_DMA_LoadSrcAddr(CHX, ADDR)   (DMA0->TCD[CHX].SADDR=DMA_SADDR_SADDR(ADDR))
//����Ŀ�ĵ�ַ
#define LPLD_DMA_LoadDstAddr(CHX, ADDR)   (DMA0->TCD[CHX].DADDR=DMA_DADDR_DADDR(ADDR))

//��ʼ��eDMAģ��
uint8 LPLD_DMA_Init(DMA_InitTypeDef);
//ʹ��eDMA�ж�
uint8 LPLD_DMA_EnableIrq(DMA_InitTypeDef);
//����eDMA�ж�
uint8 LPLD_DMA_DisableIrq(DMA_InitTypeDef);
//DMA�������������ʼ
void LPLD_DMA_SoftwareStartService(DMA_InitTypeDef);

#endif /* __HW_DMA_H__ */