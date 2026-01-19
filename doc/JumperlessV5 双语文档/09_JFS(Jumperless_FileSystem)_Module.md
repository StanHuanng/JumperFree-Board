# JFS (Jumperless FileSystem) Module JFS (Jumperless FileSystem) 模块

The `jfs` module is basically like MicroPython's `vfs` and parts of `os`, but kinda written in a style that's probably more familiar to Arduino-style C++ people (me). It uses the *almost* standardized API shared by [`FatFS` (the one Jumperless actually uses), `LittleFS`, and `SDFS`](https://arduino-pico.readthedocs.io/en/latest/fs.html#file-system-object-littlefs-sd-sdfs-fatfs), but still has been *Pythonified* to use types that are easier to work with in MicroPython.

`jfs` 模块基本上类似于 MicroPython 的 `vfs` 和部分 `os` 模块，但它的编写风格可能对 Arduino 风格的 C++ 用户（比如作者我）来说更加熟悉。它使用了 [`FatFS`（Jumperless 实际使用的文件系统）、`LittleFS` 和 `SDFS`](https://www.google.com/search?q=[https://arduino-pico.readthedocs.io/en/latest/fs.html%23file-system-object-littlefs-sd-sdfs-fatfs](https://arduino-pico.readthedocs.io/en/latest/fs.html%23file-system-object-littlefs-sd-sdfs-fatfs)) 之间共享的*近乎*标准化的 API，但经过了“Python 化”处理，使用了在 MicroPython 中更易于操作的类型。

## Quick Reference 快速参考

File Operations:

文件操作：

- `jfs.open(path, mode)` - Opens file, returns file handle

  `jfs.open(path, mode)` - 打开文件，返回文件句柄

- `jfs.read(file, size=1024)` - Read from file

  `jfs.read(file, size=1024)` - 读取文件

- `jfs.write(file, data)` - Write to file

  `jfs.write(file, data)` - 写入文件

- `jfs.close(file)` - Close file

  `jfs.close(file)` - 关闭文件

- `jfs.seek(file, position, whence=0)` - Seek in file

  `jfs.seek(file, position, whence=0)` - 在文件中定位（移动指针）

- `jfs.tell(file)` - Get current position

  `jfs.tell(file)` - 获取当前位置

- `jfs.size(file)` - Get file size

  `jfs.size(file)` - 获取文件大小

- `jfs.available(file)` - Get bytes available

  `jfs.available(file)` - 获取可用字节数

File Object Methods (after `f = jfs.open(...)`):

文件对象方法（在 `f = jfs.open(...)` 之后）：

- `f.print(data)` - Print to the file (like `write` but auto-flushes)

  `f.print(data)` - 打印到文件（类似 `write` 但会自动刷新）

- `f.flush()` - Flush buffered data to file

  `f.flush()` - 将缓冲区数据刷新到文件

- `f.position()` - Alias for `f.tell()`

  `f.position()` - `f.tell()` 的别名

- `f.name()` - Get file name

  `f.name()` - 获取文件名

Directory Operations:

目录操作：

- `jfs.exists(path)` - Check if path exists (returns True/False)

  `jfs.exists(path)` - 检查路径是否存在（返回 True/False）

- `jfs.listdir(path)` - List directory contents (returns list)

  `jfs.listdir(path)` - 列出目录内容（返回列表）

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

Filesystem Info:

文件系统信息：

- `jfs.info()` - Returns (total, used, free) tuple

  `jfs.info()` - 返回 (总空间, 已用空间, 剩余空间) 的元组

---

## Usage 用法

```python
import jfs  #you don't actually need this, jfs is imported globally by default

# List files in the root directory
files = jfs.listdir('/')   # returns a python list
print(files)
```

Output:

输出：

```
['config.txt', 'nodeFileSlot0.txt', 'python_scripts/', 'nodeFileSlot1.txt', 'nodeFileSlot2.txt', 'nodeFileSlot3.txt', 'nodeFileSlot4.txt', 'nodeFileSlot5.txt', 'nodeFileSlot6.txt', 'nodeFileSlot7.txt', 'net_colors/']
```

If you want to make this print with subdirectories

如果你想打印包含子目录的内容：

```python
files = jfs.listdir('/')

for file in range(len(files)):

    print(files[file])

    if files[file].endswith("/"):
        subdir = jfs.listdir(files[file])

        for i in range(len(subdir)):
            print("     - " + subdir[i])
```

Output:

输出：

```
nodeFileSlot0.txt
python_scripts/
     - history.txt
     - examples/
     - fake_gpio.py
     - _temp_repl_edit.py
     - Hey.txt
     - script_1.py
     - script_2.py
     - script_3.py
     - log.txt
     - lib/
     - script_4.py
     - pathtest.py
nodeFileSlot1.txt
nodeFileSlot2.txt
nodeFileSlot3.txt
nodeFileSlot4.txt
nodeFileSlot5.txt
nodeFileSlot6.txt
nodeFileSlot7.txt
net_colors/
    - netColorsSlot0.txt
```

---

## File API 文件 API

File objects returned by `jfs.open()` support method calls directly on the object:

由 `jfs.open()` 返回的文件对象支持直接在该对象上调用方法：

```python
# Object-oriented file operations

# Write-only mode
f = jfs.open('hello.txt', 'w')
f.write('Hello, Jumperless!')
f.close()

# Read from the file (need to reopen or use w+/r+ mode)
f = jfs.open('hello.txt', 'r')
content = f.read()             # Read from file object
size = f.size()                # Get file size
f.close()

# Read-write mode (truncates file)
f = jfs.open('hello.txt', 'w+')
f.write('Hello, Jumperless!')
f.seek(0)                      # Seek to beginning to read what we wrote
content = f.read()             # Now this works!
f.close()

# Context manager support (automatically closes file)
with jfs.open('data.txt', 'w+') as f:
    f.write('This file will be automatically closed')
    f.seek(0)                  # Reset to beginning
    content = f.read()         # Read back what we wrote
    pos = f.tell()             # Get current position
    name = f.name()            # Get file name
```

### Using `f.print()` for logging 使用 `f.print()` 进行日志记录

The `f.print()` method works like Python's `print()` but writes to the file. It automatically converts arguments to strings and flushes after each call - perfect for logging:

`f.print()` 方法的工作方式类似于 Python 的 `print()`，但它是写入文件。它会自动将参数转换为字符串并在每次调用后刷新（flush）——非常适合用于日志记录：

```python
# Great for logging - auto-converts types and flushes immediately
with jfs.open('log.txt', 'w+') as f:
    f.print("Starting test...")
    voltage = adc_get(0)
    f.print("Voltage:", voltage, "V")    # Multiple args work
    f.print("Test complete!")

# Unlike f.write(), f.print() handles non-strings automatically
f = jfs.open('data.txt', 'w')
f.print(123)           # OK - converts int to string
f.print(3.14)          # OK - converts float to string
f.print("mixed", 42)   # OK - multiple args joined with spaces
f.close()
```

**Note:** `f.print()` is a file object method only. There is no `jfs.print()` module-level function.

**注意：** `f.print()` 仅作为文件对象的方法存在。不存在 `jfs.print()` 这样的模块级函数。

Other ways to do the same thing

你也可以对文件句柄使用模块级函数：

### Module-Level Functions You can also use module-level functions with file handles: 你也可以对文件句柄使用模块级函数：

```python
f = jfs.open('hello.txt', 'w')
jfs.write(f, 'Hello, Jumperless!')  # Module-level function
jfs.seek(f, 0)                      # Module-level function  
content = jfs.read(f)               # Module-level function
jfs.close(f)                        # Module-level function
```

### Direct String Operations (For simple cases) 直接字符串操作（针对简单情况）

```python
# Write/read entire files at once (no file handles needed)
jfs.write('config.txt', 'key=value\nother=setting')
content = jfs.read('config.txt')
```

---

## File Modes 文件模式

When using `jfs.open(path, mode)`, the following modes are supported:

使用 `jfs.open(path, mode)` 时，支持以下模式：

| Mode   | Description   | Read | Write | Create |
| ------ | ------------- | ---- | ----- | ------ |
| `'r'`  | Read only     | ✅    | ❌     | ❌      |
| `'w'`  | Write only    | ❌    | ✅     | ✅      |
| `'a'`  | Append only   | ❌    | ✅     | ✅      |
| `'r+'` | Read + Write  | ✅    | ✅     | ❌      |
| `'w+'` | Read + Write  | ✅    | ✅     | ✅      |
| `'a+'` | Read + Append | ✅    | ✅     | ✅      |

**Important:** You cannot read from a file opened in write-only mode (`'w'` or `'a'`). Use `'w+'`, `'r+'`, or `'a+'` if you need both read and write access.

**重要提示：** 你不能从以只写模式（`'w'` 或 `'a'`）打开的文件中读取内容。如果需要同时进行读写访问，请使用 `'w+'`、`'r+'` 或 `'a+'`。

---

## Open a file for writing 打开文件进行写入

```python
f = jfs.open('hello.txt', 'w')
f.write('Hello, Jumperless!')  # Now works with object-oriented API!
f.close()
```

---

## Directory Operations 目录操作

### `jfs.listdir(path)`

Returns a list containing the names of the entries in the directory given by `path`.

返回一个包含由 `path` 指定的目录中条目名称的列表。

- `path` (str): The path to the directory.

  `path` (str): 目录的路径。

**Example:**

示例：

```python
# List contents of the root directory
print(jfs.listdir('/'))

# List contents of a subdirectory
jfs.mkdir('/my_dir')
print(jfs.listdir('/my_dir'))
```

### `jfs.mkdir(path)`

Create a new directory.

创建一个新目录。

- `path` (str): The path of the new directory.

  `path` (str): 新目录的路径。

### `jfs.rmdir(path)`

Remove an empty directory.

移除一个空目录。

- `path` (str): The path of the directory to remove.

  移除一个空目录。

### `jfs.remove(path)`

Remove a file.

移除一个文件。

- `path` (str): The path of the file to remove.

  `path` (str): 要移除的文件路径。

### `jfs.rename(old_path, new_path)`

Rename a file or directory.

重命名文件或目录。

- `old_path` (str): The current path.

  `old_path` (str): 当前路径。

- `new_path` (str): The new path.

  `new_path` (str): 新路径。

### `jfs.exists(path)`

Check if a file or directory exists.

检查文件或目录是否存在。

- `path` (str): The path to check.

  `path` (str): 要检查的路径。

- Returns `True` if it exists, `False` otherwise.

  如果存在返回 `True`，否则返回 `False`。

### `jfs.stat(path)`

Get status of a file or directory.

获取文件或目录的状态。

- `path` (str): The path of the file or directory.

  `path` (str): 文件或目录的路径。

- Returns a tuple with file information (mode, size, etc.), similar to `os.stat()`.

  返回一个包含文件信息（模式、大小等）的元组，类似于 `os.stat()`。

---

## Filesystem Information 文件系统信息

### `jfs.info()`

Get information about the filesystem.

获取关于文件系统的信息。

- Returns a tuple `(total_bytes, used_bytes, free_bytes)`.

  返回一个元组 `(total_bytes, used_bytes, free_bytes)`（总字节数，已用字节数，可用字节数）。

**Example:**

**示例：**

```python
total, used, free = jfs.info()
print("Filesystem Size: " + str(total / 1024) + " KB")
print("Used: " + str(used / 1024) + " KB")
print("Free: " + str(free / 1024) + " KB")
```

---

## File I/O 文件 I/O

The `jfs` module supports standard file opening and handling using `jfs.open()` and file objects, including support for the `with` statement for automatic resource management.

`jfs` 模块支持使用 `jfs.open()` 和文件对象进行标准的文件打开和处理，包括支持 `with` 语句以进行自动资源管理。

### `jfs.open(path, mode='r')`

Open a file and return a corresponding file object.

打开一个文件并返回相应的文件对象。

- `path` (str): The path to the file.

  `path` (str): 文件的路径。

- `mode` (str, optional): The mode in which the file is opened. Defaults to `'r'`.

  `mode` (str, 可选): 文件打开的模式。默认为 `'r'`。
  
  - `'r'`: Read (default).
  
    `'r'`: 读取（默认）。
  
  - `'w'`: Write (creates a new file or truncates an existing one).
  
    `'w'`: 写入（创建一个新文件或截断现有文件）。
  
  - `'a'`: Append.
  
    `'a'`: 追加。
  
  - `'r+'`: Read and write.
  
    `'r+'`: 读取和写入。
  
  - `'w+'`: Write and read (creates/truncates).
  
    `'w+'`: 写入和读取（创建/截断）。
  
  - `'a+'`: Append and read.
  
    `'a+'`: 追加和读取。

**Example:**

**示例：**

```python
# Open a file for reading
f = jfs.open('config.txt', 'r')
content = f.read()
f.close()

# Use 'with' for automatic closing
with jfs.open('data.log', 'a') as log_file:
    log_file.write('New log entry.\\n')
```

---

## File Object Methods 文件对象方法

The file object returned by `jfs.open()` has the following methods:

由 `jfs.open()` 返回的文件对象具有以下方法：

### `file.read([size])`

Read `size` bytes from the file. If `size` is omitted or negative, the entire file is read.

从文件中读取 `size` 字节。如果省略 `size` 或为负数，则读取整个文件。

### `file.write(data)`

Write the given string or bytes `data` to the file. Returns the number of bytes written.

将给定的字符串或字节 `data` 写入文件。返回写入的字节数。

### `file.close()`

Close the file. A closed file cannot be read or written to.

关闭文件。已关闭的文件不能被读取或写入。

### `file.seek(offset, [whence])`

Change the stream position.

改变流的位置（指针）。

* `offset`: The byte offset.

  `offset`: 字节偏移量。

* `whence` (optional):

  `whence` (可选):

  - `0`: Seek from the start of the stream (default). Use `jfs.SEEK_SET`.

    `0`: 从流的开头开始定位（默认）。使用 `jfs.SEEK_SET`。

  - `1`: Seek from the current position. Use `jfs.SEEK_CUR`.

    `1`: 从当前位置开始定位。使用 `jfs.SEEK_CUR`。

  - `2`: Seek from the end of the stream. Use `jfs.SEEK_END`.

    `2`: 从流的末尾开始定位。使用 `jfs.SEEK_END`。

### `file.tell()`

Return the current stream position.

返回当前的流位置。

- **Aliases**: `file.position()`

  **别名**: `file.position()`

### `file.size()`

Return the total size of the file in bytes.

返回文件的总字节大小。

### `file.available()`

Return the number of bytes available to be read from the current position to the end of the file.

返回从当前位置到文件末尾之间可读取的字节数。

### `file.name`

Returns the name of the file.

返回文件的名称。

------

## Module-Level File Operations 模块级文件操作

For convenience, the `jfs` module also provides functions that operate directly on file handles returned by `jfs.open()`. This can be useful in some scripting scenarios but using file object methods is generally preferred for clarity.

为了方便起见，`jfs` 模块还提供了直接对 `jfs.open()` 返回的文件句柄进行操作的函数。这在某些脚本场景中可能很有用，但为了清晰起见，通常首选使用文件对象方法。

- `jfs.read(file_handle, [size])`
- `jfs.write(file_handle, data)`
- `jfs.close(file_handle)`
- `jfs.seek(file_handle, offset, [whence])`
- `jfs.tell(file_handle)`
- `jfs.size(file_handle)`
- `jfs.available(file_handle)`

**Example:**

**示例：**

```
file_handle = jfs.open('temp.txt', 'w')
jfs.write(file_handle, 'some data')
jfs.close(file_handle)
```