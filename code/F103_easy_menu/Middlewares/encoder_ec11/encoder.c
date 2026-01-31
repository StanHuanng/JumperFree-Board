/**
 * ******************************************************************************
 * @file    encoder.c
 * @brief   EC11 Rotary Encoder Driver Implementation
 * 
 * @details EC11 encoder driver adapted for STM32F103C8T6 + RT-Thread Nano
 *          Uses TIM2 Encoder Mode for quadrature decoding
 *          Maintains signed cumulative count to handle direction and overflow
 * 
 * Pin Configuration:
 *  - PA0: EC11_A (TIM2_CH1, Encoder Phase A)
 *  - PA1: EC11_B (TIM2_CH2, Encoder Phase B)
 *  - GND: EC11_C (Common/COM, must be grounded)
 *  - VCC: EC11_VCC (3.3V)
 * 
 * ******************************************************************************
 */

#include "encoder.h"

static TIM_HandleTypeDef *s_enc_tim = NULL;
static uint16_t s_last_count = 0;
static int32_t s_signed_count = 0;

void encoder_init(TIM_HandleTypeDef *htim)
{
	if (htim == NULL)
	{
		return;
	}

	s_enc_tim = htim;
	HAL_TIM_Encoder_Start(s_enc_tim, TIM_CHANNEL_ALL);
	s_last_count = __HAL_TIM_GET_COUNTER(s_enc_tim);
	s_signed_count = 0;
}

int16_t encoder_get_delta(void)
{
	uint16_t now;
	int16_t delta;

	if (s_enc_tim == NULL)
	{
		return 0;
	}

	now = __HAL_TIM_GET_COUNTER(s_enc_tim);
	delta = (int16_t)(now - s_last_count);
	s_signed_count += delta;
	s_last_count = now;
	return delta;
}

int32_t encoder_get_count(void)
{
	/* Trigger delta calculation to update signed count */
	encoder_get_delta();
	return s_signed_count;
}

void encoder_reset(void)
{
	if (s_enc_tim == NULL)
	{
		return;
	}

	__HAL_TIM_SET_COUNTER(s_enc_tim, 0);
	s_last_count = 0;
	s_signed_count = 0;
}
