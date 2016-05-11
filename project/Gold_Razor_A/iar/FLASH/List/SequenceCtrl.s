///////////////////////////////////////////////////////////////////////////////
//
// IAR ANSI C/C++ Compiler V7.40.3.8902/W32 for ARM       11/May/2016  19:10:53
// Copyright 1999-2015 IAR Systems AB.
//
//    Cpu mode     =  thumb
//    Endian       =  little
//    Source file  =  
//        E:\11��Freescale\Gold_Razor_A\Gold_Razor_A\project\Gold_Razor_A\app\Source\SequenceCtrl.c
//    Command line =  
//        E:\11��Freescale\Gold_Razor_A\Gold_Razor_A\project\Gold_Razor_A\app\Source\SequenceCtrl.c
//        -D LPLD_K60 -D USE_K60DZ10 -lCN
//        E:\11��Freescale\Gold_Razor_A\Gold_Razor_A\project\Gold_Razor_A\iar\FLASH\List\
//        -lB
//        E:\11��Freescale\Gold_Razor_A\Gold_Razor_A\project\Gold_Razor_A\iar\FLASH\List\
//        -o
//        E:\11��Freescale\Gold_Razor_A\Gold_Razor_A\project\Gold_Razor_A\iar\FLASH\Obj\
//        --no_cse --no_unroll --no_inline --no_code_motion --no_tbaa
//        --no_clustering --no_scheduling --debug --endian=little
//        --cpu=Cortex-M4 -e --fpu=None --dlib_config
//        D:\IAR\arm\INC\c\DLib_Config_Normal.h -I
//        E:\11��Freescale\Gold_Razor_A\Gold_Razor_A\project\Gold_Razor_A\iar\..\app\
//        -I
//        E:\11��Freescale\Gold_Razor_A\Gold_Razor_A\project\Gold_Razor_A\iar\..\app\Source\
//        -I
//        E:\11��Freescale\Gold_Razor_A\Gold_Razor_A\project\Gold_Razor_A\iar\..\..\..\lib\CPU\
//        -I
//        E:\11��Freescale\Gold_Razor_A\Gold_Razor_A\project\Gold_Razor_A\iar\..\..\..\lib\common\
//        -I
//        E:\11��Freescale\Gold_Razor_A\Gold_Razor_A\project\Gold_Razor_A\iar\..\..\..\lib\LPLD\
//        -I
//        E:\11��Freescale\Gold_Razor_A\Gold_Razor_A\project\Gold_Razor_A\iar\..\..\..\lib\LPLD\HW\
//        -I
//        E:\11��Freescale\Gold_Razor_A\Gold_Razor_A\project\Gold_Razor_A\iar\..\..\..\lib\LPLD\DEV\
//        -I
//        E:\11��Freescale\Gold_Razor_A\Gold_Razor_A\project\Gold_Razor_A\iar\..\..\..\lib\LPLD\FUNC\
//        -I
//        E:\11��Freescale\Gold_Razor_A\Gold_Razor_A\project\Gold_Razor_A\iar\..\..\..\lib\uCOS-II\Ports\
//        -I
//        E:\11��Freescale\Gold_Razor_A\Gold_Razor_A\project\Gold_Razor_A\iar\..\..\..\lib\uCOS-II\Source\
//        -I
//        E:\11��Freescale\Gold_Razor_A\Gold_Razor_A\project\Gold_Razor_A\iar\..\..\..\lib\FatFs\
//        -I
//        E:\11��Freescale\Gold_Razor_A\Gold_Razor_A\project\Gold_Razor_A\iar\..\..\..\lib\FatFs\option\
//        -I
//        E:\11��Freescale\Gold_Razor_A\Gold_Razor_A\project\Gold_Razor_A\iar\..\..\..\lib\USB\common\
//        -I
//        E:\11��Freescale\Gold_Razor_A\Gold_Razor_A\project\Gold_Razor_A\iar\..\..\..\lib\USB\driver\
//        -I
//        E:\11��Freescale\Gold_Razor_A\Gold_Razor_A\project\Gold_Razor_A\iar\..\..\..\lib\USB\descriptor\
//        -I
//        E:\11��Freescale\Gold_Razor_A\Gold_Razor_A\project\Gold_Razor_A\iar\..\..\..\lib\USB\class\
//        -Ol -I D:\IAR\arm\CMSIS\Include\ -D ARM_MATH_CM4
//    List file    =  
//        E:\11��Freescale\Gold_Razor_A\Gold_Razor_A\project\Gold_Razor_A\iar\FLASH\List\SequenceCtrl.s
//
///////////////////////////////////////////////////////////////////////////////

        #define SHT_PROGBITS 0x1

        EXTERN Encoder_GetPulseNum
        EXTERN Get_Img
        EXTERN Get_MidLine
        EXTERN LPLD_NVIC_Init
        EXTERN LPLD_PIT_EnableIrq
        EXTERN LPLD_PIT_Init
        EXTERN MidAve
        EXTERN OLED_ShowNum
        EXTERN OLED_ShowString
        EXTERN PWM_Expect
        EXTERN PWM_To_Pulse
        EXTERN Speed_Controller
        EXTERN Steer_Controller
        EXTERN __aeabi_d2f
        EXTERN __aeabi_ddiv
        EXTERN __aeabi_i2d
        EXTERN __aeabi_i2f
        EXTERN __aeabi_memcpy4
        EXTERN speedCtrler
        EXTERN steerCtrler

        PUBLIC First_Process
        PUBLIC MainCtrl_Pit_Init
        PUBLIC Main_Isr
        PUBLIC NVIC_Init
        PUBLIC Second_Process
        PUBLIC Third_Process
        PUBLIC pitCounter

