#include "dw4/reflected.h"
extern "C" {
void igObject_Destroy(igObject *);
int Gap__Core__igObject__vfunc_24(...);
}
/* matching construct: the inlined refcount release is a static member so the compiler expands it as retail does */
struct ReleaseRefInline { static inline void go(igObject *object) {
    if (object) {
        --object->_refCount;
        if (((unsigned long long)(long long)object->_refCount & 0x7fffffULL) == 0)
            igObject_Destroy(object);
    }
} };
extern "C" void Gap__Bec__beStaticInfoCtl__vfunc_24(beStaticInfoCtl *arg0);
void Gap__Bec__beStaticInfoCtl__vfunc_24(beStaticInfoCtl *arg0) {
    igDataList *l = (igDataList *)arg0->_staticInfoList;
    int n = l->_count;
    int i = 0;
    if (0 < n) {
        do {
            ReleaseRefInline::go(((igObject **)l->_data)[i]);
            i++;
        } while (i < n);
    }
    int n2 = l->_count;
    int v = 0;
    if (0 < n2) {
        int lim;
        if (n2 > 8) {
            lim = n2 - 8;
            do {
                ((int *)l->_data)[v] = 0;
                ((int *)l->_data)[v + 1] = 0;
                ((int *)l->_data)[v + 2] = 0;
                ((int *)l->_data)[v + 3] = 0;
                ((int *)l->_data)[v + 4] = 0;
                ((int *)l->_data)[v + 5] = 0;
                ((int *)l->_data)[v + 6] = 0;
                ((int *)l->_data)[v + 7] = 0;
                v += 8;
            } while (v < lim);
        }
        if (v < n2) {
            do {
                ((int *)l->_data)[v] = 0;
                v++;
            } while (v < n2);
        }
    }
    l->_count = 0;
    Gap__Core__igObject__vfunc_24(arg0);
}
