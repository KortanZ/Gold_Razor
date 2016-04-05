///////////////////////////////////////////////////////////////////////////////
//
// IAR ANSI C/C++ Compiler V7.40.3.8902/W32 for ARM       23/Mar/2016  11:18:28
// Copyright 1999-2015 IAR Systems AB.
//
//    Cpu mode     =  thumb
//    Endian       =  little
//    Source file  =  
//        C:\Users\Administrator\Desktop\Gold_Razor\project\Gold_Razor\app\Source\GPIO_init.c
//    Command line =  
//        C:\Users\Administrator\Desktop\Gold_Razor\project\Gold_Razor\app\Source\GPIO_init.c
//        -D LPLD_K60 -D USE_K60DZ10 -lCN
//        C:\Users\Administrator\Desktop\Gold_Razor\project\Gold_Razor\iar\FLASH\List\
//        -lB
//        C:\Users\Administrator\Desktop\Gold_Razor\project\Gold_Razor\iar\FLASH\List\
//        -o
//        C:\Users\Administrator\Desktop\Gold_Razor\project\Gold_Razor\iar\FLASH\Obj\
//        --no_cse --no_unroll --no_inline --no_code_motion --no_tbaa
//        --no_clustering --no_scheduling --debug --endian=little
//        --cpu=Cortex-M4 -e --fpu=None --dlib_config "D:\IAR EWARM\Program
//        Files (x86)\IAR Systems\Embedded Workbench
//        7.2\arm\INC\c\DLib_Config_Normal.h" -I
//        C:\Users\Administrator\Desktop\Gold_Razor\project\Gold_Razor\iar\..\app\
//        -I
//        C:\Users\Administrator\Desktop\Gold_Razor\project\Gold_Razor\iar\..\app\Source\
//        -I
//        C:\Users\Administrator\Desktop\Gold_Razor\project\Gold_Razor\iar\..\..\..\lib\CPU\
//        -I
//        C:\Users\Administrator\Desktop\Gold_Razor\project\Gold_Razor\iar\..\..\..\lib\common\
//        -I
//        C:\Users\Administrator\Desktop\Gold_Razor\project\Gold_Razor\iar\..\..\..\lib\LPLD\
//        -I
//        C:\Users\Administrator\Desktop\Gold_Razor\project\Gold_Razor\iar\..\..\..\lib\LPLD\HW\
//        -I
//        C:\Users\Administrator\Desktop\Gold_Razor\project\Gold_Razor\iar\..\..\..\lib\LPLD\DEV\
//        -I
//        C:\Users\Administrator\Desktop\Gold_Razor\project\Gold_Razor\iar\..\..\..\lib\LPLD\FUNC\
//        -I
//        C:\Users\Administrator\Desktop\Gold_Razor\project\Gold_Razor\iar\..\..\..\lib\uCOS-II\Ports\
//        -I
//        C:\Users\Administrator\Desktop\Gold_Razor\project\Gold_Razor\iar\..\..\..\lib\uCOS-II\Source\
//        -I
//        C:\Users\Administrator\Desktop\Gold_Razor\project\Gold_Razor\iar\..\..\..\lib\FatFs\
//        -I
//        C:\Users\Administrator\Desktop\Gold_Razor\project\Gold_Razor\iar\..\..\..\lib\FatFs\option\
//        -I
//        C:\Users\Administrator\Desktop\Gold_Razor\project\Gold_Razor\iar\..\..\..\lib\USB\common\
//        -I
//        C:\Users\Administrator\Desktop\Gold_Razor\project\Gold_Razor\iar\..\..\..\lib\USB\driver\
//        -I
//        C:\Users\Administrator\Desktop\Gold_Razor\project\Gold_Razor\iar\..\..\..\lib\USB\descriptor\
//        -I
//        C:\Users\Administrator\Desktop\Gold_Razor\project\Gold_Razor\iar\..\..\..\lib\USB\class\
//        -Ol -I "D:\IAR EWARM\Program Files (x86)\IAR Systems\Embedded
//        Workbench 7.2\arm\CMSIS\Include\" -D ARM_MATH_CM4
//    List file    =  
//        C:\Users\Administrator\Desktop\Gold_Razor\project\Gold_Razor\iar\FLASH\List\GPIO_init.s
//
///////////////////////////////////////////////////////////////////////////////

        #define SHT_PROGBITS 0x1

        EXTERN LPLD_GPIO_Init
        EXTERN __aeabi_memcpy4

        PUBLIC GPIO_init
        PUBLIC gpioa_init_struct
        PUBLIC gpioe_init_struct
        PUBLIC keyC_init_struct
        PUBLIC keyD_init_struct

