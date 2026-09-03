/*
 * Screen_Menu_PROC.c
 *
 *  Created on: 28 de ago. de 2026
 *      Author: rinaldo.santos
 */

#include "stdbool.h"
#include "rng.h"
#include "stdio.h"
#include "string.h"

#include "../App/UI/Screen_Menu_PROC.h"
#include "../App/UI/Screen_Utils.h"

LV_FONT_DECLARE(Neue_Medium_12);
LV_FONT_DECLARE(Neue_Medium_14);

void create_buttons_input_proc(void);
void create_buttons_output_proc(void);
void create_button_proc_save(void);
void create_screen_proc_labels(void);
void create_buttons_output_mpx_proc(void);
void create_proc_sel(void);
void create_proc_emphase(void);
void create_proc_stereo(void);

lv_obj_t * Tela_Menu_PROC = NULL;
static lv_obj_t * img_fundo_menu_proc = NULL;
static lv_obj_t * bt_proc_save = NULL;
static lv_obj_t * bt_proc_in_xlr = NULL;
static lv_obj_t * bt_proc_in_pc = NULL;
static lv_obj_t * bt_proc_in_mp3 = NULL;
static lv_obj_t * bt_proc_in_ble = NULL;
static lv_obj_t * bt_proc_out_xlr = NULL;
static lv_obj_t * bt_proc_out_pc = NULL;
static lv_obj_t * label_screen_proc[4];
static lv_obj_t * bt_proc_out_mpx = NULL;
static lv_obj_t * bt_proc_out_aes = NULL;
static lv_obj_t * bt_proc_on = NULL;
static lv_obj_t * bt_proc_bypass = NULL;
static lv_obj_t * bt_proc_50 = NULL;
static lv_obj_t * bt_proc_75 = NULL;
static lv_obj_t * bt_proc_stereo = NULL;
static lv_obj_t * bt_proc_mono = NULL;

static uint32_t user_data_bt_in_proc = 0;
static uint32_t user_data_bt_out_proc = 0;
static uint32_t user_data_bt_proc_mpx = 0;
static uint32_t user_data_bt_proc_on = 0;
static uint32_t user_data_bt_proc_50 = 0;
static uint32_t user_data_bt_proc_stereo = 0;

void Screen_Menu_PROC_Create(void)
{
	Tela_Menu_PROC = lv_obj_create(NULL);
	lv_obj_clear_flag(Tela_Menu_PROC, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLLABLE);
	lv_obj_set_style_bg_color(Tela_Menu_PROC, lv_color_hex(0x000000), 0);
	lv_obj_set_style_bg_grad_color(Tela_Menu_PROC, lv_color_hex(0x000000), 0);

	// Imagem de Fundo
	img_fundo_menu_proc = lv_img_create(Tela_Menu_PROC);
	lv_img_set_src(img_fundo_menu_proc, "S:/PROCESSOR/TELA_PROCESSOR.bin");
	lv_obj_set_pos(img_fundo_menu_proc, 0, 0);

	// Input
	create_buttons_input_proc();

	// Buttons Output
	create_buttons_output_proc();

	// Buttons Save
	create_button_proc_save();

	// Labels
	create_screen_proc_labels();

	// Fig MPX
	create_buttons_output_mpx_proc();

	// Selecoes
	create_proc_sel();
	create_proc_emphase();
	create_proc_stereo();

	create_button_back_main(Tela_Menu_PROC, 380, 283, PAGE_MAIN);
}

static void event_bt_proc_in(lv_event_t * e)
{
	lv_event_code_t code = lv_event_get_code(e);

	if(code == LV_EVENT_CLICKED) {
		uint32_t btn = (uint32_t)(uintptr_t)lv_event_get_user_data(e);

		switch(btn) {
			case 0:
				lv_imagebutton_set_state(bt_proc_in_xlr, LV_IMAGEBUTTON_STATE_CHECKED_DISABLED);
				lv_imagebutton_set_state(bt_proc_in_pc,  LV_IMAGEBUTTON_STATE_RELEASED);
				lv_imagebutton_set_state(bt_proc_in_mp3, LV_IMAGEBUTTON_STATE_RELEASED);
				lv_imagebutton_set_state(bt_proc_in_ble, LV_IMAGEBUTTON_STATE_RELEASED);
				break;
			case 1:
				lv_imagebutton_set_state(bt_proc_in_xlr, LV_IMAGEBUTTON_STATE_RELEASED);
				lv_imagebutton_set_state(bt_proc_in_pc,  LV_IMAGEBUTTON_STATE_CHECKED_DISABLED);
				lv_imagebutton_set_state(bt_proc_in_mp3, LV_IMAGEBUTTON_STATE_RELEASED);
				lv_imagebutton_set_state(bt_proc_in_ble, LV_IMAGEBUTTON_STATE_RELEASED);
				break;
			case 2:
				lv_imagebutton_set_state(bt_proc_in_xlr, LV_IMAGEBUTTON_STATE_RELEASED);
				lv_imagebutton_set_state(bt_proc_in_pc,  LV_IMAGEBUTTON_STATE_RELEASED);
				lv_imagebutton_set_state(bt_proc_in_mp3, LV_IMAGEBUTTON_STATE_CHECKED_DISABLED);
				lv_imagebutton_set_state(bt_proc_in_ble, LV_IMAGEBUTTON_STATE_RELEASED);
				break;
			case 3:
				lv_imagebutton_set_state(bt_proc_in_xlr, LV_IMAGEBUTTON_STATE_RELEASED);
				lv_imagebutton_set_state(bt_proc_in_pc,  LV_IMAGEBUTTON_STATE_RELEASED);
				lv_imagebutton_set_state(bt_proc_in_mp3, LV_IMAGEBUTTON_STATE_RELEASED);
				lv_imagebutton_set_state(bt_proc_in_ble, LV_IMAGEBUTTON_STATE_CHECKED_DISABLED);
				break;
		}
	}
}

