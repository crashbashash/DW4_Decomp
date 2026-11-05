extern "C" {
int FUN_00100610(...);
void **FUN_001007e0(int);
void *FUN_00236f80(...);
void **FUN_00238110(...);
int FUN_00239390(...);
int FUN_00238d40(...);
int FUN_00259d40(...);
int FUN_00259f80(...);
int FUN_0025afe0(...);
int FUN_002eb010(...);
int FUN_003343a0(...);
int FUN_0033bf50(...);
int FUN_003719c0(...);
int FUN_003b04e0(...);
int FUN_00463b30(...);
int FUN_00463b70(...);
int FUN_00463bb0(...);
int FUN_00463bc0(...);
int FUN_00463c70(...);
int StringChunk_ReleaseHeader(...);
int StringPool_Construct(...);
void *StringPool_Intern(...);
extern int DAT_004ecf60[16];
struct Fr;
extern struct Fr *DAT_0056dc50[16];
extern struct A0 *DAT_0056df80[16];
extern int DAT_00586f20[16];
extern int DAT_00587d08[16];
}
struct Fr {
    void *f0;
    char f4;
    unsigned char f5;
    char p0[86];
    unsigned char f92;
    char p1;
    unsigned char f94;
    char p2[53];
    int f148;
    int f152;
    int f156;
    int f160;
    char p3[4];
    unsigned char f168;
    char p4[11];
    unsigned char f180;
    char p5[32];
    unsigned char f213;
    char p6[18];
    int f232;
    void *f236;
};
struct Rd {
    char p0[16];
    unsigned char f16;
    char p1[43];
    void *f60;
    unsigned char f64;
};
struct X { char p0[52]; int f52; char p1[8]; long long f64; };
class D { public: virtual void e0(); virtual void e1(); virtual void e2(); virtual void e3(); virtual void e4(); virtual void e5(); virtual void e6(); virtual void e7(); virtual void e8(); virtual void e9(); virtual void e10(); virtual void e11(); virtual void e12(); virtual void e13(); virtual void e14(); virtual void e15(); virtual void e16(); virtual void e17(); virtual void e18(); virtual void e19(); virtual void e20(); virtual void e21(); virtual void e22(); virtual void e23(); virtual void e24(); virtual void e25(); virtual void e26(); virtual void e27(); virtual void e28(); virtual void e29(); virtual void e30(); virtual void e31(); virtual void e32(); virtual void e33(); virtual void e34(); virtual void e35(); virtual void e36(); virtual void e37(); virtual void e38(); virtual void e39(); virtual void e40(); virtual void e41(); virtual void e42(); virtual void e43(); virtual void e44(); virtual void e45(); virtual void e46(); virtual void e47(); virtual void e48(); virtual void e49(); virtual void e50(); virtual void e51(); virtual void e52(); virtual void e53(); virtual void e54(); virtual void e55(); virtual void e56(); virtual void e57(); virtual void e58(); virtual void e59(); virtual void e60(); virtual void e61(); virtual void e62(); virtual void e63(); virtual void e64(); virtual void e65(); virtual void e66(); virtual void e67(); virtual void e68(); virtual void e69(); virtual void e70(); virtual void e71(); virtual void e72(); virtual void e73(); virtual void e74(); virtual void e75(); virtual void e76(); virtual void e77(); virtual void e78(); virtual void e79(); virtual void e80(); virtual void e81(); virtual void e82(); virtual void e83(); virtual void e84(); virtual void e85(); virtual void e86(); virtual void e87(); virtual void e88(); virtual void e89(); virtual void e90(); virtual void e91(); virtual void e92(); virtual void e93(); virtual void e94(); virtual void e95(); virtual void e96(); virtual void e97(); virtual void e98(); virtual void e99(); virtual void e100(); virtual void e101(); virtual void e102(); virtual void e103(); virtual void e104(); virtual void e105(); virtual void e106(); virtual void e107(); virtual void e108(); virtual void e109(); virtual void e110(); virtual void e111(); virtual void e112(); virtual void e113(); virtual void e114(); virtual void e115(); virtual void e116(); virtual void e117(); virtual void e118(); virtual void e119(); virtual void e120(); virtual void e121(); virtual void e122(); virtual void e123(); virtual void e124(); virtual void e125(); virtual void e126(); virtual void e127(); virtual void e128(); virtual void e129(); virtual void e130(); virtual void e131(); virtual void e132(); virtual void e133(); virtual void e134(); virtual void e135(); virtual void e136(); virtual void e137(); virtual void e138(); virtual void e139(); virtual void e140(); virtual void e141(); virtual void e142(); virtual void e143(); virtual void e144(); virtual void e145(); virtual void e146(); virtual void e147(); virtual void e148(); virtual void e149(); virtual void e150(); virtual void e151(); virtual void e152(); virtual void e153(); virtual void e154(); virtual void e155(); virtual void e156(); virtual void e157(); virtual void e158(); virtual void e159(); virtual void e160(); virtual void e161(); virtual void e162(); virtual void e163(); virtual void e164(); virtual void e165(); virtual void e166(); virtual void e167(); virtual void e168(); virtual void e169(); virtual void e170(); virtual void e171(); virtual void e172(); virtual void e173(); virtual void e174();  virtual void vB(int *); };
class C { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35();  virtual D *vA(); };
struct A0 { X *f0; char p0[20]; C *f24; char p1[16]; unsigned char f44; };
extern "C" void FUN_0025a580(A0 *arg0);
void FUN_0025a580(A0 *arg0) {
    Rd *s0;
    void *s2;
    int sp40[4];
    if (arg0->f24 != 0) {
        DAT_0056df80[0] = arg0;
        if (DAT_0056dc50[0] == 0) {
            void **v = FUN_001007e0(0xF0);
            if (v != 0) {
                v = FUN_00238110(v);
            }
            DAT_0056dc50[0] = (Fr *)v;
        }
        DAT_0056dc50[0]->f232 = DAT_0056dc50[0]->f232 + 1;
        {
            Fr *g = DAT_0056dc50[0];
            g->f180 = 0;
            g->f213 = 0;
            g->f5 = 0;
            g->f148 = 0x3DCCCCCD;
            g->f152 = 0x3DCCCCCD;
            g->f156 = 0x3DCCCCCD;
            g->f160 = 0x3F800000;
            g->f92 = 0;
            g->f94 = 1;
            g->f168 = 1;
        }
        if (DAT_0056dc50[0] != 0) {
            int rc = DAT_0056dc50[0]->f232 - 1;
            DAT_0056dc50[0]->f232 = rc;
            if (rc <= 0) {
                Fr *f = DAT_0056dc50[0];
                if (f != 0) {
                    if (&f->f236) {
                        void *p = f->f236;
                        if (p != 0) {
                            int *h = (int *)((char *)p - 8);
                            int r = *(int *)((char *)p - 4) - 1;
                            *(int *)((char *)p - 4) = r;
                            if (r == 0) {
                                StringChunk_ReleaseHeader(*h, h);
                            }
                        }
                    }
                    if (f != 0) {
                        void *p = f->f0;
                        if (p != 0) {
                            int *h = (int *)((char *)p - 8);
                            int r = *(int *)((char *)p - 4) - 1;
                            *(int *)((char *)p - 4) = r;
                            if (r == 0) {
                                StringChunk_ReleaseHeader(*h, h);
                            }
                        }
                    }
                    FUN_00100610(f);
                }
                DAT_0056dc50[0] = 0;
            }
        }
        FUN_00239390();
        FUN_00238d40();
        FUN_003343a0();
        FUN_0033bf50();
        FUN_003719c0();
        FUN_003b04e0();
        FUN_00463b30(arg0);
        FUN_00259f80(arg0);
        FUN_00463c70(arg0);
        s0 = (Rd *)FUN_00236f80(arg0->f0, DAT_00587d08[0]);
        if (DAT_00586f20[0] == 0) {
            int v = FUN_002eb010(0x10);
            if (v != 0) {
                v = StringPool_Construct(v);
            }
            DAT_00586f20[0] = v;
        }
        {
            void *old;
            s2 = StringPool_Intern(DAT_00586f20[0], DAT_004ecf60);
            old = s0->f60;
            if (old != 0) {
                int *h = (int *)((char *)old - 8);
                int r = *(int *)((char *)old - 4) - 1;
                *(int *)((char *)old - 4) = r;
                if (r == 0) {
                    StringChunk_ReleaseHeader(*h, h);
                }
            }
            s0->f60 = s2;
        }
        {
            D *dd = arg0->f24->vA();
            sp40[0] = 0;
            sp40[3] = 0x3F800000;
            sp40[1] = 0;
            sp40[2] = 0;
            dd->vB(sp40);
        }
        while (arg0->f44 == 0 && s0->f16 == 0) {
            while (arg0->f44 == 0 && s0->f64 != 0) {
                X *x = arg0->f0;
                int a1 = ((x->f64 >= 0xFE502B)) & 0xFF;
                if (x->f52 % 15 != 0) {
                    a1 = 0;
                }
                FUN_00259d40(arg0, a1);
                if (FUN_00463bc0(arg0) == 0) break;
                FUN_00463bb0(arg0);
            }
            if (s0->f60 == 0) break;
            FUN_0025afe0(arg0);
            s0->f64 = 1;
        }
        FUN_0025afe0(arg0);
        FUN_00463b70(arg0);
        DAT_0056df80[0] = 0;
    }
}
