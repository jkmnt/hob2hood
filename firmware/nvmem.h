#ifndef NVMEM_H
#define NVMEM_H

#include "syntax.h"

// Read is direct
const void *nvmem_access(void);

// Open the EEPROM for reading. Assuming it would be accessed
// by the byte-level instructions
void *nvmem_write_begin(void);
void nvmem_write_end(void);

void nvmem_write(const void *buf, u8 len);

#endif