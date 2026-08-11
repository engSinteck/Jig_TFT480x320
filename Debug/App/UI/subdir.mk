################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (14.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../App/UI/AUDIO.c \
../App/UI/LOGO_ONE_2.c \
../App/UI/screen_boot.c \
../App/UI/screen_dac.c \
../App/UI/screen_debug.c \
../App/UI/screen_gpio.c \
../App/UI/screen_mp3.c \
../App/UI/screen_tuner.c 

OBJS += \
./App/UI/AUDIO.o \
./App/UI/LOGO_ONE_2.o \
./App/UI/screen_boot.o \
./App/UI/screen_dac.o \
./App/UI/screen_debug.o \
./App/UI/screen_gpio.o \
./App/UI/screen_mp3.o \
./App/UI/screen_tuner.o 

C_DEPS += \
./App/UI/AUDIO.d \
./App/UI/LOGO_ONE_2.d \
./App/UI/screen_boot.d \
./App/UI/screen_dac.d \
./App/UI/screen_debug.d \
./App/UI/screen_gpio.d \
./App/UI/screen_mp3.d \
./App/UI/screen_tuner.d 


# Each subdirectory must supply rules for building sources it contributes
App/UI/%.o App/UI/%.su App/UI/%.cyclo: ../App/UI/%.c App/UI/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m33 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32H562xx -DLV_LVGL_H_INCLUDE_SIMPLE -c -I../Core/Inc -I../Drivers/STM32H5xx_HAL_Driver/Inc -I../Drivers/STM32H5xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H5xx/Include -I../Drivers/CMSIS/Include -I../FATFS/Target -I../FATFS/App -I../USB_DEVICE/App -I../USB_DEVICE/Target -I../Middlewares/Third_Party/FreeRTOS/Source/include/ -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2/ -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM33_NTZ/non_secure/ -I../Middlewares/Third_Party/FreeRTOS/Source/portable/MemMang -I../Middlewares/Third_Party/CMSIS/RTOS2/Include/ -I../Middlewares/Third_Party/FatFs/src -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -I../lvgl -O2 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-App-2f-UI

clean-App-2f-UI:
	-$(RM) ./App/UI/AUDIO.cyclo ./App/UI/AUDIO.d ./App/UI/AUDIO.o ./App/UI/AUDIO.su ./App/UI/LOGO_ONE_2.cyclo ./App/UI/LOGO_ONE_2.d ./App/UI/LOGO_ONE_2.o ./App/UI/LOGO_ONE_2.su ./App/UI/screen_boot.cyclo ./App/UI/screen_boot.d ./App/UI/screen_boot.o ./App/UI/screen_boot.su ./App/UI/screen_dac.cyclo ./App/UI/screen_dac.d ./App/UI/screen_dac.o ./App/UI/screen_dac.su ./App/UI/screen_debug.cyclo ./App/UI/screen_debug.d ./App/UI/screen_debug.o ./App/UI/screen_debug.su ./App/UI/screen_gpio.cyclo ./App/UI/screen_gpio.d ./App/UI/screen_gpio.o ./App/UI/screen_gpio.su ./App/UI/screen_mp3.cyclo ./App/UI/screen_mp3.d ./App/UI/screen_mp3.o ./App/UI/screen_mp3.su ./App/UI/screen_tuner.cyclo ./App/UI/screen_tuner.d ./App/UI/screen_tuner.o ./App/UI/screen_tuner.su

.PHONY: clean-App-2f-UI

