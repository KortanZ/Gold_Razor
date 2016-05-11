///////////////////////////////////////////////////////////////////////////////
//
// IAR ANSI C/C++ Compiler V7.40.3.8902/W32 for ARM       11/May/2016  19:10:53
// Copyright 1999-2015 IAR Systems AB.
//
//    Cpu mode     =  thumb
//    Endian       =  little
//    Source file  =  
//        E:\11届Freescale\Gold_Razor_A\Gold_Razor_A\project\Gold_Razor_A\app\Source\oled.c
//    Command line =  
//        E:\11届Freescale\Gold_Razor_A\Gold_Razor_A\project\Gold_Razor_A\app\Source\oled.c
//        -D LPLD_K60 -D USE_K60DZ10 -lCN
//        E:\11届Freescale\Gold_Razor_A\Gold_Razor_A\project\Gold_Razor_A\iar\FLASH\List\
//        -lB
//        E:\11届Freescale\Gold_Razor_A\Gold_Razor_A\project\Gold_Razor_A\iar\FLASH\List\
//        -o
//        E:\11届Freescale\Gold_Razor_A\Gold_Razor_A\project\Gold_Razor_A\iar\FLASH\Obj\
//        --no_cse --no_unroll --no_inline --no_code_motion --no_tbaa
//        --no_clustering --no_scheduling --debug --endian=little
//        --cpu=Cortex-M4 -e --fpu=None --dlib_config
//        D:\IAR\arm\INC\c\DLib_Config_Normal.h -I
//        E:\11届Freescale\Gold_Razor_A\Gold_Razor_A\project\Gold_Razor_A\iar\..\app\
//        -I
//        E:\11届Freescale\Gold_Razor_A\Gold_Razor_A\project\Gold_Razor_A\iar\..\app\Source\
//        -I
//        E:\11届Freescale\Gold_Razor_A\Gold_Razor_A\project\Gold_Razor_A\iar\..\..\..\lib\CPU\
//        -I
//        E:\11届Freescale\Gold_Razor_A\Gold_Razor_A\project\Gold_Razor_A\iar\..\..\..\lib\common\
//        -I
//        E:\11届Freescale\Gold_Razor_A\Gold_Razor_A\project\Gold_Razor_A\iar\..\..\..\lib\LPLD\
//        -I
//        E:\11届Freescale\Gold_Razor_A\Gold_Razor_A\project\Gold_Razor_A\iar\..\..\..\lib\LPLD\HW\
//        -I
//        E:\11届Freescale\Gold_Razor_A\Gold_Razor_A\project\Gold_Razor_A\iar\..\..\..\lib\LPLD\DEV\
//        -I
//        E:\11届Freescale\Gold_Razor_A\Gold_Razor_A\project\Gold_Razor_A\iar\..\..\..\lib\LPLD\FUNC\
//        -I
//        E:\11届Freescale\Gold_Razor_A\Gold_Razor_A\project\Gold_Razor_A\iar\..\..\..\lib\uCOS-II\Ports\
//        -I
//        E:\11届Freescale\Gold_Razor_A\Gold_Razor_A\project\Gold_Razor_A\iar\..\..\..\lib\uCOS-II\Source\
//        -I
//        E:\11届Freescale\Gold_Razor_A\Gold_Razor_A\project\Gold_Razor_A\iar\..\..\..\lib\FatFs\
//        -I
//        E:\11届Freescale\Gold_Razor_A\Gold_Razor_A\project\Gold_Razor_A\iar\..\..\..\lib\FatFs\option\
//        -I
//        E:\11届Freescale\Gold_Razor_A\Gold_Razor_A\project\Gold_Razor_A\iar\..\..\..\lib\USB\common\
//        -I
//        E:\11届Freescale\Gold_Razor_A\Gold_Razor_A\project\Gold_Razor_A\iar\..\..\..\lib\USB\driver\
//        -I
//        E:\11届Freescale\Gold_Razor_A\Gold_Razor_A\project\Gold_Razor_A\iar\..\..\..\lib\USB\descriptor\
//        -I
//        E:\11届Freescale\Gold_Razor_A\Gold_Razor_A\project\Gold_Razor_A\iar\..\..\..\lib\USB\class\
//        -Ol -I D:\IAR\arm\CMSIS\Include\ -D ARM_MATH_CM4
//    List file    =  
//        E:\11届Freescale\Gold_Razor_A\Gold_Razor_A\project\Gold_Razor_A\iar\FLASH\List\oled.s
//
///////////////////////////////////////////////////////////////////////////////

        #define SHT_PROGBITS 0x1

        EXTERN LPLD_GPIO_Init
        EXTERN LPLD_GPIO_Output_b
        EXTERN __aeabi_memcpy4

        PUBLIC F6x8
        PUBLIC F8X16
        PUBLIC OLED_Clear
        PUBLIC OLED_ClearLine
        PUBLIC OLED_Display_Off
        PUBLIC OLED_Display_On
        PUBLIC OLED_DrawBMP
        PUBLIC OLED_DrawPoint
        PUBLIC OLED_Init
        PUBLIC OLED_NumClear
        PUBLIC OLED_PinInit
        PUBLIC OLED_Set_Pos
        PUBLIC OLED_ShowChar
        PUBLIC OLED_ShowNum
        PUBLIC OLED_ShowString
        PUBLIC OLED_WR_Byte
        PUBLIC delay_ms
        PUBLIC oled_pow

// E:\11届Freescale\Gold_Razor_A\Gold_Razor_A\project\Gold_Razor_A\app\Source\oled.c
//    1 //////////////////////////////////////////////////////////////////////////////////
//    2 //本程序只供学习使用，未经作者许可，不得用于其它任何用途
//    3 //中景园电子
//    4 //店铺地址：http://shop73023976.taobao.com/?spm=2013.1.0.0.M4PqC2
//    5 //
//    6 //  文 件 名   : main.c
//    7 //  版 本 号   : v2.0
//    8 //  作    者   : HuangKai
//    9 //  生成日期   : 2014-0101
//   10 //  最近修改   :
//   11 //  功能描述   : OLED 4接口演示例程(51系列)
//   12 //              说明:
//   13 //              ----------------------------------------------------------------
//   14 //              GND    电源地
//   15 //              VCC  接5V或3.3v电源
//   16 //              D0   P1^0（SCL）
//   17 //              D1   P1^1（SDA）
//   18 //              RES  接P12
//   19 //              DC   接P13
//   20 //              CS   接P14
//   21 //              ----------------------------------------------------------------
//   22 // 修改历史   :
//   23 // 日    期   :
//   24 // 作    者   : HuangKai
//   25 // 修改内容   : 创建文件
//   26 //版权所有，盗版必究。
//   27 //Copyright(C) 中景园电子2014/3/16
//   28 //All rights reserved
//   29 //******************************************************************************/。
//   30 #include "oled.h"
//   31 //#include "stdlib.h"
//   32 #include "oledfont.h"

        SECTION `.rodata`:CONST:REORDER:NOROOT(2)
