#include "dw4/reflected.h"
class Pool {
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
    virtual void v108(int);
};
class Ctl {
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
    virtual void v124();
};
class Sub {
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
    virtual void d32();
    virtual void v140();
};
struct Holder { igInsightCore *p; };
extern "C" {
void *FUN_00236f80(...);
int igObject_IsKindOf(...);
int FUN_00463c80();
Pool *FUN_002f8a20();
Pool *Memory_GetAllocatorBySelector(...);
void *igAnimationCombinerBoneInfoPool_Create(...);
void *igAnimationStatePool_Create(...);
void *igEnbayaContextPool_Create(...);
int igObject_Destroy(...);
}
extern igAnimationCombinerBoneInfoPool * DAT_00562528[4];
extern igAnimationStatePool * DAT_00562540[4];
extern igEnbayaContextPool * DAT_00562718[4];
extern int DAT_00587108[4];
extern int DAT_00587110[4];
extern int DAT_0058c790[4];
extern unsigned char GPR_00554c14;

#define REL(v) { igObject *t_ = (igObject *)(v); if (t_ != 0) { t_->_refCount = t_->_refCount - 1; if (((unsigned long long) ((long long) (int) t_->_refCount << 0x29) >> 0x29) == 0) { igObject_Destroy(t_); } } }
struct H { static void *castit(void *s) {
    if (s != 0 && igObject_IsKindOf(s, DAT_0058c790[0]) != 0) return s; else return 0; } };
extern "C" void FUN_0025afe0(Holder *arg0) {
    Pool *var_a0;
    Pool *var_v0;
    void *var_s0;
    FUN_00463c80();
    var_s0 = H::castit(FUN_00236f80(arg0->p, DAT_0058c790[0]));
    ((Ctl *)((igViewerRenderer *)((igViewerSceneInfoManager *)var_s0)->_viewerRenderer)->_sceneTraversal)->v124();
    ((Sub *)arg0->p->_visualContext)->v140();
    REL(DAT_00562718[0]);
    DAT_00562718[0] = 0;
    { Pool *a_ = FUN_002f8a20(); var_v0 = GPR_00554c14 != 0 ? a_ : Memory_GetAllocatorBySelector(DAT_00587108[0]); }
    REL(DAT_00562718[0]);
    DAT_00562718[0] = (igEnbayaContextPool *)igEnbayaContextPool_Create(var_v0);
    { Pool *a_ = FUN_002f8a20(); var_v0 = GPR_00554c14 != 0 ? a_ : Memory_GetAllocatorBySelector(DAT_00587108[0]); }
    REL(DAT_00562528[0]);
    DAT_00562528[0] = (igAnimationCombinerBoneInfoPool *)igAnimationCombinerBoneInfoPool_Create(var_v0);
    DAT_00562528[0]->_resetMode = 0;
    { Pool *a_ = FUN_002f8a20(); var_v0 = GPR_00554c14 != 0 ? a_ : Memory_GetAllocatorBySelector(DAT_00587108[0]); }
    REL(DAT_00562540[0]);
    DAT_00562540[0] = (igAnimationStatePool *)igAnimationStatePool_Create(var_v0);
    { Pool *a_ = FUN_002f8a20(); var_a0 = GPR_00554c14 != 0 ? a_ : Memory_GetAllocatorBySelector(DAT_00587110[0]); }
    if (var_a0 != 0) {
        var_a0->v108(0);
    }
}
