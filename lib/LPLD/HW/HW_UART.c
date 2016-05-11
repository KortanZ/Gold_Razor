/**
 * @file HW_UART.c
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
#include "common.h"
#include "HW_UART.h"

//�û������жϺ�����ڵ�ַ����
UART_ISR_CALLBACK UART_R_ISR[6];
//�û������жϺ�����ڵ�ַ����
UART_ISR_CALLBACK UART_T_ISR[6];  


/*
 * LPLD_UART_Init
 * ��ʼ��UARTͨ���������ʡ����ͽ�������
 * 
 * ����:
 *    uart_init_structure--UART��ʼ���ṹ�壬
 *                        ���嶨���UART_InitTypeDef
 *
 * ���:
 *    ��
 *
 */
void LPLD_UART_Init(UART_InitTypeDef uart_init_structure)
{
  register uint16 sbr, brfa;
  uint32 sysclk;
  uint8 temp, x ,len;
  UART_Type *uartx = uart_init_structure.UART_Uartx;
  uint32 baud = uart_init_structure.UART_BaudRate;
  PortPinsEnum_Type tx_pin = uart_init_structure.UART_TxPin;
  PortPinsEnum_Type rx_pin = uart_init_structure.UART_RxPin;
  UART_ISR_CALLBACK rx_isr = uart_init_structure.UART_RxIsr;
  UART_ISR_CALLBACK tx_isr = uart_init_structure.UART_TxIsr;
  
  if(baud == NULL)
  {
    baud = 9600;
  }
  
  //ʹ��ѡ�е�UART����ͨ��ʱ�ӣ���ӦGPIO��UART���ù���   
  if(uartx == UART0)
  {
    x = 0;
    sysclk = g_core_clock;
    SIM->SCGC4 |= SIM_SCGC4_UART0_MASK;
    
    if(tx_pin == PTA2)
      PORTA->PCR[2] = PORT_PCR_MUX(2); 
    else if(tx_pin == PTA14)
      PORTA->PCR[14] = PORT_PCR_MUX(3); 
    else
      PORTB->PCR[17] = PORT_PCR_MUX(3); 
    
    if(rx_pin == PTA1)
      PORTA->PCR[1] = PORT_PCR_MUX(2); 
    else if(rx_pin == PTA15)
      PORTA->PCR[15] = PORT_PCR_MUX(3); 
    else
      PORTB->PCR[16] = PORT_PCR_MUX(3); 
  }
  else
  {
    if (uartx == UART1)
    {
      x = 1;
      sysclk = g_core_clock;
      SIM->SCGC4 |= SIM_SCGC4_UART1_MASK;
      
      if(tx_pin == PTE0)   
        PORTE->PCR[0] = PORT_PCR_MUX(3); 
      else
        PORTC->PCR[4] = PORT_PCR_MUX(3); 
      
      if(rx_pin == PTE1)
        PORTE->PCR[1] = PORT_PCR_MUX(3); 
      else
        PORTC->PCR[3] = PORT_PCR_MUX(3); 
    }
    else
    {
      sysclk = g_bus_clock;
      if (uartx == UART2)
      {
        x = 2;
        SIM->SCGC4 |= SIM_SCGC4_UART2_MASK;
        
        PORTD->PCR[3] = PORT_PCR_MUX(3); 
        PORTD->PCR[2] = PORT_PCR_MUX(3);
      }
      else
      {
        if(uartx == UART3)
        {
          x = 3;
          SIM->SCGC4 |= SIM_SCGC4_UART3_MASK;
          
          if(tx_pin == PTE4)
            PORTE->PCR[4] = PORT_PCR_MUX(3); 
          else if(tx_pin == PTB11)
            PORTB->PCR[11] = PORT_PCR_MUX(3); 
          else 
            PORTC->PCR[17] = PORT_PCR_MUX(3); 
          
          if(rx_pin == PTE5)
            PORTE->PCR[5] = PORT_PCR_MUX(3); 
          else if(rx_pin == PTB10)
            PORTB->PCR[10] = PORT_PCR_MUX(3); 
          else
            PORTC->PCR[16] = PORT_PCR_MUX(3);
        }
        else
        {
          if(uartx == UART4)
          {
            x = 4;
            SIM->SCGC1 |= SIM_SCGC1_UART4_MASK;
            
            if(tx_pin == PTE24)
              PORTE->PCR[24] = PORT_PCR_MUX(3); 
            else
              PORTC->PCR[15] = PORT_PCR_MUX(3); 
            
            if(rx_pin == PTE25)
              PORTE->PCR[25] = PORT_PCR_MUX(3); 
            else
              PORTC->PCR[14] = PORT_PCR_MUX(3);
          }
          else
          {
            x = 5;
            uartx = UART5;
            SIM->SCGC1 |= SIM_SCGC1_UART5_MASK;
            
            if(tx_pin == PTD9)
              PORTD->PCR[9] = PORT_PCR_MUX(3); 
            else
              PORTE->PCR[8] = PORT_PCR_MUX(3); 
            
            if(rx_pin == PTD8)
              PORTD->PCR[8] = PORT_PCR_MUX(3); 
            else
              PORTE->PCR[9] = PORT_PCR_MUX(3); 
          }
        }
      }
    }
  }
  
  //�����ú������Ĵ���ǰ���ȹرշ������ͽ�����
  uartx->C2 &= ~(UART_C2_TE_MASK | UART_C2_RE_MASK );
  
  //����UARTΪ 8λ, ����żУ�� */
  uartx->C1 = 0;	
  
  //���㲨����
  sbr = (uint16)((sysclk)/(baud * 16));
  
  //����UARTx_BDH�Ĵ����г���SBR��ֵ
  temp = uartx->BDH & ~(UART_BDH_SBR(0x1F));
  
  uartx->BDH = temp |  UART_BDH_SBR(((sbr & 0x1F00) >> 8));
  uartx->BDL = (uint8)(sbr & UART_BDL_SBR_MASK);
  
  //���ò����ʵ�΢������
  brfa = (((sysclk*32)/(baud * 16)) - (sbr * 32));
  
  //����UARTx_C4�Ĵ����г���BRFA��ֵ
  temp = uartx->C4 & ~(UART_C4_BRFA(0x1F));
  
  uartx->C4 = temp |  UART_C4_BRFA(brfa);    
  
  //����UART����DMA��ʽ
  if( uart_init_structure.UART_RxDMAEnable == TRUE 
    && uart_init_structure.UART_RxIntEnable == TRUE )
  {
    //ʹ�ܽ����жϻ���DMA
    uartx->C2 |= UART_C2_RIE_MASK;
    //ʹ�ܽ���DMA
    uartx->C5 |= UART_C5_RDMAS_MASK;
  }//����UART�����жϷ�ʽ
  else if(uart_init_structure.UART_RxIntEnable == TRUE 
        && rx_isr != NULL)
  {
    //ʹ�ܽ����ж�
    uartx->C2 |= UART_C2_RIE_MASK; 
    UART_R_ISR[x] = rx_isr;
  } 
  else
  {
    uartx->C2 &= ~(UART_C2_RIE_MASK); 
    uartx->C5 &= ~(UART_C5_RDMAS_MASK);
  }
  
  //����UART����DMA��ʽ
  if( uart_init_structure.UART_TxDMAEnable == TRUE 
    && uart_init_structure.UART_TxIntEnable == TRUE )
  {
    //ʹ�ܷ����жϻ���DMA
    uartx->C2 |= UART_C2_TIE_MASK;
    //ʹ�ܽ���DMA
    uartx->C5 |= UART_C5_TDMAS_MASK;
  }//����UART�����жϷ�ʽ
  else if(uart_init_structure.UART_TxIntEnable == TRUE 
        && tx_isr != NULL)
  {
    //ʹ�ܷ����ж�
    uartx->C2 |= UART_C2_TIE_MASK; 
    UART_T_ISR[x] = tx_isr;
  } 
  else
  {
    uartx->C2 &= ~(UART_C2_TIE_MASK);
    uartx->C5 &= ~(UART_C5_TDMAS_MASK);
  }
  
  //����UART FIFO ����
  if( (uartx->C2 & UART_C2_RE_MASK) == 0 
     && uart_init_structure.RxFIFO.FIFO_Enable == TRUE)
  {
    //ʹ�� UART ����FIFO
    uartx->PFIFO |= UART_PFIFO_RXFE_MASK;
    
    if(uart_init_structure.RxFIFO.FIFO_BufFlow_IntEnable == TRUE)
    {
      uartx->CFIFO |= UART_CFIFO_RXUFE_MASK;
    }
    
    //��ȡ FIFO buffer ���
    len = (uint8)( uartx->PFIFO & UART_PFIFO_RXFIFOSIZE_MASK ) >> UART_PFIFO_RXFIFOSIZE_SHIFT;
    len = len > 0 ? 1 << (len + 1) : 1;
    //���Rx FIFO buffer�е�DataWords ���ڵ��� UART_FIFOWaterMark
    //�������жϻ���DMA�źţ�ȡ��C2_RIE��C5_RDMAS��״̬
    if( uart_init_structure.RxFIFO.FIFO_WaterMark > len )
    {
      uartx->RWFIFO = UART_RWFIFO_RXWATER(len);
    }
    else
    {
      uartx->RWFIFO = UART_RWFIFO_RXWATER(uart_init_structure.RxFIFO.FIFO_WaterMark);
    }  
  }
  
  if( (uartx->C2 & UART_C2_TE_MASK) == 0 
     && uart_init_structure.TxFIFO.FIFO_Enable == TRUE)
  {
    //ʹ�� UART ����FIFO
    uartx->PFIFO |= UART_PFIFO_TXFE_MASK;
    
    if(uart_init_structure.TxFIFO.FIFO_BufFlow_IntEnable == TRUE)
    {
      uartx->CFIFO |= UART_CFIFO_TXOFE_MASK;
    }
    
    //��ȡ FIFO buffer ���
    len = (uint8)( uartx->PFIFO & UART_PFIFO_TXFIFOSIZE_MASK ) >> UART_PFIFO_TXFIFOSIZE_SHIFT;
    len = len > 0 ? 1 << (len + 1) : 1;
    //���Tx FIFO buffer�е�DataWords С�ڵ��� UART_FIFOWaterMark
    //�������жϻ���DMA�źţ�ȡ��C2_TIE��C5_TDMAS��״̬
    if( uart_init_structure.TxFIFO.FIFO_WaterMark > len )
    {
      uartx->TWFIFO = UART_TWFIFO_TXWATER(len);
    }
    else
    {
      uartx->TWFIFO = UART_TWFIFO_TXWATER(uart_init_structure.TxFIFO.FIFO_WaterMark);
    }
  }
  //ʹ�� UART ������
  uartx->C2 |= UART_C2_TE_MASK | UART_C2_RE_MASK;  
}


