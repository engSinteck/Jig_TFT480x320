################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (14.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../lvgl/src/widgets/property/lv_animimage_properties.c \
../lvgl/src/widgets/property/lv_arc_properties.c \
../lvgl/src/widgets/property/lv_bar_properties.c \
../lvgl/src/widgets/property/lv_buttonmatrix_properties.c \
../lvgl/src/widgets/property/lv_chart_properties.c \
../lvgl/src/widgets/property/lv_checkbox_properties.c \
../lvgl/src/widgets/property/lv_dropdown_properties.c \
../lvgl/src/widgets/property/lv_image_properties.c \
../lvgl/src/widgets/property/lv_keyboard_properties.c \
../lvgl/src/widgets/property/lv_label_properties.c \
../lvgl/src/widgets/property/lv_led_properties.c \
../lvgl/src/widgets/property/lv_line_properties.c \
../lvgl/src/widgets/property/lv_menu_properties.c \
../lvgl/src/widgets/property/lv_obj_properties.c \
../lvgl/src/widgets/property/lv_roller_properties.c \
../lvgl/src/widgets/property/lv_scale_properties.c \
../lvgl/src/widgets/property/lv_slider_properties.c \
../lvgl/src/widgets/property/lv_span_properties.c \
../lvgl/src/widgets/property/lv_spinbox_properties.c \
../lvgl/src/widgets/property/lv_spinner_properties.c \
../lvgl/src/widgets/property/lv_style_properties.c \
../lvgl/src/widgets/property/lv_switch_properties.c \
../lvgl/src/widgets/property/lv_table_properties.c \
../lvgl/src/widgets/property/lv_tabview_properties.c \
../lvgl/src/widgets/property/lv_textarea_properties.c 

OBJS += \
./lvgl/src/widgets/property/lv_animimage_properties.o \
./lvgl/src/widgets/property/lv_arc_properties.o \
./lvgl/src/widgets/property/lv_bar_properties.o \
./lvgl/src/widgets/property/lv_buttonmatrix_properties.o \
./lvgl/src/widgets/property/lv_chart_properties.o \
./lvgl/src/widgets/property/lv_checkbox_properties.o \
./lvgl/src/widgets/property/lv_dropdown_properties.o \
./lvgl/src/widgets/property/lv_image_properties.o \
./lvgl/src/widgets/property/lv_keyboard_properties.o \
./lvgl/src/widgets/property/lv_label_properties.o \
./lvgl/src/widgets/property/lv_led_properties.o \
./lvgl/src/widgets/property/lv_line_properties.o \
./lvgl/src/widgets/property/lv_menu_properties.o \
./lvgl/src/widgets/property/lv_obj_properties.o \
./lvgl/src/widgets/property/lv_roller_properties.o \
./lvgl/src/widgets/property/lv_scale_properties.o \
./lvgl/src/widgets/property/lv_slider_properties.o \
./lvgl/src/widgets/property/lv_span_properties.o \
./lvgl/src/widgets/property/lv_spinbox_properties.o \
./lvgl/src/widgets/property/lv_spinner_properties.o \
./lvgl/src/widgets/property/lv_style_properties.o \
./lvgl/src/widgets/property/lv_switch_properties.o \
./lvgl/src/widgets/property/lv_table_properties.o \
./lvgl/src/widgets/property/lv_tabview_properties.o \
./lvgl/src/widgets/property/lv_textarea_properties.o 

C_DEPS += \
./lvgl/src/widgets/property/lv_animimage_properties.d \
./lvgl/src/widgets/property/lv_arc_properties.d \
./lvgl/src/widgets/property/lv_bar_properties.d \
./lvgl/src/widgets/property/lv_buttonmatrix_properties.d \
./lvgl/src/widgets/property/lv_chart_properties.d \
./lvgl/src/widgets/property/lv_checkbox_properties.d \
./lvgl/src/widgets/property/lv_dropdown_properties.d \
./lvgl/src/widgets/property/lv_image_properties.d \
./lvgl/src/widgets/property/lv_keyboard_properties.d \
./lvgl/src/widgets/property/lv_label_properties.d \
./lvgl/src/widgets/property/lv_led_properties.d \
./lvgl/src/widgets/property/lv_line_properties.d \
./lvgl/src/widgets/property/lv_menu_properties.d \
./lvgl/src/widgets/property/lv_obj_properties.d \
./lvgl/src/widgets/property/lv_roller_properties.d \
./lvgl/src/widgets/property/lv_scale_properties.d \
./lvgl/src/widgets/property/lv_slider_properties.d \
./lvgl/src/widgets/property/lv_span_properties.d \
./lvgl/src/widgets/property/lv_spinbox_properties.d \
./lvgl/src/widgets/property/lv_spinner_properties.d \
./lvgl/src/widgets/property/lv_style_properties.d \
./lvgl/src/widgets/property/lv_switch_properties.d \
./lvgl/src/widgets/property/lv_table_properties.d \
./lvgl/src/widgets/property/lv_tabview_properties.d \
./lvgl/src/widgets/property/lv_textarea_properties.d 


