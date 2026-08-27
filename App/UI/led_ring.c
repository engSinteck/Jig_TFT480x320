#include "led_ring.h"

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
static void ring_refresh(led_ring_t * ring)
{
    /* LEDs acesos/apagados */
    for (int i = 0; i < ring->max; i++) {
        lv_color_t c = (i < ring->value) ?  lv_color_hex(COLOR_ON)
                                          : lv_color_hex(COLOR_OFF);
        lv_obj_set_style_bg_color(ring->dots[i], c, 0);
    }
    /* indicador gira ate o ULTIMO LED aceso (em value=0 fica no inicio) */
    if (ring->ind) {
        int32_t idx = (ring->value > 0) ? ring->value - 1 : 0;
        place_polar(ring->ind, IND_RADIUS, arc_phi_deg(idx), IND_SIZE);
    }
}

/* ============================ API PUBLICA ========================== */
void led_ring_inc(led_ring_t * ring)
{
	if (ring->value < ring->max) {
		ring->value++;
		ring_refresh(ring);
	}
}

void led_ring_dec(led_ring_t * ring)
{
	if (ring->value > 0) {
		ring->value--;
		ring_refresh(ring);
	}
}

void led_ring_set(led_ring_t * ring, int32_t value)
{
    if (value < 0)          value = 0;
    if (value > ring->max)  value = ring->max;
    ring->value = value;
    ring_refresh(ring);
}

int32_t led_ring_get(led_ring_t * ring)
{
	return ring->value;
}

/* ============================ CONSTRUCAO ========================== */
void led_ring_create(lv_obj_t * parent, led_ring_t * ring, int32_t x, int32_t y)
{
    ring->value = 0;
    ring->max   = LED_COUNT;
    ring->ind   = NULL;
    ring->pos_x = x;
    ring->pos_y = y;

    /* ---- caixa ---- */
    lv_obj_t * box = lv_obj_create(parent);
    lv_obj_set_size(box, RING_BOX, RING_BOX);
#if (KNOB_LCD_X >= 0) && (KNOB_LCD_Y >= 0)
    lv_obj_set_pos(box, ring->pos_x, ring->pos_y);
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
        ring->dots[i] = dot;
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
    ring->ind = ind;

    ring_refresh(ring);
}
