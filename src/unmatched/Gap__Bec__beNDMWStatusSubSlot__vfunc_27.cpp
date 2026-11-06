#include "dw4/reflected.h"
extern "C" {
int igObject_GetAllocator(void *);
int Memory_GetAllocatorBySelector(int);
beNDMWStatusSelectE0 *FUN_003b5370(int);
igBoolList *FUN_002cb0d0(int);
int beNDMWWindow_BindContext(void *, void *, int, int, int);
int ObjectList_AppendRetained(int, void *);
int List_Resize(void *, int, int);
int beMessenger_SelectGroup(int, int *);
int beMessenger_AppendString(int, int *);
int beMessenger_DispatchSelected(int, int *);
void igObject_Destroy(void *);
extern int DAT_00519b50[4];
extern int DAT_00519c28[4];
extern int DAT_00519c30[4];
extern int DAT_00519f68[4];
extern int *DAT_004cf670[4];
extern int DAT_00587110[4];
extern unsigned char GPR_00554a2c;
extern unsigned char GPR_00554c14;
}
#define REL(P) { igObject *q = (igObject *)(P); if (q != 0) { q->_refCount = q->_refCount - 1; if ((q->_refCount & 0x7fffff) == 0) { igObject_Destroy(q); } } }
#define APPEND(V) { igBoolList *l = flags.p; int n = l->_count; if (n < l->_capacity) { l->_count = n + 1; } else { List_Resize(l, n + 1, 1); } *(unsigned char *)(n + l->_data) = (V); }
/* Owning stack reference to the new select window; released on scope exit (reference count in the
 * low 23 bits of _refCount). */
class WindowRef {
public:
    beNDMWStatusSelectE0 *p;
    WindowRef(beNDMWStatusSelectE0 *w) : p(w) {}
    ~WindowRef() { beNDMWStatusSelectE0 *w = p; if (w != 0) { --w->_refCount; if ((w->_refCount & 0x7fffff) == 0) igObject_Destroy(w); } }
};
/* Owning stack reference to the new decide list; released on scope exit. */
class BoolListRef {
public:
    igBoolList *p;
    BoolListRef(igBoolList *l) : p(l) {}
    ~BoolListRef() { igBoolList *l; if ((l = p) != 0) { --l->_refCount; if ((l->_refCount & 0x7fffff) == 0) igObject_Destroy(l); } }
};
extern "C" void Gap__Bec__beNDMWStatusSubSlot__vfunc_27(beNDMWStatusSubSlot *arg0);
extern "C" void Gap__Bec__beNDMWStatusSubSlot__vfunc_27(beNDMWStatusSubSlot *arg0) {
    int a;
    igBoolList *l0;
    beNDMWStatusSelectE0 *w;
    bool fl;
    int i;
    int **p;
    int *s3;
    igIntList *t;

    a = igObject_GetAllocator(arg0);
    a = GPR_00554c14 ? a : Memory_GetAllocatorBySelector(DAT_00587110[0]);
    WindowRef win(FUN_003b5370(a));
    beNDMWWindow_BindContext(win.p, arg0, arg0->_insight, arg0->_playerNo, 0);
    ObjectList_AppendRetained((unsigned int)arg0->_subWindow /* matching construct: unsigned argument keeps the retail load order */, win.p);
    win.p->_selectMax = 3;
    win.p->_entCode = 0x78;
    a = igObject_GetAllocator(arg0);
    a = GPR_00554c14 ? a : Memory_GetAllocatorBySelector(DAT_00587110[0]);
    BoolListRef flags(FUN_002cb0d0(a));
    APPEND(GPR_00554a2c)
    t = (igIntList *)arg0->_subSlot;
    fl = false;
    if (t->_count > 0 && ((int *)t->_data)[arg0->_kindListPos] != 0) fl = true;
    APPEND(0)
    APPEND(fl)
    l0 = *(igBoolList * volatile *)&flags.p; /* matching construct: pinned reads keep the s1/s2 colouring */
    w = *(beNDMWStatusSelectE0 * volatile *)&win.p;
    if (l0 != 0) {
        l0->_refCount = l0->_refCount + 1;
    }
    REL(w->_decideList)
    w->_decideList = (int)l0;
    i = 0;
    l0 = flags.p;
    if (0 < l0->_count) {
        p = &DAT_004cf670[0];
        do {
            if (*(unsigned char *)(l0->_data + i) != 0) {
                s3 = &DAT_00519c30[0];
            } else {
                s3 = &DAT_00519f68[0];
            }
            beMessenger_SelectGroup(arg0->_messenger, &DAT_00519c28[0]);
            beMessenger_AppendString(arg0->_messenger, &DAT_00519b50[0]);
            beMessenger_AppendString(arg0->_messenger, *p);
            beMessenger_DispatchSelected(arg0->_messenger, s3);
            l0 = flags.p;
            i += 1;
            p += 1;
        } while (i < l0->_count);
    }
}
