/**
 * @file relocate.c
 * @version 3.0[By LPLD]
 * @date 2013-06-18
 * @brief Kinetisͨ�����ݴ���Ǩ�ƺ���
 *
 * ���Ľ���:�������޸�
 *
 * ʵ�����ݡ�������ROM��RAMǨ�ƵĹ���
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

#if defined(__IAR_SYSTEMS_ICC__)
  #pragma section = ".data"
  #pragma section = ".data_init"
  #pragma section = ".bss"
  #pragma section = "CodeRelocate"
  #pragma section = "CodeRelocateRam"
#endif
   
/********************************************************************/
void common_relocate(void)
{
    #ifndef __IAR_SYSTEMS_ICC__
      #warning ��IAR��������ȷ���˴���ַ
      extern char __START_BSS[];
      extern char __END_BSS[];
      extern uint32 __DATA_ROM[];
      extern uint32 __DATA_RAM[];
      extern char __DATA_END[];
    #endif
  
  /* ����һ���������ڿ���ѭ����ʹ�� */
  uint32 n;
  
  /* Ϊ��ͬ�����ݶζ���ָ�롣
  * ��Щ�������������ļ��л�ȡ��ֵ��ʼ��
  */
  uint8 * data_ram, * data_rom, * data_rom_end;
  uint8 * bss_start, * bss_end;
  
  
  /* ���������ļ��е�VECTOR_TABLE��VECTOR_RAM�ĵ�ַ */
  extern uint32 __VECTOR_TABLE[];
  extern uint32 __VECTOR_RAM[];
  
  /* ���ж��������Ƶ�RAM�� */
  if (__VECTOR_RAM != __VECTOR_TABLE)
  {
    for (n = 0; n < 0x410; n++)
      __VECTOR_RAM[n] = __VECTOR_TABLE[n];
  }
  /* ���µ��ж�������ָ�븳��VTOR�Ĵ��� */
  write_vtor((uint32)__VECTOR_RAM);
  
  /* ���.data�εĵ�ַ(�ѳ�ʼ�������ݶ�) */
  #if defined(__IAR_SYSTEMS_ICC__)
    data_ram = __section_begin(".data");
    data_rom = __section_begin(".data_init");
    data_rom_end = __section_end(".data_init");
    n = data_rom_end - data_rom;	
  #else
    #warning ��IAR��������ȷ���˴���ַ
    data_ram = (uint8 *)__DATA_RAM;
    data_rom = (uint8 *)__DATA_ROM;
    data_rom_end  = (uint8 *)__DATA_END; /* �ö���CodeWarrior��������ΪRAM��ַ */
    n = data_rom_end - data_rom;
  #endif
  
  /* ��ROM�����ѳ�ʼ�������ݵ�RAM */
  while (n--)
    *data_ram++ = *data_rom++;
  
  
  /* ���.bss�εĵ�ַ (��ʼ��Ϊ0������) */
  #if defined(__IAR_SYSTEMS_ICC__)
  bss_start = __section_begin(".bss");
  bss_end = __section_end(".bss");  
  #else
  #warning ��IAR��������ȷ���˴���ַ
  bss_start = (uint8 *)__START_BSS;
  bss_end = (uint8 *)__END_BSS;
  #endif
  
  /* �����ʼ��Ϊ0�����ݶ� */
  n = bss_end - bss_start;
  while(n--)
    *bss_start++ = 0;
  
  /* ȡ������Ӧ�ô�ROM���Ƶ�RAM�Ĵ���εĵ�ַ��
  * IAR��һ��Ԥ����Ĺؼ��ֿ��Ա�Ƕ����ĺ���Ϊ��RAMִ�С�
  * �ں����ķ�������ǰ���"__ramfunc"�ؼ��ֿ��Խ��������Ϊ��RAM��ִ�С�
  * ����:__ramfunc void foo(void);
  */
  #if defined(__IAR_SYSTEMS_ICC__)
  uint8* code_relocate_ram = __section_begin("CodeRelocateRam");
  uint8* code_relocate = __section_begin("CodeRelocate");
  uint8* code_relocate_end = __section_end("CodeRelocate");
  
  /* ��������ROM���Ƶ�RAM */
  n = code_relocate_end - code_relocate;
  while (n--)
    *code_relocate_ram++ = *code_relocate++;
  #endif
}
/********************************************************************/
