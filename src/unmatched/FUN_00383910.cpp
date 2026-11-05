#include "dw4/reflected.h"
/* matching construct: dummy virtual slots so the vX() call dispatches through the retail vtable offset of the
   vertex-array configure method (an igVertexArray subclass instance; the reflected igVertexArray has no vtable type) */
class Sink { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void vX(unsigned &, int, int, int); };
extern "C" {
void *Memory_GetAllocatorBySelector(...);
void *igObject_GetAllocator(...);
int igObject_Destroy(igVertexArray *);
Sink *FUN_0014b940(...);
extern unsigned char GPR_00554c14;
extern int DAT_00587110[4];
void FUN_00383910(beFont *arg0, igGeometryAttr *arg1, int arg2, int arg3);
}
/* Owning stack reference to a vertex array: first the attribute's current array, then the newly created one
 * (reference count in the low 23 bits of _refCount); released on scope exit.  The out-of-line copy the
 * exception table names is the retail body 0x001338d0 (config/SLUS-20836/unit-objects.json, duplicate
 * __dt__9ObjectRefFv). */
class ObjectRef {
public:
    igVertexArray *p;
    ObjectRef(igVertexArray *o) : p(o) {}
    ~ObjectRef() { igVertexArray *o = p; if (o != 0) { --o->_refCount; if ((o->_refCount & 0x7fffff) == 0) igObject_Destroy(o); } }
};
void FUN_00383910(beFont *arg0, igGeometryAttr *arg1, int arg2, int arg3) {
    ObjectRef va((igVertexArray *)arg1->_vertexArray); /* matching construct: declared first so it takes the retail slot above sp68 */
    unsigned sp68;
    void *al;
    igVertexArray *t;
    igVertexArray *p;
    t = va.p;
    if (t != 0) {
        t->_refCount = t->_refCount + 1;
    }
    al = igObject_GetAllocator(arg0);
    al = (GPR_00554c14 != 0) ? al : Memory_GetAllocatorBySelector(DAT_00587110[0]);
    /* Re-point the reference at the new array: the borrowed current array is released first. */
    t = va.p;
    if (t != 0) {
        t->_refCount = t->_refCount - 1;
        if (((unsigned long long)(long long)(int)t->_refCount & 0x7fffffULL) == 0) {
            igObject_Destroy(t);
        }
    }
    va.p = (igVertexArray *)FUN_0014b940(al);
    sp68 = ((beFontImage **)((beFontImageList *)arg0->_fonts)->_data)[arg2]->_vertexFlags;
    sp68 = sp68 & ~4u;
    ((Sink *)va.p)->vX(sp68, arg3, 0, 0);
    p = va.p;
    if (p != 0) {
        p->_refCount = p->_refCount + 1;
    }
    t = (igVertexArray *)arg1->_vertexArray;
    if (t != 0) {
        t->_refCount = t->_refCount - 1;
        if (((unsigned long long)(long long)(int)t->_refCount & 0x7fffffULL) == 0) {
            igObject_Destroy(t);
        }
    }
    arg1->_vertexArray = (int)p;
}
