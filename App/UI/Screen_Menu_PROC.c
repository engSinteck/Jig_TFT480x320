/*
 * Screen_Menu_PROC.c
 *
 *  Created on: 28 de ago. de 2026
 *      Author: rinaldo.santos
 */

#include "stdbool.h"
#include "rng.h"
#include "stdio.h"
#include "string.h"

#include "../App/UI/Screen_Menu_PROC.h"
#include "../App/UI/Screen_Utils.h"

lv_obj_t * Tela_Menu_PROC = NULL;
static lv_obj_t * img_fundo_menu_proc = NULL;

void Screen_Menu_PROC_Create(void)
{
	Tela_Menu_PROC = lv_obj_create(NULL);
	lv_obj_clear_flag(Tela_Menu_PROC, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLLABLE);
	lv_obj_set_style_bg_color(Tela_Menu_PROC, lv_color_hex(0x000000), 0);
	lv_obj_set_style_bg_grad_color(Tela_Menu_PROC, lv_color_hex(0x000000), 0);

	// Imagem de Fundo
	img_fundo_menu_proc = lv_img_create(Tela_Menu_PROC);
	lv_img_set_src(img_fundo_menu_proc, "S:/CONFIG/TELA_FUNDO.bin");
	lv_obj_set_pos(img_fundo_menu_proc, 0, 0);

	create_button_back_main(Tela_Menu_PROC, 380, 265);
}
