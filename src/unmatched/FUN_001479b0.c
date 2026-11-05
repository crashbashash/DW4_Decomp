#include "dw4/reflected.h"
void FUN_001479b0(igPsx2Controller *arg0) {
    int i;
    char *p = (char *)arg0;
    for (i = 0; i < 6; i++) {
        *(p + i + 91) = 0;
    }
    for (i = 0; i < 12; i++) {
        *(p + i + 97) = 0;
    }
    for (i = 0; i < 2; i++) {
        arg0->_x[i] = 0;
        arg0->_y[i] = 0;
        *(p + i + 76) = 0;
        *(p + i + 78) = 0;
    }
    arg0->_connected = 0;
    arg0->_buttonState = 0xFFFF;
    arg0->_hasPressure = 0;
    arg0->_phase = 0;
    arg0->_term_id = 0;
    arg0->_lockState = 1;
    arg0->_analogState = 1;
}
