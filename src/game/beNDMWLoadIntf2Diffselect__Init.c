#include "dw4/reflected.h"
void beNDMWLoadIntf2Diffselect__Init(beNDMWLoadIntf2Diffselect *arg0, int arg1, int arg2) {
    arg0->_selectPoint = 0;
    arg0->_result = 0;
    arg0->_plNo = arg2;
    arg0->_result = 0;
    arg0->_kind = arg1;
    arg0->_isEnd = 0;
    arg0->_isCancel = 0;
    arg0->_st0 = 0;
    arg0->_st3 = 0;
    arg0->_st2 = 0;
    arg0->_st1 = 0;
    switch (arg0->_kind) { case 0: arg0->_maxSel = 2; break; case 1: arg0->_maxSel = 3; break; }
}
