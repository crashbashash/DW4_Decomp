struct HI { char pad[32]; int f32; int f36; char pad2[4]; int f44; };
class O48 {
public:
    virtual void d0();
    virtual void d1();
    virtual void d2();
    virtual void d3();
    virtual void d4();
    virtual void d5();
    virtual void d6();
    virtual void d7();
    virtual void d8();
    virtual void d9();
    virtual void d10();
    virtual void d11();
    virtual void d12();
    virtual void d13();
    virtual void d14();
    virtual void d15();
    virtual void d16();
    virtual void d17();
    virtual void d18();
    virtual void d19();
    virtual void d20();
    virtual void d21();
    virtual void d22();
    virtual void d23();
    virtual void d24();
    virtual void d25();
    virtual void d26();
    virtual void d27();
    virtual void d28();
    virtual void d29();
    virtual void d30();
    virtual void d31();
    virtual int v136(int);
    int refs;
};
class O44 {
public:
    virtual void d0();
    virtual void d1();
    virtual void d2();
    virtual void d3();
    virtual void d4();
    virtual void d5();
    virtual void d6();
    virtual void d7();
    virtual void d8();
    virtual void d9();
    virtual void d10();
    virtual void d11();
    virtual void d12();
    virtual void d13();
    virtual void d14();
    virtual void d15();
    virtual void d16();
    virtual void d17();
    virtual void d18();
    virtual void d19();
    virtual void d20();
    virtual void d21();
    virtual void d22();
    virtual void d23();
    virtual O48 *v104(void *);
    int refs;
};
class O40 {
public:
    virtual void d0();
    virtual void d1();
    virtual void d2();
    virtual void d3();
    virtual void d4();
    virtual void d5();
    virtual void d6();
    virtual void d7();
    virtual void d8();
    virtual void d9();
    virtual void d10();
    virtual void d11();
    virtual void d12();
    virtual void d13();
    virtual void d14();
    virtual void d15();
    virtual void d16();
    virtual void d17();
    virtual void d18();
    virtual void d19();
    virtual void d20();
    virtual void d21();
    virtual void d22();
    virtual void d23();
    virtual void d24();
    virtual int v108(int *, int);
    virtual int v112(int *, int);
};
class PA {
public:
    virtual void d0();
    virtual void d1();
    virtual void d2();
    virtual void d3();
    virtual void d4();
    virtual void d5();
    virtual void d6();
    virtual void d7();
    virtual void d8();
    virtual void d9();
    virtual void d10();
    virtual void d11();
    virtual void d12();
    virtual void d13();
    virtual void d14();
    virtual void d15();
    virtual void d16();
    virtual void d17();
    virtual void d18();
    virtual void d19();
    virtual void d20();
    virtual int v92(int, int, O44 *, float, float);
    int pad4;
    HI *f8;
    int f12;
    char pad16[4];
    float f20;
    float f24;
    float f28;
    int f32;
    int f36;
    O40 *f40;
    O44 *f44;
    O48 *f48;
    int f52;
    int f56;
    char pad60[12];
    unsigned char f72;
    unsigned char f73;
    char pad74[2];
    int (*f76)(float, int, int, int, int, O40 *, O48 *);
    char pad80[4];
    float f84;
    int f88;
};
extern "C" {
extern long long DAT_00560668[4];
extern int DAT_004dc000[4];
void *FUN_00166d40(void);
void FUN_0015db90(int *);
void FUN_0015b880(PA *);
void FUN_0015bc20(PA *, int, int);
void igObject_Destroy(void *);
int Gap__Gfx__igParticleArray__vfunc_28(PA *arg0, int arg1, int arg2, int *arg3, float fparg0);
}
extern "C" int Gap__Gfx__igParticleArray__vfunc_28(PA *arg0, int arg1, int arg2, int *arg3, float fparg0) {
    int sp70[8];
    int temp_s0;
    O44 *a;
    O44 *t;
    O48 *b;
    O48 *u;
    arg0->f28 = fparg0;
    if (!(fparg0 <= arg0->f24 + arg0->f84)) {
        *arg3 = 1;
        return 1;
    }
    if (fparg0 < arg0->f20) {
        *arg3 = 2;
        return 1;
    }
    DAT_00560668[0] += 1;
    if (arg0->f44 == 0) {
        if (arg0->f44 == 0) {
            a = (O44 *)FUN_00166d40();
            if (a != 0) {
                a->refs = a->refs + 1;
            }
            t = arg0->f44;
            if (t != 0) {
                t->refs = t->refs - 1;
                if (((unsigned long long)((long long)t->refs << 0x29) >> 0x29) == 0) {
                    igObject_Destroy(t);
                }
            }
            arg0->f44 = a;
            if (arg0->f73 != 0 && arg0->f8->f32 != 0 && arg0->f48 == 0) {
                b = arg0->f44->v104(&DAT_004dc000[0]);
                if (b != 0) {
                    b->refs = b->refs + 1;
                }
                u = arg0->f48;
                if (u != 0) {
                    u->refs = u->refs - 1;
                    if (((unsigned long long)((long long)u->refs << 0x29) >> 0x29) == 0) {
                        igObject_Destroy(u);
                    }
                }
                arg0->f48 = b;
            }
        }
        if (arg0->f44 != 0) {
            if (arg0->f73 == 0) {
                arg0->v92((int)arg0->f8, arg0->f12, arg0->f44, arg0->f20, arg0->f24);
            }
            goto L24;
        }
        *arg3 = 1;
        return 0;
    }
L24:
    arg0->f56 = arg1;
    arg0->f88 = arg1;
    arg0->f52 = arg2;
    FUN_0015db90(sp70);
    sp70[1] = 0;
    sp70[0] = 0;
    arg0->f40->v108(sp70, 1);
    arg0->f40->v112(sp70, 2);
    temp_s0 = arg0->f8->f44 > 0;
    if (arg0->f72 == 0 && temp_s0 == 0) {
        FUN_0015b880(arg0);
    }
    if (arg0->f76 != 0) {
        if (arg0->f48 != 0) {
            arg0->f48->v136(arg0->f8->f36);
        }
        arg0->f76(fparg0, arg1, arg2, arg0->f36, arg0->f32, arg0->f40, arg0->f48);
    } else if (temp_s0 == 0) {
        FUN_0015bc20(arg0, temp_s0, 1);
    } else {
        FUN_0015bc20(arg0, temp_s0, 0);
    }
    arg0->f72 = 1;
    *arg3 = 0;
    return 1;
}
