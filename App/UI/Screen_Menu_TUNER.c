/*
 * Screen_Menu_TUNER.c
 *
 *  Created on: 28 de ago. de 2026
 *      Author: rinaldo.santos
 */

#include "stdbool.h"
#include "rng.h"
#include "stdio.h"
#include "string.h"

#include "../App/UI/Screen_Menu_TUNER.h"
#include "../App/UI/Screen_Utils.h"

LV_FONT_DECLARE(Neue_MediumItalic_14);
LV_FONT_DECLARE(Neue_Medium_10);
LV_FONT_DECLARE(Neue_Medium_14);
LV_FONT_DECLARE(Neue_Medium_16);
LV_FONT_DECLARE(Neue_Medium_20);
LV_FONT_DECLARE(Neue_Medium_52);

extern int32_t fm_frequency;
extern char str_freq[20];
extern void formatar_frequencia(int32_t valor, char *resultado, size_t tamanho);
extern void create_vumeter_50_left_tuner(void);
extern void create_vumeter_50_right_tuner(void);
extern void create_vumeter_50_mpx_tuner(void);
extern void set_vumeter_50_left_tuner(int32_t value);
extern void set_vumeter_50_right_tuner(int32_t value);
extern void set_vumeter_50_mpx_tuner(int32_t value);

void create_tuner_fm_symbol(void);
void create_tuner_tuned(void);
void create_tuner_stereo(void);
void create_tuner_rds(void);
void create_tuner_Label_Frequency(int32_t frequency);
void create_tuner_Label_RDS(void);
void create_tuner_buttons_tunner(void);
void create_memory_bank(void);
void create_channel_space(void);
void create_bw_space(void);
void create_tuner_phone(void);
void create_tuner_text_indic(void);
void create_buttons_tuner(void);

lv_obj_t * Tela_Menu_TUNER = NULL;
static lv_obj_t * img_fundo_menu_tuner = NULL;
static lv_obj_t * label_tuner_frequency = NULL;
static lv_obj_t * label_tuner_rds = NULL;
static lv_obj_t * tuner_bt_rev = NULL;
static lv_obj_t * tuner_bt_next = NULL;
static lv_obj_t * tuner_bt_prevff = NULL;
static lv_obj_t * tuner_bt_nextff = NULL;
static lv_obj_t * tuner_bt_channel_dec = NULL;
static lv_obj_t * tuner_bt_channel_inc = NULL;
static lv_obj_t * label_channel = NULL;
static lv_obj_t * tuner_bt_bw_dec = NULL;
static lv_obj_t * tuner_bt_bw_inc = NULL;
static lv_obj_t * label_bw = NULL;
static lv_obj_t * tuner_bt_phone_dec = NULL;
static lv_obj_t * tuner_bt_phone_inc = NULL;
static lv_obj_t * label_vol_phone = NULL;
static lv_obj_t * tuner_bt_mpx = NULL;
static lv_obj_t * tuner_bt_tuner = NULL;

static uint32_t channel_space = 100;
static uint32_t band_bw = 50;
static uint8_t volume_phone = 55;
static uint32_t user_data_bt_tuner = 0;

void Screen_Menu_TUNER_Create(void)
{
	Tela_Menu_TUNER = lv_obj_create(NULL);
	lv_obj_clear_flag(Tela_Menu_TUNER, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLLABLE);
	lv_obj_set_style_bg_color(Tela_Menu_TUNER, lv_color_hex(0x000000), 0);
	lv_obj_set_style_bg_grad_color(Tela_Menu_TUNER, lv_color_hex(0x000000), 0);

	// Imagem de Fundo
	img_fundo_menu_tuner = lv_img_create(Tela_Menu_TUNER);
	lv_img_set_src(img_fundo_menu_tuner, "S:/TUNER/TELA_TUNER.bin");
	lv_obj_set_pos(img_fundo_menu_tuner, 0, 0);

	// FM SYMBOL
	create_tuner_fm_symbol();
	create_tuner_tuned();
	create_tuner_stereo();
	create_tuner_rds();

	// Frequency
	create_tuner_Label_Frequency(fm_frequency);

	// Label RDS
	create_tuner_Label_RDS();

	// Buttons Tunner
	create_tuner_buttons_tunner();

	// MEMORY BANK
	create_memory_bank();

	// CH SPACE
	create_channel_space();

	// IF BW
	create_bw_space();

	// VOLUME
	create_tuner_phone();

	// Text
	create_tuner_text_indic();

	// VU-Meter
	create_vumeter_50_left_tuner();
	create_vumeter_50_right_tuner();
	create_vumeter_50_mpx_tuner();

	// Buttons TUNER
	create_buttons_tuner();

	create_button_back_main(Tela_Menu_TUNER, 383, 288, PAGE_MAIN);
}

