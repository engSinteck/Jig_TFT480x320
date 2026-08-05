################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (14.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../lvgl/tests/test_images/stride_align64/LZ4/test_A1_LZ4_align64.c \
../lvgl/tests/test_images/stride_align64/LZ4/test_A2_LZ4_align64.c \
../lvgl/tests/test_images/stride_align64/LZ4/test_A4_LZ4_align64.c \
../lvgl/tests/test_images/stride_align64/LZ4/test_A8_LZ4_align64.c \
../lvgl/tests/test_images/stride_align64/LZ4/test_ARGB8565_LZ4_align64.c \
../lvgl/tests/test_images/stride_align64/LZ4/test_ARGB8888_LZ4_align64.c \
../lvgl/tests/test_images/stride_align64/LZ4/test_ARGB8888_PREMULTIPLIED_LZ4_align64.c \
../lvgl/tests/test_images/stride_align64/LZ4/test_I1_LZ4_align64.c \
../lvgl/tests/test_images/stride_align64/LZ4/test_I2_LZ4_align64.c \
../lvgl/tests/test_images/stride_align64/LZ4/test_I4_LZ4_align64.c \
../lvgl/tests/test_images/stride_align64/LZ4/test_I8_LZ4_align64.c \
../lvgl/tests/test_images/stride_align64/LZ4/test_L8_LZ4_align64.c \
../lvgl/tests/test_images/stride_align64/LZ4/test_RGB565A8_LZ4_align64.c \
../lvgl/tests/test_images/stride_align64/LZ4/test_RGB565_LZ4_align64.c \
../lvgl/tests/test_images/stride_align64/LZ4/test_RGB565_SWAPPED_LZ4_align64.c \
../lvgl/tests/test_images/stride_align64/LZ4/test_RGB888_LZ4_align64.c \
../lvgl/tests/test_images/stride_align64/LZ4/test_XRGB8888_LZ4_align64.c 

OBJS += \
./lvgl/tests/test_images/stride_align64/LZ4/test_A1_LZ4_align64.o \
./lvgl/tests/test_images/stride_align64/LZ4/test_A2_LZ4_align64.o \
./lvgl/tests/test_images/stride_align64/LZ4/test_A4_LZ4_align64.o \
./lvgl/tests/test_images/stride_align64/LZ4/test_A8_LZ4_align64.o \
./lvgl/tests/test_images/stride_align64/LZ4/test_ARGB8565_LZ4_align64.o \
./lvgl/tests/test_images/stride_align64/LZ4/test_ARGB8888_LZ4_align64.o \
./lvgl/tests/test_images/stride_align64/LZ4/test_ARGB8888_PREMULTIPLIED_LZ4_align64.o \
./lvgl/tests/test_images/stride_align64/LZ4/test_I1_LZ4_align64.o \
./lvgl/tests/test_images/stride_align64/LZ4/test_I2_LZ4_align64.o \
./lvgl/tests/test_images/stride_align64/LZ4/test_I4_LZ4_align64.o \
./lvgl/tests/test_images/stride_align64/LZ4/test_I8_LZ4_align64.o \
./lvgl/tests/test_images/stride_align64/LZ4/test_L8_LZ4_align64.o \
./lvgl/tests/test_images/stride_align64/LZ4/test_RGB565A8_LZ4_align64.o \
./lvgl/tests/test_images/stride_align64/LZ4/test_RGB565_LZ4_align64.o \
./lvgl/tests/test_images/stride_align64/LZ4/test_RGB565_SWAPPED_LZ4_align64.o \
./lvgl/tests/test_images/stride_align64/LZ4/test_RGB888_LZ4_align64.o \
./lvgl/tests/test_images/stride_align64/LZ4/test_XRGB8888_LZ4_align64.o 

C_DEPS += \
./lvgl/tests/test_images/stride_align64/LZ4/test_A1_LZ4_align64.d \
./lvgl/tests/test_images/stride_align64/LZ4/test_A2_LZ4_align64.d \
./lvgl/tests/test_images/stride_align64/LZ4/test_A4_LZ4_align64.d \
./lvgl/tests/test_images/stride_align64/LZ4/test_A8_LZ4_align64.d \
./lvgl/tests/test_images/stride_align64/LZ4/test_ARGB8565_LZ4_align64.d \
./lvgl/tests/test_images/stride_align64/LZ4/test_ARGB8888_LZ4_align64.d \
./lvgl/tests/test_images/stride_align64/LZ4/test_ARGB8888_PREMULTIPLIED_LZ4_align64.d \
./lvgl/tests/test_images/stride_align64/LZ4/test_I1_LZ4_align64.d \
./lvgl/tests/test_images/stride_align64/LZ4/test_I2_LZ4_align64.d \
./lvgl/tests/test_images/stride_align64/LZ4/test_I4_LZ4_align64.d \
./lvgl/tests/test_images/stride_align64/LZ4/test_I8_LZ4_align64.d \
./lvgl/tests/test_images/stride_align64/LZ4/test_L8_LZ4_align64.d \
./lvgl/tests/test_images/stride_align64/LZ4/test_RGB565A8_LZ4_align64.d \
./lvgl/tests/test_images/stride_align64/LZ4/test_RGB565_LZ4_align64.d \
./lvgl/tests/test_images/stride_align64/LZ4/test_RGB565_SWAPPED_LZ4_align64.d \
./lvgl/tests/test_images/stride_align64/LZ4/test_RGB888_LZ4_align64.d \
./lvgl/tests/test_images/stride_align64/LZ4/test_XRGB8888_LZ4_align64.d 


