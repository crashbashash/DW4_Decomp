#include "dw4/reflected.h"
struct SortItem { int w0; int references; int f8; int key; };
/* matching construct: the count is read through a volatile lvalue so it is reloaded at every test, as retail does */
typedef igObjectList VList;
#define VCNT(l) (*(volatile int *)&(l)->_count)
struct SortOwner { VList *list; };
extern "C" {
void *FUN_003c90f0(...);
int List_RemoveWordAt(...);
int Memory_GetAllocatorBySelector(...);
int ObjectList_AppendRetained(...);
int ObjectList_RemoveFirstRetained(...);
int igObject_Destroy(...);
int igObject_GetAllocator(...);
extern int DAT_00587110[4];
extern unsigned char GPR_00554c14;
void FUN_00423000(void *arg0, SortOwner *arg1);
}
/* Owning stack reference to the temporary list; releases it on scope exit. */
struct RP { VList *p; RP(VList *x) : p(x) {} ~RP() { igObject *o = (igObject *)p; if (o != 0) { o->_refCount = o->_refCount - 1; if ((o->_refCount & 0x7fffff) == 0) igObject_Destroy(o); } } };
void FUN_00423000(void *arg0, SortOwner *arg1) {
    int al;
    int v;
    VList *l;
    SortItem *best;
    int i;
    SortItem *c;
    VList *t;
    VList *u;
    VList *l2;
    int n, j;
    int m, k;
    v = igObject_GetAllocator(arg0);
    if (GPR_00554c14 != 0) al = v; else al = Memory_GetAllocatorBySelector(DAT_00587110[0]);
    RP tmp((VList *)FUN_003c90f0(al));
    int sp68;
    l = arg1->list;
    if (VCNT(l) > 0) {
        do {
            l2 = l; /* matching construct: dummy copy re-made at the loop bottom keeps the base out of a pointer induction variable */
            best = ((SortItem **)l2->_data)[0];
            i = 1;
            if (i < VCNT(l)) {
                j = 4;
                do {
                    c = ((SortItem **)(l2->_data + j))[0];
                    if (c->key < best->key) best = c;
                    i++;
                    j += 4; /* matching construct: explicit byte offset */
                    l2 = l;
                } while (i < VCNT(l));
            }
            ObjectList_AppendRetained(tmp.p, best);
            ObjectList_RemoveFirstRetained(&sp68, arg1->list, best, 0);
            l = arg1->list;
        } while (VCNT(l) > 0);
    }
    n = VCNT(l);
    i = 0;
    if (0 < n) {
        j = 0;
        do {
            igObject *o = ((igObject **)(l->_data + j))[0];
            if (o != 0) {
                o->_refCount = o->_refCount - 1;
                if (((unsigned long long)(long long)(int)o->_refCount & 0x7fffffULL) == 0) igObject_Destroy(o);
            }
            i++;
            j += 4;
        } while (i < n);
    }
    m = VCNT(l);
    for (k = 0; k < m; k++) ((int *)l->_data)[k] = 0;
    VCNT(l) = 0;
    t = tmp.p;
    if (VCNT(t) > 0) {
        do {
            ObjectList_AppendRetained(arg1->list, ((int *)t->_data)[0]);
            u = tmp.p;
            igObject *o = ((igObject **)u->_data)[0];
            if (o != 0) {
                o->_refCount = o->_refCount - 1;
                if (((unsigned long long)(long long)(int)o->_refCount & 0x7fffffULL) == 0) igObject_Destroy(o);
            }
            List_RemoveWordAt(u, 0);
            ((int *)u->_data)[VCNT(u)] = 0;
            t = tmp.p;
        } while (VCNT(t) > 0);
    }
}
