/*
 * Screen_Main.c
 *
 *  Created on: 14 de ago. de 2026
 *      Author: rinaldo.santos
 */

#include "main.h"
#include "stdbool.h"
#include "lvgl.h"
#include "rng.h"
#include "stdio.h"
#include "string.h"

#include "../App/UI/Screen_Main.h"
#include "../App/UI/led_ring.h"

extern void create_vumeter_left(void);
extern void create_vumeter_right(void);
extern void set_vumeter_left(int32_t value);
extern void set_vumeter_right(int32_t value);

void create_fm_symbol(void);
void create_text_lr(void);
void create_tuned(void);
void create_stereo(void);
void create_rds(void);
void create_buttons_tunner(void);
void create_buttons_volume(void);
void create_buttons_menu_1(void);
void create_buttons_menu_2(void);
//void create_vumeter_left(void);
//void create_vumeter_right(void);
void create_vumeter_xlr(void);
void create_vumeter_aes(void);
void create_vumeter_pc(void);
void create_vumeter_tunner(void);
void create_vumeter_usb(void);
void create_vumeter_mpx(void);
void create_Label_RDS(void);
void create_Label_Frequency(int32_t frequency);
void create_text_audio_source(void);
void create_text_scale_vu(void);
void create_leds_volume(void);
void formatar_frequencia(int32_t valor, char *resultado, size_t tamanho);
void create_img_button_volume(void);

LV_FONT_DECLARE(Neue_Medium_10);
LV_FONT_DECLARE(Neue_Medium_11);
LV_FONT_DECLARE(Neue_Medium_12);
LV_FONT_DECLARE(Neue_Medium_14);
LV_FONT_DECLARE(Neue_Medium_16);
LV_FONT_DECLARE(Neue_Medium_18);
LV_FONT_DECLARE(Neue_Medium_20);
LV_FONT_DECLARE(Neue_Medium_52);
LV_FONT_DECLARE(Neue_MediumItalic_14);

LV_IMG_DECLARE(LED_GR_OFF);
LV_IMG_DECLARE(LED_GR);
LV_IMG_DECLARE(KNOB_ON);
LV_IMG_DECLARE(KNOB_OFF);
LV_IMG_DECLARE(LED);
LV_IMG_DECLARE(LED_OFF);
LV_IMG_DECLARE(KNOB_CENTRAL);
LV_IMG_DECLARE(PHONE);
LV_IMG_DECLARE(BT_INDIC);

lv_obj_t * Tela_Main;
static lv_obj_t * img_fundo;
static lv_obj_t * bt_rev;
static lv_obj_t * bt_next;
static lv_obj_t * bt_prevff;
static lv_obj_t * bt_nextff;
static lv_obj_t * bt_vol_inc;
static lv_obj_t * bt_vol_dec;
static lv_obj_t * bt_menu[5];
static lv_obj_t * bt_inputs;
static lv_obj_t * bt_outputs;
static lv_obj_t * bt_configs;
static lv_obj_t * label_rds;
static lv_obj_t * label_frequency;
static lv_obj_t * label_scale[8];
//static lv_obj_t * vu_left;
//static lv_obj_t * vu_right;
static lv_obj_t * vu_xlr_l;
static lv_obj_t * vu_xlr_r;
static lv_obj_t * vu_aes_l;
static lv_obj_t * vu_aes_r;
static lv_obj_t * vu_pc_l;
static lv_obj_t * vu_pc_r;
static lv_obj_t * vu_tuner_l;
static lv_obj_t * vu_tuner_r;
static lv_obj_t * vu_usb_l;
static lv_obj_t * vu_usb_r;
static lv_obj_t * vu_mpx_1;
static lv_obj_t * vu_mpx_2;

static lv_timer_t * task_Main;

static uint32_t cont_main = 0;

uint8_t flag_vumeter_lr = 0;
uint32_t demo_vumeter_lr = 0;

uint8_t flag_vu_xlr = 0;
uint32_t demo_vu_xlr = 0;

uint8_t flag_vu_aes = 1;
uint32_t demo_vu_aes = 12;

uint8_t flag_vu_pc = 0;
uint32_t demo_vu_pc = 0;

static int32_t fm_frequency = 104100;	// Escala de 76.000 - 108.100 MHz
char str_freq[20] = {0};

uint8_t ObterNumeroAleatorio0a13(void)
{
    uint32_t valor_raw = 0;

    // Gera um número aleatório de 32 bits usando o hardware RNG
    if (HAL_RNG_GenerateRandomNumber(&hrng, &valor_raw) == HAL_OK) {
        // Restringe o valor para a faixa de 0 a 13 (14 valores possíveis)
        return (uint8_t)(valor_raw % 14);
    }

    return 0; // Retorno de segurança em caso de erro no periférico
}


uint32_t Gerar_Aleatorio_0_64(void)
{
    uint32_t valor_32bit = 0;

    // Solicita um número aleatório de hardware de 32 bits
    if (HAL_RNG_GenerateRandomNumber(&hrng, &valor_32bit) == HAL_OK)
    {
        // Restringe o valor para a faixa de 0 até 64 (65 possibilidades)
        return (valor_32bit % 65);
    }

    return 0; // Retorno padrão em caso de erro no periférico
}

void update_main_screen(lv_timer_t * timer)
{

	// Vu-Meter Left+Right
	if(!flag_vumeter_lr) {
		demo_vumeter_lr++;
		if(demo_vumeter_lr > 64) flag_vumeter_lr = 1;
	}
	else {
		if(demo_vumeter_lr >= 1) {
			demo_vumeter_lr--;
		}
		else flag_vumeter_lr = 0;
	}

	uint32_t val_left = Gerar_Aleatorio_0_64();
	set_vumeter_left(val_left);
	set_vumeter_right(val_left);

	// Vu-Meter XLR
	if( !flag_vu_xlr) {
		demo_vu_xlr++;
		if(demo_vu_xlr > 13) flag_vu_xlr = 1;
	}
	else {
		if(demo_vu_xlr >= 1) {
			demo_vu_xlr--;
		}
		else flag_vu_xlr = 0;
	}
	lv_slider_set_value(vu_xlr_l, demo_vu_xlr, LV_ANIM_OFF);
	lv_slider_set_value(vu_xlr_r, demo_vu_xlr, LV_ANIM_OFF);
	lv_slider_set_value(vu_mpx_1, demo_vu_xlr, LV_ANIM_OFF);
	lv_slider_set_value(vu_mpx_2, demo_vu_xlr, LV_ANIM_OFF);


	// Vu-Meter AES
	if( !flag_vu_aes) {
		demo_vu_aes++;
		if(demo_vu_aes > 13) flag_vu_aes = 1;
	}
	else {
		if(demo_vu_aes >= 1) {
			demo_vu_aes--;
		}
		else flag_vu_aes = 0;
	}
	lv_slider_set_value(vu_aes_l, demo_vu_aes, LV_ANIM_OFF);
	lv_slider_set_value(vu_aes_r, demo_vu_aes, LV_ANIM_OFF);
	lv_slider_set_value(vu_usb_l, demo_vu_aes, LV_ANIM_OFF);
	lv_slider_set_value(vu_usb_r, demo_vu_aes, LV_ANIM_OFF);

	// Vu-Meter PC
	uint8_t val = ObterNumeroAleatorio0a13();

	lv_slider_set_value(vu_pc_l, val, LV_ANIM_OFF);
	lv_slider_set_value(vu_pc_r, val, LV_ANIM_OFF);
	lv_slider_set_value(vu_tuner_l, val, LV_ANIM_OFF);
	lv_slider_set_value(vu_tuner_r, val, LV_ANIM_OFF);
}

void Screen_Main(void)
{
	Tela_Main = lv_obj_create(NULL);
	lv_obj_clear_flag(Tela_Main, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLLABLE);
	lv_obj_set_style_bg_color(Tela_Main, lv_color_hex(0x000000), 0);
	lv_obj_set_style_bg_grad_color(Tela_Main, lv_color_hex(0x000000), 0);

	// Imagem de Fundo
	img_fundo = lv_img_create(Tela_Main);
	lv_img_set_src(img_fundo, "S:/MAIN/TELA_FUNDO_MAIN.bin");
	lv_obj_set_pos(img_fundo, 0, 0);

	// Create FM Symbol
	create_fm_symbol();

	// Create Text L + R
	create_text_lr();

	// Create Tuned
	create_tuned();
	// Create Stereo
	create_stereo();
	// Create RDS
	create_rds();
	// Buttons Volume
	create_buttons_volume();
	// Buttons Menu
	create_buttons_menu_1();
	create_buttons_menu_2();
	// Vu-Meter L+R
	create_vumeter_left();
	create_vumeter_right();
	create_vumeter_xlr();
	create_vumeter_aes();
	create_vumeter_pc();
	create_vumeter_tunner();
	create_vumeter_usb();
	create_vumeter_mpx();
	// Label RDS
	create_Label_RDS();
	// Label Frequency
	create_Label_Frequency(fm_frequency);
	// Text Audio Source
	create_text_audio_source();
	// Text Scale VU
	create_text_scale_vu();
	// Knob Volume
	led_ring_create(Tela_Main);
	// Buttons Tunner
	create_buttons_tunner();
	// Phone + BT Indicador
	create_img_button_volume();

    cont_main = 0;
    static uint32_t user_data = 10;
    task_Main = lv_timer_create(update_main_screen, 30,  &user_data);

	lv_scr_load(Tela_Main);
}

