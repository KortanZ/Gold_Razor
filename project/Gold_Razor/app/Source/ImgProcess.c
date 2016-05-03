/* 
*This head file for image processing
*include edge extacting
*include 
*/
#include "common.h"

ListEdge *Img_Edge(uint8 *img)
{
	uint8 i, j;

	uint8 thresh = 180;
		/* define  laplacian */
	int8 laplacian[3][3] = {{0, 1, 0}, {1, -4, 1}, {0, 1, 0}};

		/* declear temp array for convolution */
	int16 *imgTemp = (int16 *)malloc(sizeof(int16) * CAMERA_H * CAMERA_W);

	ListEdge *edgeHead = (ListEdge *)malloc(sizeof(ListEdge));
	ListEdge *edgeTail = edgeHead;

	if (!edgeHead)
	{
		OLED_ShowString(0, 5, "Edge malloc faild");
		while (1);
	}
	else
	{
		edgeHead -> x = 255;
		edgeHead -> y = 255;
		edgeHead -> next = NULL;
	}

	if (!imgTemp)
	{
		//printf("Memery alloc faild!\n");
		OLED_ShowString(4, 0, "Memery alloc faild");
		while (1);
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

		for (j = 1; j < CAMERA_W - 1; ++j)
		{
			for (i = CAMERA_H - 2; i > 0; --i)
			{
				if (imgTemp[CAMERA_W * i + j] > thresh) 
				{
					//img[i * CAMERA_W + j] = 255;
					edgeTail = List_Insert(edgeTail, j, i);
				}

			}
		}
		free(imgTemp);
	}

	//List_Destroy(edgeHead);

	/* return head pionter */
	return edgeHead;
}

ListEdge *List_Insert(ListEdge *listTail, uint8 setX, uint8 setY)
{
	/* only tail insert */

	ListEdge *temp = (ListEdge *)malloc(sizeof(ListEdge));

	/* if listTail == listHead */

	if (!temp)
	{
		OLED_ShowString(0, 5, "Node malloc faild");
		while (1);
		//return NULL;
	}
	else
	{
		temp -> x = setX;
		temp -> y = setY;
		temp -> next = NULL;
	}
	listTail -> next = temp;

	/* return tail pointer */

	return temp;
}

ListEdge *Find_Kth(ListEdge *edgeHead, uint16 i)
{
	uint16 cnt = 1;
	ListEdge *temp = edgeHead;

	while (temp && cnt < i)
	{
		temp = temp -> next;
		++cnt;
	}
	if (i == cnt)
	{	
		return temp;
	}
	else
	{
		return NULL;
	}
}

ListEdge *Node_Delete(ListEdge *edgeHead, uint16 i)
{
	/* Delete i th node in the edgeHead */
	ListEdge *p, *s;
	if (i == 1)
	{
		s = edgeHead;
		if (edgeHead)
		{
			edgeHead = edgeHead -> next;
		}
		else
		{
			return NULL;
		}
		free(s);
		return edgeHead;
	}
	p = Find_Kth(edgeHead, i - 1);
	if (!p)
	{
		/* Theres no i - 1 th node */
		return NULL;
	}
	else if (!(p -> next))
	{
		/* Theres no i th node */
		return NULL;
	}
	else
	{
		s = p -> next;
		p -> next = s -> next;
		free(s);
		return edgeHead;
	}
}

void List_Destroy(ListEdge *edgeList)
{
	ListEdge *temp;
	while (edgeList)
	{
		temp = edgeList -> next;
		free(edgeList);
		edgeList = temp;
	}
}

ListEdge *Img_Track(ListEdge *edgeList, uint8 *img)
{
	ListEdge *temp = edgeList -> next;
	uint8 i;
	uint16 top = 0, bottom = 0;
	uint8 isDelete = 0;
	uint16 seq = 1;

	while (temp)
	{
		if (!isDelete)
		{
			if (temp -> y < 109 && temp -> y > 11) //116 = 120 - 1 - 3; 4 = 0 + 1 + 3; 
			{
				for (i = 0; i < 10; ++i)
				{
					top += img[(temp -> y + i) * CAMERA_W + (temp -> x)];
				}

				for (i = 0; i < 10; ++i)
				{
					bottom += img[(temp -> y - i) * CAMERA_W + (temp -> x)];
				}

				if (bottom > top)
				{
					isDelete = 1;
				}
			}
		}
		else
		{
			
			if (!(temp -> next) || (temp -> x) != (temp -> next -> x))
			{
				isDelete = 0;
			}
			edgeList = Node_Delete(edgeList, seq);
		}

		temp = temp -> next;
		++seq;
	}

	return edgeList;
}

void Track_Test(ListEdge *edgeList, uint8 *img)
{
	uint8 i, j;
	ListEdge *temp = edgeList;

	for (i = 0; i < CAMERA_H; ++i)
	{
		for (j = 0; j < CAMERA_W; ++j)
		{
			img[i * CAMERA_W + j] = 0;
		}
	}

	for (edgeList = edgeList -> next; edgeList; edgeList = edgeList -> next)
	{
		img[(edgeList -> y) * CAMERA_W + (edgeList -> x)] = 255;
		free(temp);
		temp = edgeList;
	}
	//List_Destroy(edgeList);
}
