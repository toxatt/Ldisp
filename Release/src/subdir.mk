################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/SysInit.c \
../src/can.c \
../src/debug.c \
../src/hardware.c \
../src/main.c \
../src/ring_buffer.c \
../src/stm32f1xx_it.c \
../src/syscalls.c \
../src/system_stm32f10x.c 

OBJS += \
./src/SysInit.o \
./src/can.o \
./src/debug.o \
./src/hardware.o \
./src/main.o \
./src/ring_buffer.o \
./src/stm32f1xx_it.o \
./src/syscalls.o \
./src/system_stm32f10x.o 

C_DEPS += \
./src/SysInit.d \
./src/can.d \
./src/debug.d \
./src/hardware.d \
./src/main.d \
./src/ring_buffer.d \
./src/stm32f1xx_it.d \
./src/syscalls.d \
./src/system_stm32f10x.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -mfloat-abi=soft -DSTM32 -DSTM32F1 -DSTM32F103C8Tx -DSTM32F10X_MD -DUSE_STDPERIPH_DRIVER -I"/media/D/Electronika/Project/ARM/Ldisp/Firmware/StdPeriph_Driver/inc" -I"/media/D/Electronika/Project/ARM/Ldisp/Firmware/inc" -I"/media/D/Electronika/Project/ARM/Ldisp/Firmware/CMSIS/device" -I"/media/D/Electronika/Project/ARM/Ldisp/Firmware/CMSIS/core" -O3 -Wall -fmessage-length=0 -ffunction-sections -c -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


