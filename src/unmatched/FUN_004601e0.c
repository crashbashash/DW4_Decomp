#include "dw4/reflected.h"
int FUN_001b6ce0(void *, float, float, float, float, float);
int FUN_004578c0(void *, int *);
int Matrix44_Copy(void *, void *);
extern int DAT_0058ca20[4];
void FUN_004601e0(igViewerRenderer *arg0) {
    int sp[3];
    igViewerParameters *temp_v1;
    temp_v1 = (igViewerParameters *)arg0->_parameters;
    FUN_001b6ce0((void *)arg0->_sceneTraversal, temp_v1->_hfov, -1.0f, temp_v1->_ratio, temp_v1->_nearPlane, temp_v1->_farPlane);
    Matrix44_Copy(&((igViewerParameters *)arg0->_parameters)->_projectionMatrix[0], (char *)arg0->_sceneTraversal + 0x110);
    sp[0] = 2;
    sp[1] = 0;
    sp[2] = DAT_0058ca20[0];
    FUN_004578c0((void *)arg0->_parameters, sp);
}
