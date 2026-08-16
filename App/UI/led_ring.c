#include "led_ring.h"

/* ======================= GEOMETRIA (medida da figura) =======================
 * 20 LEDs num ARCO de ~214 graus, centrado no TOPO, com vao (~146) embaixo.
 * Convencao: 0 = topo, sentido horario.
 *   phi=0 topo | 90 direita | 180 fundo | 270 esquerda
 * -------------------------------------------------------------------------- */
#define LED_COUNT        20      /* numero de LEDs                            */
#define ARC_SWEEP_DEG   214      /* abertura ocupada pelos LEDs (graus)       */
#define ARC_ROTATE_DEG    0      /* gira o conjunto; 0 => gap no fundo        */

#define RING_BOX         90      /* lado da caixa/knob (px)                   */
#define KNOB_SIZE        70      /* diametro do botao central (px)            */
#define RING_RADIUS      40      /* raio do CENTRO dos LEDs (px)              */
#define DOT_SIZE          6      /* diametro de cada LED (px)                 */

/* --- ajuste fino da POSICAO do anel DENTRO da caixa (px, +/-) --- */
#define RING_CX_OFF       0      /* desloca centro do anel em X              */
#define RING_CY_OFF       0      /* desloca centro do anel em Y              */

/* --- POSICAO do conjunto no LCD (canto sup-esq da caixa, em px do pai) --- */
/*     deixe -1 para usar o alinhamento automatico (lv_obj_align).          */
#define KNOB_LCD_X       386
#define KNOB_LCD_Y        95

#define COLOR_ON     0x1E90FF    /* azul aceso    */
#define COLOR_OFF    0x14283C    /* azul apagado  */

/* ============================== ESTADO ============================== */
typedef struct {
    lv_obj_t * dots[LED_COUNT];
    int32_t    value;
    int32_t    max;
} led_ring_t;

static led_ring_t g_ring;

/* ============================ INTERNOS ============================== */
static void ring_refresh(void)
{
    for (int i = 0; i < g_ring.max; i++) {
        lv_color_t c = (i < g_ring.value) ? lv_color_hex(COLOR_ON)
                                          : lv_color_hex(COLOR_OFF);
        lv_obj_set_style_bg_color(g_ring.dots[i], c, 0);
        /* Glow OPCIONAL so no aceso (cuidado: pouco espaco entre LEDs!):
        if (i < g_ring.value) {
            lv_obj_set_style_shadow_width(g_ring.dots[i], 2, 0);
            lv_obj_set_style_shadow_spread(g_ring.dots[i], 0, 0);
            lv_obj_set_style_shadow_color(g_ring.dots[i], lv_color_hex(COLOR_ON), 0);
        } else {
            lv_obj_set_style_shadow_width(g_ring.dots[i], 0, 0);
        }
        */
    }
}

//static void plus_cb(lv_event_t * e)  { (void)e; led_ring_inc(); }
//static void minus_cb(lv_event_t * e) { (void)e; led_ring_dec(); }

/* ============================ API PUBLICA ========================== */
void led_ring_inc(void)
{ if (g_ring.value < g_ring.max) { g_ring.value++; ring_refresh(); } }

void led_ring_dec(void)
{ if (g_ring.value > 0) { g_ring.value--; ring_refresh(); } }

void led_ring_set(int32_t value)
{
    if (value < 0)          value = 0;
    if (value > g_ring.max) value = g_ring.max;
    g_ring.value = value; ring_refresh();
}
int32_t led_ring_get(void) { return g_ring.value; }

