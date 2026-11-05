#include "dw4/reflected.h"
void Gap__Bec__beNDMWStatusPowerSocket__vfunc_25(beNDMWStatusPowerSocket *arg0) {
    switch (arg0->_retCode) {
    case 0:
        arg0->_st1 = 1;
        arg0->_st3 = 0;
        arg0->_st2 = 0;
        break;
    case 1:
    case 2:
        arg0->_st1 = 1;
        arg0->_st3 = 0;
        arg0->_st2 = 0;
        arg0->_st3 = 1;
        break;
    }
}
