#ifndef SYNTAX_H
#define SYNTAX_H

#include <stdint.h>
#include <stdbool.h>

// convinience macros
#define countof( arg)       ( sizeof(arg)/sizeof(arg[0]))
#define firstof( arg)       (arg[0])
#define lastof( arg)        (arg[countof(arg) - 1])
#define endof( arg)         (arg[countof(arg)])
// Size of slice between first field end last field of struct (including last field)
#define sliceof(type, first_field, last_field)  (offsetof(type, last_field) - offsetof(type, first_field) + sizeof(((type *)0)->last_field))

#ifndef containerof
    #define containerof(ptr, type, member) ({ const typeof( ((type *)0)->member ) *__mptr = (ptr); (type *)(void *)( (char *)__mptr - offsetof(type,member) );})
#endif

// common macro stringifications
#define _QUOTE(x) # x
#define QUOTE(x) _QUOTE(x)

#define ___PASTE(a,b) a##b
#define __PASTE(a,b) ___PASTE(a,b)
#define __UNIQUE_ID(prefix) __PASTE(__PASTE(__UNIQUE_ID_, prefix), __COUNTER__)

// static assert
#define PANIC_IF( arg)              extern char __UNIQUE_ID(__PANIC)  [ ( arg) ? -1 : 0 ]

// aliases for common types
typedef unsigned int uint;
typedef signed int sint;

typedef unsigned long ulong;
typedef signed long slong;

typedef unsigned char uchar;
typedef signed char schar;

typedef uint64_t u64;
typedef int64_t s64;

typedef uint32_t u32;
typedef int32_t s32;

typedef uint16_t u16;
typedef int16_t s16;

typedef uint8_t u8;
typedef int8_t s8;

// aliases for gcc builtin functions
#ifndef offsetof
    #define offsetof( obj, field)   __builtin_offsetof( obj, field)
#endif

// range clamp, abs
#define CLAMP(min, a, max)  ({ typeof(min) _min = (min); typeof(a) _a = (a); typeof(max) _max = (max); (_a > _max) ? _max : ((_a < min) ? _min : _a);})
#define ABS(x)          (((x) < 0) ? (-(x)) : (x))

#define _MIN_ONCE(a, b, unique_a, unique_b)     ({ typeof(a) unique_a = (a); typeof(b) unique_b = (b); (unique_a < unique_b) ? unique_a : unique_b; })
#define MIN(a, b)            _MIN_ONCE(a, b, __UNIQUE_ID(_a), __UNIQUE_ID(_b))
#define MIN_3(a, b, c)       MIN(c, MIN(b, a))
#define MIN_4(a, b, c, d)    MIN(d, MIN(c, MIN(b, a)))

#define _MAX_ONCE(a, b, unique_a, unique_b)     ({ typeof(a) unique_a = (a); typeof(b) unique_b = (b); (unique_a > unique_b) ? unique_a : unique_b; })
#define MAX(a, b)            _MAX_ONCE(a, b, __UNIQUE_ID(_a), __UNIQUE_ID(_b))
#define MAX_3(a, b, c)       MAX(c, MAX(b, a))
#define MAX_4(a, b, c, d)    MAX(d, MAX(c, MAX(b, a)))



#endif