// E:\11��Freescale\Gold_Razor_A\Gold_Razor_A\project\Gold_Razor_A\app\Source\SequenceCtrl.c
//    1 /*
//    2 *该代码提供时中断优先级初始化函数
//    3 *提供时序控制初始化和核心控制函数
//    4 */
//    5 
//    6 #include "SequenceCtrl.h"
//    7 #include "ImgProcess.h"
//    8 #include "EncoderDriver.h"
//    9 #include "MotorDriver.h"
//   10 #include "SteerDriver.h"
//   11 #include "DebugerDriver.h"
//   12 #include "Oled.h"
//   13 #include "PID.h"
//   14 

        SECTION `.bss`:DATA:REORDER:NOROOT(0)
//   15 uint8 pitCounter=0; //时序控制变量
pitCounter:
        DS8 1
//   16 
//   17 /*     process functiong declare   */
//   18 void First_Process(void);
//   19 void Second_Process(void);
//   20 void Thrid_Process(void);
//   21 
//   22 /*时序控制PIT初始化*/
//   23 

        SECTION `.text`:CODE:NOROOT(1)
        THUMB
//   24 void MainCtrl_Pit_Init(void)
//   25 {
MainCtrl_Pit_Init:
        PUSH     {LR}
        SUB      SP,SP,#+28
