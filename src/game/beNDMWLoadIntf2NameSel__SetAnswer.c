/* NameSel Yes/No answer: _isNameOK = a1, _isAnswer = 1. Receiver is the reflected
 * beNDMWLoadIntf2NameSel (+80 _isNameOK, +79 _isAnswer). */
#include "dw4/reflected.h"
void beNDMWLoadIntf2NameSel__SetAnswer(beNDMWLoadIntf2NameSel *arg0, char arg1) {
    arg0->_isNameOK = arg1;
    arg0->_isAnswer = 1;
}
