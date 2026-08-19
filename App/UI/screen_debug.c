/*
 * screen_debug.c
 *
 *  Created on: 14 de jul. de 2026
 *      Author: rinaldo.santos
 */

#include "main.h"
#include "lvgl.h"
#include "../App/UI/screen_dac.h"
#include "../App/UI/screen_debug.h"
#include "../App/UI/screen_gpio.h"
#include "../App/UI/screen_mp3.h"
#include "../App/UI/screen_tuner.h"

void update_debug_screen(lv_timer_t * timer);
void Vol_in_XLR(void);
void Vol_out_XLR(void);
void Vol_MPX(void);
void Vol_Digital(void);

extern lv_obj_t * Tela_Gpio;
extern lv_obj_t * Tela_DAC;
extern lv_obj_t * Tela_MP3;
extern lv_obj_t * Tela_Tuner;

lv_obj_t * Tela_Debug;
//static lv_obj_t * img_fundo;
static lv_obj_t * spinbox_left;
static lv_obj_t * spinbox_right;

static lv_obj_t * spinbox_out_left;
static lv_obj_t * spinbox_out_right;

static lv_obj_t * spinbox_mpx1;
static lv_obj_t * spinbox_mpx2;
static lv_obj_t * spinbox_digital;
static lv_obj_t * spinbox_phone;

//static lv_timer_t * task_Debug;

void screen_debug(void)
{
	Tela_Debug = lv_obj_create(NULL);
	lv_obj_clear_flag(Tela_Debug, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLLABLE);
	lv_obj_set_style_bg_color(Tela_Debug, lv_color_hex(0x000000), 0);
	lv_obj_set_style_bg_grad_color(Tela_Debug, lv_color_hex(0x000000), 0);

	// Imagem de Fundo
//	img_fundo = lv_img_create(Tela_Debug);
//	lv_img_set_src(img_fundo, &TELA_TUNNER_1);
//	//  lv_obj_set_width(img_fundo, 480);
//	//  lv_obj_set_height(img_fundo, 128);
//	  //lv_obj_set_protect(img_fundo, LV_PROTECT_POS);
//	  lv_obj_set_pos(img_fundo, 0, 0);
//	  //lv_obj_align(img_fundo, LV_ALIGN_CENTER, 0, 0);

//	 static lv_style_t style_txt;
//	 lv_style_init(&style_txt);
//	 lv_style_set_text_font(&style_txt, &Helvetica_12);
//	 lv_style_set_text_color(&style_txt, lv_color_hex(0xFFFFFF)); // Red text
//
//	  lv_obj_t * label1 = lv_label_create(Tela_Debug);
//	  lv_label_set_long_mode(label1, LV_LABEL_LONG_WRAP);     /*Break the long lines*/
//	  lv_label_set_recolor(label1, true);                      /*Enable re-coloring by commands in the text*/
//	  lv_label_set_text(label1, "MEMORY BANK / SET:");
//	  lv_obj_add_style(label1, &style_txt, LV_PART_MAIN);
//	  lv_obj_set_pos(label1, 180, 90);
//
//	  lv_obj_t * label2 = lv_label_create(Tela_Debug);
//	  lv_label_set_long_mode(label2, LV_LABEL_LONG_WRAP);     /*Break the long lines*/
//	  lv_label_set_recolor(label2, true);                      /*Enable re-coloring by commands in the text*/
//	  lv_label_set_text(label2, "50");
//	  lv_obj_add_style(label2, &style_txt, LV_PART_MAIN);
//	  lv_obj_set_pos(label2, 130, 213);


	// Widgets
	Vol_in_XLR();
	Vol_out_XLR();
	Vol_Digital();
	Vol_MPX();

	Button_Menu(Tela_Debug);

	 lv_scr_load(Tela_Debug);

	 LV_LOG_USER("Tela_Debug Start\n");
}

void update_debug_screen(lv_timer_t * timer)
{


}

static void lv_spinbox_left_increment_event_cb(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);
    if(code == LV_EVENT_SHORT_CLICKED || code  == LV_EVENT_LONG_PRESSED_REPEAT) {
        lv_spinbox_increment(spinbox_left);
    }
}

static void lv_spinbox_left_decrement_event_cb(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);
    if(code == LV_EVENT_SHORT_CLICKED || code == LV_EVENT_LONG_PRESSED_REPEAT) {
        lv_spinbox_decrement(spinbox_left);
    }
}

