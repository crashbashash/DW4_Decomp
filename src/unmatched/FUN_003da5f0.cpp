#include "dw4/reflected.h"
extern "C" {
int TextOrder_ClearFont(int, int *, int, int);
int TextOrder_PublishLineListOnly(int, int);
extern int DAT_00516c40[4];
extern int DAT_00516c80[4];
extern int DAT_00516c98[4];
void FUN_003da5f0(beNDMWLoadIntf2DegiState *arg0) {
    if (arg0->_dispPos == 0) {
        TextOrder_ClearFont(arg0->_textOrder, &DAT_00516c40[0], arg0->_plNo, 0);
        TextOrder_ClearFont(arg0->_textOrder, &DAT_00516c80[0], arg0->_plNo, 0);
        TextOrder_ClearFont(arg0->_textOrder, &DAT_00516c80[0], arg0->_plNo, 0xA);
        TextOrder_ClearFont(arg0->_textOrder, &DAT_00516c98[0], arg0->_plNo, 0);
        TextOrder_ClearFont(arg0->_textOrder, &DAT_00516c98[0], arg0->_plNo, 0xA);
        TextOrder_ClearFont(arg0->_textOrder, &DAT_00516c98[0], arg0->_plNo, 1);
        TextOrder_ClearFont(arg0->_textOrder, &DAT_00516c98[0], arg0->_plNo, 0xB);
        TextOrder_PublishLineListOnly(arg0->_textOrder, (arg0->_plNo << 0x10) | 0x10);
        return;
    }
    if (arg0->_isUseData == 1) {
        TextOrder_ClearFont(arg0->_textOrder, &DAT_00516c40[0], arg0->_plNo, 0xA);
        TextOrder_ClearFont(arg0->_textOrder, &DAT_00516c80[0], arg0->_plNo, 0xB);
        TextOrder_ClearFont(arg0->_textOrder, &DAT_00516c80[0], arg0->_plNo, 1);
        TextOrder_ClearFont(arg0->_textOrder, &DAT_00516c98[0], arg0->_plNo, 2);
        TextOrder_ClearFont(arg0->_textOrder, &DAT_00516c98[0], arg0->_plNo, 0xC);
        TextOrder_ClearFont(arg0->_textOrder, &DAT_00516c98[0], arg0->_plNo, 3);
        TextOrder_ClearFont(arg0->_textOrder, &DAT_00516c98[0], arg0->_plNo, 0xD);
        return;
    }
    TextOrder_PublishLineListOnly(arg0->_textOrder, (arg0->_plNo << 0x10) | 0x110);
}
}
