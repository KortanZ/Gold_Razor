/******************************************************************************
 *
 * Freescale Semiconductor Inc.
 * (c) Copyright 2004-2009 Freescale Semiconductor, Inc.
 * ALL RIGHTS RESERVED.
 *
 **************************************************************************//*!
 *
 * @file virtual_com.h
 *
 * @author 
 *
 * @version 
 *
 * @date May-28-2009
 *
 * @brief The file contains Macro's and functions required for Virtual COM  
 *        Loopback Application
 *
 *****************************************************************************/

#ifndef _VIRTUAL_COM_H
#define _VIRTUAL_COM_H

#include "types.h"

/******************************************************************************
 * Constants - None
 *****************************************************************************/

/******************************************************************************
 * Macro's
 *****************************************************************************/
#define  CONTROLLER_ID      (0)   /* ID to identify USB CONTROLLER */ 

#define  KBI_STAT_MASK      (0x0F)

/* 
   DATA_BUFF_SIZE should be greater than or equal to the endpoint buffer size, 
   otherwise there will be data loss. For MC9S08JS16, maximum DATA_BUFF_SIZE 
   supported is 16 Bytes
*/
/*
*   ���ܺͷ������ݻ������ĳ��ȱ�����ڵ���USB�˵�ĳ��ȣ�����ᶪʧ���ݡ�
*   USB_Config.h�����ö˵�ĳ��ȡ�����USB2.0��׼�����ݶ˵㳤�����64�ֽڡ�
*/
#ifndef _MC9S08JS16_H
#define  DATA_BUFF_SIZE     (64)    //define the length of send/receive buffer
#else
#define  DATA_BUFF_SIZE     (16)
#endif

//����USB���սṹ��
typedef struct _USB_REV
{
  uint8_t buffer[DATA_BUFF_SIZE]; //����DATA_BUFF_SIZE�ֽڵĻ�����
  uint8_t len;                    //�������ճ���
}tUSB_Rev;

extern tUSB_Rev tUSB_Rev_Data;    //����ṹ�����

typedef void(*USB_REV_CALLBACK)(void); //��������ջص�����
/*****************************************************************************
 * Global variables
 *****************************************************************************/

/*****************************************************************************
 * Global Functions
 *****************************************************************************/
extern void USB_CDC_Init(void);
extern void USB_CDC_Task(void);
void USB_Rev_SetIsr(USB_REV_CALLBACK );
#endif 
