/**
 * @file HW_SYSTICK.h
 * @version 3.02[By LPLD]
 * @date 2013-11-29
 * @brief SYSTICK�ײ�ģ����غ���
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
#ifndef __HW_SYSTICK_H__
#define __HW_SYSTICK_H__
/* ----------------------------------------------------------------------------
   -- SYSTICK Access Layer
   ---------------------------------------------------------------------------- */

/**
 * @addtogroup SYSTICK_Access_Layer SYSTICK Access Layer
 * @{
 */

/** SYSTICK - Register Layout Typedef */
typedef struct {
  __IO uint32_t CSR;     /**< Systemtick Control and Status Register , offset: 0x0 */
  __IO uint32_t RVR;     /**< Systemtick Reload Value High, offset: 0x4 */
  __IO uint32_t CVR;     /**< Systemtick Current Value Register , offset: 0x8 */
  __IO uint32_t CALIB;   /**< Systemtick Calibration Value Register , offset: 0xC */
}SYSTICK_Type;

/* ----------------------------------------------------------------------------
   -- SYSTICK Register Masks
   ---------------------------------------------------------------------------- */

/**
 * @addtogroup SYSTICK_Register_Masks SYSTICK Register Masks
 * @{
 */
/* CSR Bit Fields */
#define SYSTICK_CSR_ENABLE_MASK                  0x1u
#define SYSTICK_CSR_ENABLE_SHIFT                 0
#define SYSTICK_CSR_TICKINT_MASK                 0x2u
#define SYSTICK_CSR_TICKINT_SHIFT                1
#define SYSTICK_CSR_CLKSOURCE_MASK               0x4u
#define SYSTICK_CSR_CLKSOURCE_SHIFT              2
#define SYSTICK_CSR_COUNTFLAG_MASK               0x10000u
#define SYSTICK_CSR_COUNTFLAG_SHIFT              16
/* RVR Bit Fields */
#define SYSTICK_RVR_RELOAD_MASK                  0xFFFFFFu
#define SYSTICK_RVR_RELOAD_SHIFT                 0
#define SYSTICK_RVR_RELOAD(x)                    (((uint32_t)(((uint32_t)(x))<<SYSTICK_RVR_RELOAD_SHIFT))&SYSTICK_RVR_RELOAD_MASK)
/* CVR Bit Fields */
#define SYSTICK_CVR_CURRENT_MASK                 0xFFFFFFu
#define SYSTICK_CVR_CURRENT_SHIFT                0
#define SYSTICK_CVR_CURRENT(x)                   (((uint32_t)(((uint32_t)(x))<<SYSTICK_CVR_CURRENT_SHIFT))&SYSTICK_CVR_CURRENT_MASK)
/* CALIB Bit Fields */
#define SYSTICK_CALIB_TENMS_MASK                 0xFFFFFFu
#define SYSTICK_CALIB_TENMS_SHIFT                0
#define SYSTICK_CALIB_TENMS(x)                   (((uint32_t)(((uint32_t)(x))<<SYSTICK_CALIB_TENMS_SHIFT))&SYSTICK_CALIB_TENMS_MASK)
#define SYSTICK_CALIB_SKEW_MASK                  0x40000000u
#define SYSTICK_CALIB_SKEW_SHIFT                 30
#define SYSTICK_CALIB_NOREF_MASK                 0x80000000u
#define SYSTICK_CALIB_NOREF_SHIFT                31
/**
 * @}
 */ /* end of group SYSTICK_Register_Masks */

/* SYSTICK - instance base addresses */
/** Peripheral SYSTICK base address */
#define SYSTICK_BASE (0xE000E010u)
/** Peripheral SYSTICK base pointer */
#define SYSTICK  ((SYSTICK_Type *)SYSTICK_BASE)

/**
 * @}
 */ /* end of group SYSTICK_Access_Layer */
typedef void (*SYSTICK_ISR_CALLBACK)(void);

#define SYSTICK_COUNTER_MAX (0xFFFFFF)
#define SYSTICK_UINT_US(x)  (x/1000000)
#define SYSTICK_UINT_MS(x)  (x/1000)
#define LPLD_SYSTICK_ISDONE ( SYSTICK->CSR & SYSTICK_CSR_COUNTFLAG_MASK )

typedef struct {
  /*
    ������
      SYSTICKģ������ڣ���λus
    ȡֵ��
      1~0xFFFFFFFF
    ��ʼ����
      �������ʼ����SYSTICK_PeriodUs��SYSTICK_PeriodMs��SYSTICK_PeriodS����һ����ʼ��
  */
  uint32 SYSTICK_PeriodUs;
  
  /*
    ������
      SYSTICKģ������ڣ���λms
    ȡֵ��
      1~0xFFFFFFFF
    ��ʼ����
      �������ʼ����SYSTICK_PeriodUs��SYSTICK_PeriodMs��SYSTICK_PeriodS����һ����ʼ��
  */
  uint32 SYSTICK_PeriodMs;

  /*
    ������
      SYSTICK�жϻص�����
    ȡֵ��
      ��������Ϊ�޷���ֵ,�޲���(eg. void isr(void);)
    ��ʼ����
      �������ʼ������δ��ʼ���򲻻ᴥ���ж�
  */
  SYSTICK_ISR_CALLBACK SYSTICK_Isr; 
	
}SYSTICK_InitType;

//SYSTICK��ʼ������
void LPLD_SYSTICK_Init(SYSTICK_InitType );
//SYSTICK����ʼ������
void LPLD_SYSTICK_DeInit(void);
//SYSTICK��ʱUS����
void LPLD_SYSTICK_DelayUs(uint32 );
//SYSTICK��ʱMS����
void LPLD_SYSTICK_DelayMs(uint32 );
#endif