///////////////////////////////////////////////////////////////////////////////
//
// IAR ANSI C/C++ Compiler V7.40.3.8902/W32 for ARM       24/Apr/2016  20:13:18
// Copyright 1999-2015 IAR Systems AB.
//
//    Cpu mode     =  thumb
//    Endian       =  little
//    Source file  =  
//        C:\Users\Administrator\Desktop\Gold_Razor_A\project\Gold_Razor_A\app\Source\EncoderDriver.c
//    Command line =  
//        C:\Users\Administrator\Desktop\Gold_Razor_A\project\Gold_Razor_A\app\Source\EncoderDriver.c
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
//        C:\Users\Administrator\Desktop\Gold_Razor_A\project\Gold_Razor_A\iar\FLASH\List\EncoderDriver.s
//
///////////////////////////////////////////////////////////////////////////////

        #define SHT_PROGBITS 0x1

        EXTERN LPLD_FTM_ClearCounter
        EXTERN LPLD_FTM_GetCounter
        EXTERN LPLD_FTM_Init
        EXTERN LPLD_FTM_QD_Enable
        EXTERN LPLD_LPTMR_GetPulseAcc
        EXTERN LPLD_LPTMR_Init
        EXTERN LPLD_LPTMR_ResetCounter
        EXTERN __aeabi_memcpy4

        PUBLIC Encoder_GetPulseNum
        PUBLIC Encoder_Init
        PUBLIC Right_Encoder_init_param

// C:\Users\Administrator\Desktop\Gold_Razor_A\project\Gold_Razor_A\app\Source\EncoderDriver.c
//    1 //#include "common.h"
//    2 #include "EncoderDriver.h"

        SECTION `.bss`:DATA:REORDER:NOROOT(2)
//    3 LPTMR_InitTypeDef Right_Encoder_init_param;
Right_Encoder_init_param:
        DS8 12
//    4 /*编码器初始化*/

        SECTION `.text`:CODE:NOROOT(1)
        THUMB
//    5 void Encoder_Init(void)
//    6 {
Encoder_Init:
        PUSH     {LR}
        SUB      SP,SP,#+44
