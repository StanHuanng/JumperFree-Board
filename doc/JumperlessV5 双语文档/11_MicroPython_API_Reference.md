# Jumperless MicroPython API Reference Jumperless MicroPython API 参考手册

This document provides a comprehensive reference for the `jumperless` MicroPython module, which allows for direct control over the Jumperless hardware.

本文档为 `jumperless` MicroPython 模块提供了详尽的参考，该模块允许直接控制 Jumperless 硬件。

## A Note on Usage 使用说明

All functions and constants from the `jumperless` module are automatically imported into the global namespace. This means you can call them directly (e.g., `connect(1, 5)`) without needing the `jumperless.` prefix.

`jumperless` 模块中的所有函数和常量都会自动导入到全局命名空间中。这意味着你可以直接调用它们（例如 `connect(1, 5)`），而无需加上 `jumperless.` 前缀。

There are three primary ways to specify nodes in functions:

在函数中指定节点（Node）主要有三种方式：

1. **By Number**: Use the integer corresponding to the breadboard row (1-60).

   **通过数字**：使用对应面包板行号的整数（1-60）。

2. **By String Name**: Use a case-insensitive string for any named node (e.g., `"d13"`, `"TOP_RAIL"`).

   **通过字符串名称**：使用任何命名节点的大小写不敏感字符串（例如 `"d13"`, `"TOP_RAIL"`）。

3. **By Constant**: Use the predefined, case-sensitive constant for a node (e.g., `D13`, `TOP_RAIL`).

   **通过常量**：使用预定义的、区分大小写的节点常量（例如 `D13`, `TOP_RAIL`）。

------

