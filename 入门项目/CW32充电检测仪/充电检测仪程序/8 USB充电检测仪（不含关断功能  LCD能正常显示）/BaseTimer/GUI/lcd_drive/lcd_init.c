#include "lcd_init.h"
#include "cw32L010.h"
#include "main.h"
#include "cw32l010_spi.h"

extern void delay1ms(uint32_t u32Cnt);

void LCD_GPIO_Init(void)
{
	  GPIO_InitTypeDef GPIO_InitStruct; // �����ṹ��
	
	  REGBITS_SET(CW_SYSCTRL->AHBEN, SYSCTRL_AHBEN_GPIOA_Msk);
    SYSCTRL_APBPeriphClk_Enable1(SYSCTRL_APB1_PERIPH_SPI, ENABLE);  
	
		GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
		GPIO_InitStruct.IT = GPIO_IT_NONE;
		GPIO_InitStruct.Pins = GPIO_PIN_3|GPIO_PIN_6|GPIO_PIN_4|GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2;
		GPIO_Init(CW_GPIOA, &GPIO_InitStruct);
	 
	  PA00_AFx_SPI1SCK();
	  PA04_AFx_SPI1MOSI();
	  PA01_AFx_SPI1NCS();
 

    SPI_InitTypeDef SPI_InitStructure = {0};

    SPI_InitStructure.SPI_Direction = SPI_Direction_1Line_TxOnly;       // ˫��ȫ˫��
    SPI_InitStructure.SPI_Mode = SPI_Mode_Master;                       // ����ģʽ
    SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;                   // ֡���ݳ���Ϊ8bit
    SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;                          // ʱ�ӿ��е�ƽΪ��
    SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;                        // ��һ�����ز���
    SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;                           // Ƭѡ�ź���SSI�Ĵ�������
    SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_4; // ������ΪPCLK��8��Ƶ
    SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;                  // �����Чλ MSB �շ���ǰ
    SPI_InitStructure.SPI_Speed = SPI_Speed_High;                        // ����SPI
    SPI_Init(CW_SPI, &SPI_InitStructure);

    SPI_Cmd(CW_SPI, ENABLE);
}


/******************************************************************************
      ����˵����LCD��������д�뺯��
      ������ݣ�dat  Ҫд��Ĵ�������
      ����ֵ��  ��
******************************************************************************/
void LCD_Writ_Bus(u8 dat)
{
	// LCD_CS_Clr();
	while (SPI_GetFlagStatus(CW_SPI, SPI_FLAG_TXE) == RESET)
		;
	SPI_SendData(CW_SPI, dat);
	while (SPI_GetFlagStatus(CW_SPI, SPI_FLAG_BUSY) == SET)
		;
	// LCD_CS_Set();
}
void LCD_WR_DATA16_N(u16 dat,int len)
{
	SPI_NSSInternalSoftwareConfig(CW_SPI, SPI_NSSInternalSoft_Reset);
	while (SPI_GetFlagStatus(CW_SPI, SPI_FLAG_TXE) == RESET)
		;
	while (len--)
	{
		// LCD_Writ_Bus(dat>>8);
		// LCD_Writ_Bus(dat);
		SPI_SendData(CW_SPI, dat >> 8);
		while (SPI_GetFlagStatus(CW_SPI, SPI_FLAG_BUSY) == SET)
			;
		SPI_SendData(CW_SPI, dat);
		while (SPI_GetFlagStatus(CW_SPI, SPI_FLAG_BUSY) == SET)
			;
	}

	SPI_NSSInternalSoftwareConfig(CW_SPI, SPI_NSSInternalSoft_Set);
}
/******************************************************************************
      ����˵����LCDд������
      ������ݣ�dat д�������
      ����ֵ��  ��
******************************************************************************/
void LCD_WR_DATA8(u8 dat)
{
	SPI_NSSInternalSoftwareConfig(CW_SPI, SPI_NSSInternalSoft_Reset);
	LCD_Writ_Bus(dat);
	SPI_NSSInternalSoftwareConfig(CW_SPI, SPI_NSSInternalSoft_Set);
}


/******************************************************************************
      ����˵����LCDд������
      ������ݣ�dat д�������
      ����ֵ��  ��
******************************************************************************/
void LCD_WR_DATA(u16 dat)
{
	SPI_NSSInternalSoftwareConfig(CW_SPI, SPI_NSSInternalSoft_Reset);
	LCD_Writ_Bus(dat>>8);
	LCD_Writ_Bus(dat);
	SPI_NSSInternalSoftwareConfig(CW_SPI, SPI_NSSInternalSoft_Set);
}


/******************************************************************************
      ����˵����LCDд������
      ������ݣ�dat д�������
      ����ֵ��  ��
******************************************************************************/
void LCD_WR_REG(u8 dat)
{
	LCD_DC_Clr();//д����
	SPI_NSSInternalSoftwareConfig(CW_SPI, SPI_NSSInternalSoft_Reset);
	LCD_Writ_Bus(dat);
	SPI_NSSInternalSoftwareConfig(CW_SPI, SPI_NSSInternalSoft_Set);
	LCD_DC_Set();//д����
}


