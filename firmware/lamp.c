#include "timer.h"
#include "outs.h"
#include "lamp.h"

// same as for the fan
static const u16 throttle_ms = 120;

static struct
{
    u16 last_change_ms;
    u8 set;
    u8 cur;
} rt;

void lamp_drive(bool on)
{
    rt.set = on;
}

void lamp_periodic(void)
{
    u16 now = timer_ms();
    if (now - rt.last_change_ms < throttle_ms)
        return;

    if (rt.cur == rt.set)
    {
        rt.last_change_ms = now - throttle_ms;
        return;
    }

    rt.last_change_ms = now;
    rt.cur = rt.set;

    outs_drive(rt.cur ? COIL_LAMP : 0, COIL_LAMP);
}