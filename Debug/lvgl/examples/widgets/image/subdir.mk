################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (14.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../lvgl/examples/widgets/image/lv_example_image_1.c \
../lvgl/examples/widgets/image/lv_example_image_2.c \
../lvgl/examples/widgets/image/lv_example_image_3.c \
../lvgl/examples/widgets/image/lv_example_image_4.c \
../lvgl/examples/widgets/image/lv_example_image_5.c 

OBJS += \
./lvgl/examples/widgets/image/lv_example_image_1.o \
./lvgl/examples/widgets/image/lv_example_image_2.o \
./lvgl/examples/widgets/image/lv_example_image_3.o \
./lvgl/examples/widgets/image/lv_example_image_4.o \
./lvgl/examples/widgets/image/lv_example_image_5.o 

C_DEPS += \
./lvgl/examples/widgets/image/lv_example_image_1.d \
./lvgl/examples/widgets/image/lv_example_image_2.d \
./lvgl/examples/widgets/image/lv_example_image_3.d \
./lvgl/examples/widgets/image/lv_example_image_4.d \
./lvgl/examples/widgets/image/lv_example_image_5.d 


# Each subdirectory must supply rules for building sources it contributes
lvgl/examples/widgets/image/%.o lvgl/examples/widgets/image/%.su lvgl/examples/widgets/image/%.cyclo: ../lvgl/examples/widgets/image/%.c lvgl/examples/widgets/image/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m33 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32H562xx -DLV_LVGL_H_INCLUDE_SIMPLE -c -I../Core/Inc -I../Drivers/STM32H5xx_HAL_Driver/Inc -I../Drivers/STM32H5xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H5xx/Include -I../Drivers/CMSIS/Include -I../FATFS/Target -I../FATFS/App -I../USB_DEVICE/App -I../USB_DEVICE/Target -I../Middlewares/Third_Party/FreeRTOS/Source/include/ -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2/ -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM33_NTZ/non_secure/ -I../Middlewares/Third_Party/FreeRTOS/Source/portable/MemMang -I../Middlewares/Third_Party/CMSIS/RTOS2/Include/ -I../Middlewares/Third_Party/FatFs/src -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -I../lvgl -O2 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-lvgl-2f-examples-2f-widgets-2f-image

clean-lvgl-2f-examples-2f-widgets-2f-image:
	-$(RM) ./lvgl/examples/widgets/image/lv_example_image_1.cyclo ./lvgl/examples/widgets/image/lv_example_image_1.d ./lvgl/examples/widgets/image/lv_example_image_1.o ./lvgl/examples/widgets/image/lv_example_image_1.su ./lvgl/examples/widgets/image/lv_example_image_2.cyclo ./lvgl/examples/widgets/image/lv_example_image_2.d ./lvgl/examples/widgets/image/lv_example_image_2.o ./lvgl/examples/widgets/image/lv_example_image_2.su ./lvgl/examples/widgets/image/lv_example_image_3.cyclo ./lvgl/examples/widgets/image/lv_example_image_3.d ./lvgl/examples/widgets/image/lv_example_image_3.o ./lvgl/examples/widgets/image/lv_example_image_3.su ./lvgl/examples/widgets/image/lv_example_image_4.cyclo ./lvgl/examples/widgets/image/lv_example_image_4.d ./lvgl/examples/widgets/image/lv_example_image_4.o ./lvgl/examples/widgets/image/lv_example_image_4.su ./lvgl/examples/widgets/image/lv_example_image_5.cyclo ./lvgl/examples/widgets/image/lv_example_image_5.d ./lvgl/examples/widgets/image/lv_example_image_5.o ./lvgl/examples/widgets/image/lv_example_image_5.su

.PHONY: clean-lvgl-2f-examples-2f-widgets-2f-image

