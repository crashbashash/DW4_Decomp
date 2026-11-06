#include "dw4/reflected.h"
/* The count is held in a local so the `!= 0 && > 0` test (beqz + slt) is reproduced. */
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
