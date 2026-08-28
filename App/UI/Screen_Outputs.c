/*
 * Screen_Outpus.c
 *
 *  Created on: 27 de ago. de 2026
 *      Author: rinaldo.santos
 */

#include "stdbool.h"
#include "rng.h"
#include "stdio.h"
#include "string.h"

#include "../App/UI/Screen_Outputs.h"
#include "../App/UI/Screen_Utils.h"
#include "../App/UI/led_ring.h"
#include "../App/UI/bar_leds.h"

LV_FONT_DECLARE(Neue_Medium_12);
LV_FONT_DECLARE(Neue_Medium_14);
LV_FONT_DECLARE(Segment_BoldItalic_28);

LV_IMG_DECLARE(LED);
LV_IMG_DECLARE(LED_OFF);

void create_labels_outputs(void);
void create_buttons_vol_out_xlr(void);
void create_buttons_vol_out_aes(void);
void create_buttons_vol_out_phone(void);
void create_buttons_vol_out_mpx1(void);
void create_buttons_vol_out_mpx2(void);
void create_output_barmeter_xlr_out(void);
void create_outputs_text(void);
void create_outputs_7Segment(void);

lv_obj_t * Tela_Outputs = NULL;
static lv_obj_t * img_fundo_outputs = NULL;
static lv_obj_t * text_output_top = NULL;
static lv_obj_t * bt_out_xlr_dec = NULL;
static lv_obj_t * bt_out_xlr_inc = NULL;
static lv_obj_t * bt_out_aes_inc = NULL;
static lv_obj_t * bt_out_aes_dec = NULL;
static lv_obj_t * bt_out_phone_inc = NULL;
static lv_obj_t * bt_out_phone_dec = NULL;
static lv_obj_t * bt_out_mpx1_inc = NULL;
static lv_obj_t * bt_out_mpx1_dec = NULL;
static lv_obj_t * bt_out_mpx2_inc = NULL;
static lv_obj_t * bt_out_mpx2_dec = NULL;
static lv_obj_t * text_out_indic[9];
static lv_obj_t * label_out_xlr = NULL;
static lv_obj_t * label_out_aes = NULL;
static lv_obj_t * label_out_mpx1 = NULL;
static lv_obj_t * label_out_mpx2 = NULL;

static led_ring_t ring_out_xlr;
static led_ring_t ring_out_aes;
static led_ring_t ring_out_phone;
static led_ring_t ring_out_mpx1;
static led_ring_t ring_out_mpx2;

static barmeter_t out_xlr_l;
static barmeter_t out_xlr_r;

void Screen_Outputs_Create(void)
{
	Tela_Outputs = lv_obj_create(NULL);
	lv_obj_clear_flag(Tela_Outputs, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLLABLE);
	lv_obj_set_style_bg_color(Tela_Outputs, lv_color_hex(0x000000), 0);
	lv_obj_set_style_bg_grad_color(Tela_Outputs, lv_color_hex(0x000000), 0);

	// Imagem de Fundo
	img_fundo_outputs = lv_img_create(Tela_Outputs);
	lv_img_set_src(img_fundo_outputs, "S:/OUTPUT/TELA_FUNDO_OUTPUT.bin");
	lv_obj_set_pos(img_fundo_outputs, 0, 0);

	create_labels_outputs();
	// Buttons
	create_buttons_vol_out_xlr();
	create_buttons_vol_out_aes();
	create_buttons_vol_out_phone();
	create_buttons_vol_out_mpx1();
	create_buttons_vol_out_mpx2();

	// Text Indicator
	create_outputs_text();

	// Led Rings
	led_ring_create(Tela_Outputs, &ring_out_xlr, 12, 39);
	led_ring_create(Tela_Outputs, &ring_out_aes, 200, 39);
	led_ring_create(Tela_Outputs, &ring_out_phone, 382, 39);
	led_ring_create(Tela_Outputs, &ring_out_mpx1, 12, 174);
	led_ring_create(Tela_Outputs, &ring_out_mpx2, 200, 174);

	led_ring_set(&ring_out_xlr, 20);
	led_ring_set(&ring_out_aes, 10);
	led_ring_set(&ring_out_phone, 15);
	led_ring_set(&ring_out_mpx1, 12);
	led_ring_set(&ring_out_mpx2, 6);

	// Bar-Meter
	create_output_barmeter_xlr_out();

	// Text 7-Segment
	create_outputs_7Segment();

	create_button_back_main(Tela_Outputs, 381, 265);
	create_text_footer(Tela_Outputs);
}

