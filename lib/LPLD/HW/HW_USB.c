/**
 * @file HW_USB.c
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
#include "common.h"     /* Common definitions */
#include "HW_USB.h"
#include "usb_driver.h"

//�û��Զ����жϷ���������
USB_ISR_CALLBACK USB_ISR[1];

/*
* LPLD_USB_Init
* K60 USB�����ʼ������
* �ڸú�����,��ʼ��USB����ʱ��,����USB������жϷ�����,
* ���ҵ���USB�豸��ʼ������
*/

void LPLD_USB_Init(void)
{ 
  MPU->CESR=0; //MPU ����
#if (defined(CPU_MK60DZ10))  
  SIM->SOPT2 |= SIM_SOPT2_USBSRC_MASK |   //ѡ��PLL/FLL��Ϊʱ��Դ
               SIM_SOPT2_PLLFLLSEL_MASK; //��PLL��ΪUSB��ʱ��Դ����ʱ��PLL��Ƶ��Ϊ96Mhz 
#if(CORE_CLK_MHZ == PLL_96)
  SIM->CLKDIV2 = 0x02;                    //���÷�Ƶϵ��USBʱ�� = 96Mhz/2 =48Mhz
#endif 
  SIM->SCGC4 |= SIM_SCGC4_USBOTG_MASK;  //ʹ��USB����ʱ��
#elif defined(CPU_MK60F12) || defined(CPU_MK60F15)
  SIM->SOPT2 |= SIM_SOPT2_PLLFLLSEL(1)      // ѡ�� PLL0 ��Ϊ�ο�   
            |  SIM_SOPT2_USBFSRC(0)         // ѡ�� MCGPLLCLK ��Ϊ CLKC �ο�Դ 
            |  SIM_SOPT2_USBF_CLKSEL_MASK;  // ѡ�� USB fractional divider ��λ USB reference clock �ο�Դ 
#if(CORE_CLK_MHZ == PLL_120)
// MCGPLLCLK =  120MHz 
// USB Clock = PLL0 x (FRAC +1) / (DIV+1)    
// USB Clock = 120MHz x (1+1) / (4+1) = 48 MHz   
  SIM->CLKDIV2 = SIM_CLKDIV2_USBFSFRAC_MASK | SIM_CLKDIV2_USBFSDIV(4);
#endif
  SIM->SCGC4 |= SIM_SCGC4_USBFS_MASK;   //ʹ��USB����ʱ�� 
#endif 
  USB0->USBTRC0 = 0x40;                   //�����ĵ���������λ��������Ϊ1
  SIM->SOPT1 |= SIM_SOPT1_USBREGEN_MASK;  //����USB�豸��ѹԴ
  
  /* NVICģ������ */
  enable_irq(USB0_IRQn);                 //ʹ��NVIC�е�USB OTG�ж�
  USB_ISR[0] = USB_DEVICE_ISR;           //��USBЭ�鴦������ӵ��жϴ�����������
  
#if(USB_DEVICE_CLASS == USB_DEVICE_CLASS_CDC)
  USB_CDC_Init();                        //��ʼ��CDC��
#elif(USB_DEVICE_CLASS == USB_DEVICE_CLASS_HID)
  USB_HID_Mouse_Init();                  //��ʼ��HID��
#endif
  
  
}

/*
* LPLD_USB_DeInit
* K60 USBģ��ע������
* ע����ѡ���USB�豸
*/

void LPLD_USB_DeInit(void)
{ 
#if(USB_DEVICE_CLASS == USB_DEVICE_CLASS_CDC)
  USB_Class_CDC_DeInit(CONTROLLER_ID);                        //ע��CDC��
#elif(USB_DEVICE_CLASS == USB_DEVICE_CLASS_HID)
  USB_Class_HID_DeInit(CONTROLLER_ID);                        //ע��HID��
#endif
}

