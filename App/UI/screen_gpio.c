/*
 * screen_gpio.c
 *
 *  Created on: 20 de jul. de 2026
 *      Author: rinaldo.santos
 */

#include "main.h"
#include "lvgl.h"
#include "../App/UI/screen_debug.h"

void update_gpio_screen(lv_timer_t * timer);
void Set_backlight(void);
void Set_fmt0_aes(void);
void Set_fmt1_aes(void);
void Set_mute(void);
void Set_Analog(void);
void Set_DSP1(void);
void Set_DSP2(void);
void Set_Toslink(void);
void Set_Impedance(void);
void print_line_1(void);

extern lv_obj_t * Tela_Debug;
extern lv_obj_t * Tela_DAC;

lv_obj_t * Tela_Gpio;
static lv_obj_t * backlight;
static lv_obj_t * label_back;
static lv_obj_t * fmt_0;
static lv_obj_t * fmt_1;
static lv_obj_t * mutempx;
static lv_obj_t * analog;
static lv_obj_t * dsp1;
static lv_obj_t * dsp2;
static lv_obj_t * toslink;
static lv_obj_t * impedance;

//static lv_timer_t * task_Gpio;

void screen_gpio(void)
{
	Tela_Gpio = lv_obj_create(NULL);
	lv_obj_clear_flag(Tela_Gpio, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLLABLE);
	lv_obj_set_style_bg_color(Tela_Gpio, lv_color_hex(0x000000), 0);
	lv_obj_set_style_bg_grad_color(Tela_Gpio, lv_color_hex(0x000000), 0);

	Set_backlight();
	Set_fmt0_aes();
	Set_fmt1_aes();
	Set_mute();
	print_line_1();
	//
	Set_Analog();
	Set_DSP1();
	Set_DSP2();
	Set_Toslink();
	Set_Impedance();

	Button_Menu(Tela_Gpio);

    //static uint32_t user_data = 10;
    //task_Gpio = lv_timer_create(update_gpio_screen, 200,  &user_data);

	lv_scr_load(Tela_Gpio);
}

void update_gpio_screen(lv_timer_t * timer)
{


}

static void event_back_handler(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * obj = lv_event_get_target(e);

    if(code == LV_EVENT_VALUE_CHANGED) {
    	if(lv_obj_has_state(obj, LV_STATE_CHECKED)) {
    		  //HAL_GPIO_WritePin(TFT_BACKLIGHT_GPIO_Port, TFT_BACKLIGHT_Pin, GPIO_PIN_SET);
    	}
    	else {
    		//HAL_GPIO_WritePin(TFT_BACKLIGHT_GPIO_Port, TFT_BACKLIGHT_Pin, GPIO_PIN_RESET);
    	}
    }
}

void Set_backlight(void)
{
	static lv_style_t style_txt;
	lv_style_init(&style_txt);
	lv_style_set_text_color(&style_txt, lv_color_hex(0xFFFFFF));

    label_back = lv_label_create(Tela_Gpio);
    lv_obj_add_style(label_back, &style_txt, LV_PART_MAIN);
    lv_label_set_text(label_back, "BACKLIGHT:");
    lv_obj_set_pos(label_back, 1, 2);

	backlight = lv_switch_create(Tela_Gpio);
    lv_obj_add_event_cb(backlight, event_back_handler, LV_EVENT_ALL, NULL);
    lv_obj_add_flag(backlight, LV_OBJ_FLAG_CHECKABLE);
//    if(HAL_GPIO_ReadPin(TFT_BACKLIGHT_GPIO_Port, TFT_BACKLIGHT_Pin)) {
//    	lv_obj_add_state(backlight, LV_STATE_CHECKED);
//    }
//    else {
    	lv_obj_clear_state(backlight, LV_STATE_CHECKED);
//    }
    lv_obj_set_pos(backlight, 48, 30);

    lv_obj_t * label_high = lv_label_create(Tela_Gpio);
    lv_obj_add_style(label_high, &style_txt, LV_PART_MAIN);
    lv_label_set_text(label_high, "HIGH");
    lv_obj_align_to(label_high, backlight, LV_ALIGN_OUT_RIGHT_MID, 5, 0);

    lv_obj_t * label_low = lv_label_create(Tela_Gpio);
    lv_obj_add_style(label_low, &style_txt, LV_PART_MAIN);
    lv_label_set_text(label_low, "LOW");
    lv_obj_align_to(label_low, backlight, LV_ALIGN_OUT_LEFT_MID, -5, 0);
}

