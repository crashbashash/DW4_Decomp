#include "dw4/reflected.h"
int FUN_00448050(igObjectList *arg0, int arg1) {
    int i;
    beNDMWItemDisk **p;
    int n = arg0->_count;
    i = 0;
    if (0 < n) {
        p = (beNDMWItemDisk **)arg0->_data;
        do {
            if (arg1 == (*p)->_recNo) return i;
            i++;
            p++;
        } while (i < n);
    }
    return -1;
}
