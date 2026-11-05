#include "dw4/reflected.h"
/* Receiver: beNDMWMdlPEBaseInfoWork (+248 _timerList, an arena ref to a
 * count/capacity/data list; its caller passes the beMessenger_GetObject
 * result, which also reads +260 _poisonEndurance).
 * 0x00447b40, 88 bytes: forwards the second argument and a fixed string to
 * FUN_003a8580, then stores the global word at 0x004cfe80 into the first
 * element of the list at +248 when that list is non-empty.  Alternate
 * compiler (-O3,p); the count is held in a local so the retail
 * "!= 0 && > 0" test (beqz + slt) is reproduced. */
extern "C" void FUN_003a8580(void *, const char *);
extern const char DAT_0051d3f0[16];
extern int DAT_004cfe80[4];

extern "C" void FUN_00447b40(beNDMWMdlPEBaseInfoWork *owner, void *arg)
{
    igDataList *list;
    int n;

    FUN_003a8580(arg, DAT_0051d3f0);
    list = (igDataList *)owner->_timerList;
    n = list->_count;
    if (n != 0 && 0 < n) {
        *(int *)list->_data = DAT_004cfe80[0];
    }
}
