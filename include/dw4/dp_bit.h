#ifndef DW4_DP_BIT_H
#define DW4_DP_BIT_H

typedef int SItype __attribute__((mode(SI)));
typedef unsigned int USItype __attribute__((mode(SI)));
typedef int DItype __attribute__((mode(DI)));
typedef unsigned int UDItype __attribute__((mode(DI)));
typedef float SFtype __attribute__((mode(SF)));
typedef float DFtype __attribute__((mode(DF)));

typedef UDItype fractype;
typedef DFtype FLO_type;
typedef DItype intfrac;

#define NGARDS 8L
#define EXPBITS 11
#define EXPBIAS 1023
#define FRACBITS 52
#define EXPMAX (0x7ff)
#define QUIET_NAN 0x8000000000000LL
#define FRAC_NBITS 64
#define FRACHIGH 0x8000000000000000LL
#define NORMAL_EXPMIN (-(EXPBIAS) + 1)
#define IMPLICIT_1 (1LL << (FRACBITS + NGARDS))
#define IMPLICIT_2 (1LL << (FRACBITS + 1 + NGARDS))
#define LSHIFT(a) { a = (a & 1) | (a >> 1); }

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

static __inline__ int isnan(fp_number_type *x) {
    return x->class == CLASS_SNAN || x->class == CLASS_QNAN;
}

static __inline__ int isinf(fp_number_type *x) {
    return x->class == CLASS_INFINITY;
}

static __inline__ int iszero(fp_number_type *x) {
    return x->class == CLASS_ZERO;
}

extern const fp_number_type __thenan_df;

static __inline__ fp_number_type *nan(void) {
    return (fp_number_type *)&__thenan_df;
}

FLO_type __pack_d(fp_number_type *);
void __unpack_d(FLO_union_type *, fp_number_type *);
int __fpcmp_parts_d(fp_number_type *, fp_number_type *);
fp_number_type *_fpadd_parts(fp_number_type *, fp_number_type *, fp_number_type *);
SFtype __make_fp(fp_class_type, unsigned int, int, USItype);

static __inline__ fp_number_type *_fpmul_parts(fp_number_type *a, fp_number_type *b, fp_number_type *tmp) {
    fractype low = 0;
    fractype high = 0;

    if (isnan(a)) {
        a->sign = a->sign != b->sign;
        return a;
    }
    if (isnan(b)) {
        b->sign = a->sign != b->sign;
        return b;
    }
    if (isinf(a)) {
        if (iszero(b)) {
            return nan();
        }
        a->sign = a->sign != b->sign;
        return a;
    }
    if (isinf(b)) {
        if (iszero(a)) {
            return nan();
        }
        b->sign = a->sign != b->sign;
        return b;
    }
    if (iszero(a)) {
        a->sign = a->sign != b->sign;
        return a;
    }
    if (iszero(b)) {
        b->sign = a->sign != b->sign;
        return b;
    }

    {
        UDItype nl = a->fraction.ll & 0xffffffff;
        UDItype nh = a->fraction.ll >> 32;
        UDItype ml = b->fraction.ll & 0xffffffff;
        UDItype mh = b->fraction.ll >> 32;
        UDItype pp_ll = ml * nl;
        UDItype pp_hl = mh * nl;
        UDItype pp_lh = ml * nh;
        UDItype pp_hh = mh * nh;
        UDItype res2 = 0;
        UDItype res0 = 0;
        UDItype ps_hh__ = pp_hl + pp_lh;
        if (ps_hh__ < pp_hl) {
            res2 += 0x100000000LL;
        }
        pp_hl = (ps_hh__ << 32) & 0xffffffff00000000LL;
        res0 = pp_ll + pp_hl;
        if (res0 < pp_ll) {
            res2++;
        }
        res2 += ((ps_hh__ >> 32) & 0xffffffffL) + pp_hh;
        high = res2;
        low = res0;
    }

    tmp->normal_exp = a->normal_exp + b->normal_exp;
    tmp->sign = a->sign != b->sign;
    tmp->normal_exp += 4;
    while (high >= IMPLICIT_2) {
        tmp->normal_exp++;
        if (high & 1) {
            low >>= 1;
            low |= FRACHIGH;
        }
        high >>= 1;
    }
    while (high < IMPLICIT_1) {
        tmp->normal_exp--;

        high <<= 1;
        if (low & FRACHIGH) {
            high |= 1;
        }
        low <<= 1;
    }
    tmp->fraction.ll = high;
    tmp->class = CLASS_NUMBER;
    return tmp;
}

static __inline__ fp_number_type *_fpdiv_parts(fp_number_type *a, fp_number_type *b) {
    fractype bit;
    fractype numerator;
    fractype denominator;
    fractype quotient;

    if (isnan(a)) {
        return a;
    }
    if (isnan(b)) {
        return b;
    }

    a->sign = a->sign ^ b->sign;

    if (isinf(a) || iszero(a)) {
        if (a->class == b->class) {
            return nan();
        }
        return a;
    }

    if (isinf(b)) {
        a->fraction.ll = 0;
        a->normal_exp = 0;
        return a;
    }
    if (iszero(b)) {
        a->class = CLASS_INFINITY;
        return a;
    }

    {
        a->normal_exp = a->normal_exp - b->normal_exp;
        numerator = a->fraction.ll;
        denominator = b->fraction.ll;

        if (numerator < denominator) {
            numerator *= 2;
            a->normal_exp--;
        }
        bit = IMPLICIT_1;
        quotient = 0;
        while (bit) {
            if (numerator >= denominator) {
                quotient |= bit;
                numerator -= denominator;
            }
            bit >>= 1;
            numerator *= 2;
        }
        a->fraction.ll = quotient;
        return (a);
    }
}

#endif
