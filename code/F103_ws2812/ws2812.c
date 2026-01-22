/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-01-22     User         WS2812 PWM+DMA Driver Implementation
 */

#include "ws2812.h"
#include <rtthread.h>
#include <string.h>

/* 私有变量 */
static uint16_t ws2812_pwm_buffer[WS2812_BUFFER_SIZE];  /* PWM DMA缓冲区 */
static ws2812_color_t ws2812_colors[WS2812_LED_COUNT];  /* LED颜色数组 */
static uint8_t ws2812_brightness = 100;                 /* 全局亮度(0-100) */
static volatile uint8_t ws2812_busy_flag = 0;           /* DMA忙碌标志 */

/* 私有函数声明 */
static void ws2812_rgb_to_pwm_buffer(void);
static uint8_t ws2812_apply_brightness(uint8_t color);

/**
 * @brief 初始化WS2812驱动
 */
int ws2812_init(void)
{
    /* 验证PWM频率配置 */
    uint32_t tim_clk = HAL_RCC_GetPCLK1Freq() * 2;  /* TIM2时钟 = APB1 * 2 */
    uint32_t pwm_freq = tim_clk / (htim2.Init.Prescaler + 1) / (htim2.Init.Period + 1);

    if (pwm_freq != 800000) {
        rt_kprintf("[WS2812] Error: PWM frequency is %d Hz, expected 800000 Hz\n", pwm_freq);
        rt_kprintf("[WS2812] Please check TIM2 configuration: PSC=%d, ARR=%d\n",
                   htim2.Init.Prescaler, htim2.Init.Period);
        return -1;
    }

    /* 清空颜色数组 */
    memset(ws2812_colors, 0, sizeof(ws2812_colors));

    /* 初始化PWM缓冲区为复位状态 */
    memset(ws2812_pwm_buffer, 0, sizeof(ws2812_pwm_buffer));

    /* 清除忙碌标志 */
    ws2812_busy_flag = 0;

    rt_kprintf("[WS2812] Init success: %d LEDs, PWM=%d kHz\n",
               WS2812_LED_COUNT, pwm_freq / 1000);

    return 0;
}

/**
 * @brief 设置单个LED颜色
 */
int ws2812_set_pixel(uint16_t index, ws2812_color_t color)
{
    if (index >= WS2812_LED_COUNT) {
        rt_kprintf("[WS2812] Error: LED index %d out of range (0-%d)\n",
                   index, WS2812_LED_COUNT - 1);
        return -1;
    }

    ws2812_colors[index] = color;
    return 0;
}

/**
 * @brief 设置所有LED为同一颜色
 */
void ws2812_set_all(ws2812_color_t color)
{
    for (uint16_t i = 0; i < WS2812_LED_COUNT; i++) {
        ws2812_colors[i] = color;
    }
}

/**
 * @brief 清除所有LED
 */
void ws2812_clear(void)
{
    memset(ws2812_colors, 0, sizeof(ws2812_colors));
}

/**
 * @brief 设置全局亮度
 */
void ws2812_set_brightness(uint8_t brightness)
{
    if (brightness > 100) {
        brightness = 100;
    }
    ws2812_brightness = brightness;
}

/**
 * @brief 应用亮度调整
 */
static uint8_t ws2812_apply_brightness(uint8_t color)
{
    return (uint8_t)((uint32_t)color * ws2812_brightness / 100);
}

/**
 * @brief 将RGB颜色数组转换为PWM缓冲区
 * @note WS2812使用GRB顺序, MSB先发送
 */
static void ws2812_rgb_to_pwm_buffer(void)
{
    uint32_t buffer_index = 0;

    /* 遍历每个LED */
    for (uint16_t led = 0; led < WS2812_LED_COUNT; led++) {
        /* 应用亮度调整 */
        uint8_t g = ws2812_apply_brightness(ws2812_colors[led].g);
        uint8_t r = ws2812_apply_brightness(ws2812_colors[led].r);
        uint8_t b = ws2812_apply_brightness(ws2812_colors[led].b);

        /* 按GRB顺序编码24位数据 */
        uint32_t grb = ((uint32_t)g << 16) | ((uint32_t)r << 8) | b;

        /* MSB先发送: 从bit23到bit0 */
        for (int8_t bit = 23; bit >= 0; bit--) {
            if (grb & (1 << bit)) {
                /* 位为1: 高电平0.81us */
                ws2812_pwm_buffer[buffer_index] = WS2812_PWM_ONE_CODE;
            } else {
                /* 位为0: 高电平0.40us */
                ws2812_pwm_buffer[buffer_index] = WS2812_PWM_ZERO_CODE;
            }
            buffer_index++;
        }
    }

    /* 添加复位时序: 50个低电平周期(62.5us) */
    for (uint16_t i = 0; i < WS2812_RESET_BITS; i++) {
        ws2812_pwm_buffer[buffer_index++] = WS2812_PWM_RESET_CODE;
    }
}

/**
 * @brief 更新LED显示(启动DMA传输)
 */
int ws2812_update(void)
{
    /* 检查DMA是否忙碌 */
    if (ws2812_busy_flag) {
        rt_kprintf("[WS2812] Warning: DMA busy, update skipped\n");
        return -1;
    }

    /* 转换RGB数据到PWM缓冲区 */
    ws2812_rgb_to_pwm_buffer();

    /* 设置忙碌标志 */
    ws2812_busy_flag = 1;

    /* 启动PWM DMA传输 */
    HAL_TIM_PWM_Start_DMA(&WS2812_TIM, WS2812_TIM_CHANNEL,
                          (uint32_t *)ws2812_pwm_buffer, WS2812_BUFFER_SIZE);

    return 0;
}

/**
 * @brief 获取DMA传输状态
 */
int ws2812_is_busy(void)
{
    return ws2812_busy_flag;
}

/**
 * @brief PWM DMA传输完成回调
 * @note 由HAL库自动调用
 */
void HAL_TIM_PWM_PulseFinishedCallback(TIM_HandleTypeDef *htim)
{
    if (htim == &WS2812_TIM) {
        /* 停止PWM输出 */
        HAL_TIM_PWM_Stop_DMA(&WS2812_TIM, WS2812_TIM_CHANNEL);

        /* 清除忙碌标志 */
        ws2812_busy_flag = 0;
    }
}

/*
 * 注意：DMA1_Channel1_IRQHandler 已在 stm32f1xx_it.c 中定义
 * 如需在RT-Thread环境下使用，请在 stm32f1xx_it.c 的中断函数中
 * 添加 rt_interrupt_enter() 和 rt_interrupt_leave()
 */
