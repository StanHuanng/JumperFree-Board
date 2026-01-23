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

/* 跑马灯效果（物理顺序自检） */
void ws2812_running_light(void)
{
    rt_uint8_t i;
    
    rt_kprintf("WS2812 Running Light Start...\n");
    
    /* 跑马灯：红色依次点亮每个LED（Index 0-24） */
    for (i = 0; i < WS2812_LED_NUM; i++) {
        ws2812_clear();
        ws2812_set_pixel(i, 50, 0, 0);  /* 红色，亮度适中 */
        ws2812_show();
        rt_thread_mdelay(50);
    }
    
    /* 自检完成后清空，等待后续显示 */
    ws2812_clear();
    ws2812_show();
    
    rt_kprintf("WS2812 Self-test Complete.\n");
}

/**
 * @brief 坐标转换为LED索引（适配5x5蛇形走线）
 * @note 左下角为(0,0)，右上角为(4,4)
 *       偶数行(y=0,2,4)从左向右：x递增
 *       奇数行(y=1,3)从右向左：x递减
 */
rt_uint8_t ws2812_get_index(rt_uint8_t x, rt_uint8_t y)
{
    if (x > 4 || y > 4) return 0;
    
    if (y % 2 == 0) {
        /* 偶数行：从左到右 */
        return y * 5 + x;
    } else {
        /* 奇数行：从右到左 */
        return y * 5 + (4 - x);
    }
}

/**
 * @brief 通过坐标设置像素颜色
 */
void ws2812_set_pixel_xy(rt_uint8_t x, rt_uint8_t y, rt_uint8_t r, rt_uint8_t g, rt_uint8_t b)
{
    if (x > 4 || y > 4) return;
    
    rt_uint8_t index = ws2812_get_index(x, y);
    ws2812_set_pixel(index, r, g, b);
}

/**
 * @brief 更新视觉显示（绘制L型路径）
 * @param y_idx 当前Y通道索引 (0-7)
 * 
 * 锚点：(4,4) 红色
 * 目标点：y0~y4 -> (0,0)~(4,0)，y5~y7 -> (0,1)~(2,1) 绿色
 * 路径：从目标点向右到x=4，再向上到y=4 黄色
 */
void ws2812_update_visual(rt_uint8_t y_idx)
{
    rt_uint8_t target_x, target_y;
    rt_uint8_t i;
    
    /* 参数检查 */
    if (y_idx > 7) return;
    
    /* 清空缓冲区 */
    ws2812_clear();
    
    /* 计算目标点坐标 */
    if (y_idx <= 4) {
        /* y0~y4 映射到第0行 */
        target_x = y_idx;
        target_y = 0;
    } else {
        /* y5~y7 映射到第1行 */
        target_x = y_idx - 5;
        target_y = 1;
    }
    
    /* 1. 绘制L型路径（黄色 15,15,0） */
    /* 从目标点向右延伸到 x=4 */
    for (i = target_x; i <= 4; i++) {
        ws2812_set_pixel_xy(i, target_y, 15, 15, 0);
    }
    /* 从 (4, target_y) 向上延伸到 y=4 */
    for (i = target_y; i <= 4; i++) {
        ws2812_set_pixel_xy(4, i, 15, 15, 0);
    }
    
    /* 2. 绘制目标点（绿色 0,50,0）- 覆盖路径起点 */
    ws2812_set_pixel_xy(target_x, target_y, 0, 50, 0);
    
    /* 3. 绘制锚点（红色 50,0,0）- 覆盖路径终点 */
    ws2812_set_pixel_xy(4, 4, 50, 0, 0);
    
    /* 发送数据到LED */
    ws2812_show();
}