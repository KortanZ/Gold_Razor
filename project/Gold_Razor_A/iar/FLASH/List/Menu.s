///////////////////////////////////////////////////////////////////////////////
//
// IAR ANSI C/C++ Compiler V7.40.3.8902/W32 for ARM       11/May/2016  19:28:45
// Copyright 1999-2015 IAR Systems AB.
//
//    Cpu mode     =  thumb
//    Endian       =  little
//    Source file  =  
//        E:\11ΩÏFreescale\Gold_Razor_A\Gold_Razor_A\project\Gold_Razor_A\app\Source\Menu.c
//    Command line =  
//        E:\11ΩÏFreescale\Gold_Razor_A\Gold_Razor_A\project\Gold_Razor_A\app\Source\Menu.c
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
//        E:\11ΩÏFreescale\Gold_Razor_A\Gold_Razor_A\project\Gold_Razor_A\iar\FLASH\List\Menu.s
//
///////////////////////////////////////////////////////////////////////////////

        #define SHT_PROGBITS 0x1

        EXTERN OLED_ClearLine
        EXTERN OLED_ShowChar
        EXTERN OLED_ShowNum
        EXTERN OLED_ShowString
        EXTERN PWM_Expect
        EXTERN __aeabi_d2f
        EXTERN __aeabi_dadd
        EXTERN __aeabi_f2d
        EXTERN __aeabi_f2iz
        EXTERN __aeabi_fmul
        EXTERN differCtrler
        EXTERN speedCtrler
        EXTERN steerCtrler

        PUBLIC Menu_Data_Decrease
        PUBLIC Menu_Data_Increase
        PUBLIC Menu_Data_Link
        PUBLIC Menu_Num_Show
        PUBLIC Menu_Show
        PUBLIC currentList
        PUBLIC menuList

// E:\11ΩÏFreescale\Gold_Razor_A\Gold_Razor_A\project\Gold_Razor_A\app\Source\Menu.c
//    1 #include "Menu.h"
//    2 #include "oled.h"
//    3 #include "PID.h"
//    4 #include "MotorDriver.h"
//    5 

        SECTION `.bss`:DATA:REORDER:NOROOT(0)
//    6 ListType currentList = DEBUG;
currentList:
        DS8 1
//    7 

        SECTION `.data`:DATA:REORDER:NOROOT(2)
//    8 MenuType menuList[] = {
menuList:
        DATA
        DC8 1, 1, 0, 2
        DC32 ?_0, 0H, 0H
        DC8 0, 0, 0, 0, 0, 0, 1, 1
        DC32 ?_1, 0H, 0H
        DC8 1, 0, 0, 0, 4, 3, 0, 5
        DC32 ?_2, 0H, 0H
        DC8 0, 0, 0, 0, 2, 4, 0, 8
        DC32 ?_3, 0H, 0H
        DC8 1, 0, 0, 0, 3, 2, 0, 11
        DC32 ?_4, 0H, 0H
        DC8 2, 0, 0, 0, 7, 6, 2, 5
        DC32 ?_5, 0H, 0H
        DC8 0, 0, 0, 0, 5, 7, 2, 6
        DC32 ?_6, 0H, 0H
        DC8 1, 0, 0, 0, 6, 5, 2, 7
        DC32 ?_7, 0H, 0H
        DC8 2, 0, 0, 0, 10, 9, 3, 8
        DC32 ?_8, 0H, 0H
        DC8 0, 0, 0, 0, 8, 10, 3, 9
        DC32 ?_9, 0H, 0H
        DC8 1, 0, 0, 0, 9, 14, 3, 10
        DC32 ?_10, 0H, 0H
        DC8 2, 0, 0, 0, 13, 12, 4, 11
        DC32 ?_11, 0H, 0H
        DC8 0, 0, 0, 0, 11, 13, 4, 12
        DC32 ?_12, 0H, 0H
        DC8 1, 0, 0, 0, 12, 11, 4, 13
        DC32 ?_13, 0H, 0H
        DC8 2, 0, 0, 0, 9, 8, 3, 14
        DC32 ?_14, 0H, 0H
        DC8 3, 0, 0, 0
