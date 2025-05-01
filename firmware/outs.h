#ifndef OUTS_H
#define OUTS_H

#include "syntax.h"

enum outs_e
{
    LED_LAMP = 0x0001,
    LED_FAN1 = 0x0002,
    LED_FAN2 = 0x0004,
    LED_FAN3 = 0x0008,
    LED_FAN4 = 0x0010,
    LED_AUTOMAN = 0x0020,

    COIL_LAMP = 0x0100,
    COIL_FAN1 = 0x0200,
    COIL_FAN2 = 0x0400,
    COIL_FAN3 = 0x0800,
    COIL_FAN4 = 0x1000,
};

void outs_init(void);
void outs_drive(u16 set, u16 clr);

#endif