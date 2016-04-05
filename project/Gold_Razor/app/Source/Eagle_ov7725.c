#include "Eagle_ov7725.h"
#include "Eagle_ov7725_reg.h"
#include "ImgDispose.h"

/*OV7725��ʼ�����ñ�*/
reg_s ov7725_eagle_reg[] =
{
    //�Ĵ������Ĵ���ֵ��
    {OV7725_COM4         , 0xC1},   //PLLʱ������:8xʱ��   AEC����:Full Window
    {OV7725_CLKRC        , 0x00},   //ʹ���ⲿʱ��
    {OV7725_COM2         , 0x03},   //���������������:4x��������
    {OV7725_COM3         , 0xD0},   //7:��ֱ��ת���� 6:ˮƽ���񿪹�
    {OV7725_COM7         , 0x40},   //SCCB : No Change
    {OV7725_HSTART       , 0x3F},
    {OV7725_HSIZE        , 0x50},
    {OV7725_VSTRT        , 0x03},
    {OV7725_VSIZE        , 0x78},
    {OV7725_HREF         , 0x00},
    {OV7725_SCAL0        , 0x0A},
    {OV7725_AWB_Ctrl0    , 0xE0},
    {OV7725_DSPAuto      , 0xff},
    {OV7725_DSP_Ctrl2    , 0x0C},
    {OV7725_DSP_Ctrl3    , 0x00},
    {OV7725_DSP_Ctrl4    , 0x00},

#if (CAMERA_W == 80)
    {OV7725_HOutSize     , 0x14},
#elif (CAMERA_W == 160)
    {OV7725_HOutSize     , 0x28},
#elif (CAMERA_W == 240)
    {OV7725_HOutSize     , 0x3c},
#elif (CAMERA_W == 320)
    {OV7725_HOutSize     , 0x50},
#else

#endif

#if (CAMERA_H == 60 )
    {OV7725_VOutSize     , 0x1E},
#elif (CAMERA_H == 120 )
    {OV7725_VOutSize     , 0x3c},
#elif (CAMERA_H == 180 )
    {OV7725_VOutSize     , 0x5a},
#elif (CAMERA_H == 240 )
    {OV7725_VOutSize     , 0x78},
#else

#endif

    {OV7725_EXHCH        , 0x00},
    {OV7725_GAM1         , 0x0c},
    {OV7725_GAM2         , 0x16},
    {OV7725_GAM3         , 0x2a},
    {OV7725_GAM4         , 0x4e},
    {OV7725_GAM5         , 0x61},
    {OV7725_GAM6         , 0x6f},
    {OV7725_GAM7         , 0x7b},
    {OV7725_GAM8         , 0x86},
    {OV7725_GAM9         , 0x8e},
    {OV7725_GAM10        , 0x97},
    {OV7725_GAM11        , 0xa4},
    {OV7725_GAM12        , 0xaf},
    {OV7725_GAM13        , 0xc5},
    {OV7725_GAM14        , 0xd7},
    {OV7725_GAM15        , 0xe8},
    {OV7725_SLOP         , 0x20},
    {OV7725_LC_RADI      , 0x00},
    {OV7725_LC_COEF      , 0x13},
    {OV7725_LC_XC        , 0x08},
    {OV7725_LC_COEFB     , 0x14},
    {OV7725_LC_COEFR     , 0x17},
    {OV7725_LC_CTR       , 0x05},
    {OV7725_BDBase       , 0x99},
    {OV7725_BDMStep      , 0x03},
    {OV7725_SDE          , 0x04},
    {OV7725_BRIGHT       , 0x00},
    {OV7725_CNST         , 0x3C},
    {OV7725_SIGN         , 0x06},
    {OV7725_UVADJ0       , 0x11},
    {OV7725_UVADJ1       , 0x02},

};
uint8 ov7725_eagle_cfgnum = ARR_SIZE( ov7725_eagle_reg ) ; /*�ṹ�������Ա��Ŀ*/

uint32 Count=0;

GPIO_InitTypeDef pta_init;
GPIO_InitTypeDef ptb_init;
DMA_InitTypeDef dma_init_struct;

static uint8 ov7725_eagle_reg_init(void);
static void GPIO_ov7725_init(void);
static void DMA_ov7725_init(void);
void porta_isr(void);
void delay(void);
void RazorDMA_Isr(void);

