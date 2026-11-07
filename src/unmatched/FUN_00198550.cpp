#include "dw4/reflected.h"
extern igMetaObject *DAT_005614b0[4];
extern "C" {
void FUN_00198680(void);
igMetaObject *FUN_00198550(void);
}
igMetaObject *FUN_00198550(void)
{
    igMetaObject *g = DAT_005614b0[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00198680();
    return DAT_005614b0[0];
}
