#include "dw4/reflected.h"
extern igMetaObject *DAT_00588b40[4];
extern "C" {
void FUN_00352890(void);
igMetaObject *FUN_00352800(void);
}
igMetaObject *FUN_00352800(void)
{
    igMetaObject *g = DAT_00588b40[0];
    bool t;
    if (!g || (t = g->_validity & 4) == 0)
        FUN_00352890();
    return DAT_00588b40[0];
}
