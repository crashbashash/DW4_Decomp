extern "C" {
int FUN_002364e0(...);
int FUN_004541f0(...);
int FUN_00457ca0(...);
int igObject_Destroy(...);
struct OO;
void FUN_00237530(OO *arg0);
}
struct R; class DW4VC_152 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual R *vX(); };
struct R { int w0; int rc; };
struct Lst { char pad[8]; int n; int w12; int *items; };
struct Wr { char pad[8]; Lst *f8; };
struct OO { char pad[20]; DW4VC_152 *f20; R *f24; Wr *f28; int f32; };
void FUN_00237530(OO *arg0) {
    R *sp4C;
    int temp_s1;
    int var_s0;
    R *t;
    R *s0;

    if (arg0->f20 == 0) {
        FUN_002364e0(&sp4C, 0);
        s0 = sp4C;
        if (s0 != 0) {
            s0->rc = s0->rc + 1;
        }
        t = (R *)arg0->f20;
        if (t != 0) {
            t->rc = t->rc - 1;
            if ((t->rc & 0x7FFFFF) == 0) {
                igObject_Destroy(t);
            }
        }
        arg0->f20 = (DW4VC_152 *)s0;
        if (sp4C != 0) {
            sp4C->rc = sp4C->rc - 1;
            if ((sp4C->rc & 0x7FFFFF) == 0) {
                igObject_Destroy(sp4C);
            }
        }
    }
    s0 = arg0->f20->vX();
    if (s0 != 0) {
        s0->rc = s0->rc + 1;
    }
    t = arg0->f24;
    if (t != 0) {
        t->rc = t->rc - 1;
        if ((t->rc & 0x7FFFFF) == 0) {
            igObject_Destroy(t);
        }
    }
    arg0->f24 = s0;
    FUN_004541f0(arg0->f32, arg0->f20);
    temp_s1 = arg0->f28->f8->n;
    var_s0 = 0;
    while (var_s0 < temp_s1) {
        FUN_00457ca0(arg0->f28->f8->items[var_s0], arg0->f24);
        var_s0 += 1;
    }
}
