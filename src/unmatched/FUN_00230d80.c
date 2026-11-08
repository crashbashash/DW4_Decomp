#include "dw4/fp_bit.h"

#define MAX_SI_INT ((SItype)((unsigned)(~0) >> 1))

SItype FUN_00230d80(FLO_type arg_a) {
    fp_number_type a;
    SItype tmp;

    unpack_d((FLO_union_type *)&arg_a, &a);
    if (iszero(&a)) {
        return 0;
    }
    if (isnan(&a)) {
        return 0;
    }
    if (isinf(&a)) {
        return a.sign ? (-MAX_SI_INT) - 1 : MAX_SI_INT;
    }
    if (a.normal_exp < 0) {
        return 0;
    }
    if (a.normal_exp > 30) {
        return a.sign ? (-MAX_SI_INT) - 1 : MAX_SI_INT;
    }
    tmp = a.fraction.ll >> ((FRACBITS + NGARDS) - a.normal_exp);
    return a.sign ? (-tmp) : (tmp);
}
