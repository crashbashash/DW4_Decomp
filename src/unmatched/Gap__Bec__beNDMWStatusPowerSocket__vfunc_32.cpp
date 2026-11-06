#include "dw4/reflected.h"
extern "C" {
int FUN_00412600(beNDMWStatusPowerSocket *, int, int, int);

void Gap__Bec__beNDMWStatusPowerSocket__vfunc_32(beNDMWStatusPowerSocket *arg0, int arg1) {
    if (arg1 != -1) {
        FUN_00412600(arg0, arg0->_powerSocket, 0, arg1);
    }
}
}
