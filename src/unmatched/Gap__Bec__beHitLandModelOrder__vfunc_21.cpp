/* BeHitLandModelOrder vfunc 21: grows the ray list by one new ray when every pooled ray is in use
 * (the new ray is held in an ObjectRef across the append), then configures the next ray and
 * advances the count. */
#include "dw4/reflected.h"
extern "C" {
/* igObject header: vtable and reference count (the count is not a reflected field) */
igObject *FUN_00188220(int);
int FUN_0018d2b0(int, int, int);
int Memory_GetAllocatorBySelector(int);
int ObjectList_AppendRetained(void *, igObject *);
void igObject_Destroy(igObject *);
int igObject_GetAllocator(beHitLandModelOrder *);
extern int DAT_00587110[4];
extern unsigned char GPR_00554c14;
}
/* Owning stack reference to the newly created ray, released on scope exit (reference count in the
 * low 23 bits of _refCount). */
class ObjectRef {
public:
    igObject *p;
    ObjectRef(igObject *o) : p(o) {}
    ~ObjectRef() { igObject *o = p; if (o != 0) { --o->_refCount; if ((o->_refCount & 0x7fffff) == 0) igObject_Destroy(o); } }
};
extern "C" void Gap__Bec__beHitLandModelOrder__vfunc_21(beHitLandModelOrder *self, int a1, int a2) {
    if (self->_rayCount >= ((igRayList *)self->_rayList)->_count) {
        int a = igObject_GetAllocator(self);
        ObjectRef ray(FUN_00188220(GPR_00554c14 != 0 ? a : Memory_GetAllocatorBySelector(DAT_00587110[0])));
        /* matching construct: the (void *)(long) cast fixes the argument evaluation order of the append */
        ObjectList_AppendRetained((void *)(long)self->_rayList, ray.p);
    }
    FUN_0018d2b0(((int *)((igRayList *)self->_rayList)->_data)[self->_rayCount], a1, a2);
    self->_rayCount = self->_rayCount + 1;
}