//    9 	{RACE, RACE, DEBUG, PID_STEER, "Debug Mode", NULL, NULL, 0}, 			//Ë∞ÉËØïÊ®°Âºè
//   10 	{DEBUG, DEBUG, RACE, RACE, "Race Mode", NULL, NULL, 1}, 					//ÊØîËµõÊ®°Âºè
//   11 
//   12 	{PID_DIFF, PID_MOTOR, DEBUG, STEER_KP, "Steer", NULL, NULL, 0},
//   13 	{PID_STEER, PID_DIFF, DEBUG, MOTOR_KP, "Motor", NULL, NULL, 1},
//   14 	{PID_MOTOR, PID_STEER, DEBUG, DIFF_KP, "Diff", NULL , NULL, 2},
//   15 
//   16 	{STEER_KI, STEER_KD, PID_STEER, STEER_KP, "Steer_Kp:", NULL, NULL, 0},
//   17 	{STEER_KP, STEER_KI, PID_STEER, STEER_KD, "Steer_kd:", NULL, NULL, 1},
//   18 	{STEER_KD, STEER_KP, PID_STEER, STEER_KI, "Steer_Ki:", NULL, NULL, 2},
//   19 
//   20 	{MOTOR_KI, MOTOR_KD, PID_MOTOR, MOTOR_KP, "Motro_Kp:", NULL, NULL, 0},
//   21 	{MOTOR_KP, MOTOR_KI, PID_MOTOR, MOTOR_KD, "Motor_kd:", NULL, NULL, 1},
//   22 	{MOTOR_KD, MOTOR_SPEED, PID_MOTOR, MOTOR_KI, "Motor_Ki:", NULL, NULL, 2},
//   23 
//   24 	{DIFF_KI, DIFF_KD, PID_DIFF, DIFF_KP, "Diff_Kp:", NULL, NULL, 0},
//   25 	{DIFF_KP, DIFF_KI, PID_DIFF, DIFF_KD, "Diff_kd:", NULL, NULL, 1},
//   26 	{DIFF_KD, DIFF_KP, PID_DIFF, DIFF_KI, "Diff_Ki:", NULL, NULL, 2},
//   27 	
//   28 	{MOTOR_KD, MOTOR_KP, PID_MOTOR, MOTOR_SPEED, "Motor_Speed:", NULL, NULL, 3},
//   29 };
//   30 

        SECTION `.text`:CODE:NOROOT(1)
        THUMB
//   31 void Menu_Show(void)
//   32 {
Menu_Show:
        PUSH     {R4-R6,LR}
