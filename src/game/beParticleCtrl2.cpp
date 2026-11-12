#include "dw4/reflected.h"
#include "dw4/igSmartPointer.h"

extern "C" void FUN_001dc8d0(int);
extern "C" void igObject_Destroy(void *);
extern "C" int Gap__Bec__beParticleCtrl2__vfunc_30(void);
extern "C" int Gap__Bec__beParticleCtrl2__vfunc_20(void);
extern "C" int igMatrix44f_SetIdentity(...);
extern "C" void FUN_00191670(void *, void *, float);
extern "C" void *FUN_0034c040(...);
extern "C" int FUN_0034c5d0(...);
extern "C" void Matrix44_TranslateLocal(void *, void *);
extern "C" int Memory_GetAllocatorBySelector(...);
extern "C" int beMessenger_AppendBool(int, unsigned char);
extern "C" int beMessenger_AppendString(...);
extern "C" int beMessenger_GetBool(int, int);
extern "C" int beMessenger_GetInt(int, int);
extern "C" void beMessenger_GetMatrix(void *, int, int);
extern "C" void *beMessenger_GetObject(int, int);
extern "C" int beMessenger_GetString(int, int);
extern "C" int beMessenger_GetStringCount(int);
extern "C" void beMessenger_GetVec3(void *, int, int);
extern "C" int beMessenger_GetVec3Count(int);
extern "C" unsigned int beMessenger_ResolveEnumValue(int, int, void *);
extern "C" int beMessenger_SendNamed(...);
extern "C" int igObject_GetAllocator(...);
extern "C" void Gap__Bec__beParticleCtrl2__vfunc_32(beParticleCtrl2 *arg0);
extern "C" int g_beParticleCtrl2Info_metaObject[4];
extern "C" int g_beParticleCtrl2_metaObject[4];
typedef struct NameHolder { char pad[8]; int *f8; } NameHolder;
typedef struct RamInfoArg { char pad[8]; int f8; NameHolder *fc; char pad2[4]; unsigned char f14; char pad3[31]; igObject *f34; } RamInfoArg;
extern "C" int beMessenger_RegisterReceiver(int, RamInfoArg *, int *, int *, int);
extern "C" int DAT_004e0858[4];
extern "C" int DAT_0050f638[4];
extern "C" void Gap__Bec__beParticleCtrl2__vfunc_29(beParticleCtrl2 *arg0, RamInfoArg *arg1);
extern "C" float DAT_004e1058[4];
extern "C" float DAT_004e105c[4];
extern "C" float DAT_004e1060[4];
extern "C" int DAT_004e1078[4];
extern "C" int DAT_004e1088[4];
extern "C" int DAT_004e1098[4];
extern "C" int DAT_0050f648[4];
extern "C" int DAT_0050f658[4];
extern "C" int DAT_0050f668[4];
extern "C" int DAT_00587110[4];
extern "C" unsigned char GPR_00554c14;
struct Rel { static inline void go(igObject *object) {
    if (object) {
        --object->_refCount;
        if (((unsigned long long)(long long)object->_refCount & 0x7fffffULL) == 0)
            igObject_Destroy(object);
    }
} };
struct V3 { float x; float y; float z; };
/* Owning stack reference to the new particle work record; released on scope exit (reference count
 * in the low 23 bits of _refCount). */

/* matching construct: dummy virtual slots so t() dispatches through retail vtable slot 22 (the beSystem _random source) */
struct Clk {
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
    virtual unsigned int t();
};
/* matching construct: dummy virtual slots so put() dispatches through retail vtable slot 35 (_transform) */
struct Mtx {
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
    virtual void d32();
    virtual void d33();
    virtual void d34();
    virtual void put(void *);
};
extern "C" int Gap__Bec__beParticleCtrl2__vfunc_34(beParticleCtrl2 *arg0, beParticleCtrl2InfoRam *arg1, beMessengerWork *arg2);

void Gap__Bec__beParticleCtrl2__vfunc_32(beParticleCtrl2 *arg0) {
    int n1;
    int i;
    int n2;
    int j;
    beParticleCtrl2InfoRam *it;
    beParticleCtrl2Info *g;
    int o1;
    int o2;
    igObject *r;
    n1 = ((igObjectList *)arg0->_infoList)->_count;
    i = 0;
    if (0 < n1) {
        o1 = 0;
        do {
            g = *(beParticleCtrl2Info **)((char *)((igObjectList *)arg0->_infoList)->_data + o1);
            FUN_001dc8d0(g->_mainSwitch);
            FUN_001dc8d0(g->_subSwitch);
            n2 = ((igObjectList *)g->_ramList)->_count;
            j = 0;
            if (0 < n2) {
                o2 = 0;
                do {
                    it = *(beParticleCtrl2InfoRam **)((char *)((igObjectList *)g->_ramList)->_data + o2);
                    it->_isRun = 0;
                    r = (igObject *)it->_work;
                    if (r != 0) {
                        --r->_refCount;
                        if (((unsigned long long)(long long)r->_refCount & 0x7fffffULL) == 0) {
                            igObject_Destroy((void *)r);
                        }
                    }
                    it->_work = 0;
                    j++;
                    o2 += 4;
                    ((ParticleTimer *)it->_particleTimer)->_timeRunning = 0;
                } while (j < n2);
            }
            i++;
            o1 += 4;
        } while (i < n1);
    }
}

int Gap__Bec__beParticleCtrl2__vfunc_30(void)
{
    return g_beParticleCtrl2Info_metaObject[0];
}

