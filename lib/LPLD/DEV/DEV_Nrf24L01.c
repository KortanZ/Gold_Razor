/**
 * @file DEV_Nrf24L01.c
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
#include "DEV_Nrf24L01.h"
#include "HW_GPIO.h"

static uint8 LPLD_Nrf24L01_WriteBuf(uint8 reg,uint8 *pbuf ,uint8 len);
static uint8 LPLD_Nrf24L01_ReadBuf(uint8 reg,uint8 *pbuf,uint8 len);
static uint8 LPLD_Nrf24L01_WriteReg(uint8 reg,uint8 value);
static uint8 LPLD_Nrf24L01_ReadReg(uint8 reg);
static uint8 LPLD_Nrf24L01_CheckID(void);
static void Nrf24L01_DelayUs(uint16 t);

uint8 TX_ADDRESS[NRF24L01_TX_ADR_LEN]={0x34,0x43,0x10,0x10,0x02}; //���͵�ַ
uint8 RX_ADDRESS[NRF24L01_RX_ADR_LEN]={0x34,0x43,0x10,0x10,0x02}; //���յ�ַ(������ַ,�����ڽ���ģʽ)
//NRF24L01��λ֮�����ڼ��
// NRF24L01_RX_ADDR_P0�ĸ�λֵ�Ƿ�Ϊ0xE7E7E7E7
// NRF24L01_RX_ADDR_P1�ĸ�λֵ�Ƿ�Ϊ0xC2C2C2C2
// NRF24L01_TX_ADDR�ĸ�λֵ�Ƿ�Ϊ0xE7E7E7E7
uint8 NRF24L01_RX_ADDR_P0_RESET_BUF[5];
uint8 NRF24L01_RX_ADDR_P1_RESET_BUF[5];
uint8 NRF24L01_TX_ADDR_RESET_BUF[5];

SPI_InitTypeDef spi_init_param;
GPIO_InitTypeDef ce_io_param;
/*
 * LPLD_Nrf24L01_Init
 * Nrf24L01��ʼ������������SPIģ�飬ѡ��Nrf24L01 CE����
 * 
 * ����:
 *    ��
 *
 * ���:
 *    1 ���óɹ�
 */
uint8 LPLD_Nrf24L01_Init(void)
{
  //����SPI
  spi_init_param.SPI_SPIx = NRF24L01_SPIX;
  spi_init_param.SPI_SckDivider = SPI_SCK_DIV_32;//1.56Mhz
  spi_init_param.SPI_Pcs0Pin = NRF24L01_PCS0;
  spi_init_param.SPI_SckPin  = NRF24L01_SCK;
  spi_init_param.SPI_MosiPin = NRF24L01_MOSI;
  spi_init_param.SPI_MisoPin = NRF24L01_MISO;
  
  spi_init_param.SPI_TxCompleteIntIsr = NULL;
  spi_init_param.SPI_QueueEndIntIsr = NULL;
  spi_init_param.SPI_TxFIFO_FillIntIsr = NULL;
  spi_init_param.SPI_TxFIFO_UnderflowIntIsr = NULL;
  spi_init_param.SPI_RxFIFO_DrainIntIsr = NULL;
  spi_init_param.SPI_RxFIFO_OverflowIntIsr = NULL;
  //����CE
  ce_io_param.GPIO_PTx  = NRF24L01_CE_PTX;
  ce_io_param.GPIO_Pins = NRF24L01_CE_IOX;
  ce_io_param.GPIO_Dir  = DIR_OUTPUT;
  ce_io_param.GPIO_Output = OUTPUT_L;

  LPLD_GPIO_Init(ce_io_param);
  LPLD_SPI_Init(spi_init_param);
  
  return 1;
}

/*
 * LPLD_Nrf24L01_TxModeInit
 * Nrf24L01����ģʽ��ʼ��
 * 
 * ����:
 *    ��
 *
 * ���:
 *    Nrf24L01�Ĵ�������״̬
 */
