#define Pack_32
#define IEEE_8087
typedef unsigned int __ULong;
typedef int __Long;
typedef unsigned int size_t;
typedef struct _Bigint {
    struct _Bigint *_next;
    int _k, _maxwds, _sign, _wds;
    __ULong _x[1];
} _Bigint;
struct _reent {
    int _errno;
    void *_stdin, *_stdout, *_stderr;
    int _inc;
    char _emergency[25];
    int _current_category;
    const char *_current_locale;
    int __sdidinit;
    void (*__cleanup)(struct _reent *);
    struct _Bigint *_result;
    int _result_k;
    struct _Bigint *_p5s;
    struct _Bigint **_freelist;
};
union double_union {
    double d;
    __ULong i[2];
};
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
void *memcpy(void *, const void *, size_t);
_Bigint *FUN_001273e0(struct _reent *, int);
void FUN_00127488(struct _reent *, _Bigint *);
_Bigint *FUN_001274b8(struct _reent *, _Bigint *, int, int);
_Bigint *FUN_00127830(struct _reent *, int);
_Bigint *FUN_00127868(struct _reent *, _Bigint *, _Bigint *);
int FUN_00127cd0(_Bigint *, _Bigint *);
int FUN_001276f0(__ULong);
int FUN_00127770(__ULong *);
#define Balloc FUN_001273e0
#define Bfree FUN_00127488
#define multadd FUN_001274b8
#define s2b FUN_001275c0
#define i2b FUN_00127830
#define mult FUN_00127868
#define pow5mult FUN_00127a78
#define lshift FUN_00127b78
#define cmp FUN_00127cd0
#define diff FUN_00127d38
#define ulp FUN_00127ec8
#define hi0bits FUN_001276f0
#define lo0bits FUN_00127770
#define _DEFUN(name, arglist, args) name(args)
#define _AND ,
#define _CONST const
#define Sign_Extend(a, b)
int
FUN_001238a8(_Bigint * b, _Bigint * S)
{
  int n;
  __Long borrow, y;
  __ULong carry, q, ys;
  __ULong *bx, *bxe, *sx, *sxe;
#ifdef Pack_32
  __Long z;
  __ULong si, zs;
#endif

  n = S->_wds;
#ifdef DEBUG
  /*debug*/ if (b->_wds > n)
    /*debug*/ Bug ("oversize b in quorem");
#endif
  if (b->_wds < n)
    return 0;
  sx = S->_x;
  sxe = sx + --n;
  bx = b->_x;
  bxe = bx + n;
  q = *bxe / (*sxe + 1);	/* ensure q <= true quotient */
#ifdef DEBUG
  /*debug*/ if (q > 9)
    /*debug*/ Bug ("oversized quotient in quorem");
#endif
  if (q)
    {
      borrow = 0;
      carry = 0;
      do
	{
#ifdef Pack_32
	  si = *sx++;
	  ys = (si & 0xffff) * q + carry;
	  zs = (si >> 16) * q + (ys >> 16);
	  carry = zs >> 16;
	  y = (*bx & 0xffff) - (ys & 0xffff) + borrow;
	  borrow = y >> 16;
	  Sign_Extend (borrow, y);
	  z = (*bx >> 16) - (zs & 0xffff) + borrow;
	  borrow = z >> 16;
	  Sign_Extend (borrow, z);
	  Storeinc (bx, z, y);
#else
	  ys = *sx++ * q + carry;
	  carry = ys >> 16;
	  y = *bx - (ys & 0xffff) + borrow;
	  borrow = y >> 16;
	  Sign_Extend (borrow, y);
	  *bx++ = y & 0xffff;
#endif
	}
      while (sx <= sxe);
      if (!*bxe)
	{
	  bx = b->_x;
	  while (--bxe > bx && !*bxe)
	    --n;
	  b->_wds = n;
	}
    }
  if (cmp (b, S) >= 0)
    {
      q++;
      borrow = 0;
      carry = 0;
      bx = b->_x;
      sx = S->_x;
      do
	{
#ifdef Pack_32
	  si = *sx++;
	  ys = (si & 0xffff) + carry;
	  zs = (si >> 16) + (ys >> 16);
	  carry = zs >> 16;
	  y = (*bx & 0xffff) - (ys & 0xffff) + borrow;
	  borrow = y >> 16;
	  Sign_Extend (borrow, y);
	  z = (*bx >> 16) - (zs & 0xffff) + borrow;
	  borrow = z >> 16;
	  Sign_Extend (borrow, z);
	  Storeinc (bx, z, y);
#else
	  ys = *sx++ + carry;
	  carry = ys >> 16;
	  y = *bx - (ys & 0xffff) + borrow;
	  borrow = y >> 16;
	  Sign_Extend (borrow, y);
	  *bx++ = y & 0xffff;
#endif
	}
      while (sx <= sxe);
      bx = b->_x;
      bxe = bx + n;
      if (!*bxe)
	{
	  while (--bxe > bx && !*bxe)
	    --n;
	  b->_wds = n;
	}
    }
  return q;
}

/* dtoa for IEEE arithmetic (dmg): convert double to ASCII string.
 *
 * Inspired by "How to Print Floating-Point Numbers Accurately" by
 * Guy L. Steele, Jr. and Jon L. White [Proc. ACM SIGPLAN '90, pp. 92-101].
 *
 * Modifications:
 *	1. Rather than iterating, we use a simple numeric overestimate
 *	   to determine k = floor(log10(d)).  We scale relevant
 *	   quantities using O(log2(k)) rather than O(k) multiplications.
 *	2. For some modes > 2 (corresponding to ecvt and fcvt), we don't
 *	   try to generate digits strictly left to right.  Instead, we
 *	   compute with fewer bits and propagate the carry if necessary
 *	   when rounding the final digit up.  This is often faster.
 *	3. Under the assumption that input will be rounded nearest,
 *	   mode 0 renders 1e23 as 1e23 rather than 9.999999999999999e22.
 *	   That is, we allow equality in stopping tests when the
 *	   round-nearest rule will give the same floating-point value
 *	   as would satisfaction of the stopping test with strict
 *	   inequality.
 *	4. We remove common factors of powers of 2 from relevant
 *	   quantities.
 *	5. When converting floating-point integers less than 1e16,
 *	   we use floating-point arithmetic rather than resorting
 *	   to multiple-precision integers.
 *	6. When asked to produce fewer than 15 digits, we first try
 *	   to get by with floating-point arithmetic; we resort to
 *	   multiple-precision integer arithmetic only if we cannot
 *	   guarantee that the floating-point calculation has given
 *	   the correctly rounded result.  For k requested digits and
 *	   "uniformly" distributed input, the probability is
 *	   something like 10^(k-15) that we must resort to the long
 *	   calculation.
 */


