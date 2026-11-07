#include "dw4/reflected.h"
extern igMetaObject *DAT_005614d8[4];
extern "C" {
void FUN_00198a40(void);
igMetaObject *FUN_00198960(void);
}
igMetaObject *FUN_00198960(void)
{
    igMetaObject *g = DAT_005614d8[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00198a40();
    return DAT_005614d8[0];
}
