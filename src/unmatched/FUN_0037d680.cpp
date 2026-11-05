#include "dw4/reflected.h"
extern "C" {
int FUN_00280f60(int *);
int FUN_00281078(int, int);
int FUN_002813c8(int);
extern int DAT_0058a360[4];
extern int DAT_0058a3e0[4];
extern int DAT_0058a460[4];
int FUN_0037d680(int arg0, beCriSfpData *arg1);
}

int FUN_0037d680(int arg0, beCriSfpData *arg1) {
    int temp_s2;
    int *temp_s1;
    int temp_s0;
    if (arg1->_isTransfer != 0) {
        return 1;
    }
    temp_s2 = arg1->_portNo;
    temp_s0 = temp_s2 * 4;
    temp_s1 = (int *)((char *)&DAT_0058a360[0] + temp_s0);
    if (*temp_s1 == 0) {
        if (DAT_0058a3e0[temp_s2] != 0) {
            goto block_6;
        }
    } else {
block_6:
        FUN_002813c8(temp_s2);
    }
    *temp_s1 = arg1->_tblSize;
    DAT_0058a3e0[temp_s2] = arg1->_pcmSize;
    if (FUN_00280f60(&DAT_0058a360[0]) < 0) {
        return 0;
    }
    if (FUN_00281078(temp_s2, arg1->_dataBuffer) < 0) {
        return 0;
    }
    DAT_0058a460[temp_s2] = 1;
    return 1;
}
