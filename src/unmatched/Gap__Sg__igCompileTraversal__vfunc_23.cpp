#include "dw4/reflected.h"
extern "C" {
struct T { virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual int setMatrix(int); int references; int f8; T *f12; char p[16]; int f32; };
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
}
class VC104 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual int vX(int, int); };
class VC128L { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual int vX(long long); };
struct ObjectRef {
    T *p;
    ObjectRef(void *object) : p((T *)object) {}
    ~ObjectRef() {
        T *object = p;
        if (object != 0) {
            --object->references;
            if ((object->references & 0x7FFFFF) == 0) {
                igObject_Destroy(object);
            }
        }
    }
    T *operator->() const { return p; }
};
extern "C" void Gap__Sg__igCompileTraversal__vfunc_23(igCompileTraversal *self, int arg1) {
    int a1 = self->_vc;
    if (a1 != 0) {
        L0 *stack = (L0 *)self->_attrStack;
        ((VC104 *)(stack->f16->f16[stack->f68[DAT_0055f308[0]->f8]]->f20))->vX(a1, (int)stack);
    }
    {
    ObjectRef matrix(FUN_001356b0(igObject_GetAllocator(self)));
    ObjectRef info(FUN_001a3590(igObject_GetAllocator(self)));
    T **slot = &info->f12;
    T *old = *slot;
    if (old != 0) {
        --old->references;
        if ((old->references & 0x7FFFFF) == 0) {
            igObject_Destroy(old);
        }
    }
    *slot = 0;
    info->f8 = -1;
    info->f32 = 0;
    self->_currentBoneIndex = 1;
    int identity[16];
    igMatrix44f_SetIdentity(identity);
    FUN_001b6ee0(self, identity);
    matrix->setMatrix((int)&self->_viewMat);
    ObjectList_AppendRetained(self->_mvmList, matrix.p);
    ObjectList_AppendRetained(self->_xformInfoList, info.p);
    FUN_001b1030(self->_attrStack, matrix.p);
    }
    if (self->_userTimeState != 0) {
        ((VC128L *)self)->vX(self->_timeLong);
    }
    Gap__Sg__igTraversal__vfunc_23(self, arg1);
}