void create_labels_outputs(void)
{
    text_output_top = lv_label_create(Tela_Outputs);
    lv_obj_set_width(text_output_top, LV_SIZE_CONTENT);
    lv_obj_set_height(text_output_top, LV_SIZE_CONTENT);
    lv_label_set_text(text_output_top, "OUTPUT LEVEL ADJUST:");
    lv_obj_set_style_text_color(text_output_top, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(text_output_top, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(text_output_top, &Neue_Medium_14, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(text_output_top, 7, 5);
}

static void event_bt_out_xlr_inc(lv_event_t * e)
{
	lv_event_code_t code = lv_event_get_code(e);

	if(code == LV_EVENT_CLICKED || code == LV_EVENT_LONG_PRESSED_REPEAT) {
		led_ring_inc(&ring_out_xlr);
	}
}

static void event_bt_out_xlr_dec(lv_event_t * e)
{
	lv_event_code_t code = lv_event_get_code(e);

	if(code == LV_EVENT_CLICKED || code == LV_EVENT_LONG_PRESSED_REPEAT) {
		led_ring_dec(&ring_out_xlr);
	}
}

void create_buttons_vol_out_xlr(void)
{
    // Button "+"
    bt_out_xlr_inc = lv_imagebutton_create(Tela_Outputs);
    lv_imagebutton_set_src(bt_out_xlr_inc, LV_IMAGEBUTTON_STATE_RELEASED, NULL, "S:/MAIN/BT_INC.bin", NULL);
    lv_imagebutton_set_src(bt_out_xlr_inc, LV_IMAGEBUTTON_STATE_PRESSED, NULL, "S:/MAIN/BT_INC_P.bin", NULL);
    lv_imagebutton_set_src(bt_out_xlr_inc, LV_IMAGEBUTTON_STATE_DISABLED, NULL, "S:/MAIN/BT_INC.bin", NULL);
    lv_imagebutton_set_src(bt_out_xlr_inc, LV_IMAGEBUTTON_STATE_CHECKED_PRESSED, NULL, "S:/MAIN/BT_INC_P.bin", NULL);
    lv_imagebutton_set_src(bt_out_xlr_inc, LV_IMAGEBUTTON_STATE_CHECKED_RELEASED, NULL, "S:/MAIN/BT_INC.bin", NULL);
    lv_imagebutton_set_src(bt_out_xlr_inc, LV_IMAGEBUTTON_STATE_CHECKED_DISABLED, NULL, "S:/MAIN/BT_INC.bin", NULL);
    lv_obj_add_state(bt_out_xlr_inc, LV_IMAGEBUTTON_STATE_RELEASED);
    lv_obj_set_pos(bt_out_xlr_inc, 145, 130);
    lv_obj_add_event_cb(bt_out_xlr_inc, event_bt_out_xlr_inc, LV_EVENT_ALL, NULL);

    // Button "-"
    bt_out_xlr_dec = lv_imagebutton_create(Tela_Outputs);
    lv_imagebutton_set_src(bt_out_xlr_dec, LV_IMAGEBUTTON_STATE_RELEASED, NULL, "S:/MAIN/BT_DEC.bin", NULL);
    lv_imagebutton_set_src(bt_out_xlr_dec, LV_IMAGEBUTTON_STATE_PRESSED, NULL, "S:/MAIN/BT_DEC_P.bin", NULL);
    lv_imagebutton_set_src(bt_out_xlr_dec, LV_IMAGEBUTTON_STATE_DISABLED, NULL, "S:/MAIN/BT_DEC.bin", NULL);
    lv_imagebutton_set_src(bt_out_xlr_dec, LV_IMAGEBUTTON_STATE_CHECKED_PRESSED, NULL, "S:/MAIN/BT_DEC_P.bin", NULL);
    lv_imagebutton_set_src(bt_out_xlr_dec, LV_IMAGEBUTTON_STATE_CHECKED_RELEASED, NULL, "S:/MAIN/BT_DEC.bin", NULL);
    lv_imagebutton_set_src(bt_out_xlr_dec, LV_IMAGEBUTTON_STATE_CHECKED_DISABLED, NULL, "S:/MAIN/BT_DEC.bin", NULL);
    lv_obj_add_state(bt_out_xlr_dec, LV_IMAGEBUTTON_STATE_RELEASED);
    lv_obj_set_pos(bt_out_xlr_dec, 6, 130);
    lv_obj_add_event_cb(bt_out_xlr_dec, event_bt_out_xlr_dec, LV_EVENT_ALL, NULL);
}

static void event_bt_out_aes_inc(lv_event_t * e)
{
	lv_event_code_t code = lv_event_get_code(e);

	if(code == LV_EVENT_CLICKED || code == LV_EVENT_LONG_PRESSED_REPEAT) {
		led_ring_inc(&ring_out_aes);
	}
}

static void event_bt_out_aes_dec(lv_event_t * e)
{
	lv_event_code_t code = lv_event_get_code(e);

	if(code == LV_EVENT_CLICKED || code == LV_EVENT_LONG_PRESSED_REPEAT) {
		led_ring_dec(&ring_out_aes);
	}
}

void create_buttons_vol_out_aes(void)
{
    // Button "+"
    bt_out_aes_inc = lv_imagebutton_create(Tela_Outputs);
    lv_imagebutton_set_src(bt_out_aes_inc, LV_IMAGEBUTTON_STATE_RELEASED, NULL, "S:/MAIN/BT_INC.bin", NULL);
    lv_imagebutton_set_src(bt_out_aes_inc, LV_IMAGEBUTTON_STATE_PRESSED, NULL, "S:/MAIN/BT_INC_P.bin", NULL);
    lv_imagebutton_set_src(bt_out_aes_inc, LV_IMAGEBUTTON_STATE_DISABLED, NULL, "S:/MAIN/BT_INC.bin", NULL);
    lv_imagebutton_set_src(bt_out_aes_inc, LV_IMAGEBUTTON_STATE_CHECKED_PRESSED, NULL, "S:/MAIN/BT_INC_P.bin", NULL);
    lv_imagebutton_set_src(bt_out_aes_inc, LV_IMAGEBUTTON_STATE_CHECKED_RELEASED, NULL, "S:/MAIN/BT_INC.bin", NULL);
    lv_imagebutton_set_src(bt_out_aes_inc, LV_IMAGEBUTTON_STATE_CHECKED_DISABLED, NULL, "S:/MAIN/BT_INC.bin", NULL);
    lv_obj_add_state(bt_out_aes_inc, LV_IMAGEBUTTON_STATE_RELEASED);
    lv_obj_set_pos(bt_out_aes_inc, 332, 130);
    lv_obj_add_event_cb(bt_out_aes_inc, event_bt_out_aes_inc, LV_EVENT_ALL, NULL);

    // Button "-"
    bt_out_aes_dec = lv_imagebutton_create(Tela_Outputs);
    lv_imagebutton_set_src(bt_out_aes_dec, LV_IMAGEBUTTON_STATE_RELEASED, NULL, "S:/MAIN/BT_DEC.bin", NULL);
    lv_imagebutton_set_src(bt_out_aes_dec, LV_IMAGEBUTTON_STATE_PRESSED, NULL, "S:/MAIN/BT_DEC_P.bin", NULL);
    lv_imagebutton_set_src(bt_out_aes_dec, LV_IMAGEBUTTON_STATE_DISABLED, NULL, "S:/MAIN/BT_DEC.bin", NULL);
    lv_imagebutton_set_src(bt_out_aes_dec, LV_IMAGEBUTTON_STATE_CHECKED_PRESSED, NULL, "S:/MAIN/BT_DEC_P.bin", NULL);
    lv_imagebutton_set_src(bt_out_aes_dec, LV_IMAGEBUTTON_STATE_CHECKED_RELEASED, NULL, "S:/MAIN/BT_DEC.bin", NULL);
    lv_imagebutton_set_src(bt_out_aes_dec, LV_IMAGEBUTTON_STATE_CHECKED_DISABLED, NULL, "S:/MAIN/BT_DEC.bin", NULL);
    lv_obj_add_state(bt_out_aes_dec, LV_IMAGEBUTTON_STATE_RELEASED);
    lv_obj_set_pos(bt_out_aes_dec, 193, 130);
    lv_obj_add_event_cb(bt_out_aes_dec, event_bt_out_aes_dec, LV_EVENT_ALL, NULL);
}

static void event_bt_out_phone_inc(lv_event_t * e)
{
	lv_event_code_t code = lv_event_get_code(e);

	if(code == LV_EVENT_CLICKED || code == LV_EVENT_LONG_PRESSED_REPEAT) {
		led_ring_inc(&ring_out_phone);
	}
}

static void event_bt_out_phone_dec(lv_event_t * e)
{
	lv_event_code_t code = lv_event_get_code(e);

	if(code == LV_EVENT_CLICKED || code == LV_EVENT_LONG_PRESSED_REPEAT) {
		led_ring_dec(&ring_out_phone);
	}
}

void create_buttons_vol_out_phone(void)
{
    // Button "+"
    bt_out_phone_inc = lv_imagebutton_create(Tela_Outputs);
    lv_imagebutton_set_src(bt_out_phone_inc, LV_IMAGEBUTTON_STATE_RELEASED, NULL, "S:/MAIN/BT_INC.bin", NULL);
    lv_imagebutton_set_src(bt_out_phone_inc, LV_IMAGEBUTTON_STATE_PRESSED, NULL, "S:/MAIN/BT_INC_P.bin", NULL);
    lv_imagebutton_set_src(bt_out_phone_inc, LV_IMAGEBUTTON_STATE_DISABLED, NULL, "S:/MAIN/BT_INC.bin", NULL);
    lv_imagebutton_set_src(bt_out_phone_inc, LV_IMAGEBUTTON_STATE_CHECKED_PRESSED, NULL, "S:/MAIN/BT_INC_P.bin", NULL);
    lv_imagebutton_set_src(bt_out_phone_inc, LV_IMAGEBUTTON_STATE_CHECKED_RELEASED, NULL, "S:/MAIN/BT_INC.bin", NULL);
    lv_imagebutton_set_src(bt_out_phone_inc, LV_IMAGEBUTTON_STATE_CHECKED_DISABLED, NULL, "S:/MAIN/BT_INC.bin", NULL);
    lv_obj_add_state(bt_out_phone_inc, LV_IMAGEBUTTON_STATE_RELEASED);
    lv_obj_set_pos(bt_out_phone_inc, 428, 130);
    lv_obj_add_event_cb(bt_out_phone_inc, event_bt_out_phone_inc, LV_EVENT_ALL, NULL);

    // Button "-"
    bt_out_phone_dec = lv_imagebutton_create(Tela_Outputs);
    lv_imagebutton_set_src(bt_out_phone_dec, LV_IMAGEBUTTON_STATE_RELEASED, NULL, "S:/MAIN/BT_DEC.bin", NULL);
    lv_imagebutton_set_src(bt_out_phone_dec, LV_IMAGEBUTTON_STATE_PRESSED, NULL, "S:/MAIN/BT_DEC_P.bin", NULL);
    lv_imagebutton_set_src(bt_out_phone_dec, LV_IMAGEBUTTON_STATE_DISABLED, NULL, "S:/MAIN/BT_DEC.bin", NULL);
    lv_imagebutton_set_src(bt_out_phone_dec, LV_IMAGEBUTTON_STATE_CHECKED_PRESSED, NULL, "S:/MAIN/BT_DEC_P.bin", NULL);
    lv_imagebutton_set_src(bt_out_phone_dec, LV_IMAGEBUTTON_STATE_CHECKED_RELEASED, NULL, "S:/MAIN/BT_DEC.bin", NULL);
    lv_imagebutton_set_src(bt_out_phone_dec, LV_IMAGEBUTTON_STATE_CHECKED_DISABLED, NULL, "S:/MAIN/BT_DEC.bin", NULL);
    lv_obj_add_state(bt_out_phone_dec, LV_IMAGEBUTTON_STATE_RELEASED);
    lv_obj_set_pos(bt_out_phone_dec, 381, 130);
    lv_obj_add_event_cb(bt_out_phone_dec, event_bt_out_phone_dec, LV_EVENT_ALL, NULL);
}

static void event_bt_out_mpx1_inc(lv_event_t * e)
{
	lv_event_code_t code = lv_event_get_code(e);

	if(code == LV_EVENT_CLICKED || code == LV_EVENT_LONG_PRESSED_REPEAT) {
		led_ring_inc(&ring_out_mpx1);
	}
}

static void event_bt_out_mpx1_dec(lv_event_t * e)
{
	lv_event_code_t code = lv_event_get_code(e);

	if(code == LV_EVENT_CLICKED || code == LV_EVENT_LONG_PRESSED_REPEAT) {
		led_ring_dec(&ring_out_mpx1);
	}
}

void create_buttons_vol_out_mpx1(void)
{
    // Button "+"
    bt_out_mpx1_inc = lv_imagebutton_create(Tela_Outputs);
    lv_imagebutton_set_src(bt_out_mpx1_inc, LV_IMAGEBUTTON_STATE_RELEASED, NULL, "S:/MAIN/BT_INC.bin", NULL);
    lv_imagebutton_set_src(bt_out_mpx1_inc, LV_IMAGEBUTTON_STATE_PRESSED, NULL, "S:/MAIN/BT_INC_P.bin", NULL);
    lv_imagebutton_set_src(bt_out_mpx1_inc, LV_IMAGEBUTTON_STATE_DISABLED, NULL, "S:/MAIN/BT_INC.bin", NULL);
    lv_imagebutton_set_src(bt_out_mpx1_inc, LV_IMAGEBUTTON_STATE_CHECKED_PRESSED, NULL, "S:/MAIN/BT_INC_P.bin", NULL);
    lv_imagebutton_set_src(bt_out_mpx1_inc, LV_IMAGEBUTTON_STATE_CHECKED_RELEASED, NULL, "S:/MAIN/BT_INC.bin", NULL);
    lv_imagebutton_set_src(bt_out_mpx1_inc, LV_IMAGEBUTTON_STATE_CHECKED_DISABLED, NULL, "S:/MAIN/BT_INC.bin", NULL);
    lv_obj_add_state(bt_out_mpx1_inc, LV_IMAGEBUTTON_STATE_RELEASED);
    lv_obj_set_pos(bt_out_mpx1_inc, 145, 265);
    lv_obj_add_event_cb(bt_out_mpx1_inc, event_bt_out_mpx1_inc, LV_EVENT_ALL, NULL);

    // Button "-"
    bt_out_mpx1_dec = lv_imagebutton_create(Tela_Outputs);
    lv_imagebutton_set_src(bt_out_mpx1_dec, LV_IMAGEBUTTON_STATE_RELEASED, NULL, "S:/MAIN/BT_DEC.bin", NULL);
    lv_imagebutton_set_src(bt_out_mpx1_dec, LV_IMAGEBUTTON_STATE_PRESSED, NULL, "S:/MAIN/BT_DEC_P.bin", NULL);
    lv_imagebutton_set_src(bt_out_mpx1_dec, LV_IMAGEBUTTON_STATE_DISABLED, NULL, "S:/MAIN/BT_DEC.bin", NULL);
    lv_imagebutton_set_src(bt_out_mpx1_dec, LV_IMAGEBUTTON_STATE_CHECKED_PRESSED, NULL, "S:/MAIN/BT_DEC_P.bin", NULL);
    lv_imagebutton_set_src(bt_out_mpx1_dec, LV_IMAGEBUTTON_STATE_CHECKED_RELEASED, NULL, "S:/MAIN/BT_DEC.bin", NULL);
    lv_imagebutton_set_src(bt_out_mpx1_dec, LV_IMAGEBUTTON_STATE_CHECKED_DISABLED, NULL, "S:/MAIN/BT_DEC.bin", NULL);
    lv_obj_add_state(bt_out_mpx1_dec, LV_IMAGEBUTTON_STATE_RELEASED);
    lv_obj_set_pos(bt_out_mpx1_dec, 6, 265);
    lv_obj_add_event_cb(bt_out_mpx1_dec, event_bt_out_mpx1_dec, LV_EVENT_ALL, NULL);
}

static void event_bt_out_mpx2_inc(lv_event_t * e)
{
	lv_event_code_t code = lv_event_get_code(e);

	if(code == LV_EVENT_CLICKED || code == LV_EVENT_LONG_PRESSED_REPEAT) {
		led_ring_inc(&ring_out_mpx2);
	}
}

static void event_bt_out_mpx2_dec(lv_event_t * e)
{
	lv_event_code_t code = lv_event_get_code(e);

	if(code == LV_EVENT_CLICKED || code == LV_EVENT_LONG_PRESSED_REPEAT) {
		led_ring_dec(&ring_out_mpx2);
	}
}

void create_buttons_vol_out_mpx2(void)
{
    // Button "+"
    bt_out_mpx2_inc = lv_imagebutton_create(Tela_Outputs);
    lv_imagebutton_set_src(bt_out_mpx2_inc, LV_IMAGEBUTTON_STATE_RELEASED, NULL, "S:/MAIN/BT_INC.bin", NULL);
    lv_imagebutton_set_src(bt_out_mpx2_inc, LV_IMAGEBUTTON_STATE_PRESSED, NULL, "S:/MAIN/BT_INC_P.bin", NULL);
    lv_imagebutton_set_src(bt_out_mpx2_inc, LV_IMAGEBUTTON_STATE_DISABLED, NULL, "S:/MAIN/BT_INC.bin", NULL);
    lv_imagebutton_set_src(bt_out_mpx2_inc, LV_IMAGEBUTTON_STATE_CHECKED_PRESSED, NULL, "S:/MAIN/BT_INC_P.bin", NULL);
    lv_imagebutton_set_src(bt_out_mpx2_inc, LV_IMAGEBUTTON_STATE_CHECKED_RELEASED, NULL, "S:/MAIN/BT_INC.bin", NULL);
    lv_imagebutton_set_src(bt_out_mpx2_inc, LV_IMAGEBUTTON_STATE_CHECKED_DISABLED, NULL, "S:/MAIN/BT_INC.bin", NULL);
    lv_obj_add_state(bt_out_mpx2_inc, LV_IMAGEBUTTON_STATE_RELEASED);
    lv_obj_set_pos(bt_out_mpx2_inc, 332, 265);
    lv_obj_add_event_cb(bt_out_mpx2_inc, event_bt_out_mpx2_inc, LV_EVENT_ALL, NULL);

    // Button "-"
    bt_out_mpx2_dec = lv_imagebutton_create(Tela_Outputs);
    lv_imagebutton_set_src(bt_out_mpx2_dec, LV_IMAGEBUTTON_STATE_RELEASED, NULL, "S:/MAIN/BT_DEC.bin", NULL);
    lv_imagebutton_set_src(bt_out_mpx2_dec, LV_IMAGEBUTTON_STATE_PRESSED, NULL, "S:/MAIN/BT_DEC_P.bin", NULL);
    lv_imagebutton_set_src(bt_out_mpx2_dec, LV_IMAGEBUTTON_STATE_DISABLED, NULL, "S:/MAIN/BT_DEC.bin", NULL);
    lv_imagebutton_set_src(bt_out_mpx2_dec, LV_IMAGEBUTTON_STATE_CHECKED_PRESSED, NULL, "S:/MAIN/BT_DEC_P.bin", NULL);
    lv_imagebutton_set_src(bt_out_mpx2_dec, LV_IMAGEBUTTON_STATE_CHECKED_RELEASED, NULL, "S:/MAIN/BT_DEC.bin", NULL);
    lv_imagebutton_set_src(bt_out_mpx2_dec, LV_IMAGEBUTTON_STATE_CHECKED_DISABLED, NULL, "S:/MAIN/BT_DEC.bin", NULL);
    lv_obj_add_state(bt_out_mpx2_dec, LV_IMAGEBUTTON_STATE_RELEASED);
    lv_obj_set_pos(bt_out_mpx2_dec, 193, 265);
    lv_obj_add_event_cb(bt_out_mpx2_dec, event_bt_out_mpx2_dec, LV_EVENT_ALL, NULL);
}

void create_output_barmeter_xlr_out(void)
{
	out_xlr_l.on       = NULL;
	out_xlr_l.last_seg = -1;
	out_xlr_l.x        = 187;
	out_xlr_l.y        = 40;
	out_xlr_l.w        = BAR_W;
	out_xlr_l.h        = BAR_H;
	out_xlr_l.range    = BAR_RANGE;
	out_xlr_l.segs     = BAR_SEGMENTS;
	out_xlr_l.bounds   = NULL;
	out_xlr_l.img_off  = &LED_OFF;
	out_xlr_l.img_on   = &LED;
	out_xlr_l.rotation = 900;

	out_xlr_r.on       = NULL;
	out_xlr_r.last_seg = -1;
	out_xlr_r.x        = 187;
	out_xlr_r.y        = 63;
	out_xlr_r.w        = BAR_W;
	out_xlr_r.h        = BAR_H;
	out_xlr_r.range    = BAR_RANGE;
	out_xlr_r.segs     = BAR_SEGMENTS;
	out_xlr_r.bounds   = NULL;
	out_xlr_r.img_off  = &LED_OFF;
	out_xlr_r.img_on   = &LED;
	out_xlr_r.rotation = 900;

	barmeter_create(Tela_Outputs, &out_xlr_l);
	barmeter_create(Tela_Outputs, &out_xlr_r);

	//barmeter_set(&out_xlr_l, 4);
	//barmeter_set(&out_xlr_r, 4);
}

void create_outputs_text(void)
{
	for(uint8_t x = 0; x < 9; x++) {
		text_out_indic[x] = lv_label_create(Tela_Outputs);
		lv_obj_set_width(text_out_indic[x], LV_SIZE_CONTENT);
		lv_obj_set_height(text_out_indic[x], LV_SIZE_CONTENT);
		lv_obj_set_style_text_color(text_out_indic[x], lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
		lv_obj_set_style_text_opa(text_out_indic[x], 255, LV_PART_MAIN | LV_STATE_DEFAULT);
		lv_obj_set_style_text_font(text_out_indic[x], &Neue_Medium_12, LV_PART_MAIN | LV_STATE_DEFAULT);
	}

    lv_label_set_text(text_out_indic[0], "LEVEL %:");
    lv_obj_set_pos(text_out_indic[0], 10, 28);

    lv_label_set_text(text_out_indic[1], "L");
    lv_obj_set_pos(text_out_indic[1], 100, 44);

    lv_label_set_text(text_out_indic[2], "R");
    lv_obj_set_pos(text_out_indic[2], 100, 64);

    lv_label_set_text(text_out_indic[3], "LEVEL %:");
    lv_obj_set_pos(text_out_indic[3], 196, 28);

    lv_label_set_text(text_out_indic[4], "L");
    lv_obj_set_pos(text_out_indic[4], 290, 44);

    lv_label_set_text(text_out_indic[5], "R");
    lv_obj_set_pos(text_out_indic[5], 290, 64);

    lv_label_set_text(text_out_indic[6], "LEVEL %:");
    lv_obj_set_pos(text_out_indic[6], 120, 200);

    lv_label_set_text(text_out_indic[7], "LEVEL %:");
    lv_obj_set_pos(text_out_indic[7], 310, 200);

    lv_label_set_text(text_out_indic[8], "EARPHONES");
    lv_obj_set_pos(text_out_indic[8], 394, 28);
}

void create_outputs_7Segment(void)
{
	label_out_xlr = lv_label_create(Tela_Outputs);
	lv_obj_set_width(label_out_xlr, LV_SIZE_CONTENT);
	lv_obj_set_height(label_out_xlr, LV_SIZE_CONTENT);
	lv_obj_set_style_text_color(label_out_xlr, lv_color_hex(0xB4DCFF), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_opa(label_out_xlr, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(label_out_xlr, &Segment_BoldItalic_28, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_label_set_text(label_out_xlr, "26.6");
    lv_obj_set_pos(label_out_xlr, 108, 94);

	label_out_aes = lv_label_create(Tela_Outputs);
	lv_obj_set_width(label_out_aes, LV_SIZE_CONTENT);
	lv_obj_set_height(label_out_aes, LV_SIZE_CONTENT);
	lv_obj_set_style_text_color(label_out_aes, lv_color_hex(0xB4DCFF), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_opa(label_out_aes, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(label_out_aes, &Segment_BoldItalic_28, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_label_set_text(label_out_aes, "35.8");
    lv_obj_set_pos(label_out_aes, 300, 94);

	label_out_mpx1 = lv_label_create(Tela_Outputs);
	lv_obj_set_width(label_out_mpx1, LV_SIZE_CONTENT);
	lv_obj_set_height(label_out_mpx1, LV_SIZE_CONTENT);
	lv_obj_set_style_text_color(label_out_mpx1, lv_color_hex(0xB4DCFF), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_opa(label_out_mpx1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(label_out_mpx1, &Segment_BoldItalic_28, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_label_set_text(label_out_mpx1, "58.0");
    lv_obj_set_pos(label_out_mpx1, 108, 226);

	label_out_mpx2 = lv_label_create(Tela_Outputs);
	lv_obj_set_width(label_out_mpx2, LV_SIZE_CONTENT);
	lv_obj_set_height(label_out_mpx2, LV_SIZE_CONTENT);
	lv_obj_set_style_text_color(label_out_mpx2, lv_color_hex(0xB4DCFF), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_opa(label_out_mpx2, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(label_out_mpx2, &Segment_BoldItalic_28, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_label_set_text(label_out_mpx2, "22.2");
    lv_obj_set_pos(label_out_mpx2, 300, 226);
}
