#include "dw4/reflected.h"
extern igMetaObject *DAT_005897f0[4];
extern "C" {
void FUN_00363b70(void);
igMetaObject *FUN_00363ae0(void);
}
igMetaObject *FUN_00363ae0(void)
{
    igMetaObject *g = DAT_005897f0[0];
    bool t;
    if (!g || (t = g->_validity & 4) == 0)
        FUN_00363b70();
    return DAT_005897f0[0];
}
