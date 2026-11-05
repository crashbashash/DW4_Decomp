#include "dw4/reflected.h"
extern "C" {
int igObject_Destroy(igObject *);
void Gap__Bec__beTimer__vfunc_26(beTimer *arg0);
}
void Gap__Bec__beTimer__vfunc_26(beTimer *arg0) {
    igObjectList *l = (igObjectList *)arg0->_dataList;
    int n = l->_count;
    int i;
    igObject *o;
    for (i = 0; i < n; i++) {
        o = ((igObject **)l->_data)[i];
        if (o != 0) {
            o->_refCount = (int)o->_refCount - 1;
            if (((unsigned long long)((long long)(int)o->_refCount << 0x29) >> 0x29) == 0) {
                igObject_Destroy(o);
            }
        }
    }
    {
        /* matching construct: block-local zero loop */
        int m = l->_count;
        int j;
        for (j = 0; j < m; j++) {
            ((igObject **)l->_data)[j] = 0;
        }
    }
    l->_count = 0;
}
