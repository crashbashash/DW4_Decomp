#include "dw4/reflected.h"
extern igMetaObject *DAT_0058ab60[4];
extern "C" {
void FUN_003b3a10(void);
igMetaObject *FUN_003b3940(void);
}
igMetaObject *FUN_003b3940(void)
{
    igMetaObject *g = DAT_0058ab60[0];
    bool t;
    if (!g || (t = g->_validity & 4) == 0)
        FUN_003b3a10();
    return DAT_0058ab60[0];
}
