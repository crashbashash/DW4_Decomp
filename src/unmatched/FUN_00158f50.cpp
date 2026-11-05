class VStream { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual int v23(int, void *); virtual void v24(); virtual int v25(void *, int, int); int refs; };
class VLoad { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual int v37(int); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual int v42(void *);  };
struct S { int *vt; char pad4[12]; int f16; char pad20[8]; int f28, f32, f36, f40, f44; char pad48[4]; void *f52; char pad56[4]; unsigned char f60; char pad61[3]; int f64; char pad68[4]; int f72; char pad76[8]; int f84; };
extern "C" {
int FUN_00156340(...);
int FUN_00159a80(...);
int FUN_00159f00(int);
void *FUN_002c4ca0(...);
int FUN_002eb010(...);
int Memory_FreeBuffer(...);
int StringChunk_ReleaseHeader(...);
int StringPool_Construct(...);
int StringPool_Intern(...);
int igObject_Destroy(...);
int FUN_00158cc0(...);
void *igObject_GetAllocator(...);
extern int DAT_004de6c0[4];
extern int DAT_00586f20[4];
int FUN_00158f50(S *arg0, int arg1);
}
#define REL_S(p) { int *q_ = (p); if (q_) { int *hd = q_ - 2; int c = q_[-1] - 1; q_[-1] = c; if (c == 0) StringChunk_ReleaseHeader(*hd, hd); } }
#define REL_O(p) { VStream *q_ = (p); if (q_) { int *r = (int *)q_; r[1] = r[1] - 1; if (((unsigned long long)(long long)r[1] & 0x7fffffULL) == 0) igObject_Destroy(q_); } }
int FUN_00158f50(S *arg0, int arg1) {
    int sp5C, sp58, sp54, sp50, sp4C, sp48, sp44;
    VStream * volatile sp40;
    int sp3C;
    int * volatile sp38;
    int a0;
    int *var_v0;
    int v;
    int r;
    a0 = *(int *)&arg0->f52;
    if (a0 != 0 && arg0->f60 != 0) Memory_FreeBuffer(a0);
    arg0->f52 = 0;
    arg0->f64 = 0;
    arg0->f72 = 0;
    arg0->f28 = 0;
    arg0->f32 = 0;
    arg0->f36 = 0;
    arg0->f40 = 0;
    arg0->f84 = 0;
    if (arg1 == 0) {
        var_v0 = 0;
    } else {
        if (DAT_00586f20[0] == 0) {
            v = FUN_002eb010(16);
            if (v != 0) v = StringPool_Construct(v);
            DAT_00586f20[0] = v;
        }
        var_v0 = (int *)StringPool_Intern(DAT_00586f20[0], arg1);
    }
    sp38 = var_v0;
    FUN_00156340(arg0, (void *)&sp38);
    REL_S(sp38)
    if ((((VLoad *)arg0)->v37(arg1) & 0xFF) == 1) {
        if (arg0->f44 < 0) {
            arg0->f44 = FUN_00159f00(arg0->f16);
            FUN_00159a80(arg0->f44, &sp5C, &sp58, &sp54, &sp50, &sp4C, &sp48, &sp44);
            arg0->f64 = sp5C;
            arg0->f72 = sp58;
            arg0->f28 = sp54;
            arg0->f32 = sp50;
            arg0->f36 = sp4C;
            arg0->f40 = sp48;
            arg0->f84 = sp44;
        }
        return 1;
    }
    sp40 = (VStream *)FUN_002c4ca0(igObject_GetAllocator(arg0));
    if (sp40->v23(arg1, &DAT_004de6c0[0]) == 0) {
        REL_O(sp40)
        return 0;
    }
    sp40->v25(&sp3C, 4, 1);
    switch (sp3C) {
    case 0x1F295FF4:
    case 0xF45F291F:
        r = ((VLoad *)arg0)->v42(sp40) & 0xFF;
        REL_O(sp40)
        return r;
    case 0x312A57F2:
    case 0xF2572A31:
        r = FUN_00158cc0(arg0, sp40) & 0xFF;
        REL_O(sp40)
        return r;
    default:
        sp40->v24();
        REL_O(sp40)
        return 0;
    }
}
