#include "dw4/reflected.h"
/* 0x003b00e0 - Gap__Bec__beTextureCtrl__vfunc_32. Typed fields, 64-bit bitfield compare on a 32-bit load, padding nop after the destroy call. */
typedef struct { int pad0; int rc; } RefObj;
extern "C" {
int igObject_Destroy(RefObj *);
void Gap__Bec__beTextureCtrl__vfunc_32(beTextureCtrl *arg0);
}

void Gap__Bec__beTextureCtrl__vfunc_32(beTextureCtrl *arg0) {
    RefObj *temp_a0;

    arg0->_isFirstTime = 1;
    temp_a0 = (RefObj *)arg0->_work;
    if (temp_a0 != 0) {
        temp_a0->rc = (int)((int) (temp_a0->rc - 1));
        if (((unsigned long long) ((long long) temp_a0->rc << 0x29) >> 0x29) == 0) {
            igObject_Destroy(temp_a0);
            /* matching construct: padding nop after the destroy call, as in retail */
            asm { nop }
        }
    }
    arg0->_work = 0;
}
