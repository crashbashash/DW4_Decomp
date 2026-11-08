#include "dw4/fp_bit.h"

FLO_type __floatsidf(SItype arg_a) {
    fp_number_type in;

    in.class = CLASS_NUMBER;
    in.sign = arg_a < 0;
    if (!arg_a) {
        in.class = CLASS_ZERO;
    } else {
        in.normal_exp = FRACBITS + NGARDS;
        if (in.sign) {
            if (arg_a == (SItype)0x80000000) {
                return -2147483648.0;
            }
            in.fraction.ll = (-arg_a);
        } else {
            in.fraction.ll = arg_a;
        }

        while (in.fraction.ll < (1LL << (FRACBITS + NGARDS))) {
            in.fraction.ll <<= 1;
            in.normal_exp -= 1;
        }
    }
    return pack_d(&in);
}
