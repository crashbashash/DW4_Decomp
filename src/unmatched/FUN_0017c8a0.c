#include "dw4/reflected.h"
void FUN_00209090(int function, int colorComponent);
extern int DAT_00560a5c[8];
extern int DAT_0048acf0[4];
extern int DAT_00569330[4];
extern int DAT_00569340[4];
extern int * DAT_0056ad80[4];
void FUN_0017c8a0(igPsx2VisualContext *context, int stage, int function, unsigned char colorComponent) {
    int n;
    int j;

    if (stage < 15) {
        n = stage;
    } else {
        n = 15;
    }
    if (n < 8) {
        if (context->_texStageFunc[n] == function) {
            DAT_00560a5c[n] += 1;
        }
    }
    context->_texStageFunc[n] = function;
    if (n > 1) {
        j = n - 1;
    } else {
        j = 0;
    }
    DAT_00569330[0] = n;
    DAT_0056ad80[0] = &DAT_00569340[j * 112];
    context->_bTextureColorComponent = colorComponent;
    FUN_00209090(DAT_0048acf0[function], colorComponent);
    DAT_00569330[0] = 0;
    DAT_0056ad80[0] = DAT_00569340;
}
