#include "dw4/reflected.h"
extern "C" {
int FUN_00236c40(int, beNDMWAfsSetup *);
int List_Reserve(igDataList *, int, int);
int igObject_Destroy(igObject *);
void Gap__Bec__beNDMWAfsSetup__vfunc_26(beNDMWAfsSetup *arg0) {
    igDataList *l;
    int n;
    int n2;
    int i;
    int j;
    igObject *p;

    l = (igDataList *)arg0->_infoList;
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
    if (!(0 < ((igDataList *)arg0->_infoList)->_count)) {
        List_Reserve((igDataList *)arg0->_infoList, 0, 4);
    }
    FUN_00236c40(arg0->_insight, arg0);
}
}
