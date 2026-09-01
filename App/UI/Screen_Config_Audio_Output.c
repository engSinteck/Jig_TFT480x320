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
LV_FONT_DECLARE(Neue_Medium_16);

void create_btn_config_audio_out_xlr(void);
void create_btn_config_audio_out_digital(void);

lv_obj_t * Tela_Config_Audio_Output = NULL;
static lv_obj_t * img_fundo_audio_out = NULL;
static lv_obj_t * bt_config_audio_out_xlr = NULL;
static lv_obj_t * text_bt_audio_out_digital = NULL;

void Screen_Config_Audio_Output_Create(void)
{
	Tela_Config_Audio_Output = lv_obj_create(NULL);
	lv_obj_clear_flag(Tela_Config_Audio_Output, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLLABLE);
	lv_obj_set_style_bg_color(Tela_Config_Audio_Output, lv_color_hex(0x000000), 0);
	lv_obj_set_style_bg_grad_color(Tela_Config_Audio_Output, lv_color_hex(0x000000), 0);

	// Imagem de Fundo
	img_fundo_audio_out = lv_img_create(Tela_Config_Audio_Output);
	lv_img_set_src(img_fundo_audio_out, "S:/CONFIG/TELA_CONFIG_AUDIO_OUTPUT.bin");
	lv_obj_set_pos(img_fundo_audio_out, 0, 0);

	// Buttons
	create_btn_config_audio_out_xlr();
	create_btn_config_audio_out_digital();

	create_button_back_main(Tela_Config_Audio_Output, 383, 4, PAGE_CONFIG);
}

static void event_audio_out_xlr(lv_event_t * e)
{
	lv_event_code_t code = lv_event_get_code(e);

	if(code == LV_EVENT_CLICKED) {
		lv_imagebutton_set_state(bt_config_audio_out_xlr, LV_IMAGEBUTTON_STATE_CHECKED_DISABLED);
		lv_imagebutton_set_state(text_bt_audio_out_digital, LV_IMAGEBUTTON_STATE_RELEASED);
	}
}

