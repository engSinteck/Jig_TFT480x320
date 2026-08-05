################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (14.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../lvgl/src/libs/svg/lv_svg.c \
../lvgl/src/libs/svg/lv_svg_decoder.c \
../lvgl/src/libs/svg/lv_svg_parser.c \
../lvgl/src/libs/svg/lv_svg_render.c \
../lvgl/src/libs/svg/lv_svg_token.c 

OBJS += \
./lvgl/src/libs/svg/lv_svg.o \
./lvgl/src/libs/svg/lv_svg_decoder.o \
./lvgl/src/libs/svg/lv_svg_parser.o \
./lvgl/src/libs/svg/lv_svg_render.o \
./lvgl/src/libs/svg/lv_svg_token.o 

C_DEPS += \
./lvgl/src/libs/svg/lv_svg.d \
./lvgl/src/libs/svg/lv_svg_decoder.d \
./lvgl/src/libs/svg/lv_svg_parser.d \
./lvgl/src/libs/svg/lv_svg_render.d \
./lvgl/src/libs/svg/lv_svg_token.d 


# Each subdirectory must supply rules for building sources it contributes
lvgl/src/libs/svg/%.o lvgl/src/libs/svg/%.su lvgl/src/libs/svg/%.cyclo: ../lvgl/src/libs/svg/%.c lvgl/src/libs/svg/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m33 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32H562xx -DLV_LVGL_H_INCLUDE_SIMPLE -c -I../Core/Inc -I../Drivers/STM32H5xx_HAL_Driver/Inc -I../Drivers/STM32H5xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H5xx/Include -I../Drivers/CMSIS/Include -I../FATFS/Target -I../FATFS/App -I../USB_DEVICE/App -I../USB_DEVICE/Target -I../Middlewares/Third_Party/FreeRTOS/Source/include/ -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2/ -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM33_NTZ/non_secure/ -I../Middlewares/Third_Party/FreeRTOS/Source/portable/MemMang -I../Middlewares/Third_Party/CMSIS/RTOS2/Include/ -I../Middlewares/Third_Party/FatFs/src -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -I../lvgl -O2 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-lvgl-2f-src-2f-libs-2f-svg

clean-lvgl-2f-src-2f-libs-2f-svg:
	-$(RM) ./lvgl/src/libs/svg/lv_svg.cyclo ./lvgl/src/libs/svg/lv_svg.d ./lvgl/src/libs/svg/lv_svg.o ./lvgl/src/libs/svg/lv_svg.su ./lvgl/src/libs/svg/lv_svg_decoder.cyclo ./lvgl/src/libs/svg/lv_svg_decoder.d ./lvgl/src/libs/svg/lv_svg_decoder.o ./lvgl/src/libs/svg/lv_svg_decoder.su ./lvgl/src/libs/svg/lv_svg_parser.cyclo ./lvgl/src/libs/svg/lv_svg_parser.d ./lvgl/src/libs/svg/lv_svg_parser.o ./lvgl/src/libs/svg/lv_svg_parser.su ./lvgl/src/libs/svg/lv_svg_render.cyclo ./lvgl/src/libs/svg/lv_svg_render.d ./lvgl/src/libs/svg/lv_svg_render.o ./lvgl/src/libs/svg/lv_svg_render.su ./lvgl/src/libs/svg/lv_svg_token.cyclo ./lvgl/src/libs/svg/lv_svg_token.d ./lvgl/src/libs/svg/lv_svg_token.o ./lvgl/src/libs/svg/lv_svg_token.su

.PHONY: clean-lvgl-2f-src-2f-libs-2f-svg

