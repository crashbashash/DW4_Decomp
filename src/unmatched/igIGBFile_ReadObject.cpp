struct R { int w0; R() {} R(const R &o) { w0 = o.w0; } bool operator==(const R &o) const { return w0 == o.w0; } };
struct T { int w0; int refs; };
struct C { char p0[80]; int f80; int f84; char p88[12]; int f100; char p104[64]; unsigned char f168; char p169[23]; int f192; char p196[20]; int f216; char p220[40]; int f260; int f264; char p268[12]; int f280; };
extern "C" {
int FUN_002e3a10(...);
int FUN_002e7030(R *, C *);
int FUN_002fff90(T*, int*, C*, int, unsigned char);
int FUN_00300250(T*, int*, C*, int, unsigned char);
int igObject_IsKindOf(...);
int igObject_Destroy(...);
int igObject_RegisterInstance(...);
extern R DAT_004fb418[2];
extern int DAT_00586710[4];
}
class MF {
public:
  virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9();
  virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19();
  virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29();
  virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39();
  virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49();
  virtual int vX(int *, int);
};
extern "C" {
void *igIntMetaField_GetDefaultDescriptor(...);
void *igMetaObject_CreateInstanceWithPool(...);
int igIGBFile_ReadObject(T **arg0, C *arg1);
}
int igIGBFile_ReadObject(T **arg0, C *arg1)
{
  int sp5C;
  T * volatile sp58;
  int *s0;
  T *s3, *r2;
  T *t;
  int v;
  int r;
  R sp54;
  int o = arg1->f80;
  int ea = arg1->f264 + o;
  int t0;
  if (o > arg1->f260 - 9 || (t0 = arg1->f216 * 4 + (arg1->f80 + FUN_002e3a10(arg1, ea)), arg1->f260 < t0)) {
    r = FUN_002e7030(&sp54, arg1);
    if (*(R *)(int)&sp54 == DAT_004fb418[0]) {
      *arg0 = 0;
      t = *arg0;
      if (t != 0) t->refs = t->refs + 1;
      return r;
    }
  }
  s0 = (int *)((char *)arg1->f264 + arg1->f80);
  sp5C = *s0;
  if (arg1->f168 != 0) {
    ((MF *)igIntMetaField_GetDefaultDescriptor())->vX(&sp5C, 1);
  }
  s3 = (T *)igMetaObject_CreateInstanceWithPool(*(int *)(*(int *)((char *)arg1->f192 + 16) + sp5C * 4), arg1->f280);
  if (s3 != 0 && igObject_IsKindOf(s3, DAT_00586710[0]) != 0) {
    r2 = s3;
  } else {
    r2 = 0;
  }
  sp58 = r2;
  t = sp58;
  if (t != 0) t->refs = t->refs + 1;
  t = sp58;
  t->refs = t->refs - 1;
  if (((unsigned long long)(long long)t->refs & 0x7fffffULL) == 0) igObject_Destroy(t);
  igObject_RegisterInstance(sp58, 0);
  if (arg1->f100 < 4) {
    v = FUN_002fff90(sp58, s0, arg1, arg1->f192, arg1->f168);
  } else {
    v = FUN_00300250(sp58, s0, arg1, arg1->f192, arg1->f168);
  }
  arg1->f80 = arg1->f80 + v;
  arg1->f84 = arg1->f84 + v;
  arg1->f80 = arg1->f80 + arg1->f216 * 4;
  arg1->f84 = arg1->f84 + arg1->f216 * 4;
  *arg0 = sp58;
  t = *arg0;
  if (t != 0) t->refs = t->refs + 1;
  t = sp58;
  if (t != 0) {
    t->refs = t->refs - 1;
    if (((unsigned long long)(long long)t->refs & 0x7fffffULL) == 0) igObject_Destroy(t);
  }
  return 0;
}
