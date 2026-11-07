# 1- variables

cc = arm-none-eabi-gcc 
OBJCOPY = arm-none-eabi-objcopy
TARGET = firmware
BUILD_DIR = build
LINKER_SCRIPT = $(wildcard *.ld)

#2- cpu and compiler flags
CPU = -mcpu=cortex-m4 -mthumb -mfpu=fpv4-sp-d16 -mfloat-abi=hard
CCFLAGS = $(CPU) -std=c11 -Wall -Wextra -g -O0 -IInc 
LDFLAGS = $(CPU) -T $(LINKER_SCRIPT)



#3 - source files
C_SOURCES =$(wildcard Src/*.c)
ASM_SOURCES = Startup/startup_stm32f407xx.s 


#4- object files




#5 -build targets 
all: $(BUILD_DIR)/$(TARGET).bin



#6- Compilation 




#7 assembly 


#8- link


#9- Binary conversion


#10 - clean



