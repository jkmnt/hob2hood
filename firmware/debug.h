#ifndef DEBUG_H
#define DEBUG_H

#include <stdio.h>
#include <stdarg.h>
#include "syntax.h"

#define LOG(__fmt, ...) printf(__FILE__ ": " __fmt "\n", ##__VA_ARGS__)
#define WARN(__fmt, ...) printf(__FILE__ ":" QUOTE(__LINE__) " Warn: " __fmt "\n", ##__VA_ARGS__)
#define ERR(__fmt, ...) printf(__FILE__ ":" QUOTE(__LINE__) " Err: " __fmt "\n", ##__VA_ARGS__)

#endif