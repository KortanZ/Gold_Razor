/*
*This head file for image processing
*include edge extacting
*include
*/
//#include "common.h"
#include "ImgProcess.h"
#include "Eagle_ov7725.h"
#include "VirtualOsc.h"
#include "Oled.h"
#include "PID.h"
#include "SteerDriver.h"
#include "MotorDriver.h"
#include "EncoderDriver.h"

PIC_DateStruct PIC_DateBlock;
CrossInf_Struct CrossInf_Data;
LeftFlag_Struct LeftFlag_Switch;
RightFlag_Struct RightFlag_Switch;


void Cross_Check(int8 );
uint8 Bef_Scan(uint8*);
void TwinLine_Deal(uint8 *,int8);
void LinerFitting(int16 *,uint8 ,uint8 ,uint8 );
void CrossDeal(void);
void BlackDeal(int8 );
void Get_MidAve(uint8 * ,float32 ,float32 ,float32 ,float32);
void clearflag(void);




int16 MidAve = 0;
uint8 brokeDownFlag = 0;
float32 weight[4] = {0.02, 0.04, 0.02, 0.02};

void Get_MidLine(void)
{
	uint8 i,j,k;
	int8 Row;
	img_extract(img,imgbuff,CAMERA_SIZE);       //å›¾åƒè§£åŽ‹
	for(k = 0,i = 1; i < CAMERA_H; i += 3 , k++)          //éš”è¡Œæå–
	{
		for(j = 0; j < CAMERA_W; j++)
		{
			PIC_DateBlock.pic[CAMERA_W * k + j] = img[i * CAMERA_W + j];
		}
	}

	for(Row = Bef_Scan(PIC_DateBlock.pic);Row >= 0;Row--)
	{
		/*SingleLine_Deal(Row);
		if(SingleModle_Flag)
		{

		}*/

		TwinLine_Deal(PIC_DateBlock.pic,Row);


		if(LeftFlag_Switch.LeftTurnFlag || RightFlag_Switch.RightTurnFlag)
		{
			if(LeftFlag_Switch.LeftBlackLost&& RightFlag_Switch.RightBlackLost)
				break;
		}
	}

	if(Row < 0)
	{
		if(LeftFlag_Switch.LeftCrossFlag && RightFlag_Switch.RightCrossFlag)
		{
			CrossDeal();
		}
	}
	else
	{
		BlackDeal(Row);
	}
	//BlackDeal(Row);

	Get_MidAve(PIC_DateBlock.TrackInf_DataBlock.MidLine  \
		       , weight[0]    \
		       , weight[1]    \
		       , weight[2]    \
		       , weight[3]);
}

