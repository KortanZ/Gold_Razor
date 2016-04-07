/**
 * @file HW_CAN.c
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

#include "common.h"
#include "HW_CAN.h"
//FlexCANģ�����ò����ʺ���
static void LPLD_CAN_SetBaudRate(CAN_Type *,uint32 );
//FlexCAN ����жϱ�־λ����
static void LPLD_CAN_Interrupt_ClearPending(CAN_Type *, uint8 );
//FlexCAN ����жϱ�־λ����
static uint8 LPLD_CAN_Interrupt_GetFlag(CAN_Type *, uint8 );
//FlexCAN ����Msg����������
static uint16 LPLD_CAN_UnlockMsg(CAN_Type *);
//FlexCAN ʹ��Msg�������жϺ���
static void LPLD_CAN_EnableMsgInterrupt(CAN_Type *, uint8 );
//FlexCAN ����Msg��������CODE
static void LPLD_CAN_SetMsgCode(CAN_Type *, uint8 , uint8 );
//FlexCAN ���Msg��������CODE
static uint32 LPLD_CAN_GetMsgCode(CAN_Type *, uint8 );
//FlexCAN ���Msg��������TIMESTAMP
static uint16 LPLD_CAN_GetMsgTimeStamp(CAN_Type *, uint8 );
//FlexCAN ����Msg��������ID
void LPLD_CAN_SetMsgID(CAN_Type *, uint8 ,uint8, uint32 );
//FlexCAN ���Msg��������ID
static uint32 LPLD_CAN_GetMsgID(CAN_Type *, uint8 );
//FlexCAN ���Msg�������ĳ���
uint8 LPLD_CAN_GetMsgLength(CAN_Type *canx, uint8 MSG_NUM);
//FlexCAN ���Msg������������
static void LPLD_CAN_GetData(CAN_Type *canx, uint8 , uint8 ,  uint8 *);
//FlexCAN дMsg������������
static void LPLD_CAN_WriteData(CAN_Type *, uint8 , uint8, uint8 * );
//FlexCAN �����жϺ���
void LPLD_CAN_Transmit_Interrupt(CAN_Type *, uint8 );
//FlexCAN �����жϺ���
static void LPLD_CAN_Receive_Interrupt(CAN_Type *, uint8 );
//FlexCAN CANx���жϴ�����
static void LPLD_CAN_MB_ISR(void);
//����16��Msg�Ľṹ��
CAN_MSGOBJ_InitTypeDef  flexcan_msgobj_param_t[MSG_MAX_NO] = {0};
//����CANx Msg���жϻص�����
CAN_ISR_CALLBACK CAN0_ISR[MSG_MAX_NO];
CAN_ISR_CALLBACK CAN1_ISR[MSG_MAX_NO];

/*
 * LPLD_CAN_Init
 * �ڸú�����ʹ��CANx������CANx�Ĳ����ʣ�ѡ����Ӧ�Ĺ���ģʽ
 * ͨ��CAN_InitTypeDef�ṹ���CAN���г�ʼ����
 * 
 * ����:
 *    CAN_InitTypeDef--can_init_structure
 *                     ���嶨���HW_CAN.h can_init_structure
 *
 * ���:
 *    ��
 *
 */
