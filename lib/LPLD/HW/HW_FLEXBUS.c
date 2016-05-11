/**
 * @file HW_FLEXBUS.c
 * @version 3.0[By LPLD]
 * @date 2013-06-18
 * @brief FLEXBUS�ײ�ģ����غ���
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
#include "HW_FLEXBUS.h"

const uint32* FB_PORT[32] = {(uint32*)&PORTD->PCR[6], (uint32*)&PORTD->PCR[5], (uint32*)&PORTD->PCR[4], (uint32*)&PORTD->PCR[3],
                             (uint32*)&PORTD->PCR[2], (uint32*)&PORTC->PCR[10], (uint32*)&PORTC->PCR[9], (uint32*)&PORTC->PCR[8],
                             (uint32*)&PORTC->PCR[7], (uint32*)&PORTC->PCR[6], (uint32*)&PORTC->PCR[5], (uint32*)&PORTC->PCR[4],
                             (uint32*)&PORTC->PCR[2], (uint32*)&PORTC->PCR[1], (uint32*)&PORTC->PCR[0], (uint32*)&PORTB->PCR[18],
                             (uint32*)&PORTB->PCR[17], (uint32*)&PORTB->PCR[16], (uint32*)&PORTB->PCR[11], (uint32*)&PORTB->PCR[10],
                             (uint32*)&PORTB->PCR[9], (uint32*)&PORTB->PCR[8], (uint32*)&PORTB->PCR[7], (uint32*)&PORTB->PCR[6],
                             (uint32*)&PORTC->PCR[15], (uint32*)&PORTC->PCR[14], (uint32*)&PORTC->PCR[13], (uint32*)&PORTC->PCR[12],
                             (uint32*)&PORTB->PCR[23], (uint32*)&PORTB->PCR[22], (uint32*)&PORTB->PCR[21], (uint32*)&PORTB->PCR[20]};

/*
 * LPLD_FlexBus_Init
 * FlexBuxͨ�ó�ʼ������
 * 
 * ����:
 *    fb_init_struct--FlexBus��ʼ���ṹ�壬
 *                        ���嶨���FB_InitTypeDef
 *
 * ���:
 *    0--���ô���
 *    1--���óɹ�
 */
