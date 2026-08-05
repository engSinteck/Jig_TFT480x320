################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (14.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../lvgl/tests/src/test_cases/_test_template.c \
../lvgl/tests/src/test_cases/test_align_flex.c \
../lvgl/tests/src/test_cases/test_anim.c \
../lvgl/tests/src/test_cases/test_anim_timeline.c \
../lvgl/tests/src/test_cases/test_area.c \
../lvgl/tests/src/test_cases/test_array.c \
../lvgl/tests/src/test_cases/test_async.c \
../lvgl/tests/src/test_cases/test_bindings.c \
../lvgl/tests/src/test_cases/test_circle_buf.c \
../lvgl/tests/src/test_cases/test_click.c \
../lvgl/tests/src/test_cases/test_color.c \
../lvgl/tests/src/test_cases/test_config.c \
../lvgl/tests/src/test_cases/test_demo_stress.c \
../lvgl/tests/src/test_cases/test_demo_vector_graphic.c \
../lvgl/tests/src/test_cases/test_demo_widgets.c \
../lvgl/tests/src/test_cases/test_display.c \
../lvgl/tests/src/test_cases/test_draw_buf.c \
../lvgl/tests/src/test_cases/test_event.c \
../lvgl/tests/src/test_cases/test_event_trickle.c \
../lvgl/tests/src/test_cases/test_file_explorer.c \
../lvgl/tests/src/test_cases/test_flex_grow.c \
../lvgl/tests/src/test_cases/test_font_loader.c \
../lvgl/tests/src/test_cases/test_font_manager.c \
../lvgl/tests/src/test_cases/test_fs.c \
../lvgl/tests/src/test_cases/test_gesture_pinch.c \
../lvgl/tests/src/test_cases/test_grid.c \
../lvgl/tests/src/test_cases/test_grid_fr.c \
../lvgl/tests/src/test_cases/test_gridnav.c \
../lvgl/tests/src/test_cases/test_group.c \
../lvgl/tests/src/test_cases/test_hover.c \
../lvgl/tests/src/test_cases/test_indev.c \
../lvgl/tests/src/test_cases/test_indev_event.c \
../lvgl/tests/src/test_cases/test_indev_key_remap.c \
../lvgl/tests/src/test_cases/test_lcd.c \
../lvgl/tests/src/test_cases/test_ll.c \
../lvgl/tests/src/test_cases/test_margin_align.c \
../lvgl/tests/src/test_cases/test_margin_flex.c \
../lvgl/tests/src/test_cases/test_margin_grid.c \
../lvgl/tests/src/test_cases/test_math.c \
../lvgl/tests/src/test_cases/test_mem.c \
../lvgl/tests/src/test_cases/test_observer.c \
../lvgl/tests/src/test_cases/test_palette.c \
../lvgl/tests/src/test_cases/test_profiler.c \
../lvgl/tests/src/test_cases/test_recolor.c \
../lvgl/tests/src/test_cases/test_screen_load.c \
../lvgl/tests/src/test_cases/test_snapshot.c \
../lvgl/tests/src/test_cases/test_style.c \
../lvgl/tests/src/test_cases/test_svg.c \
../lvgl/tests/src/test_cases/test_svg_anim.c \
../lvgl/tests/src/test_cases/test_svg_file.c \
../lvgl/tests/src/test_cases/test_theme.c \
../lvgl/tests/src/test_cases/test_tick.c \
../lvgl/tests/src/test_cases/test_translation.c \
../lvgl/tests/src/test_cases/test_tree.c \
../lvgl/tests/src/test_cases/test_txt.c \
../lvgl/tests/src/test_cases/test_utils.c 

