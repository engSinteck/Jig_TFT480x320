/*
 * Screen_Config_Signal.c
 *
 *  Created on: 29 de ago. de 2026
 *      Author: rdsan
 */

#include "stdbool.h"
#include "rng.h"
#include "stdio.h"
#include "string.h"

#include "../App/UI/Screen_Config_Signal.h"
#include "../App/UI/Screen_Utils.h"

LV_FONT_DECLARE(Neue_Medium_11);
LV_FONT_DECLARE(Neue_Medium_12);
LV_FONT_DECLARE(Neue_Medium_14);
LV_FONT_DECLARE(Neue_Medium_16);
LV_FONT_DECLARE(Neue_Medium_18);
LV_FONT_DECLARE(Neue_Medium_20);
LV_FONT_DECLARE(Neue_Medium_24);
LV_FONT_DECLARE(Neue_Medium_40);

extern void create_vumeter_50_left(void);
extern void create_vumeter_50_right(void);
extern void create_vumeter_50_mpx(void);
extern void set_vumeter_50_left(int32_t value);
extern void set_vumeter_50_right(int32_t value);
extern void set_vumeter_50_mpx(int32_t value);

void create_config_signal_label(void);
void create_buttons_signal_tone(void);
void create_buttons_signal_mpx(void);
void create_buttons_signal_tone_freq(void);
void create_buttons_signal_mpx_freq(void);
void create_buttons_signal_frequency(void);
void create_buttons_signal_label_frequency(int32_t frequency);
void formatar_frequencia_signal(int32_t valor, char *resultado, size_t tamanho);
void create_label_freq_tone(void);
void create_label_freq_mpx(void);
void create_label_vumeter_lr(void);
void create_label_vumeter_mpx(void);
void create_label_Deviation(void);

extern int32_t fm_frequency;
extern char str_freq[20];

lv_obj_t * Tela_Config_Signal = NULL;
static lv_obj_t * text_config_signal_top = NULL;
static lv_obj_t * text_config_signal_mpx = NULL;
static lv_obj_t * text_config_signal_freq = NULL;
static lv_obj_t * text_config_signal_left = NULL;
static lv_obj_t * text_config_signal_right = NULL;
static lv_obj_t * text_config_signal_mpx1 = NULL;
static lv_obj_t * text_config_signal_frequency = NULL;
static lv_obj_t * img_fundo_signal = NULL;

static lv_obj_t * bt_signal_tone_dec = NULL;
static lv_obj_t * bt_signal_tone_inc = NULL;
static lv_obj_t * bt_signal_tone_up = NULL;
static lv_obj_t * bt_signal_tone_dn = NULL;
static lv_obj_t * bt_signal_tone_prev = NULL;
static lv_obj_t * bt_signal_tone_next = NULL;
static lv_obj_t * bt_signal_tone_play = NULL;
static lv_obj_t * bt_signal_tone_stop = NULL;

static lv_obj_t * bt_signal_mpx_dec = NULL;
static lv_obj_t * bt_signal_mpx_inc = NULL;
static lv_obj_t * bt_signal_mpx_up = NULL;
static lv_obj_t * bt_signal_mpx_dn = NULL;
static lv_obj_t * bt_signal_mpx_prev = NULL;
static lv_obj_t * bt_signal_mpx_next = NULL;
static lv_obj_t * bt_signal_mpx_play = NULL;
static lv_obj_t * bt_signal_mpx_stop = NULL;

static lv_obj_t * bt_signal_tone_freq_dec = NULL;
static lv_obj_t * bt_signal_tone_freq_inc = NULL;
static lv_obj_t * bt_signal_mpx_freq_dec = NULL;
static lv_obj_t * bt_signal_mpx_freq_inc = NULL;

static lv_obj_t * bt_signal_freq_dec = NULL;
static lv_obj_t * bt_signal_freq_inc = NULL;

static lv_obj_t * text_config_signal_level_mpx = NULL;
static lv_obj_t * text_config_signal_level_tone = NULL;

static lv_obj_t * label_signal_freq_tone = NULL;
static lv_obj_t * label_signal_freq_mpx = NULL;

static lv_obj_t * text_signal_vumeter_lr[8];
static lv_obj_t * text_signal_vumeter_mpx[7];
static lv_obj_t * text_signal_deviation;

static int level_signal_mpx = 0;
static int level_signal_tone = 0;
static int freq_signal_tone = 400;
static int freq_signal_mpx = 10000;

void Screen_Config_Signal_Create(void)
{
	Tela_Config_Signal = lv_obj_create(NULL);
	lv_obj_clear_flag(Tela_Config_Signal, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLLABLE);
	lv_obj_set_style_bg_color(Tela_Config_Signal, lv_color_hex(0x000000), 0);
	lv_obj_set_style_bg_grad_color(Tela_Config_Signal, lv_color_hex(0x000000), 0);

	// Imagem de Fundo
	img_fundo_signal = lv_img_create(Tela_Config_Signal);
	lv_img_set_src(img_fundo_signal, "S:/GENERATOR/TELA_GENERATOR.bin");
	lv_obj_set_pos(img_fundo_signal, 0, 0);

	// Label Screen
	create_config_signal_label();

	// Buttons Tone
	create_buttons_signal_tone();

	// Buttons MPX
	create_buttons_signal_mpx();

	// Buttons Tone Freq.
	create_buttons_signal_tone_freq();

	// Buttons MPX  Freq.
	create_buttons_signal_mpx_freq();

	// Buttons Frequency
	create_buttons_signal_frequency();

	// Label Frequency
	create_buttons_signal_label_frequency(fm_frequency);

	// Label Set Frequency
	create_label_freq_tone();
	create_label_freq_mpx();

	// Vu-Meter L+R
	create_vumeter_50_left();  set_vumeter_50_left(45);
	create_vumeter_50_right(); set_vumeter_50_right(45);

	// Vu-Meter MPX
	create_vumeter_50_mpx();   set_vumeter_50_mpx(10);

	// Text Indic Vu-Meter L+R
	create_label_vumeter_lr();

	// Text Indic Vu-Meter MPX
	create_label_vumeter_mpx();

	// Text Deviation Monitor
	create_label_Deviation();

	create_button_back_main(Tela_Config_Signal, 384, 288, PAGE_CONFIG);
}

