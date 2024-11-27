
#include "ADC.h" 
#include "cw32l010_sysctrl.h"

uint16_t Volt_Buffer[ADC_SAMPLE_SIZE];
uint16_t Curr_Buffer[ADC_SAMPLE_SIZE];
uint16_t V12V_Buffer[ADC_SAMPLE_SIZE];
uint16_t IPV1_Buffer[ADC_SAMPLE_SIZE];
uint16_t CBV2_Buffer[ADC_SAMPLE_SIZE];
uint16_t NTC_Buffer[ADC_SAMPLE_SIZE];
 
void  ADC_init(void)
{
	unsigned int i;
    ADC_InitTypeDef ADC_InitStructure = {0};
	 	
   //打开GPIO时钟
    __SYSCTRL_GPIOA_CLK_ENABLE();
		__SYSCTRL_GPIOB_CLK_ENABLE();
    //打开ADC时钟
    __SYSCTRL_ADC_CLK_ENABLE();

    PB03_ANALOG_ENABLE(); 
    PB04_ANALOG_ENABLE();    
    PB05_ANALOG_ENABLE();
    PB06_ANALOG_ENABLE();    
		REGBITS_SET(CW_ADC->CR, ADC_CR_BGREN_Msk); //使能1.2V BGR
		
    ADC_InitStructure.ADC_ClkDiv = ADC_Clk_Div4; //48/4=12M
    ADC_InitStructure.ADC_ConvertMode = ADC_ConvertMode_Continuous;    // 连续采样
    ADC_InitStructure.ADC_SQREns = ADC_SqrEns0to4;     // 单通道
    ADC_InitStructure.ADC_IN0.ADC_InputChannel = ADC_InputCH11;  //电流偏执电压
    ADC_InitStructure.ADC_IN0.ADC_SampTime = ADC_SampTime6Clk;  //15+6=21 12MHZ/21=571K
    ADC_InitStructure.ADC_IN1.ADC_InputChannel = ADC_InputCH12;  //电流
    ADC_InitStructure.ADC_IN1.ADC_SampTime = ADC_SampTime6Clk;
    ADC_InitStructure.ADC_IN2.ADC_InputChannel = ADC_InputCH13;  //电压
    ADC_InitStructure.ADC_IN2.ADC_SampTime = ADC_SampTime6Clk;  
    ADC_InitStructure.ADC_IN3.ADC_InputChannel = ADC_InputVref1P2; //1.2V
    ADC_InitStructure.ADC_IN3.ADC_SampTime = ADC_SampTime6Clk;     
    ADC_InitStructure.ADC_IN4.ADC_InputChannel = ADC_InputCH10;  //NTC温度
    ADC_InitStructure.ADC_IN4.ADC_SampTime = ADC_SampTime6Clk;  
    ADC_Init(&ADC_InitStructure);

		ADC_ClearITPendingAll();           //清除ADC所有中断状态
    ADC_Enable();                      // ADC使能
    ADC_SoftwareStartConvCmd(ENABLE);  //ADC转换软件启动命令
}


void Get_ADC_Value(void)
{
	static uint8_t cnt; 
	
  ADC_GetSqr0Result(&IPV1_Buffer[cnt]);  
  ADC_GetSqr1Result(&Curr_Buffer[cnt]);	 
  ADC_GetSqr2Result(&Volt_Buffer[cnt]);
	ADC_GetSqr3Result(&V12V_Buffer[cnt]); 		
	ADC_GetSqr4Result(&NTC_Buffer[cnt]);   
	
	cnt++;
	if(cnt >= ADC_SAMPLE_SIZE)
    {
        cnt = 0;
    }
}