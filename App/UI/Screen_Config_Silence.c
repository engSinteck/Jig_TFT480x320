/*
 * Screen_Config_Silence.c
 *
 *  Created on: 29 de ago. de 2026
 *      Author: rdsan
 */

#include "stdbool.h"
#include "rng.h"
#include "stdio.h"
#include "string.h"

#include "../App/UI/Screen_Config_Silence.h"
#include "../App/UI/Screen_Utils.h"

LV_FONT_DECLARE(Neue_Medium_14);
LV_FONT_DECLARE(Neue_Medium_16);

void create_config_silence_label(void);
void create_config_silence_label_2(void);
void create_btn_silence_pc(void);
void create_btn_silence_tuner(void);
void create_btn_silence_ble(void);
void create_btn_silence_30s(void);
void create_btn_silence_1min(void);
void create_btn_silence_2min(void);
void create_btn_silence_5min(void);
void create_btn_silence_10min(void);
void create_btn_silence_never(void);

lv_obj_t * Tela_Config_Silence = NULL;
static lv_obj_t * text_config_silence_top = NULL;
static lv_obj_t * bt_config_silence_pc = NULL;
static lv_obj_t * bt_config_silence_tuner = NULL;
static lv_obj_t * bt_config_silence_ble = NULL;
static lv_obj_t * bt_config_silence_30s = NULL;
static lv_obj_t * bt_config_silence_1min = NULL;
static lv_obj_t * bt_config_silence_2min = NULL;
static lv_obj_t * bt_config_silence_5min = NULL;
static lv_obj_t * bt_config_silence_10min = NULL;
static lv_obj_t * bt_config_silence_never = NULL;
static lv_obj_t * img_fundo_silence = NULL;

void Screen_Config_Silence_Create(void)
{
	Tela_Config_Silence = lv_obj_create(NULL);
	lv_obj_clear_flag(Tela_Config_Silence, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLLABLE);
	lv_obj_set_style_bg_color(Tela_Config_Silence, lv_color_hex(0x000000), 0);
	lv_obj_set_style_bg_grad_color(Tela_Config_Silence, lv_color_hex(0x000000), 0);

	// Label Screen
	//create_config_silence_label();
	//create_config_silence_label_2();

	// Imagem de Fundo
	img_fundo_silence = lv_img_create(Tela_Config_Silence);
	lv_img_set_src(img_fundo_silence, "S:/CONFIG/TELA_CONFIG_SILENCE.bin");
	lv_obj_set_pos(img_fundo_silence, 0, 0);

	// Buttons
	create_btn_silence_30s();
	create_btn_silence_1min();
	create_btn_silence_2min();
	create_btn_silence_5min();
	create_btn_silence_10min();
	create_btn_silence_never();
	//
	create_btn_silence_pc();
	create_btn_silence_tuner();
	create_btn_silence_ble();

	create_button_back_main(Tela_Config_Silence, 380, 8, PAGE_CONFIG);
}

