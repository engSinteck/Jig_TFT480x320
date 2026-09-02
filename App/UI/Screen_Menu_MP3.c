/*
 * Screen_Menu_MP3.c
 *
 *  Created on: 28 de ago. de 2026
 *      Author: rinaldo.santos
 */

#include "stdbool.h"
#include "rng.h"
#include "stdio.h"
#include "string.h"

#include "../App/UI/Screen_Menu_MP3.h"
#include "../App/UI/Screen_Utils.h"

lv_obj_t * Tela_Menu_MP3 = NULL;
static lv_obj_t * img_fundo_menu_mp3 = NULL;

void Screen_Menu_MP3_Create(void)
{
	Tela_Menu_MP3 = lv_obj_create(NULL);
	lv_obj_clear_flag(Tela_Menu_MP3, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLLABLE);
	lv_obj_set_style_bg_color(Tela_Menu_MP3, lv_color_hex(0x000000), 0);
	lv_obj_set_style_bg_grad_color(Tela_Menu_MP3, lv_color_hex(0x000000), 0);

	// Imagem de Fundo
	img_fundo_menu_mp3 = lv_img_create(Tela_Menu_MP3);
	lv_img_set_src(img_fundo_menu_mp3, "S:/USB/TELA_USB.bin");
	lv_obj_set_pos(img_fundo_menu_mp3, 0, 0);

	create_button_back_main(Tela_Menu_MP3, 380, 265, PAGE_MAIN);
}

