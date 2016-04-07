/**
 * @file HW_FTM.h
 * @version 3.0[By LPLD]
 * @date 2013-06-18
 * @brief FTM�ײ�ģ����غ���
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
#ifndef __HW_FTM_H__
#define __HW_FTM_H__
/********************************************************************/

//FTMͨ��ö�ٶ���
typedef enum FtmChnEnum
{
  FTM_Ch0       =0,
  FTM_Ch1       =1,
  FTM_Ch2       =2,
  FTM_Ch3       =3,
  FTM_Ch4       =4,
  FTM_Ch5       =5,
  FTM_Ch6       =6,
  FTM_Ch7       =7,
  FTM_PhA       =8,
  FTM_PhB       =9
} FtmChnEnum_Type;

#define FTM_MODE_PWM    0x01    //PWM���ģʽ
#define FTM_MODE_IC     0x02    //���벶��ģʽ
#define FTM_MODE_QD     0x04    //��������ģʽ
#define FTM_MODE_DEC    0x08    //˫��Ե����ģʽ

#define FTM_CLK_DIV1    0       //FTM CLK��Ƶϵ��1
#define FTM_CLK_DIV2    1       //FTM CLK��Ƶϵ��2
#define FTM_CLK_DIV4    2       //FTM CLK��Ƶϵ��4
#define FTM_CLK_DIV8    3       //FTM CLK��Ƶϵ��8
#define FTM_CLK_DIV16   4       //FTM CLK��Ƶϵ��16
#define FTM_CLK_DIV32   5       //FTM CLK��Ƶϵ��32
#define FTM_CLK_DIV64   6       //FTM CLK��Ƶϵ��64
#define FTM_CLK_DIV128  7       //FTM CLK��Ƶϵ��128

#define ALIGN_LEFT  (FTM_CnSC_MSB_MASK|FTM_CnSC_ELSB_MASK)    //PWM�����
#define ALIGN_RIGHT (FTM_CnSC_MSB_MASK|FTM_CnSC_ELSA_MASK)    //PWM�����

#define DEADTIME_CH01   FTM_COMBINE_DTEN0_MASK  //FTM_Ch0\FTM_Ch1��������
#define DEADTIME_CH23   FTM_COMBINE_DTEN1_MASK  //FTM_Ch0\FTM_Ch1��������
#define DEADTIME_CH45   FTM_COMBINE_DTEN2_MASK  //FTM_Ch0\FTM_Ch1��������
#define DEADTIME_CH67   FTM_COMBINE_DTEN3_MASK  //FTM_Ch0\FTM_Ch1��������

#define DEADTIME_DIV1   0    //PWM����CLK��Ƶϵ��1
#define DEADTIME_DIV4   1    //PWM����CLK��Ƶϵ��4
#define DEADTIME_DIV16  3    //PWM����CLK��Ƶϵ��16

#define CAPTURE_RI      FTM_CnSC_ELSA_MASK      //�����ز���
#define CAPTURE_FA      FTM_CnSC_ELSB_MASK      //�½��ز���
#define CAPTURE_RIFA    (FTM_CnSC_ELSA_MASK|FTM_CnSC_ELSB_MASK)      //�����½��ز���

#define QD_MODE_PHAB    0                               //AB�����ģʽ
#define QD_MODE_CNTDIR  FTM_QDCTRL_QUADMODE_MASK        //�����ͷ������ģʽ

//FTMģ���жϻص���������
typedef void (*FTM_ISR_CALLBACK)(void);

