
/* igObject header: the reference count at +4 is not a reflected field */
#include "dw4/reflected.h"
extern "C" {
int Gap__Core__igObject__vfunc_08__002ff0f0(beSvReadMediaApi *);
int igObject_Destroy(igObject *);
void Gap__Bec__beSvReadMediaApi__vfunc_08(beSvReadMediaApi *arg0);
}
void Gap__Bec__beSvReadMediaApi__vfunc_08(beSvReadMediaApi *arg0) {
    igObjectList *l = (igObjectList *)arg0->_loadWorkList;
    /* matching construct: volatile read forces the early count load */
    if (((volatile igObjectList *)l)->_count != 0) {
        int n = l->_count;
        int i;
        igObject *t;
        for (i = 0; i < n; i++) {
            t = ((igObject **)l->_data)[i];
            if (t != 0) {
                t->_refCount = (int)t->_refCount - 1;
                if (((unsigned long long) ((long long) (int)t->_refCount << 0x29) >> 0x29) == 0) {
                    igObject_Destroy(t);
                }
            }
        }
        {
            int m = l->_count;
            int j;
            for (j = 0; j < m; j++) {
                ((igObject **)l->_data)[j] = 0;
            }
        }
        l->_count = 0;
    }
    Gap__Core__igObject__vfunc_08__002ff0f0(arg0);
}
