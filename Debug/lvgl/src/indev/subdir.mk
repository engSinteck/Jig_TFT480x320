################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (14.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../lvgl/src/indev/lv_gridnav.c \
../lvgl/src/indev/lv_indev.c \
../lvgl/src/indev/lv_indev_gesture.c \
../lvgl/src/indev/lv_indev_scroll.c 

OBJS += \
./lvgl/src/indev/lv_gridnav.o \
./lvgl/src/indev/lv_indev.o \
./lvgl/src/indev/lv_indev_gesture.o \
./lvgl/src/indev/lv_indev_scroll.o 

C_DEPS += \
./lvgl/src/indev/lv_gridnav.d \
./lvgl/src/indev/lv_indev.d \
./lvgl/src/indev/lv_indev_gesture.d \
./lvgl/src/indev/lv_indev_scroll.d 


# Each subdirectory must supply rules for building sources it contributes
lvgl/src/indev/%.o lvgl/src/indev/%.su lvgl/src/indev/%.cyclo: ../lvgl/src/indev/%.c lvgl/src/indev/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m33 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32H562xx -DLV_LVGL_H_INCLUDE_SIMPLE -c -I../Core/Inc -I../Drivers/STM32H5xx_HAL_Driver/Inc -I../Drivers/STM32H5xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H5xx/Include -I../Drivers/CMSIS/Include -I../FATFS/Target -I../FATFS/App -I../USB_DEVICE/App -I../USB_DEVICE/Target -I../Middlewares/Third_Party/FreeRTOS/Source/include/ -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2/ -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM33_NTZ/non_secure/ -I../Middlewares/Third_Party/FreeRTOS/Source/portable/MemMang -I../Middlewares/Third_Party/CMSIS/RTOS2/Include/ -I../Middlewares/Third_Party/FatFs/src -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -I../lvgl -O2 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-lvgl-2f-src-2f-indev

clean-lvgl-2f-src-2f-indev:
	-$(RM) ./lvgl/src/indev/lv_gridnav.cyclo ./lvgl/src/indev/lv_gridnav.d ./lvgl/src/indev/lv_gridnav.o ./lvgl/src/indev/lv_gridnav.su ./lvgl/src/indev/lv_indev.cyclo ./lvgl/src/indev/lv_indev.d ./lvgl/src/indev/lv_indev.o ./lvgl/src/indev/lv_indev.su ./lvgl/src/indev/lv_indev_gesture.cyclo ./lvgl/src/indev/lv_indev_gesture.d ./lvgl/src/indev/lv_indev_gesture.o ./lvgl/src/indev/lv_indev_gesture.su ./lvgl/src/indev/lv_indev_scroll.cyclo ./lvgl/src/indev/lv_indev_scroll.d ./lvgl/src/indev/lv_indev_scroll.o ./lvgl/src/indev/lv_indev_scroll.su

.PHONY: clean-lvgl-2f-src-2f-indev

