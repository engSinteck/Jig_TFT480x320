/*
 * Screen_Menu_USB.c
 *
 *  Created on: 28 de ago. de 2026
 *      Author: rinaldo.santos
 */

#include "stdbool.h"
#include "rng.h"
#include "stdio.h"
#include "string.h"

#include "../App/UI/Screen_Menu_USB.h"
#include "../App/UI/Screen_Utils.h"

LV_FONT_DECLARE(Neue_Medium_12);
LV_FONT_DECLARE(Neue_Medium_14);

void create_buttons_input_usb(void);
void create_buttons_output_usb(void);
void create_buttons_output_mpx(void);
void create_button_usb_save(void);
void create_screen_usb_labels(void);

lv_obj_t * Tela_Menu_USB = NULL;
static lv_obj_t * img_fundo_menu_usb = NULL;
static lv_obj_t * bt_usb_in_xlr = NULL;
static lv_obj_t * bt_usb_in_pc = NULL;
static lv_obj_t * bt_usb_in_mp3 = NULL;
static lv_obj_t * bt_usb_in_ble = NULL;
static lv_obj_t * bt_usb_out_xlr = NULL;
static lv_obj_t * bt_usb_out_pc = NULL;
static lv_obj_t * bt_usb_out_mpx = NULL;
static lv_obj_t * bt_usb_out_aes = NULL;
static lv_obj_t * bt_usb_save = NULL;
static lv_obj_t * label_screen_usb[8];

static uint32_t user_data_bt_mpx = 0;
static uint32_t user_data_bt_out = 0;
static uint32_t user_data_bt_in = 0;

void Screen_Menu_USB_Create(void)
{
	Tela_Menu_USB = lv_obj_create(NULL);
	lv_obj_clear_flag(Tela_Menu_USB, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLLABLE);
	lv_obj_set_style_bg_color(Tela_Menu_USB, lv_color_hex(0x000000), 0);
	lv_obj_set_style_bg_grad_color(Tela_Menu_USB, lv_color_hex(0x000000), 0);

	// Imagem de Fundo
	img_fundo_menu_usb = lv_img_create(Tela_Menu_USB);
	lv_img_set_src(img_fundo_menu_usb, "S:/USB/TELA_USB.bin");
	lv_obj_set_pos(img_fundo_menu_usb, 0, 0);

	// Buttons Input
	create_buttons_input_usb();

	// Buttons Output
	create_buttons_output_usb();

	// Buttons MPX
	create_buttons_output_mpx();

	// Button Save
	create_button_usb_save();

	// Labels
	create_screen_usb_labels();

	create_button_back_main(Tela_Menu_USB, 380, 283, PAGE_MAIN);
}

static void event_bt_usb_in(lv_event_t * e)
{
	lv_event_code_t code = lv_event_get_code(e);

	if(code == LV_EVENT_CLICKED) {
		uint32_t btn = (uint32_t)(uintptr_t)lv_event_get_user_data(e);

		switch(btn) {
			case 0:
				lv_imagebutton_set_state(bt_usb_in_xlr, LV_IMAGEBUTTON_STATE_CHECKED_DISABLED);
				lv_imagebutton_set_state(bt_usb_in_pc,  LV_IMAGEBUTTON_STATE_RELEASED);
				lv_imagebutton_set_state(bt_usb_in_mp3, LV_IMAGEBUTTON_STATE_RELEASED);
				lv_imagebutton_set_state(bt_usb_in_ble, LV_IMAGEBUTTON_STATE_RELEASED);
				break;
			case 1:
				lv_imagebutton_set_state(bt_usb_in_xlr, LV_IMAGEBUTTON_STATE_RELEASED);
				lv_imagebutton_set_state(bt_usb_in_pc,  LV_IMAGEBUTTON_STATE_CHECKED_DISABLED);
				lv_imagebutton_set_state(bt_usb_in_mp3, LV_IMAGEBUTTON_STATE_RELEASED);
				lv_imagebutton_set_state(bt_usb_in_ble, LV_IMAGEBUTTON_STATE_RELEASED);
				break;
			case 2:
				lv_imagebutton_set_state(bt_usb_in_xlr, LV_IMAGEBUTTON_STATE_RELEASED);
				lv_imagebutton_set_state(bt_usb_in_pc,  LV_IMAGEBUTTON_STATE_RELEASED);
				lv_imagebutton_set_state(bt_usb_in_mp3, LV_IMAGEBUTTON_STATE_CHECKED_DISABLED);
				lv_imagebutton_set_state(bt_usb_in_ble, LV_IMAGEBUTTON_STATE_RELEASED);
				break;
			case 3:
				lv_imagebutton_set_state(bt_usb_in_xlr, LV_IMAGEBUTTON_STATE_RELEASED);
				lv_imagebutton_set_state(bt_usb_in_pc,  LV_IMAGEBUTTON_STATE_RELEASED);
				lv_imagebutton_set_state(bt_usb_in_mp3, LV_IMAGEBUTTON_STATE_RELEASED);
				lv_imagebutton_set_state(bt_usb_in_ble, LV_IMAGEBUTTON_STATE_CHECKED_DISABLED);
				break;
		}
	}
}

