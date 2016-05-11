/**
 * @file DEV_MPU6050.h
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
#ifndef __DEV_MPU6050_H__
#define __DEV_MPU6050_H__

#include "common.h"
#include "HW_I2C.h"

/********�û����޸�ֵ ��ʼ***********/
//����MPU6050�õ���I2Cͨ��
#define MPU6050_I2CX    (I2C1)

//����MPU6050�õ���SCL����
//I2C0 - PTB2��PTB0��PTD8
//I2C1 - PTC10��PTE1
#define MPU6050_SCLPIN  (PTC10)

//����MPU6050�õ���SDA����
//I2C0 - PTB3��PTB1��PTD9
//I2C1 - PTC11��PTE0
#define MPU6050_SDAPIN  (PTC11)
/********�û����޸�ֵ ����***********/

//MPU6050�ڲ��Ĵ���
#define	SMPLRT_DIV		(0x19)	//�����ǲ����ʣ�����ֵ��0x07(125Hz)
#define	CONFIG			(0x1A)	//��ͨ�˲�Ƶ�ʣ�����ֵ��0x06(5Hz)
#define	GYRO_CONFIG		(0x1B)	//�������Լ켰������Χ������ֵ��0x18(���Լ죬2000deg/s)
#define	ACCEL_CONFIG	        (0x1C)	//���ټ��Լ졢������Χ����ͨ�˲�Ƶ�ʣ�����ֵ��0x01(���Լ죬2G��5Hz)
#define	ACCEL_XOUT_H	        (0x3B)  //X����ٶ�  ���ٶ�
#define	ACCEL_XOUT_L	        (0x3C)
#define	ACCEL_YOUT_H	        (0x3D)  //Y����ٶ�
#define	ACCEL_YOUT_L	        (0x3E)
#define	ACCEL_ZOUT_H	        (0x3F)  //Z����ٶ�
#define	ACCEL_ZOUT_L	        (0x40)
#define	TEMP_OUT_H		(0x41)
#define	TEMP_OUT_L		(0x42)
#define	GYRO_XOUT_H		(0x43)  //X����ٶ�  ������
#define	GYRO_XOUT_L		(0x44)	
#define	GYRO_YOUT_H		(0x45)  //Y����ٶ�
#define	GYRO_YOUT_L		(0x46)
#define	GYRO_ZOUT_H		(0x47)  //Z����ٶ�
#define	GYRO_ZOUT_L		(0x48)
#define	PWR_MGMT_1		(0x6B)	//��Դ��������ֵ��0x00(��������)
#define	WHO_AM_I		(0x75)	//IIC��ַ�Ĵ���(Ĭ����ֵ0x68��ֻ��)
#define	SlaveAddress	        (0x68)	//Ӳ��I2C��ַ0x68 ���I2C��ַ0xD0

//����SCL Bus Speedȡֵ����������Ϊ50Mhzʱ�ļ�����
#define MPU6050_SCL_50KHZ       (0x33)
#define MPU6050_SCL_100KHZ      (0x2B)
#define MPU6050_SCL_150KHZ      (0x28)
#define MPU6050_SCL_200KHZ      (0x23)
#define MPU6050_SCL_250KHZ      (0x21)
#define MPU6050_SCL_300KHZ      (0x20)
#define MPU6050_SCL_400KHZ      (0x17)

//��������
void  MPU6050_WriteReg(uint8 RegisterAddress, uint8 Data);
uint8 MPU6050_ReadReg(uint8 RegisterAddress);
int16 MPU6050_GetResult(uint8 Regs_Addr);
void  MPU6050_Init();

#endif