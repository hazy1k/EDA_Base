#include "seg.h"
#include "main.h"

//unsigned char Seg_Table[21] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x6f,
	//0xbf, 0x86, 0xdb, 0xcf, 0xe6, 0xed, 0xfd, 0x87, 0xff, 0xef,0xF7};// 0xF7:A.

	
unsigned char Seg_Table[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0,0X79,0X5C,0X38,0X3E,0X77,0x80};

unsigned char Seg_Reg[3] ={0,0,0};

#define CW_GPIO6 CW_GPIOB
#define CW_GPIO5 CW_GPIOB
#define CW_GPIO4 CW_GPIOB
#define CW_GPIO3 CW_GPIOA
#define CW_GPIO2 CW_GPIOA
#define CW_GPIO1 CW_GPIOA

#define CW_GPIO_PIN6 GPIO_PIN_6
#define CW_GPIO_PIN5 GPIO_PIN_4
#define CW_GPIO_PIN4 GPIO_PIN_5
#define CW_GPIO_PIN3 GPIO_PIN_6
#define CW_GPIO_PIN2 GPIO_PIN_5
#define CW_GPIO_PIN1 GPIO_PIN_4

#define  CW_GPIO_PIN1H  GPIO_WritePin(CW_GPIO1,CW_GPIO_PIN1,GPIO_Pin_SET)  
#define  CW_GPIO_PIN1L  GPIO_WritePin(CW_GPIO1,CW_GPIO_PIN1,GPIO_Pin_RESET)  
#define  CW_GPIO_PIN2H  GPIO_WritePin(CW_GPIO2,CW_GPIO_PIN2,GPIO_Pin_SET)   
#define  CW_GPIO_PIN2L  GPIO_WritePin(CW_GPIO2,CW_GPIO_PIN2,GPIO_Pin_RESET) 
#define  CW_GPIO_PIN3H  GPIO_WritePin(CW_GPIO3,CW_GPIO_PIN3,GPIO_Pin_SET)    
#define  CW_GPIO_PIN3L  GPIO_WritePin(CW_GPIO3,CW_GPIO_PIN3,GPIO_Pin_RESET)  
#define  CW_GPIO_PIN4H  GPIO_WritePin(CW_GPIO4,CW_GPIO_PIN4,GPIO_Pin_SET)    
#define  CW_GPIO_PIN4L  GPIO_WritePin(CW_GPIO4,CW_GPIO_PIN4,GPIO_Pin_RESET)  
#define  CW_GPIO_PIN5H  GPIO_WritePin(CW_GPIO5,CW_GPIO_PIN5,GPIO_Pin_SET)    
#define  CW_GPIO_PIN5L  GPIO_WritePin(CW_GPIO5,CW_GPIO_PIN5,GPIO_Pin_RESET)  
#define  CW_GPIO_PIN6H  GPIO_WritePin(CW_GPIO6,CW_GPIO_PIN6,GPIO_Pin_SET)    
#define  CW_GPIO_PIN6L  GPIO_WritePin(CW_GPIO6,CW_GPIO_PIN6,GPIO_Pin_RESET)     
 

void Seg_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct; 
	//打开GPIO时钟
	 REGBITS_SET(CW_SYSCTRL->AHBEN, SYSCTRL_AHBEN_GPIOA_Msk);
	 REGBITS_SET(CW_SYSCTRL->AHBEN, SYSCTRL_AHBEN_GPIOB_Msk);
	
	
	GPIO_InitStruct.Pins = GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_4;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.IT = GPIO_IT_NONE;
  GPIO_Init(CW_GPIOA, &GPIO_InitStruct);
  GPIO_Init(CW_GPIOB, &GPIO_InitStruct);	 
	
	
	GPIO_InitStruct.Pins = GPIO_PIN_0|GPIO_PIN_1;  //a0 a1配置为模拟输入
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.IT = GPIO_IT_NONE;
  GPIO_Init(CW_GPIOA, &GPIO_InitStruct);
}

void Close_ALL(void)
{
  GPIO_InitTypeDef GPIO_InitStruct; 
		
	GPIO_InitStruct.Pins =  GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.IT = GPIO_IT_NONE; 
  GPIO_Init(CW_GPIOA, &GPIO_InitStruct);  
  GPIO_Init(CW_GPIOB, &GPIO_InitStruct);  
}