void create_buttons_input_usb(void)
{
	// XLR INPUT
	bt_usb_in_xlr = lv_imagebutton_create(Tela_Menu_USB);
	lv_imagebutton_set_src(bt_usb_in_xlr, LV_IMAGEBUTTON_STATE_RELEASED, NULL, "S:/USB/BT_XLR_IN_OFF.bin", NULL);
	lv_imagebutton_set_src(bt_usb_in_xlr, LV_IMAGEBUTTON_STATE_PRESSED, NULL, "S:/USB/BT_XLR_IN_ON.bin", NULL);
	lv_imagebutton_set_src(bt_usb_in_xlr, LV_IMAGEBUTTON_STATE_DISABLED, NULL, "S:/USB/BT_XLR_IN_OFF.bin", NULL);
	lv_imagebutton_set_src(bt_usb_in_xlr, LV_IMAGEBUTTON_STATE_CHECKED_PRESSED, NULL, "S:/USB/BT_XLR_IN_ON.bin", NULL);
	lv_imagebutton_set_src(bt_usb_in_xlr, LV_IMAGEBUTTON_STATE_CHECKED_RELEASED, NULL, "S:/USB/BT_XLR_IN_OFF.bin", NULL);
	lv_imagebutton_set_src(bt_usb_in_xlr, LV_IMAGEBUTTON_STATE_CHECKED_DISABLED, NULL, "S:/USB/BT_XLR_IN_ON.bin", NULL);
	user_data_bt_in = 0;
	lv_obj_add_event_cb(bt_usb_in_xlr, event_bt_usb_in, LV_EVENT_ALL, (void *)(uintptr_t)user_data_bt_in);
	lv_obj_set_pos(bt_usb_in_xlr, 18, 18);
	lv_imagebutton_set_state(bt_usb_in_xlr, LV_IMAGEBUTTON_STATE_CHECKED_DISABLED);

	// PC INPUT
	bt_usb_in_pc = lv_imagebutton_create(Tela_Menu_USB);
	lv_imagebutton_set_src(bt_usb_in_pc, LV_IMAGEBUTTON_STATE_RELEASED, NULL, "S:/USB/BT_PC_INPUT_OFF.bin", NULL);
	lv_imagebutton_set_src(bt_usb_in_pc, LV_IMAGEBUTTON_STATE_PRESSED, NULL, "S:/USB/BT_PC_INPUT_ON.bin", NULL);
	lv_imagebutton_set_src(bt_usb_in_pc, LV_IMAGEBUTTON_STATE_DISABLED, NULL, "S:/USB/BT_PC_INPUT_OFF.bin", NULL);
	lv_imagebutton_set_src(bt_usb_in_pc, LV_IMAGEBUTTON_STATE_CHECKED_PRESSED, NULL, "S:/USB/BT_PC_INPUT_ON.bin", NULL);
	lv_imagebutton_set_src(bt_usb_in_pc, LV_IMAGEBUTTON_STATE_CHECKED_RELEASED, NULL, "S:/USB/BT_PC_INPUT_OFF.bin", NULL);
	lv_imagebutton_set_src(bt_usb_in_pc, LV_IMAGEBUTTON_STATE_CHECKED_DISABLED, NULL, "S:/USB/BT_PC_INPUT_ON.bin", NULL);
	user_data_bt_in = 1;
	lv_obj_add_event_cb(bt_usb_in_pc, event_bt_usb_in, LV_EVENT_ALL, (void *)(uintptr_t)user_data_bt_in);
	lv_obj_set_pos(bt_usb_in_pc, 130, 18);
	lv_imagebutton_set_state(bt_usb_in_pc, LV_IMAGEBUTTON_STATE_RELEASED);

	// PC USB/MP3
	bt_usb_in_mp3 = lv_imagebutton_create(Tela_Menu_USB);
	lv_imagebutton_set_src(bt_usb_in_mp3, LV_IMAGEBUTTON_STATE_RELEASED, NULL, "S:/USB/BT_MP3_IN_OFF.bin", NULL);
	lv_imagebutton_set_src(bt_usb_in_mp3, LV_IMAGEBUTTON_STATE_PRESSED, NULL, "S:/USB/BT_MP3_IN_ON.bin", NULL);
	lv_imagebutton_set_src(bt_usb_in_mp3, LV_IMAGEBUTTON_STATE_DISABLED, NULL, "S:/USB/BT_MP3_IN_OFF.bin", NULL);
	lv_imagebutton_set_src(bt_usb_in_mp3, LV_IMAGEBUTTON_STATE_CHECKED_PRESSED, NULL, "S:/USB/BT_MP3_IN_ON.bin", NULL);
	lv_imagebutton_set_src(bt_usb_in_mp3, LV_IMAGEBUTTON_STATE_CHECKED_RELEASED, NULL, "S:/USB/BT_MP3_IN_OFF.bin", NULL);
	lv_imagebutton_set_src(bt_usb_in_mp3, LV_IMAGEBUTTON_STATE_CHECKED_DISABLED, NULL, "S:/USB/BT_MP3_IN_ON.bin", NULL);
	user_data_bt_in = 2;
	lv_obj_add_event_cb(bt_usb_in_mp3, event_bt_usb_in, LV_EVENT_ALL, (void *)(uintptr_t)user_data_bt_in);
	lv_obj_set_pos(bt_usb_in_mp3, 242, 18);
	lv_imagebutton_set_state(bt_usb_in_mp3, LV_IMAGEBUTTON_STATE_RELEASED);

	// PC BLUETOOTH
	bt_usb_in_ble = lv_imagebutton_create(Tela_Menu_USB);
	lv_imagebutton_set_src(bt_usb_in_ble, LV_IMAGEBUTTON_STATE_RELEASED, NULL, "S:/USB/BT_BLUETOOTH_OFF.bin", NULL);
	lv_imagebutton_set_src(bt_usb_in_ble, LV_IMAGEBUTTON_STATE_PRESSED, NULL, "S:/USB/BT_BLUETOOTH_ON.bin", NULL);
	lv_imagebutton_set_src(bt_usb_in_ble, LV_IMAGEBUTTON_STATE_DISABLED, NULL, "S:/USB/BT_BLUETOOTH_OFF.bin", NULL);
	lv_imagebutton_set_src(bt_usb_in_ble, LV_IMAGEBUTTON_STATE_CHECKED_PRESSED, NULL, "S:/USB/BT_BLUETOOTH_ON.bin", NULL);
	lv_imagebutton_set_src(bt_usb_in_ble, LV_IMAGEBUTTON_STATE_CHECKED_RELEASED, NULL, "S:/USB/BT_BLUETOOTH_OFF.bin", NULL);
	lv_imagebutton_set_src(bt_usb_in_ble, LV_IMAGEBUTTON_STATE_CHECKED_DISABLED, NULL, "S:/USB/BT_BLUETOOTH_OFF.bin", NULL);
	user_data_bt_in = 3;
	lv_obj_add_event_cb(bt_usb_in_ble, event_bt_usb_in, LV_EVENT_ALL, (void *)(uintptr_t)user_data_bt_in);
	lv_obj_set_pos(bt_usb_in_ble, 354, 18);
	lv_imagebutton_set_state(bt_usb_in_ble, LV_IMAGEBUTTON_STATE_RELEASED);
}