void LPLD_CAN_Init(CAN_InitTypeDef can_init_structure)
{
  uint8 i;
  CAN_Type *canx = can_init_structure.CAN_Canx;
  uint32 baud = can_init_structure.CAN_BaudRate;
  uint8  mask_mode = can_init_structure.CAN_RxMaskMode;
  PortPinsEnum_Type tx_pin = can_init_structure.CAN_TxPin;
  PortPinsEnum_Type rx_pin = can_init_structure.CAN_RxPin;

  ASSERT(mask_mode <= CAN_MSGOBJ_GLOBAL_MASKING);
  ASSERT(baud <= CAN_BAUD_RATE_1MBPS);
    
#if defined(CPU_MK60DZ10) || defined(CPU_MK60D10)  
  OSC->CR |= OSC_CR_ERCLKEN_MASK | OSC_CR_EREFSTEN_MASK;
#elif defined(CPU_MK60F12) || defined(CPU_MK60F15)
  OSC0->CR |= OSC_CR_ERCLKEN_MASK | OSC_CR_EREFSTEN_MASK;
#endif    
  if(canx == CAN0)
    SIM->SCGC6 |= SIM_SCGC6_FLEXCAN0_MASK;
  else
    SIM->SCGC3 |= SIM_SCGC3_FLEXCAN1_MASK;
  
  if(canx == CAN0)
  {
    if(tx_pin == PTB18)//CAN0_TX
    {
      PORTB->PCR[18] = PORT_PCR_MUX(2)| PORT_PCR_PE_MASK | PORT_PCR_PS_MASK; 
    }
    else
    {
      PORTA->PCR[12] = PORT_PCR_MUX(2); 
    }

    if(rx_pin == PTB19)//CAN0_RX
    {
      PORTB->PCR[19] = PORT_PCR_MUX(2)| PORT_PCR_PE_MASK | PORT_PCR_PS_MASK; 
    }
    else
    {
      PORTA->PCR[13] = PORT_PCR_MUX(2); 
    }
  }
  else
  {
    if(tx_pin == PTC17)//CAN1_TX
    {
      PORTC->PCR[17] = PORT_PCR_MUX(2)| PORT_PCR_PE_MASK | PORT_PCR_PS_MASK; 
    }
    else
    {
      PORTE->PCR[24] = PORT_PCR_MUX(2)| PORT_PCR_PE_MASK | PORT_PCR_PS_MASK;
    }

    if(rx_pin == PTC16)//CAN1_RX
    {
      PORTC->PCR[16] = PORT_PCR_MUX(2)| PORT_PCR_PE_MASK | PORT_PCR_PS_MASK; 
    }
    else
    {
      PORTE->PCR[25] = PORT_PCR_MUX(2)| PORT_PCR_PE_MASK | PORT_PCR_PS_MASK;
    }
  } 
  //��ֹCAN����
  canx->MCR   |= CAN_MCR_MDIS_MASK;
  //ֻ����LPM_ACK = 1����²ſ���ѡ����Դ
  canx->CTRL1 |= CAN_CTRL1_CLKSRC_MASK;  //ѡ��peripheral clock��ΪCAN�����ʱ��Դ
                                         //���ô�λ������CANֹͣģʽ��
  //��ʱ�ӳ�ʼ����Ϻ�CAN����ʹ����Ϻ�
  //��Ƭ���Զ����붳��ģʽ
  //ֻ���ڶ���ģʽ�²������ô����CAN���߼Ĵ���
  //ʹ�ܶ���ģʽ 
  canx->MCR |= CAN_MCR_FRZ_MASK;
  canx->MCR &= ~CAN_MCR_MDIS_MASK; 
  
  while(!(canx->MCR & CAN_MCR_LPMACK_MASK));	

  //���������λ
  canx->MCR ^= CAN_MCR_SOFTRST_MASK;
  while(canx->MCR & CAN_MCR_SOFTRST_MASK);
            
  //�ȴ����붳��ģʽ 
  while(!(canx->MCR & CAN_MCR_FRZACK_MASK));
  
  if(mask_mode == CAN_MSGOBJ_GLOBAL_MASKING)
  {
    canx->MCR &= ~CAN_MCR_IRMQ_MASK;   //ʹ��ȫ��ƥ��Ĵ�����ֹ����ƥ�� 
  }
  else
  {
    canx->MCR |= CAN_MCR_IRMQ_MASK;   //ʹ��Msg����ƥ�� 
  }
  //��MB_MAX�����仺����������0
  for(i = 0;i < MSG_MAX_NO; i++)
  {
    canx->MB[i].CS    = 0x00000000;
    canx->MB[i].ID    = 0x00000000;
    canx->MB[i].WORD0 = 0x00000000;
    canx->MB[i].WORD1 = 0x00000000;        
  }
  
  canx->MCR |= CAN_MCR_SRXDIS_MASK ; //��ֹ���ҽ���
  //canx->MCR |= CAN_MCR_RFEN_MASK ;   //ʹ�ܽ���FIFO
  //canx->CTRL2 |= CAN_CTRL2_RFFN(0);
  //canx->MCR |= CAN_MCR_IDAM(0);
  
  //������صļĴ���
  canx->CTRL2 &= ~CAN_CTRL2_EACEN_MASK; //�����������IDEƥ�䣬RTR��ƥ��
  canx->CTRL2 &= ~CAN_CTRL2_RRS_MASK;  //���Զ�����Զ������֡����
  canx->CTRL2 &= ~CAN_CTRL2_MRP_MASK;   //ID���ȴ�������ƥ��

  //canx->CTRL1 |= CAN_CTRL1_LBUF_MASK;  //���͵�ʱ��ӵ�Msg��ʼ
  canx->CTRL1 &= ~CAN_CTRL1_LBUF_MASK;   //���͵�ʱ��ӵ����ȼ�����
                             
  //canx->CTRL1 |= CAN_CTRL1_LPB_MASK;  //loop ģʽ,���ڲ���
  canx->CTRL1 &= ~CAN_CTRL1_LPB_MASK;   //ʹ������ģʽ
  //����CAN����ͨ�ŵĲ�����
  LPLD_CAN_SetBaudRate(canx,baud);

  //���CAN���ɼ����� 
  canx->TIMER = 0x0000; 
   /*
  ���MCR��IRMQΪ1����ʾÿ�����䶼���Ե�������IDƥ��
  ע�⣺�����low cost MCUs�������õ�MCU����û�е���ƥ������ܡ�
          1\IDƥ���ѡ��free to receive״̬��������Ϊʤ�ߣ�
          ��ʤ��������Դӽ��ջ������ڽ����յ�֡ Move in ��MB�У�
          2\�������ID����ͬ�����䣬�����ȴ���ŵ͵��������ƥ�䣬���
          �����������non free to receive״̬����ôƥ����̽������
          ��һ������ֱ���ҵ�free to receive״̬��ID��ͬ�����䣻
          3\���ID����ͬ�����䶼����non free to receive״̬����ôƥ�����
          ��ֹͣ�����һ������ͬID������λ�ã���֡Move in ��MB�в��ҽ�����
          ���״̬���ó�OVERRUN��
          RXIMR[i]�洢�ڵ�Ƭ����RAM�У�ֻ����CAN����ģʽ�¿�д��
          ��ʱCANx_RXMGMASK��CANx_RX14MASK��CANx_RX15MASK��������
  */
  if(canx->MCR & CAN_MCR_IRMQ_MASK)
  {
    for(i = 0;i < MSG_MAX_NO; i++)
    {
      canx->RXIMR[i] = 0x1FFFFFFFL;//��������29λȫ������
    }
  } 
 /*
  ���MCR��IRMQΪ0����ʾʹ��ȫ��ƥ��Ĵ�������ƥ�䣬
          ��ʱCANx_RXMGMASK��CANx_RX14MASK��CANx_RX15MASK�����ã�
          CANx_RXMGMASK�����CANx_RX14MASK��CANx_RX15MASK���������Msg��
          IDƥ����̻�ֹͣ���ҵ��ĵ�һ��ID��ͬ������λ�ã����ܸ������Ƿ���
          free to receive״̬��
  */

  canx->RXMGMASK = 0x1FFFFFFF; //29λIDȫ��ƥ��            
  canx->RX14MASK = 0x1FFFFFFF;
  canx->RX15MASK = 0x1FFFFFFF; 
 
  canx->MCR &= ~(CAN_MCR_HALT_MASK); 
  //�ȵ����ڶ���ģʽ������ģʽ����ֹͣģʽ
  while( canx->MCR & CAN_MCR_FRZACK_MASK); 
  
  while( canx->MCR & CAN_MCR_NOTRDY_MASK);
}
/*
 * LPLD_CAN_SetBaudRate
 * ����CAN������,PLL������100Mhz
 * ����:
 *    CAN_Type *canx
 *      |___CAN0 --CAN0��ģ��
 *      |___CAN1 --CAN0��ģ��
 *    baud ������
 *      |__CAN_BAUD_RATE_50KBPS  --������50KBPS
 *      |__CAN_BAUD_RATE_100KBPS --������100KBPS
 *      |__CAN_BAUD_RATE_250KBPS --������250KBPS
 *      |__CAN_BAUD_RATE_500KBPS --������500KBPS
 *      |__CAN_BAUD_RATE_1MBPS   --������1MBPS
 *  �����
 *    ��
*/
static void LPLD_CAN_SetBaudRate(CAN_Type *canx,uint32 baud)
{
  uint8 prescale;
  //1��CAN����λ��ʱ�����ӣ�Time Quanta = SYNC_SEG + (PROP_SEG + PSEG1 + 2) + (PSEG2 + 1)��
  //SYNC_SEG =  1 ���̶�ֵ��
  ASSERT(baud <= CAN_BAUD_RATE_1MBPS);
  switch(baud)
  {
    case CAN_BAUD_RATE_1MBPS:
      {
        prescale = CAN_GET_PRESCALE(g_bus_clock,baud,8); 
        //����CAN����ͨ�ŵĲ�����
        canx->CTRL1 = (0 | CAN_CTRL1_PROPSEG(3)
                         | CAN_CTRL1_RJW(0)   
                         | CAN_CTRL1_PSEG1(0) 
                         | CAN_CTRL1_PSEG2(1)
                         | CAN_CTRL1_PRESDIV(prescale)); 
        break;
      }
    case CAN_BAUD_RATE_33KBPS:
    case CAN_BAUD_RATE_83KBPS:
    case CAN_BAUD_RATE_100KBPS:
    case CAN_BAUD_RATE_125KBPS:
      {
        //����time_quanta = 12 
        prescale = CAN_GET_PRESCALE(g_bus_clock,baud,12); 
        //����CAN����ͨ�ŵĲ�����
        canx->CTRL1 = (0 | CAN_CTRL1_PROPSEG(2) 
                         | CAN_CTRL1_RJW(2)  
                         | CAN_CTRL1_PSEG1(3) 
                         | CAN_CTRL1_PSEG2(3)
                         | CAN_CTRL1_PRESDIV(prescale)); 
        break;
      }
    case CAN_BAUD_RATE_50KBPS:
    case CAN_BAUD_RATE_500KBPS:
    case CAN_BAUD_RATE_250KBPS:
      {
        //����time_quanta = 12 
        prescale = CAN_GET_PRESCALE(g_bus_clock,baud,12); 
        //����CAN����ͨ�ŵĲ�����
        canx->CTRL1 = (0 | CAN_CTRL1_PROPSEG(2)
                         | CAN_CTRL1_RJW(1)  
                         | CAN_CTRL1_PSEG1(3) 
                         | CAN_CTRL1_PSEG2(3)
                         | CAN_CTRL1_PRESDIV(prescale)); 
        break;
      }
    default:break;
  }
}

