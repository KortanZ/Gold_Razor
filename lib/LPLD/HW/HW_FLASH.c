/**
 * @file HW_FLASH.c
 * @version 3.0[By LPLD]
 * @date 2013-06-18
 * @brief FTFL�ײ�ģ����غ���
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
#include "common.h"
#include "HW_FLASH.h"

/*
 * LPLD_Flash_Init
 * Flashģ���ʼ��
 * 
 * ����:
 *    ��
 *
 * ���:
 *    ��
 */
void LPLD_Flash_Init(void)
{
#if defined(CPU_MK60DZ10) || defined(CPU_MK60D10) 
  //���Flash���ʴ���
  if (FTFL->FSTAT & FTFL_FSTAT_ACCERR_MASK)
  {
    FTFL->FSTAT |= FTFL_FSTAT_ACCERR_MASK;       //��������־
  }
  //��鱣������
  else if (FTFL->FSTAT & FTFL_FSTAT_FPVIOL_MASK)
  {
    FTFL->FSTAT |= FTFL_FSTAT_FPVIOL_MASK;
  }
  //������ͻ����
  else if (FTFL->FSTAT & FTFL_FSTAT_RDCOLERR_MASK)
  {
    FTFL->FSTAT |= FTFL_FSTAT_RDCOLERR_MASK;
  }
  
  //����Flashģ������ݻ���
  FMC->PFB0CR &= ~FMC_PFB0CR_B0DCE_MASK;
  FMC->PFB1CR &= ~FMC_PFB1CR_B1DCE_MASK;
#elif defined(CPU_MK60F12) || defined(CPU_MK60F15)  
  //���Flash���ʴ���
  if (FTFE->FSTAT & FTFE_FSTAT_ACCERR_MASK)
  {
    FTFE->FSTAT |= FTFE_FSTAT_ACCERR_MASK;//��������־
  }
  //��鱣������
  else if (FTFE->FSTAT & FTFE_FSTAT_FPVIOL_MASK)
  {
    FTFE->FSTAT |= FTFE_FSTAT_FPVIOL_MASK;
  }
  else if (FTFE->FSTAT & FTFE_FSTAT_RDCOLERR_MASK)
  {
  //������ͻ����
    FTFE->FSTAT |= FTFE_FSTAT_RDCOLERR_MASK;
  } /* EndIf */
  //����Flashģ������ݻ���
  FMC->PFB01CR &= ~FMC_PFB01CR_B01DCE_MASK;
  FMC->PFB23CR &= ~FMC_PFB23CR_B23DCE_MASK;
#endif
} 


/*
 * LPLD_Flash_SectorErase
 * ����Flash����
 * 
 * ����:
 *    FlashPtr--������ַָ�룬�������ų���2048
 *
 * ���:
 *    �������
 */
