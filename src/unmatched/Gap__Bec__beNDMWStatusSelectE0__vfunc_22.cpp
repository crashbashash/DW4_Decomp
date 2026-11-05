#include "dw4/reflected.h"
/* The retail unit was C++ with exceptions on (it keeps an exception index record);
 * the code is C, so the whole unit keeps C linkage. */
extern "C" {
int FUN_002eb010(int);
int FUN_003f5410(beNDMWStatusSelectE0 *, int *, int *, int *, int *);
int StringChunk_ReleaseHeader(int, int *);
int StringPool_Construct(int);
int *StringPool_Intern(int, int *);
int beNDMWWindow_RunMessageScript(beNDMWStatusSelectE0 *, int *, int);
extern int DAT_0051a9b8[4];
extern int DAT_0051a9c0[4];
extern int DAT_0051a9c8[4];
extern int DAT_0051a9d0[4];
extern int DAT_0051aa18[4];
extern int DAT_0051aa28[4];
extern int DAT_0051aa30[4];
extern int DAT_0051aa38[4];
extern int DAT_0051aa58[4];
extern int DAT_00586f20[4];
void Gap__Bec__beNDMWStatusSelectE0__vfunc_22(beNDMWStatusSelectE0 *arg0) {
    int *temp_a1;
    int temp_v1;
    int var_v0;
    int *temp_a0;
    int *temp_s0;

    FUN_003f5410(arg0, &DAT_0051aa18[0], &DAT_0051aa28[0], &DAT_0051aa30[0], &DAT_0051aa38[0]);
    FUN_003f5410(arg0, &DAT_0051aa18[0], &DAT_0051a9b8[0], &DAT_0051aa30[0], &DAT_0051aa38[0]);
    FUN_003f5410(arg0, &DAT_0051aa18[0], &DAT_0051a9c0[0], &DAT_0051aa30[0], &DAT_0051aa38[0]);
    FUN_003f5410(arg0, &DAT_0051aa18[0], &DAT_0051a9c8[0], &DAT_0051aa30[0], &DAT_0051aa38[0]);
    if (arg0->_entCode > 0) {
        beNDMWWindow_RunMessageScript(arg0, &DAT_0051a9d0[0], arg0->_entCode);
    }
    if (DAT_00586f20[0] == 0) {
        var_v0 = FUN_002eb010(0x10);
        if (var_v0 != 0) {
            var_v0 = StringPool_Construct(var_v0);
        }
        DAT_00586f20[0] = var_v0;
    }
    temp_s0 = StringPool_Intern(DAT_00586f20[0], &DAT_0051aa58[0]);
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
    arg0->_offsetPos[0] = 0;
    arg0->_offsetPos[1] = 0;
    arg0->_offsetPos[2] = 0;
    arg0->_startPoint = 0;
    arg0->_isNoCancel = 0;
}
} /* extern "C" */
