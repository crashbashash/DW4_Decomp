#ifndef DW4_FP_BIT_H
#define DW4_FP_BIT_H

#include "dw4/support/fp_bit_common.h"

typedef USItype fractype;
typedef SFtype FLO_type;
typedef SItype intfrac;

#define NGARDS 7L
#define EXPBITS 8
#define EXPBIAS 127
#define FRACBITS 23
#define EXPMAX (0xff)
#define NORMAL_EXPMIN (-(EXPBIAS) + 1)
#define IMPLICIT_1 (1LL << (FRACBITS + NGARDS))
#define IMPLICIT_2 (1LL << (FRACBITS + 1 + NGARDS))

typedef struct {
    fp_class_type class;
    unsigned int sign;
    int normal_exp;
    union {
        fractype ll;
    } fraction;
} fp_number_type;

typedef union {
    FLO_type value;
    struct {
        fractype fraction : FRACBITS __attribute__((packed));
        unsigned int exp : EXPBITS __attribute__((packed));
        unsigned int sign : 1 __attribute__((packed));
    } bits;
} FLO_union_type;

static __inline__ int iszero(fp_number_type *x) {
    return x->class == CLASS_ZERO;
}

FLO_type __pack_f(fp_number_type *);
void __unpack_f(FLO_union_type *, fp_number_type *);

#endif