// __absolute unsigned char const F6x8[92][6]
F6x8:
        DATA
        DC8 0, 0, 0, 0, 0, 0, 0, 0, 0, 47, 0, 0, 0, 0, 7, 0, 7, 0, 0, 20, 127
        DC8 20, 127, 20, 0, 36, 42, 127, 42, 18, 0, 98, 100, 8, 19, 35, 0, 54
        DC8 73, 85, 34, 80, 0, 0, 5, 3, 0, 0, 0, 0, 28, 34, 65, 0, 0, 0, 65, 34
        DC8 28, 0, 0, 20, 8, 62, 8, 20, 0, 8, 8, 62, 8, 8, 0, 0, 0, 160, 96, 0
        DC8 0, 8, 8, 8, 8, 8, 0, 0, 96, 96, 0, 0, 0, 32, 16, 8, 4, 2, 0, 62, 81
        DC8 73, 69, 62, 0, 0, 66, 127, 64, 0, 0, 66, 97, 81, 73, 70, 0, 33, 65
        DC8 69, 75, 49, 0, 24, 20, 18, 127, 16, 0, 39, 69, 69, 69, 57, 0, 60
        DC8 74, 73, 73, 48, 0, 1, 113, 9, 5, 3, 0, 54, 73, 73, 73, 54, 0, 6, 73
        DC8 73, 41, 30, 0, 0, 54, 54, 0, 0, 0, 0, 86, 54, 0, 0, 0, 8, 20, 34
        DC8 65, 0, 0, 20, 20, 20, 20, 20, 0, 0, 65, 34, 20, 8, 0, 2, 1, 81, 9
        DC8 6, 0, 50, 73, 89, 81, 62, 0, 124, 18, 17, 18, 124, 0, 127, 73, 73
        DC8 73, 54, 0, 62, 65, 65, 65, 34, 0, 127, 65, 65, 34, 28, 0, 127, 73
        DC8 73, 73, 65, 0, 127, 9, 9, 9, 1, 0, 62, 65, 73, 73, 122, 0, 127, 8
        DC8 8, 8, 127, 0, 0, 65, 127, 65, 0, 0, 32, 64, 65, 63, 1, 0, 127, 8
        DC8 20, 34, 65, 0, 127, 64, 64, 64, 64, 0, 127, 2, 12, 2, 127, 0, 127
        DC8 4, 8, 16, 127, 0, 62, 65, 65, 65, 62, 0, 127, 9, 9, 9, 6, 0, 62, 65
        DC8 81, 33, 94, 0, 127, 9, 25, 41, 70, 0, 70, 73, 73, 73, 49, 0, 1, 1
        DC8 127, 1, 1, 0, 63, 64, 64, 64, 63, 0, 31, 32, 64, 32, 31, 0, 63, 64
        DC8 56, 64, 63, 0, 99, 20, 8, 20, 99, 0, 7, 8, 112, 8, 7, 0, 97, 81, 73
        DC8 69, 67, 0, 0, 127, 65, 65, 0, 0, 85, 42, 85, 42, 85, 0, 0, 65, 65
        DC8 127, 0, 0, 4, 2, 1, 2, 4, 0, 64, 64, 64, 64, 64, 0, 0, 1, 2, 4, 0
        DC8 0, 32, 84, 84, 84, 120, 0, 127, 72, 68, 68, 56, 0, 56, 68, 68, 68
        DC8 32, 0, 56, 68, 68, 72, 127, 0, 56, 84, 84, 84, 24, 0, 8, 126, 9, 1
        DC8 2, 0, 24, 164, 164, 164, 124, 0, 127, 8, 4, 4, 120, 0, 0, 68, 125
        DC8 64, 0, 0, 64, 128, 132, 125, 0, 0, 127, 16, 40, 68, 0, 0, 0, 65
        DC8 127, 64, 0, 0, 124, 4, 24, 4, 120, 0, 124, 8, 4, 4, 120, 0, 56, 68
        DC8 68, 68, 56, 0, 252, 36, 36, 36, 24, 0, 24, 36, 36, 24, 252, 0, 124
        DC8 8, 4, 4, 8, 0, 72, 84, 84, 84, 32, 0, 4, 63, 68, 64, 32, 0, 60, 64
        DC8 64, 32, 124, 0, 28, 32, 64, 32, 28, 0, 60, 64, 48, 64, 60, 0, 68
        DC8 40, 16, 40, 68, 0, 28, 160, 160, 160, 124, 0, 68, 100, 84, 76, 68
        DC8 20, 20, 20, 20, 20, 20

        SECTION `.rodata`:CONST:REORDER:NOROOT(2)
// __absolute unsigned char const F8X16[1520]
F8X16:
        DATA
        DC8 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 248, 0, 0
        DC8 0, 0, 0, 0, 0, 51, 48, 0, 0, 0, 0, 16, 12, 6, 16, 12, 6, 0, 0, 0, 0
        DC8 0, 0, 0, 0, 0, 64, 192, 120, 64, 192, 120, 64, 0, 4, 63, 4, 4, 63
        DC8 4, 4, 0, 0, 112, 136, 252, 8, 48, 0, 0, 0, 24, 32, 255, 33, 30, 0
        DC8 0, 240, 8, 240, 0, 224, 24, 0, 0, 0, 33, 28, 3, 30, 33, 30, 0, 0
        DC8 240, 8, 136, 112, 0, 0, 0, 30, 33, 35, 36, 25, 39, 33, 16, 16, 22
        DC8 14, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 224, 24, 4, 2
        DC8 0, 0, 0, 0, 7, 24, 32, 64, 0, 0, 2, 4, 24, 224, 0, 0, 0, 0, 64, 32
        DC8 24, 7, 0, 0, 0, 64, 64, 128, 240, 128, 64, 64, 0, 2, 2, 1, 15, 1, 2
        DC8 2, 0, 0, 0, 0, 240, 0, 0, 0, 0, 1, 1, 1, 31, 1, 1, 1, 0, 0, 0, 0, 0
        DC8 0, 0, 0, 0, 128, 176, 112, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        DC8 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 48, 48, 0, 0, 0, 0
        DC8 0, 0, 0, 0, 0, 128, 96, 24, 4, 0, 96, 24, 6, 1, 0, 0, 0, 0, 224, 16
        DC8 8, 8, 16, 224, 0, 0, 15, 16, 32, 32, 16, 15, 0, 0, 16, 16, 248, 0
        DC8 0, 0, 0, 0, 32, 32, 63, 32, 32, 0, 0, 0, 112, 8, 8, 8, 136, 112, 0
        DC8 0, 48, 40, 36, 34, 33, 48, 0, 0, 48, 8, 136, 136, 72, 48, 0, 0, 24
        DC8 32, 32, 32, 17, 14, 0, 0, 0, 192, 32, 16, 248, 0, 0, 0, 7, 4, 36
        DC8 36, 63, 36, 0, 0, 248, 8, 136, 136, 8, 8, 0, 0, 25, 33, 32, 32, 17
        DC8 14, 0, 0, 224, 16, 136, 136, 24, 0, 0, 0, 15, 17, 32, 32, 17, 14, 0
        DC8 0, 56, 8, 8, 200, 56, 8, 0, 0, 0, 0, 63, 0, 0, 0, 0, 0, 112, 136, 8
        DC8 8, 136, 112, 0, 0, 28, 34, 33, 33, 34, 28, 0, 0, 224, 16, 8, 8, 16
        DC8 224, 0, 0, 0, 49, 34, 34, 17, 15, 0, 0, 0, 0, 192, 192, 0, 0, 0, 0
        DC8 0, 0, 48, 48, 0, 0, 0, 0, 0, 0, 128, 0, 0, 0, 0, 0, 0, 128, 96, 0
        DC8 0, 0, 0, 0, 0, 128, 64, 32, 16, 8, 0, 0, 1, 2, 4, 8, 16, 32, 0, 64
        DC8 64, 64, 64, 64, 64, 64, 0, 4, 4, 4, 4, 4, 4, 4, 0, 0, 8, 16, 32, 64
        DC8 128, 0, 0, 0, 32, 16, 8, 4, 2, 1, 0, 0, 112, 72, 8, 8, 8, 240, 0, 0
        DC8 0, 0, 48, 54, 1, 0, 0, 192, 48, 200, 40, 232, 16, 224, 0, 7, 24, 39
        DC8 36, 35, 20, 11, 0, 0, 0, 192, 56, 224, 0, 0, 0, 32, 60, 35, 2, 2
        DC8 39, 56, 32, 8, 248, 136, 136, 136, 112, 0, 0, 32, 63, 32, 32, 32
        DC8 17, 14, 0, 192, 48, 8, 8, 8, 8, 56, 0, 7, 24, 32, 32, 32, 16, 8, 0
        DC8 8, 248, 8, 8, 8, 16, 224, 0, 32, 63, 32, 32, 32, 16, 15, 0, 8, 248
        DC8 136, 136, 232, 8, 16, 0, 32, 63, 32, 32, 35, 32, 24, 0, 8, 248, 136
        DC8 136, 232, 8, 16, 0, 32, 63, 32, 0, 3, 0, 0, 0, 192, 48, 8, 8, 8, 56
        DC8 0, 0, 7, 24, 32, 32, 34, 30, 2, 0, 8, 248, 8, 0, 0, 8, 248, 8, 32
        DC8 63, 33, 1, 1, 33, 63, 32, 0, 8, 8, 248, 8, 8, 0, 0, 0, 32, 32, 63
        DC8 32, 32, 0, 0, 0, 0, 8, 8, 248, 8, 8, 0, 192, 128, 128, 128, 127, 0
        DC8 0, 0, 8, 248, 136, 192, 40, 24, 8, 0, 32, 63, 32, 1, 38, 56, 32, 0
        DC8 8, 248, 8, 0, 0, 0, 0, 0, 32, 63, 32, 32, 32, 32, 48, 0, 8, 248
        DC8 248, 0, 248, 248, 8, 0, 32, 63, 0, 63, 0, 63, 32, 0, 8, 248, 48
        DC8 192, 0, 8, 248, 8, 32, 63, 32, 0, 7, 24, 63, 0, 224, 16, 8, 8, 8
        DC8 16, 224, 0, 15, 16, 32, 32, 32, 16, 15, 0, 8, 248, 8, 8, 8, 8, 240
        DC8 0, 32, 63, 33, 1, 1, 1, 0, 0, 224, 16, 8, 8, 8, 16, 224, 0, 15, 24
        DC8 36, 36, 56, 80, 79, 0, 8, 248, 136, 136, 136, 136, 112, 0, 32, 63
        DC8 32, 0, 3, 12, 48, 32, 0, 112, 136, 8, 8, 8, 56, 0, 0, 56, 32, 33
        DC8 33, 34, 28, 0, 24, 8, 8, 248, 8, 8, 24, 0, 0, 0, 32, 63, 32, 0, 0
        DC8 0, 8, 248, 8, 0, 0, 8, 248, 8, 0, 31, 32, 32, 32, 32, 31, 0, 8, 120
        DC8 136, 0, 0, 200, 56, 8, 0, 0, 7, 56, 14, 1, 0, 0, 248, 8, 0, 248, 0
        DC8 8, 248, 0, 3, 60, 7, 0, 7, 60, 3, 0, 8, 24, 104, 128, 128, 104, 24
        DC8 8, 32, 48, 44, 3, 3, 44, 48, 32, 8, 56, 200, 0, 200, 56, 8, 0, 0, 0
        DC8 32, 63, 32, 0, 0, 0, 16, 8, 8, 8, 200, 56, 8, 0, 32, 56, 38, 33, 32
        DC8 32, 24, 0, 0, 0, 0, 254, 2, 2, 2, 0, 0, 0, 0, 127, 64, 64, 64, 0, 0
        DC8 12, 48, 192, 0, 0, 0, 0, 0, 0, 0, 1, 6, 56, 192, 0, 0, 2, 2, 2, 254
        DC8 0, 0, 0, 0, 64, 64, 64, 127, 0, 0, 0, 0, 0, 4, 2, 2, 2, 4, 0, 0, 0
        DC8 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 128, 128, 128, 128, 128
        DC8 128, 128, 128, 0, 2, 2, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        DC8 128, 128, 128, 128, 0, 0, 0, 25, 36, 34, 34, 34, 63, 32, 8, 248, 0
        DC8 128, 128, 0, 0, 0, 0, 63, 17, 32, 32, 17, 14, 0, 0, 0, 0, 128, 128
        DC8 128, 0, 0, 0, 14, 17, 32, 32, 32, 17, 0, 0, 0, 0, 128, 128, 136
        DC8 248, 0, 0, 14, 17, 32, 32, 16, 63, 32, 0, 0, 128, 128, 128, 128, 0
        DC8 0, 0, 31, 34, 34, 34, 34, 19, 0, 0, 128, 128, 240, 136, 136, 136
        DC8 24, 0, 32, 32, 63, 32, 32, 0, 0, 0, 0, 128, 128, 128, 128, 128, 0
        DC8 0, 107, 148, 148, 148, 147, 96, 0, 8, 248, 0, 128, 128, 128, 0, 0
        DC8 32, 63, 33, 0, 0, 32, 63, 32, 0, 128, 152, 152, 0, 0, 0, 0, 0, 32
        DC8 32, 63, 32, 32, 0, 0, 0, 0, 0, 128, 152, 152, 0, 0, 0, 192, 128
        DC8 128, 128, 127, 0, 0, 8, 248, 0, 0, 128, 128, 128, 0, 32, 63, 36, 2
        DC8 45, 48, 32, 0, 0, 8, 8, 248, 0, 0, 0, 0, 0, 32, 32, 63, 32, 32, 0
        DC8 0, 128, 128, 128, 128, 128, 128, 128, 0, 32, 63, 32, 0, 63, 32, 0
        DC8 63, 128, 128, 0, 128, 128, 128, 0, 0, 32, 63, 33, 0, 0, 32, 63, 32
        DC8 0, 0, 128, 128, 128, 128, 0, 0, 0, 31, 32, 32, 32, 32, 31, 0, 128
        DC8 128, 0, 128, 128, 0, 0, 0, 128, 255, 161, 32, 32, 17, 14, 0, 0, 0
        DC8 0, 128, 128, 128, 128, 0, 0, 14, 17, 32, 32, 160, 255, 128, 128
        DC8 128, 128, 0, 128, 128, 128, 0, 32, 32, 63, 33, 32, 0, 1, 0, 0, 0
        DC8 128, 128, 128, 128, 128, 0, 0, 51, 36, 36, 36, 36, 25, 0, 0, 128
        DC8 128, 224, 128, 128, 0, 0, 0, 0, 0, 31, 32, 32, 0, 0, 128, 128, 0, 0
        DC8 0, 128, 128, 0, 0, 31, 32, 32, 32, 16, 63, 32, 128, 128, 128, 0, 0
        DC8 128, 128, 128, 0, 1, 14, 48, 8, 6, 1, 0, 128, 128, 0, 128, 0, 128
        DC8 128, 128, 15, 48, 12, 3, 12, 48, 15, 0, 0, 128, 128, 0, 128, 128
        DC8 128, 0, 0, 32, 49, 46, 14, 49, 32, 0, 128, 128, 128, 0, 0, 128, 128
        DC8 128, 128, 129, 142, 112, 24, 6, 1, 0, 0, 128, 128, 128, 128, 128
        DC8 128, 0, 0, 33, 48, 44, 34, 33, 48, 0, 0, 0, 0, 0, 128, 124, 2, 2, 0
        DC8 0, 0, 0, 0, 63, 64, 64, 0, 0, 0, 0, 255, 0, 0, 0, 0, 0, 0, 0, 255
        DC8 0, 0, 0, 0, 2, 2, 124, 128, 0, 0, 0, 0, 64, 64, 63, 0, 0, 0, 0, 0
        DC8 6, 1, 1, 2, 2, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0
