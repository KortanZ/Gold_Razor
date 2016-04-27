#include "common.h"

/*OV7725³õÊ¼»¯ÅäÖÃ±í*/
reg_s ov7725_eagle_reg[] =
{
    //¼Ä´æÆ÷£¬¼Ä´æÆ÷Öµ´Î
    { OV7725_COM4, 0xC1 },   //PLLÊ±ÖÓÉèÖÃ:8xÊ±ÖÓ   AECÉèÖÃ:Full Window
    { OV7725_CLKRC, 0x00 },   //Ê¹ÓÃÍâ²¿Ê±ÖÓ
    { OV7725_COM2, 0x03 },   //ÅäÖÃÊä³öÇý¶¯ÄÜÁ¦:4xÇý¶¯ÄÜÁ¦
    { OV7725_COM3, 0xD0 },   //7:´¹Ö±·­×ª¿ª¹Ø 6:Ë®Æ½¾µÏñ¿ª¹Ø
    { OV7725_COM7, 0x40 },   //SCCB : No Change
    { OV7725_HSTART, 0x3F },
    { OV7725_HSIZE, 0x50 },
    { OV7725_VSTRT, 0x03 },
    { OV7725_VSIZE, 0x78 },
    { OV7725_HREF, 0x00 },
    { OV7725_SCAL0, 0x0A },
    { OV7725_AWB_Ctrl0, 0xE0 },
    { OV7725_DSPAuto, 0xff },
    { OV7725_DSP_Ctrl2, 0x0C },
    { OV7725_DSP_Ctrl3, 0x00 },
    { OV7725_DSP_Ctrl4, 0x00 },

#if (CAMERA_W == 80)
    { OV7725_HOutSize, 0x14 },
#elif (CAMERA_W == 160)
    { OV7725_HOutSize, 0x28 },
#elif (CAMERA_W == 240)
    { OV7725_HOutSize, 0x3c },
#elif (CAMERA_W == 320)
    { OV7725_HOutSize, 0x50 },
#else

#endif

#if (CAMERA_H == 60 )
    { OV7725_VOutSize, 0x1E },
#elif (CAMERA_H == 120 )
    { OV7725_VOutSize, 0x3c },
#elif (CAMERA_H == 180 )
    { OV7725_VOutSize, 0x5a },
#elif (CAMERA_H == 240 )
    { OV7725_VOutSize, 0x78 },
#else

#endif

    { OV7725_EXHCH, 0x00 },
    { OV7725_GAM1, 0x0c },
    { OV7725_GAM2, 0x16 },
    { OV7725_GAM3, 0x2a },
    { OV7725_GAM4, 0x4e },
    { OV7725_GAM5, 0x61 },
    { OV7725_GAM6, 0x6f },
    { OV7725_GAM7, 0x7b },
    { OV7725_GAM8, 0x86 },
    { OV7725_GAM9, 0x8e },
    { OV7725_GAM10, 0x97 },
    { OV7725_GAM11, 0xa4 },
    { OV7725_GAM12, 0xaf },
    { OV7725_GAM13, 0xc5 },
    { OV7725_GAM14, 0xd7 },
    { OV7725_GAM15, 0xe8 },
    { OV7725_SLOP, 0x20 },
    { OV7725_LC_RADI, 0x00 },
    { OV7725_LC_COEF, 0x13 },
    { OV7725_LC_XC, 0x08 },
    { OV7725_LC_COEFB, 0x14 },
    { OV7725_LC_COEFR, 0x17 },
    { OV7725_LC_CTR, 0x05 },
    { OV7725_BDBase, 0x99 },
    { OV7725_BDMStep, 0x03 },
    { OV7725_SDE, 0x04 },
    { OV7725_BRIGHT, 0x00 },
    { OV7725_CNST, 0x3C },
    { OV7725_SIGN, 0x06 },
    { OV7725_UVADJ0, 0x11 },
    { OV7725_UVADJ1, 0x02 },

};


uint8 ov7725_eagle_cfgnum = ARR_SIZE(ov7725_eagle_reg); /*½á¹¹ÌåÊý×é³ÉÔ±ÊýÄ¿*/


uint8 imgbuff[CAMERA_SIZE];
uint8 img[CAMERA_H * CAMERA_W];
uint8 ov7725_eagle_img_flag = IMG_FINISH;

uint8 Camera_init(void)
{
    while (ov7725_eagle_reg_init() == 0);
    camera_delay();

	GPIO_ov7725_init();
	DMA_ov7725_init();


    return 0;
}


