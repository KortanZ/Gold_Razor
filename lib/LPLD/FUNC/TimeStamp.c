/**
 * @file TimeStamp.c
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
#include "common.h"
#include "TimeStamp.h"
//����ÿ����������
const uint8 month_table[12]={31,28,31,30,31,30,31,31,30,31,30,31};
//�������ڲ�������
const uint8 week_table[12]={0,3,3,6,1,4,6,2,5,0,3,5}; 

const uint8 month_list[12][3]={"Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec"};

/*
 * LPLD_DateTimeToTimeStamp
 * ��ʱ��ṹ��ת��Ϊ��
 * ��IBMʱ���׼Ϊ����
 * 
 * ����:
 *    TimeStamp_FormatTypeDef* realtime_init_struct
 *                        ���嶨���TimeStamp_FormatTypeDef
 *
 * ���:
 *    ����ֵΪ�룬������ΪRTC���������ֵ
 *    �������ʾ����
 *
 */
uint32 LPLD_DateTimeToTimeStamp(TimeStamp_FormatTypeDef *realtime_init_struct)
{
  uint16 i; 
  uint32 current_second = 0;
  uint16 current_year = realtime_init_struct->year;
  uint8 current_month = realtime_init_struct->month;
  uint8 current_day = realtime_init_struct->day;
  uint8 current_hour = realtime_init_struct->hour;
  uint8 current_minute = realtime_init_struct->minute;
  //�ж�ʱ������ն��Ƿ�Խ��
  if(current_year < IBM_YEAR_START || current_year > IBM_YEAR_END)
  {
    return 0;
  }
  //����ת��Ϊ��
  for (i = IBM_YEAR_START; i < current_year; i++)
  {
    if(IS_LEAPYEAR(i))
    {
        current_second += LEAPYEAR_CONVERTTO_SECONEDS;
    }
    else
    {
        current_second += AVERAGEYEAR_CONVERTTO_SECONEDS;
    }
  }
  //����ת��Ϊ��
  for ( i = 0; i < (current_month - 1); i++)
  {
    current_second += (uint32)month_table[i] * DAY_CONVERTTO_SECONEDS;
    if(IS_LEAPYEAR(current_year) && i == FEBRUARY)
    {
        current_second += DAY_CONVERTTO_SECONEDS;
    }
  }
  //���죬Сʱ����ת��Ϊ��
  current_second += (uint32)(current_day - 1) * DAY_CONVERTTO_SECONEDS;
  current_second += (uint32)current_hour * HOUR_CONVERTTO_SECONEDS;
  current_second += (uint32)current_minute * MINUTE_CONVERTTO_SECONEDS;
  current_second += realtime_init_struct->second;   
  return current_second;   
}
/*
 * LPLD_TimeStampToDateTime
 * ����ת��Ϊʱ��ṹ��
 * ��IBMʱ���׼Ϊ����
 * 
 * ����:
 *    uint32 -- rtc_second  RTC���������ֵ
 *    TimeStamp_FormatTypeDef* realtime_init_struct
 *                        ���嶨���TimeStamp_FormatTypeDef
 *
 * ���:
 *    ����ֵΪ�룬������ΪRTC���������ֵ
 *    ����1��ʾ��ȷ
 *
 */
uint8 LPLD_TimeStampToDateTime(uint32 rtc_second, TimeStamp_FormatTypeDef *realtime_init_struct)
{
  static uint32 day_counter = 0;
  uint32 days = 0;
  uint32 i = 0;
  days = rtc_second / DAY_CONVERTTO_SECONEDS;//second to days
  if(day_counter != days)
  {
    day_counter = days;
    i = IBM_YEAR_START;
    //days to years
    while(days >= AVERAGEYEAR_DAYS)
    {
      if(IS_LEAPYEAR(i)) 
      {
        if(days >= LEAPYEAR_DAYS)
        {
            days-= LEAPYEAR_DAYS;
        }   
        else 
        {
            i++;
            break;
        }   
      }
      else 
      {
         days -= AVERAGEYEAR_DAYS; 
      }
      i++;  
    }
    realtime_init_struct->year = i;
    i = 0;
    //days to month
    while(days >= AVERAGEYEAR_FEBRUARY_DAYS )
    {
      if(IS_LEAPYEAR(realtime_init_struct->year) && i == FEBRUARY )
      {
        if(days >= LEAPYEAR_FEBRUARY_DAYS) 
        {
          days -= LEAPYEAR_FEBRUARY_DAYS;
        }
        else break; 
      }
      else 
      {
        if(days >= month_table[i]) 
        {
          days -= month_table[i];
        }
        else break;
      }
      i++;  
    }
    realtime_init_struct->month = i+1;
    realtime_init_struct->day = days+1;
  }
  i = rtc_second % DAY_CONVERTTO_SECONEDS;     
  realtime_init_struct->week = LPLD_GetWeek(realtime_init_struct);         
  realtime_init_struct->hour = i / HOUR_CONVERTTO_SECONEDS;        //hours
  realtime_init_struct->minute = (i % HOUR_CONVERTTO_SECONEDS) / MINUTE_CONVERTTO_SECONEDS; //minutes  
  realtime_init_struct->second = (i % HOUR_CONVERTTO_SECONEDS) % MINUTE_CONVERTTO_SECONEDS; //seconds
  return 1;
}
/*
 * LPLD_GetWeek
 * ��ʱ��ṹ��������
 * 
 * ����:
 *    TimeStamp_FormatTypeDef* realtime_init_struct
 *                        ���嶨���TimeStamp_FormatTypeDef
 *
 * ���:
 *    ����ֵΪ����
 *
 */
uint8 LPLD_GetWeek(TimeStamp_FormatTypeDef *realtime_init_struct)
{   
  uint16 i;
  uint8 yh,yl,day,month;
  i = realtime_init_struct->year;
  day = realtime_init_struct->day;
  month = realtime_init_struct->month;
  yh = i / 100;
  yl = i % 100;
  if(yh >= 20 && yh <21)
  {
    yl +=100;
  }
  i = (yl + yl/4)%7 + day + week_table[month - 1];
  if(!(yl % 4) && month < 3)
  {
    i--;
  }
  return (i % 7);
} 

/*
 * LPLD_AutoInitTimeStamp
 * ���ݱ�����ʱ���Զ���ʼ��TimeStamp_FormatTypeDef�ṹ��
 * 
 * ����:
 *    TimeStamp_FormatTypeDef* realtime_init_struct
 *                        ���嶨���TimeStamp_FormatTypeDef
 *
 * ���:
 */
void LPLD_AutoInitTimeStamp(TimeStamp_FormatTypeDef *realtime_init_struct)
{
  int i;
  for(i = 0;i < 12;i++)
  {
    if(strncmp((char*)month_list[i],__DATE__,3)==0)
    {
      realtime_init_struct->month = i + 1;
      break;
    }
  }
  realtime_init_struct->year = GET_COMPILE_YEAR;
  realtime_init_struct->day = GET_COMPILE_DAY;
  realtime_init_struct->week = 0;
  realtime_init_struct->hour = GET_COMPILE_HOUR;
  realtime_init_struct->minute = GET_COMPILE_MINUTE;
  realtime_init_struct->second = GET_COMPILE_SECOND;
}

