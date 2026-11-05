#include "dw4/reflected.h"
extern "C" {
int List_Reserve(igObjectList *, int, int);
int igObject_Destroy(igObject *);
void Gap__Bec__beDemoManager__vfunc_26(beDemoManager *arg0);
}

void Gap__Bec__beDemoManager__vfunc_26(beDemoManager *arg0) {
    igObjectList *l;
    int n;
    int i;
    igObject *o;
    igObjectList *l2;
    if (arg0->_disableRemoveAll == 1) {
        arg0->_calledRemoveAll = 1;
        return;
    }
    l = (igObjectList *)arg0->_activeDataList;
    n = l->_count;
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
    l2 = (igObjectList *)arg0->_activeDataList;
    /* matching construct: empty then-branch reproduces the retail branch layout */
    if (0 < l2->_count) {
    } else {
        List_Reserve(l2, 0, 4);
    }
    o = (igObject *)arg0->_buildData;
    if (o != 0) {
        o->_refCount = (int)o->_refCount - 1;
        if (((unsigned long long)((long long)(int)o->_refCount << 0x29) >> 0x29) == 0) {
            igObject_Destroy(o);
        }
    }
    arg0->_buildData = 0;
    arg0->_turningOK = 0;
    arg0->_calledRemoveAll = 0;
}
