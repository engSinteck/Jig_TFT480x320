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

LV_FONT_DECLARE(Neue_Medium_11);
LV_FONT_DECLARE(Neue_Medium_14);

extern void create_barmeter_left(void);
extern void create_barmeter_right(void);

void create_labels_inputs(void);
void create_text_inputs(void);
void create_buttons_vol_in_xlr(void);
void create_buttons_vol_in_usb(void);
void create_buttons_vol_in_phone(void);
void create_buttons_vol_in_bluetooth(void);
void create_buttons_vol_in_pc(void);

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

static led_ring_t ring_xlr;

void Screen_Inputs_Create(void)
{
	Tela_Inputs = lv_obj_create(NULL);
	lv_obj_clear_flag(Tela_Inputs, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLLABLE);
	lv_obj_set_style_bg_color(Tela_Inputs, lv_color_hex(0x000000), 0);
	lv_obj_set_style_bg_grad_color(Tela_Inputs, lv_color_hex(0x000000), 0);

	// Imagem de Fundo
	img_fundo_inputs = lv_img_create(Tela_Inputs);
	//lv_img_set_src(img_fundo_inputs, "S:/Inputs/TELA_FUNDO.bin");
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
	//create_barmeter_left();
	//create_barmeter_right();
	// Led Rings
	led_ring_create(Tela_Inputs, &ring_xlr, 56, 39);
	//
	create_button_back_main(Tela_Inputs);
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
    lv_obj_set_pos(text_inputs_indic[7], 11, 164);
    lv_obj_set_pos(text_inputs_indic[8], 70, 164);
    lv_obj_set_pos(text_inputs_indic[9], 140, 164);
    lv_obj_set_pos(text_inputs_indic[10], 200, 164);
    lv_obj_set_pos(text_inputs_indic[11], 260, 164);
    lv_obj_set_pos(text_inputs_indic[12], 330, 164);
}

static void event_bt_in_xlr_inc(lv_event_t * e)
{
	lv_event_code_t code = lv_event_get_code(e);

	if(code == LV_EVENT_CLICKED || code == LV_EVENT_LONG_PRESSED_REPEAT) {
		led_ring_inc(&ring_xlr);
	 }
}

static void event_bt_in_xlr_dec(lv_event_t * e)
{
	lv_event_code_t code = lv_event_get_code(e);

	if(code == LV_EVENT_CLICKED || code == LV_EVENT_LONG_PRESSED_REPEAT) {
		led_ring_dec(&ring_xlr);
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

	 }
}

static void event_bt_in_usb_dec(lv_event_t * e)
{
	lv_event_code_t code = lv_event_get_code(e);

	if(code == LV_EVENT_CLICKED || code == LV_EVENT_LONG_PRESSED_REPEAT) {

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

	 }
}

static void event_bt_in_phone_dec(lv_event_t * e)
{
	lv_event_code_t code = lv_event_get_code(e);

	if(code == LV_EVENT_CLICKED || code == LV_EVENT_LONG_PRESSED_REPEAT) {

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

	 }
}

static void event_bt_in_ble_dec(lv_event_t * e)
{
	lv_event_code_t code = lv_event_get_code(e);

	if(code == LV_EVENT_CLICKED || code == LV_EVENT_LONG_PRESSED_REPEAT) {

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

	 }
}

static void event_bt_in_pc_dec(lv_event_t * e)
{
	lv_event_code_t code = lv_event_get_code(e);

	if(code == LV_EVENT_CLICKED || code == LV_EVENT_LONG_PRESSED_REPEAT) {

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