uint8 LPLD_Nrf24L01_TxModeInit(void)
{
  uint8 Temp;
  
  NRF24L01_CE_L;  
  // оƬ�ϵ縴λ��
  // �ֱ��ȡNRF24L01_RX_ADDR_P0��NRF24L01_RX_ADDR_P1��NRF24L01_TX_ADDR��ֵ
  // �鿴��������
  // NRF24L01_RX_ADDR_P0�ĸ�λֵ�Ƿ�Ϊ0xE7E7E7E7
  // NRF24L01_RX_ADDR_P1�ĸ�λֵ�Ƿ�Ϊ0xC2C2C2C2
  // NRF24L01_TX_ADDR�ĸ�λֵ�Ƿ�Ϊ0xE7E7E7E7
  // �����ȷ֤��SPI��дû�����⣬��֮��Ȼ
  LPLD_Nrf24L01_CheckID();
    
  Temp=LPLD_Nrf24L01_WriteReg(NRF24L01_FLUSE_TX,0xFF);
  
  Temp=LPLD_Nrf24L01_WriteBuf(NRF24L01_WRITE_REG + NRF24L01_TX_ADDR,TX_ADDRESS,NRF24L01_TX_ADR_LEN);
  
  Temp=LPLD_Nrf24L01_WriteReg(NRF24L01_WRITE_REG + NRF24L01_EN_AA, 0x01);       //Ƶ��0�Զ�,ACKӦ������
  Temp=LPLD_Nrf24L01_WriteReg(NRF24L01_WRITE_REG + NRF24L01_EN_RXADDR, 0x01);   //������յ�ַֻ��Ƶ��0      
  Temp=LPLD_Nrf24L01_WriteReg(NRF24L01_WRITE_REG + NRF24L01_SETUP_RETR, 0x1a);  //�����Զ��ط�ʱ��ʹ�����500us + 86us, 10 retrans...
  Temp=LPLD_Nrf24L01_WriteReg(NRF24L01_WRITE_REG + NRF24L01_RF_CH, 40);         //�����ŵ�����Ϊ2.4GHZ���շ�����һ��
  Temp=LPLD_Nrf24L01_WriteReg(NRF24L01_WRITE_REG + NRF24L01_RF_SETUP, 0x0F);    //���÷�������Ϊ1MHZ�����书��Ϊ���ֵ0dB
  Temp=LPLD_Nrf24L01_WriteReg(NRF24L01_WRITE_REG + NRF24L01_CONFIG, 0x0E);      //ʹ��CRCУ�飬ʹ��TX�������ϵ�
  
  NRF24L01_CE_H;
  
  Nrf24L01_DelayUs(2000);//�ȴ�Nrf24L01����ģʽ��ʼ�����
  
  return Temp;
}

/*
 * LPLD_Nrf24L01_RxModeInit
 * Nrf24L01����ģʽ��ʼ��
 * 
 * ����:
 *    ��
 *
 * ���:
 *    Nrf24L01�Ĵ�������״̬
 */
uint8 LPLD_Nrf24L01_RxModeInit(void) 
{ 
  uint8 Temp;
  
  NRF24L01_CE_L; 
  // оƬ�ϵ縴λ��
  // �ֱ��ȡNRF24L01_RX_ADDR_P0��NRF24L01_RX_ADDR_P1��NRF24L01_TX_ADDR��ֵ
  // �鿴��������
  // NRF24L01_RX_ADDR_P0�ĸ�λֵ�Ƿ�Ϊ0xE7E7E7E7
  // NRF24L01_RX_ADDR_P1�ĸ�λֵ�Ƿ�Ϊ0xC2C2C2C2
  // NRF24L01_TX_ADDR�ĸ�λֵ�Ƿ�Ϊ0xE7E7E7E7
  // �����ȷ֤��SPI��дû�����⣬��֮��Ȼ
  LPLD_Nrf24L01_CheckID();
 
  Temp=LPLD_Nrf24L01_WriteBuf(NRF24L01_WRITE_REG + NRF24L01_RX_ADDR_P0, RX_ADDRESS, NRF24L01_RX_ADR_LEN); 
  Temp=LPLD_Nrf24L01_WriteReg(NRF24L01_WRITE_REG + NRF24L01_RX_PW_P0, NRF24L01_PLOAD_LEN);
  
  Temp=LPLD_Nrf24L01_WriteReg(NRF24L01_WRITE_REG + NRF24L01_EN_AA, 0x01);      //Ƶ��0�Զ�,ACKӦ������      
  Temp=LPLD_Nrf24L01_WriteReg(NRF24L01_WRITE_REG + NRF24L01_EN_RXADDR, 0x01);  //������յ�ַֻ��Ƶ��0 
  Temp=LPLD_Nrf24L01_WriteReg(NRF24L01_WRITE_REG + NRF24L01_SETUP_RETR, 0x1a); // 500us + 86us, 10 retrans... 	
  Temp=LPLD_Nrf24L01_WriteReg(NRF24L01_WRITE_REG + NRF24L01_RF_CH, 40);        //�����ŵ�����Ϊ2.4GHZ���շ�����һ��  
  Temp=LPLD_Nrf24L01_WriteReg(NRF24L01_WRITE_REG + NRF24L01_RF_SETUP, 0x0F);   //���÷�������Ϊ1MHZ�����书��Ϊ���ֵ0dB
  Temp=LPLD_Nrf24L01_WriteReg(NRF24L01_WRITE_REG + NRF24L01_CONFIG, 0x0F);     //ʹ��CRCУ�飬ʹ��RX�������ϵ� 
  
  NRF24L01_CE_H;  
  
  Nrf24L01_DelayUs(2000);//�ȴ�Nrf24L01����ģʽ��ʼ�����
  
  return Temp;
}

