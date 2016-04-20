/**
 * @file common.h
 * @version 3.1[By LPLD]
 * @date 2015-01-11
 * @brief ����������Ҫ�õ���ͷ�ļ��Լ���غ궨��
 *
 * ���Ľ���:���鱸�ݺ��޸�
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

#ifndef _COMMON_H_
#define _COMMON_H_

/***********************************************************************/
/*
 * �����������Ͷ���
 */
typedef unsigned char	uint8;  /*  8 bits */
typedef unsigned short int	uint16; /* 16 bits */
typedef unsigned long int	uint32; /* 32 bits */

typedef signed char		int8;   /*  8 bits */
typedef short int	        int16;  /* 16 bits */
typedef int		        int32;  /* 32 bits */

typedef volatile int8		vint8;  /*  8 bits */
typedef volatile int16	vint16; /* 16 bits */
typedef volatile int32	vint32; /* 32 bits */

typedef volatile uint8	vuint8;  /*  8 bits */
typedef volatile uint16	vuint16; /* 16 bits */
typedef volatile uint32	vuint32; /* 32 bits */

typedef float   		float32; /*  32 bits */
typedef double   		float64; /*  64 bits */

typedef unsigned char   boolean;      /* 8-bit*/

/*
 * ��������
 */
#ifdef	FALSE
#undef	FALSE
#endif
#define FALSE	0

#ifdef	TRUE
#undef	TRUE
#endif
#define	TRUE	1

#ifndef NULL
#define NULL    0
#endif

/********************************************************************/

/*
 * RAMFUNC�ؼ��ֶ��壬���ڸ��߱�����������RAM������
 */
#ifndef __IAR_SYSTEMS_ICC__
  #warning OSKineits��֧��IAR������[http://www.lpld.cn]
  #define RAMFUNC
#else
  #define RAMFUNC __ramfunc
#endif

/*
 * ��ӡ������Ϣ����
 */
#define DEBUG_PRINT

/*
 * ʹ�ö����жϲ����Ϸ���
 */
#define DEBUG_ASSERT

/*
 * ��������ƽָ̨����ͷ�ļ�
 * ���ʹ���������¿������趨��LPLD_K60
 * �����ʾ"δ����K60����ƽ̨"�����ڹ���ѡ������Ӷ���
 */
#if (defined(LPLD_K60))
 #include "k60_card.h"
#else
  #error "δ����K60����ƽ̨"
#endif

/*
 * ����CPUָ����ͷ�ļ�
 * CPU�ͺ�Ӧ����"����ƽָ̨����ͷ�ļ�"�ж���
 */
#if (defined(CPU_MK60DZ10))
  #include "MK60DZ10.h"
#elif (defined(CPU_MK60D10))
  #include "MK60D10.h"
#elif (defined(CPU_MK60F12))
  #include "MK60F12.h"
#elif (defined(CPU_MK60F15))
  #include "MK60F15.h"
#endif


/*
 * ����ͨ�ù��ܺ���
 */
#include "assert.h"
#include "io.h"
#include "uif.h"
#include "stdlib.h"
#include "relocate.h"
#include "math.h"
#if (defined(__IAR_SYSTEMS_ICC__))
	#include "intrinsics.h"
#endif

/*
 * ������������K60�̼���ͷ�ļ�
 */
#include "LPLD_Drivers.h"

/*�û�ͷ�ļ�*/

#include "ImgProcess.h"
#include "oled.h"
#include "Eagle_ov7725.h"
#include "Eagle_ov7725_reg.h"
#include "EncoderDriver.h"
#include "SequenceCtrl.h"
#include "MotorDriver.h"
#include "SteerDriver.h"
#include "DebugerDriver.h"
#include "PID.h"
#include "VirtualOsc.h"

/*
 * ����ʵʱϵͳͷ�ļ�
 */
#if (UCOS_II > 0u)
#include  <ucos_ii.h>
#endif

/*
 * �����ļ�ϵͳͷ�ļ�
 */
#if (USE_FATFS > 0u)
#include  <ff.h>
#endif

/***********************************************************************/
/*
 * �ж���غ�������
 */
//ʹ��ȫ���жϺ궨��
#define EnableInterrupts __enable_irq()
//����ȫ���жϺ궨��
#define DisableInterrupts  __disable_irq()
//ʹ��ָ���ж������ŵ��ж�
#define enable_irq(IRQn)    NVIC_EnableIRQ(IRQn)
//����ָ���ж������ŵ��ж�
#define disable_irq(IRQn)    NVIC_DisableIRQ(IRQn)
//�����ж��������ַ��дVTOR�Ĵ���
#define write_vtor(vector_addr) SCB->VTOR = (uint32_t)vector_addr;
/***********************************************************************/

/*
 * �û���ں�������
 */
void main(void);


/********************************************************************/

#endif /* _COMMON_H_ */
