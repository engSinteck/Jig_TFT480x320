/*
 * Screen_Menu_MP3.c
 *
 *  Created on: 28 de ago. de 2026
 *      Author: rinaldo.santos
 */

#include "stdbool.h"
#include "rng.h"
#include "stdio.h"
#include "string.h"

#include "../App/UI/Screen_Menu_MP3.h"
#include "../App/UI/Screen_Utils.h"

void create_button_mp3_save(void);
void create_buttons_mp3_proc(void);
void create_labels_mp3(void);
void create_buttons_mp3(void);
void create_buttons_mp3_ble(void);
void create_titule_usb(void);
void create_titule_mp3(void);

LV_FONT_DECLARE(Neue_Medium_14);
LV_FONT_DECLARE(Neue_Medium_20);
LV_FONT_DECLARE(Neue_Medium_24);

lv_obj_t * Tela_Menu_MP3 = NULL;
static lv_obj_t * img_fundo_menu_mp3 = NULL;
static lv_obj_t * bt_mp3_save = NULL;
static lv_obj_t * bt_mp3_out_xlr = NULL;
static lv_obj_t * bt_mp3_out_pc = NULL;
static lv_obj_t * text_mp3_top = NULL;
static lv_obj_t * text_mp3_bottom = NULL;
static lv_obj_t * bt_mp3_usb_next = NULL;
static lv_obj_t * bt_mp3_usbstop = NULL;
static lv_obj_t * bt_mp3_usbrev = NULL;
static lv_obj_t * bt_mp3_usbnext = NULL;

static lv_obj_t * bt_mp3_ble_next = NULL;
static lv_obj_t * bt_mp3_blestop = NULL;
static lv_obj_t * bt_mp3_blerev = NULL;
static lv_obj_t * bt_mp3_blenext = NULL;

static lv_obj_t * text_usb_titule = NULL;
static lv_obj_t * text_usb_music = NULL;
static lv_obj_t * text_mp3_titule = NULL;
static lv_obj_t * text_mp3_music = NULL;

static uint32_t user_data_bt_out_mp3 = 0;

void Screen_Menu_MP3_Create(void)
{
	Tela_Menu_MP3 = lv_obj_create(NULL);
	lv_obj_clear_flag(Tela_Menu_MP3, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLLABLE);
	lv_obj_set_style_bg_color(Tela_Menu_MP3, lv_color_hex(0x000000), 0);
	lv_obj_set_style_bg_grad_color(Tela_Menu_MP3, lv_color_hex(0x000000), 0);

	// Imagem de Fundo
	img_fundo_menu_mp3 = lv_img_create(Tela_Menu_MP3);
	lv_img_set_src(img_fundo_menu_mp3, "S:/MP3/TELA_MP3.bin");
	lv_obj_set_pos(img_fundo_menu_mp3, 0, 0);

	// Button Save
	create_button_mp3_save();

	// Output
	create_buttons_mp3_proc();

	// Labels
	create_labels_mp3();

	// Buttons USB
	create_buttons_mp3();

	// Buttons Bluetooth
	create_buttons_mp3_ble();

	// Titulos USB
	create_titule_usb();

	// Titulos MP3
	create_titule_mp3();

	create_button_back_main(Tela_Menu_MP3, 380, 283, PAGE_MAIN);
}

static void event_bt_mp3_save(lv_event_t * e)
{
	lv_event_code_t code = lv_event_get_code(e);

	if(code == LV_EVENT_CLICKED) {

	}
}

