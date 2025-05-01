#ifndef IR_H
#define IR_H

#include "syntax.h"

#define IR_ISRA_IRQN 6
#define IR_ISRB_IRQN 13

typedef enum
{
    IR_BASE_1US = 4,
    IR_BASE_2US,
    IR_BASE_4US,
    IR_BASE_8US,
    IR_BASE_16US,
    IR_BASE_32US,
    IR_BASE_64US,
    IR_BASE_128US,
    IR_BASE_256US,
    IR_BASE_512US,
    IR_BASE_1024US,
    IR_BASE_2048US,
} ir_base_t;


// compile-time bound callback
extern void ir_onrecv(const u8 *pulse_widths, u8 len);

void ir_isra(void) __interrupt(IR_ISRA_IRQN);
void ir_isrb(void) __interrupt(IR_ISRB_IRQN);

void ir_init(ir_base_t base, u8 eof_ticks);
void ir_periodic(void);

#endif