static void lv_spinbox_right_increment_event_cb(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);
    if(code == LV_EVENT_SHORT_CLICKED || code  == LV_EVENT_LONG_PRESSED_REPEAT) {
        lv_spinbox_increment(spinbox_right);
    }
}

static void lv_spinbox_right_decrement_event_cb(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);
    if(code == LV_EVENT_SHORT_CLICKED || code == LV_EVENT_LONG_PRESSED_REPEAT) {
        lv_spinbox_decrement(spinbox_right);
    }
}

void Vol_in_XLR(void)
{
	static lv_style_t style_symbol;
	lv_style_init(&style_symbol);
	lv_style_set_text_font(&style_symbol, &lv_font_montserrat_16);
	lv_style_set_text_color(&style_symbol, lv_color_hex(0xFFFFFF));

    // XLR IN LEFT
    lv_obj_t * label1 = lv_label_create(Tela_Debug);
    lv_label_set_long_mode(label1, LV_LABEL_LONG_WRAP);     	/*Break the long lines*/
    lv_label_set_recolor(label1, true);                      	/*Enable re-coloring by commands in the text*/
    lv_label_set_text(label1, "#FFFFFF XLR INPUT:");
    lv_obj_align_to(label1, Tela_Debug, LV_ALIGN_TOP_MID, 0, 10);

    spinbox_left = lv_spinbox_create(Tela_Debug);
    lv_spinbox_set_range(spinbox_left, 0, 72);
    lv_spinbox_set_digit_format(spinbox_left, 3, 0);
    lv_spinbox_set_cursor_pos(spinbox_left, 0);
    lv_spinbox_set_step(spinbox_left, 1);
    lv_spinbox_set_value(spinbox_left, 0);
    lv_obj_set_width(spinbox_left, 64);
    lv_obj_set_pos(spinbox_left, 80, 24);

    lv_coord_t h = lv_obj_get_height(spinbox_left);

    lv_obj_t * btn_left_inc = lv_btn_create(Tela_Debug);
    lv_obj_set_size(btn_left_inc, h, h);
    lv_obj_align_to(btn_left_inc, spinbox_left, LV_ALIGN_OUT_RIGHT_MID, 5, 0);
    lv_obj_add_style(btn_left_inc, &style_symbol, LV_PART_MAIN);
    lv_obj_set_style_bg_img_src(btn_left_inc, LV_SYMBOL_PLUS, 0);
    lv_obj_add_event_cb(btn_left_inc, lv_spinbox_left_increment_event_cb, LV_EVENT_ALL,  NULL);

    lv_obj_t * btn_left_dec = lv_btn_create(Tela_Debug);
    lv_obj_set_size(btn_left_dec, h, h);
    lv_obj_align_to(btn_left_dec, spinbox_left, LV_ALIGN_OUT_LEFT_MID, -5, 0);
    lv_obj_add_style(btn_left_dec, &style_symbol, LV_PART_MAIN);
    lv_obj_set_style_bg_img_src(btn_left_dec, LV_SYMBOL_MINUS, 0);
    lv_obj_add_event_cb(btn_left_dec, lv_spinbox_left_decrement_event_cb, LV_EVENT_ALL, NULL);

    // XLR IN RIGHT
	spinbox_right = lv_spinbox_create(Tela_Debug);
	//lv_obj_add_style(spinbox_right, &style_spin, LV_PART_MAIN);
    lv_spinbox_set_range(spinbox_right, 0, 72);
    lv_spinbox_set_digit_format(spinbox_right, 3, 0);
    lv_spinbox_set_cursor_pos(spinbox_right, 0);
    lv_spinbox_set_step(spinbox_right, 1);
    lv_spinbox_set_value(spinbox_right, 0);
    lv_obj_set_width(spinbox_right, 64);
    lv_obj_set_pos(spinbox_right, 350, 24);

    lv_coord_t h_r = lv_obj_get_height(spinbox_right);

    lv_obj_t * btn_right_inc = lv_btn_create(Tela_Debug);
    lv_obj_set_size(btn_right_inc, h_r, h_r);
    lv_obj_align_to(btn_right_inc, spinbox_right, LV_ALIGN_OUT_RIGHT_MID, 5, 0);
    lv_obj_add_style(btn_right_inc, &style_symbol, LV_PART_MAIN);
    lv_obj_set_style_bg_img_src(btn_right_inc, LV_SYMBOL_PLUS, 0);
    lv_obj_add_event_cb(btn_right_inc, lv_spinbox_right_increment_event_cb, LV_EVENT_ALL,  NULL);

    lv_obj_t * btn_right_dec = lv_btn_create(Tela_Debug);
    lv_obj_set_size(btn_right_dec, h_r, h_r);
    lv_obj_align_to(btn_right_dec, spinbox_right, LV_ALIGN_OUT_LEFT_MID, -5, 0);
    lv_obj_add_style(btn_right_dec, &style_symbol, LV_PART_MAIN);
    lv_obj_set_style_bg_img_src(btn_right_dec, LV_SYMBOL_MINUS, 0);
    lv_obj_add_event_cb(btn_right_dec, lv_spinbox_right_decrement_event_cb, LV_EVENT_ALL, NULL);
}

