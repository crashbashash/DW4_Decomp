#define NEED_NAN
#include "dw4/fp_bit.h"

#include "dw4/fp_bit_divdf3.h"

FLO_type __divdf3(FLO_type arg_a, FLO_type arg_b) {
    fp_number_type a;
    fp_number_type b;
    fp_number_type *res;

    unpack_d((FLO_union_type *)&arg_a, &a);
    unpack_d((FLO_union_type *)&arg_b, &b);

    res = _fpdiv_parts(&a, &b);

    return pack_d(res);
}
