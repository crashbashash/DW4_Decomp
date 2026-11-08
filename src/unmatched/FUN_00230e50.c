#include "dw4/fp_bit.h"

#define F_D_BITOFF (52 + 8 - (23 + 7))

extern SFtype FUN_00230268(fp_class_type, unsigned int, int, USItype);

SFtype FUN_00230e50(DFtype arg_a) {
    fp_number_type in;
    USItype sffrac;

    unpack_d((FLO_union_type *)&arg_a, &in);
    sffrac = in.fraction.ll >> F_D_BITOFF;

    if ((in.fraction.ll & (((USItype)1 << F_D_BITOFF) - 1)) != 0) {
        sffrac |= 1;
    }
    return FUN_00230268(in.class, in.sign, in.normal_exp, sffrac);
}
