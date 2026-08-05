################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (14.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../lvgl/examples/libs/tiny_ttf/lv_example_tiny_ttf_1.c \
../lvgl/examples/libs/tiny_ttf/lv_example_tiny_ttf_2.c \
../lvgl/examples/libs/tiny_ttf/lv_example_tiny_ttf_3.c \
../lvgl/examples/libs/tiny_ttf/ubuntu_font.c 

OBJS += \
./lvgl/examples/libs/tiny_ttf/lv_example_tiny_ttf_1.o \
./lvgl/examples/libs/tiny_ttf/lv_example_tiny_ttf_2.o \
./lvgl/examples/libs/tiny_ttf/lv_example_tiny_ttf_3.o \
./lvgl/examples/libs/tiny_ttf/ubuntu_font.o 

C_DEPS += \
./lvgl/examples/libs/tiny_ttf/lv_example_tiny_ttf_1.d \
./lvgl/examples/libs/tiny_ttf/lv_example_tiny_ttf_2.d \
./lvgl/examples/libs/tiny_ttf/lv_example_tiny_ttf_3.d \
./lvgl/examples/libs/tiny_ttf/ubuntu_font.d 


# Each subdirectory must supply rules for building sources it contributes
lvgl/examples/libs/tiny_ttf/%.o lvgl/examples/libs/tiny_ttf/%.su lvgl/examples/libs/tiny_ttf/%.cyclo: ../lvgl/examples/libs/tiny_ttf/%.c lvgl/examples/libs/tiny_ttf/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m33 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32H562xx -DLV_LVGL_H_INCLUDE_SIMPLE -c -I../Core/Inc -I../Drivers/STM32H5xx_HAL_Driver/Inc -I../Drivers/STM32H5xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H5xx/Include -I../Drivers/CMSIS/Include -I../FATFS/Target -I../FATFS/App -I../USB_DEVICE/App -I../USB_DEVICE/Target -I../Middlewares/Third_Party/FreeRTOS/Source/include/ -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2/ -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM33_NTZ/non_secure/ -I../Middlewares/Third_Party/FreeRTOS/Source/portable/MemMang -I../Middlewares/Third_Party/CMSIS/RTOS2/Include/ -I../Middlewares/Third_Party/FatFs/src -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -I../lvgl -O2 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-lvgl-2f-examples-2f-libs-2f-tiny_ttf

clean-lvgl-2f-examples-2f-libs-2f-tiny_ttf:
	-$(RM) ./lvgl/examples/libs/tiny_ttf/lv_example_tiny_ttf_1.cyclo ./lvgl/examples/libs/tiny_ttf/lv_example_tiny_ttf_1.d ./lvgl/examples/libs/tiny_ttf/lv_example_tiny_ttf_1.o ./lvgl/examples/libs/tiny_ttf/lv_example_tiny_ttf_1.su ./lvgl/examples/libs/tiny_ttf/lv_example_tiny_ttf_2.cyclo ./lvgl/examples/libs/tiny_ttf/lv_example_tiny_ttf_2.d ./lvgl/examples/libs/tiny_ttf/lv_example_tiny_ttf_2.o ./lvgl/examples/libs/tiny_ttf/lv_example_tiny_ttf_2.su ./lvgl/examples/libs/tiny_ttf/lv_example_tiny_ttf_3.cyclo ./lvgl/examples/libs/tiny_ttf/lv_example_tiny_ttf_3.d ./lvgl/examples/libs/tiny_ttf/lv_example_tiny_ttf_3.o ./lvgl/examples/libs/tiny_ttf/lv_example_tiny_ttf_3.su ./lvgl/examples/libs/tiny_ttf/ubuntu_font.cyclo ./lvgl/examples/libs/tiny_ttf/ubuntu_font.d ./lvgl/examples/libs/tiny_ttf/ubuntu_font.o ./lvgl/examples/libs/tiny_ttf/ubuntu_font.su

.PHONY: clean-lvgl-2f-examples-2f-libs-2f-tiny_ttf

