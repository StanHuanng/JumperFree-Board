# JumperFree-Board 

> **探索电路的可能性：一个向经典致敬的无跳线面包板尝试**
>
> 团队：高电位队 (High Voltage Team)

[![Standard](https://img.shields.io/badge/Stage-Completed-success.svg)](https://github.com/Architeuthis-Flux/JumperlessV5)
[![Board](https://img.shields.io/badge/MCU-STM32F103-blue.svg)](https://www.st.com)
[![RTOS](https://img.shields.io/badge/RTOS-RT--Thread%20Nano-brightgreen.svg)](https://www.rt-thread.org/)

---

### 📖 项目初衷

`JumperFree-Board` 是我们团队在学习嵌入式拓扑与矩阵切换技术过程中的实践记录。我们深受 [JumperlessV5](https://github.com/Architeuthis-Flux/JumperlessV5) 项目的启发，尝试在有限的硬件资源上（以 STM32F103 为起点）复刻并探索模拟开关矩阵的应用边界。

目前，我们已经初步完成了 **Stage 1 (F103 原型验证)**，通过模拟开关逻辑与 LED 视觉反馈，实现了基础的信号路由功能。

---

### 🛠️ 核心进展

#### **Stage 1: 硬件原型验证 [已达成]**
作为项目的基石，我们在此阶段重点攻克了底层驱动与实时性问题：

*   **信号路由**：基于 `CH446Q` 芯片，通过串口协议精确控制 128 个交叉点。
*   **视觉路径**：
    *   适配 5x5 **蛇形拓扑** 矩阵算法，实现逻辑坐标到物理 LED 的映射。
    *   **L 型智能路径渲染**：清晰展示信号源与目标通道的连接状态。
*   **交互管理**：基于 `RT-Thread Nano` 多线程模型，实现响应迅速的按键消抖与状态机切换。

---

### 📈 路线图 (Roadmap)

| 阶段        | 目标                                                    | 状态     |
| :---------- | :------------------------------------------------------ | :------- |
| **Stage 1** | **F103 原型验证**：基础驱动、蛇形矩阵显示、按键逻辑     | ✅ 已完成 |
| **Stage 2** | **H743 性能跨越**：更高主频、多片层叠矩阵、USB-CDC 通讯 | 🚧 进行中 |
| **Stage 3** | **集成与优化**：低噪声 PCB 设计、智能功耗管理           | 📅 计划中 |

---

### 🧩 软件架构示例

我们追求代码的简洁与模块化。在 `F103` 阶段，核心业务逻辑通过以下方式驱动：

```c
/* 典型的 X-Y 连接与视觉更新流程 */
ch446q_connect(x_source, y_dest);    // 硬件物理连通
ws2812_update_visual(y_dest);        // UI 实时反馈显示
```

---

### 🤝 关于我们

**高电位队**
专注于单片机与FPGA电子开发与原型设计。团队成员涵盖硬件、嵌入式软件、PCB 设计等领域，力求推动实验平台的发展与普及。

*   **核心领域**：微控制器应用、矩阵算法实现、PCB 设计。
*   **致谢**：感谢 [JumperlessV5](https://github.com/Architeuthis-Flux/JumperlessV5) 提供的卓越灵感。

---
> **源码指引**：Stage 1 的完整代码存放在 `code/F103_ch446q_ws2812` 目录下，欢迎交流。
