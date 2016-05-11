///////////////////////////////////////////////////////////////////////////////
//
// IAR ANSI C/C++ Compiler V7.40.3.8902/W32 for ARM       24/Apr/2016  20:13:22
// Copyright 1999-2015 IAR Systems AB.
//
//    Cpu mode     =  thumb
//    Endian       =  little
//    Source file  =  
//        C:\Users\Administrator\Desktop\Gold_Razor_A\lib\common\relocate.c
//    Command line =  
//        C:\Users\Administrator\Desktop\Gold_Razor_A\lib\common\relocate.c -D
//        LPLD_K60 -D USE_K60DZ10 -lCN
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
//        C:\Users\Administrator\Desktop\Gold_Razor_A\project\Gold_Razor_A\iar\FLASH\List\relocate.s
//
///////////////////////////////////////////////////////////////////////////////

        #define SHT_PROGBITS 0x1

        SECTION `.bss`:DATA:REORDER:NOROOT(0)
        SECTION_TYPE SHT_PROGBITS, 0
        SECTION `.data`:DATA:REORDER:NOROOT(0)
        SECTION_TYPE SHT_PROGBITS, 0
        SECTION `.data_init`:DATA:REORDER:NOROOT(0)
        SECTION_TYPE SHT_PROGBITS, 0
        SECTION CodeRelocate:DATA:REORDER:NOROOT(0)
        SECTION_TYPE SHT_PROGBITS, 0
        SECTION CodeRelocateRam:DATA:REORDER:NOROOT(0)
        SECTION_TYPE SHT_PROGBITS, 0

        EXTERN __VECTOR_RAM
        EXTERN __VECTOR_TABLE

        PUBLIC common_relocate

// C:\Users\Administrator\Desktop\Gold_Razor_A\lib\common\relocate.c
//    1 /**
//    2  * @file relocate.c
//    3  * @version 3.0[By LPLD]
//    4  * @date 2013-06-18
//    5  * @brief Kinetisͨ�����ݴ���Ǩ�ƺ���
//    6  *
//    7  * ���Ľ���:�������޸�
//    8  *
//    9  * ʵ�����ݡ�������ROM��RAMǨ�ƵĹ���
//   10  *
//   11  * ��Ȩ����:�����������µ��Ӽ������޹�˾
//   12  * http://www.lpld.cn
//   13  * mail:support@lpld.cn
//   14  *
//   15  * @par
//   16  * ����������������[LPLD]������ά������������ʹ���߿���Դ���롣
//   17  * �����߿���������ʹ�û��Դ���롣�����μ�����ע��Ӧ���Ա�����
//   18  * ���ø��Ļ�ɾ��ԭ��Ȩ���������������ο����߿��Լ�ע���ΰ�Ȩ�����ߡ�
//   19  * ��Ӧ�����ش�Э��Ļ����ϣ�����Դ���롢���ó��۴��뱾��
//   20  * �������²���������ʹ�ñ��������������κ��¹ʡ��������λ���ز���Ӱ�졣
//   21  * ����������������͡�˵��������ľ���ԭ�����ܡ�ʵ�ַ�����
//   22  * ������������[LPLD]��Ȩ�������߲��ý�������������ҵ��Ʒ��
//   23  */
//   24 
//   25 #include "common.h"
//   26 
//   27 #if defined(__IAR_SYSTEMS_ICC__)
//   28   #pragma section = ".data"
//   29   #pragma section = ".data_init"
//   30   #pragma section = ".bss"
//   31   #pragma section = "CodeRelocate"
//   32   #pragma section = "CodeRelocateRam"
//   33 #endif
//   34    
//   35 /********************************************************************/

        SECTION `.text`:CODE:NOROOT(2)
        THUMB
