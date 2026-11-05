#include "dw4/reflected.h"
extern "C" {
int FUN_001194c0();
int FUN_0032cf50(int *, int *, int, int, int);
int sceMtapGetConnection(int);
int sceMtapPortOpen(int);
extern int DAT_004c91a0[4];
extern int DAT_00510428[4];
extern int DAT_00510438[4];
extern int DAT_0058a608[4];
extern char GPR_005549dc;
extern unsigned char GPR_00554e58;
extern char GPR_00554e5c;
extern char GPR_00554e60;
extern char GPR_00554e64;
void Gap__Bec__beSvStartApi__vfunc_21(beSvStartApi *arg0, void *arg1);
}

void Gap__Bec__beSvStartApi__vfunc_21(beSvStartApi *arg0, void *arg1) {
    int sp3C;
    int sp38;

    arg0->_isEnd = 0;
    if (GPR_00554e58 == 0) {
        FUN_0032cf50(&sp3C, &DAT_00510428[0], 1, 0, 0);
        FUN_0032cf50(&sp38, &DAT_00510438[0], 1, 0, 0);
        FUN_001194c0();
        GPR_00554e58 = 1;
    }
    sceMtapPortOpen(2);
    DAT_004c91a0[0] = 5;
    DAT_0058a608[0] = *(int *)((char *)(arg1) + 20);
    if (sceMtapGetConnection(2) == 1) {
        GPR_005549dc = 1;
        GPR_00554e5c = 0;
    } else {
        GPR_00554e5c = 0;
        GPR_005549dc = -1;
    }
    GPR_00554e60 = 0;
    GPR_00554e64 = 0;
    *(int *)((char *)(arg0) + 60) = 0;
    arg0->_result = 1;
    arg0->_st0 = 0;
    arg0->_st3 = 0;
    arg0->_st2 = 0;
    arg0->_st1 = 0;
}
