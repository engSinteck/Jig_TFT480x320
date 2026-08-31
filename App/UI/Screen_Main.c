/*
 * Screen_Main.c
 *
 *  Created on: 14 de ago. de 2026
 *      Author: rinaldo.santos
 */

#include "stdbool.h"
#include "rng.h"
#include "stdio.h"
#include "string.h"

#include "../App/UI/Screen_Main.h"
#include "../App/UI/Screen_Inputs.h"
#include "../App/UI/Screen_Outputs.h"
#include "../App/UI/Screen_Config.h"
#include "../App/UI/Screen_Menu_USB.h"
#include "../App/UI/Screen_Menu_PC.h"
#include "../App/UI/Screen_Menu_PROC.h"
#include "../App/UI/Screen_Menu_MP3.h"
#include "../App/UI/Screen_Menu_TUNER.h"
#include "../App/UI/led_ring.h"
#include "../App/UI/bar_leds.h"

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
void create_main_barmeter_xlr(void);
void create_main_barmeter_aes(void);
void create_main_barmeter_pc(void);
void create_main_barmeter_tuner(void);
void create_main_barmeter_usb(void);
void create_main_barmeter_mpx(void);

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
LV_IMG_DECLARE(TELA_FUNDO_MAIN);
LV_IMG_DECLARE(IMG_FM);
LV_IMG_DECLARE(BT_TUNED);
LV_IMG_DECLARE(BT_STEREO);
LV_IMG_DECLARE(BT_RDS);

lv_obj_t * Tela_Main = NULL;

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

static lv_timer_t * task_Main;

static uint32_t cont_main = 0;

static led_ring_t ring_vol;

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

static barmeter_t main_xlr_l;
static barmeter_t main_xlr_r;
static barmeter_t main_aes_l;
static barmeter_t main_aes_r;
static barmeter_t main_pc_l;
static barmeter_t main_pc_r;
static barmeter_t main_tuner_l;
static barmeter_t main_tuner_r;
static barmeter_t main_usb_l;
static barmeter_t main_usb_r;
static barmeter_t main_mpx1;
static barmeter_t main_mpx2;

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
/*
	uint32_t val_64 = Gerar_Aleatorio_0_64();
	set_vumeter_left(val_64);
	set_vumeter_right(val_64);

	uint8_t val_13_0 = ObterNumeroAleatorio0a13();
	barmeter_set(&main_xlr_l, (int32_t)val_13_0);
	barmeter_set(&main_xlr_r, (int32_t)val_13_0);

	barmeter_set(&main_aes_l, (int32_t)val_13_0);
	barmeter_set(&main_aes_r, (int32_t)val_13_0);

	barmeter_set(&main_pc_l, (int32_t)val_13_0);
	barmeter_set(&main_pc_r, (int32_t)val_13_0);

	barmeter_set(&main_tuner_l, (int32_t)val_13_0);
	barmeter_set(&main_tuner_r, (int32_t)val_13_0);

	barmeter_set(&main_usb_l, (int32_t)val_13_0);
	barmeter_set(&main_usb_r, (int32_t)val_13_0);

	barmeter_set(&main_mpx1, (int32_t)val_13_0);
	barmeter_set(&main_mpx2, (int32_t)val_13_0);
*/
}

