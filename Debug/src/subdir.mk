################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/KS0108-STM32.c \
../src/KS0108.c \
../src/SysInit.c \
../src/can.c \
../src/cmd.c \
../src/debug.c \
../src/graphic.c \
../src/hardware.c \
../src/main.c \
../src/ring_buffer.c \
../src/stm32f1xx_it.c \
../src/syscalls.c \
../src/system_stm32f10x.c \
../src/tok.c \
../src/utility.c 

OBJS += \
./src/KS0108-STM32.o \
./src/KS0108.o \
./src/SysInit.o \
./src/can.o \
./src/cmd.o \
./src/debug.o \
./src/graphic.o \
./src/hardware.o \
./src/main.o \
./src/ring_buffer.o \
./src/stm32f1xx_it.o \
./src/syscalls.o \
./src/system_stm32f10x.o \
./src/tok.o \
./src/utility.o 

C_DEPS += \
./src/KS0108-STM32.d \
./src/KS0108.d \
./src/SysInit.d \
./src/can.d \
./src/cmd.d \
./src/debug.d \
./src/graphic.d \
./src/hardware.d \
./src/main.d \
./src/ring_buffer.d \
./src/stm32f1xx_it.d \
./src/syscalls.d \
./src/system_stm32f10x.d \
./src/tok.d \
./src/utility.d 