uint8 Bef_Scan(uint8 *pic_buff)
{
	uint8 i;
	int8 Row;
	uint8 Black_Check = 0;
	for(Row = PICTURE_H - 1;Row > PICTURE_H - 4;Row--)
	{
		if(White == *(pic_buff + Row * PICTURE_W + 1) && \
		   White == *(pic_buff + Row * PICTURE_W + 2))        //å·¦çº¿æ‰«æ
		{
			PIC_DateBlock.TrackInf_DataBlock.LeftLine[Row] = 2;
			LeftFlag_Switch.LeftBlackLost = 0;
			LeftFlag_Switch.LeftWhiteLost = 1;
			LeftFlag_Switch.LeftLost = 1;
		}
		else
		{
			for(i = 4;i < PICTURE_W - 1;i++)
			{
				if(White == *(pic_buff + Row * PICTURE_W + i) && 		\
				   White == *(pic_buff + Row * PICTURE_W + i - 1) && 	\
				   Black == *(pic_buff + Row * PICTURE_W + i - 2) &&	\
				   Black == *(pic_buff + Row * PICTURE_W + i - 3))
				{
					PIC_DateBlock.TrackInf_DataBlock.LeftLine[Row] = i - 1;
					break;
				}
			}
			if(i == PICTURE_W - 1)
			{
				PIC_DateBlock.TrackInf_DataBlock.LeftLine[Row] = 1;
				LeftFlag_Switch.LeftBlackLost = 1;
				LeftFlag_Switch.LeftWhiteLost = 0;
				LeftFlag_Switch.LeftLost = 1;
			}
			else
			{
				LeftFlag_Switch.LeftBlackLost = 0;
				LeftFlag_Switch.LeftWhiteLost = 0;
				LeftFlag_Switch.LeftLost = 0;

			}
		}

		if(White == *(pic_buff + Row * PICTURE_W + PICTURE_W - 2) && \
		   White == *(pic_buff + Row * PICTURE_W + PICTURE_W - 3))      // å³çº¿æ‰«æ
		{
			PIC_DateBlock.TrackInf_DataBlock.RightLine[Row] = PICTURE_W - 3;
			RightFlag_Switch.RightBlackLost = 0;
			RightFlag_Switch.RightWhiteLost = 1;
			RightFlag_Switch.RightLost = 1;
		}
		else
		{
			for(i = PICTURE_W - 5;i > 0; i--)
			{
				if(White == *(pic_buff + Row * PICTURE_W + i)  &&		\
				   White == *(pic_buff + Row * PICTURE_W + i + 1) &&	\
				   Black == *(pic_buff + Row * PICTURE_W + i + 2) &&	\
				   Black == *(pic_buff + Row * PICTURE_W + i + 3))
				{
					PIC_DateBlock.TrackInf_DataBlock.RightLine[Row] = i + 1;
					RightFlag_Switch.RightLost = 0;
					break;
				}
			}
            if(i == 0)
			{
				PIC_DateBlock.TrackInf_DataBlock.RightLine[Row] = PICTURE_W - 3;
				RightFlag_Switch.RightBlackLost = 1;
				RightFlag_Switch.RightWhiteLost = 0;
				RightFlag_Switch.RightLost = 1;
			}
			else
			{
				RightFlag_Switch.RightBlackLost = 0;
				RightFlag_Switch.RightWhiteLost = 0;
				RightFlag_Switch.RightLost = 0;
			}

		}
   		//å³çº¿åœ¨å·¦çº¿çš„å·¦è¾¹,è®¾ç½®ä¸ºç¼ºçœå€¼
		if(PIC_DateBlock.TrackInf_DataBlock.RightLine[Row] < PIC_DateBlock.TrackInf_DataBlock.LeftLine[Row])
		{
			PIC_DateBlock.TrackInf_DataBlock.LeftLine[Row] = 2;
			PIC_DateBlock.TrackInf_DataBlock.RightLine[Row] = 157;
		}
		//è®¡ç®—èµ›é“å®½åº¦å’Œä¸­çº¿å€¼
		PIC_DateBlock.TrackInf_DataBlock.TrackWidth = PIC_DateBlock.TrackInf_DataBlock.RightLine[Row]     \
		                                              - PIC_DateBlock.TrackInf_DataBlock.LeftLine[Row];
		PIC_DateBlock.TrackInf_DataBlock.MidLine[Row] = (PIC_DateBlock.TrackInf_DataBlock.RightLine[Row]     \
		                                                 + PIC_DateBlock.TrackInf_DataBlock.LeftLine[Row]) / 2;
		(PIC_DateBlock.TrackInf_DataBlock.MidLine[Row] >= 155) ? 	\
			(PIC_DateBlock.TrackInf_DataBlock.MidLine[Row] = 155) : (NULL);
		(PIC_DateBlock.TrackInf_DataBlock.MidLine[Row] <= 4) ?
			(PIC_DateBlock.TrackInf_DataBlock.MidLine[Row] = 4) : (NULL);
		(LeftFlag_Switch.LeftBlackLost == 1 && RightFlag_Switch.RightBlackLost== 1) ?    \
			(Black_Check++) : (NULL);
	}
	Cross_Check(Row) ;

	/*              å†²å‡ºèµ›é“åœè½¦ä»£ç å—        */
	if(Black_Check > 2)
	{

		LPLD_FTM_PWM_ChangeDuty(FTM0, FTM_Ch1, 0);
		LPLD_FTM_PWM_ChangeDuty(FTM0, FTM_Ch2, 0);
		LPLD_FTM_PWM_ChangeDuty(FTM0, FTM_Ch3, 0);
		LPLD_FTM_PWM_ChangeDuty(FTM0, FTM_Ch4, 0);
		OLED_ClearLine(5);
		OLED_ShowString(0 ,5 ,"Car Broke Down!");
		brokeDownFlag = 1;
		while(brokeDownFlag);
	}
	return Row;
}
void TwinLine_Deal(uint8 *pic_buff,int8 Row_buff)
{
	uint8 i;
	//ä»Žä¸­é—´å‘å·¦æ‰«å·¦ä¸­çº¿
	for(i = PIC_DateBlock.TrackInf_DataBlock.MidLine[Row_buff + 1];i > 0;i--)
	{
		if(Black == *(pic_buff + Row_buff * PICTURE_W + i) &&		\
		   Black == *(pic_buff + Row_buff * PICTURE_W + i + 1) &&	\
		   White == *(pic_buff + Row_buff * PICTURE_W + i + 2) &&	\
		   White == *(pic_buff + Row_buff * PICTURE_W + i + 3))
		{
			PIC_DateBlock.TrackInf_DataBlock.LeftLine[Row_buff] = i + 1;
			break;
		}
	}
	if(i == 0)
	{
		if(White == *(pic_buff + Row_buff * PICTURE_W + 1) &&   \
		   White == *(pic_buff + Row_buff * PICTURE_W + 2))
		{
			LeftFlag_Switch.LeftWhiteLost = 1;
			LeftFlag_Switch.LeftBlackLost = 0;
			LeftFlag_Switch.LeftLost = 1;
		}
		else
		{
			LeftFlag_Switch.LeftWhiteLost = 0;
			LeftFlag_Switch.LeftBlackLost = 1;
			LeftFlag_Switch.LeftLost = 1;
		}
		PIC_DateBlock.TrackInf_DataBlock.LeftLine[Row_buff] = PIC_DateBlock.TrackInf_DataBlock.LeftLine[Row_buff + 1] \
															  + PIC_DateBlock.TrackInf_DataBlock.LeftLine[Row_buff + 2] \
															  - PIC_DateBlock.TrackInf_DataBlock.LeftLine[Row_buff + 3];

		(PIC_DateBlock.TrackInf_DataBlock.LeftLine[Row_buff] <= 2) ?  \
			(PIC_DateBlock.TrackInf_DataBlock.LeftLine[Row_buff] = 2) : (NULL);
		(PIC_DateBlock.TrackInf_DataBlock.LeftLine[Row_buff] >= PICTURE_W - 3) ?
			(PIC_DateBlock.TrackInf_DataBlock.LeftLine[Row_buff] = PICTURE_W - 3) : (NULL);
	}
	else
	{
		LeftFlag_Switch.LeftWhiteLost = 0;
		LeftFlag_Switch.LeftBlackLost = 0;
		LeftFlag_Switch.LeftLost = 0;
	}
	//ä»Žä¸­é—´å‘å³æ‰«å³çº¿
	for(i = PIC_DateBlock.TrackInf_DataBlock.MidLine[Row_buff + 1];i < PICTURE_W - 1;i++)
	{
		if(Black == *(pic_buff + Row_buff * PICTURE_W + i) &&
		   Black == *(pic_buff + Row_buff * PICTURE_W + i - 1) &&
		   White == *(pic_buff + Row_buff * PICTURE_W + i - 2) &&
		   White == *(pic_buff + Row_buff * PICTURE_W + i - 3))
		{
			PIC_DateBlock.TrackInf_DataBlock.RightLine[Row_buff] = i - 1;
			break;
		}
	}
	if(i == PICTURE_W - 1)
	{
		if(White == *(pic_buff + Row_buff * PICTURE_W + PICTURE_W - 2) &&   \
		   White == *(pic_buff + Row_buff * PICTURE_W + PICTURE_W - 3)  )
		{
			RightFlag_Switch.RightWhiteLost = 1;
			RightFlag_Switch.RightBlackLost = 0;
			RightFlag_Switch.RightLost = 1;
		}
		else
		{
			RightFlag_Switch.RightWhiteLost = 0;
			RightFlag_Switch.RightBlackLost = 1;
			RightFlag_Switch.RightLost = 1;
		}
		PIC_DateBlock.TrackInf_DataBlock.RightLine[Row_buff] = PIC_DateBlock.TrackInf_DataBlock.RightLine[Row_buff + 1] \
															   + PIC_DateBlock.TrackInf_DataBlock.RightLine[Row_buff + 2] \
															   - PIC_DateBlock.TrackInf_DataBlock.RightLine[Row_buff + 3];
		(PIC_DateBlock.TrackInf_DataBlock.RightLine[Row_buff] >= PICTURE_W - 3) ? \
			(PIC_DateBlock.TrackInf_DataBlock.RightLine[Row_buff] = PICTURE_W - 3) : (NULL);
		(PIC_DateBlock.TrackInf_DataBlock.RightLine[Row_buff] <= 2) ? \
			(PIC_DateBlock.TrackInf_DataBlock.RightLine[Row_buff] = 2) : (NULL);
	}
	else
	{
		RightFlag_Switch.RightWhiteLost = 0;
		RightFlag_Switch.RightBlackLost = 0;
		RightFlag_Switch.RightLost = 0;
	}
	if(LeftFlag_Switch.LeftLost == 0 && RightFlag_Switch.RightLost == 0)
	{
		PIC_DateBlock.TrackInf_DataBlock.TrackWidth = PIC_DateBlock.TrackInf_DataBlock.RightLine[Row_buff]     \
		                                              - PIC_DateBlock.TrackInf_DataBlock.LeftLine[Row_buff];
	}
	PIC_DateBlock.TrackInf_DataBlock.MidLine[Row_buff] = (PIC_DateBlock.TrackInf_DataBlock.RightLine[Row_buff]     \
		                                                 + PIC_DateBlock.TrackInf_DataBlock.LeftLine[Row_buff]) / 2;
	(PIC_DateBlock.TrackInf_DataBlock.MidLine[Row_buff] >= 155) ? 	\
		(PIC_DateBlock.TrackInf_DataBlock.MidLine[Row_buff] = 155) : (NULL);
	(PIC_DateBlock.TrackInf_DataBlock.MidLine[Row_buff] <= 4) ?
		(PIC_DateBlock.TrackInf_DataBlock.MidLine[Row_buff] = 4) : (NULL);
	/*           åå­—èµ›é“æ£€æµ‹         */
	Cross_Check(Row_buff) ;

	/*           å¤§è½¬å¼¯å¼¯é“æ£€æµ‹       */
	if(LeftFlag_Switch.LeftLost == 0 && RightFlag_Switch.RightWhiteLost == 1)
	{
		(++RightFlag_Switch.RightTurn >= 10)  ? 	\
			(RightFlag_Switch.RightTurnFlag = 1) :	\
			(LeftFlag_Switch.LeftTurn = 0 , LeftFlag_Switch.LeftTurnFlag = 0);
	}
	else if(LeftFlag_Switch.LeftWhiteLost == 1 && RightFlag_Switch.RightLost == 0)
	{
		(++LeftFlag_Switch.LeftTurn >= 10) ?		\
			(LeftFlag_Switch.LeftTurnFlag = 1) :	\
			(RightFlag_Switch.RightTurn = 0 , RightFlag_Switch.RightTurnFlag = 0);
	}
}

