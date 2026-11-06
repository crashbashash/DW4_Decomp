/* Widens a float to a double by unpacking it and repacking the fraction 30 bits higher with
 * FUN_00230e20 (fp-bit __extendsfdf2 shape; name is a hypothesis). */
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

#define FLOAT_TO_DOUBLE_SHIFT 30 /* F_D_BITOFF */

void FUN_00230208(FloatBits *source, FloatNumber *destination);
DFtype FUN_00230e20(FloatClass numberClass, unsigned int sign, int exponent, UDItype fraction);

DFtype FUN_00230298(SFtype value) {
    FloatNumber number;
    FloatBits bits;

    bits.value = value;
    FUN_00230208(&bits, &number);
    return FUN_00230e20(number.numberClass, number.sign, number.normalExponent,
                        ((UDItype)number.fraction.ll) << FLOAT_TO_DOUBLE_SHIFT);
}
