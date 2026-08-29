/*
 * Screen_Config_Impedance.c
 *
 *  Created on: 29 de ago. de 2026
 *      Author: rdsan
 */

#include "stdbool.h"
#include "rng.h"
#include "stdio.h"
#include "string.h"

#include "../App/UI/Screen_Config_Impedance.h"
#include "../App/UI/Screen_Utils.h"

LV_FONT_DECLARE(Neue_Medium_14);

void create_config_imp_label(void);
void create_btn_config_imp_600(void);
void create_btn_config_imp_10k(void);

lv_obj_t * Tela_Config_IMP = NULL;
static lv_obj_t * text_config_imp_top = NULL;
static lv_obj_t * bt_config_imp_600 = NULL;
static lv_obj_t * bt_config_imp_10k = NULL;

void Screen_Config_IMP_Create(void)
{
	Tela_Config_IMP = lv_obj_create(NULL);
	lv_obj_clear_flag(Tela_Config_IMP, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLLABLE);
	lv_obj_set_style_bg_color(Tela_Config_IMP, lv_color_hex(0x000000), 0);
	lv_obj_set_style_bg_grad_color(Tela_Config_IMP, lv_color_hex(0x000000), 0);

	// Label Screen
	create_config_imp_label();

	// Buttons
	create_btn_config_imp_600();
	create_btn_config_imp_10k();

	create_button_back_main(Tela_Config_IMP, 380, 8, PAGE_CONFIG);
}

void create_config_imp_label(void)
{
    text_config_imp_top = lv_label_create(Tela_Config_IMP);
    lv_obj_set_width(text_config_imp_top, LV_SIZE_CONTENT);
    lv_obj_set_height(text_config_imp_top, LV_SIZE_CONTENT);
    lv_label_set_text(text_config_imp_top, "GENERAL CONFIGURATIONS/XLR INPUT IMPEDANCE:");
    lv_obj_set_style_text_color(text_config_imp_top, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(text_config_imp_top, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(text_config_imp_top, &Neue_Medium_14, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(text_config_imp_top, 7, 16);
}

static void event_bt_600(lv_event_t * e)
{
	lv_event_code_t code = lv_event_get_code(e);

	if(code == LV_EVENT_CLICKED) {

	}
}

void create_btn_config_imp_600(void)
{
	bt_config_imp_600 = lv_imagebutton_create(Tela_Config_IMP);
	lv_imagebutton_set_src(bt_config_imp_600, LV_IMAGEBUTTON_STATE_RELEASED, NULL, "S:/CONFIG/BT_CONFIG.bin", NULL);
	lv_imagebutton_set_src(bt_config_imp_600, LV_IMAGEBUTTON_STATE_PRESSED, NULL, "S:/CONFIG/BT_CONFIG_P.bin", NULL);
	lv_imagebutton_set_src(bt_config_imp_600, LV_IMAGEBUTTON_STATE_DISABLED, NULL, "S:/CONFIG/BT_CONFIG.bin", NULL);
	lv_imagebutton_set_src(bt_config_imp_600, LV_IMAGEBUTTON_STATE_CHECKED_PRESSED, NULL, "S:/CONFIG/BT_CONFIG_P.bin", NULL);
	lv_imagebutton_set_src(bt_config_imp_600, LV_IMAGEBUTTON_STATE_CHECKED_RELEASED, NULL, "S:/CONFIG/BT_CONFIG.bin", NULL);
	lv_imagebutton_set_src(bt_config_imp_600, LV_IMAGEBUTTON_STATE_CHECKED_DISABLED, NULL, "S:/CONFIG/BT_CONFIG_SEL.bin", NULL);
	lv_obj_add_event_cb(bt_config_imp_600, event_bt_600, LV_EVENT_ALL, NULL);
	lv_obj_set_pos(bt_config_imp_600, 40, 200);
	lv_imagebutton_set_state(bt_config_imp_600, LV_IMAGEBUTTON_STATE_RELEASED);

	// Text
    lv_obj_t * text_bt_imp_600 = lv_label_create(bt_config_imp_600);
    lv_obj_set_width(text_bt_imp_600, LV_SIZE_CONTENT);
    lv_obj_set_height(text_bt_imp_600, LV_SIZE_CONTENT);
    lv_label_set_text(text_bt_imp_600, "600 OHMS");
    lv_obj_set_style_text_color(text_bt_imp_600, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(text_bt_imp_600, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(text_bt_imp_600, &Neue_Medium_14, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_align_to(text_bt_imp_600, bt_config_imp_600, LV_ALIGN_CENTER, 0, 0);
}

static void event_bt_10k(lv_event_t * e)
{
	lv_event_code_t code = lv_event_get_code(e);

	if(code == LV_EVENT_CLICKED) {

	}
}

void create_btn_config_imp_10k(void)
{
	bt_config_imp_10k = lv_imagebutton_create(Tela_Config_IMP);
	lv_imagebutton_set_src(bt_config_imp_10k, LV_IMAGEBUTTON_STATE_RELEASED, NULL, "S:/CONFIG/BT_CONFIG.bin", NULL);
	lv_imagebutton_set_src(bt_config_imp_10k, LV_IMAGEBUTTON_STATE_PRESSED, NULL, "S:/CONFIG/BT_CONFIG_P.bin", NULL);
	lv_imagebutton_set_src(bt_config_imp_10k, LV_IMAGEBUTTON_STATE_DISABLED, NULL, "S:/CONFIG/BT_CONFIG.bin", NULL);
	lv_imagebutton_set_src(bt_config_imp_10k, LV_IMAGEBUTTON_STATE_CHECKED_PRESSED, NULL, "S:/CONFIG/BT_CONFIG_P.bin", NULL);
	lv_imagebutton_set_src(bt_config_imp_10k, LV_IMAGEBUTTON_STATE_CHECKED_RELEASED, NULL, "S:/CONFIG/BT_CONFIG.bin", NULL);
	lv_imagebutton_set_src(bt_config_imp_10k, LV_IMAGEBUTTON_STATE_CHECKED_DISABLED, NULL, "S:/CONFIG/BT_CONFIG_SEL.bin", NULL);
	lv_obj_add_event_cb(bt_config_imp_10k, event_bt_10k, LV_EVENT_ALL, NULL);
	lv_obj_set_pos(bt_config_imp_10k, 261, 200);
	lv_imagebutton_set_state(bt_config_imp_10k, LV_IMAGEBUTTON_STATE_RELEASED);

	// Text
    lv_obj_t * text_bt_imp_10k = lv_label_create(bt_config_imp_10k);
    lv_obj_set_width(text_bt_imp_10k, LV_SIZE_CONTENT);
    lv_obj_set_height(text_bt_imp_10k, LV_SIZE_CONTENT);
    lv_label_set_text(text_bt_imp_10k, "10K OHMS");
    lv_obj_set_style_text_color(text_bt_imp_10k, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(text_bt_imp_10k, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(text_bt_imp_10k, &Neue_Medium_14, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_align_to(text_bt_imp_10k, bt_config_imp_10k, LV_ALIGN_CENTER, 0, 0);
}

