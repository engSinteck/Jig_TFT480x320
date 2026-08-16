#ifndef LED_RING_H
#define LED_RING_H

#include "lvgl.h"

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Cria o anel de LEDs azuis + botoes  -  e  +  dentro de `parent`.
 * O valor inicial e 0 (nenhum ponto aceso).
 */
void    led_ring_create(lv_obj_t * parent);

/*
 * Controle programatico do valor (numero de pontos acesos).
 * Uteis tanto para os botoes na tela quanto para TECLAS FISICAS (GPIO):
 * basta chamar led_ring_inc() / led_ring_dec() na sua rotina de varredura.
 */
void    led_ring_inc(void);          /* +1 (limita no maximo)          */
void    led_ring_dec(void);          /* -1 (limita em 0)               */
void    led_ring_set(int32_t value); /* define valor (clamp 0..max)    */
int32_t led_ring_get(void);          /* le o valor atual               */

#ifdef __cplusplus
}
#endif

#endif /* LED_RING_H */
