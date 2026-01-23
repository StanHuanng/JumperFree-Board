#include "ws2812.h"

/* LED颜色缓冲区 */
static ws2812_color_t ws2812_buffer[WS2812_LED_NUM];

/* GPIO 寄存器直接操作宏 - 提高时序精度 */
#define WS2812_GPIO_PORT    GPIOB
#define WS2812_GPIO_PIN     GPIO_PIN_10
#define WS2812_HIGH()       WS2812_GPIO_PORT->BSRR = WS2812_GPIO_PIN
#define WS2812_LOW()        WS2812_GPIO_PORT->BSRR = (uint32_t)WS2812_GPIO_PIN << 16U

/* 发送0码: 高电平约0.4us, 低电平约0.85us */
static __inline void ws2812_send_0(void)
{
    /* 72MHz下，需要考虑寄存器操作的开销
     * 高电平约0.4us = 29个周期，减去操作开销约需要20个NOP
     * 低电平约0.85us = 61个周期，减去操作开销约需要55个NOP */
    WS2812_HIGH();
    __NOP(); __NOP(); __NOP(); __NOP(); __NOP();
    __NOP(); __NOP(); __NOP(); __NOP(); __NOP();
    __NOP(); __NOP(); __NOP(); __NOP(); __NOP();
    __NOP(); __NOP(); __NOP(); __NOP(); __NOP();
    WS2812_LOW();
    __NOP(); __NOP(); __NOP(); __NOP(); __NOP();
    __NOP(); __NOP(); __NOP(); __NOP(); __NOP();
    __NOP(); __NOP(); __NOP(); __NOP(); __NOP();
    __NOP(); __NOP(); __NOP(); __NOP(); __NOP();
    __NOP(); __NOP(); __NOP(); __NOP(); __NOP();
    __NOP(); __NOP(); __NOP(); __NOP(); __NOP();
    __NOP(); __NOP(); __NOP(); __NOP(); __NOP();
    __NOP(); __NOP(); __NOP(); __NOP(); __NOP();
    __NOP(); __NOP(); __NOP(); __NOP(); __NOP();
    __NOP(); __NOP(); __NOP(); __NOP(); __NOP();
    __NOP(); __NOP(); __NOP(); __NOP(); __NOP();
}

/* 发送1码: 高电平约0.8us, 低电平约0.45us */
static __inline void ws2812_send_1(void)
{
    /* 72MHz下
     * 高电平约0.8us = 58个周期，减去操作开销约需要50个NOP
     * 低电平约0.45us = 32个周期，减去操作开销约需要25个NOP */
    WS2812_HIGH();
    __NOP(); __NOP(); __NOP(); __NOP(); __NOP();
    __NOP(); __NOP(); __NOP(); __NOP(); __NOP();
    __NOP(); __NOP(); __NOP(); __NOP(); __NOP();
    __NOP(); __NOP(); __NOP(); __NOP(); __NOP();
    __NOP(); __NOP(); __NOP(); __NOP(); __NOP();
    __NOP(); __NOP(); __NOP(); __NOP(); __NOP();
    __NOP(); __NOP(); __NOP(); __NOP(); __NOP();
    __NOP(); __NOP(); __NOP(); __NOP(); __NOP();
    __NOP(); __NOP(); __NOP(); __NOP(); __NOP();
    __NOP(); __NOP(); __NOP(); __NOP(); __NOP();
    WS2812_LOW();
    __NOP(); __NOP(); __NOP(); __NOP(); __NOP();
    __NOP(); __NOP(); __NOP(); __NOP(); __NOP();
    __NOP(); __NOP(); __NOP(); __NOP(); __NOP();
    __NOP(); __NOP(); __NOP(); __NOP(); __NOP();
    __NOP(); __NOP(); __NOP(); __NOP(); __NOP();
}

