#include "dw4/reflected.h"
struct UnidentifiedNameHolder { char pad8[8]; int f8; };
struct UnidentifiedReceiverObject { char pad8[8]; int f8; UnidentifiedNameHolder *f12; };
extern "C" {
int beMessenger_RegisterReceiver(int, UnidentifiedReceiverObject *, void *, int *, int);
extern int DAT_004e0858[4];
extern int DAT_0050feb0[4];
void Gap__Bec__beNumberCtrl__vfunc_29(beNumberCtrl *arg0, UnidentifiedReceiverObject *arg1) {
    int *var_a3;
    int t = arg1->f8;
    var_a3 = (int *)(((UnidentifiedNameHolder *)arg1->f12)->f8);
    var_a3 = var_a3 != 0 ? var_a3 : &DAT_004e0858[0];
    beMessenger_RegisterReceiver(arg0->_messenger, arg1, &DAT_0050feb0[0], var_a3, t);
}
}
