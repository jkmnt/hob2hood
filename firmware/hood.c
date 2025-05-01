#include "syntax.h"
#include "hood.h"
#include "fan.h"
#include "lamp.h"
#include "outs.h"
#include "timer.h"
#include "nvmem.h"
#include "sys.h"
#include "debug.h"

// quick'n'dirty fsm here

typedef void (*state_t)(u8 ev, u8 arg);

static void state_manual(u8 ev, u8 arg);
static void state_auto(u8 ev, u8 arg);
static void state_auto_sleep(u8 ev, u8 arg);
static void state_manual_sleep(u8 ev, u8 arg);
static void state_cfg(u8 ev, u8 arg);

typedef struct
{
    u8 is_auto_enabled;
    u8 lamp_is_auto;
    u8 hob_fan_speed_limit;
    u8 res;
    u16 sleep_timeout_sec; // 18 hours max
    u8 checksum;           // (negative) sum of cfg bytes
} cfg_t;

static struct
{
    state_t state;

    u32 last_activity_ts;

    struct
    {
        u8 fan;
        u8 lamp;
    } hob;

    struct
    {
        u8 fan;
        u8 lamp;
    } man;

    cfg_t cfg;
} rt;

static u8 calc_checksum(const void *mem, u8 len)
{
    u8 sum = 0;
    const u8 *p = mem;
    for (u8 i = 0; i < len; i++)
        sum += *p++;

    return sum;
}

static void store_cfg(void)
{
    rt.cfg.checksum = -calc_checksum(&rt.cfg, sizeof(rt.cfg) - 1);
    nvmem_write(&rt.cfg, sizeof(rt.cfg));
}

static void load_cfg(void)
{
    const cfg_t *nv_cfg = nvmem_access();

    if (calc_checksum(nv_cfg, sizeof(cfg_t)) != 0)
    {
        WARN("Bad nvmem");
        rt.cfg.hob_fan_speed_limit = 4;
        rt.cfg.is_auto_enabled = true;
        rt.cfg.lamp_is_auto = false;
        rt.cfg.sleep_timeout_sec = 14400; // 4 hours
        return;
    }

    rt.cfg = *nv_cfg;
    if (rt.cfg.hob_fan_speed_limit < 1)
        rt.cfg.hob_fan_speed_limit = 1;
    if (rt.cfg.hob_fan_speed_limit > 4)
        rt.cfg.hob_fan_speed_limit = 4;
}

static void trans(state_t tgt)
{
    rt.state = tgt;
    tgt(_HOOD_EV_ENTRY, 0);
}

static u8 clamp_hob_fan(u8 val)
{
    u8 limit = rt.cfg.hob_fan_speed_limit;
    return val > limit ? limit : val;
}

// Automatic mode.
// Fans are controlled by the hood.
// Lamp is controlled by the hood if feature is enabled, otherwise it's always manual (independent).
// Pressing any button enables manual mode. Manual state set to the same as remote.
static void state_auto(u8 ev, u8 arg)
{
    u32 now = timer_sec();
    if (ev != _HOOD_EV_PERIODIC)
        rt.last_activity_ts = now;

    switch (ev)
    {
        case _HOOD_EV_ENTRY:
            LOG("auto");
            outs_drive(0, LED_AUTOMAN);
            return;

        case HOOD_EV_FAN_RECEIVED:
            rt.hob.fan = clamp_hob_fan(arg);
            return;

        case HOOD_EV_LAMP_RECEIVED:
            rt.hob.lamp = arg;
            return;

        case HOOD_EV_FAN_PRESSED:
            rt.man.fan = rt.hob.fan;
            if (rt.cfg.lamp_is_auto)
                rt.man.lamp = rt.hob.lamp;
            trans(state_manual);
            hood_dispatch(ev, arg); // redispatch
            return;

        case HOOD_EV_LAMP_PRESSED:
            if (! rt.cfg.lamp_is_auto)
            {
                rt.man.lamp = ! rt.man.lamp;
                return;
            }

            rt.man.fan = rt.hob.fan;
            rt.man.lamp = rt.hob.lamp;
            trans(state_manual);
            hood_dispatch(ev, arg); // redispatch
            return;

        case HOOD_EV_AUTOMAN_PRESSED:
            rt.man.fan = rt.hob.fan;
            if (rt.cfg.lamp_is_auto)
                rt.man.lamp = rt.hob.lamp;
            trans(state_manual);
            return;

        case _HOOD_EV_PERIODIC:
            fan_set_speed(rt.hob.fan);
            lamp_drive(rt.cfg.lamp_is_auto ? rt.hob.lamp : rt.man.lamp);

            if (rt.cfg.sleep_timeout_sec && (now - rt.last_activity_ts > rt.cfg.sleep_timeout_sec))
                trans(state_auto_sleep);
            return;
    }
}

