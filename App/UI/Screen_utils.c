/*
 * Screen_utils.c
 *
 *  Created on: 27 de ago. de 2026
 *      Author: rinaldo.santos
 */

#include "../App/UI/Screen_Utils.h"
#include "../App/UI/Screen_Main.h"

LV_FONT_DECLARE(Neue_Medium_14);
LV_FONT_DECLARE(Neue_Medium_16);

extern lv_obj_t * Tela_Main;

static lv_obj_t * bt_backmain = NULL;
static lv_obj_t * text_footer = NULL;

static void event_menu_back(lv_event_t * e)
{
	lv_event_code_t code = lv_event_get_code(e);

	if(code == LV_EVENT_CLICKED) {
		// Cria a próxima tela antes de carregar
		Screen_Create_Main();

		// auto_del = true vai deletar a Tela_Main automaticamente ao fim da animação
		lv_screen_load_anim(Tela_Main, LV_SCREEN_LOAD_ANIM_NONE, 0, 0, true);
	 }
}

void create_button_back_main(lv_obj_t * parent, int32_t x, int32_t y)
{
    // Button BACK/MAIN
    bt_backmain = lv_imagebutton_create(parent);
    lv_imagebutton_set_src(bt_backmain, LV_IMAGEBUTTON_STATE_RELEASED, NULL, "S:/Inputs/BT_BACK.bin", NULL);
    lv_imagebutton_set_src(bt_backmain, LV_IMAGEBUTTON_STATE_PRESSED, NULL, "S:/Inputs/BT_BACK_P.bin", NULL);
    lv_imagebutton_set_src(bt_backmain, LV_IMAGEBUTTON_STATE_DISABLED, NULL, "S:/Inputs/BT_BACK.bin", NULL);
    lv_imagebutton_set_src(bt_backmain, LV_IMAGEBUTTON_STATE_CHECKED_PRESSED, NULL, "S:/Inputs/BT_BACK_P.bin", NULL);
    lv_imagebutton_set_src(bt_backmain, LV_IMAGEBUTTON_STATE_CHECKED_RELEASED, NULL, "S:/Inputs/BT_BACK.bin", NULL);
    lv_imagebutton_set_src(bt_backmain, LV_IMAGEBUTTON_STATE_CHECKED_DISABLED, NULL, "S:/Inputs/BT_BACK.bin", NULL);
    lv_obj_add_state(bt_backmain, LV_IMAGEBUTTON_STATE_RELEASED);
    lv_obj_set_pos(bt_backmain, x, y);
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

void create_text_footer(lv_obj_t * parent)
{
    text_footer = lv_label_create(parent);
    lv_obj_set_width(text_footer, LV_SIZE_CONTENT);
    lv_obj_set_height(text_footer, LV_SIZE_CONTENT);
    lv_label_set_text(text_footer, "AIO MPX192 - NUMBER ONE");
    lv_obj_set_style_text_color(text_footer, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(text_footer, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(text_footer, &Neue_Medium_14, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(text_footer, 284, 300);
}

