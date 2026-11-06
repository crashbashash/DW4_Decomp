/* Slot-selection screen mark finish (stage 2). The kind switch is written 'case 0: default: <phase
 * switch>; ... case 1: case 2: break;'. The extra 'case 0:' label (its compare folds away) puts a
 * second edge into the default block, so the constant 1 kept in v0 by 'return 1' is not reused for
 * the phase compare and call argument (they get their own t0). */
#include "dw4/reflected.h"
extern "C" {

extern int DAT_00516d30[4];
extern int DAT_00517118[4];
extern int DAT_00517150[4];
extern int DAT_00517160[4];
extern int DAT_00517170[4];
extern int DAT_005171a0[4];
extern void beNDMWLoadIntf2ComMdlCtrl__Close(int, int, void *, void *, int);
extern unsigned char beNDMWLoadIntf2ComMdlCtrl__IsRunning(int, int, void *);
extern unsigned char beNDMWLoadIntf2ComMdlCtrl__IsCloseQueueEmpty(int);
extern void TextOrder_PublishLineListOnly(int, int);

unsigned char beNDMWLoadIntf2SelSlot__Close(beNDMWLoadIntf2SelSlot *self) {
    if (self->_st0 != 2) return 0;
    if (self->_isEnd == 1) return 1;
    switch (self->_kindHard) {
    case 0:
    default:
        switch (self->_st1) {
        case 0:
            if (self->_mode == 0) {
                int i;
                int c;
                beNDMWLoadIntf2ComMdlCtrl__Close(self->_comMdlCtrl, self->_ramNo, DAT_00517118, DAT_00516d30, 1);
                beNDMWLoadIntf2ComMdlCtrl__Close(self->_comMdlCtrl, self->_ramNo, DAT_00517160, DAT_00516d30, 1);
                beNDMWLoadIntf2ComMdlCtrl__Close(self->_comMdlCtrl, self->_ramNo, DAT_00517150, DAT_00516d30, 1);
                c = self->_textOrder;
                TextOrder_PublishLineListOnly(c, (self->_ramNo << 16) | 0x100c);
                TextOrder_PublishLineListOnly(c, (self->_ramNo << 16) | 0x1100);
                TextOrder_PublishLineListOnly(c, (self->_ramNo << 16) | 0x102e);
                for (i = 0; i < 2; i++) {
                    switch (i) {
                    case 0:
                        if (beNDMWLoadIntf2ComMdlCtrl__IsRunning(self->_comMdlCtrl, self->_ramNo * 2, DAT_00517170) == 1)
                            beNDMWLoadIntf2ComMdlCtrl__Close(self->_comMdlCtrl, self->_ramNo * 2, DAT_00517170, DAT_00516d30, 0);
                        break;
                    case 1:
                        if (beNDMWLoadIntf2ComMdlCtrl__IsRunning(self->_comMdlCtrl, self->_ramNo * 2 + 1, DAT_00517170) == 1)
                            beNDMWLoadIntf2ComMdlCtrl__Close(self->_comMdlCtrl, self->_ramNo * 2 + 1, DAT_00517170, DAT_00516d30, 0);
                        break;
                    }
                }
            } else {
                int j;
                int d;
                beNDMWLoadIntf2ComMdlCtrl__Close(self->_comMdlCtrl, self->_ramNo, DAT_00517118, DAT_00516d30, 1);
                beNDMWLoadIntf2ComMdlCtrl__Close(self->_comMdlCtrl, self->_ramNo, DAT_00517160, DAT_00516d30, 1);
                beNDMWLoadIntf2ComMdlCtrl__Close(self->_comMdlCtrl, self->_ramNo, DAT_00517150, DAT_00516d30, 1);
                d = self->_textOrder;
                TextOrder_PublishLineListOnly(d, (self->_ramNo << 16) | 0x100c);
                TextOrder_PublishLineListOnly(d, (self->_ramNo << 16) | 0x1100);
                TextOrder_PublishLineListOnly(d, (self->_ramNo << 16) | 0x102e);
                for (j = 0; j < 5; j++) {
                    switch (j) {
                    case 0:
                        if (beNDMWLoadIntf2ComMdlCtrl__IsRunning(self->_comMdlCtrl, self->_ramNo * 5, DAT_005171a0) == 1)
                            beNDMWLoadIntf2ComMdlCtrl__Close(self->_comMdlCtrl, self->_ramNo * 5, DAT_005171a0, DAT_00516d30, 0);
                        break;
                    case 1:
                        if (beNDMWLoadIntf2ComMdlCtrl__IsRunning(self->_comMdlCtrl, self->_ramNo * 5 + 1, DAT_005171a0) == 1)
                            beNDMWLoadIntf2ComMdlCtrl__Close(self->_comMdlCtrl, self->_ramNo * 5 + 1, DAT_005171a0, DAT_00516d30, 0);
                        break;
                    case 2:
                        if (beNDMWLoadIntf2ComMdlCtrl__IsRunning(self->_comMdlCtrl, self->_ramNo * 5 + 2, DAT_005171a0) == 1)
                            beNDMWLoadIntf2ComMdlCtrl__Close(self->_comMdlCtrl, self->_ramNo * 5 + 2, DAT_005171a0, DAT_00516d30, 0);
                        break;
                    case 3:
                        if (beNDMWLoadIntf2ComMdlCtrl__IsRunning(self->_comMdlCtrl, self->_ramNo * 5 + 3, DAT_005171a0) == 1)
                            beNDMWLoadIntf2ComMdlCtrl__Close(self->_comMdlCtrl, self->_ramNo * 5 + 3, DAT_005171a0, DAT_00516d30, 0);
                        break;
                    case 4:
                        if (beNDMWLoadIntf2ComMdlCtrl__IsRunning(self->_comMdlCtrl, self->_ramNo * 2, DAT_00517170) == 1)
                            beNDMWLoadIntf2ComMdlCtrl__Close(self->_comMdlCtrl, self->_ramNo * 2, DAT_00517170, DAT_00516d30, 0);
                        break;
                    }
                }
            }
            self->_st1 = self->_st1 + 1;
            self->_st3 = 0;
            self->_st2 = 0;
            break;
        case 1:
            if (beNDMWLoadIntf2ComMdlCtrl__IsCloseQueueEmpty(self->_comMdlCtrl) == 1) {
                self->_isEnd = 1;
                self->_st1 = self->_st1 + 1;
                self->_st3 = 0;
                self->_st2 = 0;
            }
            break;
        }
        break;
    case 1:
    case 2:
        break;
    }
    return self->_isEnd;
}
}