/*
 * LPLD_UART_RxFIFO_Flush
 * ���UART Rx FIFO
 * 
 * ����:
 *    uartx--UARTģ���
 *      |__UART0          --UART0
 *      |__UART1          --UART1
 *      |__UART2          --UART2
 *      |__UART3          --UART3
 *      |__UART4          --UART4
 *      |__UART5          --UART5
 *
 */
void LPLD_UART_RxFIFO_Flush(UART_Type *uartx)
{
  //��ս��� FIFO
  if( uartx->PFIFO & UART_PFIFO_RXFE_MASK )
  {
    uartx->CFIFO |= UART_CFIFO_RXFLUSH_MASK;
  }
}

/*
 * LPLD_UART_TxFIFO_Flush
 * ���UART Tx FIFO
 * 
 * ����:
 *    uartx--UARTģ���
 *      |__UART0          --UART0
 *      |__UART1          --UART1
 *      |__UART2          --UART2
 *      |__UART3          --UART3
 *      |__UART4          --UART4
 *      |__UART5          --UART5
 *
 */
void LPLD_UART_TxFIFO_Flush(UART_Type *uartx)
{
  //��շ��� FIFO
  if( uartx->PFIFO & UART_PFIFO_TXFE_MASK )
  {
    uartx->CFIFO |= UART_CFIFO_TXFLUSH_MASK;
  }
}