//   33 //#include "delay.h"
//   34 //OLED的显存
//   35 //存放格式如下.
//   36 //[0]0 1 2 3 ... 127
//   37 //[1]0 1 2 3 ... 127
//   38 //[2]0 1 2 3 ... 127
//   39 //[3]0 1 2 3 ... 127
//   40 //[4]0 1 2 3 ... 127
//   41 //[5]0 1 2 3 ... 127
//   42 //[6]0 1 2 3 ... 127
//   43 //[7]0 1 2 3 ... 127

        SECTION `.text`:CODE:NOROOT(1)
        THUMB
//   44 void delay_ms(unsigned int ms)
//   45 {
delay_ms:
        B.N      ??delay_ms_0
//   46 	unsigned int a;
//   47 	while (ms)
//   48 	{
//   49 		a = 1800;
??delay_ms_1:
        MOV      R1,#+1800
//   50 		while (a--);
??delay_ms_2:
        MOVS     R2,R1
        SUBS     R1,R2,#+1
        CMP      R2,#+0
        BNE.N    ??delay_ms_2
//   51 		ms--;
        SUBS     R0,R0,#+1
//   52 	}
??delay_ms_0:
        CMP      R0,#+0
        BNE.N    ??delay_ms_1
//   53 	return;
        BX       LR               ;; return
//   54 }
//   55 #if OLED_MODE==1
//   56 //向SSD1106写入一个字节。
//   57 //dat:要写入的数据/命令
//   58 //cmd:数据/命令标志 0,表示命令;1,表示数据;
//   59 void OLED_WR_Byte(u8 dat, u8 cmd)
//   60 {
//   61 	DATAOUT(dat);
//   62 	if (cmd)
//   63 		OLED_DC_Set();
//   64 	else
//   65 		OLED_DC_Clr();
//   66 	OLED_CS_Clr();
//   67 	OLED_WR_Clr();
//   68 	OLED_WR_Set();
//   69 	OLED_CS_Set();
//   70 	OLED_DC_Set();
//   71 }
//   72 #else
//   73 //向SSD1306写入一个字节。
//   74 //dat:要写入的数据/命令
//   75 //cmd:数据/命令标志 0,表示命令;1,表示数据;

        SECTION `.text`:CODE:NOROOT(1)
        THUMB
//   76 void OLED_WR_Byte(u8 dat, u8 cmd)
//   77 {
OLED_WR_Byte:
        PUSH     {R3-R5,LR}
        MOVS     R4,R0
//   78 	u8 i;
//   79 	if (cmd)
        UXTB     R1,R1            ;; ZeroExt  R1,R1,#+24,#+24
        CMP      R1,#+0
        BEQ.N    ??OLED_WR_Byte_0
//   80 		OLED_DC_Set();
        MOVS     R2,#+1
        MOVS     R1,#+9
        LDR.W    R0,??DataTable4  ;; 0x400ff0c0
        BL       LPLD_GPIO_Output_b
        B.N      ??OLED_WR_Byte_1
//   81 	else
//   82 		OLED_DC_Clr();
??OLED_WR_Byte_0:
        MOVS     R2,#+0
        MOVS     R1,#+9
        LDR.W    R0,??DataTable4  ;; 0x400ff0c0
        BL       LPLD_GPIO_Output_b