static void lv_spinbox_out_left_increment_event_cb(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);
    if(code == LV_EVENT_SHORT_CLICKED || code  == LV_EVENT_LONG_PRESSED_REPEAT) {
        lv_spinbox_increment(spinbox_out_left);
    }
}

static void lv_spinbox_out_left_decrement_event_cb(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);
    if(code == LV_EVENT_SHORT_CLICKED || code == LV_EVENT_LONG_PRESSED_REPEAT) {
        lv_spinbox_decrement(spinbox_out_left);
    }
}

static void lv_spinbox_out_right_increment_event_cb(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);
    if(code == LV_EVENT_SHORT_CLICKED || code  == LV_EVENT_LONG_PRESSED_REPEAT) {
        lv_spinbox_increment(spinbox_out_right);
    }
}

static void lv_spinbox_out_right_decrement_event_cb(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);
    if(code == LV_EVENT_SHORT_CLICKED || code == LV_EVENT_LONG_PRESSED_REPEAT) {
        lv_spinbox_decrement(spinbox_out_right);
    }
}

void Vol_out_XLR(void)
{
	static lv_style_t style_symbol;
	lv_style_init(&style_symbol);
	lv_style_set_text_font(&style_symbol, &lv_font_montserrat_16);
	lv_style_set_text_color(&style_symbol, lv_color_hex(0xFFFFFF));

	// XLR OUT LEFT
    lv_obj_t * label3 = lv_label_create(Tela_Debug);
    lv_label_set_long_mode(label3, LV_LABEL_LONG_WRAP);     	/*Break the long lines*/
    lv_label_set_recolor(label3, true);                      	/*Enable re-coloring by commands in the text*/
    lv_label_set_text(label3, "#FFFFFF XLR OUTPUT:");
    lv_obj_align_to(label3, Tela_Debug, LV_ALIGN_TOP_MID, 2, 76);

    spinbox_out_left = lv_spinbox_create(Tela_Debug);
    lv_spinbox_set_range(spinbox_out_left, 0, 72);
    lv_spinbox_set_digit_format(spinbox_out_left, 3, 0);
    lv_spinbox_set_cursor_pos(spinbox_out_left, 0);
    lv_spinbox_set_step(spinbox_out_left, 1);
    lv_spinbox_set_value(spinbox_out_left, 0);
    lv_obj_set_width(spinbox_out_left, 64);
    lv_obj_set_pos(spinbox_out_left, 80, 88);

    lv_coord_t h = lv_obj_get_height(spinbox_out_left);

    lv_obj_t * btn_left_inc = lv_btn_create(Tela_Debug);
    lv_obj_set_size(btn_left_inc, h, h);
    lv_obj_align_to(btn_left_inc, spinbox_out_left, LV_ALIGN_OUT_RIGHT_MID, 5, 0);
    lv_obj_add_style(btn_left_inc, &style_symbol, LV_PART_MAIN);
    lv_obj_set_style_bg_img_src(btn_left_inc, LV_SYMBOL_PLUS, 0);
    lv_obj_add_event_cb(btn_left_inc, lv_spinbox_out_left_increment_event_cb, LV_EVENT_ALL,  NULL);

    lv_obj_t * btn_left_dec = lv_btn_create(Tela_Debug);
    lv_obj_set_size(btn_left_dec, h, h);
    lv_obj_align_to(btn_left_dec, spinbox_out_left, LV_ALIGN_OUT_LEFT_MID, -5, 0);
    lv_obj_add_style(btn_left_dec, &style_symbol, LV_PART_MAIN);
    lv_obj_set_style_bg_img_src(btn_left_dec, LV_SYMBOL_MINUS, 0);
    lv_obj_add_event_cb(btn_left_dec, lv_spinbox_out_left_decrement_event_cb, LV_EVENT_ALL, NULL);

    // XLR OUT RIGHT
	spinbox_out_right = lv_spinbox_create(Tela_Debug);
    lv_spinbox_set_range(spinbox_out_right, 0, 72);
    lv_spinbox_set_digit_format(spinbox_out_right, 3, 0);
    lv_spinbox_set_cursor_pos(spinbox_out_right, 0);
    lv_spinbox_set_step(spinbox_out_right, 1);
    lv_spinbox_set_value(spinbox_out_right, 0);
    lv_obj_set_width(spinbox_out_right, 64);
    lv_obj_set_pos(spinbox_out_right, 350, 88);

    lv_coord_t h_r = lv_obj_get_height(spinbox_out_right);

    lv_obj_t * btn_right_inc = lv_btn_create(Tela_Debug);
    lv_obj_set_size(btn_right_inc, h_r, h_r);
    lv_obj_align_to(btn_right_inc, spinbox_out_right, LV_ALIGN_OUT_RIGHT_MID, 5, 0);
    lv_obj_add_style(btn_right_inc, &style_symbol, LV_PART_MAIN);
    lv_obj_set_style_bg_img_src(btn_right_inc, LV_SYMBOL_PLUS, 0);
    lv_obj_add_event_cb(btn_right_inc, lv_spinbox_out_right_increment_event_cb, LV_EVENT_ALL,  NULL);

    lv_obj_t * btn_right_dec = lv_btn_create(Tela_Debug);
    lv_obj_set_size(btn_right_dec, h_r, h_r);
    lv_obj_align_to(btn_right_dec, spinbox_out_right, LV_ALIGN_OUT_LEFT_MID, -5, 0);
    lv_obj_add_style(btn_right_dec, &style_symbol, LV_PART_MAIN);
    lv_obj_set_style_bg_img_src(btn_right_dec, LV_SYMBOL_MINUS, 0);
    lv_obj_add_event_cb(btn_right_dec, lv_spinbox_out_right_decrement_event_cb, LV_EVENT_ALL, NULL);
}

