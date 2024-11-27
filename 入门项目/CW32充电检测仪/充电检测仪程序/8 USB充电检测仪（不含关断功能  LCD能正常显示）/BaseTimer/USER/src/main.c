/**
 * @file main.c
 * @author WHXY
 * @brief
 * @version 0.1
 * @date 2022-7-12
 *
 * @copyright Copyright (c) 2021
 */
/*******************************************************************************
*
* 代码许可和免责信息
* 武汉芯源半导体有限公司授予您使用所有编程代码示例的非专属的版权许可，您可以由此
* 生成根据您的特定需要而定制的相似功能。根据不能被排除的任何法定保证，武汉芯源半
* 导体有限公司及其程序开发商和供应商对程序或技术支持（如果有）不提供任何明示或暗
* 含的保证或条件，包括但不限于暗含的有关适销性、适用于某种特定用途和非侵权的保证
* 或条件。
* 无论何种情形，武汉芯源半导体有限公司及其程序开发商或供应商均不对下列各项负责，
* 即使被告知其发生的可能性时，也是如此：数据的丢失或损坏；直接的、特别的、附带的
* 或间接的损害，或任何后果性经济损害；或利润、业务、收入、商誉或预期可节省金额的
* 损失。
* 某些司法辖区不允许对直接的、附带的或后果性的损害有任何的排除或限制，因此某些或
* 全部上述排除或限制可能并不适用于您。
*
*******************************************************************************/

/******************************************************************************
 * Include files
 ******************************************************************************/
#include "main.h"
#include "seg.h"
#include "adc.h"
#include "flash.h"
#include "cw32l010_systick.h"
#include "lcd.h"
#include "lcd_init.h"
#include "logo.h"
#include "timer.h"
#include "ntc.h"
#include <stdio.h>


#define CBR1 10    //43
#define CBR2 82    //220
//插拔的IO ADC 分压比为220K：43K

#define KEY_0  GPIO_ReadPin(CW_GPIOB, GPIO_PIN_0)
#define KEY_1  GPIO_ReadPin(CW_GPIOB, GPIO_PIN_1)

extern uint16_t Volt_Buffer[ADC_SAMPLE_SIZE];
extern uint16_t Curr_Buffer[ADC_SAMPLE_SIZE];
extern uint16_t V12V_Buffer[ADC_SAMPLE_SIZE];
extern uint16_t CBV1_Buffer[ADC_SAMPLE_SIZE];
extern uint16_t CBV2_Buffer[ADC_SAMPLE_SIZE];
extern uint16_t IPV1_Buffer[ADC_SAMPLE_SIZE];
extern uint16_t NTC_Buffer[ADC_SAMPLE_SIZE];
uint16_t V_Buffer,I_Buffer,V12_Buffer,CB1_Buffer,CB2_Buffer;


unsigned char kecou=0;

unsigned char Mode=0;
//Mode==0显示电压  =1显示电流  4充电时闪  // 后面未用  5修改电流=2待机 3充满 

unsigned int Vvalue=0,Ivalue=0;

unsigned int tcount=0;
unsigned int tcountD=0;



unsigned char CMflag=0;
void Brush(void);

unsigned char VSEGONflag=0,ISEGONflag=0; //V段是否亮


unsigned char BrushFlag=0;
unsigned int timecount=0;


unsigned char flag=0;
unsigned char datad,Dis_Value;
unsigned char comb=0,segb=0;
unsigned int adsampleflag=0;
unsigned int IDIN=0;          	//1.2V参考电压值
unsigned int Ipiancha=0;

char str[20];//字符串缓冲
unsigned int lcd_time=0;
unsigned char Screen = 1;//屏幕显示状态
unsigned char Screen_Lock = 1;//屏幕锁
unsigned char timer_Temp = 0;//充电时间缓存
unsigned char timer_Lock = 0;//充电时间锁
unsigned int timer_Num = 0;//计时器缓存
unsigned short NTC_Num = 0;//温度


void SYSCTRL_Configuration(void)
{    
    SYSCTRL_HSI_Enable(SYSCTRL_HSIOSC_DIV3); //48M	
	  REGBITS_SET(CW_SYSCTRL->AHBEN, (0x5A5A0000 |bv1)); //flash
	
	   IDIN=*((uint16_t*)0x001007D2);
}

