/*
 * screen_tuner.c
 *
 *  Created on: 20 de jul. de 2026
 *      Author: rinaldo.santos
 */


#include "main.h"
#include "lvgl.h"
#include <math.h>
#include "../App/UI/screen_tuner.h"
#include "../App/UI/screen_debug.h"
#include "../App/src/log_cdc.h"

void Tuner_Freq(void);
void Tuner_Band(void);

lv_obj_t * Tela_Tuner;
static lv_obj_t * spinbox_freq;
static lv_obj_t * spinbox_band;

int32_t freq_teste = 9810;

void screen_tuner(void)
{
	Tela_Tuner = lv_obj_create(NULL);
	lv_obj_clear_flag(Tela_Tuner, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLLABLE);
	lv_obj_set_style_bg_color(Tela_Tuner, lv_color_hex(0x000000), 0);
	lv_obj_set_style_bg_grad_color(Tela_Tuner, lv_color_hex(0x000000), 0);

	static lv_style_t style_txt;
	lv_style_init(&style_txt);
	lv_style_set_text_font(&style_txt, &lv_font_montserrat_16);
	lv_style_set_text_color(&style_txt, lv_color_hex(0xFFFFFF)); // white text

	lv_obj_t * label1 = lv_label_create(Tela_Tuner);
	lv_label_set_long_mode(label1, LV_LABEL_LONG_WRAP);     /*Break the long lines*/
	lv_label_set_recolor(label1, true);                      /*Enable re-coloring by commands in the text*/
	lv_label_set_text(label1, "TUNER:");
	lv_obj_add_style(label1, &style_txt, LV_PART_MAIN);
	lv_obj_align_to(label1, Tela_Tuner, LV_ALIGN_TOP_MID, 0, 2);

	Tuner_Freq();
	Tuner_Band();

	Button_Menu(Tela_Tuner);

	lv_scr_load(Tela_Tuner);
}

static void lv_spinbox_freq_increment_event_cb(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);
    if(code == LV_EVENT_SHORT_CLICKED || code  == LV_EVENT_LONG_PRESSED_REPEAT) {
        lv_spinbox_increment(spinbox_freq);
        int32_t frequency = lv_spinbox_get_value(spinbox_freq);
        freq_teste  = frequency / 100;
        logI("Freq: [%d] [%d] \n", frequency, freq_teste);
        //EEPROM_Write(ADDR_TUNER_FREQ, (uint8_t*)&cfg.Frequency, sizeof(cfg.Frequency));
    }
}

static void lv_spinbox_freq_decrement_event_cb(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);
    if(code == LV_EVENT_SHORT_CLICKED || code == LV_EVENT_LONG_PRESSED_REPEAT) {
        lv_spinbox_decrement(spinbox_freq);
        int32_t frequency = lv_spinbox_get_value(spinbox_freq);
        freq_teste  = frequency / 100;
        logI("Freq: [%d] [%d] \n", frequency, freq_teste);
        //EEPROM_Write(ADDR_TUNER_FREQ, (uint8_t*)&cfg.Frequency, sizeof(cfg.Frequency));
    }
}

void Tuner_Freq(void)
{
	static lv_style_t style_symbol;
	lv_style_init(&style_symbol);
	lv_style_set_text_font(&style_symbol, &lv_font_montserrat_16);
	lv_style_set_text_color(&style_symbol, lv_color_hex(0xFFFFFF));

    // Tuner Freq
    lv_obj_t * label1 = lv_label_create(Tela_Tuner);
    lv_label_set_long_mode(label1, LV_LABEL_LONG_WRAP);     	/*Break the long lines*/
    lv_label_set_recolor(label1, true);                      	/*Enable re-coloring by commands in the text*/
    lv_label_set_text(label1, "#FFFFFF FM FREQUENCY (MHz):");
    lv_obj_align_to(label1, Tela_Tuner, LV_ALIGN_TOP_LEFT, 2, 24);

    spinbox_freq = lv_spinbox_create(Tela_Tuner);
    lv_spinbox_set_range(spinbox_freq, 6400, 10810);
    lv_spinbox_set_digit_format(spinbox_freq, 5, 3);
    lv_spinbox_set_cursor_pos(spinbox_freq, 0);
    lv_spinbox_set_step(spinbox_freq, 10);
    lv_spinbox_set_value(spinbox_freq, freq_teste);
    lv_obj_set_width(spinbox_freq, 80);
    lv_obj_set_pos(spinbox_freq, 80, 48);

    lv_coord_t h = lv_obj_get_height(spinbox_freq);

    lv_obj_t * btn_left_inc = lv_btn_create(Tela_Tuner);
    lv_obj_set_size(btn_left_inc, h, h);
    lv_obj_align_to(btn_left_inc, spinbox_freq, LV_ALIGN_OUT_RIGHT_MID, 5, 0);
    lv_obj_add_style(btn_left_inc, &style_symbol, LV_PART_MAIN);
    lv_obj_set_style_bg_img_src(btn_left_inc, LV_SYMBOL_PLUS, 0);
    lv_obj_add_event_cb(btn_left_inc, lv_spinbox_freq_increment_event_cb, LV_EVENT_ALL,  NULL);

    lv_obj_t * btn_left_dec = lv_btn_create(Tela_Tuner);
    lv_obj_set_size(btn_left_dec, h, h);
    lv_obj_align_to(btn_left_dec, spinbox_freq, LV_ALIGN_OUT_LEFT_MID, -5, 0);
    lv_obj_add_style(btn_left_dec, &style_symbol, LV_PART_MAIN);
    lv_obj_set_style_bg_img_src(btn_left_dec, LV_SYMBOL_MINUS, 0);
    lv_obj_add_event_cb(btn_left_dec, lv_spinbox_freq_decrement_event_cb, LV_EVENT_ALL, NULL);
}

