/* Converts a float to a signed 64-bit integer by converting its magnitude with FUN_0022ffe8 and
 * negating. */
typedef int SItype __attribute__((mode(SI)));
typedef unsigned int USItype __attribute__((mode(SI)));
typedef int DItype __attribute__((mode(DI)));
typedef unsigned int UDItype __attribute__((mode(DI)));
typedef float SFtype __attribute__((mode(SF)));
typedef float DFtype __attribute__((mode(DF)));

#define WORD_SIZE (sizeof(SItype) * 8)
#define HIGH_HALFWORD_COEFF (((UDItype)1) << (WORD_SIZE / 2))
#define HIGH_WORD_COEFF (((UDItype)1) << WORD_SIZE)

UDItype FUN_0022ffe8(SFtype a);

DItype FUN_00230110(SFtype a) {
    if (a < 0) {
        return -FUN_0022ffe8(-a);
    }
    return FUN_0022ffe8(a);
}
