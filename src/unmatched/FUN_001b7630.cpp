/* Traversal pop: virtual call (slot 33 via 31 dummies after the header words), index list lookup,
 * pop hook with the last item, element count decrement. Alternate compiler -O3. */
#include "dw4/reflected.h"
extern "C" {
int FUN_001b1490(void *, void *, int);
void FUN_001b73d0();
void Gap__Sg__igTraversal__vfunc_24(void *, int);
}
struct Ent { int pad[2]; int count; int pad2; int *items; int pad3[2]; void (*fn)(int, int); };
struct Tab { int pad[4]; Ent **ents; };
struct Mgr { int pad[4]; Tab *tab; int pad2[7]; int arg; int pad3[4]; int *idx; };
/* matching construct: dummy-virtual view so ->f31() dispatches through vtable slot 31 of the traversal */
struct TravView { virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void f31(); };
extern "C" void FUN_001b7630(igCommonTraversal *t, int arg1) {
    Mgr *m;
    int idx;
    Ent *e;
    int v;
    int last;
    FUN_001b73d0();
    if (t->_userTimeState != 0) {
        ((TravView *)t)->f31();
    }
    m = (Mgr *)t->_attrStack;
    idx = ((igTimeAttr *)t->_defaultTimeAttr)->_cachedUnitID + m->idx[((igTimeAttr *)t->_defaultTimeAttr)->_cachedAttrIndex];
    e = m->tab->ents[idx];
    last = e->count - 1; v = e->items[last];
    if (e->fn != 0) {
        e->fn(v, m->arg);
    }
    e->count = e->count - 1;
    FUN_001b1490(m, e, idx);
    Gap__Sg__igTraversal__vfunc_24(t, arg1);
}
