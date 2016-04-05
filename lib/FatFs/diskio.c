/*-----------------------------------------------------------------------*/
/* Low level disk I/O module skeleton for FatFs     (C)ChaN, 2013        */
/*-----------------------------------------------------------------------*/
/* If a working storage control module is available, it should be        */
/* attached to the FatFs via a glue function rather than modifying it.   */
/* This is an example of glue functions to attach various exsisting      */
/* storage control module to the FatFs module with a defined API.        */
/*-----------------------------------------------------------------------*/

#include "diskio.h"		/* FatFs lower layer API */
//#include "usbdisk.h"	/* Example: USB drive control */
//#include "atadrive.h"	/* Example: ATA drive control */
//#include "sdcard.h"		/* Example: MMC/SDC contorl */
#include "common.h"     //����LPLD�ײ���K60���ļ�[By LPLD]


//SD����Ϣȫ�ֱ���[By LPLD]
extern SDCARD_STRUCT_PTR sdcard_ptr;

/*-----------------------------------------------------------------------*/
/* Inidialize a Drive                                                    */
/*-----------------------------------------------------------------------*/

DSTATUS disk_initialize (
	BYTE pdrv				/* Physical drive nmuber (0..) */
)
{
  if(pdrv)
    return RES_PARERR;
 
  return (DSTATUS)LPLD_SDHC_InitCard();
}



/*-----------------------------------------------------------------------*/
/* Get Disk Status                                                       */
/*-----------------------------------------------------------------------*/

DSTATUS disk_status (
	BYTE pdrv		/* Physical drive nmuber (0..) */
)
{
  return (DSTATUS)sdcard_ptr->STATUS;
}



/*-----------------------------------------------------------------------*/
/* Read Sector(s)                                                        */
/*-----------------------------------------------------------------------*/

DRESULT disk_read (
	BYTE pdrv,		/* Physical drive nmuber (0..) */
	BYTE *buff,		/* Data buffer to store read data */
	DWORD sector,	/* Sector address (LBA) */
	BYTE count		/* Number of sectors to read (1..128) */
)
{
  if(pdrv || (count == 0))
    return RES_PARERR;

  return (DRESULT)LPLD_SDHC_ReadBlocks(buff, sector, count);
}



/*-----------------------------------------------------------------------*/
/* Write Sector(s)                                                       */
/*-----------------------------------------------------------------------*/

#if _USE_WRITE
DRESULT disk_write (
	BYTE pdrv,			/* Physical drive nmuber (0..) */
	const BYTE *buff,	/* Data to be written */
	DWORD sector,		/* Sector address (LBA) */
	BYTE count			/* Number of sectors to write (1..128) */
)
{
  if(pdrv || (count == 0))
    return RES_PARERR;
  
  return (DRESULT)LPLD_SDHC_WriteBlocks((uint8*)buff, sector, count);
}
#endif


/*-----------------------------------------------------------------------*/
/* Miscellaneous Functions                                               */
/*-----------------------------------------------------------------------*/

#if _USE_IOCTL
DRESULT disk_ioctl (
	BYTE pdrv,		/* Physical drive nmuber (0..) */
	BYTE cmd,		/* Control code */
	void *buff		/* Buffer to send/receive control data */
)
{
  DRESULT result = RES_OK;
  
  if(pdrv)
    return RES_PARERR;
  
  switch(cmd)
  {
    case CTRL_SYNC:
      /*
      ȷ�����������Ѿ����д��������Ĵ���. 
      ������IOģ����һ����д���棬��������������. ���������ֻ��ģʽʹ��.
      */
      // ��POLLINGģʽ�У�����д��������ɡ�
      break;
    case GET_SECTOR_SIZE:
      /*
      ��WORD��ָ���������ʽ����������С.
      ����������ڿɱ�������С������, 
      _MAX_SS Ϊ 512.
      */
      if(buff == NULL)
        result = RES_PARERR;
      else
        *(uint32*)buff = IO_SDCARD_BLOCK_SIZE;      
      break;
    case GET_SECTOR_COUNT:
      /*
      ��UINT32��ָ���������ʽ���ش��̵Ŀ���������. 
      ���������f_mkfs���������Ծ����ɴ������ľ�. 
      */
      if(buff == NULL)
        result = RES_PARERR;
      else
        *(uint32*)buff = sdcard_ptr->NUM_BLOCKS;
      break;
    case GET_BLOCK_SIZE:
      /*
      ��UINT32���͵�ָ��������ط���flash�ڴ��в�����������.
      �Ϸ�����ֵΪ2��1��32768�η�.
      ����1���������С������豸δ֪.
      ���������f_mkfs�������ò���ͼ�������������߽�������ݶ���.
      */
      result = RES_PARERR;
      break;
    case CTRL_ERASE_SECTOR:
      /*
      ������UINT32����ָ������ָ����flash�ڴ�,{<start sector>, <end sector>}.
      �������Ϊ��flash�ڴ�,���������Ч.
      FatFsϵͳ��������,�������ʧ��Ҳ����Ӱ���ļ�����.
      ��_USE_ERASEΪ1ʱ�ƶ�һ����������ô�����.
      */
      result = RES_PARERR;
      break;
    default:
      return RES_PARERR;
    
  }
  return result;
}
#endif
