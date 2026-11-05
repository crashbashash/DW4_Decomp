#include "dw4/reflected.h"
void beMessenger_SetFreezeTime(beMessenger *arg0, int arg1) {
    if (arg1 != 0) {
        arg0->_freezeTime = (long long) ((igInsightCore *)arg0->_insight)->_worldTime;
        return;
    }
    arg0->_freezeTime = 0;
}
