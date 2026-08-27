/*
 * Screen_Splash.c
 *
 *  Created on: 26 de ago. de 2026
 *      Author: rinaldo.santos
 */

#include "main.h"
#include "stdbool.h"
#include "lvgl.h"

#include "../App/UI/Screen_Splash.h"
#include "../App/UI/Screen_Main.h"

LV_IMG_DECLARE(LOGO_ONE_2);

extern lv_obj_t * Tela_Main;

static lv_obj_t * Tela_Splash = NULL;
static lv_obj_t * img_fundo_splash = NULL;

static lv_timer_t * task_Splash = NULL;

void update_screen_splash(lv_timer_t * timer)
{
    // 1. Cria a tela principal
	Screen_Create_Main();

    // 2. Transiciona para a Main (auto_del = true deleta a Tela_Splash automaticamente)
    lv_screen_load_anim(Tela_Main, LV_SCREEN_LOAD_ANIM_NONE, 500, 2, true);

    // 3. Deleta este timer de disparo único
    lv_timer_delete(timer);
    task_Splash = NULL;
}

// Callback para limpar o ponteiro quando a splash for deletada da memória
//static void screen_splash_lifecycle_event_cb(lv_event_t * e)
//{
//	if(lv_event_get_code(e) == LV_EVENT_SCREEN_UNLOADED) {
//		Tela_Splash = NULL;
//	}
//}

void Screen_Create_Splash(void)
{
	Tela_Splash = lv_obj_create(NULL);
	lv_obj_clear_flag(Tela_Splash, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLLABLE);
	lv_obj_set_style_bg_color(Tela_Splash, lv_color_hex(0x000000), 0);
	lv_obj_set_style_bg_grad_color(Tela_Splash, lv_color_hex(0x000000), 0);

	// Vincula o evento de destruição
	//lv_obj_add_event_cb(Tela_Splash, screen_splash_lifecycle_event_cb, LV_EVENT_ALL, NULL);

	// Imagem de Fundo
	img_fundo_splash = lv_img_create(Tela_Splash);
	lv_img_set_src(img_fundo_splash, &LOGO_ONE_2);
	lv_obj_set_pos(img_fundo_splash, 0, 0);

	// Cria o timer de 3000ms (3 segundos)
	task_Splash = lv_timer_create(update_screen_splash, 3000, NULL);

	// Configura para executar apenas uma vez (one-shot)
	lv_timer_set_repeat_count(task_Splash, 1);

	lv_scr_load(Tela_Splash);
}
