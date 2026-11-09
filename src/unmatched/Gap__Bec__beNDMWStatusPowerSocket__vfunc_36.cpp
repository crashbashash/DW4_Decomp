#include "dw4/igSmartPointer.h"
#include "dw4/reflected.h"
extern "C" {
int List_Resize(...);
int Memory_GetAllocatorBySelector(...);
int ObjectList_AppendRetained(...);
int beNDMWWindow_BindContext(...);
int igObject_GetAllocator(...);
extern int DAT_004cf6d8[4];
extern int DAT_00587110[4];
extern unsigned char GPR_00554c14;
}
static inline int countOf(const igDataList *l) { return l->_count; }
struct UnidentifiedChildWindow : public igObject { char p8[92]; igDataList *list; int f104; char f108; char pad109; char f110; };
extern "C" UnidentifiedChildWindow *FUN_003baf10(...);
/* Owning stack reference to the new child window; released on scope exit (reference count in the
 * low 23 bits of _refCount). */

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
    igSmartPointer<UnidentifiedChildWindow> child(FUN_003baf10(a));
    beNDMWWindow_BindContext(child.p, arg0, arg0->_insight, arg0->_playerNo, 0);
    ObjectList_AppendRetained(arg0->_subWindow, child.p);
    s0 = child.p->list;
    s1 = s0->_count;
    if (s1 < s0->_capacity) {
                s0->_count = countOf(s0) + 1;
    } else {
        List_Resize(s0, s1 + 1, 4);
    }
    ((int *)s0->_data)[s1] = DAT_004cf6d8[0];
    child.p->f104 = 0;
    child.p->f108 = 1;
    child.p->f110 = 1;
}
