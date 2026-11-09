#include "dw4/reflected.h"
typedef struct MaterialState { char _pad0[84]; int blendMode; } MaterialState;
void FUN_001e7500(int capability);
void FUN_001e74b0(int capability);
void FUN_001fb0a0(int mode);
extern int DAT_00560914[4];
void Gap__Gfx__igPsx2VisualContext__vfunc_100(igPsx2VisualContext *self, unsigned int mode) {
    if (((MaterialState *)self->_currentMaterial)->blendMode == mode) {
        DAT_00560914[0] += 1;
    }
    ((MaterialState *)self->_currentMaterial)->blendMode = mode;
    switch (mode) {
    case 0:
        FUN_001e7500(12);
        FUN_001fb0a0(0);
        return;
    case 1:
        FUN_001e74b0(12);
        FUN_001fb0a0(1);
        break;
    case 2:
        FUN_001e74b0(12);
        FUN_001fb0a0(4);
        break;
    case 3:
        FUN_001e74b0(12);
        FUN_001fb0a0(5);
        break;
    case 4:
        FUN_001e74b0(12);
        FUN_001fb0a0(3);
        break;
    case 5:
        FUN_001e74b0(12);
        FUN_001fb0a0(2);
        break;
    }
}
