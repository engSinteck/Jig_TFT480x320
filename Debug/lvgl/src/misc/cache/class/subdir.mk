################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (14.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../lvgl/src/misc/cache/class/lv_cache_lru_ll.c \
../lvgl/src/misc/cache/class/lv_cache_lru_rb.c \
../lvgl/src/misc/cache/class/lv_cache_sc_da.c 

OBJS += \
./lvgl/src/misc/cache/class/lv_cache_lru_ll.o \
./lvgl/src/misc/cache/class/lv_cache_lru_rb.o \
./lvgl/src/misc/cache/class/lv_cache_sc_da.o 

C_DEPS += \
./lvgl/src/misc/cache/class/lv_cache_lru_ll.d \
./lvgl/src/misc/cache/class/lv_cache_lru_rb.d \
./lvgl/src/misc/cache/class/lv_cache_sc_da.d 


# Each subdirectory must supply rules for building sources it contributes
lvgl/src/misc/cache/class/%.o lvgl/src/misc/cache/class/%.su lvgl/src/misc/cache/class/%.cyclo: ../lvgl/src/misc/cache/class/%.c lvgl/src/misc/cache/class/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m33 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32H562xx -DLV_LVGL_H_INCLUDE_SIMPLE -c -I../Core/Inc -I../Drivers/STM32H5xx_HAL_Driver/Inc -I../Drivers/STM32H5xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H5xx/Include -I../Drivers/CMSIS/Include -I../FATFS/Target -I../FATFS/App -I../USB_DEVICE/App -I../USB_DEVICE/Target -I../Middlewares/Third_Party/FreeRTOS/Source/include/ -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2/ -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM33_NTZ/non_secure/ -I../Middlewares/Third_Party/FreeRTOS/Source/portable/MemMang -I../Middlewares/Third_Party/CMSIS/RTOS2/Include/ -I../Middlewares/Third_Party/FatFs/src -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -I../lvgl -O2 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-lvgl-2f-src-2f-misc-2f-cache-2f-class

clean-lvgl-2f-src-2f-misc-2f-cache-2f-class:
	-$(RM) ./lvgl/src/misc/cache/class/lv_cache_lru_ll.cyclo ./lvgl/src/misc/cache/class/lv_cache_lru_ll.d ./lvgl/src/misc/cache/class/lv_cache_lru_ll.o ./lvgl/src/misc/cache/class/lv_cache_lru_ll.su ./lvgl/src/misc/cache/class/lv_cache_lru_rb.cyclo ./lvgl/src/misc/cache/class/lv_cache_lru_rb.d ./lvgl/src/misc/cache/class/lv_cache_lru_rb.o ./lvgl/src/misc/cache/class/lv_cache_lru_rb.su ./lvgl/src/misc/cache/class/lv_cache_sc_da.cyclo ./lvgl/src/misc/cache/class/lv_cache_sc_da.d ./lvgl/src/misc/cache/class/lv_cache_sc_da.o ./lvgl/src/misc/cache/class/lv_cache_sc_da.su

.PHONY: clean-lvgl-2f-src-2f-misc-2f-cache-2f-class

