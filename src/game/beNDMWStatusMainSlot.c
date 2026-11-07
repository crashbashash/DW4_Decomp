/* Main-equipment slot view of the NDMW status screen. */
#include "dw4/reflected.h"
extern int g_beNDMWStatusMainSlot_metaObject[4];

/* Enter state 1; the later state levels restart at 0 */
void Gap__Bec__beNDMWStatusMainSlot__vfunc_25(beNDMWStatusMainSlot *self) {
    self->_st1 = 1;
    self->_st3 = 0;
    self->_st2 = 0;
}

/* Class metaObject accessor */
int Gap__Bec__beNDMWStatusMainSlot__vfunc_20(void) {
    return g_beNDMWStatusMainSlot_metaObject[0];
}
