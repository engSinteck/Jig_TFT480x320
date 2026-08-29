/*
 * Screen_Config_About.c
 *
 *  Created on: 29 de ago. de 2026
 *      Author: rdsan
 */

#include "stdbool.h"
#include "rng.h"
#include "stdio.h"
#include "string.h"

#include "../App/UI/Screen_Config_About.h"
#include "../App/UI/Screen_Utils.h"

LV_FONT_DECLARE(Neue_Medium_14);

void create_config_about_label(void);

lv_obj_t * Tela_Config_About = NULL;
static lv_obj_t * text_config_about_top = NULL;

void Screen_Config_About_Create(void)
{
	Tela_Config_About = lv_obj_create(NULL);
	lv_obj_clear_flag(Tela_Config_About, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLLABLE);
	lv_obj_set_style_bg_color(Tela_Config_About, lv_color_hex(0x000000), 0);
	lv_obj_set_style_bg_grad_color(Tela_Config_About, lv_color_hex(0x000000), 0);

	// Label Screen
	create_config_about_label();

	create_button_back_main(Tela_Config_About, 380, 8, PAGE_CONFIG);
}

void create_config_about_label(void)
{
	text_config_about_top = lv_label_create(Tela_Config_About);
    lv_obj_set_width(text_config_about_top, LV_SIZE_CONTENT);
    lv_obj_set_height(text_config_about_top, LV_SIZE_CONTENT);
    lv_label_set_text(text_config_about_top, "GENERAL CONFIGURATIONS/ABOUT THIS PRODUCT:");
    lv_obj_set_style_text_color(text_config_about_top, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(text_config_about_top, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(text_config_about_top, &Neue_Medium_14, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(text_config_about_top, 7, 16);
}