/*
 * LPLD_UART_GetChar
 * ���ڲ�ѯ��ʽ��ȡһ���ֽ�
 * 
 * ����:
 *    uartx--UARTģ���
 *      |__UART0          --UART0
 *      |__UART1          --UART1
 *      |__UART2          --UART2
 *      |__UART3          --UART3
 *      |__UART4          --UART4
 *      |__UART5          --UART5
 *
 * ���:
 *    ���ڽ��յ�1���ֽ�
 *
 */
int8 LPLD_UART_GetChar(UART_Type *uartx)
{
  //�ȴ����ݽ���
  while (!(uartx->S1 & UART_S1_RDRF_MASK));
  
  //���ؽ��յ�1���ֽ�����
  return uartx->D;
}

/********************************************************************/
/*
 * LPLD_UART_GetChar_Present
 * ����Ƿ���յ��ַ�
 * 
 * ����:
 *    uartx--UARTģ���
 *      |__UART0          --UART0
 *      |__UART1          --UART1
 *      |__UART2          --UART2
 *      |__UART3          --UART3
 *      |__UART4          --UART4
 *      |__UART5          --UART5
 *
 * ���:
 *  0       û�н��յ��ַ�
 *  1       �Ѿ����յ��ַ�
 */
int32 LPLD_UART_GetChar_Present(UART_Type *uartx)
{
    return (uartx->S1 & UART_S1_RDRF_MASK);
}

