# 经验沉淀（可复用）

## CubeMX 配置

### GPIO 配置
- **OLED 软 I2C**：PB6/PB7 配置为 GPIO_Output_OD，速度设为 High，不启用内部上拉（模块自带）。
- **SYS Timebase**：必须为 TIM1，避免与 RT-Thread 占用的 SysTick 冲突。

### TIM2 编码器模式
- **Encoder Mode**：TI1 and TI2（四倍频）
- **Counter Period (ARR)**：默认 65535（16 位全范围）
- **IC1/IC2 Filter**：设置为 15（最大滤波，减少高频噪声）
- **Prescaler**：0
- 无需额外配置 PB0 EXTI（若编码器无 SW 引脚）

## 驱动迁移经验

- **从非 HAL/StdPeriph 代码移植**：需将 GPIO/RCC 访问替换为 HAL（如 `HAL_GPIO_WritePin`、`HAL_GPIO_Init`）。
- **软 I2C 引脚映射**：根据计划书指定引脚（PB6/PB7），并在驱动中定义宏常量。
- **I2C 时序延迟**：加入 `__NOP()` 延迟循环，避免时钟速度过快超出规范。

## OLED 显示驱动

- **显示驱动最少需要 3 类文件**：软 I2C（低层时序）、OLED 驱动（SSD1306 命令）、字库（字体表）。
- **最小测试流程**：`OLED_Init()` → `OLED_ShowString()` → `OLED_Update()`。
- **仅在数据变化时刷屏**：避免频繁清屏导致显示闪烁。

## 旋转编码器驱动

### 硬件特性
- **EC11 四倍频编码**：一个齿产生 4 计数。
- **TIM Counter 16 位无符号**：向下计数会溢出（65535 → 0），需维护有符号累计器。
- **轮询间隔建议**：
  - 20ms：捕捉快速旋转反应
  - 100ms：减少 ±1~5 抖动
  - 启用 IC Filter=15 可进一步减少高频噪声

### 驱动实现
- **有符号累计**：通过每轮询一次的 delta（16 位有符号差值）累加到 int32_t 累计器。
- **导出接口**：
  - `encoder_init(TIM_HandleTypeDef *htim)`：初始化并启动 Encoder
  - `encoder_get_delta()`：返回本轮自上轮的位移（有符号）
  - `encoder_get_count()`：返回累计计数（int32，范围 ±2G）
  - `encoder_reset()`：重置为零

## 代码注释规范

- **文件头部**：使用标准 Doxygen 注释块，包含文件说明、引脚配置、硬件注意事项。
- **函数声明**：每个公开函数都要有 @brief、@param、@return 注释。
- **关键变量**：静态全局变量需标注用途（如 `s_enc_tim` 表示编码器 TIM 句柄）。

