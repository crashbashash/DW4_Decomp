#include "dw4/reflected.h"
extern "C" {
int FUN_002825e0(int, unsigned int, int);
void FUN_0037e020(beCri *arg0, int arg1);
}

void FUN_0037e020(beCri *arg0, int arg1) {
    if (arg0->_sndfVolume == 0) {
        if (arg1 <= 0 || arg1 > 127) arg1 = 127;
        arg0->_sndfVolume = arg1;
        FUN_002825e0(0, 0xA0010000, arg1);
    }
}
