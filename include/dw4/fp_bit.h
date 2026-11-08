#ifndef DW4_FP_BIT_H
#define DW4_FP_BIT_H

typedef int SItype __attribute__((mode(SI)));
typedef unsigned int USItype __attribute__((mode(SI)));
typedef int DItype __attribute__((mode(DI)));
typedef unsigned int UDItype __attribute__((mode(DI)));
typedef float SFtype __attribute__((mode(SF)));
typedef float DFtype __attribute__((mode(DF)));

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

typedef enum { CLASS_SNAN, CLASS_QNAN, CLASS_ZERO, CLASS_NUMBER, CLASS_INFINITY } fp_class_type;

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
DFtype __make_dp(fp_class_type, unsigned int, int, UDItype);

#endif
