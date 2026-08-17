/*
 * Screen_Splash.c
 *
 *  Created on: 17 de ago. de 2026
 *      Author: rinaldo.santos
 */

#include "main.h"
#include "stdbool.h"
#include "lvgl.h"

#include "../App/UI/lvgl_data.h"
#include "../App/UI/Screen_Splash.h"
#include "../App/UI/Screen_Main.h"

static lv_obj_t * Tela_Splash = NULL;
static lv_timer_t * timer_Splash = NULL;

// Callback disparado após os 3 segundos
static void splash_timer_cb(lv_timer_t * timer)
{
    // 1. Cria a tela principal
	Screen_Main_Create();

    // 2. Transiciona para a Main (auto_del = true deleta a Tela_Splash automaticamente)
    lv_screen_load_anim(Tela_Main, LV_SCREEN_LOAD_ANIM_FADE_ON, 500, 0, true);

    // 3. Deleta este timer de disparo único
    lv_timer_delete(timer);
    timer_Splash = NULL;
}

// Callback para limpar o ponteiro quando a splash for deletada da memória
static void screen_splash_lifecycle_event_cb(lv_event_t * e)
{
    if(lv_event_get_code(e) == LV_EVENT_SCREEN_UNLOADED) {
        Tela_Splash = NULL;
    }
}

void Screen_Splash_Create(void)
{
    if(Tela_Splash != NULL) return;

    // Cria a tela base
    Tela_Splash = lv_obj_create(NULL);
    lv_obj_clear_flag(Tela_Splash, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_bg_color(Tela_Splash, lv_color_hex(0x000000), 0);

    // Vincula o evento de destruição
    lv_obj_add_event_cb(Tela_Splash, screen_splash_lifecycle_event_cb, LV_EVENT_ALL, NULL);

    // Imagem de Fundo da Apresentação
    lv_obj_t * img_splash = lv_image_create(Tela_Splash);
    lv_image_set_src(img_splash, "S:/SPLASH/TELA_SPLASH.bin"); // Sua imagem de splash
    lv_obj_set_pos(img_splash, 0, 0);

    // Cria o timer de 3000ms (3 segundos)
    timer_Splash = lv_timer_create(splash_timer_cb, 3000, NULL);

    // Configura para executar apenas uma vez (one-shot)
    lv_timer_set_repeat_count(timer_Splash, 1);
}

void app_init(void)
{
    // Inicializa o sistema abrindo a Splash Screen
    Screen_Splash_Create();
    lv_screen_load(Tela_Splash);
}
