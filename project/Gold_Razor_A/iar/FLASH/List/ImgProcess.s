///////////////////////////////////////////////////////////////////////////////
//
// IAR ANSI C/C++ Compiler V7.40.3.8902/W32 for ARM       11/May/2016  19:10:53
// Copyright 1999-2015 IAR Systems AB.
//
//    Cpu mode     =  thumb
//    Endian       =  little
//    Source file  =  
//        E:\11��Freescale\Gold_Razor_A\Gold_Razor_A\project\Gold_Razor_A\app\Source\ImgProcess.c
//    Command line =  
//        E:\11��Freescale\Gold_Razor_A\Gold_Razor_A\project\Gold_Razor_A\app\Source\ImgProcess.c
//        -D LPLD_K60 -D USE_K60DZ10 -lCN
//        E:\11��Freescale\Gold_Razor_A\Gold_Razor_A\project\Gold_Razor_A\iar\FLASH\List\
//        -lB
//        E:\11��Freescale\Gold_Razor_A\Gold_Razor_A\project\Gold_Razor_A\iar\FLASH\List\
//        -o
//        E:\11��Freescale\Gold_Razor_A\Gold_Razor_A\project\Gold_Razor_A\iar\FLASH\Obj\
//        --no_cse --no_unroll --no_inline --no_code_motion --no_tbaa
//        --no_clustering --no_scheduling --debug --endian=little
//        --cpu=Cortex-M4 -e --fpu=None --dlib_config
//        D:\IAR\arm\INC\c\DLib_Config_Normal.h -I
//        E:\11��Freescale\Gold_Razor_A\Gold_Razor_A\project\Gold_Razor_A\iar\..\app\
//        -I
//        E:\11��Freescale\Gold_Razor_A\Gold_Razor_A\project\Gold_Razor_A\iar\..\app\Source\
//        -I
//        E:\11��Freescale\Gold_Razor_A\Gold_Razor_A\project\Gold_Razor_A\iar\..\..\..\lib\CPU\
//        -I
//        E:\11��Freescale\Gold_Razor_A\Gold_Razor_A\project\Gold_Razor_A\iar\..\..\..\lib\common\
//        -I
//        E:\11��Freescale\Gold_Razor_A\Gold_Razor_A\project\Gold_Razor_A\iar\..\..\..\lib\LPLD\
//        -I
//        E:\11��Freescale\Gold_Razor_A\Gold_Razor_A\project\Gold_Razor_A\iar\..\..\..\lib\LPLD\HW\
//        -I
//        E:\11��Freescale\Gold_Razor_A\Gold_Razor_A\project\Gold_Razor_A\iar\..\..\..\lib\LPLD\DEV\
//        -I
//        E:\11��Freescale\Gold_Razor_A\Gold_Razor_A\project\Gold_Razor_A\iar\..\..\..\lib\LPLD\FUNC\
//        -I
//        E:\11��Freescale\Gold_Razor_A\Gold_Razor_A\project\Gold_Razor_A\iar\..\..\..\lib\uCOS-II\Ports\
//        -I
//        E:\11��Freescale\Gold_Razor_A\Gold_Razor_A\project\Gold_Razor_A\iar\..\..\..\lib\uCOS-II\Source\
//        -I
//        E:\11��Freescale\Gold_Razor_A\Gold_Razor_A\project\Gold_Razor_A\iar\..\..\..\lib\FatFs\
//        -I
//        E:\11��Freescale\Gold_Razor_A\Gold_Razor_A\project\Gold_Razor_A\iar\..\..\..\lib\FatFs\option\
//        -I
//        E:\11��Freescale\Gold_Razor_A\Gold_Razor_A\project\Gold_Razor_A\iar\..\..\..\lib\USB\common\
//        -I
//        E:\11��Freescale\Gold_Razor_A\Gold_Razor_A\project\Gold_Razor_A\iar\..\..\..\lib\USB\driver\
//        -I
//        E:\11��Freescale\Gold_Razor_A\Gold_Razor_A\project\Gold_Razor_A\iar\..\..\..\lib\USB\descriptor\
//        -I
//        E:\11��Freescale\Gold_Razor_A\Gold_Razor_A\project\Gold_Razor_A\iar\..\..\..\lib\USB\class\
//        -Ol -I D:\IAR\arm\CMSIS\Include\ -D ARM_MATH_CM4
//    List file    =  
//        E:\11��Freescale\Gold_Razor_A\Gold_Razor_A\project\Gold_Razor_A\iar\FLASH\List\ImgProcess.s
//
///////////////////////////////////////////////////////////////////////////////

        #define SHT_PROGBITS 0x1

        EXTERN LPLD_FTM_PWM_ChangeDuty
        EXTERN OLED_Clear
        EXTERN OLED_ShowString
        EXTERN __aeabi_f2iz
        EXTERN __aeabi_fadd
        EXTERN __aeabi_fmul
        EXTERN __aeabi_ui2f
        EXTERN img
        EXTERN img_extract
        EXTERN imgbuff
        EXTERN ov7725_eagle_img_flag

        PUBLIC Bef_Scan
        PUBLIC Get_Img
        PUBLIC Get_MidAve
        PUBLIC Get_MidLine
        PUBLIC LeftFlag_Switch
        PUBLIC MidAve
        PUBLIC PIC_DateBlock
        PUBLIC RightFlag_Switch
        PUBLIC TwinLine_Deal

// E:\11��Freescale\Gold_Razor_A\Gold_Razor_A\project\Gold_Razor_A\app\Source\ImgProcess.c
//    1 /*
//    2 *This head file for image processing
//    3 *include edge extacting
//    4 *include
//    5 */
//    6 //#include "common.h"
//    7 #include "ImgProcess.h"

        SECTION `.text`:CODE:NOROOT(1)
        THUMB
