#include "dw4/reflected.h"
#include "dw4/typecast.h"

extern "C" int FUN_00337630(int, int, int, int, int, int, int, int);
extern "C" void FUN_00337410(unsigned long long *arg0, unsigned arg1, unsigned arg2, unsigned arg3, unsigned arg4, unsigned arg5, unsigned arg6);
extern "C" void FUN_00337480(void *arg0, unsigned long long arg1, int arg2, int arg3, int arg4, int arg5, int arg6, int arg7);
extern "C" static void FUN_003374e0(int *arg0, int arg1, unsigned long long arg2);
extern "C" void FUN_00337520(int *arg0, unsigned int dbp, unsigned int dbw, unsigned int dpsm);
extern "C" void FUN_00337570(int *arg0, unsigned int dir, unsigned int dsax, unsigned int dsay);
extern "C" void FUN_003375c0(int *arg0, unsigned int rrw, unsigned int rrh);
extern "C" void FUN_00337600(int arg0, unsigned int arg1);
extern "C" int FUN_003378e0(int a0, int a1, int a2, int a3, int a4, int a5, int a6);
typedef struct { char pad[32]; unsigned int f20; unsigned int f24; } A;
typedef struct { char pad[4]; int f4; } R;
extern "C" int FUN_002ed2b0(unsigned int, int, int);
extern "C" int igObject_IsKindOf(...);
extern "C" int Memory_GetAllocatorBySelector(int);
extern "C" int igObject_Destroy(...);
extern "C" int igObject_GetAllocator(...);
extern "C" int g_igPsx2VisualContext_metaObject[4];
extern "C" int g_ndmwAllocatorSelector[4];
extern "C" int DAT_005878c0[4];
extern "C" void * DAT_005878d8[4];
extern "C" unsigned char GPR_00554c14;
extern "C" int Gap__igCriMovieCodec__vfunc_28(int arg0, A *arg1, void **arg2);
extern "C" int Memory_FreeBufferWithAllocator(int, int);
extern "C" int Gap__igCriMovieCodec__vfunc_29(void *arg0);
extern "C" int FUN_0016cdd0(...);
extern "C" int FUN_0016cde0(...);
extern "C" int FUN_00308320(const char *, ...);
extern "C" char DAT_00500d70[];
extern "C" int DAT_005878b8[4];
extern "C" unsigned char GPR_00554e00;
struct S { char p[32]; int f32; int f36; };
extern "C" int FUN_00337aa0(struct S *arg0, int arg1);
extern "C" int g_igCriMovieData_metaObject[4];
extern "C" int Gap__Core__igObject__vfunc_11(...);
extern "C" void Gap__igCriMovieData__vfunc_11(igCriMovieData *self);
extern "C" int Gap__igCriMovieData__vfunc_20(void);
extern "C" void Gap__Core__igObject__vfunc_02(void);
extern "C" void Gap__igCriMovieCodec__vfunc_02(void);
extern "C" int g_igCriMovieCodec_metaObject[4];
extern "C" int FUN_002934c0(...);
extern "C" int Gap__Core__igObject__vfunc_01(...);
extern "C" void Gap__igCriMovieCodec__vfunc_01(igCriMovieCodec *self);
extern "C" int Gap__igCriMovieCodec__vfunc_21(void);
extern "C" int Gap__igCriMovieCodec__vfunc_20(void);
/* Deleting destructor; the deletion flag is a signed short. */
typedef struct ObjectRefTarget { int word0; int references; } ObjectRefTarget;
typedef struct ObjectRefWord { ObjectRefTarget *value; } ObjectRefWord;
extern "C" void FUN_00100610(void *);
extern "C" ObjectRefWord *FUN_003387d0(ObjectRefWord *self,int delete_storage);
extern "C" int FUN_0026b728(int);
extern "C" int FUN_0026bc60(int);
extern "C" int g_igCriMovieData_metaObject[4];
typedef struct S_338850 { char pad8[8]; int *f8; int f12; int f16; int f20; } S_338850;
extern "C" int Gap__igCriMovieCodec__vfunc_24(int arg0, void *arg1);
typedef struct V { int *vt; } V;
typedef struct D { char pad8[8]; V *f8; char pad[4]; int f16; } D;
typedef struct A_338920 { char pad[24]; int f24; char pad2[48]; int f76; char pad3[16]; D *f96; } A_338920;
extern "C" int FUN_0026ce40(int, int);
extern "C" int FUN_0026cf70(int);
extern "C" int FUN_00295468(...);
extern "C" int Gap__igCriMovieCodec__vfunc_25(int arg0, A_338920 *arg1);
extern "C" int Gap__igCriMovieCodec__vfunc_26(void *arg0, igMovieInfo *arg1, int arg2);
struct D_338ae0 { char pad[8]; int f8; int pad2; int f16; 
    static inline D_338ae0 *Cast(D_338ae0 *p) {
        if (p != 0 && igObject_IsKindOf(p, g_igCriMovieData_metaObject[0]) != 0) { return p; }
        return 0;
    }
};
struct A_338ae0 { char pad[24]; int f24; char pad2[48]; int f76; char pad3[16]; D_338ae0 *f96; };
class C { public:
 virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24();
 virtual int v108(A_338ae0 *);
 virtual int v112(A_338ae0 *, int);
};
extern "C" int Gap__igCriMovieCodec__vfunc_30(C *arg0, A_338ae0 *arg1);
class DW4VC_216_1 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual int vX(int); };
extern "C" void FUN_00338d60(int dummy0, int arg1);
class DW4VC_220_2 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual int vX(int, int); };
extern "C" void FUN_00338da0(int dummy0, int arg1, int arg2);
class DW4VC_264_1 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual void d53(); virtual void d54(); virtual void d55(); virtual void d56(); virtual void d57(); virtual void d58(); virtual void d59(); virtual void d60(); virtual void d61(); virtual void d62(); virtual void d63(); virtual int vX(int); };
extern "C" void FUN_00338df0(int dummy0, int arg1);