//   83 	OLED_CS_Clr();
??OLED_WR_Byte_1:
        MOVS     R2,#+0
        MOVS     R1,#+8
        LDR.W    R0,??DataTable4  ;; 0x400ff0c0
        BL       LPLD_GPIO_Output_b
//   84 	for (i = 0; i<8; i++)
        MOVS     R5,#+0
        B.N      ??OLED_WR_Byte_2
//   85 	{
//   86 		OLED_SCLK_Clr();
//   87 		if (dat & 0x80)
//   88 			OLED_SDIN_Set();
//   89 		else
//   90 			OLED_SDIN_Clr();
??OLED_WR_Byte_3:
        MOVS     R2,#+0
        MOVS     R1,#+20
        LDR.W    R0,??DataTable4_1  ;; 0x400ff040
        BL       LPLD_GPIO_Output_b
//   91 		OLED_SCLK_Set();
??OLED_WR_Byte_4:
        MOVS     R2,#+1
        MOVS     R1,#+21
        LDR.W    R0,??DataTable4_1  ;; 0x400ff040
        BL       LPLD_GPIO_Output_b
//   92 		dat <<= 1;
        LSLS     R4,R4,#+1
        ADDS     R5,R5,#+1
??OLED_WR_Byte_2:
        UXTB     R5,R5            ;; ZeroExt  R5,R5,#+24,#+24
        CMP      R5,#+8
        BGE.N    ??OLED_WR_Byte_5
        MOVS     R2,#+0
        MOVS     R1,#+21
        LDR.W    R0,??DataTable4_1  ;; 0x400ff040
        BL       LPLD_GPIO_Output_b
        LSLS     R0,R4,#+24
        BPL.N    ??OLED_WR_Byte_3
        MOVS     R2,#+1
        MOVS     R1,#+20
        LDR.W    R0,??DataTable4_1  ;; 0x400ff040
        BL       LPLD_GPIO_Output_b
        B.N      ??OLED_WR_Byte_4
//   93 	}
//   94 
//   95 	OLED_SCLK_Clr();
??OLED_WR_Byte_5:
        MOVS     R2,#+0
        MOVS     R1,#+21
        LDR.W    R0,??DataTable4_1  ;; 0x400ff040
        BL       LPLD_GPIO_Output_b
//   96 	OLED_CS_Set();
        MOVS     R2,#+1
        MOVS     R1,#+8
        LDR.W    R0,??DataTable4  ;; 0x400ff0c0
        BL       LPLD_GPIO_Output_b
//   97 	OLED_DC_Set();
        MOVS     R2,#+1
        MOVS     R1,#+9
        LDR.W    R0,??DataTable4  ;; 0x400ff0c0
        BL       LPLD_GPIO_Output_b
//   98 }
        POP      {R0,R4,R5,PC}    ;; return
//   99 
//  100 #endif

        SECTION `.text`:CODE:NOROOT(1)
        THUMB
//  101 void OLED_Set_Pos(unsigned char x, unsigned char y)
//  102 {
OLED_Set_Pos:
        PUSH     {R4,LR}
        MOVS     R4,R0
        MOVS     R0,R1
//  103 	OLED_WR_Byte(0xb0 + y, OLED_CMD);
        MOVS     R1,#+0
        SUBS     R0,R0,#+80
        UXTB     R0,R0            ;; ZeroExt  R0,R0,#+24,#+24
        BL       OLED_WR_Byte
//  104 	OLED_WR_Byte(((x & 0xf0) >> 4) | 0x10, OLED_CMD);
        MOVS     R1,#+0
        UXTB     R4,R4            ;; ZeroExt  R4,R4,#+24,#+24
        LSRS     R0,R4,#+4
        ORRS     R0,R0,#0x10
        UXTB     R0,R0            ;; ZeroExt  R0,R0,#+24,#+24
        BL       OLED_WR_Byte
//  105 	OLED_WR_Byte((x & 0x0f), OLED_CMD);
        MOVS     R1,#+0
        ANDS     R0,R4,#0xF
        BL       OLED_WR_Byte
//  106 }
        POP      {R4,PC}          ;; return
//  107 //开启OLED显示

        SECTION `.text`:CODE:NOROOT(1)
        THUMB
//  108 void OLED_Display_On(void)
//  109 {
OLED_Display_On:
        PUSH     {R7,LR}
//  110 	OLED_WR_Byte(0X8D, OLED_CMD);  //SET DCDC命令
        MOVS     R1,#+0
        MOVS     R0,#+141
        BL       OLED_WR_Byte
//  111 	OLED_WR_Byte(0X14, OLED_CMD);  //DCDC ON
        MOVS     R1,#+0
        MOVS     R0,#+20
        BL       OLED_WR_Byte
//  112 	OLED_WR_Byte(0XAF, OLED_CMD);  //DISPLAY ON
        MOVS     R1,#+0
        MOVS     R0,#+175
        BL       OLED_WR_Byte
//  113 }
        POP      {R0,PC}          ;; return
//  114 //关闭OLED显示

        SECTION `.text`:CODE:NOROOT(1)
        THUMB
//  115 void OLED_Display_Off(void)
//  116 {
OLED_Display_Off:
        PUSH     {R7,LR}
//  117 	OLED_WR_Byte(0X8D, OLED_CMD);  //SET DCDC命令
        MOVS     R1,#+0
        MOVS     R0,#+141
        BL       OLED_WR_Byte
//  118 	OLED_WR_Byte(0X10, OLED_CMD);  //DCDC OFF
        MOVS     R1,#+0
        MOVS     R0,#+16
        BL       OLED_WR_Byte
//  119 	OLED_WR_Byte(0XAE, OLED_CMD);  //DISPLAY OFF
        MOVS     R1,#+0
        MOVS     R0,#+174
        BL       OLED_WR_Byte
//  120 }
        POP      {R0,PC}          ;; return
//  121 //清屏函数,清完屏,整个屏幕是黑色的!和没点亮一样!!!

        SECTION `.text`:CODE:NOROOT(1)
        THUMB
//  122 void OLED_Clear(void)
//  123 {
OLED_Clear:
        PUSH     {R3-R5,LR}
//  124 	u8 i, n;
//  125 	for (i = 0; i<8; i++)
        MOVS     R4,#+0
        B.N      ??OLED_Clear_0
//  126 	{
//  127 		OLED_WR_Byte(0xb0 + i, OLED_CMD);    //设置页地址（0~7）
//  128 		OLED_WR_Byte(0x00, OLED_CMD);      //设置显示位置—列低地址
//  129 		OLED_WR_Byte(0x10, OLED_CMD);      //设置显示位置—列高地址
//  130 		for (n = 0; n<128; n++)OLED_WR_Byte(0, OLED_DATA);
??OLED_Clear_1:
        MOVS     R1,#+1
        MOVS     R0,#+0
        BL       OLED_WR_Byte
        ADDS     R5,R5,#+1
??OLED_Clear_2:
        UXTB     R5,R5            ;; ZeroExt  R5,R5,#+24,#+24
        CMP      R5,#+128
        BLT.N    ??OLED_Clear_1
        ADDS     R4,R4,#+1
??OLED_Clear_0:
        UXTB     R4,R4            ;; ZeroExt  R4,R4,#+24,#+24
        CMP      R4,#+8
        BGE.N    ??OLED_Clear_3
        MOVS     R1,#+0
        SUBS     R0,R4,#+80
        UXTB     R0,R0            ;; ZeroExt  R0,R0,#+24,#+24
        BL       OLED_WR_Byte
        MOVS     R1,#+0
        MOVS     R0,#+0
        BL       OLED_WR_Byte
        MOVS     R1,#+0
        MOVS     R0,#+16
        BL       OLED_WR_Byte
        MOVS     R5,#+0
        B.N      ??OLED_Clear_2
//  131 	} //更新显示
//  132 }
??OLED_Clear_3:
        POP      {R0,R4,R5,PC}    ;; return
//  133 

        SECTION `.text`:CODE:NOROOT(1)
        THUMB
//  134 void OLED_ClearLine(u8 y)
//  135 {
OLED_ClearLine:
        PUSH     {R4,LR}
//  136 	unsigned char i = 0;
        MOVS     R4,#+0
//  137 	if (SIZE == 16)
//  138 	{
//  139 		OLED_Set_Pos(0, y);
//  140 		for (i = 0; i<128; i++)
//  141 			OLED_WR_Byte(0x00, OLED_DATA);
//  142 		OLED_Set_Pos(0, y + 1);
//  143 		for (i = 0; i<128; i++)
//  144 			OLED_WR_Byte(0x00, OLED_DATA);
//  145 	}
//  146 	else {
//  147 		OLED_Set_Pos(0, y + 1);
        ADDS     R1,R0,#+1
        UXTB     R1,R1            ;; ZeroExt  R1,R1,#+24,#+24
        MOVS     R0,#+0
        BL       OLED_Set_Pos
