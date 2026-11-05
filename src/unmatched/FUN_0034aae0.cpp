#include "dw4/reflected.h"
extern igMetaObject *DAT_00588370[4];
extern "C" {
void FUN_0034ab30(void);
igMetaObject *FUN_0034aae0(void);
}
igMetaObject *FUN_0034aae0(void)
{
    igMetaObject *g = DAT_00588370[0];
    bool t;
    if (!g || (t = g->_validity & 4) == 0)
        FUN_0034ab30();
    return DAT_00588370[0];
}
