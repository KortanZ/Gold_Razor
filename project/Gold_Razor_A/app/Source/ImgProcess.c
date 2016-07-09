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

int16 MidAve = 0;
uint8 brokeDownFlag = 0;
uint8 Strightcount,Fakestrightcount,Curvecount;
float32 weight[4] = {0.020, 0.045, 0.030, 0.005};

void Get_MidLine(void)
{
	uint8 i,j,k;
	int8 Row;
	img_extract(img,imgbuff,CAMERA_SIZE);
	for(k = 0,i = 1; i < CAMERA_H; i += 3 , k++)
	{
		for(j = 0; j < CAMERA_W; j++)
		{
			PIC_DateBlock.pic[CAMERA_W * k + j] = img[i * CAMERA_W + j];
		}
	}

	for(Row = Bef_Scan(PIC_DateBlock.pic);Row >= 0;Row--)
	{
		TwinLine_Deal(PIC_DateBlock.pic,Row);


		if(LeftFlag_Switch.LeftTurnFlag || RightFlag_Switch.RightTurnFlag)
		{
			if(LeftFlag_Switch.LeftBlackLost && RightFlag_Switch.RightBlackLost)
				break;
		}
	}

	if(Row < 0)
	{
		if(LeftFlag_Switch.LeftCrossFlag && RightFlag_Switch.RightCrossFlag)
		{
			CrossDeal();
			LPLD_GPIO_Output_b(PTA,17,0);
		}
		else
			LPLD_GPIO_Output_b(PTA,17,1);
	}
	else
	{
		BlackDeal(Row);
		LPLD_GPIO_Output_b(PTA,17,1);
	}
	//BlackDeal(Row);
	Get_MidAve(PIC_DateBlock.MidLine  \
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
		   White == *(pic_buff + Row * PICTURE_W + 2))
		{
			PIC_DateBlock.LeftLine[Row] = 2;
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
					PIC_DateBlock.LeftLine[Row] = i - 1;
					break;
				}
			}
			if(i == PICTURE_W - 1)
			{
				PIC_DateBlock.LeftLine[Row] = 1;
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
			White == *(pic_buff + Row * PICTURE_W + PICTURE_W - 3))
		{
			PIC_DateBlock.RightLine[Row] = PICTURE_W - 3;
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
					PIC_DateBlock.RightLine[Row] = i + 1;
					RightFlag_Switch.RightLost = 0;
					break;
				}
			}
			if(i == 0)
			{
				PIC_DateBlock.RightLine[Row] = PICTURE_W - 3;
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
   		//如果扫描错误
		if(PIC_DateBlock.RightLine[Row] < PIC_DateBlock.LeftLine[Row])
		{
			PIC_DateBlock.LeftLine[Row] = 2;
			PIC_DateBlock.RightLine[Row] = 157;
		}
		//计算赛道宽度
		PIC_DateBlock.TrackWidth[Row] = PIC_DateBlock.RightLine[Row]     \
		                                              - PIC_DateBlock.LeftLine[Row];
		PIC_DateBlock.MidLine[Row] = (PIC_DateBlock.RightLine[Row]     \
		                                                 + PIC_DateBlock.LeftLine[Row]) >> 1;
		(PIC_DateBlock.MidLine[Row] >= 155) ? 	\
			(PIC_DateBlock.MidLine[Row] = 155) : (NULL);
		(PIC_DateBlock.MidLine[Row] <= 4) ?
			(PIC_DateBlock.MidLine[Row] = 4) : (NULL);
		(LeftFlag_Switch.LeftBlackLost == 1 && RightFlag_Switch.RightBlackLost== 1) ?    \
			(Black_Check++) : (NULL);
	}
	//Cross_StartCheck(Row) ;

	/*              冲出赛道检测        */
	if(Black_Check > 2)
	{
	   brokeDownFlag = 1;
	   OLED_ShowString(0, 5, "Car break down!");
	   while (brokeDownFlag);
	}
	return Row;
}

