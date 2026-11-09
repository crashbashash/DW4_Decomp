#include "dw4/reflected.h"
extern "C" {
void igObject_Destroy(igObject *);
int List_Resize(...);
int Memory_GetAllocatorBySelector(...);
int ObjectList_AppendRetained(...);
int beNDMWWindow_BindContext(...);
int igObject_GetAllocator(...);
extern int DAT_004cf6d8[4];
extern int DAT_00587110[4];
extern unsigned char GPR_00554c14;
}
struct UnidentifiedChildWindow { int word0; int references; char p8[92]; igDataList *list; int f104; char f108; char pad109; char f110; };
extern "C" UnidentifiedChildWindow *FUN_003baf10(...);
/* Owning stack reference to the new child window; released on scope exit (reference count in the
 * low 23 bits of references). */
class ObjectRef {
public:
    UnidentifiedChildWindow *p;
    ObjectRef(UnidentifiedChildWindow *o) : p(o) {}
    ~ObjectRef() { UnidentifiedChildWindow *o = p; if (o != 0) { --o->references; if ((o->references & 0x7fffff) == 0) igObject_Destroy((igObject *)o); } }
};
extern "C" void Gap__Bec__beNDMWStatusPowerSocket__vfunc_36(beNDMWStatusPowerSocket *arg0);
void Gap__Bec__beNDMWStatusPowerSocket__vfunc_36(beNDMWStatusPowerSocket *arg0) {
    int alloc;
    int a;
    int s1;
    igDataList *s0;
    alloc = igObject_GetAllocator(arg0);
    if (GPR_00554c14 != 0) {
        a = alloc;
    } else {
        a = Memory_GetAllocatorBySelector(DAT_00587110[0]);
    }
    ObjectRef child(FUN_003baf10(a));
    beNDMWWindow_BindContext(child.p, arg0, arg0->_insight, arg0->_playerNo, 0);
    ObjectList_AppendRetained(arg0->_subWindow, child.p);
    s0 = child.p->list;
    s1 = s0->_count;
    if (s1 < s0->_capacity) {
        /* matching construct: const re-read of the count */
        s0->_count = ((const igDataList *)s0)->_count + 1;
    } else {
        List_Resize(s0, s1 + 1, 4);
    }
    ((int *)s0->_data)[s1] = DAT_004cf6d8[0];
    child.p->f104 = 0;
    child.p->f108 = 1;
    child.p->f110 = 1;
}
