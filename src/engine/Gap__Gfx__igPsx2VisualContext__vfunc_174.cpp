extern "C" {
int FUN_00178970(...);
int FUN_001f6f50(...);
int FUN_002073c0(...);
int FUN_00207560(...);
float FUN_00230e50(...);

}
struct N;
class B { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual int v100(); virtual long long v104(); virtual void d25(); virtual void d26(); virtual void v116(); };
class A { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void v112(float,float); virtual void v116(float); char pad[52]; B *f56; unsigned char b60; char p61[3]; int f64; float f68; char pad2[1480]; N *f1552; };
struct N { char pad0[4]; int f4; int f8; char pad1[4]; unsigned char b16; char pad2[463]; char f480[456]; long long f936; char pad3[8]; N *f952; };
extern "C" void Gap__Gfx__igPsx2VisualContext__vfunc_174(A *arg0) {
    float f20 = 0.0f;
    N *n;
    if (arg0->b60 != 0) {
        f20 = FUN_00230e50(arg0->f56->v100());
        arg0->f56->v116();
    }
    FUN_002073c0();
    FUN_00207560();
    if (arg0->b60 != 0) {
        arg0->v112(f20, f20 - arg0->f68);
        arg0->v116(f20);
        arg0->f64 = 0;
    }
    n = arg0->f1552;
    if (n != 0) {
      while (n != 0) {
        if (n->b16 != 0 && n->f8 == -n->f4) {
            FUN_001f6f50(n->f480);
            n->f936 = arg0->f56->v104();
            FUN_00178970(arg0, n);
            n->b16 = 0;
        }
        n = n->f952;
      }
    }
}
