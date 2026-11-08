#include "dw4/fp_bit.h"

#define F_D_BITOFF (52 + 8 - (23 + 7))

FLO_type __pack_f(fp_number_type *src) {
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

void __unpack_f(FLO_union_type *src, fp_number_type *dst) {
    fractype fraction;
    int exp;
    int sign;

    fraction = src->bits.fraction;
    exp = src->bits.exp;
    sign = src->bits.sign;
    dst->sign = sign;
    if (exp == 0) {
        dst->class = CLASS_ZERO;
    } else {
        dst->normal_exp = exp - EXPBIAS;
        dst->class = CLASS_NUMBER;
        dst->fraction.ll = (fraction << NGARDS) | IMPLICIT_1;
    }
}

FLO_type __make_fp(fp_class_type class, unsigned int sign, int exp, fractype frac) {
    fp_number_type in;

    in.class = class;
    in.sign = sign;
    in.normal_exp = exp;
    in.fraction.ll = frac;
    return __pack_f(&in);
}

DFtype fptodp(FLO_type arg_a) {
    fp_number_type in;

    __unpack_f((FLO_union_type *)&arg_a, &in);
    return __make_dp(in.class, in.sign, in.normal_exp, ((UDItype)in.fraction.ll) << F_D_BITOFF);
}
