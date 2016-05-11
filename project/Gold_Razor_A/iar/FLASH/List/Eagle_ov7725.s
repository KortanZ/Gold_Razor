///////////////////////////////////////////////////////////////////////////////
//
// IAR ANSI C/C++ Compiler V7.40.3.8902/W32 for ARM       08/May/2016  17:35:42
// Copyright 1999-2015 IAR Systems AB.
//
//    Cpu mode     =  thumb
//    Endian       =  little
//    Source file  =  
//        C:\Users\Administrator\Desktop\Gold_Razor_A\project\Gold_Razor_A\app\Source\Eagle_ov7725.c
//    Command line =  
//        C:\Users\Administrator\Desktop\Gold_Razor_A\project\Gold_Razor_A\app\Source\Eagle_ov7725.c
//        -D LPLD_K60 -D USE_K60DZ10 -lCN
//        C:\Users\Administrator\Desktop\Gold_Razor_A\project\Gold_Razor_A\iar\FLASH\List\
//        -lB
//        C:\Users\Administrator\Desktop\Gold_Razor_A\project\Gold_Razor_A\iar\FLASH\List\
//        -o
//        C:\Users\Administrator\Desktop\Gold_Razor_A\project\Gold_Razor_A\iar\FLASH\Obj\
//        --no_cse --no_unroll --no_inline --no_code_motion --no_tbaa
//        --no_clustering --no_scheduling --debug --endian=little
//        --cpu=Cortex-M4 -e --fpu=None --dlib_config "D:\IAR EWARM\Program
//        Files (x86)\IAR Systems\Embedded Workbench
//        7.2\arm\INC\c\DLib_Config_Normal.h" -I
//        C:\Users\Administrator\Desktop\Gold_Razor_A\project\Gold_Razor_A\iar\..\app\
//        -I
//        C:\Users\Administrator\Desktop\Gold_Razor_A\project\Gold_Razor_A\iar\..\app\Source\
//        -I
//        C:\Users\Administrator\Desktop\Gold_Razor_A\project\Gold_Razor_A\iar\..\..\..\lib\CPU\
//        -I
//        C:\Users\Administrator\Desktop\Gold_Razor_A\project\Gold_Razor_A\iar\..\..\..\lib\common\
//        -I
//        C:\Users\Administrator\Desktop\Gold_Razor_A\project\Gold_Razor_A\iar\..\..\..\lib\LPLD\
//        -I
//        C:\Users\Administrator\Desktop\Gold_Razor_A\project\Gold_Razor_A\iar\..\..\..\lib\LPLD\HW\
//        -I
//        C:\Users\Administrator\Desktop\Gold_Razor_A\project\Gold_Razor_A\iar\..\..\..\lib\LPLD\DEV\
//        -I
//        C:\Users\Administrator\Desktop\Gold_Razor_A\project\Gold_Razor_A\iar\..\..\..\lib\LPLD\FUNC\
//        -I
//        C:\Users\Administrator\Desktop\Gold_Razor_A\project\Gold_Razor_A\iar\..\..\..\lib\uCOS-II\Ports\
//        -I
//        C:\Users\Administrator\Desktop\Gold_Razor_A\project\Gold_Razor_A\iar\..\..\..\lib\uCOS-II\Source\
//        -I
//        C:\Users\Administrator\Desktop\Gold_Razor_A\project\Gold_Razor_A\iar\..\..\..\lib\FatFs\
//        -I
//        C:\Users\Administrator\Desktop\Gold_Razor_A\project\Gold_Razor_A\iar\..\..\..\lib\FatFs\option\
//        -I
//        C:\Users\Administrator\Desktop\Gold_Razor_A\project\Gold_Razor_A\iar\..\..\..\lib\USB\common\
//        -I
//        C:\Users\Administrator\Desktop\Gold_Razor_A\project\Gold_Razor_A\iar\..\..\..\lib\USB\driver\
//        -I
//        C:\Users\Administrator\Desktop\Gold_Razor_A\project\Gold_Razor_A\iar\..\..\..\lib\USB\descriptor\
//        -I
//        C:\Users\Administrator\Desktop\Gold_Razor_A\project\Gold_Razor_A\iar\..\..\..\lib\USB\class\
//        -Ol -I "D:\IAR EWARM\Program Files (x86)\IAR Systems\Embedded
//        Workbench 7.2\arm\CMSIS\Include\" -D ARM_MATH_CM4
//    List file    =  
//        C:\Users\Administrator\Desktop\Gold_Razor_A\project\Gold_Razor_A\iar\FLASH\List\Eagle_ov7725.s
//
///////////////////////////////////////////////////////////////////////////////

        #define SHT_PROGBITS 0x1

        EXTERN LPLD_DMA_EnableIrq
        EXTERN LPLD_DMA_Init
        EXTERN LPLD_GPIO_Init
        EXTERN LPLD_SCCB_Init
        EXTERN LPLD_SCCB_ReadReg
        EXTERN LPLD_SCCB_WriteReg
        EXTERN LPLD_UART_PutCharArr
        EXTERN __aeabi_memcpy4

        PUBLIC Camera_init
        PUBLIC RazorDMA_Isr
        PUBLIC camera_delay
        PUBLIC img
        PUBLIC img_extract
        PUBLIC imgbuff
        PUBLIC ov7725_eagle_cfgnum
        PUBLIC ov7725_eagle_img_flag
        PUBLIC ov7725_eagle_reg
        PUBLIC porta_isr
        PUBLIC vcan_sendimg

