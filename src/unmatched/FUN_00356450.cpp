#include "dw4/reflected.h"
extern igMetaObject *DAT_00588e28[4];
extern "C" {
void FUN_00356570(void);
igMetaObject *FUN_00356450(void);
}
igMetaObject *FUN_00356450(void)
{
    igMetaObject *g = DAT_00588e28[0];
    bool t;
    if (!g || (t = g->_validity & 4) == 0)
        FUN_00356570();
    return DAT_00588e28[0];
}
