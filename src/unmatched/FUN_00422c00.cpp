/* 0x00422c00 FUN_00422c00: stable sort (descending by beNDMWItemBase.key) of the object list held by arg1->list,
 * then removal of the entries whose (kind,id) is (0,276), (1,31) or (2,44).
 * Build: alternate compiler (local/mwcps2/combat/mwccps2.exe), flags "-O3,p -Iinclude".
 * Codegen notes (all measured):
 *  - List.count is volatile: retail reloads the count at every use (no CSE/hoist) and keeps data[] hoisted.
 *  - 'd = l->data;' is repeated inside the sort loop: that makes the compiler keep a byte-offset induction
 *    variable (addu base,off) instead of a pointer walk.
 *  - '> -1' / '((Keyed *)t)->key > ((Keyed *)best)->key' spellings give retail's slti-at and operand order.
 *  - one local per loop and per list element (i/i2, t..t5, l2/l3) decides the saved-register colouring.
 *  - the scratch list is owned by a stack reference (ObjectRef) whose address-taken member is reloaded
 *    before every use, like retail's stack slot. */
#include "dw4/reflected.h"
/* The list holds beNDMWItemBase entries (kind _kindNo, record _recNo); the sort key at +20 belongs to the item subclasses and has no reflected
 * name here. The list view stays local: its count is volatile and its data a pointer, which the reflected igObjectList does not express. */
/* The retail unit was C++ with exceptions on (it keeps an exception index record); the code keeps C linkage
 * and owns its one stack object through the ObjectRef below. */
typedef struct Keyed { char hdr[20]; int key; } Keyed;
typedef struct List { int w0; int _refCount; volatile int count; int pad1; beNDMWItemBase **data; } List;
typedef struct Holder { List *list; } Holder;
extern "C" {
void *FUN_003c90f0(void *);
int ObjectList_AppendRetained(int, int);
int ObjectList_RemoveFirstRetained(int *, List *, beNDMWItemBase *, int);
void igObject_Destroy(beNDMWItemBase *);
void List_RemoveWordAt(List *, int);
void *igObject_GetAllocator(void *);
void *Memory_GetAllocatorBySelector(int);
extern int DAT_00587110[4];
extern unsigned char GPR_00554c14;
void FUN_00422c00(void *arg0, Holder *arg1);
}
#define RELEASE(o) { if ((o) != 0) { (o)->_refCount = (o)->_refCount - 1; if (((unsigned long long)((long long)(int)(o)->_refCount << 0x29) >> 0x29) == 0) igObject_Destroy(o); } }
/* Owning stack reference to the scratch list the sort builds into: constructed from the object and released
 * on scope exit (reference count in the low 23 bits of _refCount).  The out-of-line copy the exception table
 * names is the retail body 0x003b6090 (config/SLUS-20836/unit-objects.json, duplicate __dt__9ObjectRefFv). */
class ObjectRef {
public:
    List *p;
    ObjectRef(List *o) : p(o) {}
    ~ObjectRef() { List *o = p; if (o != 0) { --o->_refCount; if ((o->_refCount & 0x7fffff) == 0) igObject_Destroy((beNDMWItemBase *)o); } }
};

void FUN_00422c00(void *arg0, Holder *arg1) {
    void *al;
    List *l;
    List *src;
    beNDMWItemBase **d;
    beNDMWItemBase *best;
    int i;
    beNDMWItemBase *t;
    int n;
    int c;
    int j;
    beNDMWItemBase *e;
    List *l2;
    int k;
    int i2;
    beNDMWItemBase *t2;
    beNDMWItemBase *t3;
    beNDMWItemBase *t4;
    List *l3;
    al = igObject_GetAllocator(arg0);
    al = (GPR_00554c14 != 0) ? al : Memory_GetAllocatorBySelector(DAT_00587110[0]);
    ObjectRef sorted((List *)FUN_003c90f0(al));
    int sp68; /* matching construct: declared after the reference so it takes the slot below it */
    l = arg1->list;
    if (l->count > 0) {
        do {
            d = l->data;
            best = d[0];
            for (i = 1; i < l->count; i++) {
                d = l->data;
                t = d[i];
                if (((Keyed *)t)->key > ((Keyed *)best)->key) best = t;
            }
            ObjectList_AppendRetained((int)sorted.p, (int)best);
            ObjectList_RemoveFirstRetained(&sp68, arg1->list, best, 0);
            l = arg1->list;
        } while (l->count > 0);
    }
    n = l->count;
    for (i2 = 0; i2 < n; i2++) {
        t2 = l->data[i2];
        RELEASE(t2)
    }
    c = l->count;
    for (j = 0; j < c; j++) {
        l->data[j] = 0;
    }
    l->count = 0;
    src = sorted.p;
    while (src->count > 0) {
        ObjectList_AppendRetained((int)arg1->list, (int)src->data[0]);
        src = sorted.p;
        t3 = src->data[0];
        RELEASE(t3)
        List_RemoveWordAt(src, 0);
        src->data[src->count] = 0;
        src = sorted.p;
    }
    for (k = arg1->list->count - 1; k > -1; k--) {
        l2 = arg1->list;
        e = l2->data[k];
        if ((e->_kindNo == 0 && e->_recNo == 276) || (e->_kindNo == 1 && e->_recNo == 31) || (e->_kindNo == 2 && e->_recNo == 44)) {
            ObjectList_AppendRetained((int)l2, (int)e);
            l3 = arg1->list;
            t4 = l3->data[k];
            RELEASE(t4)
            List_RemoveWordAt(l3, k);
            l3->data[l3->count] = 0;
        }
    }
}
