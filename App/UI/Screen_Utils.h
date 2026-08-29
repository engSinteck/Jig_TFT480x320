/*
 * Screen_Utils.h
 *
 *  Created on: 27 de ago. de 2026
 *      Author: rinaldo.santos
 */

#ifndef UI_SCREEN_UTILS_H_
#define UI_SCREEN_UTILS_H_

#include "main.h"
#include "lvgl.h"

enum page {
	PAGE_MAIN = 0,
	PAGE_CONFIG
};

void create_button_back_main(lv_obj_t * parent, int32_t x, int32_t y, uint32_t page);
void create_text_footer(lv_obj_t * parent);

#endif /* UI_SCREEN_UTILS_H_ */
