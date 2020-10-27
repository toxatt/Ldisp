################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../CMSIS/core/core_cm3.c 

OBJS += \
./CMSIS/core/core_cm3.o 

C_DEPS += \
./CMSIS/core/core_cm3.d 


# Each subdirectory must supply rules for building sources it contributes
CMSIS/core/core_cm3.o: ../CMSIS/core/core_cm3.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C8Tx -DDEBUG -DSTM32F10X_MD -DUSE_STDPERIPH_DRIVER -c -I"/media/D/Electronika/Project/ARM/Ldisp/Firmware/Ldisp/StdPeriph_Driver/inc" -I"/media/D/Electronika/Project/ARM/Ldisp/Firmware/Ldisp/inc" -I"/media/D/Electronika/Project/ARM/Ldisp/Firmware/Ldisp/CMSIS/device" -I"/media/D/Electronika/Project/ARM/Ldisp/Firmware/Ldisp/CMSIS/core" -I"/media/D/Electronika/Project/ARM/Ldisp/Firmware/Ldisp/FreeRTOS/include" -I"/media/D/Electronika/Project/ARM/Ldisp/Firmware/Ldisp/FreeRTOS/source" -Og -ffunction-sections -fdata-sections -fno-strict-aliasing -Wall -fstack-usage -MMD -MP -MF"CMSIS/core/core_cm3.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

