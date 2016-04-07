/*
 * @file HW_I2C.c
 * @version 3.02[By LPLD]
 * @date 2013-11-22
 * @brief I2C�ײ�ģ����غ���
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
#include "HW_I2C.h"

//�û��Զ����жϷ���������
I2C_ISR_CALLBACK I2C_ISR[2];

/*
 * LPLD_I2C_Init
 * I2Cͨ�ó�ʼ���������ڸú�����ѡ��I2Cͨ����ѡ��I2C SCK����Ƶ�ʣ�
 * ѡ��I2C SDA �� I2C SCL�����ţ�����I2C���жϻص�����
 * 
 * ����:
 *    I2C_InitTypeDef--i2c_init_structure
 *                     ���嶨���I2C_InitTypeDef
 * ���:
 *    0--���ô���
 *    1--���óɹ�
 */
uint8 LPLD_I2C_Init(I2C_InitTypeDef i2c_init_structure)
{
  I2C_Type *i2cx = i2c_init_structure.I2C_I2Cx;
  uint8 bus_speed = i2c_init_structure.I2C_ICR;
  PortPinsEnum_Type scl_pin = i2c_init_structure.I2C_SclPin;
  PortPinsEnum_Type sda_pin = i2c_init_structure.I2C_SdaPin;
  I2C_ISR_CALLBACK isr_func = i2c_init_structure.I2C_Isr;
  boolean ode = i2c_init_structure.I2C_OpenDrainEnable;
  uint8 ode_mask = 0;

  //������飬�ж�SCLƵ��
  ASSERT( bus_speed <= 0x3F);
  
  if(ode == TRUE)
  {
    ode_mask = PORT_PCR_ODE_MASK;
  }

  if(i2cx == I2C0)
  {
#if defined(CPU_MK60DZ10) || defined(CPU_MK60D10) 
    SIM->SCGC4 |= SIM_SCGC4_I2C0_MASK; //����I2C0ʱ��
#elif defined(CPU_MK60F12) || defined(CPU_MK60F15)
    SIM->SCGC4 |= SIM_SCGC4_IIC0_MASK; //����I2C0ʱ��
#endif 
    if(scl_pin == PTD8)
    {
      PORTD->PCR[8] = PORT_PCR_MUX(2) | ode_mask;         
    }
    else if(scl_pin == PTB0) 
    {
      PORTB->PCR[0] = PORT_PCR_MUX(2) | ode_mask;
    }
    else //scl_pin = PTB2
    {
      PORTB->PCR[2] = PORT_PCR_MUX(2) | ode_mask;
    }

    if(sda_pin == PTD9)
    {
      PORTD->PCR[9] = PORT_PCR_MUX(2) | ode_mask;
    }
    else if(sda_pin == PTB1) 
    {
      PORTB->PCR[1] = PORT_PCR_MUX(2) | ode_mask;
    }
    else //sda_pin = PTB3
    {
      PORTB->PCR[3] = PORT_PCR_MUX(2) | ode_mask; 
    }
  }
  else if(i2cx == I2C1)
  { 
#if defined(CPU_MK60DZ10) || defined(CPU_MK60D10)  
    SIM->SCGC4 |= SIM_SCGC4_I2C1_MASK; //����I2C0ʱ��
#elif defined(CPU_MK60F12) || defined(CPU_MK60F15)
    SIM->SCGC4 |= SIM_SCGC4_IIC1_MASK; //����I2C0ʱ��
#endif

    if(scl_pin == PTE1)
    {
      PORTE->PCR[1] = PORT_PCR_MUX(6) | ode_mask;         
    }
    else //scl_pin = PTC10
    {
      PORTC->PCR[10] = PORT_PCR_MUX(2) | ode_mask;  
    }

    if(sda_pin == PTE0)
    {
      PORTE->PCR[0] = PORT_PCR_MUX(6) | ode_mask;
    }
    else //sda_pin = PTC11
    {
      PORTC->PCR[11] = PORT_PCR_MUX(2) | ode_mask; 
    }
  }
  else
    return 0;
  
  if(i2c_init_structure.I2C_IntEnable == TRUE && isr_func != NULL)
  {
    //����I2C�жϵ��ж�Դ��
    //1,���1���ֽڴ���ʱ��IICIF��λ�����ж�;
    //2,��Calling Addressƥ��ɹ�ʱ�����жϣ��ο�K60�ĵ�1456ҳI2Cx_S�Ĵ���IAASλ;
    //3,�ӻ�ģʽ�µ������ٲö�ʧʱ��IICIF��λ�����ж�;
    //  ��Ҫͬʱд1���II2Cx_S��ARBL��־λ�� I2Cx_S�� IICIF�ı�־λ;
    //4,���SMB�Ĵ�����SHTF2 interruptʹ�ܣ���SHTF2 timeoutʱIICIF��λ�����ж�;
    //  ��Ҫͬʱд1���I2Cx_SMB��SLTF��־λ�� I2Cx_S�� IICIF�ı�־λ;
    //5,��SLT�Ĵ�����Ϊ0ʱ��SMBus��SCL low timer��������SLT��ֵʱIICIF��λ�����ж�;
    //  ��Ҫͬʱд1���I2Cx_SMB��SHTF2��־λ�� I2Cx_S�� IICIF�ı�־λ;
    //6,��Wakeup ʹ�ܣ�I2C��ֹͣģʽ�½��յ�Wakeup�źţ��������ж�.

    i2cx->C1 |= I2C_C1_IICIE_MASK;

    if(i2cx == I2C0)
    {
      I2C_ISR[0] = isr_func;
    }
    else if(i2cx == I2C0)
    {
      I2C_ISR[1] = isr_func;
    }
    else 
      return 0;
  }

  //i2cx->C2 |= I2C_C2_HDRS_MASK;      //���I2C��������
  i2cx->F  = I2C_F_ICR(bus_speed)|I2C_F_MULT(0);   //����I2Cx SCL BusSpeed
  i2cx->C1 |= I2C_C1_IICEN_MASK;      //ʹ��I2Cx
  
  return 1;
}

