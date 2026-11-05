#include "dw4/reflected.h"
#include "dw4/typecast.h"
extern int DAT_00560f38[4];
int FUN_0022ce90(char *arg0, int arg1, char *arg2, int arg3) {
    char *temp_a0;
    char *temp_v1;

    arg0 = dw4_cast_or_null(arg0, DAT_00560f38);
    arg2 = dw4_cast_or_null(arg2, DAT_00560f38);
    if ((arg0 != 0) && (arg2 != 0)) {
        temp_a0 = (char *)(arg1 + ((igVec4fMetaField *)arg0)->_offset);
        temp_v1 = (char *)(arg3 + ((igVec4fMetaField *)arg2)->_offset);
        *(float *)(temp_v1 + 0) = *(float *)(temp_a0 + 0);
        *(float *)(temp_v1 + 4) = *(float *)(temp_a0 + 4);
        *(float *)(temp_v1 + 8) = *(float *)(temp_a0 + 8);
        *(float *)(temp_v1 + 12) = *(float *)(temp_a0 + 12);
        return 1;
    }
    return 0;
}
