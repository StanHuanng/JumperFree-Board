# 经验沉淀（可复用）

## 2026-01-31
- Phase 2（显示驱动）中，软 I2C 需要将 PB6/PB7 配置为 GPIO_Output Open Drain；若模块已带上拉，GPIO 侧不再启用内部上拉。
- RT-Thread 工程的 SYS Timebase 必须为 TIM1，避免与 RT-Thread 占用的 SysTick 冲突。
- OLED 显示驱动最少需要 3 类文件：软 I2C（或低层 I2C）、OLED 驱动（SSD1306），以及字库（字体表）。其中字库通常拆成 font.c/h，避免与驱动耦合。
- 从非 HAL/StdPeriph 代码移植时，需把 GPIO/RCC 访问替换为 HAL（如 `HAL_GPIO_WritePin`、`HAL_GPIO_Init`），并把 SCL/SDA 引脚改为计划书指定的 PB6/PB7。
- OLED 功能测试的最小流程：在初始化外设后调用 `OLED_Init()`，再用 `OLED_ShowString()` 写入测试字符并调用 `OLED_Update()` 刷屏。
