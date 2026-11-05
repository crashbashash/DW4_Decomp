#include "dw4/reflected.h"
extern "C" {
float sqrtf(float);
void Gap__Core__igObject__vfunc_07(void *);
void Gap__Bec__bePadData__vfunc_07(void *);
}
void Gap__Bec__bePadData__vfunc_07(void *self) {
    bePadData *p = (bePadData *)self;
    Gap__Core__igObject__vfunc_07(self);
    /* matching construct: the store/reload and sqrtf(x*x+0) reproduce the retail instruction sequence */
    p->_enaLen = 0.4f; float x = p->_enaLen; float z = 0.0f; float s = x * x; p->_enaLen = sqrtf(s + z);
    p->_adAngle = 0.7853982f;
    p->_1sttime = 10;
    p->_2ndtime = 6;
    p->_lTime = 0; p->_lLast = 0; p->_lStk = 0; p->_lRpt = 0; p->_lTrg = 0;
    p->_rTime = 0; p->_rLast = 0; p->_rStk = 0; p->_rRpt = 0; p->_rTrg = 0;
    p->_rptime = 0; p->_last = 0; p->_repeat = 0; p->_trigger = 0; p->_button = 0;
}
