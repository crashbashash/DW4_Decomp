#include "dw4/dp_bit.h"

#define MAX_SI_INT ((SItype)((unsigned)(~0) >> 1))
#define MAX_USI_INT ((USItype)~0)
#define F_D_BITOFF (52 + 8 - (23 + 7))

FLO_type __pack_d(fp_number_type *src) {
    FLO_union_type dst;
    fractype fraction = src->fraction.ll;
    int sign = src->sign;
    int exp = 0;

    if (isnan(src)) {
        exp = EXPMAX;
        fraction |= QUIET_NAN;
    } else if (isinf(src)) {
        exp = EXPMAX;
        fraction = 0;
    } else if (iszero(src)) {
        exp = 0;
        fraction = 0;
    } else if (fraction == 0) {
        exp = 0;
    } else {
        if (src->normal_exp < NORMAL_EXPMIN) {
            exp = 0;
            fraction = 0;
        } else if (src->normal_exp > EXPBIAS) {
            exp = EXPMAX;
            fraction = 0;
        } else {
            exp = src->normal_exp + EXPBIAS;
            fraction >>= NGARDS;
        }
    }
    dst.bits.fraction = fraction;
    dst.bits.exp = exp;
    dst.bits.sign = sign;
    return dst.value;
}

void __unpack_d(FLO_union_type *src, fp_number_type *dst) {
    fractype fraction;
    int exp;
    int sign;

    fraction = src->bits.fraction;
    exp = src->bits.exp;
    sign = src->bits.sign;
    dst->sign = sign;
    if (exp == 0) {
        dst->class = CLASS_ZERO;
    } else if (exp == EXPMAX) {
        dst->normal_exp = EXPBIAS;
        if (fraction == 0) {
            dst->class = CLASS_INFINITY;
            dst->fraction.ll = IMPLICIT_1;
        } else {
            if (fraction & QUIET_NAN) {
                dst->class = CLASS_QNAN;
            } else {
                dst->class = CLASS_SNAN;
            }
            dst->fraction.ll = fraction;
        }
    } else {
        dst->normal_exp = exp - EXPBIAS;
        dst->class = CLASS_NUMBER;
        dst->fraction.ll = (fraction << NGARDS) | IMPLICIT_1;
    }
}

fp_number_type *_fpadd_parts(fp_number_type *a, fp_number_type *b, fp_number_type *tmp) {
    intfrac tfraction;
    int a_normal_exp;
    int b_normal_exp;
    fractype a_fraction;
    fractype b_fraction;

    if (isnan(a)) {
        return a;
    }
    if (isnan(b)) {
        return b;
    }
    if (isinf(a)) {
        if (isinf(b) && a->sign != b->sign) {
            return nan();
        }
        return a;
    }
    if (isinf(b)) {
        return b;
    }
    if (iszero(b)) {
        if (iszero(a)) {
            *tmp = *a;
            tmp->sign = a->sign & b->sign;
            return tmp;
        }
        return a;
    }
    if (iszero(a)) {
        return b;
    }

    {
        int diff;

        a_normal_exp = a->normal_exp;
        b_normal_exp = b->normal_exp;
        a_fraction = a->fraction.ll;
        b_fraction = b->fraction.ll;

        diff = a_normal_exp - b_normal_exp;

        if (diff < 0) {
            diff = -diff;
        }
        if (diff < FRAC_NBITS) {
            while (a_normal_exp > b_normal_exp) {
                b_normal_exp++;
                LSHIFT(b_fraction);
            }
            while (b_normal_exp > a_normal_exp) {
                a_normal_exp++;
                LSHIFT(a_fraction);
            }
        } else {
            if (a_normal_exp > b_normal_exp) {
                b_normal_exp = a_normal_exp;
                b_fraction = 0;
            } else {
                a_normal_exp = b_normal_exp;
                a_fraction = 0;
            }
        }
    }

    if (a->sign != b->sign) {
        if (a->sign) {
            tfraction = -a_fraction + b_fraction;
        } else {
            tfraction = a_fraction - b_fraction;
        }
        if (tfraction >= 0) {
            tmp->sign = 0;
            tmp->normal_exp = a_normal_exp;
            tmp->fraction.ll = tfraction;
        } else {
            tmp->sign = 1;
            tmp->normal_exp = a_normal_exp;
            tmp->fraction.ll = -tfraction;
        }

        while (tmp->fraction.ll < IMPLICIT_1 && tmp->fraction.ll) {
            tmp->fraction.ll <<= 1;
            tmp->normal_exp--;
        }
    } else {
        tmp->sign = a->sign;
        tmp->normal_exp = a_normal_exp;
        tmp->fraction.ll = a_fraction + b_fraction;
    }
    tmp->class = CLASS_NUMBER;

    if (tmp->fraction.ll >= IMPLICIT_2) {
        LSHIFT(tmp->fraction.ll);
        tmp->normal_exp++;
    }
    return tmp;
}