/*
 * LPLD_UART_PutChar
 * ���ڲ�ѯ��ʽ����һ���ֽ�
 * 
 * ����:
 *    uartx--UARTģ���
 *      |__UART0          --UART0
 *      |__UART1          --UART1
 *      |__UART2          --UART2
 *      |__UART3          --UART3
 *      |__UART4          --UART4
 *      |__UART5          --UART5
 *    ch--�����͵�1���ֽ�
 *
 * ���:
 *    ��
 *
 */
void LPLD_UART_PutChar(UART_Type *uartx, int8 ch)
{
  //�ȴ�FIFO׼������
  while(!(uartx->S1 & UART_S1_TDRE_MASK));
  
  //��Ҫ���͵�1���ֽڷ���UART���ݼĴ���
  uartx->D = (uint8)ch;
}


/*
 * LPLD_UART_PutCharArr
 * ���ڲ�ѯ��ʽ�����ֽ�������
 * 
 * ����:
 *    uartx--UARTģ���
 *      |__UART0          --UART0
 *      |__UART1          --UART1
 *      |__UART2          --UART2
 *      |__UART3          --UART3
 *      |__UART4          --UART4
 *      |__UART5          --UART5
 *    *ch--�����͵��ֽ�����ͷ��ַ
 *    len--�ֽ����鳤��
 *
 * ���:
 *    ��
 *
 */
void LPLD_UART_PutCharArr(UART_Type *uartx, int8 *ch, int32 len)
{
  while(len--)
  {
    LPLD_UART_PutChar(uartx, *(ch++));
  }
}

/*
 * LPLD_UART_EnableIrq
 * ʹ�ܴ������ݽ����ж�
 * 
 * ����:
 *    uart_init_structure--UART��ʼ���ṹ�壬
 *                        ���嶨���UART_InitTypeDef
 *
 * ���:
 *    ��
 *
 */
