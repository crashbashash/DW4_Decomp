#include "dw4/igSmartPointer.h"

extern "C" {
typedef struct R : public igObject { struct R *f8; } R;
typedef struct O { char pad[32]; R *f32; R *f36; char pad2[20]; R *f60; } O;
void *igObject_GetAllocator(O *);
R *FUN_00130020(void *);
R *FUN_00137ab0(void *);
R *FUN_00149c30(void *);
R *FUN_0014f2c0(void *);
int FUN_001b6f30(O *, R *, R *);
}

static inline void retain(R *object) {
    if (object != 0) {
        object->_refCount = object->_refCount + 1;
    }
}
static inline void release(R *object) {
    if (object != 0) {
        object->_refCount = object->_refCount - 1;
        if ((object->_refCount & 0x7FFFFF) == 0) {
            igObject_Destroy(object);
        }
    }
}
extern "C" void Gap__Sg__igCommonTraversal__vfunc_28(O *arg0, R *arg1) {
    void *a;
    bool var_s1;
    R *t;

    retain(arg1);
    release(arg0->f60);
    arg0->f60 = arg1;
    var_s1 = 0;
    if (arg1 == 0) {
        a = igObject_GetAllocator(arg0);
        release(arg0->f36);
        arg0->f36 = FUN_00137ab0(a);
        a = igObject_GetAllocator(arg0);
        release(arg0->f32);
        arg0->f32 = FUN_0014f2c0(a);
        var_s1 = 1;
    } else {
        if (arg0->f36 == 0) {
            igSmartPointer<R> created(FUN_00130020(igObject_GetAllocator(arg0)));
            t = created.get();
            retain(arg1);
            release(t->f8);
            t->f8 = arg1;
            t = created.get();
            retain(t);
            release(arg0->f36);
            arg0->f36 = t;
            var_s1 = 1;
        }
        if (arg0->f32 == 0) {
            igSmartPointer<R> created(FUN_00149c30(igObject_GetAllocator(arg0)));
            t = created.get();
            retain(arg1);
            release(t->f8);
            t->f8 = arg1;
            t = created.get();
            retain(t);
            release(arg0->f32);
            arg0->f32 = t;
            var_s1 = 1;
        }
    }
    if (var_s1) {
        FUN_001b6f30(arg0, arg0->f36, arg0->f32);
    }
}
