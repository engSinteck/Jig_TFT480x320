/*
 * Screen_Config.c
 *
 *  Created on: 28 de ago. de 2026
 *      Author: rinaldo.santos
 */

#include "stdbool.h"
#include "rng.h"
#include "stdio.h"
#include "string.h"

#include "../App/UI/Screen_Config.h"
#include "../App/UI/Screen_Utils.h"

LV_FONT_DECLARE(Neue_Medium_14);

void create_labels_config(void);
void create_buttons_config(void);
void create_buttons_config_about(void);

lv_obj_t * Tela_Config = NULL;
static lv_obj_t * img_fundo_config = NULL;
static lv_obj_t * text_config_top = NULL;
static lv_obj_t * bt_config[8];
static lv_obj_t * label_bt_config[8];
static lv_obj_t * bt_config_about;

void Screen_Config_Create(void)
{
	Tela_Config = lv_obj_create(NULL);
	lv_obj_clear_flag(Tela_Config, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLLABLE);
	lv_obj_set_style_bg_color(Tela_Config, lv_color_hex(0x000000), 0);
	lv_obj_set_style_bg_grad_color(Tela_Config, lv_color_hex(0x000000), 0);

	// Imagem de Fundo
	img_fundo_config = lv_img_create(Tela_Config);
	lv_img_set_src(img_fundo_config, "S:/CONFIG/TELA_FUNDO.bin");
	lv_obj_set_pos(img_fundo_config, 0, 0);

	// Text Top
	create_labels_config();

	// Buttons
	create_buttons_config();
	create_buttons_config_about();

	create_button_back_main(Tela_Config, 380, 8);
}

