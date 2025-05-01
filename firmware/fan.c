#include "timer.h"
#include "outs.h"
#include "fan.h"

// Fan switching should have a deadtime so only one relay
// is energized at time.
// Original firmware had the deadtime about 120 ms.
// Let's keep is dumb for now: call the update routine every 60 ms,
// update outputs via intermediate off. We'll satisfy the 120ms
// in any case.

static struct
{
    u16 last_change_ms;
    u8 set; // commanded speed
    u8 cur; // current speed
} rt;

static const u16 throttle_ms = 60;

static u16 speed_to_coil(u8 speed)
{
    switch (speed)
    {
        case 1:  return COIL_FAN1;
        case 2:  return COIL_FAN2;
        case 3:  return COIL_FAN3;
        case 4:  return COIL_FAN4;
        default: return 0;
    }
}

void fan_set_speed(u8 speed)
{
    rt.set = speed;
}

void fan_periodic(void)
{
    u16 now = timer_ms();
    // unsigned compare is ok here if delta < 2^15
    if (now - rt.last_change_ms < throttle_ms)
        return;

    if (rt.cur == rt.set)
    {
        // If there was a long time without changes, last_change_ts and now
        // may drift > 2^15. Preset to something in the recent past to avoid it.
        rt.last_change_ms = now - throttle_ms;
        return;
    }

    rt.last_change_ms = now;
    // change via off
    rt.cur = rt.cur ? 0 : rt.set;

    outs_drive(speed_to_coil(rt.cur), COIL_FAN1 | COIL_FAN2 | COIL_FAN3 | COIL_FAN4);
}