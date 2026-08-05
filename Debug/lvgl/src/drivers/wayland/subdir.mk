################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (14.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../lvgl/src/drivers/wayland/lv_wayland.c \
../lvgl/src/drivers/wayland/lv_wl_egl_backend.c \
../lvgl/src/drivers/wayland/lv_wl_g2d_backend.c \
../lvgl/src/drivers/wayland/lv_wl_keyboard.c \
../lvgl/src/drivers/wayland/lv_wl_pointer.c \
../lvgl/src/drivers/wayland/lv_wl_seat.c \
../lvgl/src/drivers/wayland/lv_wl_shm_backend.c \
../lvgl/src/drivers/wayland/lv_wl_touch.c \
../lvgl/src/drivers/wayland/lv_wl_window.c \
../lvgl/src/drivers/wayland/lv_wl_xdg_shell.c 

OBJS += \
./lvgl/src/drivers/wayland/lv_wayland.o \
./lvgl/src/drivers/wayland/lv_wl_egl_backend.o \
./lvgl/src/drivers/wayland/lv_wl_g2d_backend.o \
./lvgl/src/drivers/wayland/lv_wl_keyboard.o \
./lvgl/src/drivers/wayland/lv_wl_pointer.o \
./lvgl/src/drivers/wayland/lv_wl_seat.o \
./lvgl/src/drivers/wayland/lv_wl_shm_backend.o \
./lvgl/src/drivers/wayland/lv_wl_touch.o \
./lvgl/src/drivers/wayland/lv_wl_window.o \
./lvgl/src/drivers/wayland/lv_wl_xdg_shell.o 

C_DEPS += \
./lvgl/src/drivers/wayland/lv_wayland.d \
./lvgl/src/drivers/wayland/lv_wl_egl_backend.d \
./lvgl/src/drivers/wayland/lv_wl_g2d_backend.d \
./lvgl/src/drivers/wayland/lv_wl_keyboard.d \
./lvgl/src/drivers/wayland/lv_wl_pointer.d \
./lvgl/src/drivers/wayland/lv_wl_seat.d \
./lvgl/src/drivers/wayland/lv_wl_shm_backend.d \
./lvgl/src/drivers/wayland/lv_wl_touch.d \
./lvgl/src/drivers/wayland/lv_wl_window.d \
./lvgl/src/drivers/wayland/lv_wl_xdg_shell.d 


# Each subdirectory must supply rules for building sources it contributes
lvgl/src/drivers/wayland/%.o lvgl/src/drivers/wayland/%.su lvgl/src/drivers/wayland/%.cyclo: ../lvgl/src/drivers/wayland/%.c lvgl/src/drivers/wayland/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m33 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32H562xx -DLV_LVGL_H_INCLUDE_SIMPLE -c -I../Core/Inc -I../Drivers/STM32H5xx_HAL_Driver/Inc -I../Drivers/STM32H5xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H5xx/Include -I../Drivers/CMSIS/Include -I../FATFS/Target -I../FATFS/App -I../USB_DEVICE/App -I../USB_DEVICE/Target -I../Middlewares/Third_Party/FreeRTOS/Source/include/ -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2/ -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM33_NTZ/non_secure/ -I../Middlewares/Third_Party/FreeRTOS/Source/portable/MemMang -I../Middlewares/Third_Party/CMSIS/RTOS2/Include/ -I../Middlewares/Third_Party/FatFs/src -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -I../lvgl -O2 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-lvgl-2f-src-2f-drivers-2f-wayland

clean-lvgl-2f-src-2f-drivers-2f-wayland:
	-$(RM) ./lvgl/src/drivers/wayland/lv_wayland.cyclo ./lvgl/src/drivers/wayland/lv_wayland.d ./lvgl/src/drivers/wayland/lv_wayland.o ./lvgl/src/drivers/wayland/lv_wayland.su ./lvgl/src/drivers/wayland/lv_wl_egl_backend.cyclo ./lvgl/src/drivers/wayland/lv_wl_egl_backend.d ./lvgl/src/drivers/wayland/lv_wl_egl_backend.o ./lvgl/src/drivers/wayland/lv_wl_egl_backend.su ./lvgl/src/drivers/wayland/lv_wl_g2d_backend.cyclo ./lvgl/src/drivers/wayland/lv_wl_g2d_backend.d ./lvgl/src/drivers/wayland/lv_wl_g2d_backend.o ./lvgl/src/drivers/wayland/lv_wl_g2d_backend.su ./lvgl/src/drivers/wayland/lv_wl_keyboard.cyclo ./lvgl/src/drivers/wayland/lv_wl_keyboard.d ./lvgl/src/drivers/wayland/lv_wl_keyboard.o ./lvgl/src/drivers/wayland/lv_wl_keyboard.su ./lvgl/src/drivers/wayland/lv_wl_pointer.cyclo ./lvgl/src/drivers/wayland/lv_wl_pointer.d ./lvgl/src/drivers/wayland/lv_wl_pointer.o ./lvgl/src/drivers/wayland/lv_wl_pointer.su ./lvgl/src/drivers/wayland/lv_wl_seat.cyclo ./lvgl/src/drivers/wayland/lv_wl_seat.d ./lvgl/src/drivers/wayland/lv_wl_seat.o ./lvgl/src/drivers/wayland/lv_wl_seat.su ./lvgl/src/drivers/wayland/lv_wl_shm_backend.cyclo ./lvgl/src/drivers/wayland/lv_wl_shm_backend.d ./lvgl/src/drivers/wayland/lv_wl_shm_backend.o ./lvgl/src/drivers/wayland/lv_wl_shm_backend.su ./lvgl/src/drivers/wayland/lv_wl_touch.cyclo ./lvgl/src/drivers/wayland/lv_wl_touch.d ./lvgl/src/drivers/wayland/lv_wl_touch.o ./lvgl/src/drivers/wayland/lv_wl_touch.su ./lvgl/src/drivers/wayland/lv_wl_window.cyclo ./lvgl/src/drivers/wayland/lv_wl_window.d ./lvgl/src/drivers/wayland/lv_wl_window.o ./lvgl/src/drivers/wayland/lv_wl_window.su ./lvgl/src/drivers/wayland/lv_wl_xdg_shell.cyclo ./lvgl/src/drivers/wayland/lv_wl_xdg_shell.d ./lvgl/src/drivers/wayland/lv_wl_xdg_shell.o ./lvgl/src/drivers/wayland/lv_wl_xdg_shell.su

.PHONY: clean-lvgl-2f-src-2f-drivers-2f-wayland

