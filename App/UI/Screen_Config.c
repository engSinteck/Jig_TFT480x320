/*
 * Screen_Config.c
 *
 *  Created on: 28 de ago. de 2026
 *      Author: rinaldo.santos
 */

#include "stdbool.h"
#include "rng.h"
#include "stdio.h"
#include "string.h"

#include "../App/UI/Screen_Config.h"
#include "../App/UI/Screen_Utils.h"

#include "../App/UI/Screen_Config_Impedance.h"
#include "../App/UI/Screen_Config_Audio_Input.h"
#include "../App/UI/Screen_Config_Audio_Output.h"
#include "../App/UI/Screen_Config_SampleRate.h"
#include "../App/UI/Screen_Config_Silence.h"
#include "../App/UI/Screen_Config_Lock.h"
#include "../App/UI/Screen_Config_Display.h"
#include "../App/UI/Screen_Config_Signal.h"
#include "../App/UI/Screen_Config_About.h"

LV_FONT_DECLARE(Neue_Medium_14);

void create_labels_config(void);
void create_buttons_config(void);
void create_buttons_config_about(void);

lv_obj_t * Tela_Config = NULL;
static lv_obj_t * img_fundo_config = NULL;
static lv_obj_t * text_config_top = NULL;
static lv_obj_t * bt_config[8];
static lv_obj_t * label_bt_config[8];
static lv_obj_t * bt_config_about;

void Screen_Config_Create(void)
{
	Tela_Config = lv_obj_create(NULL);
	lv_obj_clear_flag(Tela_Config, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLLABLE);
	lv_obj_set_style_bg_color(Tela_Config, lv_color_hex(0x000000), 0);
	lv_obj_set_style_bg_grad_color(Tela_Config, lv_color_hex(0x000000), 0);

	// Imagem de Fundo
	img_fundo_config = lv_img_create(Tela_Config);
	lv_img_set_src(img_fundo_config, "S:/CONFIG/TELA_FUNDO.bin");
	lv_obj_set_pos(img_fundo_config, 0, 0);

	// Text Top
	create_labels_config();

	// Buttons
	create_buttons_config();
	create_buttons_config_about();

	create_button_back_main(Tela_Config, 380, 8);
}