void Display_SEGA(unsigned char segbit)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.IT = GPIO_IT_NONE; 
	 if(segbit==0)
		{  					GPIO_InitStruct.Pins = CW_GPIO_PIN2;  
								GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;  
								GPIO_Init(CW_GPIO2, &GPIO_InitStruct);	
			
								GPIO_InitStruct.Pins = CW_GPIO_PIN1;   
								GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;
								GPIO_Init(CW_GPIO1, &GPIO_InitStruct);
                CW_GPIO_PIN2H;CW_GPIO_PIN1L;
		}
		else if(segbit==1)
		{  					GPIO_InitStruct.Pins = CW_GPIO_PIN2;  
								GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD; 
								GPIO_Init(CW_GPIO2, &GPIO_InitStruct);
			
								GPIO_InitStruct.Pins = CW_GPIO_PIN4;  
								GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
								GPIO_Init(CW_GPIO4, &GPIO_InitStruct);
                CW_GPIO_PIN4H;CW_GPIO_PIN2L;
		}
		else if(segbit==2)
		{  					GPIO_InitStruct.Pins = CW_GPIO_PIN6;  
								GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
								GPIO_Init(CW_GPIO6, &GPIO_InitStruct);
								GPIO_InitStruct.Pins = CW_GPIO_PIN3;  
								GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD; 
								GPIO_Init(CW_GPIO3, &GPIO_InitStruct);
                CW_GPIO_PIN6H;CW_GPIO_PIN3L;
		}
}

void Display_SEGB(unsigned char segbit)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	 if(segbit==0)
		{  					GPIO_InitStruct.Pins = CW_GPIO_PIN1;  
								GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;
								GPIO_Init(CW_GPIO1, &GPIO_InitStruct);
								GPIO_InitStruct.Pins = CW_GPIO_PIN3;   
								GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
								GPIO_Init(CW_GPIO3, &GPIO_InitStruct);
                CW_GPIO_PIN3H;CW_GPIO_PIN1L;
		}
		else if(segbit==1)
		{  					GPIO_InitStruct.Pins = CW_GPIO_PIN5;   
								GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
								GPIO_Init(CW_GPIO5, &GPIO_InitStruct);
								GPIO_InitStruct.Pins = CW_GPIO_PIN2;  
								GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;
								GPIO_Init(CW_GPIO2, &GPIO_InitStruct);								
                CW_GPIO_PIN5H;CW_GPIO_PIN2L;
		}
		else if(segbit==2)
		{  					GPIO_InitStruct.Pins = CW_GPIO_PIN1;  
								GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
								GPIO_Init(CW_GPIO1, &GPIO_InitStruct);
								GPIO_InitStruct.Pins = CW_GPIO_PIN4;   
								GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;
								GPIO_Init(CW_GPIO4, &GPIO_InitStruct);
                CW_GPIO_PIN1H;CW_GPIO_PIN4L;
		}
}

void Display_SEGC(unsigned char segbit)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	 if(segbit==0)
		{  					GPIO_InitStruct.Pins = CW_GPIO_PIN1;  
								GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;
								GPIO_Init(CW_GPIO1, &GPIO_InitStruct);
								GPIO_InitStruct.Pins = CW_GPIO_PIN4;   
								GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
								GPIO_Init(CW_GPIO4, &GPIO_InitStruct);
                CW_GPIO_PIN4H;CW_GPIO_PIN1L;
		}
		else if(segbit==1)
		{  					GPIO_InitStruct.Pins = CW_GPIO_PIN6;   
								GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
								GPIO_Init(CW_GPIO6, &GPIO_InitStruct);
                GPIO_InitStruct.Pins = CW_GPIO_PIN2;  
								GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;
								GPIO_Init(CW_GPIO2, &GPIO_InitStruct);
								CW_GPIO_PIN6H;CW_GPIO_PIN2L;
		}
		else if(segbit==2)
		{  					GPIO_InitStruct.Pins = CW_GPIO_PIN2;  
								GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
								GPIO_Init(CW_GPIO2, &GPIO_InitStruct);
								GPIO_InitStruct.Pins = CW_GPIO_PIN4;  
								GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD; 
								GPIO_Init(CW_GPIO4, &GPIO_InitStruct);
                CW_GPIO_PIN2H;CW_GPIO_PIN4L;
		}
}