void Get_MidAve(uint8 *MidLine_Buff,float32 Coe_1,float32 Coe_2,float32 Coe_3,float32 Coe_4)
{
	uint8 i;
	float32 sum1,sum2,sum3,sum4;
	for (i = 0; i < 10; i++)
	{
		sum1 += *(MidLine_Buff + i);
	}
	for (; i < 20; i++)
	{
		sum2 += *(MidLine_Buff + i);
	}
	for(; i < 30; i++)
	{
		sum3 += *(MidLine_Buff + i);
	}
	for(; i < 40; i++)
	{
		sum4 += *(MidLine_Buff + i);
	}
	sum1 *= Coe_1 , sum2 *= Coe_2 , sum3 *= Coe_3 , sum4 *= Coe_4;
	MidAve = (int16) (sum1 + sum2 + sum3 + sum4);

}

void Get_Img(void)
{
    ov7725_eagle_img_flag = IMG_START;                   //
	PORTA->ISFR = ~0;
    enable_irq((IRQn_Type)(PORTA_IRQn));
    while (ov7725_eagle_img_flag != IMG_FINISH)
    {
        if (ov7725_eagle_img_flag == IMG_FAIL)            //
        {
            ov7725_eagle_img_flag = IMG_START;           //
            PORTA->ISFR = 0xFFFFFFFFu;                //
            enable_irq(PORTA_IRQn);                 //
        }
    }
	Get_MidLine();
	Mode_Change(steerCtrler);
	clearflag();
	
	Steer_Controller(steerCtrler, steerMidValue, MidAve);
	OLED_ShowString(0,0,"MidAve");
	OLED_ShowNum(70,0,MidAve,3);
}

