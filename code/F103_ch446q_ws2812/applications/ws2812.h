#ifndef __WS2812_H__
#define __WS2812_H__

#include <rtthread.h>
#include <rtdevice.h>
#include <drv_gpio.h>

/* WS2812配置 */
#define WS2812_LED_NUM      25      /* 5x5 LED灯板 */
#define WS2812_PIN          GET_PIN(B, 10)  /* PB10 */

/* 颜色结构体 */
typedef struct {
    rt_uint8_t r;
    rt_uint8_t g;
    rt_uint8_t b;
} ws2812_color_t;

/* 函数声明 */
void ws2812_init(void);
void ws2812_set_pixel(rt_uint8_t index, rt_uint8_t r, rt_uint8_t g, rt_uint8_t b);
void ws2812_set_all(rt_uint8_t r, rt_uint8_t g, rt_uint8_t b);
void ws2812_clear(void);
void ws2812_show(void);
void ws2812_running_light(void);

/**
 * @brief 坐标转换为LED索引（适配5x5蛇形走线）
 * @param x X坐标 (0-4)
 * @param y Y坐标 (0-4)
 * @return LED索引 (0-24)
 */
rt_uint8_t ws2812_get_index(rt_uint8_t x, rt_uint8_t y);

/**
 * @brief 通过坐标设置像素颜色
 * @param x X坐标 (0-4)
 * @param y Y坐标 (0-4)
 * @param r 红色分量
 * @param g 绿色分量
 * @param b 蓝色分量
 */
void ws2812_set_pixel_xy(rt_uint8_t x, rt_uint8_t y, rt_uint8_t r, rt_uint8_t g, rt_uint8_t b);

/**
 * @brief 更新视觉显示（绘制L型路径）
 * @param y_idx 当前Y通道索引 (0-7)
 * @note 锚点(4,4)红色，目标点绿色，路径黄色
 */
void ws2812_update_visual(rt_uint8_t y_idx);

#endif /* __WS2812_H__ */