/******************************************************************************
      ����˵����������ʼ�ͽ�����ַ
      ������ݣ�x1,x2 �����е���ʼ�ͽ�����ַ
                y1,y2 �����е���ʼ�ͽ�����ַ
      ����ֵ��  ��
******************************************************************************/
void LCD_Address_Set(u16 x1,u16 y1,u16 x2,u16 y2)
{
	if(USE_HORIZONTAL==0)
	{
		LCD_WR_REG(0x2a);//�е�ַ����
		LCD_WR_DATA(x1+24);
		LCD_WR_DATA(x2+24);
		LCD_WR_REG(0x2b);//�е�ַ����
		LCD_WR_DATA(y1);
		LCD_WR_DATA(y2);
		LCD_WR_REG(0x2c);//������д
	}
	else if(USE_HORIZONTAL==1)
	{
		LCD_WR_REG(0x2a);//�е�ַ����
		LCD_WR_DATA(x1+24);
		LCD_WR_DATA(x2+24);
		LCD_WR_REG(0x2b);//�е�ַ����
		LCD_WR_DATA(y1);
		LCD_WR_DATA(y2);
		LCD_WR_REG(0x2c);//������д
	}
	else if(USE_HORIZONTAL==2)
	{
		LCD_WR_REG(0x2a);//�е�ַ����
		LCD_WR_DATA(x1);
		LCD_WR_DATA(x2);
		LCD_WR_REG(0x2b);//�е�ַ����
		LCD_WR_DATA(y1+24);
		LCD_WR_DATA(y2+24);
		LCD_WR_REG(0x2c);//������д
	}
	else
	{
		LCD_WR_REG(0x2a);//�е�ַ����
		LCD_WR_DATA(x1);
		LCD_WR_DATA(x2);
		LCD_WR_REG(0x2b);//�е�ַ����
		LCD_WR_DATA(y1+24);
		LCD_WR_DATA(y2+24);
		LCD_WR_REG(0x2c);//������д
	}
}

void LCD_Init(void)
{
	long i;
	
	LCD_GPIO_Init();//��ʼ��GPIO
	
	LCD_RES_Clr();//��λ
	 for(i=0;i<10000;i++);
	LCD_RES_Set();
	 for(i=0;i<10000;i++);
	
	LCD_BLK_Set();//�򿪱���
   for(i=0;i<10000;i++);
	
	LCD_WR_REG(0x11);//Sleep exit 
	 for(i=0;i<200000;i++);               //Delay 120ms 
	LCD_WR_REG(0xB1);     
	LCD_WR_DATA8(0x05);   
	LCD_WR_DATA8(0x3C);   
	LCD_WR_DATA8(0x3C);   

	LCD_WR_REG(0xB2);     
	LCD_WR_DATA8(0x05);   
	LCD_WR_DATA8(0x3C);   
	LCD_WR_DATA8(0x3C);   

	LCD_WR_REG(0xB3);     
	LCD_WR_DATA8(0x05);   
	LCD_WR_DATA8(0x3C);   
	LCD_WR_DATA8(0x3C);   
	LCD_WR_DATA8(0x05);   
	LCD_WR_DATA8(0x3C);   
	LCD_WR_DATA8(0x3C);   

	LCD_WR_REG(0xB4);     //Dot inversion
	LCD_WR_DATA8(0x03);   

	LCD_WR_REG(0xC0);     
	LCD_WR_DATA8(0x0E);   
	LCD_WR_DATA8(0x0E);   
	LCD_WR_DATA8(0x04);   

	LCD_WR_REG(0xC1);     
	LCD_WR_DATA8(0xC5);   

	LCD_WR_REG(0xC2);     
	LCD_WR_DATA8(0x0d);   
	LCD_WR_DATA8(0x00);   

	LCD_WR_REG(0xC3);     
	LCD_WR_DATA8(0x8D);   
	LCD_WR_DATA8(0x2A);   

	LCD_WR_REG(0xC4);     
	LCD_WR_DATA8(0x8D);   
	LCD_WR_DATA8(0xEE);   

	LCD_WR_REG(0xC5);     //VCOM
	LCD_WR_DATA8(0x06); //1D  .06


	LCD_WR_REG(0x36);     //MX, MY, RGB mode
	if(USE_HORIZONTAL==0)LCD_WR_DATA8(0x08);
	else if(USE_HORIZONTAL==1)LCD_WR_DATA8(0xC8);
	else if(USE_HORIZONTAL==2)LCD_WR_DATA8(0x78);
	else LCD_WR_DATA8(0xA8);  

	LCD_WR_REG(0x3A); 
	LCD_WR_DATA8(0x55);
		
	LCD_WR_REG(0xE0);     
	LCD_WR_DATA8(0x0b);   
	LCD_WR_DATA8(0x17);   
	LCD_WR_DATA8(0x0a);   
	LCD_WR_DATA8(0x0d);   
	LCD_WR_DATA8(0x1a);   
	LCD_WR_DATA8(0x19);   
	LCD_WR_DATA8(0x16);   
	LCD_WR_DATA8(0x1d);   
	LCD_WR_DATA8(0x21);   
	LCD_WR_DATA8(0x26);   
	LCD_WR_DATA8(0x37);   
	LCD_WR_DATA8(0x3c);   
	LCD_WR_DATA8(0x00);   
	LCD_WR_DATA8(0x09);   
	LCD_WR_DATA8(0x05);   
	LCD_WR_DATA8(0x10);   

	LCD_WR_REG(0xE1);     
	LCD_WR_DATA8(0x0c);   
	LCD_WR_DATA8(0x19);   
	LCD_WR_DATA8(0x09);   
	LCD_WR_DATA8(0x0d);   
	LCD_WR_DATA8(0x1b);   
	LCD_WR_DATA8(0x19);   
	LCD_WR_DATA8(0x15);   
	LCD_WR_DATA8(0x1d);   
	LCD_WR_DATA8(0x21);   
	LCD_WR_DATA8(0x26);   
	LCD_WR_DATA8(0x39);   
	LCD_WR_DATA8(0x3E);   
	LCD_WR_DATA8(0x00);   
	LCD_WR_DATA8(0x09);   
	LCD_WR_DATA8(0x05);   
	LCD_WR_DATA8(0x10);   
	 
//	delay1ms (120);
 for(i=0;i<200000;i++);
	LCD_WR_REG(0x29);     //Display on
}