void create_tuner_fm_symbol(void)
{
	// FM Symbol
	lv_obj_t * img_fm = lv_img_create(Tela_Menu_TUNER);
	lv_img_set_src(img_fm, "S:/MAIN/IMG_FM.bin");
	lv_obj_set_pos(img_fm, 8, 8);
	//
    lv_obj_t * text_fm = lv_label_create(img_fm);
    lv_obj_set_width(text_fm, LV_SIZE_CONTENT);
    lv_obj_set_height(text_fm, LV_SIZE_CONTENT);
    lv_label_set_text(text_fm, "FM");
    lv_obj_set_style_text_color(text_fm, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(text_fm, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(text_fm, &Neue_MediumItalic_14, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_align_to(text_fm, img_fm, LV_ALIGN_CENTER, 0, 0);
}

void create_tuner_tuned(void)
{
	// TUNED Symbol
	lv_obj_t * img_tuned = lv_img_create(Tela_Menu_TUNER);
	lv_img_set_src(img_tuned, "S:/MAIN/BT_TUNED.bin");

	lv_obj_set_pos(img_tuned, 332, 8);

	// Text
    lv_obj_t * text_tuned = lv_label_create(img_tuned);
    lv_obj_set_width(text_tuned, LV_SIZE_CONTENT);
    lv_obj_set_height(text_tuned, LV_SIZE_CONTENT);
    lv_label_set_text(text_tuned, "TUNED");
    lv_obj_set_style_text_color(text_tuned, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(text_tuned, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(text_tuned, &Neue_Medium_10, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_align_to(text_tuned, img_tuned, LV_ALIGN_CENTER, 0, 0);
}

void create_tuner_stereo(void)
{
	// STEREO Symbol
	lv_obj_t * img_stereo = lv_img_create(Tela_Menu_TUNER);
	lv_img_set_src(img_stereo, "S/MAIN/BT_STEREO.bin");
	lv_obj_set_pos(img_stereo, 330, 38);

	// Text
    lv_obj_t * text_stereo = lv_label_create(img_stereo);
    lv_obj_set_width(text_stereo, LV_SIZE_CONTENT);
    lv_obj_set_height(text_stereo, LV_SIZE_CONTENT);
    lv_label_set_text(text_stereo, "STEREO");
    lv_obj_set_style_text_color(text_stereo, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(text_stereo, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(text_stereo, &Neue_Medium_10, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_align_to(text_stereo, img_stereo, LV_ALIGN_CENTER, 0, 0);
}

void create_tuner_rds(void)
{
	// RDS Symbol
	lv_obj_t * img_rds = lv_img_create(Tela_Menu_TUNER);
	lv_img_set_src(img_rds, "S:/MAIN/BT_RDS.bin");
	lv_obj_set_pos(img_rds, 332, 66);

	// Text
    lv_obj_t * text_rds = lv_label_create(img_rds);
    lv_obj_set_width(text_rds, LV_SIZE_CONTENT);
    lv_obj_set_height(text_rds, LV_SIZE_CONTENT);
    lv_label_set_text(text_rds, "RDS");
    lv_obj_set_style_text_color(text_rds, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(text_rds, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(text_rds, &Neue_Medium_10, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_align_to(text_rds, img_rds, LV_ALIGN_CENTER, 0, 1);
}

void create_tuner_Label_Frequency(int32_t frequency)
{
    label_tuner_frequency = lv_label_create(Tela_Menu_TUNER);
    lv_obj_set_width(label_tuner_frequency, 316);
    lv_obj_set_height(label_tuner_frequency, LV_SIZE_CONTENT);
    // Color Font
    lv_obj_set_style_text_color(label_tuner_frequency, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(label_tuner_frequency, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(label_tuner_frequency, &Neue_Medium_52, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(label_tuner_frequency, 0, 1);
    lv_obj_set_style_text_line_space(label_tuner_frequency, 0, 1);
    lv_obj_set_style_text_align(label_tuner_frequency, LV_TEXT_ALIGN_CENTER, 0);

    formatar_frequencia(frequency, str_freq, sizeof(str_freq));
    lv_label_set_text_fmt(label_tuner_frequency, str_freq);

    lv_obj_set_pos(label_tuner_frequency, 12, 34);
}

void create_tuner_Label_RDS(void)
{
    label_tuner_rds = lv_label_create(Tela_Menu_TUNER);
    lv_obj_set_width(label_tuner_rds, 280);
    lv_obj_set_height(label_tuner_rds, LV_SIZE_CONTENT);
    lv_label_set_text(label_tuner_rds, "AS MELHORES DA PROGRAMACAO SINTECK NEXT");
    lv_label_set_long_mode(label_tuner_rds, LV_LABEL_LONG_SCROLL_CIRCULAR);
    lv_obj_set_style_text_color(label_tuner_rds, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(label_tuner_rds, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(label_tuner_rds, &Neue_Medium_16, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(label_tuner_rds, 48, 12);
}

static void event_tuner_bt_next(lv_event_t * e)
{
	lv_event_code_t code = lv_event_get_code(e);

	if(code == LV_EVENT_CLICKED || code == LV_EVENT_LONG_PRESSED_REPEAT) {
		 if(fm_frequency < 108100) {
			 fm_frequency += 100; // Incrementa de 100
			 formatar_frequencia(fm_frequency, str_freq, sizeof(str_freq));
			 lv_label_set_text_fmt(label_tuner_frequency, str_freq);
		 }
	 }
}

static void event_tuner_bt_rev(lv_event_t * e)
{
	lv_event_code_t code = lv_event_get_code(e);

	if(code == LV_EVENT_CLICKED || code == LV_EVENT_LONG_PRESSED_REPEAT) {
		 if(fm_frequency > 76000) {
			 fm_frequency -= 100; // Decrementa de 100
			 formatar_frequencia(fm_frequency, str_freq, sizeof(str_freq));
			 lv_label_set_text_fmt(label_tuner_frequency, str_freq);
		 }
	 }
}

static void event_tuner_bt_nextff(lv_event_t * e)
{
	lv_event_code_t code = lv_event_get_code(e);

	if(code == LV_EVENT_CLICKED || code == LV_EVENT_LONG_PRESSED_REPEAT) {
		 if(fm_frequency < 108100) {
			 fm_frequency += 1000; // Incrementa de 1000
			 formatar_frequencia(fm_frequency, str_freq, sizeof(str_freq));
			 lv_label_set_text_fmt(label_tuner_frequency, str_freq);
		 }
	 }
}

static void event_tuner_bt_prevff(lv_event_t * e)
{
	lv_event_code_t code = lv_event_get_code(e);

	 if(code == LV_EVENT_CLICKED || code == LV_EVENT_LONG_PRESSED_REPEAT) {
		 if(fm_frequency > 76100) {
			 fm_frequency -= 1000; // Decrementa de 1000
			 formatar_frequencia(fm_frequency, str_freq, sizeof(str_freq));
			 lv_label_set_text_fmt(label_tuner_frequency, str_freq);
		 }
	 }
}

void create_tuner_buttons_tunner(void)
{
    // Button PREV
    tuner_bt_rev = lv_imagebutton_create(Tela_Menu_TUNER);
    lv_imagebutton_set_src(tuner_bt_rev, LV_IMAGEBUTTON_STATE_RELEASED, NULL, "S:/MAIN/BT_RR.bin", NULL);
    lv_imagebutton_set_src(tuner_bt_rev, LV_IMAGEBUTTON_STATE_PRESSED, NULL, "S:/MAIN/BT_RR_P.bin", NULL);
    lv_imagebutton_set_src(tuner_bt_rev, LV_IMAGEBUTTON_STATE_DISABLED, NULL, "S:/MAIN/BT_RR.bin", NULL);
    lv_imagebutton_set_src(tuner_bt_rev, LV_IMAGEBUTTON_STATE_CHECKED_PRESSED, NULL, "S:/MAIN/BT_RR_P.bin", NULL);
    lv_imagebutton_set_src(tuner_bt_rev, LV_IMAGEBUTTON_STATE_CHECKED_RELEASED, NULL, "S:/MAIN/BT_RR.bin", NULL);
    lv_imagebutton_set_src(tuner_bt_rev, LV_IMAGEBUTTON_STATE_CHECKED_DISABLED, NULL, "S:/MAIN/BT_RR.bin", NULL);
    lv_obj_set_pos(tuner_bt_rev, 384, 10);
    lv_obj_add_event_cb(tuner_bt_rev, event_tuner_bt_rev, LV_EVENT_ALL, NULL);

    // Button NEXT
    tuner_bt_next = lv_imagebutton_create(Tela_Menu_TUNER);
    lv_imagebutton_set_src(tuner_bt_next, LV_IMAGEBUTTON_STATE_RELEASED, NULL, "S:/MAIN/BT_FW.bin", NULL);
    lv_imagebutton_set_src(tuner_bt_next, LV_IMAGEBUTTON_STATE_PRESSED, NULL, "S:/MAIN/BT_FW_P.bin", NULL);
    lv_imagebutton_set_src(tuner_bt_next, LV_IMAGEBUTTON_STATE_DISABLED, NULL, "S:/MAIN/BT_FW.bin", NULL);
    lv_imagebutton_set_src(tuner_bt_next, LV_IMAGEBUTTON_STATE_CHECKED_PRESSED, NULL, "S:/MAIN/BT_FW_P.bin", NULL);
    lv_imagebutton_set_src(tuner_bt_next, LV_IMAGEBUTTON_STATE_CHECKED_RELEASED, NULL, "S:/MAIN/BT_FW.bin", NULL);
    lv_imagebutton_set_src(tuner_bt_next, LV_IMAGEBUTTON_STATE_CHECKED_DISABLED, NULL, "S:/MAIN/BT_FW.bin", NULL);
    lv_obj_set_pos(tuner_bt_next, 432, 10);
    lv_obj_add_event_cb(tuner_bt_next, event_tuner_bt_next, LV_EVENT_ALL, NULL);

    // Button REV FF
    tuner_bt_prevff = lv_imagebutton_create(Tela_Menu_TUNER);
    lv_imagebutton_set_src(tuner_bt_prevff, LV_IMAGEBUTTON_STATE_RELEASED, NULL, "S:/MAIN/BT_RW.bin", NULL);
    lv_imagebutton_set_src(tuner_bt_prevff, LV_IMAGEBUTTON_STATE_PRESSED, NULL, "S:/MAIN/BT_RW_P.bin", NULL);
    lv_imagebutton_set_src(tuner_bt_prevff, LV_IMAGEBUTTON_STATE_DISABLED, NULL, "S:/MAIN/BT_RW.bin", NULL);
    lv_imagebutton_set_src(tuner_bt_prevff, LV_IMAGEBUTTON_STATE_CHECKED_PRESSED, NULL, "S:/MAIN/BT_RW_P.bin", NULL);
    lv_imagebutton_set_src(tuner_bt_prevff, LV_IMAGEBUTTON_STATE_CHECKED_RELEASED, NULL, "S:/MAIN/BT_RW.bin", NULL);
    lv_imagebutton_set_src(tuner_bt_prevff, LV_IMAGEBUTTON_STATE_CHECKED_DISABLED, NULL, "S:/MAIN/BT_RW.bin", NULL);
    lv_obj_set_pos(tuner_bt_prevff, 384, 50);
    lv_obj_add_event_cb(tuner_bt_prevff, event_tuner_bt_nextff, LV_EVENT_ALL, NULL);

    // Button REV FF
    tuner_bt_nextff = lv_imagebutton_create(Tela_Menu_TUNER);
    lv_imagebutton_set_src(tuner_bt_nextff, LV_IMAGEBUTTON_STATE_RELEASED, NULL, "S:/MAIN/BT_FF.bin", NULL);
    lv_imagebutton_set_src(tuner_bt_nextff, LV_IMAGEBUTTON_STATE_PRESSED, NULL, "S:/MAIN/BT_FF_P.bin", NULL);
    lv_imagebutton_set_src(tuner_bt_nextff, LV_IMAGEBUTTON_STATE_DISABLED, NULL, "S:/MAIN/BT_FF.bin", NULL);
    lv_imagebutton_set_src(tuner_bt_nextff, LV_IMAGEBUTTON_STATE_CHECKED_PRESSED, NULL, "S:/MAIN/BT_FF_P.bin", NULL);
    lv_imagebutton_set_src(tuner_bt_nextff, LV_IMAGEBUTTON_STATE_CHECKED_RELEASED, NULL, "S:/MAIN/BT_FF.bin", NULL);
    lv_imagebutton_set_src(tuner_bt_nextff, LV_IMAGEBUTTON_STATE_CHECKED_DISABLED, NULL, "S:/MAIN/BT_FF.bin", NULL);
    lv_obj_set_pos(tuner_bt_nextff, 432, 50);
    lv_obj_add_event_cb(tuner_bt_nextff, event_tuner_bt_prevff, LV_EVENT_ALL, NULL);
}

void create_memory_bank(void)
{
    lv_obj_t * text_memory_bank = lv_label_create(Tela_Menu_TUNER);
    lv_obj_set_width(text_memory_bank, LV_SIZE_CONTENT);
    lv_obj_set_height(text_memory_bank, LV_SIZE_CONTENT);
    lv_label_set_text(text_memory_bank, "MEMORY BANK / SET:");
    lv_obj_set_style_text_color(text_memory_bank, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(text_memory_bank, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(text_memory_bank, &Neue_Medium_14, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(text_memory_bank, 18, 98);
}


static void event_channel_inc(lv_event_t * e)
{
	lv_event_code_t code = lv_event_get_code(e);

	if(code == LV_EVENT_CLICKED || code == LV_EVENT_LONG_PRESSED_REPEAT) {
		if(channel_space < 200) {
			channel_space += 50;
			lv_label_set_text_fmt(label_channel, "%ld KHz", channel_space);
		}
	 }
}

static void event_channel_dec(lv_event_t * e)
{
	lv_event_code_t code = lv_event_get_code(e);

	if(code == LV_EVENT_CLICKED || code == LV_EVENT_LONG_PRESSED_REPEAT) {
		if(channel_space > 50) {
			channel_space -= 50;
			lv_label_set_text_fmt(label_channel, "%ld KHz", channel_space);
		}
	 }
}

void create_channel_space(void)
{
    lv_obj_t * text_channel = lv_label_create(Tela_Menu_TUNER);
    lv_obj_set_width(text_channel, LV_SIZE_CONTENT);
    lv_obj_set_height(text_channel, LV_SIZE_CONTENT);
    lv_label_set_text(text_channel, "CH SPACE:");
    lv_obj_set_style_text_color(text_channel, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(text_channel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(text_channel, &Neue_Medium_14, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(text_channel, 202, 98);

    // Button DEC Channel
    tuner_bt_channel_dec = lv_imagebutton_create(Tela_Menu_TUNER);
    lv_imagebutton_set_src(tuner_bt_channel_dec, LV_IMAGEBUTTON_STATE_RELEASED, NULL, "S:/GENERATOR/BT_DN_2.bin", NULL);
    lv_imagebutton_set_src(tuner_bt_channel_dec, LV_IMAGEBUTTON_STATE_PRESSED, NULL, "S:/GENERATOR/BT_DN_2_P.bin", NULL);
    lv_imagebutton_set_src(tuner_bt_channel_dec, LV_IMAGEBUTTON_STATE_DISABLED, NULL, "S:/GENERATOR/BT_DN_2.bin", NULL);
    lv_imagebutton_set_src(tuner_bt_channel_dec, LV_IMAGEBUTTON_STATE_CHECKED_PRESSED, NULL, "S:/GENERATOR/BT_DN_2_P.bin", NULL);
    lv_imagebutton_set_src(tuner_bt_channel_dec, LV_IMAGEBUTTON_STATE_CHECKED_RELEASED, NULL, "S:/GENERATOR/BT_DN_2.bin", NULL);
    lv_imagebutton_set_src(tuner_bt_channel_dec, LV_IMAGEBUTTON_STATE_CHECKED_DISABLED, NULL, "S:/GENERATOR/BT_DN_2.bin", NULL);
    lv_obj_set_pos(tuner_bt_channel_dec, 195, 152);
    lv_obj_add_event_cb(tuner_bt_channel_dec, event_channel_dec, LV_EVENT_ALL, NULL);

    // Button INC Channel
    tuner_bt_channel_inc = lv_imagebutton_create(Tela_Menu_TUNER);
    lv_imagebutton_set_src(tuner_bt_channel_inc, LV_IMAGEBUTTON_STATE_RELEASED, NULL, "S:/GENERATOR/BT_UP_2.bin", NULL);
    lv_imagebutton_set_src(tuner_bt_channel_inc, LV_IMAGEBUTTON_STATE_PRESSED, NULL, "S:/GENERATOR/BT_UP_2_P.bin", NULL);
    lv_imagebutton_set_src(tuner_bt_channel_inc, LV_IMAGEBUTTON_STATE_DISABLED, NULL, "S:/GENERATOR/BT_UP_2.bin", NULL);
    lv_imagebutton_set_src(tuner_bt_channel_inc, LV_IMAGEBUTTON_STATE_CHECKED_PRESSED, NULL, "S:/GENERATOR/BT_UP_2_P.bin", NULL);
    lv_imagebutton_set_src(tuner_bt_channel_inc, LV_IMAGEBUTTON_STATE_CHECKED_RELEASED, NULL, "S:/GENERATOR/BT_UP_2.bin", NULL);
    lv_imagebutton_set_src(tuner_bt_channel_inc, LV_IMAGEBUTTON_STATE_CHECKED_DISABLED, NULL, "S:/GENERATOR/BT_UP_2.bin", NULL);
    lv_obj_set_pos(tuner_bt_channel_inc, 240, 152);
    lv_obj_add_event_cb(tuner_bt_channel_inc, event_channel_inc, LV_EVENT_ALL, NULL);

    label_channel = lv_label_create(Tela_Menu_TUNER);
    lv_obj_set_width(label_channel, 90);
    lv_obj_set_height(label_channel, LV_SIZE_CONTENT);
    lv_label_set_text_fmt(label_channel, "%ld KHz", channel_space);
    lv_obj_set_style_text_align(label_channel, LV_TEXT_ALIGN_CENTER, 0);
    lv_obj_set_style_text_color(label_channel, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(label_channel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(label_channel, &Neue_Medium_16, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(label_channel, 194, 125);
}

static void event_bw_inc(lv_event_t * e)
{
	lv_event_code_t code = lv_event_get_code(e);

	if(code == LV_EVENT_CLICKED || code == LV_EVENT_LONG_PRESSED_REPEAT) {
		if(band_bw < 300) {
			band_bw += 50;
			lv_label_set_text_fmt(label_bw, "%ld KHz", band_bw);
		}
	 }
}

static void event_bw_dec(lv_event_t * e)
{
	lv_event_code_t code = lv_event_get_code(e);

	if(code == LV_EVENT_CLICKED || code == LV_EVENT_LONG_PRESSED_REPEAT) {
		if(band_bw > 50) {
			band_bw -= 50;
			lv_label_set_text_fmt(label_bw, "%ld KHz", band_bw);
		}
	 }
}

void create_bw_space(void)
{
    lv_obj_t * text_bw = lv_label_create(Tela_Menu_TUNER);
    lv_obj_set_width(text_bw, LV_SIZE_CONTENT);
    lv_obj_set_height(text_bw, LV_SIZE_CONTENT);
    lv_label_set_text(text_bw, "IF BW:");
    lv_obj_set_style_text_color(text_bw, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(text_bw, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(text_bw, &Neue_Medium_14, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(text_bw, 312, 98);

    // Button DEC BW
    tuner_bt_bw_dec = lv_imagebutton_create(Tela_Menu_TUNER);
    lv_imagebutton_set_src(tuner_bt_bw_dec, LV_IMAGEBUTTON_STATE_RELEASED, NULL, "S:/GENERATOR/BT_DN_2.bin", NULL);
    lv_imagebutton_set_src(tuner_bt_bw_dec, LV_IMAGEBUTTON_STATE_PRESSED, NULL, "S:/GENERATOR/BT_DN_2_P.bin", NULL);
    lv_imagebutton_set_src(tuner_bt_bw_dec, LV_IMAGEBUTTON_STATE_DISABLED, NULL, "S:/GENERATOR/BT_DN_2.bin", NULL);
    lv_imagebutton_set_src(tuner_bt_bw_dec, LV_IMAGEBUTTON_STATE_CHECKED_PRESSED, NULL, "S:/GENERATOR/BT_DN_2_P.bin", NULL);
    lv_imagebutton_set_src(tuner_bt_bw_dec, LV_IMAGEBUTTON_STATE_CHECKED_RELEASED, NULL, "S:/GENERATOR/BT_DN_2.bin", NULL);
    lv_imagebutton_set_src(tuner_bt_bw_dec, LV_IMAGEBUTTON_STATE_CHECKED_DISABLED, NULL, "S:/GENERATOR/BT_DN_2.bin", NULL);
    lv_obj_set_pos(tuner_bt_bw_dec, 290, 152);
    lv_obj_add_event_cb(tuner_bt_bw_dec, event_bw_dec, LV_EVENT_ALL, NULL);

    // Button INC BW
    tuner_bt_bw_inc = lv_imagebutton_create(Tela_Menu_TUNER);
    lv_imagebutton_set_src(tuner_bt_bw_inc, LV_IMAGEBUTTON_STATE_RELEASED, NULL, "S:/GENERATOR/BT_UP_2.bin", NULL);
    lv_imagebutton_set_src(tuner_bt_bw_inc, LV_IMAGEBUTTON_STATE_PRESSED, NULL, "S:/GENERATOR/BT_UP_2_P.bin", NULL);
    lv_imagebutton_set_src(tuner_bt_bw_inc, LV_IMAGEBUTTON_STATE_DISABLED, NULL, "S:/GENERATOR/BT_UP_2.bin", NULL);
    lv_imagebutton_set_src(tuner_bt_bw_inc, LV_IMAGEBUTTON_STATE_CHECKED_PRESSED, NULL, "S:/GENERATOR/BT_UP_2_P.bin", NULL);
    lv_imagebutton_set_src(tuner_bt_bw_inc, LV_IMAGEBUTTON_STATE_CHECKED_RELEASED, NULL, "S:/GENERATOR/BT_UP_2.bin", NULL);
    lv_imagebutton_set_src(tuner_bt_bw_inc, LV_IMAGEBUTTON_STATE_CHECKED_DISABLED, NULL, "S:/GENERATOR/BT_UP_2.bin", NULL);
    lv_obj_set_pos(tuner_bt_bw_inc, 335, 152);
    lv_obj_add_event_cb(tuner_bt_bw_inc, event_bw_inc, LV_EVENT_ALL, NULL);

    label_bw = lv_label_create(Tela_Menu_TUNER);
    lv_obj_set_width(label_bw, 90);
    lv_obj_set_height(label_bw, LV_SIZE_CONTENT);
    lv_label_set_text_fmt(label_bw, "%ld KHz", band_bw);
    lv_obj_set_style_text_align(label_bw, LV_TEXT_ALIGN_CENTER, 0);
    lv_obj_set_style_text_color(label_bw, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(label_bw, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(label_bw, &Neue_Medium_16, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(label_bw, 288, 125);
}

static void event_tuner_phone_inc(lv_event_t * e)
{
	lv_event_code_t code = lv_event_get_code(e);

	if(code == LV_EVENT_CLICKED || code == LV_EVENT_LONG_PRESSED_REPEAT) {
		volume_phone++;
		if(volume_phone >= 100) volume_phone = 100;
		lv_label_set_text_fmt(label_vol_phone, "%d%%", volume_phone);
	 }
}

static void event_tuner_phone_dec(lv_event_t * e)
{
	lv_event_code_t code = lv_event_get_code(e);

	if(code == LV_EVENT_CLICKED || code == LV_EVENT_LONG_PRESSED_REPEAT) {
		if(volume_phone >= 1) {
			volume_phone--;
			lv_label_set_text_fmt(label_vol_phone, "%d%%", volume_phone);
		}
	}
}

void create_tuner_phone(void)
{
    lv_obj_t * text_vol = lv_label_create(Tela_Menu_TUNER);
    lv_obj_set_width(text_vol, LV_SIZE_CONTENT);
    lv_obj_set_height(text_vol, LV_SIZE_CONTENT);
    lv_label_set_text(text_vol, "VOLUME:");
    lv_obj_set_style_text_color(text_vol, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(text_vol, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(text_vol, &Neue_Medium_14, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(text_vol, 398, 98);

    // Button DEC BW
    tuner_bt_phone_dec = lv_imagebutton_create(Tela_Menu_TUNER);
    lv_imagebutton_set_src(tuner_bt_phone_dec, LV_IMAGEBUTTON_STATE_RELEASED, NULL, "S:/GENERATOR/BT_DN_2.bin", NULL);
    lv_imagebutton_set_src(tuner_bt_phone_dec, LV_IMAGEBUTTON_STATE_PRESSED, NULL, "S:/GENERATOR/BT_DN_2_P.bin", NULL);
    lv_imagebutton_set_src(tuner_bt_phone_dec, LV_IMAGEBUTTON_STATE_DISABLED, NULL, "S:/GENERATOR/BT_DN_2.bin", NULL);
    lv_imagebutton_set_src(tuner_bt_phone_dec, LV_IMAGEBUTTON_STATE_CHECKED_PRESSED, NULL, "S:/GENERATOR/BT_DN_2_P.bin", NULL);
    lv_imagebutton_set_src(tuner_bt_phone_dec, LV_IMAGEBUTTON_STATE_CHECKED_RELEASED, NULL, "S:/GENERATOR/BT_DN_2.bin", NULL);
    lv_imagebutton_set_src(tuner_bt_phone_dec, LV_IMAGEBUTTON_STATE_CHECKED_DISABLED, NULL, "S:/GENERATOR/BT_DN_2.bin", NULL);
    lv_obj_set_pos(tuner_bt_phone_dec, 387, 152);
    lv_obj_add_event_cb(tuner_bt_phone_dec, event_tuner_phone_dec, LV_EVENT_ALL, NULL);

    // Button INC BW
    tuner_bt_phone_inc = lv_imagebutton_create(Tela_Menu_TUNER);
    lv_imagebutton_set_src(tuner_bt_phone_inc, LV_IMAGEBUTTON_STATE_RELEASED, NULL, "S:/GENERATOR/BT_UP_2.bin", NULL);
    lv_imagebutton_set_src(tuner_bt_phone_inc, LV_IMAGEBUTTON_STATE_PRESSED, NULL, "S:/GENERATOR/BT_UP_2_P.bin", NULL);
    lv_imagebutton_set_src(tuner_bt_phone_inc, LV_IMAGEBUTTON_STATE_DISABLED, NULL, "S:/GENERATOR/BT_UP_2.bin", NULL);
    lv_imagebutton_set_src(tuner_bt_phone_inc, LV_IMAGEBUTTON_STATE_CHECKED_PRESSED, NULL, "S:/GENERATOR/BT_UP_2_P.bin", NULL);
    lv_imagebutton_set_src(tuner_bt_phone_inc, LV_IMAGEBUTTON_STATE_CHECKED_RELEASED, NULL, "S:/GENERATOR/BT_UP_2.bin", NULL);
    lv_imagebutton_set_src(tuner_bt_phone_inc, LV_IMAGEBUTTON_STATE_CHECKED_DISABLED, NULL, "S:/GENERATOR/BT_UP_2.bin", NULL);
    lv_obj_set_pos(tuner_bt_phone_inc, 431, 152);
    lv_obj_add_event_cb(tuner_bt_phone_inc, event_tuner_phone_inc, LV_EVENT_ALL, NULL);

    label_vol_phone = lv_label_create(Tela_Menu_TUNER);
    lv_obj_set_width(label_vol_phone, 90);
    lv_obj_set_height(label_vol_phone, LV_SIZE_CONTENT);
    lv_label_set_text_fmt(label_vol_phone, "%d%%", volume_phone);
    lv_obj_set_style_text_align(label_vol_phone, LV_TEXT_ALIGN_RIGHT, 0);
    lv_obj_set_style_text_color(label_vol_phone, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(label_vol_phone, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(label_vol_phone, &Neue_Medium_16, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(label_vol_phone, 372, 125);

	// PHONE Symbol
	lv_obj_t * img_phone_tuner = lv_img_create(Tela_Menu_TUNER);
	lv_img_set_src(img_phone_tuner, "S:/TUNER/PHONE_BR.bin");
	lv_obj_set_pos(img_phone_tuner, 388, 118);
}

void create_tuner_text_indic(void)
{
    lv_obj_t * text_tuner_signal = lv_label_create(Tela_Menu_TUNER);
    lv_obj_set_width(text_tuner_signal, LV_SIZE_CONTENT);
    lv_obj_set_height(text_tuner_signal, LV_SIZE_CONTENT);
    lv_label_set_text(text_tuner_signal, "S");
    lv_obj_set_style_text_color(text_tuner_signal, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(text_tuner_signal, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(text_tuner_signal, &Neue_Medium_20, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(text_tuner_signal, 7, 191);

    lv_obj_t * text_tuner_signal_1 = lv_label_create(Tela_Menu_TUNER);
    lv_obj_set_width(text_tuner_signal_1, LV_SIZE_CONTENT);
    lv_obj_set_height(text_tuner_signal_1, LV_SIZE_CONTENT);
    lv_label_set_text(text_tuner_signal_1, "P");
    lv_obj_set_style_text_color(text_tuner_signal_1, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(text_tuner_signal_1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(text_tuner_signal_1, &Neue_Medium_20, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(text_tuner_signal_1, 250, 191);

    lv_obj_t * text_tuner_mpx = lv_label_create(Tela_Menu_TUNER);
    lv_obj_set_width(text_tuner_mpx, LV_SIZE_CONTENT);
    lv_obj_set_height(text_tuner_mpx, LV_SIZE_CONTENT);
    lv_label_set_text(text_tuner_mpx, "M");
    lv_obj_set_style_text_color(text_tuner_mpx, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(text_tuner_mpx, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(text_tuner_mpx, &Neue_Medium_20, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(text_tuner_mpx, 5, 230);

    lv_obj_t * text_tuner_l = lv_label_create(Tela_Menu_TUNER);
    lv_obj_set_width(text_tuner_l, LV_SIZE_CONTENT);
    lv_obj_set_height(text_tuner_l, LV_SIZE_CONTENT);
    lv_label_set_text(text_tuner_l, "L");
    lv_obj_set_style_text_color(text_tuner_l, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(text_tuner_l, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(text_tuner_l, &Neue_Medium_20, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(text_tuner_l, 8, 258);

    lv_obj_t * text_tuner_r = lv_label_create(Tela_Menu_TUNER);
    lv_obj_set_width(text_tuner_r, LV_SIZE_CONTENT);
    lv_obj_set_height(text_tuner_r, LV_SIZE_CONTENT);
    lv_label_set_text(text_tuner_r, "R");
    lv_obj_set_style_text_color(text_tuner_r, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(text_tuner_r, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(text_tuner_r, &Neue_Medium_20, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(text_tuner_r, 7, 294);
}

static void event_bt_tuner(lv_event_t * e)
{
	lv_event_code_t code = lv_event_get_code(e);

	if(code == LV_EVENT_CLICKED) {
		uint32_t btn = (uint32_t)(uintptr_t)lv_event_get_user_data(e);

		switch(btn) {
			case 0:
				lv_imagebutton_set_state(tuner_bt_mpx,  LV_IMAGEBUTTON_STATE_CHECKED_DISABLED);
				lv_imagebutton_set_state(tuner_bt_tuner, LV_IMAGEBUTTON_STATE_RELEASED);
				break;
			case 1:
				lv_imagebutton_set_state(tuner_bt_mpx,  LV_IMAGEBUTTON_STATE_RELEASED);
				lv_imagebutton_set_state(tuner_bt_tuner, LV_IMAGEBUTTON_STATE_CHECKED_DISABLED);
				break;
		}
	}
}

void create_buttons_tuner(void)
{
    // Button MPX
    tuner_bt_mpx = lv_imagebutton_create(Tela_Menu_TUNER);
    lv_imagebutton_set_src(tuner_bt_mpx, LV_IMAGEBUTTON_STATE_RELEASED, NULL, "S:/TUNER/BT_TUNER_OFF.bin", NULL);
    lv_imagebutton_set_src(tuner_bt_mpx, LV_IMAGEBUTTON_STATE_PRESSED, NULL, "S:/TUNER/BT_TUNER_ON.bin", NULL);
    lv_imagebutton_set_src(tuner_bt_mpx, LV_IMAGEBUTTON_STATE_DISABLED, NULL, "S:/TUNER/BT_TUNER_OFF.bin", NULL);
    lv_imagebutton_set_src(tuner_bt_mpx, LV_IMAGEBUTTON_STATE_CHECKED_PRESSED, NULL, "S:/TUNER/BT_TUNER_ON.bin", NULL);
    lv_imagebutton_set_src(tuner_bt_mpx, LV_IMAGEBUTTON_STATE_CHECKED_RELEASED, NULL, "S:/TUNER/BT_TUNER_OFF.bin", NULL);
    lv_imagebutton_set_src(tuner_bt_mpx, LV_IMAGEBUTTON_STATE_CHECKED_DISABLED, NULL, "S:/TUNER/BT_TUNER_ON.bin", NULL);
	user_data_bt_tuner = 0;
	lv_obj_add_event_cb(tuner_bt_mpx, event_bt_tuner, LV_EVENT_ALL, (void *)(uintptr_t)user_data_bt_tuner);
	lv_obj_set_pos(tuner_bt_tuner, 382, 180);

	// Button TUNER
    tuner_bt_tuner = lv_imagebutton_create(Tela_Menu_TUNER);
    lv_imagebutton_set_src(tuner_bt_tuner, LV_IMAGEBUTTON_STATE_RELEASED, NULL, "S:/TUNER/BT_TUNER_OFF.bin", NULL);
    lv_imagebutton_set_src(tuner_bt_tuner, LV_IMAGEBUTTON_STATE_PRESSED, NULL, "S:/TUNER/BT_TUNER_ON.bin", NULL);
    lv_imagebutton_set_src(tuner_bt_tuner, LV_IMAGEBUTTON_STATE_DISABLED, NULL, "S:/TUNER/BT_TUNER_OFF.bin", NULL);
    lv_imagebutton_set_src(tuner_bt_tuner, LV_IMAGEBUTTON_STATE_CHECKED_PRESSED, NULL, "S:/TUNER/BT_TUNER_ON.bin", NULL);
    lv_imagebutton_set_src(tuner_bt_tuner, LV_IMAGEBUTTON_STATE_CHECKED_RELEASED, NULL, "S:/TUNER/BT_TUNER_OFF.bin", NULL);
    lv_imagebutton_set_src(tuner_bt_tuner, LV_IMAGEBUTTON_STATE_CHECKED_DISABLED, NULL, "S:/TUNER/BT_TUNER_ON.bin", NULL);
	user_data_bt_tuner = 1;
	lv_obj_add_event_cb(tuner_bt_tuner, event_bt_tuner, LV_EVENT_ALL, (void *)(uintptr_t)user_data_bt_tuner);
	lv_obj_set_pos(tuner_bt_tuner, 382, 248);
}
