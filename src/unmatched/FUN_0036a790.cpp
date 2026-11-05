#include "dw4/reflected.h"
extern igMetaObject *DAT_00589db0[4];
extern "C" {
void FUN_0036a820(void);
igMetaObject *FUN_0036a790(void);
}
igMetaObject *FUN_0036a790(void)
{
    igMetaObject *g = DAT_00589db0[0];
    bool t;
    if (!g || (t = g->_validity & 4) == 0)
        FUN_0036a820();
    return DAT_00589db0[0];
}
