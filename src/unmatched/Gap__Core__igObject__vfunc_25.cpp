extern "C" {
int FUN_00236be0(...);
int ObjectList_AppendRetained(...);
}
#include "dw4/reflected.h"
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
