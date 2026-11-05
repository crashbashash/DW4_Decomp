/* 0x00154860 - FUN_00154860. 27-entry string-table loop through a virtual call (C++ unit, T27 struct copies); alternate compiler. Verified byte-identical by tools/verify.py. */
extern "C" int sprintf(char *, const char *, int);
extern "C" int FUN_002d9740(int, int, int, char *);
struct T27 { int v[27]; };
extern T27 DAT_0048a180;
extern T27 DAT_0048a1f0;
extern char DAT_004de6a8[];
class V { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual int vX(int); };
extern "C" void FUN_00154860(V *arg0, int arg1) {
    T27 sp140 = DAT_0048a180;
    T27 spD0 = DAT_0048a1f0;
    char sp50[128];
    int i;
    for (i = 0; i < 27; i++) {
        sprintf(sp50, DAT_004de6a8, arg0->vX(sp140.v[i]));
        FUN_002d9740(arg1, 8, spD0.v[i], sp50);
    }
}
