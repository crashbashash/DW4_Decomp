#include "dw4/reflected.h"
extern "C" {
long long __fixsfdi(float);
void *FUN_0036a510(...);
void *beBaseInfoDataList_Create(...);
int Memory_GetAllocatorBySelector(...);
int ObjectList_AppendRetained(...);
int igNamedObject_SetName(...);
int igObject_Destroy(...);
int igObject_GetAllocator(...);
void *igProperty_FindByName(...);
extern int DAT_00585be0[4];
extern int DAT_00587110[4];
extern unsigned char GPR_00554c14;
}
typedef igObject Obj;
struct Rel {
    static inline void go(Obj *p) {
        if (p != 0) {
            p->_refCount = p->_refCount - 1;
            if ((p->_refCount & 0x7fffff) == 0) igObject_Destroy(p);
        }
    }
};
struct Ref {
    Obj *p;
    Ref(void *x) { p = (Obj *)x; }
    ~Ref() { Obj *x = p; if (x) { --x->_refCount; if ((x->_refCount & 0x7fffff) == 0) igObject_Destroy(x); } }
};
struct RefB {
    Obj *p;
    RefB(void *x) { p = (Obj *)x; }
    ~RefB() { Obj *x = p; if (x) { --x->_refCount; if ((x->_refCount & 0x7fffff) == 0) igObject_Destroy(x); } }
};
typedef beBaseInfoRamTimer Lst;
typedef beAction2InfoRam Act;
struct ActOps {
    static inline void Ensure(Act *o) {
        if (o->_dataList == 0) {
            int a = igObject_GetAllocator(o);
            a = GPR_00554c14 ? a : Memory_GetAllocatorBySelector(DAT_00587110[0]);
            Ref r(beBaseInfoDataList_Create(a));
            Obj *s2 = r.p;
            if (s2 != 0) s2->_refCount = s2->_refCount + 1;
            Rel::go((Obj *)o->_dataList);
            o->_dataList = (int)s2;
        }
    }
};
extern "C" void FUN_003a7a20(Act *arg0, int arg1, long long arg2) {
    Lst *var_s2;
    long long t;
    unsigned v;
    float f;

    ActOps::Ensure(arg0);
    var_s2 = (Lst *)igProperty_FindByName((Obj *)arg0->_dataList, DAT_00585be0[0], arg1);
    if (var_s2 == 0) {
        int a = igObject_GetAllocator(arg0);
        a = GPR_00554c14 ? a : Memory_GetAllocatorBySelector(DAT_00587110[0]);
        RefB sp5C(FUN_0036a510(a));
        igNamedObject_SetName(sp5C.p, arg1);
        if (arg0->_dataList == 0) {
            int b = igObject_GetAllocator(arg0);
            b = GPR_00554c14 ? b : Memory_GetAllocatorBySelector(DAT_00587110[0]);
            Ref sp58(beBaseInfoDataList_Create(b));
            Obj *s2 = sp58.p;
            if (s2 != 0) s2->_refCount = s2->_refCount + 1;
            Rel::go((Obj *)arg0->_dataList);
            arg0->_dataList = (int)s2;
        }
        ObjectList_AppendRetained((Obj *)arg0->_dataList, sp5C.p);
        var_s2 = (Lst *)sp5C.p;
    }
    t = ((igInsightCore *)((beAction2 *)arg0->_parentManager)->_insight)->_worldTime;
    v = (unsigned)(t >> 0x12);
    f = (float)v;
    f = f * var_s2->_timeScale;
    var_s2->_timeBias = -(__fixsfdi(f) << 0x12);
    var_s2->_svWorldTime = t;
    var_s2->_keikaFrame = 1.0f;
    var_s2->_endTime = arg2;
}
