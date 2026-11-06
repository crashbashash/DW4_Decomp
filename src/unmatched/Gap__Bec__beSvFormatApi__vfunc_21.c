#include "dw4/reflected.h"
extern char GPR_00554e60;

void Gap__Bec__beSvFormatApi__vfunc_21(beSvFormatApi *arg0, void *arg1) {
    arg0->_isEnd = 0;
    arg0->_connect = (int)((int) *(int *)((char *)(arg1) + 16));
    arg0->_result = 1;
    arg0->_st0 = 0;
    arg0->_st3 = 0;
    arg0->_st2 = 0;
    arg0->_st1 = 0;
    GPR_00554e60 = 1;
    *(int *)((char *)(arg0) + 60) = 0;
}