uint8 LPLD_Flash_SectorErase(uint32 FlashPtr)
{
  uint8 Return = FLASH_OK;
#if defined(CPU_MK60DZ10) || defined(CPU_MK60D10)   
  //�ȴ�CCIF��1
  while (!(FTFL->FSTAT & FTFL_FSTAT_CCIF_MASK)){};
  //д�������FCCOB�Ĵ���
  FTFL->FCCOB0 = FLASH_CMD_ERSSCR;
  FTFL->FCCOB1 = (uint8) (FlashPtr >> 16);
  FTFL->FCCOB2 = (uint8)((FlashPtr >> 8 ) & 0xFF);
  FTFL->FCCOB3 = (uint8)( FlashPtr & 0xFF);
  
  //ִ������
  FTFL->FSTAT |= FTFL_FSTAT_CCIF_MASK;    
  //�ȴ��������
  while (!(FTFL->FSTAT & FTFL_FSTAT_CCIF_MASK)) {};
  
  //���Flash���ʴ���
  if (FTFL->FSTAT & FTFL_FSTAT_ACCERR_MASK)
  {
    FTFL->FSTAT |= FTFL_FSTAT_ACCERR_MASK;       //��������־
    Return |= FLASH_FACCERR;                    //���·���ֵ
  }
  //���Flash������־
  else if (FTFL->FSTAT & FTFL_FSTAT_FPVIOL_MASK)
  {
    FTFL->FSTAT |= FTFL_FSTAT_FPVIOL_MASK;
    Return |= FLASH_FPVIOL;
  }
  //���Flash����ͻ����
  else if (FTFL->FSTAT & FTFL_FSTAT_RDCOLERR_MASK)
  {
    FTFL->FSTAT |= FTFL_FSTAT_RDCOLERR_MASK;
    Return |= FLASH_RDCOLERR;
  }
  //���MGSTAT0�ǿɾ�������
  else if (FTFL->FSTAT & FTFL_FSTAT_MGSTAT0_MASK)
  {
    Return |= FLASH_MGSTAT0;
  } 
#elif defined(CPU_MK60F12) || defined(CPU_MK60F15)
  //�ȴ�CCIF��1
  while (!(FTFE->FSTAT & FTFE_FSTAT_CCIF_MASK)){};
  //д�������FCCOB�Ĵ���
  FTFE->FCCOB0 = FlashCmd_SectorErase;
  FTFE->FCCOB1 = (uint8_t) (FlashPtr >> 16);
  FTFE->FCCOB2 = (uint8_t)((FlashPtr >> 8 ) & 0xFF);
  FTFE->FCCOB3 = (uint8_t)( FlashPtr & 0xFF);

  //ִ������
  FTFE->FSTAT |= FTFE_FSTAT_CCIF_MASK;    
  //�ȴ��������
  while (!(FTFE->FSTAT & FTFE_FSTAT_CCIF_MASK)) {};
  //���Flash���ʴ���
  if (FTFE->FSTAT & FTFE_FSTAT_ACCERR_MASK)
  {
    FTFE->FSTAT |= FTFE_FSTAT_ACCERR_MASK; //��������־
    Return |= FLASH_FACCERR;              //���·���ֵ
  }
  //���Flash������־
  else if (FTFE->FSTAT & FTFE_FSTAT_FPVIOL_MASK)
  {
    FTFE->FSTAT |= FTFE_FSTAT_FPVIOL_MASK;
    Return |= FLASH_FPVIOL;
  }
  else if (FTFE->FSTAT & FTFE_FSTAT_RDCOLERR_MASK)
  {
    FTFE->FSTAT |= FTFE_FSTAT_RDCOLERR_MASK;
    Return |= FLASH_RDCOLERR;
  }
  //���Flash����ͻ����
  else if (FTFE->FSTAT & FTFE_FSTAT_MGSTAT0_MASK)
  {
    Return |= FLASH_MGSTAT0;
  } 
#endif
  return  Return;
}

/*
 * LPLD_Flash_ByteProgram
 * ���Flash
 * 
 * ����:
 *    FlashStartAdd--Flash�����ʼ��ַ
 *    *DataSrcPtr--����Դָ��
 *    NumberOfBytes--�����ֽڳ���
 *
 * ���:
 *    �������
 */
