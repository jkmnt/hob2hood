#include "syntax.h"
#include "stm8s003f3.h"
#include "timer.h"
#include "buttons.h"

// PA1 = lamp, lamp led
// PA2 = fan1, fan1 led
// PA3 = fan2, fan2 led
// PB4 - fan4, fan4 led
// PB5 - fan3, fan3 led
// PD6 - automan led

typedef struct
{
    u8 clock_a;
    u8 clock_b;
    u8 clock_c;
    u8 output;
} debounce_t;

typedef struct
{
    debounce_t deb;
    u16 last_ts;
} keyb_rt_t;

static keyb_rt_t rt;

static u8 remap_to_buttons(u8 bitmap)
{
    u8 res = 0;

    if (bitmap & (1U << 0)) res |= BTN_LAMP;
    if (bitmap & (1U << 1)) res |= BTN_FAN1;
    if (bitmap & (1U << 2)) res |= BTN_FAN2;
    if (bitmap & (1U << 3)) res |= BTN_FAN4;
    if (bitmap & (1U << 4)) res |= BTN_FAN3;
    if (bitmap & (1U << 5)) res |= BTN_AUTOMAN;

    return res;
}

static u8 debounce_4(debounce_t *ctx, u8 sample)
{
    const u8 diff = sample ^ ctx->output;
    const u8 same = ~diff;

    ctx->clock_a = ctx->clock_a ^ ctx->clock_b;
    ctx->clock_b = ~ctx->clock_b;
    ctx->clock_a &= diff;
    ctx->clock_b &= diff;

    const u8 changed = ~(same | ctx->clock_a | ctx->clock_b);
    ctx->output ^= changed;

    return changed;
}

static u8 debounce_2(debounce_t *ctx, u8 sample)
{
    const u8 diff = sample ^ ctx->output;
    const u8 same = ~diff;

    ctx->clock_a = ~ctx->clock_a;
    ctx->clock_a &= diff;

    const u8 changed = ~(same | ctx->clock_a);
    ctx->output ^= changed;

    return changed;
}

static u8 debounce_bypass(debounce_t *ctx, u8 sample)
{
    const u8 diff = sample ^ ctx->output;
    ctx->output = sample;
    return diff;
}

u8 buttons_sample(void)
{

    const u8 a = PORTA->IDR;
    const u8 b = PORTB->IDR;
    const u8 d = PORTD->IDR;

    u8 res = 0;
    res |= a & (7U << 1);
    res |= b & (3U << 4);
    res |= d & (1U << 6);
    res >>= 1;

    // invert, since the buttons are normally high, leave 6 buttons only
    res = ~res & 0x3F;

    return remap_to_buttons(res);
}

void buttons_init(void)
{
    // assuming hw defaults are ok
}

void buttons_periodic(void)
{
    u16 now = timer_ms();
    if (now - rt.last_ts < 10)
        return;
    rt.last_ts = now;

    const u8 sample = buttons_sample();
    // 40 ms debouncer
    const u8 changes = debounce_4(&rt.deb, sample);

    if (changes)
        buttons_onchange(sample & changes, (~sample) & changes);
}