#ifndef __SEG_H
#define __SEG_H

#include "cw32l010_gpio.h"

extern uint8_t Seg_Reg[3] ;
extern uint8_t Seg_Table[21];

void Seg_Init(void);
void Close_ALL(void);
void Display_SEGA(unsigned char segbit);
void Display_SEGB(unsigned char segbit);
void Display_SEGC(unsigned char segbit);
void Display_SEGD(unsigned char segbit);
void Display_SEGE(unsigned char segbit);
void Display_SEGF(unsigned char segbit);
void Display_SEGG(unsigned char segbit);
void Display_SEGDP(unsigned char segbit);
void Display_SEGV(void);

void DisplayValue(unsigned int value);

#endif