void create_labels_config(void)
{
    text_config_top = lv_label_create(Tela_Config);
    lv_obj_set_width(text_config_top, LV_SIZE_CONTENT);
    lv_obj_set_height(text_config_top, LV_SIZE_CONTENT);
    lv_label_set_text(text_config_top, "GENERAL CONFIGURATIONS:");
    lv_obj_set_style_text_color(text_config_top, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(text_config_top, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(text_config_top, &Neue_Medium_14, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(text_config_top, 7, 5);
}

static void event_config_impedance(lv_event_t * e)
{
	lv_event_code_t code = lv_event_get_code(e);

	if(code == LV_EVENT_CLICKED) {
		// Cria a próxima tela antes de carregar
		Screen_Config_IMP_Create();

		// auto_del = true vai deletar a Tela_Main automaticamente ao fim da animação
		lv_screen_load_anim(Tela_Config_IMP, LV_SCREEN_LOAD_ANIM_NONE, 0, 0, true);
	 }
}

static void event_config_input(lv_event_t * e)
{
	lv_event_code_t code = lv_event_get_code(e);

	if(code == LV_EVENT_CLICKED) {
		// Cria a próxima tela antes de carregar
		Screen_Config_Audio_Input_Create();

		// auto_del = true vai deletar a Tela_Main automaticamente ao fim da animação
		lv_screen_load_anim(Tela_Config_Audio_Input, LV_SCREEN_LOAD_ANIM_NONE, 0, 0, true);
	 }
}

static void event_config_output(lv_event_t * e)
{
	lv_event_code_t code = lv_event_get_code(e);

	if(code == LV_EVENT_CLICKED) {
		// Cria a próxima tela antes de carregar
		Screen_Config_Audio_Output_Create();

		// auto_del = true vai deletar a Tela_Main automaticamente ao fim da animação
		lv_screen_load_anim(Tela_Config_Audio_Output, LV_SCREEN_LOAD_ANIM_NONE, 0, 0, true);
	 }
}

static void event_config_rate(lv_event_t * e)
{
	lv_event_code_t code = lv_event_get_code(e);

	if(code == LV_EVENT_CLICKED) {
		// Cria a próxima tela antes de carregar
		Screen_Config_Sample_Create();

		// auto_del = true vai deletar a Tela_Main automaticamente ao fim da animação
		lv_screen_load_anim(Tela_Config_Sample, LV_SCREEN_LOAD_ANIM_NONE, 0, 0, true);
	 }
}

static void event_config_silence(lv_event_t * e)
{
	lv_event_code_t code = lv_event_get_code(e);

	if(code == LV_EVENT_CLICKED) {
		// Cria a próxima tela antes de carregar
		Screen_Config_Silence_Create();

		// auto_del = true vai deletar a Tela_Main automaticamente ao fim da animação
		lv_screen_load_anim(Tela_Config_Silence, LV_SCREEN_LOAD_ANIM_NONE, 0, 0, true);
	 }
}

static void event_config_lock(lv_event_t * e)
{
	lv_event_code_t code = lv_event_get_code(e);

	if(code == LV_EVENT_CLICKED) {
		// Cria a próxima tela antes de carregar
		Screen_Config_Lock_Create();

		// auto_del = true vai deletar a Tela_Main automaticamente ao fim da animação
		lv_screen_load_anim(Tela_Config_Lock, LV_SCREEN_LOAD_ANIM_NONE, 0, 0, true);
	 }
}

static void event_config_display(lv_event_t * e)
{
	lv_event_code_t code = lv_event_get_code(e);

	if(code == LV_EVENT_CLICKED) {
		// Cria a próxima tela antes de carregar
		Screen_Config_Display_Create();

		// auto_del = true vai deletar a Tela_Main automaticamente ao fim da animação
		lv_screen_load_anim(Tela_Config_Display, LV_SCREEN_LOAD_ANIM_NONE, 0, 0, true);
	 }
}

static void event_config_signal(lv_event_t * e)
{
	lv_event_code_t code = lv_event_get_code(e);

	if(code == LV_EVENT_CLICKED) {
		// Cria a próxima tela antes de carregar
		Screen_Config_Signal_Create();

		// auto_del = true vai deletar a Tela_Main automaticamente ao fim da animação
		lv_screen_load_anim(Tela_Config_Signal, LV_SCREEN_LOAD_ANIM_NONE, 0, 0, true);
	 }
}

static void event_config_about(lv_event_t * e)
{
	lv_event_code_t code = lv_event_get_code(e);

	if(code == LV_EVENT_CLICKED) {
		// Cria a próxima tela antes de carregar
		Screen_Config_About_Create();

		// auto_del = true vai deletar a Tela_Main automaticamente ao fim da animação
		lv_screen_load_anim(Tela_Config_About, LV_SCREEN_LOAD_ANIM_NONE, 0, 0, true);
	 }
}

void create_buttons_config(void)
{
    // Button
	for(uint8_t x = 0; x < 8; x++) {
		bt_config[x] = lv_imagebutton_create(Tela_Config);
		lv_imagebutton_set_src(bt_config[x], LV_IMAGEBUTTON_STATE_RELEASED, NULL, "S:/CONFIG/BT_CONFIG.bin", NULL);
		lv_imagebutton_set_src(bt_config[x], LV_IMAGEBUTTON_STATE_PRESSED, NULL, "S:/CONFIG/BT_CONFIG_P.bin", NULL);
		lv_imagebutton_set_src(bt_config[x], LV_IMAGEBUTTON_STATE_DISABLED, NULL, "S:/CONFIG/BT_CONFIG.bin", NULL);
		lv_imagebutton_set_src(bt_config[x], LV_IMAGEBUTTON_STATE_CHECKED_PRESSED, NULL, "S:/CONFIG/BT_CONFIG_P.bin", NULL);
		lv_imagebutton_set_src(bt_config[x], LV_IMAGEBUTTON_STATE_CHECKED_RELEASED, NULL, "S:/CONFIG/BT_CONFIG.bin", NULL);
		lv_imagebutton_set_src(bt_config[x], LV_IMAGEBUTTON_STATE_CHECKED_DISABLED, NULL, "S:/CONFIG/BT_CONFIG.bin", NULL);
		lv_obj_add_state(bt_config[x], LV_IMAGEBUTTON_STATE_RELEASED);

		// Text
		label_bt_config[x] = lv_label_create(bt_config[x]);
	    lv_obj_set_width(label_bt_config[x], LV_SIZE_CONTENT);
	    lv_obj_set_height(label_bt_config[x], LV_SIZE_CONTENT);
	    lv_obj_set_style_text_color(label_bt_config[x], lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
	    lv_obj_set_style_text_opa(label_bt_config[x], 255, LV_PART_MAIN | LV_STATE_DEFAULT);
	    lv_obj_set_style_text_font(label_bt_config[x], &Neue_Medium_14, LV_PART_MAIN | LV_STATE_DEFAULT);
	    //lv_obj_align_to(label_bt_config[x], bt_config[x], LV_ALIGN_CENTER, 0, 0);
	}

	lv_obj_set_pos(bt_config[0], 30, 54);
	lv_obj_set_pos(bt_config[1], 30, 104);
	lv_obj_set_pos(bt_config[2], 30, 154);
	lv_obj_set_pos(bt_config[3], 30, 204);

	lv_obj_set_pos(bt_config[4], 225, 54);
	lv_obj_set_pos(bt_config[5], 225, 104);
	lv_obj_set_pos(bt_config[6], 225, 154);
	lv_obj_set_pos(bt_config[7], 225, 204);

	// Text
    lv_label_set_text(label_bt_config[0], "XLR INPUT IMPEDANCE");
    lv_obj_align_to(label_bt_config[0], bt_config[0], LV_ALIGN_CENTER, 0, 0);
    lv_label_set_text(label_bt_config[1], "AUDIO INPUT TYPE");
    lv_obj_align_to(label_bt_config[1], bt_config[1], LV_ALIGN_CENTER, 0, 0);
    lv_label_set_text(label_bt_config[2], "AUDIO OUTPUT TYPE");
    lv_obj_align_to(label_bt_config[2], bt_config[2], LV_ALIGN_CENTER, 0, 0);
    lv_label_set_text(label_bt_config[3], "SAMPLE RATE");
    lv_obj_align_to(label_bt_config[3], bt_config[3], LV_ALIGN_CENTER, 0, 0);

    lv_label_set_text(label_bt_config[4], "SILENCE TIMEOUT");
    lv_obj_align_to(label_bt_config[4], bt_config[4], LV_ALIGN_CENTER, 0, 0);
    lv_label_set_text(label_bt_config[5], "LOCK SETTINGS");
    lv_obj_align_to(label_bt_config[5], bt_config[5], LV_ALIGN_CENTER, 0, 0);
    lv_label_set_text(label_bt_config[6], "DISPLAY");
    lv_obj_align_to(label_bt_config[6], bt_config[6], LV_ALIGN_CENTER, 0, 0);
    lv_label_set_text(label_bt_config[7], "SIGNAL GENERATOR");
    lv_obj_align_to(label_bt_config[7], bt_config[7], LV_ALIGN_CENTER, 0, 0);

    // Events
	lv_obj_add_event_cb(bt_config[0], event_config_impedance, LV_EVENT_ALL, NULL);
	lv_obj_add_event_cb(bt_config[1], event_config_input, LV_EVENT_ALL, NULL);
	lv_obj_add_event_cb(bt_config[2], event_config_output, LV_EVENT_ALL, NULL);
	lv_obj_add_event_cb(bt_config[3], event_config_rate, LV_EVENT_ALL, NULL);
	lv_obj_add_event_cb(bt_config[4], event_config_silence, LV_EVENT_ALL, NULL);
	lv_obj_add_event_cb(bt_config[5], event_config_lock, LV_EVENT_ALL, NULL);
	lv_obj_add_event_cb(bt_config[6], event_config_display, LV_EVENT_ALL, NULL);
	lv_obj_add_event_cb(bt_config[7], event_config_signal, LV_EVENT_ALL, NULL);
}

void create_buttons_config_about(void)
{
	bt_config_about = lv_imagebutton_create(Tela_Config);
	lv_imagebutton_set_src(bt_config_about, LV_IMAGEBUTTON_STATE_RELEASED, NULL, "S:/CONFIG/BT_CONFIG_VD.bin", NULL);
	lv_imagebutton_set_src(bt_config_about, LV_IMAGEBUTTON_STATE_PRESSED, NULL, "S:/CONFIG/BT_CONFIG_VD_P.bin", NULL);
	lv_imagebutton_set_src(bt_config_about, LV_IMAGEBUTTON_STATE_DISABLED, NULL, "S:/CONFIG/BT_CONFIG_VD.bin", NULL);
	lv_imagebutton_set_src(bt_config_about, LV_IMAGEBUTTON_STATE_CHECKED_PRESSED, NULL, "S:/CONFIG/BT_CONFIG_VD_P.bin", NULL);
	lv_imagebutton_set_src(bt_config_about, LV_IMAGEBUTTON_STATE_CHECKED_RELEASED, NULL, "S:/CONFIG/BT_CONFIG_VD.bin", NULL);
	lv_imagebutton_set_src(bt_config_about, LV_IMAGEBUTTON_STATE_CHECKED_DISABLED, NULL, "S:/CONFIG/BT_CONFIG_VD.bin", NULL);
	lv_obj_add_state(bt_config_about, LV_IMAGEBUTTON_STATE_RELEASED);
	lv_obj_add_event_cb(bt_config_about, event_config_about, LV_EVENT_ALL, NULL);
	lv_obj_set_pos(bt_config_about, 225, 254);

	// Text
    lv_obj_t * text_config_about = lv_label_create(bt_config_about);
    lv_obj_set_width(text_config_about, LV_SIZE_CONTENT);
    lv_obj_set_height(text_config_about, LV_SIZE_CONTENT);
    lv_label_set_text(text_config_about, "ABOUT THIS PRODUCT");
    lv_obj_set_style_text_color(text_config_about, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(text_config_about, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(text_config_about, &Neue_Medium_14, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_align_to(text_config_about, bt_config_about, LV_ALIGN_CENTER, 0, 0);
}
