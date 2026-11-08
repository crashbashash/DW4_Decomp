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
double
FUN_00127ec8(double _x)
{
  union double_union x, a;
  register __Long L;

  x.d = _x;

  L = (word0 (x) & Exp_mask) - (P - 1) * Exp_msk1;
#ifndef Sudden_Underflow
  if (L > 0)
    {
#endif
#ifdef IBM
      L |= Exp_msk1 >> 4;
#endif
      word0 (a) = L;
#ifndef _DOUBLE_IS_32BITS
      word1 (a) = 0;
#endif

#ifndef Sudden_Underflow
    }
  else
    {
      L = -L >> Exp_shift;
      if (L < Exp_shift)
	{
	  word0 (a) = 0x80000 >> L;
#ifndef _DOUBLE_IS_32BITS
	  word1 (a) = 0;
#endif
	}
      else
	{
	  word0 (a) = 0;
	  L -= Exp_shift;
#ifndef _DOUBLE_IS_32BITS
	  word1 (a) = L >= 31 ? 1 : 1 << 31 - L;
#endif
	}
    }
#endif
  return a.d;
}

