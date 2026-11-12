#include "dw4/reflected.h"

extern "C" void Gap__Core__igObject__vfunc_01(void);
extern "C" void FUN_00261c88(...);
extern "C" void Gap__igAdxFile__vfunc_01(void);
extern "C" void Gap__igAdxFile__vfunc_24(char * p0);
extern "C" int FUN_00262510(...);
extern "C" int Gap__igAdxFile__vfunc_20(void);
extern "C" int Gap__igAdxFile__vfunc_27(void);
extern "C" int Gap__igAdxFile__vfunc_30(void);
extern "C" int Gap__igAdxFile__vfunc_31(void);
extern "C" int Gap__igAdxFile__vfunc_33(void);
extern "C" int Gap__igAdxFile__vfunc_34(void);
extern "C" int Gap__igAdxFile__vfunc_35(void);
extern "C" int Gap__igAdxFile__vfunc_32(void);
extern "C" int Gap__Core__igObject__vfunc_11(...);
extern "C" int Memory_FreeBufferWithAllocator(int, int);
extern "C" void * igObject_GetAllocator(...);
extern "C" int Gap__Core__igObject__vfunc_08__002ff0f0(...);
extern "C" int igMetaObject_CountInstances(...);
extern "C" void Gap__igAdxFile__vfunc_08(void **arg0);
extern "C" int FUN_00262678(int);
extern "C" void FUN_00332cd0(void);
extern "C" void FUN_00332cf0(int);
extern "C" void FUN_00333a40(int a0, int a1);
extern "C" void FUN_00333a50(int a0, int a1);
extern "C" int strcpy(char *, int);
extern "C" int FUN_002618c0(char *, int);
extern "C" int FUN_00261b78(int, int);
extern "C" int FUN_003082b0(...);
extern "C" int FUN_00333440(int);
extern "C" int FUN_002e30b0(...);
extern "C" int strcmp(...);
extern "C" int memcpy(char *, char *, int);
extern "C" int FUN_002620d8(void *, int, char *);
extern "C" int FUN_00262540(...);
extern "C" char *FUN_002ed2b0(int, int, void *);
extern "C" int FUN_00304430(const char *, ...);
extern "C" int FUN_00304680(...);
extern "C" int Gap__igAdxFile__vfunc_28(int a, int b, ...);
extern "C" int Gap__igAdxFile__vfunc_29(void *arg0, void *arg1, ...);
extern "C" int FUN_002623f8(int, int, int);
extern "C" int FUN_00334370(void *arg0);
extern "C" int g_igAdxFile_metaObject[4];
extern "C" int Gap__igAdxFile__vfunc_37(igAdxFile *self);
extern "C" void Gap__igAdxFile__vfunc_11(igAdxFile *arg0);
typedef struct S0 { char pad48[48]; int f30; int f34; int f38; } S0;
extern "C" void Gap__igAdxFile__vfunc_02(S0 *arg0);
class DW4VC_88_0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual int vX(); };
extern "C" int FUN_00333970(igAdxFile *file);
struct igResult { int value; };
class SleepingThread {
public:
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4();
    virtual void s5(); virtual void s6(); virtual void s7(); virtual void s8(); virtual void s9();
    virtual void s10(); virtual void s11(); virtual void s12(); virtual void s13(); virtual void s14();
    virtual void s15(); virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
    virtual void s20(); virtual void s21(); virtual void s22();
    virtual igResult sleep(unsigned long long time);
};
struct ThreadList { int _vtable; unsigned int _refCount; int _count; int _capacity; SleepingThread **_data; };
struct ThreadManager { int _vtable; unsigned int _refCount; ThreadList *_threads; };
extern "C" ThreadManager *DAT_005871d0;
extern "C" int FUN_00333990(igAdxFile *file);
typedef struct F { char p0[12]; int f12; char p1[4]; int f20; char p2[20]; unsigned char b44; char p3[51]; int f96; } F;
typedef struct Ent { char p[16]; short s16; short s18; } Ent;
typedef struct Tab { char p[16]; Ent **data; } Tab;
extern "C" int DAT_004fb410[4];
extern "C" int DAT_004fb418[4];
extern "C" int DAT_004fffa0[4];
extern "C" int DAT_004fffe0[4];
extern "C" int DAT_00500020[4];
extern "C" Tab *DAT_00587620[4];
extern "C" unsigned char GPR_00554de8;
extern "C" unsigned char GPR_00554df0;
extern "C" unsigned char GPR_00554df4;
extern "C" unsigned char GPR_00554df8;
extern "C" void Gap__igAdxFile__vfunc_21(int *out, F *f, unsigned int mode);
extern "C" void Gap__igAdxFile__vfunc_22(igAdxFile *arg0);
extern "C" int DAT_00500060[4];
extern "C" int DAT_00500068[4];
struct R { int code; inline int Ok() { return code == DAT_004fb410[0]; } };
class MF { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20();  virtual R vX(int); };
extern "C" MF *Gap__igAdxFile__vfunc_23(MF *arg0, int arg1, int arg2);
typedef struct F_333d90 {
    char p0[48];
    char *f48;
    char *f52;
    char *f56;
    unsigned char f60;
    unsigned char f61;
    unsigned char f62;
    unsigned char f63;
    int f64;
    int f68;
    char p72[8];
    int f80;
    char p84[12];
    void *f96;
} F_333d90;
extern "C" char DAT_00500070[];
extern "C" int Gap__igAdxFile__vfunc_25(F_333d90 *arg0, char *arg1, int arg2, int arg3);
typedef struct O { char pad[63]; char f3f; char pad2[8]; int f48; char pad3[4]; int f50; char pad4[12]; int f60; } O;
extern "C" int Gap__igAdxFile__vfunc_36(O *arg0, int arg1, int arg2);

