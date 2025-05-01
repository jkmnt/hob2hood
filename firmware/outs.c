#include "stm8s003f3.h"
#include "outs.h"

// PC3 - fan4 coil, pp output
// PC4 - fan1 coil, pp output
// PC5 - lamp coil, pp output
// PC6 - fan2 coil, pp output
// PC7 - fan3 coil, pp output
// PD2 - automan led, pp output
// PD3 - coils enable, pp output

// NOTE: the coil enable output is managed automatic.
// Despite the coils and fans outputs are shared,
// outs API present them as distinct outputs.
// Leaky abstraction for sure, but handy.
// Any requested coil output drives the 'coils_enable' too.

static const u8 mask_c = (1U << 7) | (1U << 6) | (1U << 5) | (1U << 4) | (1U << 3);
static const u8 mask_d = (1U << 3) | (1U << 2);

static struct
{
    u16 cur;
} outs_rt;

void outs_init(void)
{
    // all pins low, out, push-pull

    PORTC->ODR &= ~mask_c;
    PORTD->ODR &= ~mask_d;

    PORTC->DDR |= mask_c;
    PORTC->CR1 |= mask_c;

    PORTD->DDR |= mask_d;
    PORTD->CR1 |= mask_d;
}

void outs_drive(u16 set, u16 clr)
{
    u16 cur = outs_rt.cur;
    cur = (cur & ~clr) | set;
    outs_rt.cur = cur;

    u8 set_c = 0;
    u8 set_d = 0;

    if (cur & (LED_FAN4 | COIL_FAN4)) set_c |= 1U << 3;
    if (cur & (LED_FAN1 | COIL_FAN1)) set_c |= 1U << 4;
    if (cur & (LED_LAMP | COIL_LAMP)) set_c |= 1U << 5;
    if (cur & (LED_FAN2 | COIL_FAN2)) set_c |= 1U << 6;
    if (cur & (LED_FAN3 | COIL_FAN3)) set_c |= 1U << 7;
    if (cur & LED_AUTOMAN) set_d |= 1U << 2;
    if (cur & (COIL_FAN1 | COIL_FAN2 | COIL_FAN3 | COIL_FAN4 | COIL_LAMP)) set_d |= 1U << 3;

    PORTC->ODR = (PORTC->ODR & ~mask_c) | set_c;
    PORTD->ODR = (PORTD->ODR & ~mask_d) | set_d;
}