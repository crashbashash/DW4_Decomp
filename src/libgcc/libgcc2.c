typedef int SItype __attribute__((mode(SI)));
typedef unsigned int USItype __attribute__((mode(SI)));
typedef int DItype __attribute__((mode(DI)));
typedef unsigned int UDItype __attribute__((mode(DI)));
typedef float SFtype __attribute__((mode(SF)));
typedef float DFtype __attribute__((mode(DF)));

#define WORD_SIZE (sizeof(SItype) * 8)
#define HIGH_HALFWORD_COEFF (((UDItype)1) << (WORD_SIZE / 2))
#define HIGH_WORD_COEFF (((UDItype)1) << WORD_SIZE)

#define DI_SIZE (sizeof(DItype) * 8)
#define DF_SIZE 53
#define SF_SIZE 24
#define REP_BIT ((UDItype)1 << (DI_SIZE - DF_SIZE))

DItype __fixunsdfdi(DFtype a);
DItype __fixunssfdi(SFtype original_a);

DFtype __floatdidf(DItype u) {
    DFtype d;

    d = (SItype)(u >> WORD_SIZE);
    d *= HIGH_HALFWORD_COEFF;
    d *= HIGH_HALFWORD_COEFF;
    d += (USItype)(u & (HIGH_WORD_COEFF - 1));

    return d;
}

SFtype __floatdisf(DItype u) {
    DFtype f;

    if (DF_SIZE < DI_SIZE && DF_SIZE > (DI_SIZE - DF_SIZE + SF_SIZE)) {
        if (!(-((DItype)1 << DF_SIZE) < u && u < ((DItype)1 << DF_SIZE))) {
            if ((UDItype)u & (REP_BIT - 1)) {
                u |= REP_BIT;
            }
        }
    }
    f = (SItype)(u >> WORD_SIZE);
    f *= HIGH_HALFWORD_COEFF;
    f *= HIGH_HALFWORD_COEFF;
    f += (USItype)(u & (HIGH_WORD_COEFF - 1));

    return (SFtype)f;
}

DItype __fixunsdfdi(DFtype a) {
    DFtype b;
    UDItype v;

    if (a < 0) {
        return 0;
    }

    b = (a / HIGH_WORD_COEFF);
    v = (USItype)b;
    v <<= WORD_SIZE;
    a -= (DFtype)v;
    if (a < 0) {
        v -= (USItype)(-a);
    } else {
        v += (USItype)a;
    }
    return v;
}

DItype __fixdfdi(DFtype a) {
    if (a < 0) {
        return -__fixunsdfdi(-a);
    }
    return __fixunsdfdi(a);
}

DItype __fixunssfdi(SFtype original_a) {
    DFtype a = original_a;
    DFtype b;
    UDItype v;

    if (a < 0) {
        return 0;
    }

    b = (a / HIGH_WORD_COEFF);
    v = (USItype)b;
    v <<= WORD_SIZE;
    a -= (DFtype)v;
    if (a < 0) {
        v -= (USItype)(-a);
    } else {
        v += (USItype)a;
    }
    return v;
}

DItype __fixsfdi(SFtype a) {
    if (a < 0) {
        return -__fixunssfdi(-a);
    }
    return __fixunssfdi(a);
}
