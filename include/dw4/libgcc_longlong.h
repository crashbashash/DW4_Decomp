/* Word-pair helpers used by the EE GCC 2.96 libgcc2 64-bit division routines
 * (generic longlong.h fallbacks for a 32-bit word).  Shared by __udivdi3,
 * __divdi3, __umoddi3 and __moddi3, which inline __udivmoddi4. */
#ifndef LIBGCC_LONGLONG_H
#define LIBGCC_LONGLONG_H

typedef unsigned int UWtype;
typedef unsigned long long UDWtype;

typedef struct {
    int low;
    int high;
} DWstruct;

typedef union {
    DWstruct s;
    long long ll;
} DWunion;

/* libgcc2 __clz_tab: highest-set-bit count of each byte value. Each division
 * object carries its own copy; a file defines __clz_tab to its copy before
 * including this header. */
#ifndef __clz_tab
#define __clz_tab D_004e82a8
#endif
extern const unsigned char __clz_tab[256];

#define SI_TYPE_SIZE 32
#define W_TYPE_SIZE 32
#define __BITS4 (W_TYPE_SIZE / 4)
#define __ll_B ((UWtype) 1 << (W_TYPE_SIZE / 2))
#define __ll_lowpart(t) ((UWtype) (t) & (__ll_B - 1))
#define __ll_highpart(t) ((UWtype) (t) >> (W_TYPE_SIZE / 2))

/* Leading zero count of a 32-bit word through __clz_tab (generic longlong.h). */
#define count_leading_zeros(count, x) \
    do { \
        UWtype __xr = (x); \
        UWtype __a; \
        __a = __xr < ((UWtype) 1 << 2 * __BITS4) \
            ? (__xr < ((UWtype) 1 << __BITS4) ? 0 : __BITS4) \
            : (__xr < ((UWtype) 1 << 3 * __BITS4) ? 2 * __BITS4 : 3 * __BITS4); \
        (count) = W_TYPE_SIZE - (__clz_tab[__xr >> __a] + __a); \
    } while (0)

/* 32x32 -> 64 unsigned multiply into (w1:w0) with the MIPS multu/HI/LO pair. */
#define umul_ppmm(w1, w0, u, v) \
    __asm__("multu %2,%3" : "=l"((UWtype) (w0)), "=h"((UWtype) (w1)) \
            : "d"((UWtype) (u)), "d"((UWtype) (v)))

/* (sh:sl) = (ah:al) - (bh:bl), two-word subtract with borrow. */
#define sub_ddmmss(sh, sl, ah, al, bh, bl) \
    do { \
        UWtype __x; \
        __x = (al) - (bl); \
        (sh) = (ah) - (bh) - (__x > (al)); \
        (sl) = __x; \
    } while (0)

/* Divide the two-word (n1:n0) by d (n1 < d) into quotient q and remainder r,
 * by schoolbook division on 16-bit halves (generic longlong.h fallback). */
#define udiv_qrnnd(q, r, n1, n0, d) \
    do { \
        UWtype __d1, __d0, __q1, __q0; \
        UWtype __r1, __r0, __m; \
        __d1 = __ll_highpart(d); \
        __d0 = __ll_lowpart(d); \
        __r1 = (n1) % __d1; \
        __q1 = (n1) / __d1; \
        __m = (UWtype) __q1 * __d0; \
        __r1 = __r1 * __ll_B | __ll_highpart(n0); \
        if (__r1 < __m) { \
            __q1--, __r1 += (d); \
            if (__r1 >= (d)) \
                if (__r1 < __m) \
                    __q1--, __r1 += (d); \
        } \
        __r1 -= __m; \
        __r0 = __r1 % __d1; \
        __q0 = __r1 / __d1; \
        __m = (UWtype) __q0 * __d0; \
        __r0 = __r0 * __ll_B | __ll_lowpart(n0); \
        if (__r0 < __m) { \
            __q0--, __r0 += (d); \
            if (__r0 >= (d)) \
                if (__r0 < __m) \
                    __q0--, __r0 += (d); \
        } \
        __r0 -= __m; \
        (q) = (UWtype) __q1 * __ll_B | __q0; \
        (r) = __r0; \
    } while (0)


/* libgcc2 __udivmoddi4: quotient returned, remainder stored through rp when
 * non-null.  Inlined into each caller, as built into the retail image. */
static inline UDWtype __udivmoddi4(UDWtype u, UDWtype v, UDWtype *rp)
{
    DWunion ww, nn, dd, rr;
    UWtype d0, d1, n0, n1, n2;
    UWtype q0, q1;
    UWtype b, bm;

    nn.ll = u;
    dd.ll = v;
    d0 = dd.s.low;
    d1 = dd.s.high;
    n0 = nn.s.low;
    n1 = nn.s.high;

    if (d1 == 0) {
        if (d0 > n1) {
            /* 0q = nn / 0D */
            count_leading_zeros(bm, d0);
            if (bm != 0) {
                d0 = d0 << bm;
                n1 = (n1 << bm) | (n0 >> (SI_TYPE_SIZE - bm));
                n0 = n0 << bm;
            }
            udiv_qrnnd(q0, n0, n1, n0, d0);
            q1 = 0;
        } else {
            /* qq = NN / 0d */
            if (d0 == 0)
                d0 = 1 / d0; /* divide intentionally by zero */
            count_leading_zeros(bm, d0);
            if (bm == 0) {
                n1 -= d0;
                q1 = 1;
            } else {
                b = SI_TYPE_SIZE - bm;
                d0 = d0 << bm;
                n2 = n1 >> b;
                n1 = (n1 << bm) | (n0 >> b);
                n0 = n0 << bm;
                udiv_qrnnd(q1, n1, n2, n1, d0);
            }
            udiv_qrnnd(q0, n0, n1, n0, d0);
        }
        if (rp != 0) {
            rr.s.low = n0 >> bm;
            rr.s.high = 0;
            *rp = rr.ll;
        }
    } else {
        if (d1 > n1) {
            /* 00 = nn / DD: remainder is nn */
            q0 = 0;
            q1 = 0;
            if (rp != 0) {
                rr.s.low = n0;
                rr.s.high = n1;
                *rp = rr.ll;
            }
        } else {
            /* 0q = NN / dd */
            count_leading_zeros(bm, d1);
            if (bm == 0) {
                if (n1 > d1 || n0 >= d0) {
                    q0 = 1;
                    sub_ddmmss(n1, n0, n1, n0, d1, d0);
                } else
                    q0 = 0;
                q1 = 0;
                if (rp != 0) {
                    rr.s.low = n0;
                    rr.s.high = n1;
                    *rp = rr.ll;
                }
            } else {
                UWtype m1, m0;
                b = SI_TYPE_SIZE - bm;
                d1 = (d1 << bm) | (d0 >> b);
                d0 = d0 << bm;
                n2 = n1 >> b;
                n1 = (n1 << bm) | (n0 >> b);
                n0 = n0 << bm;
                udiv_qrnnd(q0, n1, n2, n1, d1);
                umul_ppmm(m1, m0, q0, d0);
                if (m1 > n1 || (m1 == n1 && m0 > n0)) {
                    q0--;
                    sub_ddmmss(m1, m0, m1, m0, d1, d0);
                }
                q1 = 0;
                if (rp != 0) {
                    sub_ddmmss(n1, n0, n1, n0, m1, m0);
                    rr.s.low = (n1 << b) | (n0 >> bm);
                    rr.s.high = n1 >> bm;
                    *rp = rr.ll;
                }
            }
        }
    }

    ww.s.low = q0;
    ww.s.high = q1;
    return ww.ll;
}

#endif
