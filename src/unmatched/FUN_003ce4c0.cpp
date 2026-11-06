#include "dw4/reflected.h"
extern "C" {
struct P4B { float x; float y; float z; };
void FUN_003ce4c0(beNDMWPanelObject *arg0, struct P4B *arg1) {
    arg1->x = 150.0f * (float) arg0->_playerNo - 260.0f;
    arg1->y = -160.0f;
    arg1->z = 0.0f;
}
}
