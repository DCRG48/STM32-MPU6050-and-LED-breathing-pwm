/*
 * PWM.c
 *
 *  Created on: Dec 23, 2024
 *      Author: doudz
 */
#include "main.h"
#include "PWM.h"


extern TIM_HandleTypeDef htim2;



void LED_pwm ()
{
	  for(uint16_t duty_cycle = 0; duty_cycle<180; duty_cycle ++)
	  {
		  __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_3, duty_cycle);
		  HAL_Delay(10);
	  }


	  for(uint16_t duty_cycle = 180; duty_cycle>0; duty_cycle --)
	  {
		  __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_3, duty_cycle);
		  HAL_Delay(10);
	  }
}