/*
 * LPLD_CAN_Deinit
 * CAN����ʼ���������ڸú����н�ֹCANx������ʱ�ӣ���ֹģ���жϣ��ر�CANģ��
 * 
 * ����:
 *    CAN_InitTypeDef--can_init_structure
 *                     ���嶨���HW_CAN.h can_init_structure
 * ���:
 *    ��
 *
*/
void LPLD_CAN_Deinit(CAN_InitTypeDef can_init_structure)
{
  CAN_Type *canx = can_init_structure.CAN_Canx;
  
  if(canx == CAN0)
  {
    SIM->SCGC6 &= ~SIM_SCGC6_FLEXCAN0_MASK;
    disable_irq(CAN0_ORed_Message_buffer_IRQn);
  }
  else
  {
    SIM->SCGC3 &= ~SIM_SCGC3_FLEXCAN1_MASK;
    enable_irq(CAN1_ORed_Message_buffer_IRQn);
  }
  //��ֹCAN����
  canx->MCR |= CAN_MCR_MDIS_MASK;
  canx->MCR |= CAN_MCR_HALT_MASK; 
  canx->MCR |= CAN_MCR_FRZ_MASK;
}
/*
 * LPLD_CAN_EnableIrq
 * ʹ��CANģ���ж�
 * 
 * ����:
 *    CAN_InitTypeDef--can_init_structure
 *                     ���嶨���HW_CAN.h can_init_structure
 * ���:
 *    ��
 *
*/
void LPLD_CAN_EnableIrq(CAN_InitTypeDef can_init_structure)
{
  CAN_Type *canx = can_init_structure.CAN_Canx;
    
  if(canx == CAN0)
  {
    enable_irq(CAN0_ORed_Message_buffer_IRQn);
  }
  else if(canx == CAN1)
  {
    enable_irq(CAN1_ORed_Message_buffer_IRQn);
  }
}

/*
 * LPLD_CAN_DisableIrq
 * ��ֹCANģ���ж�
 * 
 * ����:
 *    CAN_InitTypeDef--can_init_structure
 *                     ���嶨���HW_CAN.h can_init_structure
 * ���:
 *    ��
 *
*/
void LPLD_CAN_DisableIrq(CAN_InitTypeDef can_init_structure)
{
  CAN_Type *canx = can_init_structure.CAN_Canx;
    
  if(canx == CAN0)
  {
    disable_irq(CAN0_ORed_Message_buffer_IRQn);
  }
  else if(canx == CAN1)
  {
    disable_irq(CAN1_ORed_Message_buffer_IRQn);
  }
}

/*
 * LPLD_CAN_InitMessageObject
 *
 * ����CAN Message buffer��Msg����ʽ��ͨ��CAN_MSGOBJ_InitTypeDef
 * �ṹ���CAN Message buffer���г�ʼ����
 * 
 * ����:
 *    CAN_MSGOBJ_InitTypeDef--can_msg_init_structure
 *                            ���嶨���HW_CAN.h CAN_MSGOBJ_InitTypeDef
 *    message_id
 *      ����message_id��id���ȸ���CAN_MSGOBJ_InitTypeDef�Ĳ�������
 *      id�ĳ��ȷ�Ϊ11λ��׼֡��29λ��չ֡����
 *      CAN_MSGOBJ_ID_STD ��ʾ��׼֡����CAN_MSGOBJ_InitTypeDef������id����ΪCAN_MSGOBJ_ID_STD
 *      ��ʱmessage_id�Ϊ11λ�����ܳ���0x0FFF��
 *      CAN_MSGOBJ_ID_EXT ��ʾ��չ֡����CAN_MSGOBJ_InitTypeDef������id����ΪCAN_MSGOBJ_ID_EXT
 *      ��ʱmessage_id�Ϊ29λ�����ܳ���0x1FFFFFFF��
 * ���:
 *    ��
 *
 */
