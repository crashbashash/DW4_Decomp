#include "dw4/reflected.h"

extern int DAT_00560910;

void FUN_001f8750(unsigned char enable);

void Gap__Gfx__igPsx2VisualContext__vfunc_110(igPsx2VisualContext *self, int enable)
{
    if (self->_materialSpecularState == (enable & 0xFF))
        DAT_00560910 += 1;
    self->_materialSpecularState = enable;
    FUN_001f8750(enable);
}
