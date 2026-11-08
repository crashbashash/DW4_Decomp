typedef unsigned int __ULong;
typedef struct _Bigint { struct _Bigint *_next; int _k, _maxwds, _sign, _wds; __ULong _x[1]; } _Bigint;
union double_union { double d; __ULong i[2]; };
struct _reent;
_Bigint *FUN_001273e0(struct _reent *ptr, int k);
int FUN_00127770(__ULong *y);
int FUN_001276f0(__ULong x);
#define word0(x) (x.i[1])
#define word1(x) (x.i[0])
#define Frac_mask 0xfffff
#define Exp_shift 20
#define Exp_msk1 0x100000
#define Bias 1023
#define P 53

_Bigint *FUN_00128130(struct _reent *ptr, double _d, int *e, int *bits)
{
  union double_union d;
  _Bigint *b;
  int de, i, k;
  __ULong *x, y, z;
  d.d = _d;
#define d0 word0(d)
#define d1 word1(d)
  d.d = _d;

  b = FUN_001273e0 (ptr, 1);
  x = b->_x;

  z = d0 & Frac_mask;
  d0 &= 0x7fffffff;
  if ((de = (int) (d0 >> Exp_shift)))
    z |= Exp_msk1;
  if (d1)
    {
      y = d1;
      k = FUN_00127770 (&y);
      if (k)
	{
	  x[0] = y | z << (32 - k);
	  z >>= k;
	}
      else
	x[0] = y;
      i = b->_wds = (x[1] = z) ? 2 : 1;
    }
  else
    {
      k = FUN_00127770 (&z);
      x[0] = z;
      i = b->_wds = 1;
      k += 32;
    }
  if (de)
    {
      *e = de - Bias - (P - 1) + k;
      *bits = P - k;
    }
  else
    {
      *e = de - Bias - (P - 1) + 1 + k;
      *bits = 32 * i - FUN_001276f0 (x[i - 1]);
    }
  return b;
}
