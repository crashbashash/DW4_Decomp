#include "dw4/reflected.h"
/* Pad edge detection and auto-repeat; arg0 is the pad data and arg1 is the new button word. */
void FUN_0039af10(bePadData *arg0, int arg1) {
    int temp_a1;
    int temp_v1;
    int var_v1;

    arg0->_last = arg0->_button;
    arg0->_button = arg1;
    temp_a1 = arg0->_button;
    arg0->_trigger = temp_a1 & (arg0->_last ^ temp_a1);
    if ((arg0->_last ^ arg0->_button) != 0) {
        arg0->_repeat = arg0->_trigger;
        arg0->_rptime = arg0->_1sttime;
        return;
    }
    temp_v1 = arg0->_rptime - 1;
    arg0->_rptime = temp_v1;
    if (temp_v1 != 0) {
        arg0->_repeat = 0;
        return;
    }
    arg0->_repeat = arg0->_button;
    arg0->_rptime = arg0->_2ndtime;
}