void create_button_mp3_save(void)
{
	// SAVE/APPLY
	bt_mp3_save = lv_imagebutton_create(Tela_Menu_MP3);
	lv_imagebutton_set_src(bt_mp3_save, LV_IMAGEBUTTON_STATE_RELEASED, NULL, "S:/USB/BT_SAVE.bin", NULL);
	lv_imagebutton_set_src(bt_mp3_save, LV_IMAGEBUTTON_STATE_PRESSED, NULL, "S:/USB/BT_SAVE_P.bin", NULL);
	lv_imagebutton_set_src(bt_mp3_save, LV_IMAGEBUTTON_STATE_DISABLED, NULL, "S:/USB/BT_SAVE.bin", NULL);
	lv_imagebutton_set_src(bt_mp3_save, LV_IMAGEBUTTON_STATE_CHECKED_PRESSED, NULL, "S:/USB/BT_SAVE_P.bin", NULL);
	lv_imagebutton_set_src(bt_mp3_save, LV_IMAGEBUTTON_STATE_CHECKED_RELEASED, NULL, "S:/USB/BT_SAVE.bin", NULL);
	lv_imagebutton_set_src(bt_mp3_save, LV_IMAGEBUTTON_STATE_CHECKED_DISABLED, NULL, "S:/USB/BT_SAVE.bin", NULL);
	lv_obj_add_event_cb(bt_mp3_save, event_bt_mp3_save, LV_EVENT_ALL, NULL);
	lv_obj_set_pos(bt_mp3_save, 281, 283);
	lv_imagebutton_set_state(bt_mp3_save, LV_IMAGEBUTTON_STATE_RELEASED);

	// Text
    lv_obj_t * text_save = lv_label_create(bt_mp3_save);
    lv_obj_set_width(text_save, LV_SIZE_CONTENT);
    lv_obj_set_height(text_save, LV_SIZE_CONTENT);
    lv_label_set_text(text_save, "SAVE/APPLY");
    lv_obj_set_style_text_color(text_save, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(text_save, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(text_save, &Neue_Medium_14, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_align_to(text_save, bt_mp3_save, LV_ALIGN_CENTER, 0, 0);
}

static void event_bt_mp3_out(lv_event_t * e)
{
	lv_event_code_t code = lv_event_get_code(e);

	if(code == LV_EVENT_CLICKED) {
		uint32_t btn = (uint32_t)(uintptr_t)lv_event_get_user_data(e);

		switch(btn) {
			case 0:
				lv_imagebutton_set_state(bt_mp3_out_xlr,  LV_IMAGEBUTTON_STATE_CHECKED_DISABLED);
				lv_imagebutton_set_state(bt_mp3_out_pc, LV_IMAGEBUTTON_STATE_RELEASED);
				break;
			case 1:
				lv_imagebutton_set_state(bt_mp3_out_xlr,  LV_IMAGEBUTTON_STATE_RELEASED);
				lv_imagebutton_set_state(bt_mp3_out_pc, LV_IMAGEBUTTON_STATE_CHECKED_DISABLED);
				break;
		}
	}
}

void create_buttons_mp3_proc(void)
{
	// XLR OUTPUT
	bt_mp3_out_xlr = lv_imagebutton_create(Tela_Menu_MP3);
	lv_imagebutton_set_src(bt_mp3_out_xlr, LV_IMAGEBUTTON_STATE_RELEASED, NULL, "S:/USB/BT_XLR_OUT_OFF.bin", NULL);
	lv_imagebutton_set_src(bt_mp3_out_xlr, LV_IMAGEBUTTON_STATE_PRESSED, NULL, "S:/USB/BT_XLR_OUT_ON.bin", NULL);
	lv_imagebutton_set_src(bt_mp3_out_xlr, LV_IMAGEBUTTON_STATE_DISABLED, NULL, "S:/USB/BT_XLR_OUT_OFF.bin", NULL);
	lv_imagebutton_set_src(bt_mp3_out_xlr, LV_IMAGEBUTTON_STATE_CHECKED_PRESSED, NULL, "S:/USB/BT_XLR_OUT_ON.bin", NULL);
	lv_imagebutton_set_src(bt_mp3_out_xlr, LV_IMAGEBUTTON_STATE_CHECKED_RELEASED, NULL, "S:/USB/BT_XLR_OUT_OFF.bin", NULL);
	lv_imagebutton_set_src(bt_mp3_out_xlr, LV_IMAGEBUTTON_STATE_CHECKED_DISABLED, NULL, "S:/USB/BT_XLR_OUT_ON.bin", NULL);
	user_data_bt_out_mp3 = 0;
	lv_obj_add_event_cb(bt_mp3_out_xlr, event_bt_mp3_out, LV_EVENT_ALL, (void *)(uintptr_t)user_data_bt_out_mp3);
	lv_obj_set_pos(bt_mp3_out_xlr, 12, 266);
	lv_imagebutton_set_state(bt_mp3_out_xlr, LV_IMAGEBUTTON_STATE_CHECKED_DISABLED);

	// PC OUTPUT
	bt_mp3_out_pc = lv_imagebutton_create(Tela_Menu_MP3);
	lv_imagebutton_set_src(bt_mp3_out_pc, LV_IMAGEBUTTON_STATE_RELEASED, NULL, "S:/USB/BT_PC_OUT_OFF.bin", NULL);
	lv_imagebutton_set_src(bt_mp3_out_pc, LV_IMAGEBUTTON_STATE_PRESSED, NULL, "S:/USB/BT_PC_OUT_ON.bin", NULL);
	lv_imagebutton_set_src(bt_mp3_out_pc, LV_IMAGEBUTTON_STATE_DISABLED, NULL, "S:/USB/BT_PC_OUT_OFF.bin", NULL);
	lv_imagebutton_set_src(bt_mp3_out_pc, LV_IMAGEBUTTON_STATE_CHECKED_PRESSED, NULL, "S:/USB/BT_PC_OUT_ON.bin", NULL);
	lv_imagebutton_set_src(bt_mp3_out_pc, LV_IMAGEBUTTON_STATE_CHECKED_RELEASED, NULL, "S:/USB/BT_PC_OUT_OFF.bin", NULL);
	lv_imagebutton_set_src(bt_mp3_out_pc, LV_IMAGEBUTTON_STATE_CHECKED_DISABLED, NULL, "S:/USB/BT_PC_OUT_ON.bin", NULL);
	user_data_bt_out_mp3 = 1;
	lv_obj_add_event_cb(bt_mp3_out_pc, event_bt_mp3_out, LV_EVENT_ALL, (void *)(uintptr_t)user_data_bt_out_mp3);
	lv_obj_set_pos(bt_mp3_out_pc, 124, 266);
	lv_imagebutton_set_state(bt_mp3_out_pc, LV_IMAGEBUTTON_STATE_RELEASED);
}

void create_labels_mp3(void)
{
	// Text Top
    text_mp3_top = lv_label_create(Tela_Menu_MP3);
    lv_obj_set_width(text_mp3_top, LV_SIZE_CONTENT);
    lv_obj_set_height(text_mp3_top, LV_SIZE_CONTENT);
    lv_label_set_text(text_mp3_top, "MODE: MP3 PLAYER / BLUETOOTH");
    lv_obj_set_style_text_color(text_mp3_top, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(text_mp3_top, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(text_mp3_top, &Neue_Medium_14, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(text_mp3_top, 8, 7);

    // Text Select
    text_mp3_bottom = lv_label_create(Tela_Menu_MP3);
    lv_obj_set_width(text_mp3_bottom, LV_SIZE_CONTENT);
    lv_obj_set_height(text_mp3_top, LV_SIZE_CONTENT);
    lv_label_set_text(text_mp3_bottom, "SELECT AUDIO OUTPUT:");
    lv_obj_set_style_text_color(text_mp3_bottom, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(text_mp3_bottom, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(text_mp3_bottom, &Neue_Medium_14, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(text_mp3_bottom, 36, 248);
}

static void event_mp3_usb_next(lv_event_t * e)
{
	lv_event_code_t code = lv_event_get_code(e);

	if(code == LV_EVENT_CLICKED) {

	}
}

static void event_mp3_usb_stop(lv_event_t * e)
{
	lv_event_code_t code = lv_event_get_code(e);

	if(code == LV_EVENT_CLICKED) {

	}
}

static void event_mp3_usb_rev(lv_event_t * e)
{
	lv_event_code_t code = lv_event_get_code(e);

	if(code == LV_EVENT_CLICKED) {

	}
}

static void event_mp3_usb_next2(lv_event_t * e)
{
	lv_event_code_t code = lv_event_get_code(e);

	if(code == LV_EVENT_CLICKED) {

	}
}

void create_buttons_mp3(void)
{
	// Button NEXT
	bt_mp3_usb_next = lv_imagebutton_create(Tela_Menu_MP3);
	lv_imagebutton_set_src(bt_mp3_usb_next, LV_IMAGEBUTTON_STATE_RELEASED, NULL, "S:/GENERATOR/BT_NEXT.bin", NULL);
	lv_imagebutton_set_src(bt_mp3_usb_next, LV_IMAGEBUTTON_STATE_PRESSED, NULL, "S:/GENERATOR/BT_NEXT_P.bin", NULL);
	lv_imagebutton_set_src(bt_mp3_usb_next, LV_IMAGEBUTTON_STATE_DISABLED, NULL, "S:/GENERATOR/BT_NEXT.bin", NULL);
	lv_imagebutton_set_src(bt_mp3_usb_next, LV_IMAGEBUTTON_STATE_CHECKED_PRESSED, NULL, "S:/GENERATOR/BT_NEXT_P.bin", NULL);
	lv_imagebutton_set_src(bt_mp3_usb_next, LV_IMAGEBUTTON_STATE_CHECKED_RELEASED, NULL, "S:/GENERATOR/BT_NEXT.bin", NULL);
	lv_imagebutton_set_src(bt_mp3_usb_next, LV_IMAGEBUTTON_STATE_CHECKED_DISABLED, NULL, "S:/GENERATOR/BT_NEXT.bin", NULL);
	lv_obj_add_state(bt_mp3_usb_next, LV_IMAGEBUTTON_STATE_RELEASED);
	lv_obj_add_event_cb(bt_mp3_usb_next, event_mp3_usb_next, LV_EVENT_ALL, NULL);
	lv_obj_set_pos(bt_mp3_usb_next, 380, 34);

	// Button PLAY/STOP
	bt_mp3_usbstop = lv_imagebutton_create(Tela_Menu_MP3);
	lv_imagebutton_set_src(bt_mp3_usbstop, LV_IMAGEBUTTON_STATE_RELEASED, NULL, "S:/GENERATOR/BT_STOP.bin", NULL);
	lv_imagebutton_set_src(bt_mp3_usbstop, LV_IMAGEBUTTON_STATE_PRESSED, NULL, "S:/GENERATOR/BT_STOP_P.bin", NULL);
	lv_imagebutton_set_src(bt_mp3_usbstop, LV_IMAGEBUTTON_STATE_DISABLED, NULL, "S:/GENERATOR/BT_STOP.bin", NULL);
	lv_imagebutton_set_src(bt_mp3_usbstop, LV_IMAGEBUTTON_STATE_CHECKED_PRESSED, NULL, "S:/GENERATOR/BT_STOP_P.bin", NULL);
	lv_imagebutton_set_src(bt_mp3_usbstop, LV_IMAGEBUTTON_STATE_CHECKED_RELEASED, NULL, "S:/GENERATOR/BT_STOP.bin", NULL);
	lv_imagebutton_set_src(bt_mp3_usbstop, LV_IMAGEBUTTON_STATE_CHECKED_DISABLED, NULL, "S:/GENERATOR/BT_STOP.bin", NULL);
	lv_obj_add_state(bt_mp3_usbstop, LV_IMAGEBUTTON_STATE_RELEASED);
	lv_obj_add_event_cb(bt_mp3_usbstop, event_mp3_usb_stop, LV_EVENT_ALL, NULL);
	lv_obj_set_pos(bt_mp3_usbstop, 428, 34);

	// Button REV
	bt_mp3_usbrev = lv_imagebutton_create(Tela_Menu_MP3);
	lv_imagebutton_set_src(bt_mp3_usbrev, LV_IMAGEBUTTON_STATE_RELEASED, NULL, "S:/GENERATOR/BT_REF.bin", NULL);
	lv_imagebutton_set_src(bt_mp3_usbrev, LV_IMAGEBUTTON_STATE_PRESSED, NULL, "S:/GENERATOR/BT_REF_P.bin", NULL);
	lv_imagebutton_set_src(bt_mp3_usbrev, LV_IMAGEBUTTON_STATE_DISABLED, NULL, "S:/GENERATOR/BT_REF.bin", NULL);
	lv_imagebutton_set_src(bt_mp3_usbrev, LV_IMAGEBUTTON_STATE_CHECKED_PRESSED, NULL, "S:/GENERATOR/BT_REF_P.bin", NULL);
	lv_imagebutton_set_src(bt_mp3_usbrev, LV_IMAGEBUTTON_STATE_CHECKED_RELEASED, NULL, "S:/GENERATOR/BT_REF.bin", NULL);
	lv_imagebutton_set_src(bt_mp3_usbrev, LV_IMAGEBUTTON_STATE_CHECKED_DISABLED, NULL, "S:/GENERATOR/BT_REF.bin", NULL);
	lv_obj_add_state(bt_mp3_usbrev, LV_IMAGEBUTTON_STATE_RELEASED);
	lv_obj_add_event_cb(bt_mp3_usbrev, event_mp3_usb_rev, LV_EVENT_ALL, NULL);
	lv_obj_set_pos(bt_mp3_usbrev, 380, 74);

	// Button FF
	bt_mp3_usbnext = lv_imagebutton_create(Tela_Menu_MP3);
	lv_imagebutton_set_src(bt_mp3_usbnext, LV_IMAGEBUTTON_STATE_RELEASED, NULL, "S:/GENERATOR/BT_FF.bin", NULL);
	lv_imagebutton_set_src(bt_mp3_usbnext, LV_IMAGEBUTTON_STATE_PRESSED, NULL, "S:/GENERATOR/BT_FF_P.bin", NULL);
	lv_imagebutton_set_src(bt_mp3_usbnext, LV_IMAGEBUTTON_STATE_DISABLED, NULL, "S:/GENERATOR/BT_FF.bin", NULL);
	lv_imagebutton_set_src(bt_mp3_usbnext, LV_IMAGEBUTTON_STATE_CHECKED_PRESSED, NULL, "S:/GENERATOR/BT_FF_P.bin", NULL);
	lv_imagebutton_set_src(bt_mp3_usbnext, LV_IMAGEBUTTON_STATE_CHECKED_RELEASED, NULL, "S:/GENERATOR/BT_FF.bin", NULL);
	lv_imagebutton_set_src(bt_mp3_usbnext, LV_IMAGEBUTTON_STATE_CHECKED_DISABLED, NULL, "S:/GENERATOR/BT_FF.bin", NULL);
	lv_obj_add_state(bt_mp3_usbnext, LV_IMAGEBUTTON_STATE_RELEASED);
	lv_obj_add_event_cb(bt_mp3_usbnext, event_mp3_usb_next2, LV_EVENT_ALL, NULL);
	lv_obj_set_pos(bt_mp3_usbnext, 428, 74);
}

static void event_mp3_blenext(lv_event_t * e)
{
	lv_event_code_t code = lv_event_get_code(e);

	if(code == LV_EVENT_CLICKED) {

	}
}

static void event_mp3_blestop(lv_event_t * e)
{
	lv_event_code_t code = lv_event_get_code(e);

	if(code == LV_EVENT_CLICKED) {

	}
}

static void event_mp3_blerev(lv_event_t * e)
{
	lv_event_code_t code = lv_event_get_code(e);

	if(code == LV_EVENT_CLICKED) {

	}
}

static void event_mp3_blenext1(lv_event_t * e)
{
	lv_event_code_t code = lv_event_get_code(e);

	if(code == LV_EVENT_CLICKED) {

	}
}

void create_buttons_mp3_ble(void)
{
	// Button NEXT
	bt_mp3_ble_next = lv_imagebutton_create(Tela_Menu_MP3);
	lv_imagebutton_set_src(bt_mp3_ble_next, LV_IMAGEBUTTON_STATE_RELEASED, NULL, "S:/GENERATOR/BT_NEXT.bin", NULL);
	lv_imagebutton_set_src(bt_mp3_ble_next, LV_IMAGEBUTTON_STATE_PRESSED, NULL, "S:/GENERATOR/BT_NEXT_P.bin", NULL);
	lv_imagebutton_set_src(bt_mp3_ble_next, LV_IMAGEBUTTON_STATE_DISABLED, NULL, "S:/GENERATOR/BT_NEXT.bin", NULL);
	lv_imagebutton_set_src(bt_mp3_ble_next, LV_IMAGEBUTTON_STATE_CHECKED_PRESSED, NULL, "S:/GENERATOR/BT_NEXT_P.bin", NULL);
	lv_imagebutton_set_src(bt_mp3_ble_next, LV_IMAGEBUTTON_STATE_CHECKED_RELEASED, NULL, "S:/GENERATOR/BT_NEXT.bin", NULL);
	lv_imagebutton_set_src(bt_mp3_ble_next, LV_IMAGEBUTTON_STATE_CHECKED_DISABLED, NULL, "S:/GENERATOR/BT_NEXT.bin", NULL);
	lv_obj_add_state(bt_mp3_ble_next, LV_IMAGEBUTTON_STATE_RELEASED);
	lv_obj_add_event_cb(bt_mp3_ble_next, event_mp3_blenext, LV_EVENT_ALL, NULL);
	lv_obj_set_pos(bt_mp3_ble_next, 380, 130);

	// Button PLAY/STOP
	bt_mp3_blestop = lv_imagebutton_create(Tela_Menu_MP3);
	lv_imagebutton_set_src(bt_mp3_blestop, LV_IMAGEBUTTON_STATE_RELEASED, NULL, "S:/GENERATOR/BT_STOP.bin", NULL);
	lv_imagebutton_set_src(bt_mp3_blestop, LV_IMAGEBUTTON_STATE_PRESSED, NULL, "S:/GENERATOR/BT_STOP_P.bin", NULL);
	lv_imagebutton_set_src(bt_mp3_blestop, LV_IMAGEBUTTON_STATE_DISABLED, NULL, "S:/GENERATOR/BT_STOP.bin", NULL);
	lv_imagebutton_set_src(bt_mp3_blestop, LV_IMAGEBUTTON_STATE_CHECKED_PRESSED, NULL, "S:/GENERATOR/BT_STOP_P.bin", NULL);
	lv_imagebutton_set_src(bt_mp3_blestop, LV_IMAGEBUTTON_STATE_CHECKED_RELEASED, NULL, "S:/GENERATOR/BT_STOP.bin", NULL);
	lv_imagebutton_set_src(bt_mp3_blestop, LV_IMAGEBUTTON_STATE_CHECKED_DISABLED, NULL, "S:/GENERATOR/BT_STOP.bin", NULL);
	lv_obj_add_state(bt_mp3_blestop, LV_IMAGEBUTTON_STATE_RELEASED);
	lv_obj_add_event_cb(bt_mp3_blestop, event_mp3_blestop, LV_EVENT_ALL, NULL);
	lv_obj_set_pos(bt_mp3_blestop, 428, 130);

	// Button REV
	bt_mp3_blerev = lv_imagebutton_create(Tela_Menu_MP3);
	lv_imagebutton_set_src(bt_mp3_blerev, LV_IMAGEBUTTON_STATE_RELEASED, NULL, "S:/GENERATOR/BT_REF.bin", NULL);
	lv_imagebutton_set_src(bt_mp3_blerev, LV_IMAGEBUTTON_STATE_PRESSED, NULL, "S:/GENERATOR/BT_REF_P.bin", NULL);
	lv_imagebutton_set_src(bt_mp3_blerev, LV_IMAGEBUTTON_STATE_DISABLED, NULL, "S:/GENERATOR/BT_REF.bin", NULL);
	lv_imagebutton_set_src(bt_mp3_blerev, LV_IMAGEBUTTON_STATE_CHECKED_PRESSED, NULL, "S:/GENERATOR/BT_REF_P.bin", NULL);
	lv_imagebutton_set_src(bt_mp3_blerev, LV_IMAGEBUTTON_STATE_CHECKED_RELEASED, NULL, "S:/GENERATOR/BT_REF.bin", NULL);
	lv_imagebutton_set_src(bt_mp3_blerev, LV_IMAGEBUTTON_STATE_CHECKED_DISABLED, NULL, "S:/GENERATOR/BT_REF.bin", NULL);
	lv_obj_add_state(bt_mp3_blerev, LV_IMAGEBUTTON_STATE_RELEASED);
	lv_obj_add_event_cb(bt_mp3_blerev, event_mp3_blerev, LV_EVENT_ALL, NULL);
	lv_obj_set_pos(bt_mp3_blerev, 380, 170);

	// Button FF
	bt_mp3_blenext = lv_imagebutton_create(Tela_Menu_MP3);
	lv_imagebutton_set_src(bt_mp3_blenext, LV_IMAGEBUTTON_STATE_RELEASED, NULL, "S:/GENERATOR/BT_FF.bin", NULL);
	lv_imagebutton_set_src(bt_mp3_blenext, LV_IMAGEBUTTON_STATE_PRESSED, NULL, "S:/GENERATOR/BT_FF_P.bin", NULL);
	lv_imagebutton_set_src(bt_mp3_blenext, LV_IMAGEBUTTON_STATE_DISABLED, NULL, "S:/GENERATOR/BT_FF.bin", NULL);
	lv_imagebutton_set_src(bt_mp3_blenext, LV_IMAGEBUTTON_STATE_CHECKED_PRESSED, NULL, "S:/GENERATOR/BT_FF_P.bin", NULL);
	lv_imagebutton_set_src(bt_mp3_blenext, LV_IMAGEBUTTON_STATE_CHECKED_RELEASED, NULL, "S:/GENERATOR/BT_FF.bin", NULL);
	lv_imagebutton_set_src(bt_mp3_blenext, LV_IMAGEBUTTON_STATE_CHECKED_DISABLED, NULL, "S:/GENERATOR/BT_FF.bin", NULL);
	lv_obj_add_state(bt_mp3_blenext, LV_IMAGEBUTTON_STATE_RELEASED);
	lv_obj_add_event_cb(bt_mp3_blenext, event_mp3_blenext1, LV_EVENT_ALL, NULL);
	lv_obj_set_pos(bt_mp3_blenext, 428, 170);
}

void create_titule_usb(void)
{
	// Text Titulo
    text_usb_titule = lv_label_create(Tela_Menu_MP3);
    lv_obj_set_width(text_usb_titule, 300);
    lv_obj_set_height(text_usb_titule, LV_SIZE_CONTENT);
    lv_obj_set_style_text_color(text_usb_titule, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(text_usb_titule, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(text_usb_titule, &Neue_Medium_24, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_label_set_long_mode(text_usb_titule, LV_LABEL_LONG_SCROLL_CIRCULAR);
    lv_label_set_text(text_usb_titule, "Track 17");
    lv_obj_set_style_text_align(text_usb_titule, LV_TEXT_ALIGN_LEFT, 0);
    lv_obj_set_pos(text_usb_titule, 64, 40);

    // Text Music
    text_usb_music = lv_label_create(Tela_Menu_MP3);
    lv_obj_set_width(text_usb_music, 310);
    lv_obj_set_height(text_usb_music, LV_SIZE_CONTENT);
    lv_obj_set_style_text_color(text_usb_music, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(text_usb_music, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(text_usb_music, &Neue_Medium_20, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_label_set_long_mode(text_usb_music, LV_LABEL_LONG_SCROLL_CIRCULAR);
    lv_label_set_text(text_usb_music, "Like a prayer - Madonna");
    lv_obj_set_style_text_align(text_usb_music, LV_TEXT_ALIGN_LEFT, 0);
    lv_obj_set_pos(text_usb_music, 64, 82);
}

void create_titule_mp3(void)
{
	// Text Titulo
    text_mp3_titule = lv_label_create(Tela_Menu_MP3);
    lv_obj_set_width(text_mp3_titule, 310);
    lv_obj_set_height(text_mp3_titule, LV_SIZE_CONTENT);
    lv_obj_set_style_text_color(text_mp3_titule, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(text_mp3_titule, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(text_mp3_titule, &Neue_Medium_24, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_label_set_long_mode(text_mp3_titule, LV_LABEL_LONG_SCROLL_CIRCULAR);
    lv_label_set_text(text_mp3_titule, "Iphone Luciano");
    lv_obj_set_style_text_align(text_mp3_titule, LV_TEXT_ALIGN_LEFT, 0);
    lv_obj_set_pos(text_mp3_titule, 64, 136);

    // Text Music
    text_mp3_music = lv_label_create(Tela_Menu_MP3);
    lv_obj_set_width(text_mp3_music, 310);
    lv_obj_set_height(text_mp3_music, LV_SIZE_CONTENT);
    lv_obj_set_style_text_color(text_mp3_music, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(text_mp3_music, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(text_mp3_music, &Neue_Medium_20, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_label_set_long_mode(text_mp3_music, LV_LABEL_LONG_SCROLL_CIRCULAR);
    lv_label_set_text(text_mp3_music, "Oingo Boingo - Dead men's party");
    lv_obj_set_style_text_align(text_mp3_music, LV_TEXT_ALIGN_LEFT, 0);
    lv_obj_set_pos(text_mp3_music, 64, 176);
}
