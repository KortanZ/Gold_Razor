/**
 * @file HW_FLEXBUS.h
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
#ifndef __HW_FLEXBUS_H__
#define __HW_FLEXBUS_H__

//FlexBusģ��Ŷ���
typedef enum FBx
{
  FB0=0,
  FB1=1,
  FB2=2,
  FB3=3,
  FB4=4,
  FB5=5
}FBx;

//FB_InitTypeDef�ṹ��FB_PortSizeȡֵ
#define FB_SIZE_8BIT    0x01
#define FB_SIZE_16BIT   0x02
#define FB_SIZE_32BIT   0x00
//FB_InitTypeDef�ṹ��FB_AddressSpaceȡֵ
#define FB_SPACE_KB(n)  (n*1024)

typedef struct 
{    
  /*
    ������
      ѡ��FBx
    ȡֵ��
      FB0��FB1��FB2��FB3��FB4��FB5
    ��ʼ����
      �����ʼ��
  */
  FBx FB_Fbx;
  
  /*
    ������
      ����FBx��Ƭѡ��ַ����Ѱַ����ַ
    ȡֵ��
      0x60000000~0xDFFFFFFF-������FlexBuxѰַ��Χ��
    ��ʼ����
      �����ʼ��
  */
  uint32 FB_ChipSelAddress;
  
  /*
    ������
      ����FBx���ߵ�Ѱַ�ռ��С
    ȡֵ��
      FB_SPACE_KB(n)-��nKB��С
    ��ʼ����
      �����ʼ��
  */
  uint32 FB_AddressSpace;
  
  /*
    ������
      ����FBx���ߵ�����λ��
    ȡֵ��
      FB_SIZE_8BIT-8λ��
      FB_SIZE_16BIT-16λ��
      FB_SIZE_32BIT-32λ��
    ��ʼ����
      �������ʼ����Ĭ��FB_SIZE_8BIT
  */
  uint8 FB_PortSize;
  
  /*
    ������
      ����FBx���ߵ������Ƿ�Ϊ�Ҷ���
    ȡֵ��
      TRUE-�Ҷ���
      FALSE-�����
    ��ʼ����
      �������ʼ����Ĭ�������
  */
  boolean FB_IsRightJustied;
    
  /*
    ������
      ����FBx�����Ƿ��Զ������ڲ�Ӧ��
    ȡֵ��
      TRUE-ʹ��
      FALSE-����
    ��ʼ����
      �������ʼ����Ĭ�������
  */  
  boolean FB_AutoAckEnable; 
  
  /*
    ������
      ����FBx�����ڲ����ڲ�Ӧ��ǰ����ĵȴ�����
    ȡֵ��
      0~63
    ��ʼ����
      �������ʼ����Ĭ��0
  */ 
  uint8 FB_WateStates;
  
  /*
    ������
      ����FBx���ߵĶ���ַ�ź���CSʹ��֮ǰ����ʱ��
    ȡֵ��
      0-���FB_AutoAckEnable����Ϊ1�����ڣ�����0������
      1-���FB_AutoAckEnable����Ϊ2�����ڣ�����1������
      2-���FB_AutoAckEnable����Ϊ3�����ڣ�����2������
      3-���FB_AutoAckEnable����Ϊ4�����ڣ�����3������
    ��ʼ����
      �������ʼ����Ĭ��0
  */ 
  uint8 FB_ReadAddrHold;
  
  /*
    ������
      ����FBx���ߵ�д��ַ�ź���CSʹ��֮ǰ����ʱ��
    ȡֵ��
      0-1������
      1-2������
      2-3������
      3-4������
    ��ʼ����
      �������ʼ����Ĭ��0
  */ 
  uint8 FB_WriteAddrHold;
  
}FB_InitTypeDef;
  
//FlexBuxͨ�ó�ʼ������
uint8 LPLD_FlexBus_Init(FB_InitTypeDef);

#endif /* __HW_FLEXBUS_H__ */
