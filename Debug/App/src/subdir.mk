################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (14.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../App/src/GT911.c \
../App/src/GT911_User.c \
../App/src/ILI9488.c \
../App/src/file_handle.c \
../App/src/log_cdc.c 

OBJS += \
./App/src/GT911.o \
./App/src/GT911_User.o \
./App/src/ILI9488.o \
./App/src/file_handle.o \
./App/src/log_cdc.o 

C_DEPS += \
./App/src/GT911.d \
./App/src/GT911_User.d \
./App/src/ILI9488.d \
./App/src/file_handle.d \
./App/src/log_cdc.d 


# Each subdirectory must supply rules for building sources it contributes
App/src/%.o App/src/%.su App/src/%.cyclo: ../App/src/%.c App/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m33 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32H562xx -DLV_LVGL_H_INCLUDE_SIMPLE -c -I../Core/Inc -I../Drivers/STM32H5xx_HAL_Driver/Inc -I../Drivers/STM32H5xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H5xx/Include -I../Drivers/CMSIS/Include -I../FATFS/Target -I../FATFS/App -I../USB_DEVICE/App -I../USB_DEVICE/Target -I../Middlewares/Third_Party/FreeRTOS/Source/include/ -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2/ -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM33_NTZ/non_secure/ -I../Middlewares/Third_Party/FreeRTOS/Source/portable/MemMang -I../Middlewares/Third_Party/CMSIS/RTOS2/Include/ -I../Middlewares/Third_Party/FatFs/src -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -I../lvgl -O2 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-App-2f-src

clean-App-2f-src:
	-$(RM) ./App/src/GT911.cyclo ./App/src/GT911.d ./App/src/GT911.o ./App/src/GT911.su ./App/src/GT911_User.cyclo ./App/src/GT911_User.d ./App/src/GT911_User.o ./App/src/GT911_User.su ./App/src/ILI9488.cyclo ./App/src/ILI9488.d ./App/src/ILI9488.o ./App/src/ILI9488.su ./App/src/file_handle.cyclo ./App/src/file_handle.d ./App/src/file_handle.o ./App/src/file_handle.su ./App/src/log_cdc.cyclo ./App/src/log_cdc.d ./App/src/log_cdc.o ./App/src/log_cdc.su

.PHONY: clean-App-2f-src

