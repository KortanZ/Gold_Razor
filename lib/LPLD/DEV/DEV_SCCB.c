/**
* @file DEV_SCCB.c
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
#include "DEV_SCCB.h"

static uint8 LPLD_SCCB_Start(void);
static void LPLD_SCCB_Stop(void);
static void LPLD_SCCB_Ack(void);
static void LPLD_SCCB_NoAck(void);
static uint8 LPLD_SCCB_WaitAck(void);
static void LPLD_SCCB_SendByte(uint8);
static uint8 LPLD_SCCB_ReceiveByte(void);
static void LPLD_SCCB_Delay(uint16);

/*
 * LPLD_SCCB_Init
 * ��ʼ��SCCB��������
 */
void LPLD_SCCB_Init(void)
{
  GPIO_InitTypeDef pta;
  /********�û����޸�ֵ ��ʼ***********/
  pta.GPIO_PTx = PTA;
  pta.GPIO_Pins = GPIO_Pin25 | GPIO_Pin26;
  /********�û����޸�ֵ ����***********/
  pta.GPIO_Dir = DIR_OUTPUT;
  pta.GPIO_Output = OUTPUT_H;
  pta.GPIO_PinControl = NULL;
  LPLD_GPIO_Init(pta);
}

/*
 * LPLD_SCCB_WriteReg
 * дSCCB�豸�Ĵ���
 *
 * ����:
 *    reg_addr--�Ĵ�����ַ
 *    data--��д����
 *
 * ���:
 *    1-�ɹ�
 *    0-ʧ��
 */
uint8 LPLD_SCCB_WriteReg(uint16 reg_addr , uint8 data)
{
  if(!LPLD_SCCB_Start())
  {
    return 0;
  }
  LPLD_SCCB_SendByte( SCCB_DEV_ADR );
  if( !LPLD_SCCB_WaitAck() )
  {
    LPLD_SCCB_Stop();
    return 0;
  }
  LPLD_SCCB_SendByte((uint8)(reg_addr & 0x00FF));
  LPLD_SCCB_WaitAck();
  LPLD_SCCB_SendByte(data);
  LPLD_SCCB_WaitAck();
  LPLD_SCCB_Stop();
  return 1;
}




/******************************************************************************************************************
* ��������SCCB_ReadByte
* ����  ����ȡһ������
* ����  ��- data: ��Ŷ������� 	- length: ����������	- reg_addr: ��������ַ		 - DeviceAddress: ��������
* ���  ������Ϊ:=1�ɹ�����,=0ʧ��
* ע��  ����
**********************************************************************************************************************/
/*
 * LPLD_SCCB_ReadReg
 * ��SCCB�豸�Ĵ���
 *
 * ����:
 *    reg_addr--�Ĵ�����ַ
 *    *data--����������ݵ�ַ
 *    length--��ȡ����
 *
 * ���:
 *    1-�ɹ�
 *    0-ʧ��
 */
uint8 LPLD_SCCB_ReadReg(uint8 reg_addr, uint8* data, uint16 length)
{
  if(!LPLD_SCCB_Start())
  {
    return 0;
  }
  LPLD_SCCB_SendByte( SCCB_DEV_ADR );
  if( !LPLD_SCCB_WaitAck() )
  {
    LPLD_SCCB_Stop();
    return 0;
  }
  LPLD_SCCB_SendByte( reg_addr );
  LPLD_SCCB_WaitAck();
  LPLD_SCCB_Stop();

  if(!LPLD_SCCB_Start())
  {
    return 0;
  }
  LPLD_SCCB_SendByte( SCCB_DEV_ADR + 1 );
  if(!LPLD_SCCB_WaitAck())
  {
    LPLD_SCCB_Stop();
    return 0;
  }
  while(length)
  {
    *data = LPLD_SCCB_ReceiveByte();
    if(length == 1)
    {
      LPLD_SCCB_NoAck();
    }
    else
    {
      LPLD_SCCB_Ack();
    }
    data++;
    length--;
  }
  LPLD_SCCB_Stop();
  return 1;
}

/*
 * LPLD_SCCB_Start
 * SCCB��ʼ�źţ��ڲ�����
 */
