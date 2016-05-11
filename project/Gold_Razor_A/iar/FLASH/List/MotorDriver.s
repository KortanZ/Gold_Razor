///////////////////////////////////////////////////////////////////////////////
//
// IAR ANSI C/C++ Compiler V7.40.3.8902/W32 for ARM       09/May/2016  19:09:26
// Copyright 1999-2015 IAR Systems AB.
//
//    Cpu mode     =  thumb
//    Endian       =  little
//    Source file  =  
//        C:\Users\Administrator\Desktop\Gold_Razor_A\project\Gold_Razor_A\app\Source\MotorDriver.c
//    Command line =  
//        C:\Users\Administrator\Desktop\Gold_Razor_A\project\Gold_Razor_A\app\Source\MotorDriver.c
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
//        C:\Users\Administrator\Desktop\Gold_Razor_A\project\Gold_Razor_A\iar\FLASH\List\MotorDriver.s
//
///////////////////////////////////////////////////////////////////////////////

        #define SHT_PROGBITS 0x1

        EXTERN LPLD_FTM_Init
        EXTERN LPLD_FTM_PWM_ChangeDuty
        EXTERN LPLD_FTM_PWM_Enable
        EXTERN __aeabi_cfcmple
        EXTERN __aeabi_d2f
        EXTERN __aeabi_dadd
        EXTERN __aeabi_ddiv
        EXTERN __aeabi_dmul
        EXTERN __aeabi_f2d
        EXTERN __aeabi_memcpy4
        EXTERN __aeabi_ui2d

        PUBLIC Motor_Duty_Change
        PUBLIC Motor_Init
        PUBLIC PWM_Expect
        PUBLIC PWM_To_Pulse
        PUBLIC PulseNum_To_PWM

// C:\Users\Administrator\Desktop\Gold_Razor_A\project\Gold_Razor_A\app\Source\MotorDriver.c
//    1 /*
//    2 *This file for motor driver
//    3 *include initial and control
//    4 */
//    5 
//    6 //#include "common.h"
//    7 #include "MotorDriver.h"

        SECTION `.data`:DATA:REORDER:NOROOT(2)
//    8 int32 PWM_Expect = 1500;
PWM_Expect:
        DATA
        DC32 1500
//    9 

        SECTION `.text`:CODE:NOROOT(1)
        THUMB
//   10 void Motor_Init(void)
//   11 {
Motor_Init:
        PUSH     {LR}
        SUB      SP,SP,#+44