# Each subdirectory must supply rules for building sources it contributes
lvgl/src/widgets/property/%.o lvgl/src/widgets/property/%.su lvgl/src/widgets/property/%.cyclo: ../lvgl/src/widgets/property/%.c lvgl/src/widgets/property/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m33 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32H562xx -DLV_LVGL_H_INCLUDE_SIMPLE -c -I../Core/Inc -I../Drivers/STM32H5xx_HAL_Driver/Inc -I../Drivers/STM32H5xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H5xx/Include -I../Drivers/CMSIS/Include -I../FATFS/Target -I../FATFS/App -I../USB_DEVICE/App -I../USB_DEVICE/Target -I../Middlewares/Third_Party/FreeRTOS/Source/include/ -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2/ -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM33_NTZ/non_secure/ -I../Middlewares/Third_Party/FreeRTOS/Source/portable/MemMang -I../Middlewares/Third_Party/CMSIS/RTOS2/Include/ -I../Middlewares/Third_Party/FatFs/src -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -I../lvgl -O2 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-lvgl-2f-src-2f-widgets-2f-property

clean-lvgl-2f-src-2f-widgets-2f-property:
	-$(RM) ./lvgl/src/widgets/property/lv_animimage_properties.cyclo ./lvgl/src/widgets/property/lv_animimage_properties.d ./lvgl/src/widgets/property/lv_animimage_properties.o ./lvgl/src/widgets/property/lv_animimage_properties.su ./lvgl/src/widgets/property/lv_arc_properties.cyclo ./lvgl/src/widgets/property/lv_arc_properties.d ./lvgl/src/widgets/property/lv_arc_properties.o ./lvgl/src/widgets/property/lv_arc_properties.su ./lvgl/src/widgets/property/lv_bar_properties.cyclo ./lvgl/src/widgets/property/lv_bar_properties.d ./lvgl/src/widgets/property/lv_bar_properties.o ./lvgl/src/widgets/property/lv_bar_properties.su ./lvgl/src/widgets/property/lv_buttonmatrix_properties.cyclo ./lvgl/src/widgets/property/lv_buttonmatrix_properties.d ./lvgl/src/widgets/property/lv_buttonmatrix_properties.o ./lvgl/src/widgets/property/lv_buttonmatrix_properties.su ./lvgl/src/widgets/property/lv_chart_properties.cyclo ./lvgl/src/widgets/property/lv_chart_properties.d ./lvgl/src/widgets/property/lv_chart_properties.o ./lvgl/src/widgets/property/lv_chart_properties.su ./lvgl/src/widgets/property/lv_checkbox_properties.cyclo ./lvgl/src/widgets/property/lv_checkbox_properties.d ./lvgl/src/widgets/property/lv_checkbox_properties.o ./lvgl/src/widgets/property/lv_checkbox_properties.su ./lvgl/src/widgets/property/lv_dropdown_properties.cyclo ./lvgl/src/widgets/property/lv_dropdown_properties.d ./lvgl/src/widgets/property/lv_dropdown_properties.o ./lvgl/src/widgets/property/lv_dropdown_properties.su ./lvgl/src/widgets/property/lv_image_properties.cyclo ./lvgl/src/widgets/property/lv_image_properties.d ./lvgl/src/widgets/property/lv_image_properties.o ./lvgl/src/widgets/property/lv_image_properties.su ./lvgl/src/widgets/property/lv_keyboard_properties.cyclo ./lvgl/src/widgets/property/lv_keyboard_properties.d ./lvgl/src/widgets/property/lv_keyboard_properties.o ./lvgl/src/widgets/property/lv_keyboard_properties.su ./lvgl/src/widgets/property/lv_label_properties.cyclo ./lvgl/src/widgets/property/lv_label_properties.d ./lvgl/src/widgets/property/lv_label_properties.o ./lvgl/src/widgets/property/lv_label_properties.su ./lvgl/src/widgets/property/lv_led_properties.cyclo ./lvgl/src/widgets/property/lv_led_properties.d ./lvgl/src/widgets/property/lv_led_properties.o ./lvgl/src/widgets/property/lv_led_properties.su ./lvgl/src/widgets/property/lv_line_properties.cyclo ./lvgl/src/widgets/property/lv_line_properties.d ./lvgl/src/widgets/property/lv_line_properties.o ./lvgl/src/widgets/property/lv_line_properties.su ./lvgl/src/widgets/property/lv_menu_properties.cyclo ./lvgl/src/widgets/property/lv_menu_properties.d ./lvgl/src/widgets/property/lv_menu_properties.o ./lvgl/src/widgets/property/lv_menu_properties.su ./lvgl/src/widgets/property/lv_obj_properties.cyclo ./lvgl/src/widgets/property/lv_obj_properties.d ./lvgl/src/widgets/property/lv_obj_properties.o ./lvgl/src/widgets/property/lv_obj_properties.su ./lvgl/src/widgets/property/lv_roller_properties.cyclo ./lvgl/src/widgets/property/lv_roller_properties.d ./lvgl/src/widgets/property/lv_roller_properties.o ./lvgl/src/widgets/property/lv_roller_properties.su ./lvgl/src/widgets/property/lv_scale_properties.cyclo ./lvgl/src/widgets/property/lv_scale_properties.d ./lvgl/src/widgets/property/lv_scale_properties.o ./lvgl/src/widgets/property/lv_scale_properties.su ./lvgl/src/widgets/property/lv_slider_properties.cyclo ./lvgl/src/widgets/property/lv_slider_properties.d ./lvgl/src/widgets/property/lv_slider_properties.o ./lvgl/src/widgets/property/lv_slider_properties.su ./lvgl/src/widgets/property/lv_span_properties.cyclo ./lvgl/src/widgets/property/lv_span_properties.d ./lvgl/src/widgets/property/lv_span_properties.o ./lvgl/src/widgets/property/lv_span_properties.su ./lvgl/src/widgets/property/lv_spinbox_properties.cyclo ./lvgl/src/widgets/property/lv_spinbox_properties.d ./lvgl/src/widgets/property/lv_spinbox_properties.o ./lvgl/src/widgets/property/lv_spinbox_properties.su ./lvgl/src/widgets/property/lv_spinner_properties.cyclo ./lvgl/src/widgets/property/lv_spinner_properties.d ./lvgl/src/widgets/property/lv_spinner_properties.o ./lvgl/src/widgets/property/lv_spinner_properties.su ./lvgl/src/widgets/property/lv_style_properties.cyclo ./lvgl/src/widgets/property/lv_style_properties.d ./lvgl/src/widgets/property/lv_style_properties.o ./lvgl/src/widgets/property/lv_style_properties.su ./lvgl/src/widgets/property/lv_switch_properties.cyclo ./lvgl/src/widgets/property/lv_switch_properties.d ./lvgl/src/widgets/property/lv_switch_properties.o ./lvgl/src/widgets/property/lv_switch_properties.su ./lvgl/src/widgets/property/lv_table_properties.cyclo ./lvgl/src/widgets/property/lv_table_properties.d ./lvgl/src/widgets/property/lv_table_properties.o ./lvgl/src/widgets/property/lv_table_properties.su ./lvgl/src/widgets/property/lv_tabview_properties.cyclo ./lvgl/src/widgets/property/lv_tabview_properties.d ./lvgl/src/widgets/property/lv_tabview_properties.o ./lvgl/src/widgets/property/lv_tabview_properties.su ./lvgl/src/widgets/property/lv_textarea_properties.cyclo ./lvgl/src/widgets/property/lv_textarea_properties.d ./lvgl/src/widgets/property/lv_textarea_properties.o ./lvgl/src/widgets/property/lv_textarea_properties.su

.PHONY: clean-lvgl-2f-src-2f-widgets-2f-property

