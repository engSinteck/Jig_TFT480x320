/*
 * Screen_Config_Lock.c
 *
 *  Created on: 29 de ago. de 2026
 *      Author: rdsan
 */

#include "stdbool.h"
#include "rng.h"
#include "stdio.h"
#include "string.h"

#include "../App/UI/Screen_Config_Lock.h"
#include "../App/UI/Screen_Utils.h"

LV_FONT_DECLARE(Neue_Medium_14);
LV_FONT_DECLARE(Neue_Medium_16);

void create_config_lock_label(void);
void create_config_lock_label_2(void);
void create_btn_config_lock(void);
void create_btn_config_unlock(void);

lv_obj_t * Tela_Config_Lock = NULL;
static lv_obj_t * text_config_lock_top = NULL;
static lv_obj_t * bt_config_lock = NULL;
static lv_obj_t * bt_config_unlock = NULL;
static lv_obj_t * img_fundo_lock = NULL;

void Screen_Config_Lock_Create(void)
{
	Tela_Config_Lock = lv_obj_create(NULL);
	lv_obj_clear_flag(Tela_Config_Lock, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLLABLE);
	lv_obj_set_style_bg_color(Tela_Config_Lock, lv_color_hex(0x000000), 0);
	lv_obj_set_style_bg_grad_color(Tela_Config_Lock, lv_color_hex(0x000000), 0);

	// Label Screen
	//create_config_lock_label();
	//create_config_lock_label_2();

	// Imagem de Fundo
	img_fundo_lock = lv_img_create(Tela_Config_Lock);
	lv_img_set_src(img_fundo_lock, "S:/CONFIG/TELA_CONFIG_LOCK.bin");
	lv_obj_set_pos(img_fundo_lock, 0, 0);

	// Buttons
	create_btn_config_lock();
	create_btn_config_unlock();

	create_button_back_main(Tela_Config_Lock, 380, 8, PAGE_CONFIG);
}

