#include "dw4/reflected.h"

void beNDMWLoadIntf2DataSelIntf__ClearStatesFrom(beNDMWLoadIntf2DataSelIntf *arg0, int arg1) {
    switch (arg1) {
    default:
        arg0->_st0 = 0;
        arg0->_st3 = 0;
        arg0->_st2 = 0;
        arg0->_st1 = 0;
        return;
    case 1:
        arg0->_st1 = 0;
        arg0->_st3 = 0;
        arg0->_st2 = 0;
        return;
    case 2:
        arg0->_st2 = 0;
        arg0->_st3 = 0;
        return;
    case 3:
        arg0->_st3 = 0;
        return;
    }
}
