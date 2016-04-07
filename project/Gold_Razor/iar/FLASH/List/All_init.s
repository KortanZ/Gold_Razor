///////////////////////////////////////////////////////////////////////////////
//
// IAR ANSI C/C++ Compiler V7.40.3.8902/W32 for ARM       07/Apr/2016  16:08:35
// Copyright 1999-2015 IAR Systems AB.
//
//    Cpu mode     =  thumb
//    Endian       =  little
//    Source file  =  
//        E:\MCU\Freescale\K60\Gold_Razor\project\Gold_Razor\app\Source\All_init.c
//    Command line =  
//        E:\MCU\Freescale\K60\Gold_Razor\project\Gold_Razor\app\Source\All_init.c
//        -D LPLD_K60 -D USE_K60DZ10 -lCN
//        E:\MCU\Freescale\K60\Gold_Razor\project\Gold_Razor\iar\FLASH\List\
//        -lB
//        E:\MCU\Freescale\K60\Gold_Razor\project\Gold_Razor\iar\FLASH\List\ -o
//        E:\MCU\Freescale\K60\Gold_Razor\project\Gold_Razor\iar\FLASH\Obj\
//        --no_cse --no_unroll --no_inline --no_code_motion --no_tbaa
//        --no_clustering --no_scheduling --debug --endian=little
//        --cpu=Cortex-M4 -e --fpu=None --dlib_config
//        E:\MCU\Freescale\K60\IAR7.4\arm\INC\c\DLib_Config_Normal.h -I
//        E:\MCU\Freescale\K60\Gold_Razor\project\Gold_Razor\iar\..\app\ -I
//        E:\MCU\Freescale\K60\Gold_Razor\project\Gold_Razor\iar\..\app\Source\
//        -I
//        E:\MCU\Freescale\K60\Gold_Razor\project\Gold_Razor\iar\..\..\..\lib\CPU\
//        -I
//        E:\MCU\Freescale\K60\Gold_Razor\project\Gold_Razor\iar\..\..\..\lib\common\
//        -I
//        E:\MCU\Freescale\K60\Gold_Razor\project\Gold_Razor\iar\..\..\..\lib\LPLD\
//        -I
//        E:\MCU\Freescale\K60\Gold_Razor\project\Gold_Razor\iar\..\..\..\lib\LPLD\HW\
//        -I
//        E:\MCU\Freescale\K60\Gold_Razor\project\Gold_Razor\iar\..\..\..\lib\LPLD\DEV\
//        -I
//        E:\MCU\Freescale\K60\Gold_Razor\project\Gold_Razor\iar\..\..\..\lib\LPLD\FUNC\
//        -I
//        E:\MCU\Freescale\K60\Gold_Razor\project\Gold_Razor\iar\..\..\..\lib\uCOS-II\Ports\
//        -I
//        E:\MCU\Freescale\K60\Gold_Razor\project\Gold_Razor\iar\..\..\..\lib\uCOS-II\Source\
//        -I
//        E:\MCU\Freescale\K60\Gold_Razor\project\Gold_Razor\iar\..\..\..\lib\FatFs\
//        -I
//        E:\MCU\Freescale\K60\Gold_Razor\project\Gold_Razor\iar\..\..\..\lib\FatFs\option\
//        -I
//        E:\MCU\Freescale\K60\Gold_Razor\project\Gold_Razor\iar\..\..\..\lib\USB\common\
//        -I
//        E:\MCU\Freescale\K60\Gold_Razor\project\Gold_Razor\iar\..\..\..\lib\USB\driver\
//        -I
//        E:\MCU\Freescale\K60\Gold_Razor\project\Gold_Razor\iar\..\..\..\lib\USB\descriptor\
//        -I
//        E:\MCU\Freescale\K60\Gold_Razor\project\Gold_Razor\iar\..\..\..\lib\USB\class\
//        -Ol -I E:\MCU\Freescale\K60\IAR7.4\arm\CMSIS\Include\ -D ARM_MATH_CM4
//    List file    =  
//        E:\MCU\Freescale\K60\Gold_Razor\project\Gold_Razor\iar\FLASH\List\All_init.s
//
///////////////////////////////////////////////////////////////////////////////

        #define SHT_PROGBITS 0x1

        EXTERN Camera_init
        EXTERN Encoder_init
        EXTERN Motor_init
        EXTERN NVIC_init
        EXTERN OLED_Init
        EXTERN Steer_init
        EXTERN UART_init
        EXTERN pit_init

        PUBLIC All_init

// E:\MCU\Freescale\K60\Gold_Razor\project\Gold_Razor\app\Source\All_init.c
//    1 #include "All_init.h"
//    2 
//    3 
//    4 
//    5 

        SECTION `.text`:CODE:NOROOT(1)
        THUMB
//    6 void All_init(void)
//    7 {
All_init:
        PUSH     {R7,LR}
//    8   //GPIO_init();
//    9   NVIC_init();
        BL       NVIC_init
//   10   Motor_init();
        BL       Motor_init
//   11   Steer_init();
        BL       Steer_init
//   12   OLED_Init();
        BL       OLED_Init
//   13   Encoder_init();
        BL       Encoder_init
//   14   UART_init();
        BL       UART_init
//   15   pit_init();
        BL       pit_init
//   16   Camera_init();
        BL       Camera_init
//   17 }
        POP      {R0,PC}          ;; return

        SECTION `.iar_vfe_header`:DATA:NOALLOC:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
        DC32 0

        SECTION __DLIB_PERTHREAD:DATA:REORDER:NOROOT(0)
        SECTION_TYPE SHT_PROGBITS, 0

        SECTION __DLIB_PERTHREAD_init:DATA:REORDER:NOROOT(0)
        SECTION_TYPE SHT_PROGBITS, 0

        END
//   18 
// 
// 36 bytes in section .text
// 
// 36 bytes of CODE memory
//
//Errors: none
//Warnings: none
