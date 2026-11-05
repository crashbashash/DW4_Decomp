#include "dw4/reflected.h"
extern igMetaObject *DAT_005881f0[4];
extern "C" {
void FUN_00348b00(void);
igMetaObject *FUN_00348970(void);
}
igMetaObject *FUN_00348970(void)
{
    igMetaObject *g = DAT_005881f0[0];
    bool t;
    if (!g || (t = g->_validity & 4) == 0)
        FUN_00348b00();
    return DAT_005881f0[0];
}