void create_btn_config_audio_out_xlr(void)
{
	bt_config_audio_out_xlr = lv_imagebutton_create(Tela_Config_Audio_Output);
	lv_imagebutton_set_src(bt_config_audio_out_xlr, LV_IMAGEBUTTON_STATE_RELEASED, NULL, "S:/CONFIG/BT_CONFIG_G.bin", NULL);
	lv_imagebutton_set_src(bt_config_audio_out_xlr, LV_IMAGEBUTTON_STATE_PRESSED, NULL, "S:/CONFIG/BT_CONFIG_G_P.bin", NULL);
	lv_imagebutton_set_src(bt_config_audio_out_xlr, LV_IMAGEBUTTON_STATE_DISABLED, NULL, "S:/CONFIG/BT_CONFIG_G.bin", NULL);
	lv_imagebutton_set_src(bt_config_audio_out_xlr, LV_IMAGEBUTTON_STATE_CHECKED_PRESSED, NULL, "S:/CONFIG/BT_CONFIG_G_P.bin", NULL);
	lv_imagebutton_set_src(bt_config_audio_out_xlr, LV_IMAGEBUTTON_STATE_CHECKED_RELEASED, NULL, "S:/CONFIG/BT_CONFIG_G.bin", NULL);
	lv_imagebutton_set_src(bt_config_audio_out_xlr, LV_IMAGEBUTTON_STATE_CHECKED_DISABLED, NULL, "S:/CONFIG/BT_CONFIG_G_SEL.bin", NULL);
	lv_obj_add_event_cb(bt_config_audio_out_xlr, event_audio_out_xlr, LV_EVENT_ALL, NULL);
	lv_obj_set_pos(bt_config_audio_out_xlr, 36, 206);
	lv_imagebutton_set_state(bt_config_audio_out_xlr, LV_IMAGEBUTTON_STATE_CHECKED_DISABLED);

	// Text
    lv_obj_t * text_bt_audio_out_xlr = lv_label_create(bt_config_audio_out_xlr);
    lv_obj_set_width(text_bt_audio_out_xlr, LV_SIZE_CONTENT);
    lv_obj_set_height(text_bt_audio_out_xlr, LV_SIZE_CONTENT);
    lv_label_set_text(text_bt_audio_out_xlr, "ANALOG XLR OUTPUTS");
    lv_obj_set_style_text_color(text_bt_audio_out_xlr, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(text_bt_audio_out_xlr, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(text_bt_audio_out_xlr, &Neue_Medium_14, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_align_to(text_bt_audio_out_xlr, bt_config_audio_out_xlr, LV_ALIGN_CENTER, 0, 0);
}

static void event_audio_out_digital(lv_event_t * e)
{
	lv_event_code_t code = lv_event_get_code(e);

	if(code == LV_EVENT_CLICKED) {
		lv_imagebutton_set_state(bt_config_audio_out_xlr, LV_IMAGEBUTTON_STATE_RELEASED);
		lv_imagebutton_set_state(text_bt_audio_out_digital, LV_IMAGEBUTTON_STATE_CHECKED_DISABLED);
	}
}

void create_btn_config_audio_out_digital(void)
{
	text_bt_audio_out_digital = lv_imagebutton_create(Tela_Config_Audio_Output);
	lv_imagebutton_set_src(text_bt_audio_out_digital, LV_IMAGEBUTTON_STATE_RELEASED, NULL, "S:/CONFIG/BT_CONFIG_G.bin", NULL);
	lv_imagebutton_set_src(text_bt_audio_out_digital, LV_IMAGEBUTTON_STATE_PRESSED, NULL, "S:/CONFIG/BT_CONFIG_G_P.bin", NULL);
	lv_imagebutton_set_src(text_bt_audio_out_digital, LV_IMAGEBUTTON_STATE_DISABLED, NULL, "S:/CONFIG/BT_CONFIG_G.bin", NULL);
	lv_imagebutton_set_src(text_bt_audio_out_digital, LV_IMAGEBUTTON_STATE_CHECKED_PRESSED, NULL, "S:/CONFIG/BT_CONFIG_G_P.bin", NULL);
	lv_imagebutton_set_src(text_bt_audio_out_digital, LV_IMAGEBUTTON_STATE_CHECKED_RELEASED, NULL, "S:/CONFIG/BT_CONFIG_G.bin", NULL);
	lv_imagebutton_set_src(text_bt_audio_out_digital, LV_IMAGEBUTTON_STATE_CHECKED_DISABLED, NULL, "S:/CONFIG/BT_CONFIG_G_SEL.bin", NULL);
	lv_obj_add_event_cb(text_bt_audio_out_digital, event_audio_out_digital, LV_EVENT_ALL, NULL);
	lv_obj_set_pos(text_bt_audio_out_digital, 260, 206);
	lv_imagebutton_set_state(text_bt_audio_out_digital, LV_IMAGEBUTTON_STATE_RELEASED);

	// Text
    lv_obj_t * text_bt_audio_out_xlr = lv_label_create(text_bt_audio_out_digital);
    lv_obj_set_width(text_bt_audio_out_xlr, LV_SIZE_CONTENT);
    lv_obj_set_height(text_bt_audio_out_xlr, LV_SIZE_CONTENT);
    lv_label_set_text(text_bt_audio_out_xlr, "DIGITAL AES192 OUTPUT");
    lv_obj_set_style_text_color(text_bt_audio_out_xlr, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(text_bt_audio_out_xlr, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(text_bt_audio_out_xlr, &Neue_Medium_14, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_align_to(text_bt_audio_out_xlr, text_bt_audio_out_digital, LV_ALIGN_CENTER, 0, 0);
}