void create_config_silence_label(void)
{
	text_config_silence_top = lv_label_create(Tela_Config_Silence);
    lv_obj_set_width(text_config_silence_top, LV_SIZE_CONTENT);
    lv_obj_set_height(text_config_silence_top, LV_SIZE_CONTENT);
    lv_label_set_text(text_config_silence_top, "GENERAL CONFIGURATIONS/SILENCE TIMEOUT:");
    lv_obj_set_style_text_color(text_config_silence_top, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(text_config_silence_top, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(text_config_silence_top, &Neue_Medium_14, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(text_config_silence_top, 7, 16);
}

void create_config_silence_label_2(void)
{
	// Criar o label pai na tela atual
	lv_obj_t * label_main = lv_label_create(Tela_Config_Silence);

	// Font
	lv_obj_set_style_text_color(label_main, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_opa(label_main, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(label_main, &Neue_Medium_14, LV_PART_MAIN | LV_STATE_DEFAULT);

	// Definir o texto
	// Texto do bloco superior
	lv_label_set_text(label_main,
	    "          Set the delay before the audio interface automatically\n"
	    "switches to the USB audio input when no audio is detected on the\n"
	    "selected primary input.");

	// Definir largura fixa para forçar a quebra de linha (word wrap)
	lv_obj_set_width(label_main, 434); // Ajuste conforme a resolução da tela
	lv_label_set_long_mode(label_main, LV_LABEL_LONG_WRAP);

	// Centralizar o alinhamento das linhas de texto e a posição no container
	lv_obj_set_style_text_align(label_main, LV_TEXT_ALIGN_LEFT, 0);
	lv_obj_align(label_main, LV_ALIGN_CENTER, 4, -92);

	// Criar o label pai na tela atual
	lv_obj_t * label_main_b = lv_label_create(Tela_Config_Silence);

	// Font
	lv_obj_set_style_text_color(label_main_b, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_opa(label_main_b, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(label_main_b, &Neue_Medium_14, LV_PART_MAIN | LV_STATE_DEFAULT);

	// Definir o texto
	// Texto do bloco superior
	lv_label_set_text(label_main_b,
	    "       If no audio is available from the USB drive, or if no USB\n"
	    "drive is connected, select the backup audio source to be used by\n"
	    "the Silence Detector:");

	// Definir largura fixa para forçar a quebra de linha (word wrap)
	lv_obj_set_width(label_main_b, 434); // Ajuste conforme a resolução da tela
	lv_label_set_long_mode(label_main_b, LV_LABEL_LONG_WRAP);

	// Centralizar o alinhamento das linhas de texto e a posição no container
	lv_obj_set_style_text_align(label_main_b, LV_TEXT_ALIGN_LEFT, 0);
	lv_obj_align(label_main_b, LV_ALIGN_CENTER, 4, 64);
}

static void event_bt_silence_pc(lv_event_t * e)
{
	lv_event_code_t code = lv_event_get_code(e);

	if(code == LV_EVENT_CLICKED) {
		lv_imagebutton_set_state(bt_config_silence_pc,  LV_IMAGEBUTTON_STATE_CHECKED_DISABLED);
		lv_imagebutton_set_state(bt_config_silence_tuner, LV_IMAGEBUTTON_STATE_RELEASED);
		lv_imagebutton_set_state(bt_config_silence_ble , LV_IMAGEBUTTON_STATE_RELEASED);
	}
}

void create_btn_silence_pc(void)
{
	bt_config_silence_pc = lv_imagebutton_create(Tela_Config_Silence);
	lv_imagebutton_set_src(bt_config_silence_pc, LV_IMAGEBUTTON_STATE_RELEASED, NULL, "S:/CONFIG/BT_CONFIG_P.bin", NULL);
	lv_imagebutton_set_src(bt_config_silence_pc, LV_IMAGEBUTTON_STATE_PRESSED, NULL, "S:/CONFIG/BT_CONFIG_P_P.bin", NULL);
	lv_imagebutton_set_src(bt_config_silence_pc, LV_IMAGEBUTTON_STATE_DISABLED, NULL, "S:/CONFIG/BT_CONFIG_P.bin", NULL);
	lv_imagebutton_set_src(bt_config_silence_pc, LV_IMAGEBUTTON_STATE_CHECKED_PRESSED, NULL, "S:/CONFIG/BT_CONFIG_P_P.bin", NULL);
	lv_imagebutton_set_src(bt_config_silence_pc, LV_IMAGEBUTTON_STATE_CHECKED_RELEASED, NULL, "S:/CONFIG/BT_CONFIG_P.bin", NULL);
	lv_imagebutton_set_src(bt_config_silence_pc, LV_IMAGEBUTTON_STATE_CHECKED_DISABLED, NULL, "S:/CONFIG/BT_CONFIG_P_SEL.bin", NULL);
	lv_obj_add_event_cb(bt_config_silence_pc, event_bt_silence_pc, LV_EVENT_ALL, NULL);
	lv_obj_set_pos(bt_config_silence_pc, 18, 254);
	lv_imagebutton_set_state(bt_config_silence_pc, LV_IMAGEBUTTON_STATE_CHECKED_DISABLED);

	// Text
    lv_obj_t * text_bt_silence_pc = lv_label_create(bt_config_silence_pc);
    lv_obj_set_width(text_bt_silence_pc, LV_SIZE_CONTENT);
    lv_obj_set_height(text_bt_silence_pc, LV_SIZE_CONTENT);
    lv_label_set_text(text_bt_silence_pc, "PC");
    lv_obj_set_style_text_color(text_bt_silence_pc, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(text_bt_silence_pc, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(text_bt_silence_pc, &Neue_Medium_14, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_align_to(text_bt_silence_pc, bt_config_silence_pc, LV_ALIGN_CENTER, 0, 0);
}


static void event_bt_silence_tuner(lv_event_t * e)
{
	lv_event_code_t code = lv_event_get_code(e);

	if(code == LV_EVENT_CLICKED) {
		lv_imagebutton_set_state(bt_config_silence_tuner,  LV_IMAGEBUTTON_STATE_CHECKED_DISABLED);
		lv_imagebutton_set_state(bt_config_silence_pc, LV_IMAGEBUTTON_STATE_RELEASED);
		lv_imagebutton_set_state(bt_config_silence_ble , LV_IMAGEBUTTON_STATE_RELEASED);
	}
}

void create_btn_silence_tuner(void)
{
	bt_config_silence_tuner = lv_imagebutton_create(Tela_Config_Silence);
	lv_imagebutton_set_src(bt_config_silence_tuner, LV_IMAGEBUTTON_STATE_RELEASED, NULL, "S:/CONFIG/BT_CONFIG_P.bin", NULL);
	lv_imagebutton_set_src(bt_config_silence_tuner, LV_IMAGEBUTTON_STATE_PRESSED, NULL, "S:/CONFIG/BT_CONFIG_P_P.bin", NULL);
	lv_imagebutton_set_src(bt_config_silence_tuner, LV_IMAGEBUTTON_STATE_DISABLED, NULL, "S:/CONFIG/BT_CONFIG_P.bin", NULL);
	lv_imagebutton_set_src(bt_config_silence_tuner, LV_IMAGEBUTTON_STATE_CHECKED_PRESSED, NULL, "S:/CONFIG/BT_CONFIG_P_P.bin", NULL);
	lv_imagebutton_set_src(bt_config_silence_tuner, LV_IMAGEBUTTON_STATE_CHECKED_RELEASED, NULL, "S:/CONFIG/BT_CONFIG_P.bin", NULL);
	lv_imagebutton_set_src(bt_config_silence_tuner, LV_IMAGEBUTTON_STATE_CHECKED_DISABLED, NULL, "S:/CONFIG/BT_CONFIG_P_SEL.bin", NULL);
	lv_obj_add_event_cb(bt_config_silence_tuner, event_bt_silence_tuner, LV_EVENT_ALL, NULL);
	lv_obj_set_pos(bt_config_silence_tuner, 172, 254);
	lv_imagebutton_set_state(bt_config_silence_tuner, LV_IMAGEBUTTON_STATE_RELEASED);

	// Text
    lv_obj_t * text_bt_silence_tuner = lv_label_create(bt_config_silence_tuner);
    lv_obj_set_width(text_bt_silence_tuner, LV_SIZE_CONTENT);
    lv_obj_set_height(text_bt_silence_tuner, LV_SIZE_CONTENT);
    lv_label_set_text(text_bt_silence_tuner, "TUNER");
    lv_obj_set_style_text_color(text_bt_silence_tuner, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(text_bt_silence_tuner, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(text_bt_silence_tuner, &Neue_Medium_14, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_align_to(text_bt_silence_tuner, bt_config_silence_tuner, LV_ALIGN_CENTER, 0, 0);
}

static void event_bt_silence_ble(lv_event_t * e)
{
	lv_event_code_t code = lv_event_get_code(e);

	if(code == LV_EVENT_CLICKED) {
		lv_imagebutton_set_state(bt_config_silence_ble,  LV_IMAGEBUTTON_STATE_CHECKED_DISABLED);
		lv_imagebutton_set_state(bt_config_silence_pc, LV_IMAGEBUTTON_STATE_RELEASED);
		lv_imagebutton_set_state(bt_config_silence_tuner , LV_IMAGEBUTTON_STATE_RELEASED);
	}
}

void create_btn_silence_ble(void)
{
	bt_config_silence_ble = lv_imagebutton_create(Tela_Config_Silence);
	lv_imagebutton_set_src(bt_config_silence_ble, LV_IMAGEBUTTON_STATE_RELEASED, NULL, "S:/CONFIG/BT_CONFIG_P.bin", NULL);
	lv_imagebutton_set_src(bt_config_silence_ble, LV_IMAGEBUTTON_STATE_PRESSED, NULL, "S:/CONFIG/BT_CONFIG_P_P.bin", NULL);
	lv_imagebutton_set_src(bt_config_silence_ble, LV_IMAGEBUTTON_STATE_DISABLED, NULL, "S:/CONFIG/BT_CONFIG_P.bin", NULL);
	lv_imagebutton_set_src(bt_config_silence_ble, LV_IMAGEBUTTON_STATE_CHECKED_PRESSED, NULL, "S:/CONFIG/BT_CONFIG_P_P.bin", NULL);
	lv_imagebutton_set_src(bt_config_silence_ble, LV_IMAGEBUTTON_STATE_CHECKED_RELEASED, NULL, "S:/CONFIG/BT_CONFIG_P.bin", NULL);
	lv_imagebutton_set_src(bt_config_silence_ble, LV_IMAGEBUTTON_STATE_CHECKED_DISABLED, NULL, "S:/CONFIG/BT_CONFIG_P_SEL.bin", NULL);
	lv_obj_add_event_cb(bt_config_silence_ble, event_bt_silence_ble, LV_EVENT_ALL, NULL);
	lv_obj_set_pos(bt_config_silence_ble, 326, 254);
	lv_imagebutton_set_state(bt_config_silence_tuner, LV_IMAGEBUTTON_STATE_RELEASED);

	// Text
    lv_obj_t * text_bt_silence_ble = lv_label_create(bt_config_silence_ble);
    lv_obj_set_width(text_bt_silence_ble, LV_SIZE_CONTENT);
    lv_obj_set_height(text_bt_silence_ble, LV_SIZE_CONTENT);
    lv_label_set_text(text_bt_silence_ble, "BLUETOOTH");
    lv_obj_set_style_text_color(text_bt_silence_ble, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(text_bt_silence_ble, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(text_bt_silence_ble, &Neue_Medium_14, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_align_to(text_bt_silence_ble, bt_config_silence_ble, LV_ALIGN_CENTER, 0, 0);
}


static void event_bt_silence_30s(lv_event_t * e)
{
	lv_event_code_t code = lv_event_get_code(e);

	if(code == LV_EVENT_CLICKED) {
		lv_imagebutton_set_state(bt_config_silence_30s,  LV_IMAGEBUTTON_STATE_CHECKED_DISABLED);
		lv_imagebutton_set_state(bt_config_silence_1min,  LV_IMAGEBUTTON_STATE_RELEASED);
		lv_imagebutton_set_state(bt_config_silence_2min,  LV_IMAGEBUTTON_STATE_RELEASED);
		lv_imagebutton_set_state(bt_config_silence_5min,  LV_IMAGEBUTTON_STATE_RELEASED);
		lv_imagebutton_set_state(bt_config_silence_10min,  LV_IMAGEBUTTON_STATE_RELEASED);
		lv_imagebutton_set_state(bt_config_silence_never,  LV_IMAGEBUTTON_STATE_RELEASED);
	}
}

void create_btn_silence_30s(void)
{
	bt_config_silence_30s = lv_imagebutton_create(Tela_Config_Silence);
	lv_imagebutton_set_src(bt_config_silence_30s, LV_IMAGEBUTTON_STATE_RELEASED, NULL, "S:/CONFIG/BT_CONFIG_P.bin", NULL);
	lv_imagebutton_set_src(bt_config_silence_30s, LV_IMAGEBUTTON_STATE_PRESSED, NULL, "S:/CONFIG/BT_CONFIG_P_P.bin", NULL);
	lv_imagebutton_set_src(bt_config_silence_30s, LV_IMAGEBUTTON_STATE_DISABLED, NULL, "S:/CONFIG/BT_CONFIG_P.bin", NULL);
	lv_imagebutton_set_src(bt_config_silence_30s, LV_IMAGEBUTTON_STATE_CHECKED_PRESSED, NULL, "S:/CONFIG/BT_CONFIG_P_P.bin", NULL);
	lv_imagebutton_set_src(bt_config_silence_30s, LV_IMAGEBUTTON_STATE_CHECKED_RELEASED, NULL, "S:/CONFIG/BT_CONFIG_P.bin", NULL);
	lv_imagebutton_set_src(bt_config_silence_30s, LV_IMAGEBUTTON_STATE_CHECKED_DISABLED, NULL, "S:/CONFIG/BT_CONFIG_P_SEL.bin", NULL);
	lv_obj_add_event_cb(bt_config_silence_30s, event_bt_silence_30s, LV_EVENT_ALL, NULL);
	lv_obj_set_pos(bt_config_silence_30s, 18, 97);
	lv_imagebutton_set_state(bt_config_silence_30s, LV_IMAGEBUTTON_STATE_RELEASED);

	// Text
    lv_obj_t * text_bt_silence_30s = lv_label_create(bt_config_silence_30s);
    lv_obj_set_width(text_bt_silence_30s, LV_SIZE_CONTENT);
    lv_obj_set_height(text_bt_silence_30s, LV_SIZE_CONTENT);
    lv_label_set_text(text_bt_silence_30s, "30 Seconds");
    lv_obj_set_style_text_color(text_bt_silence_30s, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(text_bt_silence_30s, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(text_bt_silence_30s, &Neue_Medium_14, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_align_to(text_bt_silence_30s, bt_config_silence_30s, LV_ALIGN_CENTER, 0, 0);
}

static void event_bt_silence_1min(lv_event_t * e)
{
	lv_event_code_t code = lv_event_get_code(e);

	if(code == LV_EVENT_CLICKED) {
		lv_imagebutton_set_state(bt_config_silence_30s,  LV_IMAGEBUTTON_STATE_RELEASED);
		lv_imagebutton_set_state(bt_config_silence_1min,  LV_IMAGEBUTTON_STATE_CHECKED_DISABLED);
		lv_imagebutton_set_state(bt_config_silence_2min,  LV_IMAGEBUTTON_STATE_RELEASED);
		lv_imagebutton_set_state(bt_config_silence_5min,  LV_IMAGEBUTTON_STATE_RELEASED);
		lv_imagebutton_set_state(bt_config_silence_10min,  LV_IMAGEBUTTON_STATE_RELEASED);
		lv_imagebutton_set_state(bt_config_silence_never,  LV_IMAGEBUTTON_STATE_RELEASED);
	}
}

void create_btn_silence_1min(void)
{
	bt_config_silence_1min = lv_imagebutton_create(Tela_Config_Silence);
	lv_imagebutton_set_src(bt_config_silence_1min, LV_IMAGEBUTTON_STATE_RELEASED, NULL, "S:/CONFIG/BT_CONFIG_P.bin", NULL);
	lv_imagebutton_set_src(bt_config_silence_1min, LV_IMAGEBUTTON_STATE_PRESSED, NULL, "S:/CONFIG/BT_CONFIG_P_P.bin", NULL);
	lv_imagebutton_set_src(bt_config_silence_1min, LV_IMAGEBUTTON_STATE_DISABLED, NULL, "S:/CONFIG/BT_CONFIG_P.bin", NULL);
	lv_imagebutton_set_src(bt_config_silence_1min, LV_IMAGEBUTTON_STATE_CHECKED_PRESSED, NULL, "S:/CONFIG/BT_CONFIG_P_P.bin", NULL);
	lv_imagebutton_set_src(bt_config_silence_1min, LV_IMAGEBUTTON_STATE_CHECKED_RELEASED, NULL, "S:/CONFIG/BT_CONFIG_P.bin", NULL);
	lv_imagebutton_set_src(bt_config_silence_1min, LV_IMAGEBUTTON_STATE_CHECKED_DISABLED, NULL, "S:/CONFIG/BT_CONFIG_P_SEL.bin", NULL);
	lv_obj_add_event_cb(bt_config_silence_1min, event_bt_silence_1min, LV_EVENT_ALL, NULL);
	lv_obj_set_pos(bt_config_silence_1min, 172, 97);
	lv_imagebutton_set_state(bt_config_silence_1min, LV_IMAGEBUTTON_STATE_RELEASED);

	// Text
    lv_obj_t * text_bt_silence_1min = lv_label_create(bt_config_silence_1min);
    lv_obj_set_width(text_bt_silence_1min, LV_SIZE_CONTENT);
    lv_obj_set_height(text_bt_silence_1min, LV_SIZE_CONTENT);
    lv_label_set_text(text_bt_silence_1min, "1 Minute");
    lv_obj_set_style_text_color(text_bt_silence_1min, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(text_bt_silence_1min, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(text_bt_silence_1min, &Neue_Medium_14, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_align_to(text_bt_silence_1min, bt_config_silence_1min, LV_ALIGN_CENTER, 0, 0);
}

static void event_bt_silence_2min(lv_event_t * e)
{
	lv_event_code_t code = lv_event_get_code(e);

	if(code == LV_EVENT_CLICKED) {
		lv_imagebutton_set_state(bt_config_silence_30s,  LV_IMAGEBUTTON_STATE_RELEASED);
		lv_imagebutton_set_state(bt_config_silence_1min,  LV_IMAGEBUTTON_STATE_RELEASED);
		lv_imagebutton_set_state(bt_config_silence_2min,  LV_IMAGEBUTTON_STATE_CHECKED_DISABLED);
		lv_imagebutton_set_state(bt_config_silence_5min,  LV_IMAGEBUTTON_STATE_RELEASED);
		lv_imagebutton_set_state(bt_config_silence_10min,  LV_IMAGEBUTTON_STATE_RELEASED);
		lv_imagebutton_set_state(bt_config_silence_never,  LV_IMAGEBUTTON_STATE_RELEASED);
	}
}

void create_btn_silence_2min(void)
{
	bt_config_silence_2min = lv_imagebutton_create(Tela_Config_Silence);
	lv_imagebutton_set_src(bt_config_silence_2min, LV_IMAGEBUTTON_STATE_RELEASED, NULL, "S:/CONFIG/BT_CONFIG_P.bin", NULL);
	lv_imagebutton_set_src(bt_config_silence_2min, LV_IMAGEBUTTON_STATE_PRESSED, NULL, "S:/CONFIG/BT_CONFIG_P_P.bin", NULL);
	lv_imagebutton_set_src(bt_config_silence_2min, LV_IMAGEBUTTON_STATE_DISABLED, NULL, "S:/CONFIG/BT_CONFIG_P.bin", NULL);
	lv_imagebutton_set_src(bt_config_silence_2min, LV_IMAGEBUTTON_STATE_CHECKED_PRESSED, NULL, "S:/CONFIG/BT_CONFIG_P_P.bin", NULL);
	lv_imagebutton_set_src(bt_config_silence_2min, LV_IMAGEBUTTON_STATE_CHECKED_RELEASED, NULL, "S:/CONFIG/BT_CONFIG_P.bin", NULL);
	lv_imagebutton_set_src(bt_config_silence_2min, LV_IMAGEBUTTON_STATE_CHECKED_DISABLED, NULL, "S:/CONFIG/BT_CONFIG_P_SEL.bin", NULL);
	lv_obj_add_event_cb(bt_config_silence_2min, event_bt_silence_2min, LV_EVENT_ALL, NULL);
	lv_obj_set_pos(bt_config_silence_2min, 326, 97);
	lv_imagebutton_set_state(bt_config_silence_2min, LV_IMAGEBUTTON_STATE_RELEASED);

	// Text
    lv_obj_t * text_bt_silence_2min = lv_label_create(bt_config_silence_2min);
    lv_obj_set_width(text_bt_silence_2min, LV_SIZE_CONTENT);
    lv_obj_set_height(text_bt_silence_2min, LV_SIZE_CONTENT);
    lv_label_set_text(text_bt_silence_2min, "2 Minutes");
    lv_obj_set_style_text_color(text_bt_silence_2min, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(text_bt_silence_2min, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(text_bt_silence_2min, &Neue_Medium_14, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_align_to(text_bt_silence_2min, bt_config_silence_2min, LV_ALIGN_CENTER, 0, 0);
}

static void event_bt_silence_5min(lv_event_t * e)
{
	lv_event_code_t code = lv_event_get_code(e);

	if(code == LV_EVENT_CLICKED) {
		lv_imagebutton_set_state(bt_config_silence_30s,  LV_IMAGEBUTTON_STATE_RELEASED);
		lv_imagebutton_set_state(bt_config_silence_1min,  LV_IMAGEBUTTON_STATE_RELEASED);
		lv_imagebutton_set_state(bt_config_silence_2min,  LV_IMAGEBUTTON_STATE_RELEASED);
		lv_imagebutton_set_state(bt_config_silence_5min,  LV_IMAGEBUTTON_STATE_CHECKED_DISABLED);
		lv_imagebutton_set_state(bt_config_silence_10min,  LV_IMAGEBUTTON_STATE_RELEASED);
		lv_imagebutton_set_state(bt_config_silence_never,  LV_IMAGEBUTTON_STATE_RELEASED);
	}
}

void create_btn_silence_5min(void)
{
	bt_config_silence_5min = lv_imagebutton_create(Tela_Config_Silence);
	lv_imagebutton_set_src(bt_config_silence_5min, LV_IMAGEBUTTON_STATE_RELEASED, NULL, "S:/CONFIG/BT_CONFIG_P.bin", NULL);
	lv_imagebutton_set_src(bt_config_silence_5min, LV_IMAGEBUTTON_STATE_PRESSED, NULL, "S:/CONFIG/BT_CONFIG_P_P.bin", NULL);
	lv_imagebutton_set_src(bt_config_silence_5min, LV_IMAGEBUTTON_STATE_DISABLED, NULL, "S:/CONFIG/BT_CONFIG_P.bin", NULL);
	lv_imagebutton_set_src(bt_config_silence_5min, LV_IMAGEBUTTON_STATE_CHECKED_PRESSED, NULL, "S:/CONFIG/BT_CONFIG_P_P.bin", NULL);
	lv_imagebutton_set_src(bt_config_silence_5min, LV_IMAGEBUTTON_STATE_CHECKED_RELEASED, NULL, "S:/CONFIG/BT_CONFIG_P.bin", NULL);
	lv_imagebutton_set_src(bt_config_silence_5min, LV_IMAGEBUTTON_STATE_CHECKED_DISABLED, NULL, "S:/CONFIG/BT_CONFIG_P_SEL.bin", NULL);
	lv_obj_add_event_cb(bt_config_silence_5min, event_bt_silence_5min, LV_EVENT_ALL, NULL);
	lv_obj_set_pos(bt_config_silence_5min, 18, 147);
	lv_imagebutton_set_state(bt_config_silence_5min, LV_IMAGEBUTTON_STATE_RELEASED);

	// Text
    lv_obj_t * text_bt_silence_5min = lv_label_create(bt_config_silence_5min);
    lv_obj_set_width(text_bt_silence_5min, LV_SIZE_CONTENT);
    lv_obj_set_height(text_bt_silence_5min, LV_SIZE_CONTENT);
    lv_label_set_text(text_bt_silence_5min, "5 Minutes");
    lv_obj_set_style_text_color(text_bt_silence_5min, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(text_bt_silence_5min, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(text_bt_silence_5min, &Neue_Medium_14, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_align_to(text_bt_silence_5min, bt_config_silence_5min, LV_ALIGN_CENTER, 0, 0);
}

static void event_bt_silence_10min(lv_event_t * e)
{
	lv_event_code_t code = lv_event_get_code(e);

	if(code == LV_EVENT_CLICKED) {
		lv_imagebutton_set_state(bt_config_silence_30s,  LV_IMAGEBUTTON_STATE_RELEASED);
		lv_imagebutton_set_state(bt_config_silence_1min,  LV_IMAGEBUTTON_STATE_RELEASED);
		lv_imagebutton_set_state(bt_config_silence_2min,  LV_IMAGEBUTTON_STATE_RELEASED);
		lv_imagebutton_set_state(bt_config_silence_5min,  LV_IMAGEBUTTON_STATE_RELEASED);
		lv_imagebutton_set_state(bt_config_silence_10min,  LV_IMAGEBUTTON_STATE_CHECKED_DISABLED);
		lv_imagebutton_set_state(bt_config_silence_never,  LV_IMAGEBUTTON_STATE_RELEASED);
	}
}

void create_btn_silence_10min(void)
{
	bt_config_silence_10min = lv_imagebutton_create(Tela_Config_Silence);
	lv_imagebutton_set_src(bt_config_silence_10min, LV_IMAGEBUTTON_STATE_RELEASED, NULL, "S:/CONFIG/BT_CONFIG_P.bin", NULL);
	lv_imagebutton_set_src(bt_config_silence_10min, LV_IMAGEBUTTON_STATE_PRESSED, NULL, "S:/CONFIG/BT_CONFIG_P_P.bin", NULL);
	lv_imagebutton_set_src(bt_config_silence_10min, LV_IMAGEBUTTON_STATE_DISABLED, NULL, "S:/CONFIG/BT_CONFIG_P.bin", NULL);
	lv_imagebutton_set_src(bt_config_silence_10min, LV_IMAGEBUTTON_STATE_CHECKED_PRESSED, NULL, "S:/CONFIG/BT_CONFIG_P_P.bin", NULL);
	lv_imagebutton_set_src(bt_config_silence_10min, LV_IMAGEBUTTON_STATE_CHECKED_RELEASED, NULL, "S:/CONFIG/BT_CONFIG_P.bin", NULL);
	lv_imagebutton_set_src(bt_config_silence_10min, LV_IMAGEBUTTON_STATE_CHECKED_DISABLED, NULL, "S:/CONFIG/BT_CONFIG_P_SEL.bin", NULL);
	lv_obj_add_event_cb(bt_config_silence_10min, event_bt_silence_10min, LV_EVENT_ALL, NULL);
	lv_obj_set_pos(bt_config_silence_10min, 172, 147);
	lv_imagebutton_set_state(bt_config_silence_10min, LV_IMAGEBUTTON_STATE_RELEASED);

	// Text
    lv_obj_t * text_bt_silence_10min = lv_label_create(bt_config_silence_10min);
    lv_obj_set_width(text_bt_silence_10min, LV_SIZE_CONTENT);
    lv_obj_set_height(text_bt_silence_10min, LV_SIZE_CONTENT);
    lv_label_set_text(text_bt_silence_10min, "10 Minutes");
    lv_obj_set_style_text_color(text_bt_silence_10min, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(text_bt_silence_10min, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(text_bt_silence_10min, &Neue_Medium_14, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_align_to(text_bt_silence_10min, bt_config_silence_10min, LV_ALIGN_CENTER, 0, 0);
}

static void event_bt_silence_never(lv_event_t * e)
{
	lv_event_code_t code = lv_event_get_code(e);

	if(code == LV_EVENT_CLICKED) {
		lv_imagebutton_set_state(bt_config_silence_30s,  LV_IMAGEBUTTON_STATE_RELEASED);
		lv_imagebutton_set_state(bt_config_silence_1min,  LV_IMAGEBUTTON_STATE_RELEASED);
		lv_imagebutton_set_state(bt_config_silence_2min,  LV_IMAGEBUTTON_STATE_RELEASED);
		lv_imagebutton_set_state(bt_config_silence_5min,  LV_IMAGEBUTTON_STATE_RELEASED);
		lv_imagebutton_set_state(bt_config_silence_10min,  LV_IMAGEBUTTON_STATE_RELEASED);
		lv_imagebutton_set_state(bt_config_silence_never,  LV_IMAGEBUTTON_STATE_CHECKED_DISABLED);
	}
}

void create_btn_silence_never(void)
{
	bt_config_silence_never = lv_imagebutton_create(Tela_Config_Silence);
	lv_imagebutton_set_src(bt_config_silence_never, LV_IMAGEBUTTON_STATE_RELEASED, NULL, "S:/CONFIG/BT_CONFIG_P.bin", NULL);
	lv_imagebutton_set_src(bt_config_silence_never, LV_IMAGEBUTTON_STATE_PRESSED, NULL, "S:/CONFIG/BT_CONFIG_P_P.bin", NULL);
	lv_imagebutton_set_src(bt_config_silence_never, LV_IMAGEBUTTON_STATE_DISABLED, NULL, "S:/CONFIG/BT_CONFIG_P.bin", NULL);
	lv_imagebutton_set_src(bt_config_silence_never, LV_IMAGEBUTTON_STATE_CHECKED_PRESSED, NULL, "S:/CONFIG/BT_CONFIG_P_P.bin", NULL);
	lv_imagebutton_set_src(bt_config_silence_never, LV_IMAGEBUTTON_STATE_CHECKED_RELEASED, NULL, "S:/CONFIG/BT_CONFIG_P.bin", NULL);
	lv_imagebutton_set_src(bt_config_silence_never, LV_IMAGEBUTTON_STATE_CHECKED_DISABLED, NULL, "S:/CONFIG/BT_CONFIG_P_SEL.bin", NULL);
	lv_obj_add_event_cb(bt_config_silence_never, event_bt_silence_never, LV_EVENT_ALL, NULL);
	lv_obj_set_pos(bt_config_silence_never, 326, 147);
	lv_imagebutton_set_state(bt_config_silence_never, LV_IMAGEBUTTON_STATE_CHECKED_DISABLED);

	// Text
    lv_obj_t * text_bt_silence_never = lv_label_create(bt_config_silence_never);
    lv_obj_set_width(text_bt_silence_never, LV_SIZE_CONTENT);
    lv_obj_set_height(text_bt_silence_never, LV_SIZE_CONTENT);
    lv_label_set_text(text_bt_silence_never, "NEVER");
    lv_obj_set_style_text_color(text_bt_silence_never, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(text_bt_silence_never, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(text_bt_silence_never, &Neue_Medium_14, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_align_to(text_bt_silence_never, bt_config_silence_never, LV_ALIGN_CENTER, 0, 0);
}
