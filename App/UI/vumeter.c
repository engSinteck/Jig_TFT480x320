#include "lvgl.h"

#include "../App/UI/Screen_Main.h"

/* Imagens (C-array). IDEAL: RGB565 SEM alpha p/ blit direto por DMA2D. */
extern const lv_image_dsc_t LED_GR_OFF;   /* barra apagada (fundo) */
extern const lv_image_dsc_t LED_GR;       /* barra acesa (cresce)  */

/* ----------------------------- CONFIG ----------------------------- */
#define VU_W        445
#define VU_H         28
#define VU_RANGE     64

/* Quantos SEGMENTOS de LED existem desenhados na imagem de 445px.
 * Se cada unidade do range e 1 segmento, use 64. Se a barra e continua
 * (sem segmentos), coloque VU_W p/ nao quantizar. CONFIRME NA SUA ARTE. */
#define VU_SEGMENTS  64

/* ----------------------------- MODELO ----------------------------- */
typedef struct {
    lv_obj_t *             on;       /* camada acesa (clipada)          */
    int32_t                last_seg; /* ultimo segmento (guard)         */
    int16_t                x, y, w, h;
    int16_t                range, segs;
    const int16_t *        bounds;   /* tabela de bordas em px (NULL=linear) */
    const lv_image_dsc_t * img_off;
    const lv_image_dsc_t * img_on;
} vumeter_t;

/* Left e Right. Ajuste x/y do RIGHT p/ a posicao real na sua tela.       */
static vumeter_t g_vu_left = {
    .on=NULL, .last_seg=-1, .x=31, .y=228, .w=VU_W, .h=VU_H,
    .range=VU_RANGE, .segs=VU_SEGMENTS, .bounds=NULL,
    .img_off=&LED_GR_OFF, .img_on=&LED_GR
};
static vumeter_t g_vu_right = {
    .on=NULL, .last_seg=-1, .x=31, .y=258, .w=VU_W, .h=VU_H,   /* <-- y do RIGHT */
    .range=VU_RANGE, .segs=VU_SEGMENTS, .bounds=NULL,
    .img_off=&LED_GR_OFF, .img_on=&LED_GR
};

/* --------------------------- INTERNOS ----------------------------- */
/* segmento -> largura em pixels (borda linear ou por tabela nao-linear) */
static int32_t seg_to_px(const vumeter_t * vu, int32_t seg)
{
    if (seg <= 0)          return 0;
    if (seg >= vu->segs)   return vu->w;
    if (vu->bounds)        return vu->bounds[seg];       /* escala nao-linear */
    return (seg * vu->w) / vu->segs;                     /* escala linear     */
}

static void vumeter_create(vumeter_t * vu, lv_obj_t * parent)
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

static void vumeter_set(vumeter_t * vu, int32_t value)
{
    if (value < 0)         value = 0;
    if (value > vu->range) value = vu->range;

    /* valor -> nº de segmentos acesos (arredonda ao mais proximo) */
    int32_t seg = (value * vu->segs + vu->range / 2) / vu->range;

    if (seg == vu->last_seg) return;         /* nada mudou -> NAO invalida */
    vu->last_seg = seg;

    lv_obj_set_width(vu->on, seg_to_px(vu, seg)); /* so a faixa alterada */
}

/* ---------------------- API (mesma que voce usa) ------------------ */
void create_vumeter_left(void)   { vumeter_create(&g_vu_left,  Tela_Main); }
void create_vumeter_right(void)  { vumeter_create(&g_vu_right, Tela_Main); }

void set_vumeter_left(int32_t value)  { vumeter_set(&g_vu_left,  value); }
void set_vumeter_right(int32_t value) { vumeter_set(&g_vu_right, value); }