//   12 	/* Initial motor pwm */
//   13 
//   14 	FTM_InitTypeDef motorInitStruct;
//   15 
//   16     motorInitStruct.FTM_Ftmx = FTM0;
        LDR.N    R0,??DataTable3  ;; 0x40038000
        STR      R0,[SP, #+12]
//   17     motorInitStruct.FTM_Mode = FTM_MODE_PWM;
        MOVS     R0,#+1
        STRB     R0,[SP, #+16]
//   18     motorInitStruct.FTM_PwmFreq = MOTOR_FRE;
        MOVW     R0,#+10000
        STR      R0,[SP, #+20]
//   19     motorInitStruct.FTM_PwmDeadtimeCfg = DEADTIME_CH01;
        MOVS     R0,#+16
        STR      R0,[SP, #+24]
//   20     motorInitStruct.FTM_PwmDeadtimeDiv = DEADTIME_DIV1;
        MOVS     R0,#+0
        STRB     R0,[SP, #+28]
//   21     motorInitStruct.FTM_PwmDeadtimeVal = 0;
        MOVS     R0,#+0
        STRB     R0,[SP, #+29]
//   22 
//   23 
//   24     LPLD_FTM_Init(motorInitStruct);
        ADD      R1,SP,#+12
        SUB      SP,SP,#+16
        MOV      R0,SP
        MOVS     R2,#+28
        BL       __aeabi_memcpy4
        POP      {R0-R3}
        BL       LPLD_FTM_Init
//   25 /*----------left motor backward initial--------*/
//   26     LPLD_FTM_PWM_Enable(FTM0,
//   27                         FTM_Ch1,
//   28                         0,
//   29                         MOTOR_LEFT_BACKWARD,  //PTA4
//   30                         ALIGN_LEFT
//   31                         );
        MOVS     R0,#+40
        STR      R0,[SP, #+0]
        MOVS     R3,#+4
        MOVS     R2,#+0
        MOVS     R1,#+1
        LDR.N    R0,??DataTable3  ;; 0x40038000
        BL       LPLD_FTM_PWM_Enable
//   32 /*----------left motor forward initial--------*/
//   33     LPLD_FTM_PWM_Enable(FTM0,
//   34                         FTM_Ch2,
//   35                         0,
//   36                         MOTOR_LEFT_FORWARD,  //PTA5
//   37                         ALIGN_LEFT
//   38                         );
        MOVS     R0,#+40
        STR      R0,[SP, #+0]
        MOVS     R3,#+5
        MOVS     R2,#+0
        MOVS     R1,#+2
        LDR.N    R0,??DataTable3  ;; 0x40038000
        BL       LPLD_FTM_PWM_Enable
//   39 /*----------right motor backward initial--------*/
//   40     LPLD_FTM_PWM_Enable(FTM0,
//   41                         FTM_Ch3,
//   42                         0,
//   43                         MOTOR_RIGHT_BACKWARD,  //PTA6
//   44                         ALIGN_LEFT
//   45                         );
        MOVS     R0,#+40
        STR      R0,[SP, #+0]
        MOVS     R3,#+6
        MOVS     R2,#+0
        MOVS     R1,#+3
        LDR.N    R0,??DataTable3  ;; 0x40038000
        BL       LPLD_FTM_PWM_Enable
//   46 /*----------righ motor forward initial--------*/
//   47     LPLD_FTM_PWM_Enable(FTM0,
//   48                         FTM_Ch4,
//   49                         0,
//   50                         MOTOR_RIGHT_FORWARD,  //PTA7
//   51                         ALIGN_LEFT
//   52                         );
        MOVS     R0,#+40
        STR      R0,[SP, #+0]
        MOVS     R3,#+7
        MOVS     R2,#+0
        MOVS     R1,#+4
        LDR.N    R0,??DataTable3  ;; 0x40038000
        BL       LPLD_FTM_PWM_Enable
//   53 }
        ADD      SP,SP,#+44
        POP      {PC}             ;; return
//   54 

        SECTION `.text`:CODE:NOROOT(1)
        THUMB
//   55 void Motor_Duty_Change(MotorPosition motorPos, int32 tagetDuty)
//   56 {
Motor_Duty_Change:
        PUSH     {R4,LR}
        MOVS     R4,R1
//   57 
//   58     /* Set motor threshold */
//   59     if (tagetDuty > 9000)
        MOVW     R1,#+9001
        CMP      R4,R1
        BLT.N    ??Motor_Duty_Change_0
//   60     {
//   61         tagetDuty = 9000;
        MOVW     R4,#+9000
        B.N      ??Motor_Duty_Change_1
//   62     }
//   63     else if (tagetDuty < -9000)
??Motor_Duty_Change_0:
        LDR.N    R1,??DataTable3_1  ;; 0xffffdcd8
        CMP      R4,R1
        BGE.N    ??Motor_Duty_Change_1
//   64     {
//   65         tagetDuty = -9000;
        LDR.N    R4,??DataTable3_1  ;; 0xffffdcd8
//   66     }
//   67 
//   68 	switch (motorPos)
??Motor_Duty_Change_1:
        UXTB     R0,R0            ;; ZeroExt  R0,R0,#+24,#+24
        CMP      R0,#+0
        BEQ.N    ??Motor_Duty_Change_2
        CMP      R0,#+1
        BEQ.N    ??Motor_Duty_Change_3
        B.N      ??Motor_Duty_Change_4
//   69 	{
//   70 		case MOTOR_LEFT :
//   71 			LPLD_FTM_PWM_ChangeDuty(FTM0, FTM_Ch1, tagetDuty > 0 ? 0 : (uint32)(-tagetDuty));
??Motor_Duty_Change_2:
        CMP      R4,#+1
        BLT.N    ??Motor_Duty_Change_5
        MOVS     R2,#+0
        B.N      ??Motor_Duty_Change_6
??Motor_Duty_Change_5:
        RSBS     R2,R4,#+0
??Motor_Duty_Change_6:
        MOVS     R1,#+1
        LDR.N    R0,??DataTable3  ;; 0x40038000
        BL       LPLD_FTM_PWM_ChangeDuty
//   72 			LPLD_FTM_PWM_ChangeDuty(FTM0, FTM_Ch2, tagetDuty > 0 ? (uint32)tagetDuty : 0);
        CMP      R4,#+1
        BGE.N    ??Motor_Duty_Change_7
??Motor_Duty_Change_8:
        MOVS     R4,#+0
??Motor_Duty_Change_7:
        MOVS     R2,R4
        MOVS     R1,#+2
        LDR.N    R0,??DataTable3  ;; 0x40038000
        BL       LPLD_FTM_PWM_ChangeDuty
//   73 			break;
        B.N      ??Motor_Duty_Change_4
//   74 		case MOTOR_RIGHT :
//   75 			LPLD_FTM_PWM_ChangeDuty(FTM0, FTM_Ch3, tagetDuty > 0 ? 0 : (uint32)(-tagetDuty));
??Motor_Duty_Change_3:
        CMP      R4,#+1
        BLT.N    ??Motor_Duty_Change_9
        MOVS     R2,#+0
        B.N      ??Motor_Duty_Change_10
??Motor_Duty_Change_9:
        RSBS     R2,R4,#+0
??Motor_Duty_Change_10:
        MOVS     R1,#+3
        LDR.N    R0,??DataTable3  ;; 0x40038000
        BL       LPLD_FTM_PWM_ChangeDuty
//   76 			LPLD_FTM_PWM_ChangeDuty(FTM0, FTM_Ch4, tagetDuty > 0 ? (uint32)tagetDuty : 0);
        CMP      R4,#+1
        BGE.N    ??Motor_Duty_Change_11
??Motor_Duty_Change_12:
        MOVS     R4,#+0
??Motor_Duty_Change_11:
        MOVS     R2,R4
        MOVS     R1,#+4
        LDR.N    R0,??DataTable3  ;; 0x40038000
        BL       LPLD_FTM_PWM_ChangeDuty
//   77             break;
//   78 	}
//   79 }
??Motor_Duty_Change_4:
        POP      {R4,PC}          ;; return

        SECTION `.text`:CODE:NOROOT(1)
        THUMB
//   80 float32 PulseNum_To_PWM(float32 pulseNum)
//   81 {
PulseNum_To_PWM:
        PUSH     {R7,LR}
//   82 	/* This function convert pulse number to rotational speed */
//   83 
//   84 	float32 pwm;
//   85 	pwm = (pulseNum + 319.8) / 0.5724;
        BL       __aeabi_f2d
        LDR.N    R2,??DataTable3_2  ;; 0xcccccccd
        LDR.N    R3,??DataTable3_3  ;; 0x4073fccc
        BL       __aeabi_dadd
        LDR.N    R2,??DataTable3_4  ;; 0xce075f70
        LDR.N    R3,??DataTable3_5  ;; 0x3fe25119
        BL       __aeabi_ddiv
        BL       __aeabi_d2f
//   86 	return pwm;
        POP      {R1,PC}          ;; return
//   87 }
//   88 

        SECTION `.text`:CODE:NOROOT(1)
        THUMB
//   89 float32 PWM_To_Pulse(uint32 pwm)
//   90 {
PWM_To_Pulse:
        PUSH     {R7,LR}
//   91 	float32 pulse;
//   92 	pulse = 0.5724 * pwm - 319.8;
        BL       __aeabi_ui2d
        LDR.N    R2,??DataTable3_4  ;; 0xce075f70
        LDR.N    R3,??DataTable3_5  ;; 0x3fe25119
        BL       __aeabi_dmul
        LDR.N    R2,??DataTable3_2  ;; 0xcccccccd
        LDR.N    R3,??DataTable3_6  ;; 0xc073fccc
        BL       __aeabi_dadd
        BL       __aeabi_d2f
//   93 
//   94 	if (pulse < 0)
        MOVS     R1,#+0
        BL       __aeabi_cfcmple
        BCS.N    ??PWM_To_Pulse_0
//   95 	{
//   96 		pulse = 0;
        MOVS     R0,#+0
//   97 	}
//   98 
//   99 	return pulse;
??PWM_To_Pulse_0:
        POP      {R1,PC}          ;; return
//  100 }

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable3:
        DC32     0x40038000

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable3_1:
        DC32     0xffffdcd8

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable3_2:
        DC32     0xcccccccd

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable3_3:
        DC32     0x4073fccc

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable3_4:
        DC32     0xce075f70

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable3_5:
        DC32     0x3fe25119

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable3_6:
        DC32     0xc073fccc

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
// 326 bytes in section .text
// 
// 326 bytes of CODE memory
//   4 bytes of DATA memory
//
//Errors: none
//Warnings: none