static void lv_spinbox_mpx1_increment_event_cb(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);
    if(code == LV_EVENT_SHORT_CLICKED || code  == LV_EVENT_LONG_PRESSED_REPEAT) {
        lv_spinbox_increment(spinbox_mpx1);
    }
}

static void lv_spinbox_mpx1_decrement_event_cb(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);
    if(code == LV_EVENT_SHORT_CLICKED || code == LV_EVENT_LONG_PRESSED_REPEAT) {
        lv_spinbox_decrement(spinbox_mpx1);
    }
}

static void lv_spinbox_mpx2_increment_event_cb(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);
    if(code == LV_EVENT_SHORT_CLICKED || code  == LV_EVENT_LONG_PRESSED_REPEAT) {
        lv_spinbox_increment(spinbox_mpx2);
    }
}

static void lv_spinbox_mpx2_decrement_event_cb(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);
    if(code == LV_EVENT_SHORT_CLICKED || code == LV_EVENT_LONG_PRESSED_REPEAT) {
        lv_spinbox_decrement(spinbox_mpx2);
    }
}

void Vol_MPX(void)
{
	static lv_style_t style_symbol;
	lv_style_init(&style_symbol);
	lv_style_set_text_font(&style_symbol, &lv_font_montserrat_16);
	lv_style_set_text_color(&style_symbol, lv_color_hex(0xFFFFFF));

	// MPX1
    lv_obj_t * label4 = lv_label_create(Tela_Debug);
    lv_label_set_long_mode(label4, LV_LABEL_LONG_WRAP);     /*Break the long lines*/
    lv_label_set_recolor(label4, true);                      /*Enable re-coloring by commands in the text*/
    lv_label_set_text(label4, "#FFFFFF MPX OUTPUT:");
    lv_obj_align_to(label4, Tela_Debug, LV_ALIGN_TOP_MID, 4, 150);

    spinbox_mpx1 = lv_spinbox_create(Tela_Debug);
    lv_spinbox_set_range(spinbox_mpx1, 0, 72);
    lv_spinbox_set_digit_format(spinbox_mpx1, 3, 0);
    lv_spinbox_set_cursor_pos(spinbox_mpx1, 0);
    lv_spinbox_set_step(spinbox_mpx1, 1);
    lv_spinbox_set_value(spinbox_mpx1, 0);
    lv_obj_set_width(spinbox_mpx1, 64);
    lv_obj_set_pos(spinbox_mpx1, 80, 152);

    lv_coord_t h = lv_obj_get_height(spinbox_mpx1);

    lv_obj_t * btn_mpx1_inc = lv_btn_create(Tela_Debug);
    lv_obj_set_size(btn_mpx1_inc, h, h);
    lv_obj_align_to(btn_mpx1_inc, spinbox_mpx1, LV_ALIGN_OUT_RIGHT_MID, 5, 0);
    lv_obj_add_style(btn_mpx1_inc, &style_symbol, LV_PART_MAIN);
    lv_obj_set_style_bg_img_src(btn_mpx1_inc, LV_SYMBOL_PLUS, 0);
    lv_obj_add_event_cb(btn_mpx1_inc, lv_spinbox_mpx1_increment_event_cb, LV_EVENT_ALL,  NULL);

    lv_obj_t * btn_mpx1_dec = lv_btn_create(Tela_Debug);
    lv_obj_set_size(btn_mpx1_dec, h, h);
    lv_obj_align_to(btn_mpx1_dec, spinbox_mpx1, LV_ALIGN_OUT_LEFT_MID, -5, 0);
    lv_obj_add_style(btn_mpx1_dec, &style_symbol, LV_PART_MAIN);
    lv_obj_set_style_bg_img_src(btn_mpx1_dec, LV_SYMBOL_MINUS, 0);
    lv_obj_add_event_cb(btn_mpx1_dec, lv_spinbox_mpx1_decrement_event_cb, LV_EVENT_ALL, NULL);

    // MPX 2
	spinbox_mpx2 = lv_spinbox_create(Tela_Debug);
    lv_spinbox_set_range(spinbox_mpx2, 0, 72);
    lv_spinbox_set_digit_format(spinbox_mpx2, 3, 0);
    lv_spinbox_set_cursor_pos(spinbox_mpx2, 0);
    lv_spinbox_set_step(spinbox_mpx2, 1);
    lv_spinbox_set_value(spinbox_mpx2, 0);
    lv_obj_set_width(spinbox_mpx2, 64);
    lv_obj_set_pos(spinbox_mpx2, 350, 152);

    lv_coord_t h_r = lv_obj_get_height(spinbox_mpx2);

    lv_obj_t * btn_mpx2_inc = lv_btn_create(Tela_Debug);
    lv_obj_set_size(btn_mpx2_inc, h_r, h_r);
    lv_obj_align_to(btn_mpx2_inc, spinbox_mpx2, LV_ALIGN_OUT_RIGHT_MID, 5, 0);
    lv_obj_add_style(btn_mpx2_inc, &style_symbol, LV_PART_MAIN);
    lv_obj_set_style_bg_img_src(btn_mpx2_inc, LV_SYMBOL_PLUS, 0);
    lv_obj_add_event_cb(btn_mpx2_inc, lv_spinbox_mpx2_increment_event_cb, LV_EVENT_ALL,  NULL);

    lv_obj_t * btn_mpx2_dec = lv_btn_create(Tela_Debug);
    lv_obj_set_size(btn_mpx2_dec, h_r, h_r);
    lv_obj_align_to(btn_mpx2_dec, spinbox_mpx2, LV_ALIGN_OUT_LEFT_MID, -5, 0);
    lv_obj_add_style(btn_mpx2_dec, &style_symbol, LV_PART_MAIN);
    lv_obj_set_style_bg_img_src(btn_mpx2_dec, LV_SYMBOL_MINUS, 0);
    lv_obj_add_event_cb(btn_mpx2_dec, lv_spinbox_mpx2_decrement_event_cb, LV_EVENT_ALL, NULL);
}

