# F103_bridge Change Log

## 2026-04-21

- Added `applications/bridge_manager.h` and `applications/bridge_manager.c` bridge data storage foundation.
- Bridge manager now maintains fixed-size CH446Q `(x, y)` bridge records with validation, add/remove, contains, count, capacity, and indexed read APIs.
- Moved `bridge_manager` into `applications/`, so `applications/SConscript` includes it through `Glob('*.c')`.
- Updated `.gitignore` to allow tracking Keil template project files `template.uvproj` and `template.uvprojx` while continuing to ignore personal Keil option/layout files.