/* 发送一个字节 - MSB first */
static void ws2812_send_byte(rt_uint8_t byte)
{
    rt_uint8_t i;
    for (i = 0; i < 8; i++) {
        if (byte & 0x80) {
            ws2812_send_1();
        } else {
            ws2812_send_0();
        }
        byte <<= 1;
    }
}

/* 发送复位信号 (>50us低电平) */
static void ws2812_reset(void)
{
    rt_pin_write(WS2812_PIN, PIN_LOW);
    rt_hw_us_delay(60);
}

/* 初始化WS2812 */
void ws2812_init(void)
{
    /* 配置引脚为输出模式 */
    rt_pin_mode(WS2812_PIN, PIN_MODE_OUTPUT);
    rt_pin_write(WS2812_PIN, PIN_LOW);
    
    /* 清空缓冲区 */
    ws2812_clear();
    ws2812_show();
}

/* 设置单个像素颜色 */
void ws2812_set_pixel(rt_uint8_t index, rt_uint8_t r, rt_uint8_t g, rt_uint8_t b)
{
    if (index < WS2812_LED_NUM) {
        ws2812_buffer[index].r = r;
        ws2812_buffer[index].g = g;
        ws2812_buffer[index].b = b;
    }
}

/* 设置所有像素为同一颜色 */
void ws2812_set_all(rt_uint8_t r, rt_uint8_t g, rt_uint8_t b)
{
    rt_uint8_t i;
    for (i = 0; i < WS2812_LED_NUM; i++) {
        ws2812_buffer[i].r = r;
        ws2812_buffer[i].g = g;
        ws2812_buffer[i].b = b;
    }
}

/* 清除所有像素 (全部熄灭) */
void ws2812_clear(void)
{
    rt_memset(ws2812_buffer, 0, sizeof(ws2812_buffer));
}

/* 将缓冲区数据发送到WS2812 - GRB顺序 */
void ws2812_show(void)
{
    rt_uint8_t i;
    rt_base_t level;
    
    /* 关闭中断，保证时序精确 */
    level = rt_hw_interrupt_disable();
    
    /* WS2812数据格式为GRB */
    for (i = 0; i < WS2812_LED_NUM; i++) {
        ws2812_send_byte(ws2812_buffer[i].g);  /* Green first */
        ws2812_send_byte(ws2812_buffer[i].r);  /* Red second */
        ws2812_send_byte(ws2812_buffer[i].b);  /* Blue last */
    }
    
    /* 恢复中断 */
    rt_hw_interrupt_enable(level);
    
    /* 发送复位信号 */
    ws2812_reset();
}

/* 跑马灯效果，然后全部常亮 */
void ws2812_running_light(void)
{
    rt_uint8_t i;
    
    rt_kprintf("WS2812 Running Light Start...\n");
    
    /* 跑马灯：红色依次点亮每个LED */
    for (i = 0; i < WS2812_LED_NUM; i++) {
        ws2812_clear();
        ws2812_set_pixel(i, 50, 0, 0);  /* 红色，亮度适中 */
        ws2812_show();
        rt_thread_mdelay(50);
    }
    
    /* 跑马灯：绿色依次点亮每个LED */
    for (i = 0; i < WS2812_LED_NUM; i++) {
        ws2812_clear();
        ws2812_set_pixel(i, 0, 50, 0);  /* 绿色 */
        ws2812_show();
        rt_thread_mdelay(50);
    }
    
    /* 跑马灯：蓝色依次点亮每个LED */
    for (i = 0; i < WS2812_LED_NUM; i++) {
        ws2812_clear();
        ws2812_set_pixel(i, 0, 0, 50);  /* 蓝色 */
        ws2812_show();
        rt_thread_mdelay(50);
    }
    
    /* 全部25个灯常亮白色 */
    ws2812_set_all(30, 30, 30);  /* 白色，亮度较低避免过亮 */
    ws2812_show();
    
    rt_kprintf("WS2812 All LEDs ON (White)\n");
}