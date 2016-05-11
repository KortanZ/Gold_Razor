/**
 * @file DEV_Touchscreen.c
 * @version 1.0[By LPLD]
 * @date 2013-09-24
 * @brief Touchscreen�豸��������
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
#include "DEV_Touchscreen.h"

static void LPLD_Touchscreen_Delay(int i);
SPI_InitTypeDef touch_spi_param;
/*
 * LPLD_Touchscreen_Init
 * ������ADS7843оƬ���ӵ�SPIģ��
 * 
 * ����:
 *    ��
 * �����
 *    ��
 */
void LPLD_Touchscreen_Init (void)
{

  touch_spi_param.SPI_SPIx = TOUCHSCREEN_SPIX;
  touch_spi_param.SPI_SckDivider = SPI_SCK_DIV_32;//1.56Mhz
  touch_spi_param.SPI_Pcs0Pin = TOUCHSCREEN_PCS0;
  touch_spi_param.SPI_SckPin  = TOUCHSCREEN_SCK;
  touch_spi_param.SPI_MosiPin = TOUCHSCREEN_MOSI;
  touch_spi_param.SPI_MisoPin = TOUCHSCREEN_MISO;
  
  touch_spi_param.SPI_TxCompleteIntIsr = NULL;
  touch_spi_param.SPI_QueueEndIntIsr = NULL;
  touch_spi_param.SPI_TxFIFO_FillIntIsr = NULL;
  touch_spi_param.SPI_TxFIFO_UnderflowIntIsr = NULL;
  touch_spi_param.SPI_RxFIFO_DrainIntIsr = NULL;
  touch_spi_param.SPI_RxFIFO_OverflowIntIsr = NULL;
  
  LPLD_SPI_Init(touch_spi_param);

}

/*
 * LPLD_Touch_SendCmd
 * ��ADS7843оƬ���Ϳ���ָ��
 * 
 * ����:
 *    CMD--���������DEV_Touchscreen.h���ж���
 *
 *    pcs_state--ƬѡPCSx������һ֡����֮���״̬
 *      |__0  ���ֵ͵�ƽ
 *      |__1  �ɵ͵�ƽ���ߵ��ߵ�ƽ     
 */
void LPLD_Touchscreen_SendCmd(uint8_t CMD,uint8_t pcs_state)
{
  LPLD_SPI_Master_WriteRead(TOUCHSCREEN_SPIX,CMD,SPI_PCS0,pcs_state);
}

/*
 * LPLD_Touchscreen_GetCovValue
 * ��ADS7843оƬ�������
 * 
 * ����:
 *    CMD--���������Touch.h���ж���
 *
 *    pcs_state--ƬѡPCSx������һ֡����֮���״̬
 *      |__0  ���ֵ͵�ƽ
 *      |__1  �ɵ͵�ƽ���ߵ��ߵ�ƽ     
 */
uint8_t LPLD_Touchscreen_GetCovValue(uint8_t CMD,uint8_t pcs_state)
{
  return LPLD_SPI_Master_WriteRead(TOUCHSCREEN_SPIX,CMD,SPI_PCS0,pcs_state);
}

/*
 * LPLD_Touchscreen_GetResult
 * ��ô�����λ�õ�12λADת�����
 * 
 * ����:
 *    CMD--���������Touch.h���ж���
 *
 *    pcs_state--ƬѡPCSx������һ֡����֮���״̬
 *      |__0  ���ֵ͵�ƽ
 *      |__1  �ɵ͵�ƽ���ߵ��ߵ�ƽ     
 */
uint16_t LPLD_Touchscreen_GetResult(uint8_t Cmd)
{
  uint16_t HI,LO,Data;
  //�������CMD��CS�����ڵ͵�ƽ״̬
  LPLD_Touchscreen_SendCmd(Cmd,SPI_PCS_ASSERTED);
  //���б�Ҫ�ж�æ
  //�ڴ�����ж�æ����������ʱ��������ʱ����125khz����
  LPLD_Touchscreen_Delay(500);
  //���12λ���ȵĸ�8λ
  HI=LPLD_Touchscreen_GetCovValue(LPLD_CMD_DUMMY,SPI_PCS_ASSERTED);
  //���12λ���ȵĵ�4λ������CS����
  LO=LPLD_Touchscreen_GetCovValue(LPLD_CMD_DUMMY,SPI_PCS_INACTIVE);
  //�ϳ�12λ��ת�����
  //�ο�ADS7843�����ĵ�
  Data = ((HI<<8)&0xFF00)|LO;
  Data = Data>>4; 
  return Data;
}

/*
 * LPLD_Touchscreen_Delay
 * Touchscreen��ʱ����
 * 
 * ����:
 *    i--��ʱ
 *    
 */
static void LPLD_Touchscreen_Delay(int i)
{
  int k;
  for(k=0;k<i;k++)
    asm("nop");
}
/********************************************************************/