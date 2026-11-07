#include "dw4/reflected.h"
extern int g_beNDMWStatusSubSlot_metaObject[4];

/* Resets the slot's state counters; st1 and st3 end up 1, st2 0 (the _st3 = 0 store is dead but
 * kept). */
void Gap__Bec__beNDMWStatusSubSlot__vfunc_25(beNDMWStatusSubSlot *self) {
    self->_st1 = 1;
    self->_st3 = 0;
    self->_st2 = 0;
    self->_st3 = 1;
}

void Gap__Bec__beNDMWStatusSubSlot__vfunc_39(void)
{
}

void Gap__Bec__beNDMWStatusSubSlot__vfunc_33(void)
{
}

void Gap__Bec__beNDMWStatusSubSlot__vfunc_34(void)
{
}

void Gap__Bec__beNDMWStatusSubSlot__vfunc_35(void)
{
}

void Gap__Bec__beNDMWStatusSubSlot__vfunc_36(void)
{
}

void Gap__Bec__beNDMWStatusSubSlot__vfunc_37(void)
{
}

void Gap__Bec__beNDMWStatusSubSlot__vfunc_38(void)
{
}

/* Class meta-object handle getter */
int Gap__Bec__beNDMWStatusSubSlot__vfunc_20(void)
{
    return g_beNDMWStatusSubSlot_metaObject[0];
}
