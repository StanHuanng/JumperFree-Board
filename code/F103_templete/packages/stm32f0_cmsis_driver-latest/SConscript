from building import *
import os

# Import environment variables
Import('env')

# Get the current working directory
cwd = GetCurrentDir()

# Initialize include paths and source files list
path = [os.path.join(cwd, 'Include')]
src = [os.path.join(cwd, 'Source', 'Templates', 'system_stm32f0xx.c')]

# Map microcontroller units (MCUs) to their corresponding startup files
mcu_startup_files = {
    'STM32F030x6': 'startup_stm32f030x6.s',
    'STM32F030x8': 'startup_stm32f030x8.s',
    'STM32F030xC': 'startup_stm32f030xc.s',
    'STM32F031x6': 'startup_stm32f031x6.s',
    'STM32F038xx': 'startup_stm32f038xx.s',
    'STM32F042x6': 'startup_stm32f042x6.s',
    'STM32F048xx': 'startup_stm32f048xx.s',
    'STM32F051x8': 'startup_stm32f051x8.s',
    'STM32F058xx': 'startup_stm32f058xx.s',
    'STM32F070x6': 'startup_stm32f070x6.s',
    'STM32F070xB': 'startup_stm32f070xb.s',
    'STM32F071xB': 'startup_stm32f071xb.s',
    'STM32F072xB': 'startup_stm32f072xb.s',
    'STM32F078xx': 'startup_stm32f078xx.s',
    'STM32F091xC': 'startup_stm32f091xc.s',
    'STM32F098xx': 'startup_stm32f098xx.s',
}

# Check each defined MCU, match the platform and append the appropriate startup file
for mcu, startup_file in mcu_startup_files.items():
    if mcu in env.get('CPPDEFINES', []):
        if rtconfig.PLATFORM in ['gcc', 'llvm-arm']:
            src += [os.path.join(cwd, 'Source', 'Templates', 'gcc', startup_file)]
        elif rtconfig.PLATFORM in ['armcc', 'armclang']:
            src += [os.path.join(cwd, 'Source', 'Templates', 'arm', startup_file)]
        elif rtconfig.PLATFORM in ['iccarm']:
            src += [os.path.join(cwd, 'Source', 'Templates', 'iar', startup_file)]
        break

# Define the build group
group = DefineGroup('STM32F0-CMSIS', src, depend=['PKG_USING_STM32F0_CMSIS_DRIVER'], CPPPATH=path)

# Return the build group
Return('group')