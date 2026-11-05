#include "dw4/reflected.h"
int beMatCtrl_GetPlayerMatStat(beMatCtrl *m, int n) {
    igIntList *p56;
    igIntList *p60;
    int idx;
    int mask;
    unsigned char b;
    int x;
    int r;
    int a;
    idx = m->_wkChkMat;
    p60 = (igIntList *)m->_wkMatOldOnList;
    x = idx * 4;
    mask = 1 << n;
    b = mask == (mask & *(int *)((char *)p60->_data + x));
    p56 = (igIntList *)m->_wkMatOnList;
    a = mask == (mask & *(int *)((char *)p56->_data + x));
    r = 0;
    if (a == 1 && b == 1) r = 3;
    else if (a == 1 && b != 1) r = 2;
    else if (a != 1 && b == 1) r = 1;
    else if (a != 1 && b != 1) r = 0;
    return r;
}