//FTMģ���ʼ���ṹ�壬��������FTM�������
typedef struct
{
  /*
    ������
      ѡ��FTMx
    ȡֵ��
      MK60Dϵ�У�
        FTM0��FTM1��FTM2
      MK60Fϵ�� :
        FTM0��FTM1��FTM2��FTM3
    ��ʼ����
      �����ʼ��
  */
  FTM_Type *FTM_Ftmx;
  
  /*
    ������
      ����FTMx�Ĺ���ģʽ
    ȡֵ��
      FTM_MODE_PWM-PWM���ģʽ
      FTM_MODE_IC-���벶��ģʽ
      FTM_MODE_QD-��������ģʽ
    ��ʼ����
      �����ʼ��
  */
  uint8 FTM_Mode;
  
  /*
    ������
      ����PWMģʽ�µ�PWM���Ƶ�ʣ���λHz
    ȡֵ��
      1~0xFFFFFFFF
    ��ʼ����
      FTM_MODE_PWMģʽ�±����ʼ��
  */
  uint32 FTM_PwmFreq;
  
  /*
    ������
      ����PWMģʽ�µ���Ӧͨ���Ե���������
    ȡֵ��  
      DEADTIME_CH01-ͨ��0��ͨ��1��������
      DEADTIME_CH23-ͨ��2��ͨ��3��������
      DEADTIME_CH45-ͨ��4��ͨ��5��������
      DEADTIME_CH67-ͨ��6��ͨ��7��������
    ��ʼ����
      �����ʼ����Ĭ�ϲ���������
  */
  uint32 FTM_PwmDeadtimeCfg;
  
  /*
    ������
      PWMģʽ���������ܶ�����ʱ�ӵķ�Ƶϵ��
    ȡֵ��  
      DEADTIME_DIV1-����1��Ƶ
      DEADTIME_DIV4-����4��Ƶ
      DEADTIME_DIV16-����16��Ƶ
    ��ʼ����
      �����ʼ��
  */
  uint8 FTM_PwmDeadtimeDiv;

  /*
    ������
      PWMģʽ���������ܲ���ĸ���
    ȡֵ��  
      0~63��0Ϊ����������
    ��ʼ����
      �����ʼ��
  */
  uint8 FTM_PwmDeadtimeVal;
  
  /*
    ������
      ��������Ľ���ģʽ
    ȡֵ��  
      QD_MODE_PHAB-AB�����ģʽ
      QD_MODE_CNTDIR-�����ͷ������ģʽ
    ��ʼ����
      �����ʼ����Ĭ��AB�����ģʽ
  */
  uint8 FTM_QdMode;
  
  /*
    ������
      FTMxʱ���������ʱ�ӵķ�Ƶϵ��
    ȡֵ��  
      FTM_CLK_DIV1-FTM CLK��Ƶϵ��1
      FTM_CLK_DIV2-FTM CLK��Ƶϵ��2
      FTM_CLK_DIV4-FTM CLK��Ƶϵ��4
      FTM_CLK_DIV8-FTM CLK��Ƶϵ��8
      FTM_CLK_DIV16-FTM CLK��Ƶϵ��16
      FTM_CLK_DIV32-FTM CLK��Ƶϵ��32
      FTM_CLK_DIV64-FTM CLK��Ƶϵ��64
      FTM_CLK_DIV128-FTM CLK��Ƶϵ��128
    ��ʼ����
      FTM_MODE_ICģʽ�����ʼ��
  */
  uint8 FTM_ClkDiv;
  
  /*
    ������
      ʹ�ܼ���������ж�
    ȡֵ��  
      TRUE��FALSE
    ��ʼ����
      �����ʼ��
  */
  boolean FTM_ToiEnable;
  
  /*
    ������
      FTMx�жϻص�����
    ȡֵ��
      ��������Ϊ�޷���ֵ,�޲���(eg. void isr(void);)
    ��ʼ����
      �������ʼ������δ��ʼ���򲻻ᴥ���ж�
  */
  FTM_ISR_CALLBACK FTM_Isr; 
  
} FTM_InitTypeDef;

//FTMģ��ͨ�ó�ʼ�����ɳ�ʼ��ΪPWM�����벶���������롢˫�߲���ģʽ
uint8 LPLD_FTM_Init(FTM_InitTypeDef);
//FTMģ��ͨ�÷���ʼ��
uint8 LPLD_FTM_Deinit(FTM_InitTypeDef);
//FTMģ��PWMģʽ���ʹ�ܣ��������ͨ����ռ�ձȡ�ָ����Ӧ�����š����뷽ʽ
uint8 LPLD_FTM_PWM_Enable(FTM_Type *, FtmChnEnum_Type, uint32, PortPinsEnum_Type, uint8);
//���FTMģ��PWMģʽָ��ͨ�������ռ�ձ�
uint8 LPLD_FTM_PWM_ChangeDuty(FTM_Type *, FtmChnEnum_Type, uint32);
//FTMģ�����벶��ģʽ���ʹ�ܣ���������ͨ����ָ����Ӧ�����š������Ե
uint8 LPLD_FTM_IC_Enable(FTM_Type *, FtmChnEnum_Type, PortPinsEnum_Type, uint8);
//����FTMģ��ָ��ͨ�������������
uint8 LPLD_FTM_DisableChn(FTM_Type *, FtmChnEnum_Type);
//FTMģ����������ģʽ����ʹ�ܣ���������ͨ��PHA��PHB
uint8 LPLD_FTM_QD_Enable(FTM_Type *, PortPinsEnum_Type, PortPinsEnum_Type);
//FTMģ����������ģʽ�������
uint8 LPLD_FTM_QD_Disable(FTM_Type *);

//�ж�FTMx�Ƿ������������жϱ�־
boolean LPLD_FTM_IsTOF(FTM_Type *);
//���FTMx����������жϱ�־
void LPLD_FTM_ClearTOF(FTM_Type *);
//�ж�ͨ��n�Ƿ�����жϱ�־
boolean LPLD_FTM_IsCHnF(FTM_Type *, FtmChnEnum_Type);
//���ͨ��n�жϱ�־
void LPLD_FTM_ClearCHnF(FTM_Type *, FtmChnEnum_Type);
//��ȡFTMxͨ��n�����FTMx����ֵ
uint16 LPLD_FTM_GetChVal(FTM_Type *, FtmChnEnum_Type);
//��ȡFTMxʱ�ӷ�Ƶϵ��
uint8 LPLD_FTM_GetClkDiv(FTM_Type *);
//��ȡFTMx������ֵ
uint16 LPLD_FTM_GetCounter(FTM_Type *);
//���FTMx������
void LPLD_FTM_ClearCounter(FTM_Type *);

//ʹ��FTMx�ж�
uint8 LPLD_FTM_EnableIrq(FTM_InitTypeDef);
//����FTMx�ж�
uint8 LPLD_FTM_DisableIrq(FTM_InitTypeDef);

#endif /* __HW_FTM_H__ */