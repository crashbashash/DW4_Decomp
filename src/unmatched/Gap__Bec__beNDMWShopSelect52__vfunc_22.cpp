#include "dw4/reflected.h"
extern "C" {
int FUN_002eb010(int);
int StringChunk_ReleaseHeader(int, int *);
int StringPool_Construct(int);
void *StringPool_Intern(int, int *);
extern int DAT_0051c7f0[4];
extern int DAT_00586f20[4];
void Gap__Bec__beNDMWShopSelect52__vfunc_22(beNDMWShopSelect52 *arg0) {
    int *temp_a1;
    int temp_v1;
    int var_v0;
    char *temp_a0;
    void *temp_s1;
    if (DAT_00586f20[0] == 0) {
        var_v0 = FUN_002eb010(0x10);
        if (var_v0 != 0) {
            var_v0 = StringPool_Construct(var_v0);
        }
        DAT_00586f20[0] = var_v0;
    }
    temp_s1 = (void *)(StringPool_Intern(DAT_00586f20[0], &DAT_0051c7f0[0]));
    temp_a0 = (char *)arg0->_infoName;
    if (temp_a0 != 0) {
        temp_a1 = (int *)(temp_a0 - 8);
        temp_v1 = *(int *)(temp_a0 - 4) - 1;
        *(int *)(temp_a0 - 4) = temp_v1;
        if (temp_v1 == 0) {
            StringChunk_ReleaseHeader(*temp_a1, temp_a1);
        }
        }
    arg0->_infoName = (int)temp_s1;
    arg0->_selectMax = arg0->_entCode;
    arg0->_startPoint = arg0->_entCode - 1;
    arg0->_isNoCancel = 0;
}
}