[DAC](#dac-digital-to-analog-converter DAC (数模转换器)) (Digital-to-Analog Converter) - *[Examples](./08_MicroPython.md#DAC (Output Voltage) DAC (输出电压))*:

[DAC](#dac-digital-to-analog-converter DAC (数模转换器)) (数模转换器) - *[示例](./08_MicroPython.md#DAC (Output Voltage) DAC (输出电压))*:

- `dac_set(channel, voltage)` - Set DAC output voltage

  `dac_set(channel, voltage)` - 设置 DAC 输出电压

- `dac_get(channel)` - Get DAC output voltage

  `dac_get(channel)` - 获取 DAC 输出电压

- `set_dac(channel, voltage)` - Alias for dac_set

  `set_dac(channel, voltage)` - `dac_set` 的别名

- `get_dac`(channel) \- Alias for dac_get

  `get_dac(channel)` - `dac_get` 的别名
  
```
channel: 0-3, DAC0, DAC1, TOP_RAIL, BOTTOM_RAIL
channel 0/DAC0: DAC 0
channel 1/DAC1: DAC 1
channel 2/TOP_RAIL: top rail
channel 3/BOTTOM_RAIL: bottom rail
voltage: -8.0 to 8.0V
```

[ADC](#ADC (Analog-to-Digital Converter) ADC (模数转换器)) (Analog-to-Digital Converter) - *[Examples](./08_MicroPython.md#ADC (Measure Voltage) ADC (测量电压))*:

[ADC](#ADC (Analog-to-Digital Converter) ADC (模数转换器)) (模数转换器) - *[示例](./08_MicroPython.md#ADC (Measure Voltage) ADC (测量电压))*:

- `adc_get(channel)` - Read ADC input voltage

  `adc_get(channel)` - 读取 ADC 输入电压

- `get_adc(channel)` - Alias for adc_get

  `get_adc(channel)` - `adc_get` 的别名
  
```
channel: 0-4 (and 7 for the probe tip in Measure mode)
```

[INA](#INA (Current/Power Monitor) INA (电流/功率监测)) (Current/Power Monitor) - *[Examples](./08_MicroPython.md#Current Sensing (INA219) 电流感应 (INA219))*:

[INA](#INA (Current/Power Monitor) INA (电流/功率监测)) (电流/功率监测) - *[示例](./08_MicroPython.md#Current Sensing (INA219) 电流感应 (INA219))*:

- `ina_get_current(sensor)` - Read current in amps

  `ina_get_current(sensor)` - 读取电流（安培）

- `ina_get_voltage(sensor)` - Read shunt voltage

  `ina_get_voltage(sensor)` - 读取分流电压

- `ina_get_bus_voltage(sensor)` - Read bus voltage

  `ina_get_bus_voltage(sensor)` - 读取总线电压

- `ina_get_power(sensor)` - Read power in watts

  `ina_get_power(sensor)` - 读取功率（瓦特）

Aliases: `get_current`, `get_voltage`, `get_bus_voltage`, `get_power`

别名: `get_current`, `get_voltage`, `get_bus_voltage`, `get_power`

```
sensor: 0 or 1
```

[GPIO](#GPIO (General Purpose Input/Output) GPIO (通用输入/输出)) - *[Examples](./08_MicroPython.md#GPIO (General Purpose I/O) GPIO (通用输入/输出))*:

[GPIO](#GPIO (General Purpose Input/Output) GPIO (通用输入/输出)) (通用输入/输出) - *[示例](./08_MicroPython.md#GPIO (General Purpose I/O) GPIO (通用输入/输出))*:

- `gpio_set(pin, value)` - Set GPIO pin state

  `gpio_set(pin, value)` - 设置 GPIO 引脚状态

- `gpio_get(pin)` - Read GPIO pin state

  `gpio_get(pin)` - 读取 GPIO 引脚状态

- `gpio_set_dir(pin, direction)` - Set GPIO pin direction

  `gpio_set_dir(pin, direction)` - 设置 GPIO 引脚方向

- `gpio_get_dir(pin)` - Get GPIO pin direction

  `gpio_get_dir(pin)` - 获取 GPIO 引脚方向

- `gpio_set_pull(pin, pull)` - Set GPIO pull-up/down

  `gpio_set_pull(pin, pull)` - 设置 GPIO 上拉/下拉

- `gpio_get_pull(pin)` - Get GPIO pull-up/down

  `gpio_get_pull(pin)` - 获取 GPIO 上拉/下拉配置

Aliases: `set_gpio`, `get_gpio`, `set_gpio_dir`, `get_gpio_dir`, etc.

别名: `set_gpio`, `get_gpio`, `set_gpio_dir`, `get_gpio_dir` 等。

```
      pin 1-8: GPIO 1-8
      pin   9: UART Tx
      pin  10: UART Rx
        value: True/False   for HIGH/LOW
    direction: True/False   for OUTPUT/INPUT
         pull: -1/0/1       for PULL_DOWN/NONE/PULL_UP
```

[PWM](#PWM (Pulse-Width Modulation) PWM (脉冲宽度调制)) (Pulse Width Modulation) - *[Examples](./08_MicroPython.md#PWM (Pulse Width Modulation) PWM (脉冲宽度调制))*:

[PWM](#PWM (Pulse-Width Modulation) PWM (脉冲宽度调制)) (脉冲宽度调制) - *[示例](./08_MicroPython.md#PWM (Pulse Width Modulation) PWM (脉冲宽度调制))*:

- `pwm(pin, [frequency], [duty])` - Setup PWM on GPIO pin

  `pwm(pin, [frequency], [duty])` - 在 GPIO 引脚上设置 PWM

- `pwm_set_duty_cycle(pin, duty)` - Set PWM duty cycle

  `pwm_set_duty_cycle(pin, duty)` - 设置 PWM 占空比

- `pwm_set_frequency(pin, freq)` - Set PWM frequency

  `pwm_set_frequency(pin, freq)` - 设置 PWM 频率

- `pwm_stop(pin)` - Stop PWM on pin

  `pwm_stop(pin)` - 停止该引脚上的 PWM

Aliases: `set_pwm`, `set_pwm_duty_cycle`, `set_pwm_frequency`, `stop_pwm`

别名: `set_pwm`, `set_pwm_duty_cycle`, `set_pwm_frequency`, `stop_pwm`

```
         pin: 1-8         GPIO pins only
   frequency: 0.001-62500000 default 1000Hz
  duty_cycle: 0.0-1.0     default 0.5 (50%)
```

**Frequency Ranges:**

**频率范围：**

- Hardware PWM: 10Hz to 62.5MHz (high precision)

  硬件 PWM: 10Hz 到 62.5MHz (高精度)

- Slow PWM: 0.001Hz to 10Hz (hardware timer based)

  慢速 PWM: 0.001Hz 到 10Hz (基于硬件定时器)

- Automatic mode selection based on frequency

  基于频率自动选择模式

[Node Connections](#Node Connections 节点连接) - *[Examples](./08_MicroPython.md#Node Connections 节点连接)*:

[Node Connections](#Node Connections 节点连接) (节点连接) - *[示例](./08_MicroPython.md#Node Connections 节点连接)*:

- `connect(node1, node2)` - Connect two nodes

  `connect(node1, node2)` - 连接两个节点

- `disconnect(node1, node2)` - Disconnect nodes

  `disconnect(node1, node2)` - 断开节点连接

- `is_connected(node1, node2)` - Check if nodes are connected

  `is_connected(node1, node2)` - 检查节点是否已连接

- `nodes_clear()` - Clear all connections

  `nodes_clear()` - 清除所有连接

- `nodes_save([slot])` - Save connections to slot

  `nodes_save([slot])` - 保存连接到插槽

- `nodes_discard()` - Discard unsaved changes

  `nodes_discard()` - 丢弃未保存的更改

- `nodes_has_changes()` - Check for unsaved changes

  `nodes_has_changes()` - 检查是否有未保存的更改

- `switch_slot(slot)` - Switch to a different slot

  `switch_slot(slot)` - 切换到不同的插槽
```
set node2 to -1 to disconnect everything connected to node1
```

[Net Information](#Net Information API 网络信息 API):

[Net Information](#Net Information API 网络信息 API) (网络信息):

- `get_net_name(netNum)` - Get the name of a net

  `get_net_name(netNum)` - 获取网络名称

- `set_net_name(netNum, name)` - Set a custom net name

  `set_net_name(netNum, name)` - 设置自定义网络名称

- `get_net_color(netNum)` - Get net color as 0xRRGGBB

  `get_net_color(netNum)` - 获取网络颜色 (0xRRGGBB)

- `get_net_color_name(netNum)` - Get net color as name string

  `get_net_color_name(netNum)` - 获取网络颜色名称字符串

- `set_net_color(netNum, color)` - Set net color by name or RGB

  `set_net_color(netNum, color)` - 通过名称或 RGB 设置网络颜色

- `get_num_nets()` - Get number of active nets

  `get_num_nets()` - 获取活跃网络数量

- `get_num_bridges()` - Get number of bridges

  `get_num_bridges()` - 获取桥接数量

- `get_net_nodes(netNum)` - Get comma-separated node list

  `get_net_nodes(netNum)` - 获取逗号分隔的节点列表

- `get_bridge(bridgeIdx)` - Get bridge info tuple

  `get_bridge(bridgeIdx)` - 获取桥接信息元组

- `get_net_info(netNum)` - Get full net info as dict

  `get_net_info(netNum)` - 获取完整的网络信息字典

[OLED Display](#OLED Display OLED 显示屏) - *[Examples](./08_MicroPython.md#OLED Display OLED 显示屏)*:

[OLED Display](#OLED Display OLED 显示屏) (OLED 显示屏) - *[示例](./08_MicroPython.md#OLED Display OLED 显示屏)*:

- `oled_print("text")` - Display text

  `oled_print("text")` - 显示文本

- `oled_clear()` - Clear display

  `oled_clear()` - 清除显示

- `oled_connect()` - Connect OLED

  `oled_connect()` - 连接 OLED

- `oled_disconnect()` - Disconnect OLED

  `oled_disconnect()` - 断开 OLED

[Status](#Status Functions 状态函数) - *[Examples](#The entire output of help() help() 的完整输出)*:

[Status](#Status Functions 状态函数) (状态) - *[示例](#The entire output of help() help() 的完整输出)*:

- `print_bridges()` - Print all bridges

  `print_bridges()` - 打印所有桥接

- `print_paths()` - Print path between nodes

  `print_paths()` - 打印节点间的路径

- `print_crossbars()` - Print crossbar array

  `print_crossbars()` - 打印纵横开关矩阵 (crossbar) 数组

- `print_nets()` - Print nets

  `print_nets()` - 打印网络

- `print_chip_status()` - Print chip status

  `print_chip_status()` - 打印芯片状态

[Probe Functions](#Probe 探针) - *[Examples](./08_MicroPython.md#Probe Functions 探针函数)*:

[Probe Functions](#Probe 探针) (探针功能) - *[示例](./08_MicroPython.md#Probe Functions 探针函数)*:

- `probe_read_blocking()` - Wait for probe touch (don't return until a pad is touched)

  `probe_read_blocking()` - 等待探针触摸 (直到触摸焊盘才返回)

- `probe_read_nonblocking()` - Check probe immediately (return -1 if no pad is touched)

  `probe_read_nonblocking()` - 立即检查探针 (如果未触摸焊盘则返回 -1)

- `get_button([blocking=True])` - Get button state (default: blocking)

  `get_button([blocking=True])` - 获取按钮状态 (默认: 阻塞)

- `probe_button([blocking=True])` - Get button state (default: blocking)

  `probe_button([blocking=True])` - 获取按钮状态 (默认: 阻塞)

- `probe_button_blocking()` - Wait for button press

  `probe_button_blocking()` - 等待按钮按下

- `probe_button_nonblocking()` - Check buttons immediately

  `probe_button_nonblocking()` - 立即检查按钮

- `check_button()` - Check for probe button presses

  `check_button()` - 检查探针按钮按下

```
  Touch returns: ProbePad object (1-60, D13_PAD, TOP_RAIL_PAD, LOGO_PAD_TOP, etc.)
  Button returns: CONNECT, REMOVE, or NONE (front=connect, rear=remove)
```

[JFS](./09_JFS(Jumperless_FileSystem)_Module) (Jumperless File System):

[JFS](./09_JFS(Jumperless_FileSystem)_Module) (Jumperless 文件系统):

- `jfs.open(path, mode)` - Opens file, returns file handle

  `jfs.open(path, mode)` - 打开文件，返回文件句柄

- `jfs.read(file, size=1024)` - Read from file

  `jfs.read(file, size=1024)` - 读取文件

- `jfs.write(file, data)` - Write to file

  `jfs.write(file, data)` - 写入文件

- `jfs.close(file)` - Close file

  `jfs.close(file)` - 关闭文件

- `jfs.seek(file, position, whence=0)` - Seek in file

  `jfs.seek(file, position, whence=0)` - 文件指针定位

- `jfs.tell(file)` - Get current position

  `jfs.tell(file)` - 获取当前位置

- `jfs.size(file)` - Get file size

  `jfs.size(file)` - 获取文件大小

- `jfs.available(file)` - Get bytes available

  `jfs.available(file)` - 获取可用字节数

- `jfs.exists(path)` - Check if path exists (returns True/False)

  `jfs.exists(path)` - 检查路径是否存在 (返回 True/False)

- `jfs.listdir(path)` - List directory contents (returns list)

  `jfs.listdir(path)` - 列出目录内容 (返回列表)

- `jfs.mkdir(path)` - Create directory

  `jfs.mkdir(path)` - 创建目录

- `jfs.rmdir(path)` - Remove directory

  `jfs.rmdir(path)` - 删除目录

- `jfs.remove(path)` - Remove file

  `jfs.remove(path)` - 删除文件

- `jfs.rename(from, to)` - Rename/move file

  `jfs.rename(from, to)` - 重命名/移动文件

- `jfs.stat(path)` - Get file/directory status info

  `jfs.stat(path)` - 获取文件/目录状态信息

- `jfs.info()` - Returns (total, used, free) tuple

  `jfs.info()` - 返回 (total, used, free) 元组

[Misc](#System Functions 系统函数) - *[Examples](./08_MicroPython.md#System Functions 系统函数)*:

[Misc](#System Functions 系统函数) (杂项) - *[示例](./08_MicroPython.md#System Functions 系统函数)*:

- `arduino_reset()` - Reset Arduino

  `arduino_reset()` - 重置 Arduino

- `run_app('appName')` - Run app

  `run_app('appName')` - 运行应用

- `pause_core2(pause)` - Pause/resume core2 processing

  `pause_core2(pause)` - 暂停/恢复 core2 处理

- `send_raw(chip, x, y, setOrClear)` - Send raw data to core2

  `send_raw(chip, x, y, setOrClear)` - 发送原始数据到 core2

- `context_toggle()` - Toggle connection context (global/python)

  `context_toggle()` - 切换连接上下文 (global/python)

- `context_get()` - Get current context name

  `context_get()` - 获取当前上下文名称

[Help](#Help Functions 帮助函数) - *[Examples](#The entire output of help() help() 的完整输出)*:

[Help](#Help Functions 帮助函数) (帮助) - *[示例](#The entire output of help() help() 的完整输出)*:

- `help()` - Display help

  `help()` - 显示帮助

- `nodes_help()` - Show available nodes and how to address them

  `nodes_help()` - 显示可用节点及其寻址方式

------

## Node Connections 节点连接

These functions manage the connections between nodes on the breadboard and special function pins.

这些函数管理面包板上的节点与特殊功能引脚之间的连接。

### `connect(node1, node2)`

Creates a bridge between two nodes.

在两个节点之间建立桥接。

- `node1`, `node2`: The nodes to connect. Can be integers, strings, or constants.

  `node1`, `node2`: 要连接的节点。可以是整数、字符串或常量。

- `save` (optional): If `True` (default), the connection is saved to the current slot's node file. If `False`, it's a temporary connection for the current session.

  `save` (可选): 如果为 `True` (默认)，连接将保存到当前插槽的节点文件中。如果为 `False`，则为当前会话的临时连接。

**Example:**

**示例:**

```
# Connect breadboard row 1 to row 30
connect(1, 30)

# Connect Arduino D13 to the top power rail
connect(D13, TOP_RAIL)

# Connect GPIO 1 to ADC 0 using strings
connect("GPIO_1", "ADC0")
```

### `disconnect(node1, node2)`

Removes a specific bridge between two nodes.

移除两个节点之间的特定桥接。

- `node1`, `node2`: The two nodes to disconnect.

  `node1`, `node2`: 要断开连接的两个节点。

- To remove all connections from a single node, set `node2` to `-1`.

  要移除某个节点的所有连接，请将 `node2` 设置为 `-1`。

**Example:**

**示例:**

```
# Remove the bridge between rows 1 and 30
disconnect(1, 30)

# Remove all connections from GPIO_1
disconnect(GPIO_1, -1)
```

### `is_connected(node1, node2)`

Checks if a direct or indirect connection exists between two nodes.

检查两个节点之间是否存在直接或间接连接。

- Returns a custom `ConnectionState` object which evaluates to `True` if connected (`CONNECTED`) and `False` if not (`DISCONNECTED`).

  返回一个自定义 `ConnectionState` 对象，如果已连接则该对象估值为 `True` (`CONNECTED`)，未连接则为 `False` (`DISCONNECTED`)。

**Example:**

**示例:**

```
if is_connected(D13, TOP_RAIL):
    print("D13 is connected to the top rail.")

state = is_connected(1, 2)
print(state)  # Prints "CONNECTED" or "DISCONNECTED"
```

### `nodes_clear()`

Removes all connections from the board.

移除板上的所有连接。

**Example:**

**示例:**

```
nodes_clear()
print("All connections cleared.")
```

### `node(name_or_id)`

Creates a node object from a string name or integer ID. This is useful for storing a node reference in a variable.

从字符串名称或整数 ID 创建节点对象。这对于将节点引用存储在变量中很有用。

**Node Type:**

**节点类型:**

`Node` objects support arithmetic and comparison operations with integers:

`Node` 对象支持与整数进行算术和比较运算：

- **Comparisons**: `==`, `!=`, `<`, `<=`, `>`, `>=`

  **比较**: `==`, `!=`, `<`, `<=`, `>`, `>=`

- **Arithmetic**: `+`, `-`, `*`, `//`, `%`

  **算术**: `+`, `-`, `*`, `//`, `%`

- **Conversions**: `int(node)` converts to integer value

  **转换**: `int(node)` 转换为整数值

**Example:**

**示例:**

```
my_pin = node("D7")
led_pin = node(15)

connect(my_pin, led_pin)
oled_print(my_pin) # Displays 'D7' on the OLED

# Arithmetic and comparison work!
if my_pin <= 20:
    next_pin = my_pin + 1  # Returns int 8
    connect(next_pin, led_pin)
```

### `nodes_save([slot])`

Saves the current connections to a slot file.

将当前连接保存到插槽文件。

- `slot` (optional): The slot number to save to. Defaults to the current active slot.

  `slot` (可选): 要保存到的插槽编号。默认为当前活动插槽。

- Returns the slot number that was saved to.

  返回保存到的插槽编号。

**Example:**

**示例:**

```
# Save to current slot
nodes_save()

# Save to a specific slot
nodes_save(3)
```

### `nodes_discard()`

Discards all unsaved changes and restores the last saved state.

丢弃所有未保存的更改并恢复上次保存的状态。

**Example:**

**示例:**

```
connect(1, 5)  # Make a change
nodes_discard()  # Undo it
```

### `nodes_has_changes()`

Checks if there are unsaved changes since the last save.

检查自上次保存以来是否有未保存的更改。

- Returns `True` if there are unsaved changes, `False` otherwise.

  如果有未保存的更改返回 `True`，否则返回 `False`。

**Example:**

**示例:**

```
if nodes_has_changes():
    print("You have unsaved changes!")
```

### `switch_slot(slot)`

Switches to a different connection slot.

切换到不同的连接插槽。

- `slot`: The slot number to switch to (0-7).

  `slot`: 要切换到的插槽编号 (0-7)。

- Returns the previous slot number.

  返回之前的插槽编号。

**Example:**

**示例:**

```
old_slot = switch_slot(2)  # Switch to slot 2
print("Was in slot: " + str(old_slot))
```

------

## Net Information API 网络信息 API

Functions for querying and modifying net metadata. Nets are groups of connected nodes.

用于查询和修改网络元数据的函数。网络（Nets）是一组连接在一起的节点。

### `get_net_name(netNum)`

Gets the name of a specific net.

获取特定网络的名称。

- `netNum`: The net number (0 to number of nets - 1).

  `netNum`: 网络编号 (0 到 网络总数 - 1)。

- Returns the net name string, or `None` if the net doesn't exist.

  返回网络名称字符串，如果网络不存在则返回 `None`。

**Example:**

**示例:**

```
name = get_net_name(0)
print("Net 0 is called: " + str(name))
```

### `set_net_name(netNum, name)`

Sets a custom name for a net.

为网络设置自定义名称。

- `netNum`: The net number.

  `netNum`: 网络编号。

- `name`: The new name string. Pass empty string or `None` to reset to default.

  `name`: 新名称字符串。传递空字符串或 `None` 可重置为默认值。

**Example:**

**示例:**

```
set_net_name(0, "VCC")
set_net_name(1, "Signal_A")
```

### `get_net_color(netNum)`

Gets the color of a net as a 32-bit RGB value.

获取网络的 32 位 RGB 颜色值。

- `netNum`: The net number.

  `netNum`: 网络编号。

- Returns the color as `0xRRGGBB`.

  返回 `0xRRGGBB` 格式的颜色。

**Example:**

**示例:**

```
color = get_net_color(0)
print("Net color: " + hex(color))  # e.g., "0xff0000" for red
```

### `get_net_color_name(netNum)`

Gets the color name of a net as a human-readable string.

以人类可读的字符串形式获取网络的颜色名称。

- `netNum`: The net number.

  `netNum`: 网络编号。

- Returns a color name like "red", "blue", "green", etc.

  返回颜色名称，如 "red", "blue", "green" 等。

**Example:**

**示例:**

```
color_name = get_net_color_name(0)
print("Net 0 is " + color_name)  # e.g., "Net 0 is red"
```

### `set_net_color(netNum, color, [r], [g], [b])`

Sets the color of a net by name, hex string, or RGB values.

通过名称、十六进制字符串或 RGB 值设置网络颜色。

- `netNum`: The net number.

  `netNum`: 网络编号。

- `color`: Color as a name ("red", "blue", "pink") or hex string ("#FF0000", "0xFF0000").

  `color`: 颜色名称 ("red", "blue", "pink") 或十六进制字符串 ("#FF0000", "0xFF0000")。

- `r`, `g`, `b` (optional): If providing RGB values directly, pass them as separate arguments.

  `r`, `g`, `b` (可选): 如果直接提供 RGB 值，请作为单独的参数传递。

- Returns `1` on success, `0` on failure (invalid color).

  成功返回 `1`，失败（无效颜色）返回 `0`。

**Available color names:** red, orange, amber, yellow, chartreuse, green, seafoam, cyan, blue, royal blue, indigo, violet, purple, pink, magenta, brown, white, black, grey

**可用颜色名称:** red, orange, amber, yellow, chartreuse, green, seafoam, cyan, blue, royal blue, indigo, violet, purple, pink, magenta, brown, white, black, grey

**Example:**

**示例:**

```
# Set by color name
set_net_color(0, "red")
set_net_color(1, "cyan")

# Set by hex string
set_net_color(2, "#FF00FF")  # Magenta
set_net_color(3, "0x00FF00")  # Green

# Set by RGB values
set_net_color(4, 255, 128, 0)  # Orange
```

### `set_net_color_hsv(netNum, h, [s], [v])`

Sets the color of a net using HSV (Hue, Saturation, Value) color space. Automatically detects whether you're using normalized (0.0-1.0) or full-range (0-255) values based on the hue parameter.

使用 HSV（色相、饱和度、明度）色彩空间设置网络颜色。根据色相参数自动检测是使用归一化值 (0.0-1.0) 还是全范围值 (0-255)。

- `netNum`: The net number.

  `netNum`: 网络编号。

- `h`: Hue value. If `h` is between 0.0-1.0, all HSV values are treated as normalized (0.0-1.0). Otherwise, values are treated as 0-255 range.

  `h`: 色相值 (Hue)。如果 `h` 在 0.0-1.0 之间，所有 HSV 值均被视为归一化值 (0.0-1.0)。否则，值被视为 0-255 范围。

- `s` (optional): Saturation value. Defaults to maximum saturation (255) if not provided or negative.

  `s` (可选): 饱和度 (Saturation)。如果未提供或为负数，默认为最大饱和度 (255)。

- `v` (optional): Value/brightness. Defaults to 32 (reasonable LED brightness) if not provided or negative.

  `v` (可选): 明度/亮度 (Value)。如果未提供或为负数，默认为 32 (合理的 LED 亮度)。

- Returns `1` on success, `0` on failure.

  成功返回 `1`，失败返回 `0`。

**Range auto-detection:**

**范围自动检测:**

- If `h` ≤ 1.0: Normalized mode (0.0-1.0 for all values)

  如果 `h` ≤ 1.0: 归一化模式 (所有值均为 0.0-1.0)

- If `h` > 1.0: Full-range mode (0-255 for all values)

  如果 `h` > 1.0: 全范围模式 (所有值均为 0-255)

**Default brightness (32):** This provides good visibility without being overly bright. For maximum brightness, explicitly set `v` to 1.0 (normalized) or 255 (full-range).

**默认亮度 (32):** 提供良好的可见性且不过亮。要获得最大亮度，请显式将 `v` 设置为 1.0 (归一化) 或 255 (全范围)。

**Example:**

**示例:**

```
# Normalized mode (0.0-1.0) - detected because h <= 1.0
set_net_color_hsv(0, 0.0)           # Pure red, max saturation, default brightness (32)
set_net_color_hsv(1, 0.33)          # Green, max saturation, default brightness (32)
set_net_color_hsv(2, 0.66)          # Blue, max saturation, default brightness (32)
set_net_color_hsv(3, 0.5, 0.8)      # Cyan with 80% saturation, default brightness (32)
set_net_color_hsv(4, 0.5, 1.0, 0.5) # Cyan with max saturation, 50% brightness
set_net_color_hsv(5, 0.0, 1.0, 1.0) # Pure red at MAXIMUM brightness (255)

# Full-range mode (0-255) - detected because h > 1.0
set_net_color_hsv(6, 0)             # Pure red, max saturation, default brightness (32)
set_net_color_hsv(7, 85)            # Green (85 ≈ 255/3), default brightness (32)
set_net_color_hsv(8, 170)           # Blue (170 ≈ 2*255/3), default brightness (32)
set_net_color_hsv(9, 128, 200)      # Cyan-ish with 200/255 saturation, default brightness
set_net_color_hsv(10, 128, 255, 128)# Cyan with max saturation, 50% brightness
set_net_color_hsv(11, 128, 255, 255)# Cyan at MAXIMUM brightness (255)

# Using all defaults (h only)
set_net_color_hsv(12, 0.25)         # Yellow with full saturation, brightness 32
set_net_color_hsv(13, 64)           # Yellow in 0-255 mode, brightness 32
```

**Why use HSV?** HSV is often more intuitive for color selection than RGB:

**为什么使用 HSV?** HSV 在选择颜色时通常比 RGB 更直观：

- **Hue** represents the actual color (red → yellow → green → cyan → blue → magenta → red)

  **Hue (色相)** 代表实际颜色 (红 → 黄 → 绿 → 青 → 蓝 → 品红 → 红)

- **Saturation** controls color intensity (0 = grayscale, max = vivid color)

  **Saturation (饱和度)** 控制颜色强度 (0 = 灰度, max = 鲜艳颜色)

- **Value** controls brightness (0 = black, max = full brightness)

  **Value (明度)** 控制亮度 (0 = 黑, max = 全亮)

### `get_num_nets()`

Gets the number of currently active nets.

获取当前活跃网络的数量。

- Returns an integer.

  返回整数。

**Example:**

**示例:**

```
num = get_num_nets()
print("There are " + str(num) + " nets")
```

### `get_num_bridges()`

Gets the total number of bridges (connections).

获取桥接（连接）的总数。

- Returns an integer.

  返回整数。

**Example:**

**示例:**

```
num = get_num_bridges()
print("There are " + str(num) + " bridges")
```

### `get_net_nodes(netNum)`

Gets all nodes in a net as a comma-separated string.

获取网络中的所有节点，返回逗号分隔的字符串。

- `netNum`: The net number.

  `netNum`: 网络编号。

- Returns a string like "D13,TOP_RAIL,GPIO_1".

  返回类似 "D13,TOP_RAIL,GPIO_1" 的字符串。

**Example:**

**示例:**

```
nodes = get_net_nodes(0)
print("Net 0 contains: " + nodes)
```

### `get_bridge(bridgeIdx)`

Gets information about a specific bridge.

获取特定桥接的信息。

- `bridgeIdx`: The bridge index (0 to number of bridges - 1).

  `bridgeIdx`: 桥接索引 (0 到 桥接数量 - 1)。

- Returns a tuple `(node1, node2, duplicates)`.

  返回元组 `(node1, node2, duplicates)`。

**Example:**

**示例:**

```
bridge = get_bridge(0)
print("Bridge 0: " + str(bridge[0]) + " to " + str(bridge[1]))
```

### `get_net_info(netNum)`

Gets comprehensive information about a net as a dictionary.

以字典形式获取关于网络的综合信息。

- `netNum`: The net number.

  `netNum`: 网络编号。

- Returns a dict with keys: `name`, `number`, `color`, `color_name`, `nodes`.

  返回包含以下键的字典: `name`, `number`, `color`, `color_name`, `nodes`.

**Example:**

**示例:**

```
info = get_net_info(0)
print("Net name: " + info['name'])
print("Net color: " + info['color_name'])
print("Net nodes: " + info['nodes'])
```

------

## DAC (Digital-to-Analog Converter) DAC (数模转换器)

Functions for controlling the analog voltage outputs.

用于控制模拟电压输出的函数。

### `dac_set(channel, voltage, [save=True])`

Sets the output voltage for a specific DAC channel.

设置特定 DAC 通道的输出电压。

- `channel`: The DAC channel to set. Can be an integer (0-3) or a node constant (`DAC0`, `DAC1`, `TOP_RAIL`, `BOTTOM_RAIL`).

  `channel`: 要设置的 DAC 通道。可以是整数 (0-3) 或节点常量 (`DAC0`, `DAC1`, `TOP_RAIL`, `BOTTOM_RAIL`).

- `voltage`: The desired voltage (from -8.0V to 8.0V).

  `voltage`: 期望电压 (-8.0V 到 8.0V).

- `save` (optional): If `True` (default), the setting is saved to the config file.

  `save` (可选): 如果为 `True` (默认)，设置将保存到配置文件。

- **Aliases**: `set_dac()`

  **别名**: `set_dac()`

**Channels:** 

通道:

* `0` or `DAC0`: The 5V tolerant DAC output.

  `0` 或 `DAC0`: 5V 耐受 DAC 输出。

* `1` or `DAC1`: The 8V tolerant DAC output.

  `1` 或 `DAC1`: 8V 耐受 DAC 输出。

* `2` or `TOP_RAIL`: The top power rail.

  `2` 或 `TOP_RAIL`: 顶部电源轨。

* `3` or `BOTTOM_RAIL`: The bottom power rail.

  `3` 或 `BOTTOM_RAIL`: 底部电源轨。

**Example:**

**示例:**

```
# Set the top rail to 5V
dac_set(TOP_RAIL, 5.0)

# Set DAC0 to 1.25V
set_dac(DAC0, 1.25)
```

### `dac_get(channel)`

Reads the currently set voltage for a DAC channel.

读取 DAC 通道当前设置的电压。

- `channel`: The DAC channel to read.

  `channel`: 要读取的 DAC 通道。

- Returns a float.

  `channel`: 要读取的 DAC 通道。

- **Aliases**: `get_dac()`

  **别名**: `get_dac()`

**Example:**

**示例:**

```
voltage = dac_get(TOP_RAIL)
print("Top Rail voltage: " + str(voltage))
```

------

## ADC (Analog-to-Digital Converter) ADC (模数转换器)

Functions for measuring analog voltages.

用于测量模拟电压的函数。

### `adc_get(channel)`

Reads the voltage from a specific ADC channel.

从特定 ADC 通道读取电压。

- `channel`: The ADC channel to read (0-4).

  `channel`: 要读取的 ADC 通道 (0-4)。

- Returns a float.

  返回浮点数。

- **Aliases**: `get_adc()`

  **别名**: `get_adc()`

**Channels:** 

通道:

* `0-3`: 8V tolerant ADC inputs.

  `0-3`: 8V 耐受 ADC 输入。

* `4`: 5V tolerant ADC input.

  `4`: 5V 耐受 ADC 输入。

**Example:**

**示例:**

```
voltage = adc_get(0)
print("ADC0 voltage: " + str(voltage))
```

------

## GPIO (General Purpose Input/Output) GPIO (通用输入/输出)

Functions for controlling the digital I/O pins.

用于控制数字 I/O 引脚的函数。

### `gpio_set(pin, value)`

Sets the output state of a GPIO pin.

设置 GPIO 引脚的输出状态。

- `pin`: The GPIO pin number (1-10).

  `pin`: GPIO 引脚编号 (1-10)。

- `value`: `True` for HIGH, `False` for LOW.

  `value`: `True` 为高电平 (HIGH)，`False` 为低电平 (LOW)。

- **Aliases**: `set_gpio()`

  **别名**: `set_gpio()`

### `gpio_get(pin)`

Reads the state of a GPIO pin.

读取 GPIO 引脚的状态。

- `pin`: The GPIO pin number (1-10).

  `pin`: GPIO 引脚编号 (1-10)。

- Returns a `GPIOState` object (`HIGH`, `LOW`, or `FLOATING`).

  返回 `GPIOState` 对象 (`HIGH`, `LOW`, 或 `FLOATING`)。

- **Aliases**: `get_gpio()`

  **别名**: `get_gpio()`

### `gpio_set_dir(pin, direction)`

Sets the direction of a GPIO pin.

设置 GPIO 引脚的方向。

- `pin`: The GPIO pin number (1-10).

  `pin`: GPIO 引脚编号 (1-10)。

- `direction`: `True` for OUTPUT, `False` for INPUT.

  `direction`: `True` 为输出 (OUTPUT)，`False` 为输入 (INPUT)。

- **Aliases**: `set_gpio_dir()`

  **别名**: `set_gpio_dir()`

### `gpio_get_dir(pin)`

Reads the direction of a GPIO pin.

读取 GPIO 引脚的方向。

- `pin`: The GPIO pin number (1-10).

  `pin`: GPIO 引脚编号 (1-10)。

- Returns a `GPIODirection` object (`INPUT` or `OUTPUT`).

  返回 `GPIODirection` 对象 (`INPUT` 或 `OUTPUT`)。

- **Aliases**: `get_gpio_dir()`

  **别名**: `get_gpio_dir()`

### `gpio_set_pull(pin, pull)`

Configures the internal pull resistor for a GPIO pin.

配置 GPIO 引脚的内部上拉电阻。

- `pin`: The GPIO pin number (1-10).

  `pin`: GPIO 引脚编号 (1-10)。

- `pull`: `1` for PULLUP, `-1` for PULLDOWN, `0` for NONE.

  `pull`: `1` 为上拉 (PULLUP)，`-1` 为下拉 (PULLDOWN)，`0` 为无 (NONE)。

- **Aliases**: `set_gpio_pull()`

  **别名**: `set_gpio_pull()`

### `gpio_get_pull(pin)`

Reads the pull resistor configuration of a GPIO pin.

读取 GPIO 引脚的上拉电阻配置。

- `pin`: The GPIO pin number (1-10).

  `pin`: GPIO 引脚编号 (1-10)。

- Returns a `GPIOPull` object (`PULLUP`, `PULLDOWN`, or `NONE`).

  返回 `GPIOPull` 对象 (`PULLUP`, `PULLDOWN`, 或 `NONE`)。

- **Aliases**: `get_gpio_pull()`

  **别名**: `get_gpio_pull()`

**Pinout:** 

**引脚分布:**

* `1-8`: Routable GPIO pins `GPIO_1` to `GPIO_8`.

  `1-8`: 可路由的 GPIO 引脚 `GPIO_1` 到 `GPIO_8`.

* `9`: `UART_TX`.

  `9`: `UART_TX`.

* `10`: `UART_RX`.

  `10`: `UART_RX`.

**Example:**

**示例:**

```
# Set GPIO 1 as an output and turn it on
gpio_set_dir(1, True)
gpio_set(1, True)

# Set GPIO 2 as an input with a pull-up
gpio_set_dir(2, False)
gpio_set_pull(2, 1)

# Read the state of GPIO 2
state = gpio_get(2)
if state:  # GPIOState is truthy when HIGH, falsy when LOW or FLOATING
    print("GPIO 2 is HIGH")
# You can also print it directly - shows "HIGH", "LOW", or "FLOATING"
print("State: " + str(state))
```

------

## PWM (Pulse-Width Modulation) PWM (脉冲宽度调制)

Functions for generating PWM signals on GPIO pins.

在 GPIO 引脚上生成 PWM 信号的函数。

### `pwm(pin, [frequency], [duty_cycle])`

Sets up and starts a PWM signal on a GPIO pin.

在 GPIO 引脚上设置并启动 PWM 信号。

- `pin`: The GPIO pin to use (1-8).

  `pin`: 要使用的 GPIO 引脚 (1-8)。

- `frequency` (optional): The PWM frequency in Hz (0.001 to 62500000). Defaults to 1000.

  `frequency` (可选): PWM 频率，单位 Hz (0.001 到 62500000)。默认为 1000。

- `duty_cycle` (optional): The duty cycle from 0.0 to 1.0. Defaults to 0.5.

  `duty_cycle` (可选): 占空比，从 0.0 到 1.0。默认为 0.5。

- **Aliases**: `set_pwm()`

  **别名**: `set_pwm()`

**Frequency Ranges:**

**频率范围:**

* **Hardware PWM**: 10Hz to 62.5MHz (high precision, hardware peripheral)

  **硬件 PWM**: 10Hz 到 62.5MHz (高精度，硬件外设)

* **Slow PWM**: 0.001Hz to 10Hz (hardware timer based, precise timing)

  **慢速 PWM**: 0.001Hz 到 10Hz (基于硬件定时器，精确定时)

* **Automatic Selection**: System automatically chooses the appropriate mode based on frequency

  **自动选择**: 系统根据频率自动选择合适的模式

### `pwm_set_duty_cycle(pin, duty_cycle)`

Changes the duty cycle of an existing PWM signal.

更改现有 PWM 信号的占空比。

- `pin`: The GPIO pin number (1-8).

  `pin`: GPIO 引脚编号 (1-8)。

- `duty_cycle`: The new duty cycle (0.0 to 1.0).

  `duty_cycle`: 新的占空比 (0.0 到 1.0)。

- **Aliases**: `set_pwm_duty_cycle()`

  **别名**: `set_pwm_duty_cycle()`

### `pwm_set_frequency(pin, frequency)`

Changes the frequency of an existing PWM signal.

更改现有 PWM 信号的频率。

- `pin`: The GPIO pin number (1-8).

  `pin`: GPIO 引脚编号 (1-8)。

- `frequency`: The new frequency in Hz (0.001 to 62500000).

  `frequency`: 新的频率，单位 Hz (0.001 到 62500000)。

- **Aliases**: `set_pwm_frequency()`

  **别名**: `set_pwm_frequency()`

### `pwm_stop(pin)`

Stops the PWM signal on a GPIO pin.

停止 GPIO 引脚上的 PWM 信号。

- `pin`: The GPIO pin number (1-8).

  `pin`: GPIO 引脚编号 (1-8)。

- **Aliases**: `stop_pwm()`

  **别名**: `stop_pwm()`

**Example:**

**示例:**

```
# Hardware PWM: 1kHz, 25% duty cycle on GPIO_1
pwm(GPIO_1, 1000, 0.25)

# Slow PWM: 0.1Hz (10 second period), 50% duty cycle on GPIO_2
pwm(GPIO_2, 0.1, 0.5)

# Ultra-slow PWM: 0.001Hz (1000 second period), 25% duty cycle on GPIO_3
pwm(GPIO_3, 0.001, 0.25)

# Change the duty cycle to 75%
pwm_set_duty_cycle(GPIO_1, 0.75)

# Change frequency (will automatically switch between hardware/slow PWM)
pwm_set_frequency(GPIO_1, 500)  # 500Hz (hardware PWM)
pwm_set_frequency(GPIO_1, 5)    # 5Hz (slow PWM)

# Stop the PWM signal
pwm_stop(GPIO_1)
```

------

## WaveGen (Waveform Generator) WaveGen (波形发生器)

Functions for generating analog waveforms on DAC outputs.

用于在 DAC 输出上生成模拟波形的函数。

**Setters:**

**设置器 (Setters):**

- `wavegen_set_output(output)` - Select output: `DAC0`, `DAC1`, `TOP_RAIL`, `BOTTOM_RAIL` (default `DAC1`)

  `wavegen_set_output(output)` - 选择输出: `DAC0`, `DAC1`, `TOP_RAIL`, `BOTTOM_RAIL` (默认 `DAC1`)

- `wavegen_set_freq(hz)` - Set frequency: 0.0001–10000.0 Hz (default 100 Hz)

  `wavegen_set_freq(hz)` - 设置频率: 0.0001–10000.0 Hz (默认 100 Hz)

- `wavegen_set_wave(shape)` - Set waveform shape (see constants below)

  `wavegen_set_wave(shape)` - 设置波形形状 (参见下方的常量)

- `wavegen_set_sweep(start_hz, end_hz, seconds)` - Configure a linear sweep

  `wavegen_set_sweep(start_hz, end_hz, seconds)` - 配置线性扫描

- `wavegen_set_amplitude(vpp)` - 0.0–16.0 Vpp (default 3.3 Vpp)

  `wavegen_set_amplitude(vpp)` - 0.0–16.0 Vpp (默认 3.3 Vpp)

- `wavegen_set_offset(v)` - -8.0–+8.0 V (default 1.65 V for 0–3.3 V centered)

  `wavegen_set_offset(v)` - -8.0–+8.0 V (默认 1.65 V，对应 0–3.3 V 的中心)

- `wavegen_start([run=True])` - Start/stop output; calling with False stops

  `wavegen_start([run=True])` - 启动/停止输出；调用 False 可停止

- `wavegen_stop()` - Stop output immediately

  `wavegen_stop()` - 立即停止输出

**Getters:**

**获取器 (Getters):**

- `wavegen_get_output()` - Get current output channel

  `wavegen_get_output()` - 获取当前输出通道

- `wavegen_get_freq()` - Get current frequency

  `wavegen_get_freq()` - 获取当前频率

- `wavegen_get_wave()` - Get current waveform

  `wavegen_get_wave()` - 获取当前波形

- `wavegen_get_amplitude()` - Get current amplitude (Vpp)

  `wavegen_get_amplitude()` - 获取当前幅度 (Vpp)

- `wavegen_get_offset()` - Get current offset

  `wavegen_get_offset()` - 获取当前偏移量

- `wavegen_is_running()` - Check if wavegen is active

  `wavegen_is_running()` - 检查波形发生器是否处于活动状态

**Aliases:** All setters/getters have `set_wavegen_*` and `get_wavegen_*` aliases.

**别名:** 所有设置器/获取器都有 `set_wavegen_*` 和 `get_wavegen_*` 别名。

**Waveform Constants:**

**波形常量:**

- `SINE` (0) - Sine wave

  `SINE` (0) - 正弦波

- `TRIANGLE` (1) - Triangle wave

  `TRIANGLE` (1) - 三角波

- `SAWTOOTH` (2) - Sawtooth/ramp wave

  `SAWTOOTH` (2) - 锯齿波/斜波

- `RAMP` (2) - Alias for SAWTOOTH

  `RAMP` (2) - SAWTOOTH 的别名

- `SQUARE` (3) - Square wave

  `SQUARE` (3) - 方波

- `ARBITRARY` (4) - Arbitrary waveform (not yet implemented)

  `ARBITRARY` (4) - 任意波形 (尚未实现)

**Example:**

**示例:**

```
# Generate a 100Hz sine wave on DAC1
wavegen_set_output(DAC1)
wavegen_set_wave(SINE)
wavegen_set_freq(100)
wavegen_set_amplitude(3.3)  # 3.3V peak-to-peak
wavegen_set_offset(1.65)    # Center at 1.65V (0-3.3V range)
wavegen_start()

# Check if running
if wavegen_is_running():
    print("Wavegen active at " + str(wavegen_get_freq()) + "Hz")

# Change waveform while running
wavegen_set_wave(TRIANGLE)

# Stop
wavegen_stop()
```

**Notes:**

**注意:**

- Wavegen runs on core 2 and is fully blocking while active; LEDs and routing updates pause until `wavegen_stop()`.

  波形发生器在 core 2 上运行，且在活动时是完全阻塞的；LED 和路由更新将暂停，直到调用 `wavegen_stop()`。

- Frequency, waveform, amplitude, and offset can be changed live while running.

  频率、波形、幅度和偏移量可以在运行时实时更改。

------

## INA (Current/Power Monitor) INA (电流/功率监测)

Functions for reading data from the INA219 current sensors.

用于从 INA219 电流传感器读取数据的函数。

### `ina_get_current(sensor)`

Reads the current in Amps. * `sensor`: The sensor to read (0 or 1). * **Aliases**: `get_current()`

读取电流（安培）。* `sensor`: 要读取的传感器 (0 或 1)。* **别名**: `get_current()`

### `ina_get_voltage(sensor)`

Reads the shunt voltage in Volts. * `sensor`: The sensor to read (0 or 1). * **Aliases**: `get_voltage()`

读取分流电压（伏特）。* `sensor`: 要读取的传感器 (0 或 1)。* **别名**: `get_voltage()`

### `ina_get_bus_voltage(sensor)`

Reads the bus voltage in Volts. * `sensor`: The sensor to read (0 or 1). * **Aliases**: `get_bus_voltage()`

读取总线电压（伏特）。* `sensor`: 要读取的传感器 (0 或 1)。* **别名**: `get_bus_voltage()`

### `ina_get_power(sensor)`

Reads the power in Watts. * `sensor`: The sensor to read (0 or 1). * **Aliases**: `get_power()`

读取功率（瓦特）。* `sensor`: 要读取的传感器 (0 或 1)。* **别名**: `get_power()`

**Example:**

**示例:**

```
current_mA = ina_get_current(0) * 1000
print("Current: " + str(current_mA) + " mA")
```

------

## OLED Display OLED 显示屏

Functions for controlling the onboard OLED display.

用于控制板载 OLED 显示屏的函数。

### `oled_print(text, [size=2])`

Displays text on the OLED screen. It can print strings, numbers, and custom Jumperless types.

在 OLED 屏幕上显示文本。可以打印字符串、数字和自定义 Jumperless 类型。

- `text`: The content to display.

  `text`: 要显示的内容。

- `size` (optional): The font size (1 or 2). Defaults to 2.

  `size` (可选): 字体大小 (1 或 2)。默认为 2。

### `oled_clear()`

Clears the OLED display.

清除 OLED 显示。

### `oled_show()`

Refreshes the OLED display to show the latest changes. (Note: Often not needed as `oled_print` handles this).

刷新 OLED 显示以显示最新更改。(注意: 通常不需要，因为 `oled_print` 会处理这个)。

### `oled_connect()`

Connects the I2C lines to the OLED display.

将 I2C 线路连接到 OLED 显示屏。

### `oled_disconnect()`

Disconnects the I2C lines from the OLED display.

断开 I2C 线路与 OLED 显示屏的连接。

**Example:**

**示例:**

```
oled_connect()
oled_print("Hello!")
time.sleep(2)
oled_clear()
oled_disconnect()
```

------

## Probe 探针

Functions for interacting with the physical probe.

用于与物理探针交互的函数。

### `probe_read([blocking=True])`

Reads the pad currently being touched by the probe.

读取探针当前触摸的焊盘。

- `blocking` (optional): If `True` (default), the function will wait until a pad is touched. If `False`, it returns immediately.

  `blocking` (可选): 如果为 `True` (默认)，函数将等待直到触摸焊盘。如果为 `False`，它立即返回。

- Returns a `ProbePad` object (e.g., `25`, `D13_PAD`, `NO_PAD`).

  返回 `ProbePad` 对象 (例如 `25`, `D13_PAD`, `NO_PAD`)。

- **Aliases**: `read_probe()`, `probe_read_blocking()`, `probe_read_nonblocking()`, `probe_wait()`, `wait_probe()`, `probe_touch()`, `wait_touch()`

  **别名**: `read_probe()`, `probe_read_blocking()`, `probe_read_nonblocking()`, `probe_wait()`, `wait_probe()`, `probe_touch()`, `wait_touch()`

**ProbePad Type:**

**ProbePad 类型:**

`ProbePad` objects support arithmetic and comparison operations with integers:

`ProbePad` 对象支持与整数进行算术和比较运算：

- **Comparisons**: `==`, `!=`, `<`, `<=`, `>`, `>=`

  **比较**: `==`, `!=`, `<`, `<=`, `>`, `>=`

- **Arithmetic**: `+`, `-`, `*`, `//`, `%`

  **算术**: `+`, `-`, `*`, `//`, `%`

- **Conversions**: `int(pad)` converts to integer value

  **转换**: `int(pad)` 转换为整数值

**Example:**

**示例:**

```
pad = probe_read(False)  # Non-blocking

if pad != NO_PAD:
    print(pad)
    if pad <= 60:  # Compare with integer
        node_1 = pad
        node_2 = pad + 3  # Arithmetic with integer
        if node_2 > 60:   # Works!
            node_2 -= 60
        connect(node_1, node_2)
```

### `probe_button([blocking=True], [consume=False])`

Reads the state of the buttons on the probe.

读取探针上的按钮状态。

- `blocking` (optional): If `True` (default), waits for a button press. If `False`, returns the current state immediately.

  `blocking` (可选): 如果为 `True` (默认)，等待按钮按下。如果为 `False`，立即返回当前状态。

- `consume` (optional): If `True`, clears the button press after reading (one-shot detection). If `False` (default), the button state persists while held, allowing repeated reads in a loop.

  `consume` (可选): 如果为 `True`，读取后清除按钮按下状态 (一次性检测)。如果为 `False` (默认)，按钮状态在按住时持续存在，允许在循环中重复读取。

- Returns a `ProbeButton` object (`CONNECT_BUTTON`, `REMOVE_BUTTON`, or `BUTTON_NONE`).

  返回 `ProbeButton` 对象 (`CONNECT_BUTTON`, `REMOVE_BUTTON`, 或 `BUTTON_NONE`)。

- **Aliases**: `get_button()`, `button_read()`, `read_button()`, `probe_button_blocking()`, `probe_button_nonblocking()`, `check_button()`, `button_check()`

  **别名**: `get_button()`, `button_read()`, `read_button()`, `probe_button_blocking()`, `probe_button_nonblocking()`, `check_button()`, `button_check()`

**Consume Behavior:**

**Consume (消耗/清除) 行为:**

- `consume=False` (default): Holding the button returns the same state repeatedly - **ideal for continuous control** (e.g., incrementing values while held)

  `consume=False` (默认): 按住按钮会重复返回相同的状态 - **适合连续控制** (例如按住时增加数值)

- `consume=True`: Each button press is detected only once - ideal for menu navigation or one-shot actions

  `consume=True`: 每次按下按钮仅检测一次 - 适合菜单导航或单次操作

**Example:**

**示例:**

```
# Continuous control - hold button to keep changing hue
while True:
    button = check_button()  # consume=False by default
    if button == BUTTON_CONNECT:
        hue += 1  # Keeps incrementing while button is held
        set_net_color_hsv(0, hue)
    elif button == BUTTON_REMOVE:
        hue -= 1  # Keeps decrementing while button is held
        set_net_color_hsv(0, hue)
    time.sleep(0.05)

# One-shot detection - each press counted once
presses = 0
while presses < 5:
    button = get_button(consume=True)  # Each press consumed
    if button == BUTTON_CONNECT:
        presses += 1
        print(f"Press #{presses}")
```

**Example:**

**示例:**

```
print("Touch a pad...")
pad = probe_read()
print("You touched: " + str(pad))

if pad == D13_PAD:
    print("That's the Arduino LED pin!")

print("Press a probe button...")
button = get_button()
if button == CONNECT_BUTTON:
    print("Connect button pressed.")
```

------

### `get_switch_position()`

Gets the current probe switch position.

获取当前探针开关位置。

- Returns: `0` (SWITCH_MEASURE), `1` (SWITCH_SELECT), or `-1` (SWITCH_UNKNOWN)

  返回: `0` (SWITCH_MEASURE / 测量), `1` (SWITCH_SELECT / 选择), 或 `-1` (SWITCH_UNKNOWN / 未知)

**Example:**

**示例:**

```
position = get_switch_position()
if position == SWITCH_MEASURE:
    print("Probe is in measure mode")
elif position == SWITCH_SELECT:
    print("Probe is in select mode")
```

### `set_switch_position(position)`

Manually sets the probe switch position.

手动设置探针开关位置。

- `position`: `0` (SWITCH_MEASURE), `1` (SWITCH_SELECT), or `-1` (SWITCH_UNKNOWN)

  `position`: `0` (SWITCH_MEASURE), `1` (SWITCH_SELECT), 或 `-1` (SWITCH_UNKNOWN)

**Example:**

**示例:**

```
set_switch_position(SWITCH_SELECT)  # Force select mode
```

### `check_switch_position()`

Checks the probe switch position using current sensing and updates the internal state.

使用电流感应检查探针开关位置并更新内部状态。

- Returns: Updated switch position

  返回: 更新后的开关位置

Uses hysteresis thresholds to prevent oscillation between modes:

使用滞后阈值防止模式间振荡：

- Switches to SELECT when current > high threshold

  电流 > 高阈值时切换到 SELECT (选择)

- Switches to MEASURE when current < low threshold

  电流 < 低阈值时切换到 MEASURE (测量)

**Example:**

**示例:**

```
# Periodically check and respond to switch changes
while True:
    position = check_switch_position()
    if position == SWITCH_MEASURE:
        voltage = measureMode()
        print(f"Voltage: {voltage}V")
    elif position == SWITCH_SELECT:
        pad = probe_read(blocking=False)
        if pad != NO_PAD:
            print(f"Touched: {pad}")
    time.sleep(0.1)
```

------

## Clickwheel 旋转编码器

Functions for reading the rotary encoder (clickwheel) position, direction, and button state.

用于读取旋转编码器（clickwheel）位置、方向和按钮状态的函数。

### `clickwheel_get_position()`

Gets the raw clickwheel position counter.

获取原始 clickwheel 位置计数器。

- Returns: Current position value (integer, can be positive or negative)

  返回: 当前位置值（整数，可正可负）

The position accumulates as you turn the clickwheel - clockwise increases, counter-clockwise decreases.

位置随着旋转 clickwheel 而累积 - 顺时针增加，逆时针减少。

**Example:**

**示例:**

```
pos = clickwheel_get_position()
print(f"Current position: {pos}")
```

### `clickwheel_reset_position()`

Resets the clickwheel position counter to 0.

将 clickwheel 位置计数器重置为 0。

**Example:**

**示例:**

```
clickwheel_reset_position()
assert clickwheel_get_position() == 0
```

### `clickwheel_get_direction([consume=True])`

Gets the current clickwheel direction event.

获取当前 clickwheel 方向事件。

- `consume` (optional): If `True` (default), clears the direction after reading (one-shot detection). If `False`, the direction persists until consumed.

  `consume` (可选): 如果为 `True` (默认)，读取后清除方向（一次性检测）。如果为 `False`，方向将持续存在直到被消耗。

- Returns: `CLICKWHEEL_NONE` (0), `CLICKWHEEL_UP` (1), or `CLICKWHEEL_DOWN` (2)

  返回: `CLICKWHEEL_NONE` (0), `CLICKWHEEL_UP` (1), 或 `CLICKWHEEL_DOWN` (2)

**Important:** The direction state **persists** until consumed! This means you won't miss turn events even if you don't check every loop iteration. The UP or DOWN state stays active until you read it with `consume=True`.

**重要:** 方向状态**持续存在**直到被消耗！这意味着即使你没有在每个循环迭代中检查，也不会错过旋转事件。UP 或 DOWN 状态会一直保持活跃，直到你使用 `consume=True` 读取它。

**Example (One-shot - Default):**

**示例 (一次性 - 默认):**

```
direction = clickwheel_get_direction()  # consume=True (default)
if direction == CLICKWHEEL_UP:
    value += 1  # Only increments once per turn event
    print(f"Turned up: {value}")
elif direction == CLICKWHEEL_DOWN:
    value -= 1  # Only decrements once per turn event
    print(f"Turned down: {value}")
```

**Example (Persistent - Check Multiple Times):**

**示例 (持久 - 多次检查):**

```
# Check direction without consuming
direction = clickwheel_get_direction(consume=False)

if direction == CLICKWHEEL_UP:
    print("Turning clockwise...")
    # Do some work...

    # Check again - still UP until consumed!
    if clickwheel_get_direction(consume=False) == CLICKWHEEL_UP:
        print("Still turning up!")

    # Finally consume it
    clickwheel_get_direction(consume=True)
```

### `clickwheel_get_button()`

Gets the current clickwheel button state.

获取当前 clickwheel 按钮状态。

- Returns:
  
  返回:
  
  - `CLICKWHEEL_IDLE` (0) - Not pressed
  
    `CLICKWHEEL_IDLE` (0) - 未按下
  
  - `CLICKWHEEL_PRESSED` (1) - Just pressed
  
    `CLICKWHEEL_PRESSED` (1) - 刚刚按下
  
  - `CLICKWHEEL_HELD` (2) - Being held down
  
    `CLICKWHEEL_HELD` (2) - 正在按住
  
  - `CLICKWHEEL_RELEASED` (3) - Just released
  
    `CLICKWHEEL_RELEASED` (3) - 刚刚释放
  
  - `CLICKWHEEL_DOUBLECLICKED` (4) - Double-clicked
  
    `CLICKWHEEL_DOUBLECLICKED` (4) - 双击

**Example:**

**示例:**

```
button = clickwheel_get_button()
if button == CLICKWHEEL_PRESSED:
    print("Button pressed!")
elif button == CLICKWHEEL_HELD:
    print("Button held down")
elif button == CLICKWHEEL_DOUBLECLICKED:
    print("Double click!")
```

### `clickwheel_is_initialized()`

Checks if the clickwheel hardware is initialized and ready.

检查 clickwheel 硬件是否已初始化并准备就绪。

- Returns: `True` if ready, `False` otherwise

  返回: 如果就绪则为 `True`，否则为 `False`

**Example:**

**示例:**

```
if clickwheel_is_initialized():
    pos = clickwheel_get_position()
else:
    print("Clickwheel not available")
```

**Complete Example - Menu Navigation:**

**完整示例 - 菜单导航:**

```
import jumperless as j
import time

menu_items = ["Option 1", "Option 2", "Option 3", "Option 4"]
selected = 0

j.clickwheel_reset_position()

while True:
    # Check direction (consume=True by default - one turn = one event)
    direction = j.clickwheel_get_direction()
    if direction == j.CLICKWHEEL_UP:
        selected = (selected + 1) % len(menu_items)
        print(f"> {menu_items[selected]}")
    elif direction == j.CLICKWHEEL_DOWN:
        selected = (selected - 1) % len(menu_items)
        print(f"> {menu_items[selected]}")

    # Check button
    button = j.clickwheel_get_button()
    if button == j.CLICKWHEEL_PRESSED:
        print(f"Selected: {menu_items[selected]}")
    elif button == j.CLICKWHEEL_DOUBLECLICKED:
        print("Exit menu")
        break

    # Note: Direction persists, so even with slow polling (50ms),
    # you won't miss turn events!
    time.sleep(0.05)
```

**Example - Value Adjustment with Persistence:**

**示例 - 带有持久性的数值调整:**

```
import jumperless as j
import time

value = 50

while True:
    # Check direction without consuming
    direction = j.clickwheel_get_direction(consume=False)

    if direction == j.CLICKWHEEL_UP:
        value = min(100, value + 1)
        j.oled_print(f"Value: {value}", 2)
        time.sleep(0.1)  # Delay for visual feedback
        # Consume after displaying
        j.clickwheel_get_direction(consume=True)

    elif direction == j.CLICKWHEEL_DOWN:
        value = max(0, value - 1)
        j.oled_print(f"Value: {value}", 2)
        time.sleep(0.1)
        j.clickwheel_get_direction(consume=True)

    # Exit on button press
    if j.clickwheel_get_button() == j.CLICKWHEEL_PRESSED:
        break

    time.sleep(0.01)
```

------

## System Functions 系统函数

### `arduino_reset()`

Resets the connected Arduino Nano.

重置连接的 Arduino Nano。

### `run_app(appName)`

Launches a built-in Jumperless application.

启动内置的 Jumperless 应用程序。

- `appName`: The name of the app to run (e.g., "File Manager", "I2C Scan").

  `appName`: 要运行的应用程序名称 (例如 "File Manager", "I2C Scan")。

### `pause_core2(pause)`

Pauses or resumes core2 processing.

暂停或恢复 core2 处理。

- `pause`: `True` to pause core2, `False` to resume.

  `pause`: `True` 暂停 core2，`False` 恢复。

*For doing time sensitive things where you don't want core 2 to cause timing glitches while it periodically updates the LEDs.* Core 2 will resume when you exit the REPL no matter what.

*用于执行对时间敏感的操作，以避免 core 2 在周期性更新 LED 时引起时序故障。* 无论如何，当你退出 REPL 时，Core 2 都会恢复。

### `send_raw(chip, x, y, setOrClear)`

Sends raw data to core2 for direct chip control.

向 core2 发送原始数据以直接控制芯片。

- `chip`: Chip identifier (string, e.g., "A", "B", "C").

  `chip`: 芯片标识符 (字符串，例如 "A", "B", "C")。

- `x`, `y`: Coordinates for the operation.

  `x`, `y`: 操作的坐标。

- `setOrClear`: `1` to set, `0` to clear.

  `setOrClear`: `1` 设置，`0` 清除。

You should probably be looking at the schematic if you use this. By bypassing all the routing logic, you can make or break connections in ~1 µs. Pretty handy if want to do high speed switching between known states.

如果你使用此功能，你可能应该查看原理图。通过绕过所有路由逻辑，你可以在约 1 µs 内建立或断开连接。如果你想在已知状态之间进行高速切换，这非常方便。

### `force_service(name)`

Forces immediate execution of a specific system service by name.

强制按名称立即执行特定的系统服务。

- `name`: Service name as a string (e.g., `"ProbeButton"`, `"Peripherals"`).

  `name`: 服务名称字符串 (例如 `"ProbeButton"`, `"Peripherals"`)。

- Returns: `True` if service was found and executed, `False` otherwise.

  返回: 如果找到并执行了服务，返回 `True`，否则返回 `False`。

Useful for manually triggering specific services during tight loops where automatic service scheduling might not run frequently enough.

对于在紧密循环中手动触发特定服务非常有用，因为自动服务调度可能运行得不够频繁。

**Example:**

**示例:**

```
while True:
    # Fast loop that might miss automatic service updates
    connect(1, 2)
    force_service("ProbeButton")  # Ensure button state updates
    button = check_button()
    time.sleep(0.001)
```

### `force_service_by_index(index)`

Forces immediate execution of a specific system service by index (faster than name lookup).

通过索引强制立即执行特定的系统服务 (比名称查找更快)。

- `index`: Service index (integer, obtained via `get_service_index()`).

  `index`: 服务索引 (整数，通过 `get_service_index()` 获取)。

- Returns: `True` if index valid and service executed, `False` otherwise.

  返回: 如果索引有效且服务已执行，返回 `True`，否则返回 `False`。

**Example:**

**示例:**

```
# Cache the index once for maximum speed
btn_idx = get_service_index("ProbeButton")

while True:
    connect(1, 2)
    force_service_by_index(btn_idx)  # Fastest way to force service
    button = check_button()
    time.sleep(0.001)
```

### `get_service_index(name)`

Gets the index of a service by name for use with `force_service_by_index()`.

通过名称获取服务索引，以便与 `force_service_by_index()` 一起使用。

- `name`: Service name as a string.

  `name`: 服务名称字符串。

- Returns: Service index (integer, 0 or higher), or `-1` if not found.

  返回: 服务索引 (整数，0 或更高)，如果未找到则返回 `-1`。

Cache the returned index for repeated fast calls to `force_service_by_index()`.

缓存返回的索引以供重复快速调用 `force_service_by_index()`。

**Example:**

**示例:**

```
# Look up once, use many times
probe_idx = get_service_index("ProbeButton")
if probe_idx >= 0:
    # Use the cached index in your loop
    force_service_by_index(probe_idx)
```

### `context_toggle()`

Toggles the connection context between `global` and `python` modes.

在 `global` (全局) 和 `python` 模式之间切换连接上下文。

- In **global** mode: Connection changes persist after exiting Python.

  在 **global** 模式下: 连接更改在退出 Python 后仍然存在。

- In **python** mode: Connection state is restored when you exit the REPL.

  在 **python** 模式下: 退出 REPL 时恢复连接状态。

**Example:**

**示例:**

```
context_toggle()  # Switch from global to python (or vice versa)
print("Now in " + context_get() + " mode")
```

### `context_get()`

Gets the current connection context name.

获取当前连接上下文名称。

- Returns `"global"` or `"python"`.

  返回 `"global"` 或 `"python"`。

**Example:**

**示例:**

```
if context_get() == "global":
    print("Changes will persist after exit")
else:
    print("Changes will be discarded on exit")
```

------

## Status Functions 状态函数

These functions print detailed status information to the serial console.

这些函数将详细的状态信息打印到串行控制台。

- `print_bridges()`: Prints all active bridges.

  `print_bridges()`: 打印所有活跃桥接。

- `print_paths()`: Prints all resolved paths between nodes.

  `print_paths()`: 打印节点间所有解析的路径。

- `print_crossbars()`: Prints the raw state of the crossbar matrix.

  `print_crossbars()`: 打印纵横开关矩阵 (crossbar) 的原始状态。

- `print_nets()`: Prints the current net list.

  `print_nets()`: 打印当前网络列表。

- `print_chip_status()`: Prints the status of the CH446Q chips.

  `print_chip_status()`: 打印 CH446Q 芯片的状态。

------

## Help Functions 帮助函数

### `help()`

Displays a comprehensive list of all available functions and constants in the `jumperless` module.

显示 `jumperless` 模块中所有可用函数和常量的综合列表。

You can also pass it sections, so `help("GPIO")` will just print that section.

你也可以传递部分名称，因此 `help("GPIO")` 只会打印该部分。

### `nodes_help()`

Displays a detailed reference for all available node names and their aliases.

显示所有可用节点名称及其别名的详细参考。

---

## Node Names and Constants 节点名称和常量

The Jumperless module provides extensive node name support with multiple aliases for each node:

Jumperless 模块提供了广泛的节点名称支持，每个节点有多个别名：

```
# Power rails (multiple aliases supported)
TOP_RAIL = 101        # Also: TOPRAIL, T_R, TOP_R
BOTTOM_RAIL = 102     # Also: BOT_RAIL, BOTTOMRAIL, BOTRAIL, B_R, BOT_R
SUPPLY_3V3 = 103      # Also: 3V3, 3.3V
SUPPLY_5V = 105       # Also: 5V, +5V
SUPPLY_8V_P = 120     # Also: 8V_P, 8V_POS
SUPPLY_8V_N = 121     # Also: 8V_N, 8V_NEG

# Ground connections
GND = 100             # Also: GROUND
TOP_RAIL_GND = 104    # Also: TOP_GND (not actually routable but included for PADs)
BOTTOM_RAIL_GND = 126 # Also: BOT_GND, BOTTOM_GND (not actually routable but included for PADs)

# DAC outputs
DAC0 = 106            # Also: DAC_0, DAC0_5V
DAC1 = 107            # Also: DAC_1, DAC1_8V

# ADC inputs
ADC0 = 110            # Also: ADC_0, ADC0_8V
ADC1 = 111            # Also: ADC_1, ADC1_8V
ADC2 = 112            # Also: ADC_2, ADC2_8V
ADC3 = 113            # Also: ADC_3, ADC3_8V
ADC4 = 114            # Also: ADC_4, ADC4_5V
ADC7 = 115            # Also: ADC_7, ADC7_PROBE, PROBE

# Current sensing
ISENSE_PLUS = 108     # Also: ISENSE_POS, ISENSE_P, INA_P, I_P, CURRENT_SENSE_PLUS, ISENSE_POSITIVE, I_POS
ISENSE_MINUS = 109    # Also: ISENSE_NEG, ISENSE_N, INA_N, I_N, CURRENT_SENSE_MINUS, ISENSE_NEGATIVE, I_NEG

# GPIO pins (multiple naming conventions)
GPIO_1 = 131          # Also: RP_GPIO_1, GPIO1, GP_1, GP1
GPIO_2 = 132          # Also: RP_GPIO_2, GPIO2, GP_2, GP2
GPIO_3 = 133          # Also: RP_GPIO_3, GPIO3, GP_3, GP3
GPIO_4 = 134          # Also: RP_GPIO_4, GPIO4, GP_4, GP4
GPIO_5 = 135          # Also: RP_GPIO_5, GPIO5, GP_5, GP5
GPIO_6 = 136          # Also: RP_GPIO_6, GPIO6, GP_6, GP6
GPIO_7 = 137          # Also: RP_GPIO_7, GPIO7, GP_7, GP7
GPIO_8 = 138          # Also: RP_GPIO_8, GPIO8, GP_8, GP8

# UART pins
UART_TX = 116         # Also: RP_UART_TX, TX, RP_GPIO_16
UART_RX = 117         # Also: RP_UART_RX, RX, RP_GPIO_17

# Additional RP GPIOs
RP_GPIO_18 = 118      # Also: GP_18
RP_GPIO_19 = 119      # Also: GP_19

# Buffer connections
BUFFER_IN = 139       # Also: ROUTABLE_BUFFER_IN, BUF_IN, BUFF_IN, BUFFIN
BUFFER_OUT = 140      # Also: ROUTABLE_BUFFER_OUT, BUF_OUT, BUFF_OUT, BUFFOUT

# Arduino Nano pins (extensive support)
D13 = 83              # Also: NANO_D13
D12 = 82              # Also: NANO_D12
D11 = 81              # Also: NANO_D11
D10 = 80              # Also: NANO_D10
D9 = 79               # Also: NANO_D9
D8 = 78               # Also: NANO_D8
D7 = 77               # Also: NANO_D7
D6 = 76               # Also: NANO_D6
D5 = 75               # Also: NANO_D5
D4 = 74               # Also: NANO_D4
D3 = 73               # Also: NANO_D3
D2 = 72               # Also: NANO_D2
D1 = 71               # Also: NANO_D1
D0 = 70               # Also: NANO_D0

# Arduino Nano analog pins
A0 = 86               # Also: NANO_A0
A1 = 87               # Also: NANO_A1
A2 = 88               # Also: NANO_A2
A3 = 89               # Also: NANO_A3
A4 = 90               # Also: NANO_A4
A5 = 91               # Also: NANO_A5
A6 = 92               # Also: NANO_A6
A7 = 93               # Also: NANO_A7

# Arduino Nano non-routable hardwired connections
VIN = 69              # Unconnected to anything
RST0 = 94             # Hardwired to GPIO 18 on the RP2350
RST1 = 95             # Hardwired to GPIO 19 on the RP2350
N_GND0 = 97           # GND
N_GND1 = 96           # GND
NANO_5V = 99          # Hardwired to USB 5V bus (can also be used to power the Jumperless)
NANO_3V3 = 98         # Unconnected (without bridging the solder jumper on the back)
```

---

## The entire output of help() help() 的完整输出

```
>>> help()
Jumperless Native MicroPython Module
Available help sections:

  help() or help("all")     - Show all functions
  help("DAC")              - DAC functions
  help("ADC")              - ADC functions
  help("GPIO")             - GPIO functions
  help("PWM")              - PWM functions
  help("WAVEGEN")          - Waveform generator
  help("INA")              - INA current/power monitor
  help("NODES")            - Node connections
  help("NETS")             - Net info (names, colors)
  help("SLOTS")            - Slot management
  help("OLED")             - OLED display
  help("PROBE")            - Probe and button functions
  help("CLICKWHEEL")       - Clickwheel (rotary encoder) functions
  help("STATUS")           - Status and debug functions
  help("FILESYSTEM")       - Filesystem functions
  help("MISC")             - Miscellaneous functions
  help("EXAMPLES")         - Usage examples

DAC (Digital-to-Analog Converter):

   dac_set(channel, voltage)         - Set DAC output voltage
   dac_get(channel)                  - Get DAC output voltage
   set_dac(channel, voltage)         - Alias for dac_set
   get_dac(channel)                  - Alias for dac_get

          channel: 0-3, DAC0, DAC1, TOP_RAIL, BOTTOM_RAIL
          channel 0/DAC0: DAC 0
          channel 1/DAC1: DAC 1
          channel 2/TOP_RAIL: top rail
          channel 3/BOTTOM_RAIL: bottom rail
          voltage: -8.0 to 8.0V

ADC (Analog-to-Digital Converter):

   adc_get(channel)                  - Read ADC input voltage
   get_adc(channel)                  - Alias for adc_get

                                              channel: 0-4

GPIO:

   gpio_set(pin, value)             - Set GPIO pin state
   gpio_get(pin)                    - Read GPIO pin state
   gpio_set_dir(pin, direction)     - Set GPIO pin direction
   gpio_get_dir(pin)                - Get GPIO pin direction
   gpio_set_pull(pin, pull)         - Set GPIO pull-up/down
   gpio_get_pull(pin)               - Get GPIO pull-up/down

  Aliases: set_gpio, get_gpio, set_gpio_dir, get_gpio_dir, etc.

            pin 1-8: GPIO 1-8
            pin   9: UART Tx
            pin  10: UART Rx
              value: True/False   for HIGH/LOW
          direction: True/False   for OUTPUT/INPUT
               pull: -1/0/1/2     for PULLDOWN/NO_PULL/PULLUP/BUS_KEEPER

PWM (Pulse Width Modulation):

   pwm(pin, [frequency], [duty])    - Setup PWM on GPIO pin
   pwm_set_duty_cycle(pin, duty)    - Set PWM duty cycle
   pwm_set_frequency(pin, freq)     - Set PWM frequency
   pwm_stop(pin)                    - Stop PWM on pin

  Aliases: set_pwm, set_pwm_duty_cycle, set_pwm_frequency, stop_pwm

             pin: 1-8       GPIO pins only
       frequency: 0.001Hz-62.5MHz default 1000Hz
      duty_cycle: 0.0-1.0   default 0.5 (50%)

WaveGen (Waveform Generator):

   wavegen_set_output(channel)      - Set output: DAC0, DAC1, TOP_RAIL, BOTTOM_RAIL
   wavegen_set_freq(hz)             - Set frequency (0.0001-10000 Hz)
   wavegen_set_wave(shape)          - Set waveform shape
   wavegen_set_amplitude(vpp)       - Set amplitude (0-16 Vpp)
   wavegen_set_offset(v)            - Set DC offset (-8 to +8 V)
   wavegen_start()                  - Start waveform generation
   wavegen_stop()                   - Stop waveform generation

  Getters: wavegen_get_output(), wavegen_get_freq(), wavegen_get_wave(),
           wavegen_get_amplitude(), wavegen_get_offset(), wavegen_is_running()

  Waveform constants: SINE, TRIANGLE, SAWTOOTH (RAMP), SQUARE

INA (Current/Power Monitor):

   ina_get_current(sensor)          - Read current in amps
   ina_get_voltage(sensor)          - Read shunt voltage
   ina_get_bus_voltage(sensor)      - Read bus voltage
   ina_get_power(sensor)            - Read power in watts

  Aliases: get_current, get_voltage, get_bus_voltage, get_power

             sensor: 0 or 1

Node Connections:

   connect(node1, node2)            - Connect two nodes
   disconnect(node1, node2)         - Disconnect nodes
   is_connected(node1, node2)       - Check if nodes are connected
   nodes_clear()                    - Clear all connections

         set node2 to -1 to disconnect everything connected to node1

Net Information:

   get_net_name(netNum)             - Get net name
   set_net_name(netNum, name)       - Set custom net name
   get_net_color(netNum)            - Get net color as 0xRRGGBB
   get_net_color_name(netNum)       - Get net color name
   set_net_color(netNum, color)     - Set net color by name or hex
   set_net_color_hsv(netNum, h, [s], [v]) - Set by HSV (auto-detects range)
   get_num_nets()                   - Get number of active nets
   get_num_bridges()                - Get number of bridges
   get_net_nodes(netNum)            - Get comma-separated node list
   get_bridge(bridgeIdx)            - Get bridge info tuple
   get_net_info(netNum)             - Get full net info as dict

  Colors: red, orange, yellow, green, cyan, blue, purple, pink, etc.
  HSV: h=0.0-1.0 or 0-255 (auto), s=0-1/0-255 (default max), v=0-1/0-255 (default 32)

Slot Management:

   nodes_save([slot])               - Save connections to slot
   nodes_discard()                  - Discard unsaved changes
   nodes_has_changes()              - Check for unsaved changes
   switch_slot(slot)                - Switch to different slot (0-7)
   CURRENT_SLOT                     - Get current slot number

  Context (controls persistence):
   context_toggle()                 - Toggle global/python mode
   context_get()                    - Get current mode name

OLED Display:

   oled_print("text")               - Display text
   oled_clear()                     - Clear display
   oled_connect()                   - Connect OLED
   oled_disconnect()                - Disconnect OLED

Probe Functions:

   probe_read([blocking=True])                - Read probe (default: blocking)
   read_probe([blocking=True])                - Read probe (default: blocking)
   probe_read_blocking()                      - Wait for probe touch (explicit)
   probe_read_nonblocking()                   - Check probe immediately (explicit)
   get_button([blocking], [consume])          - Get button (blocking=True, consume=False)
   probe_button([blocking], [consume])        - Get button (blocking=True, consume=False)
   check_button([consume])                    - Check button non-blocking (consume=False)
   probe_button_blocking([consume])           - Wait for button (consume=False)
   probe_button_nonblocking([consume])        - Check button immediate (consume=False)

  consume=False (default): Holding button returns same state (continuous control)
  consume=True: Each press detected once (one-shot detection)

  Probe Switch Functions:
   get_switch_position()                      - Get current switch position
   set_switch_position(pos)                   - Set switch position manually
   check_switch_position()                    - Check switch via current sensing

       Touch returns: ProbePad object (1-60, D13_PAD, TOP_RAIL_PAD, LOGO_PAD_TOP, etc.)
       Button returns: CONNECT, REMOVE, or NONE (front=connect, rear=remove)
       Switch returns: SWITCH_MEASURE (0), SWITCH_SELECT (1), SWITCH_UNKNOWN (-1)

Clickwheel (Rotary Encoder):

   clickwheel_get_position()                  - Get raw position counter
   clickwheel_reset_position()                - Reset position to 0
   clickwheel_get_direction([consume=True])   - Get direction event
   clickwheel_get_button()                    - Get button state
   clickwheel_is_initialized()                - Check if clickwheel is ready

  consume=True (default): Direction cleared after reading (one-shot detection)
  consume=False: Direction persists until consumed (can read multiple times)

  Direction returns: CLICKWHEEL_NONE (0), CLICKWHEEL_UP (1), CLICKWHEEL_DOWN (2)
  Button returns: CLICKWHEEL_IDLE (0), CLICKWHEEL_PRESSED (1), CLICKWHEEL_HELD (2),
                  CLICKWHEEL_RELEASED (3), CLICKWHEEL_DOUBLECLICKED (4)

Status:

   print_bridges()                  - Print all bridges
   print_paths()                    - Print path between nodes
   print_crossbars()                - Print crossbar array
   print_nets()                     - Print nets
   print_chip_status()              - Print chip status

Filesystem:

  jfs.open(path, mode)              - Open file
  jfs.read(file, size)              - Read from file
  jfs.write(file, data)             - Write to file
  jfs.close(file)                   - Close file
  jfs.exists(path)                  - Check if file exists
  jfs.listdir(path)                 - List directory
  jfs.mkdir(path)                   - Create directory
  jfs.remove(path)                  - Remove file
  jfs.rename(from, to)              - Rename file
  jfs.info()                        - Get filesystem info

Misc:

   arduino_reset()                  - Reset Arduino
   run_app(appName)                 - Run built-in app
   pause_core2(pause)               - Pause/unpause Core2 (True/False)
   send_raw(chip, x, y, set)        - Send raw data to crossbar chip
   force_service(name)              - Force run a specific service (e.g., "ProbeButton")
   force_service_by_index(idx)      - Force run service by index (faster)
   get_service_index(name)          - Get service index by name (cache for fast calls)

Examples (all functions available globally):

  dac_set(DAC0, 5.0)                         # Set DAC0 using node constant
  voltage = get_adc(1)                       # Read ADC1 using alias
  connect(TOP_RAIL, D13)                     # Connect using constants
  connect(4, 20)                             # Connect using numbers
  top_rail = node("TOP_RAIL")                # Create node object
  oled_print("Hello!")                       # Display text on OLED
  current = get_current(0)                   # Read current using alias
  set_gpio(1, True)                          # Set GPIO pin high
  pwm(1, 1000, 0.5)                          # 1kHz PWM, 50% duty
  wavegen_set_wave(SINE); wavegen_start()    # Start sine wave
  set_net_color(0, "red")                    # Color net 0 red
  set_net_color_hsv(1, 0.5)                  # Cyan net 1 (HSV hue)
  nodes_save()                               # Save current connections
  pad = probe_read()                         # Wait for probe touch
  button = get_button()                      # Wait for button press



>>> 
```

---

## The entire output of nodes_help() nodes_help() 的完整输出

```
>>> nodes_help()
Jumperless Node Reference
========================

NODE TYPES:
  Numbered:     1-60 (breadboard)
  Arduino:      D0-D13, A0-A7 (nano header)
  GPIO:         GPIO_1-GPIO_8 (routable GPIO)
  Power:        TOP_RAIL, BOTTOM_RAIL, GND
  DAC:          DAC0, DAC1 (analog outputs)
  ADC:          ADC0-ADC4, PROBE (analog inputs)
  Current:      ISENSE_PLUS, ISENSE_MINUS
  UART:         UART_TX, UART_RX
  Buffer:       BUFFER_IN, BUFFER_OUT

THREE WAYS TO USE NODES:

1. NUMBERS (direct breadboard holes):
   connect(1, 30)                     # Connect holes 1 and 30
   connect(15, 42)                    # Any number 1-60

2. STRINGS (case-insensitive names):
   connect("D13", "TOP_RAIL")         # Arduino pin to power rail
   connect("gpio_1", "adc0")          # GPIO to ADC (case-insensitive)
   connect("15", "dac1")              # Mix numbers and names

3. CONSTANTS (pre-defined objects):
   connect(TOP_RAIL, D13)            # Using imported constants
   connect(GPIO_1, A0)               # No quotes needed
   connect(DAC0, 25)                 # Mix constants and numbers

MIXED USAGE:
   my_pin = "D13"                    # Create node object from string
   connect(my_pin, TOP_RAIL)         # Use node object with constant
   oled_print(my_pin)                # Display shows 'D13'

COMMON ALIASES (many names work for same node):
   "TOP_RAIL" = "T_R"
   "GPIO_1" = "GPIO1" = "GP1"
   "DAC0" = "DAC_0"
   "UART_TX" = "TX"

NOTES:
  - String names are case-insensitive: "d13" = "D13" = "nAnO_d13"
  - Constants are case-sensitive: use D13, not d13
  - All three methods work in any function
```