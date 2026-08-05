################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (14.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../USB-PD/usbpd.c \
../USB-PD/usbpd_dpm_core.c \
../USB-PD/usbpd_dpm_user.c \
../USB-PD/usbpd_pwr_if.c \
../USB-PD/usbpd_usb_if.c 

OBJS += \
./USB-PD/usbpd.o \
./USB-PD/usbpd_dpm_core.o \
./USB-PD/usbpd_dpm_user.o \
./USB-PD/usbpd_pwr_if.o \
./USB-PD/usbpd_usb_if.o 

C_DEPS += \
./USB-PD/usbpd.d \
./USB-PD/usbpd_dpm_core.d \
./USB-PD/usbpd_dpm_user.d \
./USB-PD/usbpd_pwr_if.d \
./USB-PD/usbpd_usb_if.d 


# Each subdirectory must supply rules for building sources it contributes
USB-PD/%.o USB-PD/%.su USB-PD/%.cyclo: ../USB-PD/%.c USB-PD/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m33 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32H562xx -DLV_LVGL_H_INCLUDE_SIMPLE -c -I../Core/Inc -I../Drivers/STM32H5xx_HAL_Driver/Inc -I../Drivers/STM32H5xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H5xx/Include -I../Drivers/CMSIS/Include -I../FATFS/Target -I../FATFS/App -I../USB_DEVICE/App -I../USB_DEVICE/Target -I../Middlewares/Third_Party/FreeRTOS/Source/include/ -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2/ -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM33_NTZ/non_secure/ -I../Middlewares/Third_Party/FreeRTOS/Source/portable/MemMang -I../Middlewares/Third_Party/CMSIS/RTOS2/Include/ -I../Middlewares/Third_Party/FatFs/src -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -I../lvgl -I../USB-PD -I../USB-PD/Target -O2 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-USB-2d-PD

clean-USB-2d-PD:
	-$(RM) ./USB-PD/usbpd.cyclo ./USB-PD/usbpd.d ./USB-PD/usbpd.o ./USB-PD/usbpd.su ./USB-PD/usbpd_dpm_core.cyclo ./USB-PD/usbpd_dpm_core.d ./USB-PD/usbpd_dpm_core.o ./USB-PD/usbpd_dpm_core.su ./USB-PD/usbpd_dpm_user.cyclo ./USB-PD/usbpd_dpm_user.d ./USB-PD/usbpd_dpm_user.o ./USB-PD/usbpd_dpm_user.su ./USB-PD/usbpd_pwr_if.cyclo ./USB-PD/usbpd_pwr_if.d ./USB-PD/usbpd_pwr_if.o ./USB-PD/usbpd_pwr_if.su ./USB-PD/usbpd_usb_if.cyclo ./USB-PD/usbpd_usb_if.d ./USB-PD/usbpd_usb_if.o ./USB-PD/usbpd_usb_if.su

.PHONY: clean-USB-2d-PD

