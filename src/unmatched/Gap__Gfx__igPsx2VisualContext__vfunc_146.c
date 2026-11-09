#include "dw4/reflected.h"

int FUN_001e7560(int capability);
void FUN_001e74b0(int capability);
void FUN_001e7500(int capability);
extern int DAT_005609f8;

void Gap__Gfx__igPsx2VisualContext__vfunc_146(igPsx2VisualContext *context, int mode) {
    if (context->_pixelPipelineMode == mode) {
        DAT_005609f8++;
    }
    context->_pixelPipelineMode = mode;
    if (context->_bMultiPassNum > 1 && context->_pixelPipelineMode == 3) {
        if (FUN_001e7560(23) == 0) {
            FUN_001e74b0(23);
        }
    } else {
        if (FUN_001e7560(23) != 0) {
            FUN_001e7500(23);
        }
    }
}