void LPLD_CAN_InitMessageObject(CAN_MSGOBJ_InitTypeDef can_msg_init_structure,uint32 rx_id)
{ 
  uint8     msg_num_temp  = can_msg_init_structure.CAN_MsgNum;
  uint8     dir           = can_msg_init_structure.CAN_MsgDirection;
  CAN_Type *canx_ptr      = can_msg_init_structure.CAN_Canx;
  uint32    id_type       = can_msg_init_structure.CAN_MsgIdLength;
  uint32    cs_temp = CAN_MB_CS_CODE(CAN_MSGOBJ_RX_EMPTY);
  CAN_ISR_CALLBACK isr_func = can_msg_init_structure.CAN_Isr;
  uint32    id_temp;	
  
  if(dir == CAN_MSGOBJ_DIR_RX)
  {
    canx_ptr->MB[msg_num_temp].CS = CAN_MB_CS_CODE(CAN_MSGOBJ_RX_INACTIVE); 
    //����Msg��ID
    if(id_type == CAN_MSGOBJ_ID_STD)
    {
      id_temp =  CAN_MB_ID_STD(rx_id);
    }
    else
    {
      id_temp =  CAN_MB_ID_EXT(rx_id);
    }
    canx_ptr->MB[msg_num_temp].ID = id_temp;  
    canx_ptr->MB[msg_num_temp].CS = cs_temp | CAN_MB_CS_IDE(id_type);
  }
  if(can_msg_init_structure.CAN_MsgInterrupt == TRUE)
  {
    LPLD_CAN_EnableMsgInterrupt(canx_ptr,msg_num_temp);//ʹ��Msg�ж� 
    //����Msg�жϻص�����
    if(canx_ptr == CAN0)
    {
      if(isr_func != NULL)
      {
        CAN0_ISR[msg_num_temp] = isr_func;
      }
    }
    else
    {
      if(isr_func != NULL)
      {
        CAN1_ISR[msg_num_temp] = isr_func;
      }
    }
  }
  else
  {
    if(canx_ptr == CAN0)
    {
        CAN0_ISR[msg_num_temp] = NULL; 
    }
    else
    {
        CAN1_ISR[msg_num_temp] = NULL;
    }
  }
}
/*
 * LPLD_CAN_TransmitMessage
 * CAN ������Ϣ����
 * ����:
 *    CAN_MSGOBJ_InitTypeDef--can_msg_init_structure
 *                            ���嶨���HW_CAN.h CAN_MSGOBJ_InitTypeDef
 *    CAN_MessageFormat_TypeDef--*can_rx_msg
 *                            ���嶨���HW_CAN.h CAN_MessageFormat_TypeDef
 *    �ýṹ�����ڶ���CAN����Ϣ��ʽ����CAN������Ϣʱ�����CAN_MessageFormat_TypeDef����Ľṹ�������
 *    ��ȡ��Ϣ���洢��MSG�У�MSG�Ὣ��Ϣ���͵�CAN�����ϡ�
 *    �ýṹ���е���Ҫ����Ϊ ��ϢID��ʱ��������ݳ��ȡ��洢���ݵĻ�����
 * ���:
 *    1 �������
 *    0 ����ʧ��
 *
 */
uint8 LPLD_CAN_TransmitMessage(CAN_MSGOBJ_InitTypeDef can_msg_init_structure,
                               CAN_MessageFormat_TypeDef *can_tx_msg )
{
  uint8  request;
  uint8  msg_num_temp  = can_msg_init_structure.CAN_MsgNum;
  CAN_Type *canx_ptr   = can_msg_init_structure.CAN_Canx;
  uint32  id_type      = can_msg_init_structure.CAN_MsgIdLength;
  
  uint32  message_id = can_tx_msg->CAN_MsgID; ;
  uint8   priority = can_tx_msg->CAN_MsgPriority; 
  uint8  *in_data_buffer = can_tx_msg->CAN_MsgDataBuffer;
  uint8   in_data_length = can_tx_msg->CAN_MsgDataLength;
  uint32  id_temp;
  uint32  cs_temp = CAN_MB_CS_RTR(can_msg_init_structure.CAN_MsgRTR) | 
                    CAN_MB_CS_SRR(can_msg_init_structure.CAN_MsgSRR) |
                    CAN_MB_CS_IDE(can_msg_init_structure.CAN_MsgIdLength);
  
  if(msg_num_temp >= MSG_MAX_NO || in_data_length > 8)
  {
    return 0; // ������ֵ
  }
  //�������Msg�������е�CODE������CAN_MSGOBJ_TX_ONCE
  if( LPLD_CAN_GetMsgCode(canx_ptr,msg_num_temp) != CAN_MSGOBJ_TX_ONCE)
  {
    //����Msg��ID
    if(id_type == CAN_MSGOBJ_ID_STD)
    {
      id_temp =  CAN_MB_ID_STD(message_id);
    }
    else
    {
      id_temp =  CAN_MB_ID_EXT(message_id);
    }
    //����Msg�������е�CODE��дINACTIVE����
    canx_ptr->MB[msg_num_temp].CS = CAN_MB_CS_CODE(CAN_MSGOBJ_TX_INACTIVE) | cs_temp;
    canx_ptr->MB[msg_num_temp].ID = CAN_MB_ID_PRIO(priority) | id_temp;
    //��Msg��д��Ҫ���͵�����
    LPLD_CAN_WriteData(canx_ptr,msg_num_temp,in_data_length,in_data_buffer);
    //����Msg�������е�CODE��дTX_ONCE����ȴ��������
    canx_ptr->MB[msg_num_temp].CS = (canx_ptr->MB[msg_num_temp].CS & (~CAN_MB_CS_CODE_MASK)) | 
                                     CAN_MB_CS_CODE(CAN_MSGOBJ_TX_ONCE)|
                                     CAN_MB_CS_DLC(in_data_length);
    //������������жϣ�������Ϻ�ᴥ���ж�
    request = 1;
  }
  else
  {
    request = 0;
  }
  return (request);
}