/*
 * LPLD_Nrf24L01_SendFrame
 * Nrf24L01��������֡
 * 
 * ����:
 *    *data--ָ���û��������ݻ�����
 *    len--�������ݳ��ȣ����ֽ�Ϊ��λ
 *
 * ���:
 *    1 ���ͳɹ�
 *    0 ����ʧ��
 */
uint8 LPLD_Nrf24L01_SendFrame(uint8 *data, uint8 len)
{
  uint8 Status;
  
  NRF24L01_CE_L; //����CE����Nrf24l01����Standby-Iģʽ
  LPLD_Nrf24L01_WriteBuf(NRF24L01_WRITE_REG + NRF24L01_RX_ADDR_P0, TX_ADDRESS, NRF24L01_RX_ADR_LEN); // װ�ؽ��ն˵�ַ
  LPLD_Nrf24L01_WriteBuf(NRF24L01_WR_TX_PLOAD, data, len); 			   // װ������	
  NRF24L01_CE_H;  
  
  while(1)
  {
    Status = LPLD_Nrf24L01_ReadReg(NRF24L01_STATUS);           //��ȡ״̬�Ĵ���
    LPLD_Nrf24L01_WriteReg(NRF24L01_WRITE_REG+NRF24L01_STATUS,Status);  //���״̬�����
    if(Status & NRF24L01_STATUS_TX_DS)                //���������ϣ������յ�ACK���ñ�־λ��λ
    {
      LPLD_Nrf24L01_WriteReg(NRF24L01_FLUSE_TX,0xFF); //��շ��ͻ�����
      Status = 1;
      break;
    }
    else if(Status & NRF24L01_STATUS_MAX_RT)//����ﵽ��η��͵����ֵ�����ڼ�û�н��յ�ACK
    { 
      Status = 0;
      break;
    }
  }
  return Status;
}

/*
 * LPLD_Nrf24L01_RecvFrame
 * Nrf24L01��������֡
 * 
 * ����:
 *    *data--ָ���û��������ݻ�����
 *    len--�������ݳ��ȣ����ֽ�Ϊ��λ
 *
 * ���:
 *    ��
 */
void LPLD_Nrf24L01_RecvFrame(uint8 *data, uint8 len)
{
  uint8 Status;
  Status = LPLD_Nrf24L01_ReadReg(NRF24L01_STATUS);                  
  LPLD_Nrf24L01_ReadBuf(NRF24L01_RD_RX_PLOAD,data,len);
  LPLD_Nrf24L01_WriteReg(NRF24L01_WRITE_REG+NRF24L01_STATUS,Status);
  Status = 0;
}

/*
* LPLD_Nrf24L01_CheckID   
* ���ڼ�鸴λ���NRF24L01_RX_ADDR_P1��NRF24L01_RX_ADDR_P0��NRF24L01_TX_ADDR��ֵ�Ƿ���ȷ
* ��ֵ���ڷ�ӳSPI�����Ƿ�������ȷ
*
* ���:
*     Nrf24L01�Ĵ�������״̬
*/
static uint8 LPLD_Nrf24L01_CheckID(void)
{
  uint8 Temp;
  Temp=LPLD_Nrf24L01_ReadBuf(NRF24L01_READ_REG + NRF24L01_RX_ADDR_P1, NRF24L01_RX_ADDR_P1_RESET_BUF,5);
  asm("nop");
  Temp=LPLD_Nrf24L01_ReadBuf(NRF24L01_READ_REG + NRF24L01_TX_ADDR, NRF24L01_TX_ADDR_RESET_BUF,5);
  asm("nop");
  Temp=LPLD_Nrf24L01_ReadBuf(NRF24L01_READ_REG + NRF24L01_RX_ADDR_P0, NRF24L01_RX_ADDR_P0_RESET_BUF,5);
  asm("nop"); 
  return Temp;
}

