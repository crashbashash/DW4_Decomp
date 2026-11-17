#ifndef DW4_FP_BIT_COMMON_H
#define DW4_FP_BIT_COMMON_H

/* What libgcc's single- and double-precision software float (fp_bit.c, dp_bit.c) share: the machine-mode
 * integer and float types, the class of an unpacked number, and the two calls that convert between the
 * precisions by packing the other one. */
typedef int SItype __attribute__((mode(SI)));
typedef unsigned int USItype __attribute__((mode(SI)));
typedef int DItype __attribute__((mode(DI)));
typedef unsigned int UDItype __attribute__((mode(DI)));
typedef float SFtype __attribute__((mode(SF)));
typedef float DFtype __attribute__((mode(DF)));

typedef enum { CLASS_SNAN, CLASS_QNAN, CLASS_ZERO, CLASS_NUMBER, CLASS_INFINITY } fp_class_type;

SFtype __make_fp(fp_class_type class, unsigned int sign, int exp, USItype frac);
DFtype __make_dp(fp_class_type class, unsigned int sign, int exp, UDItype frac);

#endif
