################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (14.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../lvgl/src/osal/lv_cmsis_rtos2.c \
../lvgl/src/osal/lv_freertos.c \
../lvgl/src/osal/lv_linux.c \
../lvgl/src/osal/lv_mqx.c \
../lvgl/src/osal/lv_os.c \
../lvgl/src/osal/lv_os_none.c \
../lvgl/src/osal/lv_pthread.c \
../lvgl/src/osal/lv_rtthread.c \
../lvgl/src/osal/lv_sdl2.c \
../lvgl/src/osal/lv_windows.c 

OBJS += \
./lvgl/src/osal/lv_cmsis_rtos2.o \
./lvgl/src/osal/lv_freertos.o \
./lvgl/src/osal/lv_linux.o \
./lvgl/src/osal/lv_mqx.o \
./lvgl/src/osal/lv_os.o \
./lvgl/src/osal/lv_os_none.o \
./lvgl/src/osal/lv_pthread.o \
./lvgl/src/osal/lv_rtthread.o \
./lvgl/src/osal/lv_sdl2.o \
./lvgl/src/osal/lv_windows.o 

C_DEPS += \
./lvgl/src/osal/lv_cmsis_rtos2.d \
./lvgl/src/osal/lv_freertos.d \
./lvgl/src/osal/lv_linux.d \
./lvgl/src/osal/lv_mqx.d \
./lvgl/src/osal/lv_os.d \
./lvgl/src/osal/lv_os_none.d \
./lvgl/src/osal/lv_pthread.d \
./lvgl/src/osal/lv_rtthread.d \
./lvgl/src/osal/lv_sdl2.d \
./lvgl/src/osal/lv_windows.d 


# Each subdirectory must supply rules for building sources it contributes
lvgl/src/osal/%.o lvgl/src/osal/%.su lvgl/src/osal/%.cyclo: ../lvgl/src/osal/%.c lvgl/src/osal/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m33 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32H562xx -DLV_LVGL_H_INCLUDE_SIMPLE -c -I../Core/Inc -I../Drivers/STM32H5xx_HAL_Driver/Inc -I../Drivers/STM32H5xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H5xx/Include -I../Drivers/CMSIS/Include -I../FATFS/Target -I../FATFS/App -I../USB_DEVICE/App -I../USB_DEVICE/Target -I../Middlewares/Third_Party/FreeRTOS/Source/include/ -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2/ -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM33_NTZ/non_secure/ -I../Middlewares/Third_Party/FreeRTOS/Source/portable/MemMang -I../Middlewares/Third_Party/CMSIS/RTOS2/Include/ -I../Middlewares/Third_Party/FatFs/src -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -I../lvgl -O2 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-lvgl-2f-src-2f-osal

clean-lvgl-2f-src-2f-osal:
	-$(RM) ./lvgl/src/osal/lv_cmsis_rtos2.cyclo ./lvgl/src/osal/lv_cmsis_rtos2.d ./lvgl/src/osal/lv_cmsis_rtos2.o ./lvgl/src/osal/lv_cmsis_rtos2.su ./lvgl/src/osal/lv_freertos.cyclo ./lvgl/src/osal/lv_freertos.d ./lvgl/src/osal/lv_freertos.o ./lvgl/src/osal/lv_freertos.su ./lvgl/src/osal/lv_linux.cyclo ./lvgl/src/osal/lv_linux.d ./lvgl/src/osal/lv_linux.o ./lvgl/src/osal/lv_linux.su ./lvgl/src/osal/lv_mqx.cyclo ./lvgl/src/osal/lv_mqx.d ./lvgl/src/osal/lv_mqx.o ./lvgl/src/osal/lv_mqx.su ./lvgl/src/osal/lv_os.cyclo ./lvgl/src/osal/lv_os.d ./lvgl/src/osal/lv_os.o ./lvgl/src/osal/lv_os.su ./lvgl/src/osal/lv_os_none.cyclo ./lvgl/src/osal/lv_os_none.d ./lvgl/src/osal/lv_os_none.o ./lvgl/src/osal/lv_os_none.su ./lvgl/src/osal/lv_pthread.cyclo ./lvgl/src/osal/lv_pthread.d ./lvgl/src/osal/lv_pthread.o ./lvgl/src/osal/lv_pthread.su ./lvgl/src/osal/lv_rtthread.cyclo ./lvgl/src/osal/lv_rtthread.d ./lvgl/src/osal/lv_rtthread.o ./lvgl/src/osal/lv_rtthread.su ./lvgl/src/osal/lv_sdl2.cyclo ./lvgl/src/osal/lv_sdl2.d ./lvgl/src/osal/lv_sdl2.o ./lvgl/src/osal/lv_sdl2.su ./lvgl/src/osal/lv_windows.cyclo ./lvgl/src/osal/lv_windows.d ./lvgl/src/osal/lv_windows.o ./lvgl/src/osal/lv_windows.su

.PHONY: clean-lvgl-2f-src-2f-osal

