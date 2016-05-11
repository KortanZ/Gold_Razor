///////////////////////////////////////////////////////////////////////////////
//
// IAR ANSI C/C++ Compiler V7.40.3.8902/W32 for ARM       11/May/2016  19:10:52
// Copyright 1999-2015 IAR Systems AB.
//
//    Cpu mode     =  thumb
//    Endian       =  little
//    Source file  =  
//        E:\11ΩÏFreescale\Gold_Razor_A\Gold_Razor_A\project\Gold_Razor_A\app\Source\DebugerDriver.c
//    Command line =  
//        E:\11ΩÏFreescale\Gold_Razor_A\Gold_Razor_A\project\Gold_Razor_A\app\Source\DebugerDriver.c
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
//        E:\11ΩÏFreescale\Gold_Razor_A\Gold_Razor_A\project\Gold_Razor_A\iar\FLASH\List\DebugerDriver.s
//
///////////////////////////////////////////////////////////////////////////////

        #define SHT_PROGBITS 0x1

        EXTERN LPLD_GPIO_EnableIrq
        EXTERN LPLD_GPIO_Init
        EXTERN LPLD_UART_Init
        EXTERN Menu_Data_Decrease
        EXTERN Menu_Data_Increase
        EXTERN Menu_Show
        EXTERN __aeabi_memcpy4
        EXTERN currentList
        EXTERN menuList

        PUBLIC Keyboard_GPIO_Init
        PUBLIC Keyboard_Isr
        PUBLIC Keybord_Delay
        PUBLIC LED_Debuger_Init
        PUBLIC Time_Counter_Get
        PUBLIC Time_Counter_Start
        PUBLIC UART_Debuger_Init
        PUBLIC steerDebugDuty

// E:\11ΩÏFreescale\Gold_Razor_A\Gold_Razor_A\project\Gold_Razor_A\app\Source\DebugerDriver.c
//    1 /*
//    2 *This file for debuger driver
//    3 *include UART and GPIO initial
//    4 *include timer initial
//    5 */
//    6 //#include "common.h"
//    7 #include "Menu.h"
//    8 #include "DebugerDriver.h"
//    9 

        SECTION `.data`:DATA:REORDER:NOROOT(2)
//   10 uint32 steerDebugDuty = 1431;
steerDebugDuty:
        DATA
        DC32 1431
//   11 #if (!Twin_Car)

        SECTION `.text`:CODE:NOROOT(1)
        THUMB
//   12 void UART_Debuger_Init(void)
//   13 {
UART_Debuger_Init:
        PUSH     {LR}
        SUB      SP,SP,#+44
