################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (14.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../lvgl/src/libs/fsdrv/lv_fs_cbfs.c \
../lvgl/src/libs/fsdrv/lv_fs_fatfs.c \
../lvgl/src/libs/fsdrv/lv_fs_frogfs.c \
../lvgl/src/libs/fsdrv/lv_fs_littlefs.c \
../lvgl/src/libs/fsdrv/lv_fs_memfs.c \
../lvgl/src/libs/fsdrv/lv_fs_posix.c \
../lvgl/src/libs/fsdrv/lv_fs_stdio.c \
../lvgl/src/libs/fsdrv/lv_fs_uefi.c \
../lvgl/src/libs/fsdrv/lv_fs_win32.c 

OBJS += \
./lvgl/src/libs/fsdrv/lv_fs_cbfs.o \
./lvgl/src/libs/fsdrv/lv_fs_fatfs.o \
./lvgl/src/libs/fsdrv/lv_fs_frogfs.o \
./lvgl/src/libs/fsdrv/lv_fs_littlefs.o \
./lvgl/src/libs/fsdrv/lv_fs_memfs.o \
./lvgl/src/libs/fsdrv/lv_fs_posix.o \
./lvgl/src/libs/fsdrv/lv_fs_stdio.o \
./lvgl/src/libs/fsdrv/lv_fs_uefi.o \
./lvgl/src/libs/fsdrv/lv_fs_win32.o 

C_DEPS += \
./lvgl/src/libs/fsdrv/lv_fs_cbfs.d \
./lvgl/src/libs/fsdrv/lv_fs_fatfs.d \
./lvgl/src/libs/fsdrv/lv_fs_frogfs.d \
./lvgl/src/libs/fsdrv/lv_fs_littlefs.d \
./lvgl/src/libs/fsdrv/lv_fs_memfs.d \
./lvgl/src/libs/fsdrv/lv_fs_posix.d \
./lvgl/src/libs/fsdrv/lv_fs_stdio.d \
./lvgl/src/libs/fsdrv/lv_fs_uefi.d \
./lvgl/src/libs/fsdrv/lv_fs_win32.d 


# Each subdirectory must supply rules for building sources it contributes
lvgl/src/libs/fsdrv/%.o lvgl/src/libs/fsdrv/%.su lvgl/src/libs/fsdrv/%.cyclo: ../lvgl/src/libs/fsdrv/%.c lvgl/src/libs/fsdrv/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m33 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32H562xx -DLV_LVGL_H_INCLUDE_SIMPLE -c -I../Core/Inc -I../Drivers/STM32H5xx_HAL_Driver/Inc -I../Drivers/STM32H5xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H5xx/Include -I../Drivers/CMSIS/Include -I../FATFS/Target -I../FATFS/App -I../USB_DEVICE/App -I../USB_DEVICE/Target -I../Middlewares/Third_Party/FreeRTOS/Source/include/ -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2/ -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM33_NTZ/non_secure/ -I../Middlewares/Third_Party/FreeRTOS/Source/portable/MemMang -I../Middlewares/Third_Party/CMSIS/RTOS2/Include/ -I../Middlewares/Third_Party/FatFs/src -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -I../lvgl -O2 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-lvgl-2f-src-2f-libs-2f-fsdrv

clean-lvgl-2f-src-2f-libs-2f-fsdrv:
	-$(RM) ./lvgl/src/libs/fsdrv/lv_fs_cbfs.cyclo ./lvgl/src/libs/fsdrv/lv_fs_cbfs.d ./lvgl/src/libs/fsdrv/lv_fs_cbfs.o ./lvgl/src/libs/fsdrv/lv_fs_cbfs.su ./lvgl/src/libs/fsdrv/lv_fs_fatfs.cyclo ./lvgl/src/libs/fsdrv/lv_fs_fatfs.d ./lvgl/src/libs/fsdrv/lv_fs_fatfs.o ./lvgl/src/libs/fsdrv/lv_fs_fatfs.su ./lvgl/src/libs/fsdrv/lv_fs_frogfs.cyclo ./lvgl/src/libs/fsdrv/lv_fs_frogfs.d ./lvgl/src/libs/fsdrv/lv_fs_frogfs.o ./lvgl/src/libs/fsdrv/lv_fs_frogfs.su ./lvgl/src/libs/fsdrv/lv_fs_littlefs.cyclo ./lvgl/src/libs/fsdrv/lv_fs_littlefs.d ./lvgl/src/libs/fsdrv/lv_fs_littlefs.o ./lvgl/src/libs/fsdrv/lv_fs_littlefs.su ./lvgl/src/libs/fsdrv/lv_fs_memfs.cyclo ./lvgl/src/libs/fsdrv/lv_fs_memfs.d ./lvgl/src/libs/fsdrv/lv_fs_memfs.o ./lvgl/src/libs/fsdrv/lv_fs_memfs.su ./lvgl/src/libs/fsdrv/lv_fs_posix.cyclo ./lvgl/src/libs/fsdrv/lv_fs_posix.d ./lvgl/src/libs/fsdrv/lv_fs_posix.o ./lvgl/src/libs/fsdrv/lv_fs_posix.su ./lvgl/src/libs/fsdrv/lv_fs_stdio.cyclo ./lvgl/src/libs/fsdrv/lv_fs_stdio.d ./lvgl/src/libs/fsdrv/lv_fs_stdio.o ./lvgl/src/libs/fsdrv/lv_fs_stdio.su ./lvgl/src/libs/fsdrv/lv_fs_uefi.cyclo ./lvgl/src/libs/fsdrv/lv_fs_uefi.d ./lvgl/src/libs/fsdrv/lv_fs_uefi.o ./lvgl/src/libs/fsdrv/lv_fs_uefi.su ./lvgl/src/libs/fsdrv/lv_fs_win32.cyclo ./lvgl/src/libs/fsdrv/lv_fs_win32.d ./lvgl/src/libs/fsdrv/lv_fs_win32.o ./lvgl/src/libs/fsdrv/lv_fs_win32.su

.PHONY: clean-lvgl-2f-src-2f-libs-2f-fsdrv

