/**
 * @file DEV_Nrf24L01.h
 * @version 1.0[By LPLD]
 * @date 2013-09-24
 * @brief Nrf24L01�豸��������
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
#ifndef __DEV_NRF24L01_H__
#define __DEV_NRF24L01_H__

#include "common.h"
#include "HW_SPI.h"
#include "HW_GPIO.h"

/********�û����޸�ֵ ��ʼ**********/
//ѡ��NRF24L01ʹ�õ�SPIģ��
#define NRF24L01_SPIX    (SPI0)

//ѡ��NRF24L01 MOSI����Ӧ��IO
#define NRF24L01_MOSI  (PTA16)

//ѡ��NRF24L01 MISO����Ӧ��IO
#define NRF24L01_MISO  (PTA17)

//ѡ��NRF24L01 SCK����Ӧ��IO
#define NRF24L01_SCK  (PTA15)

//ѡ��NRF24L01 PCS0����Ӧ��IO
#define NRF24L01_PCS0  (PTA14)

//ѡ��NRF24L01 CE����Ӧ��IO
#define NRF24L01_CE_PTX  (PTB)
#define NRF24L01_CE_IOX  (GPIO_Pin0)
#define NRF24L01_CE_H    LPLD_GPIO_Output_b(NRF24L01_CE_PTX,NRF24L01_CE_IOX,OUTPUT_H) 
#define NRF24L01_CE_L    LPLD_GPIO_Output_b(NRF24L01_CE_PTX,NRF24L01_CE_IOX,OUTPUT_L) 

// NRF24L01��ز�������
#define NRF24L01_PLOAD_LEN        (32) //�����غɳ���
#define NRF24L01_TX_ADR_LEN       (5)  //TX��ַ����
#define NRF24L01_RX_ADR_LEN       (5)  //RX��ַ����

// Nrf24L01_CheckID
#define NRF24L01_RX_ADDR_P0_RESET_ID (0xE7E7E7E7)
#define NRF24L01_RX_ADDR_P1_RESET_ID (0xC2C2C2C2)
#define NRF24L01_TX_ADDR_RESET_ID    (0xE7E7E7E7)
// NRF24L01ָ��
#define NRF24L01_READ_REG         0x00   // �����üĴ���
#define NRF24L01_WRITE_REG        0x20   // д���üĴ���
#define NRF24L01_RD_RX_PLOAD      0x61   // ��ȡRX FIFO�е�����
#define NRF24L01_WR_TX_PLOAD      0xA0   // ��TX FIFO��д������
#define NRF24L01_FLUSE_TX         0xE1   // ���TX FIFO�е����� Ӧ���ڷ���ģʽ��
#define NRF24L01_FLUSE_RX         0xE2   // ���RX FIFO�е����� Ӧ���ڽ���ģʽ��
#define NRF24L01_REUSE_TX_PL      0xE3   // ����ʹ����һ����Ч����
#define NRF24L01_NOP              0xFF   // �޲��� ���ڶ�STATUS�Ĵ���
//********************************************************************************************************************// 
// NRF24L01�Ĵ���(��ַ)
#define NRF24L01_CONFIG           0x00  //���÷���״̬��CRCУ��ģʽ�Լ����շ�״̬��Ӧ��ʽ
#define NRF24L01_EN_AA            0x01  //�Զ�Ӧ��������
#define NRF24L01_EN_RXADDR        0x02  //�����ŵ�����
#define NRF24L01_SETUP_AW         0x03  //�շ���ַ�������
#define NRF24L01_SETUP_RETR       0x04  //�Զ��ط�����������
#define NRF24L01_RF_CH            0x05  //�����ŵ��趨
#define NRF24L01_RF_SETUP         0x06  //�������ʡ����Ĺ�������
#define NRF24L01_STATUS           0x07  //״̬�Ĵ���
#define NRF24L01_OBSERVE_TX       0x08  //���ͼ�⹦��
#define NRF24L01_CD               0x09  //��ַ��� 
#define NRF24L01_RX_ADDR_P0       0x0A  //Ƶ��0�������ݵ�ַ
#define NRF24L01_RX_ADDR_P1       0x0B  //Ƶ��1�������ݵ�ַ
#define NRF24L01_RX_ADDR_P2       0x0C  //Ƶ��2�������ݵ�ַ
#define NRF24L01_RX_ADDR_P3       0x0D  //Ƶ��3�������ݵ�ַ
#define NRF24L01_RX_ADDR_P4       0x0E  //Ƶ��4�������ݵ�ַ
#define NRF24L01_RX_ADDR_P5       0x0F  //Ƶ��5�������ݵ�ַ
#define NRF24L01_TX_ADDR          0x10  //���͵�ַ�Ĵ���
#define NRF24L01_RX_PW_P0         0x11  //����Ƶ��0�������ݳ���
#define NRF24L01_RX_PW_P1         0x12  //����Ƶ��1�������ݳ���
#define NRF24L01_RX_PW_P2         0x13  //����Ƶ��2�������ݳ���
#define NRF24L01_RX_PW_P3         0x14  //����Ƶ��3�������ݳ���
#define NRF24L01_RX_PW_P4         0x15  //����Ƶ��4�������ݳ���
#define NRF24L01_RX_PW_P5         0x16  //����Ƶ��5�������ݳ���
#define NRF24L01_FIFO_STATUS      0x17  //FIFOջ��ջ��״̬�Ĵ�������
//NRF24L01״̬�Ĵ���ֵ
#define NRF24L01_STATUS_MAX_RT    0x10 //�ﵽ����ط�״̬
#define NRF24L01_STATUS_TX_DS     0x20 //���ͳɹ�
#define NRF24L01_STATUS_RX_DR     0x40 //���ճɹ�

//NRF24L01��ʼ������
uint8 LPLD_Nrf24L01_Init(void);
//NRF24L01����ģʽ��ʼ������
uint8 LPLD_Nrf24L01_TxModeInit(void);
//NRF24L01����ģʽ��ʼ������
uint8 LPLD_Nrf24L01_RxModeInit(void);
//NRF24L01��������֡����
uint8 LPLD_Nrf24L01_SendFrame(uint8 *data, uint8 len);
//NRF24L01��������֡����
void LPLD_Nrf24L01_RecvFrame(uint8 *data, uint8 len);
#endif
