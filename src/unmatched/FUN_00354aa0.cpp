#include "dw4/reflected.h"
extern igMetaObject *DAT_00588d20[4];
extern "C" {
void FUN_00354b80(void);
igMetaObject *FUN_00354aa0(void);
}
igMetaObject *FUN_00354aa0(void)
{
    igMetaObject *g = DAT_00588d20[0];
    bool t;
    if (!g || (t = g->_validity & 4) == 0)
        FUN_00354b80();
    return DAT_00588d20[0];
}
