################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../FreeRTOS/source/croutine.c \
../FreeRTOS/source/event_groups.c \
../FreeRTOS/source/heap_1.c \
../FreeRTOS/source/list.c \
../FreeRTOS/source/port.c \
../FreeRTOS/source/queue.c \
../FreeRTOS/source/stream_buffer.c \
../FreeRTOS/source/tasks.c \
../FreeRTOS/source/timers.c 

OBJS += \
./FreeRTOS/source/croutine.o \
./FreeRTOS/source/event_groups.o \
./FreeRTOS/source/heap_1.o \
./FreeRTOS/source/list.o \
./FreeRTOS/source/port.o \
./FreeRTOS/source/queue.o \
./FreeRTOS/source/stream_buffer.o \
./FreeRTOS/source/tasks.o \
./FreeRTOS/source/timers.o 

C_DEPS += \
./FreeRTOS/source/croutine.d \
./FreeRTOS/source/event_groups.d \
./FreeRTOS/source/heap_1.d \
./FreeRTOS/source/list.d \
./FreeRTOS/source/port.d \
./FreeRTOS/source/queue.d \
./FreeRTOS/source/stream_buffer.d \
./FreeRTOS/source/tasks.d \
./FreeRTOS/source/timers.d 


# Each subdirectory must supply rules for building sources it contributes
FreeRTOS/source/croutine.o: ../FreeRTOS/source/croutine.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C8Tx -DDEBUG -DSTM32F10X_MD -DUSE_STDPERIPH_DRIVER -c -I"/media/D/Electronika/Project/ARM/Ldisp/Firmware/Ldisp/StdPeriph_Driver/inc" -I"/media/D/Electronika/Project/ARM/Ldisp/Firmware/Ldisp/inc" -I"/media/D/Electronika/Project/ARM/Ldisp/Firmware/Ldisp/CMSIS/device" -I"/media/D/Electronika/Project/ARM/Ldisp/Firmware/Ldisp/CMSIS/core" -I"/media/D/Electronika/Project/ARM/Ldisp/Firmware/Ldisp/FreeRTOS/include" -I"/media/D/Electronika/Project/ARM/Ldisp/Firmware/Ldisp/FreeRTOS/source" -Og -ffunction-sections -fdata-sections -fno-strict-aliasing -Wall -fstack-usage -MMD -MP -MF"FreeRTOS/source/croutine.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
FreeRTOS/source/event_groups.o: ../FreeRTOS/source/event_groups.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C8Tx -DDEBUG -DSTM32F10X_MD -DUSE_STDPERIPH_DRIVER -c -I"/media/D/Electronika/Project/ARM/Ldisp/Firmware/Ldisp/StdPeriph_Driver/inc" -I"/media/D/Electronika/Project/ARM/Ldisp/Firmware/Ldisp/inc" -I"/media/D/Electronika/Project/ARM/Ldisp/Firmware/Ldisp/CMSIS/device" -I"/media/D/Electronika/Project/ARM/Ldisp/Firmware/Ldisp/CMSIS/core" -I"/media/D/Electronika/Project/ARM/Ldisp/Firmware/Ldisp/FreeRTOS/include" -I"/media/D/Electronika/Project/ARM/Ldisp/Firmware/Ldisp/FreeRTOS/source" -Og -ffunction-sections -fdata-sections -fno-strict-aliasing -Wall -fstack-usage -MMD -MP -MF"FreeRTOS/source/event_groups.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
FreeRTOS/source/heap_1.o: ../FreeRTOS/source/heap_1.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C8Tx -DDEBUG -DSTM32F10X_MD -DUSE_STDPERIPH_DRIVER -c -I"/media/D/Electronika/Project/ARM/Ldisp/Firmware/Ldisp/StdPeriph_Driver/inc" -I"/media/D/Electronika/Project/ARM/Ldisp/Firmware/Ldisp/inc" -I"/media/D/Electronika/Project/ARM/Ldisp/Firmware/Ldisp/CMSIS/device" -I"/media/D/Electronika/Project/ARM/Ldisp/Firmware/Ldisp/CMSIS/core" -I"/media/D/Electronika/Project/ARM/Ldisp/Firmware/Ldisp/FreeRTOS/include" -I"/media/D/Electronika/Project/ARM/Ldisp/Firmware/Ldisp/FreeRTOS/source" -Og -ffunction-sections -fdata-sections -fno-strict-aliasing -Wall -fstack-usage -MMD -MP -MF"FreeRTOS/source/heap_1.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
FreeRTOS/source/list.o: ../FreeRTOS/source/list.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C8Tx -DDEBUG -DSTM32F10X_MD -DUSE_STDPERIPH_DRIVER -c -I"/media/D/Electronika/Project/ARM/Ldisp/Firmware/Ldisp/StdPeriph_Driver/inc" -I"/media/D/Electronika/Project/ARM/Ldisp/Firmware/Ldisp/inc" -I"/media/D/Electronika/Project/ARM/Ldisp/Firmware/Ldisp/CMSIS/device" -I"/media/D/Electronika/Project/ARM/Ldisp/Firmware/Ldisp/CMSIS/core" -I"/media/D/Electronika/Project/ARM/Ldisp/Firmware/Ldisp/FreeRTOS/include" -I"/media/D/Electronika/Project/ARM/Ldisp/Firmware/Ldisp/FreeRTOS/source" -Og -ffunction-sections -fdata-sections -fno-strict-aliasing -Wall -fstack-usage -MMD -MP -MF"FreeRTOS/source/list.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
FreeRTOS/source/port.o: ../FreeRTOS/source/port.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C8Tx -DDEBUG -DSTM32F10X_MD -DUSE_STDPERIPH_DRIVER -c -I"/media/D/Electronika/Project/ARM/Ldisp/Firmware/Ldisp/StdPeriph_Driver/inc" -I"/media/D/Electronika/Project/ARM/Ldisp/Firmware/Ldisp/inc" -I"/media/D/Electronika/Project/ARM/Ldisp/Firmware/Ldisp/CMSIS/device" -I"/media/D/Electronika/Project/ARM/Ldisp/Firmware/Ldisp/CMSIS/core" -I"/media/D/Electronika/Project/ARM/Ldisp/Firmware/Ldisp/FreeRTOS/include" -I"/media/D/Electronika/Project/ARM/Ldisp/Firmware/Ldisp/FreeRTOS/source" -Og -ffunction-sections -fdata-sections -fno-strict-aliasing -Wall -fstack-usage -MMD -MP -MF"FreeRTOS/source/port.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
FreeRTOS/source/queue.o: ../FreeRTOS/source/queue.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C8Tx -DDEBUG -DSTM32F10X_MD -DUSE_STDPERIPH_DRIVER -c -I"/media/D/Electronika/Project/ARM/Ldisp/Firmware/Ldisp/StdPeriph_Driver/inc" -I"/media/D/Electronika/Project/ARM/Ldisp/Firmware/Ldisp/inc" -I"/media/D/Electronika/Project/ARM/Ldisp/Firmware/Ldisp/CMSIS/device" -I"/media/D/Electronika/Project/ARM/Ldisp/Firmware/Ldisp/CMSIS/core" -I"/media/D/Electronika/Project/ARM/Ldisp/Firmware/Ldisp/FreeRTOS/include" -I"/media/D/Electronika/Project/ARM/Ldisp/Firmware/Ldisp/FreeRTOS/source" -Og -ffunction-sections -fdata-sections -fno-strict-aliasing -Wall -fstack-usage -MMD -MP -MF"FreeRTOS/source/queue.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
FreeRTOS/source/stream_buffer.o: ../FreeRTOS/source/stream_buffer.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C8Tx -DDEBUG -DSTM32F10X_MD -DUSE_STDPERIPH_DRIVER -c -I"/media/D/Electronika/Project/ARM/Ldisp/Firmware/Ldisp/StdPeriph_Driver/inc" -I"/media/D/Electronika/Project/ARM/Ldisp/Firmware/Ldisp/inc" -I"/media/D/Electronika/Project/ARM/Ldisp/Firmware/Ldisp/CMSIS/device" -I"/media/D/Electronika/Project/ARM/Ldisp/Firmware/Ldisp/CMSIS/core" -I"/media/D/Electronika/Project/ARM/Ldisp/Firmware/Ldisp/FreeRTOS/include" -I"/media/D/Electronika/Project/ARM/Ldisp/Firmware/Ldisp/FreeRTOS/source" -Og -ffunction-sections -fdata-sections -fno-strict-aliasing -Wall -fstack-usage -MMD -MP -MF"FreeRTOS/source/stream_buffer.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
FreeRTOS/source/tasks.o: ../FreeRTOS/source/tasks.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C8Tx -DDEBUG -DSTM32F10X_MD -DUSE_STDPERIPH_DRIVER -c -I"/media/D/Electronika/Project/ARM/Ldisp/Firmware/Ldisp/StdPeriph_Driver/inc" -I"/media/D/Electronika/Project/ARM/Ldisp/Firmware/Ldisp/inc" -I"/media/D/Electronika/Project/ARM/Ldisp/Firmware/Ldisp/CMSIS/device" -I"/media/D/Electronika/Project/ARM/Ldisp/Firmware/Ldisp/CMSIS/core" -I"/media/D/Electronika/Project/ARM/Ldisp/Firmware/Ldisp/FreeRTOS/include" -I"/media/D/Electronika/Project/ARM/Ldisp/Firmware/Ldisp/FreeRTOS/source" -Og -ffunction-sections -fdata-sections -fno-strict-aliasing -Wall -fstack-usage -MMD -MP -MF"FreeRTOS/source/tasks.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
FreeRTOS/source/timers.o: ../FreeRTOS/source/timers.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C8Tx -DDEBUG -DSTM32F10X_MD -DUSE_STDPERIPH_DRIVER -c -I"/media/D/Electronika/Project/ARM/Ldisp/Firmware/Ldisp/StdPeriph_Driver/inc" -I"/media/D/Electronika/Project/ARM/Ldisp/Firmware/Ldisp/inc" -I"/media/D/Electronika/Project/ARM/Ldisp/Firmware/Ldisp/CMSIS/device" -I"/media/D/Electronika/Project/ARM/Ldisp/Firmware/Ldisp/CMSIS/core" -I"/media/D/Electronika/Project/ARM/Ldisp/Firmware/Ldisp/FreeRTOS/include" -I"/media/D/Electronika/Project/ARM/Ldisp/Firmware/Ldisp/FreeRTOS/source" -Og -ffunction-sections -fdata-sections -fno-strict-aliasing -Wall -fstack-usage -MMD -MP -MF"FreeRTOS/source/timers.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