//   26 
//   27 	PIT_InitTypeDef pit3_init_struct;
//   28 	//配置PIT3参数
//   29 	pit3_init_struct.PIT_Pitx = PIT3;
        MOVS     R0,#+3
        STRB     R0,[SP, #+4]
//   30 	pit3_init_struct.PIT_PeriodMs = 1;//定时周期
        MOVS     R0,#+1
        STR      R0,[SP, #+12]
//   31 	pit3_init_struct.PIT_PeriodUs = 0;
        MOVS     R0,#+0
        STR      R0,[SP, #+8]
//   32 	pit3_init_struct.PIT_PeriodS = 0;
        MOVS     R0,#+0
        STR      R0,[SP, #+16]
//   33 	pit3_init_struct.PIT_Isr = Main_Isr;  //设置中断函数
        ADR.W    R0,Main_Isr
        STR      R0,[SP, #+20]
//   34 	//初始化PIT3
//   35 	LPLD_PIT_Init(pit3_init_struct);
        ADD      R1,SP,#+4
        SUB      SP,SP,#+16
        MOV      R0,SP
        MOVS     R2,#+20
        BL       __aeabi_memcpy4
        POP      {R0-R3}
        BL       LPLD_PIT_Init
//   36 	LPLD_PIT_EnableIrq(pit3_init_struct);
        ADD      R1,SP,#+4
        SUB      SP,SP,#+16
        MOV      R0,SP
        MOVS     R2,#+20
        BL       __aeabi_memcpy4
        POP      {R0-R3}
        BL       LPLD_PIT_EnableIrq
//   37 }
        ADD      SP,SP,#+28
        POP      {PC}             ;; return
//   38 
//   39 
//   40 /*中断优先级初始化*/
//   41 

        SECTION `.text`:CODE:NOROOT(1)
        THUMB
//   42 void NVIC_Init(void)
//   43 {
NVIC_Init:
        PUSH     {LR}
        SUB      SP,SP,#+28
//   44 	NVIC_InitTypeDef nvic_init_struct;
//   45 
//   46 	//配置PIT3的NVIC分组
//   47 	nvic_init_struct.NVIC_IRQChannel = PIT3_IRQn;
        MOVS     R0,#+71
        STRB     R0,[SP, #+4]
//   48 	nvic_init_struct.NVIC_IRQChannelGroupPriority = NVIC_PriorityGroup_3;
        MOVS     R0,#+4
        STR      R0,[SP, #+8]
//   49 	nvic_init_struct.NVIC_IRQChannelPreemptionPriority = 3;
        MOVS     R0,#+3
        STR      R0,[SP, #+12]
//   50 	nvic_init_struct.NVIC_IRQChannelSubPriority = 1;
        MOVS     R0,#+1
        STR      R0,[SP, #+16]
//   51 	nvic_init_struct.NVIC_IRQChannelEnable = FALSE;
        MOVS     R0,#+0
        STRB     R0,[SP, #+20]
//   52 	LPLD_NVIC_Init(nvic_init_struct);
        ADD      R1,SP,#+4
        SUB      SP,SP,#+16
        MOV      R0,SP
        MOVS     R2,#+20
        BL       __aeabi_memcpy4
        POP      {R0-R3}
        BL       LPLD_NVIC_Init
//   53 	//配置Key_Isr的NVIC分组
//   54 	nvic_init_struct.NVIC_IRQChannel = PORTC_IRQn;
        MOVS     R0,#+89
        STRB     R0,[SP, #+4]
//   55 	nvic_init_struct.NVIC_IRQChannelGroupPriority = NVIC_PriorityGroup_3;
        MOVS     R0,#+4
        STR      R0,[SP, #+8]
//   56 	nvic_init_struct.NVIC_IRQChannelPreemptionPriority = 2;
        MOVS     R0,#+2
        STR      R0,[SP, #+12]
//   57 	nvic_init_struct.NVIC_IRQChannelSubPriority = 1;
        MOVS     R0,#+1
        STR      R0,[SP, #+16]
//   58 	nvic_init_struct.NVIC_IRQChannelEnable = FALSE;
        MOVS     R0,#+0
        STRB     R0,[SP, #+20]
//   59 	LPLD_NVIC_Init(nvic_init_struct);
        ADD      R1,SP,#+4
        SUB      SP,SP,#+16
        MOV      R0,SP
        MOVS     R2,#+20
        BL       __aeabi_memcpy4
        POP      {R0-R3}
        BL       LPLD_NVIC_Init
//   60 
//   61 	nvic_init_struct.NVIC_IRQChannel = PORTD_IRQn;
        MOVS     R0,#+90
        STRB     R0,[SP, #+4]
//   62 	nvic_init_struct.NVIC_IRQChannelGroupPriority = NVIC_PriorityGroup_3;
        MOVS     R0,#+4
        STR      R0,[SP, #+8]
//   63 	nvic_init_struct.NVIC_IRQChannelPreemptionPriority = 2;
        MOVS     R0,#+2
        STR      R0,[SP, #+12]
//   64 	nvic_init_struct.NVIC_IRQChannelSubPriority = 0;
        MOVS     R0,#+0
        STR      R0,[SP, #+16]
//   65 	nvic_init_struct.NVIC_IRQChannelEnable = FALSE;
        MOVS     R0,#+0
        STRB     R0,[SP, #+20]
//   66 	LPLD_NVIC_Init(nvic_init_struct);
        ADD      R1,SP,#+4
        SUB      SP,SP,#+16
        MOV      R0,SP
        MOVS     R2,#+20
        BL       __aeabi_memcpy4
        POP      {R0-R3}
        BL       LPLD_NVIC_Init
//   67 	//配置PORTA的NVIC分组
//   68 	nvic_init_struct.NVIC_IRQChannel = PORTA_IRQn;
        MOVS     R0,#+87
        STRB     R0,[SP, #+4]
//   69 	nvic_init_struct.NVIC_IRQChannelGroupPriority = NVIC_PriorityGroup_3;
        MOVS     R0,#+4
        STR      R0,[SP, #+8]
//   70 	nvic_init_struct.NVIC_IRQChannelPreemptionPriority = 1;
        MOVS     R0,#+1
        STR      R0,[SP, #+12]
//   71 	nvic_init_struct.NVIC_IRQChannelSubPriority = 1;
        MOVS     R0,#+1
        STR      R0,[SP, #+16]
//   72 	nvic_init_struct.NVIC_IRQChannelEnable = FALSE;
        MOVS     R0,#+0
        STRB     R0,[SP, #+20]
//   73 	LPLD_NVIC_Init(nvic_init_struct);
        ADD      R1,SP,#+4
        SUB      SP,SP,#+16
        MOV      R0,SP
        MOVS     R2,#+20
        BL       __aeabi_memcpy4
        POP      {R0-R3}
        BL       LPLD_NVIC_Init
//   74 	//配置DMA0的NVIC分组
//   75 	nvic_init_struct.NVIC_IRQChannel = DMA0_IRQn;
        MOVS     R0,#+0
        STRB     R0,[SP, #+4]
//   76 	nvic_init_struct.NVIC_IRQChannelGroupPriority = NVIC_PriorityGroup_3;
        MOVS     R0,#+4
        STR      R0,[SP, #+8]
//   77 	nvic_init_struct.NVIC_IRQChannelPreemptionPriority = 0;
        MOVS     R0,#+0
        STR      R0,[SP, #+12]
//   78 	nvic_init_struct.NVIC_IRQChannelSubPriority = 1;
        MOVS     R0,#+1
        STR      R0,[SP, #+16]
//   79 	nvic_init_struct.NVIC_IRQChannelEnable = FALSE;
        MOVS     R0,#+0
        STRB     R0,[SP, #+20]
//   80 	LPLD_NVIC_Init(nvic_init_struct);
        ADD      R1,SP,#+4
        SUB      SP,SP,#+16
        MOV      R0,SP
        MOVS     R2,#+20
        BL       __aeabi_memcpy4
        POP      {R0-R3}
        BL       LPLD_NVIC_Init
//   81 
//   82 }
        ADD      SP,SP,#+28
        POP      {PC}             ;; return
//   83 
//   84 /*时序控制核心函数*/
//   85 

        SECTION `.text`:CODE:NOROOT(2)
        THUMB
//   86 void Main_Isr(void)
//   87 {
Main_Isr:
        PUSH     {R7,LR}
//   88 	switch(++pitCounter)
        LDR.N    R0,??DataTable2
        LDRB     R0,[R0, #+0]
        ADDS     R0,R0,#+1
        LDR.N    R1,??DataTable2
        STRB     R0,[R1, #+0]
        LDR.N    R0,??DataTable2
        LDRB     R0,[R0, #+0]
        CMP      R0,#+1
        BEQ.N    ??Main_Isr_0
        CMP      R0,#+15
        BEQ.N    ??Main_Isr_1
        B.N      ??Main_Isr_2
//   89 	{
//   90 		case 1 : First_Process();break;
??Main_Isr_0:
        BL       First_Process
        B.N      ??Main_Isr_2
//   91 
//   92 		case 15 : Second_Process(); break;
??Main_Isr_1:
        BL       Second_Process
//   93 	}
//   94 }
??Main_Isr_2:
        POP      {R0,PC}          ;; return
//   95 
//   96 /*    process function prototype     */

        SECTION `.text`:CODE:NOROOT(1)
        THUMB
//   97 void First_Process(void)
//   98 {
First_Process:
        PUSH     {R7,LR}
//   99 	Get_Img();
        BL       Get_Img
//  100     //vcan_sendimg(imgbuff, CAMERA_SIZE);
//  101 	Get_MidLine();
        BL       Get_MidLine
//  102 	OLED_ShowString(0,0,"MidAve");
        LDR.N    R2,??DataTable2_1
        MOVS     R1,#+0
        MOVS     R0,#+0
        BL       OLED_ShowString
//  103 	OLED_ShowNum(70,0,MidAve,3);
        MOVS     R3,#+3
        LDR.N    R0,??DataTable2_2
        LDRSH    R2,[R0, #+0]
        MOVS     R1,#+0
        MOVS     R0,#+70
        BL       OLED_ShowNum
//  104 }
        POP      {R0,PC}          ;; return

        SECTION `.text`:CODE:NOROOT(1)
        THUMB
//  105 void Second_Process(void)
//  106 {
Second_Process:
        PUSH     {R4-R6,LR}
//  107 	int16 leftPulse, rightPulse;
//  108 
//  109 	pitCounter=0;
        MOVS     R0,#+0
        LDR.N    R1,??DataTable2
        STRB     R0,[R1, #+0]
//  110 
//  111 	leftPulse = Encoder_GetPulseNum(ENCODER_LEFT);
        MOVS     R0,#+0
        BL       Encoder_GetPulseNum
        MOVS     R5,R0
//  112 	rightPulse = Encoder_GetPulseNum(ENCODER_RIGHT);
        MOVS     R0,#+1
        BL       Encoder_GetPulseNum
        MOVS     R6,R0
//  113 
//  114 	if(leftPulse < 0)
        SXTH     R5,R5            ;; SignExt  R5,R5,#+16,#+16
        CMP      R5,#+0
        BPL.N    ??Second_Process_0
//  115 		rightPulse = -rightPulse;
        SXTH     R6,R6            ;; SignExt  R6,R6,#+16,#+16
        RSBS     R6,R6,#+0
//  116 
//  117 	Steer_Controller(steerCtrler , \ 
//  118 					 STEER_MIDVALUE , \ 
//  119 					 MidAve);
??Second_Process_0:
        LDR.N    R0,??DataTable2_2
        LDRSH    R0,[R0, #+0]
        BL       __aeabi_i2f
        MOVS     R2,R0
        LDR.N    R1,??DataTable2_3  ;; 0x42a00000
        LDR.N    R0,??DataTable2_4
        LDR      R0,[R0, #+0]
        BL       Steer_Controller
//  120 
//  121 	Speed_Controller(speedCtrler, \ 
//  122 					 PWM_To_Pulse(PWM_Expect), \ 
//  123 					 (leftPulse + rightPulse) / 2.0);
        LDR.N    R0,??DataTable2_5
        LDR      R0,[R0, #+0]
        BL       PWM_To_Pulse
        MOVS     R4,R0
        SXTH     R6,R6            ;; SignExt  R6,R6,#+16,#+16
        SXTAH    R0,R6,R5
        BL       __aeabi_i2d
        MOVS     R2,#+0
        MOVS     R3,#+1073741824
        BL       __aeabi_ddiv
        BL       __aeabi_d2f
        MOVS     R2,R0
        MOVS     R1,R4
        LDR.N    R0,??DataTable2_6
        LDR      R0,[R0, #+0]
        BL       Speed_Controller
//  124 }
        POP      {R4-R6,PC}       ;; return

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable2:
        DC32     pitCounter

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable2_1:
        DC32     ?_0

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable2_2:
        DC32     MidAve

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable2_3:
        DC32     0x42a00000

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable2_4:
        DC32     steerCtrler

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable2_5:
        DC32     PWM_Expect

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable2_6:
        DC32     speedCtrler

        SECTION `.text`:CODE:NOROOT(1)
        THUMB
//  125 void Third_Process(void)
//  126 {
//  127 
//  128 }
Third_Process:
        BX       LR               ;; return

        SECTION `.iar_vfe_header`:DATA:NOALLOC:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
        DC32 0

        SECTION __DLIB_PERTHREAD:DATA:REORDER:NOROOT(0)
        SECTION_TYPE SHT_PROGBITS, 0

        SECTION __DLIB_PERTHREAD_init:DATA:REORDER:NOROOT(0)
        SECTION_TYPE SHT_PROGBITS, 0

        SECTION `.rodata`:CONST:REORDER:NOROOT(2)
?_0:
        DATA
        DC8 "MidAve"
        DC8 0

        END
// 
//   1 byte  in section .bss
//   8 bytes in section .rodata
// 496 bytes in section .text
// 
// 496 bytes of CODE  memory
//   8 bytes of CONST memory
//   1 byte  of DATA  memory
//
//Errors: none
//Warnings: none
