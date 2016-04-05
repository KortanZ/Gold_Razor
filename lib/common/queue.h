/**
 * @file queue.h
 * @version 3.0[By LPLD]
 * @date 2013-06-18
 * @brief ʵ���Ƚ��ȳ�����
 *
 * ���Ľ���:�������޸�
 *
 * ��Ȩ����:�����������µ��Ӽ������޹�˾
 * http://www.lpld.cn
 * mail:support@lpld.cn
 *
 * @par
 * ����������������[LPLD]������ά������������ʹ���߿���Դ���롣
 * �����߿���������ʹ�û��Դ���롣�����μ�����ע��Ӧ���Ա�����
 * ���ø��Ļ�ɾ��ԭ��Ȩ���������������ο����߿��Լ�ע���ΰ�Ȩ�����ߡ�
 * ��Ӧ�����ش�Э��Ļ����ϣ�����Դ���롢���ó��۴��뱾��
 * �������²���������ʹ�ñ��������������κ��¹ʡ��������λ���ز���Ӱ�졣
 * ����������������͡�˵��������ľ���ԭ�����ܡ�ʵ�ַ�����
 * ������������[LPLD]��Ȩ�������߲��ý�������������ҵ��Ʒ��
 */

#ifndef _QUEUE_H_
#define _QUEUE_H_

/********************************************************************/

/* 
 * Individual queue node
 */
typedef struct NODE
{
    struct NODE *next;
} QNODE;

/* 
 * Queue Struture - linked list of qentry items 
 */
typedef struct
{
    QNODE *head;
    QNODE *tail;
} QUEUE;

/*
 * Functions provided by queue.c
 */
void queue_init(QUEUE *);

int32 queue_isempty(QUEUE *);

void queue_add(QUEUE *, QNODE *);

QNODE* queue_remove(QUEUE *);

QNODE* queue_peek(QUEUE *);

void queue_move(QUEUE *, QUEUE *);

/********************************************************************/

#endif /* _QUEUE_H_ */