OBJS += \
./lvgl/tests/src/test_cases/_test_template.o \
./lvgl/tests/src/test_cases/test_align_flex.o \
./lvgl/tests/src/test_cases/test_anim.o \
./lvgl/tests/src/test_cases/test_anim_timeline.o \
./lvgl/tests/src/test_cases/test_area.o \
./lvgl/tests/src/test_cases/test_array.o \
./lvgl/tests/src/test_cases/test_async.o \
./lvgl/tests/src/test_cases/test_bindings.o \
./lvgl/tests/src/test_cases/test_circle_buf.o \
./lvgl/tests/src/test_cases/test_click.o \
./lvgl/tests/src/test_cases/test_color.o \
./lvgl/tests/src/test_cases/test_config.o \
./lvgl/tests/src/test_cases/test_demo_stress.o \
./lvgl/tests/src/test_cases/test_demo_vector_graphic.o \
./lvgl/tests/src/test_cases/test_demo_widgets.o \
./lvgl/tests/src/test_cases/test_display.o \
./lvgl/tests/src/test_cases/test_draw_buf.o \
./lvgl/tests/src/test_cases/test_event.o \
./lvgl/tests/src/test_cases/test_event_trickle.o \
./lvgl/tests/src/test_cases/test_file_explorer.o \
./lvgl/tests/src/test_cases/test_flex_grow.o \
./lvgl/tests/src/test_cases/test_font_loader.o \
./lvgl/tests/src/test_cases/test_font_manager.o \
./lvgl/tests/src/test_cases/test_fs.o \
./lvgl/tests/src/test_cases/test_gesture_pinch.o \
./lvgl/tests/src/test_cases/test_grid.o \
./lvgl/tests/src/test_cases/test_grid_fr.o \
./lvgl/tests/src/test_cases/test_gridnav.o \
./lvgl/tests/src/test_cases/test_group.o \
./lvgl/tests/src/test_cases/test_hover.o \
./lvgl/tests/src/test_cases/test_indev.o \
./lvgl/tests/src/test_cases/test_indev_event.o \
./lvgl/tests/src/test_cases/test_indev_key_remap.o \
./lvgl/tests/src/test_cases/test_lcd.o \
./lvgl/tests/src/test_cases/test_ll.o \
./lvgl/tests/src/test_cases/test_margin_align.o \
./lvgl/tests/src/test_cases/test_margin_flex.o \
./lvgl/tests/src/test_cases/test_margin_grid.o \
./lvgl/tests/src/test_cases/test_math.o \
./lvgl/tests/src/test_cases/test_mem.o \
./lvgl/tests/src/test_cases/test_observer.o \
./lvgl/tests/src/test_cases/test_palette.o \
./lvgl/tests/src/test_cases/test_profiler.o \
./lvgl/tests/src/test_cases/test_recolor.o \
./lvgl/tests/src/test_cases/test_screen_load.o \
./lvgl/tests/src/test_cases/test_snapshot.o \
./lvgl/tests/src/test_cases/test_style.o \
./lvgl/tests/src/test_cases/test_svg.o \
./lvgl/tests/src/test_cases/test_svg_anim.o \
./lvgl/tests/src/test_cases/test_svg_file.o \
./lvgl/tests/src/test_cases/test_theme.o \
./lvgl/tests/src/test_cases/test_tick.o \
./lvgl/tests/src/test_cases/test_translation.o \
./lvgl/tests/src/test_cases/test_tree.o \
./lvgl/tests/src/test_cases/test_txt.o \
./lvgl/tests/src/test_cases/test_utils.o 

