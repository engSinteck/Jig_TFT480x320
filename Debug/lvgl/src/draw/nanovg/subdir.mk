################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (14.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../lvgl/src/draw/nanovg/lv_draw_nanovg.c \
../lvgl/src/draw/nanovg/lv_draw_nanovg_3d.c \
../lvgl/src/draw/nanovg/lv_draw_nanovg_arc.c \
../lvgl/src/draw/nanovg/lv_draw_nanovg_border.c \
../lvgl/src/draw/nanovg/lv_draw_nanovg_box_shadow.c \
../lvgl/src/draw/nanovg/lv_draw_nanovg_fill.c \
../lvgl/src/draw/nanovg/lv_draw_nanovg_grad.c \
../lvgl/src/draw/nanovg/lv_draw_nanovg_image.c \
../lvgl/src/draw/nanovg/lv_draw_nanovg_label.c \
../lvgl/src/draw/nanovg/lv_draw_nanovg_layer.c \
../lvgl/src/draw/nanovg/lv_draw_nanovg_line.c \
../lvgl/src/draw/nanovg/lv_draw_nanovg_mask_rect.c \
../lvgl/src/draw/nanovg/lv_draw_nanovg_triangle.c \
../lvgl/src/draw/nanovg/lv_draw_nanovg_vector.c \
../lvgl/src/draw/nanovg/lv_nanovg_fbo_cache.c \
../lvgl/src/draw/nanovg/lv_nanovg_image_cache.c \
../lvgl/src/draw/nanovg/lv_nanovg_utils.c 

OBJS += \
./lvgl/src/draw/nanovg/lv_draw_nanovg.o \
./lvgl/src/draw/nanovg/lv_draw_nanovg_3d.o \
./lvgl/src/draw/nanovg/lv_draw_nanovg_arc.o \
./lvgl/src/draw/nanovg/lv_draw_nanovg_border.o \
./lvgl/src/draw/nanovg/lv_draw_nanovg_box_shadow.o \
./lvgl/src/draw/nanovg/lv_draw_nanovg_fill.o \
./lvgl/src/draw/nanovg/lv_draw_nanovg_grad.o \
./lvgl/src/draw/nanovg/lv_draw_nanovg_image.o \
./lvgl/src/draw/nanovg/lv_draw_nanovg_label.o \
./lvgl/src/draw/nanovg/lv_draw_nanovg_layer.o \
./lvgl/src/draw/nanovg/lv_draw_nanovg_line.o \
./lvgl/src/draw/nanovg/lv_draw_nanovg_mask_rect.o \
./lvgl/src/draw/nanovg/lv_draw_nanovg_triangle.o \
./lvgl/src/draw/nanovg/lv_draw_nanovg_vector.o \
./lvgl/src/draw/nanovg/lv_nanovg_fbo_cache.o \
./lvgl/src/draw/nanovg/lv_nanovg_image_cache.o \
./lvgl/src/draw/nanovg/lv_nanovg_utils.o 

C_DEPS += \
./lvgl/src/draw/nanovg/lv_draw_nanovg.d \
./lvgl/src/draw/nanovg/lv_draw_nanovg_3d.d \
./lvgl/src/draw/nanovg/lv_draw_nanovg_arc.d \
./lvgl/src/draw/nanovg/lv_draw_nanovg_border.d \
./lvgl/src/draw/nanovg/lv_draw_nanovg_box_shadow.d \
./lvgl/src/draw/nanovg/lv_draw_nanovg_fill.d \
./lvgl/src/draw/nanovg/lv_draw_nanovg_grad.d \
./lvgl/src/draw/nanovg/lv_draw_nanovg_image.d \
./lvgl/src/draw/nanovg/lv_draw_nanovg_label.d \
./lvgl/src/draw/nanovg/lv_draw_nanovg_layer.d \
./lvgl/src/draw/nanovg/lv_draw_nanovg_line.d \
./lvgl/src/draw/nanovg/lv_draw_nanovg_mask_rect.d \
./lvgl/src/draw/nanovg/lv_draw_nanovg_triangle.d \
./lvgl/src/draw/nanovg/lv_draw_nanovg_vector.d \
./lvgl/src/draw/nanovg/lv_nanovg_fbo_cache.d \
./lvgl/src/draw/nanovg/lv_nanovg_image_cache.d \
./lvgl/src/draw/nanovg/lv_nanovg_utils.d 


# Each subdirectory must supply rules for building sources it contributes
lvgl/src/draw/nanovg/%.o lvgl/src/draw/nanovg/%.su lvgl/src/draw/nanovg/%.cyclo: ../lvgl/src/draw/nanovg/%.c lvgl/src/draw/nanovg/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m33 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32H562xx -DLV_LVGL_H_INCLUDE_SIMPLE -c -I../Core/Inc -I../Drivers/STM32H5xx_HAL_Driver/Inc -I../Drivers/STM32H5xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H5xx/Include -I../Drivers/CMSIS/Include -I../FATFS/Target -I../FATFS/App -I../USB_DEVICE/App -I../USB_DEVICE/Target -I../Middlewares/Third_Party/FreeRTOS/Source/include/ -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2/ -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM33_NTZ/non_secure/ -I../Middlewares/Third_Party/FreeRTOS/Source/portable/MemMang -I../Middlewares/Third_Party/CMSIS/RTOS2/Include/ -I../Middlewares/Third_Party/FatFs/src -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -I../lvgl -O2 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-lvgl-2f-src-2f-draw-2f-nanovg