/*
 * LPLD_CAN_ReceivedMessage
 * CAN ������պ������˺���һ����CAN�жϺ����е���
 * ����:
 *    CAN_MSGOBJ_InitTypeDef--can_msg_init_structure
 *                            ���嶨���HW_CAN.h CAN_MSGOBJ_InitTypeDef
 *    CAN_MessageFormat_TypeDef--*can_rx_msg
 *                            ���嶨���HW_CAN.h CAN_MessageFormat_TypeDef
 *    �ýṹ�����ڶ���CAN����Ϣ��ʽ����CAN�ɹ�������Ϣ�Ժ󣬻��MSG�н���Ϣ�洢��
 *    CAN_MessageFormat_TypeDef����Ľṹ������С�
 *    �ýṹ���е���Ҫ����Ϊ ��ϢID��ʱ��������ݳ��ȡ��洢���ݵĻ�����
 *    
 *  �����
 *    ��
 */
void LPLD_CAN_ReceivedMessage(CAN_MSGOBJ_InitTypeDef can_msg_init_structure,\
                              CAN_MessageFormat_TypeDef *can_rx_msg)
{
  uint32 message_code,i;
  volatile uint16 timer;
  uint8 rx_data[CAN_DATA_MAX_BYTES];
  uint8 data_length;
  uint16 time_stamp;
  uint32 msg_id;
  CAN_Type *canx = can_msg_init_structure.CAN_Canx;
  uint8 msg_num = can_msg_init_structure.CAN_MsgNum;
  //���Msg�������е�codeֵ
  message_code = LPLD_CAN_GetMsgCode(canx,msg_num);
  
  if ((message_code != CAN_MSGOBJ_RX_BUSY) && 
     (message_code != CAN_MSGOBJ_RX_OVERRUN))
  {
    //��ȡID(��ѡ)
    msg_id = LPLD_CAN_GetMsgID(canx, msg_num);
   
    //��ȡMsg�������������ݵĳ���
    data_length    = (uint8_t)LPLD_CAN_GetMsgLength(canx, msg_num);
    //��ȡMsg��������������
    LPLD_CAN_GetData(canx, msg_num,data_length,rx_data);
    //���Msg������ʱ���
    time_stamp = LPLD_CAN_GetMsgTimeStamp(canx, msg_num);
    
    for(i = data_length; i < 8; i++)
    {
       rx_data[i] = 0;
    }
    //��MSG�е���Ϣ�洢��can_rx_msg��
    can_rx_msg->CAN_MsgID = msg_id;
    can_rx_msg->CAN_MsgDataLength = data_length;
    can_rx_msg->CAN_MsgTimeStamp  = time_stamp;
    memcpy(can_rx_msg->CAN_MsgDataBuffer,rx_data,data_length);
     
    //��ȡ���ɼ�������������ǰMsg������
    timer = LPLD_CAN_UnlockMsg(canx);
    //���Msg���������жϱ�־λ
    LPLD_CAN_Interrupt_ClearPending(canx,msg_num);
    //�ٴ�д�����codeΪempty״̬
    LPLD_CAN_SetMsgCode(canx,msg_num,CAN_MSGOBJ_RX_EMPTY);
  }
  else
  {
    //�����������
    LPLD_CAN_Interrupt_ClearPending(canx,msg_num);
    //��ȡ���ɼ�������������ǰMsg������
    timer = LPLD_CAN_UnlockMsg(canx);
  }
}

/*
 * LPLD_CAN_Interrupt_ClearPending
 * ���Msg���жϱ�־λ
 * ����:
 *    CAN_Type *canx
 *      |___ CAN0 --CAN0��ģ��
 *      |___ CAN1 --CAN1��ģ��
 *    msg_num ѡ��Ҫ����жϱ�־��Msg������
 *      |___ MSG_NUM_0 --Msg������0
 *      |___ MSG_NUM_1 --Msg������1
 *      |___ MSG_NUM_2 --Msg������2
 *      |___ MSG_NUM_3 --Msg������3
 *      |___ MSG_NUM_4 --Msg������4
 *      ...... 
 *      |___ MSG_NUM_15 --Msg������15
 * ���:
 *   ��
 */
static void LPLD_CAN_Interrupt_ClearPending(CAN_Type *canx, uint8 msg_num)
{   
  if(msg_num < 32)
  {
    canx->IFLAG1 |= (1<<msg_num); 
  }
  else
  {
    canx->IFLAG2 |= (1<<(msg_num-32));
  }
}

/*
 * LPLD_CAN_Interrupt_GetFlag
 * ���CAN ���жϱ�־λ
 * ����:
 *    CAN_Type *canx
 *      |___ CAN0 --CAN0��ģ��
 *      |___ CAN1 --CAN1��ģ��
 *    msg_num ѡ��Ҫ����жϱ�־��Msg������
 *      |___ MSG_NUM_0 --Msg������0
 *      |___ MSG_NUM_1 --Msg������1
 *      |___ MSG_NUM_2 --Msg������2
 *      |___ MSG_NUM_3 --Msg������3
 *      |___ MSG_NUM_4 --Msg������4
 *      ...... 
 *      |___ MSG_NUM_15 --Msg������15
 * ���:
 *    ������Ҫ Msg���������жϱ�־λ
 */
static uint8 LPLD_CAN_Interrupt_GetFlag(CAN_Type *canx, uint8 msg_num)
{   
  uint8 status;
  if(msg_num < 32)
  {
    status = (canx->IFLAG1 >> msg_num) & 0x01; 
  }
  else
  {
    status = (canx->IFLAG2 >> (msg_num - 32) )& 0x01; 
  }
  return status;
}

/*
 * LPLD_CAN_UnlockMsg
 * �ú���ͨ����ȡ���ɼ�����������Msg
 * ����:
 *    canx--����CAN����ͨ��
 *      |__CAN0 --CAN0��ģ��
 *      |__CAN1 --CAN1��ģ��
 * ���:
 *    16λCAN���ɼ�������¼��ʱ���
 */