void BTIM1_init(void)
{	  	
	  BTIM_TimeBaseInitTypeDef BTIM_TimeBaseInitStruct = {0};
   
		__SYSCTRL_BTIM123_CLK_ENABLE();	
		
    __disable_irq();
    NVIC_EnableIRQ(BTIM1_IRQn);
    __enable_irq();
	
	  BTIM_TimeBaseInitStruct.BTIM_Mode = BTIM_MODE_TIMER; //400us
    BTIM_TimeBaseInitStruct.BTIM_Period =500; //500us
    BTIM_TimeBaseInitStruct.BTIM_Prescaler =16;    // 
    BTIM_TimeBaseInit(CW_BTIM1, &BTIM_TimeBaseInitStruct);
		
    BTIM_ITConfig(CW_BTIM1, BTIM_IT_UPDATE, ENABLE);
    BTIM_Cmd(CW_BTIM1, ENABLE);
}

void GPIO_Configuration(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0}; 
	
    __SYSCTRL_GPIOB_CLK_ENABLE();	
		
    GPIO_InitStruct.IT = GPIO_IT_NONE;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT_PULLUP; //KEY按键(外设)
    GPIO_InitStruct.Pins = GPIO_PIN_0;
    GPIO_Init(CW_GPIOB, &GPIO_InitStruct);			
		
    GPIO_InitStruct.IT = GPIO_IT_NONE;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT_PULLUP; //KEY按键
    GPIO_InitStruct.Pins = GPIO_PIN_1;
    GPIO_Init(CW_GPIOB, &GPIO_InitStruct);	
		
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP; //KEY按键
    GPIO_InitStruct.Pins = GPIO_PIN_3;
    GPIO_Init(CW_GPIOB, &GPIO_InitStruct);	
		
		GPIO_WritePin(CW_GPIOB,GPIO_PIN_3,GPIO_Pin_SET); //充电口打开充电  
}
 
unsigned char st=0;
void Brush(void)
{		   
//	 if(Mode==2)
//   {
//		  Seg_Reg[0]=10;
//		  Seg_Reg[1]=10;
//	   // Seg_Reg[2]=16;
//	    Seg_Reg[2]=10;
//		 VSEGONflag=0;
//	 }
//	else if(Mode==4)
//   {		 
//		  Seg_Reg[0]=10;
//		  Seg_Reg[1]=10;
//	    Seg_Reg[2]=10;
//		 VSEGONflag=0;
//	 }
//   else if(Mode==1)
//		{ Seg_Reg[0]=Ivalue/100;
//		  Seg_Reg[1]=Ivalue/10%10;
//	    Seg_Reg[2]=Ivalue%10;	
//			VSEGONflag=0;
//	  }
//	 else if(Mode==3)
//		{ Seg_Reg[0]=0;
//		  Seg_Reg[1]=0;
//	    Seg_Reg[2]=0;	
//			VSEGONflag=0;
//	  }	
//   else
//   {
//		  if(Vvalue>=100)Seg_Reg[0]=Vvalue/100;
//		  else Seg_Reg[0]=10;
//		  Seg_Reg[1]=Vvalue%100/10;
//	    Seg_Reg[2]=Vvalue%10;
//		 VSEGONflag=1;
//	 }	 
}

void Volt_Cal(void);
uint32_t Mean_Value_Filter(uint16_t *value, uint32_t size) ;    //均值滤波

/**
 * @brief
 *
 * @return int32_t
 */