static void event_fmt0_handler(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * obj = lv_event_get_target(e);

    if(code == LV_EVENT_VALUE_CHANGED) {
    	if(lv_obj_has_state(obj, LV_STATE_CHECKED)) {
    		  //HAL_GPIO_WritePin(FMT0_AES_GPIO_Port, FMT0_AES_Pin, GPIO_PIN_SET);
    	}
    	else {
    		//HAL_GPIO_WritePin(FMT0_AES_GPIO_Port, FMT0_AES_Pin, GPIO_PIN_RESET);
    	}
    }
}

void Set_fmt0_aes(void)
{
	static lv_style_t style_txt;
	lv_style_init(&style_txt);
	lv_style_set_text_color(&style_txt, lv_color_hex(0xFFFFFF));

    label_back = lv_label_create(Tela_Gpio);
    lv_obj_add_style(label_back, &style_txt, LV_PART_MAIN);
    lv_label_set_text(label_back, "FMT 0:");
    lv_obj_set_pos(label_back, 1, 70);

	fmt_0 = lv_switch_create(Tela_Gpio);
    lv_obj_add_event_cb(fmt_0, event_fmt0_handler, LV_EVENT_ALL, NULL);
    lv_obj_add_flag(fmt_0, LV_OBJ_FLAG_CHECKABLE);
//    if(HAL_GPIO_ReadPin(FMT0_AES_GPIO_Port, FMT0_AES_Pin)) {
//    	lv_obj_add_state(fmt_0, LV_STATE_CHECKED);
//    }
//    else {
    	lv_obj_clear_state(fmt_0, LV_STATE_CHECKED);
//    }
    lv_obj_set_pos(fmt_0, 48, 94);

    lv_obj_t * label_high = lv_label_create(Tela_Gpio);
    lv_obj_add_style(label_high, &style_txt, LV_PART_MAIN);
    lv_label_set_text(label_high, "HIGH");
    lv_obj_align_to(label_high, fmt_0, LV_ALIGN_OUT_RIGHT_MID, 5, 0);

    lv_obj_t * label_low = lv_label_create(Tela_Gpio);
    lv_obj_add_style(label_low, &style_txt, LV_PART_MAIN);
    lv_label_set_text(label_low, "LOW");
    lv_obj_align_to(label_low, fmt_0, LV_ALIGN_OUT_LEFT_MID, -5, 0);
}

static void event_fmt1_handler(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * obj = lv_event_get_target(e);

    if(code == LV_EVENT_VALUE_CHANGED) {
    	if(lv_obj_has_state(obj, LV_STATE_CHECKED)) {
    		 // HAL_GPIO_WritePin(FMT1_AES_GPIO_Port, FMT1_AES_Pin, GPIO_PIN_SET);
    	}
    	else {
    		//HAL_GPIO_WritePin(FMT1_AES_GPIO_Port, FMT1_AES_Pin, GPIO_PIN_RESET);
    	}
    }
}

