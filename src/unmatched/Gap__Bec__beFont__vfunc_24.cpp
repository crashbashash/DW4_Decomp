#include "dw4/reflected.h"
extern "C" {
int Gap__Core__igObject__vfunc_24(beFont *);
int igObject_Destroy(igObject *);
void Gap__Bec__beFont__vfunc_24(beFont *arg0);
}

void Gap__Bec__beFont__vfunc_24(beFont *arg0) {
    beFontImageList *l;
    int n;
    int n2;
    int i;
    int j;
    igObject *p;

    l = (beFontImageList *)arg0->_fonts;
    n = l->_count;
    for (i = 0; i < n; i++) {
        p = ((igObject **)l->_data)[i];
        if (p != 0) {
            p->_refCount = p->_refCount - 1;
            if ((p->_refCount & 0x7FFFFF) == 0) {
                igObject_Destroy(p);
            }
        }
    }
    n2 = l->_count;
    for (j = 0; j < n2; j++) {
        ((igObject **)l->_data)[j] = 0;
    }
    l->_count = 0;
    Gap__Core__igObject__vfunc_24(arg0);
}
