#include "dw4/reflected.h"
extern "C" {
int beNDMWWindow_ClearQueuedText(...);
int beNDMWWindow_PlayQueuedModelClose(...);
int beNDMWWindow_PollCloseComplete(...);
int beNDMWWindow_RequestChildrenClose(...);

void Gap__Bec__beNDMWWindowTitle__vfunc_21(beNDMWWindowTitle *arg0);
}
class DW4VC_96 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual int vX(); };
void Gap__Bec__beNDMWWindowTitle__vfunc_21(beNDMWWindowTitle *arg0) {
    switch (arg0->_st0) {
    case 0:
        ((DW4VC_96 *)(arg0))->vX();
        arg0->_st0 = (int)((int) (arg0->_st0 + 1));
        arg0->_st3 = 0;
        arg0->_st2 = 0;
        arg0->_st1 = 0;
        break;
    case 1:
        break;
    case 2:
        beNDMWWindow_PlayQueuedModelClose();
        beNDMWWindow_ClearQueuedText(arg0);
        beNDMWWindow_RequestChildrenClose(arg0);
        arg0->_st0 = (int)((int) (arg0->_st0 + 1));
        arg0->_st3 = 0;
        arg0->_st2 = 0;
        arg0->_st1 = 0;
        break;
    case 3:
        if (beNDMWWindow_PollCloseComplete() != 0) {
            arg0->_isRun = 0;
        }
        break;
    }
}
