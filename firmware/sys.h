#ifndef SYS_H
#define SYS_H

#include "syntax.h"

#define SYS_FCPU 16000000UL

void sys_init(void);
void sys_reset(void);

u16 read_r16(volatile u8 *high, volatile u8 *low);
void write_r16(volatile u8 *high, volatile u8 *low, u16 val);

#endif