static uint16 LPLD_CAN_UnlockMsg(CAN_Type *canx)
{
  return (canx->TIMER);
}

/*
 * LPLD_CAN_EnableMsgInterrupt
 * �ú�������ʹ��Msg�ж�
 * 
 * ����:
 *    canx--����CAN����ͨ��
 *      |__CAN0 --CAN0��ģ��
 *      |__CAN1 --CAN1��ģ��
 *    msg_num ѡ����Ҫʹ���жϵ�Msg������
 *      |___ MSG_NUM_0 --Msg������0
 *      |___ MSG_NUM_1 --Msg������1
 *      |___ MSG_NUM_2 --Msg������2
 *      |___ MSG_NUM_3 --Msg������3
 *      |___ MSG_NUM_4 --Msg������4
 *      ...... 
 *      |___ MSG_NUM_15 --Msg������15
 * ���:
 *    ��
 *
 */
static void LPLD_CAN_EnableMsgInterrupt(CAN_Type *canx, uint8 msg_num)
{
  if(msg_num < 32)
  {
    canx->IMASK1 |= (1<<msg_num); 
  }
  else
  {
    canx->IMASK2 |= (1<<(msg_num-32));
  }
}

/*
 * LPLD_CAN_SetMsgCode
 * �ú�����������Msg��codeֵ
 * 
 * ����:
 *    canx--����CAN����ͨ��
 *      |__CAN0 --CAN0��ģ��
 *      |__CAN1 --CAN1��ģ��
 *    msg_num ѡ����Ҫ����CODE��Msg������
 *      |___ MSG_NUM_0 --Msg������0
 *      |___ MSG_NUM_1 --Msg������1
 *      |___ MSG_NUM_2 --Msg������2
 *      |___ MSG_NUM_3 --Msg������3
 *      |___ MSG_NUM_4 --Msg������4
 *      ...... 
 *      |___ MSG_NUM_15 --Msg������15
 *    code--��Ҫ���õ�codeֵ
 * ���:
 *    ��
 *
 */
static void LPLD_CAN_SetMsgCode(CAN_Type *canx, uint8 msg_num, uint8 code)
{
  //canx->MB[msg_num].CS &= (~CAN_MB_CS_CODE_MASK);
  canx->MB[msg_num].CS |= CAN_MB_CS_CODE(code);
}

/*
 * LPLD_CAN_GetMsgCode
 * �ú������ڻ��Msg��������codeֵ
 * 
 * ����:
 *    canx--����CAN����ͨ��
 *      |__CAN0 --CAN0��ģ��
 *      |__CAN1 --CAN1��ģ��
 *    msg_num ѡ����Ҫ���CODE��Msg������
 *      |___ MSG_NUM_0 --Msg������0
 *      |___ MSG_NUM_1 --Msg������1
 *      |___ MSG_NUM_2 --Msg������2
 *      |___ MSG_NUM_3 --Msg������3
 *      |___ MSG_NUM_4 --Msg������4
 *      ...... 
 *      |___ MSG_NUM_15 --Msg������15
 * ���:
 *     ������ӦMsg��������code
 *
 */
static uint32 LPLD_CAN_GetMsgCode(CAN_Type *canx, uint8 msg_num)
{
   return CAN_GET_MB_CS_CODE(canx->MB[msg_num].CS);
}
/*
 * LPLD_CAN_GetMsgTimeStamp
 * �ú������ڻ��Msg��������ʱ���
 * 
 * ����:
 *    canx--����CAN����ͨ��
 *      |__CAN0 --CAN0��ģ��
 *      |__CAN1 --CAN1��ģ��
 *    msg_num ѡ����Ҫ���ʱ�����Msg������
 *      |___ MSG_NUM_0 --Msg������0
 *      |___ MSG_NUM_1 --Msg������1
 *      |___ MSG_NUM_2 --Msg������2
 *      |___ MSG_NUM_3 --Msg������3
 *      |___ MSG_NUM_4 --Msg������4
 *      ...... 
 *      |___ MSG_NUM_15 --Msg������15
 * ���:
 *     ������ӦMsg��������ʱ���
 *
 */
static uint16 LPLD_CAN_GetMsgTimeStamp(CAN_Type *canx, uint8 msg_num)
{
  return CAN_GET_MB_CS_TIMESTAMP(canx->MB[msg_num].CS);
}
/*
 * LPLD_CAN_GetMsgID
 * �ú������ڻ��Msg��������IDֵ
 * 
 * ����:
 *    canx--����CAN����ͨ��
 *      |__CAN0 --CAN0��ģ��
 *      |__CAN1 --CAN1��ģ��
 *    msg_num ѡ����Ҫ���ID��Msg������
 *      |___ MSG_NUM_0 --Msg������0
 *      |___ MSG_NUM_1 --Msg������1
 *      |___ MSG_NUM_2 --Msg������2
 *      |___ MSG_NUM_3 --Msg������3
 *      |___ MSG_NUM_4 --Msg������4
 *      ...... 
 *      |___ MSG_NUM_15 --Msg������15
 * ���:
 *     ������ӦMsg��������ID
 *
 */
static uint32 LPLD_CAN_GetMsgID(CAN_Type *canx, uint8 msg_num)
{
  uint32 id_temp;
  if(CAN_GET_MB_CS_IDE(canx->MB[msg_num].CS) == CAN_MSGOBJ_ID_STD)
  {
    id_temp =  CAN_GET_MB_ID_STD(canx->MB[msg_num].ID);
  }
  else
  {
    id_temp =  CAN_GET_MB_ID_EXT(canx->MB[msg_num].ID);
  }
  return id_temp;
}
/*
 * LPLD_CAN_GetMsgLength
 * �ú������ڻ��Msg�����������ݳ���
 * 
 * ����:
 *    canx--����CAN����ͨ��
 *      |__CAN0 --CAN0��ģ��
 *      |__CAN1 --CAN1��ģ��
 *    msg_num ѡ����Ҫ������ݳ��ȵ�Msg������
 *      |___ MSG_NUM_0 --Msg������0
 *      |___ MSG_NUM_1 --Msg������1
 *      |___ MSG_NUM_2 --Msg������2
 *      |___ MSG_NUM_3 --Msg������3
 *      |___ MSG_NUM_4 --Msg������4
 *      ...... 
 *      |___ MSG_NUM_15 --Msg������15
 * ���:
 *     ���ݵĳ���
 *
 */