static void lv_spinbox_digital_increment_event_cb(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);
    if(code == LV_EVENT_SHORT_CLICKED || code  == LV_EVENT_LONG_PRESSED_REPEAT) {
        lv_spinbox_increment(spinbox_digital);
    }
}

static void lv_spinbox_digital_decrement_event_cb(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);
    if(code == LV_EVENT_SHORT_CLICKED || code == LV_EVENT_LONG_PRESSED_REPEAT) {
        lv_spinbox_decrement(spinbox_digital);
    }
}

static void lv_spinbox_phone_increment_event_cb(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);
    if(code == LV_EVENT_SHORT_CLICKED || code  == LV_EVENT_LONG_PRESSED_REPEAT) {
        lv_spinbox_increment(spinbox_phone);
    }
}

static void lv_spinbox_phone_decrement_event_cb(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);
    if(code == LV_EVENT_SHORT_CLICKED || code == LV_EVENT_LONG_PRESSED_REPEAT) {
        lv_spinbox_decrement(spinbox_phone);
    }
}

void Vol_Digital(void)
{
	static lv_style_t style_symbol;
	lv_style_init(&style_symbol);
	lv_style_set_text_font(&style_symbol, &lv_font_montserrat_16);
	lv_style_set_text_color(&style_symbol, lv_color_hex(0xFFFFFF));

	// Digital
    lv_obj_t * label4 = lv_label_create(Tela_Debug);
    lv_label_set_long_mode(label4, LV_LABEL_LONG_WRAP);     /*Break the long lines*/
    lv_label_set_recolor(label4, true);                      /*Enable re-coloring by commands in the text*/
    lv_label_set_text(label4, "#FFFFFF DIGITAL / FONE:");
    lv_obj_align_to(label4, Tela_Debug, LV_ALIGN_TOP_MID, 7, 210);

    spinbox_digital = lv_spinbox_create(Tela_Debug);
    lv_spinbox_set_range(spinbox_digital, 0, 72);
    lv_spinbox_set_digit_format(spinbox_digital, 3, 0);
    lv_spinbox_set_cursor_pos(spinbox_digital, 0);
    lv_spinbox_set_step(spinbox_digital, 1);
    lv_spinbox_set_value(spinbox_digital, 0);
    lv_obj_set_width(spinbox_digital, 64);
    lv_obj_set_pos(spinbox_digital, 80, 216);

     lv_coord_t h = lv_obj_get_height(spinbox_digital);

     lv_obj_t * btn_digital_inc = lv_btn_create(Tela_Debug);
     lv_obj_set_size(btn_digital_inc, h, h);
     lv_obj_align_to(btn_digital_inc, spinbox_digital, LV_ALIGN_OUT_RIGHT_MID, 5, 0);
     lv_obj_add_style(btn_digital_inc, &style_symbol, LV_PART_MAIN);
     lv_obj_set_style_bg_img_src(btn_digital_inc, LV_SYMBOL_PLUS, 0);
     lv_obj_add_event_cb(btn_digital_inc, lv_spinbox_digital_increment_event_cb, LV_EVENT_ALL,  NULL);

     lv_obj_t * btn_digital_dec = lv_btn_create(Tela_Debug);
     lv_obj_set_size(btn_digital_dec, h, h);
     lv_obj_align_to(btn_digital_dec, spinbox_digital, LV_ALIGN_OUT_LEFT_MID, -5, 0);
     lv_obj_add_style(btn_digital_dec, &style_symbol, LV_PART_MAIN);
     lv_obj_set_style_bg_img_src(btn_digital_dec, LV_SYMBOL_MINUS, 0);
     lv_obj_add_event_cb(btn_digital_dec, lv_spinbox_digital_decrement_event_cb, LV_EVENT_ALL, NULL);

    // MPX 2
 	spinbox_phone = lv_spinbox_create(Tela_Debug);
    lv_spinbox_set_range(spinbox_phone, 0, 72);
    lv_spinbox_set_digit_format(spinbox_phone, 3, 0);
    lv_spinbox_set_cursor_pos(spinbox_phone, 0);
    lv_spinbox_set_step(spinbox_phone, 1);
    lv_spinbox_set_value(spinbox_phone, 0);
    lv_obj_set_width(spinbox_phone, 64);
    lv_obj_set_pos(spinbox_phone, 350, 216);

    lv_coord_t h_r = lv_obj_get_height(spinbox_phone);

    lv_obj_t * btn_phone_inc = lv_btn_create(Tela_Debug);
    lv_obj_set_size(btn_phone_inc, h_r, h_r);
    lv_obj_align_to(btn_phone_inc, spinbox_phone, LV_ALIGN_OUT_RIGHT_MID, 5, 0);
    lv_obj_add_style(btn_phone_inc, &style_symbol, LV_PART_MAIN);
    lv_obj_set_style_bg_img_src(btn_phone_inc, LV_SYMBOL_PLUS, 0);
    lv_obj_add_event_cb(btn_phone_inc, lv_spinbox_phone_increment_event_cb, LV_EVENT_ALL,  NULL);

    lv_obj_t * btn_phone_dec = lv_btn_create(Tela_Debug);
    lv_obj_set_size(btn_phone_dec, h_r, h_r);
    lv_obj_align_to(btn_phone_dec, spinbox_phone, LV_ALIGN_OUT_LEFT_MID, -5, 0);
    lv_obj_add_style(btn_phone_dec, &style_symbol, LV_PART_MAIN);
    lv_obj_set_style_bg_img_src(btn_phone_dec, LV_SYMBOL_MINUS, 0);
    lv_obj_add_event_cb(btn_phone_dec, lv_spinbox_phone_decrement_event_cb, LV_EVENT_ALL, NULL);
}

