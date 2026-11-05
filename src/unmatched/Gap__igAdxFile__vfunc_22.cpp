#include "dw4/reflected.h"
extern "C" {
int FUN_00261c88(int);

void Gap__igAdxFile__vfunc_22(igAdxFile *arg0) {
    int temp_a0;

    arg0->_bBufferFilled = 0;
    arg0->_iBufferPos = 0;
    temp_a0 = *(int *)((char *)(arg0) + 96);
    if (temp_a0 != 0) {
        FUN_00261c88(temp_a0);
    }
}
}
