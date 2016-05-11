/**
 * @file HW_NVIC.h
 * @version 3.02[By LPLD]
 * @date 2013-11-29
 * @brief �ں�NVICģ����غ���
 *
 * ���Ľ���:�������޸�
 *
 * ��Ȩ����:�����������µ���Ӧʽ�������޹�˾
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

#ifndef __HW_NVIC_H__
#define __HW_NVIC_H__

#include "common.h"


//����NVIC�жϷ���
#define NVIC_PriorityGroup_0         ((uint32_t)0x07) /*!< 0 bits for pre-emption priority
                                                            4 bits for subpriority */
#define NVIC_PriorityGroup_1         ((uint32_t)0x06) /*!< 1 bits for pre-emption priority
                                                            3 bits for subpriority */
#define NVIC_PriorityGroup_2         ((uint32_t)0x05) /*!< 2 bits for pre-emption priority
                                                            2 bits for subpriority */
#define NVIC_PriorityGroup_3         ((uint32_t)0x04) /*!< 3 bits for pre-emption priority
                                                            1 bits for subpriority */
#define NVIC_PriorityGroup_4         ((uint32_t)0x03) /*!< 4 bits for pre-emption priority
                                                            0 bits for subpriority */
//���Ա����Ƿ����
#define IS_NVIC_PRIORITY_GROUP(GROUP) (((GROUP) == NVIC_PriorityGroup_0) || \
                                       ((GROUP) == NVIC_PriorityGroup_1) || \
                                       ((GROUP) == NVIC_PriorityGroup_2) || \
                                       ((GROUP) == NVIC_PriorityGroup_3) || \
                                       ((GROUP) == NVIC_PriorityGroup_4))

#define IS_NVIC_PREEMPTION_PRIORITY(PRIORITY)  ((PRIORITY) < 0x10)

#define IS_NVIC_SUB_PRIORITY(PRIORITY)  ((PRIORITY) < 0x10)

typedef struct
{
  /*
    ������
      �ж�IRQn_Type�ţ�����MK60DZ10.h�в鵽
    ȡֵ��
      ��ö��IRQn_Type�ж������жϺţ�ѡȡ��Ӧͨ����IRQn_Type��
    ��ʼ����
      �����ʼ��
  */
  IRQn_Type  NVIC_IRQChannel; 
  
  /*
    ������
      NVIC �жϷ���
    ȡֵ��
      NVIC_PriorityGroup_0
        û����ռʽ���ȼ���NVIC_IRQChannelPreemptionPriority = 0�������16����Ӧʽ���ȼ���NVIC_IRQChannelSubPriority��
      NVIC_PriorityGroup_1
        ���2����ռʽ���ȼ���NVIC_IRQChannelPreemptionPriority�� �����8����Ӧʽ���ȼ���NVIC_IRQChannelSubPriority��
        ���У���ռʽ���ȼ�0 ���ȼ����� ��ռʽ���ȼ�1��
      NVIC_PriorityGroup_2
        ���4����ռʽ���ȼ���NVIC_IRQChannelPreemptionPriority�� �����4����Ӧʽ���ȼ���NVIC_IRQChannelSubPriority��
      NVIC_PriorityGroup_3
        ���8����ռʽ���ȼ���NVIC_IRQChannelPreemptionPriority�� �����2����Ӧʽ���ȼ���NVIC_IRQChannelSubPriority��
      NVIC_PriorityGroup_4
        ���16����ռʽ���ȼ���NVIC_IRQChannelPreemptionPriority����û����Ӧʽ���ȼ���NVIC_IRQChannelSubPriority = 0��
    ��ʼ����
      �����ʼ��
  */  
  uint32  NVIC_IRQChannelGroupPriority;
  
  /*
    ������
      NVIC��ռʽ���ȼ��������жϷ����е��������趨
    ȡֵ��
      ���15,ȡֵ��ʽ��NVIC �жϷ�������
    ��ʼ����
      �����ʼ��
  */                                                   
  uint32  NVIC_IRQChannelPreemptionPriority; 
  
  /*
    ������
      NVIC��Ӧʽ���ȼ��������жϷ����е��������趨
    ȡֵ��
      ���15,ȡֵ��ʽ��NVIC �жϷ�������
    ��ʼ����
      �����ʼ��
   */    
  uint32  NVIC_IRQChannelSubPriority;  
  
  /*
    ������
      ��NVIC��ʹ�ܻ��߽�ֹIRQn_Typeͨ��
      �ù��ܿ�����LPLD_XXX_EnableIRQ��������LPLD_XXX_DisableIRQ������ʵ��
    ȡֵ��
      TRUE  ʹ��
      FALSE ��ֹ
    ��ʼ����
      Ĭ�Ͻ�ֹ
   */  
  boolean NVIC_IRQChannelEnable;      
  
} NVIC_InitTypeDef;
//NVIC ��ʼ������
uint8 LPLD_NVIC_Init(NVIC_InitTypeDef );
#endif