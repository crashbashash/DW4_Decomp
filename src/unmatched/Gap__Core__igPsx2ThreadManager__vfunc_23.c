#include "dw4/reflected.h"
int ChangeThreadPriority();
int FUN_002feeb0();
int GetThreadId();
extern int DAT_00586ca8[4];
int Gap__Core__igPsx2ThreadManager__vfunc_23(igPsx2ThreadManager *arg0) {
    int temp_v0;
    int temp_s1;
    int temp_s2;

    temp_v0 = GetThreadId();
    temp_s2 = ChangeThreadPriority(temp_v0, 1);
    temp_s1 = FUN_002feeb0(arg0->_threadList, DAT_00586ca8[0], GetThreadId());
    ChangeThreadPriority(temp_v0, temp_s2);
    return temp_s1;
}
