################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (14.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../lvgl/tests/src/test_cases/libs/test_barcode.c \
../lvgl/tests/src/test_cases/libs/test_bin_decoder.c \
../lvgl/tests/src/test_cases/libs/test_bmp.c \
../lvgl/tests/src/test_cases/libs/test_ffmpeg.c \
../lvgl/tests/src/test_cases/libs/test_font_stress.c \
../lvgl/tests/src/test_cases/libs/test_freetype.c \
../lvgl/tests/src/test_cases/libs/test_gif.c \
../lvgl/tests/src/test_cases/libs/test_libjpeg_turbo.c \
../lvgl/tests/src/test_cases/libs/test_libpng.c \
../lvgl/tests/src/test_cases/libs/test_libwebp.c \
../lvgl/tests/src/test_cases/libs/test_lodepng.c \
../lvgl/tests/src/test_cases/libs/test_memmove.c \
../lvgl/tests/src/test_cases/libs/test_qrcode.c \
../lvgl/tests/src/test_cases/libs/test_svg_decoder.c \
../lvgl/tests/src/test_cases/libs/test_tiny_ttf.c \
../lvgl/tests/src/test_cases/libs/test_tjpgd.c 

OBJS += \
./lvgl/tests/src/test_cases/libs/test_barcode.o \
./lvgl/tests/src/test_cases/libs/test_bin_decoder.o \
./lvgl/tests/src/test_cases/libs/test_bmp.o \
./lvgl/tests/src/test_cases/libs/test_ffmpeg.o \
./lvgl/tests/src/test_cases/libs/test_font_stress.o \
./lvgl/tests/src/test_cases/libs/test_freetype.o \
./lvgl/tests/src/test_cases/libs/test_gif.o \
./lvgl/tests/src/test_cases/libs/test_libjpeg_turbo.o \
./lvgl/tests/src/test_cases/libs/test_libpng.o \
./lvgl/tests/src/test_cases/libs/test_libwebp.o \
./lvgl/tests/src/test_cases/libs/test_lodepng.o \
./lvgl/tests/src/test_cases/libs/test_memmove.o \
./lvgl/tests/src/test_cases/libs/test_qrcode.o \
./lvgl/tests/src/test_cases/libs/test_svg_decoder.o \
./lvgl/tests/src/test_cases/libs/test_tiny_ttf.o \
./lvgl/tests/src/test_cases/libs/test_tjpgd.o 

C_DEPS += \
./lvgl/tests/src/test_cases/libs/test_barcode.d \
./lvgl/tests/src/test_cases/libs/test_bin_decoder.d \
./lvgl/tests/src/test_cases/libs/test_bmp.d \
./lvgl/tests/src/test_cases/libs/test_ffmpeg.d \
./lvgl/tests/src/test_cases/libs/test_font_stress.d \
./lvgl/tests/src/test_cases/libs/test_freetype.d \
./lvgl/tests/src/test_cases/libs/test_gif.d \
./lvgl/tests/src/test_cases/libs/test_libjpeg_turbo.d \
./lvgl/tests/src/test_cases/libs/test_libpng.d \
./lvgl/tests/src/test_cases/libs/test_libwebp.d \
./lvgl/tests/src/test_cases/libs/test_lodepng.d \
./lvgl/tests/src/test_cases/libs/test_memmove.d \
./lvgl/tests/src/test_cases/libs/test_qrcode.d \
./lvgl/tests/src/test_cases/libs/test_svg_decoder.d \
./lvgl/tests/src/test_cases/libs/test_tiny_ttf.d \
./lvgl/tests/src/test_cases/libs/test_tjpgd.d 


# Each subdirectory must supply rules for building sources it contributes
lvgl/tests/src/test_cases/libs/%.o lvgl/tests/src/test_cases/libs/%.su lvgl/tests/src/test_cases/libs/%.cyclo: ../lvgl/tests/src/test_cases/libs/%.c lvgl/tests/src/test_cases/libs/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m33 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32H562xx -DLV_LVGL_H_INCLUDE_SIMPLE -c -I../Core/Inc -I../Drivers/STM32H5xx_HAL_Driver/Inc -I../Drivers/STM32H5xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H5xx/Include -I../Drivers/CMSIS/Include -I../FATFS/Target -I../FATFS/App -I../USB_DEVICE/App -I../USB_DEVICE/Target -I../Middlewares/Third_Party/FreeRTOS/Source/include/ -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2/ -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM33_NTZ/non_secure/ -I../Middlewares/Third_Party/FreeRTOS/Source/portable/MemMang -I../Middlewares/Third_Party/CMSIS/RTOS2/Include/ -I../Middlewares/Third_Party/FatFs/src -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -I../lvgl -O2 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-lvgl-2f-tests-2f-src-2f-test_cases-2f-libs

