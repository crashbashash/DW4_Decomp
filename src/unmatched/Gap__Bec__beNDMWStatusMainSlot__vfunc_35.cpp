#include "dw4/reflected.h"
extern "C" {
int igObject_GetAllocator(void *);
int Memory_GetAllocatorBySelector(int);
beNDMWStatusSelectE0 *FUN_003b5370(int);
igBoolList *FUN_002cb0d0(int);
int beNDMWWindow_BindContext(void *, void *, int, int, int);
int ObjectList_AppendRetained(int, void *);
int FUN_003f5410(void *, int *, int *, int *, int *);
int List_Resize(void *, int, int);
int beMessenger_SelectGroup(int, int *);
int beMessenger_AppendString(int, int *);
int beMessenger_DispatchSelected(int, int *);
void igObject_Destroy(void *);
extern int DAT_005199e0[4];
extern int DAT_005199e8[4];
extern int DAT_00519b50[4];
extern int DAT_00519b60[4];
extern int DAT_00519b68[4];
extern int DAT_00519c28[4];
extern int DAT_00519f68[4];
extern int DAT_00587110[4];
extern unsigned char GPR_00554a20;
extern unsigned char GPR_00554a24;
extern unsigned char GPR_00554a28;
extern unsigned char GPR_00554c14;
}

/* Owning stack reference to the E0 select sub-window created here; released on scope exit
 * (reference count in the low 23 bits of _refCount). */
template <class T> class igSmartPointer {
public:
    T *p;
    igSmartPointer(T *w) : p(w) {}
    ~igSmartPointer() { T *w = p; if (w != 0) { --w->_refCount; if ((w->_refCount & 0x7fffff) == 0) igObject_Destroy(w); } }
};
/* Owning stack reference to the window's new decide list; released on scope exit. */
class BoolListRef {
public:
    igBoolList *p;
    BoolListRef(igBoolList *l) : p(l) {}
    igBoolList *get() const { return p; }
    ~BoolListRef() { igBoolList *l = p; if (l != 0) { --l->_refCount; if ((l->_refCount & 0x7fffff) == 0) igObject_Destroy(l); } }
};
#define REL(P) { igObject *q = (P); if (q != 0) { q->_refCount = q->_refCount - 1; if ((q->_refCount & 0x7fffffU) == 0) { igObject_Destroy(q); } } }
static inline void append(const BoolListRef &list, const unsigned char &value) {
    igBoolList *l = list.p;
    int n = l->_count;
    if (n < l->_capacity) {
        l->_count = n + 1;
    } else {
        List_Resize(l, n + 1, 1);
    }
    ((unsigned char *)l->_data)[n] = value;
}
static inline void setDecideList(const igSmartPointer<beNDMWStatusSelectE0> &win, const BoolListRef &list) {
    igBoolList *l0 = list.p;
    beNDMWStatusSelectE0 *w = win.p;
    if (l0 != 0) {
        l0->_refCount = l0->_refCount + 1;
    }
    REL((igObject *)w->_decideList)
    w->_decideList = (int)l0;
}
extern "C" void Gap__Bec__beNDMWStatusMainSlot__vfunc_35(beNDMWStatusMainSlot *arg0);
extern "C" void Gap__Bec__beNDMWStatusMainSlot__vfunc_35(beNDMWStatusMainSlot *arg0) {
    int a;

    a = igObject_GetAllocator(arg0);
    a = GPR_00554c14 ? a : Memory_GetAllocatorBySelector(DAT_00587110[0]);
    igSmartPointer<beNDMWStatusSelectE0> win(FUN_003b5370(a));
    beNDMWWindow_BindContext(win.p, arg0, arg0->_insight, arg0->_playerNo, 0);
    ObjectList_AppendRetained((unsigned int)arg0->_subWindow, win.p);
    win.p->_selectMax = 2;
    FUN_003f5410(win.p, &DAT_00519b50[0], &DAT_005199e0[0], &DAT_00519b60[0], &DAT_00519b68[0]);
    FUN_003f5410(win.p, &DAT_00519b50[0], &DAT_005199e8[0], &DAT_00519b60[0], &DAT_00519b68[0]);
    a = igObject_GetAllocator(arg0);
    a = GPR_00554c14 ? a : Memory_GetAllocatorBySelector(DAT_00587110[0]);
    BoolListRef decide(FUN_002cb0d0(a));
    setDecideList(win, decide);
    append(decide, GPR_00554a20);
    if (((int *)((beNDMWItemBaseList *)arg0->_apuPocket)->_data)[arg0->_pocketPos] != 0) {
        append(decide, GPR_00554a24);
    } else {
        append(decide, GPR_00554a28);
        beMessenger_SelectGroup(arg0->_messenger, &DAT_00519c28[0]);
        beMessenger_AppendString(arg0->_messenger, &DAT_00519b50[0]);
        beMessenger_AppendString(arg0->_messenger, &DAT_005199e8[0]);
        beMessenger_DispatchSelected(arg0->_messenger, &DAT_00519f68[0]);
    }
}
