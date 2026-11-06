#include "dw4/reflected.h"
/* Written as C++ with the short-circuit `||` shape. */
extern "C" int FUN_00447b00(beNDMWMdlPEBaseInfoWork *owner)
{
    if (owner->_timerList == 0 || *(int *)((igDataList *)owner->_timerList)->_data == 0) {
        return 0;
    }
    return 1;
}
