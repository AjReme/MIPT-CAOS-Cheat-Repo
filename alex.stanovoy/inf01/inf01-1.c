#include <inttypes.h>

typedef enum {
    PlusZero      = 0x00,
    MinusZero     = 0x01,
    PlusInf       = 0xF0,
    MinusInf      = 0xF1,
    PlusRegular   = 0x10,
    MinusRegular  = 0x11,
    PlusDenormal  = 0x20,
    MinusDenormal = 0x21,
    SignalingNaN  = 0x30,
    QuietNaN      = 0x31
} float_class_t;

float_class_t classify(double* value_ptr) {
    union {
        uint64_t bits;
        double val;
    } T;
    T.val = *value_ptr;

    const uint64_t S = T.bits >> 63;
    const uint64_t E = (T.bits << 1) >> 53;
    const uint64_t M = (T.bits << 12) >> 12;
    const uint64_t E_full = ~0ull >> 53;

    if (S == 0) {
        if (E == E_full) {
            if (M == 0) {
                return PlusInf;
            } else {
                return (M >> 51) != 0 ? QuietNaN : SignalingNaN;
            }
        } else if (E == 0) {
            return M == 0 ? PlusZero : PlusDenormal;
        } else {
            return PlusRegular;
        }
    }
    else {
        if (E == E_full) {
            if (M == 0) {
                return MinusInf;
            } else {
                return (M >> 51) != 0 ? QuietNaN : SignalingNaN;
            }
        } else if (E == 0) {
            return M == 0 ? MinusZero : MinusDenormal;
        } else {
            return MinusRegular;
        }
    }
}

