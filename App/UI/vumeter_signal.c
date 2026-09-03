/*
 * vumeter_signal.c
 *
 *  Created on: 2 de set. de 2026
 *      Author: rinaldo.santos
 */

#include "lvgl.h"

extern lv_obj_t * Tela_Config_Signal;
extern lv_obj_t * Tela_Menu_TUNER;

/* Imagens Vu-Meter */
LV_IMG_DECLARE(LED_50_OFF);
LV_IMG_DECLARE(LED_50_ON);

LV_IMG_DECLARE(LED_50_MPX_OFF);
LV_IMG_DECLARE(LED_50_MPX_ON);


/* ----------------------------- CONFIG ----------------------------- */
#define VU_50_W        348
#define VU_50_H         28
#define VU_50_RANGE     50
/* Quantos SEGMENTOS de LED existem desenhados na imagem de 445px.
 * Se cada unidade do range e 1 segmento, use 64. Se a barra e continua
 * (sem segmentos), coloque VU_W p/ nao quantizar. CONFIRME NA SUA ARTE. */
#define VU_50_SEGMENTS	50

/* ----------------------------- MODELO ----------------------------- */
typedef struct {
    lv_obj_t *             on;       /* camada acesa (clipada)          */
    int32_t                last_seg; /* ultimo segmento (guard)         */
    int16_t                x, y, w, h;
    int16_t                range, segs;
    const int16_t *        bounds;   /* tabela de bordas em px (NULL=linear) */
    const lv_image_dsc_t * img_off;
    const lv_image_dsc_t * img_on;
} vumeter_50_t;

/* Left e Right. Ajuste x/y do RIGHT p/ a posicao real na sua tela.       */
static vumeter_50_t s_vu_left = {
    .on=NULL,
	.last_seg=-1,
	.x=31,
	.y=252,
	.w=VU_50_W,
	.h=VU_50_H,
    .range=VU_50_RANGE,
	.segs=VU_50_SEGMENTS,
	.bounds=NULL,
    .img_off=&LED_50_OFF,
	.img_on=&LED_50_ON
};

static vumeter_50_t s_vu_right = {
    .on=NULL,
	.last_seg=-1,
	.x=31,
	.y=289,
	.w=VU_50_W,
	.h=VU_50_H,   /* <-- y do RIGHT */
    .range=VU_50_RANGE,
	.segs=VU_50_SEGMENTS,
	.bounds=NULL,
    .img_off=&LED_50_OFF,
	.img_on=&LED_50_ON
};

static vumeter_50_t s_vu_mpx = {
    .on=NULL,
	.last_seg=-1,
	.x=31,
	.y=224,
	.w=VU_50_W,
	.h=VU_50_H,   /* <-- y do RIGHT */
    .range=VU_50_RANGE,
	.segs=VU_50_SEGMENTS,
	.bounds=NULL,
    .img_off=&LED_50_MPX_OFF,
	.img_on=&LED_50_MPX_ON
};

// Tela Tuner
/* Left e Right. Ajuste x/y do RIGHT p/ a posicao real na sua tela.       */
static vumeter_50_t t_vu_left = {
    .on=NULL,
	.last_seg=-1,
	.x=31,
	.y=252,
	.w=VU_50_W,
	.h=VU_50_H,
    .range=VU_50_RANGE,
	.segs=VU_50_SEGMENTS,
	.bounds=NULL,
    .img_off=&LED_50_OFF,
	.img_on=&LED_50_ON
};

static vumeter_50_t t_vu_right = {
    .on=NULL,
	.last_seg=-1,
	.x=31,
	.y=289,
	.w=VU_50_W,
	.h=VU_50_H,   /* <-- y do RIGHT */
    .range=VU_50_RANGE,
	.segs=VU_50_SEGMENTS,
	.bounds=NULL,
    .img_off=&LED_50_OFF,
	.img_on=&LED_50_ON
};

