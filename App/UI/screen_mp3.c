/*
 * screen_mp3.c
 *
 *  Created on: 20 de jul. de 2026
 *      Author: rinaldo.santos
 */

#include "main.h"
#include "lvgl.h"
#include "../App/UI/screen_mp3.h"
#include "../App/UI/screen_debug.h"
#include "../App/src/log_cdc.h"

void Button_MP3(void);
void Button_config(void);

lv_obj_t * Tela_MP3;
static lv_obj_t * btnplay;
static lv_obj_t * btnprev;
static lv_obj_t * btnnext;
static lv_obj_t * btnstop;
static lv_obj_t * btnconfig;

void screen_mp3(void)
{
	Tela_MP3 = lv_obj_create(NULL);
	lv_obj_clear_flag(Tela_MP3, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLLABLE);
	lv_obj_set_style_bg_color(Tela_MP3, lv_color_hex(0x000000), 0);
	lv_obj_set_style_bg_grad_color(Tela_MP3, lv_color_hex(0x000000), 0);

	static lv_style_t style_txt;
	lv_style_init(&style_txt);
	lv_style_set_text_font(&style_txt, &lv_font_montserrat_16);
	lv_style_set_text_color(&style_txt, lv_color_hex(0xFFFFFF)); // white text

	lv_obj_t * label1 = lv_label_create(Tela_MP3);
	lv_label_set_long_mode(label1, LV_LABEL_LONG_WRAP);     /*Break the long lines*/
	lv_label_set_recolor(label1, true);                      /*Enable re-coloring by commands in the text*/
	lv_label_set_text(label1, "BT401 / MP3:");
	lv_obj_add_style(label1, &style_txt, LV_PART_MAIN);
	lv_obj_align_to(label1, Tela_MP3, LV_ALIGN_OUT_TOP_MID, 0, 30);

	Button_config();
	Button_MP3();

	Button_Menu(Tela_MP3);
}

static void event_prev_handler(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);

    if(code == LV_EVENT_CLICKED) {
        LV_LOG_USER("Clicked");
    }
    else if(code == LV_EVENT_VALUE_CHANGED) {
        LV_LOG_USER(" PREV Toggled");

        //uint32_t btn_id = 0;
        //lv_event_send(btnplay, LV_EVENT_RELEASED, &btn_id);
        //lv_event_send(btnnext, LV_EVENT_RELEASED, &btn_id);
        //lv_event_send(btnstop, LV_EVENT_RELEASED, &btn_id);
    }
}

static void event_play_handler(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);

    if(code == LV_EVENT_CLICKED) {
        LV_LOG_USER("Clicked");
    }
    else if(code == LV_EVENT_VALUE_CHANGED) {
        LV_LOG_USER("PLAY Toggled");

        //uint32_t btn_id = 0;
        //lv_event_send(btnprev, LV_EVENT_RELEASED, &btn_id);
        //lv_event_send(btnnext, LV_EVENT_RELEASED, &btn_id);
        //lv_event_send(btnstop, LV_EVENT_RELEASED, &btn_id);
    }
}

static void event_next_handler(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);

    if(code == LV_EVENT_CLICKED) {
        LV_LOG_USER("Clicked");
    }
    else if(code == LV_EVENT_VALUE_CHANGED) {
        LV_LOG_USER("NEXT Toggled");

        //uint32_t btn_id = 0;
        //lv_event_send(btnprev, LV_EVENT_RELEASED, &btn_id);
        //lv_event_send(btnplay, LV_EVENT_RELEASED, &btn_id);
        //lv_event_send(btnstop, LV_EVENT_RELEASED, &btn_id);
    }
}

static void event_stop_handler(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);

    if(code == LV_EVENT_CLICKED) {
        LV_LOG_USER("Clicked");
    }
    else if(code == LV_EVENT_VALUE_CHANGED) {
        LV_LOG_USER("STOP Toggled");

        //uint32_t btn_id = 0;
        //lv_event_send(btnprev, LV_EVENT_RELEASED, &btn_id);
        //lv_event_send(btnplay, LV_EVENT_RELEASED, &btn_id);
        //lv_event_send(btnnext, LV_EVENT_RELEASED, &btn_id);
    }
}

void Button_MP3(void)
{
	btnprev = lv_btn_create(Tela_MP3);
	lv_obj_add_event_cb(btnprev, event_prev_handler, LV_EVENT_ALL, NULL);
	lv_obj_add_flag(btnprev, LV_OBJ_FLAG_CHECKABLE);
	lv_obj_set_height(btnprev, LV_SIZE_CONTENT);
	lv_obj_align(btnprev, LV_ALIGN_CENTER, -180, -20);

	lv_obj_t * labelprev = lv_label_create(btnprev);
	lv_label_set_text(labelprev, "PREV");
	lv_obj_center(labelprev);

	//
	btnplay = lv_btn_create(Tela_MP3);
	lv_obj_add_event_cb(btnplay, event_play_handler, LV_EVENT_ALL, NULL);
	lv_obj_add_flag(btnplay, LV_OBJ_FLAG_CHECKABLE);
	lv_obj_set_height(btnplay, LV_SIZE_CONTENT);
	lv_obj_align(btnplay, LV_ALIGN_CENTER, -60, -20);

	lv_obj_t * labelplay = lv_label_create(btnplay);
	lv_label_set_text(labelplay, "PLAY");
	lv_obj_center(labelplay);

	//
	btnnext = lv_btn_create(Tela_MP3);
	lv_obj_add_event_cb(btnnext, event_next_handler, LV_EVENT_ALL, NULL);
	lv_obj_add_flag(btnnext, LV_OBJ_FLAG_CHECKABLE);
	lv_obj_set_height(btnnext, LV_SIZE_CONTENT);
	lv_obj_align(btnnext, LV_ALIGN_CENTER, 60, -20);

	lv_obj_t * labelnext = lv_label_create(btnnext);
	lv_label_set_text(labelnext, "NEXT");
	lv_obj_center(labelnext);

	//
	btnstop = lv_btn_create(Tela_MP3);
	lv_obj_add_event_cb(btnstop, event_stop_handler, LV_EVENT_ALL, NULL);
	lv_obj_add_flag(btnstop, LV_OBJ_FLAG_CHECKABLE);
	lv_obj_set_height(btnstop, LV_SIZE_CONTENT);
	lv_obj_align(btnstop, LV_ALIGN_CENTER, 180, -20);

	lv_obj_t * labelstop = lv_label_create(btnstop);
	lv_label_set_text(labelstop, "STOP");
	lv_obj_center(labelstop);
}

static void event_config_handler(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);

    if(code == LV_EVENT_CLICKED) {
        LV_LOG_USER("Config Clicked");
    }
}

void Button_config(void)
{
	btnconfig = lv_btn_create(Tela_MP3);
	lv_obj_add_event_cb(btnconfig, event_config_handler, LV_EVENT_ALL, NULL);
	lv_obj_set_height(btnconfig, LV_SIZE_CONTENT);
	lv_obj_set_pos(btnconfig, 1, 1);

	lv_obj_t * labelconfig = lv_label_create(btnconfig);
	lv_label_set_text(labelconfig, "CONFIG");
	lv_obj_center(labelconfig);
}
