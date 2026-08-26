/*
 * Screen_Inputs.c
 *
 *  Created on: 26 de ago. de 2026
 *      Author: rinaldo.santos
 */

#include "stdbool.h"
#include "rng.h"
#include "stdio.h"
#include "string.h"

#include "../App/UI/Screen_Inputs.h"
#include "../App/UI/Screen_Main.h"

LV_FONT_DECLARE(Neue_Medium_14);
LV_FONT_DECLARE(Neue_Medium_16);

extern lv_obj_t * Tela_Main;

void create_button_back_main(void);

lv_obj_t * Tela_Inputs = NULL;
static lv_obj_t * img_fundo_inputs = NULL;
static lv_obj_t * bt_backmain = NULL;

void Screen_Inputs_Create(void)
{
	Tela_Inputs = lv_obj_create(NULL);
	lv_obj_clear_flag(Tela_Inputs, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLLABLE);
	lv_obj_set_style_bg_color(Tela_Inputs, lv_color_hex(0x000000), 0);
	lv_obj_set_style_bg_grad_color(Tela_Inputs, lv_color_hex(0x000000), 0);

	// Imagem de Fundo
	img_fundo_inputs = lv_img_create(Tela_Inputs);
	lv_img_set_src(img_fundo_inputs, "S:/Inputs/TELA_FUNDO.bin");
	lv_obj_set_pos(img_fundo_inputs, 0, 0);

	create_button_back_main();
}

static void event_menu_back(lv_event_t * e)
{
	lv_event_code_t code = lv_event_get_code(e);

	if(code == LV_EVENT_CLICKED) {
		// Cria a próxima tela antes de carregar
		Screen_Create_Main();

		// auto_del = true vai deletar a Tela_Main automaticamente ao fim da animação
		lv_screen_load_anim(Tela_Main, LV_SCREEN_LOAD_ANIM_FADE_ON, 500, 10, true);
	 }
}

void create_button_back_main(void)
{
    // Button BACK/MAIN
    bt_backmain = lv_imagebutton_create(Tela_Inputs);
    lv_imagebutton_set_src(bt_backmain, LV_IMAGEBUTTON_STATE_RELEASED, NULL, "S:/Inputs/BT_BACK.bin", NULL);
    lv_imagebutton_set_src(bt_backmain, LV_IMAGEBUTTON_STATE_PRESSED, NULL, "S:/Inputs/BT_BACK_P.bin", NULL);
    lv_imagebutton_set_src(bt_backmain, LV_IMAGEBUTTON_STATE_DISABLED, NULL, "S:/Inputs/BT_BACK.bin", NULL);
    lv_imagebutton_set_src(bt_backmain, LV_IMAGEBUTTON_STATE_CHECKED_PRESSED, NULL, "S:/Inputs/BT_BACK_P.bin", NULL);
    lv_imagebutton_set_src(bt_backmain, LV_IMAGEBUTTON_STATE_CHECKED_RELEASED, NULL, "S:/Inputs/BT_BACK.bin", NULL);
    lv_imagebutton_set_src(bt_backmain, LV_IMAGEBUTTON_STATE_CHECKED_DISABLED, NULL, "S:/Inputs/BT_BACK.bin", NULL);
    lv_obj_add_state(bt_backmain, LV_IMAGEBUTTON_STATE_RELEASED);
    lv_obj_set_pos(bt_backmain, 300, 100);
    lv_obj_add_event_cb(bt_backmain, event_menu_back, LV_EVENT_ALL, NULL);

	// Text
    lv_obj_t * text_back = lv_label_create(bt_backmain);
    lv_obj_set_width(text_back, LV_SIZE_CONTENT);
    lv_obj_set_height(text_back, LV_SIZE_CONTENT);
    lv_label_set_text(text_back, "BACK/MAIN");
    lv_obj_set_style_text_color(text_back, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(text_back, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(text_back, &Neue_Medium_14, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_align_to(text_back, bt_backmain, LV_ALIGN_CENTER, 0, 5);
}
