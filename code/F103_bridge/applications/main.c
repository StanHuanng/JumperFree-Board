#include <rtthread.h>
#include <board.h>
#include "ch446q.h"
#include "ws2812.h"

/* 按键引脚定义 */
#define KEY_PIN         GET_PIN(B, 11)

/* 消抖参数 */
#define KEY_DEBOUNCE_MS     20      /* 消抖时间 */
#define KEY_SCAN_PERIOD_MS  10      /* 扫描周期 */

/* 全局变量 */
static rt_uint8_t current_y = 0;    /* 当前Y通道索引 (0-7) */

/* 按键线程栈与控制块 */
static struct rt_thread key_thread;
static rt_uint8_t key_thread_stack[512];

/**
 * @brief 按键扫描线程入口函数
 * @note 使用软件计数消抖
 */
static void key_thread_entry(void *parameter)
{
    rt_uint8_t key_state = 0;           /* 当前按键状态 */
    rt_uint8_t key_last = 0;            /* 上次读取状态 */
    rt_uint8_t key_confirmed = 0;       /* 消抖后确认的状态 */
    rt_uint8_t debounce_cnt = 0;        /* 消抖计数器 */
    rt_uint8_t old_y;
    
    /* 配置按键引脚为下拉输入 */
    rt_pin_mode(KEY_PIN, PIN_MODE_INPUT_PULLDOWN);
    
    while (1)
    {
        /* 读取按键状态：高电平表示按下（因为按键另一端接3V3） */
        key_state = rt_pin_read(KEY_PIN);
        
        if (key_state != key_last)
        {
            /* 状态变化，重新开始消抖计数 */
            debounce_cnt = 0;
        }
        else
        {
            /* 状态稳定，累加消抖计数 */
            if (debounce_cnt < 255)
            {
                debounce_cnt++;
            }
            
            /* 消抖完成，确认状态 */
            if (debounce_cnt == (KEY_DEBOUNCE_MS / KEY_SCAN_PERIOD_MS))
            {
                /* 检测到上升沿（按键按下） */
                if (key_state == PIN_HIGH && key_confirmed == PIN_LOW)
                {
                    /* 保存旧的Y索引 */
                    old_y = current_y;
                    
                    /* Y索引递增循环 (0 -> 7 -> 0) */
                    current_y++;
                    if (current_y > 7)
                    {
                        current_y = 0;
                    }
                    
                    rt_kprintf("Key pressed: Y%d -> Y%d\n", old_y, current_y);
                    
                    /* 断开旧连接 */
                    ch446q_disconnect(0, old_y);
                    
                    /* 建立新连接 */
                    ch446q_connect(0, current_y);
                    
                    /* 更新LED显示 */
                    ws2812_update_visual(current_y);
                }
                
                /* 更新确认状态 */
                key_confirmed = key_state;
            }
        }
        
        key_last = key_state;
        rt_thread_mdelay(KEY_SCAN_PERIOD_MS);
    }
}

int main(void)
{
    rt_err_t result;
    
    rt_kprintf("JumperFree-Board System Starting...\n");
    
    /* ========== 初始化序列 ========== */
    
    /* 1. 初始化CH446Q驱动并复位所有开关 */
    rt_kprintf("Initializing CH446Q...\n");
    ch446q_init();
    ch446q_reset_all();
    rt_kprintf("CH446Q reset complete.\n");
    
    /* 2. 初始化WS2812并执行自检跑马灯 */
    rt_kprintf("Initializing WS2812...\n");
    ws2812_init();
    ws2812_running_light();
    rt_thread_mdelay(500);  /* 短暂停留观察白灯效果 */
    
    /* 3. 建立默认连接: X0 <-> Y0 */
    rt_kprintf("Establishing default connection: X0 <-> Y0\n");
    current_y = 0;
    ch446q_connect(0, current_y);
    ws2812_update_visual(current_y);
    
    rt_kprintf("Initialization complete.\n");
    
    /* ========== 创建按键扫描线程 ========== */
    result = rt_thread_init(&key_thread,
                            "key_scan",
                            key_thread_entry,
                            RT_NULL,
                            key_thread_stack,
                            sizeof(key_thread_stack),
                            RT_THREAD_PRIORITY_MAX - 3,
                            20);
    
    if (result == RT_EOK)
    {
        rt_thread_startup(&key_thread);
        rt_kprintf("Key scan thread started.\n");
    }
    else
    {
        rt_kprintf("Failed to create key scan thread!\n");
    }
    
    /* 主循环 */
    while (1)
    {
        rt_thread_mdelay(1000);
    }
}