void FUN_00337410(unsigned long long *arg0, unsigned arg1, unsigned arg2, unsigned arg3, unsigned arg4, unsigned arg5, unsigned arg6) {
    *arg0 = (unsigned long long)arg6 | (((unsigned long long)arg5 << 26) | (((unsigned long long)arg4 << 28) | (((unsigned long long)arg3 << 31) | (((unsigned long long)arg1 << 63) | ((unsigned long long)(arg2 & ~0xFU) << 32)))));
}

void FUN_00337480(void *arg0, unsigned long long arg1, int arg2, int arg3, int arg4, int arg5, int arg6, int arg7) {
    unsigned long long m;
    int *p = (int *)arg0;
    p[0] = (arg6 << 0xF) | arg7;
    p[1] = (arg2 << 0x1C) | ((arg3 << 0x1A) | ((arg5 << 0xE) | (arg4 << 0xF)));
    m = 0xFFFF;
    m = (m << 16) | 0xFFFF;
    p[2] = (int)(arg1 & m);
    p[3] = (int)(arg1 >> 32);
}

static void FUN_003374e0(int *arg0, int arg1, unsigned long long arg2) {
    arg0[0] = (int)(arg2 & 0xFFFFFFFF); arg0[1] = (int)(arg2 >> 32);
    arg0[2] = arg1;
    arg0[3] = 0;
}

void FUN_00337520(int *arg0, unsigned int dbp, unsigned int dbw, unsigned int dpsm) {
    FUN_003374e0(arg0, 0x50, (unsigned long long)dbp << 32 | ((unsigned long long)dpsm << 56 | (unsigned long long)dbw << 48));
}

void FUN_00337570(int *arg0, unsigned int dir, unsigned int dsax, unsigned int dsay) {
    FUN_003374e0(arg0, 0x51, (unsigned long long)dsax << 32 | ((unsigned long long)dir << 59 | (unsigned long long)dsay << 48));
}

void FUN_003375c0(int *arg0, unsigned int rrw, unsigned int rrh) {
    FUN_003374e0(arg0, 0x52, (unsigned long long)rrh << 32 | rrw);
}

void FUN_00337600(int arg0, unsigned int arg1) {
    FUN_003374e0((int *)arg0, 0x53, arg1);
}

int FUN_003378e0(int a0, int a1, int a2, int a3, int a4, int a5, int a6) {
    return FUN_00337630(a0, a1, 0x400, a2, a3, a4, a5, a6);
}

