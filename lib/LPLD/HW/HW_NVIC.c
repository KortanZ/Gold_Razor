/**
 * @file HW_NVIC.c
 * @version 3.02[By LPLD]
 * @date 2013-11-29
 * @brief �ں�NVICģ����غ���
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
#include "HW_NVIC.h"

/*
 * LPLD_NVIC_Init
 *
 * �ڸú���������IRQn_Typeͨ�����ȼ�����������Ҫ��NVIC��ʹ��IRQn_Type
 * �ں����е�����core_m4.h�е�NVIC��������M4�ں˵�16���ж����ȼ�
 * 16���ж����ȼ�ͨ���������ʽ���й�����NVIC�е����ȼ���Ϊ5�飬NVIC_PriorityGroup_0 -- 5
 * ÿ�������ռʽ���ȼ���NVIC_IRQChannelPreemptionPriority������Ӧʽ���ȼ���NVIC_IRQChannelSubPriority��
 *
 * ���ȼ��ٲ�:
 * >1 PreemptionPriority���ȼ��ߵĲ�����ռPreemptionPriority���ȼ��͵��ж��쳣;
 * (��NVIC_IRQChannelPreemptionPriorityֵԽС���ȼ�Խ��);
 * >2 PreemptionPriority���ȼ���ͬ���ж��쳣֮�䲻���໥��ռ;
 * >3 ���PreemptionPriority���ȼ���ȣ��ٱȽ�SubPriority��Ӧ���ȼ���SubPriority��Ӧ���ȼ�ֵԽС�ж����ȼ�Խ��;
 *
 * NVIC�е����ȼ����黮�ּ�NVIC_InitTypeDef�е�NVIC �жϷ���
 * 
 * ����:
 *    NVIC_InitStructure--NVIC��ʼ���ṹ�壬
 *                        ���嶨���NVIC_InitTypeDef
 * ���:
 *    0:����ʧ��
 *    1:���óɹ�
 *
*/
uint8 LPLD_NVIC_Init(NVIC_InitTypeDef NVIC_InitStructure)
{
  uint8  request = 1;
  IRQn_Type int_id = NVIC_InitStructure.NVIC_IRQChannel;
  uint32 nvic_priority_group = NVIC_InitStructure.NVIC_IRQChannelGroupPriority; 
  uint32 nvic_preemption_priority = NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority;
  uint32 nvic_sub_priority = NVIC_InitStructure.NVIC_IRQChannelSubPriority;
  boolean status = NVIC_InitStructure.NVIC_IRQChannelEnable;
  uint32 temp;
  //�������
  ASSERT(IS_NVIC_PRIORITY_GROUP(nvic_priority_group));
  ASSERT(IS_NVIC_PREEMPTION_PRIORITY(nvic_preemption_priority));
  ASSERT(IS_NVIC_SUB_PRIORITY(nvic_sub_priority));
  //���� NVIC�жϷ��� ������ռ���ȼ�
  switch(nvic_priority_group)
  {
      case NVIC_PriorityGroup_0: NVIC_SetPriorityGrouping(NVIC_PriorityGroup_0);
              if(nvic_preemption_priority > 0 || nvic_sub_priority >15)
                request = 0;
              break;
      case NVIC_PriorityGroup_1: NVIC_SetPriorityGrouping(NVIC_PriorityGroup_1);
              if(nvic_preemption_priority > 1 || nvic_sub_priority >7)
                request = 0;
              break;
      case NVIC_PriorityGroup_2: NVIC_SetPriorityGrouping(NVIC_PriorityGroup_2);
              if(nvic_preemption_priority > 3 || nvic_sub_priority >3)
                request = 0;
              break;
      case NVIC_PriorityGroup_3: NVIC_SetPriorityGrouping(NVIC_PriorityGroup_3);
              if(nvic_preemption_priority > 7 || nvic_sub_priority >1)
                request = 0;
              break;
      case NVIC_PriorityGroup_4: NVIC_SetPriorityGrouping(NVIC_PriorityGroup_4);
              if(nvic_preemption_priority > 15 || nvic_sub_priority >0)
                request = 0;
              break;
      default:return 0;
  }
  //�����жϷ���ռ�����ж���ռ���ȼ�
  //�����жϷ���ռ�����ж���Ӧ���ȼ�
  temp = NVIC_EncodePriority(nvic_priority_group,\
                             nvic_preemption_priority,\
                             nvic_sub_priority);
  //�����ж�������,����M4�ں�������NVIC���ȼ�
  NVIC_SetPriority(int_id,temp);
  
  if(status == TRUE)
  {
    NVIC_EnableIRQ(int_id);
  }
  else
  {
    NVIC_DisableIRQ(int_id);
  }
  return request;
}
