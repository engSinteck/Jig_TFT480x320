/*
 * Screen_Main.c
 *
 *  Created on: 14 de ago. de 2026
 *      Author: rinaldo.santos
 */

#include "main.h"
#include "stdbool.h"
#include "lvgl.h"

#include "../App/UI/Screen_Main.h"

void create_fm_symbol(void);
void create_text_lr(void);
void create_tuned(void);
void create_stereo(void);
void create_rds(void);
void create_buttons_tunner(void);
void create_buttons_volume(void);
void create_buttons_menu_1(void);
void create_buttons_menu_2(void);
void create_vumeter_left(void);
void create_Label_RDS(void);
void create_Label_Frequency(void);
void create_text_audio_source(void);
void create_text_scale_vu(void);

LV_FONT_DECLARE(Neue_Medium_10);
LV_FONT_DECLARE(Neue_Medium_11);
LV_FONT_DECLARE(Neue_Medium_12);
LV_FONT_DECLARE(Neue_Medium_14);
LV_FONT_DECLARE(Neue_Medium_16);
LV_FONT_DECLARE(Neue_Medium_18);
LV_FONT_DECLARE(Neue_Medium_20);
LV_FONT_DECLARE(Neue_Medium_52);
LV_FONT_DECLARE(Neue_MediumItalic_14);

LV_IMG_DECLARE(LED_GR_OFF);
LV_IMG_DECLARE(LED_GR);

static lv_obj_t * Tela_Main;
static lv_obj_t * img_fundo;
static lv_obj_t * bt_rev;
static lv_obj_t * bt_next;
static lv_obj_t * bt_prevff;
static lv_obj_t * bt_nextff;
static lv_obj_t * bt_vol_inc;
static lv_obj_t * bt_vol_dec;
static lv_obj_t * bt_menu[5];
static lv_obj_t * bt_inputs;
static lv_obj_t * bt_outputs;
static lv_obj_t * bt_configs;
//static lv_obj_t * vu_left[64];
//static lv_obj_t * vu_right[64];
static lv_obj_t * label_rds;
static lv_obj_t * label_frequency;
static lv_obj_t * label_scale[8];
static lv_obj_t * vu_left;

static lv_timer_t * task_Main;

static uint32_t cont_main = 0;

uint8_t flag_vumeter_lr = 0;
uint32_t demo_vumeter_lr = 0;

void update_main_screen(lv_timer_t * timer)
{
	if(!flag_vumeter_lr) {
		demo_vumeter_lr++;
		if(demo_vumeter_lr > 64) flag_vumeter_lr = 1;
	}
	else {
		if(demo_vumeter_lr >= 1) {
			demo_vumeter_lr--;
		}
		else flag_vumeter_lr = 0;
	}

	lv_slider_set_value(vu_left, demo_vumeter_lr, LV_ANIM_OFF);
}

void Screen_Main(void)
{
	Tela_Main = lv_obj_create(NULL);
	lv_obj_clear_flag(Tela_Main, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLLABLE);
	lv_obj_set_style_bg_color(Tela_Main, lv_color_hex(0x000000), 0);
	lv_obj_set_style_bg_grad_color(Tela_Main, lv_color_hex(0x000000), 0);

	// Imagem de Fundo
	img_fundo = lv_img_create(Tela_Main);
	lv_img_set_src(img_fundo, "S:/MAIN/TELA_FUNDO_MAIN.bin");
	lv_obj_set_pos(img_fundo, 0, 0);

	// Create FM Symbol
	create_fm_symbol();

	// Create Text L + R
	create_text_lr();

	// Create Tuned
	create_tuned();
	// Create Stereo
	create_stereo();
	// Create RDS
	create_rds();
	// Buttons Tunner
	create_buttons_tunner();
	// Buttons Volume
	create_buttons_volume();
	// Buttons Menu
	create_buttons_menu_1();
	create_buttons_menu_2();
	// Vu-Meter L+R
	create_vumeter_left();
	// Label RDS
	create_Label_RDS();
	// Label Frequency
	create_Label_Frequency();
	// Text Audio Source
	create_text_audio_source();
	// Text Scale VU
	create_text_scale_vu();

    cont_main = 0;
    static uint32_t user_data = 10;
    task_Main = lv_timer_create(update_main_screen, 200,  &user_data);

	lv_scr_load(Tela_Main);
}

