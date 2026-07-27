/*
 * screen_dac.c
 *
 *  Created on: 20 de jul. de 2026
 *      Author: rinaldo.santos
 */


#include "main.h"
#include "stdbool.h"
#include "lvgl.h"
#include "screen_dac.h"
#include "screen_debug.h"

void DAC_1(void);
void DAC_2(void);
void DAC_3(void);

extern lv_obj_t * Tela_Debug;
extern lv_obj_t * Tela_Gpio;

lv_obj_t * Tela_DAC;
static lv_obj_t * spinbox_dac1;
static lv_obj_t * spinbox_dac2;
static lv_obj_t * spinbox_dac3;

void screen_dac(void)
{
	Tela_DAC = lv_obj_create(NULL);
	lv_obj_clear_flag(Tela_DAC, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLLABLE);
	lv_obj_set_style_bg_color(Tela_DAC, lv_color_hex(0x000000), 0);
	lv_obj_set_style_bg_grad_color(Tela_DAC, lv_color_hex(0x000000), 0);

	// DAC 1
	DAC_1();

	// DAC 2
	DAC_2();

	// DAC 3 MCP4725
	DAC_3();

	Button_Menu(Tela_DAC);
}

static void lv_spinbox_dac1_increment_event_cb(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);
    if(code == LV_EVENT_SHORT_CLICKED || code  == LV_EVENT_LONG_PRESSED_REPEAT) {
        lv_spinbox_increment(spinbox_dac1);
    }
}

static void lv_spinbox_dac1_decrement_event_cb(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);
    if(code == LV_EVENT_SHORT_CLICKED || code == LV_EVENT_LONG_PRESSED_REPEAT) {
        lv_spinbox_decrement(spinbox_dac1);
    }
}

void DAC_1(void)
{
	static lv_style_t style_symbol;
	lv_style_init(&style_symbol);
	lv_style_set_text_font(&style_symbol, &lv_font_montserrat_16);
	lv_style_set_text_color(&style_symbol, lv_color_hex(0xFFFFFF));

    // DAC 1
    lv_obj_t * label1 = lv_label_create(Tela_DAC);
    lv_label_set_long_mode(label1, LV_LABEL_LONG_WRAP);     	/*Break the long lines*/
    lv_label_set_recolor(label1, true);                      	/*Enable re-coloring by commands in the text*/
    lv_label_set_text(label1, "#FFFFFF DAC 1:");
    lv_obj_align_to(label1, Tela_DAC, LV_ALIGN_TOP_LEFT, 4, 32);

    spinbox_dac1 = lv_spinbox_create(Tela_DAC);
    lv_spinbox_set_range(spinbox_dac1, 0, 4095);
    lv_spinbox_set_digit_format(spinbox_dac1, 4, 0);
    lv_spinbox_set_cursor_pos(spinbox_dac1, 0);
    lv_spinbox_set_step(spinbox_dac1, 1);
    lv_spinbox_set_value(spinbox_dac1, 0);
    lv_obj_set_width(spinbox_dac1, 64);
    lv_obj_set_pos(spinbox_dac1, 128, 24);

    lv_coord_t h = lv_obj_get_height(spinbox_dac1);

    lv_obj_t * btn_left_inc = lv_btn_create(Tela_DAC);
    lv_obj_set_size(btn_left_inc, h, h);
    lv_obj_align_to(btn_left_inc, spinbox_dac1, LV_ALIGN_OUT_RIGHT_MID, 5, 0);
    lv_obj_add_style(btn_left_inc, &style_symbol, LV_PART_MAIN);
    lv_obj_set_style_bg_img_src(btn_left_inc, LV_SYMBOL_PLUS, 0);
    lv_obj_add_event_cb(btn_left_inc, lv_spinbox_dac1_increment_event_cb, LV_EVENT_ALL,  NULL);

    lv_obj_t * btn_left_dec = lv_btn_create(Tela_DAC);
    lv_obj_set_size(btn_left_dec, h, h);
    lv_obj_align_to(btn_left_dec, spinbox_dac1, LV_ALIGN_OUT_LEFT_MID, -5, 0);
    lv_obj_add_style(btn_left_dec, &style_symbol, LV_PART_MAIN);
    lv_obj_set_style_bg_img_src(btn_left_dec, LV_SYMBOL_MINUS, 0);
    lv_obj_add_event_cb(btn_left_dec, lv_spinbox_dac1_decrement_event_cb, LV_EVENT_ALL, NULL);
}

static void lv_spinbox_dac2_increment_event_cb(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);
    if(code == LV_EVENT_SHORT_CLICKED || code  == LV_EVENT_LONG_PRESSED_REPEAT) {
        lv_spinbox_increment(spinbox_dac2);
    }
}

static void lv_spinbox_dac2_decrement_event_cb(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);
    if(code == LV_EVENT_SHORT_CLICKED || code == LV_EVENT_LONG_PRESSED_REPEAT) {
        lv_spinbox_decrement(spinbox_dac2);
    }
}