uint8 LPLD_FlexBus_Init(FB_InitTypeDef fb_init_struct)
{
  FBx Fbx = fb_init_struct.FB_Fbx;
  uint32 base_addr = fb_init_struct.FB_ChipSelAddress;
  uint32 addr_space = fb_init_struct.FB_AddressSpace;
  uint8 size = fb_init_struct.FB_PortSize;
  boolean justied = fb_init_struct.FB_IsRightJustied;
  boolean aa = fb_init_struct.FB_AutoAckEnable;
  uint8 ws = fb_init_struct.FB_WateStates;
  uint8 rah = fb_init_struct.FB_ReadAddrHold; 
  uint8 wah = fb_init_struct.FB_WriteAddrHold;
  uint32* pcr;
  uint8 n=0;
  
  //�������
  ASSERT( Fbx <= 5);    //�ж�FBͨ����
  ASSERT( base_addr >= 0x60000000 && base_addr <= 0xDFFFFFFF);    //�жϻ���ַ�Ϸ���
  ASSERT( addr_space != 0);    //Ѱַ�ռ��С
  ASSERT( size <= 3);    //�ж�����λ��
  ASSERT( rah <= 3);     //�ж϶���ַ����ʱ��
  ASSERT( wah <= 3);     //�ж�д��ַ����ʱ��
  
  FB->CS[Fbx].CSMR = 0;
      
  //���û���ַ
  FB->CS[Fbx].CSAR = base_addr;
  //�˿�λ��
  FB->CS[Fbx].CSCR  = FB_CSCR_PS(size);      
  
  if(justied)
  {
    FB->CS[Fbx].CSCR |= FB_CSCR_BLS_MASK;   // �����Ҷ���
  }
      
  if(aa)    
  {
    FB->CS[Fbx].CSCR |= FB_CSCR_AA_MASK;   //ʹ���ڲ�Ӧ��
  }
  
  FB->CS[Fbx].CSCR |= FB_CSCR_WS(ws)    // ���ڲ�Ӧ���ź�֮ǰ����ws��WS
                     | FB_CSCR_RDAH(rah)
                     | FB_CSCR_WRAH(wah);
  
  //����Ѱַ�ռ��С�������ַ����
  addr_space = (addr_space-1)>>16;
  FB->CS[Fbx].CSMR = FB_CSMR_BAM(addr_space)  //���û���ַ����Ϊ128K��ַ�ռ� =2^n(n=BAM+16)
                | FB_CSMR_V_MASK;    //ʹ��CS�ź�
  
  //ʹ�ܸ��ù��ܵ�FB_CSn�����Ÿ���
  if(Fbx == FB0)
  {
    PORTD->PCR[1]  = PORT_PCR_MUX(5);       // FB_CS0     
  }
  else if(Fbx == FB1)
  {
    FB->CSPMCR &= ~(FB_CSPMCR_GROUP1_MASK);
    FB->CSPMCR |= FB_CSPMCR_GROUP1(1);      
    PORTD->PCR[0]  = PORT_PCR_MUX(5);       // FB_CS1  
  }
  else if(Fbx == FB2)
  {
    FB->CSPMCR &= ~(FB_CSPMCR_GROUP4_MASK);
    FB->CSPMCR |= FB_CSPMCR_GROUP4(1);     
    PORTC->PCR[18]  = PORT_PCR_MUX(5);       // FB_CS2
  }
  else if(Fbx == FB3)
  {
    FB->CSPMCR &= ~(FB_CSPMCR_GROUP5_MASK);
    FB->CSPMCR |= FB_CSPMCR_GROUP5(1);     
    PORTC->PCR[19]  = PORT_PCR_MUX(5);       // FB_CS3
  }
  else if(Fbx == FB4)
  {
    FB->CSPMCR &= ~(FB_CSPMCR_GROUP2_MASK);
    FB->CSPMCR |= FB_CSPMCR_GROUP2(0);      
    PORTC->PCR[17]  = PORT_PCR_MUX(5);       // FB_CS4
  }
  else if(Fbx == FB5)
  {
    FB->CSPMCR &= ~(FB_CSPMCR_GROUP3_MASK);
    FB->CSPMCR |= FB_CSPMCR_GROUP3(0);     
    PORTC->PCR[16]  = PORT_PCR_MUX(5);       // FB_CS5
  }
  
  //ʹ�����ߵ�ַ���������Ÿ��ù���
  //��ʹ�ܵ�16λ��ַ����
  for(uint8 i=0; i<16; i++)
  {
    pcr = (uint32 *)FB_PORT[i];
    *pcr = PORT_PCR_MUX(5);    
  }
  //ʹ������ĵ�ַ����
  n=16;
  for(uint8 i=0; i<16; i++)
  {
    if((addr_space>>i)&0x01)
    {
      pcr = (uint32 *)FB_PORT[n++];
      *pcr = PORT_PCR_MUX(5); 
    }
  }
  //�����32λ����ʹ�ܸ�16λ
  n=0;
  if(size == 0)
  {   
    n=16;
  }else if(justied==0 && size == 0x10)
  {
    n=16;
  }else if(justied==0 && size == 0x01)
  {
    n=8;
  }
  if(n!=0)
  {
    for(uint8 i=31; i>31-n; i--)
    {
      pcr = (uint32 *)FB_PORT[i];
      *pcr = PORT_PCR_MUX(5);    
    }
  }
  
  //�����ź���
  PORTB->PCR[19] = PORT_PCR_MUX(5);          // fb_oe_b
  PORTC->PCR[11] = PORT_PCR_MUX(5);          // fb_rw_b  
              
  return 1;
}