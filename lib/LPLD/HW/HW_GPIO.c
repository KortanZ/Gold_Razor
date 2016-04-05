/**
 * @file HW_GPIO.c
 * @version 3.03[By LPLD]
 * @date 2014-2-10
 * @brief GPIO�ײ�ģ����غ���
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
#include "HW_GPIO.h"


//�û��Զ����жϷ���������
GPIO_ISR_CALLBACK GPIO_ISR[5];

/*
 * LPLD_GPIO_Init
 * GPIOͨ�ó�ʼ������
 * 
 * ����:
 *    gpio_init_structure--GPIO��ʼ���ṹ�壬
 *                        ���嶨���GPIO_InitTypeDef
 *
 * ���:
 *    0--���ô���
 *    1--���óɹ�
 */
uint8 LPLD_GPIO_Init(GPIO_InitTypeDef gpio_init_structure)
{
  uint8 i;
  PORT_Type *portx;
  uint32 pcr = PORT_PCR_MUX(1)| gpio_init_structure.GPIO_PinControl; 
  GPIO_Type *ptx = gpio_init_structure.GPIO_PTx;
  uint32 pins = gpio_init_structure.GPIO_Pins;
  uint8 dir = gpio_init_structure.GPIO_Dir;
  uint8 output = gpio_init_structure.GPIO_Output;
  GPIO_ISR_CALLBACK isr_func = gpio_init_structure.GPIO_Isr;
  
  //�������
  ASSERT( ptx <= PTE);                  //�ж϶˿�
  ASSERT( dir <= 1 );                   //�жϷ���
  ASSERT( output <= 1 );                //�ж������ƽ״̬
  
  if(ptx == PTA)
  {
    portx = PORTA;  
    i = 0;
  }
  else if(ptx == PTB) 
  {
    portx = PORTB;
    i = 1;
  }
  else if(ptx == PTC) 
  {
    portx = PORTC;
    i = 2;
  }
  else if(ptx == PTD) 
  {
    portx = PORTD;
    i = 3; 
  }
  else if(ptx == PTE) 
  {
    portx = PORTE;
    i = 4;
  }
  else
    return 0;
  
  //������������
  if(dir==DIR_OUTPUT)
  {
    ptx->PDDR |= pins;
    //���ó�ʼ���
    if(output==OUTPUT_H)
    {
      ptx->PSOR = pins; 
    }
    else
    {
      ptx->PCOR = pins;
    }
  }
  else
  { 
    ptx->PDDR &= ~(pins);
  }
  
  //������ѡ���ŵĿ��ƼĴ���
  for(uint8 i=0; i<32; i++)
  {
    if(pins&(1ul<<i))
    {
      portx->PCR[i] = pcr;
    }
  }

  if(isr_func!=NULL)
    GPIO_ISR[i] = isr_func;
  
  return 1;
}

/*
 * LPLD_GPIO_EnableIrq
 * ʹ��GPIO�ⲿ�ж�
 * 
 * ����:
 *    gpio_init_structure--GPIO��ʼ���ṹ�壬
 *                        ���嶨���GPIO_InitTypeDef
 *
 * ���:
 *    0--���ô���
 *    1--���óɹ�
 *
 */
uint8 LPLD_GPIO_EnableIrq(GPIO_InitTypeDef gpio_init_structure)
{
  uint8 i;
  GPIO_Type *ptx = gpio_init_structure.GPIO_PTx;
  
  //�������
  ASSERT( ptx <= PTE);                  //�ж϶˿�
  
  if(ptx == PTA)
    i = 0;
  else if(ptx == PTB) 
    i = 1;
  else if(ptx == PTC) 
    i = 2;
  else if(ptx == PTD) 
    i = 3;
  else
    i = 4;

  enable_irq((IRQn_Type)(i + PORTA_IRQn));
  
  return 1;
}

/*
 * LPLD_GPIO_DisableIrq
 * ����GPIO�ⲿ�ж�
 * 
 * ����:
 *    gpio_init_structure--GPIO��ʼ���ṹ�壬
 *                        ���嶨���GPIO_InitTypeDef
 *
 * ���:
 *    0--���ô���
 *    1--���óɹ�
 *
 */
uint8 LPLD_GPIO_DisableIrq(GPIO_InitTypeDef gpio_init_structure)
{
  uint8 i;
  GPIO_Type *ptx = gpio_init_structure.GPIO_PTx;
  
  //�������
  ASSERT( ptx <= PTE);                  //�ж϶˿�
  
  if(ptx == PTA)
    i = 0;
  else if(ptx == PTB) 
    i = 1;
  else if(ptx == PTC) 
    i = 2;
  else if(ptx == PTD) 
    i = 3;
  else
    i = 4;
  
  disable_irq((IRQn_Type)(i + PORTA_IRQn));
  
  return 1;
}

/*
 * LPLD_GPIO_Ouptut
 * ����GPIO�˿�0~31λ�����
 * 
 * ����:
 *    ptx--�˿ں�
 *      |__PTA        --Port A
 *      |__PTB        --Port B
 *      |__PTC        --Port C
 *      |__PTD        --Port D
 *      |__PTE        --Port E
 *    data32--�������
 *      |__0x00000000~0xFFFFFFFF--�͵��ߴ���GPIO�ڵĵ�0~31λ����
 *
 * ���:
 *
 */
