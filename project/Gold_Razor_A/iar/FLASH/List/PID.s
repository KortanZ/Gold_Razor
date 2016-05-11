///////////////////////////////////////////////////////////////////////////////
//
// IAR ANSI C/C++ Compiler V7.40.3.8902/W32 for ARM       11/May/2016  19:10:53
// Copyright 1999-2015 IAR Systems AB.
//
//    Cpu mode     =  thumb
//    Endian       =  little
//    Source file  =  
//        E:\11½ìFreescale\Gold_Razor_A\Gold_Razor_A\project\Gold_Razor_A\app\Source\PID.c
//    Command line =  
//        E:\11½ìFreescale\Gold_Razor_A\Gold_Razor_A\project\Gold_Razor_A\app\Source\PID.c
//        -D LPLD_K60 -D USE_K60DZ10 -lCN
//        E:\11½ìFreescale\Gold_Razor_A\Gold_Razor_A\project\Gold_Razor_A\iar\FLASH\List\
//        -lB
//        E:\11½ìFreescale\Gold_Razor_A\Gold_Razor_A\project\Gold_Razor_A\iar\FLASH\List\
//        -o
//        E:\11½ìFreescale\Gold_Razor_A\Gold_Razor_A\project\Gold_Razor_A\iar\FLASH\Obj\
//        --no_cse --no_unroll --no_inline --no_code_motion --no_tbaa
//        --no_clustering --no_scheduling --debug --endian=little
//        --cpu=Cortex-M4 -e --fpu=None --dlib_config
//        D:\IAR\arm\INC\c\DLib_Config_Normal.h -I
//        E:\11½ìFreescale\Gold_Razor_A\Gold_Razor_A\project\Gold_Razor_A\iar\..\app\
//        -I
//        E:\11½ìFreescale\Gold_Razor_A\Gold_Razor_A\project\Gold_Razor_A\iar\..\app\Source\
//        -I
//        E:\11½ìFreescale\Gold_Razor_A\Gold_Razor_A\project\Gold_Razor_A\iar\..\..\..\lib\CPU\
//        -I
//        E:\11½ìFreescale\Gold_Razor_A\Gold_Razor_A\project\Gold_Razor_A\iar\..\..\..\lib\common\
//        -I
//        E:\11½ìFreescale\Gold_Razor_A\Gold_Razor_A\project\Gold_Razor_A\iar\..\..\..\lib\LPLD\
//        -I
//        E:\11½ìFreescale\Gold_Razor_A\Gold_Razor_A\project\Gold_Razor_A\iar\..\..\..\lib\LPLD\HW\
//        -I
//        E:\11½ìFreescale\Gold_Razor_A\Gold_Razor_A\project\Gold_Razor_A\iar\..\..\..\lib\LPLD\DEV\
//        -I
//        E:\11½ìFreescale\Gold_Razor_A\Gold_Razor_A\project\Gold_Razor_A\iar\..\..\..\lib\LPLD\FUNC\
//        -I
//        E:\11½ìFreescale\Gold_Razor_A\Gold_Razor_A\project\Gold_Razor_A\iar\..\..\..\lib\uCOS-II\Ports\
//        -I
//        E:\11½ìFreescale\Gold_Razor_A\Gold_Razor_A\project\Gold_Razor_A\iar\..\..\..\lib\uCOS-II\Source\
//        -I
//        E:\11½ìFreescale\Gold_Razor_A\Gold_Razor_A\project\Gold_Razor_A\iar\..\..\..\lib\FatFs\
//        -I
//        E:\11½ìFreescale\Gold_Razor_A\Gold_Razor_A\project\Gold_Razor_A\iar\..\..\..\lib\FatFs\option\
//        -I
//        E:\11½ìFreescale\Gold_Razor_A\Gold_Razor_A\project\Gold_Razor_A\iar\..\..\..\lib\USB\common\
//        -I
//        E:\11½ìFreescale\Gold_Razor_A\Gold_Razor_A\project\Gold_Razor_A\iar\..\..\..\lib\USB\driver\
//        -I
//        E:\11½ìFreescale\Gold_Razor_A\Gold_Razor_A\project\Gold_Razor_A\iar\..\..\..\lib\USB\descriptor\
//        -I
//        E:\11½ìFreescale\Gold_Razor_A\Gold_Razor_A\project\Gold_Razor_A\iar\..\..\..\lib\USB\class\
//        -Ol -I D:\IAR\arm\CMSIS\Include\ -D ARM_MATH_CM4
//    List file    =  
//        E:\11½ìFreescale\Gold_Razor_A\Gold_Razor_A\project\Gold_Razor_A\iar\FLASH\List\PID.s
//
///////////////////////////////////////////////////////////////////////////////

        #define SHT_PROGBITS 0x1

        EXTERN LPLD_FTM_PWM_ChangeDuty
        EXTERN MidAve
        EXTERN Motor_Duty_Change
        EXTERN OLED_ShowString
        EXTERN PWM_Expect
        EXTERN PWM_To_Pulse
        EXTERN PulseNum_To_PWM
        EXTERN __aeabi_cfcmple
        EXTERN __aeabi_cfrcmple
        EXTERN __aeabi_f2iz
        EXTERN __aeabi_f2uiz
        EXTERN __aeabi_fadd
        EXTERN __aeabi_fmul
        EXTERN __aeabi_fsub
        EXTERN __aeabi_i2f
        EXTERN malloc
        EXTERN printf

        PUBLIC DifferCtrler_Init
        PUBLIC Differ_Controller
        PUBLIC SpeedCtrler_Init
        PUBLIC Speed_Controller
        PUBLIC SteerCtrler_Init
        PUBLIC Steer_Controller
        PUBLIC differCtrler
        PUBLIC speedCtrler
        PUBLIC steerCtrler

