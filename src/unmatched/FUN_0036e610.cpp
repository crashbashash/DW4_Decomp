#include "dw4/reflected.h"
extern igMetaObject *DAT_0058a0a0[4];
extern "C" {
void FUN_0036e6d0(void);
igMetaObject *FUN_0036e610(void);
}
igMetaObject *FUN_0036e610(void)
{
    igMetaObject *g = DAT_0058a0a0[0];
    bool t;
    if (!g || (t = g->_validity & 4) == 0)
        FUN_0036e6d0();
    return DAT_0058a0a0[0];
}