/* ============================ CONSTRUCAO ========================== */
void led_ring_create(lv_obj_t * parent)
{
    g_ring.value = 0;
    g_ring.max   = LED_COUNT;

    /* ---- caixa ---- */
    lv_obj_t * box = lv_obj_create(parent);
    lv_obj_set_size(box, RING_BOX, RING_BOX);
#if (KNOB_LCD_X >= 0) && (KNOB_LCD_Y >= 0)
    lv_obj_set_pos(box, KNOB_LCD_X, KNOB_LCD_Y);   /* posicao ABSOLUTA no LCD */
#else
    lv_obj_align(box, LV_ALIGN_TOP_MID, 0, 6);     /* posicao automatica      */
#endif
    lv_obj_set_style_bg_color(box, lv_color_hex(0x000000), 0);
    lv_obj_set_style_radius(box, LV_RADIUS_CIRCLE, 0);
    lv_obj_set_style_border_width(box, 0, 0);
    lv_obj_set_style_pad_all(box, 0, 0);
    lv_obj_remove_flag(box, LV_OBJ_FLAG_SCROLLABLE);

    /* ---- botao central 70x70 ---- */
    lv_obj_t * knob = lv_obj_create(box);
    lv_obj_set_size(knob, KNOB_SIZE, KNOB_SIZE);
    lv_obj_center(knob);
    lv_obj_set_style_bg_color(knob, lv_color_hex(0x101418), 0);
    lv_obj_set_style_radius(knob, LV_RADIUS_CIRCLE, 0);
    lv_obj_set_style_border_color(knob, lv_color_hex(0x2A2F35), 0);
    lv_obj_set_style_border_width(knob, 2, 0);
    lv_obj_remove_flag(knob, LV_OBJ_FLAG_SCROLLABLE);

    /* ---- LEDs (lv_obj = controle total, sem glow automatico) ---- */
    const int32_t cx = RING_BOX / 2 + RING_CX_OFF;
    const int32_t cy = RING_BOX / 2 + RING_CY_OFF;
    const int32_t sweep_c = ARC_SWEEP_DEG * 100;
    const int32_t step_c  = sweep_c / (LED_COUNT - 1);
    const int32_t base_c  = ARC_ROTATE_DEG * 100 - sweep_c / 2;

    for (int i = 0; i < LED_COUNT; i++) {
        int32_t phi_c = base_c + i * step_c;
        int16_t phi   = (int16_t)((phi_c + (phi_c >= 0 ? 50 : -50)) / 100);

        /* 0=topo, horario:  x = cx + r*sin(phi) ; y = cy - r*cos(phi) */
        int32_t x = cx + (RING_RADIUS * lv_trigo_sin(phi)) / LV_TRIGO_SIN_MAX;
        int32_t y = cy - (RING_RADIUS * lv_trigo_cos(phi)) / LV_TRIGO_SIN_MAX;

        lv_obj_t * dot = lv_obj_create(box);
        lv_obj_remove_style_all(dot);                 /* zera borda/pad/scroll */
        lv_obj_remove_flag(dot, LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_CLICKABLE);
        lv_obj_set_size(dot, DOT_SIZE, DOT_SIZE);
        lv_obj_set_style_radius(dot, LV_RADIUS_CIRCLE, 0);
        lv_obj_set_style_bg_opa(dot, LV_OPA_COVER, 0);
        lv_obj_set_pos(dot, x - DOT_SIZE / 2, y - DOT_SIZE / 2);
        g_ring.dots[i] = dot;
    }

    ring_refresh();

    /* ---- botoes  -  e  +  ---- */
//    lv_obj_t * btn_minus = lv_button_create(parent);
//    lv_obj_set_size(btn_minus, 72, 46);
//    lv_obj_align(btn_minus, LV_ALIGN_BOTTOM_LEFT, 6, -6);
//    lv_obj_add_event_cb(btn_minus, minus_cb, LV_EVENT_CLICKED, NULL);
//    lv_obj_add_event_cb(btn_minus, minus_cb, LV_EVENT_LONG_PRESSED_REPEAT, NULL);
//    lv_obj_t * lm = lv_label_create(btn_minus);
//    lv_label_set_text(lm, LV_SYMBOL_MINUS); lv_obj_center(lm);
//
//    lv_obj_t * btn_plus = lv_button_create(parent);
//    lv_obj_set_size(btn_plus, 72, 46);
//    lv_obj_align(btn_plus, LV_ALIGN_BOTTOM_RIGHT, -6, -6);
//    lv_obj_add_event_cb(btn_plus, plus_cb, LV_EVENT_CLICKED, NULL);
//    lv_obj_add_event_cb(btn_plus, plus_cb, LV_EVENT_LONG_PRESSED_REPEAT, NULL);
//    lv_obj_t * lp = lv_label_create(btn_plus);
//    lv_label_set_text(lp, LV_SYMBOL_PLUS); lv_obj_center(lp);
}
