struct S { int p[3]; int t; };
class O { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void v128(int); virtual void v132(int);
  int p[4]; int f20; };
extern "C" int FUN_001d2230(int a0, S *src, S *dst, O *obj, int flag) {
    int r;
    dst->t = src->t;
    switch (src->t) {
    case 1:
        r = 2;
        if (flag == 0) { dst->t = 0; obj->v128(6); obj->v132(0); }
        break;
    case 2:
        r = 1;
        if (flag == 0) { dst->t = 0; obj->v128(1); obj->v132(1); }
        break;
    case 3:
        dst->t = 0; r = 9; obj->f20 = 1;
        break;
    case 4:
        dst->t = 0; r = 9; obj->f20 = 2;
        break;
    case 11:
        r = 9;
        if (flag == 0) { dst->t = 0; obj->v128(4); obj->v132(5); }
        break;
    default:
        dst->t = 0; r = 9; obj->v128(4); obj->v132(5);
        break;
    }
    return r;
}
