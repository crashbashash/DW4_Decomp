#include "dw4/reflected.h"
extern "C" {
extern int DAT_00589ad8[4];
igObject *FUN_00236f80(int, int);
int List_Reserve(igDataList *, int, int);
int igObject_Destroy(igObject *);
void Gap__Bec__beSound__vfunc_32(beSound *arg0);
}
void Gap__Bec__beSound__vfunc_32(beSound *arg0) {
    igDataList *l;
    int n;
    int i;
    igObject *o;
    igDataList *l2;
    if (arg0->_cri == 0) {
        igObject *t = FUN_00236f80(arg0->_insight, DAT_00589ad8[0]);
        igObject *old;
        if (t != 0) {
            t->_refCount = (int)t->_refCount + 1;
        }
        old = (igObject *)arg0->_cri;
        if (old != 0) {
            old->_refCount = (int)old->_refCount - 1;
            if (((unsigned long long)((long long)(int)old->_refCount << 0x29) >> 0x29) == 0) {
                igObject_Destroy(old);
            }
        }
        arg0->_cri = (int)t;
    }
    l = (igDataList *)arg0->_playSEs;
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
    l2 = (igDataList *)arg0->_playSEs;
    if (0 < l2->_count) {
    } else {
        List_Reserve(l2, 0, 4);
    }
}
