/**
 * @file HW_MCG.h
 * @version 3.0[By LPLD]
 * @date 2013-06-18
 * @brief MCG�ײ�ģ����غ���
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
#ifndef __HW_MCG_H__
#define __HW_MCG_H__

#include "common.h"
   

typedef enum PllOptionEnum
{
  PLL_48=48u,    //���ʹ��USBģ�飬����ѡ��48�ı�����Ƶ
  PLL_50=50u,
  PLL_96=96u,    //���ʹ��USBģ�飬����ѡ��48�ı�����Ƶ
  PLL_100=100u,  //100MHz��MK60D(Z)10�Ķ�����Ƶ�������Ϸ�˼�����ɲ��ʱ� 
  PLL_120=120u,  //120MHz��MK60F12�Ķ�����Ƶ
  PLL_150=150u,  //150MHz��MK60F15�Ķ�����Ƶ
  PLL_180=180u,
  PLL_200=200u   //�������200�����Ⱥ����������˱�����>_>
  //����200Mhz���ں�Ƶ�ʲ�����ʹ�ã�MK60�����˼嵰��ˮƽ^_^ 
} PllOptionEnum_Type;

//��ʼ���ں�ʱ�Ӽ�����ϵͳʱ��
extern uint8 LPLD_PLL_Setup(PllOptionEnum_Type);
//����ϵͳʱ�ӷ�Ƶ
RAMFUNC void LPLD_Set_SYS_DIV(uint32 outdiv1, uint32 outdiv2, uint32 outdiv3, uint32 outdiv4);
   

extern uint32 g_core_clock;
extern uint32 g_bus_clock;
extern uint32 g_flash_clock;
extern uint32 g_flexbus_clock;   


#endif /* __HW_MCG_H__ */