int32_t main(void)
{	  
	/* System Clocks Configuration */
	unsigned int i=0;
	unsigned char bx=0;
 
	SYSCTRL_Configuration();
  InitTick(8000000);
	GPIO_Configuration();
	ADC_init();
 
	tcount=0;
	tcountD=0;
	BTIM1_init();	
	while(i<100)
	{
		if(adsampleflag==1)
		{
			adsampleflag=0;
			Get_ADC_Value();
			i++;
		}
	} 
	Volt_Cal();
	Ipiancha=I_Buffer;		 
			
	Mode=1;
	Brush();
	
	LCD_Init();//LCD初始化
	LCD_Fill(0, 0, LCD_W, LCD_H, BLACK); //清屏 
	LCD_ShowPicture(0,0,160,80,gImage_logo1);//logo	
	FirmwareDelay(1000*1000);
	LCD_Fill(0, 0, LCD_W, LCD_H, BLACK); //清屏 
	
	Timer2_Init();
	Timer2_Enable(DISABLE);//计时器开断	
	
	
	while(1)
	{
		if(adsampleflag==1)
		{
			adsampleflag=0;
			Get_ADC_Value();
		}
						 
		if(KEY_0==1)
		{
			bx=0;
			kecou=0;
		}
		else if(bx==0&&kecou>=10)//功能按键
		{						 
			if(KEY_0==0)
			{
				bx=1;
				if(++Screen > 3)Screen=1;
				
				if(Screen==1)Screen_Lock=1;
				else if(Screen==2)Screen_Lock=2;
				else if(Screen==3)Screen_Lock=3;
			}
		}
		
		if(tcountD>=200)
		{
			Volt_Cal();	
			Brush();
			st=1-st;
			tcountD=0;
					
			if(Ivalue > 0)timer_Temp=0;
			else timer_Temp++;
			if(timer_Lock==1 && timer_Temp > 2)
			{									
				timer_Lock=0;
				timer_Temp=0;
				timer_Num=0;
				Timer2_Enable(DISABLE);//计时器开断		
			}
			else if(timer_Lock==0 && Ivalue > 0)
			{
				timer_Lock=1;
				timer_Num=0;
				Timer2_Enable(ENABLE);//计时器开断						
			}
		}
			
		if(Screen_Lock==1)
		{
			Screen_Lock=0;							
			
			LCD_Fill(0, 0, 60, 80, BLACK);
			Show_Chinese(2,2,0,12,BLUE,BLACK,0);
			Show_Chinese(14,2,1,12,BLUE,BLACK,0);
			Show_Chinese(26,2,2,12,BLUE,BLACK,0);	
			Show_Chinese(38,2,3,12,BLUE,BLACK,0);	
			
			Show_Chinese(14,42,4,12,RED,BLACK,0);
			Show_Chinese(26,42,5,12,RED,BLACK,0);
			
			LCD_Fill(2+58, 0, 160, 27, ORANGE);
			LCD_Fill(2+58, 20, 160, 54, SGREEN);
			LCD_Fill(2+58, 40, 160, 80, GRAYBLUE);
			LCD_Fill(2+58, 60, 160, 80, BRRED);			
			Show_Chinese(5+58,2,0,16,WHITE,ORANGE,0);
			Show_Chinese(20+58,2,2,16,WHITE,ORANGE,0);			
			Show_Chinese(5+58,22,0,16,WHITE,SGREEN,0);
			Show_Chinese(20+58,22,1,16,WHITE,SGREEN,0);			
			Show_Chinese(5+58,42,3,16,WHITE,GRAYBLUE,0);
			Show_Chinese(20+58,42,4,16,WHITE,GRAYBLUE,0);				
			Show_Chinese(5+58,62,0,16,WHITE,BRRED,0);
			Show_Chinese(20+58,62,5,16,WHITE,BRRED,0);		
		}		
		else if(Screen_Lock==2)
		{
			Screen_Lock=0;			
	
			LCD_Fill(0, 0, LCD_W, LCD_H, BLACK); //清屏 	
			
			Show_Chinese(5,0,0,24,SGREEN,BLACK,0);
			Show_Chinese(30,0,1,24,SGREEN,BLACK,0);
			Show_Chinese(5,27,0,24,GRAYBLUE,BLACK,0);
			Show_Chinese(30,27,2,24,GRAYBLUE,BLACK,0);
			Show_Chinese(5,54,3,24,BRRED,BLACK,0);
			Show_Chinese(30,54,4,24,BRRED,BLACK,0);	
		}
		else if(Screen_Lock==3)
		{
			Screen_Lock=0;
			LCD_Fill(0, 0, LCD_W, LCD_H, BLACK); //息屏
			LCD_DrawPoint(150,70,WHITE);
			Draw_Circle(150,70,1,WHITE);
			Draw_Circle(150,70,2,WHITE);
			Draw_Circle(150,70,3,WHITE);
		}				
		
		if(Screen==1)
		{							
			if(lcd_time>=200)
			{
				lcd_time=0;						
				//Ntc = GetNTCTable_Temp(NTC_Num);
				sprintf(str,"%02d:%02d:%02d",timer_Num/3600,timer_Num%3600/60,timer_Num%60);
				LCD_ShowString(2,22,str,BLUE,BLACK,12, 0);
				sprintf(str,"%.1f",(float) GetNTCTable_Temp(NTC_Num)/10);
				LCD_ShowString(2,62,str,RED,BLACK,16, 0);	
				LCD_ShowString(38,60,"o",RED,BLACK,12, 0);
				LCD_ShowString(45,62,"C",RED,BLACK,16, 0);
				
				sprintf(str,(Vvalue >= 1000)?" %.1f V":" %.2f V",(float) Vvalue/100);
				LCD_ShowString(35+58,2,str,WHITE,ORANGE,16, 0);	
				sprintf(str,(Ivalue >= 1000)?" %.1f A":" %.2f A",(float) Ivalue/100);
				LCD_ShowString(35+58,22,str,WHITE,SGREEN,16, 0);	
				sprintf(str,(Ivalue*Vvalue >= 100000)?" %.1f W":" %.2f W",(float) (Ivalue*Vvalue)/10000);
				LCD_ShowString(35+58,42,str,WHITE,GRAYBLUE,16, 0);
				sprintf(str,(Ivalue*Vvalue*timer_Num/3600 >= 100000)?" %.1f Wh":" %.2f Wh",(float) (Ivalue*Vvalue)/10000*timer_Num/3600);
				LCD_ShowString(35+58,62,str,WHITE,BRRED,16, 0);
			}	
		}	
		else if(Screen==2)
		{			
			if(lcd_time>=200)
			{
				lcd_time=0;		
				sprintf(str,(Ivalue >= 1000)?": %.1f A":": %.2f A",(float) Ivalue/100);
				LCD_ShowString(55,0,str,SGREEN,BLACK,24, 0);
				sprintf(str,(Vvalue >= 1000)?": %.1f V":": %.2f V",(float) Vvalue/100);
				LCD_ShowString(55,27,str,GRAYBLUE,BLACK,24, 0);			
				sprintf(str,(Ivalue*Vvalue >= 100000)?": %.1f W":": %.2f W",(float) (Ivalue*Vvalue)/10000);
				LCD_ShowString(55,54,str,BRRED,BLACK,24, 0);		
			}
		}
		else if(Screen==3)
		{
			if(lcd_time<200)
			{
				LCD_DrawPoint(150,70,WHITE);
				Draw_Circle(150,70,1,WHITE);
				Draw_Circle(150,70,2,WHITE);
				Draw_Circle(150,70,3,WHITE);
			}			
			else if(lcd_time>200 && lcd_time<400)
			{
				LCD_Fill(140, 60, 160, 80, BLACK);
			}
			else if(lcd_time>=400)
			{
				lcd_time=0;							
			}	
		}
		
	}
}