static void event_bt_usb_out(lv_event_t * e)
{
	lv_event_code_t code = lv_event_get_code(e);

	if(code == LV_EVENT_CLICKED) {
		uint32_t btn = (uint32_t)(uintptr_t)lv_event_get_user_data(e);

		switch(btn) {
			case 0:
				lv_imagebutton_set_state(bt_usb_out_xlr,  LV_IMAGEBUTTON_STATE_CHECKED_DISABLED);
				lv_imagebutton_set_state(bt_usb_out_pc, LV_IMAGEBUTTON_STATE_RELEASED);
				break;
			case 1:
				lv_imagebutton_set_state(bt_usb_out_xlr,  LV_IMAGEBUTTON_STATE_RELEASED);
				lv_imagebutton_set_state(bt_usb_out_pc, LV_IMAGEBUTTON_STATE_CHECKED_DISABLED);
				break;
		}
	}
}

void create_buttons_output_usb(void)
{
	// XLR OUTPUT
	bt_usb_out_xlr = lv_imagebutton_create(Tela_Menu_USB);
	lv_imagebutton_set_src(bt_usb_out_xlr, LV_IMAGEBUTTON_STATE_RELEASED, NULL, "S:/USB/BT_XLR_OUT_OFF.bin", NULL);
	lv_imagebutton_set_src(bt_usb_out_xlr, LV_IMAGEBUTTON_STATE_PRESSED, NULL, "S:/USB/BT_XLR_OUT_ON.bin", NULL);
	lv_imagebutton_set_src(bt_usb_out_xlr, LV_IMAGEBUTTON_STATE_DISABLED, NULL, "S:/USB/BT_XLR_OUT_OFF.bin", NULL);
	lv_imagebutton_set_src(bt_usb_out_xlr, LV_IMAGEBUTTON_STATE_CHECKED_PRESSED, NULL, "S:/USB/BT_XLR_OUT_ON.bin", NULL);
	lv_imagebutton_set_src(bt_usb_out_xlr, LV_IMAGEBUTTON_STATE_CHECKED_RELEASED, NULL, "S:/USB/BT_XLR_OUT_OFF.bin", NULL);
	lv_imagebutton_set_src(bt_usb_out_xlr, LV_IMAGEBUTTON_STATE_CHECKED_DISABLED, NULL, "S:/USB/BT_XLR_OUT_ON.bin", NULL);
	user_data_bt_out = 0;
	lv_obj_add_event_cb(bt_usb_out_xlr, event_bt_usb_out, LV_EVENT_ALL, (void *)(uintptr_t)user_data_bt_out);
	lv_obj_set_pos(bt_usb_out_xlr, 12, 266);
	lv_imagebutton_set_state(bt_usb_out_xlr, LV_IMAGEBUTTON_STATE_CHECKED_DISABLED);

	// XLR OUTPUT
	bt_usb_out_pc = lv_imagebutton_create(Tela_Menu_USB);
	lv_imagebutton_set_src(bt_usb_out_pc, LV_IMAGEBUTTON_STATE_RELEASED, NULL, "S:/USB/BT_PC_OUT_OFF.bin", NULL);
	lv_imagebutton_set_src(bt_usb_out_pc, LV_IMAGEBUTTON_STATE_PRESSED, NULL, "S:/USB/BT_PC_OUT_ON.bin", NULL);
	lv_imagebutton_set_src(bt_usb_out_pc, LV_IMAGEBUTTON_STATE_DISABLED, NULL, "S:/USB/BT_PC_OUT_OFF.bin", NULL);
	lv_imagebutton_set_src(bt_usb_out_pc, LV_IMAGEBUTTON_STATE_CHECKED_PRESSED, NULL, "S:/USB/BT_PC_OUT_ON.bin", NULL);
	lv_imagebutton_set_src(bt_usb_out_pc, LV_IMAGEBUTTON_STATE_CHECKED_RELEASED, NULL, "S:/USB/BT_PC_OUT_OFF.bin", NULL);
	lv_imagebutton_set_src(bt_usb_out_pc, LV_IMAGEBUTTON_STATE_CHECKED_DISABLED, NULL, "S:/USB/BT_PC_OUT_ON.bin", NULL);
	user_data_bt_out = 1;
	lv_obj_add_event_cb(bt_usb_out_pc, event_bt_usb_out, LV_EVENT_ALL, (void *)(uintptr_t)user_data_bt_out);
	lv_obj_set_pos(bt_usb_out_pc, 124, 266);
	lv_imagebutton_set_state(bt_usb_out_pc, LV_IMAGEBUTTON_STATE_RELEASED);
}

