/*
*This head file for image processing
*include edge extacting
*include
*/
//#include "common.h"
#include "ImgProcess.h"
#include "Eagle_ov7725.h"
#include "Oled.h"

uint8 Bef_Scan(uint8*);
void TwinLine_Deal(uint8 *,int8);
void Get_MidAve(uint8 * ,float32 ,float32 ,float32 ,float32);

PIC_DateStruct PIC_DateBlock;
LeftFlag_Struct LeftFlag_Switch;
RightFlag_Struct RightFlag_Switch;

int16 MidAve = 0;

void Get_MidLine(void)
{
	uint8 i,j,k;
	int8 Row;
	img_extract(img,imgbuff,CAMERA_SIZE);       //图像解压
	for(k = 0,i = 1; i < CAMERA_H; i += 3 , k++)          //隔行提取
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
		if(LeftFlag_Switch.LeftLost == 0  && RightFlag_Switch.RightWhiteLost == 1)
		{
			(++RightFlag_Switch.RightTurn >= 10)  ? 	\
				(RightFlag_Switch.RightTurnFlag = 1) : 	\
				(LeftFlag_Switch.LeftTurn = 0 , LeftFlag_Switch.LeftTurnFlag = 0);
		}
		else if(LeftFlag_Switch.LeftWhiteLost == 1 && RightFlag_Switch.RightLost == 0)
		{
			(++LeftFlag_Switch.LeftTurn >= 10) ?		\
				(LeftFlag_Switch.LeftTurnFlag = 1) :	\
				(RightFlag_Switch.RightTurn = 0 , RightFlag_Switch.RightTurnFlag = 0);
		}
		if(LeftFlag_Switch.LeftTurnFlag || RightFlag_Switch.RightTurnFlag)
		{
			if(LeftFlag_Switch.LeftBlackLost&& RightFlag_Switch.RightBlackLost)
				break;
		}
	}
	for(;Row >= 0;Row--)
	{
		if(LeftFlag_Switch.LeftTurnFlag)
		{
			PIC_DateBlock.TrackInf_DataBlock.LeftLine[Row] = 1;
			PIC_DateBlock.TrackInf_DataBlock.RightLine[Row] = 1;
			PIC_DateBlock.TrackInf_DataBlock.MidLine[Row] = 1;
		}
		else if(RightFlag_Switch.RightTurnFlag)
		{
			PIC_DateBlock.TrackInf_DataBlock.LeftLine[Row] = PICTURE_W - 2;
			PIC_DateBlock.TrackInf_DataBlock.RightLine[Row] = PICTURE_W - 2;
			PIC_DateBlock.TrackInf_DataBlock.MidLine[Row] = PICTURE_W - 2;
		}
	}
	LeftFlag_Switch.LeftTurn = 0;
	LeftFlag_Switch.LeftTurnFlag = 0;
	RightFlag_Switch.RightTurn = 0;
	RightFlag_Switch.RightTurnFlag = 0;
	Get_MidAve(PIC_DateBlock.TrackInf_DataBlock.MidLine  \
		       , 0.01    \
		       , 0.04    \
		       , 0.03    \
		       , 0.02);
}

uint8 Bef_Scan(uint8 *pic_buff)
{
	uint8 i;
	int8 Row;
	uint8 Black_Check = 0;
	for(Row = PICTURE_H - 1;Row > PICTURE_H - 4;Row--)
	{
		if(White == *(pic_buff + Row * PICTURE_W + 1) &&\
		   White == *(pic_buff + Row * PICTURE_W + 2))        //左线扫描
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
		   White == *(pic_buff + Row * PICTURE_W + PICTURE_W - 3))      // 右线扫描
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
   		//右线在左线的左边,设置为缺省值
		if(PIC_DateBlock.TrackInf_DataBlock.RightLine[Row] < PIC_DateBlock.TrackInf_DataBlock.LeftLine[Row])
		{
			PIC_DateBlock.TrackInf_DataBlock.LeftLine[Row] = 2;
			PIC_DateBlock.TrackInf_DataBlock.RightLine[Row] = 157;
		}
		//计算赛道宽度和中线值
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
	if(Black_Check > 2)
	{

		LPLD_FTM_PWM_ChangeDuty(FTM0, FTM_Ch1, 0);
		LPLD_FTM_PWM_ChangeDuty(FTM0, FTM_Ch2, 0);
		LPLD_FTM_PWM_ChangeDuty(FTM0, FTM_Ch3, 0);
		LPLD_FTM_PWM_ChangeDuty(FTM0, FTM_Ch4, 0);
		OLED_Clear();
		OLED_ShowString(0 , 3 , "Car Broke Down!");
		while(1);
	}
	return Row;
}
void TwinLine_Deal(uint8 *pic_buff,int8 Row_buff)
{
	uint8 i;
	//从中间向左扫左中线
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
	//从中间向右扫右线
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
	PIC_DateBlock.TrackInf_DataBlock.TrackWidth = PIC_DateBlock.TrackInf_DataBlock.RightLine[Row_buff]     \
		                                              - PIC_DateBlock.TrackInf_DataBlock.LeftLine[Row_buff];
	PIC_DateBlock.TrackInf_DataBlock.MidLine[Row_buff] = (PIC_DateBlock.TrackInf_DataBlock.RightLine[Row_buff]     \
		                                                 + PIC_DateBlock.TrackInf_DataBlock.LeftLine[Row_buff]) / 2;
	(PIC_DateBlock.TrackInf_DataBlock.MidLine[Row_buff] >= 155) ? 	\
		(PIC_DateBlock.TrackInf_DataBlock.MidLine[Row_buff] = 155) : (NULL);
	(PIC_DateBlock.TrackInf_DataBlock.MidLine[Row_buff] <= 4) ?
		(PIC_DateBlock.TrackInf_DataBlock.MidLine[Row_buff] = 4) : (NULL);
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
    ov7725_eagle_img_flag = IMG_START;                   //¿ªÊ¼²É¼¯Í¼Ïñ
    PORTA->ISFR = ~0;
    enable_irq((IRQn_Type)(PORTA_IRQn));
    while (ov7725_eagle_img_flag != IMG_FINISH)
    {
        if (ov7725_eagle_img_flag == IMG_FAIL)            //¼ÙÈçÍ¼Ïñ²É¼¯´íÎó£¬ÔòÖØÐÂ¿ªÊ¼²É¼¯
        {
            ov7725_eagle_img_flag = IMG_START;           //¿ªÊ¼²É¼¯Í¼Ïñ
            PORTA->ISFR = 0xFFFFFFFFu;                //Ð´1ÇåÖÐ¶Ï±êÖ¾Î»(±ØÐëµÄ£¬²»È»»Øµ¼ÖÂÒ»¿ªÖÐ¶Ï¾ÍÂíÉÏ´¥·¢ÖÐ¶Ï)
            enable_irq(PORTA_IRQn);                 //ÔÊÐíPTAµÄÖÐ¶Ï
        }
    }
}