void create_buttons_input_proc(void)
{
	// XLR INPUT
	bt_proc_in_xlr = lv_imagebutton_create(Tela_Menu_PROC);
	lv_imagebutton_set_src(bt_proc_in_xlr, LV_IMAGEBUTTON_STATE_RELEASED, NULL, "S:/USB/BT_XLR_IN_OFF.bin", NULL);
	lv_imagebutton_set_src(bt_proc_in_xlr, LV_IMAGEBUTTON_STATE_PRESSED, NULL, "S:/USB/BT_XLR_IN_ON.bin", NULL);
	lv_imagebutton_set_src(bt_proc_in_xlr, LV_IMAGEBUTTON_STATE_DISABLED, NULL, "S:/USB/BT_XLR_IN_OFF.bin", NULL);
	lv_imagebutton_set_src(bt_proc_in_xlr, LV_IMAGEBUTTON_STATE_CHECKED_PRESSED, NULL, "S:/USB/BT_XLR_IN_ON.bin", NULL);
	lv_imagebutton_set_src(bt_proc_in_xlr, LV_IMAGEBUTTON_STATE_CHECKED_RELEASED, NULL, "S:/USB/BT_XLR_IN_OFF.bin", NULL);
	lv_imagebutton_set_src(bt_proc_in_xlr, LV_IMAGEBUTTON_STATE_CHECKED_DISABLED, NULL, "S:/USB/BT_XLR_IN_ON.bin", NULL);
	user_data_bt_in_proc = 0;
	lv_obj_add_event_cb(bt_proc_in_xlr, event_bt_proc_in, LV_EVENT_ALL, (void *)(uintptr_t)user_data_bt_in_proc);
	lv_obj_set_pos(bt_proc_in_xlr, 18, 18);
	lv_imagebutton_set_state(bt_proc_in_xlr, LV_IMAGEBUTTON_STATE_CHECKED_DISABLED);

	// PC INPUT
	bt_proc_in_pc = lv_imagebutton_create(Tela_Menu_PROC);
	lv_imagebutton_set_src(bt_proc_in_pc, LV_IMAGEBUTTON_STATE_RELEASED, NULL, "S:/USB/BT_PC_INPUT_OFF.bin", NULL);
	lv_imagebutton_set_src(bt_proc_in_pc, LV_IMAGEBUTTON_STATE_PRESSED, NULL, "S:/USB/BT_PC_INPUT_ON.bin", NULL);
	lv_imagebutton_set_src(bt_proc_in_pc, LV_IMAGEBUTTON_STATE_DISABLED, NULL, "S:/USB/BT_PC_INPUT_OFF.bin", NULL);
	lv_imagebutton_set_src(bt_proc_in_pc, LV_IMAGEBUTTON_STATE_CHECKED_PRESSED, NULL, "S:/USB/BT_PC_INPUT_ON.bin", NULL);
	lv_imagebutton_set_src(bt_proc_in_pc, LV_IMAGEBUTTON_STATE_CHECKED_RELEASED, NULL, "S:/USB/BT_PC_INPUT_OFF.bin", NULL);
	lv_imagebutton_set_src(bt_proc_in_pc, LV_IMAGEBUTTON_STATE_CHECKED_DISABLED, NULL, "S:/USB/BT_PC_INPUT_ON.bin", NULL);
	user_data_bt_in_proc = 1;
	lv_obj_add_event_cb(bt_proc_in_pc, event_bt_proc_in, LV_EVENT_ALL, (void *)(uintptr_t)user_data_bt_in_proc);
	lv_obj_set_pos(bt_proc_in_pc, 130, 18);
	lv_imagebutton_set_state(bt_proc_in_pc, LV_IMAGEBUTTON_STATE_RELEASED);

	// PC USB/MP3
	bt_proc_in_mp3 = lv_imagebutton_create(Tela_Menu_PROC);
	lv_imagebutton_set_src(bt_proc_in_mp3, LV_IMAGEBUTTON_STATE_RELEASED, NULL, "S:/USB/BT_MP3_IN_OFF.bin", NULL);
	lv_imagebutton_set_src(bt_proc_in_mp3, LV_IMAGEBUTTON_STATE_PRESSED, NULL, "S:/USB/BT_MP3_IN_ON.bin", NULL);
	lv_imagebutton_set_src(bt_proc_in_mp3, LV_IMAGEBUTTON_STATE_DISABLED, NULL, "S:/USB/BT_MP3_IN_OFF.bin", NULL);
	lv_imagebutton_set_src(bt_proc_in_mp3, LV_IMAGEBUTTON_STATE_CHECKED_PRESSED, NULL, "S:/USB/BT_MP3_IN_ON.bin", NULL);
	lv_imagebutton_set_src(bt_proc_in_mp3, LV_IMAGEBUTTON_STATE_CHECKED_RELEASED, NULL, "S:/USB/BT_MP3_IN_OFF.bin", NULL);
	lv_imagebutton_set_src(bt_proc_in_mp3, LV_IMAGEBUTTON_STATE_CHECKED_DISABLED, NULL, "S:/USB/BT_MP3_IN_ON.bin", NULL);
	user_data_bt_in_proc = 2;
	lv_obj_add_event_cb(bt_proc_in_mp3, event_bt_proc_in, LV_EVENT_ALL, (void *)(uintptr_t)user_data_bt_in_proc);
	lv_obj_set_pos(bt_proc_in_mp3, 242, 18);
	lv_imagebutton_set_state(bt_proc_in_mp3, LV_IMAGEBUTTON_STATE_RELEASED);

	// PC BLUETOOTH
	bt_proc_in_ble = lv_imagebutton_create(Tela_Menu_PROC);
	lv_imagebutton_set_src(bt_proc_in_ble, LV_IMAGEBUTTON_STATE_RELEASED, NULL, "S:/USB/BT_BLUETOOTH_OFF.bin", NULL);
	lv_imagebutton_set_src(bt_proc_in_ble, LV_IMAGEBUTTON_STATE_PRESSED, NULL, "S:/USB/BT_BLUETOOTH_ON.bin", NULL);
	lv_imagebutton_set_src(bt_proc_in_ble, LV_IMAGEBUTTON_STATE_DISABLED, NULL, "S:/USB/BT_BLUETOOTH_OFF.bin", NULL);
	lv_imagebutton_set_src(bt_proc_in_ble, LV_IMAGEBUTTON_STATE_CHECKED_PRESSED, NULL, "S:/USB/BT_BLUETOOTH_ON.bin", NULL);
	lv_imagebutton_set_src(bt_proc_in_ble, LV_IMAGEBUTTON_STATE_CHECKED_RELEASED, NULL, "S:/USB/BT_BLUETOOTH_OFF.bin", NULL);
	lv_imagebutton_set_src(bt_proc_in_ble, LV_IMAGEBUTTON_STATE_CHECKED_DISABLED, NULL, "S:/USB/BT_BLUETOOTH_OFF.bin", NULL);
	user_data_bt_in_proc = 3;
	lv_obj_add_event_cb(bt_proc_in_ble, event_bt_proc_in, LV_EVENT_ALL, (void *)(uintptr_t)user_data_bt_in_proc);
	lv_obj_set_pos(bt_proc_in_ble, 354, 18);
	lv_imagebutton_set_state(bt_proc_in_ble, LV_IMAGEBUTTON_STATE_RELEASED);
}