# Each subdirectory must supply rules for building sources it contributes
lvgl/tests/test_images/stride_align64/LZ4/%.o lvgl/tests/test_images/stride_align64/LZ4/%.su lvgl/tests/test_images/stride_align64/LZ4/%.cyclo: ../lvgl/tests/test_images/stride_align64/LZ4/%.c lvgl/tests/test_images/stride_align64/LZ4/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m33 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32H562xx -DLV_LVGL_H_INCLUDE_SIMPLE -c -I../Core/Inc -I../Drivers/STM32H5xx_HAL_Driver/Inc -I../Drivers/STM32H5xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H5xx/Include -I../Drivers/CMSIS/Include -I../FATFS/Target -I../FATFS/App -I../USB_DEVICE/App -I../USB_DEVICE/Target -I../Middlewares/Third_Party/FreeRTOS/Source/include/ -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2/ -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM33_NTZ/non_secure/ -I../Middlewares/Third_Party/FreeRTOS/Source/portable/MemMang -I../Middlewares/Third_Party/CMSIS/RTOS2/Include/ -I../Middlewares/Third_Party/FatFs/src -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -I../lvgl -O2 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-lvgl-2f-tests-2f-test_images-2f-stride_align64-2f-LZ4

clean-lvgl-2f-tests-2f-test_images-2f-stride_align64-2f-LZ4:
	-$(RM) ./lvgl/tests/test_images/stride_align64/LZ4/test_A1_LZ4_align64.cyclo ./lvgl/tests/test_images/stride_align64/LZ4/test_A1_LZ4_align64.d ./lvgl/tests/test_images/stride_align64/LZ4/test_A1_LZ4_align64.o ./lvgl/tests/test_images/stride_align64/LZ4/test_A1_LZ4_align64.su ./lvgl/tests/test_images/stride_align64/LZ4/test_A2_LZ4_align64.cyclo ./lvgl/tests/test_images/stride_align64/LZ4/test_A2_LZ4_align64.d ./lvgl/tests/test_images/stride_align64/LZ4/test_A2_LZ4_align64.o ./lvgl/tests/test_images/stride_align64/LZ4/test_A2_LZ4_align64.su ./lvgl/tests/test_images/stride_align64/LZ4/test_A4_LZ4_align64.cyclo ./lvgl/tests/test_images/stride_align64/LZ4/test_A4_LZ4_align64.d ./lvgl/tests/test_images/stride_align64/LZ4/test_A4_LZ4_align64.o ./lvgl/tests/test_images/stride_align64/LZ4/test_A4_LZ4_align64.su ./lvgl/tests/test_images/stride_align64/LZ4/test_A8_LZ4_align64.cyclo ./lvgl/tests/test_images/stride_align64/LZ4/test_A8_LZ4_align64.d ./lvgl/tests/test_images/stride_align64/LZ4/test_A8_LZ4_align64.o ./lvgl/tests/test_images/stride_align64/LZ4/test_A8_LZ4_align64.su ./lvgl/tests/test_images/stride_align64/LZ4/test_ARGB8565_LZ4_align64.cyclo ./lvgl/tests/test_images/stride_align64/LZ4/test_ARGB8565_LZ4_align64.d ./lvgl/tests/test_images/stride_align64/LZ4/test_ARGB8565_LZ4_align64.o ./lvgl/tests/test_images/stride_align64/LZ4/test_ARGB8565_LZ4_align64.su ./lvgl/tests/test_images/stride_align64/LZ4/test_ARGB8888_LZ4_align64.cyclo ./lvgl/tests/test_images/stride_align64/LZ4/test_ARGB8888_LZ4_align64.d ./lvgl/tests/test_images/stride_align64/LZ4/test_ARGB8888_LZ4_align64.o ./lvgl/tests/test_images/stride_align64/LZ4/test_ARGB8888_LZ4_align64.su ./lvgl/tests/test_images/stride_align64/LZ4/test_ARGB8888_PREMULTIPLIED_LZ4_align64.cyclo ./lvgl/tests/test_images/stride_align64/LZ4/test_ARGB8888_PREMULTIPLIED_LZ4_align64.d ./lvgl/tests/test_images/stride_align64/LZ4/test_ARGB8888_PREMULTIPLIED_LZ4_align64.o ./lvgl/tests/test_images/stride_align64/LZ4/test_ARGB8888_PREMULTIPLIED_LZ4_align64.su ./lvgl/tests/test_images/stride_align64/LZ4/test_I1_LZ4_align64.cyclo ./lvgl/tests/test_images/stride_align64/LZ4/test_I1_LZ4_align64.d ./lvgl/tests/test_images/stride_align64/LZ4/test_I1_LZ4_align64.o ./lvgl/tests/test_images/stride_align64/LZ4/test_I1_LZ4_align64.su ./lvgl/tests/test_images/stride_align64/LZ4/test_I2_LZ4_align64.cyclo ./lvgl/tests/test_images/stride_align64/LZ4/test_I2_LZ4_align64.d ./lvgl/tests/test_images/stride_align64/LZ4/test_I2_LZ4_align64.o ./lvgl/tests/test_images/stride_align64/LZ4/test_I2_LZ4_align64.su ./lvgl/tests/test_images/stride_align64/LZ4/test_I4_LZ4_align64.cyclo ./lvgl/tests/test_images/stride_align64/LZ4/test_I4_LZ4_align64.d ./lvgl/tests/test_images/stride_align64/LZ4/test_I4_LZ4_align64.o ./lvgl/tests/test_images/stride_align64/LZ4/test_I4_LZ4_align64.su ./lvgl/tests/test_images/stride_align64/LZ4/test_I8_LZ4_align64.cyclo ./lvgl/tests/test_images/stride_align64/LZ4/test_I8_LZ4_align64.d ./lvgl/tests/test_images/stride_align64/LZ4/test_I8_LZ4_align64.o ./lvgl/tests/test_images/stride_align64/LZ4/test_I8_LZ4_align64.su ./lvgl/tests/test_images/stride_align64/LZ4/test_L8_LZ4_align64.cyclo ./lvgl/tests/test_images/stride_align64/LZ4/test_L8_LZ4_align64.d ./lvgl/tests/test_images/stride_align64/LZ4/test_L8_LZ4_align64.o ./lvgl/tests/test_images/stride_align64/LZ4/test_L8_LZ4_align64.su ./lvgl/tests/test_images/stride_align64/LZ4/test_RGB565A8_LZ4_align64.cyclo ./lvgl/tests/test_images/stride_align64/LZ4/test_RGB565A8_LZ4_align64.d ./lvgl/tests/test_images/stride_align64/LZ4/test_RGB565A8_LZ4_align64.o ./lvgl/tests/test_images/stride_align64/LZ4/test_RGB565A8_LZ4_align64.su ./lvgl/tests/test_images/stride_align64/LZ4/test_RGB565_LZ4_align64.cyclo ./lvgl/tests/test_images/stride_align64/LZ4/test_RGB565_LZ4_align64.d ./lvgl/tests/test_images/stride_align64/LZ4/test_RGB565_LZ4_align64.o ./lvgl/tests/test_images/stride_align64/LZ4/test_RGB565_LZ4_align64.su ./lvgl/tests/test_images/stride_align64/LZ4/test_RGB565_SWAPPED_LZ4_align64.cyclo ./lvgl/tests/test_images/stride_align64/LZ4/test_RGB565_SWAPPED_LZ4_align64.d ./lvgl/tests/test_images/stride_align64/LZ4/test_RGB565_SWAPPED_LZ4_align64.o ./lvgl/tests/test_images/stride_align64/LZ4/test_RGB565_SWAPPED_LZ4_align64.su ./lvgl/tests/test_images/stride_align64/LZ4/test_RGB888_LZ4_align64.cyclo ./lvgl/tests/test_images/stride_align64/LZ4/test_RGB888_LZ4_align64.d ./lvgl/tests/test_images/stride_align64/LZ4/test_RGB888_LZ4_align64.o ./lvgl/tests/test_images/stride_align64/LZ4/test_RGB888_LZ4_align64.su ./lvgl/tests/test_images/stride_align64/LZ4/test_XRGB8888_LZ4_align64.cyclo ./lvgl/tests/test_images/stride_align64/LZ4/test_XRGB8888_LZ4_align64.d ./lvgl/tests/test_images/stride_align64/LZ4/test_XRGB8888_LZ4_align64.o ./lvgl/tests/test_images/stride_align64/LZ4/test_XRGB8888_LZ4_align64.su

.PHONY: clean-lvgl-2f-tests-2f-test_images-2f-stride_align64-2f-LZ4

