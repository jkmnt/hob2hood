#ifndef HOOD_H
#define HOOD_H

#include "syntax.h"

enum hood_event_e
{
    // internal
    _HOOD_EV_ENTRY,
    _HOOD_EV_PERIODIC,
    // remote commands
    HOOD_EV_FAN_RECEIVED,
    HOOD_EV_LAMP_RECEIVED,
    // local buttons pressed
    HOOD_EV_LAMP_PRESSED,
    HOOD_EV_FAN_PRESSED,
    HOOD_EV_AUTOMAN_PRESSED,
};

void hood_start(bool is_cfg_requested);
void hood_dispatch(u8 ev, u8 arg);
void hood_periodic(void);

#endif
