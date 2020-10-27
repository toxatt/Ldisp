################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include startup/subdir.mk
-include src/subdir.mk
-include StdPeriph_Driver/src/subdir.mk
-include FreeRTOS/source/subdir.mk
-include CMSIS/core/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
Ldisp.elf \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
Ldisp.list \

OBJCOPY_BIN += \
Ldisp.bin \


# All Target
all: Ldisp.elf secondary-outputs

# Tool invocations
Ldisp.elf: $(OBJS) $(USER_OBJS) /media/D/Electronika/Project/ARM/Ldisp/Firmware/Ldisp/LinkerScript.ld
	arm-none-eabi-gcc -o "Ldisp.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m3 -T"/media/D/Electronika/Project/ARM/Ldisp/Firmware/Ldisp/LinkerScript.ld" --specs=nosys.specs -Wl,-Map="Ldisp.map" -Wl,--gc-sections -static -u _printf_float --specs=nano.specs -mfloat-abi=soft -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

Ldisp.list: $(EXECUTABLES)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "Ldisp.list"
	@echo 'Finished building: $@'
	@echo ' '

Ldisp.bin: $(EXECUTABLES)
	arm-none-eabi-objcopy  -O binary $(EXECUTABLES) "Ldisp.bin"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) *
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST) $(OBJCOPY_BIN)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
