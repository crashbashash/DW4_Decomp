#include "dw4/reflected.h"
extern "C" {
int Matrix44_Copy(int *, int *);
int beMessenger_AppendMatrix(int, void *);
extern int DAT_004e0ef0[4];
void FUN_0039c1c0(bePoint01 *arg0, bePoint01Info *arg1, int arg2, int arg3);
}
void FUN_0039c1c0(bePoint01 *arg0, bePoint01Info *arg1, int arg2, int arg3) {
    int sp20[16];
    beGroupKeepList *l;
    beGroupKeep *it;
    l = (beGroupKeepList *)arg1->_dataList_;
    if (l->_count - 1 < arg2) {
        arg2 = 0;
    }
    it = ((beGroupKeep **)l->_data)[arg2];
    if (it != 0) {
        beMessenger_AppendMatrix(arg0->_messenger, ((igTransform **)((igObjectList *)it->_childList)->_data)[arg3]->_m);
        return;
    }
    Matrix44_Copy(sp20, &DAT_004e0ef0[0]);
    beMessenger_AppendMatrix(arg0->_messenger, sp20);
}