//  148 		for (i = 0; i<128; i++)
        MOVS     R4,#+0
        B.N      ??OLED_ClearLine_0
//  149 			OLED_WR_Byte(0x00, OLED_DATA);
??OLED_ClearLine_1:
        MOVS     R1,#+1
        MOVS     R0,#+0
        BL       OLED_WR_Byte
        ADDS     R4,R4,#+1
??OLED_ClearLine_0:
        UXTB     R4,R4            ;; ZeroExt  R4,R4,#+24,#+24
        CMP      R4,#+128
        BLT.N    ??OLED_ClearLine_1
//  150 
//  151 	}
//  152 }
        POP      {R4,PC}          ;; return
//  153 

        SECTION `.text`:CODE:NOROOT(1)
        THUMB
//  154 void OLED_DrawPoint(u8 x, u8 y, u8 cmd)
//  155 {
OLED_DrawPoint:
        PUSH     {R4-R6,LR}
        MOVS     R4,R0
        MOVS     R5,R1
//  156 	static uint8 imgMap[8][128] = { 0 };
//  157 	uint8 i, j;
//  158 	if (cmd)
        UXTB     R2,R2            ;; ZeroExt  R2,R2,#+24,#+24
        CMP      R2,#+0
        BEQ.N    ??OLED_DrawPoint_0
//  159 	{
//  160 
//  161 		imgMap[y / 8][x] = imgMap[y / 8][x] | (0x01 << (y % 8));
        UXTB     R5,R5            ;; ZeroExt  R5,R5,#+24,#+24
        MOVS     R0,#+8
        SDIV     R0,R5,R0
        MOVS     R1,#+128
        LDR.W    R2,??DataTable4_2
        MLA      R0,R1,R0,R2
        UXTB     R4,R4            ;; ZeroExt  R4,R4,#+24,#+24
        UXTB     R5,R5            ;; ZeroExt  R5,R5,#+24,#+24
        MOVS     R1,#+8
        SDIV     R1,R5,R1
        MOVS     R2,#+128
        LDR.W    R3,??DataTable4_2
        MLA      R1,R2,R1,R3
        UXTB     R4,R4            ;; ZeroExt  R4,R4,#+24,#+24
        LDRB     R1,[R4, R1]
        MOVS     R2,#+1
        UXTB     R5,R5            ;; ZeroExt  R5,R5,#+24,#+24
        MOVS     R3,#+8
        SDIV     R6,R5,R3
        MLS      R6,R6,R3,R5
        LSLS     R2,R2,R6
        ORRS     R1,R2,R1
        STRB     R1,[R4, R0]
//  162 		OLED_Set_Pos(x, y / 8);
        UXTB     R5,R5            ;; ZeroExt  R5,R5,#+24,#+24
        MOVS     R0,#+8
        SDIV     R1,R5,R0
        UXTB     R1,R1            ;; ZeroExt  R1,R1,#+24,#+24
        MOVS     R0,R4
        UXTB     R0,R0            ;; ZeroExt  R0,R0,#+24,#+24
        BL       OLED_Set_Pos
//  163 		OLED_WR_Byte(imgMap[y / 8][x], OLED_DATA);
        MOVS     R1,#+1
        UXTB     R5,R5            ;; ZeroExt  R5,R5,#+24,#+24
        MOVS     R0,#+8
        SDIV     R0,R5,R0
        MOVS     R2,#+128
        LDR.W    R3,??DataTable4_2
        MLA      R0,R2,R0,R3
        UXTB     R4,R4            ;; ZeroExt  R4,R4,#+24,#+24
        LDRB     R0,[R4, R0]
        BL       OLED_WR_Byte
//  164 	}
//  165 	else
//  166 	{
//  167 
//  168 		for (i = 0; i < 8; i++)
//  169 		for (j = 0; j < 128; j++)
//  170 		{
//  171 			imgMap[i][j] = 0x00;
//  172 			OLED_Set_Pos(j, i);
//  173 			OLED_WR_Byte(imgMap[i][j], OLED_DATA);
//  174 		}
//  175 	}
//  176 
//  177 }
??OLED_DrawPoint_1:
        POP      {R4-R6,PC}       ;; return
??OLED_DrawPoint_0:
        MOVS     R4,#+0
        B.N      ??OLED_DrawPoint_2
??OLED_DrawPoint_3:
        LDR.N    R0,??DataTable4_2
        UXTB     R4,R4            ;; ZeroExt  R4,R4,#+24,#+24
        MOVS     R1,#+128
        MLA      R0,R1,R4,R0
        UXTB     R5,R5            ;; ZeroExt  R5,R5,#+24,#+24
        MOVS     R1,#+0
        STRB     R1,[R5, R0]
        MOVS     R1,R4
        UXTB     R1,R1            ;; ZeroExt  R1,R1,#+24,#+24
        MOVS     R0,R5
        UXTB     R0,R0            ;; ZeroExt  R0,R0,#+24,#+24
        BL       OLED_Set_Pos
        MOVS     R1,#+1
        LDR.N    R0,??DataTable4_2
        UXTB     R4,R4            ;; ZeroExt  R4,R4,#+24,#+24
        MOVS     R2,#+128
        MLA      R0,R2,R4,R0
        UXTB     R5,R5            ;; ZeroExt  R5,R5,#+24,#+24
        LDRB     R0,[R5, R0]
        BL       OLED_WR_Byte
        ADDS     R5,R5,#+1
??OLED_DrawPoint_4:
        UXTB     R5,R5            ;; ZeroExt  R5,R5,#+24,#+24
        CMP      R5,#+128
        BLT.N    ??OLED_DrawPoint_3
        ADDS     R4,R4,#+1
??OLED_DrawPoint_2:
        UXTB     R4,R4            ;; ZeroExt  R4,R4,#+24,#+24
        CMP      R4,#+8
        BGE.N    ??OLED_DrawPoint_1
        MOVS     R5,#+0
        B.N      ??OLED_DrawPoint_4

        SECTION `.bss`:DATA:REORDER:NOROOT(2)
??imgMap:
        DS8 1024
//  178 
//  179 
//  180 //在指定位置显示一个字符,包括部分字符
//  181 //x:0~127
//  182 //y:0~63
//  183 //mode:0,反白显示;1,正常显示
//  184 //size:选择字体 16/12

        SECTION `.text`:CODE:NOROOT(1)
        THUMB
//  185 void OLED_ShowChar(u8 x, u8 y, u8 chr)
//  186 {
OLED_ShowChar:
        PUSH     {R3-R5,LR}
//  187 	unsigned char c = 0, i = 0;
        MOVS     R4,#+0
        MOVS     R5,#+0
//  188 	c = chr - ' ';//得到偏移后的值
        SUBS     R4,R2,#+32
//  189 	if (x>Max_Column - 1){ x = 0; y = y + 2; }
        UXTB     R0,R0            ;; ZeroExt  R0,R0,#+24,#+24
        CMP      R0,#+128
        BLT.N    ??OLED_ShowChar_0
        MOVS     R0,#+0
        ADDS     R1,R1,#+2
//  190 	if (SIZE == 16)
//  191 	{
//  192 		OLED_Set_Pos(x, y);
//  193 		for (i = 0; i<8; i++)
//  194 			OLED_WR_Byte(F8X16[c * 16 + i], OLED_DATA);
//  195 		OLED_Set_Pos(x, y + 1);
//  196 		for (i = 0; i<8; i++)
//  197 			OLED_WR_Byte(F8X16[c * 16 + i + 8], OLED_DATA);
//  198 	}
//  199 	else {
//  200 		OLED_Set_Pos(x, y + 1);
??OLED_ShowChar_0:
        ADDS     R1,R1,#+1
        UXTB     R1,R1            ;; ZeroExt  R1,R1,#+24,#+24
        UXTB     R0,R0            ;; ZeroExt  R0,R0,#+24,#+24
        BL       OLED_Set_Pos
//  201 		for (i = 0; i<6; i++)
        MOVS     R5,#+0
        B.N      ??OLED_ShowChar_1
//  202 			OLED_WR_Byte(F6x8[c][i], OLED_DATA);
??OLED_ShowChar_2:
        MOVS     R1,#+1
        LDR.N    R0,??DataTable4_3
        UXTB     R4,R4            ;; ZeroExt  R4,R4,#+24,#+24
        MOVS     R2,#+6
        MLA      R0,R2,R4,R0
        UXTB     R5,R5            ;; ZeroExt  R5,R5,#+24,#+24
        LDRB     R0,[R5, R0]
        BL       OLED_WR_Byte
        ADDS     R5,R5,#+1
