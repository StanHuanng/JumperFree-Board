# Glossary of Terms 术语表

## Basic Concepts 基本概念

- `net` = a group of all the `node`s that are connected together (enter `n` to see the list)

  **`net` (网络)** = 所有连接在一起的 `node`（节点）的集合（输入 `n` 查看列表）。

- `node` = anything the crossbar array can connect to, which includes everything on the breadboard and Nano header, as well as the internal `special function` `node`s like `routable GPIO`, `ADC`s, `DAC`s

  **`node` (节点)** = 交叉开关阵列（crossbar array）可以连接的任何对象。这包括面包板和 Nano 排针上的所有内容，以及内部的 `special function`（特殊功能）`node`，例如 `routable GPIO`（可路由 GPIO）、`ADC`（模数转换器）、`DAC`（数模转换器）。

- `row` = *kinda* the same thing as `node` but I generally use it to mean stuff on the breadboard (so special function things like `routable GPIO`, `ADC`s, `DAC`s that don't have a set location are excluded)

  **`row` (排/行)** = *有点* 像 `node`，但我通常用它指代面包板上的东西（因此排除了没有固定位置的特殊功能组件，如 `routable GPIO`、`ADC`、`DAC`）。

- `rail` = I use this to refer to the 4 horizontal power rails on the top and bottom (`top_rail`, `bottom_rail`, `gnd`), I will never call a vertical `row` a `rail`. (I know they're columns but it's easier to say a lot)

  **`rail` (导轨)** = 我用这个词指代顶部和底部的 4 个水平电源导轨（`top_rail`、`bottom_rail`、`gnd`）。我绝不会把垂直的 `row` 称为 `rail`。（我知道它们在物理上是“列”，但叫 `rail` 说起来更顺口）。

- `bridge` = a pair of exactly two `node`s (this is what you're making when you connect stuff with the probe, enter `b` to see the bridge array)

  **`bridge` (桥接)** = 恰好由两个 `node` 组成的一对（这就是当你用探针连接东西时所创建的连接，输入 `b` 查看桥接阵列）。

- `path` = the set of crossbar connections needed to make a single `bridge`, so it can have multiple `hop`s if it doesn't have a direct connection and needs to make a `bounce` through an intermediate `chip` (enter `c` to see the crossbar array)

  **`path` (路径)** = 建立单个 `bridge` 所需的一组交叉开关连接。如果它没有直接连接，需要通过中间的 `chip` 进行 `bounce`（跳转/中转），那么它可能包含多个 `hop`（跳跃）（输入 `c` 查看交叉开关阵列）。

## Hardware 硬件

- `chip` = shorthand for the CH446Qs specifically, lettered A-L. The first 8 (A-H) are considered "breadboard `chips`", and the last 4 (I-L) are considered "special function" chips (enter `c` to see their connections)

  **`chip` (芯片)** = 特指 CH446Q 芯片的简称，编号为 A-L。前 8 个 (A-H) 被认为是“面包板 `chips`”，后 4 个 (I-L) 被认为是“特殊功能”芯片（输入 `c` 查看它们的连接）。

- `menu` = I generally mean the onboard clickwheel `menu` when I say this (`click` the wheel to enter those and `scroll` around.) Sometimes I mean the `main menu` which is the list of single character command that gets presented over serial.

  **`menu` (菜单)** = 当我提到这个词时，通常是指板载拨轮 `menu`（`click` 点击拨轮进入并在其中 `scroll` 滚动）。有时我是指 `main menu`（主菜单），即通过串口显示的单字符命令列表。

## Slots and Files 插槽与文件

- `slot` = one of **10** saved circuit configurations (slots 0-9) that you can switch between. Use `<` to cycle forward through slots, or use the menus to jump to a specific slot. The **active slot** is the one currently loaded and affecting the hardware.

  **`slot` (插槽)** = **10** 个已保存的电路配置（插槽 0-9）之一，你可以在它们之间切换。使用 `<` 向前循环切换插槽，或使用菜单跳转到特定插槽。**active slot**（活动插槽）是当前已加载并正在影响硬件的那个。

- `slot file` = a YAML file on the filesystem that stores a complete circuit configuration including bridges, power settings, and colors. Located at `/slots/slotN.yaml` where N is 0-9. These files are human-readable and can be edited directly!

  **`slot file` (插槽文件)** = 文件系统上的一个 YAML 文件，存储了完整的电路配置，包括桥接、电源设置和颜色。位于 `/slots/slotN.yaml`，其中 N 是 0-9。这些文件是人类可读的，可以直接编辑！

- `active slot` = the currently loaded slot. Only the active slot affects the hardware. Use `Q` command to query which slot is active. When you make connections with the probe, they're saved to the active slot automatically.

  **`active slot` (活动插槽)** = 当前加载的插槽。只有活动插槽会影响硬件。使用 `Q` 命令查询当前哪个插槽处于活动状态。当你使用探针进行连接时，它们会自动保存到活动插槽中。

## Slot Management Commands 插槽管理命令

- `<` = cycle to next slot (0→1→2...→7→0)

  `<` = 循环切换到下一个插槽 (0→1→2...→7→0)。

- `Q` = query which slot is currently active (returns `ACTIVE_SLOT:X`)

  `Q` = 查询当前哪个插槽处于活动状态（返回 `ACTIVE_SLOT:X`）。

- `Y` = print YAML

  `Y` = 打印 YAML 内容。

## YAML Format YAML 格式

Slot files use YAML format with named nodes for readability:

插槽文件使用 YAML 格式，并带有命名节点以提高可读性：

```
bridges:
  - {n1: 1, n2: 10, dup: 2, color: red}
  - {n1: NANO_D5, n2: GPIO_1, dup: 2}

power:
  topRail: 3.30
  bottomRail: 2.50
```

**Named nodes:** `NANO_D0-D13`, `NANO_A0-A7`, `GPIO_1-8`, `TOP_RAIL`, `BOTTOM_RAIL`, `GND`, `DAC0_5V`, `DAC1_5V`, etc.

**命名节点 (Named nodes):** `NANO_D0-D13`, `NANO_A0-A7`, `GPIO_1-8`, `TOP_RAIL`, `BOTTOM_RAIL`, `GND`, `DAC0_5V`, `DAC1_5V` 等。

You can view and edit these files in the [File Manager](./07_File_Manager.md) or via USB Mass Storage mode (`U` command).

你可以在 [文件管理器](./07_File_Manager.md) 中或通过 USB 大容量存储模式（`U` 命令）查看和编辑这些文件。

## Wokwi Import Wokwi 导入

`W` = Import circuit from [Wokwi](https://wokwi.com/) simulator

**`W`** = 从 [Wokwi](https://wokwi.com/) 模拟器导入电路。

1. Design circuit on wokwi.com

   在 wokwi.com 上设计电路。

2. Copy `diagram.json` content

   复制 `diagram.json` 的内容。

3. Type `W` in Jumperless

   在 Jumperless 中输入 `W`。

4. Paste JSON content

   粘贴 JSON 内容。

5. Circuit is converted and saved to active slot

   电路将被转换并保存到活动插槽。

The parser automatically maps Wokwi breadboard pins, Arduino Nano pins, and logic analyzer channels to Jumperless nodes, and preserves your wire colors from Wokwi!

解析器会自动将 Wokwi 面包板引脚、Arduino Nano 引脚和逻辑分析仪通道映射到 Jumperless 节点，并保留你在 Wokwi 中的连线颜色！