// C:\Users\Administrator\Desktop\Gold_Razor\project\Gold_Razor\app\Source\GPIO_init.c
//    1 #include "GPIO_init.h"
//    2 
//    3 
//    4 

        SECTION `.bss`:DATA:REORDER:NOROOT(2)
//    5 GPIO_InitTypeDef gpioa_init_struct;
gpioa_init_struct:
        DS8 20

        SECTION `.bss`:DATA:REORDER:NOROOT(2)
//    6 GPIO_InitTypeDef gpioe_init_struct;
gpioe_init_struct:
        DS8 20

        SECTION `.bss`:DATA:REORDER:NOROOT(2)
//    7 GPIO_InitTypeDef keyC_init_struct;
keyC_init_struct:
        DS8 20

        SECTION `.bss`:DATA:REORDER:NOROOT(2)
//    8 GPIO_InitTypeDef keyD_init_struct;
keyD_init_struct:
        DS8 20
//    9 

        SECTION `.text`:CODE:NOROOT(2)
        THUMB
//   10 void GPIO_init(void)
//   11 {
GPIO_init:
        PUSH     {R7,LR}
//   12 //--------------------K60_LED-------------------
//   13   gpioa_init_struct.GPIO_PTx = PTA;
        LDR.N    R0,??GPIO_init_0  ;; 0x400ff000
        LDR.N    R1,??GPIO_init_0+0x4
        STR      R0,[R1, #+0]
//   14   gpioa_init_struct.GPIO_Pins = GPIO_Pin17;
        MOVS     R0,#+131072
        LDR.N    R1,??GPIO_init_0+0x4
        STR      R0,[R1, #+4]
//   15   gpioa_init_struct.GPIO_Dir = DIR_OUTPUT;
        MOVS     R0,#+1
        LDR.N    R1,??GPIO_init_0+0x4
        STRB     R0,[R1, #+12]
//   16   gpioa_init_struct.GPIO_Output = OUTPUT_H;
        MOVS     R0,#+1
        LDR.N    R1,??GPIO_init_0+0x4
        STRB     R0,[R1, #+13]
//   17   gpioa_init_struct.GPIO_PinControl = IRQC_DIS;
        MOVS     R0,#+0
        LDR.N    R1,??GPIO_init_0+0x4
        STR      R0,[R1, #+8]
//   18   LPLD_GPIO_Init(gpioa_init_struct);
        LDR.N    R1,??GPIO_init_0+0x4
        SUB      SP,SP,#+16
        MOV      R0,SP
        MOVS     R2,#+20
        BL       __aeabi_memcpy4
        POP      {R0-R3}
        BL       LPLD_GPIO_Init
//   19 //---------------------Razor_LED----------------
//   20   gpioe_init_struct.GPIO_PTx = PTE;
        LDR.N    R0,??GPIO_init_0+0x8  ;; 0x400ff100
        LDR.N    R1,??GPIO_init_0+0xC
        STR      R0,[R1, #+0]
//   21   gpioe_init_struct.GPIO_Pins = GPIO_Pin10;
        MOV      R0,#+1024
        LDR.N    R1,??GPIO_init_0+0xC
        STR      R0,[R1, #+4]
//   22   gpioe_init_struct.GPIO_Dir = DIR_OUTPUT;
        MOVS     R0,#+1
        LDR.N    R1,??GPIO_init_0+0xC
        STRB     R0,[R1, #+12]
//   23   gpioe_init_struct.GPIO_Output = OUTPUT_L;
        MOVS     R0,#+0
        LDR.N    R1,??GPIO_init_0+0xC
        STRB     R0,[R1, #+13]
//   24   gpioe_init_struct.GPIO_PinControl = IRQC_DIS;
        MOVS     R0,#+0
        LDR.N    R1,??GPIO_init_0+0xC
        STR      R0,[R1, #+8]
//   25   LPLD_GPIO_Init(gpioe_init_struct);
        LDR.N    R1,??GPIO_init_0+0xC
        SUB      SP,SP,#+16
        MOV      R0,SP
        MOVS     R2,#+20
        BL       __aeabi_memcpy4
        POP      {R0-R3}
        BL       LPLD_GPIO_Init
//   26 //---------------------Razor_Key-------------------
//   27   keyC_init_struct.GPIO_PTx = PTC;
        LDR.N    R0,??GPIO_init_0+0x10  ;; 0x400ff080
        LDR.N    R1,??GPIO_init_0+0x14
        STR      R0,[R1, #+0]
//   28   keyC_init_struct.GPIO_Pins = GPIO_Pin14 | GPIO_Pin15;
        MOV      R0,#+49152
        LDR.N    R1,??GPIO_init_0+0x14
        STR      R0,[R1, #+4]
//   29   keyC_init_struct.GPIO_Dir = DIR_INPUT;
        MOVS     R0,#+0
        LDR.N    R1,??GPIO_init_0+0x14
        STRB     R0,[R1, #+12]
//   30   //keyC_init_struct.GPIO_Output = INPUT_PULL_UP;
//   31   keyC_init_struct.GPIO_PinControl = INPUT_PULL_UP;
        MOVS     R0,#+3
        LDR.N    R1,??GPIO_init_0+0x14
        STR      R0,[R1, #+8]
//   32   LPLD_GPIO_Init(keyC_init_struct);
        LDR.N    R1,??GPIO_init_0+0x14
        SUB      SP,SP,#+16
        MOV      R0,SP
        MOVS     R2,#+20
        BL       __aeabi_memcpy4
        POP      {R0-R3}
        BL       LPLD_GPIO_Init
//   33 
//   34   keyD_init_struct.GPIO_PTx = PTD;
        LDR.N    R0,??GPIO_init_0+0x18  ;; 0x400ff0c0
        LDR.N    R1,??GPIO_init_0+0x1C
        STR      R0,[R1, #+0]
//   35   keyD_init_struct.GPIO_Pins = GPIO_Pin10 | GPIO_Pin11 | GPIO_Pin12 | GPIO_Pin13;
        MOV      R0,#+15360
        LDR.N    R1,??GPIO_init_0+0x1C
        STR      R0,[R1, #+4]
//   36   keyD_init_struct.GPIO_Dir = DIR_INPUT;
        MOVS     R0,#+0
        LDR.N    R1,??GPIO_init_0+0x1C
        STRB     R0,[R1, #+12]
//   37   //keyD_init_struct.GPIO_Output = INPUT_PULL_UP;
//   38   keyD_init_struct.GPIO_PinControl = INPUT_PULL_UP;
        MOVS     R0,#+3
        LDR.N    R1,??GPIO_init_0+0x1C
        STR      R0,[R1, #+8]
//   39   LPLD_GPIO_Init(keyD_init_struct);
        LDR.N    R1,??GPIO_init_0+0x1C
        SUB      SP,SP,#+16
        MOV      R0,SP
        MOVS     R2,#+20
        BL       __aeabi_memcpy4
        POP      {R0-R3}
        BL       LPLD_GPIO_Init
//   40 }
        POP      {R0,PC}          ;; return
        DATA
??GPIO_init_0:
        DC32     0x400ff000
        DC32     gpioa_init_struct
        DC32     0x400ff100
        DC32     gpioe_init_struct
        DC32     0x400ff080
        DC32     keyC_init_struct
        DC32     0x400ff0c0
        DC32     keyD_init_struct

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
//  80 bytes in section .bss
// 224 bytes in section .text
// 
// 224 bytes of CODE memory
//  80 bytes of DATA memory
//
//Errors: none
//Warnings: none
