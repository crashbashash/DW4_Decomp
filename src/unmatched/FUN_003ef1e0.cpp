#include "dw4/reflected.h"
extern "C" {
void igObject_Destroy(igObject *);
int Memory_GetAllocatorBySelector(...);
int igObject_GetAllocator(...);
igObject *FUN_003c85b0(int);
igObject *FUN_003c87f0(int);
igObject *FUN_003c8970(int);
igObject *FUN_003c8b00(int);
igObject *FUN_003c8c90(int);
extern int DAT_00587108[4];
extern unsigned char GPR_00554c14;
int FUN_003ef1e0(igObject **arg0, int arg1, int arg2);
}
/* matching construct: dummy virtual slots so the vX() call dispatches through the retail vtable offset */
struct V { virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual int vX(int); };
/* matching construct: one releasing holder class per retail destructor copy (the table at 0x544c20 names 0x3d9d50, 0x3d9cd0, 0x3d9c50, 0x3d9bd0 and 0x3b9ba0); same holder spelling as FUN_003d8740 */
template <int K> struct ItemRef { igObject *p; ItemRef(igObject *o) : p(o) {} ~ItemRef() { igObject *o = p; if (o != 0) { --o->_refCount; if ((o->_refCount & 0x7fffff) == 0) igObject_Destroy(o); } } };
struct ItemRefLast { igObject *p; ItemRefLast(igObject *o) : p(o) {} ~ItemRefLast() { igObject *o = p; if (o != 0) { --o->_refCount; if ((o->_refCount & 0x7fffff) == 0) igObject_Destroy(o); } } };
struct Mk {
    static inline int allocator(int arg1) {
        int alloc = igObject_GetAllocator(arg1);
        int a;
        if (GPR_00554c14 != 0) {
            a = alloc;
        } else {
            a = Memory_GetAllocatorBySelector(DAT_00587108[0]);
        }
        return a;
    }
};
extern "C" int FUN_003ef1e0(igObject **arg0, int arg1, int arg2) {
    int k = (arg2 >> 12) & 0xF;
    if (k == 0) {
        {
            int a = Mk::allocator(arg1);
            ItemRef<1> sp((igObject *)FUN_003c8c90(a));
            ((V *)sp.p)->vX(arg2);
            *arg0 = sp.p;
            igObject *t = *arg0;
            if (t != 0) {
                t->_refCount++;
            }
        }
        return 0;
    } else if (k == 1) {
        {
            int a = Mk::allocator(arg1);
            ItemRef<2> sp((igObject *)FUN_003c8b00(a));
            ((V *)sp.p)->vX(arg2);
            *arg0 = sp.p;
            igObject *t = *arg0;
            if (t != 0) {
                t->_refCount++;
            }
        }
        return 0;
    } else if (k == 2) {
        {
            int a = Mk::allocator(arg1);
            ItemRef<3> sp((igObject *)FUN_003c8970(a));
            ((V *)sp.p)->vX(arg2);
            *arg0 = sp.p;
            igObject *t = *arg0;
            if (t != 0) {
                t->_refCount++;
            }
        }
        return 0;
    } else if (k == 3) {
        {
            int a = Mk::allocator(arg1);
            ItemRef<4> sp((igObject *)FUN_003c87f0(a));
            ((V *)sp.p)->vX(arg2);
            *arg0 = sp.p;
            igObject *t = *arg0;
            if (t != 0) {
                t->_refCount++;
            }
        }
        return 0;
    } else if (k == 4) {
        {
            int a = Mk::allocator(arg1);
            ItemRefLast sp((igObject *)FUN_003c85b0(a));
            ((V *)sp.p)->vX(arg2);
            *arg0 = sp.p;
            igObject *t = *arg0;
            if (t != 0) {
                t->_refCount++;
            }
        }
        return 0;
    } else {
        *arg0 = 0;
        igObject *t = *arg0;
        if (t != 0) {
            t->_refCount++;
        }
    }
}
