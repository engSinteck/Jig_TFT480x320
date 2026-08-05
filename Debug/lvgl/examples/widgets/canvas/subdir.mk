################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (14.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../lvgl/examples/widgets/canvas/lv_example_canvas_1.c \
../lvgl/examples/widgets/canvas/lv_example_canvas_10.c \
../lvgl/examples/widgets/canvas/lv_example_canvas_11.c \
../lvgl/examples/widgets/canvas/lv_example_canvas_12.c \
../lvgl/examples/widgets/canvas/lv_example_canvas_2.c \
../lvgl/examples/widgets/canvas/lv_example_canvas_3.c \
../lvgl/examples/widgets/canvas/lv_example_canvas_4.c \
../lvgl/examples/widgets/canvas/lv_example_canvas_5.c \
../lvgl/examples/widgets/canvas/lv_example_canvas_6.c \
../lvgl/examples/widgets/canvas/lv_example_canvas_7.c \
../lvgl/examples/widgets/canvas/lv_example_canvas_8.c \
../lvgl/examples/widgets/canvas/lv_example_canvas_9.c 

OBJS += \
./lvgl/examples/widgets/canvas/lv_example_canvas_1.o \
./lvgl/examples/widgets/canvas/lv_example_canvas_10.o \
./lvgl/examples/widgets/canvas/lv_example_canvas_11.o \
./lvgl/examples/widgets/canvas/lv_example_canvas_12.o \
./lvgl/examples/widgets/canvas/lv_example_canvas_2.o \
./lvgl/examples/widgets/canvas/lv_example_canvas_3.o \
./lvgl/examples/widgets/canvas/lv_example_canvas_4.o \
./lvgl/examples/widgets/canvas/lv_example_canvas_5.o \
./lvgl/examples/widgets/canvas/lv_example_canvas_6.o \
./lvgl/examples/widgets/canvas/lv_example_canvas_7.o \
./lvgl/examples/widgets/canvas/lv_example_canvas_8.o \
./lvgl/examples/widgets/canvas/lv_example_canvas_9.o 

C_DEPS += \
./lvgl/examples/widgets/canvas/lv_example_canvas_1.d \
./lvgl/examples/widgets/canvas/lv_example_canvas_10.d \
./lvgl/examples/widgets/canvas/lv_example_canvas_11.d \
./lvgl/examples/widgets/canvas/lv_example_canvas_12.d \
./lvgl/examples/widgets/canvas/lv_example_canvas_2.d \
./lvgl/examples/widgets/canvas/lv_example_canvas_3.d \
./lvgl/examples/widgets/canvas/lv_example_canvas_4.d \
./lvgl/examples/widgets/canvas/lv_example_canvas_5.d \
./lvgl/examples/widgets/canvas/lv_example_canvas_6.d \
./lvgl/examples/widgets/canvas/lv_example_canvas_7.d \
./lvgl/examples/widgets/canvas/lv_example_canvas_8.d \
./lvgl/examples/widgets/canvas/lv_example_canvas_9.d 


# Each subdirectory must supply rules for building sources it contributes
lvgl/examples/widgets/canvas/%.o lvgl/examples/widgets/canvas/%.su lvgl/examples/widgets/canvas/%.cyclo: ../lvgl/examples/widgets/canvas/%.c lvgl/examples/widgets/canvas/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m33 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32H562xx -DLV_LVGL_H_INCLUDE_SIMPLE -c -I../Core/Inc -I../Drivers/STM32H5xx_HAL_Driver/Inc -I../Drivers/STM32H5xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H5xx/Include -I../Drivers/CMSIS/Include -I../FATFS/Target -I../FATFS/App -I../USB_DEVICE/App -I../USB_DEVICE/Target -I../Middlewares/Third_Party/FreeRTOS/Source/include/ -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2/ -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM33_NTZ/non_secure/ -I../Middlewares/Third_Party/FreeRTOS/Source/portable/MemMang -I../Middlewares/Third_Party/CMSIS/RTOS2/Include/ -I../Middlewares/Third_Party/FatFs/src -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -I../lvgl -O2 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-lvgl-2f-examples-2f-widgets-2f-canvas

