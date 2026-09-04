/*
 * Screen_utils.c
 *
 *  Created on: 27 de ago. de 2026
 *      Author: rinaldo.santos
 */

#include "../App/UI/Screen_Utils.h"
#include "../App/UI/Screen_Main.h"
#include "../App/UI/Screen_Config.h"
#include "../App/UI/Screen_Config_About.h"

LV_FONT_DECLARE(Neue_Medium_14);
LV_FONT_DECLARE(Neue_Medium_16);

LV_IMG_DECLARE(SEP_CIANO);
LV_IMG_DECLARE(SEP_VD);

extern lv_obj_t * Tela_Main;

static lv_obj_t * bt_backmain = NULL;
static lv_obj_t * bt_nextmain = NULL;
static lv_obj_t * text_footer = NULL;
static lv_obj_t * img_tuned_sep1 = NULL;
static lv_obj_t * img_tuned_sep2 = NULL;

static void event_menu_back(lv_event_t * e)
{
	lv_event_code_t code = lv_event_get_code(e);

	if(code == LV_EVENT_CLICKED) {
		uint32_t page = (uint32_t)(uintptr_t)lv_event_get_user_data(e);

		switch(page) {
			case PAGE_MAIN:
			default:
				// Cria a próxima tela antes de carregar
				Screen_Create_Main();
				// auto_del = true vai deletar a Tela_Main automaticamente ao fim da animação
				lv_screen_load_anim(Tela_Main, LV_SCREEN_LOAD_ANIM_NONE, 0, 0, true);
				break;
			case PAGE_CONFIG:
				// Cria a próxima tela antes de carregar
				Screen_Config_Create();
				// auto_del = true vai deletar a Tela_Main automaticamente ao fim da animação
				lv_screen_load_anim(Tela_Config, LV_SCREEN_LOAD_ANIM_NONE, 0, 0, true);
				break;
		}
	 }
}

void create_button_back_main(lv_obj_t * parent, int32_t x, int32_t y, uint32_t page)
{
    // Button BACK/MAIN
    bt_backmain = lv_imagebutton_create(parent);
    lv_imagebutton_set_src(bt_backmain, LV_IMAGEBUTTON_STATE_RELEASED, NULL, "S:/Inputs/BT_BACK.bin", NULL);
    lv_imagebutton_set_src(bt_backmain, LV_IMAGEBUTTON_STATE_PRESSED, NULL, "S:/Inputs/BT_BACK_P.bin", NULL);
    lv_imagebutton_set_src(bt_backmain, LV_IMAGEBUTTON_STATE_DISABLED, NULL, "S:/Inputs/BT_BACK.bin", NULL);
    lv_imagebutton_set_src(bt_backmain, LV_IMAGEBUTTON_STATE_CHECKED_PRESSED, NULL, "S:/Inputs/BT_BACK_P.bin", NULL);
    lv_imagebutton_set_src(bt_backmain, LV_IMAGEBUTTON_STATE_CHECKED_RELEASED, NULL, "S:/Inputs/BT_BACK.bin", NULL);
    lv_imagebutton_set_src(bt_backmain, LV_IMAGEBUTTON_STATE_CHECKED_DISABLED, NULL, "S:/Inputs/BT_BACK.bin", NULL);
    lv_obj_set_pos(bt_backmain, x, y);
    lv_obj_add_event_cb(bt_backmain, event_menu_back, LV_EVENT_ALL, (void *)(uintptr_t)page);

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

static void event_menu_next(lv_event_t * e)
{
	lv_event_code_t code = lv_event_get_code(e);

	if(code == LV_EVENT_CLICKED) {
		uint32_t page = (uint32_t)(uintptr_t)lv_event_get_user_data(e);

		switch(page) {
			case PAGE_MAIN:
				// Cria a próxima tela antes de carregar
				Screen_Create_Main();
				// auto_del = true vai deletar a Tela_Main automaticamente ao fim da animação
				lv_screen_load_anim(Tela_Main, LV_SCREEN_LOAD_ANIM_NONE, 0, 0, true);
				break;
			case PAGE_CONFIG:
				// Cria a próxima tela antes de carregar
				Screen_Config_Create();
				// auto_del = true vai deletar a Tela_Main automaticamente ao fim da animação
				lv_screen_load_anim(Tela_Config, LV_SCREEN_LOAD_ANIM_NONE, 0, 0, true);
				break;
			case PAGE_ABOUT:
				// Cria a próxima tela antes de carregar
				Screen_Config_About_1_Create();
				// auto_del = true vai deletar a Tela_Main automaticamente ao fim da animação
				lv_screen_load_anim(Tela_Config_About_1, LV_SCREEN_LOAD_ANIM_NONE, 0, 0, true);
				break;
		}
	 }
}

void create_button_next_main(lv_obj_t * parent, int32_t x, int32_t y, uint32_t page)
{
    // Button NEXT/MAIN
    bt_nextmain = lv_imagebutton_create(parent);
    lv_imagebutton_set_src(bt_nextmain, LV_IMAGEBUTTON_STATE_RELEASED, NULL, "S:/ABOUT/BT_NEXT.bin", NULL);
    lv_imagebutton_set_src(bt_nextmain, LV_IMAGEBUTTON_STATE_PRESSED, NULL, "S:/ABOUT/BT_NEXT_P.bin", NULL);
    lv_imagebutton_set_src(bt_nextmain, LV_IMAGEBUTTON_STATE_DISABLED, NULL, "S:/ABOUT/BT_NEXT.bin", NULL);
    lv_imagebutton_set_src(bt_nextmain, LV_IMAGEBUTTON_STATE_CHECKED_PRESSED, NULL, "S:/ABOUT/BT_NEXT_P.bin", NULL);
    lv_imagebutton_set_src(bt_nextmain, LV_IMAGEBUTTON_STATE_CHECKED_RELEASED, NULL, "S:/ABOUT/BT_NEXT.bin", NULL);
    lv_imagebutton_set_src(bt_nextmain, LV_IMAGEBUTTON_STATE_CHECKED_DISABLED, NULL, "S:/ABOUT/BT_NEXT.bin", NULL);
    lv_obj_set_pos(bt_nextmain, x, y);
    lv_obj_add_event_cb(bt_nextmain, event_menu_next, LV_EVENT_ALL, (void *)(uintptr_t)page);

	// Text
    lv_obj_t * text_next = lv_label_create(bt_nextmain);
    lv_obj_set_width(text_next, LV_SIZE_CONTENT);
    lv_obj_set_height(text_next, LV_SIZE_CONTENT);
    lv_label_set_text(text_next, "NEXT");
    lv_obj_set_style_text_color(text_next, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(text_next, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(text_next, &Neue_Medium_14, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_align_to(text_next, bt_nextmain, LV_ALIGN_CENTER, 0, 5);
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

void create_img_separator(lv_obj_t * parent)
{
	// SEP Symbol
	img_tuned_sep1 = lv_img_create(parent);
	lv_img_set_src(img_tuned_sep1, &SEP_CIANO);
	lv_obj_set_pos(img_tuned_sep1, 334, 28);

	// SEP VD Symbol
	img_tuned_sep2 = lv_img_create(parent);
	lv_img_set_src(img_tuned_sep2, &SEP_VD);
	lv_obj_set_pos(img_tuned_sep2, 334, 58);
}
