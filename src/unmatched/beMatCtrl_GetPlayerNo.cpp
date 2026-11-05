#include "dw4/reflected.h"
extern "C" int beMatCtrl_GetPlayerNo(beMatCtrl *c);
int beMatCtrl_GetPlayerNo(beMatCtrl *c) {
    unsigned char *p = (unsigned char *)c; /* matching construct: separate local byte base keeps the retail operand order of the byte index add; _wkPlExist (+32) is four inline bool bytes, reflected as one int */
    int k;
    int bit;
    int i;
    for (i = 0; i < 4; i++) {
        if (p[i + 32] != 0) {
            k = c->_wkChkMat * 4;
            bit = 1 << i;
            if (bit == (bit & *(unsigned int *)(((igDataList *)c->_wkMatOnList)->_data + k)) && bit != (bit & *(unsigned int *)(((igDataList *)c->_wkMatOldOnList)->_data + k))) return i;
        }
    }
    return 0;
}
