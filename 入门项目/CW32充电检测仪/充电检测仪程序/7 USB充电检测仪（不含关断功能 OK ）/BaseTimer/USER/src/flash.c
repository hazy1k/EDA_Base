#include "flash.h"

#define PAGE_SIZE 512
#define PAGE_NUM 1
#define START_ADDR (127 * PAGE_SIZE)
#define END_ADDR (START_ADDR + PAGE_SIZE -1)

void flash_erase(void)
{
    uint8_t Flag;
	
	  REGBITS_SET(CW_SYSCTRL->AHBEN, (0x5A5A0000 |bv1)); //flash
	
    // erase
    FLASH_UnlockPages(START_ADDR, END_ADDR);       // �������һ��ҳ��
    Flag = FLASH_ErasePages(START_ADDR, END_ADDR); // �������һ��ҳ��
    FLASH_LockAllPages();
	
	 // FLASH_UnlockPages(512*127, 512*127);    //����127ҳ
  //  Flag = FLASH_ErasePages(512*127, 512*127);    //�������һҳ��
    //FLASH_LockAllPages();
  
    if (Flag)
    {
       // while (1)
            ; // ����ʧ��
    }
}

void flash_write(uint16_t offset,uint16_t *data,uint16_t lenght)
{
    uint8_t Flag;
    // write
    FLASH_UnlockPages(START_ADDR, END_ADDR); // �������һ��ҳ��
//    Flag = FLASH_WriteHalfWords(START_ADDR+offset*2, data, lenght);
	//  FLASH_UnlockPages( 512*127, 512*127 );    //�������һҳ
    Flag = FLASH_WriteHalfWords(512*127+offset*2,data,lenght);    //127ҳ������д��
    
	
   // FLASH_LockAllPages();
    if (Flag)
    {
        while (1)
            ; // д��ʧ��
    }
}

void flash_read(uint16_t offset,uint16_t *data,uint16_t lenght)
{
    int i;
    // read
    for (i = 0; i < lenght; i++)
    {
        *data++ = *((volatile uint16_t *)(START_ADDR + offset*2 + i*2));
    }
}