// E:\11½ìFreescale\Gold_Razor_A\Gold_Razor_A\project\Gold_Razor_A\app\Source\PID.c
//    1 //#include "common.h"
//    2 #include "PID.h"
//    3 #include "Oled.h"
//    4 #include "Menu.h"
//    5 #include "MotorDriver.h"
//    6 #include "ImgProcess.h"
//    7 #include "SteerDriver.h"
//    8 
//    9 float32 Differ_Controller(PIDStruct *, float32 , float32 );
//   10 

        SECTION `.bss`:DATA:REORDER:NOROOT(2)
//   11 PIDStruct *speedCtrler;
speedCtrler:
        DS8 4

        SECTION `.bss`:DATA:REORDER:NOROOT(2)
//   12 PIDStruct *steerCtrler;
steerCtrler:
        DS8 4

        SECTION `.bss`:DATA:REORDER:NOROOT(2)
//   13 PIDStruct *differCtrler;
differCtrler:
        DS8 4
//   14 

        SECTION `.text`:CODE:NOROOT(1)
        THUMB
//   15 void Speed_Controller(PIDStruct *motorCtrler, float32 expect, float32 real)
//   16 {
Speed_Controller:
        PUSH     {R4-R6,LR}
        MOVS     R4,R0
        MOVS     R0,R1
        MOVS     R1,R2
