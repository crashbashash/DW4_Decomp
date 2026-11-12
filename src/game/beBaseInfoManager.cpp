#include "dw4/reflected.h"

extern "C" void Gap__Bec__beBaseInfoManager__vfunc_21(void);
extern "C" void Gap__Core__igObject__vfunc_22(void);
extern "C" void Gap__Core__igObject__vfunc_24(void);
extern "C" int FUN_00236f80(...);
extern "C" int FUN_00236be0(...);
extern "C" int ObjectList_AppendRetained(...);
extern "C" void FUN_003788c0(void);
extern "C" int FUN_00236c40(...);
extern "C" int List_Reserve(...);
extern "C" int igObject_Destroy(...);
extern "C" int FUN_003a0540(...);
extern "C" int Gap__Bec__beBaseInfoManager__vfunc_20(void);
class V136 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual int vX(); };
struct A { char pad[12]; int fc; int f10; int f14; };
extern "C" int g_beSystem_metaObject[4];
extern "C" int g_beMessenger_metaObject[4];
extern "C" void Gap__Core__igObject__vfunc_23(A *arg0);
struct Obj;
struct Obj {
    virtual void a0();
    virtual void a1();
    virtual void a2();
    virtual void a3();
    virtual void a4();
    virtual void a5();
    virtual void a6();
    virtual void a7();
    virtual void a8();
    virtual void a9();
    virtual void a10();
    virtual void a11();
    virtual void a12();
    virtual void a13();
    virtual void a14();
    virtual void a15();
    virtual void a16();
    virtual void a17();
    virtual void a18();
    virtual void a19();
    virtual int v88();
    virtual void b0();
    virtual void b1();
    virtual void b2();
    virtual void b3();
    virtual void b4();
    virtual void b5();
    virtual void b6();
    virtual void v120(Obj *);
    virtual void v124(beBaseInfoRam *);
    virtual int v128();
};
extern "C" int Gap__Core__igObject__vfunc_25(Obj *arg0, Obj *arg1);
/* matching construct: dummy-virtual view so ->v32() dispatches through the vtable slot;
 * beBaseInfoManager receiver is a hypothesis */
class O { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void v32(); };
extern "C" void Gap__Core__igObject__vfunc_26(beBaseInfoManager *arg0);
struct X { char pad[46]; unsigned char f46; };
struct L { char pad0[8]; int f8; char padC[4]; void **f16; };
struct Item { char pad[24]; L *f24; };
struct L2 { char pad0[8]; int f8; char padC[4]; Item **f16; };
class Self { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void v31(void *); char p4[12]; X *f16; char p20[4]; L2 *f24; unsigned char f28; };
extern "C" void Gap__Core__igObject__vfunc_27(Self *arg0);
extern "C" int g_beBaseInfoManager_metaObject[4];

void Gap__Bec__beBaseInfoManager__vfunc_21(void)
{
}

/* Slot 22 default: empty. */
void Gap__Core__igObject__vfunc_22(void)
{
}

void Gap__Core__igObject__vfunc_23(A *arg0) {
    ((V136 *)arg0)->vX();
    arg0->f10 = FUN_00236f80(arg0->fc, g_beSystem_metaObject[0]);
    arg0->f14 = FUN_00236f80(arg0->fc, g_beMessenger_metaObject[0]);
}

/* Slot 24 default: empty. */
void Gap__Core__igObject__vfunc_24(void)
{
}

int Gap__Core__igObject__vfunc_25(Obj *arg0, Obj *arg1) {
    beBaseInfoManager *mgr = (beBaseInfoManager *)arg0;
    beBaseInfo *info = (beBaseInfo *)arg1;
    int s0 = arg0->v128();
    if (s0 == arg1->v88()) {
        int n;
        int i;
        ObjectList_AppendRetained(mgr->_infoList, arg1);
        arg0->v120(arg1);
        n = ((beBaseInfoRamList *)info->_ramList)->_count;
        for (i = 0; i < n; i++) {
            beBaseInfoRam *it = ((beBaseInfoRam **)((beBaseInfoRamList *)info->_ramList)->_data)[i];
            it->_st0 = 0;
            it->_st3 = 0;
            it->_st2 = 0;
            it->_st1 = 0;
            it->_parentManager = (int)arg0;
            it->_parentInfo = (int)arg1;
            it->_ramNo = i;
            arg0->v124(it);
        }
        FUN_00236be0(mgr->_insight, arg0);
        mgr->_isUpdateRun = 1;
        return 1;
    }
    return 0;
}

void FUN_003788c0(void)
{
}

void Gap__Core__igObject__vfunc_26(beBaseInfoManager *arg0) {
    int n1;
    beBaseInfoList *S;
    int i1;
    beBaseInfoList *L;
    beBaseInfoRamList *M;
    int n3;
    int n2;
    int n4;
    int j2;
    int i4;
    int i3;

    ((O *)arg0)->v32();
    L = (beBaseInfoList *)arg0->_infoList;
    n1 = L->_count;
    for (i1 = 0; i1 < n1; i1++) {
        M = (beBaseInfoRamList *)((beBaseInfo **)((beBaseInfoList *)arg0->_infoList)->_data)[i1]->_ramList;
        n2 = M->_count;
        for (j2 = 0; j2 < n2; j2++) {
            beBaseInfoRam *e = ((beBaseInfoRam **)M->_data)[j2];
            e->_parentManager = 0;
            e->_parentInfo = 0;
        }
    }
    S = (beBaseInfoList *)arg0->_infoList;
    n3 = S->_count;
    for (i3 = 0; i3 < n3; i3++) {
        igObject *p = ((igObject **)S->_data)[i3];
        if (p != 0) {
            p->_refCount = p->_refCount - 1;
            if (((unsigned long long)((long long)(int)p->_refCount << 0x29) >> 0x29) == 0) {
                igObject_Destroy(p);
            }
        }
    }
    n4 = S->_count;
    for (i4 = 0; i4 < n4; i4++) {
        ((void **)S->_data)[i4] = 0;
    }
    S->_count = 0;
    S = (beBaseInfoList *)arg0->_infoList;
    int ok = S->_count > 0;
    if (ok == 0) {
        List_Reserve(S, 0, 4);
    }
    FUN_00236c40(arg0->_insight, arg0);
    arg0->_isUpdateRun = 0;
}

void Gap__Core__igObject__vfunc_27(Self *arg0) {
    int temp_s5;
    int var_s4;
    int temp_s3;
    int var_s2;
    L *temp_s7;
    if (FUN_003a0540(arg0->f16) != 0 && arg0->f28 != 0 && arg0->f16->f46 == 0) {
        temp_s5 = arg0->f24->f8;
        for (var_s4 = 0; var_s4 < temp_s5; var_s4++) {
            temp_s7 = arg0->f24->f16[var_s4]->f24;
            temp_s3 = temp_s7->f8;
            for (var_s2 = 0; var_s2 < temp_s3; var_s2++) {
                arg0->v31(temp_s7->f16[var_s2]);
            }
        }
    }
}

int Gap__Bec__beBaseInfoManager__vfunc_20(void)
{
    return g_beBaseInfoManager_metaObject[0];
}