??OLED_ShowChar_1:
        UXTB     R5,R5            ;; ZeroExt  R5,R5,#+24,#+24
        CMP      R5,#+6
        BLT.N    ??OLED_ShowChar_2
//  203 
//  204 	}
//  205 }
        POP      {R0,R4,R5,PC}    ;; return
//  206 
//  207 
//  208 //m^n函数

        SECTION `.text`:CODE:NOROOT(1)
        THUMB
//  209 u32 oled_pow(u8 m, u8 n)
//  210 {
//  211 	u32 result = 1;
oled_pow:
        MOVS     R2,#+1
        B.N      ??oled_pow_0
//  212 	while (n--)result *= m;
??oled_pow_1:
        UXTB     R0,R0            ;; ZeroExt  R0,R0,#+24,#+24
        MULS     R2,R0,R2
??oled_pow_0:
        MOVS     R3,R1
        SUBS     R1,R3,#+1
        UXTB     R3,R3            ;; ZeroExt  R3,R3,#+24,#+24
        CMP      R3,#+0
        BNE.N    ??oled_pow_1
//  213 	return result;
        MOVS     R0,R2
        BX       LR               ;; return
//  214 }
//  215 //显示2个数字
//  216 //x,y :起点坐标
//  217 //len :数字的位数
//  218 //size:字体大小
//  219 //mode:模式	0,填充模式;1,叠加模式
//  220 //num:数值(0~4294967295);

        SECTION `.text`:CODE:NOROOT(1)
        THUMB
//  221 void OLED_ShowNum(u8 x, u8 y, int32 num, u8 len)
//  222 {
OLED_ShowNum:
        PUSH     {R4-R10,LR}
        MOVS     R4,R0
        MOVS     R5,R1
        MOVS     R6,R2
        MOVS     R7,R3
//  223 	u8 t, temp;
//  224 	u8 enshow = 0;
        MOVS     R8,#+0
//  225 
//  226 	for (t = 0; t<len; t++)
        MOVS     R9,#+0
        B.N      ??OLED_ShowNum_0
//  227 	{
//  228 		temp = ((num >= 0 ? num : -num) / oled_pow(10, len - t - 1)) % 10;
//  229 		if (enshow == 0 && t<(len - 1))
//  230 		{
//  231 			if (temp == 0)
//  232 			{
//  233 				OLED_ShowChar(x + (Num_Size / 2)*t, y, ' ');
//  234 				continue;
//  235 			}
//  236 			else
//  237 			{
//  238 				if(num < 0)
??OLED_ShowNum_1:
        CMP      R6,#+0
        BPL.N    ??OLED_ShowNum_2
//  239 					OLED_ShowChar(x + (Num_Size / 2)*(t - 1), y, '-');
        MOVS     R2,#+45
        MOVS     R1,R5
        UXTB     R1,R1            ;; ZeroExt  R1,R1,#+24,#+24
        UXTB     R9,R9            ;; ZeroExt  R9,R9,#+24,#+24
        SUBS     R0,R9,#+1
        MOVS     R3,#+6
        MULS     R0,R3,R0
        UXTAB    R0,R0,R4
        UXTB     R0,R0            ;; ZeroExt  R0,R0,#+24,#+24
        BL       OLED_ShowChar
//  240 				enshow = 1;
??OLED_ShowNum_2:
        MOVS     R8,#+1
//  241 			}
//  242 
//  243 		}
//  244 		OLED_ShowChar(x + (Num_Size / 2)*t, y, temp + '0');
??OLED_ShowNum_3:
        ADDS     R2,R10,#+48
        UXTB     R2,R2            ;; ZeroExt  R2,R2,#+24,#+24
        MOVS     R1,R5
        UXTB     R1,R1            ;; ZeroExt  R1,R1,#+24,#+24
        UXTB     R9,R9            ;; ZeroExt  R9,R9,#+24,#+24
        MOVS     R0,#+6
        MUL      R0,R0,R9
        UXTAB    R0,R0,R4
        UXTB     R0,R0            ;; ZeroExt  R0,R0,#+24,#+24
        BL       OLED_ShowChar
??OLED_ShowNum_4:
        ADDS     R9,R9,#+1
??OLED_ShowNum_0:
        UXTB     R9,R9            ;; ZeroExt  R9,R9,#+24,#+24
        UXTB     R7,R7            ;; ZeroExt  R7,R7,#+24,#+24
        CMP      R9,R7
        BCS.N    ??OLED_ShowNum_5
        CMP      R6,#+0
        BMI.N    ??OLED_ShowNum_6
        MOV      R10,R6
        B.N      ??OLED_ShowNum_7
??OLED_ShowNum_6:
        RSBS     R10,R6,#+0
??OLED_ShowNum_7:
        SUBS     R0,R7,R9
        SUBS     R1,R0,#+1
        UXTB     R1,R1            ;; ZeroExt  R1,R1,#+24,#+24
        MOVS     R0,#+10
        BL       oled_pow
        UDIV     R0,R10,R0
        MOVS     R1,#+10
        UDIV     R2,R0,R1
        MLS      R10,R1,R2,R0
        UXTB     R8,R8            ;; ZeroExt  R8,R8,#+24,#+24
        CMP      R8,#+0
        BNE.N    ??OLED_ShowNum_3
        UXTB     R9,R9            ;; ZeroExt  R9,R9,#+24,#+24
        UXTB     R7,R7            ;; ZeroExt  R7,R7,#+24,#+24
        SUBS     R0,R7,#+1
        CMP      R9,R0
        BGE.N    ??OLED_ShowNum_3
        UXTB     R10,R10          ;; ZeroExt  R10,R10,#+24,#+24
        CMP      R10,#+0
        BNE.N    ??OLED_ShowNum_1
        MOVS     R2,#+32
        MOVS     R1,R5
        UXTB     R1,R1            ;; ZeroExt  R1,R1,#+24,#+24
        UXTB     R9,R9            ;; ZeroExt  R9,R9,#+24,#+24
        MOVS     R0,#+6
        MUL      R0,R0,R9
        UXTAB    R0,R0,R4
        UXTB     R0,R0            ;; ZeroExt  R0,R0,#+24,#+24
        BL       OLED_ShowChar
        B.N      ??OLED_ShowNum_4
//  245 	}
//  246 
//  247 }
??OLED_ShowNum_5:
        POP      {R4-R10,PC}      ;; return

        SECTION `.text`:CODE:NOROOT(1)
        THUMB
//  248 void OLED_NumClear(u8 x, u8 y, u8 len)
//  249 {
OLED_NumClear:
        PUSH     {R3-R7,LR}
        MOVS     R4,R0
        MOVS     R5,R1
        MOVS     R6,R2
//  250 	u8 t;
//  251 	for (t = 0; t<len; t++)
        MOVS     R7,#+0
        B.N      ??OLED_NumClear_0
//  252 	{
//  253 		OLED_ShowChar(x + (Num_Size / 2)*t, y, ' ');
??OLED_NumClear_1:
        MOVS     R2,#+32
        MOVS     R1,R5
        UXTB     R1,R1            ;; ZeroExt  R1,R1,#+24,#+24
        UXTB     R7,R7            ;; ZeroExt  R7,R7,#+24,#+24
        MOVS     R0,#+6
        MUL      R0,R0,R7
        UXTAB    R0,R0,R4
        UXTB     R0,R0            ;; ZeroExt  R0,R0,#+24,#+24
        BL       OLED_ShowChar
//  254 	}
        ADDS     R7,R7,#+1
??OLED_NumClear_0:
        UXTB     R7,R7            ;; ZeroExt  R7,R7,#+24,#+24
        UXTB     R6,R6            ;; ZeroExt  R6,R6,#+24,#+24
        CMP      R7,R6
        BCC.N    ??OLED_NumClear_1
//  255 
//  256 }
        POP      {R0,R4-R7,PC}    ;; return
//  257 
//  258 //显示一个字符号串

        SECTION `.text`:CODE:NOROOT(1)
        THUMB
//  259 void OLED_ShowString(u8 x, u8 y, u8 *chr)
//  260 {
OLED_ShowString:
        PUSH     {R3-R7,LR}
        MOVS     R4,R0
        MOVS     R5,R1
        MOVS     R6,R2
//  261 	unsigned char j = 0;
        MOVS     R7,#+0
        B.N      ??OLED_ShowString_0
//  262 	while (chr[j] != '\0')
//  263 	{
//  264 		OLED_ShowChar(x, y, chr[j]);
??OLED_ShowString_1:
        UXTB     R7,R7            ;; ZeroExt  R7,R7,#+24,#+24
        LDRB     R2,[R7, R6]
        MOVS     R1,R5
        UXTB     R1,R1            ;; ZeroExt  R1,R1,#+24,#+24
        MOVS     R0,R4
        UXTB     R0,R0            ;; ZeroExt  R0,R0,#+24,#+24
        BL       OLED_ShowChar
