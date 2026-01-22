/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-01-22     User         WS2812 PWM+DMA Driver for STM32F103
 */

#ifndef __WS2812_H__
#define __WS2812_H__

#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>  /* 包含板级头文件，会自动引入正确的HAL库 */

/* WS2812 配置参数 */
#define WS2812_LED_COUNT        25      /* LED数量 */
#define WS2812_BITS_PER_LED     24      /* 每个LED的位数(GRB) */
#define WS2812_RESET_BITS       50      /* 复位时序位数(>50us) */
#define WS2812_BUFFER_SIZE      (WS2812_LED_COUNT * WS2812_BITS_PER_LED + WS2812_RESET_BITS)  /* 总缓冲区大小:625 */

/* PWM时序参数 (基于72MHz TIM2时钟, ARR=89, 800kHz PWM频率) */
#define WS2812_PWM_ZERO_CODE    29      /* 0码PWM占空比(约0.40us高电平) */
#define WS2812_PWM_ONE_CODE     58      /* 1码PWM占空比(约0.81us高电平) */
#define WS2812_PWM_RESET_CODE   0       /* 复位码PWM占空比(低电平) */

/* 定时器配置 */
#define WS2812_TIM              htim2
#define WS2812_TIM_CHANNEL      TIM_CHANNEL_3
#define WS2812_DMA_CHANNEL      DMA1_Channel1

/* 颜色结构体 */
typedef struct {
    uint8_t r;  /* 红色分量 (0-255) */
    uint8_t g;  /* 绿色分量 (0-255) */
    uint8_t b;  /* 蓝色分量 (0-255) */
} ws2812_color_t;

/* 颜色宏定义 */
#define WS2812_COLOR(r, g, b)   ((ws2812_color_t){(r), (g), (b)})
#define WS2812_RED              WS2812_COLOR(255, 0, 0)
#define WS2812_GREEN            WS2812_COLOR(0, 255, 0)
#define WS2812_BLUE             WS2812_COLOR(0, 0, 255)
#define WS2812_WHITE            WS2812_COLOR(255, 255, 255)
#define WS2812_BLACK            WS2812_COLOR(0, 0, 0)
#define WS2812_YELLOW           WS2812_COLOR(255, 255, 0)
#define WS2812_CYAN             WS2812_COLOR(0, 255, 255)
#define WS2812_MAGENTA          WS2812_COLOR(255, 0, 255)

/* 外部变量声明 */
extern TIM_HandleTypeDef htim2;

/* 核心API函数 */

/**
 * @brief 初始化WS2812驱动
 * @return 0:成功, -1:失败
 */
int ws2812_init(void);

/**
 * @brief 设置单个LED颜色
 * @param index LED索引(0-24)
 * @param color 颜色值
 * @return 0:成功, -1:索引越界
 */
int ws2812_set_pixel(uint16_t index, ws2812_color_t color);

/**
 * @brief 设置所有LED为同一颜色
 * @param color 颜色值
 */
void ws2812_set_all(ws2812_color_t color);

/**
 * @brief 清除所有LED(设为黑色)
 */
void ws2812_clear(void);

/**
 * @brief 更新LED显示(启动DMA传输)
 * @return 0:成功, -1:DMA忙碌
 */
int ws2812_update(void);

/**
 * @brief 设置全局亮度
 * @param brightness 亮度级别(0-100)
 */
void ws2812_set_brightness(uint8_t brightness);

/**
 * @brief 获取DMA传输状态
 * @return 0:空闲, 1:忙碌
 */
int ws2812_is_busy(void);

#endif /* __WS2812_H__ */
