extern "C" {
int FUN_00150060(...);
int FUN_00150390(...);
int FUN_00156340(...);
int FUN_0015ad50(...);
int FUN_002b9500(...);
int FUN_002eb010(...);
int FUN_0030b3c0(...);
int StringChunk_ReleaseHeader(...);
int StringPool_Construct(...);
void *StringPool_Intern(...);
int igObject_Destroy(...);
int igObject_GetAllocator(...);
int strcmp(...);
extern int DAT_004df5b8[4];
extern int DAT_004df5c0[4];
extern int DAT_004df5c8[4];
extern int DAT_004df5d0[4];
extern int DAT_00586f20[4];
}
class G {
public:
 virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual int v21(void*,int);

};
class O0 {
public:
 virtual void d0();
  int refs;
};
class O1 {
public:
 virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual int v21(void*,void*);
  int refs;
};
class O2 {
public:
 virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual int v31(int);
  int refs;
};
extern "C" int Gap__Gfx__igPsx2Image__vfunc_39(G *arg0, int arg1)
{
  O0 * volatile sp5C;
  O1 * volatile sp58;
  O2 * volatile sp54;
  int sp50;
  int var_s0 = 0;
  int s;
  int a;
  int *h;
  int t;
  O0 *o;
  O1 *o1;
  O2 *o2;
  s = FUN_0015ad50(arg1);
  if (s != 0) {
    if (strcmp(s, &DAT_004df5b8[0]) != 0) {
      if (strcmp(s, &DAT_004df5c0[0]) == 0) goto block_4;
      goto block_22;
    }
block_4:
    sp5C = (O0 *)FUN_002b9500(igObject_GetAllocator(arg0));
    FUN_0030b3c0(sp5C, arg1);
    sp58 = (O1 *)FUN_00150060(igObject_GetAllocator(arg0));
    var_s0 = sp58->v21(sp5C, arg0) & 0xFF;
    if (arg1 == 0) {
      a = 0;
    } else {
      if (DAT_00586f20[0] == 0) {
        t = FUN_002eb010(0x10);
        if (t != 0) t = StringPool_Construct(t);
        DAT_00586f20[0] = t;
      }
      a = (int)StringPool_Intern(DAT_00586f20[0], arg1);
    }
    sp50 = a;
    FUN_00156340(arg0, &sp50);
    if (sp50 != 0) {
      h = (int *)sp50 - 2;
      t = ((int *)sp50)[-1] - 1;
      ((int *)sp50)[-1] = t;
      if (t == 0) StringChunk_ReleaseHeader(*h, h);
    }
    o1 = sp58;
    if (o1 != 0) {
      o1->refs = o1->refs - 1;
      if (((unsigned long long)(long long)o1->refs & 0x7fffffULL) == 0) igObject_Destroy(o1);
    }
    o = sp5C;
    if (o != 0) {
      o->refs = o->refs - 1;
      if (((unsigned long long)(long long)o->refs & 0x7fffffULL) == 0) igObject_Destroy(o);
    }
    return var_s0;
  }
block_22:
  if (s != 0) {
    if (strcmp(s, &DAT_004df5c8[0]) != 0) {
      if (strcmp(s, &DAT_004df5d0[0]) == 0) goto block_26;
    } else {
block_26:
      sp54 = (O2 *)FUN_00150390(igObject_GetAllocator(arg0));
      var_s0 = sp54->v31(arg1) & 0xFF;
      if (var_s0 != 0) {
        arg0->v21(sp54, 1);
      }
      o2 = sp54;
      if (o2 != 0) {
        o2->refs = o2->refs - 1;
        if (((unsigned long long)(long long)o2->refs & 0x7fffffULL) == 0) igObject_Destroy(o2);
      }
    }
  }
  return var_s0;
}