uint8 ov7725_eagle_reg_init(void)
{
    uint16 i = 0;
    uint8 Sensor_IDCode = 0;
    LPLD_SCCB_Init();
    camera_delay();

    if (0 == LPLD_SCCB_WriteReg(OV7725_COM7, 0x80))
    {
        //printf("\n Error!")
        return 0;
    }

    camera_delay();

    if (0 == LPLD_SCCB_ReadReg(OV7725_VER, &Sensor_IDCode, 1))
    {
        //printf("\n Error!")
        return 0;
    }

    if (Sensor_IDCode == OV7725_ID)
    {
        for (i = 0; i < ov7725_eagle_cfgnum; i++)
        {
            if (0 == LPLD_SCCB_WriteReg(ov7725_eagle_reg[i].addr, ov7725_eagle_reg[i].val))
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
    
    GPIO_InitTypeDef ov7725_gpio_init;
    /*------------ov7725Êý¾ÝIO³õÊ¼»¯(PTB0_PTB7)-------------*/
    ov7725_gpio_init.GPIO_PTx = PTB;
    ov7725_gpio_init.GPIO_Dir = DIR_INPUT;
    ov7725_gpio_init.GPIO_Pins = GPIO_Pin0_7;
	ov7725_gpio_init.GPIO_Output = OUTPUT_L;
    ov7725_gpio_init.GPIO_PinControl = IRQC_DIS | INPUT_PULL_DIS;
    LPLD_GPIO_Init(ov7725_gpio_init);
    /*------------ov7725³¡ÐÅºÅIO³õÊ¼»¯(PTA29)---------------*/
    ov7725_gpio_init.GPIO_PTx = PTA;
    ov7725_gpio_init.GPIO_Dir = DIR_INPUT;
    ov7725_gpio_init.GPIO_Pins = GPIO_Pin29;
    ov7725_gpio_init.GPIO_PinControl = IRQC_RI | INPUT_PULL_DOWN | INPUT_PF_EN;
    ov7725_gpio_init.GPIO_Isr = porta_isr;
    LPLD_GPIO_Init(ov7725_gpio_init);
    /*------------ov7725_PCLK_IO³õÊ¼»¯(PTA27)---------------*/
    ov7725_gpio_init.GPIO_PTx = PTA;
    ov7725_gpio_init.GPIO_Pins = GPIO_Pin27;
    ov7725_gpio_init.GPIO_Dir = DIR_INPUT;
    ov7725_gpio_init.GPIO_PinControl = IRQC_DMAFA | INPUT_PULL_DOWN;
    LPLD_GPIO_Init(ov7725_gpio_init);
}


void DMA_ov7725_init(void)
{

    DMA_InitTypeDef dma_init_struct;
    //DMA²ÎÊýÅäÖÃ
    dma_init_struct.DMA_CHx = DMA_CH0;    //CH0Í¨µÀ
    dma_init_struct.DMA_Req = PORTA_DMAREQ;       //PORTAÎªÇëÇóÔ´
    dma_init_struct.DMA_PeriodicTriggerEnable = FALSE;
    dma_init_struct.DMA_MajorLoopCnt = CAMERA_SIZE; //Ö÷Ñ­»·¼ÆÊýÖµ
    dma_init_struct.DMA_MinorByteCnt = 1; //´ÎÑ­»·×Ö½Ú¼ÆÊý£ºÃ¿´Î¶ÁÈë1×Ö½Ú
    dma_init_struct.DMA_SourceDataSize = DMA_SRC_8BIT;
    dma_init_struct.DMA_SourceAddr = (uint32)&PTB->PDIR;        //Ô´µØÖ·£ºPTD8~15
    dma_init_struct.DMA_SourceAddrOffset = 0;
    dma_init_struct.DMA_LastSourceAddrAdj = 0;
    dma_init_struct.DMA_DestAddr = (uint32)imgbuff;      //Ä¿µÄµØÖ·£º´æ·ÅÍ¼ÏñµÄÊý×é
    dma_init_struct.DMA_DestDataSize = DMA_DST_8BIT;
    dma_init_struct.DMA_DestAddrOffset = 1;       //Ä¿µÄµØÖ·Æ«ÒÆ£ºÃ¿´Î¶ÁÈëÔö¼Ó1
    dma_init_struct.DMA_LastDestAddrAdj = 0;
    dma_init_struct.DMA_AutoDisableReq = TRUE;    //×Ô¶¯½ûÓÃÇëÇó
    dma_init_struct.DMA_MajorCompleteIntEnable = TRUE;
    dma_init_struct.DMA_MajorHalfCompleteIntEnable = FALSE;
    dma_init_struct.DMA_Isr = RazorDMA_Isr;
    //³õÊ¼»¯DMA
    LPLD_DMA_Init(dma_init_struct);
    DMA0->INT |= 0x1u << 0;
    LPLD_DMA_EnableIrq(dma_init_struct);
}


void vcan_sendimg(void *imgaddr, uint32_t imgsize)
{
#define CMD_IMG     1
    int8 cmdf[2] = { CMD_IMG, ~CMD_IMG };    //É½ÍâÉÏÎ»»ú Ê¹ÓÃµÄÃüÁî
    int8 cmdr[2] = { ~CMD_IMG, CMD_IMG };    //É½ÍâÉÏÎ»»ú Ê¹ÓÃµÄÃüÁî

    LPLD_UART_PutCharArr(UART2, cmdf, sizeof(cmdf));    //ÏÈ·¢ËÍÃüÁî

    LPLD_UART_PutCharArr(UART2, (int8 *)imgaddr, imgsize); //ÔÙ·¢ËÍÍ¼Ïñ

    LPLD_UART_PutCharArr(UART2, cmdr, sizeof(cmdr));    //ÏÈ·¢ËÍÃüÁî
}
void img_extract(void *dst, void *src, uint32 srclen)
{
    uint8 colour[2] = { 255, 0 }; //0 ºÍ 1 ·Ö±ð¶ÔÓ¦µÄÑÕÉ«
    uint8 * mdst = dst;
    uint8 * msrc = src;
    //×¢£ºÉ½ÍâµÄÉãÏñÍ· 0 ±íÊ¾ °×É«£¬1±íÊ¾ ºÚÉ«
    uint8 tmpsrc;
    while (srclen--)
    {
        tmpsrc = *msrc++;
        *mdst++ = colour[(tmpsrc >> 7) & 0x01];
        *mdst++ = colour[(tmpsrc >> 6) & 0x01];
        *mdst++ = colour[(tmpsrc >> 5) & 0x01];
        *mdst++ = colour[(tmpsrc >> 4) & 0x01];
        *mdst++ = colour[(tmpsrc >> 3) & 0x01];
        *mdst++ = colour[(tmpsrc >> 2) & 0x01];
        *mdst++ = colour[(tmpsrc >> 1) & 0x01];
        *mdst++ = colour[(tmpsrc >> 0) & 0x01];
    }
}


void porta_isr(void)
{
    if (LPLD_GPIO_IsPinxExt(PORTA, GPIO_Pin29))
    {
        //³¡ÖÐ¶ÏÐèÒªÅÐ¶ÏÊÇ³¡½áÊø»¹ÊÇ³¡¿ªÊ¼
        if (ov7725_eagle_img_flag == IMG_START)                   //ÐèÒª¿ªÊ¼²É¼¯Í¼Ïñ
        {
            ov7725_eagle_img_flag = IMG_GATHER;                  //±ê¼ÇÍ¼Ïñ²É¼¯ÖÐ
            disable_irq(PORTA_IRQn);
            PORTA->ISFR = 1 << 27;            //Çå¿ÕPCLK±êÖ¾Î»
            DMA0->ERQ |= DMA_ERQ_ERQ0_MASK << 0;
            PORTA->ISFR = 1 << 27;            //Çå¿ÕPCLK±êÖ¾Î»
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
    ov7725_eagle_img_flag = IMG_FINISH;

    img_extract(img, imgbuff, CAMERA_SIZE);
    Track_Test(Img_Track(Img_Edge(img), img), img);
    //vcan_sendimg(imgbuff, CAMERA_SIZE);
    vcan_sendimg(img, CAMERA_W * CAMERA_H);                  //·¢ËÍµ½ÉÏÎ»»ú
    DMA0->INT |= 0x1u << 0;
}

void camera_delay(void)
{
    uint16 i, n;
    for (i = 0; i<30000; i++)
    {
        for (n = 0; n<200; n++)
        {
            asm("nop");
        }
    }
}

void Get_Img(void)
{
    ov7725_eagle_img_flag = IMG_START;                   //¿ªÊ¼²É¼¯Í¼Ïñ
    PORTA->ISFR = ~0;
    enable_irq((IRQn_Type)(PORTA_IRQn));
    while (ov7725_eagle_img_flag != IMG_FINISH)
    {
        if (ov7725_eagle_img_flag == IMG_FAIL)            //¼ÙÈçÍ¼Ïñ²É¼¯´íÎó£¬ÔòÖØÐÂ¿ªÊ¼²É¼¯
        {
            ov7725_eagle_img_flag = IMG_START;           //¿ªÊ¼²É¼¯Í¼Ïñ
            PORTA->ISFR = 0xFFFFFFFFu;                //Ð´1ÇåÖÐ¶Ï±êÖ¾Î»(±ØÐëµÄ£¬²»È»»Øµ¼ÖÂÒ»¿ªÖÐ¶Ï¾ÍÂíÉÏ´¥·¢ÖÐ¶Ï)
            enable_irq(PORTA_IRQn);                 //ÔÊÐíPTAµÄÖÐ¶Ï
        }
    }
}