//  265 		x += 8;
        ADDS     R4,R4,#+8
//  266 		if (x>120){ x = 0; y += 2; }
        UXTB     R4,R4            ;; ZeroExt  R4,R4,#+24,#+24
        CMP      R4,#+121
        BLT.N    ??OLED_ShowString_2
        MOVS     R4,#+0
        ADDS     R5,R5,#+2
//  267 		j++;
??OLED_ShowString_2:
        ADDS     R7,R7,#+1
//  268 	}
??OLED_ShowString_0:
        UXTB     R7,R7            ;; ZeroExt  R7,R7,#+24,#+24
        LDRB     R0,[R7, R6]
        CMP      R0,#+0
        BNE.N    ??OLED_ShowString_1
//  269 }
        POP      {R0,R4-R7,PC}    ;; return
//  270 
//  271 /***********功能描述：显示显示BMP图片128×64起始点坐标(x,y),x的范围0～127，y为页的范围0～7*****************/

        SECTION `.text`:CODE:NOROOT(1)
        THUMB
//  272 void OLED_DrawBMP(unsigned char x0, unsigned char y0, unsigned char x1, unsigned char y1, const unsigned char BMP[])
//  273 {
OLED_DrawBMP:
        PUSH     {R4-R10,LR}
        MOVS     R4,R0
        MOVS     R5,R1
        MOVS     R6,R2
        MOVS     R7,R3
//  274 	unsigned int j = 0;
        MOVS     R9,#+0
