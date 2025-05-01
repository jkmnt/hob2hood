#ifndef BUTTONS_H
#define BUTTONS_H

#include "syntax.h"

enum btns_e
{
    BTN_LAMP = 0x01,
    BTN_FAN1 = 0x02,
    BTN_FAN2 = 0x04,
    BTN_FAN3 = 0x08,
    BTN_FAN4 = 0x10,
    BTN_AUTOMAN = 0x20,
};

// compile-time bound callback
extern void buttons_onchange(u8 pressed, u8 released);

void buttons_init(void);
void buttons_periodic(void);
u8 buttons_sample(void);

#endif