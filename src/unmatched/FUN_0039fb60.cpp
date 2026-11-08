#include "dw4/reflected.h"
extern "C" {
int strcmp(int, int *);
extern int DAT_004e0858[4];
int FUN_0039fb60(void *arg0, beBaseInfoRam *arg1, int arg2);
}

int FUN_0039fb60(void *arg0, beBaseInfoRam *arg1, int arg2) {
    int i;
    igObjectList *t;
    int n;
    int *p;

    t = (igObjectList *)((beSoundInfo *)arg1->_parentInfo)->_dataList;
    n = t->_count;
    for (i = 0; i < n; i++) {
        p = (int *)((beSoundData **)t->_data)[i]->_name;
        p = p ? p : &DAT_004e0858[0];
        if (strcmp(arg2, p) == 0) {
            return i;
        }
    }
    return -1;
}
