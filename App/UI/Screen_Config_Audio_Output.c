/*
 * Screen_Config_Audio_Output.c
 *
 *  Created on: 29 de ago. de 2026
 *      Author: rdsan
 */


#include "stdbool.h"
#include "rng.h"
#include "stdio.h"
#include "string.h"

#include "../App/UI/Screen_Config_Audio_Output.h"
#include "../App/UI/Screen_Utils.h"

LV_FONT_DECLARE(Neue_Medium_14);

void create_config_audio_out_label(void);
void create_config_audio_out_label_2(void);

lv_obj_t * Tela_Config_Audio_Output = NULL;
static lv_obj_t * text_config_Audio_Out_top = NULL;

void Screen_Config_Audio_Output_Create(void)
{
	Tela_Config_Audio_Output = lv_obj_create(NULL);
	lv_obj_clear_flag(Tela_Config_Audio_Output, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLLABLE);
	lv_obj_set_style_bg_color(Tela_Config_Audio_Output, lv_color_hex(0x000000), 0);
	lv_obj_set_style_bg_grad_color(Tela_Config_Audio_Output, lv_color_hex(0x000000), 0);

	// Label Screen
	create_config_audio_out_label();
	create_config_audio_out_label_2();

	create_button_back_main(Tela_Config_Audio_Output, 380, 8, PAGE_CONFIG);
}

void create_config_audio_out_label(void)
{
	text_config_Audio_Out_top = lv_label_create(Tela_Config_Audio_Output);
    lv_obj_set_width(text_config_Audio_Out_top, LV_SIZE_CONTENT);
    lv_obj_set_height(text_config_Audio_Out_top, LV_SIZE_CONTENT);
    lv_label_set_text(text_config_Audio_Out_top, "GENERAL CONFIGURATIONS/XLR OUTPUT TYPE:");
    lv_obj_set_style_text_color(text_config_Audio_Out_top, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(text_config_Audio_Out_top, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(text_config_Audio_Out_top, &Neue_Medium_14, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(text_config_Audio_Out_top, 7, 16);
}

void create_config_audio_out_label_2(void)
{
	// Criar o label pai na tela atual
	lv_obj_t * label_main = lv_label_create(Tela_Config_Audio_Output);

	// Font
	lv_obj_set_style_text_color(label_main, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_opa(label_main, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(label_main, &Neue_Medium_14, LV_PART_MAIN | LV_STATE_DEFAULT);

	// Definir o texto
	lv_label_set_text(label_main,
	    "Select the desired audio output format. The audio\n"
	    "interface supports both analog XLR outputs and AES192 digital\n"
	    "output. Choose the output type that matches the connected\n"
	    "equipment to ensure proper operation and optimum audio\n"
	    "quality. Optical output port operate independently of this setting\n"
	    "and remain available regardless of the selected input mode.");

	// Definir largura fixa para forçar a quebra de linha (word wrap)
	lv_obj_set_width(label_main, 440); // Ajuste conforme a resolução da tela
	lv_label_set_long_mode(label_main, LV_LABEL_LONG_WRAP);

	// Centralizar o alinhamento das linhas de texto e a posição no container
	lv_obj_set_style_text_align(label_main, LV_TEXT_ALIGN_CENTER, 0);
	lv_obj_align(label_main, LV_ALIGN_CENTER, 0, -20);
}

