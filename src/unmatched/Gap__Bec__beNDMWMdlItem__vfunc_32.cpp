/* The clear loop has its own counter and bound, declared in the order that gives the right
 * register assignment. */
#include "dw4/reflected.h"
extern "C" {
void igObject_Destroy(igObject *);
void Gap__Bec__beNDMWMdlItem__vfunc_32(beNDMWMdlItem *arg0) {
    igDataList *l;
    int n;
    int i;
    igObject *r;
    int n2;
    int i2;
    l = (igDataList *)arg0->_lockRamList;
    n = l->_count;
    for (i = 0; i < n; i++) {
        r = ((igObject **)l->_data)[i];
        if (r != 0) {
            --r->_refCount;
            if (((unsigned long long)(long long)r->_refCount & 0x7fffffULL) == 0) {
                igObject_Destroy(r);
            }
        }
    }
    n2 = l->_count;
    for (i2 = 0; i2 < n2; i2++) {
        ((igObject **)l->_data)[i2] = 0;
    }
    l->_count = 0;
}
}