static void event_bt_proc_out(lv_event_t * e)
{
	lv_event_code_t code = lv_event_get_code(e);

	if(code == LV_EVENT_CLICKED) {
		uint32_t btn = (uint32_t)(uintptr_t)lv_event_get_user_data(e);

		switch(btn) {
			case 0:
				lv_imagebutton_set_state(bt_proc_out_xlr,  LV_IMAGEBUTTON_STATE_CHECKED_DISABLED);
				lv_imagebutton_set_state(bt_proc_out_pc, LV_IMAGEBUTTON_STATE_RELEASED);
				break;
			case 1:
				lv_imagebutton_set_state(bt_proc_out_xlr,  LV_IMAGEBUTTON_STATE_RELEASED);
				lv_imagebutton_set_state(bt_proc_out_pc, LV_IMAGEBUTTON_STATE_CHECKED_DISABLED);
				break;
		}
	}
}

void create_buttons_output_proc(void)
{
	// XLR OUTPUT
	bt_proc_out_xlr = lv_imagebutton_create(Tela_Menu_PROC);
	lv_imagebutton_set_src(bt_proc_out_xlr, LV_IMAGEBUTTON_STATE_RELEASED, NULL, "S:/USB/BT_XLR_OUT_OFF.bin", NULL);
	lv_imagebutton_set_src(bt_proc_out_xlr, LV_IMAGEBUTTON_STATE_PRESSED, NULL, "S:/USB/BT_XLR_OUT_ON.bin", NULL);
	lv_imagebutton_set_src(bt_proc_out_xlr, LV_IMAGEBUTTON_STATE_DISABLED, NULL, "S:/USB/BT_XLR_OUT_OFF.bin", NULL);
	lv_imagebutton_set_src(bt_proc_out_xlr, LV_IMAGEBUTTON_STATE_CHECKED_PRESSED, NULL, "S:/USB/BT_XLR_OUT_ON.bin", NULL);
	lv_imagebutton_set_src(bt_proc_out_xlr, LV_IMAGEBUTTON_STATE_CHECKED_RELEASED, NULL, "S:/USB/BT_XLR_OUT_OFF.bin", NULL);
	lv_imagebutton_set_src(bt_proc_out_xlr, LV_IMAGEBUTTON_STATE_CHECKED_DISABLED, NULL, "S:/USB/BT_XLR_OUT_ON.bin", NULL);
	user_data_bt_out_proc = 0;
	lv_obj_add_event_cb(bt_proc_out_xlr, event_bt_proc_out, LV_EVENT_ALL, (void *)(uintptr_t)user_data_bt_out_proc);
	lv_obj_set_pos(bt_proc_out_xlr, 12, 266);
	lv_imagebutton_set_state(bt_proc_out_xlr, LV_IMAGEBUTTON_STATE_CHECKED_DISABLED);

	// XLR OUTPUT
	bt_proc_out_pc = lv_imagebutton_create(Tela_Menu_PROC);
	lv_imagebutton_set_src(bt_proc_out_pc, LV_IMAGEBUTTON_STATE_RELEASED, NULL, "S:/USB/BT_PC_OUT_OFF.bin", NULL);
	lv_imagebutton_set_src(bt_proc_out_pc, LV_IMAGEBUTTON_STATE_PRESSED, NULL, "S:/USB/BT_PC_OUT_ON.bin", NULL);
	lv_imagebutton_set_src(bt_proc_out_pc, LV_IMAGEBUTTON_STATE_DISABLED, NULL, "S:/USB/BT_PC_OUT_OFF.bin", NULL);
	lv_imagebutton_set_src(bt_proc_out_pc, LV_IMAGEBUTTON_STATE_CHECKED_PRESSED, NULL, "S:/USB/BT_PC_OUT_ON.bin", NULL);
	lv_imagebutton_set_src(bt_proc_out_pc, LV_IMAGEBUTTON_STATE_CHECKED_RELEASED, NULL, "S:/USB/BT_PC_OUT_OFF.bin", NULL);
	lv_imagebutton_set_src(bt_proc_out_pc, LV_IMAGEBUTTON_STATE_CHECKED_DISABLED, NULL, "S:/USB/BT_PC_OUT_ON.bin", NULL);
	user_data_bt_out_proc = 1;
	lv_obj_add_event_cb(bt_proc_out_pc, event_bt_proc_out, LV_EVENT_ALL, (void *)(uintptr_t)user_data_bt_out_proc);
	lv_obj_set_pos(bt_proc_out_pc, 124, 266);
	lv_imagebutton_set_state(bt_proc_out_pc, LV_IMAGEBUTTON_STATE_RELEASED);
}