int Gap__igCriMovieCodec__vfunc_28(int arg0, A *arg1, void **arg2) {
    int var_v0;
    int w;
    unsigned int temp_s2;
    unsigned int temp_s1;
    R *a;
    R *var_s0;
    R *d;

    temp_s2 = arg1->f20 >> 4;
    temp_s1 = arg1->f24 >> 4;
    var_v0 = igObject_GetAllocator();
    if (GPR_00554c14 != 0) {
        w = var_v0;
    } else {
        w = Memory_GetAllocatorBySelector(g_ndmwAllocatorSelector[0]);
    }
    DAT_005878c0[0] = FUN_002ed2b0(((unsigned int) ((((temp_s2 * temp_s1 * 6) + 0xA) * 4) + 0x3F) >> 6) << 8, 0x40, w);
    a = (R *)(*arg2);
    if ((a != 0) && (igObject_IsKindOf(a, g_igPsx2VisualContext_metaObject[0]) != 0)) {
        var_s0 = a;
    } else {
        var_s0 = 0;
    }
    if (var_s0 != 0) {
        var_s0->f4 = var_s0->f4 + 1;
    }
    d = (R *)DAT_005878d8[0];
    if (d != 0) {
        d->f4 = d->f4 - 1;
        if (((unsigned long long) ((long long) d->f4 << 0x29) >> 0x29) == 0) {
            igObject_Destroy(d);
        }
    }
    DAT_005878d8[0] = (void *)(var_s0);
    return 1;
}

int Gap__igCriMovieCodec__vfunc_29(void *arg0) {
    int a;

    a = igObject_GetAllocator(arg0);
    a = GPR_00554c14 ? a : Memory_GetAllocatorBySelector(g_ndmwAllocatorSelector[0]);
    Memory_FreeBufferWithAllocator(DAT_005878c0[0], a);
    return 1;
}

int FUN_00337aa0(struct S *arg0, int arg1) {
    int s2;
    int s1;
    int s0;
    int v0;
    s2 = FUN_0016cde0(DAT_005878d8[0]);
    s1 = arg0->f32;
    s0 = arg0->f36;
    if (DAT_005878c0[0] == 0 && GPR_00554e00 == 0) {
        v0 = FUN_00308320(DAT_00500d70);
        if (v0 != 1 && v0 == 2) {
            GPR_00554e00 = 1;
        }
    }
    DAT_005878b8[0] = FUN_003378e0(DAT_005878c0[0], arg1, 0, (s2 != 0) ? 448 : 0, s1, s0, 1);
    FUN_0016cdd0(DAT_005878d8[0], DAT_005878c0[0], DAT_005878b8[0], 1);
    return 1;
}

/* Reset step: runs the igObject base step, then clears the three middleware handles the object
 * holds (_mwply, _adxt, _macroFunction; +8/+16/+24). */
void Gap__igCriMovieData__vfunc_11(igCriMovieData *self) {
    Gap__Core__igObject__vfunc_11();
    self->_mwply = 0;
    self->_adxt = 0;
    self->_macroFunction = 0;
}

/* Runs the igObject base step, then hands FUN_002934c0 a pair of callbacks with the codec as their
 * context. FUN_002934c0 stores the two function pointers and the context in a record from
 * FUN_00294a30 (record+0x28, +0x2c, +0x30). The first callback forwards its second argument to
 * vtable slot 54 of the object returned by 0x00301000. */
void Gap__igCriMovieCodec__vfunc_01(igCriMovieCodec *self) {
    Gap__Core__igObject__vfunc_01();
    FUN_002934c0(&FUN_00338d60, &FUN_00338df0, self);
}

void Gap__igCriMovieCodec__vfunc_02(void)
{
    Gap__Core__igObject__vfunc_02();
}

/* Returns 1 where the igMovieCodec base version returns 0. */
int Gap__igCriMovieCodec__vfunc_21(void)
{
    return 1;
}

ObjectRefWord *FUN_003387d0(ObjectRefWord *self,int delete_storage) {
    if(self) {
        ObjectRefTarget *object=self->value;
        if(object) {
            --object->references;
            if(((unsigned long long)(long long)object->references & 0x7fffffULL)==0)
                igObject_Destroy(object);
        }
        if((short)delete_storage>0) FUN_00100610(self);
    }
    return self;
}