__INLINE void LPLD_GPIO_Output(GPIO_Type *ptx, uint32 data32)
{ 
  ptx->PDOR = data32;
}

/*
 * LPLD_GPIO_Ouptut_b
 * ����GPIO�˿�һλ�����
 * 
 * ����:
 *    ptx--�˿ں�
 *      |__PTA        --Port A
 *      |__PTB        --Port B
 *      |__PTC        --Port C
 *      |__PTD        --Port D
 *      |__PTE        --Port E
 *    lsb_num--�˿�����λ�����
 *      |__0~31       --GPIO�ڵĵ�0~31λ
 *    data1--�������
 *      |__0          --����͵�ƽ
 *      |__1          --����ߵ�ƽ
 *
 * ���:
 *
 */
__INLINE void LPLD_GPIO_Output_b(GPIO_Type *ptx, uint32 lsb_num, uint8 data1)
{
  ptx->PDOR = (ptx->PDOR & ~(0x01L<<lsb_num)) | (uint32)data1<<lsb_num;
}

/*
 * LPLD_GPIO_Ouptut_8b
 * ����GPIO�˿�8λ�����
 * 
 * ����:
 *    ptx--�˿ں�
 *      |__PTA        --Port A
 *      |__PTB        --Port B
 *      |__PTC        --Port C
 *      |__PTD        --Port D
 *      |__PTE        --Port E
 *    lsb_num--����8���˿����ŵ����λ�����
 *      |__0~24       --GPIO�ڵĵ�0~24λ
 *    data8--�������
 *      |__0x00~0xFF--����GPIO�������8λ����
 *
 * ���:
 *
 */
__INLINE void LPLD_GPIO_Output_8b(GPIO_Type *ptx, uint8 lsb_num, uint8 data8)
{
  ptx->PDOR = (ptx->PDOR & ~(0xFFL<<lsb_num)) | (uint32)data8<<lsb_num;
}

/*
 * LPLD_GPIO_Toggle
 * ����GPIO�˿�0~31�ĵ�ƽ��ת
 * 
 * ����:
 *    ptx--�˿ں�
 *      |__PTA        --Port A
 *      |__PTB        --Port B
 *      |__PTC        --Port C
 *      |__PTD        --Port D
 *      |__PTE        --Port E
 *    data32--��ת����
 *      |__0x00000000~0xFFFFFFFF--�͵��ߴ���GPIO�ڵĵ�0~31λ�ķ�ת��1Ϊ��ת��0Ϊ���ֲ��䡣
 *
 * ���:
 *
 */
__INLINE void LPLD_GPIO_Toggle(GPIO_Type *ptx, uint32 data32)
{  
  ptx->PTOR = data32;
}

/*
 * LPLD_GPIO_Toggle_b
 * ����GPIO�˿�һλ�ķ�ת
 * 
 * ����:
 *    ptx--�˿ں�
 *      |__PTA        --Port A
 *      |__PTB        --Port B
 *      |__PTC        --Port C
 *      |__PTD        --Port D
 *      |__PTE        --Port E
 *    lsb_num--�˿�����λ�����
 *      |__0~31       --GPIO�ڵĵ�0~31λ
 *
 * ���:
 *
 */
__INLINE void LPLD_GPIO_Toggle_b(GPIO_Type *ptx, uint8 lsb_num)
{  
  ptx->PTOR = 0x01L<<lsb_num;
}

/*
 * LPLD_GPIO_Toggle_8b
 * ����GPIO�˿�8λ�ķ�ת
 * 
 * ����:
 *    ptx--�˿ں�
 *      |__PTA        --Port A
 *      |__PTB        --Port B
 *      |__PTC        --Port C
 *      |__PTD        --Port D
 *      |__PTE        --Port E
 *    lsb_num--����8���˿����ŵ����λ�����
 *      |__0~24       --GPIO�ڵĵ�0~24λ
 *    data8--�������
 *      |__0x00~0xFF--����GPIO�������8λ����
 *
 * ���:
 *
 */
__INLINE void LPLD_GPIO_Toggle_8b(GPIO_Type *ptx, uint8 lsb_num, uint8 data8)
{
  ptx->PTOR = (uint32)data8<<lsb_num;
}

/*
 * LPLD_GPIO_Input
 * ȡ��GPIO��0~31λ������
 * 
 * ����:
 *    ptx--�˿ں�
 *      |__PTA        --Port A
 *      |__PTB        --Port B
 *      |__PTC        --Port C
 *      |__PTD        --Port D
 *      |__PTE        --Port E
 *
 * ���:
 *    ָ��GPIO�ڵ�32λ����
 *
 */
__INLINE uint32 LPLD_GPIO_Input(GPIO_Type *ptx)
{
  return ptx->PDIR;
}