C_DEPS += \
./lvgl/tests/src/test_cases/_test_template.d \
./lvgl/tests/src/test_cases/test_align_flex.d \
./lvgl/tests/src/test_cases/test_anim.d \
./lvgl/tests/src/test_cases/test_anim_timeline.d \
./lvgl/tests/src/test_cases/test_area.d \
./lvgl/tests/src/test_cases/test_array.d \
./lvgl/tests/src/test_cases/test_async.d \
./lvgl/tests/src/test_cases/test_bindings.d \
./lvgl/tests/src/test_cases/test_circle_buf.d \
./lvgl/tests/src/test_cases/test_click.d \
./lvgl/tests/src/test_cases/test_color.d \
./lvgl/tests/src/test_cases/test_config.d \
./lvgl/tests/src/test_cases/test_demo_stress.d \
./lvgl/tests/src/test_cases/test_demo_vector_graphic.d \
./lvgl/tests/src/test_cases/test_demo_widgets.d \
./lvgl/tests/src/test_cases/test_display.d \
./lvgl/tests/src/test_cases/test_draw_buf.d \
./lvgl/tests/src/test_cases/test_event.d \
./lvgl/tests/src/test_cases/test_event_trickle.d \
./lvgl/tests/src/test_cases/test_file_explorer.d \
./lvgl/tests/src/test_cases/test_flex_grow.d \
./lvgl/tests/src/test_cases/test_font_loader.d \
./lvgl/tests/src/test_cases/test_font_manager.d \
./lvgl/tests/src/test_cases/test_fs.d \
./lvgl/tests/src/test_cases/test_gesture_pinch.d \
./lvgl/tests/src/test_cases/test_grid.d \
./lvgl/tests/src/test_cases/test_grid_fr.d \
./lvgl/tests/src/test_cases/test_gridnav.d \
./lvgl/tests/src/test_cases/test_group.d \
./lvgl/tests/src/test_cases/test_hover.d \
./lvgl/tests/src/test_cases/test_indev.d \
./lvgl/tests/src/test_cases/test_indev_event.d \
./lvgl/tests/src/test_cases/test_indev_key_remap.d \
./lvgl/tests/src/test_cases/test_lcd.d \
./lvgl/tests/src/test_cases/test_ll.d \
./lvgl/tests/src/test_cases/test_margin_align.d \
./lvgl/tests/src/test_cases/test_margin_flex.d \
./lvgl/tests/src/test_cases/test_margin_grid.d \
./lvgl/tests/src/test_cases/test_math.d \
./lvgl/tests/src/test_cases/test_mem.d \
./lvgl/tests/src/test_cases/test_observer.d \
./lvgl/tests/src/test_cases/test_palette.d \
./lvgl/tests/src/test_cases/test_profiler.d \
./lvgl/tests/src/test_cases/test_recolor.d \
./lvgl/tests/src/test_cases/test_screen_load.d \
./lvgl/tests/src/test_cases/test_snapshot.d \
./lvgl/tests/src/test_cases/test_style.d \
./lvgl/tests/src/test_cases/test_svg.d \
./lvgl/tests/src/test_cases/test_svg_anim.d \
./lvgl/tests/src/test_cases/test_svg_file.d \
./lvgl/tests/src/test_cases/test_theme.d \
./lvgl/tests/src/test_cases/test_tick.d \
./lvgl/tests/src/test_cases/test_translation.d \
./lvgl/tests/src/test_cases/test_tree.d \
./lvgl/tests/src/test_cases/test_txt.d \
./lvgl/tests/src/test_cases/test_utils.d 


# Each subdirectory must supply rules for building sources it contributes
lvgl/tests/src/test_cases/%.o lvgl/tests/src/test_cases/%.su lvgl/tests/src/test_cases/%.cyclo: ../lvgl/tests/src/test_cases/%.c lvgl/tests/src/test_cases/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m33 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32H562xx -DLV_LVGL_H_INCLUDE_SIMPLE -c -I../Core/Inc -I../Drivers/STM32H5xx_HAL_Driver/Inc -I../Drivers/STM32H5xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H5xx/Include -I../Drivers/CMSIS/Include -I../FATFS/Target -I../FATFS/App -I../USB_DEVICE/App -I../USB_DEVICE/Target -I../Middlewares/Third_Party/FreeRTOS/Source/include/ -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2/ -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM33_NTZ/non_secure/ -I../Middlewares/Third_Party/FreeRTOS/Source/portable/MemMang -I../Middlewares/Third_Party/CMSIS/RTOS2/Include/ -I../Middlewares/Third_Party/FatFs/src -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -I../lvgl -O2 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-lvgl-2f-tests-2f-src-2f-test_cases

