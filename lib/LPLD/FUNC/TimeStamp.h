/**
 * @file TIMESTAMP.h
 * @version 3.01[By LPLD]
 * @date 2013-10-29
 * @brief TIMESTAMPʱ������ܶ���
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
#ifndef __HW_TIMESTAMP_H__
#define __HW_TIMESTAMP_H__

//����ʱ��궨��
#define IBM_YEAR_START (1970)
#define IBM_YEAR_END   (2099)
#define LEAPYEAR_CONVERTTO_SECONEDS    (31622400)
#define AVERAGEYEAR_CONVERTTO_SECONEDS (31536000)
#define DAY_CONVERTTO_SECONEDS         (86400)
#define HOUR_CONVERTTO_SECONEDS        (3600)
#define MINUTE_CONVERTTO_SECONEDS      (60)
#define LEAPYEAR_DAYS      (366)
#define AVERAGEYEAR_DAYS   (365)
#define LEAPYEAR_FEBRUARY_DAYS      (29)
#define AVERAGEYEAR_FEBRUARY_DAYS   (28)
//�ж�ƽ�������궨��
#define IS_LEAPYEAR(YEAR) (YEAR % 4 ? FALSE : YEAR % 100 ? TRUE : YEAR % 400 ? FALSE : TRUE )
//��ñ�����ʱ��
#define GET_COMPILE_YEAR  ((__DATE__[7] - '0')*1000+\
                          (__DATE__[8] - '0')*100+\
                          (__DATE__[9] - '0')*10+\
                          (__DATE__[10] - '0'))
#define GET_COMPILE_DAY  ((__DATE__[4]==0x20?0:(__DATE__[4] - '0')*10) + (__DATE__[5] - '0'))
#define GET_COMPILE_HOUR ((__TIME__[0] - '0')*10 + (__TIME__[1] - '0'))
#define GET_COMPILE_MINUTE ((__TIME__[3] - '0')*10 + (__TIME__[4] - '0'))
#define GET_COMPILE_SECOND ((__TIME__[6] - '0')*10 + (__TIME__[7] - '0'))
//ö���·�
typedef enum 
{  
  JANUARY,
  FEBRUARY,
  MARCH,
  APRIL,
  MAY,
  JUNE,
  JULY,
  AUGUST,
  SEPTEMBER,
  OCTOBER,
  NOVOMBER,
  DECEMBER
}Month_TypeEnum;
//ʱ��ṹ��
typedef struct 
{
  uint8 hour;
  uint8 minute;
  uint8 second;         
  uint8 week; 
  uint8 day;
  uint8 month; 
  uint16 year;     
}TimeStamp_FormatTypeDef;
//��ʱ��ṹ��ת��Ϊ��
uint32 LPLD_DateTimeToTimeStamp(TimeStamp_FormatTypeDef*);
//����ת��Ϊʱ��ṹ��
uint8 LPLD_TimeStampToDateTime(uint32 ,TimeStamp_FormatTypeDef*);
//��������ṹ��
uint8 LPLD_GetWeek(TimeStamp_FormatTypeDef*);
//���ݱ�����ʱ�ӳ�ʼ��TimeStamp_FormatTypeDef�ṹ��
void LPLD_AutoInitTimeStamp(TimeStamp_FormatTypeDef *);
#endif