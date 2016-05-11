/**
 * @file HW_ENET.c
 * @version 3.01[By LPLD]
 * @date 2013-10-21
 * @brief ENET�ײ�ģ����غ���
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
#include "HW_ENET.h"

//�û��Զ����жϷ���������
ENET_ISR_CALLBACK ENET_ISR[4]={NULL, NULL, NULL, NULL};

//�ڲ���������
static void LPLD_ENET_BDInit( void );
static void LPLD_ENET_Delay(uint32 time);


/*******************************************************************
 *
 *                ENETģ�麯��
 *
*******************************************************************/

/*
 * LPLD_ENET_Init
 * ENETģ���ʼ��������PHY�շ�����ʼ����MAC��ʼ����BD��ʼ��
 * 
 * ����:
 *    enet_init_struct--ENET��ʼ���ṹ�壬
 *                        ���嶨���ENET_InitTypeDef
 *
 * ���:
 *    ��
 */
void LPLD_ENET_Init(ENET_InitTypeDef enet_init_struct)
{
 
  uint16 usData;
 
  //ʹ��ENETʱ��
  SIM->SCGC2 |= SIM_SCGC2_ENET_MASK;

  //����������MPU������
  MPU->CESR = 0;         
        
  //��������������ʼ��
  LPLD_ENET_BDInit();
  
  //��λENET
  ENET->ECR = ENET_ECR_RESET_MASK;

  //�ȴ�����8��ʱ������
  for( usData = 0; usData < 10; usData++ )
  {
    asm( "NOP" );
  }
    
  //��ʼ��MII�ӿ�
  LPLD_ENET_MiiInit(g_bus_clock/1000000/*MHz*/);       
        
  //ʹ���жϲ��������ȼ�
  //set_irq_priority (76, 6);
  enable_irq(ENET_Transmit_IRQn);        //ENET�����ж�
  //set_irq_priority (77, 6);
  enable_irq(ENET_Receive_IRQn);         //ENET�����ж�
  //set_irq_priority (78, 6);
  enable_irq(ENET_Error_IRQn);           //ENET���������ж�
  
  if(enet_init_struct.ENET_TxIsr != NULL)
  {
    ENET_ISR[ENET_TXF_ISR] = enet_init_struct.ENET_TxIsr;
  }
  if(enet_init_struct.ENET_RxIsr != NULL)
  {
    ENET_ISR[ENET_RXF_ISR] = enet_init_struct.ENET_RxIsr;
  }
  if(enet_init_struct.ENET_1588Isr != NULL)
  {
    ENET_ISR[ENET_1588_ISR] = enet_init_struct.ENET_1588Isr;
  }
  if(enet_init_struct.ENET_ErrIsr != NULL)
  {
    ENET_ISR[ENET_ERR_ISR] = enet_init_struct.ENET_ErrIsr;
  }

  //ʹ��GPIO���Ÿ��ù���
  PORTB->PCR[0]  = PORT_PCR_MUX(4);  //GPIO;//RMII0_MDIO/MII0_MDIO
  PORTB->PCR[1]  = PORT_PCR_MUX(4);  //GPIO;//RMII0_MDC/MII0_MDC    
  PORTA->PCR[14] = PORT_PCR_MUX(4);  //RMII0_CRS_DV/MII0_RXDV
  PORTA->PCR[12] = PORT_PCR_MUX(4);  //RMII0_RXD1/MII0_RXD1
  PORTA->PCR[13] = PORT_PCR_MUX(4);  //RMII0_RXD0/MII0_RXD0
  PORTA->PCR[15] = PORT_PCR_MUX(4);  //RMII0_TXEN/MII0_TXEN
  PORTA->PCR[16] = PORT_PCR_MUX(4);  //RMII0_TXD0/MII0_TXD0
  PORTA->PCR[17] = PORT_PCR_MUX(4);  //RMII0_TXD1/MII0_TXD1
  
    
  //�ȴ�PHY�շ�����λ���
  do
  {
    LPLD_ENET_Delay( ENET_LINK_DELAY );
    usData = 0xffff;
    LPLD_ENET_MiiRead(CFG_PHY_ADDRESS, PHY_PHYIDR1, &usData );     
  } while( usData == 0xffff );

#ifdef ENET_PRINT_PHY_INFO
  printf("PHY_PHYIDR1=0x%X\r\n",usData);
  LPLD_ENET_MiiRead(CFG_PHY_ADDRESS, PHY_PHYIDR2, &usData );
  printf("PHY_PHYIDR2=0x%X\r\n",usData); 
  LPLD_ENET_MiiRead(CFG_PHY_ADDRESS, PHY_ANLPAR, &usData );
  printf("PHY_ANLPAR=0x%X\r\n",usData);
  LPLD_ENET_MiiRead(CFG_PHY_ADDRESS, PHY_ANLPARNP, &usData );
  printf("PHY_ANLPARNP=0x%X\r\n",usData);
  LPLD_ENET_MiiRead(CFG_PHY_ADDRESS, PHY_PHYSTS, &usData );
  printf("PHY_PHYSTS=0x%X\r\n",usData);
  LPLD_ENET_MiiRead(CFG_PHY_ADDRESS, PHY_MICR, &usData );
  printf("PHY_MICR=0x%X\r\n",usData);
  LPLD_ENET_MiiRead(CFG_PHY_ADDRESS, PHY_MISR, &usData );
  printf("PHY_MISR=0x%X\r\n",usData);
#endif 
  
  //��ʼ�Զ�Э��
  LPLD_ENET_MiiWrite(CFG_PHY_ADDRESS, PHY_BMCR, ( PHY_BMCR_AN_RESTART | PHY_BMCR_AN_ENABLE ) );

#ifdef ENET_PRINT_PHY_INFO
  LPLD_ENET_MiiRead(CFG_PHY_ADDRESS, PHY_BMCR, &usData );
  printf("PHY_BMCR=0x%X\r\n",usData);
#endif 
  
  //�ȴ��Զ�Э�����
  do
  {
    LPLD_ENET_Delay( ENET_LINK_DELAY );
    LPLD_ENET_MiiRead(CFG_PHY_ADDRESS, PHY_BMSR, &usData );

  } while( !( usData & PHY_BMSR_AN_COMPLETE ) );

#ifdef ENET_PRINT_PHY_INFO
    printf("PHY_BMSR=0x%X\r\n",usData);
#endif 
    
  //����Э�̽������ENETģ��
  LPLD_ENET_MiiRead(CFG_PHY_ADDRESS, PHY_STATUS, &usData );  

#ifdef ENET_PRINT_PHY_INFO
  printf("PHY_STATUS=0x%X\r\n",usData);
#endif 
  
  //������������ַ��ϣ�Ĵ���
  ENET->IALR = 0;
  ENET->IAUR = 0;
  ENET->GALR = 0;
  ENET->GAUR = 0;
  
  //����ENETģ��MAC��ַ
  LPLD_ENET_SetAddress(enet_init_struct.ENET_MacAddress);
    
  //���ý��տ��ƼĴ�������󳤶ȡ�RMIIģʽ������CRCУ���
  ENET->RCR = ENET_RCR_MAX_FL(CFG_ENET_MAX_PACKET_SIZE) | ENET_RCR_MII_MODE_MASK | ENET_RCR_CRCFWD_MASK | ENET_RCR_RMII_MODE_MASK;

  //������ͽ��տ���
  ENET->TCR = 0;
        
  //ͨѶ��ʽ����
  if( usData & PHY_DUPLEX_STATUS )
  {
    //ȫ˫��
    ENET->RCR &= (uint32)~ENET_RCR_DRT_MASK;
    ENET->TCR |= ENET_TCR_FDEN_MASK;
  }
  else
  {
    //��˫��
    ENET->RCR |= ENET_RCR_DRT_MASK;
    ENET->TCR &= (uint32)~ENET_TCR_FDEN_MASK;
  }
  
  //ͨ����������
  if( usData & PHY_SPEED_STATUS )
  {
    //10Mbps
    ENET->RCR |= ENET_RCR_RMII_10T_MASK;
  }

  //ʹ�÷���ǿ�ͻ�����������
  ENET->ECR = 0;
  
  
  //���ý��ջ���������
  ENET->MRBR = (unsigned short) CFG_ENET_RX_BUFFER_SIZE;

  //ָ���ν��ջ��������������е�ͷ��ַ
  ENET->RDSR = ( uint32 ) &( xENETRxDescriptors[ 0 ] );

  //ָ���η��ͻ��������������е�ͷ��ַ
  ENET->TDSR = ( uint32 ) xENETTxDescriptors;

  //���ENET�ж��¼�
  ENET->EIR = ( uint32 ) -1;

  //ʹ���ж�
  ENET->EIMR = 0 
            | ENET_EIMR_RXF_MASK  //�����ж�
            | ENET_EIMR_TXF_MASK  //�����ж�
            //ENET�ж�
            | ENET_EIMR_UN_MASK | ENET_EIMR_RL_MASK | ENET_EIMR_LC_MASK | ENET_EIMR_BABT_MASK | ENET_EIMR_BABR_MASK | ENET_EIMR_EBERR_MASK
            | ENET_EIMR_RXB_MASK
            ;

  //ʹ��ENETģ��
  ENET->ECR |= ENET_ECR_ETHEREN_MASK;

  //�������ջ�����Ϊ��
  ENET->RDAR = ENET_RDAR_RDAR_MASK;
}


