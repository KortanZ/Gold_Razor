/**
* @file HW_CAN.h
* @version 3.03[By LPLD]
* @date 2014-3-9
* @brief CAN�ײ�ģ����غ���
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
#ifndef __HW_CAN_H__
#define __HW_CAN_H__

//����FlexCAN�жϻص�����
typedef void (*CAN_ISR_CALLBACK)(void);


#define MSG_NUM_0                (0)  //����Msg������0
#define MSG_NUM_1                (1)  //����Msg������1
#define MSG_NUM_2                (2)  //����Msg������2
#define MSG_NUM_3                (3)  //����Msg������3
#define MSG_NUM_4                (4)  //����Msg������4
#define MSG_NUM_5                (5)  //����Msg������5
#define MSG_NUM_6                (6)  //����Msg������6
#define MSG_NUM_7                (7)  //����Msg������7
#define MSG_NUM_8                (8)  //����Msg������8
#define MSG_NUM_9                (9)  //����Msg������9
#define MSG_NUM_10               (10) //����Msg������10
#define MSG_NUM_11               (11) //����Msg������11
#define MSG_NUM_12               (12) //����Msg������12
#define MSG_NUM_13               (13) //����Msg������13
#define MSG_NUM_14               (14) //����Msg������14
#define MSG_NUM_15               (15) //����Msg������15

//FlexCANģ��Bit Rate Values
#define CAN_BAUD_RATE_33KBPS    (33333ul)
#define CAN_BAUD_RATE_50KBPS    (50000ul)
#define CAN_BAUD_RATE_83KBPS    (83333ul)
#define CAN_BAUD_RATE_100KBPS   (100000ul)
#define CAN_BAUD_RATE_125KBPS   (125000ul)
#define CAN_BAUD_RATE_250KBPS   (250000ul)
#define CAN_BAUD_RATE_500KBPS   (500000ul)
#define CAN_BAUD_RATE_1MBPS     (1000000ul)

//���FlexCAN Ctr1�Ĵ�����Prescale�ε�ֵ����������FlexCAN��ͨ�Ų�����
#define CAN_GET_PRESCALE( device_freq, desired_baud, time_quanta )\
     (uint8)(( device_freq/(desired_baud * time_quanta)) - 1 )

//ѡ���ʼ���������Ŀ������Ŀ��CAN_MCR_REG������Msg���ٵ����λ����
#define MSG_MAX_NO    (16)
       
//FlexCAN_MB��CODEλ����
#define CAN_MB_CS_CODE_MASK         (0x0F000000u)
#define CAN_MB_CS_CODE_SHIFT        (24) 
#define CAN_MB_CS_CODE(x)           (((uint32)(((uint32)(x))<<CAN_MB_CS_CODE_SHIFT))&CAN_MB_CS_CODE_MASK)
#define CAN_MB_CS_RTR_MASK          (0x00100000u)
#define CAN_MB_CS_RTR_SHIFT         (20)
#define CAN_MB_CS_RTR(x)            (((uint32)(((uint32)(x))<<CAN_MB_CS_RTR_SHIFT))&CAN_MB_CS_RTR_MASK)
#define CAN_MB_CS_IDE_MASK          (0x00200000u)
#define CAN_MB_CS_IDE_SHIFT         (21)
#define CAN_MB_CS_IDE(x)            (((uint32)(((uint32)(x))<<CAN_MB_CS_IDE_SHIFT))&CAN_MB_CS_IDE_MASK)
#define CAN_MB_CS_SRR_MASK          (0x00400000u)
#define CAN_MB_CS_SRR_SHIFT         (22)
#define CAN_MB_CS_SRR(x)            (((uint32)(((uint32)(x))<<CAN_MB_CS_SRR_SHIFT))&CAN_MB_CS_SRR_MASK) 
#define CAN_MB_CS_DLC_MASK          (0x000F0000u)
#define CAN_MB_CS_DLC_SHIFT         (16)       
#define CAN_MB_CS_DLC(x)            (((uint32)(((uint32)(x))<<CAN_MB_CS_DLC_SHIFT))&CAN_MB_CS_DLC_MASK)
#define CAN_MB_CS_TIMESTAMP_MASK    (0x0000FFFFu)
#define CAN_MB_CS_TIMESTAMP_SHIFT   (0)     
#define CAN_MB_CS_TIMESTAMP(x)      (((uint32)(((uint32)(x))<<CAN_MB_CS_TIMESTAMP_SHIFT))&CAN_MB_CS_TIMESTAMP_MASK)
#define CAN_GET_MB_CS_CODE(x)       (((x) & CAN_MB_CS_CODE_MASK)>>CAN_MB_CS_CODE_SHIFT)
#define CAN_GET_MB_CS_LENGTH(x)     (((x) & CAN_MB_CS_DLC_MASK )>>CAN_MB_CS_DLC_SHIFT)
#define CAN_GET_MB_CS_IDE(x)        (((x) & CAN_MB_CS_IDE_MASK )>>CAN_MB_CS_IDE_SHIFT)
#define CAN_GET_MB_CS_TIMESTAMP(x) (((x) & CAN_MB_CS_TIMESTAMP_MASK )>>CAN_MB_CS_TIMESTAMP_SHIFT)    
//FLEXCAN_MB_ID��λ����ͺ�
#define CAN_MB_ID_PRIO_MASK         (0xE0000000u)
#define CAN_MB_ID_PRIO_SHIFT        (29)
#define CAN_MB_ID_PRIO(x)           (((uint32)(((uint32)(x))<<CAN_MB_ID_PRIO_SHIFT))&CAN_MB_ID_PRIO_MASK)  
#define CAN_MB_ID_STD_MASK          (0x1FFC0000u)
#define CAN_MB_ID_STD_SHIFT         (18)
#define CAN_MB_ID_STD(x)            (((uint32)(((uint32)(x))<<CAN_MB_ID_STD_SHIFT))&CAN_MB_ID_STD_MASK)
#define CAN_MB_ID_EXT_MASK          (0x1FFFFFFFu)
#define CAN_MB_ID_EXT_SHIFT         (0)
#define CAN_MB_ID_EXT(x)            (((uint32)(((uint32)(x))<<CAN_MB_ID_EXT_SHIFT))&CAN_MB_ID_EXT_MASK)     
#define CAN_GET_MB_ID_STD(x)        (((x) & CAN_MB_ID_STD_MASK )>>CAN_MB_ID_STD_SHIFT)
#define CAN_GET_MB_ID_EXT(x)        (((x) & CAN_MB_ID_EXT_MASK )>>CAN_MB_ID_EXT_SHIFT)
     
//ö��FlexCANģ�������CODE�ε���ֵ
typedef enum CAN_Msg_Code_Tag
{
  CAN_MSGOBJ_RX_INACTIVE      = 0x0,  //@emem RX Inactive
  CAN_MSGOBJ_RX_BUSY          = 0x1,  //@emem RX Busy
  CAN_MSGOBJ_RX_FULL          = 0x2,  //@emem RX FULL
  CAN_MSGOBJ_RX_EMPTY         = 0x4,  //@emem RX Empty
  CAN_MSGOBJ_RX_OVERRUN       = 0x6,  //@emem RX Overrun
  CAN_MSGOBJ_TX_INACTIVE      = 0x8,  //@emem TX Inactive
  CAN_MSGOBJ_TX_REMOTE        = 0xA,  //@emem TX Remote
  CAN_MSGOBJ_TX_ONCE          = 0xC,  //@emem TX Unconditional
  CAN_MSGOBJ_TX_REMOTE_MATCH  = 0xE   //@emem Tx Remote match
} CAN_Msg_CodeEnum_Type ;


//ö��FlexCANģ���ж���ʽ
typedef enum CAN_Int_Tag
{
  CAN_MB_INT,
  CAN_BUS_OFF_INT,
  CAN_ERROR_INT,
  CAN_TRANS_WARNING_INT,
  CAN_RECV_WARNING_INT,
  CAN_WAKEUP_INT,
  CAN_IMEU_INT,
  CAN_LOST_RECV_INT
}CAN_IntEnum_Type;

//ö��FlexCANģ�����ݳ���
typedef enum CAN_MSGOBJ_Data_Length_Tag
{
  CAN_DATA_0_BYTES = 0,
  CAN_DATA_1_BYTES = 1,
  CAN_DATA_2_BYTES = 2,
  CAN_DATA_3_BYTES = 3,
  CAN_DATA_4_BYTES = 4,
  CAN_DATA_5_BYTES = 5,
  CAN_DATA_6_BYTES = 6,
  CAN_DATA_7_BYTES = 7,
  CAN_DATA_MAX_BYTES = 8
}CAN_MSGOBJ_Data_LengthEnum_Type;

//ö��FlexCANģ��Msg�ķ���
typedef enum CAN_MSGOBJ_DIR_Tag
{
  CAN_MSGOBJ_DIR_NULL,
  CAN_MSGOBJ_DIR_RX, 
  CAN_MSGOBJ_DIR_TX  
}CAN_MSGOBJ_DIR_T;

//ö��FlexCANģ��Msg��ID��ʽ
typedef enum CAN_MSGOBJ_ID_Tag
{
  CAN_MSGOBJ_ID_STD, 
  CAN_MSGOBJ_ID_EXT 
}CAN_MSGOBJ_IDEnum_Type;

//ö��FlexCANģ��Msg�Ľ������η�ʽ
typedef enum CAN_MSGOBJ_RxMasking_Tag
{
  CAN_MSGOBJ_INDIVIDUAL_MASKING, 
  CAN_MSGOBJ_GLOBAL_MASKING 
}CAN_MSGOBJ_RxMaskingEnum_Type;

typedef struct 
{
  /*
    ������
      ѡ��CANx
    ȡֵ��
      CAN0
      CAN1
    ��ʼ����
      �����ʼ��
  */
  CAN_Type *CAN_Canx;
  
  /*
    ������
      ����FlexCAN������
    �Ƽ�ȡֵ��
      CAN_BAUD_RATE_50KBPS - ������50KBPS
      CAN_BAUD_RATE_100KBPS- ������100KBPS
      CAN_BAUD_RATE_250KBPS- ������250KBPS
      CAN_BAUD_RATE_500KBPS- ������500KBPS
      CAN_BAUD_RATE_1MBPS  - ������1MKBPS
    ��ʼ����
      �����ʼ��
  */
  uint32 CAN_BaudRate;
  
  /*
    ������
      ����FlexCAN Msg����ƥ�䷽ʽ
    �Ƽ�ȡֵ��
      CAN_MSGOBJ_INDIVIDUAL_MASKING-ÿһ·Msg��������ƥ��
      CAN_MSGOBJ_GLOBAL_MASKING-����RXMGMASK, RX14MASK and RX15MASK, RXFGMASKƥ�����
    ��ʼ����
      �������ʼ����Ĭ��ΪCAN_MSGOBJ_INDIVIDUAL_MASKING
  */
  uint8 CAN_RxMaskMode;
  
  /*
    ������
      �������ţ�ÿ��CANTx��Ӧ��ͬ��TxPin
    ȡֵ��
      CAN0-*PTA12��PTB18
      CAN1-*PTE24��PTC17
    ��ʼ����
      �����CAN0��Ĭ��TX IOΪPTA12
      �����CAN1��Ĭ��TX IOΪPTE24
  */
  PortPinsEnum_Type CAN_TxPin;  
  

  /*
    ������
      �������ţ�ÿ��CANRx��Ӧ��ͬ��RxPin
    ȡֵ��
      CAN0-*PTA13��PTB19
      CAN1-*PTE25��PTC16
    ��ʼ����
      �����CAN0��Ĭ��RX IOΪPTA13
      �����CAN1��Ĭ��RX IOΪPTE25
  */
  PortPinsEnum_Type CAN_RxPin;

}CAN_InitTypeDef;

