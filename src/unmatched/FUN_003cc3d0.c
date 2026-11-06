#include "dw4/reflected.h"
void FUN_003cc3d0(igIntList *arg0, int *arg1) {
    int n = arg0->_count;
    int *d = (int *)arg0->_data;
    int i;
    for (i = 0; i < n; i++) {
        d[i] = *arg1;
    }
}
