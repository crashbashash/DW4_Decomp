/* The retail unit was C++ with exceptions on (it keeps an exception index record);
 * the code is C, so the whole unit keeps C linkage. */
extern "C" {
int FUN_002eb010(int);
int StringChunk_ReleaseHeader(int, int *);
int StringPool_Construct(int);
int StringPool_Intern(int, int *);
extern int DAT_0051aa68[4];
extern int DAT_00586f20[4];

#include "dw4/reflected.h"

void Gap__Bec__beNDMWStatusSelectE1__vfunc_22(beNDMWStatusSelectE1 *arg0) {
    int *temp_a1;
    int temp_v1;
    int var_v0;
    int *temp_a0;
    int *temp_s0;

    if (DAT_00586f20[0] == 0) {
        var_v0 = FUN_002eb010(0x10);
        if (var_v0 != 0) {
            var_v0 = StringPool_Construct(var_v0);
        }
        DAT_00586f20[0] = var_v0;
    }
    temp_s0 = (int *)StringPool_Intern(DAT_00586f20[0], &DAT_0051aa68[0]);
    temp_a0 = (int *)arg0->_infoName;
    if (temp_a0 != 0) {
        temp_a1 = temp_a0 - 2;
        temp_v1 = temp_a0[-1] - 1;
        temp_a0[-1] = temp_v1;
        if (temp_v1 == 0) {
            StringChunk_ReleaseHeader(*temp_a1, temp_a1);
        }
    }
    arg0->_infoName = (int)temp_s0;
    arg0->_isNoCancel = 0;
}
} /* extern "C" */
