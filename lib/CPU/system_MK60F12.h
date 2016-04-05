/**
 * @file system_MK60F12.h
 * @version 1.2.1[By LPLD]
 * @date 2013-06-18
 * @brief MK60F12ϵ�е�Ƭ��ϵͳ�����ļ�
 *
 * ���Ľ���:��ֹ�޸�
 *
 * �ô����ṩϵͳ���ú����Լ�һ������ϵͳ��Ƶ��ȫ�ֱ�����
 * ���ú�����Ҫ������ϵͳ��ģ���ʱ�ӡ�
 * ���뻹ʵ�ֳ�����ϵͳ�жϺ�����
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

#ifndef SYSTEM_MK60F12_H_
#define SYSTEM_MK60F12_H_                   

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
  
/**
 * @brief ϵͳ��Ƶ����λHz��
 */
extern uint32_t SystemCoreClock;

/**
 * ��ʼ��ϵͳ
 *
 * @param  none
 * @return none
 *
 * @brief  ��ʼ��MCUӲ��ϵͳ����������IOʱ�ӡ���ʼ����Ƶ����ʼ�����Դ��ڣ�
 *         ��ӡ������Ϣ��SystemInit��MCU�����ļ����á�
 *         
 */
extern void SystemInit (void);

/**
 * ����SystemCoreClock
 *
 * @param  none
 * @return none
 *
 * @brief  ����ȫ�ֱ���SystemCoreClock��ֵ���Ա��ȡ���µ�ϵͳ�ں�Ƶ�ʡ�
 *         
 */
void SystemCoreClockUpdate (void);

/**
 * Ӳ�������жϺ���
 *
 * @param  none
 * @return none
 *
 * @brief  �������жϵ�ԭ��һ��Ϊ��ģ��ʹ��δ��ʼ���������Ѱַ�ռ�ȡ�
 *         
 */
void HardFault_Handler (void);

/**
 * Ĭ���жϺ���
 *
 * @param  none
 * @return none
 *
 * @brief  δ�����жϴ��������ж�Դ�����˺���������ӡ�ж������š�
 *         
 */
void DefaultISR (void);

/**
 * ��ʼ������ϵͳ�ĵδ�ʱ��(OS Tick)
 *
 * @param  none
 * @return none
 *
 * @brief  �ú�������uC/OS��ϵͳ�е��ã��б�����OSStart()�ʹ�������ʼ�������
 *         
 */
#if UCOS_II > 0u
extern void SystemTickInit (void);
#endif

#ifdef __cplusplus
}
#endif

#endif  /* #if !defined(SYSTEM_MK60F12_H_) */