void LPLD_UART_EnableIrq(UART_InitTypeDef uart_init_structure)
{
  if(uart_init_structure.UART_Uartx == UART0)
  {
    enable_irq(UART0_RX_TX_IRQn);
    enable_irq(UART0_ERR_IRQn);
  }
  else if(uart_init_structure.UART_Uartx == UART1)
  {
    enable_irq(UART1_RX_TX_IRQn);
    enable_irq(UART1_ERR_IRQn);
  }
  else if(uart_init_structure.UART_Uartx == UART2)
  {
    enable_irq(UART2_RX_TX_IRQn);
    enable_irq(UART2_ERR_IRQn);
  }
  else if(uart_init_structure.UART_Uartx == UART3)
  {
    enable_irq(UART3_RX_TX_IRQn);
    enable_irq(UART3_ERR_IRQn);
  }
  else if(uart_init_structure.UART_Uartx == UART4)
  {
    enable_irq(UART4_RX_TX_IRQn);
    enable_irq(UART4_ERR_IRQn);
  }
  else if(uart_init_structure.UART_Uartx == UART5)
  {
    enable_irq(UART5_RX_TX_IRQn);
    enable_irq(UART5_ERR_IRQn);
  }
}

/*
 * LPLD_UART_DisableIrq
 * ���ô������ݽ����ж�
 * 
 * ����:
 *    uart_init_structure--UART��ʼ���ṹ�壬
 *                        ���嶨���UART_InitTypeDef
 *
 * ���:
 *    ��
 *
 */
void LPLD_UART_DisableIrq(UART_InitTypeDef uart_init_structure)
{
  //�����ж������ʹ����Ӧ�ж�
  if(uart_init_structure.UART_Uartx == UART0)
  {
    disable_irq(UART0_RX_TX_IRQn);
    disable_irq(UART0_ERR_IRQn);
  }
  else if(uart_init_structure.UART_Uartx == UART1)
  {
    disable_irq(UART1_RX_TX_IRQn);
    disable_irq(UART1_ERR_IRQn);
  }
  else if(uart_init_structure.UART_Uartx == UART2)
  {
    disable_irq(UART2_RX_TX_IRQn);
    disable_irq(UART2_ERR_IRQn);
  }
  else if(uart_init_structure.UART_Uartx == UART3)
  {
    disable_irq(UART3_RX_TX_IRQn);
    disable_irq(UART3_ERR_IRQn);
  }
  else if(uart_init_structure.UART_Uartx == UART4)
  {
    disable_irq(UART4_RX_TX_IRQn);
    disable_irq(UART4_ERR_IRQn);
  }
  else if(uart_init_structure.UART_Uartx == UART5)
  {
    disable_irq(UART5_RX_TX_IRQn);
    disable_irq(UART5_ERR_IRQn);
  }
}

//HW���жϺ������û��������
void UART0_IRQHandler(void)
{
#if (UCOS_II > 0u)
  OS_CPU_SR  cpu_sr = 0u;
  OS_ENTER_CRITICAL(); //��֪ϵͳ��ʱ�Ѿ��������жϷ����Ӻ���
  OSIntEnter();
  OS_EXIT_CRITICAL();
#endif
  //�ж�Rx FIFO�Ƿ� Under flow
  if( UART0->SFIFO & UART_SFIFO_RXUF_MASK)
  {
    UART0->SFIFO |= UART_SFIFO_RXUF_MASK;
  }
  //�ж�Tx FIFO�Ƿ� Over flow
  if( UART0->SFIFO & UART_SFIFO_TXOF_MASK)
  {
    UART0->SFIFO |= UART_SFIFO_TXOF_MASK;
  }
  //��������жϺ���
  if((UART0->S1 & UART_S1_RDRF_MASK) && (UART0->C2 & UART_C2_RIE_MASK))
  {
    UART_R_ISR[0]();
  }
  //���뷢���жϺ���
  if((UART0->S1 & UART_S1_TDRE_MASK) && (UART0->C2 & UART_C2_TIE_MASK))
  {
    UART_T_ISR[0]();
  }
  
#if (UCOS_II > 0u)
  OSIntExit();          //��֪ϵͳ��ʱ�����뿪�жϷ����Ӻ���
#endif
}

