################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (14.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../lvgl/demos/render/assets/img_render_arc_bg.c \
../lvgl/demos/render/assets/img_render_lvgl_logo_argb8888.c \
../lvgl/demos/render/assets/img_render_lvgl_logo_argb8888_premultiplied.c \
../lvgl/demos/render/assets/img_render_lvgl_logo_i1.c \
../lvgl/demos/render/assets/img_render_lvgl_logo_l8.c \
../lvgl/demos/render/assets/img_render_lvgl_logo_rgb565.c \
../lvgl/demos/render/assets/img_render_lvgl_logo_rgb565_swapped.c \
../lvgl/demos/render/assets/img_render_lvgl_logo_rgb565a8.c \
../lvgl/demos/render/assets/img_render_lvgl_logo_rgb888.c \
../lvgl/demos/render/assets/img_render_lvgl_logo_xrgb8888.c 

OBJS += \
./lvgl/demos/render/assets/img_render_arc_bg.o \
./lvgl/demos/render/assets/img_render_lvgl_logo_argb8888.o \
./lvgl/demos/render/assets/img_render_lvgl_logo_argb8888_premultiplied.o \
./lvgl/demos/render/assets/img_render_lvgl_logo_i1.o \
./lvgl/demos/render/assets/img_render_lvgl_logo_l8.o \
./lvgl/demos/render/assets/img_render_lvgl_logo_rgb565.o \
./lvgl/demos/render/assets/img_render_lvgl_logo_rgb565_swapped.o \
./lvgl/demos/render/assets/img_render_lvgl_logo_rgb565a8.o \
./lvgl/demos/render/assets/img_render_lvgl_logo_rgb888.o \
./lvgl/demos/render/assets/img_render_lvgl_logo_xrgb8888.o 

C_DEPS += \
./lvgl/demos/render/assets/img_render_arc_bg.d \
./lvgl/demos/render/assets/img_render_lvgl_logo_argb8888.d \
./lvgl/demos/render/assets/img_render_lvgl_logo_argb8888_premultiplied.d \
./lvgl/demos/render/assets/img_render_lvgl_logo_i1.d \
./lvgl/demos/render/assets/img_render_lvgl_logo_l8.d \
./lvgl/demos/render/assets/img_render_lvgl_logo_rgb565.d \
./lvgl/demos/render/assets/img_render_lvgl_logo_rgb565_swapped.d \
./lvgl/demos/render/assets/img_render_lvgl_logo_rgb565a8.d \
./lvgl/demos/render/assets/img_render_lvgl_logo_rgb888.d \
./lvgl/demos/render/assets/img_render_lvgl_logo_xrgb8888.d 


# Each subdirectory must supply rules for building sources it contributes
lvgl/demos/render/assets/%.o lvgl/demos/render/assets/%.su lvgl/demos/render/assets/%.cyclo: ../lvgl/demos/render/assets/%.c lvgl/demos/render/assets/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m33 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32H562xx -DLV_LVGL_H_INCLUDE_SIMPLE -c -I../Core/Inc -I../Drivers/STM32H5xx_HAL_Driver/Inc -I../Drivers/STM32H5xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H5xx/Include -I../Drivers/CMSIS/Include -I../FATFS/Target -I../FATFS/App -I../USB_DEVICE/App -I../USB_DEVICE/Target -I../Middlewares/Third_Party/FreeRTOS/Source/include/ -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2/ -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM33_NTZ/non_secure/ -I../Middlewares/Third_Party/FreeRTOS/Source/portable/MemMang -I../Middlewares/Third_Party/CMSIS/RTOS2/Include/ -I../Middlewares/Third_Party/FatFs/src -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -I../lvgl -O2 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-lvgl-2f-demos-2f-render-2f-assets

clean-lvgl-2f-demos-2f-render-2f-assets:
	-$(RM) ./lvgl/demos/render/assets/img_render_arc_bg.cyclo ./lvgl/demos/render/assets/img_render_arc_bg.d ./lvgl/demos/render/assets/img_render_arc_bg.o ./lvgl/demos/render/assets/img_render_arc_bg.su ./lvgl/demos/render/assets/img_render_lvgl_logo_argb8888.cyclo ./lvgl/demos/render/assets/img_render_lvgl_logo_argb8888.d ./lvgl/demos/render/assets/img_render_lvgl_logo_argb8888.o ./lvgl/demos/render/assets/img_render_lvgl_logo_argb8888.su ./lvgl/demos/render/assets/img_render_lvgl_logo_argb8888_premultiplied.cyclo ./lvgl/demos/render/assets/img_render_lvgl_logo_argb8888_premultiplied.d ./lvgl/demos/render/assets/img_render_lvgl_logo_argb8888_premultiplied.o ./lvgl/demos/render/assets/img_render_lvgl_logo_argb8888_premultiplied.su ./lvgl/demos/render/assets/img_render_lvgl_logo_i1.cyclo ./lvgl/demos/render/assets/img_render_lvgl_logo_i1.d ./lvgl/demos/render/assets/img_render_lvgl_logo_i1.o ./lvgl/demos/render/assets/img_render_lvgl_logo_i1.su ./lvgl/demos/render/assets/img_render_lvgl_logo_l8.cyclo ./lvgl/demos/render/assets/img_render_lvgl_logo_l8.d ./lvgl/demos/render/assets/img_render_lvgl_logo_l8.o ./lvgl/demos/render/assets/img_render_lvgl_logo_l8.su ./lvgl/demos/render/assets/img_render_lvgl_logo_rgb565.cyclo ./lvgl/demos/render/assets/img_render_lvgl_logo_rgb565.d ./lvgl/demos/render/assets/img_render_lvgl_logo_rgb565.o ./lvgl/demos/render/assets/img_render_lvgl_logo_rgb565.su ./lvgl/demos/render/assets/img_render_lvgl_logo_rgb565_swapped.cyclo ./lvgl/demos/render/assets/img_render_lvgl_logo_rgb565_swapped.d ./lvgl/demos/render/assets/img_render_lvgl_logo_rgb565_swapped.o ./lvgl/demos/render/assets/img_render_lvgl_logo_rgb565_swapped.su ./lvgl/demos/render/assets/img_render_lvgl_logo_rgb565a8.cyclo ./lvgl/demos/render/assets/img_render_lvgl_logo_rgb565a8.d ./lvgl/demos/render/assets/img_render_lvgl_logo_rgb565a8.o ./lvgl/demos/render/assets/img_render_lvgl_logo_rgb565a8.su ./lvgl/demos/render/assets/img_render_lvgl_logo_rgb888.cyclo ./lvgl/demos/render/assets/img_render_lvgl_logo_rgb888.d ./lvgl/demos/render/assets/img_render_lvgl_logo_rgb888.o ./lvgl/demos/render/assets/img_render_lvgl_logo_rgb888.su ./lvgl/demos/render/assets/img_render_lvgl_logo_xrgb8888.cyclo ./lvgl/demos/render/assets/img_render_lvgl_logo_xrgb8888.d ./lvgl/demos/render/assets/img_render_lvgl_logo_xrgb8888.o ./lvgl/demos/render/assets/img_render_lvgl_logo_xrgb8888.su

.PHONY: clean-lvgl-2f-demos-2f-render-2f-assets

