#include "dw4/igSmartPointer.h"
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
extern int DAT_00519b50[4];
extern int DAT_00519c28[4];
extern int DAT_00519c30[4];
extern int DAT_00519f68[4];
extern int *DAT_004cf670[4];
extern int DAT_00587110[4];
extern unsigned char GPR_00554a0c;
extern unsigned char GPR_00554c14;
}
#define REL(P) { igObject *q = (igObject *)(P); if (q != 0) { q->_refCount = q->_refCount - 1; if ((q->_refCount & 0x7fffff) == 0) { igObject_Destroy(q); } } }
#define APPEND(V) { igBoolList *l = flags.p; int n = l->_count; if (n < l->_capacity) { l->_count = n + 1; } else { List_Resize(l, n + 1, 1); } *(unsigned char *)(n + l->_data) = (V); }

/* Owning stack reference to the new decide list; released on scope exit. */
class BoolListRef {
public:
    igBoolList *p;
    BoolListRef(igBoolList *l) : p(l) {}
    igBoolList *get() const { return p; }
    ~BoolListRef() { igBoolList *l; if ((l = p) != 0) { --l->_refCount; if ((l->_refCount & 0x7fffff) == 0) igObject_Destroy(l); } }
};
struct SlotKind { char p[24]; int lineCount; };
extern "C" void Gap__Bec__beNDMWStatusPowerSocket__vfunc_27(beNDMWStatusPowerSocket *arg0);
extern "C" void Gap__Bec__beNDMWStatusPowerSocket__vfunc_27(beNDMWStatusPowerSocket *arg0) {
    int a;
    igBoolList *l0;
    beNDMWStatusSelectE0 *w;
    bool fl0;
    bool fl;
    int i;
    int **p;
    int *s3;
    igIntList *t;

    a = igObject_GetAllocator(arg0);
    a = GPR_00554c14 ? a : Memory_GetAllocatorBySelector(DAT_00587110[0]);
    igSmartPointer<beNDMWStatusSelectE0> win(FUN_003b5370(a));
    beNDMWWindow_BindContext(win.p, arg0, arg0->_insight, arg0->_playerNo, 0);
    ObjectList_AppendRetained((unsigned int)arg0->_subWindow /* matching construct: unsigned argument keeps the retail load order */, win.p);
    switch (((beNDMWWindow *)arg0->_mother)->_entCode) {
    case 0:
        win.p->_entCode = 124;
        win.p->_selectMax = 2;
        break;
    case 1:
        win.p->_entCode = 46;
        win.p->_selectMax = 3;
        break;
    }
    a = igObject_GetAllocator(arg0);
    a = GPR_00554c14 ? a : Memory_GetAllocatorBySelector(DAT_00587110[0]);
    BoolListRef flags(FUN_002cb0d0(a));
    APPEND(GPR_00554a0c)
    t = (igIntList *)arg0->_powerSocket;
    fl0 = false;
    fl = false;
    if (t->_count > 0) {
        if (arg0->_st3 == 0) {
            SlotKind *kind = ((SlotKind **)t->_data)[0];
            if (kind != 0 && kind->lineCount > 0) fl0 = true;
        }
        if (((int *)t->_data)[arg0->_kindListPos] != 0 && arg0->_kindListPos != 0) fl = true;
    }
    APPEND(fl0)
    if (((beNDMWWindow *)arg0->_mother)->_entCode == 1) APPEND(fl)
    /* matching construct: a const view of the holder keeps the retail reload of the list */
    { const BoolListRef &view = flags; l0 = view.p; }
    w = win.p;
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
