################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (14.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../lvgl/src/drivers/opengles/lv_opengles_debug.c \
../lvgl/src/drivers/opengles/lv_opengles_driver.c \
../lvgl/src/drivers/opengles/lv_opengles_egl.c \
../lvgl/src/drivers/opengles/lv_opengles_glfw.c \
../lvgl/src/drivers/opengles/lv_opengles_texture.c 

OBJS += \
./lvgl/src/drivers/opengles/lv_opengles_debug.o \
./lvgl/src/drivers/opengles/lv_opengles_driver.o \
./lvgl/src/drivers/opengles/lv_opengles_egl.o \
./lvgl/src/drivers/opengles/lv_opengles_glfw.o \
./lvgl/src/drivers/opengles/lv_opengles_texture.o 

C_DEPS += \
./lvgl/src/drivers/opengles/lv_opengles_debug.d \
./lvgl/src/drivers/opengles/lv_opengles_driver.d \
./lvgl/src/drivers/opengles/lv_opengles_egl.d \
./lvgl/src/drivers/opengles/lv_opengles_glfw.d \
./lvgl/src/drivers/opengles/lv_opengles_texture.d 


# Each subdirectory must supply rules for building sources it contributes
lvgl/src/drivers/opengles/%.o lvgl/src/drivers/opengles/%.su lvgl/src/drivers/opengles/%.cyclo: ../lvgl/src/drivers/opengles/%.c lvgl/src/drivers/opengles/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m33 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32H562xx -DLV_LVGL_H_INCLUDE_SIMPLE -c -I../Core/Inc -I../Drivers/STM32H5xx_HAL_Driver/Inc -I../Drivers/STM32H5xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H5xx/Include -I../Drivers/CMSIS/Include -I../FATFS/Target -I../FATFS/App -I../USB_DEVICE/App -I../USB_DEVICE/Target -I../Middlewares/Third_Party/FreeRTOS/Source/include/ -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2/ -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM33_NTZ/non_secure/ -I../Middlewares/Third_Party/FreeRTOS/Source/portable/MemMang -I../Middlewares/Third_Party/CMSIS/RTOS2/Include/ -I../Middlewares/Third_Party/FatFs/src -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -I../lvgl -O2 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-lvgl-2f-src-2f-drivers-2f-opengles

clean-lvgl-2f-src-2f-drivers-2f-opengles:
	-$(RM) ./lvgl/src/drivers/opengles/lv_opengles_debug.cyclo ./lvgl/src/drivers/opengles/lv_opengles_debug.d ./lvgl/src/drivers/opengles/lv_opengles_debug.o ./lvgl/src/drivers/opengles/lv_opengles_debug.su ./lvgl/src/drivers/opengles/lv_opengles_driver.cyclo ./lvgl/src/drivers/opengles/lv_opengles_driver.d ./lvgl/src/drivers/opengles/lv_opengles_driver.o ./lvgl/src/drivers/opengles/lv_opengles_driver.su ./lvgl/src/drivers/opengles/lv_opengles_egl.cyclo ./lvgl/src/drivers/opengles/lv_opengles_egl.d ./lvgl/src/drivers/opengles/lv_opengles_egl.o ./lvgl/src/drivers/opengles/lv_opengles_egl.su ./lvgl/src/drivers/opengles/lv_opengles_glfw.cyclo ./lvgl/src/drivers/opengles/lv_opengles_glfw.d ./lvgl/src/drivers/opengles/lv_opengles_glfw.o ./lvgl/src/drivers/opengles/lv_opengles_glfw.su ./lvgl/src/drivers/opengles/lv_opengles_texture.cyclo ./lvgl/src/drivers/opengles/lv_opengles_texture.d ./lvgl/src/drivers/opengles/lv_opengles_texture.o ./lvgl/src/drivers/opengles/lv_opengles_texture.su

.PHONY: clean-lvgl-2f-src-2f-drivers-2f-opengles

