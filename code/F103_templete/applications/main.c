#include <rtthread.h>
#include <board.h>
#include "CH446Q.h"

int main(void)
{
    /* 初始化 CH446Q 驱动 */
    ch446q_init();

	ch446q_reset_all();
	
    /* 示例：将 X0 连接到 Y0 */
    ch446q_connect(0, 0);
    rt_kprintf("Connected X0 to Y0\n");
    rt_thread_mdelay(1000);

    /* 示例：将 X3 连接到 Y2 */
    ch446q_connect(3, 2);
    rt_kprintf("Connected X3 to Y2\n");
    rt_thread_mdelay(1000);



    while (1)
    {
        rt_thread_mdelay(1000);
    }
}