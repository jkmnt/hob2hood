#include "h2h.h"

/*
    My hob is sending ~24 bits of NRZ at 1405 Hz. That's ~711uS per bit.
    The ir routine tick is 32us.
    The longest run of zeros or ones is 6.
    The bit pattern is inverted.
*/

static u8 decode_run(u8 ticks)
{
    // The thresholds are approximately between the bits.
    if (ticks < 11) return 0;
    if (ticks < 33) return 1;
    if (ticks < 56) return 2;
    if (ticks < 78) return 3;
    if (ticks < 100) return 4;
    if (ticks < 122) return 5;
    if (ticks < 144) return 6;
    if (ticks < 167) return 7;
    if (ticks < 189) return 8;

    // something triggering overflow
    return 32;
}

// result 0 is error
u32 h2h_decode(const u8 *pulse_widths, u8 len)
{
    u32 res = 0;
    u8 pos = 0;
    for (u8 i = 0; i < len; i++)
    {
        u8 run_len = decode_run(pulse_widths[i]);
        pos += run_len;
        if (pos > 32)
            return 0;
        res <<= run_len;
        if (! (i & 0x01)) // append run of ones if current bit is even.
            res |= (1U << run_len) - 1;
    }

    return res;
}
