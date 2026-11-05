#include "dw4/reflected.h"
int FUN_00304430();
int FUN_00304680();
int *FUN_00320ea0();
int FUN_00321c10();
extern char DAT_004c2580[];
extern char DAT_004c25b0[];
extern char DAT_004f95c8[];
extern char DAT_004fe7a0[];
extern char DAT_004fe7c0[];
extern char DAT_004fe7f0[];
extern char DAT_004fe820[];
extern char DAT_004fe850[];
extern char DAT_004fe880[];
extern char DAT_004fe8b0[];
extern char DAT_004fe8e0[];
extern char DAT_004fe910[];
extern char DAT_004f7910[];
void FUN_00322240(igElfFile *arg0, int arg1, unsigned char *arg2) {
    int *temp_v0;
    char *var_s0;

    temp_v0 = FUN_00320ea0(arg0, *(unsigned short *)(arg2 + 14));
    if (temp_v0 != 0) {
        var_s0 = (char *)(arg0->_sectionHeaderStringTable + *temp_v0);
    } else {
        var_s0 = DAT_004f7910;
    }
    FUN_00304430(DAT_004fe7a0, arg1);
    FUN_00304680();
    FUN_00304430(DAT_004fe7c0, *(int *)(arg2 + 0), arg0->_symbolStringTable + *(int *)(arg2 + 0));
    FUN_00304680();
    FUN_00304430(DAT_004fe7f0, *(int *)(arg2 + 4));
    FUN_00304680();
    FUN_00304430(DAT_004fe820, *(int *)(arg2 + 8));
    FUN_00304680();
    FUN_00304430(DAT_004fe850, arg2[12]);
    FUN_00304680();
    FUN_00304430(DAT_004fe880, FUN_00321c10(arg2[12] >> 4, DAT_004c2580));
    FUN_00304680();
    FUN_00304430(DAT_004fe8b0, FUN_00321c10(arg2[12] & 0xF, DAT_004c25b0));
    FUN_00304680();
    FUN_00304430(DAT_004fe8e0, arg2[13]);
    FUN_00304680();
    FUN_00304430(DAT_004fe910, *(unsigned short *)(arg2 + 14), var_s0);
    FUN_00304680();
    FUN_00304430(DAT_004f95c8);
    FUN_00304680();
}