#if(USB_DEVICE_CLASS == USB_DEVICE_CLASS_CDC)
/*
*  LPLD_USB_VirtualCom_Rx
*  ��USB CDC��ģʽ����ɴ���ģʽ���ú����Ǵ��ڽ��պ���
*  ������
*      *rx_buf--ָ���û����ݴ洢�������ڴ�����յ�������
*  ������������ݵĳ��ȣ����ֽ�Ϊ��λ
*/
uint8 LPLD_USB_VirtualCom_Rx(uint8 *rx_buf)
{
  memcpy(rx_buf,tUSB_Rev_Data.buffer,tUSB_Rev_Data.len);
  return tUSB_Rev_Data.len;
}

/*
*  LPLD_USB_VirtualCom_Tx
*  ��USB CDC��ģʽ����ɴ���ģʽ���ú����Ǵ��ڷ��ͺ���
*  ������
*      *tx_buf -- ָ���û����ݴ洢�������ڴ���Ҫ���͵�����
*      len -- Ҫ���͵����ݳ���
*  �����0x00   ���ͳɹ�
*        ��0x00 ����ʧ��
*/
uint8 LPLD_USB_VirtualCom_Tx(uint8 *tx_buf,uint8 len)
{
  uint8 status = 0;
  status = USB_Class_CDC_Interface_DIC_Send_Data(CONTROLLER_ID,tx_buf,len);
  return status;
}

/*
*  LPLD_USB_SetRevIsr
*  ���USB ���⴮�ڽ��������жϷ�����
*  ��
*  ��
*/
void LPLD_USB_SetRevIsr(USB_REV_ISR_CALLBACK isr)
{
  USB_Rev_SetIsr(isr);
}

/*
*  LPLD_USB_QueueData
*  ��USB���ڴ��лָ����յ������ݵ��û��ڴ���
*  ���ճɹ�����ô˺���
*  ��
*  ��
*/
void LPLD_USB_QueueData(void)
{
  (void)USB_Class_CDC_Interface_DIC_Recv_Data(CONTROLLER_ID, NULL, 0);
}
#endif

#if(USB_DEVICE_CLASS == USB_DEVICE_CLASS_HID)
/*
*  LPLD_USB_HID_MouseControl
*  HID�����ƺ���
*  ����
*    uint8 *buf -- �������4���ֽڿ�������
*      ��һ���ֽڿ���������Ҽ�
*        ȡֵ��MOUSE_LEFT_CLICK  ���
*              MOUSE_RIGHT_CLICK �Ҽ�
*      �ڶ����ֽڿ���X���ƶ�
*        ȡֵ��MOUSE_LEFT_MOVE   ����
*              MOUSE_RIGHT_MOVE  ����
*      �������ֽڿ���Y���ƶ�
*        ȡֵ��MOUSE_UP_MOVE    ����
*              MOUSE_DOWN_MOVE  ����
*  �����
*    ��
*/
void LPLD_USB_HID_MouseControl(uint8 *buf)
{
  USB_HID_MouseControl(buf);
}

/*
*  LPLD_USB_HID_LoopTask
*  ��main loop��ѭ�����������
*  ����
*    uint8 *buf -- �������4���ֽڿ�������
*      ��һ���ֽڿ���������Ҽ�
*        ȡֵ��MOUSE_LEFT_CLICK  ���
*              MOUSE_RIGHT_CLICK �Ҽ�
*      �ڶ����ֽڿ���X���ƶ�
*        ȡֵ��MOUSE_LEFT_MOVE   ����
*              MOUSE_RIGHT_MOVE  ����
*      �������ֽڿ���Y���ƶ�
*        ȡֵ��MOUSE_UP_MOVE    ����
*              MOUSE_DOWN_MOVE  ����
*  �����
*    ��
*/
void LPLD_USB_HID_LoopTask(uint8 *buf)
{
  if(USB_HID_Mouse_Task())
  {
    LPLD_USB_HID_MouseControl(buf);
  }
}
#endif
/*
*  LPLD_USB_Isr
*  USB�жϴ�����
*/
void USB_OTG_IRQHandler(void)
{
  //�����û��Զ����жϷ���
  USB_ISR[0]();  
}