void Gap__Bec__beParticleCtrl2__vfunc_29(beParticleCtrl2 *arg0, RamInfoArg *arg1) {
    int *var_a3;
    int t0;
    igObject *temp_a0;

    t0 = arg1->f8;
    var_a3 = arg1->fc->f8;
    var_a3 = (var_a3 != 0) ? var_a3 : (int *)(&DAT_004e0858[0]);
    beMessenger_RegisterReceiver(arg0->_messenger, arg1, &DAT_0050f638[0], var_a3, t0);
    arg1->f14 = 0;
    temp_a0 = arg1->f34;
    if (temp_a0 != 0) {
        temp_a0->_refCount = (int)temp_a0->_refCount - 1;
        if (((unsigned long long) ((long long) (int)temp_a0->_refCount << 0x29) >> 0x29) == 0) {
            igObject_Destroy((void *)temp_a0);
        }
    }
    arg1->f34 = 0;
}

int Gap__Bec__beParticleCtrl2__vfunc_34(beParticleCtrl2 *arg0, beParticleCtrl2InfoRam *arg1, beMessengerWork *arg2) {
    switch (beMessenger_ResolveEnumValue(arg0->_messenger, FUN_0034c5d0(), (void *)arg2->_message)) {
    case 0:
        if (beMessenger_GetStringCount(arg0->_messenger) != 0) {
            V3 sp100;
            V3 spF0;
            int spB0[16];
            float f22, f21, f20;
            int s3 = beMessenger_GetString(arg0->_messenger, 0);
            int s2 = beMessenger_GetInt(arg0->_messenger, 0);
            beMessenger_GetVec3(&sp100, arg0->_messenger, 0);
            unsigned char s1 = beMessenger_GetBool(arg0->_messenger, 0);
            if (beMessenger_GetVec3Count(arg0->_messenger) == 2) {
                beMessenger_GetVec3(&spF0, arg0->_messenger, 1);
                f21 = spF0.y;
                f22 = spF0.x;
                f20 = spF0.z;
                if (!(f21 <= 6.2831855f)) {
                    f21 = (float)(((Clk *)((beSystem *)arg0->_system)->_random)->t() % 6144U) / 1000.0f;
                }
            } else {
                f22 = DAT_004e1058[0];
                f21 = DAT_004e105c[0];
                f20 = DAT_004e1060[0];
            }
            beMessenger_SendNamed(arg0->_messenger, DAT_0050f638, s3, s2, DAT_0050f648);
            beMessenger_GetMatrix(spB0, arg0->_messenger, 0);
            if (s1) {
                int alloc = igObject_GetAllocator(arg0);
                int a;
                if (GPR_00554c14 != 0) {
                    a = alloc;
                } else {
                    a = Memory_GetAllocatorBySelector(DAT_00587110[0]);
                }
                igSmartPointer<beParticleCtrl2InfoWork> work((beParticleCtrl2InfoWork *)FUN_0034c040(a));
                igObject *o = (igObject *)beMessenger_GetObject(arg0->_messenger, 0);
                beParticleCtrl2InfoWork *r = work.p;
                if (o != 0) {
                    o->_refCount = o->_refCount + 1;
                }
                Rel::go((igObject *)r->_positionLockNode);
                r->_positionLockNode = (int)o;
                beParticleCtrl2InfoWork *d = work.p;
                V3 *dv = (V3 *)&d->_positionLockOffset;
                dv->x = sp100.x;
                dv->y = sp100.y;
                dv->z = sp100.z;
                r = work.p;
                if (r != 0) {
                    r->_refCount = r->_refCount + 1;
                }
                Rel::go((igObject *)arg1->_work);
                arg1->_work = (int)r;
            }
            Matrix44_TranslateLocal(spB0, &sp100);
            if (f22 != 0.0f) {
                FUN_00191670(spB0, DAT_004e1078, f22);
            }
            if (f21 != 0.0f) {
                FUN_00191670(spB0, DAT_004e1088, f21);
            }
            if (f20 != 0.0f) {
                FUN_00191670(spB0, DAT_004e1098, f20);
            }
            ((Mtx *)arg1->_transform)->put(spB0);
        } else {
            int sp70[16];
            igMatrix44f_SetIdentity(sp70);
            ((Mtx *)arg1->_transform)->put(sp70);
        }
        arg1->_isRun = 1;
        arg1->_st0 = 0;
        arg1->_st3 = 0;
        arg1->_st2 = 0;
        arg1->_st1 = 0;
        break;
    case 2:
        arg1->_st0 = 2;
        arg1->_st3 = 0;
        arg1->_st2 = 0;
        arg1->_st1 = 0;
        break;
    case 1:
        beMessenger_AppendBool(arg0->_messenger, arg1->_isRun);
        break;
    case 6:
        if (arg1->_isRun != 0) {
            ((ParticleTimer *)arg1->_particleTimer)->_timeRunning = 0;
        }
        break;
    case 7:
        if (arg1->_isRun != 0) {
            ((ParticleTimer *)arg1->_particleTimer)->_timeRunning = 1;
        }
        break;
    case 3:
        beMessenger_AppendString(arg0->_messenger, DAT_0050f658);
        beMessenger_AppendString(arg0->_messenger, DAT_0050f658);
        beMessenger_AppendString(arg0->_messenger, DAT_0050f668);
        break;
    }
    return 1;
}

int Gap__Bec__beParticleCtrl2__vfunc_20(void)
{
    return g_beParticleCtrl2_metaObject[0];
}
