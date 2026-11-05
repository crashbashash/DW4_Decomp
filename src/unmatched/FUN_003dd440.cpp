#include "dw4/reflected.h"
/* Receiver: the shared data-selection interface object (beNDMWLoadIntf2DataSelIntf), called by the matched beNDMWSaveIntf::vfunc_31. */
extern "C" {
extern int DAT_00516d30[4];
extern int DAT_00516d70[4];
extern int DAT_00516d80[4];
extern int DAT_00516d90[4];
extern int DAT_00516da0[4];
extern int DAT_00516db0[4];
extern int DAT_00516dc8[4];
void beNDMWLoadIntf2ComMdlCtrl__Close(int, int, int *, int *, int);
unsigned char beNDMWLoadIntf2ComMdlCtrl__IsCloseQueueEmpty(int);
void TextOrder_ClearFont(int, int *, int, int);
}


extern "C" unsigned char FUN_003dd440(beNDMWLoadIntf2DataSelIntf *arg0, int arg1) {
    int s3; int s2; bool s1; int s0;

    s3 = arg0->_comMdlCtrl;
    s2 = arg0->_textOrder;
    s1 = 0;
    switch (arg1) {
    default:
        s0 = arg0->_st0;
        break;
    case 1:
        s0 = arg0->_st1;
        break;
    case 2:
        s0 = arg0->_st2;
        break;
    case 3:
        s0 = arg0->_st3;
        break;
    }
    switch (s0) {
    case 0:
        if (arg0->_isSaveArea == 1) {
            beNDMWLoadIntf2ComMdlCtrl__Close(s3, arg0->_plNo, DAT_00516d70, DAT_00516d30, 1);
            beNDMWLoadIntf2ComMdlCtrl__Close(s3, arg0->_plNo, DAT_00516d80, DAT_00516d30, 1);
            beNDMWLoadIntf2ComMdlCtrl__Close(s3, arg0->_plNo, DAT_00516d90, DAT_00516d30, 1);
            beNDMWLoadIntf2ComMdlCtrl__Close(s3, arg0->_plNo, DAT_00516da0, DAT_00516d30, 1);
            TextOrder_ClearFont(s2, DAT_00516dc8, arg0->_plNo, 0);
            TextOrder_ClearFont(s2, DAT_00516dc8, arg0->_plNo, 1);
            TextOrder_ClearFont(s2, DAT_00516dc8, arg0->_plNo, 2);
            TextOrder_ClearFont(s2, DAT_00516dc8, arg0->_plNo, 3);
            arg0->_isSaveArea = 0;
        }
        if (arg0->_isSelCur == 1) {
            beNDMWLoadIntf2ComMdlCtrl__Close(s3, arg0->_plNo, DAT_00516db0, DAT_00516d30, 1);
        }
        s0 += 1;
        break;
    case 1:
        if (beNDMWLoadIntf2ComMdlCtrl__IsCloseQueueEmpty(s3) == 1) {
            s1 = 1;
            s0 += 1;
        }
        break;
    case 2:
        s1 = 1;
        break;
    }
    switch (arg1) {
    default:
        arg0->_st0 = s0;
        arg0->_st3 = 0;
        arg0->_st2 = 0;
        arg0->_st1 = 0;
        break;
    case 1:
        arg0->_st1 = s0;
        arg0->_st3 = 0;
        arg0->_st2 = 0;
        break;
    case 2:
        arg0->_st2 = s0;
        arg0->_st3 = 0;
        break;
    case 3:
        arg0->_st3 = s0;
        break;
    }
    return s1;
}