void create_fm_symbol(void)
{
	// FM Symbol
	lv_obj_t * img_fm = lv_img_create(Tela_Main);
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

void create_text_lr(void)
{
	// Text L + R
    lv_obj_t * text_L = lv_label_create(Tela_Main);
    lv_obj_set_width(text_L, LV_SIZE_CONTENT);
    lv_obj_set_height(text_L, LV_SIZE_CONTENT);
    lv_label_set_text(text_L, "L");
    lv_obj_set_style_text_color(text_L, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(text_L, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(text_L, &Neue_Medium_20, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(text_L, 10, 232);

    lv_obj_t * text_R = lv_label_create(Tela_Main);
    lv_obj_set_width(text_R, LV_SIZE_CONTENT);
    lv_obj_set_height(text_R, LV_SIZE_CONTENT);
    lv_label_set_text(text_R, "R");
    lv_obj_set_style_text_color(text_R, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(text_R, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(text_R, &Neue_Medium_20, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(text_R, 10, 262);
}

void create_tuned(void)
{
	// TUNED Symbol
	lv_obj_t * img_tuned = lv_img_create(Tela_Main);
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

void create_stereo(void)
{
	// STEREO Symbol
	lv_obj_t * img_stereo = lv_img_create(Tela_Main);
	lv_img_set_src(img_stereo, "S:/MAIN/BT_STEREO.bin");
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

void create_rds(void)
{
	// RDS Symbol
	lv_obj_t * img_rds = lv_img_create(Tela_Main);
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
    lv_obj_align_to(text_rds, img_rds, LV_ALIGN_CENTER, 0, 0);
}

void create_buttons_tunner(void)
{
    // Button PREV
    bt_rev = lv_imagebutton_create(Tela_Main);
    lv_imagebutton_set_src(bt_rev, LV_IMAGEBUTTON_STATE_RELEASED, NULL, "S:/MAIN/BT_RR.bin", NULL);
    lv_imagebutton_set_src(bt_rev, LV_IMAGEBUTTON_STATE_PRESSED, NULL, "S:/MAIN/BT_RR_P.bin", NULL);
    lv_imagebutton_set_src(bt_rev, LV_IMAGEBUTTON_STATE_DISABLED, NULL, "S:/MAIN/BT_RR.bin", NULL);
    lv_imagebutton_set_src(bt_rev, LV_IMAGEBUTTON_STATE_CHECKED_PRESSED, NULL, "S:/MAIN/BT_RR_P.bin", NULL);
    lv_imagebutton_set_src(bt_rev, LV_IMAGEBUTTON_STATE_CHECKED_RELEASED, NULL, "S:/MAIN/BT_RR.bin", NULL);
    lv_imagebutton_set_src(bt_rev, LV_IMAGEBUTTON_STATE_CHECKED_DISABLED, NULL, "S:/MAIN/BT_RR.bin", NULL);
    lv_obj_add_state(bt_rev, LV_IMAGEBUTTON_STATE_RELEASED);
    lv_obj_set_pos(bt_rev, 384, 10);
    //lv_obj_add_event_cb(bt_rev, event_utils_bt_back, LV_EVENT_ALL, NULL);

    // Button NEXT
    bt_next = lv_imagebutton_create(Tela_Main);
    lv_imagebutton_set_src(bt_next, LV_IMAGEBUTTON_STATE_RELEASED, NULL, "S:/MAIN/BT_FW.bin", NULL);
    lv_imagebutton_set_src(bt_next, LV_IMAGEBUTTON_STATE_PRESSED, NULL, "S:/MAIN/BT_FW_P.bin", NULL);
    lv_imagebutton_set_src(bt_next, LV_IMAGEBUTTON_STATE_DISABLED, NULL, "S:/MAIN/BT_FW.bin", NULL);
    lv_imagebutton_set_src(bt_next, LV_IMAGEBUTTON_STATE_CHECKED_PRESSED, NULL, "S:/MAIN/BT_FW_P.bin", NULL);
    lv_imagebutton_set_src(bt_next, LV_IMAGEBUTTON_STATE_CHECKED_RELEASED, NULL, "S:/MAIN/BT_FW.bin", NULL);
    lv_imagebutton_set_src(bt_next, LV_IMAGEBUTTON_STATE_CHECKED_DISABLED, NULL, "S:/MAIN/BT_FW.bin", NULL);
    lv_obj_add_state(bt_next, LV_IMAGEBUTTON_STATE_RELEASED);
    lv_obj_set_pos(bt_next, 432, 10);
    //lv_obj_add_event_cb(bt_next, event_utils_bt_back, LV_EVENT_ALL, NULL);

    // Button REV FF
    bt_prevff = lv_imagebutton_create(Tela_Main);
    lv_imagebutton_set_src(bt_prevff, LV_IMAGEBUTTON_STATE_RELEASED, NULL, "S:/MAIN/BT_RW.bin", NULL);
    lv_imagebutton_set_src(bt_prevff, LV_IMAGEBUTTON_STATE_PRESSED, NULL, "S:/MAIN/BT_RW_P.bin", NULL);
    lv_imagebutton_set_src(bt_prevff, LV_IMAGEBUTTON_STATE_DISABLED, NULL, "S:/MAIN/BT_RW.bin", NULL);
    lv_imagebutton_set_src(bt_prevff, LV_IMAGEBUTTON_STATE_CHECKED_PRESSED, NULL, "S:/MAIN/BT_RW_P.bin", NULL);
    lv_imagebutton_set_src(bt_prevff, LV_IMAGEBUTTON_STATE_CHECKED_RELEASED, NULL, "S:/MAIN/BT_RW.bin", NULL);
    lv_imagebutton_set_src(bt_prevff, LV_IMAGEBUTTON_STATE_CHECKED_DISABLED, NULL, "S:/MAIN/BT_RW.bin", NULL);
    lv_obj_add_state(bt_prevff, LV_IMAGEBUTTON_STATE_RELEASED);
    lv_obj_set_pos(bt_prevff, 384, 50);
    //lv_obj_add_event_cb(bt_prevff, event_utils_bt_back, LV_EVENT_ALL, NULL);

    // Button REV FF
    bt_nextff = lv_imagebutton_create(Tela_Main);
    lv_imagebutton_set_src(bt_nextff, LV_IMAGEBUTTON_STATE_RELEASED, NULL, "S:/MAIN/BT_FF.bin", NULL);
    lv_imagebutton_set_src(bt_nextff, LV_IMAGEBUTTON_STATE_PRESSED, NULL, "S:/MAIN/BT_FF_P.bin", NULL);
    lv_imagebutton_set_src(bt_nextff, LV_IMAGEBUTTON_STATE_DISABLED, NULL, "S:/MAIN/BT_FF.bin", NULL);
    lv_imagebutton_set_src(bt_nextff, LV_IMAGEBUTTON_STATE_CHECKED_PRESSED, NULL, "S:/MAIN/BT_FF_P.bin", NULL);
    lv_imagebutton_set_src(bt_nextff, LV_IMAGEBUTTON_STATE_CHECKED_RELEASED, NULL, "S:/MAIN/BT_FF.bin", NULL);
    lv_imagebutton_set_src(bt_nextff, LV_IMAGEBUTTON_STATE_CHECKED_DISABLED, NULL, "S:/MAIN/BT_FF.bin", NULL);
    lv_obj_add_state(bt_nextff, LV_IMAGEBUTTON_STATE_RELEASED);
    lv_obj_set_pos(bt_nextff, 432, 50);
    //lv_obj_add_event_cb(bt_prevff, event_utils_bt_back, LV_EVENT_ALL, NULL);
}

void create_buttons_volume(void)
{
    // Button PREV
    bt_vol_inc = lv_imagebutton_create(Tela_Main);
    lv_imagebutton_set_src(bt_vol_inc, LV_IMAGEBUTTON_STATE_RELEASED, NULL, "S:/MAIN/BT_INC.bin", NULL);
    lv_imagebutton_set_src(bt_vol_inc, LV_IMAGEBUTTON_STATE_PRESSED, NULL, "S:/MAIN/BT_INC_P.bin", NULL);
    lv_imagebutton_set_src(bt_vol_inc, LV_IMAGEBUTTON_STATE_DISABLED, NULL, "S:/MAIN/BT_INC.bin", NULL);
    lv_imagebutton_set_src(bt_vol_inc, LV_IMAGEBUTTON_STATE_CHECKED_PRESSED, NULL, "S:/MAIN/BT_INC_P.bin", NULL);
    lv_imagebutton_set_src(bt_vol_inc, LV_IMAGEBUTTON_STATE_CHECKED_RELEASED, NULL, "S:/MAIN/BT_INC.bin", NULL);
    lv_imagebutton_set_src(bt_vol_inc, LV_IMAGEBUTTON_STATE_CHECKED_DISABLED, NULL, "S:/MAIN/BT_INC.bin", NULL);
    lv_obj_add_state(bt_vol_inc, LV_IMAGEBUTTON_STATE_RELEASED);
    lv_obj_set_pos(bt_vol_inc, 384, 185);
    //lv_obj_add_event_cb(bt_rev, event_utils_bt_back, LV_EVENT_ALL, NULL);

    // Button NEXT
    bt_vol_dec = lv_imagebutton_create(Tela_Main);
    lv_imagebutton_set_src(bt_vol_dec, LV_IMAGEBUTTON_STATE_RELEASED, NULL, "S:/MAIN/BT_DEC.bin", NULL);
    lv_imagebutton_set_src(bt_vol_dec, LV_IMAGEBUTTON_STATE_PRESSED, NULL, "S:/MAIN/BT_DEC_P.bin", NULL);
    lv_imagebutton_set_src(bt_vol_dec, LV_IMAGEBUTTON_STATE_DISABLED, NULL, "S:/MAIN/BT_DEC.bin", NULL);
    lv_imagebutton_set_src(bt_vol_dec, LV_IMAGEBUTTON_STATE_CHECKED_PRESSED, NULL, "S:/MAIN/BT_DEC_P.bin", NULL);
    lv_imagebutton_set_src(bt_vol_dec, LV_IMAGEBUTTON_STATE_CHECKED_RELEASED, NULL, "S:/MAIN/BT_DEC.bin", NULL);
    lv_imagebutton_set_src(bt_vol_dec, LV_IMAGEBUTTON_STATE_CHECKED_DISABLED, NULL, "S:/MAIN/BT_DEC.bin", NULL);
    lv_obj_add_state(bt_vol_dec, LV_IMAGEBUTTON_STATE_RELEASED);
    lv_obj_set_pos(bt_vol_dec, 432, 185);
    //lv_obj_add_event_cb(bt_vol_dec, event_utils_bt_back, LV_EVENT_ALL, NULL);
}

void create_buttons_menu_1(void)
{
    // Button INPUTS
    bt_inputs = lv_imagebutton_create(Tela_Main);
    lv_imagebutton_set_src(bt_inputs, LV_IMAGEBUTTON_STATE_RELEASED, NULL, "S:/MAIN/BT_INPUT.bin", NULL);
    lv_imagebutton_set_src(bt_inputs, LV_IMAGEBUTTON_STATE_PRESSED, NULL, "S:/MAIN/BT_INPUT_P.bin", NULL);
    lv_imagebutton_set_src(bt_inputs, LV_IMAGEBUTTON_STATE_DISABLED, NULL, "S:/MAIN/BT_INPUT.bin", NULL);
    lv_imagebutton_set_src(bt_inputs, LV_IMAGEBUTTON_STATE_CHECKED_PRESSED, NULL, "S:/MAIN/BT_INPUT_P.bin", NULL);
    lv_imagebutton_set_src(bt_inputs, LV_IMAGEBUTTON_STATE_CHECKED_RELEASED, NULL, "S:/MAIN/BT_INPUT.bin", NULL);
    lv_imagebutton_set_src(bt_inputs, LV_IMAGEBUTTON_STATE_CHECKED_DISABLED, NULL, "S:/MAIN/BT_INPUT.bin", NULL);
    lv_obj_add_state(bt_inputs, LV_IMAGEBUTTON_STATE_RELEASED);
    lv_obj_set_pos(bt_inputs, 2, 93);
    //lv_obj_add_event_cb(bt_inputs, event_utils_bt_back, LV_EVENT_ALL, NULL);

	// Text
    lv_obj_t * text_inputs = lv_label_create(bt_inputs);
    lv_obj_set_width(text_inputs, LV_SIZE_CONTENT);
    lv_obj_set_height(text_inputs, LV_SIZE_CONTENT);
    lv_label_set_text(text_inputs, "INPUTS");
    lv_obj_set_style_text_color(text_inputs, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(text_inputs, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(text_inputs, &Neue_Medium_16, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_align_to(text_inputs, bt_inputs, LV_ALIGN_CENTER, 0, 0);

    // Button OUTPUTS
    bt_outputs = lv_imagebutton_create(Tela_Main);
    lv_imagebutton_set_src(bt_outputs, LV_IMAGEBUTTON_STATE_RELEASED, NULL, "S:/MAIN/BT_INPUT.bin", NULL);
    lv_imagebutton_set_src(bt_outputs, LV_IMAGEBUTTON_STATE_PRESSED, NULL, "S:/MAIN/BT_INPUT_P.bin", NULL);
    lv_imagebutton_set_src(bt_outputs, LV_IMAGEBUTTON_STATE_DISABLED, NULL, "S:/MAIN/BT_INPUT.bin", NULL);
    lv_imagebutton_set_src(bt_outputs, LV_IMAGEBUTTON_STATE_CHECKED_PRESSED, NULL, "S:/MAIN/BT_INPUT_P.bin", NULL);
    lv_imagebutton_set_src(bt_outputs, LV_IMAGEBUTTON_STATE_CHECKED_RELEASED, NULL, "S:/MAIN/BT_INPUT.bin", NULL);
    lv_imagebutton_set_src(bt_outputs, LV_IMAGEBUTTON_STATE_CHECKED_DISABLED, NULL, "S:/MAIN/BT_INPUT.bin", NULL);
    lv_obj_add_state(bt_outputs, LV_IMAGEBUTTON_STATE_RELEASED);
    lv_obj_set_pos(bt_outputs, 2, 134);
    //lv_obj_add_event_cb(bt_outputs, event_utils_bt_back, LV_EVENT_ALL, NULL);

	// Text
    lv_obj_t * text_outputs = lv_label_create(bt_outputs);
    lv_obj_set_width(text_outputs, LV_SIZE_CONTENT);
    lv_obj_set_height(text_outputs, LV_SIZE_CONTENT);
    lv_label_set_text(text_outputs, "OUTPUTS");
    lv_obj_set_style_text_color(text_outputs, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(text_outputs, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(text_outputs, &Neue_Medium_16, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_align_to(text_outputs, bt_outputs, LV_ALIGN_CENTER, 0, 0);

    // Button Configs
    bt_configs = lv_imagebutton_create(Tela_Main);
    lv_imagebutton_set_src(bt_configs, LV_IMAGEBUTTON_STATE_RELEASED, NULL, "S:/MAIN/BT_INPUT.bin", NULL);
    lv_imagebutton_set_src(bt_configs, LV_IMAGEBUTTON_STATE_PRESSED, NULL, "S:/MAIN/BT_INPUT_P.bin", NULL);
    lv_imagebutton_set_src(bt_configs, LV_IMAGEBUTTON_STATE_DISABLED, NULL, "S:/MAIN/BT_INPUT.bin", NULL);
    lv_imagebutton_set_src(bt_configs, LV_IMAGEBUTTON_STATE_CHECKED_PRESSED, NULL, "S:/MAIN/BT_INPUT_P.bin", NULL);
    lv_imagebutton_set_src(bt_configs, LV_IMAGEBUTTON_STATE_CHECKED_RELEASED, NULL, "S:/MAIN/BT_INPUT.bin", NULL);
    lv_imagebutton_set_src(bt_configs, LV_IMAGEBUTTON_STATE_CHECKED_DISABLED, NULL, "S:/MAIN/BT_INPUT.bin", NULL);
    lv_obj_add_state(bt_configs, LV_IMAGEBUTTON_STATE_RELEASED);
    lv_obj_set_pos(bt_configs, 2, 175);
    //lv_obj_add_event_cb(bt_configs, event_utils_bt_back, LV_EVENT_ALL, NULL);

	// Text
    lv_obj_t * text_configs = lv_label_create(bt_configs);
    lv_obj_set_width(text_configs, LV_SIZE_CONTENT);
    lv_obj_set_height(text_configs, LV_SIZE_CONTENT);
    lv_label_set_text(text_configs, "CONFIGS");
    lv_obj_set_style_text_color(text_configs, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(text_configs, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(text_configs, &Neue_Medium_16, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_align_to(text_configs, bt_configs, LV_ALIGN_CENTER, 0, 0);
}

void create_buttons_menu_2(void)
{
    // Menu
	// Button USB_PC_FM
	for(uint8_t x = 0; x < 5; x++) {
		bt_menu[x] = lv_imagebutton_create(Tela_Main);
		lv_imagebutton_set_src(bt_menu[x], LV_IMAGEBUTTON_STATE_RELEASED, NULL, "S:/MAIN/BT_MENU.bin", NULL);
		lv_imagebutton_set_src(bt_menu[x], LV_IMAGEBUTTON_STATE_PRESSED, NULL, "S:/MAIN/BT_MENU_P.bin", NULL);
		lv_imagebutton_set_src(bt_menu[x], LV_IMAGEBUTTON_STATE_DISABLED, NULL, "S:/MAIN/BT_MENU.bin", NULL);
		lv_imagebutton_set_src(bt_menu[x], LV_IMAGEBUTTON_STATE_CHECKED_PRESSED, NULL, "S:/MAIN/BT_MENU_P.bin", NULL);
		lv_imagebutton_set_src(bt_menu[x], LV_IMAGEBUTTON_STATE_CHECKED_RELEASED, NULL, "S:/MAIN/BT_MENU.bin", NULL);
		lv_imagebutton_set_src(bt_menu[x], LV_IMAGEBUTTON_STATE_CHECKED_DISABLED, NULL, "S:/MAIN/BT_MENU.bin", NULL);
		lv_obj_add_state(bt_menu[x], LV_IMAGEBUTTON_STATE_RELEASED);
		//lv_obj_add_event_cb(bt_menu[x], event_utils_bt_back, LV_EVENT_ALL, NULL);
	}
	// Pos
	lv_obj_set_pos(bt_menu[0], 2, 286);
	lv_obj_set_pos(bt_menu[1], 97, 286);
	lv_obj_set_pos(bt_menu[2], 192, 286);
	lv_obj_set_pos(bt_menu[3], 288, 286);
	lv_obj_set_pos(bt_menu[4], 384, 286);

	// Text
    lv_obj_t * text_menu_0 = lv_label_create(bt_menu[0]);
    lv_obj_set_width(text_menu_0, LV_SIZE_CONTENT);
    lv_obj_set_height(text_menu_0, LV_SIZE_CONTENT);
    lv_label_set_text(text_menu_0, "USB PC FM");
    lv_obj_set_style_text_color(text_menu_0, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(text_menu_0, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(text_menu_0, &Neue_Medium_16, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_align_to(text_menu_0, bt_menu[0], LV_ALIGN_CENTER, 0, 1);

    lv_obj_t * text_menu_1 = lv_label_create(bt_menu[1]);
    lv_obj_set_width(text_menu_1, LV_SIZE_CONTENT);
    lv_obj_set_height(text_menu_1, LV_SIZE_CONTENT);
    lv_label_set_text(text_menu_1, "PC ADC/DAC");
    lv_obj_set_style_text_color(text_menu_1, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(text_menu_1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(text_menu_1, &Neue_Medium_14, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_align_to(text_menu_1, bt_menu[1], LV_ALIGN_CENTER, 0, 1);

    lv_obj_t * text_menu_2 = lv_label_create(bt_menu[2]);
    lv_obj_set_width(text_menu_2, LV_SIZE_CONTENT);
    lv_obj_set_height(text_menu_2, LV_SIZE_CONTENT);
    lv_label_set_text(text_menu_2, "PROCESSOR");
    lv_obj_set_style_text_color(text_menu_2, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(text_menu_2, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(text_menu_2, &Neue_Medium_14, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_align_to(text_menu_2, bt_menu[2], LV_ALIGN_CENTER, 0, 1);

    lv_obj_t * text_menu_3 = lv_label_create(bt_menu[3]);
    lv_obj_set_width(text_menu_3, LV_SIZE_CONTENT);
    lv_obj_set_height(text_menu_3, LV_SIZE_CONTENT);
    lv_label_set_text(text_menu_3, "MP3 B/T");
    lv_obj_set_style_text_color(text_menu_3, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(text_menu_3, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(text_menu_3, &Neue_Medium_14, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_align_to(text_menu_3, bt_menu[3], LV_ALIGN_CENTER, 0, 1);

    lv_obj_t * text_menu_4 = lv_label_create(bt_menu[4]);
    lv_obj_set_width(text_menu_4, LV_SIZE_CONTENT);
    lv_obj_set_height(text_menu_4, LV_SIZE_CONTENT);
    lv_label_set_text(text_menu_4, "FM TUNER");
    lv_obj_set_style_text_color(text_menu_4, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(text_menu_4, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(text_menu_4, &Neue_Medium_14, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_align_to(text_menu_4, bt_menu[4], LV_ALIGN_CENTER, 0, 1);
}

void create_vumeter_left(void)
{
	 // VU-Meter
	vu_left = lv_slider_create(Tela_Main);
	lv_obj_clear_flag(vu_left, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLLABLE);
	lv_slider_set_range(vu_left, 0, 64);
	lv_obj_set_width(vu_left, 445);
	lv_obj_set_height(vu_left, 28);
	lv_obj_set_pos(vu_left, 31, 229);

	lv_obj_set_style_radius(vu_left, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(vu_left, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(vu_left, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_main_stop(vu_left, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_stop(vu_left, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(vu_left, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(vu_left, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(vu_left, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(vu_left, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(vu_left, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_img_src(vu_left, &LED_GR_OFF, LV_PART_MAIN | LV_STATE_DEFAULT);

	lv_obj_set_style_radius(vu_left, 4, LV_PART_INDICATOR | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(vu_left, lv_color_hex(0xFFFFFF), LV_PART_INDICATOR | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(vu_left, 0, LV_PART_INDICATOR | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_main_stop(vu_left, 0, LV_PART_INDICATOR | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_stop(vu_left, 255, LV_PART_INDICATOR | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_img_src(vu_left, &LED_GR, LV_PART_INDICATOR | LV_STATE_DEFAULT);

	lv_obj_set_style_bg_color(vu_left, lv_color_hex(0xFFFFFF), LV_PART_KNOB | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(vu_left, 0, LV_PART_KNOB | LV_STATE_DEFAULT);

	lv_slider_set_value(vu_left, 0, LV_ANIM_OFF);
}

void create_Label_RDS(void)
{
    label_rds = lv_label_create(Tela_Main);
    lv_obj_set_width(label_rds, 280);
    lv_obj_set_height(label_rds, LV_SIZE_CONTENT);
    lv_label_set_text(label_rds, "AS MELHORES DA PROGRAMACAO");
    //lv_label_set_long_mode(label_rds, LV_LABEL_LONG_SCROLL_CIRCULAR);
    lv_obj_set_style_text_color(label_rds, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(label_rds, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(label_rds, &Neue_Medium_16, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(label_rds, 40, 12);
}

void create_Label_Frequency(void)
{
    label_frequency = lv_label_create(Tela_Main);
    lv_obj_set_width(label_frequency, LV_SIZE_CONTENT);
    lv_obj_set_height(label_frequency, LV_SIZE_CONTENT);
    lv_obj_set_style_text_letter_space(label_frequency, 0, 1);
    lv_obj_set_style_text_line_space(label_frequency, 0, 1);
    lv_label_set_text(label_frequency, "104.100 MHz");
    lv_obj_set_style_text_color(label_frequency, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(label_frequency, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(label_frequency, &Neue_Medium_52, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(label_frequency, 12, 34);
}

void create_text_audio_source(void)
{
    lv_obj_t * text_audio_source = lv_label_create(Tela_Main);
    lv_obj_set_width(text_audio_source, LV_SIZE_CONTENT);
    lv_obj_set_height(text_audio_source, LV_SIZE_CONTENT);
    lv_obj_set_style_text_letter_space(text_audio_source, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(text_audio_source, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_label_set_text(text_audio_source, "AUDIO SOURCE - INPUTS");
    lv_obj_set_style_text_color(text_audio_source, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(text_audio_source, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(text_audio_source, &Neue_Medium_11, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(text_audio_source, 161, 97);

    lv_obj_t * text_audio_mpx = lv_label_create(Tela_Main);
    lv_obj_set_width(text_audio_mpx, LV_SIZE_CONTENT);
    lv_obj_set_height(text_audio_mpx, LV_SIZE_CONTENT);
    lv_obj_set_style_text_letter_space(text_audio_mpx, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(text_audio_mpx, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_label_set_text(text_audio_mpx, "MPX OUT");
    lv_obj_set_style_text_color(text_audio_mpx, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(text_audio_mpx, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(text_audio_mpx, &Neue_Medium_11, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(text_audio_mpx, 328, 97);

    /*Create style*/
    static lv_style_t style_line;
    lv_style_init(&style_line);
    lv_style_set_line_width(&style_line, 1);
    lv_style_set_line_color(&style_line, lv_color_hex(0xFFFFFF));
    lv_style_set_line_rounded(&style_line, true);

    /*Create an array for the points of the line*/
    static lv_point_precise_t line_points1[] = { {0, 0}, {44, 0} };
    static lv_point_precise_t line_points2[] = { {0, 0}, {22, 0} };

    /*Create a line and apply the new style*/
    lv_obj_t * line1;
    line1 = lv_line_create(Tela_Main);
    lv_line_set_points(line1, line_points1, 2);     /*Set the points*/
    lv_obj_add_style(line1, &style_line, 0);
    lv_obj_set_pos(line1, 108, 103);
    //
    lv_obj_t * line2;
    line2 = lv_line_create(Tela_Main);
    lv_line_set_points(line2, line_points2, 2);     /*Set the points*/
    lv_obj_add_style(line2, &style_line, 0);
    lv_obj_set_pos(line2, 300, 103);

}

void create_text_scale_vu(void)
{
	for(uint8_t x = 0; x < 8; x++) {
		label_scale[x] = lv_label_create(Tela_Main);
		lv_obj_set_width(label_scale[x], LV_SIZE_CONTENT);
		lv_obj_set_height(label_scale[x], LV_SIZE_CONTENT);
		lv_obj_set_style_text_letter_space(label_scale[x], 0, LV_PART_MAIN | LV_STATE_DEFAULT);
		lv_obj_set_style_text_line_space(label_scale[x], 0, LV_PART_MAIN | LV_STATE_DEFAULT);
		lv_obj_set_style_text_color(label_scale[x], lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
		lv_obj_set_style_text_opa(label_scale[x], 255, LV_PART_MAIN | LV_STATE_DEFAULT);
		lv_obj_set_style_text_font(label_scale[x], &Neue_Medium_11, LV_PART_MAIN | LV_STATE_DEFAULT);
	}
	lv_label_set_text(label_scale[0], "-60");
	lv_label_set_text(label_scale[1], "-50");
	lv_label_set_text(label_scale[2], "-40");
	lv_label_set_text(label_scale[3], "-30");
	lv_label_set_text(label_scale[4], "-20");
	lv_label_set_text(label_scale[5], "-10");
	lv_label_set_text(label_scale[6], "0dB");
	lv_label_set_text(label_scale[7], "10dB>");

	lv_obj_set_pos(label_scale[0], 16, 216);
	lv_obj_set_pos(label_scale[1], 50, 216);
	lv_obj_set_pos(label_scale[2], 90, 216);
	lv_obj_set_pos(label_scale[3], 150, 216);
	lv_obj_set_pos(label_scale[4], 190, 216);
	lv_obj_set_pos(label_scale[5], 250, 216);
	lv_obj_set_pos(label_scale[6], 300, 216);
	lv_obj_set_pos(label_scale[7], 380, 216);
}
