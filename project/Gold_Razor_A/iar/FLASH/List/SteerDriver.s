///////////////////////////////////////////////////////////////////////////////
//
// IAR ANSI C/C++ Compiler V7.40.3.8902/W32 for ARM       09/May/2016  19:05:03
// Copyright 1999-2015 IAR Systems AB.
//
//    Cpu mode     =  thumb
//    Endian       =  little
//    Source file  =  
//        C:\Users\Administrator\Desktop\Gold_Razor_A\project\Gold_Razor_A\app\Source\SteerDriver.c
//    Command line =  
//        C:\Users\Administrator\Desktop\Gold_Razor_A\project\Gold_Razor_A\app\Source\SteerDriver.c
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
//        C:\Users\Administrator\Desktop\Gold_Razor_A\project\Gold_Razor_A\iar\FLASH\List\SteerDriver.s
//
///////////////////////////////////////////////////////////////////////////////

        #define SHT_PROGBITS 0x1

        EXTERN LPLD_FTM_Init
        EXTERN LPLD_FTM_PWM_ChangeDuty
        EXTERN LPLD_FTM_PWM_Enable
        EXTERN __aeabi_memcpy4

        PUBLIC Steer_Duty_Change
        PUBLIC Steer_Init

// C:\Users\Administrator\Desktop\Gold_Razor_A\project\Gold_Razor_A\app\Source\SteerDriver.c
//    1 /* 
//    2 *This file for steer driver
//    3 *include initial and control
//    4 */
//    5 #include "SteerDriver.h"

        SECTION `.text`:CODE:NOROOT(1)
        THUMB
//    6 void Steer_Init(void)
//    7 {
Steer_Init:
        PUSH     {LR}
        SUB      SP,SP,#+44
//    8 
//    9 	FTM_InitTypeDef steerInitStruct;
//   10 
//   11     steerInitStruct.FTM_Ftmx = FTM2;
        LDR.N    R0,??DataTable1  ;; 0x400b8000
        STR      R0,[SP, #+12]
//   12     steerInitStruct.FTM_Mode = FTM_MODE_PWM;
        MOVS     R0,#+1
        STRB     R0,[SP, #+16]
//   13     steerInitStruct.FTM_PwmFreq = 100;
        MOVS     R0,#+100
        STR      R0,[SP, #+20]
//   14     steerInitStruct.FTM_PwmDeadtimeCfg = DEADTIME_CH01;
        MOVS     R0,#+16
        STR      R0,[SP, #+24]
//   15     steerInitStruct.FTM_PwmDeadtimeDiv = DEADTIME_DIV1;
        MOVS     R0,#+0
        STRB     R0,[SP, #+28]
//   16     steerInitStruct.FTM_PwmDeadtimeVal = 0;
        MOVS     R0,#+0
        STRB     R0,[SP, #+29]
//   17 
//   18     LPLD_FTM_Init(steerInitStruct);
        ADD      R1,SP,#+12
        SUB      SP,SP,#+16
        MOV      R0,SP
        MOVS     R2,#+28
        BL       __aeabi_memcpy4
        POP      {R0-R3}
        BL       LPLD_FTM_Init
//   19 
//   20     LPLD_FTM_PWM_Enable(FTM2, //使用FTM2
//   21                         FTM_Ch0, //使能Ch0通道
//   22                         STEER_MID_DUTY, //初始化角度0度  100HZ为1432  MAX=1570,Min=1250
//   23                         PTA10, //使用Ch0通道的PTD0引脚
//   24                         ALIGN_LEFT        //脉宽左对齐
//   25                         );
        MOVS     R0,#+40
        STR      R0,[SP, #+0]
        MOVS     R3,#+10
        MOVW     R2,#+1420
        MOVS     R1,#+0
        LDR.N    R0,??DataTable1  ;; 0x400b8000
        BL       LPLD_FTM_PWM_Enable
//   26 }
        ADD      SP,SP,#+44
        POP      {PC}             ;; return
//   27 

        SECTION `.text`:CODE:NOROOT(1)
        THUMB
//   28 void Steer_Duty_Change(uint32 tagetDuty)
//   29 {
Steer_Duty_Change:
        PUSH     {R7,LR}
//   30 	if(tagetDuty < STEER_LEFT_DUTY)
        CMP      R0,#+1224
        BHI.N    ??Steer_Duty_Change_0
//   31     {
//   32         tagetDuty = STEER_LEFT_DUTY;
        MOVW     R0,#+1225
        B.N      ??Steer_Duty_Change_1
//   33     }
//   34     else if(tagetDuty > STEER_RIGHT_DUTY)
??Steer_Duty_Change_0:
        CMP      R0,#+1560
        BLS.N    ??Steer_Duty_Change_1
//   35     {
//   36         tagetDuty = STEER_RIGHT_DUTY;
        MOV      R0,#+1560
//   37     }
//   38     LPLD_FTM_PWM_ChangeDuty(FTM2, FTM_Ch0, tagetDuty);
??Steer_Duty_Change_1:
        MOVS     R2,R0
        MOVS     R1,#+0
        LDR.N    R0,??DataTable1  ;; 0x400b8000
        BL       LPLD_FTM_PWM_ChangeDuty
//   39 }
        POP      {R0,PC}          ;; return

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable1:
        DC32     0x400b8000

        SECTION `.iar_vfe_header`:DATA:NOALLOC:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
        DC32 0

        SECTION __DLIB_PERTHREAD:DATA:REORDER:NOROOT(0)
        SECTION_TYPE SHT_PROGBITS, 0

        SECTION __DLIB_PERTHREAD_init:DATA:REORDER:NOROOT(0)
        SECTION_TYPE SHT_PROGBITS, 0

        END
// 
// 114 bytes in section .text
// 
// 114 bytes of CODE memory
//
//Errors: none
//Warnings: none
