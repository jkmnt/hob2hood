#include <stdio.h>
#include "syntax.h"
#include "stm8s003f3.h"
#include "sys.h"
#include "timer.h"
#include "ir.h"

/*

Using the hardware timer compare and edge trigger seems to be the right way, but
it's not that flexible and setup may be a pain.

I'll use a more "software" way: pin interrupt and
oneshot timer. Timer is started, stopped, or reset in response
to the pin, timeout is handled via the timer overflow.

The IR pin is PD4, normally high with pullup.

The receive routine is quite generic. It stores pulse times to the
caller-supplied buffer. The end of message is defined as N ticks of silence.
The TIM2 timer rate could be only one of the fixed rates.

*/

static enum state_e {
    STATE_WAITING_START_0,
    STATE_WAITING_0,
    STATE_WAITING_1,
    STATE_DONE,
};

static enum event_e {
    EVENT_1,
    EVENT_0,
    EVENT_TIMEOUT,
    EVENT_START_REQ,
};

static TIM2_t *const tmr = TIM2;

static u8 const pin = 4;

#define BUF_SIZE 128

static struct
{
    volatile u8 state;
    u8 pos;
    u8 buf[BUF_SIZE];
} ir_rt;

static void start_timer(void)
{
    write_r16(&tmr->CNTRH, &tmr->CNTRL, 0);
    tmr->CR1 = TIM2_CR1_URS | TIM2_CR1_CEN;
}

static void process_event(u8 ev)
{
    switch (ir_rt.state)
    {
        case STATE_WAITING_START_0:
            if (ev == EVENT_0)
            {
                start_timer();
                ir_rt.pos = 0;
                ir_rt.state = STATE_WAITING_1;
            }
            return;

        case STATE_WAITING_1:
            if (ev == EVENT_1)
            {
                u8 pos = ir_rt.pos;
                if (pos < BUF_SIZE)
                {
                    u16 val = read_r16(&tmr->CNTRH, &tmr->CNTRL);
                    start_timer();
                    ir_rt.buf[pos] = val;
                    ir_rt.pos = pos + 1;
                    ir_rt.state = STATE_WAITING_0;
                    return;
                }
            }
            // anything else restarts
            ir_rt.state = STATE_WAITING_START_0;
            return;

        case STATE_WAITING_0:
            if (ev == EVENT_TIMEOUT)
            {
                ir_rt.state = STATE_DONE;
                return;
            }

            if (ev == EVENT_0)
            {
                // Copypaste yeah!
                u8 pos = ir_rt.pos;
                if (pos < BUF_SIZE)
                {
                    u16 val = read_r16(&tmr->CNTRH, &tmr->CNTRL);
                    start_timer();
                    ir_rt.buf[pos] = val;
                    ir_rt.pos = pos + 1;
                    ir_rt.state = STATE_WAITING_1;
                    return;
                }
            }
            // restart
            ir_rt.state = STATE_WAITING_START_0;
            return;

        case STATE_DONE:
            if (ev == EVENT_START_REQ)
                ir_rt.state = STATE_WAITING_START_0;
            return;
    }
}

void ir_init(ir_base_t base, u8 max_pulse_width)
{
    ir_rt.state = STATE_WAITING_START_0;

    // The IR chip have a pullup, but it's quite weak. Add own ~50k pullup too.
    PORTD->CR1 |= 1 << pin;
    // Ext interrupt controller: both edges on PORTD.
    // may only be set with the interrupts disabled
    __asm__("sim");
    ITC->CR1 |= 3 << 6;
    __asm__("rim");

    // both interrupts of high priority
    ITC->SPR2 |= 3U << 4;
    ITC->SPR4 |= 3U << 2;

    // Timer stuff
    CLK->PCKENR1 |= 1 << 5;
    tmr->PSCR = base;
    write_r16(&tmr->ARRH, &tmr->ARRL, max_pulse_width);
    write_r16(&tmr->CNTRH, &tmr->CNTRL, 0);
    // no interrupt on software UG bit
    tmr->CR1 = TIM2_CR1_URS;
    tmr->EGR = TIM2_EGR_UG;
    tmr->SR1 = 0;
    // interrupt on overflow (ARR match)
    tmr->IER = TIM2_IER_UIE;

    // Enable ext interrupt
    PORTD->CR2 |= 1 << pin;
}

PANIC_IF(IR_ISRA_IRQN != EXTI3_IRQN);

void ir_isra(void) __interrupt(IR_ISRA_IRQN)
{
    u8 smp = PORTD->IDR;
    tmr->CR1 = 0;
    tmr->SR1 = 0;
    process_event((smp & (1 << pin)) ? EVENT_1 : EVENT_0);
}

PANIC_IF(IR_ISRB_IRQN != TIM2_OVR_UIF_IRQN);

void ir_isrb(void) __interrupt(IR_ISRB_IRQN)
{
    tmr->CR1 = 0;
    tmr->SR1 = 0;
    process_event(EVENT_TIMEOUT);
}

void ir_periodic(void)
{
    if (ir_rt.state == STATE_DONE)
    {
        ir_onrecv(ir_rt.buf, ir_rt.pos);
        process_event(EVENT_START_REQ);
    }
}