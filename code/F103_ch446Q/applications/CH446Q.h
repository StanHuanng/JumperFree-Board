/*
 * File: CH446Q.h
 * Description: CH446Q 8x16 Analog Matrix Switch Driver for RT-Thread
 */

#ifndef __CH446Q_H__
#define __CH446Q_H__

#include <rtthread.h>
#include <board.h>
#include <drv_gpio.h>

/* 引脚定义，参考原理图 */
#define CH_DAT_PIN      GET_PIN(A, 10)  // DAT: Data Input
#define CH_CS_PIN       GET_PIN(A, 9)   // CS/CK: Clock
#define CH_STB_PIN      GET_PIN(A, 8)   // STB: Strobe/Latch

/* 功能函数声明 */

/**
 * @brief 初始化 CH446Q GPIO 引脚
 * @return int RT_EOK
 */
int ch446q_init(void);

/**
 * @brief 连接指定的 X 和 Y 通道
 * * @param x X通道编号 (0 - 15)
 * @param y Y通道编号 (0 - 7)
 */
void ch446q_connect(rt_uint8_t x, rt_uint8_t y);

/**
 * @brief 断开指定的 X 和 Y 通道
 * * @param x X通道编号 (0 - 15)
 * @param y Y通道编号 (0 - 7)
 */
void ch446q_disconnect(rt_uint8_t x, rt_uint8_t y);

/**
 * @brief 断开所有通道 (通过向所有地址写0实现，软复位)
 * 注意：硬件RST引脚复位更彻底，但此函数可在只有串口线控制时使用
 */
void ch446q_reset_all(void);

#endif /* __CH446Q_H__ */