/*
 * LPLD_ENET_SetIsr
 * ENETģ���жϺ�������
 * 
 * ����:
 *    type--�ж�����
 *      |__ENET_RXF_ISR   -�����ж�
 *      |__ENET_TXF_ISR   -�����ж�
 *    isr_func--�û��жϳ�����ڵ�ַ
 *      |__�û��ڹ����ļ��¶�����жϺ���������������Ϊ:�޷���ֵ,�޲���(eg. void isr(void);)
 *
 * ���:
 *    0--���ô���
 *    1--���óɹ�
 *
 */
uint8 LPLD_ENET_SetIsr(uint8 type, ENET_ISR_CALLBACK isr_func)
{
  if(type>4)
    return 0;
  
  ENET_ISR[type] = isr_func;
  return 1;
}


/*
 * Eth_RX_IRQHandler
 * ENET�����жϵײ���ں���
 * 
 * �û������޸ģ������Զ������Ӧͨ���жϺ���
 */
void Eth_RX_IRQHandler(void)
{   
  ENET->EIR |= ENET_EIMR_RXF_MASK; 
    
  //�����û��Զ����жϷ���
  if(ENET_ISR[ENET_RXF_ISR] != NULL)
  {
    ENET_ISR[ENET_RXF_ISR]();  
  }
}