void TwinLine_Deal(uint8 *pic_buff,int8 Row_buff)
{
	uint8 i;
	//向左扫描
	for(i = PIC_DateBlock.MidLine[Row_buff + 1];i > 0;i--)
	{
		if(Black == *(pic_buff + Row_buff * PICTURE_W + i) &&		\
			Black == *(pic_buff + Row_buff * PICTURE_W + i + 1) &&	\
			White == *(pic_buff + Row_buff * PICTURE_W + i + 2) &&	\
			White == *(pic_buff + Row_buff * PICTURE_W + i + 3))
		{
			PIC_DateBlock.LeftLine[Row_buff] = i + 1;
			break;
		}
	}
	if(i == 0)
	{
		if(White == *(pic_buff + Row_buff * PICTURE_W + 2) &&   \
		   White == *(pic_buff + Row_buff * PICTURE_W + 3))
		{
			LeftFlag_Switch.LastLeftWhiteLost = LeftFlag_Switch.LeftWhiteLost;
			LeftFlag_Switch.LeftWhiteLost = 1;
			LeftFlag_Switch.LeftBlackLost = 0;
			LeftFlag_Switch.LeftLost = 1;
		}
		else
		{
			LeftFlag_Switch.LastLeftWhiteLost = LeftFlag_Switch.LeftWhiteLost;
			LeftFlag_Switch.LeftWhiteLost = 0;
			LeftFlag_Switch.LeftBlackLost = 1;
			LeftFlag_Switch.LeftLost = 1;
		}
		// PIC_DateBlock.LeftLine[Row_buff] = PIC_DateBlock.LeftLine[Row_buff + 1] \
		// 									+ PIC_DateBlock.LeftLine[Row_buff + 2] \
		// 									- PIC_DateBlock.LeftLine[Row_buff + 3];
		PIC_DateBlock.LeftLine[Row_buff] = 2;
	}
	else
	{
		LeftFlag_Switch.LastLeftWhiteLost = LeftFlag_Switch.LeftWhiteLost;
		LeftFlag_Switch.LeftWhiteLost = 0;
		LeftFlag_Switch.LeftBlackLost = 0;
		LeftFlag_Switch.LeftLost = 0;
	}
	if (fabs(PIC_DateBlock.LeftLine[Row_buff] - PIC_DateBlock.LeftLine[Row_buff + 1]) > 100)
	{
		PIC_DateBlock.LeftLine[Row_buff] = PIC_DateBlock.LeftLine[Row_buff + 1] \
										+ PIC_DateBlock.LeftLine[Row_buff + 2] \
										- PIC_DateBlock.LeftLine[Row_buff + 3];
	}

	(PIC_DateBlock.LeftLine[Row_buff] < 2) ?  \
		(PIC_DateBlock.LeftLine[Row_buff] = 2) : (NULL);
	(PIC_DateBlock.LeftLine[Row_buff] > PICTURE_W - 3) ?
		(PIC_DateBlock.LeftLine[Row_buff] = PICTURE_W - 3) : (NULL);	
	//向右扫描
	for(i = PIC_DateBlock.MidLine[Row_buff + 1];i < PICTURE_W - 1;i++)
	{
		if(Black == *(pic_buff + Row_buff * PICTURE_W + i) &&
			Black == *(pic_buff + Row_buff * PICTURE_W + i - 1) &&
			White == *(pic_buff + Row_buff * PICTURE_W + i - 2) &&
			White == *(pic_buff + Row_buff * PICTURE_W + i - 3))
		{
			PIC_DateBlock.RightLine[Row_buff] = i - 1;
			break;
		}
	}
	if(i == PICTURE_W - 1)
	{
		if(White == *(pic_buff + Row_buff * PICTURE_W + PICTURE_W - 3) &&   \
			White == *(pic_buff + Row_buff * PICTURE_W + PICTURE_W - 4)  )
		{
			RightFlag_Switch.LastRightWhiteLost = RightFlag_Switch.RightWhiteLost;
			RightFlag_Switch.RightWhiteLost = 1;
			RightFlag_Switch.RightBlackLost = 0;
			RightFlag_Switch.RightLost = 1;
		}
		else
		{
			RightFlag_Switch.LastRightWhiteLost = RightFlag_Switch.RightWhiteLost;
			RightFlag_Switch.RightWhiteLost = 0;
			RightFlag_Switch.RightBlackLost = 1;
			RightFlag_Switch.RightLost = 1;
		}
		PIC_DateBlock.RightLine[Row_buff] = PICTURE_W - 3;
	}
	else
	{
		RightFlag_Switch.LastRightWhiteLost = RightFlag_Switch.RightWhiteLost;
		RightFlag_Switch.RightWhiteLost = 0;
		RightFlag_Switch.RightBlackLost = 0;
		RightFlag_Switch.RightLost = 0;
	}
	if (fabs(PIC_DateBlock.RightLine[Row_buff] - PIC_DateBlock.RightLine[Row_buff + 1]) > 100)
	{
		PIC_DateBlock.RightLine[Row_buff] = PIC_DateBlock.RightLine[Row_buff + 1] \
										+ PIC_DateBlock.RightLine[Row_buff + 2] \
										- PIC_DateBlock.RightLine[Row_buff + 3];
	}

	(PIC_DateBlock.RightLine[Row_buff] > PICTURE_W - 3) ? \
		(PIC_DateBlock.RightLine[Row_buff] = PICTURE_W - 3) : (NULL);
	(PIC_DateBlock.RightLine[Row_buff] < 2) ? \
		(PIC_DateBlock.RightLine[Row_buff] = 2) : (NULL);
	
	//如果扫描错误
	if(PIC_DateBlock.RightLine[Row_buff] < PIC_DateBlock.LeftLine[Row_buff])
	{
		PIC_DateBlock.LeftLine[Row_buff] = PIC_DateBlock.LeftLine[Row_buff + 1] \
											+ PIC_DateBlock.LeftLine[Row_buff + 2] \
											- PIC_DateBlock.LeftLine[Row_buff + 3];
		PIC_DateBlock.RightLine[Row_buff] = PIC_DateBlock.RightLine[Row_buff + 1] \
											+ PIC_DateBlock.RightLine[Row_buff + 2] \
											- PIC_DateBlock.RightLine[Row_buff + 3];
		(PIC_DateBlock.LeftLine[Row_buff] < 2) ?  \
			(PIC_DateBlock.LeftLine[Row_buff] = 2) : (NULL);
		(PIC_DateBlock.LeftLine[Row_buff] > PICTURE_W - 3) ?
			(PIC_DateBlock.LeftLine[Row_buff] = PICTURE_W - 3) : (NULL);
		(PIC_DateBlock.RightLine[Row_buff] > PICTURE_W - 3) ? \
			(PIC_DateBlock.RightLine[Row_buff] = PICTURE_W - 3) : (NULL);
		(PIC_DateBlock.RightLine[Row_buff] < 2) ? \
			(PIC_DateBlock.RightLine[Row_buff] = 2) : (NULL);
		if(PIC_DateBlock.RightLine[Row_buff] < PIC_DateBlock.LeftLine[Row_buff])
		{
			PIC_DateBlock.RightLine[Row_buff] = PIC_DateBlock.RightLine[Row_buff + 1];
			PIC_DateBlock.LeftLine[Row_buff] = PIC_DateBlock.LeftLine[Row_buff + 1];
		}
	}
	PIC_DateBlock.TrackWidth[Row_buff] = PIC_DateBlock.RightLine[Row_buff]     \
	                         			- PIC_DateBlock.LeftLine[Row_buff];

	PIC_DateBlock.MidLine[Row_buff] = ((PIC_DateBlock.RightLine[Row_buff]     \
		                            + PIC_DateBlock.LeftLine[Row_buff]) >> 1);
	(PIC_DateBlock.MidLine[Row_buff] >= 155) ? 	\
		(PIC_DateBlock.MidLine[Row_buff] = 155) : (NULL);
	(PIC_DateBlock.MidLine[Row_buff] <= 4) ?    \
		(PIC_DateBlock.MidLine[Row_buff] = 4) : (NULL);
		
	/*           转弯检测       */
	if(!LeftFlag_Switch.LeftLost && RightFlag_Switch.RightWhiteLost)//右转弯
	{
		if(RightFlag_Switch.LastRightWhiteLost)  //是否上一行也是白丢线
			(++RightFlag_Switch.RightTurn >= 5)  ? 	\
				(RightFlag_Switch.RightTurnFlag = 1) :	\
				(LeftFlag_Switch.LeftTurn = 0 , LeftFlag_Switch.LeftTurnFlag = 0);
		else
			RightFlag_Switch.RightTurn = 0;
	}
	else if(LeftFlag_Switch.LeftWhiteLost && !RightFlag_Switch.RightLost)//左转弯
	{
		if (LeftFlag_Switch.LastLeftWhiteLost)//是否上一行也是白丢线
			(++LeftFlag_Switch.LeftTurn >= 5) ?		\
				(LeftFlag_Switch.LeftTurnFlag = 1) :	\
				(RightFlag_Switch.RightTurn = 0 , RightFlag_Switch.RightTurnFlag = 0);
		else
			LeftFlag_Switch.LeftTurn = 0;
	}
	/*          十字检测         */
	if(Row_buff > 2)
		Cross_StartCheck(Row_buff);
}