uint8 imgbuff[CAMERA_SIZE];
uint8 pic[PICTURE_W * PICTURE_H];
uint8 img[CAMERA_H * CAMERA_W];
uint8 ov7725_eagle_img_flag = IMG_FINISH ;


uint16 temp_i,temp_j=0;

uint8 Camera_init(void)
{
  while(ov7725_eagle_reg_init() == 0);
  delay();

  GPIO_ov7725_init();
  DMA_ov7725_init();


  return 0;
}


uint8 ov7725_eagle_reg_init(void)
{
    uint16 i = 0;
    uint8 Sensor_IDCode = 0;
    LPLD_SCCB_Init();
    delay();

    if(0 == LPLD_SCCB_WriteReg(OV7725_COM7,0x80))
    {
      //printf("\n Error!")
      return 0;
    }

    delay();

    if(0 == LPLD_SCCB_ReadReg(OV7725_VER,&Sensor_IDCode,1))
    {
      //printf("\n Error!")
      return 0;
    }

    if(Sensor_IDCode == OV7725_ID)
    {
      for(i = 0;i < ov7725_eagle_cfgnum;i++)
      {
        if(0 == LPLD_SCCB_WriteReg(ov7725_eagle_reg[i].addr, ov7725_eagle_reg[i].val))
        {
          //printf("\n Error!")
          return 0;
        }
      }
    }
    else
      {
	      return 0;
	  }
    //printf("\n Successfully")
    return 1;
}

static void GPIO_ov7725_init(void)
{

/*------------ov7725����IO��ʼ��(PTB0_PTB7)-------------*/
  ptb_init.GPIO_PTx = PTB;
  ptb_init.GPIO_Dir = DIR_INPUT;
  ptb_init.GPIO_Pins = GPIO_Pin0_7;
  ptb_init.GPIO_PinControl = IRQC_DIS | INPUT_PULL_DIS;
  LPLD_GPIO_Init(ptb_init);
/*------------ov7725���ź�IO��ʼ��(PTA29)---------------*/
  pta_init.GPIO_PTx = PTA;
  pta_init.GPIO_Dir = DIR_INPUT;
  pta_init.GPIO_Pins = GPIO_Pin29;
  pta_init.GPIO_PinControl = IRQC_RI|INPUT_PULL_DOWN|INPUT_PF_EN;
  pta_init.GPIO_Isr = porta_isr;
  LPLD_GPIO_Init(pta_init);
/*------------ov7725_PCLK_IO��ʼ��(PTA27)---------------*/
  pta_init.GPIO_PTx = PTA;
  pta_init.GPIO_Pins = GPIO_Pin27;
  pta_init.GPIO_Dir = DIR_INPUT;
  pta_init.GPIO_PinControl = IRQC_DMAFA | INPUT_PULL_DOWN;
  LPLD_GPIO_Init(pta_init);
}