/*
 * Eth_TX_IRQHandler
 * ENET�����жϵײ���ں���
 * 
 * �û������޸ģ������Զ������Ӧͨ���жϺ���
 */
void Eth_TX_IRQHandler(void)
{  
  ENET->EIR |= ENET_EIMR_TXF_MASK; 
    
  //�����û��Զ����жϷ���
  if(ENET_ISR[ENET_TXF_ISR] != NULL)
  {
    ENET_ISR[ENET_TXF_ISR]();  
  }
}

/*
 * Eth_IEEE1588_IRQHandler
 * IEEE1588�жϵײ���ں���
 * 
 * �û������޸ģ������Զ������Ӧͨ���жϺ���
 */
void Eth_IEEE1588_IRQHandler(void)
{    
  //�����û��Զ����жϷ���
  if(ENET_ISR[ENET_1588_ISR] != NULL)
  {
    ENET_ISR[ENET_1588_ISR]();  
  }
}

/*
 * Eth_Err_Misc_IRQHandler
 * ���������жϵײ���ں���
 * 
 * �û������޸ģ������Զ������Ӧͨ���жϺ���
 */
void Eth_Err_Misc_IRQHandler(void)
{  
  //�����û��Զ����жϷ���
  if(ENET_ISR[ENET_ERR_ISR] != NULL)
  {
    ENET_ISR[ENET_ERR_ISR](); 
  } 
}

