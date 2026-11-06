#include "dw4/reflected.h"
extern "C" {
int igObject_IsKindOf(beShadow01Info *, int);
int FUN_0039e090(beShadow01 *, beShadow01Info *);
int Gap__Core__igObject__vfunc_25(beShadow01 *, beShadow01Info *);
int ObjectList_AppendRetained(int, beShadow01Info *);
extern int DAT_00587ef0[4];
int Gap__Bec__beShadow01__vfunc_25(beShadow01 *arg0, beShadow01Info *arg1);
}
int Gap__Bec__beShadow01__vfunc_25(beShadow01 *arg0, beShadow01Info *arg1) {
    igProjectiveShadowShader *t;

    if (igObject_IsKindOf(arg1, DAT_00587ef0[0]) != 0) {
        t = (igProjectiveShadowShader *)arg1->_projShadowShader;
        if (t != 0) {
            t->_drawReceiver = 0;
            t->_useOrthographic = 1;
            t->_blurState = 0;
            t->_cutoff = 22.5f;
            if (t->_top == 5.0f) {
                t->_top = 100.0f;
                t->_bottom = -100.0f;
                t->_right = 100.0f;
                t->_left = -100.0f;
            }
            FUN_0039e090(arg0, arg1);
            Gap__Core__igObject__vfunc_25(arg0, arg1);
        } else {
            ObjectList_AppendRetained(arg0->_svInfoList, arg1);
        }
        return 1;
    }
    return 0;
}