/*
* LPLD_Nrf24L01_WriteBuf
* ��nrf24l01�Ļ�������д�����ݣ������ؼĴ�����״̬
* ����:   
*     reg--nrf24l01�Ĵ���
*     *pbuf--ָ��洢д�����ݵ��׵�ַ
*     len--��ȡ���ĳ��ȣ���λ�ֽ�
* ����ֵ: 
*     ���ص�ǰ�Ĵ�����״̬
*/
static uint8 LPLD_Nrf24L01_WriteBuf(uint8 reg,uint8 *pbuf ,uint8 len)
{
  uint8 status,i;
  
  status = LPLD_SPI_Master_WriteRead(NRF24L01_SPIX, reg, SPI_PCS0, SPI_PCS_ASSERTED); //֡������Ϻ�PCS���ֵ͵�ƽ
  
  for(i = 0;i < len;i++) 
  {       
    if( i == (len-1) )
    {
      LPLD_SPI_Master_WriteRead(NRF24L01_SPIX,*pbuf++,SPI_PCS0,SPI_PCS_INACTIVE);//֡������Ϻ�PCS��ɸߵ�ƽ
    }
    else
    {
      LPLD_SPI_Master_WriteRead(NRF24L01_SPIX,*pbuf++,SPI_PCS0,SPI_PCS_ASSERTED);
    }
  }
  return status;
} 

/*
* LPLD_Nrf24L01_ReadBuf
* ��nrf24l01�Ļ������ж�ȡ���ݣ������ؼĴ�����״̬
* ����:
*     reg--nrf24l01�Ĵ���
*     *pBUF--ָ��洢�������ݵ��׵�ַ
*     len--��ȡ���ĳ��ȣ���λ�ֽ�
* ����ֵ��
*     ���ص�ǰ�Ĵ�����״̬
*/
static uint8 LPLD_Nrf24L01_ReadBuf(uint8 reg,uint8 *pbuf,uint8 len)
{
  uint8 Status,i;
  
  Status = LPLD_SPI_Master_WriteRead(NRF24L01_SPIX,reg,SPI_PCS0,SPI_PCS_ASSERTED); 
  
  for(i = 0 ;i < len ;i++)
  {
    if( i == (len-1) )
    {
      pbuf[i] = LPLD_SPI_Master_WriteRead(NRF24L01_SPIX,0xFF,SPI_PCS0,SPI_PCS_INACTIVE);
    }
    else
    {
      pbuf[i] = LPLD_SPI_Master_WriteRead(NRF24L01_SPIX,0xFF,SPI_PCS0,SPI_PCS_ASSERTED);
    }
  }
  return Status ;
}

/*
* LPLD_Nrf24L01_WriteReg
* ��nrf24l01�Ĵ�����д�����ݣ������ؼĴ�����״̬/��nrf24l01д��ָ��
* ����:
*     reg--nrf24l01�Ĵ���
*     value--�Ĵ�������ֵ
* ����ֵ: 
*     ���ص�ǰ�Ĵ�����״̬
*/
static uint8 LPLD_Nrf24L01_WriteReg(uint8 reg,uint8 value)
{
  uint8 Status;
  Status = LPLD_SPI_Master_WriteRead(NRF24L01_SPIX,reg,SPI_PCS0,SPI_PCS_ASSERTED);    
  LPLD_SPI_Master_WriteRead(NRF24L01_SPIX,value,SPI_PCS0,SPI_PCS_INACTIVE);  
  return Status;
}

/*
* LPLD_Nrf24L01_ReadReg
* ��nrf24l01�Ĵ�����д�����ݣ������ؼĴ�����״̬/��nrf24l01д��ָ��
* ����:
*     reg--nrf24l01�Ĵ���
* ����ֵ: 
*     ���ص�ǰ�Ĵ�������ֵ
*/
static uint8 LPLD_Nrf24L01_ReadReg(uint8 reg)
{
  uint8 temp;
  LPLD_SPI_Master_WriteRead(NRF24L01_SPIX,reg,SPI_PCS0,SPI_PCS_ASSERTED);  
  temp = LPLD_SPI_Master_WriteRead(NRF24L01_SPIX,0xFF,SPI_PCS0,SPI_PCS_INACTIVE); 
  return temp;
}

/*
* Nrf24L01_DelayUs
* ������ʱ ��С10us
* ����:   
*     t ��ʱ
* ����ֵ: 
*     ��      
*/
static void Nrf24L01_DelayUs(uint16 t)
{
  uint16 i;
  for(i = 0; i < t;i++)
  {
    asm("nop");
  }
}
