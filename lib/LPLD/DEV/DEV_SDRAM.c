/*
* @file DEV_SDRAM.c
* @version 0.1[By LPLD]
* @date 2013-09-24
* @brief SDRAM�豸��������
*
* ���Ľ���:�ɸ���ʵ��Ӳ���޸�
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
#include "DEV_SDRAM.h"

//�ýṹ�幹�ɷ����ڴ����С��Ԫ
//ͬ���������ڷ�����ͷ��ڴ�ռ亯��������ṹ
typedef struct LPLD_ALLOC_HDR
{
  struct
  {
    struct LPLD_ALLOC_HDR *ptr;
    unsigned int size;
  } s;
  unsigned int align;
  unsigned int pad;
} LPLD_ALLOC_HDR;

static LPLD_ALLOC_HDR EX_base;
static LPLD_ALLOC_HDR *EX_freep = NULL;

/*
 * LPLD_SDRAM_Init
 * ��ʼ��SDRAM�����FlexBus
 * 
 * ˵��:
 *    ����ʼ��������������FlexBus��SDRAM������
 *    ����Ϊ8λ�˿ڴ�С
 *    ��ַ�������߸���
 *    ��ַ��ΪFB_AD[19:0]
 *    ������ΪFB_AD[31:24]
 *    CS:FB_CS1
 *    RW:FB_FB_RW
 *    RD:FB_OE 
 */
void LPLD_SDRAM_Init()
{
  FB_InitTypeDef fb_init;
  fb_init.FB_Fbx = FB1;
  fb_init.FB_ChipSelAddress = SDRAM_ADDRESS;
  fb_init.FB_AutoAckEnable = TRUE;
  fb_init.FB_IsRightJustied = FALSE;
  fb_init.FB_WateStates = 0x02;
  fb_init.FB_PortSize = FB_SIZE_8BIT;
  fb_init.FB_AddressSpace = FB_SPACE_KB(SDRAM_SIZE); 
  fb_init.FB_ReadAddrHold = 0;
  fb_init.FB_WriteAddrHold = 0;
  LPLD_FlexBus_Init(fb_init); 
}

/*
 * LPLD_SDRAM_Free
 * �ͷ�SDRAM�еĿռ�
 * 
 * ������
 *    *ap--�ռ��׵�ַָ��
 */
void LPLD_SDRAM_Free(void *ap)
{
  LPLD_ALLOC_HDR *bp, *p;
  
  bp = (LPLD_ALLOC_HDR *)ap - 1;  
  for (p = EX_freep; !((bp > p) && (bp < p->s.ptr)) ; p = p->s.ptr)
  {
    if ((p >= p->s.ptr) && ((bp > p) || (bp < p->s.ptr)))
    {
      break; 
    }
  }
  
  if ((bp + bp->s.size) == p->s.ptr)
  {
    bp->s.size += p->s.ptr->s.size;
    bp->s.ptr = p->s.ptr->s.ptr;
  }
  else
  {
    bp->s.ptr = p->s.ptr;
  }
  
  if ((p + p->s.size) == bp)
  {
    p->s.size += bp->s.size;
    p->s.ptr = bp->s.ptr;
  }
  else
  {
    p->s.ptr = bp;
  }
  
  EX_freep = p;
}

/*
 * LPLD_SDRAM_Malloc
 * ��̬����SDRAM�еĿռ�
 * 
 * ������
 *    nbytes--���ݳ���
 *
 * ����ֵ��
 *    �ռ��ַָ��
 */
void *LPLD_SDRAM_Malloc(unsigned nbytes)
{
  LPLD_ALLOC_HDR *p, *prevp;
  unsigned nunits;   
  char* __HEAP_START;
  char* __HEAP_END;
  
  __HEAP_START = (char*)(SDRAM_ADDRESS);
  __HEAP_END = (char*)(SDRAM_ADDRESS+SDRAM_SIZE*1024);
  
  nunits = ((nbytes+sizeof(LPLD_ALLOC_HDR)-1) / sizeof(LPLD_ALLOC_HDR)) + 1;
  
  if ((prevp = EX_freep) == NULL)
  {
    p = (LPLD_ALLOC_HDR *)__HEAP_START;
    p->s.size = ( ((uint32)__HEAP_END - (uint32)__HEAP_START)
                 / sizeof(LPLD_ALLOC_HDR) );
    p->s.ptr = &EX_base;
    EX_base.s.ptr = p;
    EX_base.s.size = 0;
    prevp = EX_freep = &EX_base;
  }
  
  for (p = prevp->s.ptr; ; prevp = p, p = p->s.ptr)
  {
    if (p->s.size >= nunits)
    {
      if (p->s.size == nunits)
      {
        prevp->s.ptr = p->s.ptr;
      }
      else
      {
        p->s.size -= nunits;
        p += p->s.size;
        p->s.size = nunits;
      }
      EX_freep = prevp;
      return (void *)(p + 1);
    }
    
    if (p == EX_freep)
      return NULL;
  }
}