void Gap__igAdxFile__vfunc_01(void)
{
    Gap__Core__igObject__vfunc_01();
}

void Gap__igAdxFile__vfunc_11(igAdxFile *arg0) {
    Gap__Core__igObject__vfunc_11();
    arg0->_pBufferPtr = (int)((int) arg0->_pBuffer);
    arg0->_bBufferFilled = 0;
    arg0->_iBufferPos = 0;
    *(int *)((char *)(arg0) + 96) = 0;
}

/* Slot 20, class meta-object handle getter */
int Gap__igAdxFile__vfunc_20(void)
{
    return g_igAdxFile_metaObject[0];
}

void Gap__igAdxFile__vfunc_02(S0 *arg0) {
    if (arg0->f30 != 0) {
        Memory_FreeBufferWithAllocator(arg0->f30, ((int)igObject_GetAllocator(arg0)));
        arg0->f34 = 0;
    }
    if (arg0->f38 != 0) {
        Memory_FreeBufferWithAllocator(arg0->f38, ((int)igObject_GetAllocator(arg0)));
    }
}

void Gap__igAdxFile__vfunc_08(void **arg0) {
    igMetaObject_CountInstances(((DW4VC_88_0 *)(arg0))->vX(), 1);
    Gap__Core__igObject__vfunc_08__002ff0f0(arg0);
}

int FUN_00333970(igAdxFile *file)
{
    return FUN_00262678(*(int *)((char *)file + 96));
}

int FUN_00333990(igAdxFile *file) {
    while (FUN_00333970(file) != 3) {
        if (file->_bUseAsync && file->_bUseAlchemyAsync) {
            DAT_005871d0->_threads->_data[0]->sleep(file->_lSleepTime);
        } else {
            FUN_00332cd0();
        }
        FUN_00332cf0(0);
    }
    return 3;
}

void FUN_00333a40(int a0, int a1)
{
    *(char *)((char *)a0 + 62) = a1;
}

void FUN_00333a50(int a0, int a1)
{
    *(char *)((char *)a0 + 60) = a1;
}

