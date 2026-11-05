#include "dw4/reflected.h"
extern "C" int FUN_00393c80(int, int, int, int, int *);
extern "C" int DAT_004e0858[4];
extern "C" int FUN_003943c0(int arg0, int arg1, int arg2, beModelCtrlLABELCTRL *arg3) {
    int *p = (int *)arg3->_name;
    p = p != 0 ? p : &DAT_004e0858[0];
    FUN_00393c80(arg0, arg1, arg2, arg3->_seqName, p);
    return 1;
}
