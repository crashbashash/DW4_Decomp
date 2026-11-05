extern "C" {
int FUN_0018ffa0(...);
int FUN_0023b3b0(...);
int FUN_0023b720(...);
}
class Sph { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19();  virtual int vX();
    char pad[4]; float f8; float f12; float f16; float f20; };
struct Tab { char pad[16]; int *f16; };
struct Grid { char pad[8]; Tab *f8; int f12; int f16; int f20; };
struct Ent { char pad[16]; int f16; };
struct Arg1 { char pad[12]; Sph *f12; };
extern int DAT_00560fa0[4];
extern "C" void FUN_0023b820(Grid *arg0, Arg1 *arg1) {
    int mnx, mny, mnz, mxx, mxy, mxz;
    float v[3];
    Sph *s0;
    int z;
    int y;
    int x;
    int base1, base2;
    Ent *e;
    float r;
    s0 = arg1->f12;
    mnx = -1; mny = -1; mnz = -1; mxx = -1; mxy = -1; mxz = -1;
    if (DAT_00560fa0[0] == s0->vX()) {
        r = s0->f20;
        v[0] = s0->f8 - r;
        v[1] = s0->f12 - r;
        v[2] = s0->f16 - r;
        FUN_0023b720(arg0, v, &mnx, &mny, &mnz);
        v[0] = s0->f8 + r;
        v[1] = s0->f12 + r;
        v[2] = s0->f16 + r;
        FUN_0023b720(arg0, v, &mxx, &mxy, &mxz);
    }
    for (z = mnz; z <= mxz; z++) {
        base1 = arg0->f20 * z;
        for (y = mny; y <= mxy; y++) {
            base2 = arg0->f16 * (y + base1);
            for (x = mnx; x <= mxx; x++) {
                e = (Ent *)arg0->f8->f16[x + base2];
                if (FUN_0018ffa0(e->f16, arg1->f12) != 0) {
                    FUN_0023b3b0(e, arg1);
                }
            }
        }
    }
}
