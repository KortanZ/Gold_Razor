/**
 * @file DEV_MMA7660.c
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
#include "DEV_MMA7660.h"

static void MMA7660_Delay(void);

/*
 *   LPLD_MMA7660_Init
 *   ��ʼ��MMA7660��������ʼ��7660�����I2C�ӿ��Լ�7660�ļĴ���
 *
 *   ������
 *    ��
 */
void LPLD_MMA7660_Init(void)
{
  I2C_InitTypeDef i2c_init_param;
    
  //��ʼ��MMA7660_I2CX
  i2c_init_param.I2C_I2Cx = MMA7660_I2CX;       //��DEV_MMA7660.h���޸ĸ�ֵ
  i2c_init_param.I2C_IntEnable = FALSE;
  i2c_init_param.I2C_ICR = MMA7660_SCL_200KHZ;  //�ɸ���ʵ�ʵ�·����SCLƵ��
  i2c_init_param.I2C_SclPin = MMA7660_SCLPIN;   //��DEV_MMA7660.h���޸ĸ�ֵ
  i2c_init_param.I2C_SdaPin = MMA7660_SDAPIN;   //��DEV_MMA7660.h���޸ĸ�ֵ
  i2c_init_param.I2C_Isr = NULL;
  
  LPLD_I2C_Init(i2c_init_param);

  LPLD_MMA7660_WriteReg(MMA7660_MODE, 0x00); //Disable tap detection
  LPLD_MMA7660_WriteReg(MMA7660_SR, 0x02);   //Enable auto-sleep, auto-wake, and put in active mode
  LPLD_MMA7660_WriteReg(MMA7660_MODE, 0x11); //Disable tap detection
}

/*
 *   LPLD_MMA7660_WriteReg
 *   �ú�����������MMA7660�ļĴ���
 *
 *   ������
 *   RegisterAddress 
 *    |__ MMA7660�Ĵ�����ַ
 *   Data
 *    |__ ����д����ֽ������� 
 */
void LPLD_MMA7660_WriteReg(uint8 RegisterAddress, uint8 Data)
{
  //���ʹӻ���ַ
  LPLD_I2C_StartTrans(MMA7660_I2CX, MMA7660_DEV_ADDR, I2C_MWSR);
  LPLD_I2C_WaitAck(MMA7660_I2CX, I2C_ACK_ON);
  
  //дMMA7660�Ĵ�����ַ
  LPLD_I2C_WriteByte(MMA7660_I2CX, RegisterAddress);
  LPLD_I2C_WaitAck(MMA7660_I2CX, I2C_ACK_ON);
  
  //��Ĵ�����д��������
  LPLD_I2C_WriteByte(MMA7660_I2CX, Data);
  LPLD_I2C_WaitAck(MMA7660_I2CX, I2C_ACK_ON);

  LPLD_I2C_Stop(MMA7660_I2CX);

  //MMA7660_Delay();
}

/*
 *   LPLD_MMA7660_WriteReg
 *   �ú������ڶ�ȡMMA7660������
 *
 *   ������
 *     RegisterAddress 
 *        |__ MMA7660�Ĵ�����ַ
 *   ����ֵ
 *      ���ٴ������Ĳ���ֵ
 */
uint8 LPLD_MMA7660_ReadReg(uint8 RegisterAddress)
{
  uint8 result;

  //���ʹӻ���ַ
  LPLD_I2C_StartTrans(MMA7660_I2CX, MMA7660_DEV_ADDR, I2C_MWSR);
  LPLD_I2C_WaitAck(MMA7660_I2CX, I2C_ACK_ON);

  //дMMA7660�Ĵ�����ַ
  LPLD_I2C_WriteByte(MMA7660_I2CX, RegisterAddress);
  LPLD_I2C_WaitAck(MMA7660_I2CX, I2C_ACK_ON);

  //�ٴβ�����ʼ�ź�
  LPLD_I2C_ReStart(MMA7660_I2CX);

  //���ʹӻ���ַ�Ͷ�ȡλ
  LPLD_I2C_WriteByte(MMA7660_I2CX, MMA7660_DEV_READ);
  LPLD_I2C_WaitAck(MMA7660_I2CX, I2C_ACK_ON);

  //ת������ģʽΪ��
  LPLD_I2C_SetMasterWR(MMA7660_I2CX, I2C_MRSW);

  //�ر�Ӧ��ACK
  LPLD_I2C_WaitAck(MMA7660_I2CX, I2C_ACK_OFF);//�ر�ACK

  //��IIC����
  result =LPLD_I2C_ReadByte(MMA7660_I2CX);
  LPLD_I2C_WaitAck(MMA7660_I2CX, I2C_ACK_ON);

  //����ֹͣ�ź�
  LPLD_I2C_Stop(MMA7660_I2CX);

   //��IIC����
  result = LPLD_I2C_ReadByte(MMA7660_I2CX);
  
  MMA7660_Delay();

  return result;
}

/*
 * �������ܣ���MAA7660���ٶ����
 * �����w
 *       Regs_Addr - ���ٶȼĴ�����ַ
 * ��������ֵ�����ٶ�ֵ��int8��
 */   
int8 LPLD_MMA7660_GetResult(uint8 Regs_Addr) 
{
   char ret;
   
   if(Regs_Addr>MMA7660_ZOUT)
    return 0;
   
   // �ȴ�ת����ɲ�ȡ��ֵ   
   ret=LPLD_MMA7660_ReadReg(Regs_Addr);
   while(ret&0x40) {
    ret=LPLD_MMA7660_ReadReg(Regs_Addr);
   }
 
   return ret;

}


/*
 * ��ʱ����
 */
static void MMA7660_Delay(void){
  int n;
  for(n=1;n<200;n++) {
    asm("nop");
  }
}