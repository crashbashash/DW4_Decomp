#include "dw4/reflected.h"
/* Receiver hypothesis: beNDMWLoadIntf2DegiState (offsets 32/40/44/52..64 match
 * _isEnd/_kind/_dataNo/_st0.._st3; sibling setters FUN_003d9e10/e70/e90 also write +36 =
 * _closeKind). Resets the state to st0 = 3. */
void FUN_003d9e40(beNDMWLoadIntf2DegiState *arg0, int arg1, int arg2) {
    arg0->_kind = arg1;
    arg0->_dataNo = arg2;
    arg0->_isEnd = 0;
    arg0->_st0 = 3;
    arg0->_st3 = 0;
    arg0->_st2 = 0;
    arg0->_st1 = 0;
}
