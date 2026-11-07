#include "dw4/reflected.h"
extern "C" {
igObject *FUN_00236f80(...);
int igObject_Destroy(...);
extern int DAT_00588518[4];
void Gap__Bec__beNDMWSaveCtrl__vfunc_32(beNDMWSaveCtrl *arg0);
}
void Gap__Bec__beNDMWSaveCtrl__vfunc_32(beNDMWSaveCtrl *arg0) {
    igObject *temp_a0;
    igObject *temp_v0;

    if (arg0->_padManager == 0) {
        temp_v0 = FUN_00236f80(arg0->_insight, DAT_00588518[0]);
        if (temp_v0 != 0) {
            temp_v0->_refCount = temp_v0->_refCount + 1;
            ;
        }
        temp_a0 = (igObject *)arg0->_padManager;
        if (temp_a0 != 0) {
            temp_a0->_refCount = temp_a0->_refCount - 1;
            if ((temp_a0->_refCount & 0x7FFFFF) == 0) {
                igObject_Destroy(temp_a0);
                ;
            }
        }
        arg0->_padManager = (int)temp_v0;
        ;
    }
}