int Gap__igCriMovieCodec__vfunc_24(int arg0, void *arg1) {
    S_338850 *var_s0;
    int temp_a0;

    var_s0 = (S_338850 *)dw4_cast_or_null((char *)*(int *)((char *)(arg1) + 96), g_igCriMovieData_metaObject);
    if (var_s0 != 0) {
        temp_a0 = var_s0->f16;
        if (temp_a0 != 0) {
            FUN_0026bc60(temp_a0);
            FUN_0026b728(var_s0->f16);
            FUN_00338df0(arg0, var_s0->f20);
            var_s0->f16 = 0;
            var_s0->f20 = 0;
        }
        ((int (*)(int *))*(int *)((char *)(*(int *)var_s0->f8) + 20))(var_s0->f8);
        FUN_00338df0(arg0, var_s0->f12);
        var_s0->f8 = 0;
        var_s0->f12 = 0;
        return 1;
    }
    return 0;
}

static inline D * cast0(D * o) { if (o != 0 && igObject_IsKindOf(o, g_igCriMovieData_metaObject[0]) != 0) { return o; } return 0; }

int Gap__igCriMovieCodec__vfunc_25(int arg0, A_338920 *arg1) {
    V *temp_a0;
    D *var_s0;

    var_s0 = arg1->f96;
    var_s0 = cast0(var_s0);
    if (var_s0 != 0) {
        arg1->f76 = 0;
        if (arg1->f24 == 2) {
            if (FUN_0026cf70(var_s0->f16) != 0) {
                FUN_0026ce40(var_s0->f16, 0);
            }
        } else if (FUN_00295468(var_s0->f8) == 1) {
            temp_a0 = var_s0->f8;
            ((int (*)(V *, int))temp_a0->vt[10])(temp_a0, 0);
        }
        return 1;
    }
    return 0;
}

int Gap__igCriMovieCodec__vfunc_26(void *arg0, igMovieInfo *arg1, int arg2) {
    void *obj;
    igCriMovieData *r;
    obj = (void *)arg1->_userdata;
    if (obj != 0 && igObject_IsKindOf(obj, g_igCriMovieData_metaObject[0]) != 0) {
        r = (igCriMovieData *)obj;
    } else {
        r = 0;
    }
    if (r != 0) {
        int *p;
        arg1->_state = arg2;
        if (arg1->_type == 2) {
            if (FUN_0026cf70(r->_adxt) == 0) {
                FUN_0026ce40(r->_adxt, 1);
            }
        } else if (FUN_00295468(r->_mwply) == 0) {
            p = (int *)r->_mwply;
            ((int (*)(int *, int))*(int *)(*p + 40))(p, 1);
        }
        return 1;
    }
    return 0;
}

int Gap__igCriMovieCodec__vfunc_30(C *arg0, A_338ae0 *arg1) {
    D_338ae0 *s2 = D_338ae0::Cast(arg1->f96);
    if (s2 != 0) {
        bool b;
        if (arg1->f24 == 2) {
            b = FUN_0026cf70(s2->f16) == 1;
        } else {
            b = FUN_00295468(s2->f8) == 1;
        }
        if (arg1->f76 == 1 && !b) {
            return arg0->v112(arg1, 1);
        }
        if (arg1->f76 == 0 && b) {
            return arg0->v108(arg1);
        }
    }
    return 0;
}

void FUN_00338d60(int dummy0, int arg1) {
    void **temp_v0;

    temp_v0 = (void **)(igObject_GetAllocator());
    ((DW4VC_216_1 *)(temp_v0))->vX((int)(arg1));
}

void FUN_00338da0(int dummy0, int arg1, int arg2) {
    void **temp_v0;

    temp_v0 = (void **)(igObject_GetAllocator());
    ((DW4VC_220_2 *)(temp_v0))->vX((int)(arg1), (int)(arg2 & 0xFF));
}

void FUN_00338df0(int dummy0, int arg1) {
    void **temp_v0;

    temp_v0 = (void **)(igObject_GetAllocator());
    ((DW4VC_264_1 *)(temp_v0))->vX((int)(arg1));
}

int Gap__igCriMovieCodec__vfunc_20(void)
{
    return g_igCriMovieCodec_metaObject[0];
}

int Gap__igCriMovieData__vfunc_20(void)
{
    return g_igCriMovieData_metaObject[0];
}