/*
 * LPLD_I2C_Deinit
 * I2Cģ�鷴��ʼ���������ڸú����йر�I2Cx����������ʱ�ӣ��ر�I2Cģ���
 * ʱ�ӣ���ֹ�����жϡ�
 *
 * ����:
 *    I2C_InitTypeDef--i2c_init_structure
 *                     ���嶨���I2C_InitTypeDef
 *
 * ���:
 *    ��
 *
 */  
uint8 LPLD_I2C_Deinit(I2C_InitTypeDef i2c_init_structure)
{
  I2C_Type *i2cx = i2c_init_structure.I2C_I2Cx;

  i2cx->C1 &= ~I2C_C1_IICEN_MASK;      //I2Cx
  if(i2cx == I2C0)
  {
#if defined(CPU_MK60DZ10) || defined(CPU_MK60D10)  
    SIM->SCGC4 |= SIM_SCGC4_I2C0_MASK; //����I2C0ʱ��
#elif defined(CPU_MK60F12) || defined(CPU_MK60F15)
    SIM->SCGC4 |= SIM_SCGC4_IIC0_MASK; //����I2C0ʱ��
#endif
    disable_irq((IRQn_Type)I2C0_IRQn);
  }
  else if (i2cx == I2C1)
  {
#if defined(CPU_MK60DZ10) || defined(CPU_MK60D10)  
    SIM->SCGC4 |= SIM_SCGC4_I2C1_MASK; //����I2C0ʱ��
#elif defined(CPU_MK60F12) || defined(CPU_MK60F15)
    SIM->SCGC4 |= SIM_SCGC4_IIC1_MASK; //����I2C0ʱ��
#endif
    disable_irq((IRQn_Type)I2C1_IRQn);
  }
  else
  {
    return 0;
  }
  return 1;
}

/*
 * LPLD_I2C_EnableIrq
 * I2C�����ж�ʹ��
 *
 * ����:
 *    I2C_InitTypeDef--i2c_init_structure
 *                     ���嶨���I2C_InitTypeDef
 *
 * ���:
 *    ��
 *
 */  
void LPLD_I2C_EnableIrq(I2C_InitTypeDef i2c_init_structure)
{
  I2C_Type *i2cx = i2c_init_structure.I2C_I2Cx; 

  if(i2cx == I2C0)
  {
    enable_irq((IRQn_Type)I2C0_IRQn);
  }
  else if (i2cx == I2C1)
  {
    enable_irq((IRQn_Type)I2C1_IRQn);
  }
  else
  {
    return;
  }
}

