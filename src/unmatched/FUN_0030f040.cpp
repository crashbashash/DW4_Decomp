#include "dw4/reflected.h"
#include "dw4/igMemoryPoolView.h"
extern "C" {
extern int DAT_004c2368[4];
int FUN_002dcc50(...);
int igReportNotice(...);
extern int DAT_004c2310[4];
extern int DAT_004c2330[4];
extern int DAT_004c2338[4];
extern int DAT_004c2340[4];
extern int DAT_004c2348[4];
extern int DAT_004c2350[4];
extern int DAT_004c2358[4];
extern int DAT_004fb480[4];
extern int DAT_005871e0[4];
extern int DAT_005871e8[4];
extern int (*DAT_005871f0[4])(void *, int, int, int, int, int, int);
extern unsigned char GPR_00554c34;
}
extern "C" void FUN_0030f040(igArenaMemoryPool *arg0, int arg1, int arg2, int arg3) {
    int temp_v0;
    int temp_v0_2;
    int var_s1;
    int var_s0;

    if ((DAT_005871e8[0] != 0) && (var_s1 = 0, var_s0 = -1, ((DAT_004c2330[0] & arg1) != 0))) {
        if (DAT_004c2338[0] == arg0->_poolIndex) {
            var_s1 |= 1;
        }
        if (arg2 == DAT_004c2340[0]) {
            var_s1 |= 2;
        }
        if (arg3 == DAT_004c2348[0]) {
            var_s1 |= 4;
        }
        if (DAT_005871e0[0] == DAT_004c2350[0]) {
            var_s1 |= 8;
        }
        if (DAT_004c2358[0] != -1) {
            temp_v0 = (int)((igMemoryPoolView *)arg0)->getEventTracker();
            if (temp_v0 != 0) {
                var_s0 = FUN_002dcc50(temp_v0);
                if (var_s0 == DAT_004c2358[0]) {
                    var_s1 |= 0x10;
                }
            }
        }
        if ((var_s1 != 0) && (DAT_005871e8[0] == (DAT_005871e8[0] & var_s1))) {
            if (DAT_005871f0[0] != 0) {
                DAT_005871f0[0](arg0, arg1, arg2, arg3, DAT_005871e0[0], var_s0, var_s1);
                return;
            }
            if ((DAT_004c2368[0] < 4) && (GPR_00554c34 == 0)) {
                temp_v0_2 = igReportNotice(&DAT_004fb480[0], DAT_004c2310[arg1], arg2, arg3, DAT_005871e0[0], var_s0, var_s1);
                if ((temp_v0_2 != 1) && (temp_v0_2 == 2)) {
                    GPR_00554c34 = 1;
                }
            }
        }
    }
}
