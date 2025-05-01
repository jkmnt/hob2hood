#include "stm8s003f3.h"
#include "nvmem.h"
#include "debug.h"

static u8 *const eeprom = (u8 *)EEPROM_ADDR_START;

const void *nvmem_access(void)
{
    return eeprom;
}

void *nvmem_write_begin(void)
{
    // unlock if required
    if (! (FLASH->IAPSR & FLASH_IAPSR_DUL))
    {
        FLASH->DUKR = 0xAE;
        FLASH->DUKR = 0x56;
    }

    // Some wait is needed for the flag to be updated
    __asm__("nop");
    __asm__("nop");
    __asm__("nop");
    __asm__("nop");
    __asm__("nop");
    __asm__("nop");
    __asm__("nop");
    __asm__("nop");

    if (! (FLASH->IAPSR & FLASH_IAPSR_DUL))
    {
        ERR("Locked");
        return NULL;
    }

    return eeprom;
}

void nvmem_write_end(void)
{
    // No need to wait here. Datasheet says app is stopped for the programming duration
    // if we have no RWW buffering (the case for our chip).
    FLASH->IAPSR &= ~FLASH_IAPSR_DUL;
}

void nvmem_write(const void *buf, u8 len)
{
    if (len > (EEPROM_ADDR_END - EEPROM_ADDR_START + 1))
        return;

    // program byte by byte, keep it simple
    u8 *dst = nvmem_write_begin();

    if (! dst)
        return;

    const u8 *src = buf;
    while (len--)
        *dst++ = *src++;

    nvmem_write_end();
}