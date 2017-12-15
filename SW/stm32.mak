#This file is generated by VisualGDB.
#It contains GCC settings automatically derived from the board support package (BSP).
#DO NOT EDIT MANUALLY. THE FILE WILL BE OVERWRITTEN. 
#Use VisualGDB Project Properties dialog or modify Makefile or per-configuration .mak files instead.

#VisualGDB provides BSP_ROOT and TOOLCHAIN_ROOT via environment when running Make. The line below will only be active if GNU Make is started manually.
BSP_ROOT ?= $(LOCALAPPDATA)/VisualGDB/EmbeddedBSPs/arm-eabi/com.sysprogs.arm.stm32
EFP_BASE ?= $(LOCALAPPDATA)/VisualGDB/EmbeddedEFPs
TESTFW_BASE ?= $(LOCALAPPDATA)/VisualGDB/TestFrameworks
TOOLCHAIN_ROOT ?= C:/SysGCC/arm-eabi
#Embedded toolchain
CC := $(TOOLCHAIN_ROOT)/bin/arm-eabi-gcc.exe
CXX := $(TOOLCHAIN_ROOT)/bin/arm-eabi-g++.exe
LD := $(CXX)
AR := $(TOOLCHAIN_ROOT)/bin/arm-eabi-ar.exe
OBJCOPY := $(TOOLCHAIN_ROOT)/bin/arm-eabi-objcopy.exe

#Additional flags
PREPROCESSOR_MACROS += ARM_MATH_CM4 STM32F405RG USE_FREERTOS flash_layout STM32F405xx
INCLUDE_DIRS += . $(BSP_ROOT)/FreeRTOS/Source/CMSIS_RTOS $(BSP_ROOT)/FreeRTOS/Source/Include $(BSP_ROOT)/FreeRTOS/Source/Portable/gcc/ARM_CM4F $(BSP_ROOT)/STM32F4xxxx/STM32F4xx_HAL_Driver/Inc $(BSP_ROOT)/STM32F4xxxx/STM32F4xx_HAL_Driver/Inc/Legacy $(BSP_ROOT)/STM32F4xxxx/CMSIS_HAL/Device/ST/STM32F4xx/Include $(BSP_ROOT)/STM32F4xxxx/CMSIS_HAL/Include
LIBRARY_DIRS += 
LIBRARY_NAMES += 
ADDITIONAL_LINKER_INPUTS += 
MACOS_FRAMEWORKS += 
LINUX_PACKAGES += 

CFLAGS += 
CXXFLAGS += 
ASFLAGS += -mfpu=fpv4-sp-d16
LDFLAGS += --specs=nano.specs 
COMMONFLAGS += -mcpu=cortex-m4 -mthumb -mfloat-abi=hard
LINKER_SCRIPT := $(BSP_ROOT)/STM32F4xxxx/LinkerScripts/STM32F405RG_flash.lds

