#include <stdio.h>
#include "sys.h"
#include "buttons.h"
#include "outs.h"
#include "tty.h"
#include "fan.h"
#include "lamp.h"
#include "timer.h"
#include "ir.h"
#include "h2h.h"
#include "nvmem.h"
#include "hood.h"
#include "debug.h"

int putchar(int byte)
{
    tty_putc(byte);
    return byte;
}

void ir_onrecv(const u8 *buf, u8 len)
{
    // ignore IR noise
    if (len <= 4)
        return;

    u32 bits = h2h_decode(buf, len);
    u8 ev;
    u8 arg;
    switch (bits)
    {
        case 0x012D2C2B:
            LOG("-> l1");
            ev = HOOD_EV_LAMP_RECEIVED;
            arg = 1;
            break;

        case 0x01939291:
            LOG("-> f1");
            ev = HOOD_EV_FAN_RECEIVED;
            arg = 1;
            break;

        case 0x00C847C7:
            LOG("-> f2");
            ev = HOOD_EV_FAN_RECEIVED;
            arg = 2;
            break;

        case 0x00478747:
            LOG("-> f3");
            ev = HOOD_EV_FAN_RECEIVED;
            arg = 3;
            break;

        case 0x018D8C8B:
            LOG("-> f4");
            ev = HOOD_EV_FAN_RECEIVED;
            arg = 4;
            break;

        case 0x01272625:
            LOG("-> f0");
            ev = HOOD_EV_FAN_RECEIVED;
            arg = 0;
            break;

        case 0x00254525:
            LOG("-> l0");
            ev = HOOD_EV_LAMP_RECEIVED;
            arg = 0;
            break;

        default:
            WARN("-> 0x%08lX", bits);
            return;
    }

    hood_dispatch(ev, arg);
}

void buttons_onchange(u8 pressed, u8 released)
{
    // NOTE: accepting the single press only. multiple simultaneous presses are unlikely.
    u8 ev;
    u8 arg;
    switch (pressed)
    {
        case BTN_FAN1:
            ev = HOOD_EV_FAN_PRESSED;
            arg = 1;
            break;
        case BTN_FAN2:
            ev = HOOD_EV_FAN_PRESSED;
            arg = 2;
            break;
        case BTN_FAN3:
            ev = HOOD_EV_FAN_PRESSED;
            arg = 3;
            break;
        case BTN_FAN4:
            ev = HOOD_EV_FAN_PRESSED;
            arg = 4;
            break;
        case BTN_LAMP:
            ev = HOOD_EV_LAMP_PRESSED;
            arg = 0;
            break;
        case BTN_AUTOMAN:
            ev = HOOD_EV_AUTOMAN_PRESSED;
            arg = 0;
            break;
        default:
            return;
    }

    hood_dispatch(ev, arg);
}

void show_startup_animation(void)
{
    const u8 seq[] = {LED_LAMP, LED_FAN1, LED_FAN2, LED_FAN3, LED_FAN4, LED_AUTOMAN};

    for (u8 i = 0; i < countof(seq); i++)
    {
        outs_drive(seq[i], 0);
        timer_sleep(100);
    }
    for (u8 i = 0; i < countof(seq); i++)
    {
        outs_drive(0, seq[i]);
        timer_sleep(100);
    }
}

void main(void)
{
    sys_init();
    outs_init();
    timer_init();
    tty_init(115200, TTY_F_BLOCK_IF_BUSY);
    buttons_init();
    // ~8 bits timeout
    ir_init(IR_BASE_32US, 172);

    show_startup_animation();

    // Wait buttons release
    const u8 is_cfg = buttons_sample() & BTN_AUTOMAN;
    while (buttons_sample())
        ;

    // enter config mode if automan button was pressed
    hood_start(is_cfg);

    while (1)
    {
        // take a nap to save a power, wake on any interrupt.
        // the 78l05 powering us is a little underrated.
        timer_sleep(0);
        buttons_periodic();
        fan_periodic();
        lamp_periodic();
        ir_periodic();
        hood_periodic();
    }
}