// C:\Users\Administrator\Desktop\Gold_Razor_A\project\Gold_Razor_A\app\Source\Eagle_ov7725.c
//    1 //#include "common.h"
//    2 #include "Eagle_ov7725.h"

        SECTION `.text`:CODE:NOROOT(1)
        THUMB
// static __interwork __softfp void NVIC_DisableIRQ(IRQn_Type)
NVIC_DisableIRQ:
        MOVS     R1,#+1
        ANDS     R2,R0,#0x1F
        LSLS     R1,R1,R2
        LDR.N    R2,??DataTable7  ;; 0xe000e180
        SXTB     R0,R0            ;; SignExt  R0,R0,#+24,#+24
        LSRS     R0,R0,#+5
        STR      R1,[R2, R0, LSL #+2]
        BX       LR               ;; return
//    3 #include "Eagle_ov7725_reg.h"
//    4 /*OV7725初始化配置表*/

        SECTION `.data`:DATA:REORDER:NOROOT(2)
//    5 reg_s ov7725_eagle_reg[] =
ov7725_eagle_reg:
        DATA
        DC8 13, 193, 17, 0, 9, 3, 12, 208, 18, 64, 23, 63, 24, 80, 25, 3, 26
        DC8 120, 50, 0, 160, 10, 99, 224, 172, 255, 101, 12, 102, 0, 103, 0, 41
        DC8 40, 44, 60, 42, 0, 126, 12, 127, 22, 128, 42, 129, 78, 130, 97, 131
        DC8 111, 132, 123, 133, 134, 134, 142, 135, 151, 136, 164, 137, 175
        DC8 138, 197, 139, 215, 140, 232, 141, 32, 74, 0, 73, 19, 71, 8, 75, 20
        DC8 76, 23, 70, 5, 34, 153, 35, 3, 166, 4, 155, 0, 156, 60, 171, 6, 158
        DC8 17, 159, 2, 0, 0
//    6 {
//    7     //寄存器，寄存器值次
//    8     { OV7725_COM4, 0xC1 },   //PLL时钟设置:8x时钟   AEC设置:Full Window
//    9     { OV7725_CLKRC, 0x00 },   //使用外部时钟
//   10     { OV7725_COM2, 0x03 },   //配置输出驱动能力:4x驱动能力
//   11     { OV7725_COM3, 0xD0 },   //7:垂直翻转开关 6:水平镜像开关
//   12     { OV7725_COM7, 0x40 },   //SCCB : No Change
//   13     { OV7725_HSTART, 0x3F },
//   14     { OV7725_HSIZE, 0x50 },
//   15     { OV7725_VSTRT, 0x03 },
//   16     { OV7725_VSIZE, 0x78 },
//   17     { OV7725_HREF, 0x00 },
//   18     { OV7725_SCAL0, 0x0A },
//   19     { OV7725_AWB_Ctrl0, 0xE0 },
//   20     { OV7725_DSPAuto, 0xff },
//   21     { OV7725_DSP_Ctrl2, 0x0C },
//   22     { OV7725_DSP_Ctrl3, 0x00 },
//   23     { OV7725_DSP_Ctrl4, 0x00 },
//   24 
//   25 #if (CAMERA_W == 80)
//   26     { OV7725_HOutSize, 0x14 },
//   27 #elif (CAMERA_W == 160)
//   28     { OV7725_HOutSize, 0x28 },
//   29 #elif (CAMERA_W == 240)
//   30     { OV7725_HOutSize, 0x3c },
//   31 #elif (CAMERA_W == 320)
//   32     { OV7725_HOutSize, 0x50 },
//   33 #else
//   34 
//   35 #endif
//   36 
//   37 #if (CAMERA_H == 60 )
//   38     { OV7725_VOutSize, 0x1E },
//   39 #elif (CAMERA_H == 120 )
//   40     { OV7725_VOutSize, 0x3c },
//   41 #elif (CAMERA_H == 180 )
//   42     { OV7725_VOutSize, 0x5a },
//   43 #elif (CAMERA_H == 240 )
//   44     { OV7725_VOutSize, 0x78 },
//   45 #else
//   46 
//   47 #endif
//   48 
//   49     { OV7725_EXHCH, 0x00 },
//   50     { OV7725_GAM1, 0x0c },
//   51     { OV7725_GAM2, 0x16 },
//   52     { OV7725_GAM3, 0x2a },
//   53     { OV7725_GAM4, 0x4e },
//   54     { OV7725_GAM5, 0x61 },
//   55     { OV7725_GAM6, 0x6f },
//   56     { OV7725_GAM7, 0x7b },
//   57     { OV7725_GAM8, 0x86 },
//   58     { OV7725_GAM9, 0x8e },
//   59     { OV7725_GAM10, 0x97 },
//   60     { OV7725_GAM11, 0xa4 },
//   61     { OV7725_GAM12, 0xaf },
//   62     { OV7725_GAM13, 0xc5 },
//   63     { OV7725_GAM14, 0xd7 },
//   64     { OV7725_GAM15, 0xe8 },
//   65     { OV7725_SLOP, 0x20 },
//   66     { OV7725_LC_RADI, 0x00 },
//   67     { OV7725_LC_COEF, 0x13 },
//   68     { OV7725_LC_XC, 0x08 },
//   69     { OV7725_LC_COEFB, 0x14 },
//   70     { OV7725_LC_COEFR, 0x17 },
//   71     { OV7725_LC_CTR, 0x05 },
//   72     { OV7725_BDBase, 0x99 },
//   73     { OV7725_BDMStep, 0x03 },
//   74     { OV7725_SDE, 0x04 },
//   75     { OV7725_BRIGHT, 0x00 },
//   76     { OV7725_CNST, 0x3C },
//   77     { OV7725_SIGN, 0x06 },
//   78     { OV7725_UVADJ0, 0x11 },
//   79     { OV7725_UVADJ1, 0x02 },
//   80 
//   81 };
//   82 
//   83 

        SECTION `.data`:DATA:REORDER:NOROOT(0)
//   84 uint8 ov7725_eagle_cfgnum = ARR_SIZE(ov7725_eagle_reg); /*结构体数组成员数目*/
ov7725_eagle_cfgnum:
        DATA
        DC8 49
//   85 
//   86 

        SECTION `.bss`:DATA:REORDER:NOROOT(2)
//   87 uint8 imgbuff[CAMERA_SIZE];
imgbuff:
        DS8 2400

        SECTION `.bss`:DATA:REORDER:NOROOT(2)
//   88 uint8 img[CAMERA_H * CAMERA_W];
img:
        DS8 19200

        SECTION `.data`:DATA:REORDER:NOROOT(0)
//   89 uint8 ov7725_eagle_img_flag = IMG_FINISH;
ov7725_eagle_img_flag:
        DATA
        DC8 1
//   90 

        SECTION `.text`:CODE:NOROOT(1)
        THUMB
//   91 uint8 Camera_init(void)
//   92 {
Camera_init:
        PUSH     {R7,LR}
//   93     while (ov7725_eagle_reg_init() == 0);
??Camera_init_0:
        BL       ov7725_eagle_reg_init
        CMP      R0,#+0
        BEQ.N    ??Camera_init_0
//   94     camera_delay();
        BL       camera_delay
//   95 
//   96 	GPIO_ov7725_init();
        BL       GPIO_ov7725_init
//   97 	DMA_ov7725_init();
        BL       DMA_ov7725_init
//   98 
//   99 
//  100     return 0;
        MOVS     R0,#+0
        POP      {R1,PC}          ;; return
//  101 }
//  102 
//  103 

        SECTION `.text`:CODE:NOROOT(1)
        THUMB
//  104 uint8 ov7725_eagle_reg_init(void)
//  105 {
ov7725_eagle_reg_init:
        PUSH     {R4,LR}
        SUB      SP,SP,#+8
//  106     uint16 i = 0;
        MOVS     R4,#+0
//  107     uint8 Sensor_IDCode = 0;
        MOVS     R0,#+0
        STRB     R0,[SP, #+0]
//  108     LPLD_SCCB_Init();
        BL       LPLD_SCCB_Init
//  109     camera_delay();
        BL       camera_delay
//  110 
//  111     if (0 == LPLD_SCCB_WriteReg(OV7725_COM7, 0x80))
        MOVS     R1,#+128
        MOVS     R0,#+18
        BL       LPLD_SCCB_WriteReg
        CMP      R0,#+0
        BNE.N    ??ov7725_eagle_reg_init_0
//  112     {
//  113         //printf("\n Error!")
//  114         return 0;
        MOVS     R0,#+0
        B.N      ??ov7725_eagle_reg_init_1
//  115     }
//  116 
//  117     camera_delay();
??ov7725_eagle_reg_init_0:
        BL       camera_delay
//  118 
//  119     if (0 == LPLD_SCCB_ReadReg(OV7725_VER, &Sensor_IDCode, 1))
        MOVS     R2,#+1
        ADD      R1,SP,#+0
        MOVS     R0,#+11
        BL       LPLD_SCCB_ReadReg
        CMP      R0,#+0
        BNE.N    ??ov7725_eagle_reg_init_2
//  120     {
//  121         //printf("\n Error!")
//  122         return 0;
        MOVS     R0,#+0
        B.N      ??ov7725_eagle_reg_init_1
//  123     }
//  124 
//  125     if (Sensor_IDCode == OV7725_ID)
??ov7725_eagle_reg_init_2:
        LDRB     R0,[SP, #+0]
        CMP      R0,#+33
        BNE.N    ??ov7725_eagle_reg_init_3
//  126     {
//  127         for (i = 0; i < ov7725_eagle_cfgnum; i++)
        MOVS     R4,#+0
        B.N      ??ov7725_eagle_reg_init_4
??ov7725_eagle_reg_init_5:
        ADDS     R4,R4,#+1
??ov7725_eagle_reg_init_4:
        LDR.N    R0,??DataTable7_1
        LDRB     R0,[R0, #+0]
        UXTH     R4,R4            ;; ZeroExt  R4,R4,#+16,#+16
        UXTH     R0,R0            ;; ZeroExt  R0,R0,#+16,#+16
        CMP      R4,R0
        BCS.N    ??ov7725_eagle_reg_init_6
//  128         {
//  129             if (0 == LPLD_SCCB_WriteReg(ov7725_eagle_reg[i].addr, ov7725_eagle_reg[i].val))
        LDR.N    R0,??DataTable7_2
        UXTH     R4,R4            ;; ZeroExt  R4,R4,#+16,#+16
        ADDS     R0,R0,R4, LSL #+1
        LDRB     R1,[R0, #+1]
        LDR.N    R0,??DataTable7_2
        UXTH     R4,R4            ;; ZeroExt  R4,R4,#+16,#+16
        LDRB     R0,[R0, R4, LSL #+1]
        UXTH     R0,R0            ;; ZeroExt  R0,R0,#+16,#+16
        BL       LPLD_SCCB_WriteReg
        CMP      R0,#+0
        BNE.N    ??ov7725_eagle_reg_init_5
//  130             {
//  131                 //printf("\n Error!")
//  132                 return 0;
        MOVS     R0,#+0
        B.N      ??ov7725_eagle_reg_init_1
//  133             }
//  134         }
//  135     }
//  136     else
//  137     {
//  138         return 0;
//  139     }
//  140     //printf("\n Successfully")
//  141     return 1;
??ov7725_eagle_reg_init_6:
        MOVS     R0,#+1
        B.N      ??ov7725_eagle_reg_init_1
??ov7725_eagle_reg_init_3:
        MOVS     R0,#+0
??ov7725_eagle_reg_init_1:
        POP      {R1,R2,R4,PC}    ;; return
//  142 }
//  143 

        SECTION `.text`:CODE:NOROOT(1)
        THUMB
//  144 static void GPIO_ov7725_init(void)
//  145 {
GPIO_ov7725_init:
        PUSH     {LR}
        SUB      SP,SP,#+28
//  146     
//  147     GPIO_InitTypeDef ov7725_gpio_init;
//  148     /*------------ov7725数据IO初始化(PTB0_PTB7)-------------*/
//  149     ov7725_gpio_init.GPIO_PTx = PTB;
        LDR.N    R0,??DataTable7_3  ;; 0x400ff040
        STR      R0,[SP, #+4]
//  150     ov7725_gpio_init.GPIO_Dir = DIR_INPUT;
        MOVS     R0,#+0
        STRB     R0,[SP, #+16]
//  151     ov7725_gpio_init.GPIO_Pins = GPIO_Pin0_7;
        MOVS     R0,#+255
        STR      R0,[SP, #+8]
//  152 	ov7725_gpio_init.GPIO_Output = OUTPUT_L;
        MOVS     R0,#+0
        STRB     R0,[SP, #+17]
//  153     ov7725_gpio_init.GPIO_PinControl = IRQC_DIS | INPUT_PULL_DIS;
        MOVS     R0,#+0
        STR      R0,[SP, #+12]
//  154     LPLD_GPIO_Init(ov7725_gpio_init);
        ADD      R1,SP,#+4
        SUB      SP,SP,#+16
        MOV      R0,SP
        MOVS     R2,#+20
        BL       __aeabi_memcpy4
        POP      {R0-R3}
        BL       LPLD_GPIO_Init
//  155     /*------------ov7725场信号IO初始化(PTA29)---------------*/
//  156     ov7725_gpio_init.GPIO_PTx = PTA;
        LDR.N    R0,??DataTable7_4  ;; 0x400ff000
        STR      R0,[SP, #+4]
//  157     ov7725_gpio_init.GPIO_Dir = DIR_INPUT;
        MOVS     R0,#+0
        STRB     R0,[SP, #+16]
//  158     ov7725_gpio_init.GPIO_Pins = GPIO_Pin29;
        MOVS     R0,#+536870912
        STR      R0,[SP, #+8]
//  159     ov7725_gpio_init.GPIO_PinControl = IRQC_RI | INPUT_PULL_DOWN | INPUT_PF_EN;
        LDR.N    R0,??DataTable7_5  ;; 0x90012
        STR      R0,[SP, #+12]
//  160     ov7725_gpio_init.GPIO_Isr = porta_isr;
        ADR.W    R0,porta_isr
        STR      R0,[SP, #+20]
//  161     LPLD_GPIO_Init(ov7725_gpio_init);
        ADD      R1,SP,#+4
        SUB      SP,SP,#+16
        MOV      R0,SP
        MOVS     R2,#+20
        BL       __aeabi_memcpy4
        POP      {R0-R3}
        BL       LPLD_GPIO_Init
//  162     /*------------ov7725_PCLK_IO初始化(PTA27)---------------*/
//  163     ov7725_gpio_init.GPIO_PTx = PTA;
        LDR.N    R0,??DataTable7_4  ;; 0x400ff000
        STR      R0,[SP, #+4]
//  164     ov7725_gpio_init.GPIO_Pins = GPIO_Pin27;
        MOVS     R0,#+134217728
        STR      R0,[SP, #+8]
//  165     ov7725_gpio_init.GPIO_Dir = DIR_INPUT;
        MOVS     R0,#+0
        STRB     R0,[SP, #+16]
//  166     ov7725_gpio_init.GPIO_PinControl = IRQC_DMAFA | INPUT_PULL_DOWN;
        MOVS     R0,#+131074
        STR      R0,[SP, #+12]
//  167     LPLD_GPIO_Init(ov7725_gpio_init);
        ADD      R1,SP,#+4
        SUB      SP,SP,#+16
        MOV      R0,SP
        MOVS     R2,#+20
        BL       __aeabi_memcpy4
        POP      {R0-R3}
        BL       LPLD_GPIO_Init
//  168 }
        ADD      SP,SP,#+28
        POP      {PC}             ;; return
//  169 
//  170 

        SECTION `.text`:CODE:NOROOT(1)
        THUMB
//  171 void DMA_ov7725_init(void)
//  172 {
DMA_ov7725_init:
        PUSH     {LR}
        SUB      SP,SP,#+76
//  173 
//  174     DMA_InitTypeDef dma_init_struct;
//  175     //DMA参数配置
//  176     dma_init_struct.DMA_CHx = DMA_CH0;    //CH0通道
        MOVS     R0,#+0
        STRB     R0,[SP, #+28]
//  177     dma_init_struct.DMA_Req = PORTA_DMAREQ;       //PORTA为请求源
        MOVS     R0,#+49
        STRB     R0,[SP, #+29]
//  178     dma_init_struct.DMA_PeriodicTriggerEnable = FALSE;
        MOVS     R0,#+0
        STRB     R0,[SP, #+30]
//  179     dma_init_struct.DMA_MajorLoopCnt = CAMERA_SIZE; //主循环计数值
        MOV      R0,#+2400
        STRH     R0,[SP, #+32]
//  180     dma_init_struct.DMA_MinorByteCnt = 1; //次循环字节计数：每次读入1字节
        MOVS     R0,#+1
        STR      R0,[SP, #+36]
//  181     dma_init_struct.DMA_SourceDataSize = DMA_SRC_8BIT;
        MOVS     R0,#+0
        STRB     R0,[SP, #+44]
//  182     dma_init_struct.DMA_SourceAddr = (uint32)&PTB->PDIR;        //源地址：PTD8~15
        LDR.N    R0,??DataTable7_6  ;; 0x400ff050
        STR      R0,[SP, #+40]
//  183     dma_init_struct.DMA_SourceAddrOffset = 0;
        MOVS     R0,#+0
        STRH     R0,[SP, #+46]
//  184     dma_init_struct.DMA_LastSourceAddrAdj = 0;
        MOVS     R0,#+0
        STR      R0,[SP, #+48]
//  185     dma_init_struct.DMA_DestAddr = (uint32)imgbuff;      //目的地址：存放图像的数组
        LDR.N    R0,??DataTable7_7
        STR      R0,[SP, #+52]
//  186     dma_init_struct.DMA_DestDataSize = DMA_DST_8BIT;
        MOVS     R0,#+0
        STRB     R0,[SP, #+56]
//  187     dma_init_struct.DMA_DestAddrOffset = 1;       //目的地址偏移：每次读入增加1
        MOVS     R0,#+1
        STRH     R0,[SP, #+58]
//  188     dma_init_struct.DMA_LastDestAddrAdj = 0;
        MOVS     R0,#+0
        STR      R0,[SP, #+60]
//  189     dma_init_struct.DMA_AutoDisableReq = TRUE;    //自动禁用请求
        MOVS     R0,#+1
        STRB     R0,[SP, #+64]
//  190     dma_init_struct.DMA_MajorCompleteIntEnable = TRUE;
        MOVS     R0,#+1
        STRB     R0,[SP, #+65]
//  191     dma_init_struct.DMA_MajorHalfCompleteIntEnable = FALSE;
        MOVS     R0,#+0
        STRB     R0,[SP, #+66]
//  192     dma_init_struct.DMA_Isr = RazorDMA_Isr;
        ADR.W    R0,RazorDMA_Isr
        STR      R0,[SP, #+68]
//  193     //初始化DMA
//  194     LPLD_DMA_Init(dma_init_struct);
        ADD      R1,SP,#+28
        SUB      SP,SP,#+16
        MOV      R0,SP
        MOVS     R2,#+44
        BL       __aeabi_memcpy4
        POP      {R0-R3}
        BL       LPLD_DMA_Init
//  195     DMA0->INT |= 0x1u << 0;
        LDR.N    R0,??DataTable7_8  ;; 0x40008024
        LDR      R0,[R0, #+0]
        ORRS     R0,R0,#0x1
        LDR.N    R1,??DataTable7_8  ;; 0x40008024
        STR      R0,[R1, #+0]
//  196     LPLD_DMA_EnableIrq(dma_init_struct);
        ADD      R1,SP,#+28
        SUB      SP,SP,#+16
        MOV      R0,SP
        MOVS     R2,#+44
        BL       __aeabi_memcpy4
        POP      {R0-R3}
        BL       LPLD_DMA_EnableIrq
//  197 }
        ADD      SP,SP,#+76
        POP      {PC}             ;; return
//  198 
//  199 

        SECTION `.text`:CODE:NOROOT(1)
        THUMB
//  200 void vcan_sendimg(void *imgaddr, uint32_t imgsize)
//  201 {
vcan_sendimg:
        PUSH     {R3-R5,LR}
        MOVS     R4,R0
        MOVS     R5,R1
//  202 #define CMD_IMG     1
//  203     int8 cmdf[2] = { CMD_IMG, ~CMD_IMG };    //山外上位机 使用的命令
        LDR.N    R0,??DataTable7_9
        LDRH     R0,[R0, #+0]
        STRH     R0,[SP, #+2]
//  204     int8 cmdr[2] = { ~CMD_IMG, CMD_IMG };    //山外上位机 使用的命令
        LDR.N    R0,??DataTable7_10
        LDRH     R0,[R0, #+0]
        STRH     R0,[SP, #+0]
//  205 
//  206     LPLD_UART_PutCharArr(UART2, cmdf, sizeof(cmdf));    //先发送命令
        MOVS     R2,#+2
        ADD      R1,SP,#+2
        LDR.N    R0,??DataTable7_11  ;; 0x4006c000
        BL       LPLD_UART_PutCharArr
//  207 
//  208     LPLD_UART_PutCharArr(UART2, (int8 *)imgaddr, imgsize); //再发送图像
        MOVS     R2,R5
        MOVS     R1,R4
        LDR.N    R0,??DataTable7_11  ;; 0x4006c000
        BL       LPLD_UART_PutCharArr
//  209 
//  210     LPLD_UART_PutCharArr(UART2, cmdr, sizeof(cmdr));    //先发送命令
        MOVS     R2,#+2
        ADD      R1,SP,#+0
        LDR.N    R0,??DataTable7_11  ;; 0x4006c000
        BL       LPLD_UART_PutCharArr
//  211 }
        POP      {R0,R4,R5,PC}    ;; return

        SECTION `.text`:CODE:NOROOT(1)
        THUMB
//  212 void img_extract(void *dst, void *src, uint32 srclen)
//  213 {
img_extract:
        PUSH     {R3-R5}
//  214     uint8 colour[2] = { 255, 0 }; //0 和 1 分别对应的颜色
        LDR.N    R3,??DataTable7_12
        LDRH     R3,[R3, #+0]
        STRH     R3,[SP, #+0]
//  215     uint8 * mdst = dst;
//  216     uint8 * msrc = src;
        B.N      ??img_extract_0
//  217     //注：山外的摄像头 0 表示 白色，1表示 黑色
//  218     uint8 tmpsrc;
//  219     while (srclen--)
//  220     {
//  221         tmpsrc = *msrc++;
??img_extract_1:
        LDRB     R3,[R1, #+0]
        ADDS     R1,R1,#+1
//  222         *mdst++ = colour[(tmpsrc >> 7) & 0x01];
        ADD      R4,SP,#+0
        UXTB     R3,R3            ;; ZeroExt  R3,R3,#+24,#+24
        ASRS     R5,R3,#+7
        LDRB     R4,[R5, R4]
        STRB     R4,[R0, #+0]
        ADDS     R0,R0,#+1
//  223         *mdst++ = colour[(tmpsrc >> 6) & 0x01];
        ADD      R4,SP,#+0
        UBFX     R5,R3,#+6,#+1
        UXTB     R5,R5            ;; ZeroExt  R5,R5,#+24,#+24
        LDRB     R4,[R5, R4]
        STRB     R4,[R0, #+0]
        ADDS     R0,R0,#+1
//  224         *mdst++ = colour[(tmpsrc >> 5) & 0x01];
        ADD      R4,SP,#+0
        UBFX     R5,R3,#+5,#+1
        UXTB     R5,R5            ;; ZeroExt  R5,R5,#+24,#+24
        LDRB     R4,[R5, R4]
        STRB     R4,[R0, #+0]
        ADDS     R0,R0,#+1
//  225         *mdst++ = colour[(tmpsrc >> 4) & 0x01];
        ADD      R4,SP,#+0
        UBFX     R5,R3,#+4,#+1
        UXTB     R5,R5            ;; ZeroExt  R5,R5,#+24,#+24
        LDRB     R4,[R5, R4]
        STRB     R4,[R0, #+0]
        ADDS     R0,R0,#+1
//  226         *mdst++ = colour[(tmpsrc >> 3) & 0x01];
        ADD      R4,SP,#+0
        UBFX     R5,R3,#+3,#+1
        UXTB     R5,R5            ;; ZeroExt  R5,R5,#+24,#+24
        LDRB     R4,[R5, R4]
        STRB     R4,[R0, #+0]
        ADDS     R0,R0,#+1
//  227         *mdst++ = colour[(tmpsrc >> 2) & 0x01];
        ADD      R4,SP,#+0
        UBFX     R5,R3,#+2,#+1
        UXTB     R5,R5            ;; ZeroExt  R5,R5,#+24,#+24
        LDRB     R4,[R5, R4]
        STRB     R4,[R0, #+0]
        ADDS     R0,R0,#+1
//  228         *mdst++ = colour[(tmpsrc >> 1) & 0x01];
        ADD      R4,SP,#+0
        UBFX     R5,R3,#+1,#+1
        UXTB     R5,R5            ;; ZeroExt  R5,R5,#+24,#+24
        LDRB     R4,[R5, R4]
        STRB     R4,[R0, #+0]
        ADDS     R0,R0,#+1
//  229         *mdst++ = colour[(tmpsrc >> 0) & 0x01];
        ADD      R4,SP,#+0
        UXTB     R3,R3            ;; ZeroExt  R3,R3,#+24,#+24
        ANDS     R3,R3,#0x1
        LDRB     R3,[R3, R4]
        STRB     R3,[R0, #+0]
        ADDS     R0,R0,#+1
//  230     }
??img_extract_0:
        MOVS     R3,R2
        SUBS     R2,R3,#+1
        CMP      R3,#+0
        BNE.N    ??img_extract_1
//  231 }
        POP      {R0,R4,R5}
        BX       LR               ;; return
//  232 
//  233 

        SECTION `.text`:CODE:NOROOT(2)
        THUMB
//  234 void porta_isr(void)
//  235 {
porta_isr:
        PUSH     {R7,LR}
//  236     if (LPLD_GPIO_IsPinxExt(PORTA, GPIO_Pin29))
        LDR.N    R0,??DataTable7_13  ;; 0x400490a0
        LDR      R0,[R0, #+0]
        LSLS     R0,R0,#+2
        BPL.N    ??porta_isr_0
//  237     {
//  238         //场中断需要判断是场结束还是场开始
//  239         if (ov7725_eagle_img_flag == IMG_START)                   //需要开始采集图像
        LDR.N    R0,??DataTable7_14
        LDRB     R0,[R0, #+0]
        CMP      R0,#+4
        BNE.N    ??porta_isr_1
//  240         {
//  241             ov7725_eagle_img_flag = IMG_GATHER;                  //标记图像采集中
        MOVS     R0,#+3
        LDR.N    R1,??DataTable7_14
        STRB     R0,[R1, #+0]
//  242             disable_irq(PORTA_IRQn);
        MOVS     R0,#+87
        BL       NVIC_DisableIRQ
//  243             PORTA->ISFR = 1 << 27;            //清空PCLK标志位
        MOVS     R0,#+134217728
        LDR.N    R1,??DataTable7_13  ;; 0x400490a0
        STR      R0,[R1, #+0]
//  244             DMA0->ERQ |= DMA_ERQ_ERQ0_MASK << 0;
        LDR.N    R0,??DataTable7_15  ;; 0x4000800c
        LDR      R0,[R0, #+0]
        ORRS     R0,R0,#0x1
        LDR.N    R1,??DataTable7_15  ;; 0x4000800c
        STR      R0,[R1, #+0]
//  245             PORTA->ISFR = 1 << 27;            //清空PCLK标志位
        MOVS     R0,#+134217728
        LDR.N    R1,??DataTable7_13  ;; 0x400490a0
        STR      R0,[R1, #+0]
//  246             DMA0->TCD[0].DADDR = DMA_DADDR_DADDR(imgbuff);
        LDR.N    R0,??DataTable7_7
        LDR.N    R1,??DataTable7_16  ;; 0x40009010
        STR      R0,[R1, #+0]
        B.N      ??porta_isr_0
//  247         }
//  248         else
//  249         {
//  250             disable_irq(PORTA_IRQn);
??porta_isr_1:
        MOVS     R0,#+87
        BL       NVIC_DisableIRQ
//  251             ov7725_eagle_img_flag = IMG_FAIL;
        MOVS     R0,#+2
        LDR.N    R1,??DataTable7_14
        STRB     R0,[R1, #+0]
//  252         }
//  253     }
//  254 }
??porta_isr_0:
        POP      {R0,PC}          ;; return
//  255 

        SECTION `.text`:CODE:NOROOT(2)
        THUMB
//  256 void RazorDMA_Isr(void)
//  257 {
//  258     ov7725_eagle_img_flag = IMG_FINISH;
RazorDMA_Isr:
        MOVS     R0,#+1
        LDR.N    R1,??DataTable7_14
        STRB     R0,[R1, #+0]
//  259 
//  260     //img_extract(img, imgbuff, CAMERA_SIZE);
//  261     //imgEdge(img);
//  262     //vcan_sendimg(imgbuff, CAMERA_SIZE);
//  263     //vcan_sendimg(img, CAMERA_W * CAMERA_H);                  //发送到上位机
//  264     DMA0->INT |= 0x1u << 0;
        LDR.N    R0,??DataTable7_8  ;; 0x40008024
        LDR      R0,[R0, #+0]
        ORRS     R0,R0,#0x1
        LDR.N    R1,??DataTable7_8  ;; 0x40008024
        STR      R0,[R1, #+0]
//  265 }
        BX       LR               ;; return

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable7:
        DC32     0xe000e180

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable7_1:
        DC32     ov7725_eagle_cfgnum

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable7_2:
        DC32     ov7725_eagle_reg

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable7_3:
        DC32     0x400ff040

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable7_4:
        DC32     0x400ff000

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable7_5:
        DC32     0x90012

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable7_6:
        DC32     0x400ff050

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable7_7:
        DC32     imgbuff

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable7_8:
        DC32     0x40008024

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable7_9:
        DC32     ?_0

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable7_10:
        DC32     ?_1

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable7_11:
        DC32     0x4006c000

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable7_12:
        DC32     ?_2

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable7_13:
        DC32     0x400490a0

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable7_14:
        DC32     ov7725_eagle_img_flag

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable7_15:
        DC32     0x4000800c

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable7_16:
        DC32     0x40009010
//  266 

        SECTION `.text`:CODE:NOROOT(2)
        THUMB
//  267 void camera_delay(void)
//  268 {
//  269     uint16 i, n;
//  270     for (i = 0; i<30000; i++)
camera_delay:
        MOVS     R0,#+0
        B.N      ??camera_delay_0
//  271     {
//  272         for (n = 0; n<200; n++)
//  273         {
//  274             asm("nop");
??camera_delay_1:
        nop
//  275         }
        ADDS     R1,R1,#+1
??camera_delay_2:
        UXTH     R1,R1            ;; ZeroExt  R1,R1,#+16,#+16
        CMP      R1,#+200
        BLT.N    ??camera_delay_1
        ADDS     R0,R0,#+1
??camera_delay_0:
        UXTH     R0,R0            ;; ZeroExt  R0,R0,#+16,#+16
        MOVW     R1,#+30000
        CMP      R0,R1
        BGE.N    ??camera_delay_3
        MOVS     R1,#+0
        B.N      ??camera_delay_2
//  276     }
//  277 }
??camera_delay_3:
        BX       LR               ;; return

        SECTION `.iar_vfe_header`:DATA:NOALLOC:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
        DC32 0

        SECTION __DLIB_PERTHREAD:DATA:REORDER:NOROOT(0)
        SECTION_TYPE SHT_PROGBITS, 0

        SECTION __DLIB_PERTHREAD_init:DATA:REORDER:NOROOT(0)
        SECTION_TYPE SHT_PROGBITS, 0

        SECTION `.rodata`:CONST:REORDER:NOROOT(1)
?_0:
        DATA
        DC8 1, -2

        SECTION `.rodata`:CONST:REORDER:NOROOT(1)
?_1:
        DATA
        DC8 -2, 1

        SECTION `.rodata`:CONST:REORDER:NOROOT(1)
?_2:
        DATA
        DC8 255, 0

        END
//  278 
//  279 
// 
// 21 600 bytes in section .bss
//    102 bytes in section .data
//      6 bytes in section .rodata
//    848 bytes in section .text
// 
//    848 bytes of CODE  memory
//      6 bytes of CONST memory
// 21 702 bytes of DATA  memory
//
//Errors: none
//Warnings: none