static vumeter_50_t t_vu_mpx = {
    .on=NULL,
	.last_seg=-1,
	.x=31,
	.y=224,
	.w=VU_50_W,
	.h=VU_50_H,   /* <-- y do RIGHT */
    .range=VU_50_RANGE,
	.segs=VU_50_SEGMENTS,
	.bounds=NULL,
    .img_off=&LED_50_MPX_OFF,
	.img_on=&LED_50_MPX_ON
};

/* --------------------------- INTERNOS ----------------------------- */
/* segmento -> largura em pixels (borda linear ou por tabela nao-linear) */
static int32_t seg_to_px_50(const vumeter_50_t * vu, int32_t seg)
{
    if (seg <= 0)          return 0;
    if (seg >= vu->segs)   return vu->w;
    if (vu->bounds)        return vu->bounds[seg];       /* escala nao-linear */
    return (seg * vu->w) / vu->segs;                     /* escala linear     */
}

static void vumeter_50_create(vumeter_50_t * vu, lv_obj_t * parent)
{
    /* fundo estatico: desenhado UMA vez, nunca mais invalida */
    lv_obj_t * bg = lv_image_create(parent);
    lv_image_set_src(bg, vu->img_off);
    lv_obj_set_pos(bg, vu->x, vu->y);

    /* barra acesa: imagem CLIPADA (nao escalada) pela largura do objeto */
    vu->on = lv_image_create(parent);
    lv_image_set_src(vu->on, vu->img_on);
    lv_image_set_inner_align(vu->on, LV_IMAGE_ALIGN_TOP_LEFT);
    lv_obj_set_pos(vu->on, vu->x, vu->y);
    lv_obj_set_height(vu->on, vu->h);
    lv_obj_set_width(vu->on, 0);
    vu->last_seg = -1;
}

static void vumeter_50_set(vumeter_50_t * vu, int32_t value)
{
    if (value < 0)         value = 0;
    if (value > vu->range) value = vu->range;

    /* valor -> nº de segmentos acesos (arredonda ao mais proximo) */
    int32_t seg = (value * vu->segs + vu->range / 2) / vu->range;

    if (seg == vu->last_seg) return;         /* nada mudou -> NAO invalida */
    vu->last_seg = seg;

    lv_obj_set_width(vu->on, seg_to_px_50(vu, seg)); /* so a faixa alterada */
}

/* ---------------------- API (mesma que voce usa) ------------------ */
void create_vumeter_50_left(void)   { vumeter_50_create(&s_vu_left,  Tela_Config_Signal); }
void create_vumeter_50_right(void)  { vumeter_50_create(&s_vu_right, Tela_Config_Signal); }
void create_vumeter_50_mpx(void)    { vumeter_50_create(&s_vu_mpx,   Tela_Config_Signal); }

// Tela Tuner
void create_vumeter_50_left_tuner(void)   { vumeter_50_create(&t_vu_left,  Tela_Menu_TUNER); }
void create_vumeter_50_right_tuner(void)  { vumeter_50_create(&t_vu_right, Tela_Menu_TUNER); }
void create_vumeter_50_mpx_tuner(void)    { vumeter_50_create(&t_vu_mpx,   Tela_Menu_TUNER); }

void set_vumeter_50_left(int32_t value)  { vumeter_50_set(&s_vu_left,  value); }
void set_vumeter_50_right(int32_t value) { vumeter_50_set(&s_vu_right, value); }
void set_vumeter_50_mpx(int32_t value)   { vumeter_50_set(&s_vu_mpx, value); }

// Tela Tuner
void set_vumeter_50_left_tuner(int32_t value)  { vumeter_50_set(&t_vu_left,  value); }
void set_vumeter_50_right_tuner(int32_t value) { vumeter_50_set(&t_vu_right, value); }
void set_vumeter_50_mpx_tuner(int32_t value)   { vumeter_50_set(&t_vu_mpx, value); }