static void event_bt_proc_save(lv_event_t * e)
{
	lv_event_code_t code = lv_event_get_code(e);

	if(code == LV_EVENT_CLICKED) {

	}
}

void create_button_proc_save(void)
{
	// SAVE/APPLY
	bt_proc_save = lv_imagebutton_create(Tela_Menu_PROC);
	lv_imagebutton_set_src(bt_proc_save, LV_IMAGEBUTTON_STATE_RELEASED, NULL, "S:/USB/BT_SAVE.bin", NULL);
	lv_imagebutton_set_src(bt_proc_save, LV_IMAGEBUTTON_STATE_PRESSED, NULL, "S:/USB/BT_SAVE_P.bin", NULL);
	lv_imagebutton_set_src(bt_proc_save, LV_IMAGEBUTTON_STATE_DISABLED, NULL, "S:/USB/BT_SAVE.bin", NULL);
	lv_imagebutton_set_src(bt_proc_save, LV_IMAGEBUTTON_STATE_CHECKED_PRESSED, NULL, "S:/USB/BT_SAVE_P.bin", NULL);
	lv_imagebutton_set_src(bt_proc_save, LV_IMAGEBUTTON_STATE_CHECKED_RELEASED, NULL, "S:/USB/BT_SAVE.bin", NULL);
	lv_imagebutton_set_src(bt_proc_save, LV_IMAGEBUTTON_STATE_CHECKED_DISABLED, NULL, "S:/USB/BT_SAVE.bin", NULL);
	lv_obj_add_event_cb(bt_proc_save, event_bt_proc_save, LV_EVENT_ALL, NULL);
	lv_obj_set_pos(bt_proc_save, 281, 283);
	lv_imagebutton_set_state(bt_proc_save, LV_IMAGEBUTTON_STATE_RELEASED);

	// Text
    lv_obj_t * text_save = lv_label_create(bt_proc_save);
    lv_obj_set_width(text_save, LV_SIZE_CONTENT);
    lv_obj_set_height(text_save, LV_SIZE_CONTENT);
    lv_label_set_text(text_save, "SAVE/APPLY");
    lv_obj_set_style_text_color(text_save, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(text_save, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(text_save, &Neue_Medium_14, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_align_to(text_save, bt_proc_save, LV_ALIGN_CENTER, 0, 0);
}

void create_screen_proc_labels(void)
{
	// Labels
	for(uint8_t x = 0; x < 4; x++) {
		label_screen_proc[x] = lv_label_create(Tela_Menu_PROC);
		lv_obj_set_width(label_screen_proc[x], LV_SIZE_CONTENT);
		lv_obj_set_height(label_screen_proc[x], LV_SIZE_CONTENT);
		lv_obj_set_style_text_color(label_screen_proc[x], lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
		lv_obj_set_style_text_opa(label_screen_proc[x], 255, LV_PART_MAIN | LV_STATE_DEFAULT);
		lv_obj_set_style_text_font(label_screen_proc[x], &Neue_Medium_12, LV_PART_MAIN | LV_STATE_DEFAULT);
	}

	lv_label_set_text(label_screen_proc[0], "SELECT AUDIO SOURCE:");
	lv_label_set_text(label_screen_proc[1], "MODE: PROCESSOR");
	lv_label_set_text(label_screen_proc[2], "MPX OUT");
	lv_label_set_text(label_screen_proc[3], "AES192");

	lv_obj_align_to(label_screen_proc[0], Tela_Menu_PROC, LV_ALIGN_CENTER, 0, -148);
	lv_obj_align_to(label_screen_proc[1], Tela_Menu_PROC, LV_ALIGN_CENTER, -160, -148);
	lv_obj_align_to(label_screen_proc[2], Tela_Menu_PROC, LV_ALIGN_CENTER, 204, -62);
	lv_obj_align_to(label_screen_proc[3], Tela_Menu_PROC, LV_ALIGN_CENTER, 202, 85);
}

static void event_bt_proc_out_mpx(lv_event_t * e)
{
	lv_event_code_t code = lv_event_get_code(e);

	if(code == LV_EVENT_CLICKED) {
		uint32_t btn = (uint32_t)(uintptr_t)lv_event_get_user_data(e);

		switch(btn) {
			case 0:
				lv_imagebutton_set_state(bt_proc_out_mpx,  LV_IMAGEBUTTON_STATE_CHECKED_DISABLED);
				lv_imagebutton_set_state(bt_proc_out_aes, LV_IMAGEBUTTON_STATE_RELEASED);
				break;
			case 1:
				lv_imagebutton_set_state(bt_proc_out_mpx,  LV_IMAGEBUTTON_STATE_RELEASED);
				lv_imagebutton_set_state(bt_proc_out_aes, LV_IMAGEBUTTON_STATE_CHECKED_DISABLED);
				break;
		}
	}
}

void create_buttons_output_mpx_proc(void)
{
	// MPX OUT
	bt_proc_out_mpx = lv_imagebutton_create(Tela_Menu_PROC);
	lv_imagebutton_set_src(bt_proc_out_mpx, LV_IMAGEBUTTON_STATE_RELEASED, NULL, "S:/USB/LED_MPX_OFF.bin", NULL);
	lv_imagebutton_set_src(bt_proc_out_mpx, LV_IMAGEBUTTON_STATE_PRESSED, NULL, "S:/USB/LED_MPX_ON.bin", NULL);
	lv_imagebutton_set_src(bt_proc_out_mpx, LV_IMAGEBUTTON_STATE_DISABLED, NULL, "S:/USB/LED_MPX_OFF.bin", NULL);
	lv_imagebutton_set_src(bt_proc_out_mpx, LV_IMAGEBUTTON_STATE_CHECKED_PRESSED, NULL, "S:/USB/LED_MPX_ON.bin", NULL);
	lv_imagebutton_set_src(bt_proc_out_mpx, LV_IMAGEBUTTON_STATE_CHECKED_RELEASED, NULL, "S:/USB/LED_MPX_OFF.bin", NULL);
	lv_imagebutton_set_src(bt_proc_out_mpx, LV_IMAGEBUTTON_STATE_CHECKED_DISABLED, NULL, "S:/USB/LED_MPX_ON.bin", NULL);
	user_data_bt_proc_mpx = 0;
	lv_obj_add_event_cb(bt_proc_out_mpx, event_bt_proc_out_mpx, LV_EVENT_ALL, (void *)(uintptr_t)user_data_bt_proc_mpx);
	lv_obj_set_pos(bt_proc_out_mpx, 412, 108);
	lv_imagebutton_set_state(bt_proc_out_mpx, LV_IMAGEBUTTON_STATE_RELEASED);

	// AES192 OUT
	bt_proc_out_aes = lv_imagebutton_create(Tela_Menu_PROC);
	lv_imagebutton_set_src(bt_proc_out_aes, LV_IMAGEBUTTON_STATE_RELEASED, NULL, "S:/USB/LED_MPX_OFF.bin", NULL);
	lv_imagebutton_set_src(bt_proc_out_aes, LV_IMAGEBUTTON_STATE_PRESSED, NULL, "S:/USB/LED_MPX_ON.bin", NULL);
	lv_imagebutton_set_src(bt_proc_out_aes, LV_IMAGEBUTTON_STATE_DISABLED, NULL, "S:/USB/LED_MPX_OFF.bin", NULL);
	lv_imagebutton_set_src(bt_proc_out_aes, LV_IMAGEBUTTON_STATE_CHECKED_PRESSED, NULL, "S:/USB/LED_MPX_ON.bin", NULL);
	lv_imagebutton_set_src(bt_proc_out_aes, LV_IMAGEBUTTON_STATE_CHECKED_RELEASED, NULL, "S:/USB/LED_MPX_OFF.bin", NULL);
	lv_imagebutton_set_src(bt_proc_out_aes, LV_IMAGEBUTTON_STATE_CHECKED_DISABLED, NULL, "S:/USB/LED_MPX_ON.bin", NULL);
	user_data_bt_proc_mpx = 1;
	lv_obj_add_event_cb(bt_proc_out_aes, event_bt_proc_out_mpx, LV_EVENT_ALL, (void *)(uintptr_t)user_data_bt_proc_mpx);
	lv_obj_set_pos(bt_proc_out_aes, 412, 180);
	lv_imagebutton_set_state(bt_proc_out_aes, LV_IMAGEBUTTON_STATE_RELEASED);
}

static void event_bt_proc_on(lv_event_t * e)
{
	lv_event_code_t code = lv_event_get_code(e);

	if(code == LV_EVENT_CLICKED) {
		uint32_t btn = (uint32_t)(uintptr_t)lv_event_get_user_data(e);

		switch(btn) {
			case 0:
				lv_imagebutton_set_state(bt_proc_on,  LV_IMAGEBUTTON_STATE_CHECKED_DISABLED);
				lv_imagebutton_set_state(bt_proc_bypass, LV_IMAGEBUTTON_STATE_RELEASED);
				break;
			case 1:
				lv_imagebutton_set_state(bt_proc_on,  LV_IMAGEBUTTON_STATE_RELEASED);
				lv_imagebutton_set_state(bt_proc_bypass, LV_IMAGEBUTTON_STATE_CHECKED_DISABLED);
				break;
		}
	}
}

void create_proc_sel(void)
{
	// PROCESSOR ON
	bt_proc_on = lv_imagebutton_create(Tela_Menu_PROC);
	lv_imagebutton_set_src(bt_proc_on, LV_IMAGEBUTTON_STATE_RELEASED, NULL, "S:/USB/BT_OFF.bin", NULL);
	lv_imagebutton_set_src(bt_proc_on, LV_IMAGEBUTTON_STATE_PRESSED, NULL, "S:/USB/BT_ON.bin", NULL);
	lv_imagebutton_set_src(bt_proc_on, LV_IMAGEBUTTON_STATE_DISABLED, NULL, "S:/USB/BT_OFF.bin", NULL);
	lv_imagebutton_set_src(bt_proc_on, LV_IMAGEBUTTON_STATE_CHECKED_PRESSED, NULL, "S:/USB/BT_ON.bin", NULL);
	lv_imagebutton_set_src(bt_proc_on, LV_IMAGEBUTTON_STATE_CHECKED_RELEASED, NULL, "S:/USB/BT_OFF.bin", NULL);
	lv_imagebutton_set_src(bt_proc_on, LV_IMAGEBUTTON_STATE_CHECKED_DISABLED, NULL, "S:/USB/BT_ON.bin", NULL);
	user_data_bt_proc_on = 0;
	lv_obj_add_event_cb(bt_proc_on, event_bt_proc_on, LV_EVENT_ALL, (void *)(uintptr_t)user_data_bt_proc_on);
	lv_obj_set_pos(bt_proc_on, 20, 225);
	lv_imagebutton_set_state(bt_proc_on, LV_IMAGEBUTTON_STATE_CHECKED_DISABLED);

	// PROCESSOR BYPASS
	bt_proc_bypass = lv_imagebutton_create(Tela_Menu_PROC);
	lv_imagebutton_set_src(bt_proc_bypass, LV_IMAGEBUTTON_STATE_RELEASED, NULL, "S:/USB/BT_BYPASS_OFF.bin", NULL);
	lv_imagebutton_set_src(bt_proc_bypass, LV_IMAGEBUTTON_STATE_PRESSED, NULL, "S:/USB/BT_BYPASS_ON.bin", NULL);
	lv_imagebutton_set_src(bt_proc_bypass, LV_IMAGEBUTTON_STATE_DISABLED, NULL, "S:/USB/BT_BYPASS_OFF.bin", NULL);
	lv_imagebutton_set_src(bt_proc_bypass, LV_IMAGEBUTTON_STATE_CHECKED_PRESSED, NULL, "S:/USB/BT_BYPASS_ON.bin", NULL);
	lv_imagebutton_set_src(bt_proc_bypass, LV_IMAGEBUTTON_STATE_CHECKED_RELEASED, NULL, "S:/USB/BT_BYPASS_OFF.bin", NULL);
	lv_imagebutton_set_src(bt_proc_bypass, LV_IMAGEBUTTON_STATE_CHECKED_DISABLED, NULL, "S:/USB/BT_BYPASS_ON.bin", NULL);
	user_data_bt_proc_on = 1;
	lv_obj_add_event_cb(bt_proc_bypass, event_bt_proc_on, LV_EVENT_ALL, (void *)(uintptr_t)user_data_bt_proc_on);
	lv_obj_set_pos(bt_proc_bypass, 70, 225);
	lv_imagebutton_set_state(bt_proc_bypass, LV_IMAGEBUTTON_STATE_RELEASED);
}

static void event_bt_proc_emphase(lv_event_t * e)
{
	lv_event_code_t code = lv_event_get_code(e);

	if(code == LV_EVENT_CLICKED) {
		uint32_t btn = (uint32_t)(uintptr_t)lv_event_get_user_data(e);

		switch(btn) {
			case 0:
				lv_imagebutton_set_state(bt_proc_50,  LV_IMAGEBUTTON_STATE_CHECKED_DISABLED);
				lv_imagebutton_set_state(bt_proc_75, LV_IMAGEBUTTON_STATE_RELEASED);
				break;
			case 1:
				lv_imagebutton_set_state(bt_proc_50,  LV_IMAGEBUTTON_STATE_RELEASED);
				lv_imagebutton_set_state(bt_proc_75, LV_IMAGEBUTTON_STATE_CHECKED_DISABLED);
				break;
		}
	}
}

void create_proc_emphase(void)
{
	// 50uS
	bt_proc_50 = lv_imagebutton_create(Tela_Menu_PROC);
	lv_imagebutton_set_src(bt_proc_50, LV_IMAGEBUTTON_STATE_RELEASED, NULL, "S:/USB/BT_50us_OFF.bin", NULL);
	lv_imagebutton_set_src(bt_proc_50, LV_IMAGEBUTTON_STATE_PRESSED, NULL, "S:/USB/BT_50us_ON.bin", NULL);
	lv_imagebutton_set_src(bt_proc_50, LV_IMAGEBUTTON_STATE_DISABLED, NULL, "S:/USB/BT_50us_OFF.bin", NULL);
	lv_imagebutton_set_src(bt_proc_50, LV_IMAGEBUTTON_STATE_CHECKED_PRESSED, NULL, "S:/USB/BT_50us_ON.bin", NULL);
	lv_imagebutton_set_src(bt_proc_50, LV_IMAGEBUTTON_STATE_CHECKED_RELEASED, NULL, "S:/USB/BT_50us_OFF.bin", NULL);
	lv_imagebutton_set_src(bt_proc_50, LV_IMAGEBUTTON_STATE_CHECKED_DISABLED, NULL, "S:/USB/BT_50us_ON.bin", NULL);
	user_data_bt_proc_50 = 0;
	lv_obj_add_event_cb(bt_proc_50, event_bt_proc_emphase, LV_EVENT_ALL, (void *)(uintptr_t)user_data_bt_proc_50);
	lv_obj_set_pos(bt_proc_50, 156, 225);
	lv_imagebutton_set_state(bt_proc_50, LV_IMAGEBUTTON_STATE_RELEASED);

	// 75uS
	bt_proc_75 = lv_imagebutton_create(Tela_Menu_PROC);
	lv_imagebutton_set_src(bt_proc_75, LV_IMAGEBUTTON_STATE_RELEASED, NULL, "S:/USB/BT_75us_OFF.bin", NULL);
	lv_imagebutton_set_src(bt_proc_75, LV_IMAGEBUTTON_STATE_PRESSED, NULL, "S:/USB/BT_75us_ON.bin", NULL);
	lv_imagebutton_set_src(bt_proc_75, LV_IMAGEBUTTON_STATE_DISABLED, NULL, "S:/USB/BT_75us_OFF.bin", NULL);
	lv_imagebutton_set_src(bt_proc_75, LV_IMAGEBUTTON_STATE_CHECKED_PRESSED, NULL, "S:/USB/BT_75us_ON.bin", NULL);
	lv_imagebutton_set_src(bt_proc_75, LV_IMAGEBUTTON_STATE_CHECKED_RELEASED, NULL, "S:/USB/BT_75us_OFF.bin", NULL);
	lv_imagebutton_set_src(bt_proc_75, LV_IMAGEBUTTON_STATE_CHECKED_DISABLED, NULL, "S:/USB/BT_75us_ON.bin", NULL);
	user_data_bt_proc_50 = 1;
	lv_obj_add_event_cb(bt_proc_75, event_bt_proc_emphase, LV_EVENT_ALL, (void *)(uintptr_t)user_data_bt_proc_50);
	lv_obj_set_pos(bt_proc_75, 214, 225);
	lv_imagebutton_set_state(bt_proc_75, LV_IMAGEBUTTON_STATE_CHECKED_DISABLED);
}

static void event_bt_proc_stereo(lv_event_t * e)
{
	lv_event_code_t code = lv_event_get_code(e);

	if(code == LV_EVENT_CLICKED) {
		uint32_t btn = (uint32_t)(uintptr_t)lv_event_get_user_data(e);

		switch(btn) {
			case 0:
				lv_imagebutton_set_state(bt_proc_stereo,  LV_IMAGEBUTTON_STATE_CHECKED_DISABLED);
				lv_imagebutton_set_state(bt_proc_mono, LV_IMAGEBUTTON_STATE_RELEASED);
				break;
			case 1:
				lv_imagebutton_set_state(bt_proc_stereo,  LV_IMAGEBUTTON_STATE_RELEASED);
				lv_imagebutton_set_state(bt_proc_mono, LV_IMAGEBUTTON_STATE_CHECKED_DISABLED);
				break;
		}
	}
}

void create_proc_stereo(void)
{
	// STEREO
	bt_proc_stereo = lv_imagebutton_create(Tela_Menu_PROC);
	lv_imagebutton_set_src(bt_proc_stereo, LV_IMAGEBUTTON_STATE_RELEASED, NULL, "S:/USB/BT_STEREO_OFF.bin", NULL);
	lv_imagebutton_set_src(bt_proc_stereo, LV_IMAGEBUTTON_STATE_PRESSED, NULL, "S:/USB/BT_STEREO_ON.bin", NULL);
	lv_imagebutton_set_src(bt_proc_stereo, LV_IMAGEBUTTON_STATE_DISABLED, NULL, "S:/USB/BT_STEREO_OFF.bin", NULL);
	lv_imagebutton_set_src(bt_proc_stereo, LV_IMAGEBUTTON_STATE_CHECKED_PRESSED, NULL, "S:/USB/BT_STEREO_ON.bin", NULL);
	lv_imagebutton_set_src(bt_proc_stereo, LV_IMAGEBUTTON_STATE_CHECKED_RELEASED, NULL, "S:/USB/BT_STEREO_OFF.bin", NULL);
	lv_imagebutton_set_src(bt_proc_stereo, LV_IMAGEBUTTON_STATE_CHECKED_DISABLED, NULL, "S:/USB/BT_STEREO_ON.bin", NULL);
	user_data_bt_proc_stereo = 0;
	lv_obj_add_event_cb(bt_proc_stereo, event_bt_proc_stereo, LV_EVENT_ALL, (void *)(uintptr_t)user_data_bt_proc_stereo);
	lv_obj_set_pos(bt_proc_stereo, 300, 225);
	lv_imagebutton_set_state(bt_proc_stereo, LV_IMAGEBUTTON_STATE_CHECKED_DISABLED);

	// MONO
	bt_proc_mono = lv_imagebutton_create(Tela_Menu_PROC);
	lv_imagebutton_set_src(bt_proc_mono, LV_IMAGEBUTTON_STATE_RELEASED, NULL, "S:/USB/BT_MONO_OFF.bin", NULL);
	lv_imagebutton_set_src(bt_proc_mono, LV_IMAGEBUTTON_STATE_PRESSED, NULL, "S:/USB/BT_MONO_ON.bin", NULL);
	lv_imagebutton_set_src(bt_proc_mono, LV_IMAGEBUTTON_STATE_DISABLED, NULL, "S:/USB/BT_MONO_OFF.bin", NULL);
	lv_imagebutton_set_src(bt_proc_mono, LV_IMAGEBUTTON_STATE_CHECKED_PRESSED, NULL, "S:/USB/BT_MONO_ON.bin", NULL);
	lv_imagebutton_set_src(bt_proc_mono, LV_IMAGEBUTTON_STATE_CHECKED_RELEASED, NULL, "S:/USB/BT_MONO_OFF.bin", NULL);
	lv_imagebutton_set_src(bt_proc_mono, LV_IMAGEBUTTON_STATE_CHECKED_DISABLED, NULL, "S:/USB/BT_MONO_ON.bin", NULL);
	user_data_bt_proc_stereo = 1;
	lv_obj_add_event_cb(bt_proc_mono, event_bt_proc_stereo, LV_EVENT_ALL, (void *)(uintptr_t)user_data_bt_proc_stereo);
	lv_obj_set_pos(bt_proc_mono, 350, 225);
	lv_imagebutton_set_state(bt_proc_mono, LV_IMAGEBUTTON_STATE_RELEASED);
}