//   17 	float32 PWMoutput_1 , PWMoutput_2;
//   18 	/* previous difference PID */
//   19 
//   20 	float32 incrementU;
//   21 
//   22 	motorCtrler -> error[0] = expect - real;
        BL       __aeabi_fsub
        STR      R0,[R4, #+12]
//   23 
//   24 	incrementU = (motorCtrler -> Kp) * ((motorCtrler -> error[0]) - (motorCtrler -> error[1]))
//   25 					 + (motorCtrler -> Ki) * (motorCtrler -> error[0]) + (motorCtrler -> Kd)
//   26 					 * ((motorCtrler -> u[0]) - 2 * (motorCtrler -> u[1]) + (motorCtrler -> u[2]))
//   27 					 - (motorCtrler -> Kd) * ((motorCtrler -> u[0]) - (motorCtrler -> u[1]));
        LDR      R0,[R4, #+12]
        LDR      R1,[R4, #+16]
        BL       __aeabi_fsub
        LDR      R1,[R4, #+0]
        BL       __aeabi_fmul
        MOVS     R5,R0
        LDR      R1,[R4, #+8]
        LDR      R0,[R4, #+12]
        BL       __aeabi_fmul
        MOVS     R1,R5
        BL       __aeabi_fadd
        MOVS     R5,R0
        LDR      R1,[R4, #+28]
        MOVS     R0,#+1073741824
        BL       __aeabi_fmul
        MOVS     R1,R0
        LDR      R0,[R4, #+24]
        BL       __aeabi_fsub
        LDR      R1,[R4, #+32]
        BL       __aeabi_fadd
        LDR      R1,[R4, #+4]
        BL       __aeabi_fmul
        MOVS     R1,R5
        BL       __aeabi_fadd
        MOVS     R5,R0
        LDR      R0,[R4, #+28]
        LDR      R1,[R4, #+24]
        BL       __aeabi_fsub
        LDR      R1,[R4, #+4]
        BL       __aeabi_fmul
        MOVS     R1,R5
        BL       __aeabi_fadd
        MOVS     R5,R0
//   28 
//   29 	/* anti-windup */
//   30 
//   31 	if ((motorCtrler -> u[1]) > U_MAX || (motorCtrler -> u[1]) < -U_MAX)
        LDR      R0,[R4, #+28]
        LDR.N    R1,??DataTable5  ;; 0x45960001
        BL       __aeabi_cfrcmple
        BLS.N    ??Speed_Controller_0
        LDR      R0,[R4, #+28]
        LDR.N    R1,??DataTable5_1  ;; 0xc5960000
        BL       __aeabi_cfcmple
        BCS.N    ??Speed_Controller_1
//   32 	{
//   33 		incrementU -= (motorCtrler -> Ki) * (motorCtrler -> error[0]);
??Speed_Controller_0:
        LDR      R1,[R4, #+8]
        LDR      R0,[R4, #+12]
        BL       __aeabi_fmul
        MOVS     R1,R0
        MOVS     R0,R5
        BL       __aeabi_fsub
        MOVS     R5,R0
//   34 	}
//   35 
//   36 	motorCtrler -> u[0] = (motorCtrler -> u[1]) + incrementU;
??Speed_Controller_1:
        LDR      R0,[R4, #+28]
        MOVS     R1,R5
        BL       __aeabi_fadd
        STR      R0,[R4, #+24]
//   37 
//   38 	motorCtrler -> u[2] = motorCtrler -> u[1];
        LDR      R0,[R4, #+28]
        STR      R0,[R4, #+32]
//   39 	motorCtrler -> u[1] = motorCtrler -> u[0];
        LDR      R0,[R4, #+24]
        STR      R0,[R4, #+28]
//   40 	motorCtrler -> error[1] = motorCtrler -> error[0];
        LDR      R0,[R4, #+12]
        STR      R0,[R4, #+16]
//   41 
//   42 	/*          Differ PID Control  Block      */
//   43 	float32 Differ_Temp = 0;
        MOVS     R6,#+0
//   44 	Differ_Temp = Differ_Controller(differCtrler , \ 
//   45 					 				STEER_MIDVALUE , \ 
//   46 	 				 				MidAve);
        LDR.N    R0,??DataTable5_2
        LDRSH    R0,[R0, #+0]
        BL       __aeabi_i2f
        MOVS     R2,R0
        LDR.N    R1,??DataTable5_3  ;; 0x42a00000
        LDR.N    R0,??DataTable5_4
        LDR      R0,[R0, #+0]
        BL       Differ_Controller
        MOVS     R6,R0
//   47 	PWMoutput_1 = motorCtrler -> u[0] + Differ_Temp;
        LDR      R0,[R4, #+24]
        MOVS     R1,R6
        BL       __aeabi_fadd
        MOVS     R5,R0
//   48 	PWMoutput_2 = motorCtrler -> u[0] - Differ_Temp;
        LDR      R0,[R4, #+24]
        MOVS     R1,R6
        BL       __aeabi_fsub
        MOVS     R4,R0
//   49 
//   50 
//   51 	Motor_Duty_Change(MOTOR_LEFT, (int32)PulseNum_To_PWM(PWMoutput_1));
        MOVS     R0,R5
        BL       PulseNum_To_PWM
        BL       __aeabi_f2iz
        MOVS     R1,R0
        MOVS     R0,#+0
        BL       Motor_Duty_Change
//   52 	Motor_Duty_Change(MOTOR_RIGHT, (int32)PulseNum_To_PWM(PWMoutput_2));
        MOVS     R0,R4
        BL       PulseNum_To_PWM
        BL       __aeabi_f2iz
        MOVS     R1,R0
        MOVS     R0,#+1
        BL       Motor_Duty_Change
//   53 }
        POP      {R4-R6,PC}       ;; return
//   54 

        SECTION `.text`:CODE:NOROOT(1)
        THUMB
//   55 void SpeedCtrler_Init(void)
//   56 {
SpeedCtrler_Init:
        PUSH     {R4,LR}
//   57 	/* Initial PID speedCtrler */
//   58 	int8 i;
//   59 
//   60 	speedCtrler = (PIDStruct *)malloc(sizeof(PIDStruct));
        MOVS     R0,#+36
        BL       malloc
        LDR.N    R1,??DataTable5_5
        STR      R0,[R1, #+0]
//   61 
//   62 	if (NULL == speedCtrler)
        LDR.N    R0,??DataTable5_5
        LDR      R0,[R0, #+0]
        CMP      R0,#+0
        BNE.N    ??SpeedCtrler_Init_0
//   63 	{
//   64 		printf("Memory alloc faild!\n");
        LDR.N    R0,??DataTable5_6
        BL       printf
//   65 		OLED_ShowString(0, 5, "Memory alloc faild!");
        LDR.N    R2,??DataTable5_7
        MOVS     R1,#+5
        MOVS     R0,#+0
        BL       OLED_ShowString
        B.N      ??SpeedCtrler_Init_1
//   66 	}
//   67 	else
//   68 	{
//   69 		speedCtrler -> Kp = 3.2;
??SpeedCtrler_Init_0:
        LDR.N    R0,??DataTable5_8  ;; 0x404ccccd
        LDR.N    R1,??DataTable5_5
        LDR      R1,[R1, #+0]
        STR      R0,[R1, #+0]
//   70 		speedCtrler -> Kd = 0.5;
        MOVS     R0,#+1056964608
        LDR.N    R1,??DataTable5_5
        LDR      R1,[R1, #+0]
        STR      R0,[R1, #+4]
//   71 		speedCtrler -> Ki = 0.8;
        LDR.N    R0,??DataTable5_9  ;; 0x3f4ccccd
        LDR.N    R1,??DataTable5_5
        LDR      R1,[R1, #+0]
        STR      R0,[R1, #+8]
//   72 		for (i = 0; i < 3; ++i)
        MOVS     R4,#+0
        B.N      ??SpeedCtrler_Init_2
//   73 		{
//   74 			speedCtrler -> error[i] = 0;
??SpeedCtrler_Init_3:
        MOVS     R0,#+0
        LDR.N    R1,??DataTable5_5
        LDR      R1,[R1, #+0]
        SXTB     R4,R4            ;; SignExt  R4,R4,#+24,#+24
        ADDS     R1,R1,R4, LSL #+2
        STR      R0,[R1, #+12]
//   75 			speedCtrler -> u[i] = PWM_To_Pulse(PWM_Expect);
        LDR.N    R0,??DataTable5_10
        LDR      R0,[R0, #+0]
        BL       PWM_To_Pulse
        LDR.N    R1,??DataTable5_5
        LDR      R1,[R1, #+0]
        SXTB     R4,R4            ;; SignExt  R4,R4,#+24,#+24
        ADDS     R1,R1,R4, LSL #+2
        STR      R0,[R1, #+24]
//   76 		}
        ADDS     R4,R4,#+1
??SpeedCtrler_Init_2:
        SXTB     R4,R4            ;; SignExt  R4,R4,#+24,#+24
        CMP      R4,#+3
        BLT.N    ??SpeedCtrler_Init_3
//   77 	}
//   78 }
??SpeedCtrler_Init_1:
        POP      {R4,PC}          ;; return
//   79 

        SECTION `.text`:CODE:NOROOT(1)
        THUMB
//   80 void Steer_Controller(PIDStruct *SteerCon_Data, float32 expect, float32 real)
//   81 {
Steer_Controller:
        PUSH     {R3-R5,LR}
        MOVS     R4,R0
        MOVS     R0,R2
//   82 	float32 incrementU;
//   83 
//   84 	SteerCon_Data -> error[2] = SteerCon_Data -> error[1];
        LDR      R2,[R4, #+16]
        STR      R2,[R4, #+20]
//   85 	SteerCon_Data -> error[1] = SteerCon_Data -> error[0];
        LDR      R2,[R4, #+12]
        STR      R2,[R4, #+16]
//   86 	SteerCon_Data -> error[0] = real - expect;
        BL       __aeabi_fsub
        STR      R0,[R4, #+12]
//   87 
//   88 	incrementU = (SteerCon_Data -> Kp) * ((SteerCon_Data -> error[0])           \ 
//   89 										   - (SteerCon_Data -> error[1]))  		\ 
//   90 			   + (SteerCon_Data -> Kd) * ((SteerCon_Data -> error[0])      		\ 
//   91 											- 2 * (SteerCon_Data -> error[1])   \ 
//   92 											+ (SteerCon_Data -> error[2]));
        LDR      R0,[R4, #+12]
        LDR      R1,[R4, #+16]
        BL       __aeabi_fsub
        LDR      R1,[R4, #+0]
        BL       __aeabi_fmul
        MOVS     R5,R0
        LDR      R1,[R4, #+16]
        MOVS     R0,#+1073741824
        BL       __aeabi_fmul
        MOVS     R1,R0
        LDR      R0,[R4, #+12]
        BL       __aeabi_fsub
        LDR      R1,[R4, #+20]
        BL       __aeabi_fadd
        LDR      R1,[R4, #+4]
        BL       __aeabi_fmul
        MOVS     R1,R5
        BL       __aeabi_fadd
        MOVS     R1,R0
//   93 
//   94 	SteerCon_Data -> u[2] = SteerCon_Data -> u[1];
        LDR      R0,[R4, #+28]
        STR      R0,[R4, #+32]
//   95 	SteerCon_Data -> u[1] = SteerCon_Data -> u[0];
        LDR      R0,[R4, #+24]
        STR      R0,[R4, #+28]
//   96 	SteerCon_Data -> u[0] = SteerCon_Data -> u[1] + incrementU;
        LDR      R0,[R4, #+28]
        BL       __aeabi_fadd
        STR      R0,[R4, #+24]
//   97 
//   98 	(SteerCon_Data -> u[0] > STEER_RIGHT_DUTY) ? (SteerCon_Data -> u[0] = STEER_RIGHT_DUTY) : (NULL);
        LDR      R0,[R4, #+24]
        LDR.N    R1,??DataTable5_11  ;; 0x44c30001
        BL       __aeabi_cfrcmple
        BHI.N    ??Steer_Controller_0
        LDR.N    R0,??DataTable5_12  ;; 0x44c30000
        STR      R0,[R4, #+24]
        LDR      R0,[R4, #+24]
        B.N      ??Steer_Controller_1
??Steer_Controller_0:
        MOVS     R0,#+0
//   99 	(SteerCon_Data -> u[0] < STEER_LEFT_DUTY) ? (SteerCon_Data -> u[0] = STEER_LEFT_DUTY) : (NULL);
??Steer_Controller_1:
        LDR      R0,[R4, #+24]
        LDR.N    R1,??DataTable5_13  ;; 0x44992000
        BL       __aeabi_cfcmple
        BCS.N    ??Steer_Controller_2
        LDR.N    R0,??DataTable5_13  ;; 0x44992000
        STR      R0,[R4, #+24]
        LDR      R0,[R4, #+24]
        B.N      ??Steer_Controller_3
??Steer_Controller_2:
        MOVS     R0,#+0
//  100 
//  101 	LPLD_FTM_PWM_ChangeDuty(FTM2, FTM_Ch0, (uint32) (SteerCon_Data -> u[0]));
??Steer_Controller_3:
        LDR      R0,[R4, #+24]
        BL       __aeabi_f2uiz
        MOVS     R2,R0
        MOVS     R1,#+0
        LDR.N    R0,??DataTable5_14  ;; 0x400b8000
        BL       LPLD_FTM_PWM_ChangeDuty
//  102 }
        POP      {R0,R4,R5,PC}    ;; return

        SECTION `.text`:CODE:NOROOT(1)
        THUMB
//  103 void SteerCtrler_Init(void)
//  104 {
SteerCtrler_Init:
        PUSH     {R7,LR}
//  105 	int8 i;
//  106 	steerCtrler = (PIDStruct *)malloc(sizeof(PIDStruct));
        MOVS     R0,#+36
        BL       malloc
        LDR.N    R1,??DataTable5_15
        STR      R0,[R1, #+0]
//  107 	if (NULL == steerCtrler)
        LDR.N    R0,??DataTable5_15
        LDR      R0,[R0, #+0]
        CMP      R0,#+0
        BNE.N    ??SteerCtrler_Init_0
//  108 	{
//  109 		printf("Memory alloc faild!\n");
        LDR.N    R0,??DataTable5_6
        BL       printf
//  110 		OLED_ShowString(0, 5, "Memory alloc faild!");
        LDR.N    R2,??DataTable5_7
        MOVS     R1,#+5
        MOVS     R0,#+0
        BL       OLED_ShowString
        B.N      ??SteerCtrler_Init_1
//  111 	}
//  112 	else
//  113 	{
//  114 		steerCtrler -> Kp = 5;
??SteerCtrler_Init_0:
        LDR.N    R0,??DataTable5_16  ;; 0x40a00000
        LDR.N    R1,??DataTable5_15
        LDR      R1,[R1, #+0]
        STR      R0,[R1, #+0]
//  115 		steerCtrler -> Kd = 1;
        MOVS     R0,#+1065353216
        LDR.N    R1,??DataTable5_15
        LDR      R1,[R1, #+0]
        STR      R0,[R1, #+4]
//  116 		steerCtrler -> Ki = 0;
        MOVS     R0,#+0
        LDR.N    R1,??DataTable5_15
        LDR      R1,[R1, #+0]
        STR      R0,[R1, #+8]
//  117 		for(i = 0; i < 3; i++)
        MOVS     R0,#+0
        B.N      ??SteerCtrler_Init_2
//  118 		{
//  119 			steerCtrler -> error[i] = 0;
??SteerCtrler_Init_3:
        MOVS     R1,#+0
        LDR.N    R2,??DataTable5_15
        LDR      R2,[R2, #+0]
        SXTB     R0,R0            ;; SignExt  R0,R0,#+24,#+24
        ADDS     R2,R2,R0, LSL #+2
        STR      R1,[R2, #+12]
//  120 			steerCtrler -> u[i] = STEER_MID_DUTY;
        LDR.N    R1,??DataTable5_17  ;; 0x44b18000
        LDR.N    R2,??DataTable5_15
        LDR      R2,[R2, #+0]
        SXTB     R0,R0            ;; SignExt  R0,R0,#+24,#+24
        ADDS     R2,R2,R0, LSL #+2
        STR      R1,[R2, #+24]
//  121 		}
        ADDS     R0,R0,#+1
??SteerCtrler_Init_2:
        SXTB     R0,R0            ;; SignExt  R0,R0,#+24,#+24
        CMP      R0,#+3
        BLT.N    ??SteerCtrler_Init_3
//  122 	}
//  123 }
??SteerCtrler_Init_1:
        POP      {R0,PC}          ;; return
//  124 

        SECTION `.text`:CODE:NOROOT(1)
        THUMB
//  125 float32 Differ_Controller(PIDStruct *DifferCon_Data, float32 expect, float32 real)
//  126 {
Differ_Controller:
        PUSH     {R3-R5,LR}
        MOVS     R4,R0
        MOVS     R0,R2
//  127 	float32 incrementU;
//  128 
//  129 	DifferCon_Data -> error[2] = DifferCon_Data -> error[1];
        LDR      R2,[R4, #+16]
        STR      R2,[R4, #+20]
//  130 	DifferCon_Data -> error[1] = DifferCon_Data -> error[0];
        LDR      R2,[R4, #+12]
        STR      R2,[R4, #+16]
//  131 	DifferCon_Data -> error[0] = real - expect;
        BL       __aeabi_fsub
        STR      R0,[R4, #+12]
//  132 
//  133 	incrementU = (DifferCon_Data -> Kp) * ((DifferCon_Data -> error[0]) 		\ 
//  134 										 - (DifferCon_Data -> error[1]))		\ 
//  135 				+ (DifferCon_Data -> Kd) * ((DifferCon_Data -> error[0]) 		\ 
//  136 											- 2 * (DifferCon_Data -> error[1]) 	\ 
//  137 											+ (DifferCon_Data -> error[2]));
        LDR      R0,[R4, #+12]
        LDR      R1,[R4, #+16]
        BL       __aeabi_fsub
        LDR      R1,[R4, #+0]
        BL       __aeabi_fmul
        MOVS     R5,R0
        LDR      R1,[R4, #+16]
        MOVS     R0,#+1073741824
        BL       __aeabi_fmul
        MOVS     R1,R0
        LDR      R0,[R4, #+12]
        BL       __aeabi_fsub
        LDR      R1,[R4, #+20]
        BL       __aeabi_fadd
        LDR      R1,[R4, #+4]
        BL       __aeabi_fmul
        MOVS     R1,R5
        BL       __aeabi_fadd
        MOVS     R1,R0
//  138 
//  139 	DifferCon_Data -> u[2] = DifferCon_Data -> u[1];
        LDR      R0,[R4, #+28]
        STR      R0,[R4, #+32]
//  140 	DifferCon_Data -> u[1] = DifferCon_Data -> u[0];
        LDR      R0,[R4, #+24]
        STR      R0,[R4, #+28]
//  141 	DifferCon_Data -> u[0] = DifferCon_Data -> u[1] + incrementU;
        LDR      R0,[R4, #+28]
        BL       __aeabi_fadd
        STR      R0,[R4, #+24]
//  142 
//  143 	(DifferCon_Data -> u[0] > 2000) ? (DifferCon_Data -> u[0] = 1000) : (NULL);
        LDR      R0,[R4, #+24]
        LDR.N    R1,??DataTable5_18  ;; 0x44fa0001
        BL       __aeabi_cfrcmple
        BHI.N    ??Differ_Controller_0
        LDR.N    R0,??DataTable5_19  ;; 0x447a0000
        STR      R0,[R4, #+24]
        LDR      R0,[R4, #+24]
        B.N      ??Differ_Controller_1
??Differ_Controller_0:
        MOVS     R0,#+0
//  144 	(DifferCon_Data -> u[0] < -2000) ? (DifferCon_Data -> u[0] = -1000) : (NULL);
??Differ_Controller_1:
        LDR      R0,[R4, #+24]
        LDR.N    R1,??DataTable5_20  ;; 0xc4fa0000
        BL       __aeabi_cfcmple
        BCS.N    ??Differ_Controller_2
        LDR.N    R0,??DataTable5_21  ;; 0xc47a0000
        STR      R0,[R4, #+24]
        LDR      R0,[R4, #+24]
        B.N      ??Differ_Controller_3
??Differ_Controller_2:
        MOVS     R0,#+0
//  145 
//  146 	return (DifferCon_Data -> u[0]);
??Differ_Controller_3:
        LDR      R0,[R4, #+24]
        POP      {R1,R4,R5,PC}    ;; return
//  147 }

        SECTION `.text`:CODE:NOROOT(1)
        THUMB
//  148 void DifferCtrler_Init(void)
//  149 {
DifferCtrler_Init:
        PUSH     {R7,LR}
//  150 	uint8 i;
//  151 	differCtrler = (PIDStruct *)malloc(sizeof(PIDStruct));
        MOVS     R0,#+36
        BL       malloc
        LDR.N    R1,??DataTable5_4
        STR      R0,[R1, #+0]
//  152 	if (NULL == differCtrler)
        LDR.N    R0,??DataTable5_4
        LDR      R0,[R0, #+0]
        CMP      R0,#+0
        BNE.N    ??DifferCtrler_Init_0
//  153 	{
//  154 		printf("Memory alloc faild!\n");
        LDR.N    R0,??DataTable5_6
        BL       printf
//  155 		OLED_ShowString(0, 5, "Memory alloc faild!");
        LDR.N    R2,??DataTable5_7
        MOVS     R1,#+5
        MOVS     R0,#+0
        BL       OLED_ShowString
        B.N      ??DifferCtrler_Init_1
//  156 	}
//  157 	else
//  158 	{
//  159 		differCtrler -> Kp = 10;
??DifferCtrler_Init_0:
        LDR.N    R0,??DataTable5_22  ;; 0x41200000
        LDR.N    R1,??DataTable5_4
        LDR      R1,[R1, #+0]
        STR      R0,[R1, #+0]
//  160 		differCtrler -> Kd = 0;
        MOVS     R0,#+0
        LDR.N    R1,??DataTable5_4
        LDR      R1,[R1, #+0]
        STR      R0,[R1, #+4]
//  161 		differCtrler -> Ki = 0;
        MOVS     R0,#+0
        LDR.N    R1,??DataTable5_4
        LDR      R1,[R1, #+0]
        STR      R0,[R1, #+8]
//  162 		for(i = 0;i < 3; i++)
        MOVS     R0,#+0
        B.N      ??DifferCtrler_Init_2
//  163 		{
//  164 			differCtrler -> error[i] = 0;
??DifferCtrler_Init_3:
        MOVS     R1,#+0
        LDR.N    R2,??DataTable5_4
        LDR      R2,[R2, #+0]
        UXTB     R0,R0            ;; ZeroExt  R0,R0,#+24,#+24
        ADDS     R2,R2,R0, LSL #+2
        STR      R1,[R2, #+12]
//  165 			differCtrler -> u[i] = 0;
        MOVS     R1,#+0
        LDR.N    R2,??DataTable5_4
        LDR      R2,[R2, #+0]
        UXTB     R0,R0            ;; ZeroExt  R0,R0,#+24,#+24
        ADDS     R2,R2,R0, LSL #+2
        STR      R1,[R2, #+24]
//  166 		}
        ADDS     R0,R0,#+1
??DifferCtrler_Init_2:
        UXTB     R0,R0            ;; ZeroExt  R0,R0,#+24,#+24
        CMP      R0,#+3
        BLT.N    ??DifferCtrler_Init_3
//  167 	}
//  168 }
??DifferCtrler_Init_1:
        POP      {R0,PC}          ;; return

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable5:
        DC32     0x45960001

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable5_1:
        DC32     0xc5960000

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable5_2:
        DC32     MidAve

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable5_3:
        DC32     0x42a00000

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable5_4:
        DC32     differCtrler

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable5_5:
        DC32     speedCtrler

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable5_6:
        DC32     ?_0

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable5_7:
        DC32     ?_1

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable5_8:
        DC32     0x404ccccd

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable5_9:
        DC32     0x3f4ccccd

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable5_10:
        DC32     PWM_Expect

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable5_11:
        DC32     0x44c30001

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable5_12:
        DC32     0x44c30000

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable5_13:
        DC32     0x44992000

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable5_14:
        DC32     0x400b8000

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable5_15:
        DC32     steerCtrler

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable5_16:
        DC32     0x40a00000

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable5_17:
        DC32     0x44b18000

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable5_18:
        DC32     0x44fa0001

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable5_19:
        DC32     0x447a0000

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable5_20:
        DC32     0xc4fa0000

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable5_21:
        DC32     0xc47a0000

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable5_22:
        DC32     0x41200000

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
        DC8 "Memory alloc faild!\012"
        DC8 0, 0, 0

        SECTION `.rodata`:CONST:REORDER:NOROOT(2)
?_1:
        DATA
        DC8 "Memory alloc faild!"

        END
// 
//  12 bytes in section .bss
//  44 bytes in section .rodata
// 946 bytes in section .text
// 
// 946 bytes of CODE  memory
//  44 bytes of CONST memory
//  12 bytes of DATA  memory
//
//Errors: none
//Warnings: none