typedef struct 
{
  /*
    ������
      ѡ��CANx
    ȡֵ��
      CAN0
      CAN1
    ��ʼ����
      �����ʼ��
  */
  CAN_Type *CAN_Canx;
  
  /*
    ������
      ����FlexCAN�����е�MSG number
    ȡֵ��
      MSG_NUM_0-Msg-Msg������0
      ......
      MSG_NUM_15-Msg-Msg������15
    ��ʼ����
      �����ʼ��
  */
  uint8 CAN_MsgNum;
  
  /*
    ������
      ����ID����
    ȡֵ��
      CAN_MSGOBJ_ID_STD-��׼֡
      CAN_MSGOBJ_ID_EXT-��չ֡
    ��ʼ����
      �����ʼ��
  */
  uint8 CAN_MsgIdLength;
  
  /*
    ������
      ����Substitute Remote Request��SRR��
    ȡֵ��
      1-ʹ��
      0-��ֹ
    ��ʼ����
      �����ʼ����
  */
  uint8 CAN_MsgSRR;
  
  /*
    ������
      ����Remote Transmission Request��RTR��
    ȡֵ��
      1-ʹ��
      0-��ֹ
    ��ʼ����
      �����ʼ������
  */
  uint8 CAN_MsgRTR;
  
  /*
    ������
      ����FlexCAN�����е�MB����
    ȡֵ��
      FLEXCAN_MSGOBJ_DIR_RX-������Ϣ
      FLEXCAN_MSGOBJ_DIR_TX-������Ϣ
    ��ʼ����
      �����ʼ����
  */
  uint8 CAN_MsgDirection;
  
  /*
    ������
      ����Msg�������Ƿ��ж�
    ȡֵ��
      TRUE-ʹ��
      FALSE-��ֹ
    ��ʼ����
      �����ʼ����
  */
  boolean CAN_MsgInterrupt;
  
  /*
    ������
      �����жϻص�����
    ȡֵ��
      ��������Ϊ�޷���ֵ,�޲���(eg. void isr(void);)
    ��ʼ����
      �������ʼ������δ��ʼ���򲻻ᴥ���ж�
  */
  CAN_ISR_CALLBACK CAN_Isr;
 
}CAN_MSGOBJ_InitTypeDef;