//  275 	unsigned char x, y;
//  276 	for (y = y0; y<y1; y++)
        LDR      R8,[SP, #+32]
        B.N      ??OLED_DrawBMP_0
//  277 	{
//  278 		OLED_Set_Pos(x0, y);
//  279 		for (x = x0; x<x1; x++)
//  280 		{
//  281 			OLED_WR_Byte(BMP[j++], OLED_DATA);
??OLED_DrawBMP_1:
        MOVS     R1,#+1
        LDRB     R0,[R9, R8]
        BL       OLED_WR_Byte
        ADDS     R9,R9,#+1
//  282 		}
        ADDS     R10,R10,#+1
??OLED_DrawBMP_2:
        UXTB     R10,R10          ;; ZeroExt  R10,R10,#+24,#+24
        UXTB     R6,R6            ;; ZeroExt  R6,R6,#+24,#+24
        CMP      R10,R6
        BCC.N    ??OLED_DrawBMP_1
        ADDS     R5,R5,#+1
??OLED_DrawBMP_0:
        UXTB     R5,R5            ;; ZeroExt  R5,R5,#+24,#+24
        UXTB     R7,R7            ;; ZeroExt  R7,R7,#+24,#+24
        CMP      R5,R7
        BCS.N    ??OLED_DrawBMP_3
        MOVS     R1,R5
        UXTB     R1,R1            ;; ZeroExt  R1,R1,#+24,#+24
        MOVS     R0,R4
        UXTB     R0,R0            ;; ZeroExt  R0,R0,#+24,#+24
        BL       OLED_Set_Pos
        MOV      R10,R4
        B.N      ??OLED_DrawBMP_2
//  283 	}
//  284 }
??OLED_DrawBMP_3:
        POP      {R4-R10,PC}      ;; return

        SECTION `.text`:CODE:NOROOT(1)
        THUMB
//  285 void OLED_PinInit(void)
//  286 {
OLED_PinInit:
        PUSH     {LR}
        SUB      SP,SP,#+28
//  287 
//  288 	GPIO_InitTypeDef gpio_init_struct;
//  289 	gpio_init_struct.GPIO_PTx = PTB;
        LDR.N    R0,??DataTable4_1  ;; 0x400ff040
        STR      R0,[SP, #+4]
//  290 	gpio_init_struct.GPIO_Pins = GPIO_Pin20 | GPIO_Pin21 | GPIO_Pin22;
        MOVS     R0,#+7340032
        STR      R0,[SP, #+8]
//  291 	gpio_init_struct.GPIO_Dir = DIR_OUTPUT;
        MOVS     R0,#+1
        STRB     R0,[SP, #+16]
//  292 	gpio_init_struct.GPIO_Output = OUTPUT_H;
        MOVS     R0,#+1
        STRB     R0,[SP, #+17]
//  293 	gpio_init_struct.GPIO_PinControl = IRQC_DIS;
        MOVS     R0,#+0
        STR      R0,[SP, #+12]
//  294 	LPLD_GPIO_Init(gpio_init_struct);
        ADD      R1,SP,#+4
        SUB      SP,SP,#+16
        MOV      R0,SP
        MOVS     R2,#+20
        BL       __aeabi_memcpy4
        POP      {R0-R3}
        BL       LPLD_GPIO_Init
//  295 
//  296 	gpio_init_struct.GPIO_PTx = PTD;
        LDR.N    R0,??DataTable4  ;; 0x400ff0c0
        STR      R0,[SP, #+4]
//  297 	gpio_init_struct.GPIO_Pins = GPIO_Pin8 | GPIO_Pin9;
        MOV      R0,#+768
        STR      R0,[SP, #+8]
//  298 	gpio_init_struct.GPIO_Dir = DIR_OUTPUT;
        MOVS     R0,#+1
        STRB     R0,[SP, #+16]
//  299 	gpio_init_struct.GPIO_Output = OUTPUT_H;
        MOVS     R0,#+1
        STRB     R0,[SP, #+17]
//  300 	gpio_init_struct.GPIO_PinControl = IRQC_DIS;
        MOVS     R0,#+0
        STR      R0,[SP, #+12]
//  301 	LPLD_GPIO_Init(gpio_init_struct);
        ADD      R1,SP,#+4
        SUB      SP,SP,#+16
        MOV      R0,SP
        MOVS     R2,#+20
        BL       __aeabi_memcpy4
        POP      {R0-R3}
        BL       LPLD_GPIO_Init
//  302 }
        ADD      SP,SP,#+28
        POP      {PC}             ;; return
//  303 
//  304 
//  305 //初始化SSD1306

        SECTION `.text`:CODE:NOROOT(1)
        THUMB
//  306 void OLED_Init(void)
//  307 {
OLED_Init:
        PUSH     {R7,LR}
//  308 
//  309 
//  310 	OLED_PinInit();
        BL       OLED_PinInit
//  311 	OLED_RST_Set();
        MOVS     R2,#+1
        MOVS     R1,#+22
        LDR.N    R0,??DataTable4_1  ;; 0x400ff040
        BL       LPLD_GPIO_Output_b
//  312 	delay_ms(100);
        MOVS     R0,#+100
        BL       delay_ms
//  313 	OLED_RST_Clr();
        MOVS     R2,#+0
        MOVS     R1,#+22
        LDR.N    R0,??DataTable4_1  ;; 0x400ff040
        BL       LPLD_GPIO_Output_b
//  314 	delay_ms(100);
        MOVS     R0,#+100
        BL       delay_ms
//  315 	OLED_RST_Set();
        MOVS     R2,#+1
        MOVS     R1,#+22
        LDR.N    R0,??DataTable4_1  ;; 0x400ff040
        BL       LPLD_GPIO_Output_b
//  316 	/*
//  317 	OLED_WR_Byte(0xAE,OLED_CMD);//--turn off oled panel
//  318 	OLED_WR_Byte(0x00,OLED_CMD);//---set low column address
//  319 	OLED_WR_Byte(0x10,OLED_CMD);//---set high column address
//  320 	OLED_WR_Byte(0x40,OLED_CMD);//--set start line address  Set Mapping RAM Display Start Line (0x00~0x3F)
//  321 	OLED_WR_Byte(0x81,OLED_CMD);//--set contrast control register
//  322 	OLED_WR_Byte(0xCF,OLED_CMD); // Set SEG Output Current Brightness
//  323 	OLED_WR_Byte(0xA1,OLED_CMD);//--Set SEG/Column Mapping     0xa0左右反置 0xa1正常
//  324 	OLED_WR_Byte(0xC8,OLED_CMD);//Set COM/Row Scan Direction   0xc0上下反置 0xc8正常
//  325 	OLED_WR_Byte(0xA6,OLED_CMD);//--set normal display
//  326 	OLED_WR_Byte(0xA8,OLED_CMD);//--set multiplex ratio(1 to 64)
//  327 	OLED_WR_Byte(0x3f,OLED_CMD);//--1/64 duty
//  328 	OLED_WR_Byte(0xD3,OLED_CMD);//-set display offset	Shift Mapping RAM Counter (0x00~0x3F)
//  329 	OLED_WR_Byte(0x00,OLED_CMD);//-not offset
//  330 	OLED_WR_Byte(0xd5,OLED_CMD);//--set display clock divide ratio/oscillator frequency
//  331 	OLED_WR_Byte(0x80,OLED_CMD);//--set divide ratio, Set Clock as 100 Frames/Sec
//  332 	OLED_WR_Byte(0xD9,OLED_CMD);//--set pre-charge period
//  333 	OLED_WR_Byte(0xF1,OLED_CMD);//Set Pre-Charge as 15 Clocks & Discharge as 1 Clock
//  334 	OLED_WR_Byte(0xDA,OLED_CMD);//--set com pins hardware configuration
//  335 	OLED_WR_Byte(0x12,OLED_CMD);
//  336 	OLED_WR_Byte(0xDB,OLED_CMD);//--set vcomh
//  337 	OLED_WR_Byte(0x40,OLED_CMD);//Set VCOM Deselect Level
//  338 	OLED_WR_Byte(0x20,OLED_CMD);//-Set Page Addressing Mode (0x00/0x01/0x02)
//  339 	OLED_WR_Byte(0x02,OLED_CMD);//
//  340 	OLED_WR_Byte(0x8D,OLED_CMD);//--set Charge Pump enable/disable
//  341 	OLED_WR_Byte(0x14,OLED_CMD);//--set(0x10) disable
//  342 	OLED_WR_Byte(0xA4,OLED_CMD);// Disable Entire Display On (0xa4/0xa5)
//  343 	OLED_WR_Byte(0xA6,OLED_CMD);// Disable Inverse Display On (0xa6/a7)
//  344 	OLED_WR_Byte(0xAF,OLED_CMD);//--turn on oled panel
//  345 	*/
//  346 
//  347 	OLED_WR_Byte(0xAE, OLED_CMD);//--turn off oled panel
        MOVS     R1,#+0
        MOVS     R0,#+174
        BL       OLED_WR_Byte
//  348 	OLED_WR_Byte(0x00, OLED_CMD);//---set low column address
        MOVS     R1,#+0
        MOVS     R0,#+0
        BL       OLED_WR_Byte
//  349 	OLED_WR_Byte(0x10, OLED_CMD);//---set high column address
        MOVS     R1,#+0
        MOVS     R0,#+16
        BL       OLED_WR_Byte
//  350 	OLED_WR_Byte(0x40, OLED_CMD);//--set start line address  Set Mapping RAM Display Start Line (0x00~0x3F)
        MOVS     R1,#+0
        MOVS     R0,#+64
        BL       OLED_WR_Byte
//  351 	OLED_WR_Byte(0x81, OLED_CMD);//--set contrast control register
        MOVS     R1,#+0
        MOVS     R0,#+129
        BL       OLED_WR_Byte
//  352 	OLED_WR_Byte(0xCF, OLED_CMD); // Set SEG Output Current Brightness
        MOVS     R1,#+0
        MOVS     R0,#+207
        BL       OLED_WR_Byte
//  353 	OLED_WR_Byte(0xA1, OLED_CMD);//--Set SEG/Column Mapping     0xa0左右反置 0xa1正常
        MOVS     R1,#+0
        MOVS     R0,#+161
        BL       OLED_WR_Byte
//  354 	OLED_WR_Byte(0xC8, OLED_CMD);//Set COM/Row Scan Direction   0xc0上下反置 0xc8正常
        MOVS     R1,#+0
        MOVS     R0,#+200
        BL       OLED_WR_Byte
//  355 	OLED_WR_Byte(0xA6, OLED_CMD);//--set normal display
        MOVS     R1,#+0
        MOVS     R0,#+166
        BL       OLED_WR_Byte
//  356 	OLED_WR_Byte(0xA8, OLED_CMD);//--set multiplex ratio(1 to 64)
        MOVS     R1,#+0
        MOVS     R0,#+168
        BL       OLED_WR_Byte
//  357 	OLED_WR_Byte(0x3f, OLED_CMD);//--1/64 duty
        MOVS     R1,#+0
        MOVS     R0,#+63
        BL       OLED_WR_Byte
//  358 	OLED_WR_Byte(0xD3, OLED_CMD);//-set display offset	Shift Mapping RAM Counter (0x00~0x3F)
        MOVS     R1,#+0
        MOVS     R0,#+211
        BL       OLED_WR_Byte
//  359 	OLED_WR_Byte(0x00, OLED_CMD);//-not offset
        MOVS     R1,#+0
        MOVS     R0,#+0
        BL       OLED_WR_Byte
//  360 	OLED_WR_Byte(0xd5, OLED_CMD);//--set display clock divide ratio/oscillator frequency
        MOVS     R1,#+0
        MOVS     R0,#+213
        BL       OLED_WR_Byte
//  361 	OLED_WR_Byte(0x80, OLED_CMD);//--set divide ratio, Set Clock as 100 Frames/Sec
        MOVS     R1,#+0
        MOVS     R0,#+128
        BL       OLED_WR_Byte
//  362 	OLED_WR_Byte(0xD9, OLED_CMD);//--set pre-charge period
        MOVS     R1,#+0
        MOVS     R0,#+217
        BL       OLED_WR_Byte
//  363 	OLED_WR_Byte(0xF1, OLED_CMD);//Set Pre-Charge as 15 Clocks & Discharge as 1 Clock
        MOVS     R1,#+0
        MOVS     R0,#+241
        BL       OLED_WR_Byte
//  364 	OLED_WR_Byte(0xDA, OLED_CMD);//--set com pins hardware configuration
        MOVS     R1,#+0
        MOVS     R0,#+218
        BL       OLED_WR_Byte
//  365 	OLED_WR_Byte(0x12, OLED_CMD);
        MOVS     R1,#+0
        MOVS     R0,#+18
        BL       OLED_WR_Byte
//  366 	OLED_WR_Byte(0xDB, OLED_CMD);//--set vcomh
        MOVS     R1,#+0
        MOVS     R0,#+219
        BL       OLED_WR_Byte
//  367 	OLED_WR_Byte(0x40, OLED_CMD);//Set VCOM Deselect Level
        MOVS     R1,#+0
        MOVS     R0,#+64
        BL       OLED_WR_Byte
//  368 	OLED_WR_Byte(0x01, OLED_CMD);//-Set Page Addressing Mode (0x00/0x01/0x02)
        MOVS     R1,#+0
        MOVS     R0,#+1
        BL       OLED_WR_Byte
//  369 	OLED_WR_Byte(0x02, OLED_CMD);//
        MOVS     R1,#+0
        MOVS     R0,#+2
        BL       OLED_WR_Byte
//  370 	OLED_WR_Byte(0x8D, OLED_CMD);//--set Charge Pump enable/disable
        MOVS     R1,#+0
        MOVS     R0,#+141
        BL       OLED_WR_Byte
//  371 	OLED_WR_Byte(0x14, OLED_CMD);//--set(0x10) disable
        MOVS     R1,#+0
        MOVS     R0,#+20
        BL       OLED_WR_Byte
//  372 	OLED_WR_Byte(0xA4, OLED_CMD);// Disable Entire Display On (0xa4/0xa5)
        MOVS     R1,#+0
        MOVS     R0,#+164
        BL       OLED_WR_Byte
//  373 	OLED_WR_Byte(0xA6, OLED_CMD);// Disable Inverse Display On (0xa6/a7)
        MOVS     R1,#+0
        MOVS     R0,#+166
        BL       OLED_WR_Byte
//  374 	OLED_WR_Byte(0xAF, OLED_CMD);//--turn on oled panel
        MOVS     R1,#+0
        MOVS     R0,#+175
        BL       OLED_WR_Byte
//  375 
//  376 	OLED_WR_Byte(0xAF, OLED_CMD); /*display ON*/
        MOVS     R1,#+0
        MOVS     R0,#+175
        BL       OLED_WR_Byte
//  377 }
        POP      {R0,PC}          ;; return

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable4:
        DC32     0x400ff0c0

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable4_1:
        DC32     0x400ff040

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable4_2:
        DC32     ??imgMap

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable4_3:
        DC32     F6x8

        SECTION `.iar_vfe_header`:DATA:NOALLOC:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
        DC32 0

        SECTION __DLIB_PERTHREAD:DATA:REORDER:NOROOT(0)
        SECTION_TYPE SHT_PROGBITS, 0

        SECTION __DLIB_PERTHREAD_init:DATA:REORDER:NOROOT(0)
        SECTION_TYPE SHT_PROGBITS, 0

        END
//  378 
// 
// 1 024 bytes in section .bss
// 2 072 bytes in section .rodata
// 1 436 bytes in section .text
// 
// 1 436 bytes of CODE  memory
// 2 072 bytes of CONST memory
// 1 024 bytes of DATA  memory
//
//Errors: none
//Warnings: none
