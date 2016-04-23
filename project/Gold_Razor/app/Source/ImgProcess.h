/* 
*This head file for image processing
*include edge extacting
*include 
*/
#ifndef _IMGPROCESS_H_
#define _IMGPROCESS_H_

#include "common.h"

typedef struct node 
{
	uint8 x, y;
	struct node *next;
}ListEdge;


ListEdge *Img_Edge(uint8 *img);
ListEdge *List_Insert(ListEdge *listTail, uint8 setX, uint8 setY);
void Node_Delete(ListEdge *temp, ListEdge *preTemp);
ListEdge *Img_Track(ListEdge *edgeList, uint8 *img);
void Track_Test(ListEdge *edgeList, uint8 *img);
void List_Destroy(ListEdge *edgeList);

#endif