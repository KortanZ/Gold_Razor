/**
 * @file HW_I2C.h
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
#ifndef __HW_I2C_H__
#define __HW_I2C_H__
/********************************************************************/
//I2Cģ���жϻص���������
typedef void (*I2C_ISR_CALLBACK)(void);  
//����ACK 
#define I2C_ACK_OFF                     (0)
#define I2C_ACK_ON                      (1)
//����������дģʽ 
#define I2C_MWSR                        (0x00)  
#define I2C_MRSW                        (0x01)  

typedef struct 
{
  /*
    ������
      ѡ��I2Cx
    ȡֵ��
      I2C0 -- I2Cͨ��0
      I2C1 -- I2Cͨ��1
    ��ʼ����
      �����ʼ��
  */
  I2C_Type *I2C_I2Cx;
  
  /*
    ������
      ��ѯI2Cʱ�����ñ��е�ICR��ȡֵ����������SCL����Ƶ��I2C_SCL_BusSpeed��SDA Hold Time��
      SCL hold start time��SCL hold stop time.
      I2C baud rate = bus speed (Hz)/(mul �� SCL divider)
      SDA hold time = bus period (s) �� mul �� SDA hold value
      SCL start hold time = bus period (s) �� mul �� SCL start hold value
      SCL stop hold time = bus period (s) �� mul �� SCL stop hold value
      ע��
      1������mul = 1��SCL divider��SDA hold value��SCL start hold value��SCL stop hold value
      ����ͨ������I2Cʱ�����ñ���,I2Cʱ�����ñ��ڱ��ļ���β��.
      2��bus speed��Hz���ǵ�Ƭ������������Ƶ�ʣ�����ͨ��K60_card.h�е�BUS_CLK_MHZ�궨������趨.
      3��bus period ��s��= 1/bus speed��Hz��.
      4��SCL����Ƶ�����400Khz.
    ȡֵ��
      ��I2Cʱ�����ñ��л��ICR��ֵ
    ��ʼ����
      �����ʼ��
  */
  uint8   I2C_ICR;
  
  /*
    ������
      ʹ��I2C�ж�
    ȡֵ��
      TRUE -ʹ��
      FALSE -����
    ��ʼ����
      �������ʼ����Ĭ��ֵFALSE
  */
  boolean I2C_IntEnable;
  
  /*
    ������
      SCL���ţ�ÿ��IICx��Ӧ��ͬ��Pin
    ȡֵ��
      I2C0 -*PTB2��PTB0��PTD8
      I2C1 -*PTC10��PTE1
    ��ʼ����
      �������ʼ����Ĭ��ֵΪ��*������
  */
  PortPinsEnum_Type I2C_SclPin;
  
  /*
    ������
      SDA���ţ�ÿ��IICx��Ӧ��ͬ��Pin
    ȡֵ��
      I2C0 -*PTB3��PTB1��PTD9
      I2C1 -*PTC11��PTE0
    ��ʼ����
      �������ʼ����Ĭ��ֵΪ��*������
  */
  PortPinsEnum_Type I2C_SdaPin;
  
  /*
    ������
      SCL��SDA�����Ƿ�ʹ�ܿ�©ģʽ
    ȡֵ��
      TRUE-ʹ��
      FALSE-����
    ��ʼ����
      �������ʼ����Ĭ��ֵΪFALSE
  */
  boolean I2C_OpenDrainEnable;
  
  /*
    ������
      I2C�жϻص�����
    ȡֵ��
      ��������Ϊ�޷���ֵ,�޲���(eg. void isr(void);)
    ��ʼ����
      �������ʼ������δ��ʼ���򲻻ᴥ���ж�
  */
  I2C_ISR_CALLBACK I2C_Isr;

}I2C_InitTypeDef;

//��ʼ��I2Cxͨ����SCL����Ƶ�ʣ�SDA��SCL���ţ������ж�
uint8 LPLD_I2C_Init(I2C_InitTypeDef);
//I2Cx����ʼ���������ر�I2Cx�жϣ�����I2Cx
uint8 LPLD_I2C_Deinit(I2C_InitTypeDef);
//I2Cx�ж�ʹ�ܺ���
void LPLD_I2C_EnableIrq(I2C_InitTypeDef);
//I2Cx�жϽ�ֹ����
void LPLD_I2C_DisableIrq(I2C_InitTypeDef);
//I2Cx������ʼ�źź���
void LPLD_I2C_Start(I2C_Type *);
//I2Cx����ֹͣ�źź���
void LPLD_I2C_Stop(I2C_Type *);
//I2Cx�ȴ�ACK�źź���
void LPLD_I2C_WaitAck(I2C_Type *, uint8);
//I2Cx�ٴβ�����ʼ�źź���
void LPLD_I2C_ReStart(I2C_Type *);
//I2Cx����һ���ֽں���
void LPLD_I2C_WriteByte(I2C_Type *, uint8);
//I2Cx��ȡһ���ֽں���
uint8 LPLD_I2C_ReadByte(I2C_Type *);
//I2Cx������дģʽ���ú���
void LPLD_I2C_SetMasterWR(I2C_Type *, uint8);
//I2C��ʼ���亯������Ҫ������Χ�豸��ַ�Ͷ�дģʽ
void LPLD_I2C_StartTrans(I2C_Type *, uint8, uint8);

