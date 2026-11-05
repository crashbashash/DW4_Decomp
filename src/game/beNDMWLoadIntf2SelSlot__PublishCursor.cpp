#include "dw4/reflected.h"
extern "C" {
int beNDMWLoadIntf2ComMdlCtrl__Play(int, int, int *, int, int);
extern int DAT_004cd060[4];
extern int DAT_004cd090[4];
extern int DAT_00517160[4];
struct Entry { int w0; int w4; };
void beNDMWLoadIntf2SelSlot__PublishCursor(beNDMWLoadIntf2SelSlot *arg0, int arg1, int arg2, Entry *arg3) {
    Entry *tbl;
    tbl = arg3;
    arg0->_st0 = 1;
    arg0->_st3 = 0;
    arg0->_st2 = 0;
    arg0->_st1 = 0;
    arg0->_isSelect = 0;
    switch (arg0->_kindHard) {
    default:
        if (arg0->_mode == 0) tbl = (Entry *)DAT_004cd090;
        else tbl = (Entry *)DAT_004cd060;
        break;
    case 1:
    case 2:
        break;
    }
    beNDMWLoadIntf2ComMdlCtrl__Play(arg0->_comMdlCtrl, arg0->_ramNo, DAT_00517160, tbl[arg0->_selPoint].w0, 0);
}
}