clean-lvgl-2f-tests-2f-src-2f-test_cases:
	-$(RM) ./lvgl/tests/src/test_cases/_test_template.cyclo ./lvgl/tests/src/test_cases/_test_template.d ./lvgl/tests/src/test_cases/_test_template.o ./lvgl/tests/src/test_cases/_test_template.su ./lvgl/tests/src/test_cases/test_align_flex.cyclo ./lvgl/tests/src/test_cases/test_align_flex.d ./lvgl/tests/src/test_cases/test_align_flex.o ./lvgl/tests/src/test_cases/test_align_flex.su ./lvgl/tests/src/test_cases/test_anim.cyclo ./lvgl/tests/src/test_cases/test_anim.d ./lvgl/tests/src/test_cases/test_anim.o ./lvgl/tests/src/test_cases/test_anim.su ./lvgl/tests/src/test_cases/test_anim_timeline.cyclo ./lvgl/tests/src/test_cases/test_anim_timeline.d ./lvgl/tests/src/test_cases/test_anim_timeline.o ./lvgl/tests/src/test_cases/test_anim_timeline.su ./lvgl/tests/src/test_cases/test_area.cyclo ./lvgl/tests/src/test_cases/test_area.d ./lvgl/tests/src/test_cases/test_area.o ./lvgl/tests/src/test_cases/test_area.su ./lvgl/tests/src/test_cases/test_array.cyclo ./lvgl/tests/src/test_cases/test_array.d ./lvgl/tests/src/test_cases/test_array.o ./lvgl/tests/src/test_cases/test_array.su ./lvgl/tests/src/test_cases/test_async.cyclo ./lvgl/tests/src/test_cases/test_async.d ./lvgl/tests/src/test_cases/test_async.o ./lvgl/tests/src/test_cases/test_async.su ./lvgl/tests/src/test_cases/test_bindings.cyclo ./lvgl/tests/src/test_cases/test_bindings.d ./lvgl/tests/src/test_cases/test_bindings.o ./lvgl/tests/src/test_cases/test_bindings.su ./lvgl/tests/src/test_cases/test_circle_buf.cyclo ./lvgl/tests/src/test_cases/test_circle_buf.d ./lvgl/tests/src/test_cases/test_circle_buf.o ./lvgl/tests/src/test_cases/test_circle_buf.su ./lvgl/tests/src/test_cases/test_click.cyclo ./lvgl/tests/src/test_cases/test_click.d ./lvgl/tests/src/test_cases/test_click.o ./lvgl/tests/src/test_cases/test_click.su ./lvgl/tests/src/test_cases/test_color.cyclo ./lvgl/tests/src/test_cases/test_color.d ./lvgl/tests/src/test_cases/test_color.o ./lvgl/tests/src/test_cases/test_color.su ./lvgl/tests/src/test_cases/test_config.cyclo ./lvgl/tests/src/test_cases/test_config.d ./lvgl/tests/src/test_cases/test_config.o ./lvgl/tests/src/test_cases/test_config.su ./lvgl/tests/src/test_cases/test_demo_stress.cyclo ./lvgl/tests/src/test_cases/test_demo_stress.d ./lvgl/tests/src/test_cases/test_demo_stress.o ./lvgl/tests/src/test_cases/test_demo_stress.su ./lvgl/tests/src/test_cases/test_demo_vector_graphic.cyclo ./lvgl/tests/src/test_cases/test_demo_vector_graphic.d ./lvgl/tests/src/test_cases/test_demo_vector_graphic.o ./lvgl/tests/src/test_cases/test_demo_vector_graphic.su ./lvgl/tests/src/test_cases/test_demo_widgets.cyclo ./lvgl/tests/src/test_cases/test_demo_widgets.d ./lvgl/tests/src/test_cases/test_demo_widgets.o ./lvgl/tests/src/test_cases/test_demo_widgets.su ./lvgl/tests/src/test_cases/test_display.cyclo ./lvgl/tests/src/test_cases/test_display.d ./lvgl/tests/src/test_cases/test_display.o ./lvgl/tests/src/test_cases/test_display.su ./lvgl/tests/src/test_cases/test_draw_buf.cyclo ./lvgl/tests/src/test_cases/test_draw_buf.d ./lvgl/tests/src/test_cases/test_draw_buf.o ./lvgl/tests/src/test_cases/test_draw_buf.su ./lvgl/tests/src/test_cases/test_event.cyclo ./lvgl/tests/src/test_cases/test_event.d ./lvgl/tests/src/test_cases/test_event.o ./lvgl/tests/src/test_cases/test_event.su ./lvgl/tests/src/test_cases/test_event_trickle.cyclo ./lvgl/tests/src/test_cases/test_event_trickle.d ./lvgl/tests/src/test_cases/test_event_trickle.o ./lvgl/tests/src/test_cases/test_event_trickle.su ./lvgl/tests/src/test_cases/test_file_explorer.cyclo ./lvgl/tests/src/test_cases/test_file_explorer.d ./lvgl/tests/src/test_cases/test_file_explorer.o ./lvgl/tests/src/test_cases/test_file_explorer.su ./lvgl/tests/src/test_cases/test_flex_grow.cyclo ./lvgl/tests/src/test_cases/test_flex_grow.d ./lvgl/tests/src/test_cases/test_flex_grow.o ./lvgl/tests/src/test_cases/test_flex_grow.su ./lvgl/tests/src/test_cases/test_font_loader.cyclo ./lvgl/tests/src/test_cases/test_font_loader.d ./lvgl/tests/src/test_cases/test_font_loader.o ./lvgl/tests/src/test_cases/test_font_loader.su ./lvgl/tests/src/test_cases/test_font_manager.cyclo ./lvgl/tests/src/test_cases/test_font_manager.d ./lvgl/tests/src/test_cases/test_font_manager.o ./lvgl/tests/src/test_cases/test_font_manager.su ./lvgl/tests/src/test_cases/test_fs.cyclo ./lvgl/tests/src/test_cases/test_fs.d ./lvgl/tests/src/test_cases/test_fs.o ./lvgl/tests/src/test_cases/test_fs.su ./lvgl/tests/src/test_cases/test_gesture_pinch.cyclo ./lvgl/tests/src/test_cases/test_gesture_pinch.d ./lvgl/tests/src/test_cases/test_gesture_pinch.o ./lvgl/tests/src/test_cases/test_gesture_pinch.su ./lvgl/tests/src/test_cases/test_grid.cyclo ./lvgl/tests/src/test_cases/test_grid.d ./lvgl/tests/src/test_cases/test_grid.o ./lvgl/tests/src/test_cases/test_grid.su ./lvgl/tests/src/test_cases/test_grid_fr.cyclo ./lvgl/tests/src/test_cases/test_grid_fr.d ./lvgl/tests/src/test_cases/test_grid_fr.o ./lvgl/tests/src/test_cases/test_grid_fr.su ./lvgl/tests/src/test_cases/test_gridnav.cyclo ./lvgl/tests/src/test_cases/test_gridnav.d ./lvgl/tests/src/test_cases/test_gridnav.o ./lvgl/tests/src/test_cases/test_gridnav.su ./lvgl/tests/src/test_cases/test_group.cyclo ./lvgl/tests/src/test_cases/test_group.d ./lvgl/tests/src/test_cases/test_group.o ./lvgl/tests/src/test_cases/test_group.su ./lvgl/tests/src/test_cases/test_hover.cyclo ./lvgl/tests/src/test_cases/test_hover.d ./lvgl/tests/src/test_cases/test_hover.o ./lvgl/tests/src/test_cases/test_hover.su ./lvgl/tests/src/test_cases/test_indev.cyclo ./lvgl/tests/src/test_cases/test_indev.d ./lvgl/tests/src/test_cases/test_indev.o ./lvgl/tests/src/test_cases/test_indev.su ./lvgl/tests/src/test_cases/test_indev_event.cyclo ./lvgl/tests/src/test_cases/test_indev_event.d ./lvgl/tests/src/test_cases/test_indev_event.o ./lvgl/tests/src/test_cases/test_indev_event.su ./lvgl/tests/src/test_cases/test_indev_key_remap.cyclo ./lvgl/tests/src/test_cases/test_indev_key_remap.d ./lvgl/tests/src/test_cases/test_indev_key_remap.o
	-$(RM) ./lvgl/tests/src/test_cases/test_indev_key_remap.su ./lvgl/tests/src/test_cases/test_lcd.cyclo ./lvgl/tests/src/test_cases/test_lcd.d ./lvgl/tests/src/test_cases/test_lcd.o ./lvgl/tests/src/test_cases/test_lcd.su ./lvgl/tests/src/test_cases/test_ll.cyclo ./lvgl/tests/src/test_cases/test_ll.d ./lvgl/tests/src/test_cases/test_ll.o ./lvgl/tests/src/test_cases/test_ll.su ./lvgl/tests/src/test_cases/test_margin_align.cyclo ./lvgl/tests/src/test_cases/test_margin_align.d ./lvgl/tests/src/test_cases/test_margin_align.o ./lvgl/tests/src/test_cases/test_margin_align.su ./lvgl/tests/src/test_cases/test_margin_flex.cyclo ./lvgl/tests/src/test_cases/test_margin_flex.d ./lvgl/tests/src/test_cases/test_margin_flex.o ./lvgl/tests/src/test_cases/test_margin_flex.su ./lvgl/tests/src/test_cases/test_margin_grid.cyclo ./lvgl/tests/src/test_cases/test_margin_grid.d ./lvgl/tests/src/test_cases/test_margin_grid.o ./lvgl/tests/src/test_cases/test_margin_grid.su ./lvgl/tests/src/test_cases/test_math.cyclo ./lvgl/tests/src/test_cases/test_math.d ./lvgl/tests/src/test_cases/test_math.o ./lvgl/tests/src/test_cases/test_math.su ./lvgl/tests/src/test_cases/test_mem.cyclo ./lvgl/tests/src/test_cases/test_mem.d ./lvgl/tests/src/test_cases/test_mem.o ./lvgl/tests/src/test_cases/test_mem.su ./lvgl/tests/src/test_cases/test_observer.cyclo ./lvgl/tests/src/test_cases/test_observer.d ./lvgl/tests/src/test_cases/test_observer.o ./lvgl/tests/src/test_cases/test_observer.su ./lvgl/tests/src/test_cases/test_palette.cyclo ./lvgl/tests/src/test_cases/test_palette.d ./lvgl/tests/src/test_cases/test_palette.o ./lvgl/tests/src/test_cases/test_palette.su ./lvgl/tests/src/test_cases/test_profiler.cyclo ./lvgl/tests/src/test_cases/test_profiler.d ./lvgl/tests/src/test_cases/test_profiler.o ./lvgl/tests/src/test_cases/test_profiler.su ./lvgl/tests/src/test_cases/test_recolor.cyclo ./lvgl/tests/src/test_cases/test_recolor.d ./lvgl/tests/src/test_cases/test_recolor.o ./lvgl/tests/src/test_cases/test_recolor.su ./lvgl/tests/src/test_cases/test_screen_load.cyclo ./lvgl/tests/src/test_cases/test_screen_load.d ./lvgl/tests/src/test_cases/test_screen_load.o ./lvgl/tests/src/test_cases/test_screen_load.su ./lvgl/tests/src/test_cases/test_snapshot.cyclo ./lvgl/tests/src/test_cases/test_snapshot.d ./lvgl/tests/src/test_cases/test_snapshot.o ./lvgl/tests/src/test_cases/test_snapshot.su ./lvgl/tests/src/test_cases/test_style.cyclo ./lvgl/tests/src/test_cases/test_style.d ./lvgl/tests/src/test_cases/test_style.o ./lvgl/tests/src/test_cases/test_style.su ./lvgl/tests/src/test_cases/test_svg.cyclo ./lvgl/tests/src/test_cases/test_svg.d ./lvgl/tests/src/test_cases/test_svg.o ./lvgl/tests/src/test_cases/test_svg.su ./lvgl/tests/src/test_cases/test_svg_anim.cyclo ./lvgl/tests/src/test_cases/test_svg_anim.d ./lvgl/tests/src/test_cases/test_svg_anim.o ./lvgl/tests/src/test_cases/test_svg_anim.su ./lvgl/tests/src/test_cases/test_svg_file.cyclo ./lvgl/tests/src/test_cases/test_svg_file.d ./lvgl/tests/src/test_cases/test_svg_file.o ./lvgl/tests/src/test_cases/test_svg_file.su ./lvgl/tests/src/test_cases/test_theme.cyclo ./lvgl/tests/src/test_cases/test_theme.d ./lvgl/tests/src/test_cases/test_theme.o ./lvgl/tests/src/test_cases/test_theme.su ./lvgl/tests/src/test_cases/test_tick.cyclo ./lvgl/tests/src/test_cases/test_tick.d ./lvgl/tests/src/test_cases/test_tick.o ./lvgl/tests/src/test_cases/test_tick.su ./lvgl/tests/src/test_cases/test_translation.cyclo ./lvgl/tests/src/test_cases/test_translation.d ./lvgl/tests/src/test_cases/test_translation.o ./lvgl/tests/src/test_cases/test_translation.su ./lvgl/tests/src/test_cases/test_tree.cyclo ./lvgl/tests/src/test_cases/test_tree.d ./lvgl/tests/src/test_cases/test_tree.o ./lvgl/tests/src/test_cases/test_tree.su ./lvgl/tests/src/test_cases/test_txt.cyclo ./lvgl/tests/src/test_cases/test_txt.d ./lvgl/tests/src/test_cases/test_txt.o ./lvgl/tests/src/test_cases/test_txt.su ./lvgl/tests/src/test_cases/test_utils.cyclo ./lvgl/tests/src/test_cases/test_utils.d ./lvgl/tests/src/test_cases/test_utils.o ./lvgl/tests/src/test_cases/test_utils.su

.PHONY: clean-lvgl-2f-tests-2f-src-2f-test_cases

