/**
 * @file DEV_MMA7660.h
 * @version 0.1[By LPLD]
 * @date 2013-09-24
 * @brief MMA7660������ٶȴ������豸��������
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
#ifndef __DEV_MMA7660_H__
#define __DEV_MMA7660_H__

#include "common.h"
#include "HW_I2C.h"

/********�û����޸�ֵ ��ʼ***********/
//����MMA7660�õ���I2Cͨ��
#define MMA7660_I2CX    (I2C0)

//����MMA7660�õ���SCL����
#define MMA7660_SCLPIN  (PTD8)

//����MMA7660�õ���SDA����
#define MMA7660_SDAPIN  (PTD9)
/********�û����޸�ֵ ����***********/

//==========MMA7660 �Ĵ�����ַ==================//
#define MMA7660_XOUT  0x00   // 6-bit output value X 
#define MMA7660_YOUT  0x01   // 6-bit output value Y 
#define MMA7660_ZOUT  0x02   // 6-bit output value Z
#define MMA7660_TILT  0x03   // Tilt Status 
#define MMA7660_SRST  0x04   // Sampling Rate Status
#define MMA7660_SPCNT 0x05   // Sleep Count
#define MMA7660_INTSU 0x06   // Interrupt Setup
#define MMA7660_MODE  0x07   // Mode
#define MMA7660_SR    0x08   // Auto-Wake/Sleep and 
                      // Portrait/Landscape samples 
                      // per seconds and Debounce Filter
#define MMA7660_PDET  0x09   // Tap Detection
#define MMA7660_PD    0x0A   // Tap Debounce Count
//=========MMA7660 ���ܲ���==================//
#define MMA7660_DEV_ADDR   0x4C //Normally,can range 0x08 to 0xEF
#define MMA7660_DEV_WRITE  MMA7660_DEV_ADDR<<1 | 0x00
#define MMA7660_DEV_READ   MMA7660_DEV_ADDR<<1 | 0x01

//����SCL Bus Speedȡֵ����������Ϊ50Mhzʱ�ļ�����
#define MMA7660_SCL_50KHZ                   (0x33) 
#define MMA7660_SCL_100KHZ                  (0x2B)  
#define MMA7660_SCL_150KHZ                  (0x28)
#define MMA7660_SCL_200KHZ                  (0x23)
#define MMA7660_SCL_250KHZ                  (0x21)
#define MMA7660_SCL_300KHZ                  (0x20)
#define MMA7660_SCL_400KHZ                  (0x17)  

//��������
void LPLD_MMA7660_Init(void);
void LPLD_MMA7660_WriteReg(uint8, uint8);
uint8 LPLD_MMA7660_ReadReg(uint8);
int8 LPLD_MMA7660_GetResult(uint8);

#endif 