clean-lvgl-2f-src-2f-draw-2f-nanovg:
	-$(RM) ./lvgl/src/draw/nanovg/lv_draw_nanovg.cyclo ./lvgl/src/draw/nanovg/lv_draw_nanovg.d ./lvgl/src/draw/nanovg/lv_draw_nanovg.o ./lvgl/src/draw/nanovg/lv_draw_nanovg.su ./lvgl/src/draw/nanovg/lv_draw_nanovg_3d.cyclo ./lvgl/src/draw/nanovg/lv_draw_nanovg_3d.d ./lvgl/src/draw/nanovg/lv_draw_nanovg_3d.o ./lvgl/src/draw/nanovg/lv_draw_nanovg_3d.su ./lvgl/src/draw/nanovg/lv_draw_nanovg_arc.cyclo ./lvgl/src/draw/nanovg/lv_draw_nanovg_arc.d ./lvgl/src/draw/nanovg/lv_draw_nanovg_arc.o ./lvgl/src/draw/nanovg/lv_draw_nanovg_arc.su ./lvgl/src/draw/nanovg/lv_draw_nanovg_border.cyclo ./lvgl/src/draw/nanovg/lv_draw_nanovg_border.d ./lvgl/src/draw/nanovg/lv_draw_nanovg_border.o ./lvgl/src/draw/nanovg/lv_draw_nanovg_border.su ./lvgl/src/draw/nanovg/lv_draw_nanovg_box_shadow.cyclo ./lvgl/src/draw/nanovg/lv_draw_nanovg_box_shadow.d ./lvgl/src/draw/nanovg/lv_draw_nanovg_box_shadow.o ./lvgl/src/draw/nanovg/lv_draw_nanovg_box_shadow.su ./lvgl/src/draw/nanovg/lv_draw_nanovg_fill.cyclo ./lvgl/src/draw/nanovg/lv_draw_nanovg_fill.d ./lvgl/src/draw/nanovg/lv_draw_nanovg_fill.o ./lvgl/src/draw/nanovg/lv_draw_nanovg_fill.su ./lvgl/src/draw/nanovg/lv_draw_nanovg_grad.cyclo ./lvgl/src/draw/nanovg/lv_draw_nanovg_grad.d ./lvgl/src/draw/nanovg/lv_draw_nanovg_grad.o ./lvgl/src/draw/nanovg/lv_draw_nanovg_grad.su ./lvgl/src/draw/nanovg/lv_draw_nanovg_image.cyclo ./lvgl/src/draw/nanovg/lv_draw_nanovg_image.d ./lvgl/src/draw/nanovg/lv_draw_nanovg_image.o ./lvgl/src/draw/nanovg/lv_draw_nanovg_image.su ./lvgl/src/draw/nanovg/lv_draw_nanovg_label.cyclo ./lvgl/src/draw/nanovg/lv_draw_nanovg_label.d ./lvgl/src/draw/nanovg/lv_draw_nanovg_label.o ./lvgl/src/draw/nanovg/lv_draw_nanovg_label.su ./lvgl/src/draw/nanovg/lv_draw_nanovg_layer.cyclo ./lvgl/src/draw/nanovg/lv_draw_nanovg_layer.d ./lvgl/src/draw/nanovg/lv_draw_nanovg_layer.o ./lvgl/src/draw/nanovg/lv_draw_nanovg_layer.su ./lvgl/src/draw/nanovg/lv_draw_nanovg_line.cyclo ./lvgl/src/draw/nanovg/lv_draw_nanovg_line.d ./lvgl/src/draw/nanovg/lv_draw_nanovg_line.o ./lvgl/src/draw/nanovg/lv_draw_nanovg_line.su ./lvgl/src/draw/nanovg/lv_draw_nanovg_mask_rect.cyclo ./lvgl/src/draw/nanovg/lv_draw_nanovg_mask_rect.d ./lvgl/src/draw/nanovg/lv_draw_nanovg_mask_rect.o ./lvgl/src/draw/nanovg/lv_draw_nanovg_mask_rect.su ./lvgl/src/draw/nanovg/lv_draw_nanovg_triangle.cyclo ./lvgl/src/draw/nanovg/lv_draw_nanovg_triangle.d ./lvgl/src/draw/nanovg/lv_draw_nanovg_triangle.o ./lvgl/src/draw/nanovg/lv_draw_nanovg_triangle.su ./lvgl/src/draw/nanovg/lv_draw_nanovg_vector.cyclo ./lvgl/src/draw/nanovg/lv_draw_nanovg_vector.d ./lvgl/src/draw/nanovg/lv_draw_nanovg_vector.o ./lvgl/src/draw/nanovg/lv_draw_nanovg_vector.su ./lvgl/src/draw/nanovg/lv_nanovg_fbo_cache.cyclo ./lvgl/src/draw/nanovg/lv_nanovg_fbo_cache.d ./lvgl/src/draw/nanovg/lv_nanovg_fbo_cache.o ./lvgl/src/draw/nanovg/lv_nanovg_fbo_cache.su ./lvgl/src/draw/nanovg/lv_nanovg_image_cache.cyclo ./lvgl/src/draw/nanovg/lv_nanovg_image_cache.d ./lvgl/src/draw/nanovg/lv_nanovg_image_cache.o ./lvgl/src/draw/nanovg/lv_nanovg_image_cache.su ./lvgl/src/draw/nanovg/lv_nanovg_utils.cyclo ./lvgl/src/draw/nanovg/lv_nanovg_utils.d ./lvgl/src/draw/nanovg/lv_nanovg_utils.o ./lvgl/src/draw/nanovg/lv_nanovg_utils.su

.PHONY: clean-lvgl-2f-src-2f-draw-2f-nanovg

