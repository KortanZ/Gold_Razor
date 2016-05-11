/**
 * @file DEV_SCCB.h
 * @version 0.1[By LPLD]
 * @date 2013-09-24
 * @brief SCCB�豸��������
 *
 * ���Ľ���:�ɸ���ʵ��Ӳ���޸�
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
#ifndef __DEV_SCCB_H__
#define __DEV_SCCB_H__

#include "common.h"

#define ADR_OV7670      0x42

/********�û����޸�ֵ ��ʼ***********/
//����SCCB�豸��ַ
#define SCCB_DEV_ADR    ADR_OV7670
//����SCL��SDA������
#define SCCB_SCL        PTA26_O
#define SCCB_SDA_O      PTA25_O
#define SCCB_SDA_I      PTA25_I
//����SDA�������
#define SCCB_SDA_OUT()  DDRA25=1
#define SCCB_SDA_IN()   DDRA25=0
/********�û����޸�ֵ ����***********/

#define SCCB_DELAY()	LPLD_SCCB_Delay(5000)

extern void LPLD_SCCB_Init(void);
extern uint8 LPLD_SCCB_WriteReg(uint16, uint8);
extern uint8 LPLD_SCCB_ReadReg(uint8, uint8*, uint16);

#endif
