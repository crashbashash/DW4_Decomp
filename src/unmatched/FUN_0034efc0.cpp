#include "dw4/reflected.h"
extern igMetaObject *DAT_00588788[4];
extern "C" {
void FUN_0034f0a0(void);
igMetaObject *FUN_0034efc0(void);
}
igMetaObject *FUN_0034efc0(void)
{
    igMetaObject *g = DAT_00588788[0];
    bool t;
    if (!g || (t = g->_validity & 4) == 0)
        FUN_0034f0a0();
    return DAT_00588788[0];
}
