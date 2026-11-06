#include "dw4/reflected.h"
void FUN_0017b190(igPsx2VisualContext *arg0, int arg1, int *arg2, int *arg3, int *arg4, int *arg5, char *arg6) {
    void *temp_a0;

    temp_a0 = (void *)(*(int *)((char *)(arg0->_pTexList) + 16) + (arg1 * 0x88));
    *arg2 = *(int *)((char *)(temp_a0) + 116);
    *arg3 = *(int *)((char *)(temp_a0) + 120);
    *arg4 = *(int *)((char *)(temp_a0) + 124);
    *arg5 = *(int *)((char *)(temp_a0) + 128);
    *arg6 = 0;
}
