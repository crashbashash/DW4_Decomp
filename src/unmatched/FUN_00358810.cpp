#include "dw4/reflected.h"
extern igMetaObject *DAT_00588fe8[4];
extern "C" {
void FUN_003588a0(void);
igMetaObject *FUN_00358810(void);
}
igMetaObject *FUN_00358810(void)
{
    igMetaObject *g = DAT_00588fe8[0];
    bool t;
    if (!g || (t = g->_validity & 4) == 0)
        FUN_003588a0();
    return DAT_00588fe8[0];
}
