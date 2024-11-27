#ifndef _FLASH_H_
#define _FLASH_H_
#include "cw32l010_flash.h"

void flash_erase(void);
void flash_write(uint16_t offset, uint16_t *data, uint16_t lenght);
void flash_read(uint16_t offset, uint16_t *data, uint16_t lenght);
// void flash_write(uint16_t *data, uint16_t lenght);
// void flash_read(uint16_t *data, uint16_t lenght);
#endif
