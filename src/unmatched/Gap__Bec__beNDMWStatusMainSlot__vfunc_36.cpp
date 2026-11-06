/* BeNDMWStatusMainSlot vfunc 36: creates the D0 status sub-window (held across its binding, the
 * sub-window append and the kind-list push) and marks it as the ability-type variant with
 * equipment and unknown entries disabled. */
#include "dw4/reflected.h"
extern "C" {
beNDMWStatusCtrlD0 *FUN_003baf10(int);
int List_Resize(igIntList *, int, int);
int Memory_GetAllocatorBySelector(int);
int ObjectList_AppendRetained(int, beNDMWStatusCtrlD0 *);
int beNDMWWindow_BindContext(beNDMWStatusCtrlD0 *, beNDMWStatusMainSlot *, int, int, int);
void igObject_Destroy(igObject *);
int igObject_GetAllocator(beNDMWStatusMainSlot *);
extern int DAT_004cf6e8[4];
extern int DAT_00587110[4];
extern unsigned char GPR_00554c14;
}
/* Owning stack reference to the new sub-window, released on scope exit (reference count in the low
 * 23 bits of the igObject header's _refCount). */
class WindowRef {
public:
    beNDMWStatusCtrlD0 *p;
    WindowRef(beNDMWStatusCtrlD0 *o) : p(o) {}
    ~WindowRef() { igObject *o = (igObject *)p; if (o != 0) { --o->_refCount; if ((o->_refCount & 0x7fffff) == 0) igObject_Destroy(o); } }
};
extern "C" void Gap__Bec__beNDMWStatusMainSlot__vfunc_36(beNDMWStatusMainSlot *arg0) {
    int al;
    int c;
    igIntList *l;
    beNDMWStatusCtrlD0 *w;

    al = igObject_GetAllocator(arg0);
    al = (GPR_00554c14 != 0) ? al : Memory_GetAllocatorBySelector(DAT_00587110[0]);
    WindowRef window(FUN_003baf10(al));
    beNDMWWindow_BindContext(window.p, arg0, arg0->_insight, arg0->_playerNo, 0);
    ObjectList_AppendRetained(arg0->_subWindow, window.p);
    w = window.p;
    l = (igIntList *)w->_kindList;
    c = l->_count;
    if (c < l->_capacity) {
        /* matching construct: volatile re-read of the count */
        l->_count = *(volatile int *)&l->_count + 1;
    } else {
        List_Resize(l, c + 1, 4);
    }
    ((int *)l->_data)[c] = DAT_004cf6e8[0];
    window.p->_isAbType = 1;
    window.p->_isEquipDisable = 1;
    window.p->_isUnknownDisable = 1;
}
