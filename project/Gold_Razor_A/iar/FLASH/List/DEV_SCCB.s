///////////////////////////////////////////////////////////////////////////////
//
// IAR ANSI C/C++ Compiler V7.40.3.8902/W32 for ARM       24/Apr/2016  20:13:18
// Copyright 1999-2015 IAR Systems AB.
//
//    Cpu mode     =  thumb
//    Endian       =  little
//    Source file  =  
//        C:\Users\Administrator\Desktop\Gold_Razor_A\lib\LPLD\DEV\DEV_SCCB.c
//    Command line =  
//        C:\Users\Administrator\Desktop\Gold_Razor_A\lib\LPLD\DEV\DEV_SCCB.c
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
//        C:\Users\Administrator\Desktop\Gold_Razor_A\project\Gold_Razor_A\iar\FLASH\List\DEV_SCCB.s
//
///////////////////////////////////////////////////////////////////////////////

        #define SHT_PROGBITS 0x1

        EXTERN LPLD_GPIO_Init
        EXTERN __aeabi_memcpy4

        PUBLIC LPLD_SCCB_Init
        PUBLIC LPLD_SCCB_ReadReg
        PUBLIC LPLD_SCCB_WriteReg

// C:\Users\Administrator\Desktop\Gold_Razor_A\lib\LPLD\DEV\DEV_SCCB.c
//    1 /**
//    2 * @file DEV_SCCB.c
//    3 * @version 0.1[By LPLD]
//    4 * @date 2013-09-24
//    5 * @brief SCCB设备驱动程序
//    6 *
//    7 * 更改建议:可根据实际硬件修改
//    8 *
//    9 * 版权所有:北京拉普兰德电子技术有限公司
//   10 * http://www.lpld.cn
//   11 * mail:support@lpld.cn
//   12 *
//   13 * @par
//   14 * 本代码由拉普兰德[LPLD]开发并维护，并向所有使用者开放源代码。
//   15 * 开发者可以随意修使用或改源代码。但本段及以上注释应予以保留。
//   16 * 不得更改或删除原版权所有者姓名，二次开发者可以加注二次版权所有者。
//   17 * 但应在遵守此协议的基础上，开放源代码、不得出售代码本身。
//   18 * 拉普兰德不负责由于使用本代码所带来的任何事故、法律责任或相关不良影响。
//   19 * 拉普兰德无义务解释、说明本代码的具体原理、功能、实现方法。
//   20 * 除非拉普兰德[LPLD]授权，开发者不得将本代码用于商业产品。
//   21 */
//   22 #include "DEV_SCCB.h"
//   23 
//   24 static uint8 LPLD_SCCB_Start(void);
//   25 static void LPLD_SCCB_Stop(void);
//   26 static void LPLD_SCCB_Ack(void);
//   27 static void LPLD_SCCB_NoAck(void);
//   28 static uint8 LPLD_SCCB_WaitAck(void);
//   29 static void LPLD_SCCB_SendByte(uint8);
//   30 static uint8 LPLD_SCCB_ReceiveByte(void);
//   31 static void LPLD_SCCB_Delay(uint16);
//   32 
//   33 /*
//   34  * LPLD_SCCB_Init
//   35  * 初始化SCCB所需引脚
//   36  */

        SECTION `.text`:CODE:NOROOT(1)
        THUMB
//   37 void LPLD_SCCB_Init(void)
//   38 {
LPLD_SCCB_Init:
        PUSH     {LR}
        SUB      SP,SP,#+28