/*
 * LPLD_GPIO_Input_b
 * ȡ��GPIO��ĳһλ������
 * 
 * ����:
 *    ptx--�˿ں�
 *      |__PTA        --Port A
 *      |__PTB        --Port B
 *      |__PTC        --Port C
 *      |__PTD        --Port D
 *      |__PTE        --Port E
 *    lsb_num--�˿�����λ�����
 *      |__0~31       --GPIO�ڵĵ�0~31λ
 *
 * ���:
 *    ָ��GPIO�ڵ�ָ��λ���ĵ�ƽ
 *
 */
__INLINE uint8 LPLD_GPIO_Input_b(GPIO_Type *ptx, uint8 lsb_num)
{  
  return (uint8)((ptx->PDIR>>lsb_num)&0x01L);
}

/*
 * LPLD_GPIO_Input_8b
 * ȡ��GPIO�˿�8λ���ݵ�����
 * 
 * ����:
 *    ptx--�˿ں�
 *      |__PTA        --Port A
 *      |__PTB        --Port B
 *      |__PTC        --Port C
 *      |__PTD        --Port D
 *      |__PTE        --Port E
 *    lsb_num--����8���˿����ŵ����λ�����
 *      |__0~24       --GPIO�ڵĵ�0~24λ
 *
 * ���:
 *    ָ��GPIO�ڵ�8λ���ݵĵ�ƽ
 *
 */
__INLINE uint8 LPLD_GPIO_Input_8b(GPIO_Type *ptx, uint8 lsb_num)
{
  return (uint8)((ptx->PDIR>>lsb_num)&0xFFL);
}

/*
 * PORTA--PORTE�жϴ�����
 * �������ļ�startup_K60.s�е��ж����������
 * �û������޸ģ������Զ������Ӧͨ���жϺ���
 */
void PORTA_IRQHandler(void)
{
#if (UCOS_II > 0u)
  OS_CPU_SR  cpu_sr = 0u;
  OS_ENTER_CRITICAL(); //��֪ϵͳ��ʱ�Ѿ��������жϷ����Ӻ���
  OSIntEnter();
  OS_EXIT_CRITICAL();
#endif
  
  //�����û��Զ����жϷ���
  GPIO_ISR[0](); 
  PORTA->ISFR =0xFFFFFFFF;
  
#if (UCOS_II > 0u)
  OSIntExit();          //��֪ϵͳ��ʱ�����뿪�жϷ����Ӻ���
#endif
}//           ;87:  PORT A interrupt

void PORTB_IRQHandler(void)
{
#if (UCOS_II > 0u)
  OS_CPU_SR  cpu_sr = 0u;
  OS_ENTER_CRITICAL(); //��֪ϵͳ��ʱ�Ѿ��������жϷ����Ӻ���
  OSIntEnter();
  OS_EXIT_CRITICAL();
#endif
  
  //�����û��Զ����жϷ���
  GPIO_ISR[1](); 
  PORTB->ISFR =0xFFFFFFFF;
  
#if (UCOS_II > 0u)
  OSIntExit();          //��֪ϵͳ��ʱ�����뿪�жϷ����Ӻ���
#endif
}//           ;88:  PORT B interrupt

void PORTC_IRQHandler(void)
{
#if (UCOS_II > 0u)
  OS_CPU_SR  cpu_sr = 0u;
  OS_ENTER_CRITICAL(); //��֪ϵͳ��ʱ�Ѿ��������жϷ����Ӻ���
  OSIntEnter();
  OS_EXIT_CRITICAL();
#endif
  
  //�����û��Զ����жϷ���
  GPIO_ISR[2](); 
  PORTC->ISFR =0xFFFFFFFF;
  
#if (UCOS_II > 0u)
  OSIntExit();          //��֪ϵͳ��ʱ�����뿪�жϷ����Ӻ���
#endif
}//           ;89:  PORT C interrupt

void PORTD_IRQHandler(void)
{
#if (UCOS_II > 0u)
  OS_CPU_SR  cpu_sr = 0u;
  OS_ENTER_CRITICAL(); //��֪ϵͳ��ʱ�Ѿ��������жϷ����Ӻ���
  OSIntEnter();
  OS_EXIT_CRITICAL();
#endif
  
  //�����û��Զ����жϷ���
  GPIO_ISR[3](); 
  PORTD->ISFR =0xFFFFFFFF;
  
#if (UCOS_II > 0u)
  OSIntExit();          //��֪ϵͳ��ʱ�����뿪�жϷ����Ӻ���
#endif
}//           ;90:  PORT D interrupt

void PORTE_IRQHandler(void)
{
#if (UCOS_II > 0u)
  OS_CPU_SR  cpu_sr = 0u;
  OS_ENTER_CRITICAL(); //��֪ϵͳ��ʱ�Ѿ��������жϷ����Ӻ���
  OSIntEnter();
  OS_EXIT_CRITICAL();
#endif
  
  //�����û��Զ����жϷ���
  GPIO_ISR[4](); 
  PORTE->ISFR =0xFFFFFFFF;
  
#if (UCOS_II > 0u)
  OSIntExit();          //��֪ϵͳ��ʱ�����뿪�жϷ����Ӻ���
#endif
}//           ;91:  PORT E interrupt