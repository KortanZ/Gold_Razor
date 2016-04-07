/**
 * @file HW_ADC.h
 * @version 3.0[By LPLD]
 * @date 2013-06-18
 * @brief ADC�ײ�ģ����غ���
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
#ifndef __HW_ADC_H__
#define __HW_ADC_H__
/********************************************************************/

//ADCͨ��ö�ٶ���
typedef enum AdcChnEnum
{
  DAD0       =0,
  DAD1       =1,
  DAD2       =2,
  DAD3       =3,
  AD4        =4,
  AD5        =5,
  AD6        =6,
  AD7        =7,
  AD8        =8,
  AD9        =9,
  AD10       =10,
  AD11       =11,
  AD12       =12,
  AD13       =13,
  AD14       =14,
  AD15       =15,
  AD16       =16,
  AD17       =17,
  AD18       =18,
  AD19       =19,
  AD20       =20,
  AD21       =21,
  AD22       =22,
  AD23       =23,
  AD24       =24,
  AD25       =25,
  AD26       =26,
  AD27       =27,
  AD28       =28,
  AD29       =29,
  AD30       =30,
  AD31       =31
} AdcChnEnum_Type;

//���˺Ͳ��ģʽ�궨��
#define ADC_SE            0x00          //���˲ɼ�
#define ADC_DIFF          ADC_SC1_DIFF_MASK       //��ֲɼ�

//�ɼ�ʱ������
#define SAMTIME_SHORT     0x00          //�̲���ʱ��
#define SAMTIME_LONG      ADC_CFG1_ADLSMP_MASK    //������ʱ��

//������ʱ��궨��
#define LSAMTIME_20EX     0x00          //������ʱ������20������ADʱ��
#define LSAMTIME_12EX     0x01          //������ʱ������12������ADʱ��
#define LSAMTIME_6EX      0x02          //������ʱ������6������ADʱ��
#define LSAMTIME_2EX      0x03          //������ʱ������2������ADʱ��        

//ת�����Ⱥ궨��
#define SE_8BIT           0x00          //����8λ����
#define SE_10BIT          0x02          //����10λ����
#define SE_12BIT          0x01          //����12λ����
#define SE_16BIT          0x03          //����16λ����
#define DIFF_9BIT         SE_8BIT       //���9λ����
#define DIFF_11BIT        SE_10BIT      //���11λ����
#define DIFF_13BIT        SE_12BIT      //���13λ����
#define DIFF_16BIT        SE_16BIT      //���16λ����

//����Ӳ��ƽ���궨��
#define HW_DISAVG         0x00                         //����Ӳ��ƽ��
#define HW_4AVG           (0x00|ADC_SC3_AVGE_MASK)     //4��Ӳ��ƽ��
#define HW_8AVG           (0x01|ADC_SC3_AVGE_MASK)     //8��Ӳ��ƽ��
#define HW_16AVG          (0x02|ADC_SC3_AVGE_MASK)     //16��Ӳ��ƽ��
#define HW_32AVG          (0x03|ADC_SC3_AVGE_MASK)     //32��Ӳ��ƽ��

//ADC��������ѡ��
#define MUX_ADXXA         0x00          //ѡ��ADxxaͨ��               
#define MUX_ADXXB         ADC_CFG2_MUXSEL_MASK          //ѡ��ADxxbͨ��  

//Ӳ����������
#define HW_TRGDSABLE      0  //����Ӳ������
#define HW_TRGA           (ADC_SC2_ADTRG_MASK)  //SC1AӲ������
#define HW_TRGB           (ADC_SC2_ADTRG_MASK|0x01)  //SC1BӲ������

//PGA����궨��
#define PGA_1GAIN         (0x00|0x80)
#define PGA_2GAIN         (0x01|0x80)
#define PGA_4GAIN         (0x02|0x80)
#define PGA_8GAIN         (0x03|0x80)
#define PGA_16GAIN        (0x04|0x80)
#define PGA_32GAIN        (0x05|0x80)
#define PGA_64GAIN        (0x06|0x80)

//ADCʱ�ӷ�Ƶ�궨��
#define ADIV_1            0x00
#define ADIV_2            0x01
#define ADIV_4            0x02
#define ADIV_8            0x03

//���߷�Ƶ�궨��
#define ADICLK_BUS        0x00
#define ADICLK_BUS_2      0x01
#define ADICLK_ALTCLK     0x02
#define ADICLK_ADACK      0x03

//ADC�ο�Դ�궨��
#define REFSEL_EXT        0x00
#define REFSEL_ALT        0x01
#define REFSEL_RES        0x02     
#define REFSEL_RES_EXT    0x03   

//ADCģ���жϻص���������
typedef void (*ADC_ISR_CALLBACK)(void);

