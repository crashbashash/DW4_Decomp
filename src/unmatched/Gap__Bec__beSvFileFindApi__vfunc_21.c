#include "dw4/reflected.h"
extern int DAT_0058a600[4];
extern char GPR_00554e60;

void Gap__Bec__beSvFileFindApi__vfunc_21(beSvFileFindApi *arg0, beSvDeliver *arg1) {
    int temp_a2;

    temp_a2 = arg1->_targetConnect;
    if (temp_a2 == -1) {
        arg0->_connect = 0;
        arg0->_isConAllChk = 1;
    } else {
        arg0->_connect = temp_a2;
        arg0->_isConAllChk = 0;
    }
    arg0->_isEnd = 0;
    arg0->_result = 1;
    DAT_0058a600[0] = arg1->_platformData;
    arg0->_st0 = 0;
    arg0->_st3 = 0;
    arg0->_st2 = 0;
    arg0->_st1 = 0;
    GPR_00554e60 = 1;
    *(int *)((char *)(arg0) + 60) = 0;
}