/*
 * LPLD_ENET_Delay
 * ENETģ���ڲ���ʱ����
 * 
 * ����:
 *    time--�ӳٴ�С
 *
 * ���:
 *    ��
 */
static void LPLD_ENET_Delay(uint32 time)
{
  uint32 i = 0,j = 0;
  
  for(i = 0;i < time;i++)
  {
    for(j = 0;j < 50000;j++);
  }
}


/*
 * LPLD_ENET_BDInit
 * ��������������ʼ��
 * 
 * ����:
 *    ��
 *
 * ���:
 *    ��
 */
static void LPLD_ENET_BDInit( void )
{
  uint32 ux;
  uint8 *pcBufPointer;
  
  //Ѱ��<��������������ռ�>�е�16�ֽڶ���ĵ�ַ��������λΪ0����ʼ��ַ
  pcBufPointer = &( xENETTxDescriptors_unaligned[ 0 ] );
  while( ( ( uint32 ) pcBufPointer & 0x0fUL ) != 0 )
  {
    pcBufPointer++;
  }
  xENETTxDescriptors = ( ENET_NbufTypeDef * ) pcBufPointer;
  
  //Ѱ��<��������������ռ�>�е�16�ֽڶ���ĵ�ַ
  pcBufPointer = &( xENETRxDescriptors_unaligned[ 0 ] );
  while( ( ( uint32 ) pcBufPointer & 0x0fUL ) != 0 )
  {
    pcBufPointer++;
  }
  xENETRxDescriptors = ( ENET_NbufTypeDef * ) pcBufPointer;
  
  //���ͻ�������������ʼ��
  for( ux = 0; ux < CFG_NUM_ENET_TX_BUFFERS; ux++ )
  {
    xENETTxDescriptors[ ux ].status = 0;
    xENETTxDescriptors[ ux ].data = 0;
    xENETTxDescriptors[ ux ].length = 0;
  }
  
  //Ѱ��<���ջ������ռ�>�е�16�ֽڶ���ĵ�ַ
  pcBufPointer = &( ucENETRxBuffers[ 0 ] );
  while( ( ( uint32 ) pcBufPointer & 0x0fUL ) != 0 )
  {
    pcBufPointer++;
  }
  
  //���ջ�������������ʼ��
  for( ux = 0; ux < CFG_NUM_ENET_RX_BUFFERS; ux++ )
  {
    xENETRxDescriptors[ ux ].status = RX_BD_E;
    xENETRxDescriptors[ ux ].length = 0;
    xENETRxDescriptors[ ux ].data = (uint8 *)__REV((uint32)pcBufPointer);
    pcBufPointer += CFG_ENET_RX_BUFFER_SIZE;
  
  }
  
  //���û��������������������е����һ��״̬λΪWrap
  xENETTxDescriptors[ CFG_NUM_ENET_TX_BUFFERS - 1 ].status |= TX_BD_W;
  xENETRxDescriptors[ CFG_NUM_ENET_RX_BUFFERS - 1 ].status |= RX_BD_W;
  
  uxNextRxBuffer = 0;
  uxNextTxBuffer = 0;
}

/*
 * LPLD_ENET_MacSend
 * ��̫֡���ͺ���
 * 
 * ����:
 *    *ch--����֡ͷ��ַ��������֡Ϊ��̫֡���������Ŀ�ĵ�ַ��Դ��ַ�����͵ȡ�
 *    len--����֡���ȡ�
 *
 * ���:
 *    ��
 */