//ADCģ���ʼ���ṹ�壬��������ADC�������
typedef struct
{    
  /*
    ������
      ѡ��ADCx
    ȡֵ��
      ADC0��ADC1
      <ע:ֻ��MK60Fϵ�к���ADC2,ADC3>
      ADC2��ADC3
    ��ʼ����
      �����ʼ��
  */
  ADC_Type *ADC_Adcx;
  
  /*
    ������
      ת��ģʽѡ��
    ȡֵ��
      ADC_SE-���˲ɼ�
      ADC_DIFF-��ַּ�
    ��ʼ����
      �������ʼ����Ĭ��ADC_SE
  */
  uint8 ADC_DiffMode;
    
  /*
    ������
      ת������ѡ��
    ȡֵ��
      SE_8BIT-����8λ����
      SE_10BIT-����10λ����
      SE_12BIT-����12λ����
      SE_16BIT-����16λ����
      DIFF_9BIT-���9λ����
      DIFF_11BIT-���11λ����
      DIFF_13BIT-���13λ����
      DIFF_16BIT-���16λ����
    ��ʼ����
      �������ʼ����Ĭ��SE_8BIT
  */
  uint8 ADC_BitMode;
    
  /*
    ������
      ����ʱ��ѡ��
    ȡֵ��
      SAMTIME_SHORT-�̲���ʱ��
      SAMTIME_LONG-������ʱ��
    ��ʼ����
      �������ʼ����Ĭ��SAMTIME_SHORT
  */
  uint8 ADC_SampleTimeCfg;
    
  /*
    ������
      ������ʱ�����ADʱ��ѡ��
    ȡֵ��
      LSAMTIME_20EX-������ʱ������20������ADʱ��
      LSAMTIME_12EX-������ʱ������12������ADʱ��
      LSAMTIME_6EX-������ʱ������6������ADʱ��
      LSAMTIME_2EX-������ʱ������2������ADʱ�� 
    ��ʼ����
      �������ʼ����Ĭ��LSAMTIME_20EX
  */
  uint8 ADC_LongSampleTimeSel;
    
  /*
    ������
      Ӳ��ƽ������ѡ��
    ȡֵ��
      HW_DISAVG-����Ӳ��ƽ��
      HW_4AVG-4��Ӳ��ƽ��
      HW_8AVG-8��Ӳ��ƽ��
      HW_16AVG-16��Ӳ��ƽ��
      HW_32AVG-32��Ӳ��ƽ��
    ��ʼ����
      �������ʼ����Ĭ��HW_DISAVG
  */
  uint8 ADC_HwAvgSel;
    
  /*
    ������
      �ɱ������ѡ��ʹ����ӦPGA����ͨ������Ч
    ȡֵ��
      PGA_1GAIN-1������
      PGA_2GAIN-2������
      PGA_4GAIN-4������
      PGA_8GAIN-8������
      PGA_16GAIN-16������
      PGA_32GAIN-32������
      PGA_64GAIN-64������
    ��ʼ����
      �������ʼ����Ĭ��PGA_1GAIN
  */
  uint8 ADC_PgaGain;
    
  /*
    ������
      ADC����ͨ��a\b��������ѡ��
    ȡֵ��
      MUX_ADXXA-A����ͨ��
      MUX_ADXXB-B����ͨ��
    ��ʼ����
      �������ʼ����Ĭ��MUX_ADXXA
  */
  uint8 ADC_MuxSel;
    
  /*
    ������
      ADC��ʼ���Զ�У׼����ʹ��
    ȡֵ��
      TRUE-ʹ���Զ�У׼
      FALSE-�����Զ�У׼
    ��ʼ����
      �����ʼ��ΪTRUE
  */
  boolean ADC_CalEnable;
    
  /*
    ������
      ADCӲ����������
    ȡֵ��
      HW_TRGDSABLE-����Ӳ������
      HW_TRGA-Aת��ͨ��Ӳ������
      HW_TRGB-Bת��ͨ��Ӳ������
    ��ʼ����
      �������ʼ����Ĭ��HW_TRGDSABLE
  */
  uint8 ADC_HwTrgCfg;
    
  /*
    ������
      ʹ��ADC׼����ɴ���DMA����
    ȡֵ��
      TRUE-ʹ��DMA
      FALSE-����DMA
    ��ʼ����
      �������ʼ����Ĭ��FALSE
  */ 
  boolean ADC_DmaEnable;

  /*
    ������
      ADCx�жϻص�����
    ȡֵ��
      ��������Ϊ�޷���ֵ,�޲���(eg. void isr(void);)
    ��ʼ����
      �������ʼ������δ��ʼ���򲻻ᴥ���ж�
  */
  ADC_ISR_CALLBACK ADC_Isr; 
  
} ADC_InitTypeDef;

//ADCͨ�ó�ʼ��������ѡ��ADCx���ɼ�ģʽ�����ȵȲ���
uint8 LPLD_ADC_Init(ADC_InitTypeDef);
//ADC����ʼ������������ADCģ��
uint8 LPLD_ADC_Deinit(ADC_InitTypeDef);
//ʹ��ADCx��Ӧת��ͨ����AD�ɼ�����
uint8 LPLD_ADC_Chn_Enable(ADC_Type *, AdcChnEnum_Type);
//�������ģʽ��ȡADת�����
uint16 LPLD_ADC_Get(ADC_Type *, AdcChnEnum_Type);
//ʹ��ADCx�ж�
uint8 LPLD_ADC_EnableIrq(ADC_InitTypeDef);
//����ADCx�ж�
uint8 LPLD_ADC_DisableIrq(ADC_InitTypeDef);
//ʹ��ADCxת��ͨ������������жϡ�Ӳ��������ģʽ
void LPLD_ADC_EnableConversion(ADC_Type *, AdcChnEnum_Type, uint8, boolean);
//��ȡADת�����
uint16 LPLD_ADC_GetResult(ADC_Type *, uint8);
//��ȡSC1�Ĵ�����COCOλ��1�ı��
uint8 LPLD_ADC_GetSC1nCOCO(ADC_Type *);

#endif /* __HW_ADC_H__ */