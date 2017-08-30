#include "tim.h"


void PwmConfig(TIM_TypeDef* tim,  int period, int prescaler, int pulse, int channel)
{

	switch((uint32_t)tim)
	{
		case (uint32_t)TIM2:
			RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
			break;
		case (uint32_t)TIM3:
			RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
			break;
		case (uint32_t)TIM4:
			RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
			break;
		case (uint32_t)TIM5:
			RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);
			break;
		case (uint32_t)TIM6:
			RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, ENABLE);
			break;
		case (uint32_t)TIM7:
			RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM7, ENABLE);
			break;
	}

	if( tim )
	{
		TIM_TimeBaseInitTypeDef initstructure;

		initstructure.TIM_Period = period;
		initstructure.TIM_Prescaler = prescaler;
		initstructure.TIM_ClockDivision = TIM_CKD_DIV1;
		initstructure.TIM_CounterMode = TIM_CounterMode_Up;
		initstructure.TIM_RepetitionCounter = 0;

		TIM_TimeBaseInit(tim, &initstructure);
	}

	if( tim )
	{
		TIM_OCInitTypeDef initstructure;

		initstructure.TIM_OCMode = TIM_OCMode_PWM1;
		initstructure.TIM_OutputState = TIM_OutputState_Enable;
		initstructure.TIM_OCPolarity = TIM_OCPolarity_High;
		initstructure.TIM_Pulse = pulse;
		switch(channel)
		{
			case 1:
				TIM_OC1Init(tim, &initstructure);
				TIM_OC1PreloadConfig(tim, TIM_OCPreload_Enable);
				break;
			case 2:
				TIM_OC2Init(tim, &initstructure);
				TIM_OC2PreloadConfig(tim, TIM_OCPreload_Enable);
				break;
			case 3:
				TIM_OC3Init(tim, &initstructure);
				TIM_OC3PreloadConfig(tim, TIM_OCPreload_Enable);
				break;
			case 4:
				TIM_OC4Init(tim, &initstructure);
				TIM_OC4PreloadConfig(tim, TIM_OCPreload_Enable);
				break;
		}
	}
	TIM_Cmd(tim, ENABLE);
}
