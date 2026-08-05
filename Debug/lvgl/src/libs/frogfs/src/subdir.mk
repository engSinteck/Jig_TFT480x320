################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (14.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../lvgl/src/libs/frogfs/src/decomp_raw.c \
../lvgl/src/libs/frogfs/src/frogfs.c 

OBJS += \
./lvgl/src/libs/frogfs/src/decomp_raw.o \
./lvgl/src/libs/frogfs/src/frogfs.o 

C_DEPS += \
./lvgl/src/libs/frogfs/src/decomp_raw.d \
./lvgl/src/libs/frogfs/src/frogfs.d 


# Each subdirectory must supply rules for building sources it contributes
lvgl/src/libs/frogfs/src/%.o lvgl/src/libs/frogfs/src/%.su lvgl/src/libs/frogfs/src/%.cyclo: ../lvgl/src/libs/frogfs/src/%.c lvgl/src/libs/frogfs/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m33 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32H562xx -DLV_LVGL_H_INCLUDE_SIMPLE -c -I../Core/Inc -I../Drivers/STM32H5xx_HAL_Driver/Inc -I../Drivers/STM32H5xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H5xx/Include -I../Drivers/CMSIS/Include -I../FATFS/Target -I../FATFS/App -I../USB_DEVICE/App -I../USB_DEVICE/Target -I../Middlewares/Third_Party/FreeRTOS/Source/include/ -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2/ -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM33_NTZ/non_secure/ -I../Middlewares/Third_Party/FreeRTOS/Source/portable/MemMang -I../Middlewares/Third_Party/CMSIS/RTOS2/Include/ -I../Middlewares/Third_Party/FatFs/src -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -I../lvgl -O2 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-lvgl-2f-src-2f-libs-2f-frogfs-2f-src

clean-lvgl-2f-src-2f-libs-2f-frogfs-2f-src:
	-$(RM) ./lvgl/src/libs/frogfs/src/decomp_raw.cyclo ./lvgl/src/libs/frogfs/src/decomp_raw.d ./lvgl/src/libs/frogfs/src/decomp_raw.o ./lvgl/src/libs/frogfs/src/decomp_raw.su ./lvgl/src/libs/frogfs/src/frogfs.cyclo ./lvgl/src/libs/frogfs/src/frogfs.d ./lvgl/src/libs/frogfs/src/frogfs.o ./lvgl/src/libs/frogfs/src/frogfs.su

.PHONY: clean-lvgl-2f-src-2f-libs-2f-frogfs-2f-src

