extern "C" {
int FUN_001b6ee0(void *, void *);
int Matrix44_Copy(void *, void *);
void FUN_00456610(int *arg0);
}
class Obj { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void vX(int); };
void FUN_00456610(int *arg0) {
    int m[16];
    ((Obj *)arg0[5])->vX(arg0[2]);
    Matrix44_Copy(m, (char *)arg0[4] + 0x20);
    FUN_001b6ee0((void *)arg0[5], m);
}
