#include "dw4/reflected.h"
int igMetaObject_CountTree();
void *FUN_002fe300(igMetaObject *arg0, int arg1) {
    int cnt;
    int acc;
    int i;
    int v;
    igMetaObject *k;
    if (arg1 == 0) {
        return arg0;
    }
    if (arg0->_children == 0) {
        return 0;
    }
    cnt = *(int *)(arg0->_children + 12);
    acc = 1;
    for (i = 0; i < cnt; i++) {
        k = ((igMetaObject **)*(int *)(arg0->_children + 8))[i];
        v = igMetaObject_CountTree(k);
        v += acc;
        if (arg1 < v) {
            return FUN_002fe300(k, arg1 - acc);
        }
        acc = v;
    }
    return 0;
}
