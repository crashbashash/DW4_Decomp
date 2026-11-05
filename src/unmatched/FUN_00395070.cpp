#include "dw4/reflected.h"
extern "C" {
int FUN_003a7a20(...);
int FUN_003a7d80(...);
int igStrCmp(...);
extern int DAT_004e0858[4];
extern int DAT_0050f0b8[4];
extern int DAT_0050f190[4];
extern int DAT_0050f198[4];
extern int DAT_0050f1a0[4];
extern int DAT_0050f1b0[4];
}
struct MutekiNameOf { static int *Get(beModelCtrlMUTEKI *m) { if (m->_name != 0) { return (int *)m->_name; } return &DAT_004e0858[0]; } };
extern "C" int FUN_00395070(int arg0, int arg1, beModelCtrlInfoWork *arg2, beModelCtrlMUTEKI *arg3) {
    if (!(FUN_003a7d80(arg1, &DAT_0050f0b8[0]) & 0xFF)) { FUN_003a7a20(arg1, &DAT_0050f0b8[0], 0); }
    if (igStrCmp(MutekiNameOf::Get(arg3), &DAT_0050f190[0]) == 0) { arg2->_isWallCheck = 0; }
    else if (igStrCmp(MutekiNameOf::Get(arg3), &DAT_0050f198[0]) == 0) { arg2->_isWallCheck = 1; }
    else if (igStrCmp(MutekiNameOf::Get(arg3), &DAT_0050f1a0[0]) == 0) { arg2->_isFloorCheck = 0; }
    else if (igStrCmp(MutekiNameOf::Get(arg3), &DAT_0050f1b0[0]) == 0) { arg2->_isFloorCheck = 1; }
    else { arg2->_mutekiCount = arg3->_frame; }
    return 1;
}