static uint8 LPLD_CAN_GetMsgLength(CAN_Type *canx, uint8 msg_num)
{
  return CAN_GET_MB_CS_LENGTH(canx->MB[msg_num].CS);
}

/*
 * LPLD_CAN_GetData
 * �ú������ڻ��Msg�������е�����
 * 
 * ����:
 *    canx--����CAN����ͨ��
 *      |__CAN0 --CAN0��ģ��
 *      |__CAN1 --CAN1��ģ��
 *    msg_num ѡ����Ҫ������ݵ�Msg������
 *      |___ MSG_NUM_0 --Msg������0
 *      |___ MSG_NUM_1 --Msg������1
 *      |___ MSG_NUM_2 --Msg������2
 *      |___ MSG_NUM_3 --Msg������3
 *      |___ MSG_NUM_4 --Msg������4
 *      ...... 
 *      |___ MSG_NUM_15 --Msg������15
 *    in_length
 *      |__������ݳ���
 *    *in_buffer
 *      |__������ݵĻ�����
 * ���:
 *    �� 
 */
static void LPLD_CAN_GetData(
    CAN_Type *canx, 
    uint8     msg_num, 
    uint8     in_length, 
    uint8    *in_buffer)
{
  int i;
  uint8  *pMBData;
  uint8  *pRecieve  = in_buffer;
  uint8  word_num   = (in_length - 1)/ 4; //Get the Message buffer word number
  uint8  rest_bytes = (in_length - 1)% 4; //Get the reset bytes of buffer
  if(word_num > 0)
  {  
    pMBData = (uint8*)&canx->MB[msg_num].WORD0+3;
    for(i = 0 ; i < 4 ; i++)   
    {
      pRecieve[i] = *pMBData--;
    }
    pMBData = (uint8*)&canx->MB[msg_num].WORD1+3;
  }
  else
  {
    pMBData = (uint8*)&canx->MB[msg_num].WORD0+3;
  }

  for(i = 0; i <= rest_bytes; i++)
  {
    pRecieve[i+(word_num<<2)] = *pMBData--;    
  }
}

/*
 * LPLD_CAN_WriteData
 * �ú���������Msg�������е�д����
 * 
 * ����:
 *    canx--����CAN����ͨ��
 *      |__CAN0 --CAN0��ģ��
 *      |__CAN1 --CAN1��ģ��
 *    msg_num ѡ����Ҫд���ݵ�Msg������
 *      |___ MSG_NUM_0 --Msg������0
 *      |___ MSG_NUM_1 --Msg������1
 *      |___ MSG_NUM_2 --Msg������2
 *      |___ MSG_NUM_3 --Msg������3
 *      |___ MSG_NUM_4 --Msg������4
 *      ...... 
 *      |___ MSG_NUM_15 --Msg������15
 *    in_length
 *      |__д�����ݳ���
 *    *in_buffer
 *      |__д�����ݵĻ�����
 * ���:
 *    �� 
 */
static void LPLD_CAN_WriteData(
    CAN_Type *canx, 
    uint8     msg_num, 
    uint8     in_length, 
    uint8    *in_buffer )
{
  int i;
  uint32 word[2] = {0};  
  uint8  word_num   = (in_length - 1)/ 4; //��� Msg ��Word ֵ
  uint8  rest_bytes = (in_length - 1)% 4; //���ʣ���ֽڵ�ֵ

  if( msg_num >= MSG_MAX_NO || in_length >8)
  {
      return; 
  }

  if(word_num < 1)
  {
    for (i = 0; i <= rest_bytes ; i++)
    {
      word[word_num] |=  (uint32)in_buffer[i] << (24-(i<<3));
    }
  }
  else
  {
    for (i = 0; i < 4; i++)
    {
      word[word_num-1] |= (uint32)in_buffer[i] << (24-(i<<3));
    }
    for (i = 0; i <= rest_bytes ; i++)
    {
      word[word_num] |=  (uint32)in_buffer[i+4] << (24-(i<<3));
    }
  }
  canx->MB[msg_num].WORD0 = word[0];
  canx->MB[msg_num].WORD1 = word[1];
}

/*
 * LPLD_CAN_Transmit_Interrupt
 * �ú������ڴ���Msg�����������жϺ���
 * 
 * ����:
 *    canx--����CAN����ͨ��
 *      |__CAN0 --CAN0��ģ��
 *      |__CAN1 --CAN1��ģ��
 *    msg_num ѡ����Ҫ�������жϵ�Msg������
 *      |___ MSG_NUM_0 --Msg������0
 *      |___ MSG_NUM_1 --Msg������1
 *      |___ MSG_NUM_2 --Msg������2
 *      |___ MSG_NUM_3 --Msg������3
 *      |___ MSG_NUM_4 --Msg������4
 *      ...... 
 *      |___ MSG_NUM_15 --Msg������15
 * ���:
 *    �� 
 */
void LPLD_CAN_Transmit_Interrupt(CAN_Type *canx, uint8 msg_num)
{
  if(LPLD_CAN_Interrupt_GetFlag(canx,msg_num))
  {
   LPLD_CAN_Interrupt_ClearPending(canx,msg_num);
   if(canx == CAN0)
   {
    if( CAN0_ISR[msg_num] != NULL)
    {
      CAN0_ISR[msg_num]();
    }
   }
   else if (canx == CAN1)
   {
    if( CAN1_ISR[msg_num] != NULL)
    {
      CAN1_ISR[msg_num]();
    }
   }
   else
   {
   }
   
  }
}

