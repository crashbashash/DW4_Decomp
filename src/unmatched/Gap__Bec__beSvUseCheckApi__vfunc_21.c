#include "dw4/reflected.h"
extern char GPR_00554e60;

void Gap__Bec__beSvUseCheckApi__vfunc_21(beSvUseCheckApi *arg0, beSvDeliver *arg1) {
    arg0->_connect = (int)((int) arg1->_targetConnect);
    arg0->_isEnd = 0;
    arg0->_result = 1;
    arg0->_st0 = 0;
    arg0->_st3 = 0;
    arg0->_st2 = 0;
    arg0->_st1 = 0;
    GPR_00554e60 = 1;
    *(int *)((char *)(arg0) + 60) = 0;
}
