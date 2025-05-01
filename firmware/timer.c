#include "syntax.h"
#include "stm8s003f3.h"
#include "sys.h"
#include "timer.h"

static const u16 wake_freq = 100U;
static TIM1_t *const tmr = TIM1;

static struct
{
    u8 wake_cnt;
    volatile u32 seconds;
} rt;

// I want two timers:
// - fast one with 1ms tick (16 bit overflow of 65sec is ok)
// - slow 1 sec RTC
// Both are based on 16-bit hardware timer.
void timer_init(void)
{
    // clock on
    CLK->PCKENR1 |= (1U << 7);

    // 1 ms resolution = 1 kHz clock
    write_r16(&tmr->PSCRH, &tmr->PSCRL, SYS_FCPU / 1000U - 1);
    // count full 16-bit span
    write_r16(&tmr->ARRH, &tmr->ARRL, 0xFFFF);
    // make sure the counter is initialized
    write_r16(&tmr->CNTRH, &tmr->CNTRL, 0);
    // wake every 10 ms
    write_r16(&tmr->CCR1H, &tmr->CCR1L, 10);
    // apply prescaler, etc
    tmr->CR1 = TIM1_CR1_URS;
    tmr->EGR = TIM1_EGR_UG;
    // clear status, it should have a sticky update flag now
    tmr->SR1 = 0;
    // enable compare 1 interrupt
    tmr->IER = TIM1_IER_CC1IE;
    // other defaults are ok, go
    tmr->CR1 = TIM2_CR1_URS | TIM1_CR1_CEN;
}

u16 timer_ms(void)
{
    return read_r16(&tmr->CNTRH, &tmr->CNTRL);
}

u32 timer_sec(void)
{
    // 4 bytes of seconds are updated from isr in a non-atomic way.
    // Reading until settle.
    u32 was = rt.seconds;
    u32 val = rt.seconds;
    while (val != was)
    {
        was = val;
        val = rt.seconds;
    }

    return val;
}

void timer_sleep(u16 ms)
{
    // special. execute the single 10ms wait
    if (ms == 0)
    {
        __asm__("wfi");
        return;
    }

    u16 start = timer_ms();

    // if interval is big enough, it's worth to spend bulk of time with the core stopped.
    // timer interrupt will wake us every 10 ms.
    if (ms >= 20)
    {
        u16 coarse = ms - 20;
        while (timer_ms() - start < coarse)
            __asm__("wfi");
    }

    // busy-loop the <= 20ms remainder
    while (timer_ms() - start < ms)
        ;
}

PANIC_IF(TIMER_COMPARE_IRQN != TIM1_CAPCOM_CC1IF_IRQN);

void timer_compare_isr(void) __interrupt(TIMER_COMPARE_IRQN)
{
    TIM1->SR1 = 0;

    // schedule next wake 10ms in the future
    write_r16(&tmr->CCR1H, &tmr->CCR1L, read_r16(&tmr->CCR1H, &tmr->CCR1L) + 10);

    u8 wake = rt.wake_cnt + 1;
    if (wake >= wake_freq) // or -1 ?
    {
        wake = 0;
        rt.seconds += 1;
    }
    rt.wake_cnt = wake;
}