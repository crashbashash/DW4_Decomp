#include "dw4/reflected.h"
/* _bound stays a 4-byte handle, so it is cast to igAABox *; _min and _max are float[3] and are
 * copied as floats. */
extern "C" {
void igObject_Destroy(igAABox *);
igAABox *FUN_0018a660(...);
int FUN_0018ac80(...);
int Memory_GetAllocatorBySelector(...);
int igObject_GetAllocator(...);
extern int DAT_00587110[4];
extern unsigned char GPR_00554c14;
void FUN_00396940(beModelCtrl *arg0, beModelCtrlNode2 *arg1, igAABox *arg2);
}
struct Rel { static inline void go(igAABox *object) {
    if (object) {
        --object->_refCount;
        if (((unsigned long long)(long long)(int)object->_refCount & 0x7fffffULL) == 0)
            igObject_Destroy(object);
    }
} };
/* Owning stack reference to the freshly created bound box; released on scope exit once the node
 * holds its own reference (reference count in the low 23 bits of _refCount). */
class ObjectRef {
public:
    igAABox *p;
    ObjectRef(igAABox *o) : p(o) {}
    ~ObjectRef() { igAABox *o = p; if (o != 0) { --o->_refCount; if ((o->_refCount & 0x7fffff) == 0) igObject_Destroy(o); } }
};
void FUN_00396940(beModelCtrl *arg0, beModelCtrlNode2 *arg1, igAABox *arg2) {
    igAABox *s0;
    s0 = (igAABox *)arg1->_bound;
    if (s0 == 0) {
        int alloc = igObject_GetAllocator(arg0);
        int a;
        if (GPR_00554c14 != 0) {
            a = alloc;
        } else {
            a = Memory_GetAllocatorBySelector(DAT_00587110[0]);
        }
        ObjectRef created(FUN_0018a660(a));
        s0 = created.p;
        if (s0 != 0) {
            s0->_refCount++;
        }
        Rel::go((igAABox *)arg1->_bound);
        arg1->_bound = (int)s0;
        /* matching construct: the box is re-read from the reference before it leaves scope, so the release
         * below works on that register copy (retail 0x003969ec) */
        s0 = created.p;
    }
    s0->_min[0] = arg2->_min[0];
    s0->_min[1] = arg2->_min[1];
    s0->_min[2] = arg2->_min[2];
    s0->_max[0] = arg2->_max[0];
    s0->_max[1] = arg2->_max[1];
    s0->_max[2] = arg2->_max[2];
    FUN_0018ac80(s0, arg1->_m);
}
