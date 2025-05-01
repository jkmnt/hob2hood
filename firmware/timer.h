#ifndef SYSTIMER_H
#define SYSTIMER_H

#include "syntax.h"

#define TIMER_COMPARE_IRQN 12

void timer_init(void);
u16 timer_ms(void);
u32 timer_sec(void);
void timer_sleep(u16 ms);

void timer_compare_isr(void) __interrupt(TIMER_COMPARE_IRQN);

#endif