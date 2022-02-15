#include <math.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>

#include "FixP.h"

#ifndef FIX16
const uint8_t kIntegerPart = 16;
#else
const uint8_t kIntegerPart = 8;
#endif

#ifndef FIX16

int32_t
#else
int16_t
#endif
fixToInt(const FixP_t fp) {
    return fp >> kIntegerPart;
}

FixP_t intToFix(
        const
#ifndef FIX16
int32_t
#else
int16_t
#endif
v) {
    return v << kIntegerPart;
}

FixP_t Mul(const FixP_t v1, const FixP_t v2) {
#ifndef FIX16
    return ((v1 >> 6) * (v2 >> 6)) >> 4;
#else
    return ((((int32_t)v1) ) * (((int32_t)v2) )) >> kIntegerPart;
#endif
}

FixP_t Div(const FixP_t v1, const FixP_t v2) {
#ifndef FIX16
    return (((int64_t) v1) * (1 << kIntegerPart)) / v2;
#else
    return (((int32_t) v1) * (1 << kIntegerPart)) / v2;
#endif

}
