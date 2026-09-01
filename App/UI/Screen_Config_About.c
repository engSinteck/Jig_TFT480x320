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

lv_obj_t * Tela_Config_About = NULL;
lv_obj_t * Tela_Config_About_1 = NULL;

static lv_obj_t * img_fundo_about = NULL;
static lv_obj_t * img_fundo_about_1 = NULL;

void Screen_Config_About_Create(void)
{
	Tela_Config_About = lv_obj_create(NULL);
	lv_obj_clear_flag(Tela_Config_About, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLLABLE);
	lv_obj_set_style_bg_color(Tela_Config_About, lv_color_hex(0x000000), 0);
	lv_obj_set_style_bg_grad_color(Tela_Config_About, lv_color_hex(0x000000), 0);

	// Imagem de Fundo
	img_fundo_about = lv_img_create(Tela_Config_About);
	lv_img_set_src(img_fundo_about, "S:/ABOUT/TELA_ABOUT.bin");
	lv_obj_set_pos(img_fundo_about, 0, 0);

	create_button_back_main(Tela_Config_About, 285, 4, PAGE_CONFIG);
	create_button_next_main(Tela_Config_About, 384, 4, PAGE_ABOUT);
}

void Screen_Config_About_1_Create(void)
{
	Tela_Config_About_1 = lv_obj_create(NULL);
	lv_obj_clear_flag(Tela_Config_About_1, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLLABLE);
	lv_obj_set_style_bg_color(Tela_Config_About_1, lv_color_hex(0x000000), 0);
	lv_obj_set_style_bg_grad_color(Tela_Config_About_1, lv_color_hex(0x000000), 0);

	// Imagem de Fundo
	img_fundo_about_1 = lv_img_create(Tela_Config_About_1);
	lv_img_set_src(img_fundo_about_1, "S:/ABOUT/TELA_ABOUT_1.bin");
	lv_obj_set_pos(img_fundo_about_1, 0, 0);

	create_button_back_main(Tela_Config_About_1, 285, 4, PAGE_CONFIG);
}
