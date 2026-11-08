#include "dw4/fp_bit.h"

int FUN_00230b58(fp_number_type *a, fp_number_type *b);

SItype FUN_00230c78(FLO_type arg_a, FLO_type arg_b) {
    fp_number_type a;
    fp_number_type b;

    unpack_d((FLO_union_type *)&arg_a, &a);
    unpack_d((FLO_union_type *)&arg_b, &b);
    return FUN_00230b58(&a, &b);
}
