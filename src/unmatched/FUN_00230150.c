#include "dw4/fp_bit_float.h"

FLO_type FUN_00230150(fp_number_type *src) {
    FLO_union_type dst;
    fractype fraction = src->fraction.ll;
    int sign = src->sign;
    int exp = 0;

    if (iszero(src)) {
        exp = 0;
        fraction = 0;
    } else if (fraction == 0) {
        exp = 0;
    } else {
        if (src->normal_exp < NORMAL_EXPMIN) {
            exp = 0;
            fraction = 0;
        } else if (src->normal_exp > EXPBIAS + 1
                   || (src->normal_exp == EXPBIAS + 1 && fraction >= IMPLICIT_2)) {
            exp = EXPMAX;
            fraction = 0;
        } else {
            exp = src->normal_exp + EXPBIAS;
            fraction >>= NGARDS;
        }
    }
    dst.bits.fraction = fraction;
    dst.bits.exp = exp;
    dst.bits.sign = sign;
    return dst.value;
}