static void event_bt_usb_out_mpx(lv_event_t * e)
{
	lv_event_code_t code = lv_event_get_code(e);

	if(code == LV_EVENT_CLICKED) {
		uint32_t btn = (uint32_t)(uintptr_t)lv_event_get_user_data(e);

		switch(btn) {
			case 0:
				lv_imagebutton_set_state(bt_usb_out_mpx,  LV_IMAGEBUTTON_STATE_CHECKED_DISABLED);
				lv_imagebutton_set_state(bt_usb_out_aes, LV_IMAGEBUTTON_STATE_RELEASED);
				break;
			case 1:
				lv_imagebutton_set_state(bt_usb_out_mpx,  LV_IMAGEBUTTON_STATE_RELEASED);
				lv_imagebutton_set_state(bt_usb_out_aes, LV_IMAGEBUTTON_STATE_CHECKED_DISABLED);
				break;
		}
	}
}

void create_buttons_output_mpx(void)
{
	// MPX OUT
	bt_usb_out_mpx = lv_imagebutton_create(Tela_Menu_USB);
	lv_imagebutton_set_src(bt_usb_out_mpx, LV_IMAGEBUTTON_STATE_RELEASED, NULL, "S:/USB/LED_MPX_OFF.bin", NULL);
	lv_imagebutton_set_src(bt_usb_out_mpx, LV_IMAGEBUTTON_STATE_PRESSED, NULL, "S:/USB/LED_MPX_ON.bin", NULL);
	lv_imagebutton_set_src(bt_usb_out_mpx, LV_IMAGEBUTTON_STATE_DISABLED, NULL, "S:/USB/LED_MPX_OFF.bin", NULL);
	lv_imagebutton_set_src(bt_usb_out_mpx, LV_IMAGEBUTTON_STATE_CHECKED_PRESSED, NULL, "S:/USB/LED_MPX_ON.bin", NULL);
	lv_imagebutton_set_src(bt_usb_out_mpx, LV_IMAGEBUTTON_STATE_CHECKED_RELEASED, NULL, "S:/USB/LED_MPX_OFF.bin", NULL);
	lv_imagebutton_set_src(bt_usb_out_mpx, LV_IMAGEBUTTON_STATE_CHECKED_DISABLED, NULL, "S:/USB/LED_MPX_ON.bin", NULL);
	user_data_bt_mpx = 0;
	lv_obj_add_event_cb(bt_usb_out_mpx, event_bt_usb_out_mpx, LV_EVENT_ALL, (void *)(uintptr_t)user_data_bt_mpx);
	lv_obj_set_pos(bt_usb_out_mpx, 372, 108);
	lv_imagebutton_set_state(bt_usb_out_mpx, LV_IMAGEBUTTON_STATE_CHECKED_DISABLED);

	// AES192 OUT
	bt_usb_out_aes = lv_imagebutton_create(Tela_Menu_USB);
	lv_imagebutton_set_src(bt_usb_out_aes, LV_IMAGEBUTTON_STATE_RELEASED, NULL, "S:/USB/LED_MPX_OFF.bin", NULL);
	lv_imagebutton_set_src(bt_usb_out_aes, LV_IMAGEBUTTON_STATE_PRESSED, NULL, "S:/USB/LED_MPX_ON.bin", NULL);
	lv_imagebutton_set_src(bt_usb_out_aes, LV_IMAGEBUTTON_STATE_DISABLED, NULL, "S:/USB/LED_MPX_OFF.bin", NULL);
	lv_imagebutton_set_src(bt_usb_out_aes, LV_IMAGEBUTTON_STATE_CHECKED_PRESSED, NULL, "S:/USB/LED_MPX_ON.bin", NULL);
	lv_imagebutton_set_src(bt_usb_out_aes, LV_IMAGEBUTTON_STATE_CHECKED_RELEASED, NULL, "S:/USB/LED_MPX_OFF.bin", NULL);
	lv_imagebutton_set_src(bt_usb_out_aes, LV_IMAGEBUTTON_STATE_CHECKED_DISABLED, NULL, "S:/USB/LED_MPX_ON.bin", NULL);
	user_data_bt_mpx = 1;
	lv_obj_add_event_cb(bt_usb_out_aes, event_bt_usb_out_mpx, LV_EVENT_ALL, (void *)(uintptr_t)user_data_bt_mpx);
	lv_obj_set_pos(bt_usb_out_aes, 372, 180);
	lv_imagebutton_set_state(bt_usb_out_aes, LV_IMAGEBUTTON_STATE_RELEASED);
}

