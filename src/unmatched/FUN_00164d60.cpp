extern "C" {
int *FUN_001649f0();
int *FUN_00164a60();
int *FUN_00164aa0();
int *FUN_00164b10();
int *FUN_00164b80();
int *FUN_00164c20();
int *FUN_00164c70();
int *FUN_00164ca0();
int *FUN_00164cd0();
int *FUN_00164d50();
}
class VC { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual int v88(); };
struct A { char pad12[12]; VC *f12; unsigned int f16; };
extern "C" int FUN_00164d60(int arg0, A *arg1);
int FUN_00164d60(int arg0, A *arg1) {
    int *p; int v;
    p = 0;
    switch (arg1->f16) {
    case 1: p = (int *)FUN_001649f0(); break;
    case 2: p = (int *)FUN_00164a60(); break;
    case 3: p = (int *)FUN_00164aa0(); break;
    case 4: p = (int *)FUN_00164b10(); break;
    case 5: p = (int *)FUN_00164b80(); break;
    case 6: p = (int *)FUN_00164c20(); break;
    case 7: p = (int *)FUN_00164c70(); break;
    case 8: p = (int *)FUN_00164ca0(); break;
    case 9: p = (int *)FUN_00164cd0(); break;
    case 10: p = (int *)FUN_00164d50(); break;
    }
    goto test;
body:
    if (v == arg1->f12->v88()) { return 1; }
    p = p + 1;
test:
    v = *p;
    if (v != 0) goto body;
    return 0;
}
