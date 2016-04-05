/**
 * @file HW_DAC.h
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
#ifndef __HW_DAC_H__
#define __HW_DAC_H__
/********************************************************************/

//DACģ���жϻص���������
typedef void (*DAC_ISR_CALLBACK)(void);

//����������ģʽ����
#define BUFFER_MODE_NORMAL      0x00 //����������ģʽ
#define BUFFER_MODE_SWING       0x01 //������SWINGģʽ
#define BUFFER_MODE_ONETIMESCAN 0x02 //������ONETIMESCANģʽ
//������ˮӡѡ����
#define WATERMARK_1WORD         0x00 //1����
#define WATERMARK_2WORDS        0x01 //2����
#define WATERMARK_3WORDS        0x02 //3����
#define WATERMARK_4WORDS        0x03 //4����

//DACģ���ʼ���ṹ�壬��������DAC�������
typedef struct 
{   
  /*
    ������
      ѡ��DACx
    ȡֵ��
      DAC0��DAC1
    ��ʼ����
      �����ʼ��
  */
  DAC_Type *DAC_Dacx;
    
  /*
    ������
      ʹ�ܻ���������
    ȡֵ��
      TRUE-ʹ�ܻ���������
      FALSE-���û�����
    ��ʼ����
      �������ʼ����Ĭ��FALSE
  */  
  boolean DAC_BufferEnable;
    
  /*
    ������
      ����������ģʽѡ��ֻ��DAC_BufferEnableΪTRUEʱ��Ч
    ȡֵ��
      BUFFER_MODE_NORMAL-��ͨģʽ��ָ�뵽�����޺���0
      BUFFER_MODE_SWING-�ڶ�ģʽ��ָ�뵽�����޺��ٵݼ��ص�0
      BUFFER_MODE_ONETIMESCAN-����ɨ��ģʽ��ָ�뵽�����޺�ֹͣ
    ��ʼ����
      �������ʼ����Ĭ��BUFFER_MODE_NORMAL
  */
  uint8 DAC_BufferWorkMode;
    
  /*
    ������
      ������ˮӡѡ��ֻ��DAC_BufferEnableΪTRUEʱ��Ч��
      ��DAC_BufferWatermarkIntEnableΪTRUEʱ�����ж�����
    ȡֵ��
      WATERMARK_1WORD-ˮӡ���뻺��������1����
      WATERMARK_2WORDS-ˮӡ���뻺��������2����
      WATERMARK_3WORDS-ˮӡ���뻺��������3����
      WATERMARK_4WORDS-ˮӡ���뻺��������4����
    ��ʼ����
      �������ʼ����Ĭ��WATERMARK_1WORD
  */
  uint8 DAC_BufferWatermarkSel;
    
  /*
    ������
      ʹ��DMA
    ȡֵ��
      TRUE-ʹ��DMA
      FALSE-����DMA
    ��ʼ����
      �������ʼ����Ĭ��FALSE
  */ 
  boolean DAC_DmaEnable;
    
  /*
    ������
      ������������ֵ��ֻ��DAC_BufferEnableΪTRUEʱ��Ч
    ȡֵ��
      1~16
    ��ʼ����
      �������ʼ����Ĭ��1
  */
  uint8 DAC_BufferUpperLimit;
    
  /*
    ������
      ʹ�����������ֻ��DAC_BufferEnableΪTRUEʱ��Ч
    ȡֵ��
      TRUE-ʹ���������
      FALSE-�����������
    ��ʼ����
      �������ʼ����Ĭ��FALSE
  */ 
  boolean DAC_SoftTrgEnable;
    
  /*
    ������
      ʹ�ܶ�ָ��ײ��ж�ʹ��,ʹ�ܺ�ָ�뵽�����޺�����ж�����
    ȡֵ��
      TRUE-ʹ��
      FALSE-����
    ��ʼ����
      �������ʼ����Ĭ��FALSE
  */
  boolean DAC_ReadPointerBottomIntEnable;
    
  /*
    ������
      ʹ�ܶ�ָ�붥���ж�ʹ��,ʹ�ܺ�ָ�����0������ж�����
    ȡֵ��
      TRUE-ʹ��
      FALSE-����
    ��ʼ����
      �������ʼ����Ĭ��FALSE
  */
  boolean DAC_ReadPointerTopIntEnable;
    
  /*
    ������
      ʹ�ܻ�����ˮӡ�ж�ʹ��,ʹ�ܺ�ָ�뵽��ˮӡλ�ú�����ж�����
    ȡֵ��
      TRUE-ʹ��
      FALSE-����
    ��ʼ����
      �������ʼ����Ĭ��FALSE
  */
  boolean DAC_BufferWatermarkIntEnable;
    
  /*
    ������
      �ײ��жϻص�����
    ȡֵ��
      ��������Ϊ�޷���ֵ,�޲���(eg. void isr(void);)
    ��ʼ����
      �������ʼ������δ��ʼ���򲻻ᴥ���ж�
  */
  DAC_ISR_CALLBACK DAC_ReadPointerBottomIsr; 
    
  /*
    ������
      �����жϻص�����
    ȡֵ��
      ��������Ϊ�޷���ֵ,�޲���(eg. void isr(void);)
    ��ʼ����
      �������ʼ������δ��ʼ���򲻻ᴥ���ж�
  */
  DAC_ISR_CALLBACK DAC_ReadPointerTopIsr; 
    
  /*
    ������
      ˮӡ�жϻص�����
    ȡֵ��
      ��������Ϊ�޷���ֵ,�޲���(eg. void isr(void);)
    ��ʼ����
      �������ʼ������δ��ʼ���򲻻ᴥ���ж�
  */
  DAC_ISR_CALLBACK DAC_BufferWatermarkIsr; 
  
}DAC_InitTypeDef;

//DAC��ʼ��������ʹ��DAC�����
uint8 LPLD_DAC_Init(DAC_InitTypeDef);
//DAC����ʼ������������DACģ��
uint8 LPLD_DAC_Deinit(DAC_InitTypeDef);
//ʹ��DACx�ж�
uint8 LPLD_DAC_EnableIrq(DAC_InitTypeDef);
//����DACx�ж�
uint8 LPLD_DAC_DisableIrq(DAC_InitTypeDef);
//����DAC��������������n
void LPLD_DAC_SetBufferDataN(DAC_Type *, uint16, uint8);
//����DAC��������������
void LPLD_DAC_SetBufferData(DAC_Type *, uint16 *, uint8);
//�������DAC����������
void LPLD_DAC_SoftwareTrigger(DAC_Type *);

#endif /* __HW_DAC_H__ */