typedef unsigned int __ULong;
typedef struct _Bigint { struct _Bigint *_next; int _k, _maxwds, _sign, _wds; __ULong _x[1]; } _Bigint;
union double_union { double d; __ULong i[2]; };
double FUN_00127f98(_Bigint *a, int *e);
#define word0(x) (x.i[1])
#define Exp_msk1 0x100000

double FUN_001282b8(_Bigint *a, _Bigint *b)
{
  union double_union da, db;
  int k, ka, kb;

  da.d = FUN_00127f98 (a, &ka);
  db.d = FUN_00127f98 (b, &kb);
  k = ka - kb + 32 * (a->_wds - b->_wds);
  if (k > 0)
    word0 (da) += k * Exp_msk1;
  else
    {
      k = -k;
      word0 (db) += k * Exp_msk1;
    }
  return da.d / db.d;
}