void DMA_ov7725_init(void)
{
	  //DMA��������
  dma_init_struct.DMA_CHx = DMA_CH0;    //CH0ͨ��
  dma_init_struct.DMA_Req = PORTA_DMAREQ;       //PORTAΪ����Դ
  dma_init_struct.DMA_MajorLoopCnt = CAMERA_SIZE; //��ѭ������ֵ
  dma_init_struct.DMA_MinorByteCnt = 1; //��ѭ���ֽڼ�����ÿ�ζ���1�ֽ�
  dma_init_struct.DMA_SourceAddr = (uint32)&PTB->PDIR;        //Դ��ַ��PTD8~15
  dma_init_struct.DMA_DestAddr = (uint32)imgbuff;      //Ŀ�ĵ�ַ�����ͼ�������
  dma_init_struct.DMA_DestAddrOffset = 1;       //Ŀ�ĵ�ַƫ�ƣ�ÿ�ζ�������1
  dma_init_struct.DMA_AutoDisableReq = TRUE;    //�Զ���������
  dma_init_struct.DMA_MajorCompleteIntEnable = TRUE;
  dma_init_struct.DMA_Isr = RazorDMA_Isr;
  //��ʼ��DMA
  LPLD_DMA_Init(dma_init_struct);
  DMA0->INT |= 0x1u<<0;
  LPLD_DMA_EnableIrq(dma_init_struct);
}
void sendCamImgToCamViewer(void)
{
	  uint8 i,j;
      uint16 offset;
	  LPLD_UART_PutChar(UART2,0xFF);
	  LPLD_UART_PutChar(UART2,0xFE);
	  LPLD_UART_PutChar(UART2,0xFF);
	  LPLD_UART_PutChar(UART2,0xFE);

	  for(i = 0;i < CAMERA_H;i++)
	  	{
	  		offset = i * CAMERA_W;
			for(j = 0;j < CAMERA_H;j++)
				{
					uint8 d = imgbuff[offset + j];
					if(d > 0xFD) d = 0xFD;
					LPLD_UART_PutChar(UART2,d);
				}
	        LPLD_UART_PutChar(UART2,0xFF);
	        LPLD_UART_PutChar(UART2,0xFE);
	  	}
	  j = 0;

}
void vcan_sendimg(void *imgaddr, uint32_t imgsize)
{
#define CMD_IMG     1
    int8 cmdf[2] = {CMD_IMG, ~CMD_IMG};    //ɽ����λ�� ʹ�õ�����
    int8 cmdr[2] = {~CMD_IMG, CMD_IMG};    //ɽ����λ�� ʹ�õ�����

    LPLD_UART_PutCharArr(UART2, cmdf, sizeof(cmdf));    //�ȷ�������

    LPLD_UART_PutCharArr(UART2, (int8 *)imgaddr, imgsize); //�ٷ���ͼ��

    LPLD_UART_PutCharArr(UART2, cmdr, sizeof(cmdr));    //�ȷ�������
}
void img_extract(void *dst, void *src, uint32 srclen)
{
    uint8 colour[2] = {255, 0}; //0 �� 1 �ֱ��Ӧ����ɫ
    uint8 * mdst = dst;
    uint8 * msrc = src;
    //ע��ɽ�������ͷ 0 ��ʾ ��ɫ��1��ʾ ��ɫ
    uint8 tmpsrc;
    while(srclen --)
    {
        tmpsrc = *msrc++;
        *mdst++ = colour[ (tmpsrc >> 7 ) & 0x01 ];
        *mdst++ = colour[ (tmpsrc >> 6 ) & 0x01 ];
        *mdst++ = colour[ (tmpsrc >> 5 ) & 0x01 ];
        *mdst++ = colour[ (tmpsrc >> 4 ) & 0x01 ];
        *mdst++ = colour[ (tmpsrc >> 3 ) & 0x01 ];
        *mdst++ = colour[ (tmpsrc >> 2 ) & 0x01 ];
        *mdst++ = colour[ (tmpsrc >> 1 ) & 0x01 ];
        *mdst++ = colour[ (tmpsrc >> 0 ) & 0x01 ];
    }
}


void porta_isr(void)
{
	if(LPLD_GPIO_IsPinxExt(PORTA,GPIO_Pin29))
	{
		//���ж���Ҫ�ж��ǳ��������ǳ���ʼ
		if(ov7725_eagle_img_flag == IMG_START)                   //��Ҫ��ʼ�ɼ�ͼ��
		{
			ov7725_eagle_img_flag = IMG_GATHER;                  //���ͼ��ɼ���
			disable_irq(PORTA_IRQn);
			PORTA->ISFR = 1 << 27;            //���PCLK��־λ
			DMA0->ERQ |= DMA_ERQ_ERQ0_MASK << 0;
			PORTA->ISFR = 1 << 27;            //���PCLK��־λ
			DMA0->TCD[0].DADDR = DMA_DADDR_DADDR(imgbuff);
		}
		else
		{
			disable_irq(PORTA_IRQn);
			ov7725_eagle_img_flag = IMG_FAIL;
		}
	}
}

void RazorDMA_Isr(void)
{
    ov7725_eagle_img_flag = IMG_FINISH ;
      /*for(temp_i=1;temp_i<120;temp_i+=3)
      {
  	img_extract(&(img[160*temp_j]),&(imgbuff[160*temp_i]),CAMERA_SIZE);
	temp_j++;
       }*/
    //Get_MidLine();
    //vcan_sendimg(imgbuff, CAMERA_SIZE);                  //���͵���λ��
    DMA0->INT |= 0x1u<<0;
}

void delay(void)
{
  uint16 i, n;
  for(i=0;i<30000;i++)
  {
    for(n=0;n<200;n++)
    {
      asm("nop");
    }
  }
}