/*
I2Cʱ�����ñ�ѡȡICR��ֵ��������SCl divider��SDA Hold value��SCL Hold(Start��stop)Value  
By LPLD
__________________________________________________________________________________________
ICR  | SCL    |SDA Hold|SCL Hold |SCL Hold   ||  ICR  | SCL     |SDA Hold |SCL Hold |SCL Hold 
(hex)| Divider|Value   |(Start)  | (Stop)    ||  (hex)| Divider |Value    |(Start)  | (Stop)
     |        |        | Value   |  Value    ||       |         |         | Value   |  Value
_____|________|________|_________|___________||_______|_________|_________|_________|________
00   |   20   |   7    |      6  |      11   ||  20   |  160    |  17     |   78    |    81
01   |   22   |   7    |      7  |      12   ||  21   |  192    |  17     |   94    |    97
02   |   24   |   8    |      8  |      13   ||  22   |  224    |  33     |  110    |   113
03   |   26   |   8    |      9  |      14   ||  23   |  256    |  33     |  126    |   129
04   |   28   |   9    |     10  |      15   ||  24   |  288    |  49     |  142    |   145
05   |   30   |   9    |     11  |      16   ||  25   |  320    |  49     |  158    |   161
06   |   34   |  10    |     13  |      18   ||  26   |  384    |  65     |  190    |   193
07   |   40   |  10    |     16  |      21   ||  27   |  480    |  65     |  238    |   241
08   |   28   |   7    |     10  |      15   ||  28   |  320    |  33     |  158    |   161
09   |   32   |   7    |     12  |      17   ||  29   |  384    |  33     |  190    |   193
0A   |   36   |   9    |     14  |      19   ||  2A   |  448    |  65     |  222    |   225
0B   |   40   |   9    |     16  |      21   ||  2B   |  512    |  65     |  254    |   257
0C   |   44   |  11    |     18  |      23   ||  2C   |  576    |  97     |  286    |   289
0D   |   48   |  11    |     20  |      25   ||  2D   |  640    |  97     |  318    |   321
0E   |   56   |  13    |     24  |      29   ||  2E   |  768    | 129     |  382    |   385
0F   |   68   |  13    |     30  |      35   ||  2F   |  960    | 129     |  478    |   481
10   |   48   |   9    |     18  |      25   ||  30   |  640    |  65     |  318    |   321
11   |   56   |   9    |     22  |      29   ||  31   |  768    |  65     |  382    |   385
12   |   64   |  13    |     26  |      33   ||  32   |  896    | 129     |  446    |   449
13   |   72   |  13    |     30  |      37   ||  33   |  1024   | 129     |  510    |   513
14   |   80   |  17    |     34  |      41   ||  34   |  1152   | 193     |  574    |   577
15   |   88   |  17    |     38  |      45   ||  35   |  1280   | 193     |  638    |   641
16   |   104  |  21    |     46  |      53   ||  36   |  1536   | 257     |  766    |   769
17   |   128  |  21    |     58  |      65   ||  37   |  1920   | 257     |  958    |   961
18   |   80   |   9    |     38  |      41   ||  38   |  1280   | 129     |  638    |   641  
19   |   96   |   9    |     46  |      49   ||  39   |  1536   | 129     |  766    |   769
1A   |  112   |  17    |     54  |      57   ||  3A   |  1792   | 257     |  894    |   897
1B   |  128   |  17    |     62  |      65   ||  3B   |  2048   | 257     | 1022    |  1025
1C   |  144   |  25    |     70  |      73   ||  3C   |  2304   | 385     | 1150    |  1153
1D   |  160   |  25    |     78  |      81   ||  3D   |  2560   | 385     | 1278    |  1281
1E   |  192   |  33    |     94  |      97   ||  3E   |  3072   | 513     | 1534    |  1537
1F   |  240   |  33    |    118  |     121   ||  3F   |  3840   | 513     | 1918    |  1921
____________________________________________________________________________________________  

*/
#endif /* __HW_I2C_H__ */