void LPLD_ENET_MacSend(uint8 *ch, uint16 len)
{
  
  //��鵱ǰ���ͻ������������Ƿ����
  while( xENETTxDescriptors[ uxNextTxBuffer ].status & TX_BD_R);
  
  //���÷��ͻ�����������
  xENETTxDescriptors[ uxNextTxBuffer ].data = (uint8 *)__REV((uint32)ch);
  xENETTxDescriptors[ uxNextTxBuffer ].length = __REVSH(len);
  xENETTxDescriptors[ uxNextTxBuffer ].status = ( TX_BD_R | TX_BD_L | TX_BD_TC | TX_BD_W );
  
  uxNextTxBuffer++;
  if( uxNextTxBuffer >= CFG_NUM_ENET_TX_BUFFERS )
  {
    uxNextTxBuffer = 0;
  }
  
  //ʹ�ܷ���
  ENET->TDAR = ENET_TDAR_TDAR_MASK;
  
}


/*
 * LPLD_ENET_MacRecv
 * ��̫֡���պ���
 * 
 * ����:
 *    *ch--��������֡ͷ��ַ��
 *    *len--����֡���ȵ�ַ��
 *
 * ���:
 *    ��
 */
uint8 LPLD_ENET_MacRecv(uint8 *ch, uint16 *len)
{
  uint8 *prvRxd;
  *len = 0;
  uxNextRxBuffer = 0; 
  
  //Ѱ��Ϊ�ǿյĽ��ջ����������� 
  while( (xENETRxDescriptors[ uxNextRxBuffer ].status & RX_BD_E)!=0 )
  {
    uxNextRxBuffer++; 
    if( uxNextRxBuffer >= CFG_NUM_ENET_RX_BUFFERS )
    {
      uxNextRxBuffer = 0; 
      return 1;
    } 
    
  }
  
  //��ȡ���ջ�����������
  *len  =  __REVSH(xENETRxDescriptors[ uxNextRxBuffer ].length);
  prvRxd =  (uint8 *)__REV((uint32)xENETRxDescriptors[ uxNextRxBuffer ].data);      
  memcpy((void *)ch, (void *)prvRxd, *len);      
  
  //������ջ�����������״̬��־Empty
  xENETRxDescriptors[ uxNextRxBuffer ].status |= RX_BD_E;
  ENET->RDAR = ENET_RDAR_RDAR_MASK;	
  return 0;
}


/*
 * LPLD_ENET_HashAddress
 * ���ɸ�����MAC��ַ�Ĺ�ϣ��
 * 
 * ����:
 *    *addr--6�ֽڵ�ַָ�롣
 *
 * ���:
 *    32λCRCУ��ĸ�6λ
 */
uint8 LPLD_ENET_HashAddress(const uint8* addr)
{
  uint32 crc;
  uint8 byte;
  int i, j;
  
  crc = 0xFFFFFFFF;
  for(i=0; i<6; ++i)
  {
    byte = addr[i];
    for(j=0; j<8; ++j)
    {
      if((byte & 0x01)^(crc & 0x01))
      {
        crc >>= 1;
        crc = crc ^ 0xEDB88320;
      }
      else
        crc >>= 1;
      byte >>= 1;
    }
  }
  return (uint8)(crc >> 26);
}


/*
 * LPLD_ENET_SetAddress
 * ����MAC�����ַ
 * 
 * ����:
 *    *pa--6�ֽڵ������ַָ�롣
 *
 * ���:
 *    ��
 */
