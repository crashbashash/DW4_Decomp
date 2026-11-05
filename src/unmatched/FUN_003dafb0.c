/* 0x003dafb0 — FUN_003dafb0. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * Receiver: beNDMWLoadIntf2DataSelIntf (offsets/widths 20,48-52,56,60,72,76-88
 * match its reflected fields). Resets the data-select screen state. */
#include "dw4/reflected.h"
void FUN_003dafb0(beNDMWLoadIntf2DataSelIntf *arg0, int arg1, int arg2) {
    arg0->_plNo = arg1;
    arg0->_isEnd = 0;
    arg0->_kind = arg2;
    arg0->_svDataSelPoint = 0;
    arg0->_isSaveArea = 0;
    arg0->_isUpStatWin = 0;
    arg0->_isDownStatWin = 0;
    arg0->_isSelCur = 0;
    arg0->_st0 = 0;
    arg0->_st3 = 0;
    arg0->_st2 = 0;
    arg0->_st1 = 0;
}
