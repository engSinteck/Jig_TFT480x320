/*
 * Screen_Config_Audio_Input.c
 *
 *  Created on: 29 de ago. de 2026
 *      Author: rdsan
 */

#include "stdbool.h"
#include "rng.h"
#include "stdio.h"
#include "string.h"

#include "../App/UI/Screen_Config_Audio_Input.h"
#include "../App/UI/Screen_Utils.h"

LV_FONT_DECLARE(Neue_Medium_12);
LV_FONT_DECLARE(Neue_Medium_14);

void create_config_audio_in_label(void);
void create_config_audio_in_label_2(void);

lv_obj_t * Tela_Config_Audio_Input = NULL;
static lv_obj_t * text_config_Audio_In_top = NULL;

void Screen_Config_Audio_Input_Create(void)
{
	Tela_Config_Audio_Input = lv_obj_create(NULL);
	lv_obj_clear_flag(Tela_Config_Audio_Input, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLLABLE);
	lv_obj_set_style_bg_color(Tela_Config_Audio_Input, lv_color_hex(0x000000), 0);
	lv_obj_set_style_bg_grad_color(Tela_Config_Audio_Input, lv_color_hex(0x000000), 0);

	// Label Screen
	create_config_audio_in_label();
	create_config_audio_in_label_2();

	create_button_back_main(Tela_Config_Audio_Input, 380, 8, PAGE_CONFIG);
}

void create_config_audio_in_label(void)
{
	text_config_Audio_In_top = lv_label_create(Tela_Config_Audio_Input);
    lv_obj_set_width(text_config_Audio_In_top, LV_SIZE_CONTENT);
    lv_obj_set_height(text_config_Audio_In_top, LV_SIZE_CONTENT);
    lv_label_set_text(text_config_Audio_In_top, "GENERAL CONFIGURATIONS/AUDIO INPUT TYPE:");
    lv_obj_set_style_text_color(text_config_Audio_In_top, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(text_config_Audio_In_top, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(text_config_Audio_In_top, &Neue_Medium_14, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(text_config_Audio_In_top, 7, 16);
}

void create_config_audio_in_label_2(void)
{
	// Criar o label pai na tela atual
	lv_obj_t * label_main = lv_label_create(Tela_Config_Audio_Input);

	// Font
	lv_obj_set_style_text_color(label_main, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_opa(label_main, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(label_main, &Neue_Medium_14, LV_PART_MAIN | LV_STATE_DEFAULT);

	// Definir o texto
	lv_label_set_text(label_main,
	    "This AUDIO INTERFACE supports both analog and\n"
	    "AES/EBU digital audio inputs. Since the input type is not detected\n"
	    "automatically, you must manually select the correct input mode.\n"
	    "If the selected mode does not match the connected audio source,\n"
	    "the audio will not be processed correctly and the interface may\n"
	    "remain muted. Optical output port operate independently of this\n"
	    "setting and remain available regardless of the selected input\n"
	    "mode.");

	// Definir largura fixa para forçar a quebra de linha (word wrap)
	lv_obj_set_width(label_main, 440); // Ajuste conforme a resolução da tela
	lv_label_set_long_mode(label_main, LV_LABEL_LONG_WRAP);

	// Centralizar o alinhamento das linhas de texto e a posição no container
	lv_obj_set_style_text_align(label_main, LV_TEXT_ALIGN_CENTER, 0);
	lv_obj_align(label_main, LV_ALIGN_CENTER, 0, -20);
}
