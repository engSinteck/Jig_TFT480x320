/*
 * Screen_Inputs.c
 *
 *  Created on: 26 de ago. de 2026
 *      Author: rinaldo.santos
 */

#include "stdbool.h"
#include "rng.h"
#include "stdio.h"
#include "string.h"

#include "../App/UI/Screen_Inputs.h"
#include "../App/UI/Screen_Utils.h"
#include "../App/UI/led_ring.h"
#include "../App/UI/bar_leds.h"

LV_FONT_DECLARE(Neue_Medium_11);
LV_FONT_DECLARE(Neue_Medium_14);

LV_IMG_DECLARE(LED);
LV_IMG_DECLARE(LED_OFF);

void create_labels_inputs(void);
void create_text_inputs(void);
void create_buttons_vol_in_xlr(void);
void create_buttons_vol_in_usb(void);
void create_buttons_vol_in_phone(void);
void create_buttons_vol_in_bluetooth(void);
void create_buttons_vol_in_pc(void);
void create_input_barmeter_xlr(void);
void create_output_barmeter_xlr(void);
void create_input_barmeter_usb(void);
void create_output_barmeter_usb(void);
void create_input_barmeter_ble(void);
void create_output_barmeter_ble(void);
void create_input_barmeter_pc(void);
void create_output_barmeter_pc(void);

lv_obj_t * Tela_Inputs = NULL;
static lv_obj_t * img_fundo_inputs = NULL;
static lv_obj_t * text_inputs_top = NULL;
static lv_obj_t * text_inputs_indic[13];
static lv_obj_t * bt_in_xlr_dec = NULL;
static lv_obj_t * bt_in_xlr_inc = NULL;
static lv_obj_t * bt_in_usb_inc = NULL;
static lv_obj_t * bt_in_usb_dec = NULL;
static lv_obj_t * bt_in_phone_inc = NULL;
static lv_obj_t * bt_in_phone_dec = NULL;
static lv_obj_t * bt_in_ble_inc = NULL;
static lv_obj_t * bt_in_ble_dec = NULL;
static lv_obj_t * bt_in_pc_inc = NULL;
static lv_obj_t * bt_in_pc_dec = NULL;

static led_ring_t ring_in_xlr;
static led_ring_t ring_in_usb;
static led_ring_t ring_in_phone;
static led_ring_t ring_in_bluetooth;
static led_ring_t ring_in_pc;

static barmeter_t in_xlr_l;
static barmeter_t in_xlr_r;
static barmeter_t out_xlr_l;
static barmeter_t out_xlr_r;

static barmeter_t in_usb_l;
static barmeter_t in_usb_r;
static barmeter_t out_usb_l;
static barmeter_t out_usb_r;

static barmeter_t in_ble_l;
static barmeter_t in_ble_r;
static barmeter_t out_ble_l;
static barmeter_t out_ble_r;

static barmeter_t in_pc_l;
static barmeter_t in_pc_r;
static barmeter_t out_pc_l;
static barmeter_t out_pc_r;

void Screen_Inputs_Create(void)
{
	Tela_Inputs = lv_obj_create(NULL);
	lv_obj_clear_flag(Tela_Inputs, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLLABLE);
	lv_obj_set_style_bg_color(Tela_Inputs, lv_color_hex(0x000000), 0);
	lv_obj_set_style_bg_grad_color(Tela_Inputs, lv_color_hex(0x000000), 0);

	// Imagem de Fundo
	img_fundo_inputs = lv_img_create(Tela_Inputs);
	lv_img_set_src(img_fundo_inputs, "S:/Inputs/TELA_FUNDO_INPUTS.bin");
	lv_obj_set_pos(img_fundo_inputs, 0, 0);

	create_labels_inputs();
	create_text_inputs();
	// Buttons
	create_buttons_vol_in_xlr();
	create_buttons_vol_in_usb();
	create_buttons_vol_in_phone();
	create_buttons_vol_in_bluetooth();
	create_buttons_vol_in_pc();
	// Barra Leds
	create_input_barmeter_xlr();
	create_output_barmeter_xlr();
	create_input_barmeter_usb();
	create_output_barmeter_usb();
	create_input_barmeter_ble();
	create_output_barmeter_ble();
	create_input_barmeter_pc();
	create_output_barmeter_pc();

	// Led Rings
	led_ring_create(Tela_Inputs, &ring_in_xlr, 56, 39);
	led_ring_create(Tela_Inputs, &ring_in_usb, 240, 39);
	led_ring_create(Tela_Inputs, &ring_in_phone, 382, 39);
	led_ring_create(Tela_Inputs, &ring_in_bluetooth, 56, 174);
	led_ring_create(Tela_Inputs, &ring_in_pc, 240, 174);

	led_ring_set(&ring_in_xlr, 1);
	led_ring_set(&ring_in_usb, 4);
	led_ring_set(&ring_in_phone, 6);
	led_ring_set(&ring_in_bluetooth, 8);
	led_ring_set(&ring_in_pc, 10);
	//
	create_button_back_main(Tela_Inputs, 381, 265);
	create_text_footer(Tela_Inputs);
}