void Get_MidAve(int16 *MidLine_Buff,float32 Coe_1,float32 Coe_2,float32 Coe_3,float32 Coe_4)
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
	MidAve  = (int16) (sum1 + sum2 + sum3 + sum4);
}

void Get_Img_Start(void)
{
	ov7725_eagle_img_flag = IMG_START;
	PORTA->ISFR = ~0;
	enable_irq((IRQn_Type)(PORTA_IRQn));
}

void Get_Img_Wait(void)
{
	while (ov7725_eagle_img_flag != IMG_FINISH)
	{
		if (ov7725_eagle_img_flag == IMG_FAIL)
		{
			ov7725_eagle_img_flag = IMG_START;
			PORTA->ISFR = 0xFFFFFFFFu;
			enable_irq(PORTA_IRQn);
		}
	}
}

void Cross_StartCheck(int8 Row_buff)
{
	if(39 == Row_buff) 
		return;
	else
	{
		float32 leftdown = 0.0,rightdown = 0.0;
		float32 leftup = 0.0,rightup = 0.0;
		//左边界初始条件检查
		if(!LeftFlag_Switch.LeftCrossFlag)
		{
			if (!LeftFlag_Switch.LeftBlackLost)
			{
				if (PIC_DateBlock.LeftLine[Row_buff] >
					PIC_DateBlock.LeftLine[Row_buff + 1])
				{
					LeftFlag_Switch.LeftIncrease = 1;
				}
				else if (PIC_DateBlock.LeftLine[Row_buff] <=
						PIC_DateBlock.LeftLine[Row_buff + 1])
				{
					if(LeftFlag_Switch.LeftIncrease)
					{
						CrossInf_Data.LeftCrossStart_H = (uint8) (Row_buff + 1);
						CrossInf_Data.LeftCrossStart_L = (uint8) (PIC_DateBlock.LeftLine[Row_buff + 1]);
						if (CrossInf_Data.LeftCrossStart_H <= 4 || \
							CrossInf_Data.LeftCrossStart_H >= 35)
							LeftFlag_Switch.Left_1Con = 0;
						leftdown = (PIC_DateBlock.LeftLine[CrossInf_Data.LeftCrossStart_H + 1] - \
									  2 * PIC_DateBlock.LeftLine[CrossInf_Data.LeftCrossStart_H + 2] + \
									  PIC_DateBlock.LeftLine[CrossInf_Data.LeftCrossStart_H + 3]) / 3.0;
						leftdown = fabs(leftdown);
						if (leftdown >= 0.34)
						{
							LeftFlag_Switch.Left_1Con = 0;
						}
						else
							LeftFlag_Switch.Left_1Con = 1;
					}
					LeftFlag_Switch.LeftIncrease = 0;
				}
				else
					LeftFlag_Switch.LeftIncrease = 0;
			}
		}
		//右边界初始条件检查
		if(!RightFlag_Switch.RightCrossFlag)
		{
			if (!RightFlag_Switch.RightBlackLost)
			{
				if(PIC_DateBlock.RightLine[Row_buff] <
				   PIC_DateBlock.RightLine[Row_buff + 1])
				{
					RightFlag_Switch.Rightreduce = 1;
				}
				else if(PIC_DateBlock.RightLine[Row_buff] >=
						PIC_DateBlock.RightLine[Row_buff + 1])
				{
					if(RightFlag_Switch.Rightreduce)
					{
						CrossInf_Data.RightCrossStart_H = (uint8) (Row_buff + 1);
						CrossInf_Data.RightCrossStart_L = (uint8) (PIC_DateBlock.RightLine[Row_buff + 1]);
						if (CrossInf_Data.RightCrossStart_H <= 4 || \
							CrossInf_Data.RightCrossStart_H >= 35)
							RightFlag_Switch.Right_1Con = 0;
						rightdown = (2 * PIC_DateBlock.RightLine[CrossInf_Data.RightCrossStart_H + 2] - \
									  PIC_DateBlock.RightLine[CrossInf_Data.RightCrossStart_H + 1] - \
									  PIC_DateBlock.RightLine[CrossInf_Data.RightCrossStart_H + 3]) / 3.0;
						rightdown = fabs(rightdown);
						if (rightdown >= 0.34)
						{
							RightFlag_Switch.Right_1Con = 0;
						}
						else
							RightFlag_Switch.Right_1Con = 1;
					}
					RightFlag_Switch.Rightreduce = 0;
				}
				else
					RightFlag_Switch.Rightreduce = 0;
			}
		}
		//左边界十字单查
		if(LeftFlag_Switch.Left_1Con && !LeftFlag_Switch.LeftCrossFlag)
		{
			if (!LeftFlag_Switch.LeftBlackLost)
			{
				if (CrossInf_Data.LeftCrossStart_H - Row_buff <= 5 && \
					CrossInf_Data.LeftCrossStart_H - Row_buff >= 0)
				{
					if(LeftFlag_Switch.LeftWhiteLost)
						LeftFlag_Switch.LeftCrossFlag = 1;
				}
				else if (CrossInf_Data.LeftCrossStart_H - Row_buff <= 8 && \
						 CrossInf_Data.LeftCrossStart_H - Row_buff >= 6)
				{	//必须是递减的
					if ((PIC_DateBlock.LeftLine[CrossInf_Data.LeftCrossStart_H - 1] <= \
						  CrossInf_Data.LeftCrossStart_L) && \
						(PIC_DateBlock.LeftLine[CrossInf_Data.LeftCrossStart_H - 2] < \
							PIC_DateBlock.LeftLine[CrossInf_Data.LeftCrossStart_H - 1]) && \
						(PIC_DateBlock.LeftLine[CrossInf_Data.LeftCrossStart_H - 3] < \
							PIC_DateBlock.LeftLine[CrossInf_Data.LeftCrossStart_H - 2]))
					{
						leftup = (PIC_DateBlock.LeftLine[CrossInf_Data.LeftCrossStart_H - 1] - \
									2 * PIC_DateBlock.LeftLine[CrossInf_Data.LeftCrossStart_H - 2] + \
									PIC_DateBlock.LeftLine[CrossInf_Data.LeftCrossStart_H - 3]) / 3.0;
						leftup = fabs(leftup);
						if (leftup <= 0.34)
						{
							LeftFlag_Switch.LeftCrossFlag = 1;
						}
						else
						{
							LeftFlag_Switch.Left_1Con = 0;
							LeftFlag_Switch.LeftIncrease = 0;
							CrossInf_Data.LeftCrossStart_H = 0;
							CrossInf_Data.LeftCrossStart_L = 0;
						}
					}
					else
					{
							LeftFlag_Switch.Left_1Con = 0;
							LeftFlag_Switch.LeftIncrease = 0;
							CrossInf_Data.LeftCrossStart_H = 0;
							CrossInf_Data.LeftCrossStart_L = 0;
					}
				}
			}
			else
			{
				LeftFlag_Switch.Left_1Con = 0;
				LeftFlag_Switch.LeftIncrease = 0;
			}
		}
		//右边界十字单查
		if(RightFlag_Switch.Right_1Con && !RightFlag_Switch.RightCrossFlag)
		{
			if (!RightFlag_Switch.RightBlackLost && \
					(PIC_DateBlock.RightLine[Row_buff] >= CrossInf_Data.RightCrossStart_L))
			{
				if (CrossInf_Data.RightCrossStart_H - Row_buff <= 5 && \
					CrossInf_Data.RightCrossStart_H - Row_buff >= 0)
				{
					if(RightFlag_Switch.RightWhiteLost)
						RightFlag_Switch.RightCrossFlag = 1;
				}
				else if (CrossInf_Data.RightCrossStart_H - Row_buff <= 8 && \
						 CrossInf_Data.RightCrossStart_H - Row_buff >= 6)
				{
					if ((PIC_DateBlock.RightLine[CrossInf_Data.RightCrossStart_H - 1] >= \
						  	CrossInf_Data.RightCrossStart_L ) && \
						(PIC_DateBlock.RightLine[CrossInf_Data.RightCrossStart_H - 2] > \
							PIC_DateBlock.RightLine[CrossInf_Data.RightCrossStart_H - 1]) &&
						(PIC_DateBlock.RightLine[CrossInf_Data.RightCrossStart_H - 3] > \
							PIC_DateBlock.RightLine[CrossInf_Data.RightCrossStart_H - 2]))
					{
						rightup = (2 * PIC_DateBlock.RightLine[CrossInf_Data.RightCrossStart_H - 2] - \
									PIC_DateBlock.RightLine[CrossInf_Data.RightCrossStart_H - 3] - \
									PIC_DateBlock.RightLine[CrossInf_Data.RightCrossStart_H - 1]) / 3.0;
						rightup = fabs(rightup);
						if (rightup <= 0.35)
						{
							RightFlag_Switch.RightCrossFlag = 1;
						}
						else
						{
							RightFlag_Switch.Rightreduce = 0;
							RightFlag_Switch.Right_1Con = 0;
							CrossInf_Data.RightCrossStart_H = 0;
							CrossInf_Data.RightCrossStart_L = 0;
						}
					}
					else
					{
						RightFlag_Switch.Rightreduce = 0;
						RightFlag_Switch.Right_1Con = 0;
						CrossInf_Data.RightCrossStart_H = 0;
						CrossInf_Data.RightCrossStart_L = 0;
					}
				}
			}
			else
			{
				RightFlag_Switch.Rightreduce = 0;
				RightFlag_Switch.Right_1Con = 0;
			}
		}
		//弯道入十字
		if(LeftFlag_Switch.LeftCrossFlag)  //右拐十字
		{
			if(RightFlag_Switch.RightTurn >= 20)   // 左边起始坐标已经好
			{
				LeftFlag_Switch.LeftCrossFlag = 1;
				if(!RightFlag_Switch.RightCrossFlag)
				{
					RightFlag_Switch.RightCrossFlag = 1;
					CrossInf_Data.RightCrossStart_H = CrossInf_Data.LeftCrossStart_H;
					CrossInf_Data.RightCrossStart_L = PICTURE_W - 3;
				}
			}
		}
		if(RightFlag_Switch.RightCrossFlag)  //左拐十字
		{
			if(LeftFlag_Switch.LeftTurn >= 20)
			{
				RightFlag_Switch.RightCrossFlag = 1;
				if(!LeftFlag_Switch.LeftCrossFlag)
				{
					LeftFlag_Switch.LeftCrossFlag = 1;
					CrossInf_Data.LeftCrossStart_H = CrossInf_Data.RightCrossStart_H;
					CrossInf_Data.LeftCrossStart_L = 2;
				}
			}
		}
		if(!(LeftFlag_Switch.LeftCrossFlag) && !(RightFlag_Switch.RightCrossFlag))
		{
			if(LeftFlag_Switch.LeftWhiteLost && RightFlag_Switch.RightWhiteLost)
			{
				if (LeftFlag_Switch.LastLeftWhiteLost && \
					RightFlag_Switch.LastRightWhiteLost)
				{
					++CrossInf_Data.SpeCross;
				}
				else
					CrossInf_Data.SpeCross = 0;
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
	int8 Row;
	if(CrossInf_Data.LeftCrossStart_H >= CrossInf_Data.RightCrossStart_H)//首先找到左边十字
		Row = CrossInf_Data.LeftCrossStart_H;
	else
		Row = CrossInf_Data.RightCrossStart_H;
	for(;Row >= 0;Row--)
	{
		if (PIC_DateBlock.TrackWidth[Row] > PIC_DateBlock.TrackWidth[Row + 1])
			PIC_DateBlock.TrackWidth[Row] = PIC_DateBlock.TrackWidth[Row + 1] - 5;;
		PIC_DateBlock.MidLine[Row] = PIC_DateBlock.MidLine[Row + 1] \
									+ PIC_DateBlock.MidLine[Row + 2] \
									- PIC_DateBlock.MidLine[Row + 3];	PIC_DateBlock.TrackWidth[Row] = PIC_DateBlock.TrackWidth[Row + 1] - 5;
		(PIC_DateBlock.TrackWidth[Row] <= 6) ? 	\
			(PIC_DateBlock.TrackWidth[Row] = 6) : (NULL);
		(PIC_DateBlock.MidLine[Row] >= 155) ? 	\
			(PIC_DateBlock.MidLine[Row] = 155) : (NULL);
		(PIC_DateBlock.MidLine[Row] <= 4) ?
			(PIC_DateBlock.MidLine[Row] = 4) : (NULL);
		PIC_DateBlock.LeftLine[Row] = PIC_DateBlock.MidLine[Row] \
									- (PIC_DateBlock.TrackWidth[Row] >> 1);
		PIC_DateBlock.RightLine[Row] = PIC_DateBlock.MidLine[Row] \
									+ (PIC_DateBlock.TrackWidth[Row] >> 1);
		(PIC_DateBlock.LeftLine[Row] < 2) ?  \
			(PIC_DateBlock.LeftLine[Row] = 2) : (NULL);
		(PIC_DateBlock.LeftLine[Row] > PICTURE_W - 3) ?
			(PIC_DateBlock.LeftLine[Row] = PICTURE_W - 3) : (NULL);
		(PIC_DateBlock.RightLine[Row] > PICTURE_W - 3) ? \
			(PIC_DateBlock.RightLine[Row] = PICTURE_W - 3) : (NULL);
		(PIC_DateBlock.RightLine[Row] < 2) ? \
			(PIC_DateBlock.RightLine[Row] = 2) : (NULL);
		PIC_DateBlock.TrackWidth[Row] = PIC_DateBlock.RightLine[Row]     \
								 - PIC_DateBlock.LeftLine[Row];
		(PIC_DateBlock.TrackWidth[Row] <= 6) ? 	\
			(PIC_DateBlock.TrackWidth[Row] = 6) : (NULL);
	}
}

void BlackDeal(int8 Row_Buff)
{
	if(Row_Buff < 0) 
		return;
	for(;Row_Buff >= 0;Row_Buff--)
	{
		if(LeftFlag_Switch.LeftTurnFlag)
		{
			PIC_DateBlock.LeftLine[Row_Buff] = 1;
			PIC_DateBlock.RightLine[Row_Buff] = 1;
			PIC_DateBlock.MidLine[Row_Buff] = 1;
		}
		else if(RightFlag_Switch.RightTurnFlag)
		{
			PIC_DateBlock.LeftLine[Row_Buff] = PICTURE_W - 2;
			PIC_DateBlock.RightLine[Row_Buff] = PICTURE_W - 2;
			PIC_DateBlock.MidLine[Row_Buff] = PICTURE_W - 2;
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

	Strightcount = 0;
	Fakestrightcount = 0;
	Curvecount = 0;
}

RoadMode Road_Check(int16 *MidLine_Buff, uint8 y)
{
	RoadMode thisMode;
	int16 midErrInvSlp;
	float32 midInvSlp;

	midErrInvSlp = (MidLine_Buff[y - 5] - steerMidValue) - 2 * (MidLine_Buff[y] - steerMidValue) + (MidLine_Buff[y + 5] - steerMidValue);
	midInvSlp = (MidLine_Buff[y - 5] - steerMidValue) / -3.0;

	if(fabs(midErrInvSlp) < 3 && fabs(midInvSlp) < 5 && !(LeftFlag_Switch.LeftLost) && !(RightFlag_Switch.RightLost))
	{
		OLED_ClearLine(5);
		OLED_ShowString(0, 5, "Straight");
		thisMode = STRAIGHT;
	}
	else if (fabs(midErrInvSlp) < 3 && !(LeftFlag_Switch.LeftLost) && !(RightFlag_Switch.RightLost))
	{
		OLED_ClearLine(5);
		OLED_ShowString(0, 5, "Pse Straight");
		thisMode = PSE_ST;
	}
	else
	{
		OLED_ClearLine(5);
		OLED_ShowString(0, 5, "Curv");
		thisMode = CURV;
	}


	return thisMode;
}

void Mode_Change(PIDStruct *steerCtrler, PIDStruct *differCtrler)
{
	RoadMode thisMode;
	thisMode = Road_Check(PIC_DateBlock.MidLine, 15);

	switch (thisMode)
	{
		case STRAIGHT: 
			steerCtrler -> para = steerCtrlerStPara;
			steerCtrler -> useBang = 0;
			differCtrler -> para = differCtrlerStPara;
			//PWM_Expect = PWM_Expect_Base + 800;
			PWM_Expect = PWM_Expect_Base - 920;
			break;
		case PSE_ST:
			steerCtrler -> para = steerCtrlerPseStPara;
			steerCtrler -> useBang = 1;
			differCtrler -> para = differCtrlerPseStPara;
			PWM_Expect = PWM_Expect_Base - 940;
			break;
		case CURV:
			PWM_Expect = PWM_Expect_Base - 940;
			//PWM_Expect = PWM_Expect_Base - 750;
			steerCtrler -> para = steerCtrlerCurvPara;
			steerCtrler -> useBang = 1;
			differCtrler -> para = differCtrlerCurvPara;
			break;
	}
}