/* newlib's libc/stdlib/mprec.h: David Gay's bignum arithmetic as dtoa.c, strtod.c and mprec.c share it. */
#ifndef DW4_NEWLIB_MPREC_H
#define DW4_NEWLIB_MPREC_H

#include "dw4/newlib_reent.h"

typedef int __Long;
typedef struct _Bigint _Bigint;

union double_union {
    double d;
    __ULong i[2];
};

#define _Kmax 15
#define Pack_32
#define IEEE_8087
#define word0(x) (x.i[1])
#define word1(x) (x.i[0])
#define Storeinc(a, b, c) (((unsigned short *)a)[1] = (unsigned short)b, ((unsigned short *)a)[0] = (unsigned short)c, a++)
#define Exp_shift 20
#define Exp_shift1 20
#define Exp_msk1 ((__ULong)0x100000L)
#define Exp_mask ((__ULong)0x7ff00000L)
#define P 53
#define Bias 1023
#define Exp_1 ((__ULong)0x3ff00000L)
#define Ebits 11
#define Frac_mask ((__ULong)0xfffffL)
#define Bcopy(x, y) memcpy((char *)&x->_sign, (char *)&y->_sign, y->_wds * sizeof(__Long) + 2 * sizeof(int))
#define Sign_Extend(a, b)
#define Balloc _Balloc
#define Bfree _Bfree
#define multadd _multadd
#define s2b _s2b
#define hi0bits _hi0bits
#define lo0bits _lo0bits
#define i2b _i2b
#define mult _multiply
#define pow5mult _pow5mult
#define lshift _lshift
#define cmp __mcmp
#define diff __mdiff
#define ulp _ulp
#define b2d _b2d
#define d2b _d2b
#define ratio _ratio
#define Exp_msk11 ((__ULong)0x100000L)
#define Exp_11 ((__ULong)0x3ff00000L)
#define Frac_mask1 ((__ULong)0xfffffL)
#define Ten_pmax 22
#define Bletch 0x10
#define Bndry_mask ((__ULong)0xfffffL)
#define Bndry_mask1 ((__ULong)0xfffffL)
#define LSB 1
#define Sign_bit ((__ULong)0x80000000L)
#define Log2P 1
#define Tiny0 0
#define Tiny1 1
#define Quick_max 14
#define Int_max 14
#define IEEE_Arith
#define Emin (-1022)
#define n_bigtens 5
#define rounded_product(a, b) a *= b
#define rounded_quotient(a, b) a /= b
#define tens __mprec_tens
#define bigtens __mprec_bigtens
#define tinytens __mprec_tinytens

void *memcpy(void *, const void *, size_t);
_Bigint *_Balloc(struct _reent *, int);
void _Bfree(struct _reent *, _Bigint *);
_Bigint *_multadd(struct _reent *, _Bigint *, int, int);
_Bigint *_s2b(struct _reent *, const char *, int, int, __ULong);
int _hi0bits(__ULong);
int _lo0bits(__ULong *);
_Bigint *_i2b(struct _reent *, int);
_Bigint *_multiply(struct _reent *, _Bigint *, _Bigint *);
_Bigint *_pow5mult(struct _reent *, _Bigint *, int);
_Bigint *_lshift(struct _reent *, _Bigint *, int);
int __mcmp(_Bigint *, _Bigint *);
_Bigint *__mdiff(struct _reent *, _Bigint *, _Bigint *);
double _ulp(double);
double _b2d(_Bigint *, int *);
_Bigint *_d2b(struct _reent *, double, int *, int *);
double _ratio(_Bigint *, _Bigint *);
double _mprec_log10(int);

extern const double __mprec_tens[];
extern const double __mprec_bigtens[];
extern const double __mprec_tinytens[];

#endif
