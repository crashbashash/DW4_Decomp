#include "dw4/typecast.h"
extern int DAT_00586050[4];
int FUN_0022dce0(char *arg0, int arg1, char *arg2, int arg3) {
    char *temp_a0;
    char *temp_v1;

    arg0 = dw4_cast_or_null(arg0, DAT_00586050);
    arg2 = dw4_cast_or_null(arg2, DAT_00586050);
    if ((arg0 != 0) && (arg2 != 0)) {
        temp_a0 = (char *)(arg1 + *(int *)(arg0 + 8));
        temp_v1 = (char *)(arg3 + *(int *)(arg2 + 8));
        *(long long *)temp_v1 = *(long long *)temp_a0;
        return 1;
    }
    return 0;
}
