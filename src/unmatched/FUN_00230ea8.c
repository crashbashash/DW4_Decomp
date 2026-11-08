#include "dw4/fp_bit.h"

#define MAX_USI_INT ((USItype)~0)

USItype FUN_00230ea8(FLO_type arg_a) {
    fp_number_type a;

    unpack_d((FLO_union_type *)&arg_a, &a);
    if (iszero(&a)) {
        return 0;
    }
    if (isnan(&a)) {
        return 0;
    }
    if (a.sign) {
        return 0;
    }
    if (isinf(&a)) {
        return MAX_USI_INT;
    }
    if (a.normal_exp < 0) {
        return 0;
    }
    if (a.normal_exp > 31) {
        return MAX_USI_INT;
    } else if (a.normal_exp > (FRACBITS + NGARDS)) {
        return a.fraction.ll << (a.normal_exp - (FRACBITS + NGARDS));
    } else {
        return a.fraction.ll >> ((FRACBITS + NGARDS) - a.normal_exp);
    }
}
