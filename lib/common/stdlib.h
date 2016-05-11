/**
 * @file stdlib.h
 * @version 3.01[By LPLD]
 * @date 2013-11-4
 * @brief C��׼�����
 *
 * ���Ľ���:�������޸�
 *
 * �ɱ�׼C�������ֲ����֧��ASCII
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

#ifndef _STDLIB_H
#define _STDLIB_H

#include "common.h"
/********************************************************************
 * Standard library functions
 ********************************************************************/

int isspace (int);

int isalnum (int);

int isdigit (int);

int isupper (int);

int strcasecmp (const int8 *, const int8 *);

int strncasecmp (const int8 *, const int8 *, int);

unsigned long strtoul (int8 *, int8 **, int);

int strlen (const int8 *);

int8 * strcat (int8 *, const int8 *);

int8 * strncat (int8 *, const int8 *, int);

int8 * strcpy (int8 *, const int8 *);

int8 * strncpy (int8 *, const int8 *, int);

int strcmp (const int8 *, const int8 *);

int strncmp (const int8 *, const int8 *, int);

void * memcpy (void *, const void *, unsigned);

void * memset (void *, int, unsigned);

void free (void *);
 
void * malloc (unsigned);

/********************************************************************/

#endif