void Cross_Check(int8 Row_buff)
{
	if(39 == Row_buff) return;
	else
	{
		//左边界初始条件检查
		if(~(LeftFlag_Switch.Left_1Con))
		{
			if (PIC_DateBlock.TrackInf_DataBlock.LeftLine[Row_buff] >=
				PIC_DateBlock.TrackInf_DataBlock.LeftLine[Row_buff + 1])
			{
				/* code */
				LeftFlag_Switch.LeftIncrease = 1;
			}
			else
			{
				if(LeftFlag_Switch.LeftIncrease)
				{
					LeftFlag_Switch.Left_1Con = 1;
					/*   code   */
					CrossInf_Data.LeftCrossStart_H = (uint8) (Row_buff);
					CrossInf_Data.LeftCrossStart_L = (uint8) (PIC_DateBlock.TrackInf_DataBlock.LeftLine[Row_buff]);
				}
				else
				{
					LeftFlag_Switch.LeftIncrease = 0;
					LeftFlag_Switch.Left_1Con = 0;
					LeftFlag_Switch.LeftCrossFlag = 0;
				}
			}
		}
		//右边界初始条件检查
		if(~(RightFlag_Switch.Right_1Con))
		{
			if(PIC_DateBlock.TrackInf_DataBlock.RightLine[Row_buff] <=
			   PIC_DateBlock.TrackInf_DataBlock.RightLine[Row_buff + 1])
			{
				RightFlag_Switch.Rightreduce = 1;
			}
			else
			{
				if(RightFlag_Switch.Rightreduce)
				{
					RightFlag_Switch.Right_1Con = 1;
					/*     code    */
					CrossInf_Data.RightCrossStart_H = (uint8) (Row_buff);
					CrossInf_Data.RightCrossStart_L = (uint8) (PIC_DateBlock.TrackInf_DataBlock.RightLine[Row_buff]);
				}
				else
				{
					RightFlag_Switch.Rightreduce = 0;
					RightFlag_Switch.Right_1Con = 0;
					RightFlag_Switch.RightCrossFlag = 0;
				}
			}
		}
		//左边界十字单查
		if(LeftFlag_Switch.Left_1Con)
		{
			if(LeftFlag_Switch.LeftWhiteLost)
			{
				if((CrossInf_Data.LeftCrossStart_H) - Row_buff < 10 &&
					(CrossInf_Data.LeftCrossStart_H) - Row_buff > 0)
				{
					LeftFlag_Switch.LeftCrossFlag = 1;
				}
				else
				{
					LeftFlag_Switch.LeftIncrease = 0;
					LeftFlag_Switch.Left_1Con = 0;
				}
			}
		}
		//右边界十字单查
		if(RightFlag_Switch.Right_1Con)
		{
			if(RightFlag_Switch.RightWhiteLost)
			{
				if((CrossInf_Data.RightCrossStart_H) - Row_buff < 10 &&
					(CrossInf_Data.RightCrossStart_H) - Row_buff > 0)
				{
					RightFlag_Switch.RightCrossFlag = 1;
				}
				else
				{
					RightFlag_Switch.Rightreduce = 0;
					RightFlag_Switch.Right_1Con = 0;
				}
			}
		}
		//弯道入十字
		if(LeftFlag_Switch.Left_1Con && ~(RightFlag_Switch.RightCrossFlag))
		{
			if(RightFlag_Switch.RightWhiteLost)
			{
				RightFlag_Switch.RightCrossFlag = 1;
				LeftFlag_Switch.LeftCrossFlag = 1;

				CrossInf_Data.RightCrossStart_H = CrossInf_Data.LeftCrossStart_H;
				CrossInf_Data.RightCrossStart_L = PICTURE_W - 3;
			}
		}
		if(RightFlag_Switch.Right_1Con && ~(LeftFlag_Switch.LeftCrossFlag))
		{
			if(LeftFlag_Switch.LeftWhiteLost)
			{
				LeftFlag_Switch.LeftCrossFlag = 1;
				RightFlag_Switch.RightCrossFlag = 1;

				CrossInf_Data.LeftCrossStart_H = CrossInf_Data.RightCrossStart_H;
				CrossInf_Data.LeftCrossStart_L = 2;
			}
		}
		if(~(LeftFlag_Switch.LeftCrossFlag) && ~(RightFlag_Switch.RightCrossFlag))
		{
			if(LeftFlag_Switch.LeftWhiteLost && RightFlag_Switch.RightWhiteLost)
			{
				++CrossInf_Data.SpeCross;
			}
			if(CrossInf_Data.SpeCross >= 20)
			{
				LeftFlag_Switch.LeftCrossFlag = 1;
				RightFlag_Switch.RightCrossFlag = 1;

				CrossInf_Data.LeftCrossStart_H = (uint8) (Row_buff);
				CrossInf_Data.LeftCrossStart_L = 2;

				CrossInf_Data.RightCrossStart_H = (uint8) (Row_buff);
				CrossInf_Data.RightCrossStart_L = PICTURE_W - 3;
				CrossInf_Data.SpeCross = 0;
			}
		}
	}
}