//   39   GPIO_InitTypeDef pta;
//   40   /********用户可修改值 开始***********/
//   41   pta.GPIO_PTx = PTA;
        LDR.N    R0,??DataTable7  ;; 0x400ff000
        STR      R0,[SP, #+4]
//   42   pta.GPIO_Pins = GPIO_Pin25 | GPIO_Pin26;
        MOVS     R0,#+100663296
        STR      R0,[SP, #+8]
//   43   /********用户可修改值 结束***********/
//   44   pta.GPIO_Dir = DIR_OUTPUT;
        MOVS     R0,#+1
        STRB     R0,[SP, #+16]
//   45   pta.GPIO_Output = OUTPUT_H;
        MOVS     R0,#+1
        STRB     R0,[SP, #+17]
//   46   pta.GPIO_PinControl = NULL;
        MOVS     R0,#+0
        STR      R0,[SP, #+12]
//   47   LPLD_GPIO_Init(pta);
        ADD      R1,SP,#+4
        SUB      SP,SP,#+16
        MOV      R0,SP
        MOVS     R2,#+20
        BL       __aeabi_memcpy4
        POP      {R0-R3}
        BL       LPLD_GPIO_Init
//   48 }
        ADD      SP,SP,#+28
        POP      {PC}             ;; return
//   49 
//   50 /*
//   51  * LPLD_SCCB_WriteReg
//   52  * 写SCCB设备寄存器
//   53  *
//   54  * 参数:
//   55  *    reg_addr--寄存器地址
//   56  *    data--待写数据
//   57  *
//   58  * 输出:
//   59  *    1-成功
//   60  *    0-失败
//   61  */

        SECTION `.text`:CODE:NOROOT(1)
        THUMB
//   62 uint8 LPLD_SCCB_WriteReg(uint16 reg_addr , uint8 data)
//   63 {
LPLD_SCCB_WriteReg:
        PUSH     {R3-R5,LR}
        MOVS     R4,R0
        MOVS     R5,R1
//   64   if(!LPLD_SCCB_Start())
        BL       LPLD_SCCB_Start
        CMP      R0,#+0
        BNE.N    ??LPLD_SCCB_WriteReg_0
//   65   {
//   66     return 0;
        MOVS     R0,#+0
        B.N      ??LPLD_SCCB_WriteReg_1
//   67   }
//   68   LPLD_SCCB_SendByte( SCCB_DEV_ADR );
??LPLD_SCCB_WriteReg_0:
        MOVS     R0,#+66
        BL       LPLD_SCCB_SendByte
//   69   if( !LPLD_SCCB_WaitAck() )
        BL       LPLD_SCCB_WaitAck
        CMP      R0,#+0
        BNE.N    ??LPLD_SCCB_WriteReg_2
//   70   {
//   71     LPLD_SCCB_Stop();
        BL       LPLD_SCCB_Stop
//   72     return 0;
        MOVS     R0,#+0
        B.N      ??LPLD_SCCB_WriteReg_1
//   73   }
//   74   LPLD_SCCB_SendByte((uint8)(reg_addr & 0x00FF));
??LPLD_SCCB_WriteReg_2:
        MOVS     R0,R4
        UXTB     R0,R0            ;; ZeroExt  R0,R0,#+24,#+24
        BL       LPLD_SCCB_SendByte
//   75   LPLD_SCCB_WaitAck();
        BL       LPLD_SCCB_WaitAck
//   76   LPLD_SCCB_SendByte(data);
        MOVS     R0,R5
        UXTB     R0,R0            ;; ZeroExt  R0,R0,#+24,#+24
        BL       LPLD_SCCB_SendByte
//   77   LPLD_SCCB_WaitAck();
        BL       LPLD_SCCB_WaitAck
//   78   LPLD_SCCB_Stop();
        BL       LPLD_SCCB_Stop
//   79   return 1;
        MOVS     R0,#+1
??LPLD_SCCB_WriteReg_1:
        POP      {R1,R4,R5,PC}    ;; return
//   80 }
//   81 
//   82 
//   83 
//   84 
//   85 /******************************************************************************************************************
//   86 * 函数名：SCCB_ReadByte
//   87 * 描述  ：读取一串数据
//   88 * 输入  ：- data: 存放读出数据 	- length: 待读出长度	- reg_addr: 待读出地址		 - DeviceAddress: 器件类型
//   89 * 输出  ：返回为:=1成功读入,=0失败
//   90 * 注意  ：无
//   91 **********************************************************************************************************************/
//   92 /*
//   93  * LPLD_SCCB_ReadReg
//   94  * 读SCCB设备寄存器
//   95  *
//   96  * 参数:
//   97  *    reg_addr--寄存器地址
//   98  *    *data--待存读出数据地址
//   99  *    length--读取长度
//  100  *
//  101  * 输出:
//  102  *    1-成功
//  103  *    0-失败
//  104  */

        SECTION `.text`:CODE:NOROOT(1)
        THUMB
//  105 uint8 LPLD_SCCB_ReadReg(uint8 reg_addr, uint8* data, uint16 length)
//  106 {
LPLD_SCCB_ReadReg:
        PUSH     {R4-R6,LR}
        MOVS     R4,R0
        MOVS     R5,R1
        MOVS     R6,R2
//  107   if(!LPLD_SCCB_Start())
        BL       LPLD_SCCB_Start
        CMP      R0,#+0
        BNE.N    ??LPLD_SCCB_ReadReg_0
//  108   {
//  109     return 0;
        MOVS     R0,#+0
        B.N      ??LPLD_SCCB_ReadReg_1
//  110   }
//  111   LPLD_SCCB_SendByte( SCCB_DEV_ADR );
??LPLD_SCCB_ReadReg_0:
        MOVS     R0,#+66
        BL       LPLD_SCCB_SendByte
//  112   if( !LPLD_SCCB_WaitAck() )
        BL       LPLD_SCCB_WaitAck
        CMP      R0,#+0
        BNE.N    ??LPLD_SCCB_ReadReg_2
//  113   {
//  114     LPLD_SCCB_Stop();
        BL       LPLD_SCCB_Stop
//  115     return 0;
        MOVS     R0,#+0
        B.N      ??LPLD_SCCB_ReadReg_1
//  116   }
//  117   LPLD_SCCB_SendByte( reg_addr );
??LPLD_SCCB_ReadReg_2:
        MOVS     R0,R4
        UXTB     R0,R0            ;; ZeroExt  R0,R0,#+24,#+24
        BL       LPLD_SCCB_SendByte
//  118   LPLD_SCCB_WaitAck();
        BL       LPLD_SCCB_WaitAck
//  119   LPLD_SCCB_Stop();
        BL       LPLD_SCCB_Stop
//  120 
//  121   if(!LPLD_SCCB_Start())
        BL       LPLD_SCCB_Start
        CMP      R0,#+0
        BNE.N    ??LPLD_SCCB_ReadReg_3
//  122   {
//  123     return 0;
        MOVS     R0,#+0
        B.N      ??LPLD_SCCB_ReadReg_1
//  124   }
//  125   LPLD_SCCB_SendByte( SCCB_DEV_ADR + 1 );
??LPLD_SCCB_ReadReg_3:
        MOVS     R0,#+67
        BL       LPLD_SCCB_SendByte
//  126   if(!LPLD_SCCB_WaitAck())
        BL       LPLD_SCCB_WaitAck
        CMP      R0,#+0
        BNE.N    ??LPLD_SCCB_ReadReg_4
//  127   {
//  128     LPLD_SCCB_Stop();
        BL       LPLD_SCCB_Stop
//  129     return 0;
        MOVS     R0,#+0
        B.N      ??LPLD_SCCB_ReadReg_1
//  130   }
//  131   while(length)
//  132   {
//  133     *data = LPLD_SCCB_ReceiveByte();
//  134     if(length == 1)
//  135     {
//  136       LPLD_SCCB_NoAck();
//  137     }
//  138     else
//  139     {
//  140       LPLD_SCCB_Ack();
??LPLD_SCCB_ReadReg_5:
        BL       LPLD_SCCB_Ack
//  141     }
//  142     data++;
??LPLD_SCCB_ReadReg_6:
        ADDS     R5,R5,#+1
//  143     length--;
        SUBS     R6,R6,#+1
??LPLD_SCCB_ReadReg_4:
        UXTH     R6,R6            ;; ZeroExt  R6,R6,#+16,#+16
        CMP      R6,#+0
        BEQ.N    ??LPLD_SCCB_ReadReg_7
        BL       LPLD_SCCB_ReceiveByte
        STRB     R0,[R5, #+0]
        UXTH     R6,R6            ;; ZeroExt  R6,R6,#+16,#+16
        CMP      R6,#+1
        BNE.N    ??LPLD_SCCB_ReadReg_5
        BL       LPLD_SCCB_NoAck
        B.N      ??LPLD_SCCB_ReadReg_6
//  144   }
//  145   LPLD_SCCB_Stop();
??LPLD_SCCB_ReadReg_7:
        BL       LPLD_SCCB_Stop
//  146   return 1;
        MOVS     R0,#+1
??LPLD_SCCB_ReadReg_1:
        POP      {R4-R6,PC}       ;; return
//  147 }
//  148 
//  149 /*
//  150  * LPLD_SCCB_Start
//  151  * SCCB起始信号，内部调用
//  152  */

        SECTION `.text`:CODE:NOROOT(1)
        THUMB
//  153 static uint8 LPLD_SCCB_Start(void)
//  154 {
LPLD_SCCB_Start:
        PUSH     {R7,LR}
//  155   SCCB_SDA_O=1;
        MOVS     R0,#+1
        LDR.N    R1,??DataTable7_1  ;; 0x43fe0064
        STR      R0,[R1, #+0]
//  156   SCCB_SCL=1;
        MOVS     R0,#+1
        LDR.N    R1,??DataTable7_2  ;; 0x43fe0068
        STR      R0,[R1, #+0]
//  157   SCCB_DELAY();
        MOVW     R0,#+5000
        BL       LPLD_SCCB_Delay
//  158 
//  159   SCCB_SDA_IN();
        MOVS     R0,#+0
        LDR.N    R1,??DataTable7_3  ;; 0x43fe02e4
        STR      R0,[R1, #+0]
//  160   if(!SCCB_SDA_I)
        LDR.N    R0,??DataTable7_4  ;; 0x43fe0264
        LDR      R0,[R0, #+0]
        CMP      R0,#+0
        BNE.N    ??LPLD_SCCB_Start_0
//  161   {
//  162     SCCB_SDA_OUT();
        MOVS     R0,#+1
        LDR.N    R1,??DataTable7_3  ;; 0x43fe02e4
        STR      R0,[R1, #+0]
//  163     return 0;
        MOVS     R0,#+0
        B.N      ??LPLD_SCCB_Start_1
//  164   }
//  165   SCCB_SDA_OUT();
??LPLD_SCCB_Start_0:
        MOVS     R0,#+1
        LDR.N    R1,??DataTable7_3  ;; 0x43fe02e4
        STR      R0,[R1, #+0]
//  166   SCCB_SDA_O=0;
        MOVS     R0,#+0
        LDR.N    R1,??DataTable7_1  ;; 0x43fe0064
        STR      R0,[R1, #+0]
//  167 
//  168   SCCB_DELAY();
        MOVW     R0,#+5000
        BL       LPLD_SCCB_Delay
//  169 
//  170   SCCB_SDA_IN();
        MOVS     R0,#+0
        LDR.N    R1,??DataTable7_3  ;; 0x43fe02e4
        STR      R0,[R1, #+0]
//  171   if(SCCB_SDA_I)
        LDR.N    R0,??DataTable7_4  ;; 0x43fe0264
        LDR      R0,[R0, #+0]
        CMP      R0,#+0
        BEQ.N    ??LPLD_SCCB_Start_2
//  172   {
//  173     SCCB_SDA_OUT();
        MOVS     R0,#+1
        LDR.N    R1,??DataTable7_3  ;; 0x43fe02e4
        STR      R0,[R1, #+0]
//  174     return 0;
        MOVS     R0,#+0
        B.N      ??LPLD_SCCB_Start_1
//  175   }
//  176   SCCB_SDA_OUT();
??LPLD_SCCB_Start_2:
        MOVS     R0,#+1
        LDR.N    R1,??DataTable7_3  ;; 0x43fe02e4
        STR      R0,[R1, #+0]
//  177   SCCB_SDA_O=0;
        MOVS     R0,#+0
        LDR.N    R1,??DataTable7_1  ;; 0x43fe0064
        STR      R0,[R1, #+0]
//  178 
//  179   return 1;
        MOVS     R0,#+1
??LPLD_SCCB_Start_1:
        POP      {R1,PC}          ;; return
//  180 }
//  181 
//  182 /*
//  183  * LPLD_SCCB_Stop
//  184  * SCCB停止信号，内部调用
//  185  */

        SECTION `.text`:CODE:NOROOT(1)
        THUMB
//  186 static void LPLD_SCCB_Stop(void)
//  187 {
LPLD_SCCB_Stop:
        PUSH     {R7,LR}
//  188   SCCB_SCL=0;
        MOVS     R0,#+0
        LDR.N    R1,??DataTable7_2  ;; 0x43fe0068
        STR      R0,[R1, #+0]
//  189   SCCB_SDA_O=0;
        MOVS     R0,#+0
        LDR.N    R1,??DataTable7_1  ;; 0x43fe0064
        STR      R0,[R1, #+0]
//  190   SCCB_DELAY();
        MOVW     R0,#+5000
        BL       LPLD_SCCB_Delay
//  191 
//  192   SCCB_SCL=1;
        MOVS     R0,#+1
        LDR.N    R1,??DataTable7_2  ;; 0x43fe0068
        STR      R0,[R1, #+0]
//  193   SCCB_SDA_O=1;
        MOVS     R0,#+1
        LDR.N    R1,??DataTable7_1  ;; 0x43fe0064
        STR      R0,[R1, #+0]
//  194   SCCB_DELAY();
        MOVW     R0,#+5000
        BL       LPLD_SCCB_Delay
//  195 }
        POP      {R0,PC}          ;; return
//  196 
//  197 /*
//  198  * LPLD_SCCB_Stop
//  199  * SCCB应答信号，内部调用
//  200  */

        SECTION `.text`:CODE:NOROOT(1)
        THUMB
//  201 static void LPLD_SCCB_Ack(void)
//  202 {
LPLD_SCCB_Ack:
        PUSH     {R7,LR}
//  203   SCCB_SCL=0;
        MOVS     R0,#+0
        LDR.N    R1,??DataTable7_2  ;; 0x43fe0068
        STR      R0,[R1, #+0]
//  204   SCCB_DELAY();
        MOVW     R0,#+5000
        BL       LPLD_SCCB_Delay
//  205 
//  206   SCCB_SDA_O=0;
        MOVS     R0,#+0
        LDR.N    R1,??DataTable7_1  ;; 0x43fe0064
        STR      R0,[R1, #+0]
//  207   SCCB_DELAY();
        MOVW     R0,#+5000
        BL       LPLD_SCCB_Delay
//  208 
//  209   SCCB_SCL=1;
        MOVS     R0,#+1
        LDR.N    R1,??DataTable7_2  ;; 0x43fe0068
        STR      R0,[R1, #+0]
//  210   SCCB_DELAY();
        MOVW     R0,#+5000
        BL       LPLD_SCCB_Delay
//  211 
//  212   SCCB_SCL=0;
        MOVS     R0,#+0
        LDR.N    R1,??DataTable7_2  ;; 0x43fe0068
        STR      R0,[R1, #+0]
//  213   SCCB_DELAY();
        MOVW     R0,#+5000
        BL       LPLD_SCCB_Delay
//  214 }
        POP      {R0,PC}          ;; return
//  215 
//  216 /*
//  217  * LPLD_SCCB_NoAck
//  218  * SCCB无应答信号，内部调用
//  219  */

        SECTION `.text`:CODE:NOROOT(1)
        THUMB
//  220 static void LPLD_SCCB_NoAck(void)
//  221 {
LPLD_SCCB_NoAck:
        PUSH     {R7,LR}
//  222   SCCB_SCL=0;
        MOVS     R0,#+0
        LDR.N    R1,??DataTable7_2  ;; 0x43fe0068
        STR      R0,[R1, #+0]
//  223   SCCB_DELAY();
        MOVW     R0,#+5000
        BL       LPLD_SCCB_Delay
//  224   SCCB_SDA_O=1;
        MOVS     R0,#+1
        LDR.N    R1,??DataTable7_1  ;; 0x43fe0064
        STR      R0,[R1, #+0]
//  225   SCCB_DELAY();
        MOVW     R0,#+5000
        BL       LPLD_SCCB_Delay
//  226   SCCB_SCL=1;
        MOVS     R0,#+1
        LDR.N    R1,??DataTable7_2  ;; 0x43fe0068
        STR      R0,[R1, #+0]
//  227   SCCB_DELAY();
        MOVW     R0,#+5000
        BL       LPLD_SCCB_Delay
//  228   SCCB_SCL=0;
        MOVS     R0,#+0
        LDR.N    R1,??DataTable7_2  ;; 0x43fe0068
        STR      R0,[R1, #+0]
//  229   SCCB_DELAY();
        MOVW     R0,#+5000
        BL       LPLD_SCCB_Delay
//  230 }
        POP      {R0,PC}          ;; return
//  231 
//  232 /*
//  233  * LPLD_SCCB_WaitAck
//  234  * SCCB等待应答信号，内部调用
//  235  */

        SECTION `.text`:CODE:NOROOT(1)
        THUMB
//  236 static uint8 LPLD_SCCB_WaitAck(void)
//  237 {
LPLD_SCCB_WaitAck:
        PUSH     {R7,LR}
//  238   SCCB_SCL=0;
        MOVS     R0,#+0
        LDR.N    R1,??DataTable7_2  ;; 0x43fe0068
        STR      R0,[R1, #+0]
//  239   SCCB_DELAY();
        MOVW     R0,#+5000
        BL       LPLD_SCCB_Delay
//  240   SCCB_SDA_O=1;
        MOVS     R0,#+1
        LDR.N    R1,??DataTable7_1  ;; 0x43fe0064
        STR      R0,[R1, #+0]
//  241   SCCB_DELAY();
        MOVW     R0,#+5000
        BL       LPLD_SCCB_Delay
//  242 
//  243   SCCB_SCL=1;
        MOVS     R0,#+1
        LDR.N    R1,??DataTable7_2  ;; 0x43fe0068
        STR      R0,[R1, #+0]
//  244 
//  245   SCCB_SDA_IN();
        MOVS     R0,#+0
        LDR.N    R1,??DataTable7_3  ;; 0x43fe02e4
        STR      R0,[R1, #+0]
//  246   SCCB_DELAY();
        MOVW     R0,#+5000
        BL       LPLD_SCCB_Delay
//  247 
//  248   if(SCCB_SDA_I)
        LDR.N    R0,??DataTable7_4  ;; 0x43fe0264
        LDR      R0,[R0, #+0]
        CMP      R0,#+0
        BEQ.N    ??LPLD_SCCB_WaitAck_0
//  249   {
//  250     SCCB_SDA_OUT();
        MOVS     R0,#+1
        LDR.N    R1,??DataTable7_3  ;; 0x43fe02e4
        STR      R0,[R1, #+0]
//  251     SCCB_SCL=0;
        MOVS     R0,#+0
        LDR.N    R1,??DataTable7_2  ;; 0x43fe0068
        STR      R0,[R1, #+0]
//  252     return 0;
        MOVS     R0,#+0
        B.N      ??LPLD_SCCB_WaitAck_1
//  253   }
//  254   SCCB_SDA_OUT();
??LPLD_SCCB_WaitAck_0:
        MOVS     R0,#+1
        LDR.N    R1,??DataTable7_3  ;; 0x43fe02e4
        STR      R0,[R1, #+0]
//  255   SCCB_SCL=0;
        MOVS     R0,#+0
        LDR.N    R1,??DataTable7_2  ;; 0x43fe0068
        STR      R0,[R1, #+0]
//  256   return 1;
        MOVS     R0,#+1
??LPLD_SCCB_WaitAck_1:
        POP      {R1,PC}          ;; return
//  257 }
//  258 
//  259 /*
//  260  * LPLD_SCCB_SendByte
//  261  * SCCB发送数据，内部调用
//  262  */

        SECTION `.text`:CODE:NOROOT(1)
        THUMB
//  263 static void LPLD_SCCB_SendByte(uint8 data)
//  264 {
LPLD_SCCB_SendByte:
        PUSH     {R3-R5,LR}
        MOVS     R4,R0
//  265   uint8 i=8;
        MOVS     R5,#+8
        B.N      ??LPLD_SCCB_SendByte_0
//  266   while(i--)
//  267   {
//  268     SCCB_SCL=0;
//  269     SCCB_DELAY();
//  270     if(data&0x80)
//  271     {
//  272       SCCB_SDA_O=1;
//  273     }
//  274     else
//  275     {
//  276       SCCB_SDA_O=0;
??LPLD_SCCB_SendByte_1:
        MOVS     R0,#+0
        LDR.N    R1,??DataTable7_1  ;; 0x43fe0064
        STR      R0,[R1, #+0]
//  277     }
//  278     data<<=1;
??LPLD_SCCB_SendByte_2:
        LSLS     R4,R4,#+1
//  279     SCCB_DELAY();
        MOVW     R0,#+5000
        BL       LPLD_SCCB_Delay
//  280     SCCB_SCL=1;
        MOVS     R0,#+1
        LDR.N    R1,??DataTable7_2  ;; 0x43fe0068
        STR      R0,[R1, #+0]
//  281     SCCB_DELAY();
        MOVW     R0,#+5000
        BL       LPLD_SCCB_Delay
??LPLD_SCCB_SendByte_0:
        MOVS     R0,R5
        SUBS     R5,R0,#+1
        UXTB     R0,R0            ;; ZeroExt  R0,R0,#+24,#+24
        CMP      R0,#+0
        BEQ.N    ??LPLD_SCCB_SendByte_3
        MOVS     R0,#+0
        LDR.N    R1,??DataTable7_2  ;; 0x43fe0068
        STR      R0,[R1, #+0]
        MOVW     R0,#+5000
        BL       LPLD_SCCB_Delay
        LSLS     R0,R4,#+24
        BPL.N    ??LPLD_SCCB_SendByte_1
        MOVS     R0,#+1
        LDR.N    R1,??DataTable7_1  ;; 0x43fe0064
        STR      R0,[R1, #+0]
        B.N      ??LPLD_SCCB_SendByte_2
//  282   }
//  283   SCCB_SCL=0;
??LPLD_SCCB_SendByte_3:
        MOVS     R0,#+0
        LDR.N    R1,??DataTable7_2  ;; 0x43fe0068
        STR      R0,[R1, #+0]
//  284 }
        POP      {R0,R4,R5,PC}    ;; return
//  285 
//  286 /*
//  287  * LPLD_SCCB_SendByte
//  288  * SCCB接收数据，内部调用
//  289  */

        SECTION `.text`:CODE:NOROOT(1)
        THUMB
//  290 static uint8 LPLD_SCCB_ReceiveByte(void)
//  291 {
LPLD_SCCB_ReceiveByte:
        PUSH     {R3-R5,LR}
//  292   uint8 i=8;
        MOVS     R4,#+8
//  293   uint8 ReceiveByte=0;
        MOVS     R5,#+0
//  294 
//  295   SCCB_SDA_O=1;
        MOVS     R0,#+1
        LDR.N    R1,??DataTable7_1  ;; 0x43fe0064
        STR      R0,[R1, #+0]
//  296   SCCB_DELAY();
        MOVW     R0,#+5000
        BL       LPLD_SCCB_Delay
//  297 
//  298   SCCB_SDA_IN();
        MOVS     R0,#+0
        LDR.N    R1,??DataTable7_3  ;; 0x43fe02e4
        STR      R0,[R1, #+0]
        B.N      ??LPLD_SCCB_ReceiveByte_0
//  299 
//  300   while(i--)
//  301   {
//  302     ReceiveByte<<=1;
??LPLD_SCCB_ReceiveByte_1:
        LSLS     R5,R5,#+1
//  303     SCCB_SCL=0;
        MOVS     R0,#+0
        LDR.N    R1,??DataTable7_2  ;; 0x43fe0068
        STR      R0,[R1, #+0]
//  304     SCCB_DELAY();
        MOVW     R0,#+5000
        BL       LPLD_SCCB_Delay
//  305 
//  306     SCCB_SCL=1;
        MOVS     R0,#+1
        LDR.N    R1,??DataTable7_2  ;; 0x43fe0068
        STR      R0,[R1, #+0]
//  307     SCCB_DELAY();
        MOVW     R0,#+5000
        BL       LPLD_SCCB_Delay
//  308 
//  309     if(SCCB_SDA_I)
        LDR.N    R0,??DataTable7_4  ;; 0x43fe0264
        LDR      R0,[R0, #+0]
        CMP      R0,#+0
        BEQ.N    ??LPLD_SCCB_ReceiveByte_0
//  310     {
//  311       ReceiveByte|=0x01;
        ORRS     R5,R5,#0x1
//  312     }
//  313 
//  314   }
??LPLD_SCCB_ReceiveByte_0:
        MOVS     R0,R4
        SUBS     R4,R0,#+1
        UXTB     R0,R0            ;; ZeroExt  R0,R0,#+24,#+24
        CMP      R0,#+0
        BNE.N    ??LPLD_SCCB_ReceiveByte_1
//  315   SCCB_SDA_OUT();
        MOVS     R0,#+1
        LDR.N    R1,??DataTable7_3  ;; 0x43fe02e4
        STR      R0,[R1, #+0]
//  316   SCCB_SCL=0;
        MOVS     R0,#+0
        LDR.N    R1,??DataTable7_2  ;; 0x43fe0068
        STR      R0,[R1, #+0]
//  317 
//  318   return ReceiveByte;
        MOVS     R0,R5
        UXTB     R0,R0            ;; ZeroExt  R0,R0,#+24,#+24
        POP      {R1,R4,R5,PC}    ;; return
//  319 }

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable7:
        DC32     0x400ff000

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable7_1:
        DC32     0x43fe0064

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable7_2:
        DC32     0x43fe0068

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable7_3:
        DC32     0x43fe02e4

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable7_4:
        DC32     0x43fe0264
//  320 
//  321 /*
//  322  * LPLD_SCCB_SendByte
//  323  * SCCB延时函数，内部调用
//  324  */

        SECTION `.text`:CODE:NOROOT(1)
        THUMB
//  325 static void LPLD_SCCB_Delay(uint16 i)
//  326 {
LPLD_SCCB_Delay:
        B.N      ??LPLD_SCCB_Delay_0
//  327   while(i)
//  328     i--;
??LPLD_SCCB_Delay_1:
        SUBS     R0,R0,#+1
??LPLD_SCCB_Delay_0:
        UXTH     R0,R0            ;; ZeroExt  R0,R0,#+16,#+16
        CMP      R0,#+0
        BNE.N    ??LPLD_SCCB_Delay_1
//  329 }
        BX       LR               ;; return

        SECTION `.iar_vfe_header`:DATA:NOALLOC:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
        DC32 0

        SECTION __DLIB_PERTHREAD:DATA:REORDER:NOROOT(0)
        SECTION_TYPE SHT_PROGBITS, 0

        SECTION __DLIB_PERTHREAD_init:DATA:REORDER:NOROOT(0)
        SECTION_TYPE SHT_PROGBITS, 0

        END
//  330 
//  331 
// 
// 828 bytes in section .text
// 
// 828 bytes of CODE memory
//
//Errors: none
//Warnings: none
