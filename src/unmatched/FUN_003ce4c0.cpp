#include "dw4/reflected.h"
/* Plain 3-float output vector (a stack position, not a reflected class). */
/* The retail unit was C++ with exceptions on (it keeps an exception index record);
 * the code is C, so the whole unit keeps C linkage. */
extern "C" {
struct P4B { float x; float y; float z; };
void FUN_003ce4c0(beNDMWPanelObject *arg0, struct P4B *arg1) {
    arg1->x = 150.0f * (float) arg0->_playerNo - 260.0f;
    arg1->y = -160.0f;
    arg1->z = 0.0f;
}
} /* extern "C" */
