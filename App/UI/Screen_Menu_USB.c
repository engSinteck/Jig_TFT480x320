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

void create_buttons_input_usb(void);
void create_buttons_output_usb(void);
void create_buttons_output_mpx(void);

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

	// Create Buttons Input
	create_buttons_input_usb();

	// Create Buttons Output
	create_buttons_output_usb();

	// Create Buttons MPX
	create_buttons_output_mpx();

	create_button_back_main(Tela_Menu_USB, 380, 283, PAGE_MAIN);
}

static void event_bt_usb_in_xlr(lv_event_t * e)
{
	lv_event_code_t code = lv_event_get_code(e);

	if(code == LV_EVENT_CLICKED) {

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
	lv_obj_add_event_cb(bt_usb_in_xlr, event_bt_usb_in_xlr, LV_EVENT_ALL, NULL);
	lv_obj_set_pos(bt_usb_in_xlr, 18, 18);
	lv_imagebutton_set_state(bt_usb_in_xlr, LV_IMAGEBUTTON_STATE_RELEASED);

	// PC INPUT
	bt_usb_in_pc = lv_imagebutton_create(Tela_Menu_USB);
	lv_imagebutton_set_src(bt_usb_in_pc, LV_IMAGEBUTTON_STATE_RELEASED, NULL, "S:/USB/BT_PC_INPUT_OFF.bin", NULL);
	lv_imagebutton_set_src(bt_usb_in_pc, LV_IMAGEBUTTON_STATE_PRESSED, NULL, "S:/USB/BT_PC_INPUT_ON.bin", NULL);
	lv_imagebutton_set_src(bt_usb_in_pc, LV_IMAGEBUTTON_STATE_DISABLED, NULL, "S:/USB/BT_PC_INPUT_OFF.bin", NULL);
	lv_imagebutton_set_src(bt_usb_in_pc, LV_IMAGEBUTTON_STATE_CHECKED_PRESSED, NULL, "S:/USB/BT_PC_INPUT_ON.bin", NULL);
	lv_imagebutton_set_src(bt_usb_in_pc, LV_IMAGEBUTTON_STATE_CHECKED_RELEASED, NULL, "S:/USB/BT_PC_INPUT_OFF.bin", NULL);
	lv_imagebutton_set_src(bt_usb_in_pc, LV_IMAGEBUTTON_STATE_CHECKED_DISABLED, NULL, "S:/USB/BT_PC_INPUT_ON.bin", NULL);
	lv_obj_add_event_cb(bt_usb_in_pc, event_bt_usb_in_xlr, LV_EVENT_ALL, NULL);
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
	lv_obj_add_event_cb(bt_usb_in_mp3, event_bt_usb_in_xlr, LV_EVENT_ALL, NULL);
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
	lv_obj_add_event_cb(bt_usb_in_ble, event_bt_usb_in_xlr, LV_EVENT_ALL, NULL);
	lv_obj_set_pos(bt_usb_in_ble, 354, 18);
	lv_imagebutton_set_state(bt_usb_in_ble, LV_IMAGEBUTTON_STATE_RELEASED);
}

static void event_bt_usb_out_xlr(lv_event_t * e)
{
	lv_event_code_t code = lv_event_get_code(e);

	if(code == LV_EVENT_CLICKED) {

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
	lv_obj_add_event_cb(bt_usb_out_xlr, event_bt_usb_out_xlr, LV_EVENT_ALL, NULL);
	lv_obj_set_pos(bt_usb_out_xlr, 12, 272);
	lv_imagebutton_set_state(bt_usb_out_xlr, LV_IMAGEBUTTON_STATE_RELEASED);

	// XLR OUTPUT
	bt_usb_out_pc = lv_imagebutton_create(Tela_Menu_USB);
	lv_imagebutton_set_src(bt_usb_out_pc, LV_IMAGEBUTTON_STATE_RELEASED, NULL, "S:/USB/BT_PC_OUT_OFF.bin", NULL);
	lv_imagebutton_set_src(bt_usb_out_pc, LV_IMAGEBUTTON_STATE_PRESSED, NULL, "S:/USB/BT_PC_OUT_ON.bin", NULL);
	lv_imagebutton_set_src(bt_usb_out_pc, LV_IMAGEBUTTON_STATE_DISABLED, NULL, "S:/USB/BT_PC_OUT_OFF.bin", NULL);
	lv_imagebutton_set_src(bt_usb_out_pc, LV_IMAGEBUTTON_STATE_CHECKED_PRESSED, NULL, "S:/USB/BT_PC_OUT_ON.bin", NULL);
	lv_imagebutton_set_src(bt_usb_out_pc, LV_IMAGEBUTTON_STATE_CHECKED_RELEASED, NULL, "S:/USB/BT_PC_OUT_OFF.bin", NULL);
	lv_imagebutton_set_src(bt_usb_out_pc, LV_IMAGEBUTTON_STATE_CHECKED_DISABLED, NULL, "S:/USB/BT_PC_OUT_ON.bin", NULL);
	lv_obj_add_event_cb(bt_usb_out_pc, event_bt_usb_out_xlr, LV_EVENT_ALL, NULL);
	lv_obj_set_pos(bt_usb_out_pc, 124, 272);
	lv_imagebutton_set_state(bt_usb_out_pc, LV_IMAGEBUTTON_STATE_RELEASED);
}

static void event_bt_usb_out_mpx(lv_event_t * e)
{
	lv_event_code_t code = lv_event_get_code(e);

	if(code == LV_EVENT_CLICKED) {

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
	lv_imagebutton_set_src(bt_usb_out_mpx, LV_IMAGEBUTTON_STATE_CHECKED_DISABLED, NULL, "S:/USB/LED_MPX_OFF.bin", NULL);
	lv_obj_add_event_cb(bt_usb_out_mpx, event_bt_usb_out_mpx, LV_EVENT_ALL, NULL);
	lv_obj_set_pos(bt_usb_out_mpx, 372, 108);
	lv_imagebutton_set_state(bt_usb_out_mpx, LV_IMAGEBUTTON_STATE_RELEASED);

	// AES192 OUT
	bt_usb_out_aes = lv_imagebutton_create(Tela_Menu_USB);
	lv_imagebutton_set_src(bt_usb_out_aes, LV_IMAGEBUTTON_STATE_RELEASED, NULL, "S:/USB/LED_MPX_OFF.bin", NULL);
	lv_imagebutton_set_src(bt_usb_out_aes, LV_IMAGEBUTTON_STATE_PRESSED, NULL, "S:/USB/LED_MPX_ON.bin", NULL);
	lv_imagebutton_set_src(bt_usb_out_aes, LV_IMAGEBUTTON_STATE_DISABLED, NULL, "S:/USB/LED_MPX_OFF.bin", NULL);
	lv_imagebutton_set_src(bt_usb_out_aes, LV_IMAGEBUTTON_STATE_CHECKED_PRESSED, NULL, "S:/USB/LED_MPX_ON.bin", NULL);
	lv_imagebutton_set_src(bt_usb_out_aes, LV_IMAGEBUTTON_STATE_CHECKED_RELEASED, NULL, "S:/USB/LED_MPX_OFF.bin", NULL);
	lv_imagebutton_set_src(bt_usb_out_aes, LV_IMAGEBUTTON_STATE_CHECKED_DISABLED, NULL, "S:/USB/LED_MPX_OFF.bin", NULL);
	lv_obj_add_event_cb(bt_usb_out_aes, event_bt_usb_out_mpx, LV_EVENT_ALL, NULL);
	lv_obj_set_pos(bt_usb_out_aes, 372, 190);
	lv_imagebutton_set_state(bt_usb_out_aes, LV_IMAGEBUTTON_STATE_RELEASED);
}
