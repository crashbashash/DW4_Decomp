#include "dw4/reflected.h"
/* Reset of a beNDMWLoadIntf2DegiState (kind/dataNo set, isEnd cleared, st0 = 1, st1..st3 = 0);
 * receiver identified by the +32/+40/+44/+52..+64 layout, see summary. */
void FUN_003d9e10(beNDMWLoadIntf2DegiState *arg0, int arg1, int arg2) {
    arg0->_kind = arg1;
    arg0->_dataNo = arg2;
    arg0->_isEnd = 0;
    arg0->_st0 = 1;
    arg0->_st3 = 0;
    arg0->_st2 = 0;
    arg0->_st1 = 0;
}
