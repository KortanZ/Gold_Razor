/**
 * @file HW_SPI.h
 * @version 3.03[By LPLD]
 * @date 2014-2-10
 * @brief SPI�ײ�ģ����غ���
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
#ifndef __HW_SPI_H__
#define __HW_SPI_H__

//SPIģ���жϻص���������
typedef void (*SPI_ISR_CALLBACK)(void);
//����SPI����ģʽ
#define SPI_MODE_MASTER      (0)
#define SPI_MODE_SLAVE       (1)
//����SPI FIFO �¼���ʽ
#define SPI_FIFO_DMAREQUEST  (TRUE)
#define SPI_FIFO_INTREQUEST  (FALSE)
//����SPI ��Ƶϵ��
#define SPI_SCK_DIV_2        (0)
#define SPI_SCK_DIV_4        (1)
#define SPI_SCK_DIV_6        (2)
#define SPI_SCK_DIV_8        (3)
#define SPI_SCK_DIV_16       (4)
#define SPI_SCK_DIV_32       (5)
#define SPI_SCK_DIV_64       (6)
#define SPI_SCK_DIV_128      (7)
#define SPI_SCK_DIV_256      (8)
#define SPI_SCK_DIV_512      (9)
#define SPI_SCK_DIV_1024     (10)
#define SPI_SCK_DIV_2048     (11)
#define SPI_SCK_DIV_4096     (12)
#define SPI_SCK_DIV_8192     (13)
#define SPI_SCK_DIV_16384    (14
#define SPI_SCK_DIV_32768    (15)
//����SPI PCSȡֵ
#define SPI_PCS0             (1) //0x000001
#define SPI_PCS1             (2) //0x000010
#define SPI_PCS2             (4) //0x000100
#define SPI_PCS3             (8) //0x001000
#define SPI_PCS4             (16)//0x010000
#define SPI_PCS5             (32)//0x100000
//���巢����Ϻ�SPI PCS��״̬
#define SPI_PCS_ASSERTED     (0x01)
#define SPI_PCS_INACTIVE     (0x00)

//SPI�ж����
#define SPI_TxComplete_Int              0
#define SPI_QueueEndReq_Int             1
#define SPI_TxFIFO_UnderflowInt         2
#define SPI_RxFIFO_OverflowInt          3
#define SPI_TxFIFO_FillInt              4
#define SPI_RxFIFO_DrainInt             5

typedef struct
{
  /*
    ������
      ѡ��SPIx
    ȡֵ��
      SPI0 - SPIͨ��0
      SPI1 - SPIͨ��1
      SPI2 - SPIͨ��2
    ��ʼ����
      �����ʼ��
  */
  SPI_Type *SPI_SPIx;
  
  /*
    ������
      ѡ��SPIx ����ģʽ
    ȡֵ��
      SPI_MODE_MASTER - SPI��������ģʽ
      SPI_MODE_SLAVE - SPI�ӻ�����ģʽ
    ��ʼ����
      �������ʼ����Ĭ����������ģʽ
  */
  uint8 SPI_ModeSelect;
  
  /*
    ������
      ѡ��SPIx SCK���߷�Ƶϵ����SPI�����ʱ�ӻ�׼��g_bus_clock
      SCK����Ƶ�� = g_bus_clock/ SCK_DIV_XX
    ȡֵ��
      SPI_SCK_DIV_2     - 2��Ƶ
      SPI_SCK_DIV_4     - 4��Ƶ
      SPI_SCK_DIV_6     - 6��Ƶ
      SPI_SCK_DIV_8     - 8��Ƶ
      SPI_SCK_DIV_16    - 16��Ƶ
      SPI_SCK_DIV_32    - 32��Ƶ
      SPI_SCK_DIV_64    - 64��Ƶ
      SPI_SCK_DIV_128   - 128��Ƶ
      SPI_SCK_DIV_256   - 256��Ƶ
      SPI_SCK_DIV_512   - 512��Ƶ
      SPI_SCK_DIV_1024  - 1024��Ƶ
      SPI_SCK_DIV_2048  - 2048��Ƶ
      SPI_SCK_DIV_4096  - 4096��Ƶ
      SPI_SCK_DIV_8192  - 8192��Ƶ
      SPI_SCK_DIV_16384 - 16384��Ƶ
      SPI_SCK_DIV_32768 - 32768��Ƶ
    ��ʼ����
      �����ʼ��
  */ 
  uint8 SPI_SckDivider;
  
  /*
    ������
      ʹ��Tx FIFO��ʽ
    ȡֵ��
      TRUE - ʹ��Tx FIFO��ʽ
      FALSE - ��ֹTx FIFO��ʽ�����ô�ͳSPI��ʽ
    ��ʼ����
      �������ʼ����Ĭ�Ͻ�ֹTx FIFO��ʽ�����ô�ͳSPI��ʽ
  */
  boolean SPI_EnableTxFIFO;
  
  /*
    ������
      ʹ��Rx FIFO��ʽ
    ȡֵ��
      TRUE - ʹ��Rx FIFO��ʽ
      FALSE - ��ֹRx FIFO��ʽ�����ô�ͳSPI��ʽ
    ��ʼ����
      �������ʼ����Ĭ�Ͻ�ֹRx FIFO��ʽ�����ô�ͳSPI��ʽ
  */
  boolean SPI_EnableRxFIFO;
  
  /*
    ������
      ʹ�ܷ�������ж�
    ȡֵ��
      TRUE - ʹ�ܷ�������ж�
      FALSE - ��ֹ��������ж�
    ��ʼ����
      �������ʼ����Ĭ�Ͻ�ֹ��������ж�
  */
  boolean SPI_TxCompleteIntEnable;
  
  /*
    ������
      ѡ��ʹ�ܷ��Ͷ��н����ж�
    ȡֵ��
      TRUE - ʹ�ܷ��Ͷ��н����ж�
      FALSE - ��ֹ���Ͷ��н����ж�
    ��ʼ����
      �������ʼ����Ĭ�Ͻ�ֹ���Ͷ��н����ж�
  */
  boolean SPI_QueueEndIntEnable; 
  
  /*
    ������
      ѡ��ʹ��txFIFOΪ���ж�
    ȡֵ��
      TRUE - ʹ��txFIFOΪ���ж�
      FALSE - ��ֹtxFIFOΪ���ж�
    ��ʼ����
      �������ʼ����Ĭ�Ͻ�ֹtxFIFOΪ���ж�
  */
  boolean SPI_TxFIFO_UnderflowIntEnable;
  
  /*
    ������
      ѡ��ʹ��rxFIFO����ж�
    ȡֵ��
      TRUE - ʹ��rxFIFO����ж�
      FALSE - ��ֹrxFIFO����ж�
    ��ʼ����
      �������ʼ����Ĭ�Ͻ�ֹrxFIFO����ж�
  */
  boolean SPI_RxFIFO_OverflowIntEnable;
  
  /*
    ������
      ѡ��ʹ��txFIFO����ж�
    ȡֵ��
      TRUE - ʹ��txFIFO����ж�
      FALSE - ��ֹtxFIFO����ж�
    ��ʼ����
      �������ʼ����Ĭ�Ͻ�ֹtxFIFO����ж�
  */
  boolean SPI_TxFIFO_FillIntEnable;
  
  /*
    ������
      ѡ��ʹ��rxFIFO��ȡ�ж�
    ȡֵ��
      TRUE - ʹ��rxFIFO��ȡ�ж�
      FALSE - ��ֹrxFIFO��ȡ�ж�
    ��ʼ����
      �������ʼ����Ĭ�Ͻ�ֹrxFIFO��ȡ�ж�
  */
  boolean SPI_RxFIFO_DrainIntEnable;
  
  /*
    ������
      TxFIFO����ʽѡ��
    ȡֵ��
      SPI_FIFO_INTREQUEST - �����ж�����
      SPI_FIFO_DMAREQUEST - ����DMA����
    ��ʼ����
      �������ʼ����Ĭ��ΪSPI_FIFO_INTREQUEST
  */ 
  boolean SPI_TxFIFO_RequestSelect;
  
  /*
    ������
      RxFIFO����ʽѡ��
    ȡֵ��
      SPI_FIFO_INTREQUEST - �����ж�����
      SPI_FIFO_DMAREQUEST - ����DMA����
    ��ʼ����
      �������ʼ����Ĭ��ΪSPI_FIFO_INTREQUEST
  */
  boolean SPI_RxFIFO_RequestSelect;
  
  /*
    ������
      Pcs0���ţ�ÿ��SPIx��Ӧ��ͬ��Pcs0Pin
    ȡֵ��
      SPI0-PTA14��*PTC4
      SPI1-PTB10��*PTE4
      SPI2-PTD11��*PTB20
    ��ʼ����
      �������ʼ����Ĭ��ֵΪ��*������
  */
  PortPinsEnum_Type SPI_Pcs0Pin;
  
  /*
    ������
      Pcs1���ţ�ÿ��SPIx��Ӧ��ͬ��Pcs1Pin
    ȡֵ��
      SPI0-PTC3��*PTD4
      SPI1-PTB9��*PTE0
      SPI2-*PTD15
    ��ʼ����
      �������ʼ����Ĭ��ֵΪ��*������
  */
  PortPinsEnum_Type SPI_Pcs1Pin;
  
  /*
    ������
      Pcs2���ţ�ÿ��SPIx��Ӧ��ͬ��Pcs2Pin
    ȡֵ��
      SPI0-PTC2��*PTD5
      SPI1-*PTE5
    ��ʼ����
      �������ʼ����Ĭ��ֵΪ��*������
  */
  PortPinsEnum_Type SPI_Pcs2Pin;
  
  /*
    ������
      Pcs3���ţ�ÿ��SPIx��Ӧ��ͬ��Pcs3Pin
    ȡֵ��
      SPI0-PTC1��*PTD6
      SPI1-*PTE6
    ��ʼ����
      �������ʼ����Ĭ��ֵΪ��*������
  */
  PortPinsEnum_Type SPI_Pcs3Pin;
  
  /*
    ������
      Pcs4���ţ�ÿ��SPIx��Ӧ��ͬ��Pcs4Pin
    ȡֵ��
      SPI0-*PTC0
    ��ʼ����
      �������ʼ����Ĭ��ֵΪ��*������
  */
  PortPinsEnum_Type SPI_Pcs4Pin;
  
  /*
    ������
      Pcs5���ţ�ÿ��SPIx��Ӧ��ͬ��Pcs2Pin
    ȡֵ��
      SPI0-*PTB23
    ��ʼ����
      �������ʼ����Ĭ��ֵΪ��*������
  */
  PortPinsEnum_Type SPI_Pcs5Pin;
  
  /*
    ������
      Sck���ţ�ÿ��SPIx��Ӧ��ͬ��SckPin
    ȡֵ��
      SPI0-PTA15��*PTC5
      SPI1-PTB11��*PTE2
      SPI2-PTD12��*PTB21
    ��ʼ����
      �������ʼ����Ĭ��ֵΪ��*������
  */
  PortPinsEnum_Type SPI_SckPin;
  
  /*
    ������
      MOSI���ţ�ÿ��SPIx��Ӧ��ͬ��MosiPin
    ȡֵ��
      SPI0-PTA16��*PTC6
      SPI1-PTB16��*PTE1
      SPI2-PTD13��*PTB22
    ��ʼ����
      �������ʼ����Ĭ��ֵΪ��*������
  */
  PortPinsEnum_Type SPI_MosiPin;
  
  /*
    ������
      MISO���ţ�ÿ��SPIx��Ӧ��ͬ��MisoPin
    ȡֵ��
      SPI0-PTA17��*PTC7
      SPI1-PTB17��*PTE3
      SPI2-PTD14��*PTB23
    ��ʼ����
      �������ʼ����Ĭ��ֵΪ��*������
  */
  PortPinsEnum_Type SPI_MisoPin;
  
  /*
    ������
      ��������жϻص�����
    ȡֵ��
      ��������Ϊ�޷���ֵ,�޲���(eg. void isr(void);)
    ��ʼ����
      �������ʼ������δ��ʼ���򲻻ᴥ���ж�
  */
  SPI_ISR_CALLBACK SPI_TxCompleteIntIsr;  
  
  /*
    ������
      ���Ͷ��н����жϻص�����
    ȡֵ��
      ��������Ϊ�޷���ֵ,�޲���(eg. void isr(void);)
    ��ʼ����
      �������ʼ������δ��ʼ���򲻻ᴥ���ж�
  */
  SPI_ISR_CALLBACK SPI_QueueEndIntIsr;
  
  /*
    ������
      txFIFOΪ���жϻص�����
    ȡֵ��
      ��������Ϊ�޷���ֵ,�޲���(eg. void isr(void);)
    ��ʼ����
      �������ʼ������δ��ʼ���򲻻ᴥ���ж�
  */
  SPI_ISR_CALLBACK SPI_TxFIFO_UnderflowIntIsr;
  
  /*
    ������
      rxFIFO����жϻص�����
    ȡֵ��
      ��������Ϊ�޷���ֵ,�޲���(eg. void isr(void);)
    ��ʼ����
      �������ʼ������δ��ʼ���򲻻ᴥ���ж�
  */
  SPI_ISR_CALLBACK SPI_RxFIFO_OverflowIntIsr;
  
  /*
    ������
      txFIFO����жϻص�����
    ȡֵ��
      ��������Ϊ�޷���ֵ,�޲���(eg. void isr(void);)
    ��ʼ����
      �������ʼ������δ��ʼ���򲻻ᴥ���ж�
  */
  SPI_ISR_CALLBACK SPI_TxFIFO_FillIntIsr;
  
  /*
    ������
      rxFIFO��ȡ�жϻص�����
    ȡֵ��
      ��������Ϊ�޷���ֵ,�޲���(eg. void isr(void);)
    ��ʼ����
      �������ʼ������δ��ʼ���򲻻ᴥ���ж�
  */
  SPI_ISR_CALLBACK SPI_RxFIFO_DrainIntIsr;
  
}SPI_InitTypeDef;

//SPI��ʼ������
uint8 LPLD_SPI_Init(SPI_InitTypeDef );
//SPI����ʼ������
uint8 LPLD_SPI_Deinit(SPI_InitTypeDef );
//SPIʹ�������ж�
uint8 LPLD_SPI_EnableIrq(SPI_InitTypeDef );
//SPI��ֹ�����ж�
uint8 LPLD_SPI_DisableIrq(SPI_InitTypeDef );
//SPI������д����
uint8 LPLD_SPI_Master_WriteRead(SPI_Type * ,uint8 ,uint8 ,uint8);
//SPI����������
uint8 LPLD_SPI_Master_Read(SPI_Type *);
//SPI����д����
void LPLD_SPI_Master_Write(SPI_Type * ,uint8 ,uint8 ,uint8);

/********************************************************************/

#endif /* __HW_SPI_H__ */