void Gap__igAdxFile__vfunc_21(int *out, F *f, unsigned int mode) {
    char sp30[256];
    int r, idx;
    Ent *e;
    if (GPR_00554de8 == 0) {
        *out = DAT_004fb418[0];
        return;
    }
    if (f->b44 != 0) {
        *out = DAT_004fb410[0];
        return;
    }
    if (mode == 8) {
        mode = f->f20;
    }
    switch (mode) {
    case 0:
        if (GPR_00554df0 == 0) {
            r = FUN_003082b0(DAT_004fffa0, f->f12);
            if (r != 1 && r == 2) GPR_00554df0 = 1;
        }
        goto L4;
    case 1:
    case 2:
    case 3:
    case 5:
    case 6:
        if (GPR_00554df4 == 0) {
            r = FUN_003082b0(DAT_004fffe0, f->f12);
            if (r != 1 && r == 2) GPR_00554df4 = 1;
        }
        *out = DAT_004fb418[0];
        return;
    default:
        if (GPR_00554df8 == 0) {
            r = FUN_003082b0(DAT_00500020);
            if (r != 1 && r == 2) GPR_00554df8 = 1;
        }
        *out = DAT_004fb418[0];
        return;
    case 4:
L4:
        idx = FUN_00333440(f->f12);
        if (idx != -1) {
            e = DAT_00587620[0]->data[idx];
            f->f96 = FUN_00261b78(e->s16, e->s18);
        } else {
            strcpy(sp30, f->f12);
            f->f96 = FUN_002618c0(sp30, 0);
        }
        if (f->f96 == 0) {
            *out = DAT_004fb418[0];
            return;
        }
        f->b44 = 1;
        *out = DAT_004fb410[0];
        return;
    }
}

void Gap__igAdxFile__vfunc_22(igAdxFile *arg0) {
    int temp_a0;

    arg0->_bBufferFilled = 0;
    arg0->_iBufferPos = 0;
    temp_a0 = *(int *)((char *)(arg0) + 96);
    if (temp_a0 != 0) {
        FUN_00261c88(temp_a0);
    }
}

MF *Gap__igAdxFile__vfunc_23(MF *arg0, int arg1, int arg2) {
    int ok;
    FUN_002e30b0(arg0);
    if (strcmp(arg2, &DAT_00500060[0]) == 0) {
        ok = arg0->vX(4).Ok();
    } else if (strcmp(arg2, &DAT_00500068[0]) == 0) {
        ok = arg0->vX(0).Ok();
    } else {
        return 0;
    }
    return ok ? arg0 : 0;
}

void Gap__igAdxFile__vfunc_24(char * p0)
{
    FUN_00261c88(*(int *)((char *)p0 + 96));
}