void CrossDeal(void)
{
	int16 i;
	/*                  */
	if(White == PIC_DateBlock.pic[1] &&
	   White == PIC_DateBlock.pic[2])
	{
		CrossInf_Data.LeftCrossEnd_H = 0;
		CrossInf_Data.LeftCrossEnd_L = 2;
	}
	else
	{
		for(i = 4;i < PICTURE_W - 1;i++)
		{
			if(White == PIC_DateBlock.pic[i] &&
		   	   White == PIC_DateBlock.pic[i - 1] &&
		   	   Black == PIC_DateBlock.pic[i - 2] &&
		   	   Black == PIC_DateBlock.pic[i - 3])
			{
				CrossInf_Data.LeftCrossEnd_H = 0;
				CrossInf_Data.LeftCrossEnd_L = i - 1;
				break;
			}
		}
		if(i == PICTURE_W - 1)
		{
			CrossInf_Data.LeftCrossEnd_H = 0;
			CrossInf_Data.LeftCrossEnd_L = 80;
		}
	}
	/*                    */
	if(White == PIC_DateBlock.pic[PICTURE_W - 2] &&
	   White == PIC_DateBlock.pic[PICTURE_W - 3])
	{
		CrossInf_Data.RightCrossEnd_H = 0;
		CrossInf_Data.RightCrossEnd_L = PICTURE_W - 3;
	}
	else
	{
		for(i = PICTURE_W - 5;i > 0;i--)
		{
			if(White == PIC_DateBlock.pic[i] &&
			   White == PIC_DateBlock.pic[i + 1] &&
			   Black == PIC_DateBlock.pic[i + 2] &&
			   Black == PIC_DateBlock.pic[i + 3])
			{
				CrossInf_Data.RightCrossEnd_H = 0;
				CrossInf_Data.RightCrossEnd_L = PICTURE_W - 3;
				break;
			}
		}
		if(i == 1)
		{
			CrossInf_Data.RightCrossEnd_H = 0;
			CrossInf_Data.RightCrossEnd_L = 80;
		}
	}
	if(CrossInf_Data.RightCrossEnd_L < CrossInf_Data.LeftCrossEnd_L)
	{
		CrossInf_Data.LeftCrossEnd_L = 90;

		CrossInf_Data.RightCrossEnd_L = 90;
	}
	/*              */
	LinerFitting(PIC_DateBlock.TrackInf_DataBlock.LeftLine,\
				 CrossInf_Data.LeftCrossStart_H , \
				 0 , \
				 CrossInf_Data.LeftCrossEnd_L);
	LinerFitting(PIC_DateBlock.TrackInf_DataBlock.RightLine, \
				 CrossInf_Data.RightCrossStart_H , \
				 0 , \
				 CrossInf_Data.RightCrossEnd_L);
	(CrossInf_Data.LeftCrossStart_H >= CrossInf_Data.RightCrossStart_H) ?
		(i = CrossInf_Data.LeftCrossStart_H) : (i = CrossInf_Data.RightCrossStart_H);
	for(;i >= 0; i--)
	{
		PIC_DateBlock.TrackInf_DataBlock.MidLine[i] = (PIC_DateBlock.TrackInf_DataBlock.RightLine[i]
													+ PIC_DateBlock.TrackInf_DataBlock.LeftLine[i]) / 2;
	}
}
void BlackDeal(int8 Row_Buff)
{
    if(Row_Buff < 0) return;
	for(;Row_Buff >= 0;Row_Buff--)
	{
		if(LeftFlag_Switch.LeftTurnFlag)
		{
			PIC_DateBlock.TrackInf_DataBlock.LeftLine[Row_Buff] = 1;
			PIC_DateBlock.TrackInf_DataBlock.RightLine[Row_Buff] = 1;
			PIC_DateBlock.TrackInf_DataBlock.MidLine[Row_Buff] = 1;
		}
		else if(RightFlag_Switch.RightTurnFlag)
		{
			PIC_DateBlock.TrackInf_DataBlock.LeftLine[Row_Buff] = PICTURE_W - 2;
			PIC_DateBlock.TrackInf_DataBlock.RightLine[Row_Buff] = PICTURE_W - 2;
			PIC_DateBlock.TrackInf_DataBlock.MidLine[Row_Buff] = PICTURE_W - 2;
		}
	}
	LeftFlag_Switch.LeftTurn = 0;
	LeftFlag_Switch.LeftTurnFlag = 0;
	RightFlag_Switch.RightTurn = 0;
	RightFlag_Switch.RightTurnFlag = 0;
}
/*                 */
void LinerFitting(int16 *Tar,uint8 Start_H,uint8 End_H,uint8 End_L)
{
   int16 Sub_L,Sub_H;
   int16 Quotinet,Reminder;//
   int16 i;
   Sub_L = End_L - *(Tar + Start_H);   //
   Sub_H = Start_H - End_H;		   //
   if(Sub_H == 0)
   {
     *(Tar + End_H) = End_L;
	 return;
   }
   if(Sub_L >= 0)
   {
     Quotinet = Sub_L / Sub_H;
	 Reminder = Sub_L % Sub_H;
	 for(i = Start_H; i < End_H + Reminder - 1;i--)
	 	*(Tar + i) = *(Tar + i + 1) + Quotinet;
	 for(i = End_H + Reminder - 1;i > End_H;i--)
	 	*(Tar + i) = *(Tar + i + 1) + Quotinet + 1;
	 *(Tar + End_H) = End_L;
   }
   if(Sub_L < 0)
   {
     Quotinet = Sub_L / Sub_H;
	 Reminder = Sub_L % Sub_H;
	 for(i = Start_H; i < End_H - Reminder - 1; i--)
		*(Tar + i) = *(Tar + i + 1) + Quotinet;
	 for(i = End_H - Reminder - 1;i > End_H; i--)
		*(Tar + i) = *(Tar + i + 1) + Quotinet - 1;
	 *(Tar + End_H) = End_L;
   }
}
void clearflag(void)
{
	LeftFlag_Switch.LeftBlackLost = 0;
	LeftFlag_Switch.LeftCrossFlag = 0;
	LeftFlag_Switch.LeftIncrease = 0;
	LeftFlag_Switch.LeftLost = 0;
	LeftFlag_Switch.Leftreduce = 0;
	LeftFlag_Switch.LeftTurn = 0;
	LeftFlag_Switch.LeftTurnFlag = 0;
	LeftFlag_Switch.LeftWhiteLost = 0;
	LeftFlag_Switch.Left_1Con = 0;

	CrossInf_Data.LeftCrossEnd_H = 0;
	CrossInf_Data.LeftCrossEnd_L = 0;
	CrossInf_Data.LeftCrossStart_H = 0;
	CrossInf_Data.LeftCrossStart_L = 0;
	CrossInf_Data.RightCrossEnd_H = 0;
	CrossInf_Data.RightCrossEnd_L = 0;
	CrossInf_Data.RightCrossStart_H = 0;
	CrossInf_Data.RightCrossStart_L = 0;
	CrossInf_Data.SpeCross = 0;

	RightFlag_Switch.RightBlackLost = 0;
	RightFlag_Switch.RightCrossFlag = 0;
	RightFlag_Switch.RightIncrease = 0;
	RightFlag_Switch.RightLost = 0;
	RightFlag_Switch.Rightreduce = 0;
	RightFlag_Switch.RightTurn = 0;
	RightFlag_Switch.RightTurnFlag = 0;
	RightFlag_Switch.RightWhiteLost = 0;
	RightFlag_Switch.Right_1Con = 0;
}

