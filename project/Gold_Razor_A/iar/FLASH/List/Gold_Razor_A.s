///////////////////////////////////////////////////////////////////////////////
//
// IAR ANSI C/C++ Compiler V7.40.3.8902/W32 for ARM       11/May/2016  19:33:34
// Copyright 1999-2015 IAR Systems AB.
//
//    Cpu mode     =  thumb
//    Endian       =  little
//    Source file  =  
//        E:\11ΩÏFreescale\Gold_Razor_A\Gold_Razor_A\project\Gold_Razor_A\app\Gold_Razor_A.c
//    Command line =  
//        E:\11ΩÏFreescale\Gold_Razor_A\Gold_Razor_A\project\Gold_Razor_A\app\Gold_Razor_A.c
//        -D LPLD_K60 -D USE_K60DZ10 -lCN
//        E:\11ΩÏFreescale\Gold_Razor_A\Gold_Razor_A\project\Gold_Razor_A\iar\FLASH\List\
//        -lB
//        E:\11ΩÏFreescale\Gold_Razor_A\Gold_Razor_A\project\Gold_Razor_A\iar\FLASH\List\
//        -o
//        E:\11ΩÏFreescale\Gold_Razor_A\Gold_Razor_A\project\Gold_Razor_A\iar\FLASH\Obj\
//        --no_cse --no_unroll --no_inline --no_code_motion --no_tbaa
//        --no_clustering --no_scheduling --debug --endian=little
//        --cpu=Cortex-M4 -e --fpu=None --dlib_config
//        D:\IAR\arm\INC\c\DLib_Config_Normal.h -I
//        E:\11ΩÏFreescale\Gold_Razor_A\Gold_Razor_A\project\Gold_Razor_A\iar\..\app\
//        -I
//        E:\11ΩÏFreescale\Gold_Razor_A\Gold_Razor_A\project\Gold_Razor_A\iar\..\app\Source\
//        -I
//        E:\11ΩÏFreescale\Gold_Razor_A\Gold_Razor_A\project\Gold_Razor_A\iar\..\..\..\lib\CPU\
//        -I
//        E:\11ΩÏFreescale\Gold_Razor_A\Gold_Razor_A\project\Gold_Razor_A\iar\..\..\..\lib\common\
//        -I
//        E:\11ΩÏFreescale\Gold_Razor_A\Gold_Razor_A\project\Gold_Razor_A\iar\..\..\..\lib\LPLD\
//        -I
//        E:\11ΩÏFreescale\Gold_Razor_A\Gold_Razor_A\project\Gold_Razor_A\iar\..\..\..\lib\LPLD\HW\
//        -I
//        E:\11ΩÏFreescale\Gold_Razor_A\Gold_Razor_A\project\Gold_Razor_A\iar\..\..\..\lib\LPLD\DEV\
//        -I
//        E:\11ΩÏFreescale\Gold_Razor_A\Gold_Razor_A\project\Gold_Razor_A\iar\..\..\..\lib\LPLD\FUNC\
//        -I
//        E:\11ΩÏFreescale\Gold_Razor_A\Gold_Razor_A\project\Gold_Razor_A\iar\..\..\..\lib\uCOS-II\Ports\
//        -I
//        E:\11ΩÏFreescale\Gold_Razor_A\Gold_Razor_A\project\Gold_Razor_A\iar\..\..\..\lib\uCOS-II\Source\
//        -I
//        E:\11ΩÏFreescale\Gold_Razor_A\Gold_Razor_A\project\Gold_Razor_A\iar\..\..\..\lib\FatFs\
//        -I
//        E:\11ΩÏFreescale\Gold_Razor_A\Gold_Razor_A\project\Gold_Razor_A\iar\..\..\..\lib\FatFs\option\
//        -I
//        E:\11ΩÏFreescale\Gold_Razor_A\Gold_Razor_A\project\Gold_Razor_A\iar\..\..\..\lib\USB\common\
//        -I
//        E:\11ΩÏFreescale\Gold_Razor_A\Gold_Razor_A\project\Gold_Razor_A\iar\..\..\..\lib\USB\driver\
//        -I
//        E:\11ΩÏFreescale\Gold_Razor_A\Gold_Razor_A\project\Gold_Razor_A\iar\..\..\..\lib\USB\descriptor\
//        -I
//        E:\11ΩÏFreescale\Gold_Razor_A\Gold_Razor_A\project\Gold_Razor_A\iar\..\..\..\lib\USB\class\
//        -Ol -I D:\IAR\arm\CMSIS\Include\ -D ARM_MATH_CM4
//    List file    =  
//        E:\11ΩÏFreescale\Gold_Razor_A\Gold_Razor_A\project\Gold_Razor_A\iar\FLASH\List\Gold_Razor_A.s
//
///////////////////////////////////////////////////////////////////////////////

        #define SHT_PROGBITS 0x1

        EXTERN Camera_init
        EXTERN DifferCtrler_Init
        EXTERN Encoder_Init
        EXTERN Keyboard_GPIO_Init
        EXTERN MainCtrl_Pit_Init
        EXTERN Menu_Data_Link
        EXTERN Menu_Show
        EXTERN Motor_Init
        EXTERN NVIC_Init
        EXTERN OLED_Clear
        EXTERN OLED_Init
        EXTERN SpeedCtrler_Init
        EXTERN SteerCtrler_Init
        EXTERN Steer_Init
        EXTERN UART_Debuger_Init

        PUBLIC main

