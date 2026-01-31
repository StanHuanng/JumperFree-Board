/**
 * ******************************************************************************
 * @file    encoder.h
 * @brief   EC11 Rotary Encoder Driver Header
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
 * Hardware Notes:
 *  - TIM2 configured in Encoder Mode: TI1 and TI2 (4x frequency)
 *  - One detent = 4 counts
 *  - IC1/IC2 Filter = 15 (for noise rejection)
 *  - Period (ARR) = 65535 (16-bit, handles ±32767 range with signed conversion)
 * 
 * ******************************************************************************
 */

#ifndef __ENCODER_H
#define __ENCODER_H

#include "stm32f1xx_hal.h"
#include <stdint.h>

/**
 * @brief   Initialize encoder with TIM handle
 * @param   htim: Pointer to TIM2 handle (configured for Encoder Mode)
 * @return  None
 */
void encoder_init(TIM_HandleTypeDef *htim);

/**
 * @brief   Get encoder count change since last call (delta)
 * @return  Signed 16-bit delta count (-32768 to +32767)
 * @note    Must call this regularly to update internal signed counter
 */
int16_t encoder_get_delta(void);

/**
 * @brief   Get cumulative signed encoder count
 * @return  Signed 32-bit cumulative count
 * @note    Range: -2,147,483,648 to +2,147,483,647 (int32 full range)
 */
int32_t encoder_get_count(void);

/**
 * @brief   Reset encoder count to zero
 * @return  None
 */
void encoder_reset(void);

#endif
