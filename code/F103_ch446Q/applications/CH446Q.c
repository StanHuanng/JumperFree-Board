/*
 * File: CH446Q.c
 * Description: CH446Q Driver Implementation
 * Protocol: Serial Address Input (7-bit ADDR + STB Latch)
 */

#include "CH446Q.h"

/**
 * @brief 初始化控制引脚
 */
int ch446q_init(void)
{
    /* 配置引脚为推挽输出模式 */
    rt_pin_mode(CH_DAT_PIN, PIN_MODE_OUTPUT);
    rt_pin_mode(CH_CS_PIN,  PIN_MODE_OUTPUT);
    rt_pin_mode(CH_STB_PIN, PIN_MODE_OUTPUT);

    /* 设置默认电平 */
    rt_pin_write(CH_STB_PIN, PIN_LOW); // STB 平时为低
    rt_pin_write(CH_CS_PIN,  PIN_LOW); // CS/CK 平时为低
    rt_pin_write(CH_DAT_PIN, PIN_LOW);

    return RT_EOK;
}

/**
 * @brief 内部函数：发送地址并锁存数据
 * * 时序说明 (参考手册串行模式):
 * 1. CS/CK 提供 7 个上升沿，将 7 位地址 (ADDR6..ADDR0) 移入芯片。
 * 2. 地址移入完成后，设置 DAT 引脚为开关状态 (High=On, Low=Off)。
 * 3. STB 产生一个高脉冲，将 DAT 的状态写入由刚才地址选中的锁存器。
 * * @param addr 7位地址 (Y在形高3位，X在低4位)
 * @param state 1 = 导通, 0 = 断开
 */
static void ch446q_write_cmd(rt_uint8_t addr, rt_uint8_t state)
{
    rt_uint8_t i;

    /* 1. 移位输入 7 位地址 (ADDR6 -> ADDR0) */
    /* 地址映射: 
       Y (3 bits) | X (4 bits)
       例如: Y7(111), X15(1111) -> 1111111 (0x7F)
    */
    for (i = 0; i < 7; i++)
    {
        rt_pin_write(CH_CS_PIN, PIN_LOW); // 拉低时钟准备

        /* 准备数据位: 从最高位 ADDR6 开始发送 */
        if (addr & (1 << (6 - i))) 
        {
            rt_pin_write(CH_DAT_PIN, PIN_HIGH);
        }
        else
        {
            rt_pin_write(CH_DAT_PIN, PIN_LOW);
        }

        /* 产生上升沿，芯片锁存当前位地址 */
        rt_pin_write(CH_CS_PIN, PIN_HIGH);
        
        /* 简单的延时，保证时序稳定 (MCU主频若非常高可能需要) */
        // rt_hw_us_delay(1); 
    }
    
    rt_pin_write(CH_CS_PIN, PIN_LOW); // 时钟回落

    /* 2. 准备开关数据 */
    /* 手册说明：在 ACT (STB) 有效期间，DAT 的状态决定开关是开还是关。
       1 = 导通, 0 = 关闭
    */
    if (state)
    {
        rt_pin_write(CH_DAT_PIN, PIN_HIGH);
    }
    else
    {
        rt_pin_write(CH_DAT_PIN, PIN_LOW);
    }

    /* 3. 产生 STB 脉冲进行执行/锁存 */
    rt_pin_write(CH_STB_PIN, PIN_HIGH);
    /* 保持 STB 高电平至少 10ns (参考手册 TSTB) */
    // rt_hw_us_delay(1); 
    rt_pin_write(CH_STB_PIN, PIN_LOW);
}

/**
 * @brief 连接 X 和 Y
 */
void ch446q_connect(rt_uint8_t x, rt_uint8_t y)
{
    /* 参数检查: X (0-15), Y (0-7) */
    if (x > 15 || y > 7) return;

    /* 计算地址: ADDR = (Y << 4) | X */
    rt_uint8_t addr = (y << 4) | (x & 0x0F);

    /* 发送命令：导通 (1) */
    ch446q_write_cmd(addr, 1);
}

/**
 * @brief 断开 X 和 Y
 */
void ch446q_disconnect(rt_uint8_t x, rt_uint8_t y)
{
    if (x > 15 || y > 7) return;

    /* 计算地址 */
    rt_uint8_t addr = (y << 4) | (x & 0x0F);

    /* 发送命令：断开 (0) */
    ch446q_write_cmd(addr, 0);
}

/**
 * @brief 软复位：遍历所有地址并断开
 */
void ch446q_reset_all(void)
{
    /* CH446Q 有 128 个地址 (0x00 - 0x7F) */
    for (int i = 0; i <= 0x7F; i++)
    {
        ch446q_write_cmd(i, 0);
    }
}