// E:\11ΩÏFreescale\Gold_Razor_A\Gold_Razor_A\project\Gold_Razor_A\app\Gold_Razor_A.c
//    1 #include "Oled.h"
//    2 #include "SequenceCtrl.h"
//    3 #include "SteerDriver.h"
//    4 #include "MotorDriver.h"
//    5 #include "EncoderDriver.h"
//    6 #include "DebugerDriver.h"
//    7 #include "PID.h"
//    8 #include "Eagle_ov7725.h"
//    9 #include "Menu.h"
//   10 
//   11 /*     main function entrance    */
//   12 

        SECTION `.text`:CODE:NOROOT(1)
        THUMB
//   13 void main(void)
//   14 {
main:
        PUSH     {R7,LR}
//   15 	DisableInterrupts;
        CPSID    I
//   16 	OLED_Init();
        BL       OLED_Init
//   17 	OLED_Clear();
        BL       OLED_Clear
//   18 	NVIC_Init();
        BL       NVIC_Init
//   19 	MainCtrl_Pit_Init();
        BL       MainCtrl_Pit_Init
//   20 	Steer_Init();
        BL       Steer_Init
//   21 	Motor_Init();
        BL       Motor_Init
//   22 	Encoder_Init();
        BL       Encoder_Init
//   23 	Keyboard_GPIO_Init();
        BL       Keyboard_GPIO_Init
//   24 	UART_Debuger_Init();
        BL       UART_Debuger_Init
//   25 	SpeedCtrler_Init();
        BL       SpeedCtrler_Init
//   26 	SteerCtrler_Init();
        BL       SteerCtrler_Init
//   27 	DifferCtrler_Init();
        BL       DifferCtrler_Init
//   28 	Camera_init();
        BL       Camera_init
//   29 	Menu_Data_Link();
        BL       Menu_Data_Link
//   30 	Menu_Show();
        BL       Menu_Show
//   31 	EnableInterrupts;
        CPSIE    I
//   32 	while (1);
??main_0:
        B.N      ??main_0
//   33 }

        SECTION `.iar_vfe_header`:DATA:NOALLOC:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
        DC32 0

        SECTION __DLIB_PERTHREAD:DATA:REORDER:NOROOT(0)
        SECTION_TYPE SHT_PROGBITS, 0

        SECTION __DLIB_PERTHREAD_init:DATA:REORDER:NOROOT(0)
        SECTION_TYPE SHT_PROGBITS, 0

        END
//   34 
// 
// 68 bytes in section .text
// 
// 68 bytes of CODE memory
//
//Errors: none
//Warnings: none
