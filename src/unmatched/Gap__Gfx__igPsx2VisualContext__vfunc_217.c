#include "dw4/reflected.h"
extern unsigned char GPR_00554b50;
extern int DAT_0056098c;
void FUN_001e74b0(int which);
void FUN_001e7500(int which);
void FUN_001747f0(igPsx2VisualContext *self);

void Gap__Gfx__igPsx2VisualContext__vfunc_217(igPsx2VisualContext *self, unsigned char enable)
{
    if (GPR_00554b50 != 0)
        enable = 0;
    if (self->_alphaEnable == enable)
        DAT_0056098c += 1;
    self->_alphaEnable = enable;
    if (enable) {
        FUN_001e74b0(3);
        FUN_001747f0(self);
    } else {
        FUN_001e7500(3);
    }
}