static void lv_spinbox_band_increment_event_cb(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);
    if(code == LV_EVENT_SHORT_CLICKED || code  == LV_EVENT_LONG_PRESSED_REPEAT) {
        lv_spinbox_increment(spinbox_band);
    }
}

static void lv_spinbox_band_decrement_event_cb(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);
    if(code == LV_EVENT_SHORT_CLICKED || code == LV_EVENT_LONG_PRESSED_REPEAT) {
        lv_spinbox_decrement(spinbox_band);
    }
}

void Tuner_Band(void)
{
	static lv_style_t style_symbol;
	lv_style_init(&style_symbol);
	lv_style_set_text_font(&style_symbol, &lv_font_montserrat_16);
	lv_style_set_text_color(&style_symbol, lv_color_hex(0xFFFFFF));

    // Tuner Band
    lv_obj_t * label1 = lv_label_create(Tela_Tuner);
    lv_label_set_long_mode(label1, LV_LABEL_LONG_WRAP);     	/*Break the long lines*/
    lv_label_set_recolor(label1, true);                      	/*Enable re-coloring by commands in the text*/
    lv_label_set_text(label1, "#FFFFFF FM BAND (KHz):");
    lv_obj_align_to(label1, Tela_Tuner, LV_ALIGN_TOP_LEFT, 2, 108);

    spinbox_band = lv_spinbox_create(Tela_Tuner);
    lv_spinbox_set_range(spinbox_band, 1000, 3000);
    lv_spinbox_set_digit_format(spinbox_band, 5, 3);
    lv_spinbox_set_cursor_pos(spinbox_band, 0);
    lv_spinbox_set_step(spinbox_band, 10);
    lv_spinbox_set_value(spinbox_band, 1000);
    lv_obj_set_width(spinbox_band, 80);
    lv_obj_set_pos(spinbox_band, 80, 132);

    lv_coord_t h = lv_obj_get_height(spinbox_band);

    lv_obj_t * btn_left_inc = lv_btn_create(Tela_Tuner);
    lv_obj_set_size(btn_left_inc, h, h);
    lv_obj_align_to(btn_left_inc, spinbox_band, LV_ALIGN_OUT_RIGHT_MID, 5, 0);
    lv_obj_add_style(btn_left_inc, &style_symbol, LV_PART_MAIN);
    lv_obj_set_style_bg_img_src(btn_left_inc, LV_SYMBOL_PLUS, 0);
    lv_obj_add_event_cb(btn_left_inc, lv_spinbox_band_increment_event_cb, LV_EVENT_ALL,  NULL);

    lv_obj_t * btn_left_dec = lv_btn_create(Tela_Tuner);
    lv_obj_set_size(btn_left_dec, h, h);
    lv_obj_align_to(btn_left_dec, spinbox_band, LV_ALIGN_OUT_LEFT_MID, -5, 0);
    lv_obj_add_style(btn_left_dec, &style_symbol, LV_PART_MAIN);
    lv_obj_set_style_bg_img_src(btn_left_dec, LV_SYMBOL_MINUS, 0);
    lv_obj_add_event_cb(btn_left_dec, lv_spinbox_band_decrement_event_cb, LV_EVENT_ALL, NULL);
}