static void event_bt_usb_save(lv_event_t * e)
{
	lv_event_code_t code = lv_event_get_code(e);

	if(code == LV_EVENT_CLICKED) {

	}
}

void create_button_usb_save(void)
{
	// SAVE/APPLY
	bt_usb_save = lv_imagebutton_create(Tela_Menu_USB);
	lv_imagebutton_set_src(bt_usb_save, LV_IMAGEBUTTON_STATE_RELEASED, NULL, "S:/USB/BT_SAVE.bin", NULL);
	lv_imagebutton_set_src(bt_usb_save, LV_IMAGEBUTTON_STATE_PRESSED, NULL, "S:/USB/BT_SAVE_P.bin", NULL);
	lv_imagebutton_set_src(bt_usb_save, LV_IMAGEBUTTON_STATE_DISABLED, NULL, "S:/USB/BT_SAVE.bin", NULL);
	lv_imagebutton_set_src(bt_usb_save, LV_IMAGEBUTTON_STATE_CHECKED_PRESSED, NULL, "S:/USB/BT_SAVE_P.bin", NULL);
	lv_imagebutton_set_src(bt_usb_save, LV_IMAGEBUTTON_STATE_CHECKED_RELEASED, NULL, "S:/USB/BT_SAVE.bin", NULL);
	lv_imagebutton_set_src(bt_usb_save, LV_IMAGEBUTTON_STATE_CHECKED_DISABLED, NULL, "S:/USB/BT_SAVE.bin", NULL);
	lv_obj_add_event_cb(bt_usb_save, event_bt_usb_save, LV_EVENT_ALL, NULL);
	lv_obj_set_pos(bt_usb_save, 281, 283);
	lv_imagebutton_set_state(bt_usb_save, LV_IMAGEBUTTON_STATE_RELEASED);

	// Text
    lv_obj_t * text_save = lv_label_create(bt_usb_save);
    lv_obj_set_width(text_save, LV_SIZE_CONTENT);
    lv_obj_set_height(text_save, LV_SIZE_CONTENT);
    lv_label_set_text(text_save, "SAVE/APPLY");
    lv_obj_set_style_text_color(text_save, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(text_save, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(text_save, &Neue_Medium_14, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_align_to(text_save, bt_usb_save, LV_ALIGN_CENTER, 0, 0);
}

void create_screen_usb_labels(void)
{
	// Labels
	for(uint8_t x = 0; x < 8; x++) {
		label_screen_usb[x] = lv_label_create(Tela_Menu_USB);
		lv_obj_set_width(label_screen_usb[x], LV_SIZE_CONTENT);
		lv_obj_set_height(label_screen_usb[x], LV_SIZE_CONTENT);
		lv_obj_set_style_text_color(label_screen_usb[x], lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
		lv_obj_set_style_text_opa(label_screen_usb[x], 255, LV_PART_MAIN | LV_STATE_DEFAULT);
		lv_obj_set_style_text_font(label_screen_usb[x], &Neue_Medium_12, LV_PART_MAIN | LV_STATE_DEFAULT);
	}

	lv_label_set_text(label_screen_usb[0], "SELECT AUDIO SOURCE:");
	lv_label_set_text(label_screen_usb[1], "MODE: USB PC FM");
	lv_label_set_text(label_screen_usb[2], "SELECT AUDIO");
	lv_label_set_text(label_screen_usb[3], "OUTPUT:");
	lv_label_set_text(label_screen_usb[4], "MPX OUT");
	lv_label_set_text(label_screen_usb[5], "ANALOG");
	lv_label_set_text(label_screen_usb[6], "DIGITAL");
	lv_label_set_text(label_screen_usb[7], "AES192");

	lv_obj_align_to(label_screen_usb[0], Tela_Menu_USB, LV_ALIGN_CENTER, 0, -148);
	lv_obj_align_to(label_screen_usb[1], Tela_Menu_USB, LV_ALIGN_CENTER, -160, -148);
	lv_obj_align_to(label_screen_usb[2], Tela_Menu_USB, LV_ALIGN_CENTER, -180, 60);
	lv_obj_align_to(label_screen_usb[3], Tela_Menu_USB, LV_ALIGN_CENTER, -198, 74);
	lv_obj_align_to(label_screen_usb[4], Tela_Menu_USB, LV_ALIGN_CENTER, 164, -62);
	lv_obj_align_to(label_screen_usb[5], Tela_Menu_USB, LV_ALIGN_CENTER, 212, -20);
	lv_obj_align_to(label_screen_usb[6], Tela_Menu_USB, LV_ALIGN_CENTER, 204, 46);
	lv_obj_align_to(label_screen_usb[7], Tela_Menu_USB, LV_ALIGN_CENTER, 162, 85);
}
