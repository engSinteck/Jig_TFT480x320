################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (14.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../lvgl/examples/widgets/bar/lv_example_bar_1.c \
../lvgl/examples/widgets/bar/lv_example_bar_2.c \
../lvgl/examples/widgets/bar/lv_example_bar_3.c \
../lvgl/examples/widgets/bar/lv_example_bar_4.c \
../lvgl/examples/widgets/bar/lv_example_bar_5.c \
../lvgl/examples/widgets/bar/lv_example_bar_6.c \
../lvgl/examples/widgets/bar/lv_example_bar_7.c 

OBJS += \
./lvgl/examples/widgets/bar/lv_example_bar_1.o \
./lvgl/examples/widgets/bar/lv_example_bar_2.o \
./lvgl/examples/widgets/bar/lv_example_bar_3.o \
./lvgl/examples/widgets/bar/lv_example_bar_4.o \
./lvgl/examples/widgets/bar/lv_example_bar_5.o \
./lvgl/examples/widgets/bar/lv_example_bar_6.o \
./lvgl/examples/widgets/bar/lv_example_bar_7.o 

C_DEPS += \
./lvgl/examples/widgets/bar/lv_example_bar_1.d \
./lvgl/examples/widgets/bar/lv_example_bar_2.d \
./lvgl/examples/widgets/bar/lv_example_bar_3.d \
./lvgl/examples/widgets/bar/lv_example_bar_4.d \
./lvgl/examples/widgets/bar/lv_example_bar_5.d \
./lvgl/examples/widgets/bar/lv_example_bar_6.d \
./lvgl/examples/widgets/bar/lv_example_bar_7.d 


# Each subdirectory must supply rules for building sources it contributes
lvgl/examples/widgets/bar/%.o lvgl/examples/widgets/bar/%.su lvgl/examples/widgets/bar/%.cyclo: ../lvgl/examples/widgets/bar/%.c lvgl/examples/widgets/bar/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m33 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32H562xx -DLV_LVGL_H_INCLUDE_SIMPLE -c -I../Core/Inc -I../Drivers/STM32H5xx_HAL_Driver/Inc -I../Drivers/STM32H5xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H5xx/Include -I../Drivers/CMSIS/Include -I../FATFS/Target -I../FATFS/App -I../USB_DEVICE/App -I../USB_DEVICE/Target -I../Middlewares/Third_Party/FreeRTOS/Source/include/ -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2/ -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM33_NTZ/non_secure/ -I../Middlewares/Third_Party/FreeRTOS/Source/portable/MemMang -I../Middlewares/Third_Party/CMSIS/RTOS2/Include/ -I../Middlewares/Third_Party/FatFs/src -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -I../lvgl -O2 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-lvgl-2f-examples-2f-widgets-2f-bar

clean-lvgl-2f-examples-2f-widgets-2f-bar:
	-$(RM) ./lvgl/examples/widgets/bar/lv_example_bar_1.cyclo ./lvgl/examples/widgets/bar/lv_example_bar_1.d ./lvgl/examples/widgets/bar/lv_example_bar_1.o ./lvgl/examples/widgets/bar/lv_example_bar_1.su ./lvgl/examples/widgets/bar/lv_example_bar_2.cyclo ./lvgl/examples/widgets/bar/lv_example_bar_2.d ./lvgl/examples/widgets/bar/lv_example_bar_2.o ./lvgl/examples/widgets/bar/lv_example_bar_2.su ./lvgl/examples/widgets/bar/lv_example_bar_3.cyclo ./lvgl/examples/widgets/bar/lv_example_bar_3.d ./lvgl/examples/widgets/bar/lv_example_bar_3.o ./lvgl/examples/widgets/bar/lv_example_bar_3.su ./lvgl/examples/widgets/bar/lv_example_bar_4.cyclo ./lvgl/examples/widgets/bar/lv_example_bar_4.d ./lvgl/examples/widgets/bar/lv_example_bar_4.o ./lvgl/examples/widgets/bar/lv_example_bar_4.su ./lvgl/examples/widgets/bar/lv_example_bar_5.cyclo ./lvgl/examples/widgets/bar/lv_example_bar_5.d ./lvgl/examples/widgets/bar/lv_example_bar_5.o ./lvgl/examples/widgets/bar/lv_example_bar_5.su ./lvgl/examples/widgets/bar/lv_example_bar_6.cyclo ./lvgl/examples/widgets/bar/lv_example_bar_6.d ./lvgl/examples/widgets/bar/lv_example_bar_6.o ./lvgl/examples/widgets/bar/lv_example_bar_6.su ./lvgl/examples/widgets/bar/lv_example_bar_7.cyclo ./lvgl/examples/widgets/bar/lv_example_bar_7.d ./lvgl/examples/widgets/bar/lv_example_bar_7.o ./lvgl/examples/widgets/bar/lv_example_bar_7.su

.PHONY: clean-lvgl-2f-examples-2f-widgets-2f-bar