FLO_type dpadd(FLO_type arg_a, FLO_type arg_b) {
    fp_number_type a;
    fp_number_type b;
    fp_number_type tmp;
    fp_number_type *res;

    __unpack_d((FLO_union_type *)&arg_a, &a);
    __unpack_d((FLO_union_type *)&arg_b, &b);

    res = _fpadd_parts(&a, &b, &tmp);

    return __pack_d(res);
}

FLO_type dpsub(FLO_type arg_a, FLO_type arg_b) {
    fp_number_type a;
    fp_number_type b;
    fp_number_type tmp;
    fp_number_type *res;

    __unpack_d((FLO_union_type *)&arg_a, &a);
    __unpack_d((FLO_union_type *)&arg_b, &b);
    b.sign ^= 1;

    res = _fpadd_parts(&a, &b, &tmp);

    return __pack_d(res);
}

FLO_type dpmul(FLO_type arg_a, FLO_type arg_b) {
    fp_number_type a;
    fp_number_type b;
    fp_number_type tmp;
    fp_number_type *res;

    __unpack_d((FLO_union_type *)&arg_a, &a);
    __unpack_d((FLO_union_type *)&arg_b, &b);

    res = _fpmul_parts(&a, &b, &tmp);

    return __pack_d(res);
}

FLO_type dpdiv(FLO_type arg_a, FLO_type arg_b) {
    fp_number_type a;
    fp_number_type b;
    fp_number_type *res;

    __unpack_d((FLO_union_type *)&arg_a, &a);
    __unpack_d((FLO_union_type *)&arg_b, &b);

    res = _fpdiv_parts(&a, &b);

    return __pack_d(res);
}

int __fpcmp_parts_d(fp_number_type *a, fp_number_type *b) {
    if (isnan(a) || isnan(b)) {
        return 1;
    }
    if (isinf(a) && isinf(b)) {
        return b->sign - a->sign;
    }
    if (isinf(a)) {
        return a->sign ? -1 : 1;
    }
    if (isinf(b)) {
        return b->sign ? 1 : -1;
    }
    if (iszero(a) && iszero(b)) {
        return 0;
    }
    if (iszero(a)) {
        return b->sign ? 1 : -1;
    }
    if (iszero(b)) {
        return a->sign ? -1 : 1;
    }
    if (a->sign != b->sign) {
        return a->sign ? -1 : 1;
    }
    if (a->normal_exp > b->normal_exp) {
        return a->sign ? -1 : 1;
    }
    if (a->normal_exp < b->normal_exp) {
        return a->sign ? 1 : -1;
    }
    if (a->fraction.ll > b->fraction.ll) {
        return a->sign ? -1 : 1;
    }
    if (a->fraction.ll < b->fraction.ll) {
        return a->sign ? 1 : -1;
    }
    return 0;
}

SItype dpcmp(FLO_type arg_a, FLO_type arg_b) {
    fp_number_type a;
    fp_number_type b;

    __unpack_d((FLO_union_type *)&arg_a, &a);
    __unpack_d((FLO_union_type *)&arg_b, &b);
    return __fpcmp_parts_d(&a, &b);
}

FLO_type litodp(SItype arg_a) {
    fp_number_type in;

    in.class = CLASS_NUMBER;
    in.sign = arg_a < 0;
    if (!arg_a) {
        in.class = CLASS_ZERO;
    } else {
        in.normal_exp = FRACBITS + NGARDS;
        if (in.sign) {
            if (arg_a == (SItype)0x80000000) {
                return -2147483648.0;
            }
            in.fraction.ll = (-arg_a);
        } else {
            in.fraction.ll = arg_a;
        }

        while (in.fraction.ll < IMPLICIT_1) {
            in.fraction.ll <<= 1;
            in.normal_exp -= 1;
        }
    }
    return __pack_d(&in);
}

SItype dptoli(FLO_type arg_a) {
    fp_number_type a;
    SItype tmp;

    __unpack_d((FLO_union_type *)&arg_a, &a);
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

DFtype __make_dp(fp_class_type class, unsigned int sign, int exp, UDItype frac) {
    fp_number_type in;

    in.class = class;
    in.sign = sign;
    in.normal_exp = exp;
    in.fraction.ll = frac;
    return __pack_d(&in);
}

SFtype dptofp(DFtype arg_a) {
    fp_number_type in;
    USItype sffrac;

    __unpack_d((FLO_union_type *)&arg_a, &in);
    sffrac = in.fraction.ll >> F_D_BITOFF;

    if ((in.fraction.ll & (((USItype)1 << F_D_BITOFF) - 1)) != 0) {
        sffrac |= 1;
    }
    return __make_fp(in.class, in.sign, in.normal_exp, sffrac);
}

USItype dptoul(FLO_type arg_a) {
    fp_number_type a;

    __unpack_d((FLO_union_type *)&arg_a, &a);
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