float32 Calc_Curv(uint8 *MidLine_Buff, uint8 index)
{
	float32 det, result, mod;
	int16 matrix[2][3];

	matrix[0][0] = 3 * (index - 1) + 1;
	matrix[1][0] = MidLine_Buff[index - 1];

	matrix[0][1] = 3 * (index) + 1;
	matrix[1][1] = MidLine_Buff[index];

	matrix[0][2] = 3 * (index + 1) + 1;
	matrix[1][2] = MidLine_Buff[index + 1];

	det = (matrix[0][2] - matrix[0][1]) * (matrix[1][0] - matrix[1][1])
		 - (matrix[0][0] - matrix[0][1]) * (matrix[1][2] - matrix[1][1]); // det

	mod = Carmark_InvSqrt(
				(pow((matrix[0][0] - matrix[0][1]), 2) + pow((matrix[1][0] - matrix[1][1]), 2)) 
				* (pow((matrix[0][0] - matrix[0][2]), 2) + pow((matrix[1][0] - matrix[1][2]), 2))
				* (pow((matrix[0][1] - matrix[0][2]), 2) + pow((matrix[1][1] - matrix[1][2]), 2))
				);

	if (fabs(mod - 0) < 1e-4)
	{
		mod = 1e-4;
	}

	result = (2 * det) * mod;

	return result;
}