/*
 * LPLD_I2C_DisableIrq
 * ��ֹI2C�����ж�
 *
 * ����:
 *    I2C_InitTypeDef--i2c_init_structure
 *                     ���嶨���I2C_InitTypeDef
 *
 * ���:
 *    ��
 *
 */  
void LPLD_I2C_DisableIrq(I2C_InitTypeDef i2c_init_structure)
{
  I2C_Type *i2cx = i2c_init_structure.I2C_I2Cx;
  i2cx->C1 &= ~I2C_C1_IICIE_MASK;

  if(i2cx == I2C0)
  {
    disable_irq((IRQn_Type)I2C0_IRQn);
  }
  else if (i2cx == I2C1)
  {
    disable_irq((IRQn_Type)I2C1_IRQn);
  }
  else
  {
    return;
  }
}

/*
 * LPLD_I2C_Start
 * ����I2C��ʼ�ź�
 * 
 * ����:
 *    i2cx--ѡ��I2Cģ���ͨ��
 *      |__I2C0           --I2Cͨ��0
 *      |__I2C1           --I2Cͨ��1
 * ���:
 *    ��
 */
void LPLD_I2C_Start(I2C_Type *i2cx)
{
  i2cx->C1 |= I2C_C1_TX_MASK ;
  i2cx->C1 |= I2C_C1_MST_MASK ;
}

/*
 * LPLD_ReStart
 * I2C�ٴβ�����ʼ�ź�
 * 
 * ����:
 *    i2cx--ѡ��I2Cģ���ͨ��
 *      |__I2C0           --I2Cͨ��0
 *      |__I2C1           --I2Cͨ��1
 * ���:
 *    ��
*/
void LPLD_I2C_ReStart(I2C_Type *i2cx)
{
  i2cx->C1 |= I2C_C1_RSTA_MASK ;
}

/*
 * LPLD_I2C_Stop
 * ����I2Cֹͣ�ź�
 * 
 * ����:
 *    i2cx--ѡ��I2Cģ���ͨ��
 *      |__I2C0           --I2Cͨ��0
 *      |__I2C1           --I2Cͨ��1
 * ���:
 *    ��
 */
void LPLD_I2C_Stop(I2C_Type *i2cx)
{
  i2cx->C1 &=(~I2C_C1_MST_MASK);
  i2cx->C1 &=(~I2C_C1_TX_MASK); 
}

/*
 * LPLD_I2C_WaitAck
 * I2C���õȴ�Ӧ���źţ�������ȴ����ر��򲻵ȴ�
 * 
 * ����:
 *    i2cx--ѡ��I2Cģ���ͨ��
 *      |__I2C0           --I2Cͨ��0
 *      |__I2C1           --I2Cͨ��1
 *    is_wait--ѡ���Ƿ�ȴ�Ӧ��
 *      |__I2C_ACK_OFF    --�رյȴ�Ack
 *      |__I2C_ACK_ON     --�����ȴ�Ack�����ȴ�ACK�ź�
 * ���:
 *    ��
 */
void LPLD_I2C_WaitAck(I2C_Type *i2cx, uint8 is_wait)
{
  uint16 time_out;
  if(is_wait == I2C_ACK_ON)
  {
    while(!(i2cx->S & I2C_S_IICIF_MASK))
    {
      if(time_out>60000) //����ȴ���ʱ��ǿ���˳�
        break;
      else time_out++;
    }
    i2cx->S |= I2C_S_IICIF_MASK;
  }
  else
  {
    //�ر�I2C��ACK
    i2cx->C1 |= I2C_C1_TXAK_MASK; 
  }
}

/*
 * LPLD_I2C_Write
 * I2C����һ���ֽڸ�Ŀ�ĵ�ַ�豸
 * 
 * ����:
 *    i2cx--ѡ��I2Cģ���ͨ��
 *      |__I2C0           --I2Cͨ��0
 *      |__I2C1           --I2Cͨ��1
 *    data8--Ҫ���͵��ֽ�����
 * ���:
 *    ��
 *
 */
void LPLD_I2C_WriteByte(I2C_Type *i2cx, uint8 data8)
{
  i2cx->D = data8; 
}

/*
 * LPLD_I2C_Read
 * I2C���ⲿ�豸��һ���ֽ�
 * 
 * ����:
 *    i2cx--ѡ��I2Cģ���ͨ��
 *      |__I2C0           --I2Cͨ��0
 *      |__I2C1           --I2Cͨ��1
 * ���:
 *    I2C��ȡ���ֽ� 
 */