uint32_t Mean_Value_Filter(uint16_t *value, uint32_t size)     //均值滤波
{
    uint32_t sum = 0;
    uint16_t max = 0;
    uint16_t min = 0xffff;
    int      i;

    for(i = 0; i < size; i++)
    {
        sum += value[i];
        if(value[i] > max)
        {
            max = value[i];
        }
        if(value[i] < min)
        {
            min = value[i];
        }
    }
    sum -= max + min;
    sum  = sum / (size - 2);
    return sum;
}

void Volt_Cal(void)
{ 	
	float t,KT1;
	
	V_Buffer = Mean_Value_Filter(Volt_Buffer,ADC_SAMPLE_SIZE);//使用均值滤波
	I_Buffer = Mean_Value_Filter(Curr_Buffer,ADC_SAMPLE_SIZE); //使用均值滤波
	V12_Buffer = Mean_Value_Filter(V12V_Buffer,ADC_SAMPLE_SIZE); //使用均值滤波  
  Ipiancha = Mean_Value_Filter(IPV1_Buffer,ADC_SAMPLE_SIZE); //使用均值滤波 
	NTC_Num = Mean_Value_Filter(NTC_Buffer,ADC_SAMPLE_SIZE); //使用均值滤波

	/*
	V_Buffer：基准电压AD 678
	V12_Buffer：1.2V基准AD 1214
	IDIN：1.2V电压值	1201
	
	6.190
	5.118
	*/
	
	
	t=V_Buffer;
	
	// 1: 1.2V基准; 0: 3.3V基准
	#define Rvolt 0
	
	#if Rvolt
		V_Buffer=t/V12_Buffer*IDIN /10/R1*(R1+R2);  //1.2V作参考进行运算 	/
//		V_Buffer=(3300*IDIN*t)/(V12_Buffer*4095) /10/R1*(R1+R2);  //1.2V作参考进行运算 	/
//		Vvalue=V_Buffer; //1.2V 偏差 -102
		Vvalue=(V_Buffer+5)/10;		//利用整型特性
//	if(V_Buffer%10>=5)Vvalue=V_Buffer/10+1;
//	else Vvalue=V_Buffer/10;	
		Vvalue*=10;
	#else
		V_Buffer=(t/4095*3300/R1*(R1+R2)+5)/10;  //3.3V作参考进行运算 	/
		Vvalue=V_Buffer+7; //3.3V 偏差 +7
	#endif
	
	
//	if(I_Buffer>Ipiancha)t=I_Buffer-Ipiancha;
//	else t=Ipiancha-I_Buffer;  //减去偏置
	t=(I_Buffer>Ipiancha)?(I_Buffer-Ipiancha):(Ipiancha-I_Buffer);
	#if Rvolt
		KT1=V12_Buffer;
		KT1=KT1*0.0017; //8mA对应的 0.008*0.005*50/1.2=0.0016666...
		//if(t<KT1)t=0;	 //<8MA,认为0
		t=t/V12_Buffer*IDIN/10*4;  //1V/50倍/0.005R=4 	
		if(t<4)t=0;
	#else
		t=t/4095*3300/10*4; 	
		if(t>7)t-=7;
		else t=0;
//		if(t<7)t=0;
	#endif
	Ivalue=t;
}	


