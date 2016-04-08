#include "common.h"

/*OV7725初始化配置表*/
reg_s ov7725_eagle_reg[] =
{
    //寄存器，寄存器值次
    { OV7725_COM4, 0xC1 },   //PLL时钟设置:8x时钟   AEC设置:Full Window
    { OV7725_CLKRC, 0x00 },   //使用外部时钟
    { OV7725_COM2, 0x03 },   //配置输出驱动能力:4x驱动能力
    { OV7725_COM3, 0xD0 },   //7:垂直翻转开关 6:水平镜像开关
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


uint8 ov7725_eagle_cfgnum = ARR_SIZE(ov7725_eagle_reg); /*结构体数组成员数目*/


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
    
    GPIO_InitTypeDef pt_init;
    /*------------ov7725数据IO初始化(PTB0_PTB7)-------------*/
    pt_init.GPIO_PTx = PTB;
    pt_init.GPIO_Dir = DIR_INPUT;
    pt_init.GPIO_Pins = GPIO_Pin0_7;
    pt_init.GPIO_PinControl = IRQC_DIS | INPUT_PULL_DIS;
    LPLD_GPIO_Init(pt_init);
    /*------------ov7725场信号IO初始化(PTA29)---------------*/
    pt_init.GPIO_PTx = PTA;
    pt_init.GPIO_Dir = DIR_INPUT;
    pt_init.GPIO_Pins = GPIO_Pin29;
    pt_init.GPIO_PinControl = IRQC_RI | INPUT_PULL_DOWN | INPUT_PF_EN;
    pt_init.GPIO_Isr = porta_isr;
    LPLD_GPIO_Init(pt_init);
    /*------------ov7725_PCLK_IO初始化(PTA27)---------------*/
    pt_init.GPIO_PTx = PTA;
    pt_init.GPIO_Pins = GPIO_Pin27;
    pt_init.GPIO_Dir = DIR_INPUT;
    pt_init.GPIO_PinControl = IRQC_DMAFA | INPUT_PULL_DOWN;
    LPLD_GPIO_Init(pt_init);
}


void DMA_ov7725_init(void)
{

    DMA_InitTypeDef dma_init_struct;
    //DMA参数配置
    dma_init_struct.DMA_CHx = DMA_CH0;    //CH0通道
    dma_init_struct.DMA_Req = PORTA_DMAREQ;       //PORTA为请求源
    dma_init_struct.DMA_MajorLoopCnt = CAMERA_SIZE; //主循环计数值
    dma_init_struct.DMA_MinorByteCnt = 1; //次循环字节计数：每次读入1字节
    dma_init_struct.DMA_SourceAddr = (uint32)&PTB->PDIR;        //源地址：PTD8~15
    dma_init_struct.DMA_DestAddr = (uint32)imgbuff;      //目的地址：存放图像的数组
    dma_init_struct.DMA_DestAddrOffset = 1;       //目的地址偏移：每次读入增加1
    dma_init_struct.DMA_AutoDisableReq = TRUE;    //自动禁用请求
    dma_init_struct.DMA_MajorCompleteIntEnable = TRUE;
    dma_init_struct.DMA_Isr = RazorDMA_Isr;
    //初始化DMA
    LPLD_DMA_Init(dma_init_struct);
    DMA0->INT |= 0x1u << 0;
    LPLD_DMA_EnableIrq(dma_init_struct);
}


void vcan_sendimg(void *imgaddr, uint32_t imgsize)
{
#define CMD_IMG     1
    int8 cmdf[2] = { CMD_IMG, ~CMD_IMG };    //山外上位机 使用的命令
    int8 cmdr[2] = { ~CMD_IMG, CMD_IMG };    //山外上位机 使用的命令

    LPLD_UART_PutCharArr(UART2, cmdf, sizeof(cmdf));    //先发送命令

    LPLD_UART_PutCharArr(UART2, (int8 *)imgaddr, imgsize); //再发送图像

    LPLD_UART_PutCharArr(UART2, cmdr, sizeof(cmdr));    //先发送命令
}
void img_extract(void *dst, void *src, uint32 srclen)
{
    uint8 colour[2] = { 255, 0 }; //0 和 1 分别对应的颜色
    uint8 * mdst = dst;
    uint8 * msrc = src;
    //注：山外的摄像头 0 表示 白色，1表示 黑色
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
        //场中断需要判断是场结束还是场开始
        if (ov7725_eagle_img_flag == IMG_START)                   //需要开始采集图像
        {
            ov7725_eagle_img_flag = IMG_GATHER;                  //标记图像采集中
            disable_irq(PORTA_IRQn);
            PORTA->ISFR = 1 << 27;            //清空PCLK标志位
            DMA0->ERQ |= DMA_ERQ_ERQ0_MASK << 0;
            PORTA->ISFR = 1 << 27;            //清空PCLK标志位
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
    imgEdge(img);
    //vcan_sendimg(imgbuff, CAMERA_SIZE);
    vcan_sendimg(img, CAMERA_W * CAMERA_H);                  //发送到上位机
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
    ov7725_eagle_img_flag = IMG_START;                   //开始采集图像
    PORTA->ISFR = ~0;
    enable_irq((IRQn_Type)(PORTA_IRQn));
    while (ov7725_eagle_img_flag != IMG_FINISH)
    {
        if (ov7725_eagle_img_flag == IMG_FAIL)            //假如图像采集错误，则重新开始采集
        {
            ov7725_eagle_img_flag = IMG_START;           //开始采集图像
            PORTA->ISFR = 0xFFFFFFFFu;                //写1清中断标志位(必须的，不然回导致一开中断就马上触发中断)
            enable_irq(PORTA_IRQn);                 //允许PTA的中断
        }
    }
}
