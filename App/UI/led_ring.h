#ifndef LED_RING_H
#define LED_RING_H

#include "lvgl.h"

#ifdef __cplusplus
extern "C" {
#endif

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
    int32_t	   pos_x;
    int32_t	   pos_y;
} led_ring_t;

//static led_ring_t g_ring;

/*
 * Cria o anel de LEDs azuis + botoes  -  e  +  dentro de `parent`.
 * O valor inicial e 0 (nenhum ponto aceso).
 */
void led_ring_create(lv_obj_t * parent, led_ring_t * ring, int32_t x, int32_t y);

/*
 * Controle programatico do valor (numero de pontos acesos).
 * Uteis tanto para os botoes na tela quanto para TECLAS FISICAS (GPIO):
 * basta chamar led_ring_inc() / led_ring_dec() na sua rotina de varredura.
 */
void    led_ring_inc(led_ring_t * ring);          /* +1 (limita no maximo)          */
void    led_ring_dec(led_ring_t * ring);          /* -1 (limita em 0)               */
void    led_ring_set(led_ring_t * ring, int32_t value); /* define valor (clamp 0..max)    */
int32_t led_ring_get(led_ring_t * ring);          /* le o valor atual               */

#ifdef __cplusplus
}
#endif

#endif /* LED_RING_H */