//   36 void common_relocate(void)
//   37 {
//   38     #ifndef __IAR_SYSTEMS_ICC__
//   39       #warning ��IAR��������ȷ���˴���ַ
//   40       extern char __START_BSS[];
//   41       extern char __END_BSS[];
//   42       extern uint32 __DATA_ROM[];
//   43       extern uint32 __DATA_RAM[];
//   44       extern char __DATA_END[];
//   45     #endif
//   46   
//   47   /* ����һ���������ڿ���ѭ����ʹ�� */
//   48   uint32 n;
//   49   
//   50   /* Ϊ��ͬ�����ݶζ���ָ�롣
//   51   * ��Щ�������������ļ��л�ȡ��ֵ��ʼ��
//   52   */
//   53   uint8 * data_ram, * data_rom, * data_rom_end;
//   54   uint8 * bss_start, * bss_end;
//   55   
//   56   
//   57   /* ���������ļ��е�VECTOR_TABLE��VECTOR_RAM�ĵ�ַ */
//   58   extern uint32 __VECTOR_TABLE[];
//   59   extern uint32 __VECTOR_RAM[];
//   60   
//   61   /* ���ж��������Ƶ�RAM�� */
//   62   if (__VECTOR_RAM != __VECTOR_TABLE)
common_relocate:
        LDR.N    R0,??common_relocate_0
        LDR.N    R1,??common_relocate_0+0x4
        CMP      R0,R1
        BEQ.N    ??common_relocate_1
//   63   {
//   64     for (n = 0; n < 0x410; n++)
        MOVS     R0,#+0
        B.N      ??common_relocate_2
