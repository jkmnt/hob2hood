#include "syntax.h"
#include "STM8S003F3.h"
#include "sys.h"

// Pins on the KKV-4 control board.
// stm8s003f tssop-20

void sys_init(void)
{
    // Clock: internal oscillator at 16 MHz, no prescaler and division
    CLK->CKDIVR = 0x00;

    // Disable all peripheral clocks
    CLK->PCKENR1 = 0;
    CLK->PCKENR2 = 0;

    // By default all interrupts are of the same level2 normal priority
    ITC->SPR1 = 0;
    ITC->SPR2 = 0;
    ITC->SPR3 = 0;
    ITC->SPR4 = 0;
    ITC->SPR5 = 0;
    ITC->SPR6 = 0;
    ITC->SPR7 = 0;

    // Enable interrupts
    __asm__("rim");
}

u16 read_r16(volatile u8 *high, volatile u8 *low)
{
    u16 out = *high << 8;
    out |= *low;
    return out;
}

void write_r16(volatile u8 *high, volatile u8 *low, u16 val)
{
    *high = val >> 8;
    *low = val;
}

void sys_reset(void)
{
    __asm__(".db 0x75");
}