//   33 	uint8 i;
//   34 	ListType list = currentList;
        LDR.N    R0,??DataTable4
        LDRB     R4,[R0, #+0]
//   35 	uint8 page = (uint8)(menuList[list].indexInPage / 4);
        LDR.N    R0,??DataTable4_1
        UXTB     R4,R4            ;; ZeroExt  R4,R4,#+24,#+24
        MOVS     R1,#+20
        MLA      R0,R1,R4,R0
        LDRB     R0,[R0, #+16]
        MOVS     R1,#+4
        SDIV     R5,R0,R1
//   36 	for(i = 1; i < 5; i++)
        MOVS     R6,#+1
        B.N      ??Menu_Show_0
//   37 	{
//   38 		OLED_ClearLine(i);
??Menu_Show_1:
        MOVS     R0,R6
        UXTB     R0,R0            ;; ZeroExt  R0,R0,#+24,#+24
        BL       OLED_ClearLine
//   39 	}
        ADDS     R6,R6,#+1
??Menu_Show_0:
        UXTB     R6,R6            ;; ZeroExt  R6,R6,#+24,#+24
        CMP      R6,#+5
        BLT.N    ??Menu_Show_1
//   40 	do
//   41 	{
//   42 		if((uint8)(menuList[list].indexInPage / 4) == page)
??Menu_Show_2:
        LDR.N    R0,??DataTable4_1
        UXTB     R4,R4            ;; ZeroExt  R4,R4,#+24,#+24
        MOVS     R1,#+20
        MLA      R0,R1,R4,R0
        LDRB     R0,[R0, #+16]
        MOVS     R1,#+4
        SDIV     R0,R0,R1
        UXTB     R0,R0            ;; ZeroExt  R0,R0,#+24,#+24
        UXTB     R5,R5            ;; ZeroExt  R5,R5,#+24,#+24
        CMP      R0,R5
        BNE.N    ??Menu_Show_3
//   43 		{
//   44 			OLED_ShowString(8, (menuList[list].indexInPage % 4) + 1, menuList[list].str);
        LDR.N    R0,??DataTable4_1
        UXTB     R4,R4            ;; ZeroExt  R4,R4,#+24,#+24
        MOVS     R1,#+20
        MLA      R0,R1,R4,R0
        LDR      R2,[R0, #+4]
        LDR.N    R0,??DataTable4_1
        UXTB     R4,R4            ;; ZeroExt  R4,R4,#+24,#+24
        MOVS     R1,#+20
        MLA      R0,R1,R4,R0
        LDRB     R0,[R0, #+16]
        MOVS     R1,#+4
        SDIV     R3,R0,R1
        MLS      R3,R3,R1,R0
        ADDS     R1,R3,#+1
        UXTB     R1,R1            ;; ZeroExt  R1,R1,#+24,#+24
        MOVS     R0,#+8
        BL       OLED_ShowString
//   45 			Menu_Num_Show(list);
        MOVS     R0,R4
        UXTB     R0,R0            ;; ZeroExt  R0,R0,#+24,#+24
        BL       Menu_Num_Show
//   46 		}
//   47 		list = menuList[list].next;
??Menu_Show_3:
        LDR.N    R0,??DataTable4_1
        UXTB     R4,R4            ;; ZeroExt  R4,R4,#+24,#+24
        MOVS     R1,#+20
        MLA      R0,R1,R4,R0
        LDRB     R4,[R0, #+1]
//   48 	}while(list != currentList);
        LDR.N    R0,??DataTable4
        LDRB     R0,[R0, #+0]
        UXTB     R4,R4            ;; ZeroExt  R4,R4,#+24,#+24
        CMP      R4,R0
        BNE.N    ??Menu_Show_2
//   49 	OLED_ShowChar(0, (menuList[currentList].indexInPage % 4) + 1, '>');
        MOVS     R2,#+62
        LDR.N    R0,??DataTable4_1
        LDR.N    R1,??DataTable4
        LDRB     R1,[R1, #+0]
        MOVS     R3,#+20
        MLA      R0,R3,R1,R0
        LDRB     R0,[R0, #+16]
        MOVS     R1,#+4
        SDIV     R3,R0,R1
        MLS      R3,R3,R1,R0
        ADDS     R1,R3,#+1
        UXTB     R1,R1            ;; ZeroExt  R1,R1,#+24,#+24
        MOVS     R0,#+0
        BL       OLED_ShowChar
//   50 }
        POP      {R4-R6,PC}       ;; return
//   51 

        SECTION `.text`:CODE:NOROOT(1)
        THUMB
//   52 void Menu_Num_Show(ListType lst)
//   53 {
Menu_Num_Show:
        PUSH     {R3-R5,LR}
        MOVS     R4,R0
//   54 
//   55 	if(NULL != menuList[lst].data)
        LDR.N    R0,??DataTable4_1
        UXTB     R4,R4            ;; ZeroExt  R4,R4,#+24,#+24
        MOVS     R1,#+20
        MLA      R0,R1,R4,R0
        LDR      R0,[R0, #+12]
        CMP      R0,#+0
        BEQ.N    ??Menu_Num_Show_0
//   56 	{
//   57 		if(lst >= STEER_KP && lst <= DIFF_KI)
        UXTB     R4,R4            ;; ZeroExt  R4,R4,#+24,#+24
        SUBS     R0,R4,#+5
        CMP      R0,#+9
        BCS.N    ??Menu_Num_Show_1
//   58 			OLED_ShowNum(70, (menuList[lst].indexInPage % 4) + 1, (int32)(*((float32 *)menuList[lst].data) * 10), Num_Len);
        MOVS     R3,#+5
        MOVS     R5,R3
        LDR.N    R0,??DataTable4_1
        UXTB     R4,R4            ;; ZeroExt  R4,R4,#+24,#+24
        MOVS     R1,#+20
        MLA      R0,R1,R4,R0
        LDR      R0,[R0, #+12]
        LDR      R1,[R0, #+0]
        LDR.N    R0,??DataTable4_2  ;; 0x41200000
        BL       __aeabi_fmul
        BL       __aeabi_f2iz
        MOVS     R2,R0
        MOVS     R3,R5
        LDR.N    R0,??DataTable4_1
        UXTB     R4,R4            ;; ZeroExt  R4,R4,#+24,#+24
        MOVS     R1,#+20
        MLA      R0,R1,R4,R0
        LDRB     R0,[R0, #+16]
        MOVS     R1,#+4
        SDIV     R4,R0,R1
        MLS      R4,R4,R1,R0
        ADDS     R1,R4,#+1
        UXTB     R1,R1            ;; ZeroExt  R1,R1,#+24,#+24
        MOVS     R0,#+70
        BL       OLED_ShowNum
        B.N      ??Menu_Num_Show_0
//   59 		else if(lst >= MOTOR_SPEED && lst <= MOTOR_SPEED)
??Menu_Num_Show_1:
        UXTB     R4,R4            ;; ZeroExt  R4,R4,#+24,#+24
        SUBS     R0,R4,#+14
        CMP      R0,#+1
        BCS.N    ??Menu_Num_Show_0
//   60 		  	OLED_ShowNum(70, (menuList[lst].indexInPage % 4) + 1, (int32)(*((int32 *)menuList[lst].data)), Num_Len);
        MOVS     R3,#+5
        LDR.N    R0,??DataTable4_1
        UXTB     R4,R4            ;; ZeroExt  R4,R4,#+24,#+24
        MOVS     R1,#+20
        MLA      R0,R1,R4,R0
        LDR      R0,[R0, #+12]
        LDR      R2,[R0, #+0]
        LDR.N    R0,??DataTable4_1
        UXTB     R4,R4            ;; ZeroExt  R4,R4,#+24,#+24
        MOVS     R1,#+20
        MLA      R0,R1,R4,R0
        LDRB     R0,[R0, #+16]
        MOVS     R1,#+4
        SDIV     R4,R0,R1
        MLS      R4,R4,R1,R0
        ADDS     R1,R4,#+1
        UXTB     R1,R1            ;; ZeroExt  R1,R1,#+24,#+24
        MOVS     R0,#+70
        BL       OLED_ShowNum
//   61 	}
//   62 }
??Menu_Num_Show_0:
        POP      {R0,R4,R5,PC}    ;; return
//   63 

        SECTION `.text`:CODE:NOROOT(1)
        THUMB
//   64 void Menu_Data_Link(void)
//   65 {
//   66 	menuList[MOTOR_KP].data = (void *)(&(speedCtrler -> Kp));
Menu_Data_Link:
        LDR.N    R0,??DataTable4_3
        LDR      R0,[R0, #+0]
        LDR.N    R1,??DataTable4_1
        STR      R0,[R1, #+172]
//   67 	menuList[MOTOR_KD].data = (void *)(&(speedCtrler -> Kd));
        LDR.N    R0,??DataTable4_3
        LDR      R0,[R0, #+0]
        ADDS     R0,R0,#+4
        LDR.N    R1,??DataTable4_1
        STR      R0,[R1, #+192]
//   68 	menuList[MOTOR_KI].data = (void *)(&(speedCtrler -> Ki));
        LDR.N    R0,??DataTable4_3
        LDR      R0,[R0, #+0]
        ADDS     R0,R0,#+8
        LDR.N    R1,??DataTable4_1
        STR      R0,[R1, #+212]
//   69 
//   70 	menuList[STEER_KP].data = (void *)(&(steerCtrler -> Kp));
        LDR.N    R0,??DataTable4_4
        LDR      R0,[R0, #+0]
        LDR.N    R1,??DataTable4_1
        STR      R0,[R1, #+112]
//   71 	menuList[STEER_KD].data = (void *)(&(steerCtrler -> Kd));
        LDR.N    R0,??DataTable4_4
        LDR      R0,[R0, #+0]
        ADDS     R0,R0,#+4
        LDR.N    R1,??DataTable4_1
        STR      R0,[R1, #+132]
//   72 	menuList[STEER_KI].data = (void *)(&(steerCtrler -> Ki));
        LDR.N    R0,??DataTable4_4
        LDR      R0,[R0, #+0]
        ADDS     R0,R0,#+8
        LDR.N    R1,??DataTable4_1
        STR      R0,[R1, #+152]
//   73 
//   74 	menuList[DIFF_KP].data = (void *)(&(differCtrler -> Kp));
        LDR.N    R0,??DataTable4_5
        LDR      R0,[R0, #+0]
        LDR.N    R1,??DataTable4_1
        STR      R0,[R1, #+232]
//   75 	menuList[DIFF_KD].data = (void *)(&(differCtrler -> Kd));
        LDR.N    R0,??DataTable4_5
        LDR      R0,[R0, #+0]
        ADDS     R0,R0,#+4
        LDR.N    R1,??DataTable4_1
        STR      R0,[R1, #+252]
//   76 	menuList[DIFF_KI].data = (void *)(&(differCtrler -> Ki));
        LDR.N    R0,??DataTable4_5
        LDR      R0,[R0, #+0]
        ADDS     R0,R0,#+8
        LDR.N    R1,??DataTable4_1
        STR      R0,[R1, #+272]
//   77 	
//   78 	menuList[MOTOR_SPEED].data = (void *)(&PWM_Expect);
        LDR.N    R0,??DataTable4_6
        LDR.N    R1,??DataTable4_1
        STR      R0,[R1, #+292]
//   79 
//   80 }
        BX       LR               ;; return
//   81 

        SECTION `.text`:CODE:NOROOT(1)
        THUMB
//   82 void Menu_Data_Increase(ListType lst)
//   83 {
Menu_Data_Increase:
        PUSH     {R4,LR}
        MOVS     R4,R0
//   84 	if(NULL != menuList[lst].data)
        LDR.N    R0,??DataTable4_1
        UXTB     R4,R4            ;; ZeroExt  R4,R4,#+24,#+24
        MOVS     R1,#+20
        MLA      R0,R1,R4,R0
        LDR      R0,[R0, #+12]
        CMP      R0,#+0
        BEQ.N    ??Menu_Data_Increase_0
//   85 	{
//   86 		if(lst >= STEER_KP && lst <= DIFF_KI)
        UXTB     R4,R4            ;; ZeroExt  R4,R4,#+24,#+24
        SUBS     R0,R4,#+5
        CMP      R0,#+9
        BCS.N    ??Menu_Data_Increase_1
//   87 			*((float32 *)menuList[lst].data) += 0.1;
        LDR.N    R0,??DataTable4_1
        UXTB     R4,R4            ;; ZeroExt  R4,R4,#+24,#+24
        MOVS     R1,#+20
        MLA      R0,R1,R4,R0
        LDR      R0,[R0, #+12]
        LDR      R0,[R0, #+0]
        BL       __aeabi_f2d
        LDR.N    R2,??DataTable4_7  ;; 0x9999999a
        LDR.N    R3,??DataTable4_8  ;; 0x3fb99999
        BL       __aeabi_dadd
        BL       __aeabi_d2f
        LDR.N    R1,??DataTable4_1
        UXTB     R4,R4            ;; ZeroExt  R4,R4,#+24,#+24
        MOVS     R2,#+20
        MLA      R1,R2,R4,R1
        LDR      R1,[R1, #+12]
        STR      R0,[R1, #+0]
        B.N      ??Menu_Data_Increase_0
//   88 		else if(lst >= MOTOR_SPEED && lst <= MOTOR_SPEED)
??Menu_Data_Increase_1:
        UXTB     R4,R4            ;; ZeroExt  R4,R4,#+24,#+24
        SUBS     R0,R4,#+14
        CMP      R0,#+1
        BCS.N    ??Menu_Data_Increase_0
//   89 		  	*((int32 *)menuList[lst].data) += 1000;
        LDR.N    R0,??DataTable4_1
        UXTB     R4,R4            ;; ZeroExt  R4,R4,#+24,#+24
        MOVS     R1,#+20
        MLA      R0,R1,R4,R0
        LDR      R0,[R0, #+12]
        LDR      R0,[R0, #+0]
        ADDS     R0,R0,#+1000
        LDR.N    R1,??DataTable4_1
        UXTB     R4,R4            ;; ZeroExt  R4,R4,#+24,#+24
        MOVS     R2,#+20
        MLA      R1,R2,R4,R1
        LDR      R1,[R1, #+12]
        STR      R0,[R1, #+0]
//   90 	}
//   91 }
??Menu_Data_Increase_0:
        POP      {R4,PC}          ;; return
//   92 

        SECTION `.text`:CODE:NOROOT(1)
        THUMB
//   93 void Menu_Data_Decrease(ListType lst)
//   94 {
Menu_Data_Decrease:
        PUSH     {R4,LR}
        MOVS     R4,R0
//   95 	if(NULL != menuList[lst].data)
        LDR.N    R0,??DataTable4_1
        UXTB     R4,R4            ;; ZeroExt  R4,R4,#+24,#+24
        MOVS     R1,#+20
        MLA      R0,R1,R4,R0
        LDR      R0,[R0, #+12]
        CMP      R0,#+0
        BEQ.N    ??Menu_Data_Decrease_0
//   96 	{
//   97 		if(lst >= STEER_KP && lst <= DIFF_KI)
        UXTB     R4,R4            ;; ZeroExt  R4,R4,#+24,#+24
        SUBS     R0,R4,#+5
        CMP      R0,#+9
        BCS.N    ??Menu_Data_Decrease_1
//   98 			*((float32 *)menuList[lst].data) -= 0.1 ;
        LDR.N    R0,??DataTable4_1
        UXTB     R4,R4            ;; ZeroExt  R4,R4,#+24,#+24
        MOVS     R1,#+20
        MLA      R0,R1,R4,R0
        LDR      R0,[R0, #+12]
        LDR      R0,[R0, #+0]
        BL       __aeabi_f2d
        LDR.N    R2,??DataTable4_7  ;; 0x9999999a
        LDR.N    R3,??DataTable4_9  ;; 0xbfb99999
        BL       __aeabi_dadd
        BL       __aeabi_d2f
        LDR.N    R1,??DataTable4_1
        UXTB     R4,R4            ;; ZeroExt  R4,R4,#+24,#+24
        MOVS     R2,#+20
        MLA      R1,R2,R4,R1
        LDR      R1,[R1, #+12]
        STR      R0,[R1, #+0]
        B.N      ??Menu_Data_Decrease_0
//   99 		else if(lst >= MOTOR_SPEED && lst <= MOTOR_SPEED)
??Menu_Data_Decrease_1:
        UXTB     R4,R4            ;; ZeroExt  R4,R4,#+24,#+24
        SUBS     R0,R4,#+14
        CMP      R0,#+1
        BCS.N    ??Menu_Data_Decrease_0
//  100 		  	*((int32 *)menuList[lst].data) -= 1000;
        LDR.N    R0,??DataTable4_1
        UXTB     R4,R4            ;; ZeroExt  R4,R4,#+24,#+24
        MOVS     R1,#+20
        MLA      R0,R1,R4,R0
        LDR      R0,[R0, #+12]
        LDR      R0,[R0, #+0]
        SUBS     R0,R0,#+1000
        LDR.N    R1,??DataTable4_1
        UXTB     R4,R4            ;; ZeroExt  R4,R4,#+24,#+24
        MOVS     R2,#+20
        MLA      R1,R2,R4,R1
        LDR      R1,[R1, #+12]
        STR      R0,[R1, #+0]
//  101 	}
//  102 }
??Menu_Data_Decrease_0:
        POP      {R4,PC}          ;; return

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable4:
        DC32     currentList

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable4_1:
        DC32     menuList

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable4_2:
        DC32     0x41200000

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable4_3:
        DC32     speedCtrler

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable4_4:
        DC32     steerCtrler

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable4_5:
        DC32     differCtrler

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable4_6:
        DC32     PWM_Expect

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable4_7:
        DC32     0x9999999a

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable4_8:
        DC32     0x3fb99999

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable4_9:
        DC32     0xbfb99999

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
        DC8 "Debug Mode"
        DC8 0

        SECTION `.rodata`:CONST:REORDER:NOROOT(2)
?_1:
        DATA
        DC8 "Race Mode"
        DC8 0, 0

        SECTION `.rodata`:CONST:REORDER:NOROOT(2)
?_2:
        DATA
        DC8 "Steer"
        DC8 0, 0

        SECTION `.rodata`:CONST:REORDER:NOROOT(2)
?_3:
        DATA
        DC8 "Motor"
        DC8 0, 0

        SECTION `.rodata`:CONST:REORDER:NOROOT(2)
?_4:
        DATA
        DC8 "Diff"
        DC8 0, 0, 0

        SECTION `.rodata`:CONST:REORDER:NOROOT(2)
?_5:
        DATA
        DC8 "Steer_Kp:"
        DC8 0, 0

        SECTION `.rodata`:CONST:REORDER:NOROOT(2)
?_6:
        DATA
        DC8 "Steer_kd:"
        DC8 0, 0

        SECTION `.rodata`:CONST:REORDER:NOROOT(2)
?_7:
        DATA
        DC8 "Steer_Ki:"
        DC8 0, 0

        SECTION `.rodata`:CONST:REORDER:NOROOT(2)
?_8:
        DATA
        DC8 "Motro_Kp:"
        DC8 0, 0

        SECTION `.rodata`:CONST:REORDER:NOROOT(2)
?_9:
        DATA
        DC8 "Motor_kd:"
        DC8 0, 0

        SECTION `.rodata`:CONST:REORDER:NOROOT(2)
?_10:
        DATA
        DC8 "Motor_Ki:"
        DC8 0, 0

        SECTION `.rodata`:CONST:REORDER:NOROOT(2)
?_11:
        DATA
        DC8 "Diff_Kp:"
        DC8 0, 0, 0

        SECTION `.rodata`:CONST:REORDER:NOROOT(2)
?_12:
        DATA
        DC8 "Diff_kd:"
        DC8 0, 0, 0

        SECTION `.rodata`:CONST:REORDER:NOROOT(2)
?_13:
        DATA
        DC8 "Diff_Ki:"
        DC8 0, 0, 0

        SECTION `.rodata`:CONST:REORDER:NOROOT(2)
?_14:
        DATA
        DC8 "Motor_Speed:"
        DC8 0, 0, 0

        END
// 
//   1 byte  in section .bss
// 300 bytes in section .data
// 172 bytes in section .rodata
// 722 bytes in section .text
// 
// 722 bytes of CODE  memory
// 172 bytes of CONST memory
// 301 bytes of DATA  memory
//
//Errors: none
//Warnings: none