void Set_fmt1_aes(void)
{
	static lv_style_t style_txt;
	lv_style_init(&style_txt);
	lv_style_set_text_color(&style_txt, lv_color_hex(0xFFFFFF));

    label_back = lv_label_create(Tela_Gpio);
    lv_obj_add_style(label_back, &style_txt, LV_PART_MAIN);
    lv_label_set_text(label_back, "FMT 1:");
    lv_obj_set_pos(label_back, 1, 134);

	fmt_1 = lv_switch_create(Tela_Gpio);
    lv_obj_add_event_cb(fmt_1, event_fmt1_handler, LV_EVENT_ALL, NULL);
    lv_obj_add_flag(fmt_1, LV_OBJ_FLAG_CHECKABLE);
//    if(HAL_GPIO_ReadPin(FMT1_AES_GPIO_Port, FMT1_AES_Pin)) {
//    	lv_obj_add_state(fmt_1, LV_STATE_CHECKED);
//    }
//    else {
    	lv_obj_clear_state(fmt_1, LV_STATE_CHECKED);
//    }
    lv_obj_set_pos(fmt_1, 48, 158);

    lv_obj_t * label_high = lv_label_create(Tela_Gpio);
    lv_obj_add_style(label_high, &style_txt, LV_PART_MAIN);
    lv_label_set_text(label_high, "HIGH");
    lv_obj_align_to(label_high, fmt_1, LV_ALIGN_OUT_RIGHT_MID, 5, 0);

    lv_obj_t * label_low = lv_label_create(Tela_Gpio);
    lv_obj_add_style(label_low, &style_txt, LV_PART_MAIN);
    lv_label_set_text(label_low, "LOW");
    lv_obj_align_to(label_low, fmt_1, LV_ALIGN_OUT_LEFT_MID, -5, 0);
}


static void event_mute_handler(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * obj = lv_event_get_target(e);

    if(code == LV_EVENT_VALUE_CHANGED) {
    	if(lv_obj_has_state(obj, LV_STATE_CHECKED)) {
    		  //HAL_GPIO_WritePin(MUTE_MPX_GPIO_Port, MUTE_MPX_Pin, GPIO_PIN_SET);
    	}
    	else {
    		//HAL_GPIO_WritePin(MUTE_MPX_GPIO_Port, MUTE_MPX_Pin, GPIO_PIN_RESET);
    	}
    }
}

void Set_mute(void)
{
	static lv_style_t style_txt;
	lv_style_init(&style_txt);
	lv_style_set_text_color(&style_txt, lv_color_hex(0xFFFFFF));

    label_back = lv_label_create(Tela_Gpio);
    lv_obj_add_style(label_back, &style_txt, LV_PART_MAIN);
    lv_label_set_text(label_back, "MUTE MPX:");
    lv_obj_set_pos(label_back, 1, 201);

	mutempx = lv_switch_create(Tela_Gpio);
    lv_obj_add_event_cb(mutempx, event_mute_handler, LV_EVENT_ALL, NULL);
    lv_obj_add_flag(mutempx, LV_OBJ_FLAG_CHECKABLE);
//    if(HAL_GPIO_ReadPin(MUTE_MPX_GPIO_Port, MUTE_MPX_Pin)) {
//    	lv_obj_add_state(mutempx, LV_STATE_CHECKED);
//    }
//    else {
    	lv_obj_clear_state(mutempx, LV_STATE_CHECKED);
//    }
    lv_obj_set_pos(mutempx, 48, 222);

    lv_obj_t * label_high = lv_label_create(Tela_Gpio);
    lv_obj_add_style(label_high, &style_txt, LV_PART_MAIN);
    lv_label_set_text(label_high, "HIGH");
    lv_obj_align_to(label_high, mutempx, LV_ALIGN_OUT_RIGHT_MID, 5, 0);

    lv_obj_t * label_low = lv_label_create(Tela_Gpio);
    lv_obj_add_style(label_low, &style_txt, LV_PART_MAIN);
    lv_label_set_text(label_low, "LOW");
    lv_obj_align_to(label_low, mutempx, LV_ALIGN_OUT_LEFT_MID, -5, 0);
}

static void event_analog_handler(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * obj = lv_event_get_target(e);

    if(code == LV_EVENT_VALUE_CHANGED) {
    	if(lv_obj_has_state(obj, LV_STATE_CHECKED)) {
    		  //HAL_GPIO_WritePin(ANALOG_DIGITAL_GPIO_Port, ANALOG_DIGITAL_Pin, GPIO_PIN_SET);
    	}
    	else {
    		//HAL_GPIO_WritePin(ANALOG_DIGITAL_GPIO_Port, ANALOG_DIGITAL_Pin, GPIO_PIN_RESET);
    	}
    }
}