clean-lvgl-2f-examples-2f-widgets-2f-canvas:
	-$(RM) ./lvgl/examples/widgets/canvas/lv_example_canvas_1.cyclo ./lvgl/examples/widgets/canvas/lv_example_canvas_1.d ./lvgl/examples/widgets/canvas/lv_example_canvas_1.o ./lvgl/examples/widgets/canvas/lv_example_canvas_1.su ./lvgl/examples/widgets/canvas/lv_example_canvas_10.cyclo ./lvgl/examples/widgets/canvas/lv_example_canvas_10.d ./lvgl/examples/widgets/canvas/lv_example_canvas_10.o ./lvgl/examples/widgets/canvas/lv_example_canvas_10.su ./lvgl/examples/widgets/canvas/lv_example_canvas_11.cyclo ./lvgl/examples/widgets/canvas/lv_example_canvas_11.d ./lvgl/examples/widgets/canvas/lv_example_canvas_11.o ./lvgl/examples/widgets/canvas/lv_example_canvas_11.su ./lvgl/examples/widgets/canvas/lv_example_canvas_12.cyclo ./lvgl/examples/widgets/canvas/lv_example_canvas_12.d ./lvgl/examples/widgets/canvas/lv_example_canvas_12.o ./lvgl/examples/widgets/canvas/lv_example_canvas_12.su ./lvgl/examples/widgets/canvas/lv_example_canvas_2.cyclo ./lvgl/examples/widgets/canvas/lv_example_canvas_2.d ./lvgl/examples/widgets/canvas/lv_example_canvas_2.o ./lvgl/examples/widgets/canvas/lv_example_canvas_2.su ./lvgl/examples/widgets/canvas/lv_example_canvas_3.cyclo ./lvgl/examples/widgets/canvas/lv_example_canvas_3.d ./lvgl/examples/widgets/canvas/lv_example_canvas_3.o ./lvgl/examples/widgets/canvas/lv_example_canvas_3.su ./lvgl/examples/widgets/canvas/lv_example_canvas_4.cyclo ./lvgl/examples/widgets/canvas/lv_example_canvas_4.d ./lvgl/examples/widgets/canvas/lv_example_canvas_4.o ./lvgl/examples/widgets/canvas/lv_example_canvas_4.su ./lvgl/examples/widgets/canvas/lv_example_canvas_5.cyclo ./lvgl/examples/widgets/canvas/lv_example_canvas_5.d ./lvgl/examples/widgets/canvas/lv_example_canvas_5.o ./lvgl/examples/widgets/canvas/lv_example_canvas_5.su ./lvgl/examples/widgets/canvas/lv_example_canvas_6.cyclo ./lvgl/examples/widgets/canvas/lv_example_canvas_6.d ./lvgl/examples/widgets/canvas/lv_example_canvas_6.o ./lvgl/examples/widgets/canvas/lv_example_canvas_6.su ./lvgl/examples/widgets/canvas/lv_example_canvas_7.cyclo ./lvgl/examples/widgets/canvas/lv_example_canvas_7.d ./lvgl/examples/widgets/canvas/lv_example_canvas_7.o ./lvgl/examples/widgets/canvas/lv_example_canvas_7.su ./lvgl/examples/widgets/canvas/lv_example_canvas_8.cyclo ./lvgl/examples/widgets/canvas/lv_example_canvas_8.d ./lvgl/examples/widgets/canvas/lv_example_canvas_8.o ./lvgl/examples/widgets/canvas/lv_example_canvas_8.su ./lvgl/examples/widgets/canvas/lv_example_canvas_9.cyclo ./lvgl/examples/widgets/canvas/lv_example_canvas_9.d ./lvgl/examples/widgets/canvas/lv_example_canvas_9.o ./lvgl/examples/widgets/canvas/lv_example_canvas_9.su

.PHONY: clean-lvgl-2f-examples-2f-widgets-2f-canvas