static uint8 LPLD_SCCB_Start(void)
{
  SCCB_SDA_O=1;
  SCCB_SCL=1;
  SCCB_DELAY();

  SCCB_SDA_IN();
  if(!SCCB_SDA_I)
  {
    SCCB_SDA_OUT();
    return 0;
  }
  SCCB_SDA_OUT();
  SCCB_SDA_O=0;

  SCCB_DELAY();

  SCCB_SDA_IN();
  if(SCCB_SDA_I)
  {
    SCCB_SDA_OUT();
    return 0;
  }
  SCCB_SDA_OUT();
  SCCB_SDA_O=0;

  return 1;
}

/*
 * LPLD_SCCB_Stop
 * SCCBֹͣ�źţ��ڲ�����
 */
static void LPLD_SCCB_Stop(void)
{
  SCCB_SCL=0;
  SCCB_SDA_O=0;
  SCCB_DELAY();

  SCCB_SCL=1;
  SCCB_SDA_O=1;
  SCCB_DELAY();
}

/*
 * LPLD_SCCB_Stop
 * SCCBӦ���źţ��ڲ�����
 */
static void LPLD_SCCB_Ack(void)
{
  SCCB_SCL=0;
  SCCB_DELAY();

  SCCB_SDA_O=0;
  SCCB_DELAY();

  SCCB_SCL=1;
  SCCB_DELAY();

  SCCB_SCL=0;
  SCCB_DELAY();
}

/*
 * LPLD_SCCB_NoAck
 * SCCB��Ӧ���źţ��ڲ�����
 */
static void LPLD_SCCB_NoAck(void)
{
  SCCB_SCL=0;
  SCCB_DELAY();
  SCCB_SDA_O=1;
  SCCB_DELAY();
  SCCB_SCL=1;
  SCCB_DELAY();
  SCCB_SCL=0;
  SCCB_DELAY();
}

/*
 * LPLD_SCCB_WaitAck
 * SCCB�ȴ�Ӧ���źţ��ڲ�����
 */
static uint8 LPLD_SCCB_WaitAck(void)
{
  SCCB_SCL=0;
  SCCB_DELAY();
  SCCB_SDA_O=1;
  SCCB_DELAY();

  SCCB_SCL=1;

  SCCB_SDA_IN();
  SCCB_DELAY();

  if(SCCB_SDA_I)
  {
    SCCB_SDA_OUT();
    SCCB_SCL=0;
    return 0;
  }
  SCCB_SDA_OUT();
  SCCB_SCL=0;
  return 1;
}

/*
 * LPLD_SCCB_SendByte
 * SCCB�������ݣ��ڲ�����
 */
static void LPLD_SCCB_SendByte(uint8 data)
{
  uint8 i=8;
  while(i--)
  {
    SCCB_SCL=0;
    SCCB_DELAY();
    if(data&0x80)
    {
      SCCB_SDA_O=1;
    }
    else
    {
      SCCB_SDA_O=0;
    }
    data<<=1;
    SCCB_DELAY();
    SCCB_SCL=1;
    SCCB_DELAY();
  }
  SCCB_SCL=0;
}

/*
 * LPLD_SCCB_SendByte
 * SCCB�������ݣ��ڲ�����
 */
static uint8 LPLD_SCCB_ReceiveByte(void)
{
  uint8 i=8;
  uint8 ReceiveByte=0;

  SCCB_SDA_O=1;
  SCCB_DELAY();

  SCCB_SDA_IN();

  while(i--)
  {
    ReceiveByte<<=1;
    SCCB_SCL=0;
    SCCB_DELAY();

    SCCB_SCL=1;
    SCCB_DELAY();

    if(SCCB_SDA_I)
    {
      ReceiveByte|=0x01;
    }

  }
  SCCB_SDA_OUT();
  SCCB_SCL=0;

  return ReceiveByte;
}

/*
 * LPLD_SCCB_SendByte
 * SCCB��ʱ�������ڲ�����
 */
static void LPLD_SCCB_Delay(uint16 i)
{
  while(i)
    i--;
}


