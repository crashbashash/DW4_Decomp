#include "dw4/reflected.h"

extern "C" int Gap__Core__igObject__vfunc_24(...);
extern "C" int FUN_00236f80(int, int);
extern "C" int Gap__Bec__beStaticInfoCtl__vfunc_30(void);
extern "C" void Gap__Bec__beStaticInfoCtl__vfunc_31(void);
extern "C" int Gap__Bec__beStaticInfoCtl__vfunc_20(void);
extern "C" int ObjectList_AppendRetained(...);
extern "C" int beMessenger_RegisterReceiver(...);
extern "C" int FUN_00343700(...);
extern "C" int beMessenger_AppendObject(int, int);
extern "C" int beMessenger_ResolveEnumValue(int, int, int);
extern "C" void igObject_Destroy(igObject *);
/* matching construct: the inlined refcount release is a static member so the compiler expands it as retail does */
struct ReleaseRefInline { static inline void go(igObject *object) {
    if (object) {
        --object->_refCount;
        if (((unsigned long long)(long long)object->_refCount & 0x7fffffULL) == 0)
            igObject_Destroy(object);
    }
} };
extern "C" void Gap__Bec__beStaticInfoCtl__vfunc_24(beStaticInfoCtl *arg0);
extern "C" int DAT_00588f38[4];
extern "C" void Gap__Bec__beStaticInfoCtl__vfunc_32(beStaticInfoCtl *arg0);
extern "C" int g_beStaticInfoCtl_metaObject[4];
extern "C" int g_beStaticInfo_metaObject[4];
extern "C" int DAT_004e0858[4];
extern "C" int DAT_0050ff68[4];
struct A;
class VC { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void v136(); };
/* matching construct: dummy-virtual base so arg0->v136() dispatches through the vtable entry at byte offset 136 */
struct A : VC {};
extern "C" void Gap__Bec__beStaticInfoCtl__vfunc_29(A *arg0, beBaseInfoRam *arg1);
extern "C" int Gap__Bec__beStaticInfoCtl__vfunc_34(beStaticInfoCtl *arg0, beBaseInfoRam *arg1, beMessengerWork *arg2);

void Gap__Bec__beStaticInfoCtl__vfunc_24(beStaticInfoCtl *arg0) {
    igDataList *l = (igDataList *)arg0->_staticInfoList;
    int n = l->_count;
    int i = 0;
    if (0 < n) {
        do {
            ReleaseRefInline::go(((igObject **)l->_data)[i]);
            i++;
        } while (i < n);
    }
    int n2 = l->_count;
    int v = 0;
    if (0 < n2) {
        int lim;
        if (n2 > 8) {
            lim = n2 - 8;
            do {
                ((int *)l->_data)[v] = 0;
                ((int *)l->_data)[v + 1] = 0;
                ((int *)l->_data)[v + 2] = 0;
                ((int *)l->_data)[v + 3] = 0;
                ((int *)l->_data)[v + 4] = 0;
                ((int *)l->_data)[v + 5] = 0;
                ((int *)l->_data)[v + 6] = 0;
                ((int *)l->_data)[v + 7] = 0;
                v += 8;
            } while (v < lim);
        }
        if (v < n2) {
            do {
                ((int *)l->_data)[v] = 0;
                v++;
            } while (v < n2);
        }
    }
    l->_count = 0;
    Gap__Core__igObject__vfunc_24(arg0);
}

void Gap__Bec__beStaticInfoCtl__vfunc_32(beStaticInfoCtl *arg0) {
    if (arg0->_messenger == 0) {
        arg0->_messenger = FUN_00236f80(arg0->_insight, DAT_00588f38[0]);
    }
}

int Gap__Bec__beStaticInfoCtl__vfunc_30(void)
{
    return g_beStaticInfo_metaObject[0];
}

void Gap__Bec__beStaticInfoCtl__vfunc_31(void)
{
}

void Gap__Bec__beStaticInfoCtl__vfunc_29(A *arg0, beBaseInfoRam *arg1) {
    /* matching construct: a typed view of the receiver declared first; casting arg0 at each use makes the compiler hoist the field address into an extra saved register */
    beStaticInfoCtl *self = (beStaticInfoCtl *)arg0; int a0; beBaseInfo *s0; int *a3; int z; int t0;
    a0 = self->_messenger;
    s0 = (beBaseInfo *)arg1->_parentInfo;
    z = ((a0 != 0) ^ 1);
    if (z) { do { arg0->v136(); a0 = self->_messenger; z = ((a0 != 0) ^ 1); } while (z); }
    a3 = (int *)s0->_name;
    t0 = arg1->_ramNo;
    a3 = a3 != 0 ? a3 : &DAT_004e0858[0];
    beMessenger_RegisterReceiver(a0, arg1, &DAT_0050ff68[0], a3, t0);
    ObjectList_AppendRetained(self->_staticInfoList, s0);
}

int Gap__Bec__beStaticInfoCtl__vfunc_34(beStaticInfoCtl *arg0, beBaseInfoRam *arg1, beMessengerWork *arg2) {
    switch (beMessenger_ResolveEnumValue(arg0->_messenger, FUN_00343700(), arg2->_message)) {
    case 0:
        beMessenger_AppendObject(arg0->_messenger, arg0->_staticInfoList);
        goto one;
    default:
        return 0;
    }
one:
    return 1;
}

int Gap__Bec__beStaticInfoCtl__vfunc_20(void)
{
    return g_beStaticInfoCtl_metaObject[0];
}
