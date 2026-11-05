#include "dw4/reflected.h"
int FUN_001e74b0();
int FUN_001e7500();
int FUN_001e7560();
int FUN_001fc310();
extern int DAT_00560a04[4];
void FUN_001757c0(igPsx2VisualContext *arg0, int arg1) {
    if (arg0->_bMultiPassNum == arg1) {
        DAT_00560a04[0] += 1;
    }
    arg0->_bMultiPassNum = arg1;
    FUN_001fc310(arg0->_bMultiPassNum);
    if (arg0->_bMultiPassNum > 1 && arg0->_pixelPipelineMode == 3) {
        if (FUN_001e7560(0x17) == 0) {
            FUN_001e74b0(0x17);
        }
    } else if (FUN_001e7560(0x17) != 0) {
        FUN_001e7500(0x17);
    }
}
