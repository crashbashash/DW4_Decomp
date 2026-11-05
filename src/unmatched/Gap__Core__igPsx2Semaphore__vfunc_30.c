#include "dw4/reflected.h"
int ReferSemaStatus();
int Gap__Core__igPsx2Semaphore__vfunc_30(igPsx2Semaphore *arg0) {
    int sp[8];
    int temp_v0;
    temp_v0 = arg0->_semaID;
    if (temp_v0 < 0) {
        return arg0->_initCount;
    }
    ReferSemaStatus(temp_v0, sp);
    return sp[0];
}
