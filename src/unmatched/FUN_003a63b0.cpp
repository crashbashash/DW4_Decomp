#include "dw4/reflected.h"
extern "C" {
int FUN_003a5b40(beTargetObj *, int, int, int *, int *);
int FUN_003a5cc0(beTargetObj *, int, int, float *, int *, int *, int *);
int FUN_003a5d70(beTargetObj *, int, int, float *, int *, int *, int *);
extern int DAT_0050ffd0[4];
extern int DAT_0050ffd8[4];
extern int DAT_0058a5e0[4];
extern int DAT_0058a5f0[4];
extern int DAT_0058a5f8[4];
int FUN_003a63b0(beTargetObj *arg0, float *arg1, int arg2);
}
int FUN_003a63b0(beTargetObj *arg0, float *arg1, int arg2) {
    float a[3];
    float b[3];

    if (((igVec3fList *)arg0->_playerPosList)->_count == 0) {
        FUN_003a5b40(arg0, arg0->_playerPosList, arg0->_playerRamNoList, &DAT_0050ffd0[0], &DAT_0050ffd8[0]);
        if (((igVec3fList *)arg0->_playerPosList)->_count == 0) {
            return 0;
        }
    }
    if (arg2 != 0) {
        a[0] = arg1[0];
        a[1] = arg1[1];
        a[2] = arg1[2];
        FUN_003a5cc0(arg0, arg0->_playerPosList, arg0->_playerRamNoList, a, &DAT_0058a5e0[0], &DAT_0058a5f0[0], &DAT_0058a5f8[0]);
    } else {
        b[0] = arg1[0];
        b[1] = arg1[1];
        b[2] = arg1[2];
        FUN_003a5d70(arg0, arg0->_playerPosList, arg0->_playerRamNoList, b, &DAT_0058a5e0[0], &DAT_0058a5f0[0], &DAT_0058a5f8[0]);
    }
    return 1;
}
