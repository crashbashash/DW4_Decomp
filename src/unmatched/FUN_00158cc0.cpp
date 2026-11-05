struct S { char p0[8]; int f8, f12, f16, f20, f24, f28, f32, f36, f40, f44, f48; void *f52; char p56[4]; char f60; char p61[3]; int f64; char p68[4]; int f72, f76; char p80[4]; int f84; };
extern "C" {
int FUN_00159320(...);
int FUN_00159a80(...);
int FUN_00159f00(int);
void **Memory_GetAllocatorBySelector(...);
void **igObject_GetAllocator(...);
extern int DAT_005870e8[4];
extern unsigned char GPR_00554c14;
int FUN_00158cc0(S *arg0, void **arg1);
}
class VStream { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual int v24(); virtual int v25(void *, int, int); };
class VObj { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual int v38(); };
class VAlloc { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual void *v53(int, int); };
int FUN_00158cc0(S *arg0, void **arg1) {
    unsigned int sp5C;
    unsigned int sp58;
    int sp54, sp50, sp4C, sp48, sp44, sp40, sp3C, sp38, sp34, sp30;
    int temp_s0;
    void **var_v0;
    VStream *st = (VStream *)arg1;

    if (!(((VObj *)arg0)->v38() & 0xFF)) {
        st->v25((char *)arg0 + 48, 4, 1);
        st->v25((char *)arg0 + 8, 4, 1);
        st->v25((char *)arg0 + 12, 4, 1);
        st->v25((char *)arg0 + 16, 4, 1);
        st->v25((char *)arg0 + 20, 4, 1);
        st->v25(&sp58, 4, 1);
        arg0->f28 = (sp58 >> 24) & 0xFF;
        arg0->f32 = (sp58 >> 16) & 0xFF;
        arg0->f36 = (sp58 >> 8) & 0xFF;
        arg0->f40 = (unsigned char)sp58;
        arg0->f84 = 0;
        arg0->f72 = 0;
        arg0->f64 = 0;
        st->v25(&sp5C, 4, 1);
        st->v25(&sp5C, 4, 1);
        var_v0 = igObject_GetAllocator(arg0);
        var_v0 = (GPR_00554c14 != 0) ? var_v0 : Memory_GetAllocatorBySelector(DAT_005870e8[0]);
        arg0->f52 = ((VAlloc *)var_v0)->v53(arg0->f48, 0x80);
        arg0->f60 = 1;
        st->v25(arg0->f52, 1, arg0->f48);
        st->v24();
        arg0->f44 = FUN_00159f00(arg0->f16);
    }
    temp_s0 = arg0->f44;
    FUN_00159320(arg0, temp_s0, arg0->f8, arg0->f12, &sp54, &sp50, &sp4C);
    arg0->f76 = sp4C;
    FUN_00159a80(temp_s0, &sp48, &sp44, &sp40, &sp3C, &sp38, &sp34, &sp30);
    arg0->f64 = sp48;
    arg0->f72 = sp44;
    arg0->f28 = sp40;
    arg0->f32 = sp3C;
    arg0->f36 = sp38;
    arg0->f40 = sp34;
    arg0->f84 = sp30;
    arg0->f24 = 0x64;
    return 1;
}
