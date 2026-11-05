#include "dw4/reflected.h"
extern igMetaObject *DAT_00588608[4];
extern "C" {
void FUN_0034d160(void);
igMetaObject *FUN_0034d080(void);
}
igMetaObject *FUN_0034d080(void)
{
    igMetaObject *g = DAT_00588608[0];
    bool t;
    if (!g || (t = g->_validity & 4) == 0)
        FUN_0034d160();
    return DAT_00588608[0];
}
