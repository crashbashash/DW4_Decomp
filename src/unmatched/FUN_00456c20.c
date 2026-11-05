#include "dw4/reflected.h"
int igObject_Destroy();
int FUN_004578c0();
extern int DAT_0058c408[4];
void FUN_00456c20(igGuiSystemModel *arg0, igGuiComponent *arg1) {
    int sp30[3];
    igGuiComponent *o;
    if (arg1 != 0) {
        arg1->_refCount = arg1->_refCount + 1;
    }
    o = (igGuiComponent *)arg0->_focusedComponent;
    if (o != 0) {
        o->_refCount = o->_refCount - 1;
        if ((o->_refCount & 0x7FFFFF) == 0) {
            igObject_Destroy(o);
        }
    }
    arg0->_focusedComponent = (int)arg1;
    sp30[0] = 2;
    sp30[1] = 0;
    sp30[2] = DAT_0058c408[0];
    FUN_004578c0(arg0, sp30);
}
