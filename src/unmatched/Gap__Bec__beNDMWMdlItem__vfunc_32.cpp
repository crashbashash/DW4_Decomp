/* 0x00441450 - beNDMWMdlItem vfunc 32. Releases every shared object in the list at +48, clears the slots (the compiler unrolls the clear by eight) and resets the count; alternate compiler -O3,p; the clear loop has its own counter and bound, declared in the order that gives retail's registers. */
#include "dw4/reflected.h"
/* The retail unit was C++ with exceptions on (it keeps an exception index record);
 * the code is C, so the whole unit keeps C linkage. */
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
} /* extern "C" */
