/*
 * scrren_boot.c
 *
 *  Created on: 28 de jul. de 2026
 *      Author: rinaldo.santos
 */


#include "main.h"
#include "stdbool.h"
#include "lvgl.h"

#include "../App/UI/screen_debug.h"

LV_IMG_DECLARE(LOGO_ONE_2);

extern lv_obj_t * Tela_Debug;

static lv_obj_t * Tela_Boot;
static lv_obj_t * img_boot;

static lv_timer_t * task_Boot;

static uint32_t cont_boot = 0;

void _ui_screen_change(lv_obj_t ** target, lv_scr_load_anim_t fademode, int spd, int delay, void (*target_init)(void))
{
    if(*target == NULL)
        target_init();
    lv_scr_load_anim(*target, fademode, spd, delay, false);
}

void update_boot_screen(lv_timer_t * timer)
{
    cont_boot++;
    if(cont_boot >= 6) {
    	_ui_screen_change(&Tela_Debug, LV_SCR_LOAD_ANIM_MOVE_LEFT, 500, 10, &screen_debug);
    }
}

void screen_boot(void)
{
	Tela_Boot = lv_obj_create(NULL);
	lv_obj_clear_flag(Tela_Boot, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLLABLE);
	lv_obj_set_style_bg_color(Tela_Boot, lv_color_hex(0x000000), 0);
	lv_obj_set_style_bg_grad_color(Tela_Boot, lv_color_hex(0x000000), 0);

	// Imagem de Fundo
	img_boot = lv_img_create(Tela_Boot);
	//lv_img_set_src(img_boot, "S:/LOGO_ONE_2.bin");
	lv_img_set_src(img_boot, &LOGO_ONE_2);

    lv_obj_set_pos(img_boot, 0, 0);

    cont_boot = 0;
    static uint32_t user_data = 10;
    task_Boot = lv_timer_create(update_boot_screen, 500,  &user_data);

	lv_scr_load(Tela_Boot);
}
