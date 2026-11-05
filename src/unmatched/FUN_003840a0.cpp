#include "dw4/reflected.h"
/* 0x003840a0 — FUN_003840a0. Hand-retyped from the m2c draft, verified byte-identical to retail by tools/verify.py. */
extern "C" {
int FUN_002eb010(int);
int FUN_003841d0(...);
int StringChunk_ReleaseHeader(...);
int StringPool_Construct(int);
int StringPool_Intern(int, int);
extern int DAT_00586f20[4];
void FUN_003840a0(beFont *arg0, int arg1, int arg2, int arg3);
}
void FUN_003840a0(beFont *p0, int p1, int p2, int p3) {
    int arg2 = p2;
    beFont *arg0 = p0;
    int arg1 = p1;
    int arg3 = p3;
    int *temp_a1;
    int *temp_a1_2;
    int temp_v0;
    int temp_v0_2;
    int var_v0;
    int var_v0_2;
    int temp_v1;
    int temp_v1_2;

    if (DAT_00586f20[0] == 0) {
        var_v0 = FUN_002eb010(0x10);
        if (var_v0 != 0) {
            var_v0 = StringPool_Construct(var_v0);
        }
        DAT_00586f20[0] = var_v0;
    }
    arg2 = StringPool_Intern(DAT_00586f20[0], arg2);
    temp_v1 = arg0->_condition00;
    if (temp_v1 != 0) {
        temp_a1 = (int *)(temp_v1 - 8);
        temp_v0 = *(int *)(temp_v1 - 4) - 1;
        *(int *)(temp_v1 - 4) = temp_v0;
        if (temp_v0 == 0) {
            StringChunk_ReleaseHeader(*temp_a1, temp_a1);
        }
    }
    arg0->_condition00 = arg2;
    if (DAT_00586f20[0] == 0) {
        var_v0_2 = FUN_002eb010(0x10);
        if (var_v0_2 != 0) {
            var_v0_2 = StringPool_Construct(var_v0_2);
        }
        DAT_00586f20[0] = var_v0_2;
    }
    arg3 = StringPool_Intern(DAT_00586f20[0], arg3);
    temp_v1_2 = arg0->_condition01;
    if (temp_v1_2 != 0) {
        temp_a1_2 = (int *)(temp_v1_2 - 8);
        temp_v0_2 = *(int *)(temp_v1_2 - 4) - 1;
        *(int *)(temp_v1_2 - 4) = temp_v0_2;
        if (temp_v0_2 == 0) {
            StringChunk_ReleaseHeader(*temp_a1_2, temp_a1_2);
        }
    }
    arg0->_condition01 = arg3;
    arg0->_history = 0;
    FUN_003841d0(arg0, arg1);
}