void Set_Analog(void)
{
	static lv_style_t style_txt;
	lv_style_init(&style_txt);
	lv_style_set_text_color(&style_txt, lv_color_hex(0xFFFFFF));

    label_back = lv_label_create(Tela_Gpio);
    lv_obj_add_style(label_back, &style_txt, LV_PART_MAIN);
    lv_label_set_text(label_back, "ANALOG/DIGITAL:");
    lv_obj_set_pos(label_back, 330, 2);

	analog = lv_switch_create(Tela_Gpio);
    lv_obj_add_event_cb(analog, event_analog_handler, LV_EVENT_ALL, NULL);
    lv_obj_add_flag(analog, LV_OBJ_FLAG_CHECKABLE);
//    if(HAL_GPIO_ReadPin(ANALOG_DIGITAL_GPIO_Port, ANALOG_DIGITAL_Pin)) {
//    	lv_obj_add_state(analog, LV_STATE_CHECKED);
//    }
//    else {
    	lv_obj_clear_state(analog, LV_STATE_CHECKED);
//    }
    lv_obj_set_pos(analog, 370, 30);

    lv_obj_t * label_high = lv_label_create(Tela_Gpio);
    lv_obj_add_style(label_high, &style_txt, LV_PART_MAIN);
    lv_label_set_text(label_high, "HIGH");
    lv_obj_align_to(label_high, analog, LV_ALIGN_OUT_RIGHT_MID, 5, 0);

    lv_obj_t * label_low = lv_label_create(Tela_Gpio);
    lv_obj_add_style(label_low, &style_txt, LV_PART_MAIN);
    lv_label_set_text(label_low, "LOW");
    lv_obj_align_to(label_low, analog, LV_ALIGN_OUT_LEFT_MID, -5, 0);
}

static void event_dsp1_handler(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * obj = lv_event_get_target(e);

    if(code == LV_EVENT_VALUE_CHANGED) {
    	if(lv_obj_has_state(obj, LV_STATE_CHECKED)) {
    		  //HAL_GPIO_WritePin(DSP1_GPIO_Port, DSP1_Pin, GPIO_PIN_SET);
    	}
    	else {
    		//HAL_GPIO_WritePin(DSP1_GPIO_Port, DSP1_Pin, GPIO_PIN_RESET);
    	}
    }
}

void Set_DSP1(void)
{
	static lv_style_t style_txt;
	lv_style_init(&style_txt);
	lv_style_set_text_color(&style_txt, lv_color_hex(0xFFFFFF));

    label_back = lv_label_create(Tela_Gpio);
    lv_obj_add_style(label_back, &style_txt, LV_PART_MAIN);
    lv_label_set_text(label_back, "DSP 1:");
    lv_obj_set_pos(label_back, 330, 70);

	dsp1 = lv_switch_create(Tela_Gpio);
    lv_obj_add_event_cb(dsp1, event_dsp1_handler, LV_EVENT_ALL, NULL);
    lv_obj_add_flag(dsp1, LV_OBJ_FLAG_CHECKABLE);
//    if(HAL_GPIO_ReadPin(DSP1_GPIO_Port, DSP1_Pin)) {
//    	lv_obj_add_state(dsp1, LV_STATE_CHECKED);
//    }
//    else {
    	lv_obj_clear_state(dsp1, LV_STATE_CHECKED);
//    }
    lv_obj_set_pos(dsp1, 370, 94);

    lv_obj_t * label_high = lv_label_create(Tela_Gpio);
    lv_obj_add_style(label_high, &style_txt, LV_PART_MAIN);
    lv_label_set_text(label_high, "HIGH");
    lv_obj_align_to(label_high, dsp1, LV_ALIGN_OUT_RIGHT_MID, 5, 0);

    lv_obj_t * label_low = lv_label_create(Tela_Gpio);
    lv_obj_add_style(label_low, &style_txt, LV_PART_MAIN);
    lv_label_set_text(label_low, "LOW");
    lv_obj_align_to(label_low, dsp1, LV_ALIGN_OUT_LEFT_MID, -5, 0);
}

