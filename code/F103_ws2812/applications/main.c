#include <rtthread.h>
#include <board.h>
#include "ws2812.h"

int main(void)
{
    rt_kprintf("Hello Rt_Thread\n");
    
    /* 初始化WS2812 */
    ws2812_init();
    
    /* 执行跑马灯效果，完成后全部常亮 */
    ws2812_running_light();

    while (1)
    {
        rt_thread_mdelay(1000);
    }
}