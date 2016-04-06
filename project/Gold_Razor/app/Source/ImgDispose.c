#include "common.h"

void imgEdge(uint8 *img)
{

	uint8 i, j;
	uint8 scale = 4;
	float32 thresh, cutoff, sum = 0.0;
	/* define  laplacian */
	int8 laplacian[3][3] = {{0, 1, 0}, {1, -4, 1}, {0, 1, 0}};

	/* declear temp array for convolution */
	float32 *imgTemp = (float32 *)malloc(sizeof(float32) * CAMERA_H * CAMERA_W);

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

	/* comput summation for avg */

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
