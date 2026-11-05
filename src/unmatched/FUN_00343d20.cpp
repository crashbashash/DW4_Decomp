#include "dw4/reflected.h"
extern igMetaObject *DAT_00587e40[4];
extern "C" {
void FUN_00343e00(void);
igMetaObject *FUN_00343d20(void);
}
igMetaObject *FUN_00343d20(void)
{
    igMetaObject *g = DAT_00587e40[0];
    bool t;
    if (!g || (t = g->_validity & 4) == 0)
        FUN_00343e00();
    return DAT_00587e40[0];
}
