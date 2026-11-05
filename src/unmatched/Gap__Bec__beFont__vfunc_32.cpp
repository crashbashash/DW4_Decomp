#include "dw4/reflected.h"
extern "C" {
int FUN_0030b420(int);
int List_Reserve(int, int, int);
int igObject_Destroy(igObject *);
void Gap__Bec__beFont__vfunc_32(beFont *arg0);
}

void Gap__Bec__beFont__vfunc_32(beFont *arg0) {
    beFontGeomAttrPairList *l;
    int n;
    int n2;
    int i;
    int j;
    igObject *p;
    igObject *q;

    q = (igObject *)arg0->_root;
    if (q != 0) {
        q->_refCount = q->_refCount - 1;
        if ((q->_refCount & 0x7FFFFF) == 0) {
            igObject_Destroy(q);
        }
    }
    arg0->_root = 0;
    l = (beFontGeomAttrPairList *)arg0->_gaPairList;
    /* matching construct: volatile re-read of the count */
    if (*(volatile int *)&l->_count > 0) {
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
        if (!(0 < ((beFontGeomAttrPairList *)arg0->_gaPairList)->_count)) {
            List_Reserve(arg0->_gaPairList, 0, 4);
        }
    }
    FUN_0030b420(arg0->_convertData);
}
