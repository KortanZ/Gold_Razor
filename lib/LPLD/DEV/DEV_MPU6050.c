/**
 * @file DEV_MPU6050.c
 * @version 0.1[By LPLD]
 * @date 2015-02-22
 * @brief MPU60506���˶����������������
 *
 * ���Ľ���:�ɸ���ʵ��Ӳ���޸�
 *
 * ʮ�ָ�л���ļ����߶Եײ��Ĺ��ף�
 * http://www.lpld.cn
 * mail:support@lpld.cn
 * 
 * �ļ�������LPLD_K60�ײ��Ⱥ
 * ���ߣ�Ͷ�ʴ���
 */
#include "common.h"
#include "DEV_MPU6050.h"

I2C_InitTypeDef MPU6050_init_struct;

/*
 *   MPU6050_WriteReg
 *   MPU6050д�Ĵ���״̬
 *
 *   ������
 *    RegisterAddress �Ĵ�����ַ
 *    Data ����Ҫд������
*
 *   ����ֵ
 *    ��
 */
void MPU6050_WriteReg(uint8 RegisterAddress, uint8 Data)
{
  //���ʹӻ���ַ
  LPLD_I2C_StartTrans(I2C1, SlaveAddress, I2C_MWSR);
  LPLD_I2C_WaitAck(I2C1, I2C_ACK_ON);
  
  //дMPU6050�Ĵ�����ַ
  LPLD_I2C_WriteByte(I2C1, RegisterAddress);
  LPLD_I2C_WaitAck(I2C1, I2C_ACK_ON);
  
  //��Ĵ�����д��������
  LPLD_I2C_WriteByte(I2C1, Data);
  LPLD_I2C_WaitAck(I2C1, I2C_ACK_ON);

  LPLD_I2C_Stop(I2C1);
}

/*
 *   MPU6050_ReadReg
 *   MPU6050���Ĵ���״̬
 *
 *   ������
 *    RegisterAddress �Ĵ�����ַ
 *
 *   ����ֵ
 *    �����Ĵ���״̬
 */
uint8 MPU6050_ReadReg(uint8 RegisterAddress)
{
  uint8 result;

  //���ʹӻ���ַ
  LPLD_I2C_StartTrans(I2C1, SlaveAddress, I2C_MWSR);
  LPLD_I2C_WaitAck(I2C1, I2C_ACK_ON);

  //дMPU6050�Ĵ�����ַ
  LPLD_I2C_WriteByte(I2C1, RegisterAddress);
  LPLD_I2C_WaitAck(I2C1, I2C_ACK_ON);
  
  //�ٴβ�����ʼ�ź�
  LPLD_I2C_ReStart(I2C1);

  //���ʹӻ���ַ�Ͷ�ȡλ
  LPLD_I2C_WriteByte(I2C1, (SlaveAddress<<1)|I2C_MRSW);
  LPLD_I2C_WaitAck(I2C1, I2C_ACK_ON);

  //ת������ģʽΪ��
  LPLD_I2C_SetMasterWR(I2C1, I2C_MRSW);

  //�ر�Ӧ��ACK
  LPLD_I2C_WaitAck(I2C1, I2C_ACK_OFF);//�ر�ACK

  //��IIC����
  result =LPLD_I2C_ReadByte(I2C1);
  LPLD_I2C_WaitAck(I2C1, I2C_ACK_ON);

  //����ֹͣ�ź�
  LPLD_I2C_Stop(I2C1);

  //��IIC����
  result = LPLD_I2C_ReadByte(I2C1);
  
  LPLD_SYSTICK_DelayMs(1);

  return result;
}

/*
 *   MPU6050_GetResult
 *   ���MPU6050���
 *
 *   ������
 *    ��
 *
 *   ����ֵ
 *    ת����� 
 */
int16 MPU6050_GetResult(uint8 Regs_Addr)
{
  int16 result,temp;
  result = MPU6050_ReadReg(Regs_Addr);
  temp   = MPU6050_ReadReg(Regs_Addr+1);
  result=result<<8;
  result=result|temp;
  return result;
}

/*
 *   MPU6050_Init
 *   ��ʼ��MPU6050��������ʼ��MPU6050�����I2C�ӿ��Լ�MPU6050�ļĴ���
 *
 *   ������
 *    ��
 *
 *   ����ֵ
 *    ��
 */
void MPU6050_Init()
{
  //��ʼ��MPU6050
  MPU6050_init_struct.I2C_I2Cx = MPU6050_I2CX;          //��MPU6050.h���޸ĸ�ֵ
  MPU6050_init_struct.I2C_IntEnable = FALSE;
  MPU6050_init_struct.I2C_ICR = MPU6050_SCL_400KHZ;     //�ɸ���ʵ�ʵ�·����SCLƵ��
  MPU6050_init_struct.I2C_SclPin = MPU6050_SCLPIN;      //��MPU6050.h���޸ĸ�ֵ
  MPU6050_init_struct.I2C_SdaPin = MPU6050_SCLPIN;      //��MPU6050.h���޸ĸ�ֵ
  MPU6050_init_struct.I2C_Isr = NULL;
  LPLD_I2C_Init(MPU6050_init_struct);
  
  LPLD_SYSTICK_DelayMs(1);
  
  MPU6050_WriteReg(PWR_MGMT_1,0x00);    //�������״̬
  MPU6050_WriteReg(SMPLRT_DIV,0x07);    //�����ǲ����ʣ�����ֵ��0x07(125Hz)
  MPU6050_WriteReg(CONFIG,0x06);        //��ͨ�˲�Ƶ�ʣ�����ֵ��0x06(5Hz)
  MPU6050_WriteReg(GYRO_CONFIG,0x18);   //�������Լ켰������Χ������ֵ��0x18(���Լ죬2000deg/s)
  MPU6050_WriteReg(ACCEL_CONFIG,0x01);  //���ټ��Լ졢������Χ����ͨ�˲�Ƶ�ʣ�����ֵ��0x01(���Լ죬2G��5Hz)
  
  LPLD_SYSTICK_DelayMs(1);
}