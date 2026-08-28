/*
 * Screen_Menu_TUNER.c
 *
 *  Created on: 28 de ago. de 2026
 *      Author: rinaldo.santos
 */

#include "stdbool.h"
#include "rng.h"
#include "stdio.h"
#include "string.h"

#include "../App/UI/Screen_Menu_TUNER.h"
#include "../App/UI/Screen_Utils.h"

lv_obj_t * Tela_Menu_TUNER = NULL;
static lv_obj_t * img_fundo_menu_tuner = NULL;

void Screen_Menu_TUNER_Create(void)
{
	Tela_Menu_TUNER = lv_obj_create(NULL);
	lv_obj_clear_flag(Tela_Menu_TUNER, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLLABLE);
	lv_obj_set_style_bg_color(Tela_Menu_TUNER, lv_color_hex(0x000000), 0);
	lv_obj_set_style_bg_grad_color(Tela_Menu_TUNER, lv_color_hex(0x000000), 0);

	// Imagem de Fundo
	img_fundo_menu_tuner = lv_img_create(Tela_Menu_TUNER);
	lv_img_set_src(img_fundo_menu_tuner, "S:/CONFIG/TELA_FUNDO.bin");
	lv_obj_set_pos(img_fundo_menu_tuner, 0, 0);

	create_button_back_main(Tela_Menu_TUNER, 380, 265);
}
