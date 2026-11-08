#define NEED_NAN
#include "dw4/fp_bit.h"

#include "dw4/fp_bit_muldf3.h"

FLO_type __muldf3(FLO_type arg_a, FLO_type arg_b) {
    fp_number_type a;
    fp_number_type b;
    fp_number_type tmp;
    fp_number_type *res;

    unpack_d((FLO_union_type *)&arg_a, &a);
    unpack_d((FLO_union_type *)&arg_b, &b);

    res = _fpmul_parts(&a, &b, &tmp);

    return pack_d(res);
}
