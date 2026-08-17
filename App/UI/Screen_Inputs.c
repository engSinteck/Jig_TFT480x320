/*
 * Screen_Inputs.c
 *
 *  Created on: 17 de ago. de 2026
 *      Author: rinaldo.santos
 */
#include "main.h"
#include "stdbool.h"
#include "lvgl.h"

#include "../App/UI/lvgl_data.h"
#include "../App/UI/Screen_Inputs.h"
#include "../App/UI/Screen_Main.h"

void create_button_back_main(void);

static lv_obj_t * img_fundo = NULL;
static lv_obj_t * bt_backmain = NULL;

static lv_timer_t * task_Inputs = NULL;

void Update_Screen_Inputs(lv_timer_t * timer)
{

}

static void screen_main_lifecycle_event_cb(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);
    static uint32_t user_data = 10;

    if(code == LV_EVENT_SCREEN_LOADED) {
        // Cria o timer apenas quando a tela entra de fato no display
        if(task_Inputs == NULL) {
        	task_Inputs = lv_timer_create(Update_Screen_Inputs, 33, &user_data);
        }
    }
    else if(code == LV_EVENT_SCREEN_UNLOADED) {
        // Deleta o timer e limpa o ponteiro quando a tela sai
        if(task_Inputs != NULL) {
            lv_timer_delete(task_Inputs);
            task_Inputs = NULL;
        }
        Tela_Inputs = NULL; // Ponteiro limpo (objeto já deletado pelo auto_del)
    }
}

void Screen_Inputs_Create(void)
{
	if(Tela_Inputs != NULL) return; // Evita duplicar se já existir

	Tela_Inputs = lv_obj_create(NULL);
	lv_obj_clear_flag(Tela_Inputs, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLLABLE);
	lv_obj_set_style_bg_color(Tela_Inputs, lv_color_hex(0x000000), 0);
	lv_obj_set_style_bg_grad_color(Tela_Inputs, lv_color_hex(0x000000), 0);

    // Registra os callbacks de ciclo de vida
    lv_obj_add_event_cb(Tela_Inputs, screen_main_lifecycle_event_cb, LV_EVENT_ALL, NULL);

	// Imagem de Fundo
	img_fundo = lv_img_create(Tela_Inputs);
	lv_img_set_src(img_fundo, "S:/INPUTS/TELA_FUNDO.bin");
	lv_obj_set_pos(img_fundo, 0, 0);

	// Buttons Back/Main
	create_button_back_main();
}

static void event_bt_back_main(lv_event_t * e)
{
	if(lv_event_get_code(e) == LV_EVENT_CLICKED) {
		// Cria a próxima tela antes de carregar
		Screen_Main_Create();
		// auto_del = true vai deletar a Tela_Main automaticamente ao fim da animação
		lv_screen_load_anim(Tela_Main, LV_SCREEN_LOAD_ANIM_MOVE_LEFT, 500, 10, true);
	}
}

void create_button_back_main(void)
{
    // Button BACK/MAIN
    bt_backmain = lv_imagebutton_create(Tela_Inputs);
    lv_imagebutton_set_src(bt_backmain, LV_IMAGEBUTTON_STATE_RELEASED, NULL, "S:/INPUTS/BT_BACKMAIN.bin", NULL);
    lv_imagebutton_set_src(bt_backmain, LV_IMAGEBUTTON_STATE_PRESSED, NULL, "S:/INPUTS/BT_BACKMAIN_P.bin", NULL);
    lv_imagebutton_set_src(bt_backmain, LV_IMAGEBUTTON_STATE_DISABLED, NULL, "S:/INPUTS/BT_BACKMAIN.bin", NULL);
    lv_imagebutton_set_src(bt_backmain, LV_IMAGEBUTTON_STATE_CHECKED_PRESSED, NULL, "S:/INPUTS/BT_BACKMAIN_P.bin", NULL);
    lv_imagebutton_set_src(bt_backmain, LV_IMAGEBUTTON_STATE_CHECKED_RELEASED, NULL, "S:/INPUTS/BT_BACKMAIN.bin", NULL);
    lv_imagebutton_set_src(bt_backmain, LV_IMAGEBUTTON_STATE_CHECKED_DISABLED, NULL, "S:/INPUTS/BT_BACKMAIN.bin", NULL);
    lv_obj_add_state(bt_backmain, LV_IMAGEBUTTON_STATE_RELEASED);
    lv_obj_set_pos(bt_backmain, 2, 93);
    lv_obj_add_event_cb(bt_backmain, event_bt_back_main, LV_EVENT_ALL, NULL);
}
