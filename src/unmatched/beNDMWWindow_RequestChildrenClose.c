#include "dw4/reflected.h"
void beNDMWWindow_RequestChildrenClose(beNDMWWindow *arg0) {
    int n;
    int i;
    beNDMWWindow *t;

    n = ((igDataList *)arg0->_subWindow)->_count;
    for (i = 0; i < n; i++) {
        t = ((beNDMWWindow **)((igDataList *)arg0->_subWindow)->_data)[i];
        if (t->_st0 < 2) {
            t->_st0 = 2;
            t->_st3 = 0;
            t->_st2 = 0;
            t->_st1 = 0;
        }
    }
}
