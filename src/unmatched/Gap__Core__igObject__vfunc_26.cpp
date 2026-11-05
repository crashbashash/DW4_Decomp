#include "dw4/reflected.h"
/* matching construct: dummy-virtual view so ->v32() dispatches through the vtable slot; beBaseInfoManager receiver is a hypothesis (#2721) */
class O { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void v32(); };
extern "C" {
int FUN_00236c40(...);
int List_Reserve(...);
int igObject_Destroy(...);
void Gap__Core__igObject__vfunc_26(beBaseInfoManager *arg0);
}
extern "C" void Gap__Core__igObject__vfunc_26(beBaseInfoManager *arg0) {
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
