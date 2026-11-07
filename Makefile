# 1 - Variables

CC              = arm-none-eabi-gcc
OBJCOPY         = arm-none-eabi-objcopy
SIZE            = arm-none-eabi-size

TARGET          = firmware
BUILD_DIR       = build
LINKER_SCRIPT   = $(wildcard *.ld)


# 2 - CPU and compiler flags

CPU             = -mcpu=cortex-m4 -mthumb -mfpu=fpv4-sp-d16 -mfloat-abi=hard

CCFLAGS         = $(CPU) -std=c11 -Wall -Wextra -g -O0 -IInc
ASFLAGS         = $(CPU) -g
LDFLAGS         = $(CPU) -T$(LINKER_SCRIPT) -Wl,--gc-sections -Wl,-Map=$(BUILD_DIR)/$(TARGET).map
LDFLAGS         += -specs=nosys.specs


# 3 - Source files

C_SOURCES       = $(wildcard Src/*.c)
ASM_SOURCES     = $(wildcard Startup/*.s	)


# 4 - Object files

C_OBJECTS       = $(patsubst Src/%.c,$(BUILD_DIR)/%.o,$(C_SOURCES))
ASM_OBJECTS     = $(patsubst Startup/%.s,$(BUILD_DIR)/%.o,$(ASM_SOURCES))
OBJECTS         = $(C_OBJECTS) $(ASM_OBJECTS)


# 5 - Build targets

all: $(BUILD_DIR)/$(TARGET).bin


# 6 - C compilation

$(BUILD_DIR)/%.o: Src/%.c
	mkdir -p $(BUILD_DIR)
	$(CC) $(CCFLAGS) -ffunction-sections -fdata-sections -c $< -o $@


# 7 - Assembly

$(BUILD_DIR)/%.o: Startup/%.s
	mkdir -p $(BUILD_DIR)
	$(CC) $(ASFLAGS) -c $< -o $@


# 8 - Linking

$(BUILD_DIR)/$(TARGET).elf: $(OBJECTS) $(LINKER_SCRIPT)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@
	$(SIZE) $@


# 9 - Binary conversion

$(BUILD_DIR)/$(TARGET).bin: $(BUILD_DIR)/$(TARGET).elf
	$(OBJCOPY) -O binary $< $@


# 10 - Clean

clean:
	rm -rf $(BUILD_DIR)


.PHONY: all clean