static void event_dsp2_handler(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * obj = lv_event_get_target(e);

    if(code == LV_EVENT_VALUE_CHANGED) {
    	if(lv_obj_has_state(obj, LV_STATE_CHECKED)) {
    		  //HAL_GPIO_WritePin(DSP2_GPIO_Port, DSP2_Pin, GPIO_PIN_SET);
    	}
    	else {
    		//HAL_GPIO_WritePin(DSP2_GPIO_Port, DSP2_Pin, GPIO_PIN_RESET);
    	}
    }
}

void Set_DSP2(void)
{
	static lv_style_t style_txt;
	lv_style_init(&style_txt);
	lv_style_set_text_color(&style_txt, lv_color_hex(0xFFFFFF));

    label_back = lv_label_create(Tela_Gpio);
    lv_obj_add_style(label_back, &style_txt, LV_PART_MAIN);
    lv_label_set_text(label_back, "DSP 2:");
    lv_obj_set_pos(label_back, 330, 134);

	dsp2 = lv_switch_create(Tela_Gpio);
    lv_obj_add_event_cb(dsp2, event_dsp2_handler, LV_EVENT_ALL, NULL);
    lv_obj_add_flag(dsp2, LV_OBJ_FLAG_CHECKABLE);
//    if(HAL_GPIO_ReadPin(DSP2_GPIO_Port, DSP2_Pin)) {
//    	lv_obj_add_state(dsp2, LV_STATE_CHECKED);
//    }
//    else {
    	lv_obj_clear_state(dsp2, LV_STATE_CHECKED);
//    }
    lv_obj_set_pos(dsp2, 370, 158);

    lv_obj_t * label_high = lv_label_create(Tela_Gpio);
    lv_obj_add_style(label_high, &style_txt, LV_PART_MAIN);
    lv_label_set_text(label_high, "HIGH");
    lv_obj_align_to(label_high, dsp2, LV_ALIGN_OUT_RIGHT_MID, 5, 0);

    lv_obj_t * label_low = lv_label_create(Tela_Gpio);
    lv_obj_add_style(label_low, &style_txt, LV_PART_MAIN);
    lv_label_set_text(label_low, "LOW");
    lv_obj_align_to(label_low, dsp2, LV_ALIGN_OUT_LEFT_MID, -5, 0);
}


static void event_toslink_handler(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * obj = lv_event_get_target(e);

    if(code == LV_EVENT_VALUE_CHANGED) {
    	if(lv_obj_has_state(obj, LV_STATE_CHECKED)) {
    		  //HAL_GPIO_WritePin(AES_TOSLINK_GPIO_Port, AES_TOSLINK_Pin, GPIO_PIN_SET);
    	}
    	else {
    		//HAL_GPIO_WritePin(AES_TOSLINK_GPIO_Port, AES_TOSLINK_Pin, GPIO_PIN_RESET);
    	}
    }
}

void Set_Toslink(void)
{
	static lv_style_t style_txt;
	lv_style_init(&style_txt);
	lv_style_set_text_color(&style_txt, lv_color_hex(0xFFFFFF));

    label_back = lv_label_create(Tela_Gpio);
    lv_obj_add_style(label_back, &style_txt, LV_PART_MAIN);
    lv_label_set_text(label_back, "TOSLINK:");
    lv_obj_set_pos(label_back, 330, 201);

	toslink = lv_switch_create(Tela_Gpio);
    lv_obj_add_event_cb(toslink, event_toslink_handler, LV_EVENT_ALL, NULL);
    lv_obj_add_flag(toslink, LV_OBJ_FLAG_CHECKABLE);
 //   if(HAL_GPIO_ReadPin(AES_TOSLINK_GPIO_Port, AES_TOSLINK_Pin)) {
 //   	lv_obj_add_state(toslink, LV_STATE_CHECKED);
 //   }
 //   else {
    	lv_obj_clear_state(toslink, LV_STATE_CHECKED);
 //   }
    lv_obj_set_pos(toslink, 370, 222);

    lv_obj_t * label_high = lv_label_create(Tela_Gpio);
    lv_obj_add_style(label_high, &style_txt, LV_PART_MAIN);
    lv_label_set_text(label_high, "HIGH");
    lv_obj_align_to(label_high, toslink, LV_ALIGN_OUT_RIGHT_MID, 5, 0);

    lv_obj_t * label_low = lv_label_create(Tela_Gpio);
    lv_obj_add_style(label_low, &style_txt, LV_PART_MAIN);
    lv_label_set_text(label_low, "LOW");
    lv_obj_align_to(label_low, toslink, LV_ALIGN_OUT_LEFT_MID, -5, 0);
}

