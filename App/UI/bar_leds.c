#include "../App/UI/bar_leds.h"

/* Imagens Vu-Meter */
LV_IMG_DECLARE(LED_OFF);
LV_IMG_DECLARE(LED);

/* --------------------------- INTERNOS ----------------------------- */
/* segmento -> largura em pixels (borda linear ou por tabela nao-linear) */
static int32_t bar_seg_to_px(const barmeter_t * vu, int32_t seg)
{
    if (seg <= 0)          return 0;
    if (seg >= vu->segs)   return vu->h;
    if (vu->bounds)        return vu->bounds[seg];       /* escala nao-linear */
    return (seg * vu->h) / vu->segs;                     /* escala linear     */
}

void barmeter_create(lv_obj_t * parent, barmeter_t * bar)
{
    /* fundo estatico: desenhado UMA vez, nunca mais invalida */
    lv_obj_t * bg = lv_image_create(parent);
    lv_image_set_src(bg, bar->img_off);
    lv_obj_set_style_transform_rotation(bg, bar->rotation, 0);
    lv_obj_set_pos(bg, bar->x, bar->y);

    /* barra acesa: imagem CLIPADA (nao escalada) pela largura do objeto */
    bar->on = lv_image_create(parent);
    lv_image_set_src(bar->on, bar->img_on);
    lv_obj_set_style_transform_rotation(bar->on, bar->rotation, 0);

    lv_image_set_inner_align(bar->on, LV_IMAGE_ALIGN_BOTTOM_LEFT);
    lv_obj_set_height(bar->on, 0);
    lv_obj_set_width(bar->on, bar->w);
    lv_obj_set_pos(bar->on, bar->x, bar->y + bar->h);
    bar->last_seg = -1;
}

void barmeter_set(barmeter_t * bar, int32_t value)
{
    if (value < 0)         value = 0;
    if (value > bar->range) value = bar->range;

    /* valor -> nº de segmentos acesos (arredonda ao mais proximo) */
    int32_t seg = (value * bar->segs + bar->range / 2) / bar->range;

    if (seg == bar->last_seg) return;         /* nada mudou -> NAO invalida */
    bar->last_seg = seg;

    int32_t px_h = bar_seg_to_px(bar, seg);

    // Ajusta a altura da janela visível e reposiciona o Y para crescer subindo
    lv_obj_set_height(bar->on, px_h);
    lv_obj_set_y(bar->on, bar->y + (bar->h - px_h));
}
