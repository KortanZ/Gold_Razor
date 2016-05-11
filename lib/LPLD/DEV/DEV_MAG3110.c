/**
 * @file DEV_MAG3110.c
 * @version 0.2[By LPLD]
 * @date 2013-10-3
 * @brief MAG3110����شŴ������豸��������
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
#include "DEV_MAG3110.h"

static void MAG3110_Delay(void);

/*
 *   LPLD_MAG3110_Init
 *   ��ʼ��MAG3110��������ʼ��3110�����I2C�ӿ��Լ�3110�ļĴ���
 *
 *   ������
 *    ��
 */
uint8 LPLD_MAG3110_Init(void)
{
  uint8 device_id;
  I2C_InitTypeDef i2c_init_param;
    
  //��ʼ��MAG3110_I2CX
  i2c_init_param.I2C_I2Cx = MAG3110_I2CX;       //��DEV_MAG3110.h���޸ĸ�ֵ
  i2c_init_param.I2C_ICR = MAG3110_SCL_200KHZ;  //�ɸ���ʵ�ʵ�·����SCLƵ��
  i2c_init_param.I2C_SclPin = MAG3110_SCLPIN;   //��DEV_MAG3110.h���޸ĸ�ֵ
  i2c_init_param.I2C_SdaPin = MAG3110_SDAPIN;   //��DEV_MAG3110.h���޸ĸ�ֵ
  i2c_init_param.I2C_IntEnable = FALSE;
  i2c_init_param.I2C_Isr = NULL;
  i2c_init_param.I2C_OpenDrainEnable = FALSE;
  
  LPLD_I2C_Init(i2c_init_param);
  
  //��ȡ�豸ID
  device_id = LPLD_MAG3110_ReadReg(MAG3110_WHO_AM_I);
      
  //����CTRL_REG2
  //�Զ���λģʽ
  LPLD_MAG3110_WriteReg(MAG3110_CTRL_REG2, CTRL_REG2_AUTO_MRST_EN_MARK); 
  //����CTRL_REG1 
  LPLD_MAG3110_WriteReg(MAG3110_CTRL_REG1, CTRL_REG1_OS(0)|CTRL_REG1_AC_MARK);
  
  return device_id;
}

/*
 *   LPLD_MAG3110_WriteReg
 *   �ú�����������MAG3110�ļĴ���
 *
 *   ������
 *   RegisterAddress 
 *    |__ MAG3110�Ĵ�����ַ
 *   Data
 *    |__ ����д����ֽ������� 
 */
void LPLD_MAG3110_WriteReg(uint8 RegisterAddress, uint8 Data)
{
  //���ʹӻ���ַ
  LPLD_I2C_StartTrans(MAG3110_I2CX, MAG3110_DEV_ADDR, I2C_MWSR);
  LPLD_I2C_WaitAck(MAG3110_I2CX, I2C_ACK_ON);
  
  //дMAG3110�Ĵ�����ַ
  LPLD_I2C_WriteByte(MAG3110_I2CX, RegisterAddress);
  LPLD_I2C_WaitAck(MAG3110_I2CX, I2C_ACK_ON);
  
  //��Ĵ�����д��������
  LPLD_I2C_WriteByte(MAG3110_I2CX, Data);
  LPLD_I2C_WaitAck(MAG3110_I2CX, I2C_ACK_ON);

  LPLD_I2C_Stop(MAG3110_I2CX);

  //MAG3110_Delay();
}

/*
 *   LPLD_MAG3110_WriteReg
 *   �ú������ڶ�ȡMAG3110������
 *
 *   ������
 *     RegisterAddress 
 *        |__ MAG3110�Ĵ�����ַ
 *   ����ֵ
 *      ���ٴ������Ĳ���ֵ
 */
uint8 LPLD_MAG3110_ReadReg(uint8 RegisterAddress)
{
  uint8 result;

  //���ʹӻ���ַ
  LPLD_I2C_StartTrans(MAG3110_I2CX, MAG3110_DEV_ADDR, I2C_MWSR);
  LPLD_I2C_WaitAck(MAG3110_I2CX, I2C_ACK_ON);

  //дMAG3110�Ĵ�����ַ
  LPLD_I2C_WriteByte(MAG3110_I2CX, RegisterAddress);
  LPLD_I2C_WaitAck(MAG3110_I2CX, I2C_ACK_ON);

  //�ٴβ�����ʼ�ź�
  LPLD_I2C_ReStart(MAG3110_I2CX);

  //���ʹӻ���ַ�Ͷ�ȡλ
  LPLD_I2C_WriteByte(MAG3110_I2CX, MAG3110_DEV_READ);
  LPLD_I2C_WaitAck(MAG3110_I2CX, I2C_ACK_ON);

  //ת������ģʽΪ��
  LPLD_I2C_SetMasterWR(MAG3110_I2CX, I2C_MRSW);

  //�ر�Ӧ��ACK
  LPLD_I2C_WaitAck(MAG3110_I2CX, I2C_ACK_OFF);//�ر�ACK

  //��IIC����
  result =LPLD_I2C_ReadByte(MAG3110_I2CX);
  LPLD_I2C_WaitAck(MAG3110_I2CX, I2C_ACK_ON);

  //����ֹͣ�ź�
  LPLD_I2C_Stop(MAG3110_I2CX);

   //��IIC����
  result = LPLD_I2C_ReadByte(MAG3110_I2CX);

  MAG3110_Delay();
  
  return result;
}

/*
 * �������ܣ���MAA7660���ٶ����
 * �����w
 *       Status - ���ݼĴ���״̬
 *       Regs_Addr - ���ݼĴ�����ַ
 * ��������ֵ�����ٶ�ֵ��int8��
 */   
int16 LPLD_MAG3110_GetResult(uint8 Status, uint8 Regs_Addr) 
{
  uint8 ret=0;
  uint16 cnt=0;
  int16 result,temp;
  
  if(Regs_Addr>MAG3110_OUT_Z_LSB)
    return 0;
  
  // �ȴ�ת����ɲ�ȡ��ֵ 
  while(!(ret&Status)) 
  {
    ret = LPLD_MAG3110_ReadReg( MAG3110_DR_STATUS);
    if(++cnt>500)
      break;
  }
  
  result= LPLD_MAG3110_ReadReg( Regs_Addr);
  temp  = LPLD_MAG3110_ReadReg( Regs_Addr+1);
  result=result<<8;
  result=result|temp;
  
  return result;
}


/*
 * ��ʱ����
 */
static void MAG3110_Delay(void){
  int n;
  for(n=1;n<200;n++) {
    asm("nop");
  }
}