uint8 LPLD_I2C_ReadByte(I2C_Type *i2cx)
{
  uint8 temp;
  temp = i2cx->D; 
  return temp;
}

/*
 * LPLD_I2C_SetMasterWR
 * I2C������дģʽ����
 * 
 * ����:
 *    IICx--ѡ��I2Cģ���ͨ��
 *      |__I2C0           --I2Cͨ��0
 *      |__I2C1           --I2Cͨ��1
 *    mode--��дģʽѡ��
 *      |__I2C_MWSR         --����д
 *      |__I2C_MRSW         --������
 * ���:
 *    ��
 */
void LPLD_I2C_SetMasterWR(I2C_Type *i2cx, uint8 mode)
{
  if(mode==I2C_MRSW) 
    i2cx->C1 &= (~I2C_C1_TX_MASK);
  else
    i2cx->C1 |= ( I2C_C1_TX_MASK);
}

/*
 * LPLD_I2C_StartTrans
 * I2C��ʼ���亯������Ҫ������Χ�豸��ַ�Ͷ�дģʽ
 * 
 * ����:
 *    IICx--ѡ��I2Cģ���ͨ��
 *      |__I2C0           --I2Cͨ��0
 *      |__I2C1           --I2Cͨ��1
 *    addr--��Χ�豸��ַ     
 *    mode--��дģʽѡ��
 *      |__I2C_MWSR         --����д
 *      |__I2C_MRSW         --������
 * ���:
 *    ��
 */
void LPLD_I2C_StartTrans(I2C_Type *i2cx, uint8 addr, uint8 mode)
{
  //I2C����start�ź�
  LPLD_I2C_Start(i2cx);
  //���ӻ���ַ��������дλ�ϳ�һ���ֽ�д��
  LPLD_I2C_WriteByte(i2cx, (addr<<1)|mode );
}

//HW���жϺ������û��������
void I2C0_IRQHandler(void)
{
#if (UCOS_II > 0u)
  OS_CPU_SR  cpu_sr = 0u;
  OS_ENTER_CRITICAL(); //��֪ϵͳ��ʱ�Ѿ��������жϷ����Ӻ���
  OSIntEnter();
  OS_EXIT_CRITICAL();
#endif
  if(I2C0->S & I2C_S_IICIF_MASK)
  {
    I2C_ISR[0]();
    if(I2C0->SMB & I2C_SMB_SLTF_MASK)
    {
      I2C0->SMB |= I2C_SMB_SLTF_MASK;
    }
    if(I2C0->SMB & I2C_SMB_SHTF2_MASK)
    {
      I2C0->SMB |= I2C_SMB_SHTF2_MASK;
    }
    if(I2C0->S & I2C_S_ARBL_MASK)
    {
      I2C0->S |= I2C_S_ARBL_MASK;
    }
    I2C0->S |= I2C_S_IICIF_MASK;
  }
#if (UCOS_II > 0u)
  OSIntExit();          //��֪ϵͳ��ʱ�����뿪�жϷ����Ӻ���
#endif
}
//HW���жϺ������û��������
void I2C1_IRQHandler(void)
{

#if (UCOS_II > 0u)
  OS_CPU_SR  cpu_sr = 0u;
  OS_ENTER_CRITICAL(); //��֪ϵͳ��ʱ�Ѿ��������жϷ����Ӻ���
  OSIntEnter();
  OS_EXIT_CRITICAL();
#endif

  if(I2C1->S & I2C_S_IICIF_MASK)
  {
    I2C_ISR[1]();
    if(I2C1->SMB & I2C_SMB_SLTF_MASK)
    {
      I2C1->SMB |= I2C_SMB_SLTF_MASK;
    }
    if(I2C1->SMB & I2C_SMB_SHTF2_MASK)
    {
      I2C1->SMB |= I2C_SMB_SHTF2_MASK;
    }
    if(I2C1->S & I2C_S_ARBL_MASK)
    {
      I2C1->S |= I2C_S_ARBL_MASK;
    }
    I2C1->S |= I2C_S_IICIF_MASK;
  }
  
#if (UCOS_II > 0u)
  OSIntExit();          //��֪ϵͳ��ʱ�����뿪�жϷ����Ӻ���
#endif
}