void Display_SEGD(unsigned char segbit)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	 if(segbit==0)
		{  					GPIO_InitStruct.Pins = CW_GPIO_PIN1;  
								GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;
								GPIO_Init(CW_GPIO1, &GPIO_InitStruct);
								GPIO_InitStruct.Pins = CW_GPIO_PIN5;   
								GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP; 
								GPIO_Init(CW_GPIO5, &GPIO_InitStruct);
                CW_GPIO_PIN5H;CW_GPIO_PIN1L;
		}
		else if(segbit==1)
		{  		
			          GPIO_InitStruct.Pins = CW_GPIO_PIN3;  
								GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD; 
								GPIO_Init(CW_GPIO3, &GPIO_InitStruct);
								GPIO_InitStruct.Pins = CW_GPIO_PIN1;  
								GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP; 
								GPIO_Init(CW_GPIO1, &GPIO_InitStruct);
                CW_GPIO_PIN1H;CW_GPIO_PIN3L;
		}
		else if(segbit==2)
		{  					GPIO_InitStruct.Pins = CW_GPIO_PIN5;  
								GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
								GPIO_Init(CW_GPIO5, &GPIO_InitStruct);
								GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD; 
								GPIO_InitStruct.Pins = CW_GPIO_PIN4;   
								GPIO_Init(CW_GPIO4, &GPIO_InitStruct);
                CW_GPIO_PIN5H;CW_GPIO_PIN4L;
		}
}

void Display_SEGE(unsigned char segbit)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.IT = GPIO_IT_NONE; 
	 if(segbit==0)
		{  					GPIO_InitStruct.Pins = CW_GPIO_PIN1;  
								GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;
								GPIO_Init(CW_GPIO1, &GPIO_InitStruct);
								GPIO_InitStruct.Pins = CW_GPIO_PIN6;  
								GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;   
								GPIO_Init(CW_GPIO6, &GPIO_InitStruct);
                CW_GPIO_PIN6H;CW_GPIO_PIN1L;
		}
		else if(segbit==1)
		{  					
			          GPIO_InitStruct.Pins = CW_GPIO_PIN2;   
								GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
								GPIO_Init(CW_GPIO2, &GPIO_InitStruct);
			
								GPIO_InitStruct.Pins = CW_GPIO_PIN3;  
								GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;  
								GPIO_Init(CW_GPIO3, &GPIO_InitStruct);
								CW_GPIO_PIN2H;CW_GPIO_PIN3L;
		}
		else if(segbit==2)
		{  					GPIO_InitStruct.Pins = CW_GPIO_PIN4;  
								GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
								GPIO_Init(CW_GPIO4, &GPIO_InitStruct);
								GPIO_InitStruct.Pins = CW_GPIO_PIN5;   
								GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;
								GPIO_Init(CW_GPIO5, &GPIO_InitStruct);
                CW_GPIO_PIN4H;CW_GPIO_PIN5L;
		}
}

void Display_SEGF(unsigned char segbit)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	 if(segbit==0)
		{  					GPIO_InitStruct.Pins = CW_GPIO_PIN1;  
								GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
								GPIO_Init(CW_GPIO1, &GPIO_InitStruct);
								GPIO_InitStruct.Pins = CW_GPIO_PIN2; 
								GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD; 
								GPIO_Init(CW_GPIO2, &GPIO_InitStruct);
                CW_GPIO_PIN1H;CW_GPIO_PIN2L;
		}
		else if(segbit==1)
		{  					GPIO_InitStruct.Pins = CW_GPIO_PIN4;   
								GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
								GPIO_Init(CW_GPIO4, &GPIO_InitStruct);
                GPIO_InitStruct.Pins = CW_GPIO_PIN3;  
								GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;
								GPIO_Init(CW_GPIO3, &GPIO_InitStruct);
								CW_GPIO_PIN4H;CW_GPIO_PIN3L;
		}
		else if(segbit==2)
		{  					GPIO_InitStruct.Pins = CW_GPIO_PIN6;  
								GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
								GPIO_Init(CW_GPIO6, &GPIO_InitStruct);
								GPIO_InitStruct.Pins = CW_GPIO_PIN4;  
								GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD; 
								GPIO_Init(CW_GPIO4, &GPIO_InitStruct);
                CW_GPIO_PIN6H;CW_GPIO_PIN4L;
		}
}