float32 Carmark_InvSqrt(float32 x)
{
	float xhalf = 0.5f * x;
	int i = *(int *) & x;
	i = 0x5f3759df - (i >> 1); // 计算第一个近似根
	x = *(float *) &i;
	x = x * (1.5f - xhalf * x * x); // 牛顿迭代法
	return x;

}

float32 InvSlope_Calc(uint8 *MidLine_Buff, uint8 y1, uint8 y2)
{
	float32 invSlope;

	invSlope = (MidLine_Buff[y1] - MidLine_Buff[y2]) / (3 * (y1 - y2));

	return invSlope;
}

int8 Is_Straight(uint8 *MidLine_Buff, uint8 y)
{
	int8 isStraight = 1;
	int16 midErrInvSlp;

	midErrInvSlp = (MidLine_Buff[y - 5] - steerMidValue) - 2 * (MidLine_Buff[y] - steerMidValue) + (MidLine_Buff[y + 5] - steerMidValue);

	if(fabs(midErrInvSlp) < 3 && !(LeftFlag_Switch.LeftLost) && !(RightFlag_Switch.RightLost))
	{
		OLED_ClearLine(5);
		OLED_ShowString(0, 5, "Straight");
		isStraight = 1;
	}
	else
	{
		OLED_ClearLine(5);
		OLED_ShowString(0, 5, "Curv");
		isStraight = 0;
	}
	OLED_ShowNum(70, 5, (int32)midErrInvSlp, 5);

	return isStraight;
}

void Mode_Change(PIDStruct *steerCtrler)
{
	//float32 speedTemp;
	if (Is_Straight(PIC_DateBlock.TrackInf_DataBlock.MidLine, 11))
	{
		steerCtrler -> para = steerCtrlerStPara;
		differCtrler -> para = differCtrlerStPara;
		if (fabs(steerCtrler -> error[0]) <= 10)
		{
			PWM_Expect = PWM_Expect_Base + 1000;
		}
	}
	else
	{
		PWM_Expect = PWM_Expect_Base - 900;
		// speedTemp = (Encoder_GetPulseNum(ENCODER_LEFT) + Encoder_GetPulseNum(ENCODER_LEFT)) / 2.0;
		// if(fabs(PulseNum_To_PWM(speedTemp) - PWM_Expect) < 100)
		// {
		// 	steerCtrler -> para = steerCtrlerCurvPara;
		// 	differCtrler -> para = differCtrlerCurvPara;
		// }
		steerCtrler -> para = steerCtrlerCurvPara;
		differCtrler -> para = differCtrlerCurvPara;
	}
}