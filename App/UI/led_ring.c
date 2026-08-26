#include "led_ring.h"

/* ======================= GEOMETRIA (medida da figura) =======================
 * 20 LEDs num ARCO de ~214 graus, centrado no TOPO, com vao (~146) embaixo.
 * Convencao: 0 = topo, sentido horario (0 topo|90 dir|180 fundo|270 esq).
 * -------------------------------------------------------------------------- */
#define LED_COUNT        20
#define ARC_SWEEP_DEG   214
#define ARC_ROTATE_DEG    0

#define RING_BOX         90      /* caixa/knob (px)               */
#define KNOB_SIZE        70      /* botao central (px)            */
#define RING_RADIUS      40      /* raio do centro dos LEDs (px)  */
#define DOT_SIZE          6      /* diametro de cada LED (px)     */

/* --- indicador de posicao (o "dimple" que gira dentro do botao) --- */
#define IND_RADIUS       26      /* raio do indicador (< raio do botao=35) */
#define IND_SIZE          8      /* diametro do indicador (px)             */
#define IND_COLOR    0x05070A    /* cor do miolo do dimple                 */
#define IND_RIM      0x3A4048    /* borda/rim do dimple                    */

/* --- ajuste fino da posicao do anel DENTRO da caixa --- */
#define RING_CX_OFF       0
#define RING_CY_OFF       0

/* --- posicao ABSOLUTA no LCD (canto sup-esq); -1 = usa lv_obj_align --- */
#define KNOB_LCD_X       386
#define KNOB_LCD_Y       95

#define COLOR_ON     0x1E90FF
#define COLOR_OFF    0x14283C

/* ============================== ESTADO ============================== */
typedef struct {
    lv_obj_t * dots[LED_COUNT];
    lv_obj_t * ind;             /* indicador de posicao */
    int32_t    value;
    int32_t    max;
} led_ring_t;

static led_ring_t g_ring;

/* ==================== GEOMETRIA: angulo de cada passo ==================
 * idx = 0..LED_COUNT-1  -> devolve o angulo (graus, 0=topo horario).      */
static int16_t arc_phi_deg(int32_t idx)
{
    int32_t sweep_c = ARC_SWEEP_DEG * 100;
    int32_t step_c  = sweep_c / (LED_COUNT - 1);
    int32_t base_c  = ARC_ROTATE_DEG * 100 - sweep_c / 2;
    int32_t phi_c   = base_c + idx * step_c;
    return (int16_t)((phi_c + (phi_c >= 0 ? 50 : -50)) / 100);
}

/* posiciona um filho de `box` no raio `r` e angulo `phi` (centrado) */
static void place_polar(lv_obj_t * o, int32_t r, int16_t phi, int32_t size)
{
    int32_t cx = RING_BOX / 2 + RING_CX_OFF;
    int32_t cy = RING_BOX / 2 + RING_CY_OFF;
    int32_t x  = cx + (r * lv_trigo_sin(phi)) / LV_TRIGO_SIN_MAX;
    int32_t y  = cy - (r * lv_trigo_cos(phi)) / LV_TRIGO_SIN_MAX;
    lv_obj_set_pos(o, x - size / 2, y - size / 2);
}

/* ============================ INTERNOS ============================== */
static void ring_refresh(void)
{
    /* LEDs acesos/apagados */
    for (int i = 0; i < g_ring.max; i++) {
        lv_color_t c = (i < g_ring.value) ? lv_color_hex(COLOR_ON)
                                          : lv_color_hex(COLOR_OFF);
        lv_obj_set_style_bg_color(g_ring.dots[i], c, 0);
    }
    /* indicador gira ate o ULTIMO LED aceso (em value=0 fica no inicio) */
    if (g_ring.ind) {
        int32_t idx = (g_ring.value > 0) ? g_ring.value - 1 : 0;
        place_polar(g_ring.ind, IND_RADIUS, arc_phi_deg(idx), IND_SIZE);
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
    g_ring.ind   = NULL;

    /* ---- caixa ---- */
    lv_obj_t * box = lv_obj_create(parent);
    lv_obj_set_size(box, RING_BOX, RING_BOX);
#if (KNOB_LCD_X >= 0) && (KNOB_LCD_Y >= 0)
    lv_obj_set_pos(box, KNOB_LCD_X, KNOB_LCD_Y);
#else
    lv_obj_align(box, LV_ALIGN_TOP_MID, 0, 6);
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

    /* ---- LEDs ---- */
    for (int i = 0; i < LED_COUNT; i++) {
        lv_obj_t * dot = lv_obj_create(box);
        lv_obj_remove_style_all(dot);
        lv_obj_remove_flag(dot, LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_CLICKABLE);
        lv_obj_set_size(dot, DOT_SIZE, DOT_SIZE);
        lv_obj_set_style_radius(dot, LV_RADIUS_CIRCLE, 0);
        lv_obj_set_style_bg_opa(dot, LV_OPA_COVER, 0);
        place_polar(dot, RING_RADIUS, arc_phi_deg(i), DOT_SIZE);
        g_ring.dots[i] = dot;
    }

    /* ---- indicador de posicao (por cima do botao) ---- */
    lv_obj_t * ind = lv_obj_create(box);
    lv_obj_remove_style_all(ind);
    lv_obj_remove_flag(ind, LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_CLICKABLE);
    lv_obj_set_size(ind, IND_SIZE, IND_SIZE);
    lv_obj_set_style_radius(ind, LV_RADIUS_CIRCLE, 0);
    lv_obj_set_style_bg_opa(ind, LV_OPA_COVER, 0);
    lv_obj_set_style_bg_color(ind, lv_color_hex(IND_COLOR), 0);
    lv_obj_set_style_border_width(ind, 1, 0);
    lv_obj_set_style_border_color(ind, lv_color_hex(IND_RIM), 0);
    g_ring.ind = ind;

    ring_refresh();
}
