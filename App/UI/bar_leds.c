#include "lvgl.h"

extern lv_obj_t * Tela_Inputs;

/* Imagens Vu-Meter */
LV_IMG_DECLARE(LED_OFF);
LV_IMG_DECLARE(LED);

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
} barmeter_t;

/* Left e Right. Ajuste x/y do RIGHT p/ a posicao real na sua tela.       */
static barmeter_t g_bar_left = {
    .on=NULL,
	.last_seg=-1,
	.x=10,
	.y=40,
	.w=BAR_W,
	.h=BAR_H,
    .range=BAR_RANGE,
	.segs=BAR_SEGMENTS,
	.bounds=NULL,
    .img_off=&LED_OFF,
	.img_on=&LED
};

static barmeter_t g_bar_right = {
    .on=NULL,
	.last_seg=-1,
	.x=33,
	.y=40,
	.w=BAR_W,
	.h=BAR_H,   /* <-- y do RIGHT */
    .range=BAR_RANGE,
	.segs=BAR_SEGMENTS,
	.bounds=NULL,
    .img_off=&LED_OFF,
	.img_on=&LED
};

/* --------------------------- INTERNOS ----------------------------- */
/* segmento -> largura em pixels (borda linear ou por tabela nao-linear) */
static int32_t bar_seg_to_px(const barmeter_t * vu, int32_t seg)
{
    if (seg <= 0)          return 0;
    if (seg >= vu->segs)   return vu->w;
    if (vu->bounds)        return vu->bounds[seg];       /* escala nao-linear */
    return (seg * vu->w) / vu->segs;                     /* escala linear     */
}

static void barmeter_create(barmeter_t * bar, lv_obj_t * parent)
{
    /* fundo estatico: desenhado UMA vez, nunca mais invalida */
    lv_obj_t * bg = lv_image_create(parent);
    lv_image_set_src(bg, bar->img_off);
    lv_obj_set_pos(bg, bar->x, bar->y);

    /* barra acesa: imagem CLIPADA (nao escalada) pela largura do objeto */
    bar->on = lv_image_create(parent);
    lv_image_set_src(bar->on, bar->img_on);
    lv_image_set_inner_align(bar->on, LV_IMAGE_ALIGN_TOP_LEFT);
    lv_obj_set_pos(bar->on, bar->x, bar->y);
    lv_obj_set_height(bar->on, bar->h);
    lv_obj_set_width(bar->on, 0);
    bar->last_seg = -1;
}

static void barmeter_set(barmeter_t * bar, int32_t value)
{
    if (value < 0)         value = 0;
    if (value > bar->range) value = bar->range;

    /* valor -> nº de segmentos acesos (arredonda ao mais proximo) */
    int32_t seg = (value * bar->segs + bar->range / 2) / bar->range;

    if (seg == bar->last_seg) return;         /* nada mudou -> NAO invalida */
    bar->last_seg = seg;

    lv_obj_set_width(bar->on, bar_seg_to_px(bar, seg)); /* so a faixa alterada */
}

/* ---------------------- API (mesma que voce usa) ------------------ */
void create_barmeter_left(void)   { barmeter_create(&g_bar_left,  Tela_Inputs); }
void create_barmeter_right(void)  { barmeter_create(&g_bar_right, Tela_Inputs); }

void set_barmeter_left(int32_t value)  { barmeter_set(&g_bar_left,  value); }
void set_barmeter_right(int32_t value) { barmeter_set(&g_bar_right, value); }