// static __interwork __softfp void NVIC_EnableIRQ(IRQn_Type)
NVIC_EnableIRQ:
        MOVS     R1,#+1
        ANDS     R2,R0,#0x1F
        LSLS     R1,R1,R2
        LDR.W    R2,??DataTable5  ;; 0xe000e100
        SXTB     R0,R0            ;; SignExt  R0,R0,#+24,#+24
        LSRS     R0,R0,#+5
        STR      R1,[R2, R0, LSL #+2]
        BX       LR               ;; return
//    8 #include "Eagle_ov7725.h"
//    9 #include "Oled.h"
//   10 
//   11 uint8 Bef_Scan(uint8*);
//   12 void TwinLine_Deal(uint8 *,int8);
//   13 void Get_MidAve(uint8 * ,float32 ,float32 ,float32 ,float32);
//   14 

        SECTION `.bss`:DATA:REORDER:NOROOT(2)
//   15 PIC_DateStruct PIC_DateBlock;
PIC_DateBlock:
        DS8 6604

        SECTION `.bss`:DATA:REORDER:NOROOT(2)
//   16 LeftFlag_Struct LeftFlag_Switch;
LeftFlag_Switch:
        DS8 8

        SECTION `.bss`:DATA:REORDER:NOROOT(2)
//   17 RightFlag_Struct RightFlag_Switch;
RightFlag_Switch:
        DS8 8
//   18 

        SECTION `.bss`:DATA:REORDER:NOROOT(1)
//   19 int16 MidAve = 0;
MidAve:
        DS8 2
//   20 

        SECTION `.text`:CODE:NOROOT(1)
        THUMB
//   21 void Get_MidLine(void)
//   22 {
Get_MidLine:
        PUSH     {R4-R6,LR}
        SUB      SP,SP,#+8
//   23 	uint8 i,j,k;
//   24 	int8 Row;
//   25 	img_extract(img,imgbuff,CAMERA_SIZE);       //图像解压
        MOV      R2,#+2400
        LDR.W    R1,??DataTable5_1
        LDR.W    R0,??DataTable5_2
        BL       img_extract
//   26 	for(k = 0,i = 1; i < CAMERA_H; i += 3 , k++)          //隔行提取
        MOVS     R2,#+0
        MOVS     R0,#+1
        B.N      ??Get_MidLine_0
//   27 	{
//   28 		for(j = 0; j < CAMERA_W; j++)
//   29 		{
//   30 			PIC_DateBlock.pic[CAMERA_W * k + j] = img[i * CAMERA_W + j];
??Get_MidLine_1:
        LDR.W    R3,??DataTable5_3
        UXTB     R2,R2            ;; ZeroExt  R2,R2,#+24,#+24
        MOVS     R4,#+160
        UXTB     R1,R1            ;; ZeroExt  R1,R1,#+24,#+24
        MLA      R4,R4,R2,R1
        LDR.W    R5,??DataTable5_2
        UXTB     R0,R0            ;; ZeroExt  R0,R0,#+24,#+24
        MOVS     R6,#+160
        UXTB     R1,R1            ;; ZeroExt  R1,R1,#+24,#+24
        MLA      R6,R6,R0,R1
        LDRB     R5,[R6, R5]
        STRB     R5,[R4, R3]
//   31 		}
        ADDS     R1,R1,#+1
??Get_MidLine_2:
        UXTB     R1,R1            ;; ZeroExt  R1,R1,#+24,#+24
        CMP      R1,#+160
        BLT.N    ??Get_MidLine_1
        ADDS     R0,R0,#+3
        ADDS     R2,R2,#+1
??Get_MidLine_0:
        UXTB     R0,R0            ;; ZeroExt  R0,R0,#+24,#+24
        CMP      R0,#+120
        BGE.N    ??Get_MidLine_3
        MOVS     R1,#+0
        B.N      ??Get_MidLine_2
//   32 	}
//   33 
//   34 	for(Row = Bef_Scan(PIC_DateBlock.pic);Row >= 0;Row--)
??Get_MidLine_3:
        LDR.W    R0,??DataTable5_3
        BL       Bef_Scan
        MOVS     R4,R0
        B.N      ??Get_MidLine_4
??Get_MidLine_5:
        SUBS     R4,R4,#+1
??Get_MidLine_4:
        SXTB     R4,R4            ;; SignExt  R4,R4,#+24,#+24
        CMP      R4,#+0
        BMI.W    ??Get_MidLine_6
//   35 	{
//   36 		/*SingleLine_Deal(Row);
//   37 		if(SingleModle_Flag)
//   38 		{
//   39 
//   40 		}*/
//   41 		TwinLine_Deal(PIC_DateBlock.pic,Row);
        MOVS     R1,R4
        SXTB     R1,R1            ;; SignExt  R1,R1,#+24,#+24
        LDR.W    R0,??DataTable5_3
        BL       TwinLine_Deal
//   42 		if(LeftFlag_Switch.LeftLost == 0  && RightFlag_Switch.RightWhiteLost == 1)
        LDR.W    R0,??DataTable5_4
        LDRB     R0,[R0, #+2]
        LDR.W    R1,??DataTable5_5
        LDRB     R1,[R1, #+1]
        EORS     R1,R1,#0x1
        ORRS     R0,R1,R0
        UXTB     R0,R0            ;; ZeroExt  R0,R0,#+24,#+24
        CMP      R0,#+0
        BNE.N    ??Get_MidLine_7
//   43 		{
//   44 			(++RightFlag_Switch.RightTurn >= 10)  ? 	\ 
//   45 				(RightFlag_Switch.RightTurnFlag = 1) : 	\ 
//   46 				(LeftFlag_Switch.LeftTurn = 0 , LeftFlag_Switch.LeftTurnFlag = 0);
        LDR.W    R0,??DataTable5_5
        LDRB     R0,[R0, #+3]
        ADDS     R0,R0,#+1
        LDR.W    R1,??DataTable5_5
        STRB     R0,[R1, #+3]
        LDR.W    R0,??DataTable5_5
        LDRB     R0,[R0, #+3]
        CMP      R0,#+10
        BLT.N    ??Get_MidLine_8
        MOVS     R0,#+1
        LDR.W    R1,??DataTable5_5
        STRB     R0,[R1, #+4]
        LDR.W    R0,??DataTable5_5
        LDRB     R0,[R0, #+4]
        B.N      ??Get_MidLine_9
??Get_MidLine_8:
        MOVS     R0,#+0
        LDR.W    R1,??DataTable5_4
        STRB     R0,[R1, #+3]
        MOVS     R0,#+0
        LDR.W    R1,??DataTable5_4
        STRB     R0,[R1, #+4]
        LDR.W    R0,??DataTable5_4
        LDRB     R0,[R0, #+4]
        B.N      ??Get_MidLine_9
//   47 		}
//   48 		else if(LeftFlag_Switch.LeftWhiteLost == 1 && RightFlag_Switch.RightLost == 0)
??Get_MidLine_7:
        LDR.W    R0,??DataTable5_4
        LDRB     R0,[R0, #+1]
        LDR.W    R1,??DataTable5_5
        LDRB     R1,[R1, #+2]
        EORS     R1,R1,#0x1
        TST      R0,R1
        BEQ.N    ??Get_MidLine_9
//   49 		{
//   50 			(++LeftFlag_Switch.LeftTurn >= 10) ?		\ 
//   51 				(LeftFlag_Switch.LeftTurnFlag = 1) :	\ 
//   52 				(RightFlag_Switch.RightTurn = 0 , RightFlag_Switch.RightTurnFlag = 0);
        LDR.W    R0,??DataTable5_4
        LDRB     R0,[R0, #+3]
        ADDS     R0,R0,#+1
        LDR.W    R1,??DataTable5_4
        STRB     R0,[R1, #+3]
        LDR.W    R0,??DataTable5_4
        LDRB     R0,[R0, #+3]
        CMP      R0,#+10
        BLT.N    ??Get_MidLine_10
        MOVS     R0,#+1
        LDR.W    R1,??DataTable5_4
        STRB     R0,[R1, #+4]
        LDR.W    R0,??DataTable5_4
        LDRB     R0,[R0, #+4]
        B.N      ??Get_MidLine_9
??Get_MidLine_10:
        MOVS     R0,#+0
        LDR.W    R1,??DataTable5_5
        STRB     R0,[R1, #+3]
        MOVS     R0,#+0
        LDR.W    R1,??DataTable5_5
        STRB     R0,[R1, #+4]
        LDR.W    R0,??DataTable5_5
        LDRB     R0,[R0, #+4]
//   53 		}
//   54 		if(LeftFlag_Switch.LeftTurnFlag || RightFlag_Switch.RightTurnFlag)
??Get_MidLine_9:
        LDR.W    R0,??DataTable5_4
        LDRB     R0,[R0, #+4]
        LDR.W    R1,??DataTable5_5
        LDRB     R1,[R1, #+4]
        ORRS     R0,R1,R0
        UXTB     R0,R0            ;; ZeroExt  R0,R0,#+24,#+24
        CMP      R0,#+0
        BEQ.N    ??Get_MidLine_5
//   55 		{
//   56 			if(LeftFlag_Switch.LeftBlackLost&& RightFlag_Switch.RightBlackLost)
        LDR.W    R0,??DataTable5_4
        LDRB     R0,[R0, #+0]
        LDR.W    R1,??DataTable5_5
        LDRB     R1,[R1, #+0]
        TST      R0,R1
        BEQ.N    ??Get_MidLine_5
//   57 				break;
        B.N      ??Get_MidLine_6
//   58 		}
//   59 	}
//   60 	for(;Row >= 0;Row--)
//   61 	{
//   62 		if(LeftFlag_Switch.LeftTurnFlag)
//   63 		{
//   64 			PIC_DateBlock.TrackInf_DataBlock.LeftLine[Row] = 1;
//   65 			PIC_DateBlock.TrackInf_DataBlock.RightLine[Row] = 1;
//   66 			PIC_DateBlock.TrackInf_DataBlock.MidLine[Row] = 1;
//   67 		}
//   68 		else if(RightFlag_Switch.RightTurnFlag)
??Get_MidLine_11:
        LDR.W    R0,??DataTable5_5
        LDRB     R0,[R0, #+4]
        CMP      R0,#+0
        BEQ.N    ??Get_MidLine_12
//   69 		{
//   70 			PIC_DateBlock.TrackInf_DataBlock.LeftLine[Row] = PICTURE_W - 2;
        MOVS     R0,#+158
        LDR.W    R1,??DataTable5_3
        SXTB     R4,R4            ;; SignExt  R4,R4,#+24,#+24
        ADDS     R1,R1,R4, LSL #+1
        ADDS     R1,R1,#+6400
        STRH     R0,[R1, #+0]
//   71 			PIC_DateBlock.TrackInf_DataBlock.RightLine[Row] = PICTURE_W - 2;
        MOVS     R0,#+158
        LDR.W    R1,??DataTable5_3
        SXTB     R4,R4            ;; SignExt  R4,R4,#+24,#+24
        ADDS     R1,R1,R4, LSL #+1
        MOVW     R2,#+6480
        STRH     R0,[R2, R1]
//   72 			PIC_DateBlock.TrackInf_DataBlock.MidLine[Row] = PICTURE_W - 2;
        MOVS     R0,#+158
        LDR.W    R1,??DataTable5_3
        SXTB     R4,R4            ;; SignExt  R4,R4,#+24,#+24
        ADDS     R1,R4,R1
        ADDS     R1,R1,#+6560
        STRB     R0,[R1, #+0]
//   73 		}
??Get_MidLine_12:
        SUBS     R4,R4,#+1
??Get_MidLine_6:
        SXTB     R4,R4            ;; SignExt  R4,R4,#+24,#+24
        CMP      R4,#+0
        BMI.N    ??Get_MidLine_13
        LDR.W    R0,??DataTable5_4
        LDRB     R0,[R0, #+4]
        CMP      R0,#+0
        BEQ.N    ??Get_MidLine_11
        MOVS     R0,#+1
        LDR.W    R1,??DataTable5_3
        SXTB     R4,R4            ;; SignExt  R4,R4,#+24,#+24
        ADDS     R1,R1,R4, LSL #+1
        ADDS     R1,R1,#+6400
        STRH     R0,[R1, #+0]
        MOVS     R0,#+1
        LDR.W    R1,??DataTable5_3
        SXTB     R4,R4            ;; SignExt  R4,R4,#+24,#+24
        ADDS     R1,R1,R4, LSL #+1
        MOVW     R2,#+6480
        STRH     R0,[R2, R1]
        MOVS     R0,#+1
        LDR.W    R1,??DataTable5_3
        SXTB     R4,R4            ;; SignExt  R4,R4,#+24,#+24
        ADDS     R1,R4,R1
        ADDS     R1,R1,#+6560
        STRB     R0,[R1, #+0]
        B.N      ??Get_MidLine_12
//   74 	}
//   75 	LeftFlag_Switch.LeftTurn = 0;
??Get_MidLine_13:
        MOVS     R0,#+0
        LDR.W    R1,??DataTable5_4
        STRB     R0,[R1, #+3]
//   76 	LeftFlag_Switch.LeftTurnFlag = 0;
        MOVS     R0,#+0
        LDR.W    R1,??DataTable5_4
        STRB     R0,[R1, #+4]
//   77 	RightFlag_Switch.RightTurn = 0;
        MOVS     R0,#+0
        LDR.W    R1,??DataTable5_5
        STRB     R0,[R1, #+3]
//   78 	RightFlag_Switch.RightTurnFlag = 0;
        MOVS     R0,#+0
        LDR.W    R1,??DataTable5_5
        STRB     R0,[R1, #+4]
//   79 	Get_MidAve(PIC_DateBlock.TrackInf_DataBlock.MidLine  \ 
//   80 		       , 0.01    \ 
//   81 		       , 0.04    \ 
//   82 		       , 0.03    \ 
//   83 		       , 0.02);
        LDR.W    R0,??DataTable5_6  ;; 0x3ca3d70a
        STR      R0,[SP, #+0]
        LDR.W    R3,??DataTable5_7  ;; 0x3cf5c28f
        LDR.W    R2,??DataTable5_8  ;; 0x3d23d70a
        LDR.W    R1,??DataTable5_9  ;; 0x3c23d70a
        LDR.W    R0,??DataTable5_10
        BL       Get_MidAve
//   84 }
        POP      {R0,R1,R4-R6,PC}  ;; return
//   85 

        SECTION `.text`:CODE:NOROOT(1)
        THUMB
//   86 uint8 Bef_Scan(uint8 *pic_buff)
//   87 {
Bef_Scan:
        PUSH     {R4-R6,LR}
//   88 	uint8 i;
//   89 	int8 Row;
//   90 	uint8 Black_Check = 0;
        MOVS     R2,#+0
//   91 	for(Row = PICTURE_H - 1;Row > PICTURE_H - 4;Row--)
        MOVS     R1,#+39
        B.N      ??Bef_Scan_0
//   92 	{
//   93 		if(White == *(pic_buff + Row * PICTURE_W + 1) &&\ 
//   94 		   White == *(pic_buff + Row * PICTURE_W + 2))        //左线扫描
//   95 		{
//   96 			PIC_DateBlock.TrackInf_DataBlock.LeftLine[Row] = 2;
//   97 			LeftFlag_Switch.LeftBlackLost = 0;
//   98 			LeftFlag_Switch.LeftWhiteLost = 1;
//   99 			LeftFlag_Switch.LeftLost = 1;
//  100 		}
//  101 		else
//  102 		{
//  103 			for(i = 4;i < PICTURE_W - 1;i++)
//  104 			{
//  105 				if(White == *(pic_buff + Row * PICTURE_W + i) && 		\ 
//  106 				   White == *(pic_buff + Row * PICTURE_W + i - 1) && 	\ 
//  107 				   Black == *(pic_buff + Row * PICTURE_W + i - 2) &&	\ 
//  108 				   Black == *(pic_buff + Row * PICTURE_W + i - 3))
//  109 				{
//  110 					PIC_DateBlock.TrackInf_DataBlock.LeftLine[Row] = i - 1;
//  111 					break;
//  112 				}
//  113 			}
//  114 			if(i == PICTURE_W - 1)
//  115 			{
//  116 				PIC_DateBlock.TrackInf_DataBlock.LeftLine[Row] = 1;
//  117 				LeftFlag_Switch.LeftBlackLost = 1;
//  118 				LeftFlag_Switch.LeftWhiteLost = 0;
//  119 				LeftFlag_Switch.LeftLost = 1;
//  120 			}
//  121 			else
//  122 			{
//  123 				LeftFlag_Switch.LeftBlackLost = 0;
//  124 				LeftFlag_Switch.LeftWhiteLost = 0;
//  125 				LeftFlag_Switch.LeftLost = 0;
//  126 
//  127 			}
//  128 		}
//  129 
//  130 		if(White == *(pic_buff + Row * PICTURE_W + PICTURE_W - 2) && \ 
//  131 		   White == *(pic_buff + Row * PICTURE_W + PICTURE_W - 3))      // 右线扫描
//  132 		{
//  133 			PIC_DateBlock.TrackInf_DataBlock.RightLine[Row] = PICTURE_W - 3;
//  134 			RightFlag_Switch.RightBlackLost = 0;
//  135 			RightFlag_Switch.RightWhiteLost = 1;
//  136 			RightFlag_Switch.RightLost = 1;
//  137 		}
//  138 		else
//  139 		{
//  140 			for(i = PICTURE_W - 5;i > 0; i--)
//  141 			{
//  142 				if(White == *(pic_buff + Row * PICTURE_W + i)  &&		\ 
//  143 				   White == *(pic_buff + Row * PICTURE_W + i + 1) &&	\ 
//  144 				   Black == *(pic_buff + Row * PICTURE_W + i + 2) &&	\ 
//  145 				   Black == *(pic_buff + Row * PICTURE_W + i + 3))
//  146 				{
//  147 					PIC_DateBlock.TrackInf_DataBlock.RightLine[Row] = i + 1;
//  148 					RightFlag_Switch.RightLost = 0;
//  149 					break;
//  150 				}
//  151 			}
//  152             if(i == 0)
//  153 			{
//  154 				PIC_DateBlock.TrackInf_DataBlock.RightLine[Row] = PICTURE_W - 3;
//  155 				RightFlag_Switch.RightBlackLost = 1;
//  156 				RightFlag_Switch.RightWhiteLost = 0;
//  157 				RightFlag_Switch.RightLost = 1;
//  158 			}
//  159 			else
//  160 			{
//  161 				RightFlag_Switch.RightBlackLost = 0;
//  162 				RightFlag_Switch.RightWhiteLost = 0;
//  163 				RightFlag_Switch.RightLost = 0;
//  164 			}
//  165 
//  166 		}
//  167    		//右线在左线的左边,设置为缺省值
//  168 		if(PIC_DateBlock.TrackInf_DataBlock.RightLine[Row] < PIC_DateBlock.TrackInf_DataBlock.LeftLine[Row])
//  169 		{
//  170 			PIC_DateBlock.TrackInf_DataBlock.LeftLine[Row] = 2;
//  171 			PIC_DateBlock.TrackInf_DataBlock.RightLine[Row] = 157;
//  172 		}
//  173 		//计算赛道宽度和中线值
//  174 		PIC_DateBlock.TrackInf_DataBlock.TrackWidth = PIC_DateBlock.TrackInf_DataBlock.RightLine[Row]     \ 
//  175 		                                              - PIC_DateBlock.TrackInf_DataBlock.LeftLine[Row];
//  176 		PIC_DateBlock.TrackInf_DataBlock.MidLine[Row] = (PIC_DateBlock.TrackInf_DataBlock.RightLine[Row]     \ 
//  177 		                                                 + PIC_DateBlock.TrackInf_DataBlock.LeftLine[Row]) / 2;
//  178 		(PIC_DateBlock.TrackInf_DataBlock.MidLine[Row] >= 155) ? 	\ 
//  179 			(PIC_DateBlock.TrackInf_DataBlock.MidLine[Row] = 155) : (NULL);
//  180 		(PIC_DateBlock.TrackInf_DataBlock.MidLine[Row] <= 4) ?
//  181 			(PIC_DateBlock.TrackInf_DataBlock.MidLine[Row] = 4) : (NULL);
//  182 		(LeftFlag_Switch.LeftBlackLost == 1 && RightFlag_Switch.RightBlackLost== 1) ?    \ 
//  183 			(Black_Check++) : (NULL);
??Bef_Scan_1:
        MOVS     R3,#+0
??Bef_Scan_2:
        SUBS     R1,R1,#+1
??Bef_Scan_0:
        SXTB     R1,R1            ;; SignExt  R1,R1,#+24,#+24
        CMP      R1,#+37
        BLT.W    ??Bef_Scan_3
        SXTB     R1,R1            ;; SignExt  R1,R1,#+24,#+24
        MOVS     R3,#+160
        SMLABB   R3,R1,R3,R0
        LDRB     R3,[R3, #+1]
        CMP      R3,#+255
        BNE.N    ??Bef_Scan_4
        SXTB     R1,R1            ;; SignExt  R1,R1,#+24,#+24
        MOVS     R3,#+160
        SMLABB   R3,R1,R3,R0
        LDRB     R3,[R3, #+2]
        CMP      R3,#+255
        BNE.N    ??Bef_Scan_4
        MOVS     R3,#+2
        LDR.W    R4,??DataTable5_3
        SXTB     R1,R1            ;; SignExt  R1,R1,#+24,#+24
        ADDS     R4,R4,R1, LSL #+1
        ADDS     R4,R4,#+6400
        STRH     R3,[R4, #+0]
        MOVS     R3,#+0
        LDR.W    R4,??DataTable5_4
        STRB     R3,[R4, #+0]
        MOVS     R3,#+1
        LDR.W    R4,??DataTable5_4
        STRB     R3,[R4, #+1]
        MOVS     R3,#+1
        LDR.W    R4,??DataTable5_4
        STRB     R3,[R4, #+2]
        B.N      ??Bef_Scan_5
??Bef_Scan_4:
        MOVS     R3,#+4
        B.N      ??Bef_Scan_6
??Bef_Scan_7:
        ADDS     R3,R3,#+1
??Bef_Scan_6:
        UXTB     R3,R3            ;; ZeroExt  R3,R3,#+24,#+24
        CMP      R3,#+159
        BGE.N    ??Bef_Scan_8
        SXTB     R1,R1            ;; SignExt  R1,R1,#+24,#+24
        MOVS     R4,#+160
        SMLABB   R4,R1,R4,R0
        UXTB     R3,R3            ;; ZeroExt  R3,R3,#+24,#+24
        LDRB     R4,[R3, R4]
        CMP      R4,#+255
        BNE.N    ??Bef_Scan_7
        SXTB     R1,R1            ;; SignExt  R1,R1,#+24,#+24
        MOVS     R4,#+160
        SMLABB   R4,R1,R4,R0
        UXTB     R3,R3            ;; ZeroExt  R3,R3,#+24,#+24
        ADDS     R4,R3,R4
        LDRB     R4,[R4, #-1]
        CMP      R4,#+255
        BNE.N    ??Bef_Scan_7
        SXTB     R1,R1            ;; SignExt  R1,R1,#+24,#+24
        MOVS     R4,#+160
        SMLABB   R4,R1,R4,R0
        UXTB     R3,R3            ;; ZeroExt  R3,R3,#+24,#+24
        ADDS     R4,R3,R4
        LDRB     R4,[R4, #-2]
        CMP      R4,#+0
        BNE.N    ??Bef_Scan_7
        SXTB     R1,R1            ;; SignExt  R1,R1,#+24,#+24
        MOVS     R4,#+160
        SMLABB   R4,R1,R4,R0
        UXTB     R3,R3            ;; ZeroExt  R3,R3,#+24,#+24
        ADDS     R4,R3,R4
        LDRB     R4,[R4, #-3]
        CMP      R4,#+0
        BNE.N    ??Bef_Scan_7
        UXTB     R3,R3            ;; ZeroExt  R3,R3,#+24,#+24
        SUBS     R4,R3,#+1
        LDR.W    R5,??DataTable5_3
        SXTB     R1,R1            ;; SignExt  R1,R1,#+24,#+24
        ADDS     R5,R5,R1, LSL #+1
        ADDS     R5,R5,#+6400
        STRH     R4,[R5, #+0]
??Bef_Scan_8:
        UXTB     R3,R3            ;; ZeroExt  R3,R3,#+24,#+24
        CMP      R3,#+159
        BNE.N    ??Bef_Scan_9
        MOVS     R3,#+1
        LDR.W    R4,??DataTable5_3
        SXTB     R1,R1            ;; SignExt  R1,R1,#+24,#+24
        ADDS     R4,R4,R1, LSL #+1
        ADDS     R4,R4,#+6400
        STRH     R3,[R4, #+0]
        MOVS     R3,#+1
        LDR.W    R4,??DataTable5_4
        STRB     R3,[R4, #+0]
        MOVS     R3,#+0
        LDR.W    R4,??DataTable5_4
        STRB     R3,[R4, #+1]
        MOVS     R3,#+1
        LDR.W    R4,??DataTable5_4
        STRB     R3,[R4, #+2]
        B.N      ??Bef_Scan_5
??Bef_Scan_9:
        MOVS     R3,#+0
        LDR.W    R4,??DataTable5_4
        STRB     R3,[R4, #+0]
        MOVS     R3,#+0
        LDR.W    R4,??DataTable5_4
        STRB     R3,[R4, #+1]
        MOVS     R3,#+0
        LDR.W    R4,??DataTable5_4
        STRB     R3,[R4, #+2]
??Bef_Scan_5:
        SXTB     R1,R1            ;; SignExt  R1,R1,#+24,#+24
        MOVS     R3,#+160
        SMLABB   R3,R1,R3,R0
        LDRB     R3,[R3, #+158]
        CMP      R3,#+255
        BNE.N    ??Bef_Scan_10
        SXTB     R1,R1            ;; SignExt  R1,R1,#+24,#+24
        MOVS     R3,#+160
        SMLABB   R3,R1,R3,R0
        LDRB     R3,[R3, #+157]
        CMP      R3,#+255
        BNE.N    ??Bef_Scan_10
        MOVS     R3,#+157
        LDR.W    R4,??DataTable5_3
        SXTB     R1,R1            ;; SignExt  R1,R1,#+24,#+24
        ADDS     R4,R4,R1, LSL #+1
        MOVW     R5,#+6480
        STRH     R3,[R5, R4]
        MOVS     R3,#+0
        LDR.W    R4,??DataTable5_5
        STRB     R3,[R4, #+0]
        MOVS     R3,#+1
        LDR.W    R4,??DataTable5_5
        STRB     R3,[R4, #+1]
        MOVS     R3,#+1
        LDR.W    R4,??DataTable5_5
        STRB     R3,[R4, #+2]
        B.N      ??Bef_Scan_11
??Bef_Scan_10:
        MOVS     R3,#+155
        B.N      ??Bef_Scan_12
??Bef_Scan_13:
        SUBS     R3,R3,#+1
??Bef_Scan_12:
        UXTB     R3,R3            ;; ZeroExt  R3,R3,#+24,#+24
        CMP      R3,#+0
        BEQ.N    ??Bef_Scan_14
        SXTB     R1,R1            ;; SignExt  R1,R1,#+24,#+24
        MOVS     R4,#+160
        SMLABB   R4,R1,R4,R0
        UXTB     R3,R3            ;; ZeroExt  R3,R3,#+24,#+24
        LDRB     R4,[R3, R4]
        CMP      R4,#+255
        BNE.N    ??Bef_Scan_13
        SXTB     R1,R1            ;; SignExt  R1,R1,#+24,#+24
        MOVS     R4,#+160
        SMLABB   R4,R1,R4,R0
        UXTB     R3,R3            ;; ZeroExt  R3,R3,#+24,#+24
        ADDS     R4,R3,R4
        LDRB     R4,[R4, #+1]
        CMP      R4,#+255
        BNE.N    ??Bef_Scan_13
        SXTB     R1,R1            ;; SignExt  R1,R1,#+24,#+24
        MOVS     R4,#+160
        SMLABB   R4,R1,R4,R0
        UXTB     R3,R3            ;; ZeroExt  R3,R3,#+24,#+24
        ADDS     R4,R3,R4
        LDRB     R4,[R4, #+2]
        CMP      R4,#+0
        BNE.N    ??Bef_Scan_13
        SXTB     R1,R1            ;; SignExt  R1,R1,#+24,#+24
        MOVS     R4,#+160
        SMLABB   R4,R1,R4,R0
        UXTB     R3,R3            ;; ZeroExt  R3,R3,#+24,#+24
        ADDS     R4,R3,R4
        LDRB     R4,[R4, #+3]
        CMP      R4,#+0
        BNE.N    ??Bef_Scan_13
        UXTB     R3,R3            ;; ZeroExt  R3,R3,#+24,#+24
        ADDS     R4,R3,#+1
        LDR.W    R5,??DataTable5_3
        SXTB     R1,R1            ;; SignExt  R1,R1,#+24,#+24
        ADDS     R5,R5,R1, LSL #+1
        MOVW     R6,#+6480
        STRH     R4,[R6, R5]
        MOVS     R4,#+0
        LDR.W    R5,??DataTable5_5
        STRB     R4,[R5, #+2]
??Bef_Scan_14:
        UXTB     R3,R3            ;; ZeroExt  R3,R3,#+24,#+24
        CMP      R3,#+0
        BNE.N    ??Bef_Scan_15
        MOVS     R3,#+157
        LDR.W    R4,??DataTable5_3
        SXTB     R1,R1            ;; SignExt  R1,R1,#+24,#+24
        ADDS     R4,R4,R1, LSL #+1
        MOVW     R5,#+6480
        STRH     R3,[R5, R4]
        MOVS     R3,#+1
        LDR.W    R4,??DataTable5_5
        STRB     R3,[R4, #+0]
        MOVS     R3,#+0
        LDR.W    R4,??DataTable5_5
        STRB     R3,[R4, #+1]
        MOVS     R3,#+1
        LDR.W    R4,??DataTable5_5
        STRB     R3,[R4, #+2]
        B.N      ??Bef_Scan_11
??Bef_Scan_15:
        MOVS     R3,#+0
        LDR.W    R4,??DataTable5_5
        STRB     R3,[R4, #+0]
        MOVS     R3,#+0
        LDR.W    R4,??DataTable5_5
        STRB     R3,[R4, #+1]
        MOVS     R3,#+0
        LDR.W    R4,??DataTable5_5
        STRB     R3,[R4, #+2]
??Bef_Scan_11:
        LDR.W    R3,??DataTable5_3
        SXTB     R1,R1            ;; SignExt  R1,R1,#+24,#+24
        ADDS     R3,R3,R1, LSL #+1
        MOVW     R4,#+6480
        LDRSH    R3,[R4, R3]
        LDR.W    R4,??DataTable5_3
        SXTB     R1,R1            ;; SignExt  R1,R1,#+24,#+24
        ADDS     R4,R4,R1, LSL #+1
        ADDS     R4,R4,#+6400
        LDRSH    R4,[R4, #+0]
        CMP      R3,R4
        BGE.N    ??Bef_Scan_16
        MOVS     R3,#+2
        LDR.W    R4,??DataTable5_3
        SXTB     R1,R1            ;; SignExt  R1,R1,#+24,#+24
        ADDS     R4,R4,R1, LSL #+1
        ADDS     R4,R4,#+6400
        STRH     R3,[R4, #+0]
        MOVS     R3,#+157
        LDR.W    R4,??DataTable5_3
        SXTB     R1,R1            ;; SignExt  R1,R1,#+24,#+24
        ADDS     R4,R4,R1, LSL #+1
        MOVW     R5,#+6480
        STRH     R3,[R5, R4]
??Bef_Scan_16:
        LDR.W    R3,??DataTable5_3
        SXTB     R1,R1            ;; SignExt  R1,R1,#+24,#+24
        ADDS     R3,R3,R1, LSL #+1
        MOVW     R4,#+6480
        LDRH     R3,[R4, R3]
        LDR.W    R4,??DataTable5_3
        SXTB     R1,R1            ;; SignExt  R1,R1,#+24,#+24
        ADDS     R4,R4,R1, LSL #+1
        ADDS     R4,R4,#+6400
        LDRH     R4,[R4, #+0]
        SUBS     R3,R3,R4
        LDR.W    R4,??DataTable5_11
        STRB     R3,[R4, #+0]
        LDR.W    R3,??DataTable5_3
        SXTB     R1,R1            ;; SignExt  R1,R1,#+24,#+24
        ADDS     R3,R3,R1, LSL #+1
        MOVW     R4,#+6480
        LDRSH    R3,[R4, R3]
        LDR.W    R4,??DataTable5_3
        SXTB     R1,R1            ;; SignExt  R1,R1,#+24,#+24
        ADDS     R4,R4,R1, LSL #+1
        ADDS     R4,R4,#+6400
        LDRSH    R4,[R4, #+0]
        SXTAH    R3,R4,R3
        MOVS     R4,#+2
        SDIV     R3,R3,R4
        LDR.W    R4,??DataTable5_3
        SXTB     R1,R1            ;; SignExt  R1,R1,#+24,#+24
        ADDS     R4,R1,R4
        ADDS     R4,R4,#+6560
        STRB     R3,[R4, #+0]
        LDR.W    R3,??DataTable5_3
        SXTB     R1,R1            ;; SignExt  R1,R1,#+24,#+24
        ADDS     R3,R1,R3
        ADDS     R3,R3,#+6560
        LDRB     R3,[R3, #+0]
        CMP      R3,#+155
        BLT.N    ??Bef_Scan_17
        MOVS     R3,#+155
        LDR.W    R4,??DataTable5_3
        SXTB     R1,R1            ;; SignExt  R1,R1,#+24,#+24
        ADDS     R4,R1,R4
        ADDS     R4,R4,#+6560
        STRB     R3,[R4, #+0]
        LDR.W    R3,??DataTable5_3
        SXTB     R1,R1            ;; SignExt  R1,R1,#+24,#+24
        ADDS     R3,R1,R3
        ADDS     R3,R3,#+6560
        LDRB     R3,[R3, #+0]
        B.N      ??Bef_Scan_18
??Bef_Scan_17:
        MOVS     R3,#+0
??Bef_Scan_18:
        LDR.W    R3,??DataTable5_3
        SXTB     R1,R1            ;; SignExt  R1,R1,#+24,#+24
        ADDS     R3,R1,R3
        ADDS     R3,R3,#+6560
        LDRB     R3,[R3, #+0]
        CMP      R3,#+5
        BGE.N    ??Bef_Scan_19
        MOVS     R3,#+4
        LDR.W    R4,??DataTable5_3
        SXTB     R1,R1            ;; SignExt  R1,R1,#+24,#+24
        ADDS     R4,R1,R4
        ADDS     R4,R4,#+6560
        STRB     R3,[R4, #+0]
        LDR.W    R3,??DataTable5_3
        SXTB     R1,R1            ;; SignExt  R1,R1,#+24,#+24
        ADDS     R3,R1,R3
        ADDS     R3,R3,#+6560
        LDRB     R3,[R3, #+0]
        B.N      ??Bef_Scan_20
??Bef_Scan_19:
        MOVS     R3,#+0
??Bef_Scan_20:
        LDR.W    R3,??DataTable5_4
        LDRB     R3,[R3, #+0]
        LDR.W    R4,??DataTable5_5
        LDRB     R4,[R4, #+0]
        TST      R3,R4
        BEQ.W    ??Bef_Scan_1
        UXTB     R2,R2            ;; ZeroExt  R2,R2,#+24,#+24
        MOVS     R3,R2
        ADDS     R2,R2,#+1
        B.N      ??Bef_Scan_2
//  184 	}
//  185 	if(Black_Check > 2)
??Bef_Scan_3:
        UXTB     R2,R2            ;; ZeroExt  R2,R2,#+24,#+24
        CMP      R2,#+3
        BLT.N    ??Bef_Scan_21
//  186 	{
//  187 
//  188 		LPLD_FTM_PWM_ChangeDuty(FTM0, FTM_Ch1, 0);
        MOVS     R2,#+0
        MOVS     R1,#+1
        LDR.W    R0,??DataTable5_12  ;; 0x40038000
        BL       LPLD_FTM_PWM_ChangeDuty
//  189 		LPLD_FTM_PWM_ChangeDuty(FTM0, FTM_Ch2, 0);
        MOVS     R2,#+0
        MOVS     R1,#+2
        LDR.W    R0,??DataTable5_12  ;; 0x40038000
        BL       LPLD_FTM_PWM_ChangeDuty
//  190 		LPLD_FTM_PWM_ChangeDuty(FTM0, FTM_Ch3, 0);
        MOVS     R2,#+0
        MOVS     R1,#+3
        LDR.W    R0,??DataTable5_12  ;; 0x40038000
        BL       LPLD_FTM_PWM_ChangeDuty
//  191 		LPLD_FTM_PWM_ChangeDuty(FTM0, FTM_Ch4, 0);
        MOVS     R2,#+0
        MOVS     R1,#+4
        LDR.W    R0,??DataTable5_12  ;; 0x40038000
        BL       LPLD_FTM_PWM_ChangeDuty
//  192 		OLED_Clear();
        BL       OLED_Clear
//  193 		OLED_ShowString(0 , 3 , "Car Broke Down!");
        LDR.W    R2,??DataTable5_13
        MOVS     R1,#+3
        MOVS     R0,#+0
        BL       OLED_ShowString
//  194 		while(1);
??Bef_Scan_22:
        B.N      ??Bef_Scan_22
//  195 	}
//  196 	return Row;
??Bef_Scan_21:
        MOVS     R0,R1
        UXTB     R0,R0            ;; ZeroExt  R0,R0,#+24,#+24
        POP      {R4-R6,PC}       ;; return
//  197 }

        SECTION `.text`:CODE:NOROOT(1)
        THUMB
//  198 void TwinLine_Deal(uint8 *pic_buff,int8 Row_buff)
//  199 {
TwinLine_Deal:
        PUSH     {R4,R5}
//  200 	uint8 i;
//  201 	//从中间向左扫左中线
//  202 	for(i = PIC_DateBlock.TrackInf_DataBlock.MidLine[Row_buff + 1];i > 0;i--)
        LDR.W    R2,??DataTable5_3
        SXTB     R1,R1            ;; SignExt  R1,R1,#+24,#+24
        ADDS     R2,R1,R2
        MOVW     R3,#+6561
        LDRB     R2,[R3, R2]
        B.N      ??TwinLine_Deal_0
??TwinLine_Deal_1:
        SUBS     R2,R2,#+1
??TwinLine_Deal_0:
        UXTB     R2,R2            ;; ZeroExt  R2,R2,#+24,#+24
        CMP      R2,#+0
        BEQ.N    ??TwinLine_Deal_2
//  203 	{
//  204 		if(Black == *(pic_buff + Row_buff * PICTURE_W + i) &&		\ 
//  205 		   Black == *(pic_buff + Row_buff * PICTURE_W + i + 1) &&	\ 
//  206 		   White == *(pic_buff + Row_buff * PICTURE_W + i + 2) &&	\ 
//  207 		   White == *(pic_buff + Row_buff * PICTURE_W + i + 3))
        SXTB     R1,R1            ;; SignExt  R1,R1,#+24,#+24
        MOVS     R3,#+160
        SMLABB   R3,R1,R3,R0
        UXTB     R2,R2            ;; ZeroExt  R2,R2,#+24,#+24
        LDRB     R3,[R2, R3]
        CMP      R3,#+0
        BNE.N    ??TwinLine_Deal_1
        SXTB     R1,R1            ;; SignExt  R1,R1,#+24,#+24
        MOVS     R3,#+160
        SMLABB   R3,R1,R3,R0
        UXTB     R2,R2            ;; ZeroExt  R2,R2,#+24,#+24
        ADDS     R3,R2,R3
        LDRB     R3,[R3, #+1]
        CMP      R3,#+0
        BNE.N    ??TwinLine_Deal_1
        SXTB     R1,R1            ;; SignExt  R1,R1,#+24,#+24
        MOVS     R3,#+160
        SMLABB   R3,R1,R3,R0
        UXTB     R2,R2            ;; ZeroExt  R2,R2,#+24,#+24
        ADDS     R3,R2,R3
        LDRB     R3,[R3, #+2]
        CMP      R3,#+255
        BNE.N    ??TwinLine_Deal_1
        SXTB     R1,R1            ;; SignExt  R1,R1,#+24,#+24
        MOVS     R3,#+160
        SMLABB   R3,R1,R3,R0
        UXTB     R2,R2            ;; ZeroExt  R2,R2,#+24,#+24
        ADDS     R3,R2,R3
        LDRB     R3,[R3, #+3]
        CMP      R3,#+255
        BNE.N    ??TwinLine_Deal_1
//  208 		{
//  209 			PIC_DateBlock.TrackInf_DataBlock.LeftLine[Row_buff] = i + 1;
        UXTB     R2,R2            ;; ZeroExt  R2,R2,#+24,#+24
        ADDS     R3,R2,#+1
        LDR.W    R4,??DataTable5_3
        SXTB     R1,R1            ;; SignExt  R1,R1,#+24,#+24
        ADDS     R4,R4,R1, LSL #+1
        ADDS     R4,R4,#+6400
        STRH     R3,[R4, #+0]
//  210 			break;
//  211 		}
//  212 	}
//  213 	if(i == 0)
??TwinLine_Deal_2:
        UXTB     R2,R2            ;; ZeroExt  R2,R2,#+24,#+24
        CMP      R2,#+0
        BNE.W    ??TwinLine_Deal_3
//  214 	{
//  215 		if(White == *(pic_buff + Row_buff * PICTURE_W + 1) &&   \ 
//  216 		   White == *(pic_buff + Row_buff * PICTURE_W + 2))
        SXTB     R1,R1            ;; SignExt  R1,R1,#+24,#+24
        MOVS     R2,#+160
        SMLABB   R2,R1,R2,R0
        LDRB     R2,[R2, #+1]
        CMP      R2,#+255
        BNE.N    ??TwinLine_Deal_4
        SXTB     R1,R1            ;; SignExt  R1,R1,#+24,#+24
        MOVS     R2,#+160
        SMLABB   R2,R1,R2,R0
        LDRB     R2,[R2, #+2]
        CMP      R2,#+255
        BNE.N    ??TwinLine_Deal_4
//  217 		{
//  218 			LeftFlag_Switch.LeftWhiteLost = 1;
        MOVS     R2,#+1
        LDR.W    R3,??DataTable5_4
        STRB     R2,[R3, #+1]
//  219 			LeftFlag_Switch.LeftBlackLost = 0;
        MOVS     R2,#+0
        LDR.W    R3,??DataTable5_4
        STRB     R2,[R3, #+0]
//  220 			LeftFlag_Switch.LeftLost = 1;
        MOVS     R2,#+1
        LDR.W    R3,??DataTable5_4
        STRB     R2,[R3, #+2]
        B.N      ??TwinLine_Deal_5
//  221 		}
//  222 		else
//  223 		{
//  224 			LeftFlag_Switch.LeftWhiteLost = 0;
??TwinLine_Deal_4:
        MOVS     R2,#+0
        LDR.W    R3,??DataTable5_4
        STRB     R2,[R3, #+1]
//  225 			LeftFlag_Switch.LeftBlackLost = 1;
        MOVS     R2,#+1
        LDR.W    R3,??DataTable5_4
        STRB     R2,[R3, #+0]
//  226 			LeftFlag_Switch.LeftLost = 1;
        MOVS     R2,#+1
        LDR.W    R3,??DataTable5_4
        STRB     R2,[R3, #+2]
//  227 		}
//  228 		PIC_DateBlock.TrackInf_DataBlock.LeftLine[Row_buff] = PIC_DateBlock.TrackInf_DataBlock.LeftLine[Row_buff + 1] \ 
//  229 															  + PIC_DateBlock.TrackInf_DataBlock.LeftLine[Row_buff + 2] \ 
//  230 															  - PIC_DateBlock.TrackInf_DataBlock.LeftLine[Row_buff + 3];
??TwinLine_Deal_5:
        LDR.W    R2,??DataTable5_3
        SXTB     R1,R1            ;; SignExt  R1,R1,#+24,#+24
        ADDS     R2,R2,R1, LSL #+1
        MOVW     R3,#+6402
        LDRH     R2,[R3, R2]
        LDR.W    R3,??DataTable5_3
        SXTB     R1,R1            ;; SignExt  R1,R1,#+24,#+24
        ADDS     R3,R3,R1, LSL #+1
        MOVW     R4,#+6404
        LDRH     R3,[R4, R3]
        ADDS     R2,R3,R2
        LDR.W    R3,??DataTable5_3
        SXTB     R1,R1            ;; SignExt  R1,R1,#+24,#+24
        ADDS     R3,R3,R1, LSL #+1
        MOVW     R4,#+6406
        LDRH     R3,[R4, R3]
        SUBS     R2,R2,R3
        LDR.W    R3,??DataTable5_3
        SXTB     R1,R1            ;; SignExt  R1,R1,#+24,#+24
        ADDS     R3,R3,R1, LSL #+1
        ADDS     R3,R3,#+6400
        STRH     R2,[R3, #+0]
//  231 
//  232 		(PIC_DateBlock.TrackInf_DataBlock.LeftLine[Row_buff] <= 2) ?  \ 
//  233 			(PIC_DateBlock.TrackInf_DataBlock.LeftLine[Row_buff] = 2) : (NULL);
        LDR.W    R2,??DataTable5_3
        SXTB     R1,R1            ;; SignExt  R1,R1,#+24,#+24
        ADDS     R2,R2,R1, LSL #+1
        ADDS     R2,R2,#+6400
        LDRSH    R2,[R2, #+0]
        CMP      R2,#+3
        BGE.N    ??TwinLine_Deal_6
        MOVS     R2,#+2
        LDR.W    R3,??DataTable5_3
        SXTB     R1,R1            ;; SignExt  R1,R1,#+24,#+24
        ADDS     R3,R3,R1, LSL #+1
        ADDS     R3,R3,#+6400
        STRH     R2,[R3, #+0]
        LDR.W    R2,??DataTable5_3
        SXTB     R1,R1            ;; SignExt  R1,R1,#+24,#+24
        ADDS     R2,R2,R1, LSL #+1
        ADDS     R2,R2,#+6400
        LDRSH    R2,[R2, #+0]
        B.N      ??TwinLine_Deal_7
??TwinLine_Deal_6:
        MOVS     R2,#+0
//  234 		(PIC_DateBlock.TrackInf_DataBlock.LeftLine[Row_buff] >= PICTURE_W - 3) ?
//  235 			(PIC_DateBlock.TrackInf_DataBlock.LeftLine[Row_buff] = PICTURE_W - 3) : (NULL);
??TwinLine_Deal_7:
        LDR.W    R2,??DataTable5_3
        SXTB     R1,R1            ;; SignExt  R1,R1,#+24,#+24
        ADDS     R2,R2,R1, LSL #+1
        ADDS     R2,R2,#+6400
        LDRSH    R2,[R2, #+0]
        CMP      R2,#+157
        BLT.N    ??TwinLine_Deal_8
        MOVS     R2,#+157
        LDR.W    R3,??DataTable5_3
        SXTB     R1,R1            ;; SignExt  R1,R1,#+24,#+24
        ADDS     R3,R3,R1, LSL #+1
        ADDS     R3,R3,#+6400
        STRH     R2,[R3, #+0]
        LDR.W    R2,??DataTable5_3
        SXTB     R1,R1            ;; SignExt  R1,R1,#+24,#+24
        ADDS     R2,R2,R1, LSL #+1
        ADDS     R2,R2,#+6400
        LDRSH    R2,[R2, #+0]
        B.N      ??TwinLine_Deal_9
??TwinLine_Deal_8:
        MOVS     R2,#+0
        B.N      ??TwinLine_Deal_9
//  236 	}
//  237 	else
//  238 	{
//  239 		LeftFlag_Switch.LeftWhiteLost = 0;
??TwinLine_Deal_3:
        MOVS     R2,#+0
        LDR.N    R3,??DataTable5_4
        STRB     R2,[R3, #+1]
//  240 		LeftFlag_Switch.LeftBlackLost = 0;
        MOVS     R2,#+0
        LDR.N    R3,??DataTable5_4
        STRB     R2,[R3, #+0]
//  241 		LeftFlag_Switch.LeftLost = 0;
        MOVS     R2,#+0
        LDR.N    R3,??DataTable5_4
        STRB     R2,[R3, #+2]
//  242 	}
//  243 	//从中间向右扫右线
//  244 	for(i = PIC_DateBlock.TrackInf_DataBlock.MidLine[Row_buff + 1];i < PICTURE_W - 1;i++)
??TwinLine_Deal_9:
        LDR.N    R2,??DataTable5_3
        SXTB     R1,R1            ;; SignExt  R1,R1,#+24,#+24
        ADDS     R2,R1,R2
        MOVW     R3,#+6561
        LDRB     R2,[R3, R2]
        B.N      ??TwinLine_Deal_10
??TwinLine_Deal_11:
        ADDS     R2,R2,#+1
??TwinLine_Deal_10:
        UXTB     R2,R2            ;; ZeroExt  R2,R2,#+24,#+24
        CMP      R2,#+159
        BGE.N    ??TwinLine_Deal_12
//  245 	{
//  246 		if(Black == *(pic_buff + Row_buff * PICTURE_W + i) &&
//  247 		   Black == *(pic_buff + Row_buff * PICTURE_W + i - 1) &&
//  248 		   White == *(pic_buff + Row_buff * PICTURE_W + i - 2) &&
//  249 		   White == *(pic_buff + Row_buff * PICTURE_W + i - 3))
        SXTB     R1,R1            ;; SignExt  R1,R1,#+24,#+24
        MOVS     R3,#+160
        SMLABB   R3,R1,R3,R0
        UXTB     R2,R2            ;; ZeroExt  R2,R2,#+24,#+24
        LDRB     R3,[R2, R3]
        CMP      R3,#+0
        BNE.N    ??TwinLine_Deal_11
        SXTB     R1,R1            ;; SignExt  R1,R1,#+24,#+24
        MOVS     R3,#+160
        SMLABB   R3,R1,R3,R0
        UXTB     R2,R2            ;; ZeroExt  R2,R2,#+24,#+24
        ADDS     R3,R2,R3
        LDRB     R3,[R3, #-1]
        CMP      R3,#+0
        BNE.N    ??TwinLine_Deal_11
        SXTB     R1,R1            ;; SignExt  R1,R1,#+24,#+24
        MOVS     R3,#+160
        SMLABB   R3,R1,R3,R0
        UXTB     R2,R2            ;; ZeroExt  R2,R2,#+24,#+24
        ADDS     R3,R2,R3
        LDRB     R3,[R3, #-2]
        CMP      R3,#+255
        BNE.N    ??TwinLine_Deal_11
        SXTB     R1,R1            ;; SignExt  R1,R1,#+24,#+24
        MOVS     R3,#+160
        SMLABB   R3,R1,R3,R0
        UXTB     R2,R2            ;; ZeroExt  R2,R2,#+24,#+24
        ADDS     R3,R2,R3
        LDRB     R3,[R3, #-3]
        CMP      R3,#+255
        BNE.N    ??TwinLine_Deal_11
//  250 		{
//  251 			PIC_DateBlock.TrackInf_DataBlock.RightLine[Row_buff] = i - 1;
        UXTB     R2,R2            ;; ZeroExt  R2,R2,#+24,#+24
        SUBS     R3,R2,#+1
        LDR.N    R4,??DataTable5_3
        SXTB     R1,R1            ;; SignExt  R1,R1,#+24,#+24
        ADDS     R4,R4,R1, LSL #+1
        MOVW     R5,#+6480
        STRH     R3,[R5, R4]
//  252 			break;
//  253 		}
//  254 	}
//  255 	if(i == PICTURE_W - 1)
??TwinLine_Deal_12:
        UXTB     R2,R2            ;; ZeroExt  R2,R2,#+24,#+24
        CMP      R2,#+159
        BNE.N    ??TwinLine_Deal_13
//  256 	{
//  257 		if(White == *(pic_buff + Row_buff * PICTURE_W + PICTURE_W - 2) &&   \ 
//  258 		   White == *(pic_buff + Row_buff * PICTURE_W + PICTURE_W - 3)  )
        SXTB     R1,R1            ;; SignExt  R1,R1,#+24,#+24
        MOVS     R2,#+160
        SMLABB   R2,R1,R2,R0
        LDRB     R2,[R2, #+158]
        CMP      R2,#+255
        BNE.N    ??TwinLine_Deal_14
        SXTB     R1,R1            ;; SignExt  R1,R1,#+24,#+24
        MOVS     R2,#+160
        SMLABB   R0,R1,R2,R0
        LDRB     R0,[R0, #+157]
        CMP      R0,#+255
        BNE.N    ??TwinLine_Deal_14
//  259 		{
//  260 			RightFlag_Switch.RightWhiteLost = 1;
        MOVS     R0,#+1
        LDR.N    R2,??DataTable5_5
        STRB     R0,[R2, #+1]
//  261 			RightFlag_Switch.RightBlackLost = 0;
        MOVS     R0,#+0
        LDR.N    R2,??DataTable5_5
        STRB     R0,[R2, #+0]
//  262 			RightFlag_Switch.RightLost = 1;
        MOVS     R0,#+1
        LDR.N    R2,??DataTable5_5
        STRB     R0,[R2, #+2]
        B.N      ??TwinLine_Deal_15
//  263 		}
//  264 		else
//  265 		{
//  266 			RightFlag_Switch.RightWhiteLost = 0;
??TwinLine_Deal_14:
        MOVS     R0,#+0
        LDR.N    R2,??DataTable5_5
        STRB     R0,[R2, #+1]
//  267 			RightFlag_Switch.RightBlackLost = 1;
        MOVS     R0,#+1
        LDR.N    R2,??DataTable5_5
        STRB     R0,[R2, #+0]
//  268 			RightFlag_Switch.RightLost = 1;
        MOVS     R0,#+1
        LDR.N    R2,??DataTable5_5
        STRB     R0,[R2, #+2]
//  269 		}
//  270 		PIC_DateBlock.TrackInf_DataBlock.RightLine[Row_buff] = PIC_DateBlock.TrackInf_DataBlock.RightLine[Row_buff + 1] \ 
//  271 															   + PIC_DateBlock.TrackInf_DataBlock.RightLine[Row_buff + 2] \ 
//  272 															   - PIC_DateBlock.TrackInf_DataBlock.RightLine[Row_buff + 3];
??TwinLine_Deal_15:
        LDR.N    R0,??DataTable5_3
        SXTB     R1,R1            ;; SignExt  R1,R1,#+24,#+24
        ADDS     R0,R0,R1, LSL #+1
        MOVW     R2,#+6482
        LDRH     R0,[R2, R0]
        LDR.N    R2,??DataTable5_3
        SXTB     R1,R1            ;; SignExt  R1,R1,#+24,#+24
        ADDS     R2,R2,R1, LSL #+1
        MOVW     R3,#+6484
        LDRH     R2,[R3, R2]
        ADDS     R0,R2,R0
        LDR.N    R2,??DataTable5_3
        SXTB     R1,R1            ;; SignExt  R1,R1,#+24,#+24
        ADDS     R2,R2,R1, LSL #+1
        MOVW     R3,#+6486
        LDRH     R2,[R3, R2]
        SUBS     R0,R0,R2
        LDR.N    R2,??DataTable5_3
        SXTB     R1,R1            ;; SignExt  R1,R1,#+24,#+24
        ADDS     R2,R2,R1, LSL #+1
        MOVW     R3,#+6480
        STRH     R0,[R3, R2]
//  273 		(PIC_DateBlock.TrackInf_DataBlock.RightLine[Row_buff] >= PICTURE_W - 3) ? \ 
//  274 			(PIC_DateBlock.TrackInf_DataBlock.RightLine[Row_buff] = PICTURE_W - 3) : (NULL);
        LDR.N    R0,??DataTable5_3
        SXTB     R1,R1            ;; SignExt  R1,R1,#+24,#+24
        ADDS     R0,R0,R1, LSL #+1
        MOVW     R2,#+6480
        LDRSH    R0,[R2, R0]
        CMP      R0,#+157
        BLT.N    ??TwinLine_Deal_16
        MOVS     R0,#+157
        LDR.N    R2,??DataTable5_3
        SXTB     R1,R1            ;; SignExt  R1,R1,#+24,#+24
        ADDS     R2,R2,R1, LSL #+1
        MOVW     R3,#+6480
        STRH     R0,[R3, R2]
        LDR.N    R0,??DataTable5_3
        SXTB     R1,R1            ;; SignExt  R1,R1,#+24,#+24
        ADDS     R0,R0,R1, LSL #+1
        MOVW     R2,#+6480
        LDRSH    R0,[R2, R0]
        B.N      ??TwinLine_Deal_17
??TwinLine_Deal_16:
        MOVS     R0,#+0
//  275 		(PIC_DateBlock.TrackInf_DataBlock.RightLine[Row_buff] <= 2) ? \ 
//  276 			(PIC_DateBlock.TrackInf_DataBlock.RightLine[Row_buff] = 2) : (NULL);
??TwinLine_Deal_17:
        LDR.N    R0,??DataTable5_3
        SXTB     R1,R1            ;; SignExt  R1,R1,#+24,#+24
        ADDS     R0,R0,R1, LSL #+1
        MOVW     R2,#+6480
        LDRSH    R0,[R2, R0]
        CMP      R0,#+3
        BGE.N    ??TwinLine_Deal_18
        MOVS     R0,#+2
        LDR.N    R2,??DataTable5_3
        SXTB     R1,R1            ;; SignExt  R1,R1,#+24,#+24
        ADDS     R2,R2,R1, LSL #+1
        MOVW     R3,#+6480
        STRH     R0,[R3, R2]
        LDR.N    R0,??DataTable5_3
        SXTB     R1,R1            ;; SignExt  R1,R1,#+24,#+24
        ADDS     R0,R0,R1, LSL #+1
        MOVW     R2,#+6480
        LDRSH    R0,[R2, R0]
        B.N      ??TwinLine_Deal_19
??TwinLine_Deal_18:
        MOVS     R0,#+0
        B.N      ??TwinLine_Deal_19
//  277 	}
//  278 	else
//  279 	{
//  280 		RightFlag_Switch.RightWhiteLost = 0;
??TwinLine_Deal_13:
        MOVS     R0,#+0
        LDR.N    R2,??DataTable5_5
        STRB     R0,[R2, #+1]
//  281 		RightFlag_Switch.RightBlackLost = 0;
        MOVS     R0,#+0
        LDR.N    R2,??DataTable5_5
        STRB     R0,[R2, #+0]
//  282 		RightFlag_Switch.RightLost = 0;
        MOVS     R0,#+0
        LDR.N    R2,??DataTable5_5
        STRB     R0,[R2, #+2]
//  283 	}
//  284 	PIC_DateBlock.TrackInf_DataBlock.TrackWidth = PIC_DateBlock.TrackInf_DataBlock.RightLine[Row_buff]     \ 
//  285 		                                              - PIC_DateBlock.TrackInf_DataBlock.LeftLine[Row_buff];
??TwinLine_Deal_19:
        LDR.N    R0,??DataTable5_3
        SXTB     R1,R1            ;; SignExt  R1,R1,#+24,#+24
        ADDS     R0,R0,R1, LSL #+1
        MOVW     R2,#+6480
        LDRH     R0,[R2, R0]
        LDR.N    R2,??DataTable5_3
        SXTB     R1,R1            ;; SignExt  R1,R1,#+24,#+24
        ADDS     R2,R2,R1, LSL #+1
        ADDS     R2,R2,#+6400
        LDRH     R2,[R2, #+0]
        SUBS     R0,R0,R2
        LDR.N    R2,??DataTable5_11
        STRB     R0,[R2, #+0]
//  286 	PIC_DateBlock.TrackInf_DataBlock.MidLine[Row_buff] = (PIC_DateBlock.TrackInf_DataBlock.RightLine[Row_buff]     \ 
//  287 		                                                 + PIC_DateBlock.TrackInf_DataBlock.LeftLine[Row_buff]) / 2;
        LDR.N    R0,??DataTable5_3
        SXTB     R1,R1            ;; SignExt  R1,R1,#+24,#+24
        ADDS     R0,R0,R1, LSL #+1
        MOVW     R2,#+6480
        LDRSH    R0,[R2, R0]
        LDR.N    R2,??DataTable5_3
        SXTB     R1,R1            ;; SignExt  R1,R1,#+24,#+24
        ADDS     R2,R2,R1, LSL #+1
        ADDS     R2,R2,#+6400
        LDRSH    R2,[R2, #+0]
        SXTAH    R0,R2,R0
        MOVS     R2,#+2
        SDIV     R0,R0,R2
        LDR.N    R2,??DataTable5_3
        SXTB     R1,R1            ;; SignExt  R1,R1,#+24,#+24
        ADDS     R2,R1,R2
        ADDS     R2,R2,#+6560
        STRB     R0,[R2, #+0]
//  288 	(PIC_DateBlock.TrackInf_DataBlock.MidLine[Row_buff] >= 155) ? 	\ 
//  289 		(PIC_DateBlock.TrackInf_DataBlock.MidLine[Row_buff] = 155) : (NULL);
        LDR.N    R0,??DataTable5_3
        SXTB     R1,R1            ;; SignExt  R1,R1,#+24,#+24
        ADDS     R0,R1,R0
        ADDS     R0,R0,#+6560
        LDRB     R0,[R0, #+0]
        CMP      R0,#+155
        BLT.N    ??TwinLine_Deal_20
        MOVS     R0,#+155
        LDR.N    R2,??DataTable5_3
        SXTB     R1,R1            ;; SignExt  R1,R1,#+24,#+24
        ADDS     R2,R1,R2
        ADDS     R2,R2,#+6560
        STRB     R0,[R2, #+0]
        LDR.N    R0,??DataTable5_3
        SXTB     R1,R1            ;; SignExt  R1,R1,#+24,#+24
        ADDS     R0,R1,R0
        ADDS     R0,R0,#+6560
        LDRB     R0,[R0, #+0]
        B.N      ??TwinLine_Deal_21
??TwinLine_Deal_20:
        MOVS     R0,#+0
//  290 	(PIC_DateBlock.TrackInf_DataBlock.MidLine[Row_buff] <= 4) ?
//  291 		(PIC_DateBlock.TrackInf_DataBlock.MidLine[Row_buff] = 4) : (NULL);
??TwinLine_Deal_21:
        LDR.N    R0,??DataTable5_3
        SXTB     R1,R1            ;; SignExt  R1,R1,#+24,#+24
        ADDS     R0,R1,R0
        ADDS     R0,R0,#+6560
        LDRB     R0,[R0, #+0]
        CMP      R0,#+5
        BGE.N    ??TwinLine_Deal_22
        MOVS     R0,#+4
        LDR.N    R2,??DataTable5_3
        SXTB     R1,R1            ;; SignExt  R1,R1,#+24,#+24
        ADDS     R2,R1,R2
        ADDS     R2,R2,#+6560
        STRB     R0,[R2, #+0]
        LDR.N    R0,??DataTable5_3
        SXTB     R1,R1            ;; SignExt  R1,R1,#+24,#+24
        ADDS     R0,R1,R0
        ADDS     R0,R0,#+6560
        LDRB     R0,[R0, #+0]
        B.N      ??TwinLine_Deal_23
??TwinLine_Deal_22:
        MOVS     R0,#+0
//  292 }
??TwinLine_Deal_23:
        POP      {R4,R5}
        BX       LR               ;; return
//  293 

        SECTION `.text`:CODE:NOROOT(1)
        THUMB
//  294 void Get_MidAve(uint8 *MidLine_Buff,float32 Coe_1,float32 Coe_2,float32 Coe_3,float32 Coe_4)
//  295 {
Get_MidAve:
        PUSH     {R1,R4-R11,LR}
        MOVS     R4,R0
        MOVS     R5,R2
        MOVS     R6,R3
//  296 	uint8 i;
//  297 	float32 sum1,sum2,sum3,sum4;
//  298 	for (i = 0; i < 10; i++)
        MOVS     R7,#+0
        B.N      ??Get_MidAve_0
//  299 	{
//  300 		sum1 += *(MidLine_Buff + i);
??Get_MidAve_1:
        UXTB     R7,R7            ;; ZeroExt  R7,R7,#+24,#+24
        LDRB     R0,[R7, R4]
        BL       __aeabi_ui2f
        MOV      R1,R8
        BL       __aeabi_fadd
        MOV      R8,R0
//  301 	}
        ADDS     R7,R7,#+1
??Get_MidAve_0:
        UXTB     R7,R7            ;; ZeroExt  R7,R7,#+24,#+24
        CMP      R7,#+10
        BLT.N    ??Get_MidAve_1
//  302 	for (; i < 20; i++)
??Get_MidAve_2:
        UXTB     R7,R7            ;; ZeroExt  R7,R7,#+24,#+24
        CMP      R7,#+20
        BGE.N    ??Get_MidAve_3
//  303 	{
//  304 		sum2 += *(MidLine_Buff + i);
        UXTB     R7,R7            ;; ZeroExt  R7,R7,#+24,#+24
        LDRB     R0,[R7, R4]
        BL       __aeabi_ui2f
        MOV      R1,R9
        BL       __aeabi_fadd
        MOV      R9,R0
//  305 	}
        ADDS     R7,R7,#+1
        B.N      ??Get_MidAve_2
//  306 	for(; i < 30; i++)
//  307 	{
//  308 		sum3 += *(MidLine_Buff + i);
??Get_MidAve_4:
        UXTB     R7,R7            ;; ZeroExt  R7,R7,#+24,#+24
        LDRB     R0,[R7, R4]
        BL       __aeabi_ui2f
        MOV      R1,R10
        BL       __aeabi_fadd
        MOV      R10,R0
//  309 	}
        ADDS     R7,R7,#+1
??Get_MidAve_3:
        UXTB     R7,R7            ;; ZeroExt  R7,R7,#+24,#+24
        CMP      R7,#+30
        BLT.N    ??Get_MidAve_4
//  310 	for(; i < 40; i++)
??Get_MidAve_5:
        UXTB     R7,R7            ;; ZeroExt  R7,R7,#+24,#+24
        CMP      R7,#+40
        BGE.N    ??Get_MidAve_6
//  311 	{
//  312 		sum4 += *(MidLine_Buff + i);
        UXTB     R7,R7            ;; ZeroExt  R7,R7,#+24,#+24
        LDRB     R0,[R7, R4]
        BL       __aeabi_ui2f
        MOV      R1,R11
        BL       __aeabi_fadd
        MOV      R11,R0
//  313 	}
        ADDS     R7,R7,#+1
        B.N      ??Get_MidAve_5
//  314 	sum1 *= Coe_1 , sum2 *= Coe_2 , sum3 *= Coe_3 , sum4 *= Coe_4;
??Get_MidAve_6:
        LDR      R0,[SP, #+0]
        MOV      R1,R8
        BL       __aeabi_fmul
        MOV      R8,R0
        MOV      R0,R9
        MOVS     R1,R5
        BL       __aeabi_fmul
        MOV      R9,R0
        MOV      R0,R10
        MOVS     R1,R6
        BL       __aeabi_fmul
        MOV      R10,R0
        LDR      R0,[SP, #+40]
        MOV      R1,R11
        BL       __aeabi_fmul
        MOV      R11,R0
//  315 	MidAve = (int16) (sum1 + sum2 + sum3 + sum4);
        MOV      R0,R8
        MOV      R1,R9
        BL       __aeabi_fadd
        MOV      R1,R10
        BL       __aeabi_fadd
        MOV      R1,R11
        BL       __aeabi_fadd
        BL       __aeabi_f2iz
        LDR.N    R1,??DataTable5_14
        STRH     R0,[R1, #+0]
//  316 }
        POP      {R0,R4-R11,PC}   ;; return

        SECTION `.text`:CODE:NOROOT(1)
        THUMB
//  317 void Get_Img(void)
//  318 {
Get_Img:
        PUSH     {R7,LR}
//  319     ov7725_eagle_img_flag = IMG_START;                   //¿ªÊ¼²É¼¯Í¼Ïñ
        MOVS     R0,#+4
        LDR.N    R1,??DataTable5_15
        STRB     R0,[R1, #+0]
//  320     PORTA->ISFR = ~0;
        MOVS     R0,#-1
        LDR.N    R1,??DataTable5_16  ;; 0x400490a0
        STR      R0,[R1, #+0]
//  321     enable_irq((IRQn_Type)(PORTA_IRQn));
        MOVS     R0,#+87
        BL       NVIC_EnableIRQ
        B.N      ??Get_Img_0
//  322     while (ov7725_eagle_img_flag != IMG_FINISH)
//  323     {
//  324         if (ov7725_eagle_img_flag == IMG_FAIL)            //¼ÙÈçÍ¼Ïñ²É¼¯´íÎó£¬ÔòÖØÐÂ¿ªÊ¼²É¼¯
??Get_Img_1:
        LDR.N    R0,??DataTable5_15
        LDRB     R0,[R0, #+0]
        CMP      R0,#+2
        BNE.N    ??Get_Img_0
//  325         {
//  326             ov7725_eagle_img_flag = IMG_START;           //¿ªÊ¼²É¼¯Í¼Ïñ
        MOVS     R0,#+4
        LDR.N    R1,??DataTable5_15
        STRB     R0,[R1, #+0]
//  327             PORTA->ISFR = 0xFFFFFFFFu;                //Ð´1ÇåÖÐ¶Ï±êÖ¾Î»(±ØÐëµÄ£¬²»È»»Øµ¼ÖÂÒ»¿ªÖÐ¶Ï¾ÍÂíÉÏ´¥·¢ÖÐ¶Ï)
        MOVS     R0,#-1
        LDR.N    R1,??DataTable5_16  ;; 0x400490a0
        STR      R0,[R1, #+0]
//  328             enable_irq(PORTA_IRQn);                 //ÔÊÐíPTAµÄÖÐ¶Ï
        MOVS     R0,#+87
        BL       NVIC_EnableIRQ
//  329         }
//  330     }
??Get_Img_0:
        LDR.N    R0,??DataTable5_15
        LDRB     R0,[R0, #+0]
        CMP      R0,#+1
        BNE.N    ??Get_Img_1
//  331 }
        POP      {R0,PC}          ;; return

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable5:
        DC32     0xe000e100

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable5_1:
        DC32     imgbuff

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable5_2:
        DC32     img

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable5_3:
        DC32     PIC_DateBlock

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable5_4:
        DC32     LeftFlag_Switch

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable5_5:
        DC32     RightFlag_Switch

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable5_6:
        DC32     0x3ca3d70a

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable5_7:
        DC32     0x3cf5c28f

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable5_8:
        DC32     0x3d23d70a

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable5_9:
        DC32     0x3c23d70a

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable5_10:
        DC32     PIC_DateBlock+0x19A0

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable5_11:
        DC32     PIC_DateBlock+0x19C8

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable5_12:
        DC32     0x40038000

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable5_13:
        DC32     ?_0

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable5_14:
        DC32     MidAve

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable5_15:
        DC32     ov7725_eagle_img_flag

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable5_16:
        DC32     0x400490a0

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
        DC8 "Car Broke Down!"

        END
//  332 
// 
// 6 622 bytes in section .bss
//    16 bytes in section .rodata
// 2 740 bytes in section .text
// 
// 2 740 bytes of CODE  memory
//    16 bytes of CONST memory
// 6 622 bytes of DATA  memory
//
//Errors: none
//Warnings: none