clean-lvgl-2f-tests-2f-src-2f-test_cases-2f-libs:
	-$(RM) ./lvgl/tests/src/test_cases/libs/test_barcode.cyclo ./lvgl/tests/src/test_cases/libs/test_barcode.d ./lvgl/tests/src/test_cases/libs/test_barcode.o ./lvgl/tests/src/test_cases/libs/test_barcode.su ./lvgl/tests/src/test_cases/libs/test_bin_decoder.cyclo ./lvgl/tests/src/test_cases/libs/test_bin_decoder.d ./lvgl/tests/src/test_cases/libs/test_bin_decoder.o ./lvgl/tests/src/test_cases/libs/test_bin_decoder.su ./lvgl/tests/src/test_cases/libs/test_bmp.cyclo ./lvgl/tests/src/test_cases/libs/test_bmp.d ./lvgl/tests/src/test_cases/libs/test_bmp.o ./lvgl/tests/src/test_cases/libs/test_bmp.su ./lvgl/tests/src/test_cases/libs/test_ffmpeg.cyclo ./lvgl/tests/src/test_cases/libs/test_ffmpeg.d ./lvgl/tests/src/test_cases/libs/test_ffmpeg.o ./lvgl/tests/src/test_cases/libs/test_ffmpeg.su ./lvgl/tests/src/test_cases/libs/test_font_stress.cyclo ./lvgl/tests/src/test_cases/libs/test_font_stress.d ./lvgl/tests/src/test_cases/libs/test_font_stress.o ./lvgl/tests/src/test_cases/libs/test_font_stress.su ./lvgl/tests/src/test_cases/libs/test_freetype.cyclo ./lvgl/tests/src/test_cases/libs/test_freetype.d ./lvgl/tests/src/test_cases/libs/test_freetype.o ./lvgl/tests/src/test_cases/libs/test_freetype.su ./lvgl/tests/src/test_cases/libs/test_gif.cyclo ./lvgl/tests/src/test_cases/libs/test_gif.d ./lvgl/tests/src/test_cases/libs/test_gif.o ./lvgl/tests/src/test_cases/libs/test_gif.su ./lvgl/tests/src/test_cases/libs/test_libjpeg_turbo.cyclo ./lvgl/tests/src/test_cases/libs/test_libjpeg_turbo.d ./lvgl/tests/src/test_cases/libs/test_libjpeg_turbo.o ./lvgl/tests/src/test_cases/libs/test_libjpeg_turbo.su ./lvgl/tests/src/test_cases/libs/test_libpng.cyclo ./lvgl/tests/src/test_cases/libs/test_libpng.d ./lvgl/tests/src/test_cases/libs/test_libpng.o ./lvgl/tests/src/test_cases/libs/test_libpng.su ./lvgl/tests/src/test_cases/libs/test_libwebp.cyclo ./lvgl/tests/src/test_cases/libs/test_libwebp.d ./lvgl/tests/src/test_cases/libs/test_libwebp.o ./lvgl/tests/src/test_cases/libs/test_libwebp.su ./lvgl/tests/src/test_cases/libs/test_lodepng.cyclo ./lvgl/tests/src/test_cases/libs/test_lodepng.d ./lvgl/tests/src/test_cases/libs/test_lodepng.o ./lvgl/tests/src/test_cases/libs/test_lodepng.su ./lvgl/tests/src/test_cases/libs/test_memmove.cyclo ./lvgl/tests/src/test_cases/libs/test_memmove.d ./lvgl/tests/src/test_cases/libs/test_memmove.o ./lvgl/tests/src/test_cases/libs/test_memmove.su ./lvgl/tests/src/test_cases/libs/test_qrcode.cyclo ./lvgl/tests/src/test_cases/libs/test_qrcode.d ./lvgl/tests/src/test_cases/libs/test_qrcode.o ./lvgl/tests/src/test_cases/libs/test_qrcode.su ./lvgl/tests/src/test_cases/libs/test_svg_decoder.cyclo ./lvgl/tests/src/test_cases/libs/test_svg_decoder.d ./lvgl/tests/src/test_cases/libs/test_svg_decoder.o ./lvgl/tests/src/test_cases/libs/test_svg_decoder.su ./lvgl/tests/src/test_cases/libs/test_tiny_ttf.cyclo ./lvgl/tests/src/test_cases/libs/test_tiny_ttf.d ./lvgl/tests/src/test_cases/libs/test_tiny_ttf.o ./lvgl/tests/src/test_cases/libs/test_tiny_ttf.su ./lvgl/tests/src/test_cases/libs/test_tjpgd.cyclo ./lvgl/tests/src/test_cases/libs/test_tjpgd.d ./lvgl/tests/src/test_cases/libs/test_tjpgd.o ./lvgl/tests/src/test_cases/libs/test_tjpgd.su

.PHONY: clean-lvgl-2f-tests-2f-src-2f-test_cases-2f-libs

