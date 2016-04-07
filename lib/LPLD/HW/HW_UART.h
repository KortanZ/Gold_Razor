/**
 * @file HW_UART.h
 * @version 3.0[By LPLD]
 * @date 2013-06-18
 * @brief UART�ײ�ģ����غ���
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
#ifndef __HW_UART_H__
#define __HW_UART_H__
//UARTģ��FIFO����
typedef struct 
{
  boolean FIFO_Enable;
  boolean FIFO_BufFlow_IntEnable;
  uint8   FIFO_WaterMark;
} UART_FIFO_Config_T;
//UARTģ���жϻص���������
typedef void (*UART_ISR_CALLBACK)(void);

//UARTģ���ʼ���ṹ�壬��������UART�������
typedef struct
{
  /*
    ������
      ѡ��UARTx
    ȡֵ��
      UART0~UART5
    ��ʼ����
      �������ʼ����Ĭ��ֵUART5
  */
  UART_Type *UART_Uartx;        
      
  /*
    ������
      ����UARTx������
    �Ƽ�ȡֵ��
      4800��9600��19200��38400��115200
    ��ʼ����
      �������ʼ����Ĭ��ֵ9600
  */
  uint32 UART_BaudRate;  
  
  /*
    ������
      �������ţ�ÿ��UARTx��Ӧ��ͬ��TxPin
    ȡֵ��
      UART0-PTA2��PTA14��*PTB17
      UART1-PTE0��*PTC4
      UART2-*PTD3
      UART3-PTE4��PTB11��*PTC17
      UART4-PTE24��*PTC15
      UART5-PTD9��*PTE8
    ��ʼ����
      �������ʼ����Ĭ��ֵΪ��*������
  */
  PortPinsEnum_Type UART_TxPin;   
  
  /*
    ������
      �������ţ�ÿ��UARTx��Ӧ��ͬ��RxPin
    ȡֵ��
      UART0-PTA1��PTA15��*PTB16
      UART1-PTE1��*PTC3
      UART2-*PTD2
      UART3-PTE5��PTB10��*PTC16
      UART4-PTE25��*PTC14
      UART5-PTD8��*PTE9
    ��ʼ����
      �������ʼ����Ĭ��ֵΪ��*������
  */
  PortPinsEnum_Type UART_RxPin; 
  
  /*
    ������
      ʹ�ܽ����ж�
    ȡֵ��
      TRUE-ʹ��
      FALSE-����
    ��ʼ����
      �������ʼ����Ĭ��ֵFALSE
  */
  boolean UART_RxIntEnable;
  
  /*
    ������
      ʹ�ܷ����ж�
    ȡֵ��
      TRUE-ʹ��
      FALSE-����
    ��ʼ����
      �������ʼ����Ĭ��ֵFALSE
  */
  boolean UART_TxIntEnable;
  
  /*
    ������
      ʹ�ܷ���DMA����
    ȡֵ��
      TRUE-ʹ��
      FALSE-����
    ��ʼ����
      �������ʼ����Ĭ��ֵFALSE
  */
  boolean UART_TxDMAEnable;
  
  /*
    ������
      ʹ�ܽ���DMA����
    ȡֵ��
      TRUE-ʹ��
      FALSE-����
    ��ʼ����
      �������ʼ����Ĭ��ֵFALSE
  */
  boolean UART_RxDMAEnable;
  
  /*
    ������
      ���÷���FIFO
    ȡֵ��
      FIFO_Enable ��ʹ��FIFO��
        TRUE-ʹ��
        FALSE-����
      FIFO_BufFlow_IntEnable��ʹ��FIFO buffer overflow ���� underflow �ж� ��
        TRUE-ʹ��
        FALSE-����
      FIFO_WaterMark ������ FIFO waterMark�����ܳ���FIFO Size��
        0 -- FIFO Size
    ��ʼ����
      FIFO_Enable��Ĭ��ֵFALSE
      FIFO_BufFlow_IntEnable��Ĭ��ֵFALSE
      FIFO_WaterMark��Ĭ��ֵ0
  */
  UART_FIFO_Config_T TxFIFO;
  
  /*
    ������
      ���ý���FIFO
    ȡֵ��
      FIFO_Enable ��ʹ��FIFO��
        TRUE-ʹ��
        FALSE-����
      FIFO_BufFlow_IntEnable��ʹ��FIFO buffer overflow ���� underflow �ж� ��
        TRUE-ʹ��
        FALSE-����
      FIFO_WaterMark ������ FIFO waterMark�����ܳ���FIFO Size��
        0 -- FIFO Size
    ��ʼ����
      FIFO_Enable��Ĭ��ֵFALSE
      FIFO_BufFlow_IntEnable��Ĭ��ֵFALSE
      FIFO_WaterMark��Ĭ��ֵ0
  */
  UART_FIFO_Config_T RxFIFO;
  /*
    ������
      �����жϻص�����
    ȡֵ��
      ��������Ϊ�޷���ֵ,�޲���(eg. void isr(void);)
    ��ʼ����
      �������ʼ������δ��ʼ���򲻻ᴥ���ж�
  */
  UART_ISR_CALLBACK UART_RxIsr; 
  
  /*
    ������
      �����жϻص�����
    ȡֵ��
      ��������Ϊ�޷���ֵ,�޲���(eg. void isr(void);)
    ��ʼ����
      �������ʼ������δ��ʼ���򲻻ᴥ���ж�
  */
  UART_ISR_CALLBACK UART_TxIsr; 
} UART_InitTypeDef;


//��ʼ��UARTͨ���������ʡ����ͽ�������
void LPLD_UART_Init(UART_InitTypeDef);
//UART��ȡһ���ַ�
int8 LPLD_UART_GetChar(UART_Type *);
//����Ƿ���յ��ַ�
int32 LPLD_UART_GetChar_Present(UART_Type *);
//UART����һ���ַ�
void LPLD_UART_PutChar(UART_Type *, int8);
//UART�����ַ�����
void LPLD_UART_PutCharArr(UART_Type *, int8*, int32);
//UART�ж�ʹ��
void LPLD_UART_EnableIrq(UART_InitTypeDef);
//UART�жϽ���
void LPLD_UART_DisableIrq(UART_InitTypeDef);
//UART��ս���FIFO
void LPLD_UART_RxFIFO_Flush(UART_Type *uartx);
//UART��շ���FIFO
void LPLD_UART_TxFIFO_Flush(UART_Type *uartx);
#endif