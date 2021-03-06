#ifndef _EAGLE_OV7725_H
#define _EAGLE_OV7725_H
#include "common.h"

typedef struct
{
	uint8 addr;                 /*�Ĵ�����ַ*/
	uint8 val;                   /*�Ĵ���ֵ*/
} reg_s;

#define ARR_SIZE( a ) ( sizeof( (a) ) / sizeof( ((a)[0]) ) )

#define CAMERA_W 160
#define CAMERA_H 120
#define CAMERA_SIZE (CAMERA_W * CAMERA_H/8)

#define PICTURE_W 160
#define PICTURE_H 40
#define PICTURE_SIZE (PICTURE_W * PICTURE_H / 8)


//����ͼ��ɼ�״̬

#define IMG_NOTINIT 0
#define IMG_FINISH 1
#define IMG_FAIL 2
#define IMG_GATHER 3
#define IMG_START 4
#define IMG_STOP 5

static uint8 ov7725_eagle_reg_init(void);
static void GPIO_ov7725_init(void);
static void DMA_ov7725_init(void);

extern void porta_isr(void);
extern void camera_delay(void);
extern void RazorDMA_Isr(void);
extern void Get_Img(void);
extern uint8 Camera_init(void);

extern uint8 ov7725_eagle_img_flag;
extern uint8 img[CAMERA_H * CAMERA_W];
extern uint8 imgbuff[CAMERA_SIZE];




#endif