#include "dw4/reflected.h"
extern "C" {
int FUN_002eb010(int);
int StringChunk_ReleaseHeader(int, int *);
int StringPool_Construct(int);
void *StringPool_Intern(int, int *);
extern int DAT_004e0858[4];
extern int DAT_00586f20[4];
int FUN_00394b30(int arg0, beModelCtrlInfoWork *arg1, igNamedObject *arg2);
}
int FUN_00394b30(int arg0, beModelCtrlInfoWork *arg1, igNamedObject *arg2) {
    int *var_s0;
    int *temp_a1;
    int temp_v0;
    int var_v0;
    void *temp_s0;
    char *temp_v1;
    var_s0 = (int *)arg2->_name;
    var_s0 = var_s0 != 0 ? var_s0 : (int *)(&DAT_004e0858[0]);
    if (DAT_00586f20[0] == 0) {
        var_v0 = FUN_002eb010(0x10);
        if (var_v0 != 0) {
            var_v0 = StringPool_Construct(var_v0);
        }
        DAT_00586f20[0] = var_v0;
    }
    temp_s0 = (void *)(StringPool_Intern(DAT_00586f20[0], var_s0));
    temp_v1 = (char *)arg1->_wCheckName;
    if (temp_v1 != 0) {
        temp_a1 = (int *)(temp_v1 - 8);
        temp_v0 = *(int *)(temp_v1 - 4) - 1;
        *(int *)(temp_v1 - 4) = temp_v0;
        if (temp_v0 == 0) {
            StringChunk_ReleaseHeader(*temp_a1, temp_a1);
        }
    }
    arg1->_wCheckName = (int)temp_s0;
    return 0;
}
