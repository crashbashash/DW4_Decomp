#include "dw4/reflected.h"
/* The pad object is a bePadData: _lTrg/_lRpt are held, _trigger/_repeat are edges. */
typedef struct VecSrc { char p0[28]; float x, y, z; } VecSrc;
extern "C" int beNDMWLoadIntf2ComMdlCtrl__StartAt(...);
extern "C" int beNDMWLoadIntf2ComMdlCtrl__Play(...);
extern "C" int beNDMWLoadIntf2ComMdlCtrl__IsOpenQueueEmpty(...);
extern "C" int beNDMWLoadIntf2ComMdlCtrl__Close(...);
extern "C" int beNDMWLoadIntf2ComMdlCtrl__IsCloseQueueEmpty(...);
extern "C" int beNDMWLoadIntf2TextOrder_PublishIdLines(...);
extern "C" int TextOrder_PublishLineListOnly(...);
extern "C" int FUN_003ecad0(...);
extern "C" bePadData *bePadManager_GetPadForPlayer(...);
extern "C" int DAT_00516cd0[4];
extern "C" int DAT_00516d40[4];
extern "C" int DAT_00516d50[4];
extern "C" int DAT_00516e18[4];
extern "C" int DAT_00516e28[4];
extern "C" int DAT_00516eb0[4];
extern "C" int DAT_00516ec0[4];
extern "C" int DAT_00516ed0[4];
extern "C" int DAT_00516ee0[4];
extern "C" int DAT_00516ef0[4];
extern "C" int DAT_00516f00[4];
extern "C" unsigned char beNDMWLoadIntf2Diffselect__Update(beNDMWLoadIntf2Diffselect *self, int usePad, int e) {
    float v0[3], v1[3];
    int buttons, h;
    bool u, d;
    int up, down;
    VecSrc *a0;
    void *s1;
    void *s0;
    if (self->_isEnd == 1) return 1;
    a0 = (VecSrc *)self->_comMdlCtrl;
    s1 = (void *)self->_textOrder;
    s0 = (void *)self->_mesWin;
    buttons = 0;
    up = 0;
    down = 0;
    if ((usePad & 0xff) == 1) {
        bePadData *pad = bePadManager_GetPadForPlayer(self->_padManager, self->_plNo);
        buttons = pad->_trigger;
        e = pad->_repeat;
        h = pad->_lTrg | pad->_lRpt;
        u = 1;
        if (h & 1) goto Lu;
        if ((buttons | e) & 0x10) goto Lu;
        u = 0;
    Lu:
        up = u & 0xff;
        d = (h & 4) || ((buttons | e) & 0x40);
        down = d;
    }
    switch (self->_st0) {
    case 0:
        switch (self->_st1) {
        case 0:
            switch (self->_kind) {
            case 0:
                v0[0] = a0->x; v0[1] = a0->y; v0[2] = a0->z;
                beNDMWLoadIntf2ComMdlCtrl__StartAt(a0, self->_plNo, DAT_00516eb0, DAT_00516cd0, v0, 1);
                break;
            case 1:
                v1[0] = a0->x; v1[1] = a0->y; v1[2] = a0->z;
                beNDMWLoadIntf2ComMdlCtrl__StartAt(a0, self->_plNo, DAT_00516ec0, DAT_00516cd0, v1, 1);
                break;
            }
            self->_st1 = self->_st1 + 1; self->_st3 = 0; self->_st2 = 0;
            break;
        case 1:
            if ((beNDMWLoadIntf2ComMdlCtrl__IsOpenQueueEmpty(a0) & 0xff) == 1) {
                switch (self->_kind) {
                case 0: beNDMWLoadIntf2TextOrder_PublishIdLines(s1, (self->_plNo << 16) | 0x402, 0); break;
                case 1: beNDMWLoadIntf2TextOrder_PublishIdLines(s1, (self->_plNo << 16) | 0x403, 0); break;
                }
                FUN_003ecad0(s0, (self->_plNo << 16) | 0x404);
                self->_st0 = self->_st0 + 1; self->_st3 = 0; self->_st2 = 0; self->_st1 = 0;
            }
            break;
        }
        break;
    case 1:
        switch (self->_st1) {
        case 0:
            if (up != 0) {
                self->_selectPoint = self->_selectPoint - 1;
                if (self->_selectPoint < 0) { self->_selectPoint = 0; }
                else {
                    switch (self->_kind) {
                    case 0:
                        beNDMWLoadIntf2ComMdlCtrl__Play(a0, self->_plNo, DAT_00516eb0, DAT_00516ed0, 1);
                        break;
                    case 1:
                        if (self->_selectPoint == 0) beNDMWLoadIntf2ComMdlCtrl__Play(a0, self->_plNo, DAT_00516ec0, DAT_00516ed0, 1);
                        else beNDMWLoadIntf2ComMdlCtrl__Play(a0, self->_plNo, DAT_00516ec0, DAT_00516ee0, 1);
                        break;
                    }
                    self->_st1 = self->_st1 + 1; self->_st3 = 0; self->_st2 = 0;
                }
            } else if (down != 0) {
                self->_selectPoint = self->_selectPoint + 1;
                if (self->_maxSel - 1 < self->_selectPoint) { self->_selectPoint = self->_maxSel - 1; }
                else {
                    switch (self->_kind) {
                    case 0:
                        beNDMWLoadIntf2ComMdlCtrl__Play(a0, self->_plNo, DAT_00516eb0, DAT_00516ef0, 1);
                        break;
                    case 1:
                        if (self->_selectPoint == 1) beNDMWLoadIntf2ComMdlCtrl__Play(a0, self->_plNo, DAT_00516ec0, DAT_00516ef0, 1);
                        else beNDMWLoadIntf2ComMdlCtrl__Play(a0, self->_plNo, DAT_00516ec0, DAT_00516f00, 1);
                        break;
                    }
                    self->_st1 = self->_st1 + 1; self->_st3 = 0; self->_st2 = 0;
                }
            } else if (buttons & 0x4000) {
                self->_result = self->_selectPoint;
                self->_st0 = self->_st0 + 1; self->_st3 = 0; self->_st2 = 0; self->_st1 = 0;
            } else if (buttons & 0x2000) {
                self->_isCancel = 1;
                self->_st0 = self->_st0 + 1; self->_st3 = 0; self->_st2 = 0; self->_st1 = 0;
            }
            break;
        case 1:
            if ((beNDMWLoadIntf2ComMdlCtrl__IsOpenQueueEmpty(a0) & 0xff) == 1) { self->_st1 = 0; self->_st3 = 0; self->_st2 = 0; }
            break;
        }
        break;
    case 2:
        switch (self->_st1) {
        case 0:
            switch (self->_kind) {
            case 0:
                TextOrder_PublishLineListOnly(s1, (self->_plNo << 16) | 0x402);
                if (self->_isCancel == 0) {
                    if (self->_selectPoint == 0) beNDMWLoadIntf2ComMdlCtrl__Close(a0, self->_plNo, DAT_00516eb0, DAT_00516d40, 1);
                    else beNDMWLoadIntf2ComMdlCtrl__Close(a0, self->_plNo, DAT_00516eb0, DAT_00516e18, 1);
                } else beNDMWLoadIntf2ComMdlCtrl__Close(a0, self->_plNo, DAT_00516eb0, DAT_00516d50, 1);
                break;
            case 1:
                TextOrder_PublishLineListOnly(s1, (self->_plNo << 16) | 0x403);
                if (self->_isCancel == 0) {
                    switch (self->_selectPoint) {
                    case 0: beNDMWLoadIntf2ComMdlCtrl__Close(a0, self->_plNo, DAT_00516ec0, DAT_00516d40, 1); break;
                    case 1: beNDMWLoadIntf2ComMdlCtrl__Close(a0, self->_plNo, DAT_00516ec0, DAT_00516e18, 1); break;
                    case 2: beNDMWLoadIntf2ComMdlCtrl__Close(a0, self->_plNo, DAT_00516ec0, DAT_00516e28, 1); break;
                    }
                } else beNDMWLoadIntf2ComMdlCtrl__Close(a0, self->_plNo, DAT_00516ec0, DAT_00516d50, 1);
                break;
            }
            self->_st1 = self->_st1 + 1; self->_st3 = 0; self->_st2 = 0;
            break;
        case 1:
            if ((beNDMWLoadIntf2ComMdlCtrl__IsCloseQueueEmpty(a0) & 0xff) == 1) self->_isEnd = 1;
            break;
        }
        break;
    }
    return self->_isEnd;
}
