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

#endif /* __WS2812_H__ */