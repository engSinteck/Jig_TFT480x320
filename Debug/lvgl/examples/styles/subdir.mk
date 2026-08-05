################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (14.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../lvgl/examples/styles/lv_example_style_1.c \
../lvgl/examples/styles/lv_example_style_10.c \
../lvgl/examples/styles/lv_example_style_11.c \
../lvgl/examples/styles/lv_example_style_12.c \
../lvgl/examples/styles/lv_example_style_13.c \
../lvgl/examples/styles/lv_example_style_14.c \
../lvgl/examples/styles/lv_example_style_15.c \
../lvgl/examples/styles/lv_example_style_16.c \
../lvgl/examples/styles/lv_example_style_17.c \
../lvgl/examples/styles/lv_example_style_18.c \
../lvgl/examples/styles/lv_example_style_19.c \
../lvgl/examples/styles/lv_example_style_2.c \
../lvgl/examples/styles/lv_example_style_20.c \
../lvgl/examples/styles/lv_example_style_21.c \
../lvgl/examples/styles/lv_example_style_3.c \
../lvgl/examples/styles/lv_example_style_4.c \
../lvgl/examples/styles/lv_example_style_5.c \
../lvgl/examples/styles/lv_example_style_6.c \
../lvgl/examples/styles/lv_example_style_7.c \
../lvgl/examples/styles/lv_example_style_8.c \
../lvgl/examples/styles/lv_example_style_9.c 

OBJS += \
./lvgl/examples/styles/lv_example_style_1.o \
./lvgl/examples/styles/lv_example_style_10.o \
./lvgl/examples/styles/lv_example_style_11.o \
./lvgl/examples/styles/lv_example_style_12.o \
./lvgl/examples/styles/lv_example_style_13.o \
./lvgl/examples/styles/lv_example_style_14.o \
./lvgl/examples/styles/lv_example_style_15.o \
./lvgl/examples/styles/lv_example_style_16.o \
./lvgl/examples/styles/lv_example_style_17.o \
./lvgl/examples/styles/lv_example_style_18.o \
./lvgl/examples/styles/lv_example_style_19.o \
./lvgl/examples/styles/lv_example_style_2.o \
./lvgl/examples/styles/lv_example_style_20.o \
./lvgl/examples/styles/lv_example_style_21.o \
./lvgl/examples/styles/lv_example_style_3.o \
./lvgl/examples/styles/lv_example_style_4.o \
./lvgl/examples/styles/lv_example_style_5.o \
./lvgl/examples/styles/lv_example_style_6.o \
./lvgl/examples/styles/lv_example_style_7.o \
./lvgl/examples/styles/lv_example_style_8.o \
./lvgl/examples/styles/lv_example_style_9.o 

C_DEPS += \
./lvgl/examples/styles/lv_example_style_1.d \
./lvgl/examples/styles/lv_example_style_10.d \
./lvgl/examples/styles/lv_example_style_11.d \
./lvgl/examples/styles/lv_example_style_12.d \
./lvgl/examples/styles/lv_example_style_13.d \
./lvgl/examples/styles/lv_example_style_14.d \
./lvgl/examples/styles/lv_example_style_15.d \
./lvgl/examples/styles/lv_example_style_16.d \
./lvgl/examples/styles/lv_example_style_17.d \
./lvgl/examples/styles/lv_example_style_18.d \
./lvgl/examples/styles/lv_example_style_19.d \
./lvgl/examples/styles/lv_example_style_2.d \
./lvgl/examples/styles/lv_example_style_20.d \
./lvgl/examples/styles/lv_example_style_21.d \
./lvgl/examples/styles/lv_example_style_3.d \
./lvgl/examples/styles/lv_example_style_4.d \
./lvgl/examples/styles/lv_example_style_5.d \
./lvgl/examples/styles/lv_example_style_6.d \
./lvgl/examples/styles/lv_example_style_7.d \
./lvgl/examples/styles/lv_example_style_8.d \
./lvgl/examples/styles/lv_example_style_9.d 


# Each subdirectory must supply rules for building sources it contributes
lvgl/examples/styles/%.o lvgl/examples/styles/%.su lvgl/examples/styles/%.cyclo: ../lvgl/examples/styles/%.c lvgl/examples/styles/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m33 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32H562xx -DLV_LVGL_H_INCLUDE_SIMPLE -c -I../Core/Inc -I../Drivers/STM32H5xx_HAL_Driver/Inc -I../Drivers/STM32H5xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H5xx/Include -I../Drivers/CMSIS/Include -I../FATFS/Target -I../FATFS/App -I../USB_DEVICE/App -I../USB_DEVICE/Target -I../Middlewares/Third_Party/FreeRTOS/Source/include/ -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2/ -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM33_NTZ/non_secure/ -I../Middlewares/Third_Party/FreeRTOS/Source/portable/MemMang -I../Middlewares/Third_Party/CMSIS/RTOS2/Include/ -I../Middlewares/Third_Party/FatFs/src -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -I../lvgl -O2 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-lvgl-2f-examples-2f-styles