void create_config_lock_label(void)
{
	text_config_lock_top = lv_label_create(Tela_Config_Lock);
    lv_obj_set_width(text_config_lock_top, LV_SIZE_CONTENT);
    lv_obj_set_height(text_config_lock_top, LV_SIZE_CONTENT);
    lv_label_set_text(text_config_lock_top, "GENERAL CONFIGURATIONS/LOCK SETTINGS:");
    lv_obj_set_style_text_color(text_config_lock_top, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(text_config_lock_top, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(text_config_lock_top, &Neue_Medium_14, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(text_config_lock_top, 7, 16);
}

void create_config_lock_label_2(void)
{
	// Criar o label pai na tela atual
	lv_obj_t * label_main = lv_label_create(Tela_Config_Lock);

	// Font
	lv_obj_set_style_text_color(label_main, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_opa(label_main, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(label_main, &Neue_Medium_16, LV_PART_MAIN | LV_STATE_DEFAULT);

	// Definir o texto
	lv_label_set_text(label_main,
	    "The Lock Settings feature prevents unauthorized or\n"
	    "accidental modification of the device configuration.\n"
	    "When enabled, users cannot change any settings until\n"
		"the lock is disabled. This feature is recommended for\n"
		"installations where the equipment is accessible to\n"
		"multiple users, helping to protect the system from\n"
		"unintended or unauthorized adjustments.");

	// Definir largura fixa para forçar a quebra de linha (word wrap)
	lv_obj_set_width(label_main, 400); // Ajuste conforme a resolução da tela
	lv_label_set_long_mode(label_main, LV_LABEL_LONG_WRAP);

	// Centralizar o alinhamento das linhas de texto e a posição no container
	lv_obj_set_style_text_align(label_main, LV_TEXT_ALIGN_LEFT, 0);
	lv_obj_align(label_main, LV_ALIGN_CENTER, 4, -12);
}

static void event_bt_unlock(lv_event_t * e)
{
	lv_event_code_t code = lv_event_get_code(e);

	if(code == LV_EVENT_CLICKED) {
		lv_imagebutton_set_state(bt_config_unlock, LV_IMAGEBUTTON_STATE_CHECKED_DISABLED);
		lv_imagebutton_set_state(bt_config_lock, LV_IMAGEBUTTON_STATE_RELEASED);
	}
}

void create_btn_config_unlock(void)
{
	bt_config_unlock = lv_imagebutton_create(Tela_Config_Lock);
	lv_imagebutton_set_src(bt_config_unlock, LV_IMAGEBUTTON_STATE_RELEASED, NULL, "S:/CONFIG/BT_CONFIG_G.bin", NULL);
	lv_imagebutton_set_src(bt_config_unlock, LV_IMAGEBUTTON_STATE_PRESSED, NULL, "S:/CONFIG/BT_CONFIG_G_P.bin", NULL);
	lv_imagebutton_set_src(bt_config_unlock, LV_IMAGEBUTTON_STATE_DISABLED, NULL, "S:/CONFIG/BT_CONFIG_G.bin", NULL);
	lv_imagebutton_set_src(bt_config_unlock, LV_IMAGEBUTTON_STATE_CHECKED_PRESSED, NULL, "S:/CONFIG/BT_CONFIG_G_P.bin", NULL);
	lv_imagebutton_set_src(bt_config_unlock, LV_IMAGEBUTTON_STATE_CHECKED_RELEASED, NULL, "S:/CONFIG/BT_CONFIG_G.bin", NULL);
	lv_imagebutton_set_src(bt_config_unlock, LV_IMAGEBUTTON_STATE_CHECKED_DISABLED, NULL, "S:/CONFIG/BT_CONFIG_G_SEL.bin", NULL);
	lv_obj_add_event_cb(bt_config_unlock, event_bt_unlock, LV_EVENT_ALL, NULL);
	lv_obj_set_pos(bt_config_unlock, 23, 212);
	lv_imagebutton_set_state(bt_config_unlock, LV_IMAGEBUTTON_STATE_CHECKED_DISABLED);

	// Text
    lv_obj_t * text_bt_unlock = lv_label_create(bt_config_unlock);
    lv_obj_set_width(text_bt_unlock, LV_SIZE_CONTENT);
    lv_obj_set_height(text_bt_unlock, LV_SIZE_CONTENT);
    lv_label_set_text(text_bt_unlock, "UNLOCK SETTINGS");
    lv_obj_set_style_text_color(text_bt_unlock, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(text_bt_unlock, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(text_bt_unlock, &Neue_Medium_14, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_align_to(text_bt_unlock, bt_config_unlock, LV_ALIGN_CENTER, 0, 0);
}

static void event_bt_lock(lv_event_t * e)
{
	lv_event_code_t code = lv_event_get_code(e);

	if(code == LV_EVENT_CLICKED) {
		lv_imagebutton_set_state(bt_config_unlock, LV_IMAGEBUTTON_STATE_RELEASED);
		lv_imagebutton_set_state(bt_config_lock, LV_IMAGEBUTTON_STATE_CHECKED_DISABLED);
	}
}

void create_btn_config_lock(void)
{
	bt_config_lock = lv_imagebutton_create(Tela_Config_Lock);
	lv_imagebutton_set_src(bt_config_lock, LV_IMAGEBUTTON_STATE_RELEASED, NULL, "S:/CONFIG/BT_CONFIG_G.bin", NULL);
	lv_imagebutton_set_src(bt_config_lock, LV_IMAGEBUTTON_STATE_PRESSED, NULL, "S:/CONFIG/BT_CONFIG_G_P.bin", NULL);
	lv_imagebutton_set_src(bt_config_lock, LV_IMAGEBUTTON_STATE_DISABLED, NULL, "S:/CONFIG/BT_CONFIG_G.bin", NULL);
	lv_imagebutton_set_src(bt_config_lock, LV_IMAGEBUTTON_STATE_CHECKED_PRESSED, NULL, "S:/CONFIG/BT_CONFIG_G_P.bin", NULL);
	lv_imagebutton_set_src(bt_config_lock, LV_IMAGEBUTTON_STATE_CHECKED_RELEASED, NULL, "S:/CONFIG/BT_CONFIG_G.bin", NULL);
	lv_imagebutton_set_src(bt_config_lock, LV_IMAGEBUTTON_STATE_CHECKED_DISABLED, NULL, "S:/CONFIG/BT_CONFIG_G_SEL.bin", NULL);
	lv_obj_add_event_cb(bt_config_lock, event_bt_lock, LV_EVENT_ALL, NULL);
	lv_obj_set_pos(bt_config_lock, 252, 212);
	lv_imagebutton_set_state(bt_config_lock, LV_IMAGEBUTTON_STATE_RELEASED);

	// Text
    lv_obj_t * text_bt_lock = lv_label_create(bt_config_lock);
    lv_obj_set_width(text_bt_lock, LV_SIZE_CONTENT);
    lv_obj_set_height(text_bt_lock, LV_SIZE_CONTENT);
    lv_label_set_text(text_bt_lock, "LOCK SETTINGS");
    lv_obj_set_style_text_color(text_bt_lock, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(text_bt_lock, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(text_bt_lock, &Neue_Medium_14, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_align_to(text_bt_lock, bt_config_lock, LV_ALIGN_CENTER, 0, 0);
}