void Screen_Create_Main(void)
{
	Tela_Main = lv_obj_create(NULL);
	lv_obj_clear_flag(Tela_Main, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLLABLE);
	lv_obj_set_style_bg_color(Tela_Main, lv_color_hex(0x000000), 0);
	lv_obj_set_style_bg_grad_color(Tela_Main, lv_color_hex(0x000000), 0);

	// Imagem de Fundo
	img_fundo = lv_img_create(Tela_Main);
	//lv_img_set_src(img_fundo, &TELA_FUNDO_MAIN);
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
	// Bar-Meter
	create_main_barmeter_xlr();
	create_main_barmeter_aes();
	create_main_barmeter_pc();
	create_main_barmeter_tuner();
	create_main_barmeter_usb();
	create_main_barmeter_mpx();

	// Label RDS
	create_Label_RDS();
	// Label Frequency
	create_Label_Frequency(fm_frequency);
	// Text Audio Source
	create_text_audio_source();
	// Text Scale VU
	create_text_scale_vu();
	// Knob Volume
	led_ring_create(Tela_Main, &ring_vol, 386, 95);
	// Buttons Tunner
	create_buttons_tunner();
	// Phone + BT Indicador
	create_img_button_volume();

    cont_main = 0;
    static uint32_t user_data = 10;
    task_Main = lv_timer_create(update_main_screen, 100,  &user_data);
}

void create_fm_symbol(void)
{
	// FM Symbol
	lv_obj_t * img_fm = lv_img_create(Tela_Main);
	lv_img_set_src(img_fm, "S:/MAIN/IMG_FM.bin");
	//lv_img_set_src(img_fm, &IMG_FM);
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
	//lv_img_set_src(img_tuned, &BT_TUNED);

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
	//lv_img_set_src(img_stereo, &BT_STEREO);
	lv_img_set_src(img_stereo, "S/MAIN/BT_STEREO.bin");
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
	//lv_img_set_src(img_rds, &BT_RDS);
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
		 if(fm_frequency > 76100) {
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
		led_ring_inc(&ring_vol);
	 }
}