void create_fm_symbol(void)
{
	// FM Symbol
	lv_obj_t * img_fm = lv_img_create(Tela_Main);
	lv_img_set_src(img_fm, "S:/MAIN/IMG_FM.bin");
	lv_obj_set_pos(img_fm, 8, 8);
	//
    lv_obj_t * text_fm = lv_label_create(img_fm);
    lv_obj_set_width(text_fm, LV_SIZE_CONTENT);
    lv_obj_set_height(text_fm, LV_SIZE_CONTENT);
    lv_label_set_text(text_fm, "FM");
    lv_obj_set_style_text_color(text_fm, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(text_fm, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(text_fm, &Neue_MediumItalic_14, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_align_to(text_fm, img_fm, LV_ALIGN_CENTER, 0, 0);
}

void create_text_lr(void)
{
	// Text L + R
    lv_obj_t * text_L = lv_label_create(Tela_Main);
    lv_obj_set_width(text_L, LV_SIZE_CONTENT);
    lv_obj_set_height(text_L, LV_SIZE_CONTENT);
    lv_label_set_text(text_L, "L");
    lv_obj_set_style_text_color(text_L, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(text_L, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(text_L, &Neue_Medium_20, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(text_L, 10, 232);

    lv_obj_t * text_R = lv_label_create(Tela_Main);
    lv_obj_set_width(text_R, LV_SIZE_CONTENT);
    lv_obj_set_height(text_R, LV_SIZE_CONTENT);
    lv_label_set_text(text_R, "R");
    lv_obj_set_style_text_color(text_R, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(text_R, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(text_R, &Neue_Medium_20, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(text_R, 10, 262);
}

void create_tuned(void)
{
	// TUNED Symbol
	lv_obj_t * img_tuned = lv_img_create(Tela_Main);
	lv_img_set_src(img_tuned, "S:/MAIN/BT_TUNED.bin");
	lv_obj_set_pos(img_tuned, 332, 8);

	// Text
    lv_obj_t * text_tuned = lv_label_create(img_tuned);
    lv_obj_set_width(text_tuned, LV_SIZE_CONTENT);
    lv_obj_set_height(text_tuned, LV_SIZE_CONTENT);
    lv_label_set_text(text_tuned, "TUNED");
    lv_obj_set_style_text_color(text_tuned, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(text_tuned, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(text_tuned, &Neue_Medium_10, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_align_to(text_tuned, img_tuned, LV_ALIGN_CENTER, 0, 0);
}

void create_stereo(void)
{
	// STEREO Symbol
	lv_obj_t * img_stereo = lv_img_create(Tela_Main);
	lv_img_set_src(img_stereo, "S:/MAIN/BT_STEREO.bin");
	lv_obj_set_pos(img_stereo, 330, 38);

	// Text
    lv_obj_t * text_stereo = lv_label_create(img_stereo);
    lv_obj_set_width(text_stereo, LV_SIZE_CONTENT);
    lv_obj_set_height(text_stereo, LV_SIZE_CONTENT);
    lv_label_set_text(text_stereo, "STEREO");
    lv_obj_set_style_text_color(text_stereo, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(text_stereo, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(text_stereo, &Neue_Medium_10, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_align_to(text_stereo, img_stereo, LV_ALIGN_CENTER, 0, 0);
}

void create_rds(void)
{
	// RDS Symbol
	lv_obj_t * img_rds = lv_img_create(Tela_Main);
	lv_img_set_src(img_rds, "S:/MAIN/BT_RDS.bin");
	lv_obj_set_pos(img_rds, 332, 66);

	// Text
    lv_obj_t * text_rds = lv_label_create(img_rds);
    lv_obj_set_width(text_rds, LV_SIZE_CONTENT);
    lv_obj_set_height(text_rds, LV_SIZE_CONTENT);
    lv_label_set_text(text_rds, "RDS");
    lv_obj_set_style_text_color(text_rds, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(text_rds, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(text_rds, &Neue_Medium_10, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_align_to(text_rds, img_rds, LV_ALIGN_CENTER, 0, 1);
}

static void event_bt_next(lv_event_t * e)
{
	lv_event_code_t code = lv_event_get_code(e);

	if(code == LV_EVENT_CLICKED || code == LV_EVENT_LONG_PRESSED_REPEAT) {
		 if(fm_frequency < 108100) {
			 fm_frequency += 100; // Incrementa de 100
			 formatar_frequencia(fm_frequency, str_freq, sizeof(str_freq));
			 lv_label_set_text_fmt(label_frequency, str_freq);
		 }
	 }
}

static void event_bt_rev(lv_event_t * e)
{
	lv_event_code_t code = lv_event_get_code(e);

	if(code == LV_EVENT_CLICKED || code == LV_EVENT_LONG_PRESSED_REPEAT) {
		 if(fm_frequency > 76000) {
			 fm_frequency -= 100; // Decrementa de 100
			 formatar_frequencia(fm_frequency, str_freq, sizeof(str_freq));
			 lv_label_set_text_fmt(label_frequency, str_freq);
		 }
	 }
}

static void event_bt_nextff(lv_event_t * e)
{
	lv_event_code_t code = lv_event_get_code(e);

	if(code == LV_EVENT_CLICKED || code == LV_EVENT_LONG_PRESSED_REPEAT) {
		 if(fm_frequency < 108100) {
			 fm_frequency += 1000; // Incrementa de 1000
			 formatar_frequencia(fm_frequency, str_freq, sizeof(str_freq));
			 lv_label_set_text_fmt(label_frequency, str_freq);
		 }
	 }
}

static void event_bt_prevff(lv_event_t * e)
{
	lv_event_code_t code = lv_event_get_code(e);

	 if(code == LV_EVENT_CLICKED || code == LV_EVENT_LONG_PRESSED_REPEAT) {
		 if(fm_frequency > 76000) {
			 fm_frequency -= 1000; // Decrementa de 1000
			 formatar_frequencia(fm_frequency, str_freq, sizeof(str_freq));
			 lv_label_set_text_fmt(label_frequency, str_freq);
		 }
	 }
}

void create_buttons_tunner(void)
{
    // Button PREV
    bt_rev = lv_imagebutton_create(Tela_Main);
    lv_imagebutton_set_src(bt_rev, LV_IMAGEBUTTON_STATE_RELEASED, NULL, "S:/MAIN/BT_RR.bin", NULL);
    lv_imagebutton_set_src(bt_rev, LV_IMAGEBUTTON_STATE_PRESSED, NULL, "S:/MAIN/BT_RR_P.bin", NULL);
    lv_imagebutton_set_src(bt_rev, LV_IMAGEBUTTON_STATE_DISABLED, NULL, "S:/MAIN/BT_RR.bin", NULL);
    lv_imagebutton_set_src(bt_rev, LV_IMAGEBUTTON_STATE_CHECKED_PRESSED, NULL, "S:/MAIN/BT_RR_P.bin", NULL);
    lv_imagebutton_set_src(bt_rev, LV_IMAGEBUTTON_STATE_CHECKED_RELEASED, NULL, "S:/MAIN/BT_RR.bin", NULL);
    lv_imagebutton_set_src(bt_rev, LV_IMAGEBUTTON_STATE_CHECKED_DISABLED, NULL, "S:/MAIN/BT_RR.bin", NULL);
    lv_obj_add_state(bt_rev, LV_IMAGEBUTTON_STATE_RELEASED);
    lv_obj_set_pos(bt_rev, 384, 10);
    lv_obj_add_event_cb(bt_rev, event_bt_rev, LV_EVENT_ALL, NULL);

    // Button NEXT
    bt_next = lv_imagebutton_create(Tela_Main);
    lv_imagebutton_set_src(bt_next, LV_IMAGEBUTTON_STATE_RELEASED, NULL, "S:/MAIN/BT_FW.bin", NULL);
    lv_imagebutton_set_src(bt_next, LV_IMAGEBUTTON_STATE_PRESSED, NULL, "S:/MAIN/BT_FW_P.bin", NULL);
    lv_imagebutton_set_src(bt_next, LV_IMAGEBUTTON_STATE_DISABLED, NULL, "S:/MAIN/BT_FW.bin", NULL);
    lv_imagebutton_set_src(bt_next, LV_IMAGEBUTTON_STATE_CHECKED_PRESSED, NULL, "S:/MAIN/BT_FW_P.bin", NULL);
    lv_imagebutton_set_src(bt_next, LV_IMAGEBUTTON_STATE_CHECKED_RELEASED, NULL, "S:/MAIN/BT_FW.bin", NULL);
    lv_imagebutton_set_src(bt_next, LV_IMAGEBUTTON_STATE_CHECKED_DISABLED, NULL, "S:/MAIN/BT_FW.bin", NULL);
    lv_obj_add_state(bt_next, LV_IMAGEBUTTON_STATE_RELEASED);
    lv_obj_set_pos(bt_next, 432, 10);
    lv_obj_add_event_cb(bt_next, event_bt_next, LV_EVENT_ALL, NULL);

    // Button REV FF
    bt_prevff = lv_imagebutton_create(Tela_Main);
    lv_imagebutton_set_src(bt_prevff, LV_IMAGEBUTTON_STATE_RELEASED, NULL, "S:/MAIN/BT_RW.bin", NULL);
    lv_imagebutton_set_src(bt_prevff, LV_IMAGEBUTTON_STATE_PRESSED, NULL, "S:/MAIN/BT_RW_P.bin", NULL);
    lv_imagebutton_set_src(bt_prevff, LV_IMAGEBUTTON_STATE_DISABLED, NULL, "S:/MAIN/BT_RW.bin", NULL);
    lv_imagebutton_set_src(bt_prevff, LV_IMAGEBUTTON_STATE_CHECKED_PRESSED, NULL, "S:/MAIN/BT_RW_P.bin", NULL);
    lv_imagebutton_set_src(bt_prevff, LV_IMAGEBUTTON_STATE_CHECKED_RELEASED, NULL, "S:/MAIN/BT_RW.bin", NULL);
    lv_imagebutton_set_src(bt_prevff, LV_IMAGEBUTTON_STATE_CHECKED_DISABLED, NULL, "S:/MAIN/BT_RW.bin", NULL);
    lv_obj_add_state(bt_prevff, LV_IMAGEBUTTON_STATE_RELEASED);
    lv_obj_set_pos(bt_prevff, 384, 50);
    lv_obj_add_event_cb(bt_prevff, event_bt_prevff, LV_EVENT_ALL, NULL);

    // Button REV FF
    bt_nextff = lv_imagebutton_create(Tela_Main);
    lv_imagebutton_set_src(bt_nextff, LV_IMAGEBUTTON_STATE_RELEASED, NULL, "S:/MAIN/BT_FF.bin", NULL);
    lv_imagebutton_set_src(bt_nextff, LV_IMAGEBUTTON_STATE_PRESSED, NULL, "S:/MAIN/BT_FF_P.bin", NULL);
    lv_imagebutton_set_src(bt_nextff, LV_IMAGEBUTTON_STATE_DISABLED, NULL, "S:/MAIN/BT_FF.bin", NULL);
    lv_imagebutton_set_src(bt_nextff, LV_IMAGEBUTTON_STATE_CHECKED_PRESSED, NULL, "S:/MAIN/BT_FF_P.bin", NULL);
    lv_imagebutton_set_src(bt_nextff, LV_IMAGEBUTTON_STATE_CHECKED_RELEASED, NULL, "S:/MAIN/BT_FF.bin", NULL);
    lv_imagebutton_set_src(bt_nextff, LV_IMAGEBUTTON_STATE_CHECKED_DISABLED, NULL, "S:/MAIN/BT_FF.bin", NULL);
    lv_obj_add_state(bt_nextff, LV_IMAGEBUTTON_STATE_RELEASED);
    lv_obj_set_pos(bt_nextff, 432, 50);
    lv_obj_add_event_cb(bt_nextff, event_bt_nextff, LV_EVENT_ALL, NULL);
}

static void event_bt_vol_inc(lv_event_t * e)
{
	lv_event_code_t code = lv_event_get_code(e);

	if(code == LV_EVENT_CLICKED || code == LV_EVENT_LONG_PRESSED_REPEAT) {
		led_ring_inc();
	 }
}

static void event_bt_vol_dec(lv_event_t * e)
{
	lv_event_code_t code = lv_event_get_code(e);

	if(code == LV_EVENT_CLICKED || code == LV_EVENT_LONG_PRESSED_REPEAT) {
		led_ring_dec();
	 }
}

void create_buttons_volume(void)
{
    // Button PREV
    bt_vol_inc = lv_imagebutton_create(Tela_Main);
    lv_imagebutton_set_src(bt_vol_inc, LV_IMAGEBUTTON_STATE_RELEASED, NULL, "S:/MAIN/BT_INC.bin", NULL);
    lv_imagebutton_set_src(bt_vol_inc, LV_IMAGEBUTTON_STATE_PRESSED, NULL, "S:/MAIN/BT_INC_P.bin", NULL);
    lv_imagebutton_set_src(bt_vol_inc, LV_IMAGEBUTTON_STATE_DISABLED, NULL, "S:/MAIN/BT_INC.bin", NULL);
    lv_imagebutton_set_src(bt_vol_inc, LV_IMAGEBUTTON_STATE_CHECKED_PRESSED, NULL, "S:/MAIN/BT_INC_P.bin", NULL);
    lv_imagebutton_set_src(bt_vol_inc, LV_IMAGEBUTTON_STATE_CHECKED_RELEASED, NULL, "S:/MAIN/BT_INC.bin", NULL);
    lv_imagebutton_set_src(bt_vol_inc, LV_IMAGEBUTTON_STATE_CHECKED_DISABLED, NULL, "S:/MAIN/BT_INC.bin", NULL);
    lv_obj_add_state(bt_vol_inc, LV_IMAGEBUTTON_STATE_RELEASED);
    lv_obj_set_pos(bt_vol_inc, 384, 185);
    lv_obj_add_event_cb(bt_vol_inc, event_bt_vol_inc, LV_EVENT_ALL, NULL);

    // Button NEXT
    bt_vol_dec = lv_imagebutton_create(Tela_Main);
    lv_imagebutton_set_src(bt_vol_dec, LV_IMAGEBUTTON_STATE_RELEASED, NULL, "S:/MAIN/BT_DEC.bin", NULL);
    lv_imagebutton_set_src(bt_vol_dec, LV_IMAGEBUTTON_STATE_PRESSED, NULL, "S:/MAIN/BT_DEC_P.bin", NULL);
    lv_imagebutton_set_src(bt_vol_dec, LV_IMAGEBUTTON_STATE_DISABLED, NULL, "S:/MAIN/BT_DEC.bin", NULL);
    lv_imagebutton_set_src(bt_vol_dec, LV_IMAGEBUTTON_STATE_CHECKED_PRESSED, NULL, "S:/MAIN/BT_DEC_P.bin", NULL);
    lv_imagebutton_set_src(bt_vol_dec, LV_IMAGEBUTTON_STATE_CHECKED_RELEASED, NULL, "S:/MAIN/BT_DEC.bin", NULL);
    lv_imagebutton_set_src(bt_vol_dec, LV_IMAGEBUTTON_STATE_CHECKED_DISABLED, NULL, "S:/MAIN/BT_DEC.bin", NULL);
    lv_obj_add_state(bt_vol_dec, LV_IMAGEBUTTON_STATE_RELEASED);
    lv_obj_set_pos(bt_vol_dec, 432, 185);
    lv_obj_add_event_cb(bt_vol_dec, event_bt_vol_dec, LV_EVENT_ALL, NULL);
}

void create_buttons_menu_1(void)
{
    // Button INPUTS
    bt_inputs = lv_imagebutton_create(Tela_Main);
    lv_imagebutton_set_src(bt_inputs, LV_IMAGEBUTTON_STATE_RELEASED, NULL, "S:/MAIN/BT_INPUT.bin", NULL);
    lv_imagebutton_set_src(bt_inputs, LV_IMAGEBUTTON_STATE_PRESSED, NULL, "S:/MAIN/BT_INPUT_P.bin", NULL);
    lv_imagebutton_set_src(bt_inputs, LV_IMAGEBUTTON_STATE_DISABLED, NULL, "S:/MAIN/BT_INPUT.bin", NULL);
    lv_imagebutton_set_src(bt_inputs, LV_IMAGEBUTTON_STATE_CHECKED_PRESSED, NULL, "S:/MAIN/BT_INPUT_P.bin", NULL);
    lv_imagebutton_set_src(bt_inputs, LV_IMAGEBUTTON_STATE_CHECKED_RELEASED, NULL, "S:/MAIN/BT_INPUT.bin", NULL);
    lv_imagebutton_set_src(bt_inputs, LV_IMAGEBUTTON_STATE_CHECKED_DISABLED, NULL, "S:/MAIN/BT_INPUT.bin", NULL);
    lv_obj_add_state(bt_inputs, LV_IMAGEBUTTON_STATE_RELEASED);
    lv_obj_set_pos(bt_inputs, 2, 93);
    //lv_obj_add_event_cb(bt_inputs, event_utils_bt_back, LV_EVENT_ALL, NULL);

	// Text
    lv_obj_t * text_inputs = lv_label_create(bt_inputs);
    lv_obj_set_width(text_inputs, LV_SIZE_CONTENT);
    lv_obj_set_height(text_inputs, LV_SIZE_CONTENT);
    lv_label_set_text(text_inputs, "INPUTS");
    lv_obj_set_style_text_color(text_inputs, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(text_inputs, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(text_inputs, &Neue_Medium_16, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_align_to(text_inputs, bt_inputs, LV_ALIGN_CENTER, 0, 0);

    // Button OUTPUTS
    bt_outputs = lv_imagebutton_create(Tela_Main);
    lv_imagebutton_set_src(bt_outputs, LV_IMAGEBUTTON_STATE_RELEASED, NULL, "S:/MAIN/BT_INPUT.bin", NULL);
    lv_imagebutton_set_src(bt_outputs, LV_IMAGEBUTTON_STATE_PRESSED, NULL, "S:/MAIN/BT_INPUT_P.bin", NULL);
    lv_imagebutton_set_src(bt_outputs, LV_IMAGEBUTTON_STATE_DISABLED, NULL, "S:/MAIN/BT_INPUT.bin", NULL);
    lv_imagebutton_set_src(bt_outputs, LV_IMAGEBUTTON_STATE_CHECKED_PRESSED, NULL, "S:/MAIN/BT_INPUT_P.bin", NULL);
    lv_imagebutton_set_src(bt_outputs, LV_IMAGEBUTTON_STATE_CHECKED_RELEASED, NULL, "S:/MAIN/BT_INPUT.bin", NULL);
    lv_imagebutton_set_src(bt_outputs, LV_IMAGEBUTTON_STATE_CHECKED_DISABLED, NULL, "S:/MAIN/BT_INPUT.bin", NULL);
    lv_obj_add_state(bt_outputs, LV_IMAGEBUTTON_STATE_RELEASED);
    lv_obj_set_pos(bt_outputs, 2, 134);
    //lv_obj_add_event_cb(bt_outputs, event_utils_bt_back, LV_EVENT_ALL, NULL);

	// Text
    lv_obj_t * text_outputs = lv_label_create(bt_outputs);
    lv_obj_set_width(text_outputs, LV_SIZE_CONTENT);
    lv_obj_set_height(text_outputs, LV_SIZE_CONTENT);
    lv_label_set_text(text_outputs, "OUTPUTS");
    lv_obj_set_style_text_color(text_outputs, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(text_outputs, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(text_outputs, &Neue_Medium_16, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_align_to(text_outputs, bt_outputs, LV_ALIGN_CENTER, 0, 0);

    // Button Configs
    bt_configs = lv_imagebutton_create(Tela_Main);
    lv_imagebutton_set_src(bt_configs, LV_IMAGEBUTTON_STATE_RELEASED, NULL, "S:/MAIN/BT_INPUT.bin", NULL);
    lv_imagebutton_set_src(bt_configs, LV_IMAGEBUTTON_STATE_PRESSED, NULL, "S:/MAIN/BT_INPUT_P.bin", NULL);
    lv_imagebutton_set_src(bt_configs, LV_IMAGEBUTTON_STATE_DISABLED, NULL, "S:/MAIN/BT_INPUT.bin", NULL);
    lv_imagebutton_set_src(bt_configs, LV_IMAGEBUTTON_STATE_CHECKED_PRESSED, NULL, "S:/MAIN/BT_INPUT_P.bin", NULL);
    lv_imagebutton_set_src(bt_configs, LV_IMAGEBUTTON_STATE_CHECKED_RELEASED, NULL, "S:/MAIN/BT_INPUT.bin", NULL);
    lv_imagebutton_set_src(bt_configs, LV_IMAGEBUTTON_STATE_CHECKED_DISABLED, NULL, "S:/MAIN/BT_INPUT.bin", NULL);
    lv_obj_add_state(bt_configs, LV_IMAGEBUTTON_STATE_RELEASED);
    lv_obj_set_pos(bt_configs, 2, 175);
    //lv_obj_add_event_cb(bt_configs, event_utils_bt_back, LV_EVENT_ALL, NULL);

	// Text
    lv_obj_t * text_configs = lv_label_create(bt_configs);
    lv_obj_set_width(text_configs, LV_SIZE_CONTENT);
    lv_obj_set_height(text_configs, LV_SIZE_CONTENT);
    lv_label_set_text(text_configs, "CONFIGS");
    lv_obj_set_style_text_color(text_configs, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(text_configs, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(text_configs, &Neue_Medium_16, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_align_to(text_configs, bt_configs, LV_ALIGN_CENTER, 0, 0);
}

void create_buttons_menu_2(void)
{
    // Menu
	// Button USB_PC_FM
	for(uint8_t x = 0; x < 5; x++) {
		bt_menu[x] = lv_imagebutton_create(Tela_Main);
		lv_imagebutton_set_src(bt_menu[x], LV_IMAGEBUTTON_STATE_RELEASED, NULL, "S:/MAIN/BT_MENU.bin", NULL);
		lv_imagebutton_set_src(bt_menu[x], LV_IMAGEBUTTON_STATE_PRESSED, NULL, "S:/MAIN/BT_MENU_P.bin", NULL);
		lv_imagebutton_set_src(bt_menu[x], LV_IMAGEBUTTON_STATE_DISABLED, NULL, "S:/MAIN/BT_MENU.bin", NULL);
		lv_imagebutton_set_src(bt_menu[x], LV_IMAGEBUTTON_STATE_CHECKED_PRESSED, NULL, "S:/MAIN/BT_MENU_P.bin", NULL);
		lv_imagebutton_set_src(bt_menu[x], LV_IMAGEBUTTON_STATE_CHECKED_RELEASED, NULL, "S:/MAIN/BT_MENU.bin", NULL);
		lv_imagebutton_set_src(bt_menu[x], LV_IMAGEBUTTON_STATE_CHECKED_DISABLED, NULL, "S:/MAIN/BT_MENU.bin", NULL);
		lv_obj_add_state(bt_menu[x], LV_IMAGEBUTTON_STATE_RELEASED);
		//lv_obj_add_event_cb(bt_menu[x], event_utils_bt_back, LV_EVENT_ALL, NULL);
	}
	// Pos
	lv_obj_set_pos(bt_menu[0], 2, 286);
	lv_obj_set_pos(bt_menu[1], 97, 286);
	lv_obj_set_pos(bt_menu[2], 192, 286);
	lv_obj_set_pos(bt_menu[3], 288, 286);
	lv_obj_set_pos(bt_menu[4], 384, 286);

	// Text
    lv_obj_t * text_menu_0 = lv_label_create(bt_menu[0]);
    lv_obj_set_width(text_menu_0, LV_SIZE_CONTENT);
    lv_obj_set_height(text_menu_0, LV_SIZE_CONTENT);
    lv_label_set_text(text_menu_0, "USB PC FM");
    lv_obj_set_style_text_color(text_menu_0, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(text_menu_0, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(text_menu_0, &Neue_Medium_16, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_align_to(text_menu_0, bt_menu[0], LV_ALIGN_CENTER, 0, 1);

    lv_obj_t * text_menu_1 = lv_label_create(bt_menu[1]);
    lv_obj_set_width(text_menu_1, LV_SIZE_CONTENT);
    lv_obj_set_height(text_menu_1, LV_SIZE_CONTENT);
    lv_label_set_text(text_menu_1, "PC ADC/DAC");
    lv_obj_set_style_text_color(text_menu_1, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(text_menu_1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(text_menu_1, &Neue_Medium_14, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_align_to(text_menu_1, bt_menu[1], LV_ALIGN_CENTER, 0, 1);

    lv_obj_t * text_menu_2 = lv_label_create(bt_menu[2]);
    lv_obj_set_width(text_menu_2, LV_SIZE_CONTENT);
    lv_obj_set_height(text_menu_2, LV_SIZE_CONTENT);
    lv_label_set_text(text_menu_2, "PROCESSOR");
    lv_obj_set_style_text_color(text_menu_2, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(text_menu_2, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(text_menu_2, &Neue_Medium_14, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_align_to(text_menu_2, bt_menu[2], LV_ALIGN_CENTER, 0, 1);

    lv_obj_t * text_menu_3 = lv_label_create(bt_menu[3]);
    lv_obj_set_width(text_menu_3, LV_SIZE_CONTENT);
    lv_obj_set_height(text_menu_3, LV_SIZE_CONTENT);
    lv_label_set_text(text_menu_3, "MP3 B/T");
    lv_obj_set_style_text_color(text_menu_3, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(text_menu_3, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(text_menu_3, &Neue_Medium_14, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_align_to(text_menu_3, bt_menu[3], LV_ALIGN_CENTER, 0, 1);

    lv_obj_t * text_menu_4 = lv_label_create(bt_menu[4]);
    lv_obj_set_width(text_menu_4, LV_SIZE_CONTENT);
    lv_obj_set_height(text_menu_4, LV_SIZE_CONTENT);
    lv_label_set_text(text_menu_4, "FM TUNER");
    lv_obj_set_style_text_color(text_menu_4, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(text_menu_4, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(text_menu_4, &Neue_Medium_14, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_align_to(text_menu_4, bt_menu[4], LV_ALIGN_CENTER, 0, 1);
}

/*
void create_vumeter_left(void)
{
    vu_left = lv_slider_create(Tela_Main);
    lv_obj_clear_flag(vu_left, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLLABLE);
    lv_slider_set_range(vu_left, 0, 64);
    lv_obj_set_width(vu_left, 445);
    lv_obj_set_height(vu_left, 28);
    lv_obj_set_pos(vu_left, 31, 228);

    // --- FUNDO DO SLIDER (MAIN) ---
    lv_obj_set_style_radius(vu_left, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(vu_left, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Remove as margens internas para que o preenchimento de pixels bata com o tamanho da imagem
    lv_obj_set_style_pad_all(vu_left, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_all(vu_left, 0, LV_PART_INDICATOR | LV_STATE_DEFAULT);

    // API Estrita do LVGL 9.5 para Imagem de Fundo
    lv_obj_set_style_bg_image_src(vu_left, &LED_GR_OFF, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_image_opa(vu_left, LV_OPA_COVER, LV_PART_MAIN | LV_STATE_DEFAULT);

    // --- BARRA QUE CRESCE (INDICATOR) ---
    lv_obj_set_style_radius(vu_left, 0, LV_PART_INDICATOR | LV_STATE_DEFAULT);

    // Força o indicador a usar puramente a imagem sem misturar cor sólida por baixo
    lv_obj_set_style_bg_opa(vu_left, LV_OPA_TRANSP, LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_image_src(vu_left, &LED_GR, LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_image_opa(vu_left, LV_OPA_COVER, LV_PART_INDICATOR | LV_STATE_DEFAULT);

    // --- BOTÃO (KNOB) - ESCONDIDO ---
    lv_obj_set_style_bg_opa(vu_left, 0, LV_PART_KNOB | LV_STATE_DEFAULT);

    lv_slider_set_value(vu_left, 30, LV_ANIM_OFF);
}

void create_vumeter_right(void)
{
	 // VU-Meter
	vu_right = lv_slider_create(Tela_Main);
	lv_obj_clear_flag(vu_right, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLLABLE);
	lv_slider_set_range(vu_right, 0, 64);
	lv_obj_set_width(vu_right, 445);
	lv_obj_set_height(vu_right, 28);
	lv_obj_set_pos(vu_right, 31, 258);

    // --- FUNDO DO SLIDER (MAIN) ---
    lv_obj_set_style_radius(vu_right, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(vu_right, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Remove as margens internas para que o preenchimento de pixels bata com o tamanho da imagem
    lv_obj_set_style_pad_all(vu_right, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_all(vu_right, 0, LV_PART_INDICATOR | LV_STATE_DEFAULT);

    // API Estrita do LVGL 9.5 para Imagem de Fundo
    lv_obj_set_style_bg_image_src(vu_right, &LED_GR_OFF, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_image_opa(vu_right, LV_OPA_COVER, LV_PART_MAIN | LV_STATE_DEFAULT);

    // --- BARRA QUE CRESCE (INDICATOR) ---
    lv_obj_set_style_radius(vu_right, 0, LV_PART_INDICATOR | LV_STATE_DEFAULT);

    // Força o indicador a usar puramente a imagem sem misturar cor sólida por baixo
    lv_obj_set_style_bg_opa(vu_right, LV_OPA_TRANSP, LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_image_src(vu_right, &LED_GR, LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_image_opa(vu_right, LV_OPA_COVER, LV_PART_INDICATOR | LV_STATE_DEFAULT);

    // --- BOTÃO (KNOB) - ESCONDIDO ---
    lv_obj_set_style_bg_opa(vu_right, 0, LV_PART_KNOB | LV_STATE_DEFAULT);

    lv_slider_set_value(vu_right, 50, LV_ANIM_OFF);
}
*/

void create_vumeter_xlr(void)
{
	// VU-Meter XLR
	vu_xlr_l = lv_slider_create(Tela_Main);
	lv_obj_clear_flag(vu_xlr_l, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLLABLE);
	lv_slider_set_range(vu_xlr_l, 0, 13);
	lv_obj_set_width(vu_xlr_l, 21);
	lv_obj_set_height(vu_xlr_l, 84);
	lv_obj_set_pos(vu_xlr_l, 100, 126);

	lv_obj_set_style_radius(vu_xlr_l, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(vu_xlr_l, lv_color_hex(0xFFFF00), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(vu_xlr_l, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_main_stop(vu_xlr_l, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_stop(vu_xlr_l, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(vu_xlr_l, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(vu_xlr_l, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(vu_xlr_l, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(vu_xlr_l, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(vu_xlr_l, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_img_src(vu_xlr_l, &LED_OFF, LV_PART_MAIN | LV_STATE_DEFAULT);

	lv_obj_set_style_radius(vu_xlr_l, 0, LV_PART_INDICATOR | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(vu_xlr_l, lv_color_hex(0xFFFFFF), LV_PART_INDICATOR | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(vu_xlr_l, 255, LV_PART_INDICATOR | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_main_stop(vu_xlr_l, 0, LV_PART_INDICATOR | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_stop(vu_xlr_l, 255, LV_PART_INDICATOR | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_img_src(vu_xlr_l, &LED, LV_PART_INDICATOR | LV_STATE_DEFAULT);

	lv_obj_set_style_bg_color(vu_xlr_l, lv_color_hex(0xFFFFFF), LV_PART_KNOB | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(vu_xlr_l, 0, LV_PART_KNOB | LV_STATE_DEFAULT);

	lv_slider_set_value(vu_xlr_l, 4, LV_ANIM_OFF);

	// Right
	vu_xlr_r = lv_slider_create(Tela_Main);
	lv_obj_clear_flag(vu_xlr_r, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLLABLE);
	lv_slider_set_range(vu_xlr_r, 0, 13);
	lv_obj_set_width(vu_xlr_r, 21);
	lv_obj_set_height(vu_xlr_r, 84);
	lv_obj_set_pos(vu_xlr_r, 123, 126);

	lv_obj_set_style_radius(vu_xlr_r, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(vu_xlr_r, lv_color_hex(0xFFFF00), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(vu_xlr_r, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_main_stop(vu_xlr_r, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_stop(vu_xlr_r, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(vu_xlr_r, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(vu_xlr_r, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(vu_xlr_r, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(vu_xlr_r, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(vu_xlr_r, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_img_src(vu_xlr_r, &LED_OFF, LV_PART_MAIN | LV_STATE_DEFAULT);

	lv_obj_set_style_radius(vu_xlr_r, 0, LV_PART_INDICATOR | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(vu_xlr_r, lv_color_hex(0xFFFFFF), LV_PART_INDICATOR | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(vu_xlr_r, 0, LV_PART_INDICATOR | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_main_stop(vu_xlr_r, 0, LV_PART_INDICATOR | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_stop(vu_xlr_r, 255, LV_PART_INDICATOR | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_img_src(vu_xlr_r, &LED, LV_PART_INDICATOR | LV_STATE_DEFAULT);

	lv_obj_set_style_bg_color(vu_xlr_r, lv_color_hex(0xFFFFFF), LV_PART_KNOB | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(vu_xlr_r, 0, LV_PART_KNOB | LV_STATE_DEFAULT);

	lv_slider_set_value(vu_xlr_r, 4, LV_ANIM_OFF);
}

void create_vumeter_aes(void)
{
	// VU-Meter AES
	vu_aes_l = lv_slider_create(Tela_Main);
	lv_obj_clear_flag(vu_aes_l, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLLABLE);
	lv_slider_set_range(vu_aes_l, 0, 13);
	lv_obj_set_width(vu_aes_l, 21);
	lv_obj_set_height(vu_aes_l, 84);
	lv_obj_set_pos(vu_aes_l, 147, 126);

	lv_obj_set_style_radius(vu_aes_l, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(vu_aes_l, lv_color_hex(0xFF0000), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(vu_aes_l, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_main_stop(vu_aes_l, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_stop(vu_aes_l, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(vu_aes_l, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(vu_aes_l, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(vu_aes_l, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(vu_aes_l, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(vu_aes_l, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_img_src(vu_aes_l, &LED_OFF, LV_PART_MAIN | LV_STATE_DEFAULT);

	lv_obj_set_style_radius(vu_aes_l, 0, LV_PART_INDICATOR | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(vu_aes_l, lv_color_hex(0xFFFFFF), LV_PART_INDICATOR | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(vu_aes_l, 0, LV_PART_INDICATOR | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_main_stop(vu_aes_l, 0, LV_PART_INDICATOR | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_stop(vu_aes_l, 255, LV_PART_INDICATOR | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_img_src(vu_aes_l, &LED, LV_PART_INDICATOR | LV_STATE_DEFAULT);

	lv_obj_set_style_bg_color(vu_aes_l, lv_color_hex(0xFFFFFF), LV_PART_KNOB | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(vu_aes_l, 0, LV_PART_KNOB | LV_STATE_DEFAULT);

	lv_slider_set_value(vu_aes_l, 7, LV_ANIM_OFF);

	// Right
	vu_aes_r = lv_slider_create(Tela_Main);
	lv_obj_clear_flag(vu_aes_r, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLLABLE);
	lv_slider_set_range(vu_aes_r, 0, 13);
	lv_obj_set_width(vu_aes_r, 21);
	lv_obj_set_height(vu_aes_r, 84);
	lv_obj_set_pos(vu_aes_r, 170, 126);

	lv_obj_set_style_radius(vu_aes_r, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(vu_aes_r, lv_color_hex(0xFF0000), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(vu_aes_r, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_main_stop(vu_aes_r, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_stop(vu_aes_r, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(vu_aes_r, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(vu_aes_r, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(vu_aes_r, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(vu_aes_r, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(vu_aes_r, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_img_src(vu_aes_r, &LED_OFF, LV_PART_MAIN | LV_STATE_DEFAULT);

	lv_obj_set_style_radius(vu_aes_r, 0, LV_PART_INDICATOR | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(vu_aes_r, lv_color_hex(0xFFFFFF), LV_PART_INDICATOR | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(vu_aes_r, 0, LV_PART_INDICATOR | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_main_stop(vu_aes_r, 0, LV_PART_INDICATOR | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_stop(vu_aes_r, 255, LV_PART_INDICATOR | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_img_src(vu_aes_r, &LED, LV_PART_INDICATOR | LV_STATE_DEFAULT);

	lv_obj_set_style_bg_color(vu_aes_r, lv_color_hex(0xFFFFFF), LV_PART_KNOB | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(vu_aes_r, 0, LV_PART_KNOB | LV_STATE_DEFAULT);

	lv_slider_set_value(vu_aes_r, 7, LV_ANIM_OFF);
}

void create_vumeter_pc(void)
{
	// VU-Meter PC
	vu_pc_l = lv_slider_create(Tela_Main);
	lv_obj_clear_flag(vu_pc_l, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLLABLE);
	lv_slider_set_range(vu_pc_l, 0, 13);
	lv_obj_set_width(vu_pc_l, 21);
	lv_obj_set_height(vu_pc_l, 84);
	lv_obj_set_pos(vu_pc_l, 194, 126);

	lv_obj_set_style_radius(vu_pc_l, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(vu_pc_l, lv_color_hex(0x00FF00), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(vu_pc_l, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_main_stop(vu_pc_l, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_stop(vu_pc_l, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(vu_pc_l, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(vu_pc_l, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(vu_pc_l, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(vu_pc_l, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(vu_pc_l, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_img_src(vu_pc_l, &LED_OFF, LV_PART_MAIN | LV_STATE_DEFAULT);

	lv_obj_set_style_radius(vu_pc_l, 0, LV_PART_INDICATOR | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(vu_pc_l, lv_color_hex(0xFFFFFF), LV_PART_INDICATOR | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(vu_pc_l, 0, LV_PART_INDICATOR | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_main_stop(vu_pc_l, 0, LV_PART_INDICATOR | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_stop(vu_pc_l, 255, LV_PART_INDICATOR | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_img_src(vu_pc_l, &LED, LV_PART_INDICATOR | LV_STATE_DEFAULT);

	lv_obj_set_style_bg_color(vu_pc_l, lv_color_hex(0xFFFFFF), LV_PART_KNOB | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(vu_pc_l, 0, LV_PART_KNOB | LV_STATE_DEFAULT);

	lv_slider_set_value(vu_pc_l, 13, LV_ANIM_OFF);

	// Right
	vu_pc_r = lv_slider_create(Tela_Main);
	lv_obj_clear_flag(vu_pc_r, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLLABLE);
	lv_slider_set_range(vu_pc_r, 0, 13);
	lv_obj_set_width(vu_pc_r, 21);
	lv_obj_set_height(vu_pc_r, 84);
	lv_obj_set_pos(vu_pc_r, 217, 126);

	lv_obj_set_style_radius(vu_pc_r, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(vu_pc_r, lv_color_hex(0x00FF00), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(vu_pc_r, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_main_stop(vu_pc_r, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_stop(vu_pc_r, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(vu_pc_r, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(vu_pc_r, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(vu_pc_r, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(vu_pc_r, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(vu_pc_r, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_img_src(vu_pc_r, &LED_OFF, LV_PART_MAIN | LV_STATE_DEFAULT);

	lv_obj_set_style_radius(vu_pc_r, 0, LV_PART_INDICATOR | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(vu_pc_r, lv_color_hex(0xFFFFFF), LV_PART_INDICATOR | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(vu_pc_r, 0, LV_PART_INDICATOR | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_main_stop(vu_pc_r, 0, LV_PART_INDICATOR | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_stop(vu_pc_r, 255, LV_PART_INDICATOR | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_img_src(vu_pc_r, &LED, LV_PART_INDICATOR | LV_STATE_DEFAULT);

	lv_obj_set_style_bg_color(vu_pc_r, lv_color_hex(0xFFFFFF), LV_PART_KNOB | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(vu_pc_r, 0, LV_PART_KNOB | LV_STATE_DEFAULT);

	lv_slider_set_value(vu_pc_r, 13, LV_ANIM_OFF);
}

void create_vumeter_tunner(void)
{
	// VU-Meter TUNNER
	vu_tuner_l = lv_slider_create(Tela_Main);
	lv_obj_clear_flag(vu_tuner_l, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLLABLE);
	lv_slider_set_range(vu_tuner_l, 0, 13);
	lv_obj_set_width(vu_tuner_l, 21);
	lv_obj_set_height(vu_tuner_l, 84);
	lv_obj_set_pos(vu_tuner_l, 241, 126);

	lv_obj_set_style_radius(vu_tuner_l, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(vu_tuner_l, lv_color_hex(0x0000FF), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(vu_tuner_l, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_main_stop(vu_tuner_l, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_stop(vu_tuner_l, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(vu_tuner_l, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(vu_tuner_l, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(vu_tuner_l, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(vu_tuner_l, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(vu_tuner_l, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_img_src(vu_tuner_l, &LED_OFF, LV_PART_MAIN | LV_STATE_DEFAULT);

	lv_obj_set_style_radius(vu_tuner_l, 0, LV_PART_INDICATOR | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(vu_tuner_l, lv_color_hex(0xFFFFFF), LV_PART_INDICATOR | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(vu_tuner_l, 0, LV_PART_INDICATOR | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_main_stop(vu_tuner_l, 0, LV_PART_INDICATOR | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_stop(vu_tuner_l, 255, LV_PART_INDICATOR | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_img_src(vu_tuner_l, &LED, LV_PART_INDICATOR | LV_STATE_DEFAULT);

	lv_obj_set_style_bg_color(vu_tuner_l, lv_color_hex(0xFFFFFF), LV_PART_KNOB | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(vu_tuner_l, 0, LV_PART_KNOB | LV_STATE_DEFAULT);

	lv_slider_set_value(vu_tuner_l, 10, LV_ANIM_OFF);

	// Right
	vu_tuner_r = lv_slider_create(Tela_Main);
	lv_obj_clear_flag(vu_tuner_r, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLLABLE);
	lv_slider_set_range(vu_tuner_r, 0, 13);
	lv_obj_set_width(vu_tuner_r, 21);
	lv_obj_set_height(vu_tuner_r, 84);
	lv_obj_set_pos(vu_tuner_r, 264, 126);

	lv_obj_set_style_radius(vu_tuner_r, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(vu_tuner_r, lv_color_hex(0x0000FF), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(vu_tuner_r, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_main_stop(vu_tuner_r, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_stop(vu_tuner_r, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(vu_tuner_r, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(vu_tuner_r, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(vu_tuner_r, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(vu_tuner_r, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(vu_tuner_r, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_img_src(vu_tuner_r, &LED_OFF, LV_PART_MAIN | LV_STATE_DEFAULT);

	lv_obj_set_style_radius(vu_tuner_r, 0, LV_PART_INDICATOR | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(vu_tuner_r, lv_color_hex(0xFFFFFF), LV_PART_INDICATOR | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(vu_tuner_r, 0, LV_PART_INDICATOR | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_main_stop(vu_tuner_r, 0, LV_PART_INDICATOR | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_stop(vu_tuner_r, 255, LV_PART_INDICATOR | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_img_src(vu_tuner_r, &LED, LV_PART_INDICATOR | LV_STATE_DEFAULT);

	lv_obj_set_style_bg_color(vu_tuner_r, lv_color_hex(0xFFFFFF), LV_PART_KNOB | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(vu_tuner_r, 0, LV_PART_KNOB | LV_STATE_DEFAULT);

	lv_slider_set_value(vu_tuner_r, 10, LV_ANIM_OFF);
}

void create_vumeter_usb(void)
{
	// VU-Meter USB
	vu_usb_l = lv_slider_create(Tela_Main);
	lv_obj_clear_flag(vu_usb_l, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLLABLE);
	lv_slider_set_range(vu_usb_l, 0, 13);
	lv_obj_set_width(vu_usb_l, 21);
	lv_obj_set_height(vu_usb_l, 84);
	lv_obj_set_pos(vu_usb_l, 288, 126);

	lv_obj_set_style_radius(vu_usb_l, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(vu_usb_l, lv_color_hex(0xFF00FF), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(vu_usb_l, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_main_stop(vu_usb_l, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_stop(vu_usb_l, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(vu_usb_l, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(vu_usb_l, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(vu_usb_l, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(vu_usb_l, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(vu_usb_l, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_img_src(vu_usb_l, &LED_OFF, LV_PART_MAIN | LV_STATE_DEFAULT);

	lv_obj_set_style_radius(vu_usb_l, 0, LV_PART_INDICATOR | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(vu_usb_l, lv_color_hex(0xFFFFFF), LV_PART_INDICATOR | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(vu_usb_l, 0, LV_PART_INDICATOR | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_main_stop(vu_usb_l, 0, LV_PART_INDICATOR | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_stop(vu_usb_l, 255, LV_PART_INDICATOR | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_img_src(vu_usb_l, &LED, LV_PART_INDICATOR | LV_STATE_DEFAULT);

	lv_obj_set_style_bg_color(vu_usb_l, lv_color_hex(0xFFFFFF), LV_PART_KNOB | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(vu_usb_l, 0, LV_PART_KNOB | LV_STATE_DEFAULT);

	lv_slider_set_value(vu_usb_l, 6, LV_ANIM_OFF);

	// Right
	vu_usb_r = lv_slider_create(Tela_Main);
	lv_obj_clear_flag(vu_usb_r, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLLABLE);
	lv_slider_set_range(vu_usb_r, 0, 13);
	lv_obj_set_width(vu_usb_r, 21);
	lv_obj_set_height(vu_usb_r, 84);
	lv_obj_set_pos(vu_usb_r, 311, 126);

	lv_obj_set_style_radius(vu_usb_r, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(vu_usb_r, lv_color_hex(0xFF00FF), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(vu_usb_r, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_main_stop(vu_usb_r, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_stop(vu_usb_r, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(vu_usb_r, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(vu_usb_r, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(vu_usb_r, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(vu_usb_r, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(vu_usb_r, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_img_src(vu_usb_r, &LED_OFF, LV_PART_MAIN | LV_STATE_DEFAULT);

	lv_obj_set_style_radius(vu_usb_r, 0, LV_PART_INDICATOR | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(vu_usb_r, lv_color_hex(0xFFFFFF), LV_PART_INDICATOR | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(vu_usb_r, 0, LV_PART_INDICATOR | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_main_stop(vu_usb_r, 0, LV_PART_INDICATOR | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_stop(vu_usb_r, 255, LV_PART_INDICATOR | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_img_src(vu_usb_r, &LED, LV_PART_INDICATOR | LV_STATE_DEFAULT);

	lv_obj_set_style_bg_color(vu_usb_r, lv_color_hex(0xFFFFFF), LV_PART_KNOB | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(vu_usb_r, 0, LV_PART_KNOB | LV_STATE_DEFAULT);

	lv_slider_set_value(vu_usb_r, 6, LV_ANIM_OFF);
}


void create_vumeter_mpx(void)
{
	// VU-Meter MPX
	vu_mpx_1 = lv_slider_create(Tela_Main);
	lv_obj_clear_flag(vu_mpx_1, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLLABLE);
	lv_slider_set_range(vu_mpx_1, 0, 13);
	lv_obj_set_width(vu_mpx_1, 21);
	lv_obj_set_height(vu_mpx_1, 84);
	lv_obj_set_pos(vu_mpx_1, 335, 126);

	lv_obj_set_style_radius(vu_mpx_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(vu_mpx_1, lv_color_hex(0x00FFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(vu_mpx_1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_main_stop(vu_mpx_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_stop(vu_mpx_1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(vu_mpx_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(vu_mpx_1, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(vu_mpx_1, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(vu_mpx_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(vu_mpx_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_img_src(vu_mpx_1, &LED_OFF, LV_PART_MAIN | LV_STATE_DEFAULT);

	lv_obj_set_style_radius(vu_mpx_1, 0, LV_PART_INDICATOR | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(vu_mpx_1, lv_color_hex(0xFFFFFF), LV_PART_INDICATOR | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(vu_mpx_1, 0, LV_PART_INDICATOR | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_main_stop(vu_mpx_1, 0, LV_PART_INDICATOR | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_stop(vu_mpx_1, 255, LV_PART_INDICATOR | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_img_src(vu_mpx_1, &LED, LV_PART_INDICATOR | LV_STATE_DEFAULT);

	lv_obj_set_style_bg_color(vu_mpx_1, lv_color_hex(0xFFFFFF), LV_PART_KNOB | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(vu_mpx_1, 0, LV_PART_KNOB | LV_STATE_DEFAULT);

	lv_slider_set_value(vu_mpx_1, 2, LV_ANIM_OFF);

	// Right
	vu_mpx_2 = lv_slider_create(Tela_Main);
	lv_obj_clear_flag(vu_mpx_2, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLLABLE);
	lv_slider_set_range(vu_mpx_2, 0, 13);
	lv_obj_set_width(vu_mpx_2, 21);
	lv_obj_set_height(vu_mpx_2, 84);
	lv_obj_set_pos(vu_mpx_2, 358, 126);

	lv_obj_set_style_radius(vu_mpx_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(vu_mpx_2, lv_color_hex(0x00FFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(vu_mpx_2, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_main_stop(vu_mpx_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_stop(vu_mpx_2, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(vu_mpx_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(vu_mpx_2, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(vu_mpx_2, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(vu_mpx_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(vu_mpx_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_img_src(vu_mpx_2, &LED_OFF, LV_PART_MAIN | LV_STATE_DEFAULT);

	lv_obj_set_style_radius(vu_mpx_2, 0, LV_PART_INDICATOR | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(vu_mpx_2, lv_color_hex(0xFFFFFF), LV_PART_INDICATOR | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(vu_mpx_2, 0, LV_PART_INDICATOR | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_main_stop(vu_mpx_2, 0, LV_PART_INDICATOR | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_stop(vu_mpx_2, 255, LV_PART_INDICATOR | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_img_src(vu_mpx_2, &LED, LV_PART_INDICATOR | LV_STATE_DEFAULT);

	lv_obj_set_style_bg_color(vu_mpx_2, lv_color_hex(0xFFFFFF), LV_PART_KNOB | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(vu_mpx_2, 0, LV_PART_KNOB | LV_STATE_DEFAULT);

	lv_slider_set_value(vu_mpx_2, 2, LV_ANIM_OFF);
}

void create_Label_RDS(void)
{
    label_rds = lv_label_create(Tela_Main);
    lv_obj_set_width(label_rds, 280);
    lv_obj_set_height(label_rds, LV_SIZE_CONTENT);
    lv_label_set_text(label_rds, "AS MELHORES DA PROGRAMACAO SINTECK NEXT");
    lv_label_set_long_mode(label_rds, LV_LABEL_LONG_SCROLL_CIRCULAR);
    lv_obj_set_style_text_color(label_rds, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(label_rds, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(label_rds, &Neue_Medium_16, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(label_rds, 48, 12);
}

void formatar_frequencia(int32_t valor, char *resultado, size_t tamanho)
{
    if (valor < 76000 || valor > 108100) {
        snprintf(resultado, tamanho, "Fora do intervalo");
        return;
    }

    int milhares = valor / 1000;
    int unidades = valor % 1000;

    snprintf(resultado, tamanho, "%d.%03d MHz", milhares, unidades);
}

void create_Label_Frequency(int32_t frequency)
{
    label_frequency = lv_label_create(Tela_Main);
    lv_obj_set_width(label_frequency, LV_SIZE_CONTENT);
    lv_obj_set_height(label_frequency, LV_SIZE_CONTENT);
    lv_obj_set_style_text_letter_space(label_frequency, 0, 1);
    lv_obj_set_style_text_line_space(label_frequency, 0, 1);
    formatar_frequencia(frequency, str_freq, sizeof(str_freq));
    lv_label_set_text_fmt(label_frequency, str_freq);
    lv_obj_set_style_text_color(label_frequency, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(label_frequency, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(label_frequency, &Neue_Medium_52, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(label_frequency, 12, 34);
}

void create_text_audio_source(void)
{
    lv_obj_t * text_audio_source = lv_label_create(Tela_Main);
    lv_obj_set_width(text_audio_source, LV_SIZE_CONTENT);
    lv_obj_set_height(text_audio_source, LV_SIZE_CONTENT);
    lv_obj_set_style_text_letter_space(text_audio_source, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(text_audio_source, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_label_set_text(text_audio_source, "AUDIO SOURCE - INPUTS");
    lv_obj_set_style_text_color(text_audio_source, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(text_audio_source, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(text_audio_source, &Neue_Medium_11, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(text_audio_source, 161, 97);

    lv_obj_t * text_audio_mpx = lv_label_create(Tela_Main);
    lv_obj_set_width(text_audio_mpx, LV_SIZE_CONTENT);
    lv_obj_set_height(text_audio_mpx, LV_SIZE_CONTENT);
    lv_obj_set_style_text_letter_space(text_audio_mpx, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(text_audio_mpx, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_label_set_text(text_audio_mpx, "MPX OUT");
    lv_obj_set_style_text_color(text_audio_mpx, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(text_audio_mpx, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(text_audio_mpx, &Neue_Medium_11, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(text_audio_mpx, 328, 97);

    /*Create style*/
    static lv_style_t style_line;
    lv_style_init(&style_line);
    lv_style_set_line_width(&style_line, 1);
    lv_style_set_line_color(&style_line, lv_color_hex(0xFFFFFF));
    lv_style_set_line_rounded(&style_line, true);

    /*Create an array for the points of the line*/
    static lv_point_precise_t line_points1[] = { {0, 0}, {44, 0} };
    static lv_point_precise_t line_points2[] = { {0, 0}, {22, 0} };

    /*Create a line and apply the new style*/
    lv_obj_t * line1;
    line1 = lv_line_create(Tela_Main);
    lv_line_set_points(line1, line_points1, 2);     /*Set the points*/
    lv_obj_add_style(line1, &style_line, 0);
    lv_obj_set_pos(line1, 108, 103);
    //
    lv_obj_t * line2;
    line2 = lv_line_create(Tela_Main);
    lv_line_set_points(line2, line_points2, 2);     /*Set the points*/
    lv_obj_add_style(line2, &style_line, 0);
    lv_obj_set_pos(line2, 300, 103);

    // Indicacao VU´s
    lv_obj_t * text_vu_xlr = lv_label_create(Tela_Main);
    lv_obj_set_width(text_vu_xlr, LV_SIZE_CONTENT);
    lv_obj_set_height(text_vu_xlr, LV_SIZE_CONTENT);
    lv_obj_set_style_text_letter_space(text_vu_xlr, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(text_vu_xlr, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_label_set_text(text_vu_xlr, "XLR");
    lv_obj_set_style_text_color(text_vu_xlr, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(text_vu_xlr, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(text_vu_xlr, &Neue_Medium_11, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(text_vu_xlr, 114, 111);

    lv_obj_t * text_vu_aes = lv_label_create(Tela_Main);
    lv_obj_set_width(text_vu_aes, LV_SIZE_CONTENT);
    lv_obj_set_height(text_vu_aes, LV_SIZE_CONTENT);
    lv_obj_set_style_text_letter_space(text_vu_aes, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(text_vu_aes, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_label_set_text(text_vu_aes, "AES");
    lv_obj_set_style_text_color(text_vu_aes, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(text_vu_aes, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(text_vu_aes, &Neue_Medium_11, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(text_vu_aes, 160, 111);

    lv_obj_t * text_vu_pc = lv_label_create(Tela_Main);
    lv_obj_set_width(text_vu_pc, LV_SIZE_CONTENT);
    lv_obj_set_height(text_vu_pc, LV_SIZE_CONTENT);
    lv_obj_set_style_text_letter_space(text_vu_pc, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(text_vu_pc, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_label_set_text(text_vu_pc, "PC");
    lv_obj_set_style_text_color(text_vu_pc, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(text_vu_pc, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(text_vu_pc, &Neue_Medium_11, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(text_vu_pc, 209, 111);

    lv_obj_t * text_vu_tuner = lv_label_create(Tela_Main);
    lv_obj_set_width(text_vu_tuner, LV_SIZE_CONTENT);
    lv_obj_set_height(text_vu_tuner, LV_SIZE_CONTENT);
    lv_obj_set_style_text_letter_space(text_vu_tuner, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(text_vu_tuner, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_label_set_text(text_vu_tuner, "TUNER");
    lv_obj_set_style_text_color(text_vu_tuner, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(text_vu_tuner, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(text_vu_tuner, &Neue_Medium_11, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(text_vu_tuner, 243, 111);

    lv_obj_t * text_vu_usb = lv_label_create(Tela_Main);
    lv_obj_set_width(text_vu_usb, LV_SIZE_CONTENT);
    lv_obj_set_height(text_vu_usb, LV_SIZE_CONTENT);
    lv_obj_set_style_text_letter_space(text_vu_usb, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(text_vu_usb, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_label_set_text(text_vu_usb, "USB");
    lv_obj_set_style_text_color(text_vu_usb, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(text_vu_usb, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(text_vu_usb, &Neue_Medium_11, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(text_vu_usb, 298, 111);

    lv_obj_t * text_vu_mpx1 = lv_label_create(Tela_Main);
    lv_obj_set_width(text_vu_mpx1, LV_SIZE_CONTENT);
    lv_obj_set_height(text_vu_mpx1, LV_SIZE_CONTENT);
    lv_obj_set_style_text_letter_space(text_vu_mpx1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(text_vu_mpx1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_label_set_text(text_vu_mpx1, "1");
    lv_obj_set_style_text_color(text_vu_mpx1, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(text_vu_mpx1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(text_vu_mpx1, &Neue_Medium_11, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(text_vu_mpx1, 342, 111);

    lv_obj_t * text_vu_mpx2 = lv_label_create(Tela_Main);
    lv_obj_set_width(text_vu_mpx2, LV_SIZE_CONTENT);
    lv_obj_set_height(text_vu_mpx2, LV_SIZE_CONTENT);
    lv_obj_set_style_text_letter_space(text_vu_mpx2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(text_vu_mpx2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_label_set_text(text_vu_mpx2, "2");
    lv_obj_set_style_text_color(text_vu_mpx2, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(text_vu_mpx2, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(text_vu_mpx2, &Neue_Medium_11, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(text_vu_mpx2, 363, 111);
}

void create_text_scale_vu(void)
{
	for(uint8_t x = 0; x < 8; x++) {
		label_scale[x] = lv_label_create(Tela_Main);
		lv_obj_set_width(label_scale[x], LV_SIZE_CONTENT);
		lv_obj_set_height(label_scale[x], LV_SIZE_CONTENT);
		lv_obj_set_style_text_letter_space(label_scale[x], 0, LV_PART_MAIN | LV_STATE_DEFAULT);
		lv_obj_set_style_text_line_space(label_scale[x], 0, LV_PART_MAIN | LV_STATE_DEFAULT);
		lv_obj_set_style_text_color(label_scale[x], lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
		lv_obj_set_style_text_opa(label_scale[x], 255, LV_PART_MAIN | LV_STATE_DEFAULT);
		lv_obj_set_style_text_font(label_scale[x], &Neue_Medium_11, LV_PART_MAIN | LV_STATE_DEFAULT);
	}
	lv_label_set_text(label_scale[0], "-60"); lv_obj_set_pos(label_scale[0], 20, 216);
	lv_label_set_text(label_scale[1], "-50"); lv_obj_set_pos(label_scale[1], 92, 216);
	lv_label_set_text(label_scale[2], "-40"); lv_obj_set_pos(label_scale[2], 164, 216);
	lv_label_set_text(label_scale[3], "-30"); lv_obj_set_pos(label_scale[3], 250, 216);
	lv_label_set_text(label_scale[4], "-20"); lv_obj_set_pos(label_scale[4], 308, 216);
	lv_label_set_text(label_scale[5], "-10"); lv_obj_set_pos(label_scale[5], 372, 216);
	lv_label_set_text(label_scale[6], "0dB"); lv_obj_set_pos(label_scale[6], 408, 216);
	lv_label_set_text(label_scale[7], "10dB>"); lv_obj_set_pos(label_scale[7], 438, 216);
}

void create_img_button_volume(void)
{
	// PHONE Symbol
	lv_obj_t * img_phone = lv_img_create(Tela_Main);
	lv_img_set_src(img_phone, &PHONE);
	lv_obj_set_pos(img_phone, 456, 165);

//	// INDICADOR Symbol
//	lv_obj_t * img_bt = lv_img_create(Tela_Main);
//	lv_img_set_src(img_bt, &BT_INDIC);
//	lv_obj_set_pos(img_bt, 404, 136);
}
