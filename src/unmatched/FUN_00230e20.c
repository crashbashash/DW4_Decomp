#include "dw4/fp_bit.h"

DFtype FUN_00230e20(fp_class_type class, unsigned int sign, int exp, UDItype frac) {
    fp_number_type in;

    in.class = class;
    in.sign = sign;
    in.normal_exp = exp;
    in.fraction.ll = frac;
    return pack_d(&in);
}
