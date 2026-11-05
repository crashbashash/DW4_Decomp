class E { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual int vX(int); };
struct S { char pad[12]; int f12; char pad1[36]; E *f52; char pad2[16]; int f72; int f76; int f80; };
extern "C" {
int FUN_001b6ee0(int, int *);
int Matrix44_Copy(int *, int);
void FUN_00460260(S *arg0);
}
void FUN_00460260(S *arg0) {
    int m[16];

    Matrix44_Copy(m, arg0->f12 + 0x6C);
    FUN_001b6ee0(arg0->f80, m);
    FUN_001b6ee0(arg0->f72, m);
    arg0->f52->vX(arg0->f80 + 0xA4);
}
