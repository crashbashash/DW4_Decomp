#include "dw4/reflected.h"
extern "C" {
extern int DAT_0050e480[4];
int FUN_0037dc60(beCri *, int *);
int FUN_0037d870(beCri *, int);
int List_Reserve(igDataList *, int, int);
int igObject_Destroy(igObject *);
void Gap__Bec__beCri__vfunc_26(beCri *arg0);
}

void Gap__Bec__beCri__vfunc_26(beCri *arg0) {
    igDataList *l;
    int n;
    int i;
    igObject *o;
    igDataList *l2;
    FUN_0037dc60(arg0, &DAT_0050e480[0]);
    l = (igDataList *)arg0->_infoList;
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
        int m = l->_count;
        int j;
        for (j = 0; j < m; j++) {
            ((igObject **)l->_data)[j] = 0;
        }
    }
    l->_count = 0;
    l2 = (igDataList *)arg0->_infoList;
    if (0 < l2->_count) {
    } else {
        List_Reserve(l2, 0, 4);
    }
    FUN_0037d870(arg0, 0);
}
