/* 0x00453a40 - FUN_00453a40. Near-miss sweep fix, verified byte-identical to retail by tools/verify.py. */
#include "dw4/reflected.h"
void FUN_00453a40(igBasicColorChanger *arg0, int arg1, int arg2, int arg3, void *arg4) {
    int var_v1;
    igBasicColorChanger *temp_v1;
    int idx;
    var_v1 = 0;
    if (arg3 != 0) {
        *(float *)&arg0->_disabledColor = (float) *(float *)((char *)(arg4) + 0);
        *(float *)((char *)(arg0) + 76) = (float) *(float *)((char *)(arg4) + 4);
        *(float *)((char *)(arg0) + 80) = (float) *(float *)((char *)(arg4) + 8);
        *(float *)((char *)(arg0) + 84) = (float) *(float *)((char *)(arg4) + 12);
        return;
    }
    if (arg1 != 0) {
        var_v1 += 1;
    }
    if (arg2 != 0) {
        var_v1 += 2;
    }
    idx = var_v1 * 0x10;
    temp_v1 = (igBasicColorChanger *)(idx + (int)arg0);
    *(float *)&temp_v1->_colors[0] = (float) *(float *)((char *)(arg4) + 0);
    *(float *)&temp_v1->_colors[1] = (float) *(float *)((char *)(arg4) + 4);
    *(float *)&temp_v1->_colors[2] = (float) *(float *)((char *)(arg4) + 8);
    *(float *)&temp_v1->_colors[3] = (float) *(float *)((char *)(arg4) + 12);
}