static void event_impedance_handler(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * obj = lv_event_get_target(e);

    if(code == LV_EVENT_VALUE_CHANGED) {
    	if(lv_obj_has_state(obj, LV_STATE_CHECKED)) {
    		  //HAL_GPIO_WritePin(IMP_10K_600_GPIO_Port, IMP_10K_600_Pin, GPIO_PIN_SET);
    	}
    	else {
    		//HAL_GPIO_WritePin(IMP_10K_600_GPIO_Port, IMP_10K_600_Pin, GPIO_PIN_RESET);
    	}
    }
}

void Set_Impedance(void)
{
	static lv_style_t style_txt;
	lv_style_init(&style_txt);
	lv_style_set_text_color(&style_txt, lv_color_hex(0xFFFFFF));

    label_back = lv_label_create(Tela_Gpio);
    lv_obj_add_style(label_back, &style_txt, LV_PART_MAIN);
    lv_label_set_text(label_back, "IMPEDANCE:");
    lv_obj_set_pos(label_back, 185, 2);

	impedance = lv_switch_create(Tela_Gpio);
    lv_obj_add_event_cb(impedance, event_impedance_handler, LV_EVENT_ALL, NULL);
    lv_obj_add_flag(impedance, LV_OBJ_FLAG_CHECKABLE);
//    if(HAL_GPIO_ReadPin(IMP_10K_600_GPIO_Port, IMP_10K_600_Pin)) {
//    	lv_obj_add_state(impedance, LV_STATE_CHECKED);
//    }
//    else {
    	lv_obj_clear_state(impedance, LV_STATE_CHECKED);
//    }
    lv_obj_set_pos(impedance, 213, 30);

    lv_obj_t * label_high = lv_label_create(Tela_Gpio);
    lv_obj_add_style(label_high, &style_txt, LV_PART_MAIN);
    lv_label_set_text(label_high, "600R");
    lv_obj_align_to(label_high, impedance, LV_ALIGN_OUT_RIGHT_MID, 5, 0);

    lv_obj_t * label_low = lv_label_create(Tela_Gpio);
    lv_obj_add_style(label_low, &style_txt, LV_PART_MAIN);
    lv_label_set_text(label_low, "10K");
    lv_obj_align_to(label_low, impedance, LV_ALIGN_OUT_LEFT_MID, -5, 0);
}

void print_line_1(void)
{
    /*Create an array for the points of the line*/
	static lv_point_precise_t line_points1[] = { {110, 10}, {110, 256} };
	static lv_point_precise_t line_points2[] = { {170, 10}, {170, 256} };

    /*Create style*/
    static lv_style_t style_line;
    lv_style_init(&style_line);
    lv_style_set_line_width(&style_line, 2);
    lv_style_set_line_color(&style_line, lv_palette_main(LV_PALETTE_GREY));
    lv_style_set_line_rounded(&style_line, true);

    /*Create a line and apply the new style*/
    lv_obj_t * line1;
    line1 = lv_line_create(Tela_Gpio);
    lv_line_set_points(line1, line_points1, 2);     /*Set the points*/
    lv_obj_add_style(line1, &style_line, 0);
    lv_obj_set_pos(line1, 50, 4);


    /*Create a line and apply the new style*/
    lv_obj_t * line2;
    line2 = lv_line_create(Tela_Gpio);
    lv_line_set_points(line2, line_points2, 2);     /*Set the points*/
    lv_obj_add_style(line2, &style_line, 0);
    lv_obj_set_pos(line2, 150, 4);
}
