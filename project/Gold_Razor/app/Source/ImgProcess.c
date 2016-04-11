/* 
*This head file for image processing
*include edge extacting
*include 
*/
#include "common.h"

void imgEdge(uint8 *img)
{

	uint8 i, j;

	uint8 thresh = 254;
	/* define  laplacian */
	int8 laplacian[3][3] = {{0, 1, 0}, {1, -4, 1}, {0, 1, 0}};

	/* declear temp array for convolution */
	int16 *imgTemp = (int16 *)malloc(sizeof(int16) * CAMERA_H * CAMERA_W);

	if (NULL == imgTemp)
	{
		printf("Memery alloc faild!\n");
		OLED_ShowString(4, 0, "Memery alloc faild");
	}
	else
	{
		/* convolution */
		for (i = 1; i < CAMERA_H - 1; i++)
		{
			for (j = 1; j < CAMERA_W - 1; j++)
			{
				imgTemp[i * CAMERA_W + j] = laplacian[0][1] * img[(i - 1) * CAMERA_W + j]
										  + laplacian[1][0] * img[i * CAMERA_W + (j - 1)]
										  + laplacian[1][1] * img[i * CAMERA_W + j]
										  + laplacian[1][2] * img[i * CAMERA_W + (j + 1)]
										  + laplacian[2][1] * img[(i + 1) * CAMERA_W + j];
			}
		}
		
		/* convert to gray imgage through thresh */

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
}


uint16 *Sample(uint8 *img)
{
	uint16 *vector = (uint16 *)malloc(sizeof(uint16) * 6);

	uint16 cnt = 0;
	uint8 i, j, part;

	if (NULL == vector)
	{
		printf("Memery alloc faild!\n");
		OLED_ShowString(4, 0, "Memery alloc faild");
	}
	else
	{
		for ( part = 0; part < 6; ++part)
		{
			for ( i = (part / 2) * 40; i < ((part / 2) + 1) * 40; ++i)
			{
				for ( j = (part % 2) * 80; j < ((part % 2) + 1) * 80; ++j)
				{
					if (img[i * CAMERA_W + j] == 255)
					{
						++cnt;
					}
				}
			}
			vector[part] = cnt;
			cnt = 0;
		}
	}

	return vector;
}