void DAC_2(void)
{
	static lv_style_t style_symbol;
	lv_style_init(&style_symbol);
	lv_style_set_text_font(&style_symbol, &lv_font_montserrat_16);
	lv_style_set_text_color(&style_symbol, lv_color_hex(0xFFFFFF));

    // DAC 2
    lv_obj_t * label1 = lv_label_create(Tela_DAC);
    lv_label_set_long_mode(label1, LV_LABEL_LONG_WRAP);     	/*Break the long lines*/
    lv_label_set_recolor(label1, true);                      	/*Enable re-coloring by commands in the text*/
    lv_label_set_text(label1, "#FFFFFF DAC 2:");
    lv_obj_align_to(label1, Tela_DAC, LV_ALIGN_TOP_LEFT, 4, 96);

    spinbox_dac2 = lv_spinbox_create(Tela_DAC);
    lv_spinbox_set_range(spinbox_dac2, 0, 4095);
    lv_spinbox_set_digit_format(spinbox_dac2, 4, 0);
    lv_spinbox_set_cursor_pos(spinbox_dac2, 0);
    lv_spinbox_set_step(spinbox_dac2, 1);
    lv_spinbox_set_value(spinbox_dac2, 0);
    lv_obj_set_width(spinbox_dac2, 64);
    lv_obj_set_pos(spinbox_dac2, 128, 88);

    lv_coord_t h = lv_obj_get_height(spinbox_dac2);

    lv_obj_t * btn_left_inc = lv_btn_create(Tela_DAC);
    lv_obj_set_size(btn_left_inc, h, h);
    lv_obj_align_to(btn_left_inc, spinbox_dac2, LV_ALIGN_OUT_RIGHT_MID, 5, 0);
    lv_obj_add_style(btn_left_inc, &style_symbol, LV_PART_MAIN);
    lv_obj_set_style_bg_img_src(btn_left_inc, LV_SYMBOL_PLUS, 0);
    lv_obj_add_event_cb(btn_left_inc, lv_spinbox_dac2_increment_event_cb, LV_EVENT_ALL,  NULL);

    lv_obj_t * btn_left_dec = lv_btn_create(Tela_DAC);
    lv_obj_set_size(btn_left_dec, h, h);
    lv_obj_align_to(btn_left_dec, spinbox_dac2, LV_ALIGN_OUT_LEFT_MID, -5, 0);
    lv_obj_add_style(btn_left_dec, &style_symbol, LV_PART_MAIN);
    lv_obj_set_style_bg_img_src(btn_left_dec, LV_SYMBOL_MINUS, 0);
    lv_obj_add_event_cb(btn_left_dec, lv_spinbox_dac2_decrement_event_cb, LV_EVENT_ALL, NULL);
}

static void lv_spinbox_dac3_increment_event_cb(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);
    if(code == LV_EVENT_SHORT_CLICKED || code  == LV_EVENT_LONG_PRESSED_REPEAT) {
        lv_spinbox_increment(spinbox_dac3);
     }
}

static void lv_spinbox_dac3_decrement_event_cb(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);
    if(code == LV_EVENT_SHORT_CLICKED || code == LV_EVENT_LONG_PRESSED_REPEAT) {
        lv_spinbox_decrement(spinbox_dac3);
     }
}

void DAC_3(void)
{
	static lv_style_t style_symbol;
	lv_style_init(&style_symbol);
	lv_style_set_text_font(&style_symbol, &lv_font_montserrat_16);
	lv_style_set_text_color(&style_symbol, lv_color_hex(0xFFFFFF));

    // DAC 3
    lv_obj_t * label1 = lv_label_create(Tela_DAC);
    lv_label_set_long_mode(label1, LV_LABEL_LONG_WRAP);     	/*Break the long lines*/
    lv_label_set_recolor(label1, true);                      	/*Enable re-coloring by commands in the text*/
    lv_label_set_text(label1, "#FFFFFF DAC 3:");
    lv_obj_align_to(label1, Tela_DAC, LV_ALIGN_TOP_LEFT, 4, 158);

    spinbox_dac3 = lv_spinbox_create(Tela_DAC);
    lv_spinbox_set_range(spinbox_dac3, 0, 4095);
    lv_spinbox_set_digit_format(spinbox_dac3, 4, 0);
    lv_spinbox_set_cursor_pos(spinbox_dac3, 0);
    lv_spinbox_set_step(spinbox_dac3, 1);
    lv_spinbox_set_value(spinbox_dac3, 0);
    lv_obj_set_width(spinbox_dac3, 64);
    lv_obj_set_pos(spinbox_dac3, 128, 152);

    lv_coord_t h = lv_obj_get_height(spinbox_dac3);

    lv_obj_t * btn_left_inc = lv_btn_create(Tela_DAC);
    lv_obj_set_size(btn_left_inc, h, h);
    lv_obj_align_to(btn_left_inc, spinbox_dac3, LV_ALIGN_OUT_RIGHT_MID, 5, 0);
    lv_obj_add_style(btn_left_inc, &style_symbol, LV_PART_MAIN);
    lv_obj_set_style_bg_img_src(btn_left_inc, LV_SYMBOL_PLUS, 0);
    lv_obj_add_event_cb(btn_left_inc, lv_spinbox_dac3_increment_event_cb, LV_EVENT_ALL,  NULL);

    lv_obj_t * btn_left_dec = lv_btn_create(Tela_DAC);
    lv_obj_set_size(btn_left_dec, h, h);
    lv_obj_align_to(btn_left_dec, spinbox_dac3, LV_ALIGN_OUT_LEFT_MID, -5, 0);
    lv_obj_add_style(btn_left_dec, &style_symbol, LV_PART_MAIN);
    lv_obj_set_style_bg_img_src(btn_left_dec, LV_SYMBOL_MINUS, 0);
    lv_obj_add_event_cb(btn_left_dec, lv_spinbox_dac3_decrement_event_cb, LV_EVENT_ALL, NULL);
}
