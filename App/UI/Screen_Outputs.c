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

LV_FONT_DECLARE(Neue_Medium_14);

void create_labels_outputs(void);
void create_buttons_vol_out_xlr(void);
void create_buttons_vol_out_aes(void);
void create_buttons_vol_out_phone(void);
void create_buttons_vol_out_mpx1(void);
void create_buttons_vol_out_mpx2(void);

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

	create_button_back_main(Tela_Outputs);
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

	 }
}

static void event_bt_out_xlr_dec(lv_event_t * e)
{
	lv_event_code_t code = lv_event_get_code(e);

	if(code == LV_EVENT_CLICKED || code == LV_EVENT_LONG_PRESSED_REPEAT) {

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

	 }
}

static void event_bt_out_aes_dec(lv_event_t * e)
{
	lv_event_code_t code = lv_event_get_code(e);

	if(code == LV_EVENT_CLICKED || code == LV_EVENT_LONG_PRESSED_REPEAT) {

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

	 }
}

static void event_bt_out_phone_dec(lv_event_t * e)
{
	lv_event_code_t code = lv_event_get_code(e);

	if(code == LV_EVENT_CLICKED || code == LV_EVENT_LONG_PRESSED_REPEAT) {

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

	 }
}

static void event_bt_out_mpx1_dec(lv_event_t * e)
{
	lv_event_code_t code = lv_event_get_code(e);

	if(code == LV_EVENT_CLICKED || code == LV_EVENT_LONG_PRESSED_REPEAT) {

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

	 }
}

static void event_bt_out_mpx2_dec(lv_event_t * e)
{
	lv_event_code_t code = lv_event_get_code(e);

	if(code == LV_EVENT_CLICKED || code == LV_EVENT_LONG_PRESSED_REPEAT) {

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

