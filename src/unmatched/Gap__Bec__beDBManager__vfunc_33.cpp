#include "dw4/reflected.h"
extern "C" {
int FUN_00366070();
int beMessenger_AppendObject(int, int);
int beMessenger_ResolveEnumValue(int, int, int);
int Gap__Bec__beDBManager__vfunc_33(beDBManager *arg0, beBaseInfoRam *arg1, int arg2);
}

int Gap__Bec__beDBManager__vfunc_33(beDBManager *arg0, beBaseInfoRam *arg1, int arg2) {
    beBaseInfoRam *p = (beBaseInfoRam *)arg1->_parentInfo;
    int r;
    switch (beMessenger_ResolveEnumValue(arg0->_messenger, FUN_00366070(), arg2)) {
    case 0:
        beMessenger_AppendObject(arg0->_messenger, p->_st1);
        r = 1;
        break;
    default:
        r = 0;
        break;
    }
    return r;
}