/*
 * LPLD_CAN_Receive_Interrupt
 * �ú������ڴ���Msg�����������жϺ���
 * 
 * ����:
 *    canx--����CAN����ͨ��
 *      |__CAN0 --CAN0��ģ��
 *      |__CAN1 --CAN1��ģ��
 *    msg_num ѡ����Ҫ��������жϵ�Msg������
 *      |___ MSG_NUM_0 --Msg������0
 *      |___ MSG_NUM_1 --Msg������1
 *      |___ MSG_NUM_2 --Msg������2
 *      |___ MSG_NUM_3 --Msg������3
 *      |___ MSG_NUM_4 --Msg������4
 *      ...... 
 *      |___ MSG_NUM_15 --Msg������15
 * ���:
 *    �� 
 */
static void LPLD_CAN_Receive_Interrupt(CAN_Type *canx, uint8 msg_num)
{
  if(LPLD_CAN_Interrupt_GetFlag(canx,msg_num) == 1)
  {
    //����������жϻص��������ڴ�ִ��
    if(canx == CAN0)
    {
      if( CAN0_ISR[msg_num] != NULL)
      {
          CAN0_ISR[msg_num]();
      }
    }
    else if (canx == CAN1)
    {
      if( CAN1_ISR[msg_num] != NULL)
      {
          CAN1_ISR[msg_num]();
      }
    }
    else
    {
      return;
    }
    LPLD_CAN_Interrupt_ClearPending(canx,msg_num);
  }
}
/*
 * LPLD_CAN_MB_ISR
 * CANx�жϴ�����
 * 
 * ����:
 *    ��
 * ���:
 *    �� 
 */
static void LPLD_CAN_MB_ISR(void)
{
  uint8 msg_obj;
  
  for (msg_obj = 0; msg_obj < MSG_MAX_NO; msg_obj++)
  {
    if(flexcan_msgobj_param_t[msg_obj].CAN_Canx != NULL)
    {
      if(flexcan_msgobj_param_t[msg_obj].CAN_MsgDirection == CAN_MSGOBJ_DIR_TX)
      {
        LPLD_CAN_Transmit_Interrupt(flexcan_msgobj_param_t[msg_obj].CAN_Canx,msg_obj);
      }
      else if(flexcan_msgobj_param_t[msg_obj].CAN_MsgDirection == CAN_MSGOBJ_DIR_RX)
      {
        LPLD_CAN_Receive_Interrupt(flexcan_msgobj_param_t[msg_obj].CAN_Canx,msg_obj);
      }
      else
      {}
    }
  }
}
/*
 * CAN0�жϴ�����
 * �������ļ�startup_K60.s�е��ж����������
 * �û������޸ģ������Զ������Ӧͨ���жϺ���
 */
void CAN0_MESS_IRQHandler(void)
{
#if (UCOS_II > 0u)
  OS_CPU_SR  cpu_sr = 0u;
  OS_ENTER_CRITICAL(); //��֪ϵͳ��ʱ�Ѿ��������жϷ����Ӻ���
  OSIntEnter();
  OS_EXIT_CRITICAL();
#endif
  LPLD_CAN_MB_ISR();
#if (UCOS_II > 0u)
  OSIntExit();          //��֪ϵͳ��ʱ�����뿪�жϷ����Ӻ���
#endif
}      
//29:  CAM 0 OR'ed Message buffer (0-15)

void CAN0_BUS_OFF_IRQHandler(void)
{
  CAN0->ESR1 = CAN_ESR1_BOFFINT_MASK;
}   //38:  CAM 0 Bus Off
void CAN0_ERR_IRQHandler(void)
{
  uint32_t status;

  status = CAN0->ESR1;

  if( status  & CAN_ESR1_ERRINT_MASK)
  {
    CAN0->ESR1 = status;		
  }	
}       //39:  CAM 0 Error
void CAN0_TW_IRQHandler(void)
{
  CAN0->ESR1 = CAN_ESR1_TWRNINT_MASK;
}        //40:  CAM 0 Transmit Warning
void CAN0_RW_IRQHandler(void)
{
  CAN0->ESR1 = CAN_ESR1_RWRNINT_MASK;
}        //41:  CAM 0 Receive Warning
void CAN0_WAKE_UP_IRQHandler(void){}   //42:  CAM 0 WakeUp
void CAN0_IMEU_IRQHandler(void){}      //43:  CAM 0 Individual Matching Elements Update (IMEU)
void CAN0_LR_IRQHandler(void){}        //44:  CAM 0 Lost receive

/*
 * CAN1�жϴ�����
 * �������ļ�startup_K60.s�е��ж����������
 * �û������޸ģ������Զ������Ӧͨ���жϺ���
 */
void CAN1_MESS_IRQHandler(void)
{
#if (UCOS_II > 0u)
  OS_CPU_SR  cpu_sr = 0u;
  OS_ENTER_CRITICAL(); //��֪ϵͳ��ʱ�Ѿ��������жϷ����Ӻ���
  OSIntEnter();
  OS_EXIT_CRITICAL();
#endif
  LPLD_CAN_MB_ISR();
#if (UCOS_II > 0u)
  OSIntExit();          //��֪ϵͳ��ʱ�����뿪�жϷ����Ӻ���
#endif
}
//37:  CAM 1 OR'ed Message buffer (0-15)

void CAN1_BUS_OFF_IRQHandler(void)
{
  CAN1->ESR1 = CAN_ESR1_BOFFINT_MASK;
}   //38:  CAM 1 Bus Off
void CAN1_ERR_IRQHandler(void)
{
  uint32_t status;

  status = CAN1->ESR1;

  if( status  & CAN_ESR1_ERRINT_MASK)
  {
    CAN1->ESR1 = status;		
  }	
}       //39:  CAM 1 Error
void CAN1_TW_IRQHandler(void)
{
  CAN1->ESR1 = CAN_ESR1_TWRNINT_MASK;
}        //40:  CAM 1 Transmit Warning
void CAN1_RW_IRQHandler(void)
{
  CAN1->ESR1 = CAN_ESR1_RWRNINT_MASK;
}        //41:  CAM 1 Receive Warning
void CAN1_WAKE_UP_IRQHandler(void){}   //42:  CAM 1 WakeUp
void CAN1_IMEU_IRQHandler(void){}      //43:  CAM 1 Individual Matching Elements Update (IMEU)
void CAN1_LR_IRQHandler(void){}        //44:  CAM 1 Lost receive


