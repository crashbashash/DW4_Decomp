/* Splits a single-precision bit pattern into class, sign, unbiased exponent and guarded fraction;
 * exponent 0 is always zero (unpack_d built without denormals or NaNs). */
typedef unsigned int USItype __attribute__((mode(SI)));
typedef unsigned int UDItype __attribute__((mode(DI)));
typedef float SFtype __attribute__((mode(SF)));
typedef float DFtype __attribute__((mode(DF)));

/* fp-bit.c number classes */
typedef enum FloatClass {
    CLASS_SIGNALLING_NAN,
    CLASS_QUIET_NAN,
    CLASS_ZERO,
    CLASS_NUMBER,
    CLASS_INFINITY
} FloatClass;

/* fp-bit.c fp_number_type for single precision */
typedef struct FloatNumber {
    FloatClass numberClass;
    unsigned int sign;
    int normalExponent;
    union {
        USItype ll;
    } fraction;
} FloatNumber;

/* fp-bit.c FLO_union_type for single precision (little-endian bit order) */
typedef union FloatBits {
    SFtype value;
    struct {
        USItype fraction : 23;
        unsigned int exponent : 8;
        unsigned int sign : 1;
    } bits;
} FloatBits;

#define EXPONENT_BIAS 127
#define GUARD_BITS 7
#define IMPLICIT_ONE ((USItype)1 << (23 + GUARD_BITS))

void FUN_00230208(FloatBits *source, FloatNumber *destination) {
    USItype fraction;
    int exponent;
    int sign;

    fraction = source->bits.fraction;
    exponent = source->bits.exponent;
    sign = source->bits.sign;
    destination->sign = sign;
    if (exponent == 0) {
        destination->numberClass = CLASS_ZERO;
    } else {
        destination->normalExponent = exponent - EXPONENT_BIAS;
        destination->numberClass = CLASS_NUMBER;
        destination->fraction.ll = (fraction << GUARD_BITS) | IMPLICIT_ONE;
    }
}
