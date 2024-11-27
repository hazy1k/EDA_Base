#ifndef __LCD_INIT_H
#define __LCD_INIT_H
#include "cw32L010.h"

#define USE_HORIZONTAL 3  //���ú�������������ʾ 0��1Ϊ���� 2��3Ϊ����
#define u8 uint8_t
#define u16 uint16_t
#define u32 uint32_t


#if USE_HORIZONTAL==0||USE_HORIZONTAL==1
#define LCD_W 80
#define LCD_H 160

#else
#define LCD_W 160
#define LCD_H 80
#endif


#define LCD_RES_Clr() GPIO_WritePin(CW_GPIOA,GPIO_PIN_2,GPIO_Pin_RESET)
#define LCD_RES_Set() GPIO_WritePin(CW_GPIOA,GPIO_PIN_2,GPIO_Pin_SET)

#define LCD_DC_Clr()  GPIO_WritePin(CW_GPIOA,GPIO_PIN_3,GPIO_Pin_RESET)
#define LCD_DC_Set()  GPIO_WritePin(CW_GPIOA,GPIO_PIN_3,GPIO_Pin_SET)
 
#define LCD_BLK_Clr()  GPIO_WritePin(CW_GPIOA,GPIO_PIN_6,GPIO_Pin_SET)
#define LCD_BLK_Set() GPIO_WritePin(CW_GPIOA,GPIO_PIN_6,GPIO_Pin_RESET)

void LCD_GPIO_Init(void);//��ʼ��GPIO
void LCD_Writ_Bus(u8 dat);
void LCD_WR_DATA16_N(u16 dat, int len);
// ģ��SPIʱ��
void LCD_WR_DATA8(u8 dat);//д��һ���ֽ�
void LCD_WR_DATA(u16 dat);//д�������ֽ�
void LCD_WR_REG(u8 dat);//д��һ��ָ��
void LCD_Address_Set(u16 x1,u16 y1,u16 x2,u16 y2);//�������꺯��
void LCD_Init(void);//LCD��ʼ��


#endif





