
#include "syntax.h"
#include "stm8s003f3.h"
#include "sys.h"
#include "tty.h"

#define BUF_SIZE 64

// power of two
PANIC_IF(BUF_SIZE &(BUF_SIZE - 1));
// SDCC linker requires the ISR vectors to be visible from main.
// So I expose the ISR func in header but hide the MCU include.
PANIC_IF(TTY_IRQN != UART1_T_TXE_IRQN);

typedef struct
{
    volatile u8 r;
    volatile u8 w;
    u8 flags;
    u8 buf[BUF_SIZE];
} tty_rt_t;

static UART1_t *const uart = UART1;

static tty_rt_t rt;

void tty_init(u32 baudrate, u8 flags)
{

    rt.flags = flags;

    // Enable clock
    CLK->PCKENR1 |= 1U << 3;
    // isr with low priority
    ITC->SPR5 |= 1U << 2;

    // TODO: enable the tx pin function ?

    uart->CR1 = 0;
    uart->CR2 = 0;
    uart->CR3 = 0;

    // const u32 baudrate = 115200;
    const u16 div = (SYS_FCPU + baudrate / 2) / baudrate;
    uart->BRR2 = (div >> 8) | (div & 0x0F);
    uart->BRR1 = (div >> 4) & 0xFF;

    // transmitter enable, txe interrupt enable
    uart->CR2 = UART1_CR2_TEN | UART1_CR2_TIEN;
}

void tty_putc(char byte)
{

    u8 w = rt.w;
    u8 new_w = (w + 1) & (BUF_SIZE - 1);

    // process 'buffer is full'
    if (new_w == rt.r)
    {
        if (! (rt.flags & TTY_F_BLOCK_IF_BUSY))
            return;
        while (new_w == rt.r)
            ;
    }

    rt.buf[w] = byte;
    rt.w = new_w;

    // transmitter enable, txe irq enable
    uart->CR2 = UART1_CR2_TEN | UART1_CR2_TIEN;
}

void tty_puts(const char *s)
{
    while (*s)
        tty_putc(*s++);
}

void tty_putline(const char *s)
{
    tty_puts(s);
    tty_putc('\n');
}

void tty_isr(void) __interrupt(TTY_IRQN)
{
    if (uart->SR & UART1_SR_TXE)
    {
        u8 r = rt.r;
        if (r == rt.w)
        {
            uart->CR2 = UART1_CR2_TEN; // disable TXE interrupt
        }
        else
        {
            uart->DR = rt.buf[r];
            rt.r = (r + 1) & (BUF_SIZE - 1);
        }
    }
}