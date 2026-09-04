/*
 * bar_leds.h
 *
 *  Created on: 27 de ago. de 2026
 *      Author: rinaldo.santos
 */

#ifndef UI_BAR_LEDS_H_
#define UI_BAR_LEDS_H_

#include "main.h"
#include "lvgl.h"

/* ----------------------------- CONFIG ----------------------------- */
#define BAR_W         21
#define BAR_H         84
#define BAR_RANGE     13
/* Quantos SEGMENTOS de LED existem desenhados na imagem de 445px.
 * Se cada unidade do range e 1 segmento, use 64. Se a barra e continua
 * (sem segmentos), coloque VU_W p/ nao quantizar. CONFIRME NA SUA ARTE. */
#define BAR_SEGMENTS  13

/* ----------------------------- MODELO ----------------------------- */
typedef struct {
    lv_obj_t *             on;       /* camada acesa (clipada)          */
    int32_t                last_seg; /* ultimo segmento (guard)         */
    int16_t                x, y, w, h;
    int16_t                range, segs;
    const int16_t *        bounds;   /* tabela de bordas em px (NULL=linear) */
    const lv_image_dsc_t * img_off;
    const lv_image_dsc_t * img_on;
    int32_t				   rotation;
} barmeter_t;

void barmeter_create(lv_obj_t * parent, barmeter_t * bar);
void barmeter_set(barmeter_t * bar, int32_t value);
void barmeter_set_manual_image(barmeter_t * bar, int32_t value);

#endif /* UI_BAR_LEDS_H_ */
