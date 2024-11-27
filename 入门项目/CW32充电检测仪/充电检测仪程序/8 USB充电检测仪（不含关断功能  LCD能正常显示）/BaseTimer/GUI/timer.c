#include "timer.h"

// ��ʱ����ʼ������  
void Timer2_Init(void) { 
		BTIM_TimeBaseInitTypeDef BTIM_TimeBaseInitStruct = {0};

		__SYSCTRL_BTIM123_CLK_ENABLE();	
		
    __disable_irq();
    NVIC_EnableIRQ(BTIM2_IRQn);
    __enable_irq();

		
		BTIM_TimeBaseInitStruct.BTIM_Mode = BTIM_MODE_TIMER;/* ����ģʽ��00����ʱ��ģʽ01��������ģʽ10����������ģʽ11���ſؼ���ģʽ  */
		//48M--> 48000000/3=16000000/50000=320
		BTIM_TimeBaseInitStruct.BTIM_Period = (50000 - 1);/* �����������ڣ�ȡֵ��Χ0x0000 �� 0xFFFF.65535  */
		//320
		BTIM_TimeBaseInitStruct.BTIM_Prescaler = (320 - 1);    // 8��Ƶ /*8��Ƶ, Ԥ����ϵ����ȡֵ��Χ2��n���ݣ�n=0,1,2��15 */
		
		//BTIM������ʱ����ʼ��
		BTIM_TimeBaseInit(CW_BTIM2, &BTIM_TimeBaseInitStruct);
		//BTIM_ITConfig(CW_BTIM2, BTIM_IT_UPDATE, ENABLE);   // ʹ��BTIMx������ж�
		BTIM_Cmd(CW_BTIM2, ENABLE);
}  

void Timer2_Enable(FunctionalState NewState)
{
		BTIM_ITConfig(CW_BTIM2, BTIM_IT_UPDATE, NewState);   // ʹ��BTIMx������ж�
}

//1s���һ��1hz
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