// Manual mode.
// Fan buttons control the fan. Choosing the same speed toogles the fan off. Choosing another speed
// switches to that speed.
// Lamp button controls the lamp.
// Remote commands are received and stored to be applied later after the switching back
// to the auto mode.
// Pressing the automan button switches to auto.
// Receiving the HOB_IS_ON switches to auto - it's the start of another cooking session.
static void state_manual(u8 ev, u8 arg)
{
    u32 now = timer_sec();
    if (ev != _HOOD_EV_PERIODIC)
        rt.last_activity_ts = now;

    switch (ev)
    {
        case _HOOD_EV_ENTRY:
            LOG("man");
            if (rt.cfg.is_auto_enabled)
                outs_drive(LED_AUTOMAN, 0);
            return;

        // toggle if same or or switch
        case HOOD_EV_FAN_PRESSED:
            rt.man.fan = rt.man.fan == arg ? 0 : arg;
            return;

        case HOOD_EV_LAMP_PRESSED:
            rt.man.lamp = ! rt.man.lamp;
            return;

        case HOOD_EV_FAN_RECEIVED:
            rt.hob.fan = clamp_hob_fan(arg);
            return;

        case HOOD_EV_LAMP_RECEIVED:
            rt.hob.lamp = arg;
            // return to auto when hob turned on the lights.
            if (arg && rt.cfg.is_auto_enabled)
                trans(state_auto);
            return;

        case HOOD_EV_AUTOMAN_PRESSED:
            if (rt.cfg.is_auto_enabled)
                trans(state_auto);
            return;

        case _HOOD_EV_PERIODIC:
            fan_set_speed(rt.man.fan);
            lamp_drive(rt.man.lamp);

            if (rt.cfg.sleep_timeout_sec && (now - rt.last_activity_ts > rt.cfg.sleep_timeout_sec))
                trans(state_manual_sleep);
            return;
    }
}

// Sleep in auto mode. Turn off everything, return to auto on any activity
static void state_auto_sleep(u8 ev, u8 arg)
{
    switch (ev)
    {
        case _HOOD_EV_ENTRY:
            LOG("autosleep");
            fan_set_speed(0);
            lamp_drive(0);
            return;

        case _HOOD_EV_PERIODIC:
            return;

        default:
            trans(state_auto);
            hood_dispatch(ev, arg); // redispatch
            return;
    }
}

// Sleep in manual mode. Turn off everything, return to manual on any activity.
// Also turn off the annoying led.
static void state_manual_sleep(u8 ev, u8 arg)
{
    switch (ev)
    {
        case _HOOD_EV_ENTRY:
            LOG("mansleep");
            fan_set_speed(0);
            lamp_drive(0);
            outs_drive(0, LED_AUTOMAN);
            return;

        case _HOOD_EV_PERIODIC:
            return;

        default:
            trans(state_manual);
            hood_dispatch(ev, arg); // redispatch
            return;
    }
}

// Configure settings. Exit via reset.
static void state_cfg(u8 ev, u8 arg)
{
    switch (ev)
    {
        case _HOOD_EV_ENTRY:
            LOG("cfg");
            return;

        case HOOD_EV_AUTOMAN_PRESSED:
            rt.cfg.is_auto_enabled = ! rt.cfg.is_auto_enabled;
            store_cfg();
            return;

        case HOOD_EV_LAMP_PRESSED:
            rt.cfg.lamp_is_auto = ! rt.cfg.lamp_is_auto;
            store_cfg();
            return;

        case HOOD_EV_FAN_PRESSED:
            rt.cfg.hob_fan_speed_limit = arg;
            store_cfg();
            return;

        case _HOOD_EV_PERIODIC:
        {
            u8 leds = 0;
            if (rt.cfg.is_auto_enabled)
            {
                if (rt.cfg.lamp_is_auto)
                    leds |= LED_LAMP;
                u8 limit = rt.cfg.hob_fan_speed_limit;
                leds |= LED_FAN1;
                if (limit > 1)
                    leds |= LED_FAN2;
                if (limit > 2)
                    leds |= LED_FAN3;
                if (limit > 3)
                    leds |= LED_FAN4;
            }
            // blink with the subsecond period
            if (timer_ms() & (1 << 8))
                leds |= LED_AUTOMAN;
            outs_drive(leds, LED_AUTOMAN | LED_LAMP | LED_FAN1 | LED_FAN2 | LED_FAN3 | LED_FAN4);
            return;
        }
    }
}

void hood_start(bool is_cfg_requested)
{
    load_cfg();
    LOG("auto:%d\nlamp %d\nfan:%d\nsleep:%d",
        rt.cfg.is_auto_enabled,
        rt.cfg.lamp_is_auto,
        rt.cfg.hob_fan_speed_limit,
        rt.cfg.sleep_timeout_sec);

    if (is_cfg_requested)
    {
        trans(state_cfg);
    }
    else
    {
        trans(rt.cfg.is_auto_enabled ? state_auto : state_manual);
    }
}

void hood_dispatch(u8 ev, u8 arg)
{
    rt.state(ev, arg);
}

void hood_periodic(void)
{
    rt.state(_HOOD_EV_PERIODIC, 0);
}