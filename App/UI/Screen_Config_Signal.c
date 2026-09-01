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

LV_FONT_DECLARE(Neue_Medium_14);
LV_FONT_DECLARE(Neue_Medium_16);
LV_FONT_DECLARE(Neue_Medium_20);

void create_config_signal_label(void);
void create_buttons_signal_tone(void);
void create_buttons_signal_mpx(void);

lv_obj_t * Tela_Config_Signal = NULL;
static lv_obj_t * text_config_signal_top = NULL;
static lv_obj_t * text_config_signal_mpx = NULL;
static lv_obj_t * text_config_signal_freq = NULL;
static lv_obj_t * text_config_signal_left = NULL;
static lv_obj_t * text_config_signal_right = NULL;
static lv_obj_t * text_config_signal_mpx1 = NULL;
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
    lv_obj_set_style_text_font(text_config_signal_freq, &Neue_Medium_14, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(text_config_signal_freq, 386, 199);

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

	if(code == LV_EVENT_CLICKED) {

	 }
}

static void event_tone_inc(lv_event_t * e)
{
	lv_event_code_t code = lv_event_get_code(e);

	if(code == LV_EVENT_CLICKED) {

	 }
}

static void event_tone_up(lv_event_t * e)
{
	lv_event_code_t code = lv_event_get_code(e);

	if(code == LV_EVENT_CLICKED) {

	 }
}

static void event_tone_dn(lv_event_t * e)
{
	lv_event_code_t code = lv_event_get_code(e);

	if(code == LV_EVENT_CLICKED) {

	 }
}

static void event_tone_prev(lv_event_t * e)
{
	lv_event_code_t code = lv_event_get_code(e);

	if(code == LV_EVENT_CLICKED) {

	 }
}

static void event_tone_next(lv_event_t * e)
{
	lv_event_code_t code = lv_event_get_code(e);

	if(code == LV_EVENT_CLICKED) {

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

	if(code == LV_EVENT_CLICKED) {

	 }
}

static void event_mpx_inc(lv_event_t * e)
{
	lv_event_code_t code = lv_event_get_code(e);

	if(code == LV_EVENT_CLICKED) {

	 }
}

static void event_mpx_up(lv_event_t * e)
{
	lv_event_code_t code = lv_event_get_code(e);

	if(code == LV_EVENT_CLICKED) {

	 }
}

static void event_mpx_dn(lv_event_t * e)
{
	lv_event_code_t code = lv_event_get_code(e);

	if(code == LV_EVENT_CLICKED) {

	 }
}

static void event_mpx_prev(lv_event_t * e)
{
	lv_event_code_t code = lv_event_get_code(e);

	if(code == LV_EVENT_CLICKED) {

	 }
}

static void event_mpx_next(lv_event_t * e)
{
	lv_event_code_t code = lv_event_get_code(e);

	if(code == LV_EVENT_CLICKED) {

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