uint8 LPLD_Flash_ByteProgram(uint32 FlashStartAdd, uint32 *DataSrcPtr, uint32 NumberOfBytes)
{
  uint8 Return = FLASH_OK;
  
  uint32 size_buffer;
  
  if (NumberOfBytes == 0)
  {
    return FLASH_CONTENTERR;
  }
  else
  {
    size_buffer = (NumberOfBytes - 1)/BYTE_DIV + 1;
  }
#if defined(CPU_MK60DZ10) || defined(CPU_MK60D10)
  //�ȴ�ֱ��CCIF����
  while (!(FTFL->FSTAT & FTFL_FSTAT_CCIF_MASK)){};

  while ((size_buffer) && (Return == FLASH_OK))
  {
    //дFLASH���FCCOB
    FTFL->FCCOB0 = FLASH_CMD_PGM4;
    FTFL->FCCOB1 = (uint8)(FlashStartAdd >> 16);
    FTFL->FCCOB2 = (uint8)((FlashStartAdd >> 8) & 0xFF);
    FTFL->FCCOB3 = (uint8)(FlashStartAdd & 0xFF);
    //���K60���ó�ΪС�˸�ʽ���������²���
    FTFL->FCCOB4 = (uint8)(*((uint8*)DataSrcPtr+3));
    FTFL->FCCOB5 = (uint8)(*((uint8*)DataSrcPtr+2));
    FTFL->FCCOB6 = (uint8)(*((uint8*)DataSrcPtr+1));
    FTFL->FCCOB7 = (uint8)(*((uint8*)DataSrcPtr+0));
    //���K60���ó�Ϊ��˸�ʽ���������²���
    //FTFL_FCCOB4 = (uint8)(*((uint_8*)DataSrcPtr+0));
    //FTFL_FCCOB5 = (uint8)(*((uint_8*)DataSrcPtr+1));
    //FTFL_FCCOB6 = (uint8)(*((uint_8*)DataSrcPtr+2));
    //FTFL_FCCOB7 = (uint8)(*((uint_8*)DataSrcPtr+3));
    //����FLASH��������
    FTFL->FSTAT |= FTFL_FSTAT_CCIF_MASK;    
    //�ȴ��������
    while (!(FTFL->FSTAT & FTFL_FSTAT_CCIF_MASK)) {};
    
    //���FLASH���ʴ���
    if (FTFL->FSTAT & FTFL_FSTAT_ACCERR_MASK)
    {
        
        FTFL->FSTAT |= FTFL_FSTAT_ACCERR_MASK;
    
        Return |= FLASH_FACCERR;
    }
    //���FLASH��������
    else if (FTFL->FSTAT & FTFL_FSTAT_FPVIOL_MASK)
    {
        FTFL->FSTAT |= FTFL_FSTAT_FPVIOL_MASK;
    
        Return |= FLASH_FPVIOL;
    }
    
    else if (FTFL->FSTAT & FTFL_FSTAT_RDCOLERR_MASK)
    {
        FTFL->FSTAT |= FTFL_FSTAT_RDCOLERR_MASK;
    
        Return |= FLASH_RDCOLERR;
    }
    else if (FTFL->FSTAT & FTFL_FSTAT_MGSTAT0_MASK)
    {
        Return |= FLASH_MGSTAT0;
    } 
    size_buffer --;
    (uint32*)DataSrcPtr++;
    FlashStartAdd +=4;
  }
#elif defined(CPU_MK60F12) || defined(CPU_MK60F15) 
  //�ȴ�ֱ��CCIF����
  while (!(FTFE->FSTAT & FTFE_FSTAT_CCIF_MASK)){};

  while ((size_buffer) && (Return == FLASH_OK))
  {
    //дFLASH���FCCOB
    FTFE->FCCOB0 = FlashCmd_ProgramPhrase;
    FTFE->FCCOB1 = (uint8_t)( FlashStartAdd >> 16);
    FTFE->FCCOB2 = (uint8_t)((FlashStartAdd >>  8) & 0xFF);
    FTFE->FCCOB3 = (uint8_t)( FlashStartAdd & 0xFF);
    //���K60���ó�ΪС�˸�ʽ���������²���
    FTFE->FCCOB4 = (uint8_t)(*((uint8_t*)DataSrcPtr+3));
    FTFE->FCCOB5 = (uint8_t)(*((uint8_t*)DataSrcPtr+2));
    FTFE->FCCOB6 = (uint8_t)(*((uint8_t*)DataSrcPtr+1));
    FTFE->FCCOB7 = (uint8_t)(*((uint8_t*)DataSrcPtr+0));
    FTFE->FCCOB8 = (uint8_t)(*((uint8_t*)DataSrcPtr+7));
    FTFE->FCCOB9 = (uint8_t)(*((uint8_t*)DataSrcPtr+6));
    FTFE->FCCOBA = (uint8_t)(*((uint8_t*)DataSrcPtr+5));
    FTFE->FCCOBB = (uint8_t)(*((uint8_t*)DataSrcPtr+4));
    //���K60���ó�Ϊ��˸�ʽ���������²���
    //FTFE_FCCOB4 = (uint8_t)(*((uint_8*)DataSrcPtr+0));
    //FTFE_FCCOB5 = (uint8_t)(*((uint_8*)DataSrcPtr+1));
    //FTFE_FCCOB6 = (uint8_t)(*((uint_8*)DataSrcPtr+2));
    //FTFE_FCCOB7 = (uint8_t)(*((uint_8*)DataSrcPtr+3));
    //����FLASH��������
    FTFE->FSTAT |= FTFE_FSTAT_CCIF_MASK;    
    //�ȴ��������
    while (!(FTFE->FSTAT & FTFE_FSTAT_CCIF_MASK)) {};

    //���FLASH���ʴ���
    if (FTFE->FSTAT & FTFE_FSTAT_ACCERR_MASK)
    {
      FTFE->FSTAT |= FTFE_FSTAT_ACCERR_MASK;
      Return |= FLASH_FACCERR;
    }
    //���FLASH��������
    else if (FTFE->FSTAT & FTFE_FSTAT_FPVIOL_MASK)
    {
      FTFE->FSTAT |= FTFE_FSTAT_FPVIOL_MASK;
      Return |= FLASH_FPVIOL;
    }
    else if (FTFE->FSTAT & FTFE_FSTAT_RDCOLERR_MASK)
    {
      FTFE->FSTAT |= FTFE_FSTAT_RDCOLERR_MASK;
      Return |= FLASH_RDCOLERR;
    }
    else if (FTFE->FSTAT & FTFE_FSTAT_MGSTAT0_MASK)
    {
        Return |= FLASH_MGSTAT0;
    } 
    //����ƫ����
    size_buffer --;
    DataSrcPtr += 2;     
    FlashStartAdd +=BYTE_DIV;
  }
#endif
  return  Return;
} 