clean-lvgl-2f-examples-2f-styles:
	-$(RM) ./lvgl/examples/styles/lv_example_style_1.cyclo ./lvgl/examples/styles/lv_example_style_1.d ./lvgl/examples/styles/lv_example_style_1.o ./lvgl/examples/styles/lv_example_style_1.su ./lvgl/examples/styles/lv_example_style_10.cyclo ./lvgl/examples/styles/lv_example_style_10.d ./lvgl/examples/styles/lv_example_style_10.o ./lvgl/examples/styles/lv_example_style_10.su ./lvgl/examples/styles/lv_example_style_11.cyclo ./lvgl/examples/styles/lv_example_style_11.d ./lvgl/examples/styles/lv_example_style_11.o ./lvgl/examples/styles/lv_example_style_11.su ./lvgl/examples/styles/lv_example_style_12.cyclo ./lvgl/examples/styles/lv_example_style_12.d ./lvgl/examples/styles/lv_example_style_12.o ./lvgl/examples/styles/lv_example_style_12.su ./lvgl/examples/styles/lv_example_style_13.cyclo ./lvgl/examples/styles/lv_example_style_13.d ./lvgl/examples/styles/lv_example_style_13.o ./lvgl/examples/styles/lv_example_style_13.su ./lvgl/examples/styles/lv_example_style_14.cyclo ./lvgl/examples/styles/lv_example_style_14.d ./lvgl/examples/styles/lv_example_style_14.o ./lvgl/examples/styles/lv_example_style_14.su ./lvgl/examples/styles/lv_example_style_15.cyclo ./lvgl/examples/styles/lv_example_style_15.d ./lvgl/examples/styles/lv_example_style_15.o ./lvgl/examples/styles/lv_example_style_15.su ./lvgl/examples/styles/lv_example_style_16.cyclo ./lvgl/examples/styles/lv_example_style_16.d ./lvgl/examples/styles/lv_example_style_16.o ./lvgl/examples/styles/lv_example_style_16.su ./lvgl/examples/styles/lv_example_style_17.cyclo ./lvgl/examples/styles/lv_example_style_17.d ./lvgl/examples/styles/lv_example_style_17.o ./lvgl/examples/styles/lv_example_style_17.su ./lvgl/examples/styles/lv_example_style_18.cyclo ./lvgl/examples/styles/lv_example_style_18.d ./lvgl/examples/styles/lv_example_style_18.o ./lvgl/examples/styles/lv_example_style_18.su ./lvgl/examples/styles/lv_example_style_19.cyclo ./lvgl/examples/styles/lv_example_style_19.d ./lvgl/examples/styles/lv_example_style_19.o ./lvgl/examples/styles/lv_example_style_19.su ./lvgl/examples/styles/lv_example_style_2.cyclo ./lvgl/examples/styles/lv_example_style_2.d ./lvgl/examples/styles/lv_example_style_2.o ./lvgl/examples/styles/lv_example_style_2.su ./lvgl/examples/styles/lv_example_style_20.cyclo ./lvgl/examples/styles/lv_example_style_20.d ./lvgl/examples/styles/lv_example_style_20.o ./lvgl/examples/styles/lv_example_style_20.su ./lvgl/examples/styles/lv_example_style_21.cyclo ./lvgl/examples/styles/lv_example_style_21.d ./lvgl/examples/styles/lv_example_style_21.o ./lvgl/examples/styles/lv_example_style_21.su ./lvgl/examples/styles/lv_example_style_3.cyclo ./lvgl/examples/styles/lv_example_style_3.d ./lvgl/examples/styles/lv_example_style_3.o ./lvgl/examples/styles/lv_example_style_3.su ./lvgl/examples/styles/lv_example_style_4.cyclo ./lvgl/examples/styles/lv_example_style_4.d ./lvgl/examples/styles/lv_example_style_4.o ./lvgl/examples/styles/lv_example_style_4.su ./lvgl/examples/styles/lv_example_style_5.cyclo ./lvgl/examples/styles/lv_example_style_5.d ./lvgl/examples/styles/lv_example_style_5.o ./lvgl/examples/styles/lv_example_style_5.su ./lvgl/examples/styles/lv_example_style_6.cyclo ./lvgl/examples/styles/lv_example_style_6.d ./lvgl/examples/styles/lv_example_style_6.o ./lvgl/examples/styles/lv_example_style_6.su ./lvgl/examples/styles/lv_example_style_7.cyclo ./lvgl/examples/styles/lv_example_style_7.d ./lvgl/examples/styles/lv_example_style_7.o ./lvgl/examples/styles/lv_example_style_7.su ./lvgl/examples/styles/lv_example_style_8.cyclo ./lvgl/examples/styles/lv_example_style_8.d ./lvgl/examples/styles/lv_example_style_8.o ./lvgl/examples/styles/lv_example_style_8.su ./lvgl/examples/styles/lv_example_style_9.cyclo ./lvgl/examples/styles/lv_example_style_9.d ./lvgl/examples/styles/lv_example_style_9.o ./lvgl/examples/styles/lv_example_style_9.su

.PHONY: clean-lvgl-2f-examples-2f-styles