void create_config_signal_label(void)
{
	text_config_signal_top = lv_label_create(Tela_Config_Signal);
    lv_obj_set_width(text_config_signal_top, LV_SIZE_CONTENT);
    lv_obj_set_height(text_config_signal_top, LV_SIZE_CONTENT);
    lv_label_set_text(text_config_signal_top, "XLR - TONE GENERATOR (15Hz - 15KHz)");
    lv_obj_set_style_text_color(text_config_signal_top, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(text_config_signal_top, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(text_config_signal_top, &Neue_Medium_14, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(text_config_signal_top, 8, 10);

    // Text MPX
	text_config_signal_mpx = lv_label_create(Tela_Config_Signal);
    lv_obj_set_width(text_config_signal_mpx, LV_SIZE_CONTENT);
    lv_obj_set_height(text_config_signal_mpx, LV_SIZE_CONTENT);
    lv_label_set_text(text_config_signal_mpx, "MPX - TONE GENERATOR (15Hz - 53KHz)");
    lv_obj_set_style_text_color(text_config_signal_mpx, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(text_config_signal_mpx, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(text_config_signal_mpx, &Neue_Medium_14, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(text_config_signal_mpx, 8, 100);

    // Frequency
	text_config_signal_freq = lv_label_create(Tela_Config_Signal);
    lv_obj_set_width(text_config_signal_freq, LV_SIZE_CONTENT);
    lv_obj_set_height(text_config_signal_freq, LV_SIZE_CONTENT);
    lv_label_set_text(text_config_signal_freq, "FREQUENCY:");
    lv_obj_set_style_text_color(text_config_signal_freq, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(text_config_signal_freq, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(text_config_signal_freq, &Neue_Medium_12, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(text_config_signal_freq, 391, 199);

    // MPX
	text_config_signal_mpx1 = lv_label_create(Tela_Config_Signal);
    lv_obj_set_width(text_config_signal_mpx1, LV_SIZE_CONTENT);
    lv_obj_set_height(text_config_signal_mpx1, LV_SIZE_CONTENT);
    lv_label_set_text(text_config_signal_mpx1, "M");
    lv_obj_set_style_text_color(text_config_signal_mpx1, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(text_config_signal_mpx1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(text_config_signal_mpx1, &Neue_Medium_20, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(text_config_signal_mpx1, 5, 230);

    // LEFT
	text_config_signal_left = lv_label_create(Tela_Config_Signal);
    lv_obj_set_width(text_config_signal_left, LV_SIZE_CONTENT);
    lv_obj_set_height(text_config_signal_left, LV_SIZE_CONTENT);
    lv_label_set_text(text_config_signal_left, "L");
    lv_obj_set_style_text_color(text_config_signal_left, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(text_config_signal_left, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(text_config_signal_left, &Neue_Medium_20, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(text_config_signal_left, 9, 258);

    // RIGHT
	text_config_signal_right = lv_label_create(Tela_Config_Signal);
    lv_obj_set_width(text_config_signal_right, LV_SIZE_CONTENT);
    lv_obj_set_height(text_config_signal_right, LV_SIZE_CONTENT);
    lv_label_set_text(text_config_signal_right, "R");
    lv_obj_set_style_text_color(text_config_signal_right, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(text_config_signal_right, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(text_config_signal_right, &Neue_Medium_20, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(text_config_signal_right, 7, 293);
}

static void event_tone_dec(lv_event_t * e)
{
	lv_event_code_t code = lv_event_get_code(e);

	if(code == LV_EVENT_CLICKED || code == LV_EVENT_LONG_PRESSED_REPEAT) {

	 }
}

static void event_tone_inc(lv_event_t * e)
{
	lv_event_code_t code = lv_event_get_code(e);

	if(code == LV_EVENT_CLICKED || code == LV_EVENT_LONG_PRESSED_REPEAT) {

	 }
}

static void event_tone_up(lv_event_t * e)
{
	lv_event_code_t code = lv_event_get_code(e);

	if(code == LV_EVENT_CLICKED || code == LV_EVENT_LONG_PRESSED_REPEAT) {

	}
}

static void event_tone_dn(lv_event_t * e)
{
	lv_event_code_t code = lv_event_get_code(e);

	if(code == LV_EVENT_CLICKED || code == LV_EVENT_LONG_PRESSED_REPEAT) {

	 }
}

static void event_tone_prev(lv_event_t * e)
{
	lv_event_code_t code = lv_event_get_code(e);

	if(code == LV_EVENT_CLICKED || code == LV_EVENT_LONG_PRESSED_REPEAT) {

	 }
}

static void event_tone_next(lv_event_t * e)
{
	lv_event_code_t code = lv_event_get_code(e);

	if(code == LV_EVENT_CLICKED || code == LV_EVENT_LONG_PRESSED_REPEAT) {

	 }
}

static void event_tone_play(lv_event_t * e)
{
	lv_event_code_t code = lv_event_get_code(e);

	if(code == LV_EVENT_CLICKED) {

	 }
}

static void event_tone_stop(lv_event_t * e)
{
	lv_event_code_t code = lv_event_get_code(e);

	if(code == LV_EVENT_CLICKED) {

	 }
}

void create_buttons_signal_tone(void)
{
	// Button Decrement
	bt_signal_tone_dec = lv_imagebutton_create(Tela_Config_Signal);
	lv_imagebutton_set_src(bt_signal_tone_dec, LV_IMAGEBUTTON_STATE_RELEASED, NULL, "S:/GENERATOR/BT_REV.bin", NULL);
	lv_imagebutton_set_src(bt_signal_tone_dec, LV_IMAGEBUTTON_STATE_PRESSED, NULL, "S:/GENERATOR/BT_REV_P.bin", NULL);
	lv_imagebutton_set_src(bt_signal_tone_dec, LV_IMAGEBUTTON_STATE_DISABLED, NULL, "S:/GENERATOR/BT_REV.bin", NULL);
	lv_imagebutton_set_src(bt_signal_tone_dec, LV_IMAGEBUTTON_STATE_CHECKED_PRESSED, NULL, "S:/GENERATOR/BT_REV_P.bin", NULL);
	lv_imagebutton_set_src(bt_signal_tone_dec, LV_IMAGEBUTTON_STATE_CHECKED_RELEASED, NULL, "S:/GENERATOR/BT_REV.bin", NULL);
	lv_imagebutton_set_src(bt_signal_tone_dec, LV_IMAGEBUTTON_STATE_CHECKED_DISABLED, NULL, "S:/GENERATOR/BT_REV.bin", NULL);
	lv_obj_add_state(bt_signal_tone_dec, LV_IMAGEBUTTON_STATE_RELEASED);
	lv_obj_add_event_cb(bt_signal_tone_dec, event_tone_dec, LV_EVENT_ALL, NULL);
	lv_obj_set_pos(bt_signal_tone_dec, 284, 8);

	// Button Increment
	bt_signal_tone_inc = lv_imagebutton_create(Tela_Config_Signal);
	lv_imagebutton_set_src(bt_signal_tone_inc, LV_IMAGEBUTTON_STATE_RELEASED, NULL, "S:/GENERATOR/BT_NEXT.bin", NULL);
	lv_imagebutton_set_src(bt_signal_tone_inc, LV_IMAGEBUTTON_STATE_PRESSED, NULL, "S:/GENERATOR/BT_NEXT_P.bin", NULL);
	lv_imagebutton_set_src(bt_signal_tone_inc, LV_IMAGEBUTTON_STATE_DISABLED, NULL, "S:/GENERATOR/BT_NEXT.bin", NULL);
	lv_imagebutton_set_src(bt_signal_tone_inc, LV_IMAGEBUTTON_STATE_CHECKED_PRESSED, NULL, "S:/GENERATOR/BT_NEXT_P.bin", NULL);
	lv_imagebutton_set_src(bt_signal_tone_inc, LV_IMAGEBUTTON_STATE_CHECKED_RELEASED, NULL, "S:/GENERATOR/BT_NEXT.bin", NULL);
	lv_imagebutton_set_src(bt_signal_tone_inc, LV_IMAGEBUTTON_STATE_CHECKED_DISABLED, NULL, "S:/GENERATOR/BT_NEXT.bin", NULL);
	lv_obj_add_state(bt_signal_tone_inc, LV_IMAGEBUTTON_STATE_RELEASED);
	lv_obj_add_event_cb(bt_signal_tone_inc, event_tone_inc, LV_EVENT_ALL, NULL);
	lv_obj_set_pos(bt_signal_tone_inc, 332, 8);

	// Button UP
	bt_signal_tone_up = lv_imagebutton_create(Tela_Config_Signal);
	lv_imagebutton_set_src(bt_signal_tone_up, LV_IMAGEBUTTON_STATE_RELEASED, NULL, "S:/GENERATOR/BT_UP.bin", NULL);
	lv_imagebutton_set_src(bt_signal_tone_up, LV_IMAGEBUTTON_STATE_PRESSED, NULL, "S:/GENERATOR/BT_UP_P.bin", NULL);
	lv_imagebutton_set_src(bt_signal_tone_up, LV_IMAGEBUTTON_STATE_DISABLED, NULL, "S:/GENERATOR/BT_UP.bin", NULL);
	lv_imagebutton_set_src(bt_signal_tone_up, LV_IMAGEBUTTON_STATE_CHECKED_PRESSED, NULL, "S:/GENERATOR/BT_UP_P.bin", NULL);
	lv_imagebutton_set_src(bt_signal_tone_up, LV_IMAGEBUTTON_STATE_CHECKED_RELEASED, NULL, "S:/GENERATOR/BT_UP.bin", NULL);
	lv_imagebutton_set_src(bt_signal_tone_up, LV_IMAGEBUTTON_STATE_CHECKED_DISABLED, NULL, "S:/GENERATOR/BT_UP.bin", NULL);
	lv_obj_add_state(bt_signal_tone_up, LV_IMAGEBUTTON_STATE_RELEASED);
	lv_obj_add_event_cb(bt_signal_tone_up, event_tone_up, LV_EVENT_ALL, NULL);
	lv_obj_set_pos(bt_signal_tone_up, 380, 8);

	// Button DOWN
	bt_signal_tone_dn = lv_imagebutton_create(Tela_Config_Signal);
	lv_imagebutton_set_src(bt_signal_tone_dn, LV_IMAGEBUTTON_STATE_RELEASED, NULL, "S:/GENERATOR/BT_DN.bin", NULL);
	lv_imagebutton_set_src(bt_signal_tone_dn, LV_IMAGEBUTTON_STATE_PRESSED, NULL, "S:/GENERATOR/BT_DN_P.bin", NULL);
	lv_imagebutton_set_src(bt_signal_tone_dn, LV_IMAGEBUTTON_STATE_DISABLED, NULL, "S:/GENERATOR/BT_DN.bin", NULL);
	lv_imagebutton_set_src(bt_signal_tone_dn, LV_IMAGEBUTTON_STATE_CHECKED_PRESSED, NULL, "S:/GENERATOR/BT_DN_P.bin", NULL);
	lv_imagebutton_set_src(bt_signal_tone_dn, LV_IMAGEBUTTON_STATE_CHECKED_RELEASED, NULL, "S:/GENERATOR/BT_DN.bin", NULL);
	lv_imagebutton_set_src(bt_signal_tone_dn, LV_IMAGEBUTTON_STATE_CHECKED_DISABLED, NULL, "S:/GENERATOR/BT_DN.bin", NULL);
	lv_obj_add_state(bt_signal_tone_dn, LV_IMAGEBUTTON_STATE_RELEASED);
	lv_obj_add_event_cb(bt_signal_tone_dn, event_tone_dn, LV_EVENT_ALL, NULL);
	lv_obj_set_pos(bt_signal_tone_dn, 428, 8);

	// Button PREV
	bt_signal_tone_prev = lv_imagebutton_create(Tela_Config_Signal);
	lv_imagebutton_set_src(bt_signal_tone_prev, LV_IMAGEBUTTON_STATE_RELEASED, NULL, "S:/GENERATOR/BT_REF.bin", NULL);
	lv_imagebutton_set_src(bt_signal_tone_prev, LV_IMAGEBUTTON_STATE_PRESSED, NULL, "S:/GENERATOR/BT_REF_P.bin", NULL);
	lv_imagebutton_set_src(bt_signal_tone_prev, LV_IMAGEBUTTON_STATE_DISABLED, NULL, "S:/GENERATOR/BT_REF.bin", NULL);
	lv_imagebutton_set_src(bt_signal_tone_prev, LV_IMAGEBUTTON_STATE_CHECKED_PRESSED, NULL, "S:/GENERATOR/BT_REF_P.bin", NULL);
	lv_imagebutton_set_src(bt_signal_tone_prev, LV_IMAGEBUTTON_STATE_CHECKED_RELEASED, NULL, "S:/GENERATOR/BT_REF.bin", NULL);
	lv_imagebutton_set_src(bt_signal_tone_prev, LV_IMAGEBUTTON_STATE_CHECKED_DISABLED, NULL, "S:/GENERATOR/BT_REF.bin", NULL);
	lv_obj_add_state(bt_signal_tone_prev, LV_IMAGEBUTTON_STATE_RELEASED);
	lv_obj_add_event_cb(bt_signal_tone_prev, event_tone_prev, LV_EVENT_ALL, NULL);
	lv_obj_set_pos(bt_signal_tone_prev, 284, 51);

	// Button NEXT
	bt_signal_tone_next = lv_imagebutton_create(Tela_Config_Signal);
	lv_imagebutton_set_src(bt_signal_tone_next, LV_IMAGEBUTTON_STATE_RELEASED, NULL, "S:/GENERATOR/BT_NEXT.bin", NULL);
	lv_imagebutton_set_src(bt_signal_tone_next, LV_IMAGEBUTTON_STATE_PRESSED, NULL, "S:/GENERATOR/BT_NEXT_P.bin", NULL);
	lv_imagebutton_set_src(bt_signal_tone_next, LV_IMAGEBUTTON_STATE_DISABLED, NULL, "S:/GENERATOR/BT_NEXT.bin", NULL);
	lv_imagebutton_set_src(bt_signal_tone_next, LV_IMAGEBUTTON_STATE_CHECKED_PRESSED, NULL, "S:/GENERATOR/BT_NEXT_P.bin", NULL);
	lv_imagebutton_set_src(bt_signal_tone_next, LV_IMAGEBUTTON_STATE_CHECKED_RELEASED, NULL, "S:/GENERATOR/BT_NEXT.bin", NULL);
	lv_imagebutton_set_src(bt_signal_tone_next, LV_IMAGEBUTTON_STATE_CHECKED_DISABLED, NULL, "S:/GENERATOR/BT_NEXT.bin", NULL);
	lv_obj_add_state(bt_signal_tone_next, LV_IMAGEBUTTON_STATE_RELEASED);
	lv_obj_add_event_cb(bt_signal_tone_next, event_tone_next, LV_EVENT_ALL, NULL);
	lv_obj_set_pos(bt_signal_tone_next, 332, 51);

	// Button PLAY
	bt_signal_tone_play = lv_imagebutton_create(Tela_Config_Signal);
	lv_imagebutton_set_src(bt_signal_tone_play, LV_IMAGEBUTTON_STATE_RELEASED, NULL, "S:/GENERATOR/BT_PLAY.bin", NULL);
	lv_imagebutton_set_src(bt_signal_tone_play, LV_IMAGEBUTTON_STATE_PRESSED, NULL, "S:/GENERATOR/BT_PLAY_P.bin", NULL);
	lv_imagebutton_set_src(bt_signal_tone_play, LV_IMAGEBUTTON_STATE_DISABLED, NULL, "S:/GENERATOR/BT_PLAY.bin", NULL);
	lv_imagebutton_set_src(bt_signal_tone_play, LV_IMAGEBUTTON_STATE_CHECKED_PRESSED, NULL, "S:/GENERATOR/BT_PLAY_P.bin", NULL);
	lv_imagebutton_set_src(bt_signal_tone_play, LV_IMAGEBUTTON_STATE_CHECKED_RELEASED, NULL, "S:/GENERATOR/BT_PLAY.bin", NULL);
	lv_imagebutton_set_src(bt_signal_tone_play, LV_IMAGEBUTTON_STATE_CHECKED_DISABLED, NULL, "S:/GENERATOR/BT_PLAY.bin", NULL);
	lv_obj_add_state(bt_signal_tone_play, LV_IMAGEBUTTON_STATE_RELEASED);
	lv_obj_add_event_cb(bt_signal_tone_play, event_tone_play, LV_EVENT_ALL, NULL);
	lv_obj_set_pos(bt_signal_tone_play, 380, 51);

	// Button STOP
	bt_signal_tone_stop = lv_imagebutton_create(Tela_Config_Signal);
	lv_imagebutton_set_src(bt_signal_tone_stop, LV_IMAGEBUTTON_STATE_RELEASED, NULL, "S:/GENERATOR/BT_STOP.bin", NULL);
	lv_imagebutton_set_src(bt_signal_tone_stop, LV_IMAGEBUTTON_STATE_PRESSED, NULL, "S:/GENERATOR/BT_STOP_P.bin", NULL);
	lv_imagebutton_set_src(bt_signal_tone_stop, LV_IMAGEBUTTON_STATE_DISABLED, NULL, "S:/GENERATOR/BT_STOP.bin", NULL);
	lv_imagebutton_set_src(bt_signal_tone_stop, LV_IMAGEBUTTON_STATE_CHECKED_PRESSED, NULL, "S:/GENERATOR/BT_STOP_P.bin", NULL);
	lv_imagebutton_set_src(bt_signal_tone_stop, LV_IMAGEBUTTON_STATE_CHECKED_RELEASED, NULL, "S:/GENERATOR/BT_STOP.bin", NULL);
	lv_imagebutton_set_src(bt_signal_tone_stop, LV_IMAGEBUTTON_STATE_CHECKED_DISABLED, NULL, "S:/GENERATOR/BT_STOP.bin", NULL);
	lv_obj_add_state(bt_signal_tone_stop, LV_IMAGEBUTTON_STATE_RELEASED);
	lv_obj_add_event_cb(bt_signal_tone_stop, event_tone_stop, LV_EVENT_ALL, NULL);
	lv_obj_set_pos(bt_signal_tone_stop, 428, 51);
}

static void event_mpx_dec(lv_event_t * e)
{
	lv_event_code_t code = lv_event_get_code(e);

	if(code == LV_EVENT_CLICKED || code == LV_EVENT_LONG_PRESSED_REPEAT) {

	}
}

static void event_mpx_inc(lv_event_t * e)
{
	lv_event_code_t code = lv_event_get_code(e);

	if(code == LV_EVENT_CLICKED || code == LV_EVENT_LONG_PRESSED_REPEAT) {

	}
}

static void event_mpx_up(lv_event_t * e)
{
	lv_event_code_t code = lv_event_get_code(e);

	if(code == LV_EVENT_CLICKED || code == LV_EVENT_LONG_PRESSED_REPEAT) {

	}
}

static void event_mpx_dn(lv_event_t * e)
{
	lv_event_code_t code = lv_event_get_code(e);

	if(code == LV_EVENT_CLICKED || code == LV_EVENT_LONG_PRESSED_REPEAT) {

	 }
}

static void event_mpx_prev(lv_event_t * e)
{
	lv_event_code_t code = lv_event_get_code(e);

	if(code == LV_EVENT_CLICKED || code == LV_EVENT_LONG_PRESSED_REPEAT) {

	}
}

static void event_mpx_next(lv_event_t * e)
{
	lv_event_code_t code = lv_event_get_code(e);

	if(code == LV_EVENT_CLICKED || code == LV_EVENT_LONG_PRESSED_REPEAT) {

	}
}

static void event_mpx_play(lv_event_t * e)
{
	lv_event_code_t code = lv_event_get_code(e);

	if(code == LV_EVENT_CLICKED) {

	 }
}

static void event_mpx_stop(lv_event_t * e)
{
	lv_event_code_t code = lv_event_get_code(e);

	if(code == LV_EVENT_CLICKED) {

	 }
}

void create_buttons_signal_mpx(void)
{
	// Button Decrement
	bt_signal_mpx_dec = lv_imagebutton_create(Tela_Config_Signal);
	lv_imagebutton_set_src(bt_signal_mpx_dec, LV_IMAGEBUTTON_STATE_RELEASED, NULL, "S:/GENERATOR/BT_REV.bin", NULL);
	lv_imagebutton_set_src(bt_signal_mpx_dec, LV_IMAGEBUTTON_STATE_PRESSED, NULL, "S:/GENERATOR/BT_REV_P.bin", NULL);
	lv_imagebutton_set_src(bt_signal_mpx_dec, LV_IMAGEBUTTON_STATE_DISABLED, NULL, "S:/GENERATOR/BT_REV.bin", NULL);
	lv_imagebutton_set_src(bt_signal_mpx_dec, LV_IMAGEBUTTON_STATE_CHECKED_PRESSED, NULL, "S:/GENERATOR/BT_REV_P.bin", NULL);
	lv_imagebutton_set_src(bt_signal_mpx_dec, LV_IMAGEBUTTON_STATE_CHECKED_RELEASED, NULL, "S:/GENERATOR/BT_REV.bin", NULL);
	lv_imagebutton_set_src(bt_signal_mpx_dec, LV_IMAGEBUTTON_STATE_CHECKED_DISABLED, NULL, "S:/GENERATOR/BT_REV.bin", NULL);
	lv_obj_add_state(bt_signal_mpx_dec, LV_IMAGEBUTTON_STATE_RELEASED);
	lv_obj_add_event_cb(bt_signal_mpx_dec, event_mpx_dec, LV_EVENT_ALL, NULL);
	lv_obj_set_pos(bt_signal_mpx_dec, 284, 100);

	// Button Increment
	bt_signal_mpx_inc = lv_imagebutton_create(Tela_Config_Signal);
	lv_imagebutton_set_src(bt_signal_mpx_inc, LV_IMAGEBUTTON_STATE_RELEASED, NULL, "S:/GENERATOR/BT_NEXT.bin", NULL);
	lv_imagebutton_set_src(bt_signal_mpx_inc, LV_IMAGEBUTTON_STATE_PRESSED, NULL, "S:/GENERATOR/BT_NEXT_P.bin", NULL);
	lv_imagebutton_set_src(bt_signal_mpx_inc, LV_IMAGEBUTTON_STATE_DISABLED, NULL, "S:/GENERATOR/BT_NEXT.bin", NULL);
	lv_imagebutton_set_src(bt_signal_mpx_inc, LV_IMAGEBUTTON_STATE_CHECKED_PRESSED, NULL, "S:/GENERATOR/BT_NEXT_P.bin", NULL);
	lv_imagebutton_set_src(bt_signal_mpx_inc, LV_IMAGEBUTTON_STATE_CHECKED_RELEASED, NULL, "S:/GENERATOR/BT_NEXT.bin", NULL);
	lv_imagebutton_set_src(bt_signal_mpx_inc, LV_IMAGEBUTTON_STATE_CHECKED_DISABLED, NULL, "S:/GENERATOR/BT_NEXT.bin", NULL);
	lv_obj_add_state(bt_signal_mpx_inc, LV_IMAGEBUTTON_STATE_RELEASED);
	lv_obj_add_event_cb(bt_signal_mpx_inc, event_mpx_inc, LV_EVENT_ALL, NULL);
	lv_obj_set_pos(bt_signal_mpx_inc, 332, 100);

	// Button UP
	bt_signal_mpx_up = lv_imagebutton_create(Tela_Config_Signal);
	lv_imagebutton_set_src(bt_signal_mpx_up, LV_IMAGEBUTTON_STATE_RELEASED, NULL, "S:/GENERATOR/BT_UP.bin", NULL);
	lv_imagebutton_set_src(bt_signal_mpx_up, LV_IMAGEBUTTON_STATE_PRESSED, NULL, "S:/GENERATOR/BT_UP.bin", NULL);
	lv_imagebutton_set_src(bt_signal_mpx_up, LV_IMAGEBUTTON_STATE_DISABLED, NULL, "S:/GENERATOR/BT_UP.bin", NULL);
	lv_imagebutton_set_src(bt_signal_mpx_up, LV_IMAGEBUTTON_STATE_CHECKED_PRESSED, NULL, "S:/GENERATOR/BT_UP.bin", NULL);
	lv_imagebutton_set_src(bt_signal_mpx_up, LV_IMAGEBUTTON_STATE_CHECKED_RELEASED, NULL, "S:/GENERATOR/BT_UP.bin", NULL);
	lv_imagebutton_set_src(bt_signal_mpx_up, LV_IMAGEBUTTON_STATE_CHECKED_DISABLED, NULL, "S:/GENERATOR/BT_UP.bin", NULL);
	lv_obj_add_state(bt_signal_mpx_up, LV_IMAGEBUTTON_STATE_RELEASED);
	lv_obj_add_event_cb(bt_signal_mpx_up, event_mpx_up, LV_EVENT_ALL, NULL);
	lv_obj_set_pos(bt_signal_mpx_up, 380, 100);

	// Button DOWN
	bt_signal_mpx_dn = lv_imagebutton_create(Tela_Config_Signal);
	lv_imagebutton_set_src(bt_signal_mpx_dn, LV_IMAGEBUTTON_STATE_RELEASED, NULL, "S:/GENERATOR/BT_DN.bin", NULL);
	lv_imagebutton_set_src(bt_signal_mpx_dn, LV_IMAGEBUTTON_STATE_PRESSED, NULL, "S:/GENERATOR/BT_DN.bin", NULL);
	lv_imagebutton_set_src(bt_signal_mpx_dn, LV_IMAGEBUTTON_STATE_DISABLED, NULL, "S:/GENERATOR/BT_DN.bin", NULL);
	lv_imagebutton_set_src(bt_signal_mpx_dn, LV_IMAGEBUTTON_STATE_CHECKED_PRESSED, NULL, "S:/GENERATOR/BT_DN.bin", NULL);
	lv_imagebutton_set_src(bt_signal_mpx_dn, LV_IMAGEBUTTON_STATE_CHECKED_RELEASED, NULL, "S:/GENERATOR/BT_DN.bin", NULL);
	lv_imagebutton_set_src(bt_signal_mpx_dn, LV_IMAGEBUTTON_STATE_CHECKED_DISABLED, NULL, "S:/GENERATOR/BT_DN.bin", NULL);
	lv_obj_add_state(bt_signal_mpx_dn, LV_IMAGEBUTTON_STATE_RELEASED);
	lv_obj_add_event_cb(bt_signal_mpx_dn, event_mpx_dn, LV_EVENT_ALL, NULL);
	lv_obj_set_pos(bt_signal_mpx_dn, 428, 100);

	// Button PREV
	bt_signal_mpx_prev = lv_imagebutton_create(Tela_Config_Signal);
	lv_imagebutton_set_src(bt_signal_mpx_prev, LV_IMAGEBUTTON_STATE_RELEASED, NULL, "S:/GENERATOR/BT_REF.bin", NULL);
	lv_imagebutton_set_src(bt_signal_mpx_prev, LV_IMAGEBUTTON_STATE_PRESSED, NULL, "S:/GENERATOR/BT_REF_P.bin", NULL);
	lv_imagebutton_set_src(bt_signal_mpx_prev, LV_IMAGEBUTTON_STATE_DISABLED, NULL, "S:/GENERATOR/BT_REF.bin", NULL);
	lv_imagebutton_set_src(bt_signal_mpx_prev, LV_IMAGEBUTTON_STATE_CHECKED_PRESSED, NULL, "S:/GENERATOR/BT_REF_P.bin", NULL);
	lv_imagebutton_set_src(bt_signal_mpx_prev, LV_IMAGEBUTTON_STATE_CHECKED_RELEASED, NULL, "S:/GENERATOR/BT_REF.bin", NULL);
	lv_imagebutton_set_src(bt_signal_mpx_prev, LV_IMAGEBUTTON_STATE_CHECKED_DISABLED, NULL, "S:/GENERATOR/BT_REF.bin", NULL);
	lv_obj_add_state(bt_signal_mpx_prev, LV_IMAGEBUTTON_STATE_RELEASED);
	lv_obj_add_event_cb(bt_signal_mpx_prev, event_mpx_prev, LV_EVENT_ALL, NULL);
	lv_obj_set_pos(bt_signal_mpx_prev, 284, 143);

	// Button NEXT
	bt_signal_mpx_next = lv_imagebutton_create(Tela_Config_Signal);
	lv_imagebutton_set_src(bt_signal_mpx_next, LV_IMAGEBUTTON_STATE_RELEASED, NULL, "S:/GENERATOR/BT_NEXT.bin", NULL);
	lv_imagebutton_set_src(bt_signal_mpx_next, LV_IMAGEBUTTON_STATE_PRESSED, NULL, "S:/GENERATOR/BT_NEXT_P.bin", NULL);
	lv_imagebutton_set_src(bt_signal_mpx_next, LV_IMAGEBUTTON_STATE_DISABLED, NULL, "S:/GENERATOR/BT_NEXT.bin", NULL);
	lv_imagebutton_set_src(bt_signal_mpx_next, LV_IMAGEBUTTON_STATE_CHECKED_PRESSED, NULL, "S:/GENERATOR/BT_NEXT_P.bin", NULL);
	lv_imagebutton_set_src(bt_signal_mpx_next, LV_IMAGEBUTTON_STATE_CHECKED_RELEASED, NULL, "S:/GENERATOR/BT_NEXT.bin", NULL);
	lv_imagebutton_set_src(bt_signal_mpx_next, LV_IMAGEBUTTON_STATE_CHECKED_DISABLED, NULL, "S:/GENERATOR/BT_NEXT.bin", NULL);
	lv_obj_add_state(bt_signal_mpx_next, LV_IMAGEBUTTON_STATE_RELEASED);
	lv_obj_add_event_cb(bt_signal_mpx_next, event_mpx_next, LV_EVENT_ALL, NULL);
	lv_obj_set_pos(bt_signal_mpx_next, 332, 143);

	// Button PLAY
	bt_signal_mpx_play = lv_imagebutton_create(Tela_Config_Signal);
	lv_imagebutton_set_src(bt_signal_mpx_play, LV_IMAGEBUTTON_STATE_RELEASED, NULL, "S:/GENERATOR/BT_PLAY.bin", NULL);
	lv_imagebutton_set_src(bt_signal_mpx_play, LV_IMAGEBUTTON_STATE_PRESSED, NULL, "S:/GENERATOR/BT_PLAY_P.bin", NULL);
	lv_imagebutton_set_src(bt_signal_mpx_play, LV_IMAGEBUTTON_STATE_DISABLED, NULL, "S:/GENERATOR/BT_PLAY.bin", NULL);
	lv_imagebutton_set_src(bt_signal_mpx_play, LV_IMAGEBUTTON_STATE_CHECKED_PRESSED, NULL, "S:/GENERATOR/BT_PLAY_P.bin", NULL);
	lv_imagebutton_set_src(bt_signal_mpx_play, LV_IMAGEBUTTON_STATE_CHECKED_RELEASED, NULL, "S:/GENERATOR/BT_PLAY.bin", NULL);
	lv_imagebutton_set_src(bt_signal_mpx_play, LV_IMAGEBUTTON_STATE_CHECKED_DISABLED, NULL, "S:/GENERATOR/BT_PLAY.bin", NULL);
	lv_obj_add_state(bt_signal_mpx_play, LV_IMAGEBUTTON_STATE_RELEASED);
	lv_obj_add_event_cb(bt_signal_mpx_play, event_mpx_play, LV_EVENT_ALL, NULL);
	lv_obj_set_pos(bt_signal_mpx_play, 380, 143);

	// Button STOP
	bt_signal_mpx_stop = lv_imagebutton_create(Tela_Config_Signal);
	lv_imagebutton_set_src(bt_signal_mpx_stop, LV_IMAGEBUTTON_STATE_RELEASED, NULL, "S:/GENERATOR/BT_STOP.bin", NULL);
	lv_imagebutton_set_src(bt_signal_mpx_stop, LV_IMAGEBUTTON_STATE_PRESSED, NULL, "S:/GENERATOR/BT_STOP_P.bin", NULL);
	lv_imagebutton_set_src(bt_signal_mpx_stop, LV_IMAGEBUTTON_STATE_DISABLED, NULL, "S:/GENERATOR/BT_STOP.bin", NULL);
	lv_imagebutton_set_src(bt_signal_mpx_stop, LV_IMAGEBUTTON_STATE_CHECKED_PRESSED, NULL, "S:/GENERATOR/BT_STOP_P.bin", NULL);
	lv_imagebutton_set_src(bt_signal_mpx_stop, LV_IMAGEBUTTON_STATE_CHECKED_RELEASED, NULL, "S:/GENERATOR/BT_STOP.bin", NULL);
	lv_imagebutton_set_src(bt_signal_mpx_stop, LV_IMAGEBUTTON_STATE_CHECKED_DISABLED, NULL, "S:/GENERATOR/BT_STOP.bin", NULL);
	lv_obj_add_state(bt_signal_mpx_stop, LV_IMAGEBUTTON_STATE_RELEASED);
	lv_obj_add_event_cb(bt_signal_mpx_stop, event_mpx_stop, LV_EVENT_ALL, NULL);
	lv_obj_set_pos(bt_signal_mpx_stop, 428, 143);
}

static void event_tone_freq_dec(lv_event_t * e)
{
	lv_event_code_t code = lv_event_get_code(e);

	if(code == LV_EVENT_CLICKED || code == LV_EVENT_LONG_PRESSED_REPEAT) {
		if(level_signal_tone >= 1) level_signal_tone--;

		lv_label_set_text_fmt(text_config_signal_level_tone, "Level:%d%%", level_signal_tone);
	}
}

static void event_tone_freq_inc(lv_event_t * e)
{
	lv_event_code_t code = lv_event_get_code(e);

	if(code == LV_EVENT_CLICKED || code == LV_EVENT_LONG_PRESSED_REPEAT) {
		level_signal_tone++;
		if(level_signal_tone >= 100) level_signal_tone = 100;

		lv_label_set_text_fmt(text_config_signal_level_tone, "Level:%d%%", level_signal_tone);
	}
}

void create_buttons_signal_tone_freq(void)
{
	// Button Decrement Level Tone
	bt_signal_tone_freq_dec = lv_imagebutton_create(Tela_Config_Signal);
	lv_imagebutton_set_src(bt_signal_tone_freq_dec, LV_IMAGEBUTTON_STATE_RELEASED, NULL, "S:/GENERATOR/BT_DN_2.bin", NULL);
	lv_imagebutton_set_src(bt_signal_tone_freq_dec, LV_IMAGEBUTTON_STATE_PRESSED, NULL, "S:/GENERATOR/BT_DN_2_P.bin", NULL);
	lv_imagebutton_set_src(bt_signal_tone_freq_dec, LV_IMAGEBUTTON_STATE_DISABLED, NULL, "S:/GENERATOR/BT_DN_2.bin", NULL);
	lv_imagebutton_set_src(bt_signal_tone_freq_dec, LV_IMAGEBUTTON_STATE_CHECKED_PRESSED, NULL, "S:/GENERATOR/BT_DN_2_P.bin", NULL);
	lv_imagebutton_set_src(bt_signal_tone_freq_dec, LV_IMAGEBUTTON_STATE_CHECKED_RELEASED, NULL, "S:/GENERATOR/BT_DN_2.bin", NULL);
	lv_imagebutton_set_src(bt_signal_tone_freq_dec, LV_IMAGEBUTTON_STATE_CHECKED_DISABLED, NULL, "S:/GENERATOR/BT_DN_2.bin", NULL);
	lv_obj_add_state(bt_signal_tone_freq_dec, LV_IMAGEBUTTON_STATE_RELEASED);
	lv_obj_add_event_cb(bt_signal_tone_freq_dec, event_tone_freq_dec, LV_EVENT_ALL, NULL);
	lv_obj_set_pos(bt_signal_tone_freq_dec, 8, 60);

	// Button Increment Level Tone
	bt_signal_tone_freq_inc = lv_imagebutton_create(Tela_Config_Signal);
	lv_imagebutton_set_src(bt_signal_tone_freq_inc, LV_IMAGEBUTTON_STATE_RELEASED, NULL, "S:/GENERATOR/BT_UP_2.bin", NULL);
	lv_imagebutton_set_src(bt_signal_tone_freq_inc, LV_IMAGEBUTTON_STATE_PRESSED, NULL, "S:/GENERATOR/BT_UP_2_P.bin", NULL);
	lv_imagebutton_set_src(bt_signal_tone_freq_inc, LV_IMAGEBUTTON_STATE_DISABLED, NULL, "S:/GENERATOR/BT_UP_2.bin", NULL);
	lv_imagebutton_set_src(bt_signal_tone_freq_inc, LV_IMAGEBUTTON_STATE_CHECKED_PRESSED, NULL, "S:/GENERATOR/BT_UP_2_P.bin", NULL);
	lv_imagebutton_set_src(bt_signal_tone_freq_inc, LV_IMAGEBUTTON_STATE_CHECKED_RELEASED, NULL, "S:/GENERATOR/BT_UP_2.bin", NULL);
	lv_imagebutton_set_src(bt_signal_tone_freq_inc, LV_IMAGEBUTTON_STATE_CHECKED_DISABLED, NULL, "S:/GENERATOR/BT_UP_2.bin", NULL);
	lv_obj_add_state(bt_signal_tone_freq_inc, LV_IMAGEBUTTON_STATE_RELEASED);
	lv_obj_add_event_cb(bt_signal_tone_freq_inc, event_tone_freq_inc, LV_EVENT_ALL, NULL);
	lv_obj_set_pos(bt_signal_tone_freq_inc, 52, 60);

	// Label Level
	text_config_signal_level_tone = lv_label_create(Tela_Config_Signal);
	lv_obj_set_width(text_config_signal_level_tone, 88);
	lv_obj_set_height(text_config_signal_level_tone, LV_SIZE_CONTENT);
	lv_obj_set_style_text_align(text_config_signal_level_tone, LV_TEXT_ALIGN_CENTER, 0);
	lv_obj_set_style_text_color(text_config_signal_level_tone, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_opa(text_config_signal_level_tone, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(text_config_signal_level_tone, &Neue_Medium_16, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_pos(text_config_signal_level_tone, 8, 37);

	lv_label_set_text_fmt(text_config_signal_level_tone, "Level:%d%%", level_signal_mpx);
}

static void event_mpx_freq_dec(lv_event_t * e)
{
	lv_event_code_t code = lv_event_get_code(e);

	if(code == LV_EVENT_CLICKED || code == LV_EVENT_LONG_PRESSED_REPEAT) {
		if(level_signal_mpx >= 1) level_signal_mpx--;

		lv_label_set_text_fmt(text_config_signal_level_mpx, "Level:%d%%", level_signal_mpx);
	}
}

static void event_mpx_freq_inc(lv_event_t * e)
{
	lv_event_code_t code = lv_event_get_code(e);

	if(code == LV_EVENT_CLICKED || code == LV_EVENT_LONG_PRESSED_REPEAT) {
		level_signal_mpx++;
		if(level_signal_mpx >= 100) level_signal_mpx = 100;

		lv_label_set_text_fmt(text_config_signal_level_mpx, "Level:%d%%", level_signal_mpx);
	}
}

void create_buttons_signal_mpx_freq(void)
{
	// Button Decrement Level MPX
	bt_signal_mpx_freq_dec = lv_imagebutton_create(Tela_Config_Signal);
	lv_imagebutton_set_src(bt_signal_mpx_freq_dec, LV_IMAGEBUTTON_STATE_RELEASED, NULL, "S:/GENERATOR/BT_DN_2.bin", NULL);
	lv_imagebutton_set_src(bt_signal_mpx_freq_dec, LV_IMAGEBUTTON_STATE_PRESSED, NULL, "S:/GENERATOR/BT_DN_2_P.bin", NULL);
	lv_imagebutton_set_src(bt_signal_mpx_freq_dec, LV_IMAGEBUTTON_STATE_DISABLED, NULL, "S:/GENERATOR/BT_DN_2.bin", NULL);
	lv_imagebutton_set_src(bt_signal_mpx_freq_dec, LV_IMAGEBUTTON_STATE_CHECKED_PRESSED, NULL, "S:/GENERATOR/BT_DN_2_P.bin", NULL);
	lv_imagebutton_set_src(bt_signal_mpx_freq_dec, LV_IMAGEBUTTON_STATE_CHECKED_RELEASED, NULL, "S:/GENERATOR/BT_DN_2.bin", NULL);
	lv_imagebutton_set_src(bt_signal_mpx_freq_dec, LV_IMAGEBUTTON_STATE_CHECKED_DISABLED, NULL, "S:/GENERATOR/BT_DN_2.bin", NULL);
	lv_obj_add_state(bt_signal_mpx_freq_dec, LV_IMAGEBUTTON_STATE_RELEASED);
	lv_obj_add_event_cb(bt_signal_mpx_freq_dec, event_mpx_freq_dec, LV_EVENT_ALL, NULL);
	lv_obj_set_pos(bt_signal_mpx_freq_dec, 8, 152);

	// Button Increment Level MPX
	bt_signal_mpx_freq_inc = lv_imagebutton_create(Tela_Config_Signal);
	lv_imagebutton_set_src(bt_signal_mpx_freq_inc, LV_IMAGEBUTTON_STATE_RELEASED, NULL, "S:/GENERATOR/BT_UP_2.bin", NULL);
	lv_imagebutton_set_src(bt_signal_mpx_freq_inc, LV_IMAGEBUTTON_STATE_PRESSED, NULL, "S:/GENERATOR/BT_UP_2_P.bin", NULL);
	lv_imagebutton_set_src(bt_signal_mpx_freq_inc, LV_IMAGEBUTTON_STATE_DISABLED, NULL, "S:/GENERATOR/BT_UP_2.bin", NULL);
	lv_imagebutton_set_src(bt_signal_mpx_freq_inc, LV_IMAGEBUTTON_STATE_CHECKED_PRESSED, NULL, "S:/GENERATOR/BT_UP_2_P.bin", NULL);
	lv_imagebutton_set_src(bt_signal_mpx_freq_inc, LV_IMAGEBUTTON_STATE_CHECKED_RELEASED, NULL, "S:/GENERATOR/BT_UP_2.bin", NULL);
	lv_imagebutton_set_src(bt_signal_mpx_freq_inc, LV_IMAGEBUTTON_STATE_CHECKED_DISABLED, NULL, "S:/GENERATOR/BT_UP_2.bin", NULL);
	lv_obj_add_state(bt_signal_mpx_freq_inc, LV_IMAGEBUTTON_STATE_RELEASED);
	lv_obj_add_event_cb(bt_signal_mpx_freq_inc, event_mpx_freq_inc, LV_EVENT_ALL, NULL);
	lv_obj_set_pos(bt_signal_mpx_freq_inc, 52, 152);

	// Label Level
	text_config_signal_level_mpx = lv_label_create(Tela_Config_Signal);
	lv_obj_set_width(text_config_signal_level_mpx, 88);
	lv_obj_set_height(text_config_signal_level_mpx, LV_SIZE_CONTENT);
	lv_obj_set_style_text_align(text_config_signal_level_mpx, LV_TEXT_ALIGN_CENTER, 0);
	lv_obj_set_style_text_color(text_config_signal_level_mpx, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_opa(text_config_signal_level_mpx, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(text_config_signal_level_mpx, &Neue_Medium_16, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_pos(text_config_signal_level_mpx, 8, 130);

	lv_label_set_text_fmt(text_config_signal_level_mpx, "Level:%d%%", level_signal_mpx);
}

static void event_freq_dec(lv_event_t * e)
{
	lv_event_code_t code = lv_event_get_code(e);

	if(code == LV_EVENT_CLICKED || code == LV_EVENT_LONG_PRESSED_REPEAT) {
		 if(fm_frequency > 76000) {
			 fm_frequency -= 100; // Decrementa de 100
			 formatar_frequencia_signal(fm_frequency, str_freq, sizeof(str_freq));
			 lv_label_set_text_fmt(text_config_signal_frequency, str_freq);
		 }
	}
}

static void event_freq_inc(lv_event_t * e)
{
	lv_event_code_t code = lv_event_get_code(e);

	if(code == LV_EVENT_CLICKED || code == LV_EVENT_LONG_PRESSED_REPEAT) {
		 if(fm_frequency < 108100) {
			 fm_frequency += 100; // Incrementa de 100
			 formatar_frequencia_signal(fm_frequency, str_freq, sizeof(str_freq));
			 lv_label_set_text_fmt(text_config_signal_frequency, str_freq);;
		 }
	}
}

void create_buttons_signal_frequency(void)
{
	// Button Decrement Frequency
	bt_signal_freq_dec = lv_imagebutton_create(Tela_Config_Signal);
	lv_imagebutton_set_src(bt_signal_freq_dec, LV_IMAGEBUTTON_STATE_RELEASED, NULL, "S:/GENERATOR/BT_DN_2.bin", NULL);
	lv_imagebutton_set_src(bt_signal_freq_dec, LV_IMAGEBUTTON_STATE_PRESSED, NULL, "S:/GENERATOR/BT_DN_2_P.bin", NULL);
	lv_imagebutton_set_src(bt_signal_freq_dec, LV_IMAGEBUTTON_STATE_DISABLED, NULL, "S:/GENERATOR/BT_DN_2.bin", NULL);
	lv_imagebutton_set_src(bt_signal_freq_dec, LV_IMAGEBUTTON_STATE_CHECKED_PRESSED, NULL, "S:/GENERATOR/BT_DN_2_P.bin", NULL);
	lv_imagebutton_set_src(bt_signal_freq_dec, LV_IMAGEBUTTON_STATE_CHECKED_RELEASED, NULL, "S:/GENERATOR/BT_DN_2.bin", NULL);
	lv_imagebutton_set_src(bt_signal_freq_dec, LV_IMAGEBUTTON_STATE_CHECKED_DISABLED, NULL, "S:/GENERATOR/BT_DN_2.bin", NULL);
	lv_obj_add_state(bt_signal_freq_dec, LV_IMAGEBUTTON_STATE_RELEASED);
	lv_obj_add_event_cb(bt_signal_freq_dec, event_freq_dec, LV_EVENT_ALL, NULL);
	lv_obj_set_pos(bt_signal_freq_dec, 387, 255);

	// Button Increment Frequency
	bt_signal_freq_inc = lv_imagebutton_create(Tela_Config_Signal);
	lv_imagebutton_set_src(bt_signal_freq_inc, LV_IMAGEBUTTON_STATE_RELEASED, NULL, "S:/GENERATOR/BT_UP_2.bin", NULL);
	lv_imagebutton_set_src(bt_signal_freq_inc, LV_IMAGEBUTTON_STATE_PRESSED, NULL, "S:/GENERATOR/BT_UP_2_P.bin", NULL);
	lv_imagebutton_set_src(bt_signal_freq_inc, LV_IMAGEBUTTON_STATE_DISABLED, NULL, "S:/GENERATOR/BT_UP_2.bin", NULL);
	lv_imagebutton_set_src(bt_signal_freq_inc, LV_IMAGEBUTTON_STATE_CHECKED_PRESSED, NULL, "S:/GENERATOR/BT_UP_2_P.bin", NULL);
	lv_imagebutton_set_src(bt_signal_freq_inc, LV_IMAGEBUTTON_STATE_CHECKED_RELEASED, NULL, "S:/GENERATOR/BT_UP_2.bin", NULL);
	lv_imagebutton_set_src(bt_signal_freq_inc, LV_IMAGEBUTTON_STATE_CHECKED_DISABLED, NULL, "S:/GENERATOR/BT_UP_2.bin", NULL);
	lv_obj_add_state(bt_signal_freq_inc, LV_IMAGEBUTTON_STATE_RELEASED);
	lv_obj_add_event_cb(bt_signal_freq_inc, event_freq_inc, LV_EVENT_ALL, NULL);
	lv_obj_set_pos(bt_signal_freq_inc, 432, 255);
}

void create_buttons_signal_label_frequency(int32_t frequency)
{
    // FREQUENCY
	text_config_signal_frequency = lv_label_create(Tela_Config_Signal);
    lv_obj_set_width(text_config_signal_frequency, 88);
    lv_obj_set_height(text_config_signal_frequency, LV_SIZE_CONTENT);
    lv_obj_set_style_text_align(text_config_signal_frequency, LV_TEXT_ALIGN_CENTER, 0);
    lv_obj_set_style_text_color(text_config_signal_frequency, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(text_config_signal_frequency, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(text_config_signal_frequency, &Neue_Medium_24, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(text_config_signal_frequency, 388, 224);

    formatar_frequencia_signal(frequency, str_freq, sizeof(str_freq));
    lv_label_set_text_fmt(text_config_signal_frequency, str_freq);
}

void formatar_frequencia_signal(int32_t valor, char *resultado, size_t tamanho)
{
    int milhares = valor / 1000;
    int unidades = valor % 1000;

    snprintf(resultado, tamanho, "%d.%03d", milhares, unidades);
}

void create_label_freq_tone(void)
{
	// Label Set Frequency Tone
	label_signal_freq_tone = lv_label_create(Tela_Config_Signal);
	lv_obj_set_width(label_signal_freq_tone, 180);
	lv_obj_set_height(label_signal_freq_tone, LV_SIZE_CONTENT);
	lv_obj_set_style_text_align(label_signal_freq_tone, LV_TEXT_ALIGN_CENTER, 0);
	lv_obj_set_style_text_color(label_signal_freq_tone, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_opa(label_signal_freq_tone, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(label_signal_freq_tone, &Neue_Medium_40, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_pos(label_signal_freq_tone, 100, 52);

	lv_label_set_text_fmt(label_signal_freq_tone, "%d Hz", freq_signal_tone);
}

void create_label_freq_mpx(void)
{
	// Label Set Frequency MPX
	label_signal_freq_mpx = lv_label_create(Tela_Config_Signal);
	lv_obj_set_width(label_signal_freq_mpx, 180);
	lv_obj_set_height(label_signal_freq_mpx, LV_SIZE_CONTENT);
	lv_obj_set_style_text_align(label_signal_freq_mpx, LV_TEXT_ALIGN_CENTER, 0);
	lv_obj_set_style_text_color(label_signal_freq_mpx, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_opa(label_signal_freq_mpx, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(label_signal_freq_mpx, &Neue_Medium_40, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_pos(label_signal_freq_mpx, 100, 144);

	lv_label_set_text_fmt(label_signal_freq_mpx, "%d Hz", freq_signal_mpx);
}

void create_label_vumeter_lr(void)
{
	// Label L+R
	for(uint8_t x = 0; x < 8; x++) {
		text_signal_vumeter_lr[x] = lv_label_create(Tela_Config_Signal);
		lv_obj_set_width(text_signal_vumeter_lr[x], LV_SIZE_CONTENT);
		lv_obj_set_height(text_signal_vumeter_lr[x], LV_SIZE_CONTENT);
		lv_obj_set_style_text_align(text_signal_vumeter_lr[x], LV_TEXT_ALIGN_CENTER, 0);
		lv_obj_set_style_text_color(text_signal_vumeter_lr[x], lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
		lv_obj_set_style_text_opa(text_signal_vumeter_lr[x], 255, LV_PART_MAIN | LV_STATE_DEFAULT);
		lv_obj_set_style_text_font(text_signal_vumeter_lr[x], &Neue_Medium_11, LV_PART_MAIN | LV_STATE_DEFAULT);
	}

	// Text
	lv_label_set_text(text_signal_vumeter_lr[0], "-60");
	lv_label_set_text(text_signal_vumeter_lr[1], "-50");
	lv_label_set_text(text_signal_vumeter_lr[2], "-40");
	lv_label_set_text(text_signal_vumeter_lr[3], "-30");
	lv_label_set_text(text_signal_vumeter_lr[4], "-20");
	lv_label_set_text(text_signal_vumeter_lr[5], "-10");
	lv_label_set_text(text_signal_vumeter_lr[6], "0dB");
	lv_label_set_text(text_signal_vumeter_lr[7], "6dB>");

	// Position
	lv_obj_set_pos(text_signal_vumeter_lr[0], 27, 278);
	lv_obj_set_pos(text_signal_vumeter_lr[1], 96, 278);
	lv_obj_set_pos(text_signal_vumeter_lr[2], 164, 278);
	lv_obj_set_pos(text_signal_vumeter_lr[3], 234, 278);
	lv_obj_set_pos(text_signal_vumeter_lr[4], 270, 278);
	lv_obj_set_pos(text_signal_vumeter_lr[5], 304, 278);
	lv_obj_set_pos(text_signal_vumeter_lr[6], 329, 278);
	lv_obj_set_pos(text_signal_vumeter_lr[7], 353, 278);
}

void create_label_vumeter_mpx(void)
{
	// Label MPX
	for(uint8_t x = 0; x < 7; x++) {
		text_signal_vumeter_mpx[x] = lv_label_create(Tela_Config_Signal);
		lv_obj_set_width(text_signal_vumeter_mpx[x], LV_SIZE_CONTENT);
		lv_obj_set_height(text_signal_vumeter_mpx[x], LV_SIZE_CONTENT);
		lv_obj_set_style_text_align(text_signal_vumeter_mpx[x], LV_TEXT_ALIGN_CENTER, 0);
		lv_obj_set_style_text_color(text_signal_vumeter_mpx[x], lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
		lv_obj_set_style_text_opa(text_signal_vumeter_mpx[x], 255, LV_PART_MAIN | LV_STATE_DEFAULT);
		lv_obj_set_style_text_font(text_signal_vumeter_mpx[x], &Neue_Medium_11, LV_PART_MAIN | LV_STATE_DEFAULT);
	}

	// Text
	lv_label_set_text(text_signal_vumeter_mpx[0], "2.5KHz");
	lv_label_set_text(text_signal_vumeter_mpx[1], "STEP");
	lv_label_set_text(text_signal_vumeter_mpx[2], "25KHz");
	lv_label_set_text(text_signal_vumeter_mpx[3], "50");
	lv_label_set_text(text_signal_vumeter_mpx[4], "75");
	lv_label_set_text(text_signal_vumeter_mpx[5], "82.5");
	lv_label_set_text(text_signal_vumeter_mpx[6], "100KHz");

	// Position
	lv_obj_set_pos(text_signal_vumeter_mpx[0], 27, 212);
	lv_obj_set_pos(text_signal_vumeter_mpx[1], 65, 212);
	lv_obj_set_pos(text_signal_vumeter_mpx[2], 96, 212);
	lv_obj_set_pos(text_signal_vumeter_mpx[3], 160, 212);
	lv_obj_set_pos(text_signal_vumeter_mpx[4], 228, 212);	// 75
	lv_obj_set_pos(text_signal_vumeter_mpx[5], 250, 212);
	lv_obj_set_pos(text_signal_vumeter_mpx[6], 282, 212);
}

void create_label_Deviation(void)
{
	// Label DEVIATION MONITOR
	text_signal_deviation = lv_label_create(Tela_Config_Signal);
	lv_obj_set_width(text_signal_deviation, LV_SIZE_CONTENT);
	lv_obj_set_height(text_signal_deviation, LV_SIZE_CONTENT);
	lv_obj_set_style_text_align(text_signal_deviation, LV_TEXT_ALIGN_CENTER, 0);
	lv_obj_set_style_text_color(text_signal_deviation, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_opa(text_signal_deviation, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(text_signal_deviation, &Neue_Medium_16, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_pos(text_signal_deviation, 31, 195);
	lv_label_set_text(text_signal_deviation, "DEVIATION MONITOR:");
}
