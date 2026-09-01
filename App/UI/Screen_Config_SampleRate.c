/*
 * Screen_Config_SampleRate.c
 *
 *  Created on: 29 de ago. de 2026
 *      Author: rdsan
 */

#include "stdbool.h"
#include "rng.h"
#include "stdio.h"
#include "string.h"

#include "../App/UI/Screen_Config_SampleRate.h"
#include "../App/UI/Screen_Utils.h"

LV_FONT_DECLARE(Neue_Medium_14);
LV_FONT_DECLARE(Neue_Medium_16);

void create_config_sample_label(void);
void create_config_sample_label_2(void);
void create_btn_config_sample_48(void);
void create_btn_config_sample_96(void);
void create_btn_config_sample_192(void);

lv_obj_t * Tela_Config_Sample = NULL;
static lv_obj_t * img_fundo_sample = NULL;
static lv_obj_t * text_config_sample_top = NULL;
static lv_obj_t * bt_config_sample_48 = NULL;
static lv_obj_t * bt_config_sample_96 = NULL;
static lv_obj_t * bt_config_sample_192 = NULL;

void Screen_Config_Sample_Create(void)
{
	Tela_Config_Sample = lv_obj_create(NULL);
	lv_obj_clear_flag(Tela_Config_Sample, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLLABLE);
	lv_obj_set_style_bg_color(Tela_Config_Sample, lv_color_hex(0x000000), 0);
	lv_obj_set_style_bg_grad_color(Tela_Config_Sample, lv_color_hex(0x000000), 0);

	// Label Screen
	//create_config_sample_label();
	//create_config_sample_label_2();

	// Imagem de Fundo
	img_fundo_sample = lv_img_create(Tela_Config_Sample);
	lv_img_set_src(img_fundo_sample, "S:/CONFIG/TELA_CONFIG_SAMPLE.bin");
	lv_obj_set_pos(img_fundo_sample, 0, 0);

	// Buttons
	create_btn_config_sample_48();
	create_btn_config_sample_96();
	create_btn_config_sample_192();

	create_button_back_main(Tela_Config_Sample, 380, 8, PAGE_CONFIG);
}