void create_labels_config(void)
{
    text_config_top = lv_label_create(Tela_Config);
    lv_obj_set_width(text_config_top, LV_SIZE_CONTENT);
    lv_obj_set_height(text_config_top, LV_SIZE_CONTENT);
    lv_label_set_text(text_config_top, "GENERAL CONFIGURATIONS:");
    lv_obj_set_style_text_color(text_config_top, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(text_config_top, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(text_config_top, &Neue_Medium_14, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(text_config_top, 7, 5);
}

void create_buttons_config(void)
{
    // Button
	for(uint8_t x = 0; x < 8; x++) {
		bt_config[x] = lv_imagebutton_create(Tela_Config);
		lv_imagebutton_set_src(bt_config[x], LV_IMAGEBUTTON_STATE_RELEASED, NULL, "S:/CONFIG/BT_CONFIG.bin", NULL);
		lv_imagebutton_set_src(bt_config[x], LV_IMAGEBUTTON_STATE_PRESSED, NULL, "S:/CONFIG/BT_CONFIG_P.bin", NULL);
		lv_imagebutton_set_src(bt_config[x], LV_IMAGEBUTTON_STATE_DISABLED, NULL, "S:/CONFIG/BT_CONFIG.bin", NULL);
		lv_imagebutton_set_src(bt_config[x], LV_IMAGEBUTTON_STATE_CHECKED_PRESSED, NULL, "S:/CONFIG/BT_CONFIG_P.bin", NULL);
		lv_imagebutton_set_src(bt_config[x], LV_IMAGEBUTTON_STATE_CHECKED_RELEASED, NULL, "S:/CONFIG/BT_CONFIG.bin", NULL);
		lv_imagebutton_set_src(bt_config[x], LV_IMAGEBUTTON_STATE_CHECKED_DISABLED, NULL, "S:/CONFIG/BT_CONFIG.bin", NULL);
		lv_obj_add_state(bt_config[x], LV_IMAGEBUTTON_STATE_RELEASED);

		// Text
		label_bt_config[x] = lv_label_create(bt_config[x]);
	    lv_obj_set_width(label_bt_config[x], LV_SIZE_CONTENT);
	    lv_obj_set_height(label_bt_config[x], LV_SIZE_CONTENT);
	    lv_obj_set_style_text_color(label_bt_config[x], lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
	    lv_obj_set_style_text_opa(label_bt_config[x], 255, LV_PART_MAIN | LV_STATE_DEFAULT);
	    lv_obj_set_style_text_font(label_bt_config[x], &Neue_Medium_14, LV_PART_MAIN | LV_STATE_DEFAULT);
	    //lv_obj_align_to(label_bt_config[x], bt_config[x], LV_ALIGN_CENTER, 0, 0);
	}

	lv_obj_set_pos(bt_config[0], 30, 50);
	lv_obj_set_pos(bt_config[1], 30, 100);
	lv_obj_set_pos(bt_config[2], 30, 150);
	lv_obj_set_pos(bt_config[3], 30, 200);

	lv_obj_set_pos(bt_config[4], 225, 50);
	lv_obj_set_pos(bt_config[5], 225, 100);
	lv_obj_set_pos(bt_config[6], 225, 150);
	lv_obj_set_pos(bt_config[7], 225, 200);

	// Text
    lv_label_set_text(label_bt_config[0], "XLR INPUT IMPEDANCE");
    lv_obj_align_to(label_bt_config[0], bt_config[0], LV_ALIGN_CENTER, 0, 0);
    lv_label_set_text(label_bt_config[1], "AUDIO INPUT TYPE");
    lv_obj_align_to(label_bt_config[1], bt_config[1], LV_ALIGN_CENTER, 0, 0);
    lv_label_set_text(label_bt_config[2], "AUDIO OUTPUT TYPE");
    lv_obj_align_to(label_bt_config[2], bt_config[2], LV_ALIGN_CENTER, 0, 0);
    lv_label_set_text(label_bt_config[3], "SAMPLE RATE");
    lv_obj_align_to(label_bt_config[3], bt_config[3], LV_ALIGN_CENTER, 0, 0);

    lv_label_set_text(label_bt_config[4], "SILENCE TIMEOUT");
    lv_obj_align_to(label_bt_config[4], bt_config[4], LV_ALIGN_CENTER, 0, 0);
    lv_label_set_text(label_bt_config[5], "LOCK SETTINGS");
    lv_obj_align_to(label_bt_config[5], bt_config[5], LV_ALIGN_CENTER, 0, 0);
    lv_label_set_text(label_bt_config[6], "DISPLAY");
    lv_obj_align_to(label_bt_config[6], bt_config[6], LV_ALIGN_CENTER, 0, 0);
    lv_label_set_text(label_bt_config[7], "SIGNAL GENERATOR");
    lv_obj_align_to(label_bt_config[7], bt_config[7], LV_ALIGN_CENTER, 0, 0);

	//lv_obj_add_event_cb(bt_config[0], event_bt_out_phone_inc, LV_EVENT_ALL, NULL);
}

void create_buttons_config_about(void)
{
	bt_config_about = lv_imagebutton_create(Tela_Config);
	lv_imagebutton_set_src(bt_config_about, LV_IMAGEBUTTON_STATE_RELEASED, NULL, "S:/CONFIG/BT_CONFIG_VD.bin", NULL);
	lv_imagebutton_set_src(bt_config_about, LV_IMAGEBUTTON_STATE_PRESSED, NULL, "S:/CONFIG/BT_CONFIG_VD_P.bin", NULL);
	lv_imagebutton_set_src(bt_config_about, LV_IMAGEBUTTON_STATE_DISABLED, NULL, "S:/CONFIG/BT_CONFIG_VD.bin", NULL);
	lv_imagebutton_set_src(bt_config_about, LV_IMAGEBUTTON_STATE_CHECKED_PRESSED, NULL, "S:/CONFIG/BT_CONFIG_VD_P.bin", NULL);
	lv_imagebutton_set_src(bt_config_about, LV_IMAGEBUTTON_STATE_CHECKED_RELEASED, NULL, "S:/CONFIG/BT_CONFIG_VD.bin", NULL);
	lv_imagebutton_set_src(bt_config_about, LV_IMAGEBUTTON_STATE_CHECKED_DISABLED, NULL, "S:/CONFIG/BT_CONFIG_VD.bin", NULL);
	lv_obj_add_state(bt_config_about, LV_IMAGEBUTTON_STATE_RELEASED);
	//lv_obj_add_event_cb(bt_config_about, event_bt_out_phone_inc, LV_EVENT_ALL, NULL);
	lv_obj_set_pos(bt_config_about, 225, 250);

	// Text
    lv_obj_t * text_config_about = lv_label_create(bt_config_about);
    lv_obj_set_width(text_config_about, LV_SIZE_CONTENT);
    lv_obj_set_height(text_config_about, LV_SIZE_CONTENT);
    lv_label_set_text(text_config_about, "ABOUT THIS PRODUCT");
    lv_obj_set_style_text_color(text_config_about, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(text_config_about, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(text_config_about, &Neue_Medium_14, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_align_to(text_config_about, bt_config_about, LV_ALIGN_CENTER, 0, 0);
}