static void event_bt_vol_dec(lv_event_t * e)
{
	lv_event_code_t code = lv_event_get_code(e);

	if(code == LV_EVENT_CLICKED || code == LV_EVENT_LONG_PRESSED_REPEAT) {
		led_ring_dec(&ring_vol);
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

static void event_menu_inputs(lv_event_t * e)
{
	lv_event_code_t code = lv_event_get_code(e);

	if(code == LV_EVENT_CLICKED) {
		// Cria a próxima tela antes de carregar
		Screen_Inputs_Create();

		// auto_del = true vai deletar a Tela_Main automaticamente ao fim da animação
		lv_screen_load_anim(Tela_Inputs, LV_SCREEN_LOAD_ANIM_NONE, 0, 0, true);
	 }
}

static void event_menu_outputs(lv_event_t * e)
{
	lv_event_code_t code = lv_event_get_code(e);

	if(code == LV_EVENT_CLICKED) {
		// Cria a próxima tela antes de carregar
		Screen_Outputs_Create();

		// auto_del = true vai deletar a Tela_Main automaticamente ao fim da animação
		lv_screen_load_anim(Tela_Outputs, LV_SCREEN_LOAD_ANIM_NONE, 0, 0, true);
	 }
}

static void event_menu_config(lv_event_t * e)
{
	lv_event_code_t code = lv_event_get_code(e);

	if(code == LV_EVENT_CLICKED) {
		// Cria a próxima tela antes de carregar
		Screen_Config_Create();

		// auto_del = true vai deletar a Tela_Main automaticamente ao fim da animação
		lv_screen_load_anim(Tela_Config, LV_SCREEN_LOAD_ANIM_NONE, 0, 0, true);
	}
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
    lv_obj_add_event_cb(bt_inputs, event_menu_inputs, LV_EVENT_ALL, NULL);

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
    lv_obj_add_event_cb(bt_outputs, event_menu_outputs, LV_EVENT_ALL, NULL);

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
    lv_obj_add_event_cb(bt_configs, event_menu_config, LV_EVENT_ALL, NULL);

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

static void event_menu_usb(lv_event_t * e)
{
	lv_event_code_t code = lv_event_get_code(e);

	if(code == LV_EVENT_CLICKED) {
		// Cria a próxima tela antes de carregar
		Screen_Menu_USB_Create();

		// auto_del = true vai deletar a Tela_Main automaticamente ao fim da animação
		lv_screen_load_anim(Tela_Menu_USB, LV_SCREEN_LOAD_ANIM_NONE, 0, 0, true);
	 }
}

static void event_menu_pc(lv_event_t * e)
{
	lv_event_code_t code = lv_event_get_code(e);

	if(code == LV_EVENT_CLICKED) {
		// Cria a próxima tela antes de carregar
		Screen_Menu_PC_Create();

		// auto_del = true vai deletar a Tela_Main automaticamente ao fim da animação
		lv_screen_load_anim(Tela_Menu_PC, LV_SCREEN_LOAD_ANIM_NONE, 0, 0, true);
	 }
}

static void event_menu_proc(lv_event_t * e)
{
	lv_event_code_t code = lv_event_get_code(e);

	if(code == LV_EVENT_CLICKED) {
		// Cria a próxima tela antes de carregar
		Screen_Menu_PROC_Create();

		// auto_del = true vai deletar a Tela_Main automaticamente ao fim da animação
		lv_screen_load_anim(Tela_Menu_PROC, LV_SCREEN_LOAD_ANIM_NONE, 0, 0, true);
	 }
}

static void event_menu_mp3(lv_event_t * e)
{
	lv_event_code_t code = lv_event_get_code(e);

	if(code == LV_EVENT_CLICKED) {
		// Cria a próxima tela antes de carregar
		Screen_Menu_MP3_Create();

		// auto_del = true vai deletar a Tela_Main automaticamente ao fim da animação
		lv_screen_load_anim(Tela_Menu_MP3, LV_SCREEN_LOAD_ANIM_NONE, 0, 0, true);
	 }
}

static void event_menu_tuner(lv_event_t * e)
{
	lv_event_code_t code = lv_event_get_code(e);

	if(code == LV_EVENT_CLICKED) {
		// Cria a próxima tela antes de carregar
		Screen_Menu_TUNER_Create();

		// auto_del = true vai deletar a Tela_Main automaticamente ao fim da animação
		lv_screen_load_anim(Tela_Menu_TUNER, LV_SCREEN_LOAD_ANIM_NONE, 0, 0, true);
	 }
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

    // Events
	lv_obj_add_event_cb(bt_menu[0], event_menu_usb, LV_EVENT_ALL, NULL);
	lv_obj_add_event_cb(bt_menu[1], event_menu_pc, LV_EVENT_ALL, NULL);
	lv_obj_add_event_cb(bt_menu[2], event_menu_proc, LV_EVENT_ALL, NULL);
	lv_obj_add_event_cb(bt_menu[3], event_menu_mp3, LV_EVENT_ALL, NULL);
	lv_obj_add_event_cb(bt_menu[4], event_menu_tuner, LV_EVENT_ALL, NULL);
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
    //if (valor < 76000 || valor > 108100) {
    //    snprintf(resultado, tamanho, "Fora do intervalo");
    //    return;
    //}

    int milhares = valor / 1000;
    int unidades = valor % 1000;

    snprintf(resultado, tamanho, "%d.%03d MHz", milhares, unidades);
}

void create_Label_Frequency(int32_t frequency)
{
    label_frequency = lv_label_create(Tela_Main);
    lv_obj_set_width(label_frequency, 316);
    lv_obj_set_height(label_frequency, LV_SIZE_CONTENT);
    // Color Font
    lv_obj_set_style_text_color(label_frequency, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(label_frequency, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(label_frequency, &Neue_Medium_52, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(label_frequency, 0, 1);
    lv_obj_set_style_text_line_space(label_frequency, 0, 1);
    lv_obj_set_style_text_align(label_frequency, LV_TEXT_ALIGN_CENTER, 0);

    formatar_frequencia(frequency, str_freq, sizeof(str_freq));
    lv_label_set_text_fmt(label_frequency, str_freq);

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
	//lv_img_set_src(img_phone, &PHONE);
	lv_img_set_src(img_phone, "S:/MAIN/PHONE.bin");
	lv_obj_set_pos(img_phone, 456, 165);
}

void create_main_barmeter_xlr(void)
{
	main_xlr_l.on       = NULL;
	main_xlr_l.last_seg = -1;
	main_xlr_l.x        = 100;
	main_xlr_l.y        = 126;
	main_xlr_l.w        = BAR_W;
	main_xlr_l.h        = BAR_H;
	main_xlr_l.range    = BAR_RANGE;
	main_xlr_l.segs     = BAR_SEGMENTS;
	main_xlr_l.bounds   = NULL;
	main_xlr_l.img_off  = &LED_OFF;
	main_xlr_l.img_on   = &LED;

	main_xlr_r.on       = NULL;
	main_xlr_r.last_seg = -1;
	main_xlr_r.x        = 123;
	main_xlr_r.y        = 126;
	main_xlr_r.w        = BAR_W;
	main_xlr_r.h        = BAR_H;
	main_xlr_r.range    = BAR_RANGE;
	main_xlr_r.segs     = BAR_SEGMENTS;
	main_xlr_r.bounds   = NULL;
	main_xlr_r.img_off  = &LED_OFF;
	main_xlr_r.img_on   = &LED;

	barmeter_create(Tela_Main, &main_xlr_l);
	barmeter_create(Tela_Main, &main_xlr_r);
	barmeter_set(&main_xlr_l, 4);
	barmeter_set(&main_xlr_r, 4);
}

void create_main_barmeter_aes(void)
{
	main_aes_l.on       = NULL;
	main_aes_l.last_seg = -1;
	main_aes_l.x        = 147;
	main_aes_l.y        = 126;
	main_aes_l.w        = BAR_W;
	main_aes_l.h        = BAR_H;
	main_aes_l.range    = BAR_RANGE;
	main_aes_l.segs     = BAR_SEGMENTS;
	main_aes_l.bounds   = NULL;
	main_aes_l.img_off  = &LED_OFF;
	main_aes_l.img_on   = &LED;

	main_aes_r.on       = NULL;
	main_aes_r.last_seg = -1;
	main_aes_r.x        = 170;
	main_aes_r.y        = 126;
	main_aes_r.w        = BAR_W;
	main_aes_r.h        = BAR_H;
	main_aes_r.range    = BAR_RANGE;
	main_aes_r.segs     = BAR_SEGMENTS;
	main_aes_r.bounds   = NULL;
	main_aes_r.img_off  = &LED_OFF;
	main_aes_r.img_on   = &LED;

	barmeter_create(Tela_Main, &main_aes_l);
	barmeter_create(Tela_Main, &main_aes_r);
	barmeter_set(&main_aes_l, 7);
	barmeter_set(&main_aes_r, 7);
}

void create_main_barmeter_pc(void)
{
	main_pc_l.on       = NULL;
	main_pc_l.last_seg = -1;
	main_pc_l.x        = 194;
	main_pc_l.y        = 126;
	main_pc_l.w        = BAR_W;
	main_pc_l.h        = BAR_H;
	main_pc_l.range    = BAR_RANGE;
	main_pc_l.segs     = BAR_SEGMENTS;
	main_pc_l.bounds   = NULL;
	main_pc_l.img_off  = &LED_OFF;
	main_pc_l.img_on   = &LED;

	main_pc_r.on       = NULL;
	main_pc_r.last_seg = -1;
	main_pc_r.x        = 217;
	main_pc_r.y        = 126;
	main_pc_r.w        = BAR_W;
	main_pc_r.h        = BAR_H;
	main_pc_r.range    = BAR_RANGE;
	main_pc_r.segs     = BAR_SEGMENTS;
	main_pc_r.bounds   = NULL;
	main_pc_r.img_off  = &LED_OFF;
	main_pc_r.img_on   = &LED;

	barmeter_create(Tela_Main, &main_pc_l);
	barmeter_create(Tela_Main, &main_pc_r);
	barmeter_set(&main_pc_l, 11);
	barmeter_set(&main_pc_r, 11);
}

void create_main_barmeter_tuner(void)
{
	main_tuner_l.on       = NULL;
	main_tuner_l.last_seg = -1;
	main_tuner_l.x        = 241;
	main_tuner_l.y        = 126;
	main_tuner_l.w        = BAR_W;
	main_tuner_l.h        = BAR_H;
	main_tuner_l.range    = BAR_RANGE;
	main_tuner_l.segs     = BAR_SEGMENTS;
	main_tuner_l.bounds   = NULL;
	main_tuner_l.img_off  = &LED_OFF;
	main_tuner_l.img_on   = &LED;

	main_tuner_r.on       = NULL;
	main_tuner_r.last_seg = -1;
	main_tuner_r.x        = 264;
	main_tuner_r.y        = 126;
	main_tuner_r.w        = BAR_W;
	main_tuner_r.h        = BAR_H;
	main_tuner_r.range    = BAR_RANGE;
	main_tuner_r.segs     = BAR_SEGMENTS;
	main_tuner_r.bounds   = NULL;
	main_tuner_r.img_off  = &LED_OFF;
	main_tuner_r.img_on   = &LED;

	barmeter_create(Tela_Main, &main_tuner_l);
	barmeter_create(Tela_Main, &main_tuner_r);

	barmeter_set(&main_tuner_l, 8);
	barmeter_set(&main_tuner_r, 8);
}

void create_main_barmeter_usb(void)
{
	main_usb_l.on       = NULL;
	main_usb_l.last_seg = -1;
	main_usb_l.x        = 288;
	main_usb_l.y        = 126;
	main_usb_l.w        = BAR_W;
	main_usb_l.h        = BAR_H;
	main_usb_l.range    = BAR_RANGE;
	main_usb_l.segs     = BAR_SEGMENTS;
	main_usb_l.bounds   = NULL;
	main_usb_l.img_off  = &LED_OFF;
	main_usb_l.img_on   = &LED;

	main_usb_r.on       = NULL;
	main_usb_r.last_seg = -1;
	main_usb_r.x        = 311;
	main_usb_r.y        = 126;
	main_usb_r.w        = BAR_W;
	main_usb_r.h        = BAR_H;
	main_usb_r.range    = BAR_RANGE;
	main_usb_r.segs     = BAR_SEGMENTS;
	main_usb_r.bounds   = NULL;
	main_usb_r.img_off  = &LED_OFF;
	main_usb_r.img_on   = &LED;

	barmeter_create(Tela_Main, &main_usb_l);
	barmeter_create(Tela_Main, &main_usb_r);
	barmeter_set(&main_usb_l, 5);
	barmeter_set(&main_usb_r, 5);
}

void create_main_barmeter_mpx(void)
{
	main_mpx1.on       = NULL;
	main_mpx1.last_seg = -1;
	main_mpx1.x        = 335;
	main_mpx1.y        = 126;
	main_mpx1.w        = BAR_W;
	main_mpx1.h        = BAR_H;
	main_mpx1.range    = BAR_RANGE;
	main_mpx1.segs     = BAR_SEGMENTS;
	main_mpx1.bounds   = NULL;
	main_mpx1.img_off  = &LED_OFF;
	main_mpx1.img_on   = &LED;

	main_mpx2.on       = NULL;
	main_mpx2.last_seg = -1;
	main_mpx2.x        = 358;
	main_mpx2.y        = 126;
	main_mpx2.w        = BAR_W;
	main_mpx2.h        = BAR_H;
	main_mpx2.range    = BAR_RANGE;
	main_mpx2.segs     = BAR_SEGMENTS;
	main_mpx2.bounds   = NULL;
	main_mpx2.img_off  = &LED_OFF;
	main_mpx2.img_on   = &LED;

	barmeter_create(Tela_Main, &main_mpx1);
	barmeter_create(Tela_Main, &main_mpx2);

	barmeter_set(&main_mpx1, 1);
	barmeter_set(&main_mpx2, 1);
}
