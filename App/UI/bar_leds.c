#include "../App/UI/bar_leds.h"

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

    // Fixa o pivo no canto superior esquerdo (0,0) antes de rotacionar
    lv_obj_set_style_transform_pivot_x(bg, 0, 0);
    lv_obj_set_style_transform_pivot_y(bg, 0, 0);
    lv_obj_set_style_transform_rotation(bg, bar->rotation, 0);
    lv_image_set_inner_align(bg, LV_IMAGE_ALIGN_BOTTOM_LEFT);

    lv_obj_set_pos(bg, bar->x, bar->y);

    /* barra acesa: imagem CLIPADA (nao escalada) pela largura do objeto */
    bar->on = lv_image_create(parent);
    lv_image_set_src(bar->on, bar->img_on);

    // Fixa o pivô no mesmo ponto para acompanhar sem deslocar o centro
    lv_obj_set_style_transform_pivot_x(bar->on, 0, 0);
    lv_obj_set_style_transform_pivot_y(bar->on, 0, 0);
    lv_obj_set_style_transform_rotation(bar->on, bar->rotation, 0);

    lv_image_set_inner_align(bar->on, LV_IMAGE_ALIGN_BOTTOM_LEFT);
    lv_obj_set_height(bar->on, 0);
    lv_obj_set_width(bar->on, bar->w);
    lv_obj_set_pos(bar->on, bar->x, bar->y + bar->h);
    bar->last_seg = -1;
}

/*
void barmeter_set(barmeter_t * bar, int32_t value)
{
    if (value < 0)         value = 0;
    if (value > bar->range) value = bar->range;

    // valor -> nº de segmentos acesos (arredonda ao mais proximo)
    int32_t seg = (value * bar->segs + bar->range / 2) / bar->range;

    if (seg == bar->last_seg) return;         // nada mudou -> NAO invalida
    bar->last_seg = seg;

    int32_t px_h = bar_seg_to_px(bar, seg);

    // Ajusta a altura da janela visível e reposiciona o Y para crescer subindo
    lv_obj_set_height(bar->on, px_h);
    lv_obj_set_y(bar->on, bar->y + (bar->h - px_h));
}
*/

void barmeter_set(barmeter_t * bar, int32_t value)
{
    if (value < 0)          value = 0;
    if (value > bar->range) value = bar->range;

    int32_t seg = (value * bar->segs + bar->range / 2) / bar->range;
    if (seg == bar->last_seg) return;
    bar->last_seg = seg;

    int32_t px_h = bar_seg_to_px(bar, seg);

    /* janela visível cresce a partir da base — frame LOCAL, sem rotação */
    lv_obj_set_height(bar->on, px_h);
    lv_obj_set_y(bar->on, bar->y + (bar->h - px_h));

    /* trava o centro de rotação em (bar->x, bar->y), como o fundo:
       centro_abs_y = obj_y + pivot_y = (y + h - px_h) + (px_h - h) = y  */
    lv_obj_set_style_transform_pivot_x(bar->on, 0, 0);
    lv_obj_set_style_transform_pivot_y(bar->on, px_h - bar->h, 0);
}

void barmeter_set_manual_image(barmeter_t * bar, int32_t value)
{
    if (value < 0)         value = 0;
    if (value > bar->range) value = bar->range;

    int32_t seg = (value * bar->segs + bar->range / 2) / bar->range;
    if (seg == bar->last_seg) return;
    bar->last_seg = seg;

    int32_t px_h = bar_seg_to_px(bar, seg);

    if (bar->rotation == 900) {
        /* Em 90°, o corte de altura vira variação no eixo X e a origem se desloca */
        lv_obj_set_width(bar->on, px_h);
        lv_obj_set_x(bar->on, bar->x + bar->h); // Ajusta o deslocamento do pivô do quadrante
    } else {
        /* Comportamento padrão em 0° */
        lv_obj_set_height(bar->on, px_h);
        lv_obj_set_y(bar->on, bar->y + (bar->h - px_h));
    }
}
