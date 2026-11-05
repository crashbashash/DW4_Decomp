#include "dw4/reflected.h"
extern igMetaObject *DAT_00587c50[4];
extern "C" {
void FUN_00341950(void);
igMetaObject *FUN_00341840(void);
}
igMetaObject *FUN_00341840(void)
{
    igMetaObject *g = DAT_00587c50[0];
    bool t;
    if (!g || (t = g->_validity & 4) == 0)
        FUN_00341950();
    return DAT_00587c50[0];
}