void create_labels_inputs(void)
{
    text_inputs_top = lv_label_create(Tela_Inputs);
    lv_obj_set_width(text_inputs_top, LV_SIZE_CONTENT);
    lv_obj_set_height(text_inputs_top, LV_SIZE_CONTENT);
    lv_label_set_text(text_inputs_top, "INPUT GAIN ADJUST:");
    lv_obj_set_style_text_color(text_inputs_top, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(text_inputs_top, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(text_inputs_top, &Neue_Medium_14, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(text_inputs_top, 7, 5);
}

void create_text_inputs(void)
{
    for(uint8_t x = 0; x < 13; x++) {
    	text_inputs_indic[x] = lv_label_create(Tela_Inputs);
        lv_obj_set_width(text_inputs_indic[x], LV_SIZE_CONTENT);
        lv_obj_set_height(text_inputs_indic[x], LV_SIZE_CONTENT);
        lv_obj_set_style_text_color(text_inputs_indic[x], lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_opa(text_inputs_indic[x], 255, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_font(text_inputs_indic[x], &Neue_Medium_11, LV_PART_MAIN | LV_STATE_DEFAULT);
    }

    lv_label_set_text(text_inputs_indic[0], "INPUT");
    lv_label_set_text(text_inputs_indic[1], "GAIN: 1.10");
    lv_label_set_text(text_inputs_indic[2], "OUTPUT");

    lv_label_set_text(text_inputs_indic[3], "INPUT");
    lv_label_set_text(text_inputs_indic[4], "GAIN: 1.10");
    lv_label_set_text(text_inputs_indic[5], "OUTPUT");

    lv_label_set_text(text_inputs_indic[6], "EARPHONES");

    lv_label_set_text(text_inputs_indic[7], "INPUT");
    lv_label_set_text(text_inputs_indic[8], "GAIN: 1.10");
    lv_label_set_text(text_inputs_indic[9], "OUTPUT");

    lv_label_set_text(text_inputs_indic[10], "INPUT");
    lv_label_set_text(text_inputs_indic[11], "GAIN: 1.10");
    lv_label_set_text(text_inputs_indic[12], "OUTPUT");

    lv_obj_set_pos(text_inputs_indic[0], 11, 28);
    lv_obj_set_pos(text_inputs_indic[1], 70, 28);
    lv_obj_set_pos(text_inputs_indic[2], 140, 28);
    lv_obj_set_pos(text_inputs_indic[3], 200, 28);
    lv_obj_set_pos(text_inputs_indic[4], 260, 28);
    lv_obj_set_pos(text_inputs_indic[5], 330, 28);
    lv_obj_set_pos(text_inputs_indic[6], 394, 28);
    lv_obj_set_pos(text_inputs_indic[7], 11, 163);
    lv_obj_set_pos(text_inputs_indic[8], 70, 163);
    lv_obj_set_pos(text_inputs_indic[9], 140, 163);
    lv_obj_set_pos(text_inputs_indic[10], 200, 163);
    lv_obj_set_pos(text_inputs_indic[11], 260, 163);
    lv_obj_set_pos(text_inputs_indic[12], 330, 163);
}

static void event_bt_in_xlr_inc(lv_event_t * e)
{
	lv_event_code_t code = lv_event_get_code(e);

	if(code == LV_EVENT_CLICKED || code == LV_EVENT_LONG_PRESSED_REPEAT) {
		led_ring_inc(&ring_in_xlr);
	 }
}

static void event_bt_in_xlr_dec(lv_event_t * e)
{
	lv_event_code_t code = lv_event_get_code(e);

	if(code == LV_EVENT_CLICKED || code == LV_EVENT_LONG_PRESSED_REPEAT) {
		led_ring_dec(&ring_in_xlr);
	}
}

void create_buttons_vol_in_xlr(void)
{
    // Button "+"
    bt_in_xlr_inc = lv_imagebutton_create(Tela_Inputs);
    lv_imagebutton_set_src(bt_in_xlr_inc, LV_IMAGEBUTTON_STATE_RELEASED, NULL, "S:/MAIN/BT_INC.bin", NULL);
    lv_imagebutton_set_src(bt_in_xlr_inc, LV_IMAGEBUTTON_STATE_PRESSED, NULL, "S:/MAIN/BT_INC_P.bin", NULL);
    lv_imagebutton_set_src(bt_in_xlr_inc, LV_IMAGEBUTTON_STATE_DISABLED, NULL, "S:/MAIN/BT_INC.bin", NULL);
    lv_imagebutton_set_src(bt_in_xlr_inc, LV_IMAGEBUTTON_STATE_CHECKED_PRESSED, NULL, "S:/MAIN/BT_INC_P.bin", NULL);
    lv_imagebutton_set_src(bt_in_xlr_inc, LV_IMAGEBUTTON_STATE_CHECKED_RELEASED, NULL, "S:/MAIN/BT_INC.bin", NULL);
    lv_imagebutton_set_src(bt_in_xlr_inc, LV_IMAGEBUTTON_STATE_CHECKED_DISABLED, NULL, "S:/MAIN/BT_INC.bin", NULL);
    lv_obj_add_state(bt_in_xlr_inc, LV_IMAGEBUTTON_STATE_RELEASED);
    lv_obj_set_pos(bt_in_xlr_inc, 145, 130);
    lv_obj_add_event_cb(bt_in_xlr_inc, event_bt_in_xlr_inc, LV_EVENT_ALL, NULL);

    // Button "-"
    bt_in_xlr_dec = lv_imagebutton_create(Tela_Inputs);
    lv_imagebutton_set_src(bt_in_xlr_dec, LV_IMAGEBUTTON_STATE_RELEASED, NULL, "S:/MAIN/BT_DEC.bin", NULL);
    lv_imagebutton_set_src(bt_in_xlr_dec, LV_IMAGEBUTTON_STATE_PRESSED, NULL, "S:/MAIN/BT_DEC_P.bin", NULL);
    lv_imagebutton_set_src(bt_in_xlr_dec, LV_IMAGEBUTTON_STATE_DISABLED, NULL, "S:/MAIN/BT_DEC.bin", NULL);
    lv_imagebutton_set_src(bt_in_xlr_dec, LV_IMAGEBUTTON_STATE_CHECKED_PRESSED, NULL, "S:/MAIN/BT_DEC_P.bin", NULL);
    lv_imagebutton_set_src(bt_in_xlr_dec, LV_IMAGEBUTTON_STATE_CHECKED_RELEASED, NULL, "S:/MAIN/BT_DEC.bin", NULL);
    lv_imagebutton_set_src(bt_in_xlr_dec, LV_IMAGEBUTTON_STATE_CHECKED_DISABLED, NULL, "S:/MAIN/BT_DEC.bin", NULL);
    lv_obj_add_state(bt_in_xlr_dec, LV_IMAGEBUTTON_STATE_RELEASED);
    lv_obj_set_pos(bt_in_xlr_dec, 6, 130);
    lv_obj_add_event_cb(bt_in_xlr_dec, event_bt_in_xlr_dec, LV_EVENT_ALL, NULL);
}

static void event_bt_in_usb_inc(lv_event_t * e)
{
	lv_event_code_t code = lv_event_get_code(e);

	if(code == LV_EVENT_CLICKED || code == LV_EVENT_LONG_PRESSED_REPEAT) {
		led_ring_inc(&ring_in_usb);
	}
}

static void event_bt_in_usb_dec(lv_event_t * e)
{
	lv_event_code_t code = lv_event_get_code(e);

	if(code == LV_EVENT_CLICKED || code == LV_EVENT_LONG_PRESSED_REPEAT) {
		led_ring_dec(&ring_in_usb);
	}
}

void create_buttons_vol_in_usb(void)
{
    // Button "+"
    bt_in_usb_inc = lv_imagebutton_create(Tela_Inputs);
    lv_imagebutton_set_src(bt_in_usb_inc, LV_IMAGEBUTTON_STATE_RELEASED, NULL, "S:/MAIN/BT_INC.bin", NULL);
    lv_imagebutton_set_src(bt_in_usb_inc, LV_IMAGEBUTTON_STATE_PRESSED, NULL, "S:/MAIN/BT_INC_P.bin", NULL);
    lv_imagebutton_set_src(bt_in_usb_inc, LV_IMAGEBUTTON_STATE_DISABLED, NULL, "S:/MAIN/BT_INC.bin", NULL);
    lv_imagebutton_set_src(bt_in_usb_inc, LV_IMAGEBUTTON_STATE_CHECKED_PRESSED, NULL, "S:/MAIN/BT_INC_P.bin", NULL);
    lv_imagebutton_set_src(bt_in_usb_inc, LV_IMAGEBUTTON_STATE_CHECKED_RELEASED, NULL, "S:/MAIN/BT_INC.bin", NULL);
    lv_imagebutton_set_src(bt_in_usb_inc, LV_IMAGEBUTTON_STATE_CHECKED_DISABLED, NULL, "S:/MAIN/BT_INC.bin", NULL);
    lv_obj_add_state(bt_in_usb_inc, LV_IMAGEBUTTON_STATE_RELEASED);
    lv_obj_set_pos(bt_in_usb_inc, 332, 130);
    lv_obj_add_event_cb(bt_in_usb_inc, event_bt_in_usb_inc, LV_EVENT_ALL, NULL);

    // Button "-"
    bt_in_usb_dec = lv_imagebutton_create(Tela_Inputs);
    lv_imagebutton_set_src(bt_in_usb_dec, LV_IMAGEBUTTON_STATE_RELEASED, NULL, "S:/MAIN/BT_DEC.bin", NULL);
    lv_imagebutton_set_src(bt_in_usb_dec, LV_IMAGEBUTTON_STATE_PRESSED, NULL, "S:/MAIN/BT_DEC_P.bin", NULL);
    lv_imagebutton_set_src(bt_in_usb_dec, LV_IMAGEBUTTON_STATE_DISABLED, NULL, "S:/MAIN/BT_DEC.bin", NULL);
    lv_imagebutton_set_src(bt_in_usb_dec, LV_IMAGEBUTTON_STATE_CHECKED_PRESSED, NULL, "S:/MAIN/BT_DEC_P.bin", NULL);
    lv_imagebutton_set_src(bt_in_usb_dec, LV_IMAGEBUTTON_STATE_CHECKED_RELEASED, NULL, "S:/MAIN/BT_DEC.bin", NULL);
    lv_imagebutton_set_src(bt_in_usb_dec, LV_IMAGEBUTTON_STATE_CHECKED_DISABLED, NULL, "S:/MAIN/BT_DEC.bin", NULL);
    lv_obj_add_state(bt_in_usb_dec, LV_IMAGEBUTTON_STATE_RELEASED);
    lv_obj_set_pos(bt_in_usb_dec, 193, 130);
    lv_obj_add_event_cb(bt_in_usb_dec, event_bt_in_usb_dec, LV_EVENT_ALL, NULL);
}

static void event_bt_in_phone_inc(lv_event_t * e)
{
	lv_event_code_t code = lv_event_get_code(e);

	if(code == LV_EVENT_CLICKED || code == LV_EVENT_LONG_PRESSED_REPEAT) {
		led_ring_inc(&ring_in_phone);
	}
}

static void event_bt_in_phone_dec(lv_event_t * e)
{
	lv_event_code_t code = lv_event_get_code(e);

	if(code == LV_EVENT_CLICKED || code == LV_EVENT_LONG_PRESSED_REPEAT) {
		led_ring_dec(&ring_in_phone);
	}
}

void create_buttons_vol_in_phone(void)
{
    // Button "+"
    bt_in_phone_inc = lv_imagebutton_create(Tela_Inputs);
    lv_imagebutton_set_src(bt_in_phone_inc, LV_IMAGEBUTTON_STATE_RELEASED, NULL, "S:/MAIN/BT_INC.bin", NULL);
    lv_imagebutton_set_src(bt_in_phone_inc, LV_IMAGEBUTTON_STATE_PRESSED, NULL, "S:/MAIN/BT_INC_P.bin", NULL);
    lv_imagebutton_set_src(bt_in_phone_inc, LV_IMAGEBUTTON_STATE_DISABLED, NULL, "S:/MAIN/BT_INC.bin", NULL);
    lv_imagebutton_set_src(bt_in_phone_inc, LV_IMAGEBUTTON_STATE_CHECKED_PRESSED, NULL, "S:/MAIN/BT_INC_P.bin", NULL);
    lv_imagebutton_set_src(bt_in_phone_inc, LV_IMAGEBUTTON_STATE_CHECKED_RELEASED, NULL, "S:/MAIN/BT_INC.bin", NULL);
    lv_imagebutton_set_src(bt_in_phone_inc, LV_IMAGEBUTTON_STATE_CHECKED_DISABLED, NULL, "S:/MAIN/BT_INC.bin", NULL);
    lv_obj_add_state(bt_in_phone_inc, LV_IMAGEBUTTON_STATE_RELEASED);
    lv_obj_set_pos(bt_in_phone_inc, 428, 130);
    lv_obj_add_event_cb(bt_in_phone_inc, event_bt_in_phone_inc, LV_EVENT_ALL, NULL);

    // Button "-"
    bt_in_phone_dec = lv_imagebutton_create(Tela_Inputs);
    lv_imagebutton_set_src(bt_in_phone_dec, LV_IMAGEBUTTON_STATE_RELEASED, NULL, "S:/MAIN/BT_DEC.bin", NULL);
    lv_imagebutton_set_src(bt_in_phone_dec, LV_IMAGEBUTTON_STATE_PRESSED, NULL, "S:/MAIN/BT_DEC_P.bin", NULL);
    lv_imagebutton_set_src(bt_in_phone_dec, LV_IMAGEBUTTON_STATE_DISABLED, NULL, "S:/MAIN/BT_DEC.bin", NULL);
    lv_imagebutton_set_src(bt_in_phone_dec, LV_IMAGEBUTTON_STATE_CHECKED_PRESSED, NULL, "S:/MAIN/BT_DEC_P.bin", NULL);
    lv_imagebutton_set_src(bt_in_phone_dec, LV_IMAGEBUTTON_STATE_CHECKED_RELEASED, NULL, "S:/MAIN/BT_DEC.bin", NULL);
    lv_imagebutton_set_src(bt_in_phone_dec, LV_IMAGEBUTTON_STATE_CHECKED_DISABLED, NULL, "S:/MAIN/BT_DEC.bin", NULL);
    lv_obj_add_state(bt_in_phone_dec, LV_IMAGEBUTTON_STATE_RELEASED);
    lv_obj_set_pos(bt_in_phone_dec, 381, 130);
    lv_obj_add_event_cb(bt_in_phone_dec, event_bt_in_phone_dec, LV_EVENT_ALL, NULL);
}

static void event_bt_in_ble_inc(lv_event_t * e)
{
	lv_event_code_t code = lv_event_get_code(e);

	if(code == LV_EVENT_CLICKED || code == LV_EVENT_LONG_PRESSED_REPEAT) {
		led_ring_inc(&ring_in_bluetooth);
	}
}

static void event_bt_in_ble_dec(lv_event_t * e)
{
	lv_event_code_t code = lv_event_get_code(e);

	if(code == LV_EVENT_CLICKED || code == LV_EVENT_LONG_PRESSED_REPEAT) {
		led_ring_dec(&ring_in_bluetooth);
	}
}

void create_buttons_vol_in_bluetooth(void)
{
    // Button "+"
    bt_in_ble_inc = lv_imagebutton_create(Tela_Inputs);
    lv_imagebutton_set_src(bt_in_ble_inc, LV_IMAGEBUTTON_STATE_RELEASED, NULL, "S:/MAIN/BT_INC.bin", NULL);
    lv_imagebutton_set_src(bt_in_ble_inc, LV_IMAGEBUTTON_STATE_PRESSED, NULL, "S:/MAIN/BT_INC_P.bin", NULL);
    lv_imagebutton_set_src(bt_in_ble_inc, LV_IMAGEBUTTON_STATE_DISABLED, NULL, "S:/MAIN/BT_INC.bin", NULL);
    lv_imagebutton_set_src(bt_in_ble_inc, LV_IMAGEBUTTON_STATE_CHECKED_PRESSED, NULL, "S:/MAIN/BT_INC_P.bin", NULL);
    lv_imagebutton_set_src(bt_in_ble_inc, LV_IMAGEBUTTON_STATE_CHECKED_RELEASED, NULL, "S:/MAIN/BT_INC.bin", NULL);
    lv_imagebutton_set_src(bt_in_ble_inc, LV_IMAGEBUTTON_STATE_CHECKED_DISABLED, NULL, "S:/MAIN/BT_INC.bin", NULL);
    lv_obj_add_state(bt_in_ble_inc, LV_IMAGEBUTTON_STATE_RELEASED);
    lv_obj_set_pos(bt_in_ble_inc, 145, 265);
    lv_obj_add_event_cb(bt_in_ble_inc, event_bt_in_ble_inc, LV_EVENT_ALL, NULL);

    // Button "-"
    bt_in_ble_dec = lv_imagebutton_create(Tela_Inputs);
    lv_imagebutton_set_src(bt_in_ble_dec, LV_IMAGEBUTTON_STATE_RELEASED, NULL, "S:/MAIN/BT_DEC.bin", NULL);
    lv_imagebutton_set_src(bt_in_ble_dec, LV_IMAGEBUTTON_STATE_PRESSED, NULL, "S:/MAIN/BT_DEC_P.bin", NULL);
    lv_imagebutton_set_src(bt_in_ble_dec, LV_IMAGEBUTTON_STATE_DISABLED, NULL, "S:/MAIN/BT_DEC.bin", NULL);
    lv_imagebutton_set_src(bt_in_ble_dec, LV_IMAGEBUTTON_STATE_CHECKED_PRESSED, NULL, "S:/MAIN/BT_DEC_P.bin", NULL);
    lv_imagebutton_set_src(bt_in_ble_dec, LV_IMAGEBUTTON_STATE_CHECKED_RELEASED, NULL, "S:/MAIN/BT_DEC.bin", NULL);
    lv_imagebutton_set_src(bt_in_ble_dec, LV_IMAGEBUTTON_STATE_CHECKED_DISABLED, NULL, "S:/MAIN/BT_DEC.bin", NULL);
    lv_obj_add_state(bt_in_ble_dec, LV_IMAGEBUTTON_STATE_RELEASED);
    lv_obj_set_pos(bt_in_ble_dec, 6, 265);
    lv_obj_add_event_cb(bt_in_ble_dec, event_bt_in_ble_dec, LV_EVENT_ALL, NULL);
}

static void event_bt_in_pc_inc(lv_event_t * e)
{
	lv_event_code_t code = lv_event_get_code(e);

	if(code == LV_EVENT_CLICKED || code == LV_EVENT_LONG_PRESSED_REPEAT) {
		led_ring_inc(&ring_in_pc);
	}
}

static void event_bt_in_pc_dec(lv_event_t * e)
{
	lv_event_code_t code = lv_event_get_code(e);

	if(code == LV_EVENT_CLICKED || code == LV_EVENT_LONG_PRESSED_REPEAT) {
		led_ring_dec(&ring_in_pc);
	}
}

void create_buttons_vol_in_pc(void)
{
    // Button "+"
    bt_in_pc_inc = lv_imagebutton_create(Tela_Inputs);
    lv_imagebutton_set_src(bt_in_pc_inc, LV_IMAGEBUTTON_STATE_RELEASED, NULL, "S:/MAIN/BT_INC.bin", NULL);
    lv_imagebutton_set_src(bt_in_pc_inc, LV_IMAGEBUTTON_STATE_PRESSED, NULL, "S:/MAIN/BT_INC_P.bin", NULL);
    lv_imagebutton_set_src(bt_in_pc_inc, LV_IMAGEBUTTON_STATE_DISABLED, NULL, "S:/MAIN/BT_INC.bin", NULL);
    lv_imagebutton_set_src(bt_in_pc_inc, LV_IMAGEBUTTON_STATE_CHECKED_PRESSED, NULL, "S:/MAIN/BT_INC_P.bin", NULL);
    lv_imagebutton_set_src(bt_in_pc_inc, LV_IMAGEBUTTON_STATE_CHECKED_RELEASED, NULL, "S:/MAIN/BT_INC.bin", NULL);
    lv_imagebutton_set_src(bt_in_pc_inc, LV_IMAGEBUTTON_STATE_CHECKED_DISABLED, NULL, "S:/MAIN/BT_INC.bin", NULL);
    lv_obj_add_state(bt_in_pc_inc, LV_IMAGEBUTTON_STATE_RELEASED);
    lv_obj_set_pos(bt_in_pc_inc, 332, 265);
    lv_obj_add_event_cb(bt_in_pc_inc, event_bt_in_pc_inc, LV_EVENT_ALL, NULL);

    // Button "-"
    bt_in_pc_dec = lv_imagebutton_create(Tela_Inputs);
    lv_imagebutton_set_src(bt_in_pc_dec, LV_IMAGEBUTTON_STATE_RELEASED, NULL, "S:/MAIN/BT_DEC.bin", NULL);
    lv_imagebutton_set_src(bt_in_pc_dec, LV_IMAGEBUTTON_STATE_PRESSED, NULL, "S:/MAIN/BT_DEC_P.bin", NULL);
    lv_imagebutton_set_src(bt_in_pc_dec, LV_IMAGEBUTTON_STATE_DISABLED, NULL, "S:/MAIN/BT_DEC.bin", NULL);
    lv_imagebutton_set_src(bt_in_pc_dec, LV_IMAGEBUTTON_STATE_CHECKED_PRESSED, NULL, "S:/MAIN/BT_DEC_P.bin", NULL);
    lv_imagebutton_set_src(bt_in_pc_dec, LV_IMAGEBUTTON_STATE_CHECKED_RELEASED, NULL, "S:/MAIN/BT_DEC.bin", NULL);
    lv_imagebutton_set_src(bt_in_pc_dec, LV_IMAGEBUTTON_STATE_CHECKED_DISABLED, NULL, "S:/MAIN/BT_DEC.bin", NULL);
    lv_obj_add_state(bt_in_pc_dec, LV_IMAGEBUTTON_STATE_RELEASED);
    lv_obj_set_pos(bt_in_pc_dec, 193, 265);
    lv_obj_add_event_cb(bt_in_pc_dec, event_bt_in_pc_dec, LV_EVENT_ALL, NULL);
}

void create_input_barmeter_xlr(void)
{
	in_xlr_l.on       = NULL;
	in_xlr_l.last_seg = -1;
	in_xlr_l.x        = 10;
	in_xlr_l.y        = 41;
	in_xlr_l.w        = BAR_W;
	in_xlr_l.h        = BAR_H;
	in_xlr_l.range    = BAR_RANGE;
	in_xlr_l.segs     = BAR_SEGMENTS;
	in_xlr_l.bounds   = NULL;
	in_xlr_l.img_off  = &LED_OFF;
	in_xlr_l.img_on   = &LED;
	in_xlr_l.rotation = 0;

	in_xlr_r.on       = NULL;
	in_xlr_r.last_seg = -1;
	in_xlr_r.x        = 33;
	in_xlr_r.y        = 41;
	in_xlr_r.w        = BAR_W;
	in_xlr_r.h        = BAR_H;
	in_xlr_r.range    = BAR_RANGE;
	in_xlr_r.segs     = BAR_SEGMENTS;
	in_xlr_r.bounds   = NULL;
	in_xlr_r.img_off  = &LED_OFF;
	in_xlr_r.img_on   = &LED;
	in_xlr_r.rotation = 0;

	barmeter_create(Tela_Inputs, &in_xlr_l);
	barmeter_create(Tela_Inputs, &in_xlr_r);

	barmeter_set(&in_xlr_l, 1);
	barmeter_set(&in_xlr_r, 1);
}

void create_output_barmeter_xlr(void)
{
	out_xlr_l.on       = NULL;
	out_xlr_l.last_seg = -1;
	out_xlr_l.x        = 145;
	out_xlr_l.y        = 41;
	out_xlr_l.w        = BAR_W;
	out_xlr_l.h        = BAR_H;
	out_xlr_l.range    = BAR_RANGE;
	out_xlr_l.segs     = BAR_SEGMENTS;
	out_xlr_l.bounds   = NULL;
	out_xlr_l.img_off  = &LED_OFF;
	out_xlr_l.img_on   = &LED;
	out_xlr_r.rotation = 0;

	out_xlr_r.on       = NULL;
	out_xlr_r.last_seg = -1;
	out_xlr_r.x        = 168;
	out_xlr_r.y        = 41;
	out_xlr_r.w        = BAR_W;
	out_xlr_r.h        = BAR_H;
	out_xlr_r.range    = BAR_RANGE;
	out_xlr_r.segs     = BAR_SEGMENTS;
	out_xlr_r.bounds   = NULL;
	out_xlr_r.img_off  = &LED_OFF;
	out_xlr_r.img_on   = &LED;
	out_xlr_r.rotation = 0;

	barmeter_create(Tela_Inputs, &out_xlr_l);
	barmeter_create(Tela_Inputs, &out_xlr_r);

	barmeter_set(&out_xlr_l, 4);
	barmeter_set(&out_xlr_r, 4);
}

void create_input_barmeter_usb(void)
{
	in_usb_l.on       = NULL;
	in_usb_l.last_seg = -1;
	in_usb_l.x        = 195;
	in_usb_l.y        = 41;
	in_usb_l.w        = BAR_W;
	in_usb_l.h        = BAR_H;
	in_usb_l.range    = BAR_RANGE;
	in_usb_l.segs     = BAR_SEGMENTS;
	in_usb_l.bounds   = NULL;
	in_usb_l.img_off  = &LED_OFF;
	in_usb_l.img_on   = &LED;
	in_usb_l.rotation = 0;

	in_usb_r.on       = NULL;
	in_usb_r.last_seg = -1;
	in_usb_r.x        = 217;
	in_usb_r.y        = 41;
	in_usb_r.w        = BAR_W;
	in_usb_r.h        = BAR_H;
	in_usb_r.range    = BAR_RANGE;
	in_usb_r.segs     = BAR_SEGMENTS;
	in_usb_r.bounds   = NULL;
	in_usb_r.img_off  = &LED_OFF;
	in_usb_r.img_on   = &LED;
	in_usb_r.rotation = 0;

	barmeter_create(Tela_Inputs, &in_usb_l);
	barmeter_create(Tela_Inputs, &in_usb_r);

	barmeter_set(&in_usb_l, 3);
	barmeter_set(&in_usb_r, 3);
}

void create_output_barmeter_usb(void)
{
	out_usb_l.on       = NULL;
	out_usb_l.last_seg = -1;
	out_usb_l.x        = 332;
	out_usb_l.y        = 41;
	out_usb_l.w        = BAR_W;
	out_usb_l.h        = BAR_H;
	out_usb_l.range    = BAR_RANGE;
	out_usb_l.segs     = BAR_SEGMENTS;
	out_usb_l.bounds   = NULL;
	out_usb_l.img_off  = &LED_OFF;
	out_usb_l.img_on   = &LED;
	out_usb_l.rotation = 0;

	out_usb_r.on       = NULL;
	out_usb_r.last_seg = -1;
	out_usb_r.x        = 355;
	out_usb_r.y        = 41;
	out_usb_r.w        = BAR_W;
	out_usb_r.h        = BAR_H;
	out_usb_r.range    = BAR_RANGE;
	out_usb_r.segs     = BAR_SEGMENTS;
	out_usb_r.bounds   = NULL;
	out_usb_r.img_off  = &LED_OFF;
	out_usb_r.img_on   = &LED;
	out_usb_r.rotation = 0;

	barmeter_create(Tela_Inputs, &out_usb_l);
	barmeter_create(Tela_Inputs, &out_usb_r);

	barmeter_set(&out_usb_l, 6);
	barmeter_set(&out_usb_r, 6);
}

void create_input_barmeter_ble(void)
{
	in_ble_l.on       = NULL;
	in_ble_l.last_seg = -1;
	in_ble_l.x        = 10;
	in_ble_l.y        = 177;
	in_ble_l.w        = BAR_W;
	in_ble_l.h        = BAR_H;
	in_ble_l.range    = BAR_RANGE;
	in_ble_l.segs     = BAR_SEGMENTS;
	in_ble_l.bounds   = NULL;
	in_ble_l.img_off  = &LED_OFF;
	in_ble_l.img_on   = &LED;
	in_ble_l.rotation = 0;

	in_ble_r.on       = NULL;
	in_ble_r.last_seg = -1;
	in_ble_r.x        = 33;
	in_ble_r.y        = 177;
	in_ble_r.w        = BAR_W;
	in_ble_r.h        = BAR_H;
	in_ble_r.range    = BAR_RANGE;
	in_ble_r.segs     = BAR_SEGMENTS;
	in_ble_r.bounds   = NULL;
	in_ble_r.img_off  = &LED_OFF;
	in_ble_r.img_on   = &LED;
	in_ble_r.rotation = 0;

	barmeter_create(Tela_Inputs, &in_ble_l);
	barmeter_create(Tela_Inputs, &in_ble_r);

	barmeter_set(&in_ble_l, 7);
	barmeter_set(&in_ble_r, 7);
}

void create_output_barmeter_ble(void)
{
	out_ble_l.on       = NULL;
	out_ble_l.last_seg = -1;
	out_ble_l.x        = 145;
	out_ble_l.y        = 177;
	out_ble_l.w        = BAR_W;
	out_ble_l.h        = BAR_H;
	out_ble_l.range    = BAR_RANGE;
	out_ble_l.segs     = BAR_SEGMENTS;
	out_ble_l.bounds   = NULL;
	out_ble_l.img_off  = &LED_OFF;
	out_ble_l.img_on   = &LED;
	out_ble_l.rotation = 0;

	out_ble_r.on       = NULL;
	out_ble_r.last_seg = -1;
	out_ble_r.x        = 168;
	out_ble_r.y        = 177;
	out_ble_r.w        = BAR_W;
	out_ble_r.h        = BAR_H;
	out_ble_r.range    = BAR_RANGE;
	out_ble_r.segs     = BAR_SEGMENTS;
	out_ble_r.bounds   = NULL;
	out_ble_r.img_off  = &LED_OFF;
	out_ble_r.img_on   = &LED;
	out_ble_r.rotation = 0;

	barmeter_create(Tela_Inputs, &out_ble_l);
	barmeter_create(Tela_Inputs, &out_ble_r);

	barmeter_set(&out_ble_l, 13);
	barmeter_set(&out_ble_r, 13);
}

void create_input_barmeter_pc(void)
{
	in_pc_l.on       = NULL;
	in_pc_l.last_seg = -1;
	in_pc_l.x        = 195;
	in_pc_l.y        = 177;
	in_pc_l.w        = BAR_W;
	in_pc_l.h        = BAR_H;
	in_pc_l.range    = BAR_RANGE;
	in_pc_l.segs     = BAR_SEGMENTS;
	in_pc_l.bounds   = NULL;
	in_pc_l.img_off  = &LED_OFF;
	in_pc_l.img_on   = &LED;
	in_pc_l.rotation = 0;

	in_pc_r.on       = NULL;
	in_pc_r.last_seg = -1;
	in_pc_r.x        = 217;
	in_pc_r.y        = 177;
	in_pc_r.w        = BAR_W;
	in_pc_r.h        = BAR_H;
	in_pc_r.range    = BAR_RANGE;
	in_pc_r.segs     = BAR_SEGMENTS;
	in_pc_r.bounds   = NULL;
	in_pc_r.img_off  = &LED_OFF;
	in_pc_r.img_on   = &LED;
	in_pc_r.rotation = 0;

	barmeter_create(Tela_Inputs, &in_pc_l);
	barmeter_create(Tela_Inputs, &in_pc_r);

	barmeter_set(&in_pc_l, 7);
	barmeter_set(&in_pc_r, 7);
}

void create_output_barmeter_pc(void)
{
	out_pc_l.on       = NULL;
	out_pc_l.last_seg = -1;
	out_pc_l.x        = 332;
	out_pc_l.y        = 177;
	out_pc_l.w        = BAR_W;
	out_pc_l.h        = BAR_H;
	out_pc_l.range    = BAR_RANGE;
	out_pc_l.segs     = BAR_SEGMENTS;
	out_pc_l.bounds   = NULL;
	out_pc_l.img_off  = &LED_OFF;
	out_pc_l.img_on   = &LED;
	out_pc_l.rotation = 0;

	out_pc_r.on       = NULL;
	out_pc_r.last_seg = -1;
	out_pc_r.x        = 355;
	out_pc_r.y        = 177;
	out_pc_r.w        = BAR_W;
	out_pc_r.h        = BAR_H;
	out_pc_r.range    = BAR_RANGE;
	out_pc_r.segs     = BAR_SEGMENTS;
	out_pc_r.bounds   = NULL;
	out_pc_r.img_off  = &LED_OFF;
	out_pc_r.img_on   = &LED;
	out_pc_r.rotation = 0;

	barmeter_create(Tela_Inputs, &out_pc_l);
	barmeter_create(Tela_Inputs, &out_pc_r);

	barmeter_set(&out_pc_l, 8);
	barmeter_set(&out_pc_r, 8);
}