void create_config_sample_label(void)
{
	text_config_sample_top = lv_label_create(Tela_Config_Sample);
    lv_obj_set_width(text_config_sample_top, LV_SIZE_CONTENT);
    lv_obj_set_height(text_config_sample_top, LV_SIZE_CONTENT);
    lv_label_set_text(text_config_sample_top, "GENERAL CONFIGURATIONS/SAMPLE RATE:");
    lv_obj_set_style_text_color(text_config_sample_top, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(text_config_sample_top, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(text_config_sample_top, &Neue_Medium_14, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(text_config_sample_top, 7, 16);
}

void create_config_sample_label_2(void)
{
	// Criar o label pai na tela atual
	lv_obj_t * label_main = lv_label_create(Tela_Config_Sample);

	// Font
	lv_obj_set_style_text_color(label_main, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_opa(label_main, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(label_main, &Neue_Medium_16, LV_PART_MAIN | LV_STATE_DEFAULT);

	// Definir o texto
	lv_label_set_text(label_main,
	    "Select the desired sample rate for the AES/EBU digital\n"
	    "output. Choose 48 kHz, 96 kHz or 192 kHz to match the\n"
	    "requirements of the connected equipment. When AES192\n"
	    "is selected, the output automatically operates at a fixed\n"
	    "sample rate of 192 kHz.");

	// Definir largura fixa para forçar a quebra de linha (word wrap)
	lv_obj_set_width(label_main, 434); // Ajuste conforme a resolução da tela
	lv_label_set_long_mode(label_main, LV_LABEL_LONG_WRAP);

	// Centralizar o alinhamento das linhas de texto e a posição no container
	lv_obj_set_style_text_align(label_main, LV_TEXT_ALIGN_LEFT, 0);
	lv_obj_align(label_main, LV_ALIGN_CENTER, 10, -12);
}

static void event_bt_config_sample_48(lv_event_t * e)
{
	lv_event_code_t code = lv_event_get_code(e);

	if(code == LV_EVENT_CLICKED) {
		lv_imagebutton_set_state(bt_config_sample_48,  LV_IMAGEBUTTON_STATE_CHECKED_DISABLED);
		lv_imagebutton_set_state(bt_config_sample_96, LV_IMAGEBUTTON_STATE_RELEASED);
		lv_imagebutton_set_state(bt_config_sample_192 , LV_IMAGEBUTTON_STATE_RELEASED);
	}
}

void create_btn_config_sample_48(void)
{
	bt_config_sample_48 = lv_imagebutton_create(Tela_Config_Sample);
	lv_imagebutton_set_src(bt_config_sample_48, LV_IMAGEBUTTON_STATE_RELEASED, NULL, "S:/CONFIG/BT_CONFIG_P.bin", NULL);
	lv_imagebutton_set_src(bt_config_sample_48, LV_IMAGEBUTTON_STATE_PRESSED, NULL, "S:/CONFIG/BT_CONFIG_P_P.bin", NULL);
	lv_imagebutton_set_src(bt_config_sample_48, LV_IMAGEBUTTON_STATE_DISABLED, NULL, "S:/CONFIG/BT_CONFIG_P.bin", NULL);
	lv_imagebutton_set_src(bt_config_sample_48, LV_IMAGEBUTTON_STATE_CHECKED_PRESSED, NULL, "S:/CONFIG/BT_CONFIG_P_P.bin", NULL);
	lv_imagebutton_set_src(bt_config_sample_48, LV_IMAGEBUTTON_STATE_CHECKED_RELEASED, NULL, "S:/CONFIG/BT_CONFIG_P.bin", NULL);
	lv_imagebutton_set_src(bt_config_sample_48, LV_IMAGEBUTTON_STATE_CHECKED_DISABLED, NULL, "S:/CONFIG/BT_CONFIG_P_SEL.bin", NULL);
	lv_obj_add_event_cb(bt_config_sample_48, event_bt_config_sample_48, LV_EVENT_ALL, NULL);
	lv_obj_set_pos(bt_config_sample_48, 18, 212);
	lv_imagebutton_set_state(bt_config_sample_48, LV_IMAGEBUTTON_STATE_RELEASED);

	// Text
    lv_obj_t * text_bt_sample_48 = lv_label_create(bt_config_sample_48);
    lv_obj_set_width(text_bt_sample_48, LV_SIZE_CONTENT);
    lv_obj_set_height(text_bt_sample_48, LV_SIZE_CONTENT);
    lv_label_set_text(text_bt_sample_48, "48 KHz");
    lv_obj_set_style_text_color(text_bt_sample_48, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(text_bt_sample_48, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(text_bt_sample_48, &Neue_Medium_14, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_align_to(text_bt_sample_48, bt_config_sample_48, LV_ALIGN_CENTER, 0, 0);
}


static void event_bt_config_sample_96(lv_event_t * e)
{
	lv_event_code_t code = lv_event_get_code(e);

	if(code == LV_EVENT_CLICKED) {
		lv_imagebutton_set_state(bt_config_sample_48,  LV_IMAGEBUTTON_STATE_RELEASED);
		lv_imagebutton_set_state(bt_config_sample_96, LV_IMAGEBUTTON_STATE_CHECKED_DISABLED);
		lv_imagebutton_set_state(bt_config_sample_192 , LV_IMAGEBUTTON_STATE_RELEASED);
	}
}

void create_btn_config_sample_96(void)
{
	bt_config_sample_96 = lv_imagebutton_create(Tela_Config_Sample);
	lv_imagebutton_set_src(bt_config_sample_96, LV_IMAGEBUTTON_STATE_RELEASED, NULL, "S:/CONFIG/BT_CONFIG_P.bin", NULL);
	lv_imagebutton_set_src(bt_config_sample_96, LV_IMAGEBUTTON_STATE_PRESSED, NULL, "S:/CONFIG/BT_CONFIG_P_P.bin", NULL);
	lv_imagebutton_set_src(bt_config_sample_96, LV_IMAGEBUTTON_STATE_DISABLED, NULL, "S:/CONFIG/BT_CONFIG_P.bin", NULL);
	lv_imagebutton_set_src(bt_config_sample_96, LV_IMAGEBUTTON_STATE_CHECKED_PRESSED, NULL, "S:/CONFIG/BT_CONFIG_P_P.bin", NULL);
	lv_imagebutton_set_src(bt_config_sample_96, LV_IMAGEBUTTON_STATE_CHECKED_RELEASED, NULL, "S:/CONFIG/BT_CONFIG_P.bin", NULL);
	lv_imagebutton_set_src(bt_config_sample_96, LV_IMAGEBUTTON_STATE_CHECKED_DISABLED, NULL, "S:/CONFIG/BT_CONFIG_P_SEL.bin", NULL);
	lv_obj_add_event_cb(bt_config_sample_96, event_bt_config_sample_96, LV_EVENT_ALL, NULL);
	lv_obj_set_pos(bt_config_sample_96, 172, 212);
	lv_imagebutton_set_state(bt_config_sample_96, LV_IMAGEBUTTON_STATE_RELEASED);

	// Text
    lv_obj_t * text_bt_sample_96 = lv_label_create(bt_config_sample_96);
    lv_obj_set_width(text_bt_sample_96, LV_SIZE_CONTENT);
    lv_obj_set_height(text_bt_sample_96, LV_SIZE_CONTENT);
    lv_label_set_text(text_bt_sample_96, "96 KHz");
    lv_obj_set_style_text_color(text_bt_sample_96, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(text_bt_sample_96, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(text_bt_sample_96, &Neue_Medium_14, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_align_to(text_bt_sample_96, bt_config_sample_96, LV_ALIGN_CENTER, 0, 0);
}

static void event_bt_config_sample_192(lv_event_t * e)
{
	lv_event_code_t code = lv_event_get_code(e);

	if(code == LV_EVENT_CLICKED) {
		lv_imagebutton_set_state(bt_config_sample_48,  LV_IMAGEBUTTON_STATE_RELEASED);
		lv_imagebutton_set_state(bt_config_sample_96, LV_IMAGEBUTTON_STATE_RELEASED);
		lv_imagebutton_set_state(bt_config_sample_192 , LV_IMAGEBUTTON_STATE_CHECKED_DISABLED);
	}
}

void create_btn_config_sample_192(void)
{
	bt_config_sample_192 = lv_imagebutton_create(Tela_Config_Sample);
	lv_imagebutton_set_src(bt_config_sample_192, LV_IMAGEBUTTON_STATE_RELEASED, NULL, "S:/CONFIG/BT_CONFIG_P.bin", NULL);
	lv_imagebutton_set_src(bt_config_sample_192, LV_IMAGEBUTTON_STATE_PRESSED, NULL, "S:/CONFIG/BT_CONFIG_P_P.bin", NULL);
	lv_imagebutton_set_src(bt_config_sample_192, LV_IMAGEBUTTON_STATE_DISABLED, NULL, "S:/CONFIG/BT_CONFIG_P.bin", NULL);
	lv_imagebutton_set_src(bt_config_sample_192, LV_IMAGEBUTTON_STATE_CHECKED_PRESSED, NULL, "S:/CONFIG/BT_CONFIG_P_P.bin", NULL);
	lv_imagebutton_set_src(bt_config_sample_192, LV_IMAGEBUTTON_STATE_CHECKED_RELEASED, NULL, "S:/CONFIG/BT_CONFIG_P.bin", NULL);
	lv_imagebutton_set_src(bt_config_sample_192, LV_IMAGEBUTTON_STATE_CHECKED_DISABLED, NULL, "S:/CONFIG/BT_CONFIG_P_SEL.bin", NULL);
	lv_obj_add_event_cb(bt_config_sample_192, event_bt_config_sample_192, LV_EVENT_ALL, NULL);
	lv_obj_set_pos(bt_config_sample_192, 326, 212);
	lv_imagebutton_set_state(bt_config_sample_192, LV_IMAGEBUTTON_STATE_CHECKED_DISABLED);

	// Text
    lv_obj_t * text_bt_sample_192 = lv_label_create(bt_config_sample_192);
    lv_obj_set_width(text_bt_sample_192, LV_SIZE_CONTENT);
    lv_obj_set_height(text_bt_sample_192, LV_SIZE_CONTENT);
    lv_label_set_text(text_bt_sample_192, "192 KHz");
    lv_obj_set_style_text_color(text_bt_sample_192, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(text_bt_sample_192, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(text_bt_sample_192, &Neue_Medium_14, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_align_to(text_bt_sample_192, bt_config_sample_192, LV_ALIGN_CENTER, 0, 0);
}