//HW���жϺ������û��������
void UART1_IRQHandler(void)
{
#if (UCOS_II > 0u)
  OS_CPU_SR  cpu_sr = 0u;
  OS_ENTER_CRITICAL(); //��֪ϵͳ��ʱ�Ѿ��������жϷ����Ӻ���
  OSIntEnter();
  OS_EXIT_CRITICAL();
#endif
  //�ж�Rx FIFO�Ƿ� Under flow
  if( UART1->SFIFO & UART_SFIFO_RXUF_MASK)
  {
    UART1->SFIFO |= UART_SFIFO_RXUF_MASK;
  }
  //�ж�Tx FIFO�Ƿ� Over flow
  if( UART1->SFIFO & UART_SFIFO_TXOF_MASK)
  {
    UART1->SFIFO |= UART_SFIFO_TXOF_MASK;
  }  
  //��������жϺ���
  if((UART1->S1 & UART_S1_RDRF_MASK) && (UART1->C2 & UART_C2_RIE_MASK))
  {
    UART_R_ISR[1]();
  }
  //���뷢���жϺ���
  if((UART1->S1 & UART_S1_TDRE_MASK) && (UART1->C2 & UART_C2_TIE_MASK))
  {
    UART_T_ISR[1]();
  }
  
#if (UCOS_II > 0u)
  OSIntExit();          //��֪ϵͳ��ʱ�����뿪�жϷ����Ӻ���
#endif
}

//HW���жϺ������û��������
void UART2_IRQHandler(void)
{
#if (UCOS_II > 0u)
  OS_CPU_SR  cpu_sr = 0u;
  OS_ENTER_CRITICAL(); //��֪ϵͳ��ʱ�Ѿ��������жϷ����Ӻ���
  OSIntEnter();
  OS_EXIT_CRITICAL();
#endif
  //�ж�Rx FIFO�Ƿ� Under flow
  if( UART2->SFIFO & UART_SFIFO_RXUF_MASK)
  {
    UART2->SFIFO |= UART_SFIFO_RXUF_MASK;
  }
  //�ж�Tx FIFO�Ƿ� Over flow
  if( UART2->SFIFO & UART_SFIFO_TXOF_MASK)
  {
    UART2->SFIFO |= UART_SFIFO_TXOF_MASK;
  }    
  //��������жϺ���
  if((UART2->S1 & UART_S1_RDRF_MASK) && (UART2->C2 & UART_C2_RIE_MASK))
  {
    UART_R_ISR[2]();
  }
  //���뷢���жϺ���
  if((UART2->S1 & UART_S1_TDRE_MASK) && (UART2->C2 & UART_C2_TIE_MASK))
  {
    UART_T_ISR[2]();
  }
  
#if (UCOS_II > 0u)
  OSIntExit();          //��֪ϵͳ��ʱ�����뿪�жϷ����Ӻ���
#endif
}

//HW���жϺ������û��������
void UART3_IRQHandler(void)
{
#if (UCOS_II > 0u)
  OS_CPU_SR  cpu_sr = 0u;
  OS_ENTER_CRITICAL(); //��֪ϵͳ��ʱ�Ѿ��������жϷ����Ӻ���
  OSIntEnter();
  OS_EXIT_CRITICAL();
#endif
  //�ж�Rx FIFO�Ƿ� Under flow
  if( UART3->SFIFO & UART_SFIFO_RXUF_MASK)
  {
    UART3->SFIFO |= UART_SFIFO_RXUF_MASK;
  }
  //�ж�Tx FIFO�Ƿ� Over flow
  if( UART3->SFIFO & UART_SFIFO_TXOF_MASK)
  {
    UART3->SFIFO |= UART_SFIFO_TXOF_MASK;
  }   
  //��������жϺ���
  if((UART3->S1 & UART_S1_RDRF_MASK) && (UART3->C2 & UART_C2_RIE_MASK))
  {
    UART_R_ISR[3]();
  }
  //���뷢���жϺ���
  if((UART3->S1 & UART_S1_TDRE_MASK) && (UART3->C2 & UART_C2_TIE_MASK))
  {
    UART_T_ISR[3]();
  }
  
#if (UCOS_II > 0u)
  OSIntExit();          //��֪ϵͳ��ʱ�����뿪�жϷ����Ӻ���
#endif
}

