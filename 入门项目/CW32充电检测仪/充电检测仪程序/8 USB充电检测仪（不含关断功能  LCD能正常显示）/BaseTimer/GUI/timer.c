#include "timer.h"

// 定时器初始化函数  
void Timer2_Init(void) { 
		BTIM_TimeBaseInitTypeDef BTIM_TimeBaseInitStruct = {0};

		__SYSCTRL_BTIM123_CLK_ENABLE();	
		
    __disable_irq();
    NVIC_EnableIRQ(BTIM2_IRQn);
    __enable_irq();

		
		BTIM_TimeBaseInitStruct.BTIM_Mode = BTIM_MODE_TIMER;/* 工作模式，00：定时器模式01：计数器模式10：触发计数模式11：门控计数模式  */
		//48M--> 48000000/3=16000000/50000=320
		BTIM_TimeBaseInitStruct.BTIM_Period = (50000 - 1);/* 计数重载周期，取值范围0x0000 到 0xFFFF.65535  */
		//320
		BTIM_TimeBaseInitStruct.BTIM_Prescaler = (320 - 1);    // 8分频 /*8分频, 预分配系数，取值范围2的n次幂，n=0,1,2…15 */
		
		//BTIM基本定时器初始化
		BTIM_TimeBaseInit(CW_BTIM2, &BTIM_TimeBaseInitStruct);
		//BTIM_ITConfig(CW_BTIM2, BTIM_IT_UPDATE, ENABLE);   // 使能BTIMx的溢出中断
		BTIM_Cmd(CW_BTIM2, ENABLE);
}  

void Timer2_Enable(FunctionalState NewState)
{
		BTIM_ITConfig(CW_BTIM2, BTIM_IT_UPDATE, NewState);   // 使能BTIMx的溢出中断
}

//1s溢出一次1hz
void BTIM2_IRQHandler(void)
{ 
	extern unsigned int timer_Num;
		
	/* USER CODE BEGIN */
	if (BTIM_GetITStatus(CW_BTIM2, BTIM_IT_UPDATE))
	{
		BTIM_ClearITPendingBit(CW_BTIM2, BTIM_IT_UPDATE);
		timer_Num++;
	}
	/* USER CODE END */
}