void Display_SEGG(unsigned char segbit)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	 if(segbit==0)
		{  					GPIO_InitStruct.Pins = CW_GPIO_PIN3;  
								GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
								GPIO_Init(CW_GPIO3, &GPIO_InitStruct);
								GPIO_InitStruct.Pins = CW_GPIO_PIN2;   
								GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD; 
								GPIO_Init(CW_GPIO2, &GPIO_InitStruct);
                CW_GPIO_PIN3H;CW_GPIO_PIN2L;
		}
		else if(segbit==1)
		{  					GPIO_InitStruct.Pins = CW_GPIO_PIN5;   
								GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
								GPIO_Init(CW_GPIO5, &GPIO_InitStruct);
                GPIO_InitStruct.Pins = CW_GPIO_PIN3;  
								GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD; 
								GPIO_Init(CW_GPIO3, &GPIO_InitStruct);
								CW_GPIO_PIN5H;CW_GPIO_PIN3L;
		}
		else if(segbit==2)
		{  					GPIO_InitStruct.Pins = CW_GPIO_PIN1;  
								GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
								GPIO_Init(CW_GPIO1, &GPIO_InitStruct);
								GPIO_InitStruct.Pins = CW_GPIO_PIN5;   
								GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD; 
								GPIO_Init(CW_GPIO5, &GPIO_InitStruct);
                CW_GPIO_PIN1H;CW_GPIO_PIN5L;
		}
}

void Display_SEGDP(unsigned char segbit)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	 if(segbit==0)
		{  					GPIO_InitStruct.Pins = CW_GPIO_PIN3;  
								GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
								GPIO_Init(CW_GPIO3, &GPIO_InitStruct);
								GPIO_InitStruct.Pins = CW_GPIO_PIN4;  
								GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD; 
								GPIO_Init(CW_GPIO4, &GPIO_InitStruct);
                CW_GPIO_PIN3H;CW_GPIO_PIN4L;
		}
		else if(segbit==1)
		{  					GPIO_InitStruct.Pins = CW_GPIO_PIN2;  
								GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP; 
								GPIO_Init(CW_GPIO2, &GPIO_InitStruct);
                GPIO_InitStruct.Pins = CW_GPIO_PIN5;  
								GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD; 
								GPIO_Init(CW_GPIO5, &GPIO_InitStruct);
								CW_GPIO_PIN2H;CW_GPIO_PIN5L;
		}
		else if(segbit==2)
		{  					GPIO_InitStruct.Pins = CW_GPIO_PIN6;  
								GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
								GPIO_Init(CW_GPIO6, &GPIO_InitStruct);
								GPIO_InitStruct.Pins = CW_GPIO_PIN5;  
								GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD; 
								GPIO_Init(CW_GPIO5, &GPIO_InitStruct);
                CW_GPIO_PIN6H;CW_GPIO_PIN5L;
		}
}

void Display_SEGV(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	 					    GPIO_InitStruct.Pins = CW_GPIO_PIN3;  
								GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
								GPIO_Init(CW_GPIO3, &GPIO_InitStruct);
								GPIO_InitStruct.Pins = CW_GPIO_PIN5;  
								GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD; 
								GPIO_Init(CW_GPIO5, &GPIO_InitStruct);
                CW_GPIO_PIN3H;CW_GPIO_PIN5L;
}
extern unsigned char Mode;
void DisplayValue(unsigned int value)
{
	     Seg_Reg[0] = value/100 + 10;// 加dp显示
       Seg_Reg[1] = value%100/10; 
       Seg_Reg[2] = value%10;	
   if(Mode==1)Seg_Reg[2]+=10;
}
