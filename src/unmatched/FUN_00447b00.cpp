#include "dw4/reflected.h"
/* 0x00447b00, 56 bytes: true when the object's list at +248 exists and its
 * first element word is nonzero.  Retail is C++ and needs the short-circuit
 * "||" shape under the alternate compiler (-O3,p). */
extern "C" int FUN_00447b00(beNDMWMdlPEBaseInfoWork *owner)
{
    if (owner->_timerList == 0 || *(int *)((igDataList *)owner->_timerList)->_data == 0) {
        return 0;
    }
    return 1;
}
