#include "dw4/reflected.h"
extern "C" {
struct T { int word0; int references; int f8; T *f12; char p[16]; int f32; };
struct E { char p[20]; void *f20; };
struct L1 { char p[16]; E **f16; };
struct L0 { char p[16]; L1 *f16; char q[48]; int *f68; };
struct G { char p[8]; int f8; };
void *FUN_001356b0(...);
void *FUN_001a3590(...);
int igMatrix44f_SetIdentity(...);
int FUN_001b1030(...);
int FUN_001b6ee0(...);
int Gap__Sg__igTraversal__vfunc_23(...);
int ObjectList_AppendRetained(...);
void igObject_Destroy(T *);
int igObject_GetAllocator(...);
extern G *DAT_0055f308[4];
void Gap__Sg__igCompileTraversal__vfunc_23(void *arg0, void *arg1);
}
class VC104 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual int vX(int, int); };
class VC128 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual int vX(int); };
class VC128L { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual int vX(long long); };
struct Holder { Holder *x; };
void Gap__Sg__igCompileTraversal__vfunc_23(void *a0, void *p1) {
    igCompileTraversal *arg0 = (igCompileTraversal *)a0;
    int arg1 = (int)p1;
    T *volatile sp8C;
    T *volatile sp88;
    int sp40[16];
    int a1 = arg0->_vc;
    if (a1 != 0) {
        L0 *a2 = (L0 *)arg0->_attrStack;
        ((VC104 *)(a2->f16->f16[a2->f68[DAT_0055f308[0]->f8]]->f20))->vX(a1, (int)a2);
    }
    sp8C = (T *)FUN_001356b0(igObject_GetAllocator(arg0));
    sp88 = (T *)FUN_001a3590(igObject_GetAllocator(arg0));
    T *t = sp88;
    T **pf = &t->f12;
    T *old = *pf;
    if (old) {
        --old->references;
        if (((unsigned long long)(long long)old->references & 0x7fffffULL) == 0)
            igObject_Destroy(old);
    }
    *pf = 0;
    sp88->f8 = -1;
    sp88->f32 = 0;
    arg0->_currentBoneIndex = 1;
    igMatrix44f_SetIdentity(&sp40, -1);
    FUN_001b6ee0(arg0, &sp40);
    ((VC128 *)sp8C)->vX((int)&arg0->_viewMat);
    T *x1 = sp8C;
    int l1 = *(volatile int *)&arg0->_mvmList;
    ObjectList_AppendRetained(l1, x1);
    T *x2 = sp88;
    int l2 = *(volatile int *)&arg0->_xformInfoList;
    ObjectList_AppendRetained(l2, x2);
    T *x3 = sp8C;
    int l3 = *(volatile int *)&arg0->_attrStack;
    FUN_001b1030(l3, x3);
    T *r1 = sp88;
    if (r1) {
        --r1->references;
        if (((unsigned long long)(long long)r1->references & 0x7fffffULL) == 0)
            igObject_Destroy(r1);
    }
    T *r2 = sp8C;
    if (r2) {
        --r2->references;
        if (((unsigned long long)(long long)r2->references & 0x7fffffULL) == 0)
            igObject_Destroy(r2);
    }
    if (arg0->_userTimeState != 0) {
        ((VC128L *)arg0)->vX(arg0->_timeLong);
    }
    Gap__Sg__igTraversal__vfunc_23(arg0, arg1);
}