//    7 	
//    8 	FTM_InitTypeDef Left_Encoder_init_struct;
//    9 
//   10 	//配置正交解码功能参数
//   11 	Left_Encoder_init_struct.FTM_Ftmx = FTM1;              //只有FTM1和FTM2有正交解码功能
        LDR.N    R0,??DataTable1  ;; 0x40039000
        STR      R0,[SP, #+12]
//   12 	Left_Encoder_init_struct.FTM_Mode = FTM_MODE_QD;       //正交解码功能
        MOVS     R0,#+4
        STRB     R0,[SP, #+16]
//   13 	Left_Encoder_init_struct.FTM_PwmFreq = 0;
        MOVS     R0,#+0
        STR      R0,[SP, #+20]
//   14 
//   15 	Left_Encoder_init_struct.FTM_QdMode = QD_MODE_PHAB;    //AB相输入模式
        MOVS     R0,#+0
        STRB     R0,[SP, #+30]
//   16 	//初始化FTM
//   17 	LPLD_FTM_Init(Left_Encoder_init_struct);
        ADD      R1,SP,#+12
        SUB      SP,SP,#+16
        MOV      R0,SP
        MOVS     R2,#+28
        BL       __aeabi_memcpy4
        POP      {R0-R3}
        BL       LPLD_FTM_Init
//   18 	//使能AB相输入通道
//   19 	//PTB0引脚接A相输入、PTB1引脚接B相输入
//   20 	LPLD_FTM_QD_Enable(FTM1, PTA12, PTA13);
        MOVS     R2,#+13
        MOVS     R1,#+12
        LDR.N    R0,??DataTable1  ;; 0x40039000
        BL       LPLD_FTM_QD_Enable
//   21 
//   22 	//LPTMR_MODE_PLACC脉冲累加模式
//   23 	//LPTMR_ALT2的输入口为PTC5
//   24 	//禁用中断
//   25 	//无中断函数
//   26 	Right_Encoder_init_param.LPTMR_Mode = LPTMR_MODE_PLACC;
        MOVS     R0,#+1
        LDR.N    R1,??DataTable1_1
        STRB     R0,[R1, #+0]
//   27 	Right_Encoder_init_param.LPTMR_PluseAccInput = LPTMR_ALT2;
        MOVS     R0,#+2
        LDR.N    R1,??DataTable1_1
        STRB     R0,[R1, #+4]
//   28 	Right_Encoder_init_param.LPTMR_IntEnable = FALSE;
        MOVS     R0,#+0
        LDR.N    R1,??DataTable1_1
        STRB     R0,[R1, #+5]
//   29 	Right_Encoder_init_param.LPTMR_Isr = NULL;
        MOVS     R0,#+0
        LDR.N    R1,??DataTable1_1
        STR      R0,[R1, #+8]
//   30 
//   31 	LPLD_LPTMR_Init(Right_Encoder_init_param);
        LDR.N    R0,??DataTable1_1
        LDM      R0,{R0-R2}
        BL       LPLD_LPTMR_Init
//   32 
//   33 }
        ADD      SP,SP,#+44
        POP      {PC}             ;; return
//   34 
//   35 /*获取编码器值*/
//   36 
//   37 //参数position：Left左编码器；Right右编码器
//   38 

        SECTION `.text`:CODE:NOROOT(1)
        THUMB
//   39 int16 Encoder_GetPulseNum(EncoderPosition position)
//   40 {
Encoder_GetPulseNum:
        PUSH     {R4,LR}
//   41 	int16 result;
//   42 	
//   43 	switch (position)
        UXTB     R0,R0            ;; ZeroExt  R0,R0,#+24,#+24
        CMP      R0,#+0
        BEQ.N    ??Encoder_GetPulseNum_0
        CMP      R0,#+1
        BEQ.N    ??Encoder_GetPulseNum_1
        B.N      ??Encoder_GetPulseNum_2
//   44 	{
//   45 		case ENCODER_LEFT: 
//   46 			result = -LPLD_FTM_GetCounter(FTM1); 
??Encoder_GetPulseNum_0:
        LDR.N    R0,??DataTable1  ;; 0x40039000
        BL       LPLD_FTM_GetCounter
        RSBS     R4,R0,#+0
//   47 			LPLD_FTM_ClearCounter(FTM1);
        LDR.N    R0,??DataTable1  ;; 0x40039000
        BL       LPLD_FTM_ClearCounter
//   48 			break;	//左编码器反转
        B.N      ??Encoder_GetPulseNum_2
//   49 		case ENCODER_RIGHT: 
//   50 			result = 4 * LPLD_LPTMR_GetPulseAcc();
??Encoder_GetPulseNum_1:
        BL       LPLD_LPTMR_GetPulseAcc
        SXTH     R0,R0            ;; SignExt  R0,R0,#+16,#+16
        LSLS     R4,R0,#+2
//   51 			LPLD_LPTMR_ResetCounter();       //复位LPTMR0 counter 
        BL       LPLD_LPTMR_ResetCounter
//   52     		LPLD_LPTMR_Init(Right_Encoder_init_param);
        LDR.N    R0,??DataTable1_1
        LDM      R0,{R0-R2}
        BL       LPLD_LPTMR_Init
//   53     		break;
//   54 	}
//   55 
//   56 	return result;
??Encoder_GetPulseNum_2:
        MOVS     R0,R4
        SXTH     R0,R0            ;; SignExt  R0,R0,#+16,#+16
        POP      {R4,PC}          ;; return
//   57 }

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable1:
        DC32     0x40039000

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable1_1:
        DC32     Right_Encoder_init_param

        SECTION `.iar_vfe_header`:DATA:NOALLOC:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
        DC32 0

        SECTION __DLIB_PERTHREAD:DATA:REORDER:NOROOT(0)
        SECTION_TYPE SHT_PROGBITS, 0

        SECTION __DLIB_PERTHREAD_init:DATA:REORDER:NOROOT(0)
        SECTION_TYPE SHT_PROGBITS, 0

        END
//   58 
// 
//  12 bytes in section .bss
// 152 bytes in section .text
// 
// 152 bytes of CODE memory
//  12 bytes of DATA memory
//
//Errors: none
//Warnings: none
