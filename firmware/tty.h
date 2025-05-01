#ifndef TTY_H
#define TTY_H

#include "syntax.h"

#define TTY_IRQN 17

enum tty_flags_e
{
    TTY_F_BLOCK_IF_BUSY = 0x01,
};

void tty_isr(void) __interrupt(TTY_IRQN);

void tty_init(u32 baudrate, u8 flags);
void tty_putc(char byte);
void tty_puts(const char *s);
void tty_putline(const char *s);

#endif