unsigned char VSEGdisp=0;
void BTIM1_IRQHandler(void)
{//200us
	static unsigned int timecount2=0,timecount=0;
	
	
	if (BTIM_GetITStatus(CW_BTIM1, BTIM_IT_UPDATE))
    {
        BTIM_ClearITPendingBit(CW_BTIM1, BTIM_IT_UPDATE);	     						
			
			      timecount++;
						if(timecount>=10)
						{
							  timecount=0;
								tcount++;
								tcountD++;	
								lcd_time++;
								kecou++;	
						}						
						
						timecount2++;
						if(timecount2>=2)
						{
							timecount2=0;
							adsampleflag=1; //1MS采样一个AD
						}
						
//						if(VSEGdisp==1){segb=0;VSEGdisp=0;}
//						else	segb++;
//						if(segb>=8)  //8个段循环
//						{
//							segb=0;						
//							comb++;
//							if(comb>=3)
//								{
//									comb=0;
//									VSEGdisp=1;
//							  }								//6个位循环	
//						}
//				 	  
//					 	Close_ALL(); 	
//						if(VSEGdisp==1)
//							{if(VSEGONflag==1)Display_SEGV();}
//						else
//						{
//								Dis_Value = Seg_Table[Seg_Reg[comb]];	  					
//								if(((Dis_Value >> segb) & 0x01) ==0);  //当前段不显示
//								else
//								{
//									 if(segb==0)
//										 Display_SEGA(comb);
//									 else if(segb==1)
//										 Display_SEGB(comb);
//									 else if(segb==2)
//										 Display_SEGC(comb);
//									 else if(segb==3)
//										 Display_SEGD(comb);
//									 else if(segb==4)
//										 Display_SEGE(comb);
//									 else if(segb==5)
//										 Display_SEGF(comb);
//									 else if(segb==6)
//										 Display_SEGG(comb);
//									 else if(segb==7)
//										 Display_SEGDP(comb); 
//								}		
//							}
//						
//						if(segb==7)	
//						{	
//								if(comb==1&&Mode==0)Display_SEGDP(1); //dp
//								else if(comb==0&&(Mode==1||Mode==3))Display_SEGDP(0);
//								else	if(comb==2&&(Mode==2))Display_SEGDP(1); //dp
//								else if(comb==1&&Mode==4&&st==1)Display_SEGDP(1); //dp
//								else if(comb==2&&Mode==1)Display_SEGDP(2);
//							}
		}	
}
 

#ifdef USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
    /* USER CODE BEGIN 6 */
    /* User can add his own implementation to report the file name and line number,
       tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
    /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