//HW���жϺ������û��������
void UART4_IRQHandler(void)
{
#if (UCOS_II > 0u)
  OS_CPU_SR  cpu_sr = 0u;
  OS_ENTER_CRITICAL(); //��֪ϵͳ��ʱ�Ѿ��������жϷ����Ӻ���
  OSIntEnter();
  OS_EXIT_CRITICAL();
#endif
  //�ж�Rx FIFO�Ƿ� Under flow
  if( UART4->SFIFO & UART_SFIFO_RXUF_MASK)
  {
    UART4->SFIFO |= UART_SFIFO_RXUF_MASK;
  }
  //�ж�Tx FIFO�Ƿ� Over flow
  if( UART4->SFIFO & UART_SFIFO_TXOF_MASK)
  {
    UART4->SFIFO |= UART_SFIFO_TXOF_MASK;
  }  
  //��������жϺ���
  if((UART4->S1 & UART_S1_RDRF_MASK) && (UART4->C2 & UART_C2_RIE_MASK))
  {
    UART_R_ISR[4]();
  }
  //���뷢���жϺ���
  if((UART4->S1 & UART_S1_TDRE_MASK) && (UART4->C2 & UART_C2_TIE_MASK))
  {
    UART_T_ISR[4]();
  }
  
#if (UCOS_II > 0u)
  OSIntExit();          //��֪ϵͳ��ʱ�����뿪�жϷ����Ӻ���
#endif
}

//HW���жϺ������û��������
void UART5_IRQHandler(void)
{
#if (UCOS_II > 0u)
  OS_CPU_SR  cpu_sr = 0u;
  OS_ENTER_CRITICAL(); //��֪ϵͳ��ʱ�Ѿ��������жϷ����Ӻ���
  OSIntEnter();
  OS_EXIT_CRITICAL();
#endif
  //�ж�Rx FIFO�Ƿ� Under flow
  if( UART5->SFIFO & UART_SFIFO_RXUF_MASK)
  {
    UART5->SFIFO |= UART_SFIFO_RXUF_MASK;
  }
  //�ж�Tx FIFO�Ƿ� Over flow
  if( UART5->SFIFO & UART_SFIFO_TXOF_MASK)
  {
    UART5->SFIFO |= UART_SFIFO_TXOF_MASK;
  }   
  //��������жϺ���
  if((UART5->S1 & UART_S1_RDRF_MASK) && (UART5->C2 & UART_C2_RIE_MASK))
  {
    UART_R_ISR[5]();
  }
  //���뷢���жϺ���
  if((UART5->S1 & UART_S1_TDRE_MASK) && (UART5->C2 & UART_C2_TIE_MASK))
  {
    UART_T_ISR[5]();
  }
  
#if (UCOS_II > 0u)
  OSIntExit();          //��֪ϵͳ��ʱ�����뿪�жϷ����Ӻ���
#endif
}

void UART0_ERR_IRQHandler(void)
{
}

void UART1_ERR_IRQHandler(void)
{
}

void UART2_ERR_IRQHandler(void)
{
}

void UART3_ERR_IRQHandler(void)
{
}

void UART4_ERR_IRQHandler(void)
{
}

void UART5_ERR_IRQHandler(void)
{
}

