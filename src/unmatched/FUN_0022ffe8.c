typedef int SItype __attribute__((mode(SI)));
typedef unsigned int USItype __attribute__((mode(SI)));
typedef int DItype __attribute__((mode(DI)));
typedef unsigned int UDItype __attribute__((mode(DI)));
typedef float SFtype __attribute__((mode(SF)));
typedef float DFtype __attribute__((mode(DF)));

#define WORD_SIZE (sizeof(SItype) * 8)
#define HIGH_HALFWORD_COEFF (((UDItype)1) << (WORD_SIZE / 2))
#define HIGH_WORD_COEFF (((UDItype)1) << WORD_SIZE)

DItype FUN_0022ffe8(SFtype original_a) {
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