void LPLD_ENET_SetAddress(const uint8 *pa)
{
  uint8 crc;
  
  //���������ַ
  ENET->PALR = (uint32)((pa[0]<<24) | (pa[1]<<16) | (pa[2]<<8) | pa[3]);
  ENET->PAUR = (uint32)((pa[4]<<24) | (pa[5]<<16));
  
  //���������ַ���㲢���ö�����ַ��ϣ�Ĵ�����ֵ
  crc = LPLD_ENET_HashAddress(pa);
  if(crc >= 32)
    ENET->IAUR |= (uint32)(1 << (crc - 32));
  else
    ENET->IALR |= (uint32)(1 << crc);
}



/*******************************************************************
 *
 *                PHY�豸MII�ӿں���
 *
*******************************************************************/

/*
 * LPLD_ENET_MiiInit
 * ����ENETģ���MII�ӿ�ʱ�ӣ�����Ƶ��Ϊ2.5MHz
 * MII_SPEED = ϵͳʱ�� / (2.5MHz * 2)
 * 
 * ����:
 *    sys_clk_mhz--ϵͳ��Ƶ
 *
 * ���:
 *    ��
 */
void LPLD_ENET_MiiInit(uint32 sys_clk_mhz)
{
  ENET->MSCR = 0 | ENET_MSCR_MII_SPEED((2*sys_clk_mhz/5)+1);
}


/*
 * LPLD_ENET_MiiWrite
 * MII�ӿ�д
 * 
 * ����:
 *    phy_addr--�����շ�����ַ
 *    reg_addr--�Ĵ�����ַ
 *    data--д�������
 *
 * ���:
 *    1--д��ʱ
 *    0--д��ɹ�
 */
uint8 LPLD_ENET_MiiWrite(uint16 phy_addr, uint16 reg_addr, uint16 data)
{
  uint32 timeout;
  
  //���MII�ж��¼�
  ENET->EIR = ENET_EIR_MII_MASK;
  
  //��ʼ��MII����֡�Ĵ���
  ENET->MMFR = 0
            | ENET_MMFR_ST(0x01)
            | ENET_MMFR_OP(0x01)
            | ENET_MMFR_PA(phy_addr)
            | ENET_MMFR_RA(reg_addr)
            | ENET_MMFR_TA(0x02)
            | ENET_MMFR_DATA(data);
  
  //�ȴ�MII��������ж��¼�
  for (timeout = 0; timeout < MII_TIMEOUT; timeout++)
  {
    if (ENET->EIR & ENET_EIR_MII_MASK)
      break;
  }
  
  if(timeout == MII_TIMEOUT) 
    return 1;
  
  //���MII�ж��¼�
  ENET->EIR = ENET_EIR_MII_MASK;
  
  return 0;
}


/*
 * LPLD_ENET_MiiRead
 * MII�ӿڶ�
 * 
 * ����:
 *    phy_addr--�����շ�����ַ
 *    reg_addr--�Ĵ�����ַ
 *    *data--���������ݵ�ַָ��
 *
 * ���:
 *    1--����ʱ
 *    0--��ȡ�ɹ�
 */
uint8 LPLD_ENET_MiiRead(uint16 phy_addr, uint16 reg_addr, uint16 *data)
{
  uint32 timeout;
  
  //���MII�ж��¼�
  ENET->EIR = ENET_EIR_MII_MASK;
  
  //��ʼ��MII����֡�Ĵ���
  ENET->MMFR = 0
            | ENET_MMFR_ST(0x01)
            | ENET_MMFR_OP(0x2)
            | ENET_MMFR_PA(phy_addr)
            | ENET_MMFR_RA(reg_addr)
            | ENET_MMFR_TA(0x02);
  
  //�ȴ�MII��������ж��¼�
  for (timeout = 0; timeout < MII_TIMEOUT; timeout++)
  {
    if (ENET->EIR & ENET_EIR_MII_MASK)
      break;
  }
  
  if(timeout == MII_TIMEOUT) 
    return 1;
  
  //���MII�ж��¼�
  ENET->EIR = ENET_EIR_MII_MASK;
  
  *data = ENET->MMFR & 0x0000FFFF;
  
  return 0;
}