//   14 	UART_InitTypeDef uartInitStruct;
//   15 	uartInitStruct.UART_Uartx = UART2; //‰ΩøÁî®UART2
        LDR.N    R0,??DataTable5  ;; 0x4006c000
        STR      R0,[SP, #+12]
//   16 	uartInitStruct.UART_BaudRate = 115200; //ËÆæÁΩÆÊ≥¢ÁâπÁéá115200
        MOVS     R0,#+115200
        STR      R0,[SP, #+16]
//   17 	uartInitStruct.UART_RxPin = PTD2;  //Êé•Êî∂ÂºïËÑö‰∏∫PTD2
        MOVS     R0,#+94
        STRB     R0,[SP, #+21]
//   18 	uartInitStruct.UART_TxPin = PTD3;  //ÂèëÈÄÅÂºïËÑö‰∏∫PTD3
        MOVS     R0,#+95
        STRB     R0,[SP, #+20]
//   19 	//ÂàùÂßãÂåñUART
//   20 	LPLD_UART_Init(uartInitStruct);
        ADD      R1,SP,#+12
        SUB      SP,SP,#+16
        MOV      R0,SP
        MOVS     R2,#+28
        BL       __aeabi_memcpy4
        POP      {R0-R3}
        BL       LPLD_UART_Init
//   21 }
        ADD      SP,SP,#+44
        POP      {PC}             ;; return
//   22 #else
//   23 void UART_Blooth_Init(void)
//   24 {
//   25 
//   26 }
//   27 #endif
//   28 

        SECTION `.text`:CODE:NOROOT(1)
        THUMB
//   29 void LED_Debuger_Init(void)
//   30 {
LED_Debuger_Init:
        PUSH     {LR}
        SUB      SP,SP,#+28
//   31 	GPIO_InitTypeDef gpioInitStruct;
//   32 
//   33 	//--------------------K60_LED-------------------
//   34 	gpioInitStruct.GPIO_PTx = PTA;
        LDR.N    R0,??DataTable5_1  ;; 0x400ff000
        STR      R0,[SP, #+4]
//   35 	gpioInitStruct.GPIO_Pins = GPIO_Pin17;
        MOVS     R0,#+131072
        STR      R0,[SP, #+8]
//   36 	gpioInitStruct.GPIO_Dir = DIR_OUTPUT;
        MOVS     R0,#+1
        STRB     R0,[SP, #+16]
//   37 	gpioInitStruct.GPIO_Output = OUTPUT_H;
        MOVS     R0,#+1
        STRB     R0,[SP, #+17]
//   38 	gpioInitStruct.GPIO_PinControl = IRQC_DIS;
        MOVS     R0,#+0
        STR      R0,[SP, #+12]
//   39 	LPLD_GPIO_Init(gpioInitStruct);   /* */
        ADD      R1,SP,#+4
        SUB      SP,SP,#+16
        MOV      R0,SP
        MOVS     R2,#+20
        BL       __aeabi_memcpy4
        POP      {R0-R3}
        BL       LPLD_GPIO_Init
//   40 	//---------------------Razor_LED----------------
//   41 	gpioInitStruct.GPIO_PTx = PTE;
        LDR.N    R0,??DataTable5_2  ;; 0x400ff100
        STR      R0,[SP, #+4]
//   42 	gpioInitStruct.GPIO_Pins = GPIO_Pin10;
        MOV      R0,#+1024
        STR      R0,[SP, #+8]
//   43 	gpioInitStruct.GPIO_Dir = DIR_OUTPUT;
        MOVS     R0,#+1
        STRB     R0,[SP, #+16]
//   44 	gpioInitStruct.GPIO_Output = OUTPUT_L;
        MOVS     R0,#+0
        STRB     R0,[SP, #+17]
//   45 	gpioInitStruct.GPIO_PinControl = IRQC_DIS;
        MOVS     R0,#+0
        STR      R0,[SP, #+12]
//   46 	LPLD_GPIO_Init(gpioInitStruct);
        ADD      R1,SP,#+4
        SUB      SP,SP,#+16
        MOV      R0,SP
        MOVS     R2,#+20
        BL       __aeabi_memcpy4
        POP      {R0-R3}
        BL       LPLD_GPIO_Init
//   47 }
        ADD      SP,SP,#+28
        POP      {PC}             ;; return
//   48 

        SECTION `.text`:CODE:NOROOT(1)
        THUMB
//   49 void Keyboard_GPIO_Init(void)
//   50 {
Keyboard_GPIO_Init:
        PUSH     {LR}
        SUB      SP,SP,#+28
//   51 
//   52   	  GPIO_InitTypeDef keyboard_gpio_init_struct;
//   53 
//   54       keyboard_gpio_init_struct.GPIO_PTx = PTD;
        LDR.N    R0,??DataTable5_3  ;; 0x400ff0c0
        STR      R0,[SP, #+4]
//   55       keyboard_gpio_init_struct.GPIO_Pins = GPIO_Pin10 | GPIO_Pin11 | GPIO_Pin12 | GPIO_Pin13;
        MOV      R0,#+15360
        STR      R0,[SP, #+8]
//   56       keyboard_gpio_init_struct.GPIO_Dir = DIR_INPUT;
        MOVS     R0,#+0
        STRB     R0,[SP, #+16]
//   57       keyboard_gpio_init_struct.GPIO_Output = OUTPUT_L;
        MOVS     R0,#+0
        STRB     R0,[SP, #+17]
//   58       keyboard_gpio_init_struct.GPIO_PinControl = IRQC_FA | INPUT_PULL_UP;
        LDR.N    R0,??DataTable5_4  ;; 0xa0003
        STR      R0,[SP, #+12]
//   59       keyboard_gpio_init_struct.GPIO_Isr = Keyboard_Isr;
        ADR.W    R0,Keyboard_Isr
        STR      R0,[SP, #+20]
//   60       LPLD_GPIO_Init(keyboard_gpio_init_struct);
        ADD      R1,SP,#+4
        SUB      SP,SP,#+16
        MOV      R0,SP
        MOVS     R2,#+20
        BL       __aeabi_memcpy4
        POP      {R0-R3}
        BL       LPLD_GPIO_Init
//   61       LPLD_GPIO_EnableIrq(keyboard_gpio_init_struct);
        ADD      R1,SP,#+4
        SUB      SP,SP,#+16
        MOV      R0,SP
        MOVS     R2,#+20
        BL       __aeabi_memcpy4
        POP      {R0-R3}
        BL       LPLD_GPIO_EnableIrq
//   62 
//   63       keyboard_gpio_init_struct.GPIO_PTx = PTC;
        LDR.N    R0,??DataTable5_5  ;; 0x400ff080
        STR      R0,[SP, #+4]
//   64       keyboard_gpio_init_struct.GPIO_Pins = GPIO_Pin14 | GPIO_Pin15;
        MOV      R0,#+49152
        STR      R0,[SP, #+8]
//   65       keyboard_gpio_init_struct.GPIO_Dir = DIR_INPUT;
        MOVS     R0,#+0
        STRB     R0,[SP, #+16]
//   66       keyboard_gpio_init_struct.GPIO_Output = OUTPUT_L;
        MOVS     R0,#+0
        STRB     R0,[SP, #+17]
//   67       keyboard_gpio_init_struct.GPIO_PinControl = IRQC_FA | INPUT_PULL_UP;
        LDR.N    R0,??DataTable5_4  ;; 0xa0003
        STR      R0,[SP, #+12]
//   68       keyboard_gpio_init_struct.GPIO_Isr = Keyboard_Isr;
        ADR.W    R0,Keyboard_Isr
        STR      R0,[SP, #+20]
//   69       LPLD_GPIO_Init(keyboard_gpio_init_struct);
        ADD      R1,SP,#+4
        SUB      SP,SP,#+16
        MOV      R0,SP
        MOVS     R2,#+20
        BL       __aeabi_memcpy4
        POP      {R0-R3}
        BL       LPLD_GPIO_Init
//   70       LPLD_GPIO_EnableIrq(keyboard_gpio_init_struct);
        ADD      R1,SP,#+4
        SUB      SP,SP,#+16
        MOV      R0,SP
        MOVS     R2,#+20
        BL       __aeabi_memcpy4
        POP      {R0-R3}
        BL       LPLD_GPIO_EnableIrq
//   71 }
        ADD      SP,SP,#+28
        POP      {PC}             ;; return
//   72 

        SECTION `.text`:CODE:NOROOT(1)
        THUMB
//   73 void Time_Counter_Start(void)
//   74 {
//   75 	/* Timer count start */
//   76 	SIM->SCGC6 |= SIM_SCGC6_PIT_MASK;         //‰ΩøËÉΩPITÊó∂Èíü
Time_Counter_Start:
        LDR.N    R0,??DataTable5_6  ;; 0x4004803c
        LDR      R0,[R0, #+0]
        ORRS     R0,R0,#0x800000
        LDR.N    R1,??DataTable5_6  ;; 0x4004803c
        STR      R0,[R1, #+0]
//   77 	PIT->MCR &= ~(PIT_MCR_MDIS_MASK | PIT_MCR_FRZ_MASK);    //‰ΩøËÉΩPITÂÆöÊó∂Âô®Êó∂Èíü ÔºåË∞ÉËØïÊ®°Âºè‰∏ãÁªßÁª≠ËøêË°å
        LDR.N    R0,??DataTable5_7  ;; 0x40037000
        LDR      R0,[R0, #+0]
        LSRS     R0,R0,#+2
        LSLS     R0,R0,#+2
        LDR.N    R1,??DataTable5_7  ;; 0x40037000
        STR      R0,[R1, #+0]
//   78 	PIT->CHANNEL[0].TCTRL &= ~(PIT_TCTRL_TEN_MASK);
        LDR.N    R0,??DataTable5_8  ;; 0x40037108
        LDR      R0,[R0, #+0]
        LSRS     R0,R0,#+1
        LSLS     R0,R0,#+1
        LDR.N    R1,??DataTable5_8  ;; 0x40037108
        STR      R0,[R1, #+0]
//   79 	PIT->CHANNEL[0].LDVAL = ~0;							 //ËÆæÁΩÆÊ∫¢Âá∫‰∏≠Êñ≠Êó∂Èó¥
        MOVS     R0,#-1
        LDR.N    R1,??DataTable5_9  ;; 0x40037100
        STR      R0,[R1, #+0]
//   80 	PIT->CHANNEL[0].TFLG |= PIT_TFLG_TIF_MASK;
        LDR.N    R0,??DataTable5_10  ;; 0x4003710c
        LDR      R0,[R0, #+0]
        ORRS     R0,R0,#0x1
        LDR.N    R1,??DataTable5_10  ;; 0x4003710c
        STR      R0,[R1, #+0]
//   81 	PIT->CHANNEL[0].TCTRL &= ~PIT_TCTRL_TEN_MASK;
        LDR.N    R0,??DataTable5_8  ;; 0x40037108
        LDR      R0,[R0, #+0]
        LSRS     R0,R0,#+1
        LSLS     R0,R0,#+1
        LDR.N    R1,??DataTable5_8  ;; 0x40037108
        STR      R0,[R1, #+0]
//   82 	PIT->CHANNEL[0].TCTRL |= (0 | PIT_TCTRL_TEN_MASK);
        LDR.N    R0,??DataTable5_8  ;; 0x40037108
        LDR      R0,[R0, #+0]
        ORRS     R0,R0,#0x1
        LDR.N    R1,??DataTable5_8  ;; 0x40037108
        STR      R0,[R1, #+0]
//   83 }
        BX       LR               ;; return
//   84 

        SECTION `.text`:CODE:NOROOT(1)
        THUMB
//   85 uint32 Time_Counter_Get(void)
//   86 {
//   87 	/* Timer count end */
//   88 	uint32 val;
//   89 	val = (~0) - PIT->CHANNEL[0].CVAL;
Time_Counter_Get:
        MOVS     R0,#-1
        LDR.N    R1,??DataTable5_11  ;; 0x40037104
        LDR      R1,[R1, #+0]
        SUBS     R0,R0,R1
//   90 	if (PIT->CHANNEL[0].TFLG & PIT_TFLG_TIF_MASK)
        LDR.N    R1,??DataTable5_10  ;; 0x4003710c
        LDR      R1,[R1, #+0]
        LSLS     R1,R1,#+31
        BPL.N    ??Time_Counter_Get_0
//   91 	{
//   92 		PIT->CHANNEL[0].TFLG |= PIT_TFLG_TIF_MASK;
        LDR.N    R0,??DataTable5_10  ;; 0x4003710c
        LDR      R0,[R0, #+0]
        ORRS     R0,R0,#0x1
        LDR.N    R1,??DataTable5_10  ;; 0x4003710c
        STR      R0,[R1, #+0]
//   93 		PIT->CHANNEL[0].TCTRL &= ~PIT_TCTRL_TEN_MASK;
        LDR.N    R0,??DataTable5_8  ;; 0x40037108
        LDR      R0,[R0, #+0]
        LSRS     R0,R0,#+1
        LSLS     R0,R0,#+1
        LDR.N    R1,??DataTable5_8  ;; 0x40037108
        STR      R0,[R1, #+0]
//   94 		return ~0;
        MOVS     R0,#-1
        B.N      ??Time_Counter_Get_1
//   95 	}
//   96 	if (val == (~0))
??Time_Counter_Get_0:
        CMN      R0,#+1
        BNE.N    ??Time_Counter_Get_2
//   97 	{
//   98 		val--;              //Á°Æ‰øù ‰∏çÁ≠â‰∫é ~0
        SUBS     R0,R0,#+1
//   99 	}
//  100 	return val;
??Time_Counter_Get_2:
??Time_Counter_Get_1:
        BX       LR               ;; return
//  101 }
//  102 

        SECTION `.text`:CODE:NOROOT(2)
        THUMB
//  103 void Keybord_Delay(void)
//  104 {
//  105 	uint16 i, n;
//  106 	for (i = 0; i<15000; i++)
Keybord_Delay:
        MOVS     R0,#+0
        B.N      ??Keybord_Delay_0
//  107 	{
//  108 		for (n = 0; n<50; n++)
//  109 		{
//  110 			asm("nop");
??Keybord_Delay_1:
        nop
//  111 		}
        ADDS     R1,R1,#+1
??Keybord_Delay_2:
        UXTH     R1,R1            ;; ZeroExt  R1,R1,#+16,#+16
        CMP      R1,#+50
        BLT.N    ??Keybord_Delay_1
        ADDS     R0,R0,#+1
??Keybord_Delay_0:
        UXTH     R0,R0            ;; ZeroExt  R0,R0,#+16,#+16
        MOVW     R1,#+15000
        CMP      R0,R1
        BGE.N    ??Keybord_Delay_3
        MOVS     R1,#+0
        B.N      ??Keybord_Delay_2
//  112 	}
//  113 }
??Keybord_Delay_3:
        BX       LR               ;; return
//  114 

        SECTION `.text`:CODE:NOROOT(2)
        THUMB
//  115 void Keyboard_Isr(void)
//  116 {
Keyboard_Isr:
        PUSH     {R7,LR}
//  117 	//Á°ÆÂÆö
//  118 	if(LPLD_GPIO_IsPinxExt(PORTC, GPIO_Pin14))
        LDR.N    R0,??DataTable5_12  ;; 0x4004b0a0
        LDR      R0,[R0, #+0]
        LSLS     R0,R0,#+17
        BPL.N    ??Keyboard_Isr_0
//  119   	{
//  120   		currentList = menuList[currentList].child;
        LDR.N    R0,??DataTable5_13
        LDR.N    R1,??DataTable5_14
        LDRB     R1,[R1, #+0]
        MOVS     R2,#+20
        MLA      R0,R2,R1,R0
        LDRB     R0,[R0, #+3]
        LDR.N    R1,??DataTable5_14
        STRB     R0,[R1, #+0]
//  121   	}
//  122 
//  123   	//ËøîÂõû
//  124   	if(LPLD_GPIO_IsPinxExt(PORTC, GPIO_Pin15))
??Keyboard_Isr_0:
        LDR.N    R0,??DataTable5_12  ;; 0x4004b0a0
        LDR      R0,[R0, #+0]
        LSLS     R0,R0,#+16
        BPL.N    ??Keyboard_Isr_1
//  125   	{
//  126   		currentList = menuList[currentList].parent;
        LDR.N    R0,??DataTable5_13
        LDR.N    R1,??DataTable5_14
        LDRB     R1,[R1, #+0]
        MOVS     R2,#+20
        MLA      R0,R2,R1,R0
        LDRB     R0,[R0, #+2]
        LDR.N    R1,??DataTable5_14
        STRB     R0,[R1, #+0]
//  127   	}
//  128 
//  129   	//Âêë‰∏ãÁøª
//  130   	if(LPLD_GPIO_IsPinxExt(PORTD, GPIO_Pin10))
??Keyboard_Isr_1:
        LDR.N    R0,??DataTable5_15  ;; 0x4004c0a0
        LDR      R0,[R0, #+0]
        LSLS     R0,R0,#+21
        BPL.N    ??Keyboard_Isr_2
//  131 	{
//  132 		currentList = menuList[currentList].next;
        LDR.N    R0,??DataTable5_13
        LDR.N    R1,??DataTable5_14
        LDRB     R1,[R1, #+0]
        MOVS     R2,#+20
        MLA      R0,R2,R1,R0
        LDRB     R0,[R0, #+1]
        LDR.N    R1,??DataTable5_14
        STRB     R0,[R1, #+0]
//  133 	}
//  134 
//  135 	//ÂÄºÂáè
//  136 	if(LPLD_GPIO_IsPinxExt(PORTD, GPIO_Pin11))
??Keyboard_Isr_2:
        LDR.N    R0,??DataTable5_15  ;; 0x4004c0a0
        LDR      R0,[R0, #+0]
        LSLS     R0,R0,#+20
        BPL.N    ??Keyboard_Isr_3
//  137 	{
//  138 		Menu_Data_Decrease(currentList);
        LDR.N    R0,??DataTable5_14
        LDRB     R0,[R0, #+0]
        BL       Menu_Data_Decrease
//  139 	}
//  140 
//  141 	//Âêë‰∏äÁøª
//  142 	if(LPLD_GPIO_IsPinxExt(PORTD, GPIO_Pin12))
??Keyboard_Isr_3:
        LDR.N    R0,??DataTable5_15  ;; 0x4004c0a0
        LDR      R0,[R0, #+0]
        LSLS     R0,R0,#+19
        BPL.N    ??Keyboard_Isr_4
//  143 	{
//  144 		currentList = menuList[currentList].previous;
        LDR.N    R0,??DataTable5_13
        LDR.N    R1,??DataTable5_14
        LDRB     R1,[R1, #+0]
        MOVS     R2,#+20
        MLA      R0,R2,R1,R0
        LDRB     R0,[R0, #+0]
        LDR.N    R1,??DataTable5_14
        STRB     R0,[R1, #+0]
//  145 	}
//  146 
//  147 	//ÂÄºÂ¢û
//  148 	if(LPLD_GPIO_IsPinxExt(PORTD, GPIO_Pin13))
??Keyboard_Isr_4:
        LDR.N    R0,??DataTable5_15  ;; 0x4004c0a0
        LDR      R0,[R0, #+0]
        LSLS     R0,R0,#+18
        BPL.N    ??Keyboard_Isr_5
//  149 	{
//  150 		Menu_Data_Increase(currentList);
        LDR.N    R0,??DataTable5_14
        LDRB     R0,[R0, #+0]
        BL       Menu_Data_Increase
//  151 	}
//  152 	Menu_Show();
??Keyboard_Isr_5:
        BL       Menu_Show
//  153 }
        POP      {R0,PC}          ;; return

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable5:
        DC32     0x4006c000

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable5_1:
        DC32     0x400ff000

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable5_2:
        DC32     0x400ff100

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable5_3:
        DC32     0x400ff0c0

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable5_4:
        DC32     0xa0003

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable5_5:
        DC32     0x400ff080

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable5_6:
        DC32     0x4004803c

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable5_7:
        DC32     0x40037000

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable5_8:
        DC32     0x40037108

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable5_9:
        DC32     0x40037100

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable5_10:
        DC32     0x4003710c

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable5_11:
        DC32     0x40037104

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable5_12:
        DC32     0x4004b0a0

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable5_13:
        DC32     menuList

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable5_14:
        DC32     currentList

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable5_15:
        DC32     0x4004c0a0

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
//   4 bytes in section .data
// 668 bytes in section .text
// 
// 668 bytes of CODE memory
//   4 bytes of DATA memory
//
//Errors: none
//Warnings: none