# Each subdirectory must supply rules for building sources it contributes
src/KS0108-STM32.o: ../src/KS0108-STM32.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C8Tx -DDEBUG -DSTM32F10X_MD -DUSE_STDPERIPH_DRIVER -c -I"/media/D/Electronika/Project/ARM/Ldisp/Firmware/Ldisp/StdPeriph_Driver/inc" -I"/media/D/Electronika/Project/ARM/Ldisp/Firmware/Ldisp/inc" -I"/media/D/Electronika/Project/ARM/Ldisp/Firmware/Ldisp/CMSIS/device" -I"/media/D/Electronika/Project/ARM/Ldisp/Firmware/Ldisp/CMSIS/core" -I"/media/D/Electronika/Project/ARM/Ldisp/Firmware/Ldisp/FreeRTOS/include" -I"/media/D/Electronika/Project/ARM/Ldisp/Firmware/Ldisp/FreeRTOS/source" -Og -ffunction-sections -fdata-sections -fno-strict-aliasing -Wall -fstack-usage -MMD -MP -MF"src/KS0108-STM32.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
src/KS0108.o: ../src/KS0108.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C8Tx -DDEBUG -DSTM32F10X_MD -DUSE_STDPERIPH_DRIVER -c -I"/media/D/Electronika/Project/ARM/Ldisp/Firmware/Ldisp/StdPeriph_Driver/inc" -I"/media/D/Electronika/Project/ARM/Ldisp/Firmware/Ldisp/inc" -I"/media/D/Electronika/Project/ARM/Ldisp/Firmware/Ldisp/CMSIS/device" -I"/media/D/Electronika/Project/ARM/Ldisp/Firmware/Ldisp/CMSIS/core" -I"/media/D/Electronika/Project/ARM/Ldisp/Firmware/Ldisp/FreeRTOS/include" -I"/media/D/Electronika/Project/ARM/Ldisp/Firmware/Ldisp/FreeRTOS/source" -Og -ffunction-sections -fdata-sections -fno-strict-aliasing -Wall -fstack-usage -MMD -MP -MF"src/KS0108.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
src/SysInit.o: ../src/SysInit.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C8Tx -DDEBUG -DSTM32F10X_MD -DUSE_STDPERIPH_DRIVER -c -I"/media/D/Electronika/Project/ARM/Ldisp/Firmware/Ldisp/StdPeriph_Driver/inc" -I"/media/D/Electronika/Project/ARM/Ldisp/Firmware/Ldisp/inc" -I"/media/D/Electronika/Project/ARM/Ldisp/Firmware/Ldisp/CMSIS/device" -I"/media/D/Electronika/Project/ARM/Ldisp/Firmware/Ldisp/CMSIS/core" -I"/media/D/Electronika/Project/ARM/Ldisp/Firmware/Ldisp/FreeRTOS/include" -I"/media/D/Electronika/Project/ARM/Ldisp/Firmware/Ldisp/FreeRTOS/source" -Og -ffunction-sections -fdata-sections -fno-strict-aliasing -Wall -fstack-usage -MMD -MP -MF"src/SysInit.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
src/can.o: ../src/can.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C8Tx -DDEBUG -DSTM32F10X_MD -DUSE_STDPERIPH_DRIVER -c -I"/media/D/Electronika/Project/ARM/Ldisp/Firmware/Ldisp/StdPeriph_Driver/inc" -I"/media/D/Electronika/Project/ARM/Ldisp/Firmware/Ldisp/inc" -I"/media/D/Electronika/Project/ARM/Ldisp/Firmware/Ldisp/CMSIS/device" -I"/media/D/Electronika/Project/ARM/Ldisp/Firmware/Ldisp/CMSIS/core" -I"/media/D/Electronika/Project/ARM/Ldisp/Firmware/Ldisp/FreeRTOS/include" -I"/media/D/Electronika/Project/ARM/Ldisp/Firmware/Ldisp/FreeRTOS/source" -Og -ffunction-sections -fdata-sections -fno-strict-aliasing -Wall -fstack-usage -MMD -MP -MF"src/can.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
src/cmd.o: ../src/cmd.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C8Tx -DDEBUG -DSTM32F10X_MD -DUSE_STDPERIPH_DRIVER -c -I"/media/D/Electronika/Project/ARM/Ldisp/Firmware/Ldisp/StdPeriph_Driver/inc" -I"/media/D/Electronika/Project/ARM/Ldisp/Firmware/Ldisp/inc" -I"/media/D/Electronika/Project/ARM/Ldisp/Firmware/Ldisp/CMSIS/device" -I"/media/D/Electronika/Project/ARM/Ldisp/Firmware/Ldisp/CMSIS/core" -I"/media/D/Electronika/Project/ARM/Ldisp/Firmware/Ldisp/FreeRTOS/include" -I"/media/D/Electronika/Project/ARM/Ldisp/Firmware/Ldisp/FreeRTOS/source" -Og -ffunction-sections -fdata-sections -fno-strict-aliasing -Wall -fstack-usage -MMD -MP -MF"src/cmd.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
src/debug.o: ../src/debug.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C8Tx -DDEBUG -DSTM32F10X_MD -DUSE_STDPERIPH_DRIVER -c -I"/media/D/Electronika/Project/ARM/Ldisp/Firmware/Ldisp/StdPeriph_Driver/inc" -I"/media/D/Electronika/Project/ARM/Ldisp/Firmware/Ldisp/inc" -I"/media/D/Electronika/Project/ARM/Ldisp/Firmware/Ldisp/CMSIS/device" -I"/media/D/Electronika/Project/ARM/Ldisp/Firmware/Ldisp/CMSIS/core" -I"/media/D/Electronika/Project/ARM/Ldisp/Firmware/Ldisp/FreeRTOS/include" -I"/media/D/Electronika/Project/ARM/Ldisp/Firmware/Ldisp/FreeRTOS/source" -Og -ffunction-sections -fdata-sections -fno-strict-aliasing -Wall -fstack-usage -MMD -MP -MF"src/debug.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
src/graphic.o: ../src/graphic.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C8Tx -DDEBUG -DSTM32F10X_MD -DUSE_STDPERIPH_DRIVER -c -I"/media/D/Electronika/Project/ARM/Ldisp/Firmware/Ldisp/StdPeriph_Driver/inc" -I"/media/D/Electronika/Project/ARM/Ldisp/Firmware/Ldisp/inc" -I"/media/D/Electronika/Project/ARM/Ldisp/Firmware/Ldisp/CMSIS/device" -I"/media/D/Electronika/Project/ARM/Ldisp/Firmware/Ldisp/CMSIS/core" -I"/media/D/Electronika/Project/ARM/Ldisp/Firmware/Ldisp/FreeRTOS/include" -I"/media/D/Electronika/Project/ARM/Ldisp/Firmware/Ldisp/FreeRTOS/source" -Og -ffunction-sections -fdata-sections -fno-strict-aliasing -Wall -fstack-usage -MMD -MP -MF"src/graphic.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
src/hardware.o: ../src/hardware.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C8Tx -DDEBUG -DSTM32F10X_MD -DUSE_STDPERIPH_DRIVER -c -I"/media/D/Electronika/Project/ARM/Ldisp/Firmware/Ldisp/StdPeriph_Driver/inc" -I"/media/D/Electronika/Project/ARM/Ldisp/Firmware/Ldisp/inc" -I"/media/D/Electronika/Project/ARM/Ldisp/Firmware/Ldisp/CMSIS/device" -I"/media/D/Electronika/Project/ARM/Ldisp/Firmware/Ldisp/CMSIS/core" -I"/media/D/Electronika/Project/ARM/Ldisp/Firmware/Ldisp/FreeRTOS/include" -I"/media/D/Electronika/Project/ARM/Ldisp/Firmware/Ldisp/FreeRTOS/source" -Og -ffunction-sections -fdata-sections -fno-strict-aliasing -Wall -fstack-usage -MMD -MP -MF"src/hardware.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
src/main.o: ../src/main.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C8Tx -DDEBUG -DSTM32F10X_MD -DUSE_STDPERIPH_DRIVER -c -I"/media/D/Electronika/Project/ARM/Ldisp/Firmware/Ldisp/StdPeriph_Driver/inc" -I"/media/D/Electronika/Project/ARM/Ldisp/Firmware/Ldisp/inc" -I"/media/D/Electronika/Project/ARM/Ldisp/Firmware/Ldisp/CMSIS/device" -I"/media/D/Electronika/Project/ARM/Ldisp/Firmware/Ldisp/CMSIS/core" -I"/media/D/Electronika/Project/ARM/Ldisp/Firmware/Ldisp/FreeRTOS/include" -I"/media/D/Electronika/Project/ARM/Ldisp/Firmware/Ldisp/FreeRTOS/source" -Og -ffunction-sections -fdata-sections -fno-strict-aliasing -Wall -fstack-usage -MMD -MP -MF"src/main.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
src/ring_buffer.o: ../src/ring_buffer.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C8Tx -DDEBUG -DSTM32F10X_MD -DUSE_STDPERIPH_DRIVER -c -I"/media/D/Electronika/Project/ARM/Ldisp/Firmware/Ldisp/StdPeriph_Driver/inc" -I"/media/D/Electronika/Project/ARM/Ldisp/Firmware/Ldisp/inc" -I"/media/D/Electronika/Project/ARM/Ldisp/Firmware/Ldisp/CMSIS/device" -I"/media/D/Electronika/Project/ARM/Ldisp/Firmware/Ldisp/CMSIS/core" -I"/media/D/Electronika/Project/ARM/Ldisp/Firmware/Ldisp/FreeRTOS/include" -I"/media/D/Electronika/Project/ARM/Ldisp/Firmware/Ldisp/FreeRTOS/source" -Og -ffunction-sections -fdata-sections -fno-strict-aliasing -Wall -fstack-usage -MMD -MP -MF"src/ring_buffer.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
src/stm32f1xx_it.o: ../src/stm32f1xx_it.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C8Tx -DDEBUG -DSTM32F10X_MD -DUSE_STDPERIPH_DRIVER -c -I"/media/D/Electronika/Project/ARM/Ldisp/Firmware/Ldisp/StdPeriph_Driver/inc" -I"/media/D/Electronika/Project/ARM/Ldisp/Firmware/Ldisp/inc" -I"/media/D/Electronika/Project/ARM/Ldisp/Firmware/Ldisp/CMSIS/device" -I"/media/D/Electronika/Project/ARM/Ldisp/Firmware/Ldisp/CMSIS/core" -I"/media/D/Electronika/Project/ARM/Ldisp/Firmware/Ldisp/FreeRTOS/include" -I"/media/D/Electronika/Project/ARM/Ldisp/Firmware/Ldisp/FreeRTOS/source" -Og -ffunction-sections -fdata-sections -fno-strict-aliasing -Wall -fstack-usage -MMD -MP -MF"src/stm32f1xx_it.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
src/syscalls.o: ../src/syscalls.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C8Tx -DDEBUG -DSTM32F10X_MD -DUSE_STDPERIPH_DRIVER -c -I"/media/D/Electronika/Project/ARM/Ldisp/Firmware/Ldisp/StdPeriph_Driver/inc" -I"/media/D/Electronika/Project/ARM/Ldisp/Firmware/Ldisp/inc" -I"/media/D/Electronika/Project/ARM/Ldisp/Firmware/Ldisp/CMSIS/device" -I"/media/D/Electronika/Project/ARM/Ldisp/Firmware/Ldisp/CMSIS/core" -I"/media/D/Electronika/Project/ARM/Ldisp/Firmware/Ldisp/FreeRTOS/include" -I"/media/D/Electronika/Project/ARM/Ldisp/Firmware/Ldisp/FreeRTOS/source" -Og -ffunction-sections -fdata-sections -fno-strict-aliasing -Wall -fstack-usage -MMD -MP -MF"src/syscalls.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
src/system_stm32f10x.o: ../src/system_stm32f10x.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C8Tx -DDEBUG -DSTM32F10X_MD -DUSE_STDPERIPH_DRIVER -c -I"/media/D/Electronika/Project/ARM/Ldisp/Firmware/Ldisp/StdPeriph_Driver/inc" -I"/media/D/Electronika/Project/ARM/Ldisp/Firmware/Ldisp/inc" -I"/media/D/Electronika/Project/ARM/Ldisp/Firmware/Ldisp/CMSIS/device" -I"/media/D/Electronika/Project/ARM/Ldisp/Firmware/Ldisp/CMSIS/core" -I"/media/D/Electronika/Project/ARM/Ldisp/Firmware/Ldisp/FreeRTOS/include" -I"/media/D/Electronika/Project/ARM/Ldisp/Firmware/Ldisp/FreeRTOS/source" -Og -ffunction-sections -fdata-sections -fno-strict-aliasing -Wall -fstack-usage -MMD -MP -MF"src/system_stm32f10x.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
src/tok.o: ../src/tok.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C8Tx -DDEBUG -DSTM32F10X_MD -DUSE_STDPERIPH_DRIVER -c -I"/media/D/Electronika/Project/ARM/Ldisp/Firmware/Ldisp/StdPeriph_Driver/inc" -I"/media/D/Electronika/Project/ARM/Ldisp/Firmware/Ldisp/inc" -I"/media/D/Electronika/Project/ARM/Ldisp/Firmware/Ldisp/CMSIS/device" -I"/media/D/Electronika/Project/ARM/Ldisp/Firmware/Ldisp/CMSIS/core" -I"/media/D/Electronika/Project/ARM/Ldisp/Firmware/Ldisp/FreeRTOS/include" -I"/media/D/Electronika/Project/ARM/Ldisp/Firmware/Ldisp/FreeRTOS/source" -Og -ffunction-sections -fdata-sections -fno-strict-aliasing -Wall -fstack-usage -MMD -MP -MF"src/tok.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
src/utility.o: ../src/utility.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C8Tx -DDEBUG -DSTM32F10X_MD -DUSE_STDPERIPH_DRIVER -c -I"/media/D/Electronika/Project/ARM/Ldisp/Firmware/Ldisp/StdPeriph_Driver/inc" -I"/media/D/Electronika/Project/ARM/Ldisp/Firmware/Ldisp/inc" -I"/media/D/Electronika/Project/ARM/Ldisp/Firmware/Ldisp/CMSIS/device" -I"/media/D/Electronika/Project/ARM/Ldisp/Firmware/Ldisp/CMSIS/core" -I"/media/D/Electronika/Project/ARM/Ldisp/Firmware/Ldisp/FreeRTOS/include" -I"/media/D/Electronika/Project/ARM/Ldisp/Firmware/Ldisp/FreeRTOS/source" -Og -ffunction-sections -fdata-sections -fno-strict-aliasing -Wall -fstack-usage -MMD -MP -MF"src/utility.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