//   65       __VECTOR_RAM[n] = __VECTOR_TABLE[n];
??common_relocate_3:
        LDR.N    R1,??common_relocate_0+0x4
        LDR      R1,[R1, R0, LSL #+2]
        LDR.N    R2,??common_relocate_0
        STR      R1,[R2, R0, LSL #+2]
        ADDS     R0,R0,#+1
??common_relocate_2:
        CMP      R0,#+1040
        BCC.N    ??common_relocate_3
//   66   }
//   67   /* ���µ��ж�������ָ�븳��VTOR�Ĵ��� */
//   68   write_vtor((uint32)__VECTOR_RAM);
??common_relocate_1:
        LDR.N    R0,??common_relocate_0
        LDR.N    R1,??common_relocate_0+0x8  ;; 0xe000ed08
        STR      R0,[R1, #+0]
//   69   
//   70   /* ���.data�εĵ�ַ(�ѳ�ʼ�������ݶ�) */
//   71   #if defined(__IAR_SYSTEMS_ICC__)
//   72     data_ram = __section_begin(".data");
        LDR.N    R1,??common_relocate_0+0xC
//   73     data_rom = __section_begin(".data_init");
        LDR.N    R2,??common_relocate_0+0x10
//   74     data_rom_end = __section_end(".data_init");
        LDR.N    R0,??common_relocate_0+0x14
//   75     n = data_rom_end - data_rom;	
        SUBS     R0,R0,R2
        B.N      ??common_relocate_4
//   76   #else
//   77     #warning ��IAR��������ȷ���˴���ַ
//   78     data_ram = (uint8 *)__DATA_RAM;
//   79     data_rom = (uint8 *)__DATA_ROM;
//   80     data_rom_end  = (uint8 *)__DATA_END; /* �ö���CodeWarrior��������ΪRAM��ַ */
//   81     n = data_rom_end - data_rom;
//   82   #endif
//   83   
//   84   /* ��ROM�����ѳ�ʼ�������ݵ�RAM */
//   85   while (n--)
//   86     *data_ram++ = *data_rom++;
??common_relocate_5:
        LDRB     R3,[R2, #+0]
        STRB     R3,[R1, #+0]
        ADDS     R2,R2,#+1
        ADDS     R1,R1,#+1
??common_relocate_4:
        MOVS     R3,R0
        SUBS     R0,R3,#+1
        CMP      R3,#+0
        BNE.N    ??common_relocate_5
//   87   
//   88   
//   89   /* ���.bss�εĵ�ַ (��ʼ��Ϊ0������) */
//   90   #if defined(__IAR_SYSTEMS_ICC__)
//   91   bss_start = __section_begin(".bss");
        LDR.N    R1,??common_relocate_0+0x18
//   92   bss_end = __section_end(".bss");  
        LDR.N    R0,??common_relocate_0+0x1C
//   93   #else
//   94   #warning ��IAR��������ȷ���˴���ַ
//   95   bss_start = (uint8 *)__START_BSS;
//   96   bss_end = (uint8 *)__END_BSS;
//   97   #endif
//   98   
//   99   /* �����ʼ��Ϊ0�����ݶ� */
//  100   n = bss_end - bss_start;
        SUBS     R0,R0,R1
        B.N      ??common_relocate_6
//  101   while(n--)
//  102     *bss_start++ = 0;
??common_relocate_7:
        MOVS     R2,#+0
        STRB     R2,[R1, #+0]
        ADDS     R1,R1,#+1
??common_relocate_6:
        MOVS     R2,R0
        SUBS     R0,R2,#+1
        CMP      R2,#+0
        BNE.N    ??common_relocate_7
//  103   
//  104   /* ȡ������Ӧ�ô�ROM���Ƶ�RAM�Ĵ���εĵ�ַ��
//  105   * IAR��һ��Ԥ����Ĺؼ��ֿ��Ա�Ƕ����ĺ���Ϊ��RAMִ�С�
//  106   * �ں����ķ�������ǰ���"__ramfunc"�ؼ��ֿ��Խ��������Ϊ��RAM��ִ�С�
//  107   * ����:__ramfunc void foo(void);
//  108   */
//  109   #if defined(__IAR_SYSTEMS_ICC__)
//  110   uint8* code_relocate_ram = __section_begin("CodeRelocateRam");
        LDR.N    R1,??common_relocate_0+0x20
//  111   uint8* code_relocate = __section_begin("CodeRelocate");
        LDR.N    R2,??common_relocate_0+0x24
//  112   uint8* code_relocate_end = __section_end("CodeRelocate");
        LDR.N    R0,??common_relocate_0+0x28
//  113   
//  114   /* ��������ROM���Ƶ�RAM */
//  115   n = code_relocate_end - code_relocate;
        SUBS     R0,R0,R2
        B.N      ??common_relocate_8
//  116   while (n--)
//  117     *code_relocate_ram++ = *code_relocate++;
??common_relocate_9:
        LDRB     R3,[R2, #+0]
        STRB     R3,[R1, #+0]
        ADDS     R2,R2,#+1
        ADDS     R1,R1,#+1
??common_relocate_8:
        MOVS     R3,R0
        SUBS     R0,R3,#+1
        CMP      R3,#+0
        BNE.N    ??common_relocate_9
//  118   #endif
//  119 }
        BX       LR               ;; return
        Nop      
        DATA
??common_relocate_0:
        DC32     __VECTOR_RAM
        DC32     __VECTOR_TABLE
        DC32     0xe000ed08
        DC32     SFB(`.data`)
        DC32     SFB(`.data_init`)
        DC32     SFE(`.data_init`)
        DC32     SFB(`.bss`)
        DC32     SFE(`.bss`)
        DC32     SFB(CodeRelocateRam)
        DC32     SFB(CodeRelocate)
        DC32     SFE(CodeRelocate)

        SECTION `.iar_vfe_header`:DATA:NOALLOC:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
        DC32 0

        SECTION `.bss`:DATA:REORDER:NOROOT(0)
        SECTION_TYPE SHT_PROGBITS, 0

        SECTION `.data`:DATA:REORDER:NOROOT(0)
        SECTION_TYPE SHT_PROGBITS, 0

        SECTION `.data_init`:DATA:REORDER:NOROOT(0)
        SECTION_TYPE SHT_PROGBITS, 0

        SECTION CodeRelocate:DATA:REORDER:NOROOT(0)
        SECTION_TYPE SHT_PROGBITS, 0

        SECTION CodeRelocateRam:DATA:REORDER:NOROOT(0)
        SECTION_TYPE SHT_PROGBITS, 0

        SECTION __DLIB_PERTHREAD:DATA:REORDER:NOROOT(0)
        SECTION_TYPE SHT_PROGBITS, 0

        SECTION __DLIB_PERTHREAD_init:DATA:REORDER:NOROOT(0)
        SECTION_TYPE SHT_PROGBITS, 0

        END
//  120 /********************************************************************/
// 
// 160 bytes in section .text
// 
// 160 bytes of CODE memory
//
//Errors: none
//Warnings: none
