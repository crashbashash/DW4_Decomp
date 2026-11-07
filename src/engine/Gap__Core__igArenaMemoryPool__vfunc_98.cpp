extern "C" {
int *FUN_002f89a0(...);
int FUN_003081d0(...);
int FUN_00318b40(...);
unsigned int FUN_0031d390(...);
extern int DAT_004f7910[4];
extern int DAT_004fd670[4];
extern int DAT_004fd6d0[4];
extern int DAT_004fd730[4];
extern int DAT_00587200[4];
extern unsigned int DAT_00587208[4];
extern unsigned int DAT_00587210[4];
extern unsigned char GPR_00554d6c;
extern unsigned char GPR_00554d70;
extern unsigned char GPR_00554d74;
}
struct R { int v; R() {} };
class VC { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual int v7(int); };
struct P { char pad[2020]; int f2020; int f2024; int f2028; int f2032; };
extern VC *DAT_00587218[4];
class O { public:
 virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual int v25(int); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual void d53(); virtual void d54(); virtual void d55(); virtual void d56(); virtual void d57(); virtual void d58(); virtual void d59(); virtual void d60(); virtual void d61(); virtual void d62(); virtual void d63(); virtual void d64(); virtual void d65(); virtual void d66(); virtual void d67(); virtual void d68(); virtual void d69(); virtual void d70(); virtual void d71(); virtual void d72(); virtual void d73(); virtual void d74(); virtual void d75(); virtual void d76(); virtual void d77(); virtual void d78(); virtual void d79(); virtual void d80(); virtual void d81(); virtual void d82(); virtual void d83(); virtual void d84(); virtual void d85(); virtual int v86(); virtual void d87(); virtual void d88(); virtual void d89(); virtual void d90(); virtual void d91(); virtual void d92(); virtual void d93(); virtual void d94(); virtual void d95(); virtual void d96(); virtual void d97(); virtual void d98(); virtual void d99(); virtual R v100();
 char p4[20]; long long f24; char p32[24]; int f56; char p60[28]; long long f88; char p96[16]; P * f112; char p116[44]; long long f160; char p168[12]; int f180; char p184[4]; int f188; unsigned int f192;
};
extern "C" void Gap__Core__igArenaMemoryPool__vfunc_98(O *arg0);
extern "C" void Gap__Core__igArenaMemoryPool__vfunc_98(O *arg0) {
    int *name;
    int r;
    P *temp_v1;
    int temp_a1;

    if (arg0->f160 == 0) {
        FUN_00318b40();
    }
    if ((int)arg0->f24 != 0) {
        name = FUN_002f89a0(arg0);
        arg0->v100();
        if ((arg0->f188 >= 3) && (GPR_00554d6c == 0)) {
            long long k24 = arg0->f24;
            name = name ? name : &DAT_004f7910[0];
            r = FUN_003081d0(&DAT_004fd670[0], name, arg0->f180, (int)k24);
            if ((r != 1) && (r == 2)) {
                GPR_00554d6c = 1;
            }
        }
        arg0->v86();
    } else if (arg0->f88 != 0) {
        name = FUN_002f89a0(arg0);
        if ((arg0->f188 >= 3) && (GPR_00554d70 == 0)) {
            long long k88 = arg0->f88;
            name = name ? name : &DAT_004f7910[0];
            r = FUN_003081d0(&DAT_004fd6d0[0], name, arg0->f180, (int)k88);
            if ((r != 1) && (r == 2)) {
                GPR_00554d70 = 1;
            }
        }
        arg0->v86();
    }
    int t = (arg0->f192 & 0x200) != 0;
    if (!t && FUN_0031d390(arg0) > 1U) {
        name = FUN_002f89a0(arg0);
        if ((arg0->f188 >= 3) && (GPR_00554d74 == 0)) {
            name = name ? name : &DAT_004f7910[0];
            r = FUN_003081d0(&DAT_004fd730[0], name, arg0->f180, FUN_0031d390(arg0));
            if ((r != 1) && (r == 2)) {
                GPR_00554d74 = 1;
            }
        }
    }
    DAT_00587208[0] += (int)arg0->f24;
    DAT_00587210[0] += arg0->f56;
    if (arg0->f160 == 0) {
        arg0->v25(0);
    }
    temp_v1 = arg0->f112;
    if (temp_v1 != 0) {
        temp_a1 = temp_v1->f2020;
        if (temp_a1 != 0) {
            DAT_00587218[0]->v7(temp_a1);
            arg0->f112->f2024 = 0;
            arg0->f112->f2028 = 0;
            arg0->f112->f2032 = 0;
        }
        DAT_00587218[0]->v7((int)arg0->f112);
        arg0->f112 = 0;
    }
    arg0->f112 = 0;
    DAT_00587200[0] -= 1;
}