int Gap__igAdxFile__vfunc_25(F_333d90 *arg0, char *arg1, int arg2, int arg3) {
    int total;
    int n;
    int rem;
    int done;
    int a;
    int t;
    total = arg2 * arg3;
    if (arg0->f62 == 0) {
        n = total / arg0->f80;
        if (total % arg0->f80 != 0) {
            n += 1;
        }
        t = FUN_00262510(arg0->f96);
        if (t < FUN_00262540(arg0->f96)) {
            t = n + FUN_00262510(arg0->f96);
            if (FUN_00262540(arg0->f96) < t) {
                n = FUN_00262540(arg0->f96) - FUN_00262510(arg0->f96);
            }
            FUN_002620d8(arg0->f96, n, arg1);
        }
        if (arg0->f60 == 0 || arg0->f61 != 0) {
            FUN_00333990((igAdxFile *)arg0);
        }
        return arg3;
    }
    if (arg0->f63 == 0) {
        n = arg0->f64 / arg0->f80;
        t = FUN_00262510(arg0->f96);
        if (t < FUN_00262540(arg0->f96)) {
            t = n + FUN_00262510(arg0->f96);
            if (FUN_00262540(arg0->f96) < t) {
                n = FUN_00262540(arg0->f96) - FUN_00262510(arg0->f96);
            }
            FUN_002620d8(arg0->f96, n, arg0->f48);
        }
        if (arg0->f60 == 0 || arg0->f61 != 0) {
            FUN_00333990((igAdxFile *)arg0);
        }
        arg0->f68 = 0;
        arg0->f63 = 1;
    }
    rem = arg0->f64 - arg0->f68;
    if (total < rem) {
        arg0->f52 = arg0->f48 + arg0->f68;
        memcpy(arg1, arg0->f52, total);
        arg0->f68 = arg0->f68 + total;
        if (arg0->f68 > arg0->f64 - 1) {
            arg0->f63 = 0;
        }
        return arg3;
    }
    if (arg0->f56 == 0) {
        arg0->f56 = FUN_002ed2b0(arg0->f64, 0x40, igObject_GetAllocator(arg0));
        if (arg0->f56 == 0) {
            return 0;
        }
    }
    done = 0;
    if (0 < total) {
        do {
            n = arg0->f64 / arg0->f80;
            t = FUN_00262510(arg0->f96);
            if (t < FUN_00262540(arg0->f96)) {
                t = n + FUN_00262510(arg0->f96);
                if (FUN_00262540(arg0->f96) < t) {
                    n = FUN_00262540(arg0->f96) - FUN_00262510(arg0->f96);
                }
                FUN_002620d8(arg0->f96, n, arg0->f56);
            } else {
                FUN_00304430(&DAT_00500070[0]);
                FUN_00304680();
            }
            if (arg0->f60 == 0 || arg0->f61 != 0) {
                FUN_00333990((igAdxFile *)arg0);
            }
            if (arg0->f68 < arg0->f64 - 1) {
                arg0->f52 = arg0->f48 + arg0->f68;
                memcpy(arg1, arg0->f52, rem);
                done += rem;
                rem = total - done;
            }
            arg0->f68 = 0;
            a = arg0->f64;
            if (a < rem) {
                rem = a;
            }
            arg0->f52 = arg0->f56;
            arg0->f56 = arg0->f48;
            arg0->f48 = arg0->f52;
            memcpy(arg1 + done, arg0->f52, rem);
            done += rem;
            arg0->f68 = arg0->f68 + rem;
        } while (done < total);
    }
    return arg3;
}

/* Stub, returns -1 */
int Gap__igAdxFile__vfunc_27(void)
{
    return -1;
}

int Gap__igAdxFile__vfunc_28(int a, int b, ...) {
    return -1;
}

int Gap__igAdxFile__vfunc_29(void *arg0, void *arg1, ...) {
    return -1;
}

/* Stub, returns -1 */
int Gap__igAdxFile__vfunc_30(void)
{
    return -1;
}

/* Stub, returns -1 */
int Gap__igAdxFile__vfunc_31(void)
{
    return -1;
}

/* Stub, returns -1 */
int Gap__igAdxFile__vfunc_33(void)
{
    return -1;
}

/* Stub, returns 0 */
int Gap__igAdxFile__vfunc_34(void) {
    return 0;
}

/* Stub, returns -1 */
int Gap__igAdxFile__vfunc_35(void)
{
    return -1;
}

int Gap__igAdxFile__vfunc_36(O *arg0, int arg1, int arg2) {
    int n;
    int r;

    n = arg1 / arg0->f50;
    arg0->f3f = 0;
    switch (arg2) {
    case 0:
        arg0->f48 = arg1;
        FUN_002623f8(arg0->f60, n, 0);
        break;
    case 1:
        arg0->f48 = arg0->f48 + arg1;
        FUN_002623f8(arg0->f60, n, 1);
        break;
    case 2:
        r = FUN_002623f8(arg0->f60, n, 2);
        arg0->f48 = r * arg0->f50;
        break;
    }
    return -1;
}

/* Slot 37, returns the seek position. The result of the handle query on the field at +96 is
 * discarded. */
int Gap__igAdxFile__vfunc_37(igAdxFile *self) {
    FUN_00262510(*(int *)((char *)self + 96));
    return self->_iSeekPosition;
}

/* Stub, returns -1 */
int Gap__igAdxFile__vfunc_32(void)
{
    return -1;
}

int FUN_00334370(void *arg0) {
    if (*(unsigned char *)((char *)(arg0) + 44) != 0) {
        return (FUN_00262540(*(int *)((char *)(arg0) + 96)) << 0xB) + 0x800;
    }
    return 0;
}
