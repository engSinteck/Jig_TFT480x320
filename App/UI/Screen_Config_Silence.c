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

void create_config_silence_label(void);
void create_config_silence_label_2(void);

lv_obj_t * Tela_Config_Silence = NULL;
static lv_obj_t * text_config_silence_top = NULL;

void Screen_Config_Silence_Create(void)
{
	Tela_Config_Silence = lv_obj_create(NULL);
	lv_obj_clear_flag(Tela_Config_Silence, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLLABLE);
	lv_obj_set_style_bg_color(Tela_Config_Silence, lv_color_hex(0x000000), 0);
	lv_obj_set_style_bg_grad_color(Tela_Config_Silence, lv_color_hex(0x000000), 0);

	// Label Screen
	create_config_silence_label();
	create_config_silence_label_2();

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
	    "Set the delay before the audio interface automatically\n"
	    "switches to the USB audio input when no audio is detected on the\n"
	    "selected primary input.");

	// Definir largura fixa para forçar a quebra de linha (word wrap)
	lv_obj_set_width(label_main, 440); // Ajuste conforme a resolução da tela
	lv_label_set_long_mode(label_main, LV_LABEL_LONG_WRAP);

	// Centralizar o alinhamento das linhas de texto e a posição no container
	lv_obj_set_style_text_align(label_main, LV_TEXT_ALIGN_CENTER, 0);
	lv_obj_align(label_main, LV_ALIGN_CENTER, 0, -20);

	// Criar o label pai na tela atual
	lv_obj_t * label_main_b = lv_label_create(Tela_Config_Silence);

	// Font
	lv_obj_set_style_text_color(label_main_b, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_opa(label_main_b, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(label_main_b, &Neue_Medium_14, LV_PART_MAIN | LV_STATE_DEFAULT);

	// Definir o texto
	// Texto do bloco superior
	lv_label_set_text(label_main_b,
	    "If no audio is available from the USB drive, or if no USB\n"
	    "drive is connected, select the backup audio source to be used by\n"
	    "the Silence Detector:");

	// Definir largura fixa para forçar a quebra de linha (word wrap)
	lv_obj_set_width(label_main_b, 440); // Ajuste conforme a resolução da tela
	lv_label_set_long_mode(label_main_b, LV_LABEL_LONG_WRAP);

	// Centralizar o alinhamento das linhas de texto e a posição no container
	lv_obj_set_style_text_align(label_main_b, LV_TEXT_ALIGN_CENTER, 0);
	lv_obj_align(label_main_b, LV_ALIGN_CENTER, 20, -20);
}
