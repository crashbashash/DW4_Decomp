/* Soft-float double subtraction: unpacks both operands, flips the sign of the second, adds the
 * parts with FUN_00230470 and repacks the result. */
typedef unsigned int USItype __attribute__((mode(SI)));
typedef unsigned int UDItype __attribute__((mode(DI)));
typedef float DFtype __attribute__((mode(DF)));

/* fp-bit.c number classes */
typedef enum FloatClass {
    CLASS_SIGNALLING_NAN,
    CLASS_QUIET_NAN,
    CLASS_ZERO,
    CLASS_NUMBER,
    CLASS_INFINITY
} FloatClass;

/* fp-bit.c fp_number_type for double precision */
typedef struct DoubleNumber {
    FloatClass numberClass;
    unsigned int sign;
    int normalExponent;
    union {
        UDItype ll;
        USItype l[2];
    } fraction;
} DoubleNumber;

/* fp-bit.c FLO_union_type for double precision */
typedef union DoubleBits {
    DFtype value;
    UDItype bits;
} DoubleBits;

void unpack_d(DoubleBits *source, DoubleNumber *destination);
DoubleNumber *FUN_00230470(DoubleNumber *a, DoubleNumber *b, DoubleNumber *scratch);
DFtype pack_d(DoubleNumber *number);

DFtype FUN_00230728(DFtype valueA, DFtype valueB) {
    DoubleNumber a;
    DoubleNumber b;
    DoubleNumber scratch;
    DoubleNumber *result;
    DoubleBits bitsA;
    DoubleBits bitsB;

    bitsA.value = valueA;
    bitsB.value = valueB;
    unpack_d(&bitsA, &a);
    unpack_d(&bitsB, &b);
    b.sign ^= 1;
    result = FUN_00230470(&a, &b, &scratch);
    return pack_d(result);
}