static void event_btn1_handler(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);

    if(code == LV_EVENT_CLICKED) {
        LV_LOG_USER("Clicked");

        lv_obj_delete( lv_screen_active());
        screen_debug();
    }
}

static void event_btn2_handler(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);

    if(code == LV_EVENT_CLICKED) {
        LV_LOG_USER("Clicked");

        lv_obj_delete( lv_screen_active());
        screen_gpio();
    }
}

static void event_btn3_handler(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);

    if(code == LV_EVENT_CLICKED) {
        LV_LOG_USER("Clicked");

        lv_obj_delete( lv_screen_active());
        screen_dac();
    }
}

static void event_btn4_handler(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);

    if(code == LV_EVENT_CLICKED) {
        LV_LOG_USER("Clicked");

        lv_obj_delete( lv_screen_active() );
        screen_mp3();
    }
}

static void event_btn5_handler(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);

    if(code == LV_EVENT_CLICKED) {
        LV_LOG_USER("Clicked");

        lv_obj_delete( lv_screen_active() );
        screen_tuner();
    }
}

void Button_Menu(lv_obj_t * tela)
{
    lv_obj_t * label1;
    lv_obj_t * label2;
    lv_obj_t * label3;
    lv_obj_t * label4;
    lv_obj_t * label5;

    // BTN Volume
    lv_obj_t * btn1 = lv_btn_create(tela);
    lv_obj_add_event_cb(btn1, event_btn1_handler, LV_EVENT_ALL, NULL);
    lv_obj_align_to(btn1, tela, LV_ALIGN_OUT_BOTTOM_LEFT, 20, -48);

    label1 = lv_label_create(btn1);
    lv_label_set_text(label1, "VOLUME");
    lv_obj_center(label1);

    // BTN GPIO
    lv_obj_t * btn2 = lv_btn_create(tela);
    lv_obj_add_event_cb(btn2, event_btn2_handler, LV_EVENT_ALL, NULL);
    lv_obj_align_to(btn2, tela, LV_ALIGN_OUT_BOTTOM_LEFT, 130, -48);

    label2 = lv_label_create(btn2);
    lv_label_set_text(label2, "GPIO");
    lv_obj_center(label2);

    // BTN DAC
    lv_obj_t * btn3 = lv_btn_create(tela);
    lv_obj_add_event_cb(btn3, event_btn3_handler, LV_EVENT_ALL, NULL);
    lv_obj_align_to(btn3, tela, LV_ALIGN_OUT_BOTTOM_MID, 0, -48);

    label3 = lv_label_create(btn3);
    lv_label_set_text(label3, "DAC");
    lv_obj_center(label3);

    // BTN MP3
    lv_obj_t * btn4 = lv_btn_create(tela);
    lv_obj_add_event_cb(btn4, event_btn4_handler, LV_EVENT_ALL, NULL);
    lv_obj_align_to(btn4, tela, LV_ALIGN_OUT_BOTTOM_RIGHT, -140, -48);

    label4 = lv_label_create(btn4);
    lv_label_set_text(label4, "MP3");
    lv_obj_center(label4);

    // BTN TUNER
    lv_obj_t * btn5 = lv_btn_create(tela);
    lv_obj_add_event_cb(btn5, event_btn5_handler, LV_EVENT_ALL, NULL);
    lv_obj_align_to(btn5, tela, LV_ALIGN_OUT_BOTTOM_RIGHT, -60, -48);

    label5 = lv_label_create(btn5);
    lv_label_set_text(label5, "TUNER");
    lv_obj_center(label5);
}
