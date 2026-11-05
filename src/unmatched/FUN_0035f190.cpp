#include "dw4/reflected.h"
extern igMetaObject *DAT_00589478[4];
extern "C" {
void FUN_0035f2b0(void);
igMetaObject *FUN_0035f190(void);
}
igMetaObject *FUN_0035f190(void)
{
    igMetaObject *g = DAT_00589478[0];
    bool t;
    if (!g || (t = g->_validity & 4) == 0)
        FUN_0035f2b0();
    return DAT_00589478[0];
}