typedef struct 
{
  /*
    ������
      CAN֡��ID
    ȡֵ��
      ����ýṹ�����ڷ��͹��ܣ���Ҫ���ݱ�׼֡/��չ֡������ID
        ID�ĳ��ȷ�Ϊ11λ��׼֡��29λ��չ֡����
        CAN_MSGOBJ_ID_STD ��ʾ��׼֡����CAN_MSGOBJ_InitTypeDef������id����ΪCAN_MSGOBJ_ID_STD
        ��ʱCAN_MsgID�Ϊ11λ�����ܳ���0x07FF��
        CAN_MSGOBJ_ID_EXT ��ʾ��չ֡����CAN_MSGOBJ_InitTypeDef������id����ΪCAN_MSGOBJ_ID_EXT
        ��ʱCAN_MsgID�Ϊ29λ�����ܳ���0x1FFFFFFF��
      ����ýṹ�����ڽ������ݣ����պ����Ὣ���յ�ID��ֵ���������
    ��ʼ����
      ���ݸýṹ�����;������������ڷ��͹��ܣ�ID�����ʼ����
  */
  uint32 CAN_MsgID;
  /*
    ������
      CAN֡��ʱ���
    ȡֵ��
      ����ýṹ�����ڷ��͹��ܣ��ñ���û������
      ����ýṹ�����ڽ������ݣ����պ����Ὣ���յ�Msg��������ʱ������������
    ��ʼ����
      ���س�ʼ����
  */
  uint16 CAN_MsgTimeStamp;
  /*
    ������
      CAN֡����������
    ȡֵ��
      ����ýṹ�����ڷ��͹��ܣ���Ҫ������û�����д��Ҫ���͵�����
      ����ýṹ�����ڽ������ݣ����պ����Ὣ���յ����ݸ��Ƶ����������
    ��ʼ����
      ���ݸýṹ�����;������������ڷ��͹��ܣ������������ʼ����
  */
  uint8  CAN_MsgDataBuffer[8];
  /*
    ������
      CAN֡�����ݳ���
    ȡֵ��
      ����ýṹ�����ڷ��͹��ܣ���Ҫ�趨Ҫ���͵����ݳ���
      ����ýṹ�����ڽ������ݣ����պ����Ὣ���յ����ݳ��ȸ�ֵ���������
    ��ʼ����
      ���ݸýṹ�����;������������ڷ��͹��ܣ�Ҫ�������ݳ��ȱ����ʼ����
  */
  uint8  CAN_MsgDataLength;
  /*
    ������
      CAN֡�����ȼ�
    ȡֵ��
      0--7
    ��ʼ����
      Ӧ�ñ����ٲ����ȼ�ʱ�� MCR[LPRIO_EN]����ʹ��
  */
  uint8  CAN_MsgPriority;
  
}CAN_MessageFormat_TypeDef;

extern CAN_MSGOBJ_InitTypeDef flexcan_msgobj_param_t[];
//FlexCANģ���ʼ������
void LPLD_CAN_Init(CAN_InitTypeDef );
//FlexCANģ�鷴��ʼ������
void LPLD_CAN_Deinit(CAN_InitTypeDef );
//FlexCANģ���ж�ʹ��
void LPLD_CAN_EnableIrq(CAN_InitTypeDef );
//FlexCANģ���жϽ�ֹ
void LPLD_CAN_DisableIrq(CAN_InitTypeDef );
//FlexCAN Msg��������ʼ��
void LPLD_CAN_InitMessageObject(CAN_MSGOBJ_InitTypeDef ,uint32 );
//FlexCAN ����Msg����
uint8 LPLD_CAN_TransmitMessage(CAN_MSGOBJ_InitTypeDef, CAN_MessageFormat_TypeDef * );
//FlexCAN �����жϴ�����
void LPLD_CAN_ReceivedMessage(CAN_MSGOBJ_InitTypeDef , CAN_MessageFormat_TypeDef * );


#endif /* __HW_CAN_H__ */
