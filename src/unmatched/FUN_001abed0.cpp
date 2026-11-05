#include "dw4/reflected.h"
struct Ent { int p[2]; int key; };
struct Rec2 { char p[24]; igObjectList *tbl; };
struct X { int p[2]; Rec2 *r; };
struct Own { int p[2]; int key; };
struct Item { int p[3]; Own *owner; char q[32]; int w; };
class V { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual int vN(); };
/* the receiver is an igCollisionGrid (_activeCells/_staticCollisions/_lostGroups at +12/+48/+52; its caller reads _bound at +56);
   matching construct: the reference fields are 4-byte handles, the casts give the typed views (no layout effect) */
extern "C" void *FUN_001abed0(igCollisionGrid *a0, X *a1, void **out);
void *FUN_001abed0(igCollisionGrid *a0, X *a1, void **out) {
    int i; int j; int cnt; bool seen; Item *it; Own *best; int bestw; bool found; bool f; int k; igObjectList *tbl; int n; igObjectList *lst; int lim; Own *ow; int w; int key; int tc; Ent *e;
    n = ((V *)a0->_activeCells)->vN();
    best = 0;
    bestw = 0;
    found = false;
    tbl = a1->r->tbl;
    for (i = 0; i < n; i++) {
        lst = ((igObjectList **)((igObjectListList *)a0->_staticCollisions)->_data)[i];
        cnt = lst->_count;
        if (cnt > 0) {
            j = cnt - 1;
            lim = ((int *)((igIntList *)a0->_lostGroups)->_data)[i];
            seen = false;
            while (j >= lim) {
                it = ((Item **)lst->_data)[j];
                ow = it->owner;
                if (ow == (Own *)a1) { seen = true; }
                else if (seen) {
                    w = it->w;
                    if (!found || bestw < w) {
                        f = false;
                        key = ow->key;
                        tc = tbl->_count;
                        for (k = 0; k < tc; k++) {
                            e = ((Ent **)tbl->_data)[k];
                            if (key == e->key) {
                                f = true;
                                *out = e;
                                bestw = w;
                                best = ow;
                                found = f;
                                break;
                            }
                        }
                        if (f) break;
                    } else break;
                }
                j--;
            }
        }
    }
    return best;
}
