#include "common.h"

void imgTempgDis(void)
{

	uint8 i, j;
	uint8 scale = 4;
	float32 thresh, cutoff, sum = 0.0;
	/*define  operator x and y*/
	

	float32 *imgTemp = (float32 *)malloc(sizeof(float32) * CAMERA_H * CAMERA_W);

	for (i = 1; i < CAMERA_H - 1; i++)
	{
		for (j = 1; j < CAMERA_W - 1; j++)
		{
			
		}
	}
	for (i = 1; i < CAMERA_H - 1; ++i)
	{
		for (j = 1; j < CAMERA_W - 1; ++j)     
			sum += imgTemp[CAMERA_W * i + j];
	}
	
	cutoff = scale * (sum / ((CAMERA_H - 2) * (CAMERA_W - 2)));
	thresh = sqrt(cutoff);
	
	for (i = 1; i < CAMERA_H - 1; ++i)
	{
		for (j = 1; j < CAMERA_W - 1; ++j)
		{
			if (imgTemp[CAMERA_W * i + j] > thresh) 
				img[i * CAMERA_W + j] = 255;
			else
			    img[i * CAMERA_W + j] = 0;

		}
	}
	free(imgTemp);
}
